////////////////////////////////////////////////////////////////////////////////
///
/// \file audioIOSWBridge.hpp
/// -------------------------
///
/// Utility functionality that connects the AudioIO and SpectrumWorx libraries
/// to perform several common tasks.
///
/// Copyright (c) 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef audioIOSWBridge_hpp__94252AA7_6f0A_420D_9974_DB3EADE88EAD
#define audioIOSWBridge_hpp__94252AA7_6f0A_420D_9974_DB3EADE88EAD
#pragma once
//------------------------------------------------------------------------------
#include "audioio/device.hpp"
#include "sw_sdk/engine/chainedModuleProcessor.hpp"

#include "osAbstraction.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
///
/// RealTimeOutputContext
///
////////////////////////////////////////////////////////////////////////////////

struct RealTimeOutputContext
{
    AudioIO::BlockingDevice blockingDevice;

    Engine::ChainedModuleProcessor::Ptr pProcessor;

    AudioIO::Device::InterleavedInputData pMainData;
    AudioIO::Device::InterleavedInputData pSideData;
    unsigned int                          numberOfSamples;

    static void callback
    (
        void                                   * pContext       ,
        AudioIO::Device::InterleavedOutputData   pOutputBuffers ,
        unsigned int                             numberOfSamples
    );
};


void RealTimeOutputContext::callback
(
    void                                   * const pContext       ,
    AudioIO::Device::InterleavedOutputData   const pOutputBuffers ,
    unsigned int                                   numberOfSamples
)
{
    RealTimeOutputContext & context( *static_cast<RealTimeOutputContext *>( pContext ) );

    numberOfSamples = std::min( context.numberOfSamples, numberOfSamples );
    context.numberOfSamples -= numberOfSamples;

    context.pProcessor->process
    (
        context.pMainData,
        context.pSideData,
        pOutputBuffers,
        numberOfSamples
    );

    if ( !context.numberOfSamples )
    {
        context.blockingDevice.stop();
        return;
    }

    unsigned int const interleavedSamples( numberOfSamples * context.pProcessor->numberOfChannels() );
                             context.pMainData += interleavedSamples;
    if ( context.pSideData ) context.pSideData += interleavedSamples;
}


////////////////////////////////////////////////////////////////////////////////
///
/// PreprocessedOutputContext
///
////////////////////////////////////////////////////////////////////////////////

struct PreprocessedOutputContext
{
    AudioIO::BlockingDevice               blockingDevice;
    AudioIO::Device::InterleavedInputData pPreprocessedData;
    unsigned int                          numberOfSamples;
    unsigned int                          numberOfChannels;

    static void callback
    (
        void                                   * pContext       ,
        AudioIO::Device::InterleavedOutputData   pOutputBuffers ,
        unsigned int                             numberOfSamples
    );
};


void PreprocessedOutputContext::callback
(
    void                                   * const pContext       ,
    AudioIO::Device::InterleavedOutputData   const pOutputBuffers ,
    unsigned int                                   numberOfSamples
)
{
    PreprocessedOutputContext & context( *static_cast<PreprocessedOutputContext *>( pContext ) );

    numberOfSamples = std::min( context.numberOfSamples, numberOfSamples );

    unsigned int const interleavedSamples( numberOfSamples * context.numberOfChannels );

    std::copy( context.pPreprocessedData, context.pPreprocessedData + interleavedSamples, pOutputBuffers );

    context.numberOfSamples -= numberOfSamples;
    if ( !context.numberOfSamples )
    {
        context.blockingDevice.stop();
        return;
    }

    context.pPreprocessedData += interleavedSamples;
}


////////////////////////////////////////////////////////////////////////////////
///
/// RealTimeInputOutputContext
///
////////////////////////////////////////////////////////////////////////////////

struct RealTimeInputOutputContext
{
    RealTimeInputOutputContext( Engine::ChainedModuleProcessor::Ptr const & pProcessorParam, Engine::ModuleProcessor::InterleavedInputData const pSideDataParam, unsigned int const numberOfSamples )
        :
        pProcessor    ( pProcessorParam ),
        pSideDataBegin( pSideDataParam ),
        pSideDataEnd  ( pSideDataBegin ? pSideDataBegin + numberOfSamples * pProcessor->numberOfChannels() : nullptr ),
        pSideData     ( pSideDataBegin )
    {}

    Engine::ChainedModuleProcessor::Ptr pProcessor;

    Engine::ModuleProcessor::InterleavedInputData const pSideDataBegin;
    Engine::ModuleProcessor::InterleavedInputData const pSideDataEnd  ;
    Engine::ModuleProcessor::InterleavedInputData       pSideData     ;

    static void callback
    (
        void                                   * pContext       ,
        AudioIO::Device::InterleavedInputData    pInputBuffers  ,
        AudioIO::Device::InterleavedOutputData   pOutputBuffers ,
        unsigned int                             numberOfSamples
    );
};


void RealTimeInputOutputContext::callback
(
    void                                   * const pContext       ,
    AudioIO::Device::InterleavedInputData    const pInputBuffers  ,
    AudioIO::Device::InterleavedOutputData   const pOutputBuffers ,
    unsigned int                             const numberOfSamples
)
{
    RealTimeInputOutputContext & context( *static_cast<RealTimeInputOutputContext *>( pContext ) );

    unsigned int const interleavedSamples( numberOfSamples * context.pProcessor->numberOfChannels() );

    if ( ( context.pSideData + interleavedSamples ) > context.pSideDataEnd )
        context.pSideData = context.pSideDataBegin;

    context.pProcessor->process
    (
        pInputBuffers,
        context.pSideData,
        pOutputBuffers,
        numberOfSamples
    );

    if ( context.pSideData ) context.pSideData += interleavedSamples;
}

//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // audioIOSWBridge_hpp

////////////////////////////////////////////////////////////////////////////////
///
/// processingExample.cpp
/// ---------------------
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "audioio/device.hpp"
#include "audioio/inputWaveFile.hpp"
#include "audioio/outputWaveFile.hpp"

#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/chainedModuleProcessor.hpp"

#include "audioIOSWBridge.hpp"
#include "examplePresets.hpp"
#include "osAbstraction.hpp"

#include "boost/assert.hpp"
#include "boost/smart_ptr/scoped_array.hpp"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <ctime>
//------------------------------------------------------------------------------

bool processingExample()
{
    ////////////////////////////////////////////////////////////////////////////
    // Important note: for improved readability, some error handling (memory
    // allocation failures in particular) has been omitted from this example
    // code.
    ////////////////////////////////////////////////////////////////////////////

    using namespace LE;

#ifdef __ANDROID__
    AudioIO::ResourceWaveFile::setResourceManager( OS::getResourceManager() );
#endif // __ANDROID__

    ////////////////////////////////////////////////////////////////////////////
    // Create and setup SW SDK objects.
    ////////////////////////////////////////////////////////////////////////////

    OS::printMessage( "Setting up the SpectrumWorx engine and effects." );

    Engine::ChainedModuleProcessor::Ptr const pProcessor( Engine::ChainedModuleProcessor::create() );

	AudioIO::Device           device;
    AudioIO::ResourceWaveFile inputFile;

    // The preset loop:
    bool finalSuccess( true );
    for
    (
        ExampleCodePreset const * pExamplePreset( ExampleCodePreset::examplePresets() );
        pExamplePreset != NULL;
        pExamplePreset = pExamplePreset->pNextPreset
    )
    {
        OS::printFormattedMessage( "\nOpening preset >> %s <<.\n", pExamplePreset->name );

        BOOST_ASSERT_MSG( pExamplePreset->mainInput, "A preset must specify an input file" );

        typedef float                         sample_t;
        typedef boost::scoped_array<sample_t> Buffer  ;
        typedef AudioIO::error_msg_t          err_t   ;

        // Open and read main input:
        if ( err_t err = inputFile.open( ExampleCodePreset::fullSamplePath( pExamplePreset->mainInput ) ) )
        {
            OS::printFormattedError( "Failed to open main input file: %s (%s, errno: %d).", pExamplePreset->mainInput, err, errno );
            finalSuccess = false;
            continue;
        }

        unsigned int const numberOfMainInputChannels( inputFile.numberOfChannels() );
        unsigned int const numberOfMainInputSamples ( inputFile.remainingSamples() );
        unsigned int const mainInputSampleRate      ( inputFile.sampleRate()       );
        Buffer const pMainInput( new sample_t[ numberOfMainInputChannels * numberOfMainInputSamples ] );

        inputFile.read( pMainInput.get(), numberOfMainInputSamples );

        // Open and read side input (if any):
        unsigned int numberOfOutputSamples( numberOfMainInputSamples );
        Buffer pSideInput;
        if ( pExamplePreset->sideInput )
        {
            unsigned int const numberOfMainInputChannels( inputFile.numberOfChannels() );

            if ( err_t err = inputFile.open( ExampleCodePreset::fullSamplePath( pExamplePreset->sideInput ) ) )
            {
                OS::printFormattedError( "Failed to open side input file: %s (%s, errno: %d).", pExamplePreset->sideInput, err, errno );
                finalSuccess = false;
                continue;
            }

            unsigned int const numberOfSideInputChannels( inputFile.numberOfChannels() );
            unsigned int const numberOfSideInputSamples ( inputFile.remainingSamples() );

            if ( inputFile.sampleRate()    != mainInputSampleRate       ) { OS::printError( "Main and side channel inputs have mismatched sample rates."       ); finalSuccess = false; continue; }
            if ( numberOfSideInputChannels != numberOfMainInputChannels ) { OS::printError( "Main and side channel inputs have mismatched number of channels." ); finalSuccess = false; continue; }

            numberOfOutputSamples = (std::min)( numberOfMainInputSamples, numberOfSideInputSamples );

            pSideInput.reset( new sample_t[ numberOfSideInputChannels * numberOfSideInputSamples ] );

            inputFile.read( pSideInput.get(), numberOfSideInputSamples );
        }

        Buffer const pOutput( new sample_t[ numberOfMainInputChannels * numberOfOutputSamples ] );

        // Setup the ModuleProcessor instance for the current "preset":
        pProcessor->setEngineParameters
        (
            pExamplePreset->fftSize,
            pExamplePreset->overlapFactor,
            Engine::Constants::defaultWindow,
            mainInputSampleRate,
            numberOfMainInputChannels
        );

        // Setup the module chain for the current "preset":
        // - clear the module chain (remove modules from the previous "preset")
        pProcessor->moduleChain().clear();
        // - reset the ModuleProcessor instance for processing of a new stream
        pProcessor->reset();
        // - add new modules/setup the preset
        pExamplePreset->setupEffects( pProcessor->moduleChain(), mainInputSampleRate );

        ////////////////////////////////////////////////////////////////////////
        // Process the data:
        ////////////////////////////////////////////////////////////////////////

        OS::printMessage( " - offline processing..." );

        std::clock_t const startTime( std::clock() );

        pProcessor->process
        (
            pMainInput.get(),
            pSideInput.get(),
            pOutput   .get(),
            numberOfOutputSamples
        );

        unsigned int const totalProcessedSamples( numberOfOutputSamples * numberOfMainInputChannels * ( pSideInput ? 2 : 1 ) );
        float        const elapsedMilliseconds  ( ( std::clock() - startTime ) * 1000.0f / CLOCKS_PER_SEC                    );
        float        const dataMilliseconds     ( numberOfOutputSamples        * 1000.0f / pProcessor->sampleRate()          );
        float        const processingSpeed      ( totalProcessedSamples / elapsedMilliseconds                                );
        float        const processingSpeedRatio ( dataMilliseconds      / elapsedMilliseconds                                );
        OS::printFormattedMessage
        (
            "\tDone: %.2f ms of data, %.2f ms processing time (%.2f ratio, %.0f ksamples/second).\n",
            dataMilliseconds,
            elapsedMilliseconds,
            processingSpeedRatio,
            processingSpeed
        );

        ////////////////////////////////////////////////////////////////////////
        // Save the processed data:
        ////////////////////////////////////////////////////////////////////////

        char const * const fullOutputPath( OS::createFullOutputFilePathWithSuffix( pExamplePreset->mainInput, pExamplePreset->name ) );
        AudioIO::OutputWaveFile outputFile;
        if ( err_t err = outputFile.create( fullOutputPath, numberOfMainInputChannels, mainInputSampleRate ) )
        {
            OS::printFormattedError( "Failed to create output file: %s (%s, errno: %d).", fullOutputPath, err, errno );
            finalSuccess = false;
            continue;
        }

        OS::printFormattedMessage( "\tWriting processed data to %s...\n", fullOutputPath );
        if ( err_t err = outputFile.write( pOutput.get(), numberOfOutputSamples ) )
        {
            OS::printFormattedError( "Failed to write output file (%s, errno: %d).", err, errno );
            finalSuccess = false;
            continue;
        }


        OS::printMessage( " - real time rendering through the hardware audio device..." );
        if ( err_t err = device.setup( numberOfMainInputChannels, mainInputSampleRate, pProcessor->latencyInSamples() ) ) { OS::printError( err ); return false; }
        bool const slowPreset( processingSpeedRatio < 1.5f );
        if ( slowPreset )
        {
            OS::printMessage( "\t...device too slow for realtime processing with the current preset, playing preprocessed data and skipping full duplex rendering..." );
            PreprocessedOutputContext context = { device, pOutput.get(), numberOfOutputSamples, pProcessor->numberOfChannels() };
            if ( err_t err = device.setCallback( &PreprocessedOutputContext::callback, &context ) )
                { OS::printError( err ); finalSuccess = false; }
            else
            {
                pProcessor->reset();
                context.blockingDevice.startAndWait();
            }
        }
        else
        {
            { // Real time processing:
                RealTimeOutputContext context = { device, pProcessor, pMainInput.get(), pSideInput.get(), numberOfOutputSamples };
                if ( err_t err = device.setCallback( &RealTimeOutputContext::callback, &context ) )
                    { OS::printError( err ); finalSuccess = false; }
                else
                {
                    pProcessor->reset();
                    context.blockingDevice.startAndWait();
                }
            }
            {
                OS::printMessage( " - full duplex real time rendering for 10 seconds (please speak into the microphone)..." );
                RealTimeInputOutputContext context( pProcessor, pSideInput.get(), numberOfOutputSamples );
                if ( err_t err = device.setCallback( &RealTimeInputOutputContext::callback, &context ) )
                    { OS::printError( err ); finalSuccess = false; }
                else
                {
                    pProcessor->reset();
                    device.start();
                    OS::sleep( 10 );
                    device.stop ();
                }
            }
        }
        OS::printMessage( "Done." );
    } // preset loop

    return finalSuccess;
}

//------------------------------------------------------------------------------

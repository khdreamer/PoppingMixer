////////////////////////////////////////////////////////////////////////////////
///
/// \file chainedModuleProcessor.hpp
/// --------------------------------
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef chainedModuleProcessor_hpp__B5dE285B_24D4_4C08_9000_E37C997882A9
#define chainedModuleProcessor_hpp__B5dE285B_24D4_4C08_9000_E37C997882A9
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "moduleProcessor.hpp"

#include "common/abi.hpp"
#include "common/pimpl.hpp"

#include "boost/smart_ptr/intrusive_ptr.hpp"

#include "boost/config/abi_prefix.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace Engine
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Engine
#endif // LE_SW_SINGLE_EFFECT
/// @{

////////////////////////////////////////////////////////////////////////////////
///
/// \class ChainedModuleProcessor
///
/// \brief Allows processing with an unlimited number of modules.
///
/// Extends the ModuleProcessor with:
///  - the concept of a ModuleChain through which individual modules can be
///    attached and used for signal processing
///  - global gain and wetness parameters.
///
/// \see ModuleProcessor
///
/// \note
///  - the contents of the module chain may freely be (concurrently) altered
///    during a call to the process() member function(s)
///  - allowed values of configuration parameters:
///    - gain is a plain linear parameter and can be any positive value (default
///      is 1)
///    - wetness percentage can be any value in the [0, 100] range (default is
///      100)
///  - none of its member functions may throw.
///
////////////////////////////////////////////////////////////////////////////////

class ModuleChain;
class ChainedModuleProcessor;

typedef boost::intrusive_ptr<ChainedModuleProcessor> ChainedModuleProcessorPtr;

class ChainedModuleProcessor
    :
#ifdef DOXYGEN_ONLY
    public ModuleProcessor
#else
    public Common::HeapPImpl<ChainedModuleProcessor, ModuleProcessor>
#endif // DOXYGEN_ONLY
{
public:
    /// \brief Returns the gain applied to the output.
    /// Default value 1.
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI gain             () const;

    /// \brief Returns the gain applied to the output in decibels.
    /// Default value 0 dB.
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI gaindB           () const;

    /// \brief Returns the wetness amount, mix between original and transformed
    /// signal.
    /// Supported range is 0 to 1. Default value is 1.
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI wetness          () const;

    /// \brief Returns the wetness percentage, mix between the original and
    /// the transformed signal.
    /// Supported range is 0% to 100%. Default value is 100% wet.
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI wetnessPercentage() const;

    /// Sets the gain to be applied to output.
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI setGain             ( float );
    /// Sets the gain to be applied to output in decibels.
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI setGaindB           ( float );

    /// Sets the wetness.
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI setWetness          ( float );
    /// Sets the wetness in percentages.
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI setWetnessPercentage( float );

public: // Module chain access
    LE_NOTHROWNOALIAS ModuleChain & LE_FASTCALL_ABI moduleChain();

public: // Processing

    ////////////////////////////////////////////////////////////////////////////
    //
    // ChainedModuleProcessor::process()
    // ---------------------------------
    //
    ////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Processes the input samples as separated channels.
    ///
    /// \param mainInputs - pointer to an array of float const pointers, the
    ///                     input data of individual channels (must have at
    ///                     least numberOfChannels() elements)
    /// \param sideInputs - pointer to an array of float const pointers, the
    ///                     input data of individual side channels (must have
    ///                     at least numberOfChannels() elements), can be null
    /// \param outputs    - pointer to an array of float pointers, the output
    ///                     data for individual channels (must have at least
    ///                     numberOfChannels() elements)
    /// \param samples    - number of samples to process from mainChannels and
    ///                     sideInputs (if not null) and to save to outputs;
    ///                     there is no limit on the number of samples processed
    ///                     in one call.
    ///
    /// \note
    ///  - the process() member function is not reentrant and not thread safe
    ///    with respect to any member function that changes one of the engine
    ///    parameters (WOLA, number of channels and/or the sample rate)
    ///  - there is no limit on the amount of data that can be processed in a
    ///    single process() call
    ///
    ////////////////////////////////////////////////////////////////////////////

    void LE_NOTHROWNOALIAS LE_FASTCALL_ABI process
    (
        InputData    mainInputs,
        InputData    sideInputs,
        OutputData   outputs,
        unsigned int samples
    );

    ////////////////////////////////////////////////////////////////////////////
    //
    // ChainedModuleProcessor::process()
    // ---------------------------------
    //
    ////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Processes the input samples as interleaved channels.
    ///
    /// \note This overload has additional overhead compared to the separated
    /// channels version so it is more efficient to use the separated version if
    /// possible.
    ///
    /// \param mainInputs - pointer to an input array of interleaved channels
    ///                     (must have at least numberOfChannels() * samples
    ///                     elements)
    /// \param sideInputs - pointer to an input array of interleaved channels
    ///                     (must have at least numberOfChannels() * samples
    ///                     elements), can be null
    /// \param outputs    - pointer to an output array of interleaved channels
    ///                      (must have at least numberOfChannels() * samples
    ///                     elements)
    /// \param samples    - number of samples to process from mainChannels and
    ///                     sideInputs (if not null) and to save to outputs;
    ///                     there is no limit on the number of samples processed
    ///                     in one call.
    ///
    ////////////////////////////////////////////////////////////////////////////

    void LE_NOTHROWNOALIAS LE_FASTCALL_ABI process
    (
        InterleavedInputData  mainInputs,
        InterleavedInputData  sideInputs,
        InterleavedOutputData outputs,
        unsigned int          samples
    );

    ////////////////////////////////////////////////////////////////////////////
    //
    // ChainedModuleProcessor::reset()
    // -------------------------------
    //
    ////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Resets the processor and the attached modules.
    ///
    ////////////////////////////////////////////////////////////////////////////

    void LE_NOTHROWNOALIAS LE_FASTCALL_ABI reset();

#ifdef DOXYGEN_ONLY
public: // Factory function
    static ChainedModuleProcessorPtr LE_NOTHROW LE_FASTCALL_ABI create();
#endif // DOXYGEN_ONLY
}; // class ChainedModuleProcessor

/** @} */ // group Engine

//------------------------------------------------------------------------------
} /** @} */ // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

#include "boost/config/abi_suffix.hpp"

#endif // chainedModuleProcessor_hpp

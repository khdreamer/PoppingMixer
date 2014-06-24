////////////////////////////////////////////////////////////////////////////////
///
/// \file moduleProcessor.hpp
/// -------------------------
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef moduleProcessor_hpp__FE5806D3_6E72_428F_A861_E6282A232943
#define moduleProcessor_hpp__FE5806D3_6E72_428F_A861_E6282A232943
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "configuration.hpp"

#include "common/abi.hpp"
#include "common/pimpl.hpp"

#include "boost/noncopyable.hpp"
#include "boost/range/iterator_range_core.hpp"
#include "boost/smart_ptr/intrusive_ptr.hpp"

#include "boost/config/abi_prefix.hpp"
//------------------------------------------------------------------------------
namespace LE /// \brief root LE SW SDK namespace
{
//------------------------------------------------------------------------------
#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Engine
#endif // LE_SW_SINGLE_EFFECT
/// @{

/// \brief SW SDK core components
namespace Engine
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Engine
#endif // LE_SW_SINGLE_EFFECT
/// @{

/***************************************************************************//**

 \class ModuleProcessor
 
 \brief The core of the spectral DSP engine.
 
  - processes and transforms input time domain data according to set
    parameters
  - passes the prepared data through attached module(s)
  - post-processes and transforms the resulting data back to the time domain
    as the output data.
 
 Each ModuleProcessor instance as well as any attached modules maintain
 internal state corresponding to the current signal and its history. For this
 reason it is necessary to call the reset() member function on the concrete
 ModuleProcessor instance after processing a stream of data is finished and
 before starting the processing of a new stream of data.
 
 How modules are attached to a given ModuleProcessor depends on the concrete
 class derived from the ModuleProcessor. Each concrete class derived from the
 ModuleProcessor defines the following member functions:

 - \code
  void process
  (
      InputData   mainInputs,
      InputData   sideInputs,
      OutputData  outputs,
      std::size_t samples
  );
 \endcode
 - \code
  void process
  (
      InterleavedInputData  mainInputs,
      InterleavedInputData  sideInputs,
      InterleavedOutputData outputs,
      std::size_t           samples
  );
 \endcode

 - \code void reset(); \endcode

 \note
  - each ModuleProcessor instance is self contained: any number can be
    created and used from different threads
  - please consult the values in \link Engine::Constants \endlink for valid
    ranges of engine parameters
  - to avoid a redundant engine initialization the respective parameter
    defaults are not automatically set on creation and it is therefore
    required that you call the setEngineParameters() member function before
    using a ModuleProcessor instance even if you are satisfied with the
    engine parameters' defaults.

*******************************************************************************/

class ModuleProcessor : public LE::Common::PImpl<ModuleProcessor>
{
public:
    /// \name Processing
    /// @{

    typedef float const * LE_RESTRICT const * LE_RESTRICT InputData            ; ///< A pointer to an array of pointers to read-only input channel data
    typedef float       * LE_RESTRICT const * LE_RESTRICT OutputData           ; ///< A pointer to an array of pointers to output channel data
    typedef float const * LE_RESTRICT                     InterleavedInputData ; ///< A pointer to an array of interleaved read-only input channel data
    typedef float       * LE_RESTRICT                     InterleavedOutputData; ///< A pointer to an array of interleaved output channel data

    /// @}

    typedef Constants::Window Window;

public:
    /// \name Engine setup
    /// @{

    /// \brief The size of input data blocks that are sent to the Fourier
    /// transform.
    /// Shorter values provide lower latency and higher time resolution (faster
    /// changes in the input signal can be captured) while larger values provide
    /// a more accurate frequency analysis at the expense of higher latency and
    /// lower time resolution.
    /// <BR>Supported values are: 128, 256, 512, 1024, 2048, 4096, 8192.
    /// <BR>Default value: 2048.
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI fftSize                () const;

    /// \brief The amount of overlap between consecutive frames of audio data
    /// sent to the Fourier analysis pass. This helps offset the reduced time
    /// resolution with larger frame/FFT sizes and is vital (i.e. the more the
    /// better) for phase vocoder based effects (such as the pitch shifter).
    /// Please note that increasing the window overlapping factor increases the
    /// CPU time consumption accordingly.
    /// <BR>Supported values are: 1 (no overlap), 2, 4, and 8.
    /// <BR>Default value: 4.
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI windowOverlappingFactor() const;

    /// \brief The amount of time advance from frame to frame (effectively
    /// stepSize = fftSize / windowOverlappingFactor). In other words, it is the
    /// time quantum with which the current engine setup operates: dynamic
    /// parameter changes (whether to the ModuleProcessor or the individual
    /// effects) with finer granularity than the value returned by stepSize()
    /// will have no effect (i.e. only the parameter values at the beginning of
    /// each step will be captured/take effect).
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI stepSize               () const;

    /// \brief Returns the type of "window" used to shape the spectral leakage
    /// and frequency resolution.
    /// <BR>Supported values are: Hann, Hamming, Blackman, Blackman Harris,
    /// Gaussian, Flat top, Welch, Triangle and Rectangle.
    /// <BR>Default value: Hann.
    LE_NOTHROWNOALIAS Window       LE_FASTCALL_ABI windowFunction         () const;

    /// \brief Returns the sampling rate of input signal.
    /// Usable values are limited only by available memory.
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI sampleRate             () const;

    /// \brief Returns the number of channels.
    /// Usable values are limited only by available memory.
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI numberOfChannels       () const;

    /// \brief Returns the "ripple" value.
    /// Tells if the current engine settings
    /// will result in a so-called "perfect reconstruction" of the sound - or if
    /// some ripple will be introduced by the engine regardless of the effects
    /// being used. Successive windowed frames should overlap in time in such a
    /// way that all the data is weighted equally - this produces no ripple.
    LE_NOTHROWNOALIAS float        LE_FASTCALL_ABI ripplePercentage       () const;

    /// \brief Returns the latency of the current engine setup in samples
    /// (currently equivalent to the FFT size).
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI latencyInSamples       () const;

    /// \brief Returns the engine latency in milliseconds.
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI latencyInMilliseconds  () const;


    /// Sets the analysis frame size.
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI setFFTSize          ( unsigned int );

    /// Sets the overlapping factor.
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI setOverlappingFactor( unsigned int );

    /// Sets the window function.
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI setWindowFunction   ( Window       );

    /// Sets the sampling rate.
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI setSampleRate       ( unsigned int );

    /// Sets the number of channels.
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI setNumberOfChannels ( unsigned int );


    ////////////////////////////////////////////////////////////////////////////
    //
    // ModuleProcessor::setWOLAParameters()
    // ------------------------------------
    //
    ////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Sets the WOLA engine parameters.
    ///
    /// \param fftSize       - frame size
    /// \param overlapFactor - overlapping factor
    /// \param window        - window type
    ///
    /// Changes to Windowed-Overlap-And-Add parameters (frame size, overlap
    /// factor and window type) are potentially long operations. If possible, it
    /// is more efficient to change them all at once with a single call to
    /// setWOLAParameters() than doing it separately with the dedicated setters.
    /// Note that for the FFT size and overlap factor only power-of-two values
    /// are accepted as valid input.
    ///
    ////////////////////////////////////////////////////////////////////////////

    LE_NOTHROWNOALIAS
    bool LE_FASTCALL_ABI setWOLAParameters
    (
        unsigned int fftSize       = Constants::defaultFFTSize,
        unsigned int overlapFactor = Constants::defaultOverlapFactor,
        Window       window        = Constants::defaultWindow
    );

    ////////////////////////////////////////////////////////////////////////////
    //
    // ModuleProcessor::setEngineParameters()
    // --------------------------------------
    //
    ////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Sets all of the engine parameters.
    ///
    /// Allows changing all of the parameters that require memory allocation
    /// and/or non-trivial interdependent calculations in a single call.
    ///
    ////////////////////////////////////////////////////////////////////////////

    LE_NOTHROWNOALIAS
    bool LE_FASTCALL_ABI setEngineParameters
    (
        unsigned int fftSize          = Constants::defaultFFTSize,
        unsigned int overlapFactor    = Constants::defaultOverlapFactor,
        Window       window           = Constants::defaultWindow,
        unsigned int sampleRate       = Constants::defaultSampleRate,
        unsigned int numberOfChannels = 1
    );

    /// @}
}; // class ModuleProcessor

/// @} // group Engine

//------------------------------------------------------------------------------
} /// @} // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

#include "boost/config/abi_suffix.hpp"

#endif // moduleProcessor_hpp

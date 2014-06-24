////////////////////////////////////////////////////////////////////////////////
///
/// \file standaloneModuleProcessor.hpp
/// -----------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneModuleProcessor_hpp__0F24C2BF_F770_479D_BB0B_4039FE3198EB
#define standaloneModuleProcessor_hpp__0F24C2BF_F770_479D_BB0B_4039FE3198EB
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "moduleFactory.hpp"
#include "moduleProcessor.hpp"

#include "common/abi.hpp"
#include "common/pimpl.hpp"

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
/// \class StandaloneModuleProcessor
///
/// \brief Merges the ModuleProcessor and Module concepts into one interface.
///
/// A ModuleProcessor statically bound with one specific effect: a standalone
/// effect. For projects or parts of projects that require only a single
/// specific effect (known at compile time) it may be simpler (and slightly more
/// efficient) to use this class template instead of the generic
/// ChainedModuleProcessor.
///
/// \see ModuleProcessor
///
////////////////////////////////////////////////////////////////////////////////

template <class Effect>
class StandaloneModuleProcessor
    :
#ifdef DOXYGEN_ONLY
    public ModuleProcessor,
#else
    public Common::HeapPImpl             <StandaloneModuleProcessor<Effect>, ModuleProcessor                              >,
    public Detail::SharedParametersHelper<StandaloneModuleProcessor<Effect>                                               >,
    public Detail::ParameterJoiner       <StandaloneModuleProcessor<Effect>, Effect, Detail::has_Parameters<Effect>::value>,
#endif // DOXYGEN_ONLY
    public Effect
{
public:
    /// \name Parameters
    /// @{
    typedef typename Effects::SharedParameters::Parameters SharedParameters; ///< \brief Basic parameters provided by all effects.
    /// @}

    /// \name Classic parameter accessors
    /// @{
#ifdef DOXYGEN_ONLY
    typedef typename Effect::Parameters Parameters;
    Parameters             & parameters      ()      ;
    Parameters       const & parameters      () const;
#endif // DOXYGEN_ONLY
    SharedParameters       & sharedParameters()       { return *getSharedParameters(); }
    SharedParameters const & sharedParameters() const { return const_cast<StandaloneModuleProcessor &>( *this ).sharedParameters(); }
    /// @}

#ifdef DOXYGEN_ONLY
    /// \name Template parameter accessors
    /// @{
    template <class Parameter> Parameter const & get(                                      ) const;
    template <class Parameter> void              set( typename Parameter::param_type value )      ;
    /// @}
#endif // DOXYGEN_ONLY

    /// \name Hz based/non-normalized accessors for frequency range parameters
    ///@{
    LE_NOTHROWNOALIAS void  LE_FASTCALL_ABI setStartFrequencyInHz( float frequency )      ;
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI getStartFrequencyInHz(                 ) const;
    LE_NOTHROWNOALIAS void  LE_FASTCALL_ABI setStopFrequencyInHz ( float frequency )      ;
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI getStopFrequencyInHz (                 ) const;
    ///@}

public:
    /// \name Processing
    /// @{

    void LE_NOTHROWNOALIAS LE_FASTCALL_ABI process /// \copydoc ChainedModuleProcessor::process( InputData, InputData, OutputData, unsigned int )
    (
        ModuleProcessor::InputData  mainInputs,
        ModuleProcessor::InputData  sideInputs,
        ModuleProcessor::OutputData outputs,
        unsigned int                samples
    );

    void LE_NOTHROWNOALIAS LE_FASTCALL_ABI process /// \copydoc ChainedModuleProcessor::process( InterleavedInputData, InterleavedInputData, InterleavedOutputData, unsigned int )
    (
        ModuleProcessor::InterleavedInputData  mainInputs,
        ModuleProcessor::InterleavedInputData  sideInputs,
        ModuleProcessor::InterleavedOutputData outputs,
        unsigned int                           samples
    );


    ////////////////////////////////////////////////////////////////////////////
    //
    // StandaloneModuleProcessor::reset()
    // ----------------------------------
    //
    ////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Resets the internal state to prepare for processing of a new
    /// stream.
    ///
    /// The SW engine and effects maintain internal state corresponding to the
    /// current signal and its history. For this reason it is necessary to call
    /// the reset() member function after processing a stream of data is
    /// finished and before starting the processing of a new stream of data.
    ///
    ////////////////////////////////////////////////////////////////////////////

    void LE_NOTHROWNOALIAS reset();

    /// @}

private:
    LE_NOTHROWRESTRICTNOALIAS SharedParameters * LE_FASTCALL_ABI getSharedParameters();

#ifdef DOXYGEN_ONLY
private:
    typedef Constants::Window Window;
#endif // DOXYGEN_ONLY
}; // class StandaloneModuleProcessor

/// @} // group Engine

//------------------------------------------------------------------------------
} /// @} // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

#include "boost/config/abi_suffix.hpp"

#endif // standaloneModuleProcessor_hpp

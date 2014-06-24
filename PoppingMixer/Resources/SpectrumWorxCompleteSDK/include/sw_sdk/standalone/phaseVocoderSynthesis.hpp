////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/phaseVocoderSynthesis.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePhaseVocoderSynthesis_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePhaseVocoderSynthesis_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/phase_vocoder_synthesis/phaseVocoderSynthesis.hpp"
#else
#include "effects/phaseVocoderSynthesis.hpp"
#endif

#include "boost/smart_ptr/intrusive_ptr.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
/// \brief Standalone effects
namespace Standalone
{
//------------------------------------------------------------------------------

/// \addtogroup Standalone Standalone
/// @{

/// \typedef PhaseVocoderSynthesis
/// \brief \copybrief Effects::PhaseVocoderSynthesis
/// \details \code #include "sw_sdk/standalone/phaseVocoderSynthesis.hpp" \endcode
/// \see Effects::PhaseVocoderSynthesis
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PhaseVocoderSynthesis> PhaseVocoderSynthesis;
typedef boost::intrusive_ptr<PhaseVocoderSynthesis> PhaseVocoderSynthesisPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePhaseVocoderSynthesis_hpp

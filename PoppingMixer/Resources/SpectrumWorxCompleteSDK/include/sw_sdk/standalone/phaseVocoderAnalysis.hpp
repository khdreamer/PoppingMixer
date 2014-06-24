////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/phaseVocoderAnalysis.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePhaseVocoderAnalysis_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePhaseVocoderAnalysis_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/phase_vocoder_analysis/phaseVocoderAnalysis.hpp"
#else
#include "effects/phaseVocoderAnalysis.hpp"
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

/// \typedef PhaseVocoderAnalysis
/// \brief \copybrief Effects::PhaseVocoderAnalysis
/// \details \code #include "sw_sdk/standalone/phaseVocoderAnalysis.hpp" \endcode
/// \see Effects::PhaseVocoderAnalysis
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PhaseVocoderAnalysis> PhaseVocoderAnalysis;
typedef boost::intrusive_ptr<PhaseVocoderAnalysis> PhaseVocoderAnalysisPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePhaseVocoderAnalysis_hpp

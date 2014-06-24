////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchShifter.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchShifter_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchShifter_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/pitch_shifter/pitchShifter.hpp"
#else
#include "effects/pitchShifter.hpp"
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

/// \typedef PitchShifter
/// \brief \copybrief Effects::PitchShifter
/// \details \code #include "sw_sdk/standalone/pitchShifter.hpp" \endcode
/// \see Effects::PitchShifter
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchShifter> PitchShifter;
typedef boost::intrusive_ptr<PitchShifter> PitchShifterPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchShifter_hpp

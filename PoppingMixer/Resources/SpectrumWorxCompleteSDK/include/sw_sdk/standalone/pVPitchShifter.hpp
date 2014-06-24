////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pVPitchShifter.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePVPitchShifter_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePVPitchShifter_hpp__F4162154_D024_4280_951D_7F314B6F159E
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

/// \typedef PVPitchShifter
/// \brief \copybrief Effects::PVPitchShifter
/// \details \code #include "sw_sdk/standalone/pVPitchShifter.hpp" \endcode
/// \see Effects::PVPitchShifter
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PVPitchShifter> PVPitchShifter;
typedef boost::intrusive_ptr<PVPitchShifter> PVPitchShifterPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePVPitchShifter_hpp

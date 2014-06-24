////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchFollowerPVD.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchFollowerPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchFollowerPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/pitch_follower/pitchFollower.hpp"
#else
#include "effects/pitchFollower.hpp"
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

/// \typedef PitchFollowerPVD
/// \brief \copybrief Effects::PitchFollowerPVD
/// \details \code #include "sw_sdk/standalone/pitchFollowerPVD.hpp" \endcode
/// \see Effects::PitchFollowerPVD
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchFollowerPVD> PitchFollowerPVD;
typedef boost::intrusive_ptr<PitchFollowerPVD> PitchFollowerPVDPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchFollowerPVD_hpp

////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchFollower.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchFollower_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchFollower_hpp__F4162154_D024_4280_951D_7F314B6F159E
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

/// \typedef PitchFollower
/// \brief \copybrief Effects::PitchFollower
/// \details \code #include "sw_sdk/standalone/pitchFollower.hpp" \endcode
/// \see Effects::PitchFollower
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchFollower> PitchFollower;
typedef boost::intrusive_ptr<PitchFollower> PitchFollowerPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchFollower_hpp

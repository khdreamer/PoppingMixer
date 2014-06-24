////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchSpring.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchSpring_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchSpring_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/pitch_spring/pitchSpring.hpp"
#else
#include "effects/pitchSpring.hpp"
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

/// \typedef PitchSpring
/// \brief \copybrief Effects::PitchSpring
/// \details \code #include "sw_sdk/standalone/pitchSpring.hpp" \endcode
/// \see Effects::PitchSpring
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchSpring> PitchSpring;
typedef boost::intrusive_ptr<PitchSpring> PitchSpringPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchSpring_hpp

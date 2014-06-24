////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchSpringPVD.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchSpringPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchSpringPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
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

/// \typedef PitchSpringPVD
/// \brief \copybrief Effects::PitchSpringPVD
/// \details \code #include "sw_sdk/standalone/pitchSpringPVD.hpp" \endcode
/// \see Effects::PitchSpringPVD
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchSpringPVD> PitchSpringPVD;
typedef boost::intrusive_ptr<PitchSpringPVD> PitchSpringPVDPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchSpringPVD_hpp

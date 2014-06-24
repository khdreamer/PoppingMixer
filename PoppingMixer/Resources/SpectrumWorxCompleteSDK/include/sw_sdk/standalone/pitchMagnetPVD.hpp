////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchMagnetPVD.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchMagnetPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchMagnetPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/pitch_magnet/pitchMagnet.hpp"
#else
#include "effects/pitchMagnet.hpp"
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

/// \typedef PitchMagnetPVD
/// \brief \copybrief Effects::PitchMagnetPVD
/// \details \code #include "sw_sdk/standalone/pitchMagnetPVD.hpp" \endcode
/// \see Effects::PitchMagnetPVD
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchMagnetPVD> PitchMagnetPVD;
typedef boost::intrusive_ptr<PitchMagnetPVD> PitchMagnetPVDPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchMagnetPVD_hpp

////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pitchMagnet.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePitchMagnet_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePitchMagnet_hpp__F4162154_D024_4280_951D_7F314B6F159E
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

/// \typedef PitchMagnet
/// \brief \copybrief Effects::PitchMagnet
/// \details \code #include "sw_sdk/standalone/pitchMagnet.hpp" \endcode
/// \see Effects::PitchMagnet
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PitchMagnet> PitchMagnet;
typedef boost::intrusive_ptr<PitchMagnet> PitchMagnetPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePitchMagnet_hpp

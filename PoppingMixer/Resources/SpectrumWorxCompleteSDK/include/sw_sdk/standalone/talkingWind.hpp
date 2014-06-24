////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/talkingWind.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneTalkingWind_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneTalkingWind_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/talking_wind/talkingWind.hpp"
#else
#include "effects/talkingWind.hpp"
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

/// \typedef TalkingWind
/// \brief \copybrief Effects::TalkingWind
/// \details \code #include "sw_sdk/standalone/talkingWind.hpp" \endcode
/// \see Effects::TalkingWind
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::TalkingWind> TalkingWind;
typedef boost::intrusive_ptr<TalkingWind> TalkingWindPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneTalkingWind_hpp

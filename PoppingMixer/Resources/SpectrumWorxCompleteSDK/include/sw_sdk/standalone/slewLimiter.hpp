////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/slewLimiter.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneSlewLimiter_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneSlewLimiter_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/slew_limiter/slewLimiter.hpp"
#else
#include "effects/slewLimiter.hpp"
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

/// \typedef SlewLimiter
/// \brief \copybrief Effects::SlewLimiter
/// \details \code #include "sw_sdk/standalone/slewLimiter.hpp" \endcode
/// \see Effects::SlewLimiter
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::SlewLimiter> SlewLimiter;
typedef boost::intrusive_ptr<SlewLimiter> SlewLimiterPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneSlewLimiter_hpp

////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/quietBoost.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneQuietBoost_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneQuietBoost_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/quiet_boost/quietBoost.hpp"
#else
#include "effects/quietBoost.hpp"
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

/// \typedef QuietBoost
/// \brief \copybrief Effects::QuietBoost
/// \details \code #include "sw_sdk/standalone/quietBoost.hpp" \endcode
/// \see Effects::QuietBoost
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::QuietBoost> QuietBoost;
typedef boost::intrusive_ptr<QuietBoost> QuietBoostPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneQuietBoost_hpp

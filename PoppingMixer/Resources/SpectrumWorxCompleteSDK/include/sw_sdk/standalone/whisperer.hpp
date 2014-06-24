////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/whisperer.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneWhisperer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneWhisperer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/whisperer/whisperer.hpp"
#else
#include "effects/whisperer.hpp"
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

/// \typedef Whisperer
/// \brief \copybrief Effects::Whisperer
/// \details \code #include "sw_sdk/standalone/whisperer.hpp" \endcode
/// \see Effects::Whisperer
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Whisperer> Whisperer;
typedef boost::intrusive_ptr<Whisperer> WhispererPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneWhisperer_hpp

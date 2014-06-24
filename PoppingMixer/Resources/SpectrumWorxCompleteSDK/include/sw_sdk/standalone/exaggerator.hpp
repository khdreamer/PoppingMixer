////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/exaggerator.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneExaggerator_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneExaggerator_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/exaggerator/exaggerator.hpp"
#else
#include "effects/exaggerator.hpp"
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

/// \typedef Exaggerator
/// \brief \copybrief Effects::Exaggerator
/// \details \code #include "sw_sdk/standalone/exaggerator.hpp" \endcode
/// \see Effects::Exaggerator
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Exaggerator> Exaggerator;
typedef boost::intrusive_ptr<Exaggerator> ExaggeratorPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneExaggerator_hpp

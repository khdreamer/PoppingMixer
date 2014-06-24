////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/armonizer.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneArmonizer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneArmonizer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/armonizer/armonizer.hpp"
#else
#include "effects/armonizer.hpp"
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

/// \typedef Armonizer
/// \brief \copybrief Effects::Armonizer
/// \details \code #include "sw_sdk/standalone/armonizer.hpp" \endcode
/// \see Effects::Armonizer
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Armonizer> Armonizer;
typedef boost::intrusive_ptr<Armonizer> ArmonizerPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneArmonizer_hpp

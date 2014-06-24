////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/vaxateer.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneVaxateer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneVaxateer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/vaxateer/vaxateer.hpp"
#else
#include "effects/vaxateer.hpp"
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

/// \typedef Vaxateer
/// \brief \copybrief Effects::Vaxateer
/// \details \code #include "sw_sdk/standalone/vaxateer.hpp" \endcode
/// \see Effects::Vaxateer
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Vaxateer> Vaxateer;
typedef boost::intrusive_ptr<Vaxateer> VaxateerPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneVaxateer_hpp

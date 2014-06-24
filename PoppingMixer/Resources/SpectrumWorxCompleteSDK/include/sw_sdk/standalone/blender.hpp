////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/blender.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneBlender_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneBlender_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/blender/blender.hpp"
#else
#include "effects/blender.hpp"
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

/// \typedef Blender
/// \brief \copybrief Effects::Blender
/// \details \code #include "sw_sdk/standalone/blender.hpp" \endcode
/// \see Effects::Blender
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Blender> Blender;
typedef boost::intrusive_ptr<Blender> BlenderPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneBlender_hpp

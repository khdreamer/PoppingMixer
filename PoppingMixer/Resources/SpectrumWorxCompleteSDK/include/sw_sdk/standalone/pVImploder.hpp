////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pVImploder.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePVImploder_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePVImploder_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/eximploder/exImploder.hpp"
#else
#include "effects/exImploder.hpp"
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

/// \typedef PVImploder
/// \brief \copybrief Effects::PVImploder
/// \details \code #include "sw_sdk/standalone/pVImploder.hpp" \endcode
/// \see Effects::PVImploder
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PVImploder> PVImploder;
typedef boost::intrusive_ptr<PVImploder> PVImploderPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePVImploder_hpp

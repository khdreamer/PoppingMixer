////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/pVExploder.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePVExploder_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePVExploder_hpp__F4162154_D024_4280_951D_7F314B6F159E
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

/// \typedef PVExploder
/// \brief \copybrief Effects::PVExploder
/// \details \code #include "sw_sdk/standalone/pVExploder.hpp" \endcode
/// \see Effects::PVExploder
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::PVExploder> PVExploder;
typedef boost::intrusive_ptr<PVExploder> PVExploderPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePVExploder_hpp

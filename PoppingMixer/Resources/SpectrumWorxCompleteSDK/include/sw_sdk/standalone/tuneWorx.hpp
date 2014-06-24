////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/tuneWorx.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneTuneWorx_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneTuneWorx_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/tune_worx/tuneWorx.hpp"
#else
#include "effects/tuneWorx.hpp"
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

/// \typedef TuneWorx
/// \brief \copybrief Effects::TuneWorx
/// \details \code #include "sw_sdk/standalone/tuneWorx.hpp" \endcode
/// \see Effects::TuneWorx
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::TuneWorx> TuneWorx;
typedef boost::intrusive_ptr<TuneWorx> TuneWorxPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneTuneWorx_hpp

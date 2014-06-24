////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/tuneWorxPVD.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneTuneWorxPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneTuneWorxPVD_hpp__F4162154_D024_4280_951D_7F314B6F159E
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

/// \typedef TuneWorxPVD
/// \brief \copybrief Effects::TuneWorxPVD
/// \details \code #include "sw_sdk/standalone/tuneWorxPVD.hpp" \endcode
/// \see Effects::TuneWorxPVD
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::TuneWorxPVD> TuneWorxPVD;
typedef boost::intrusive_ptr<TuneWorxPVD> TuneWorxPVDPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneTuneWorxPVD_hpp

////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/bandstop.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneBandstop_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneBandstop_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/bandpass/bandpass.hpp"
#else
#include "effects/bandpass.hpp"
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

/// \typedef Bandstop
/// \brief \copybrief Effects::Bandstop
/// \details \code #include "sw_sdk/standalone/bandstop.hpp" \endcode
/// \see Effects::Bandstop
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Bandstop> Bandstop;
typedef boost::intrusive_ptr<Bandstop> BandstopPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneBandstop_hpp

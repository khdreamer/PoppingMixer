////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/freqnamics.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneFreqnamics_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneFreqnamics_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/freqnamics/freqnamics.hpp"
#else
#include "effects/freqnamics.hpp"
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

/// \typedef Freqnamics
/// \brief \copybrief Effects::Freqnamics
/// \details \code #include "sw_sdk/standalone/freqnamics.hpp" \endcode
/// \see Effects::Freqnamics
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Freqnamics> Freqnamics;
typedef boost::intrusive_ptr<Freqnamics> FreqnamicsPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneFreqnamics_hpp

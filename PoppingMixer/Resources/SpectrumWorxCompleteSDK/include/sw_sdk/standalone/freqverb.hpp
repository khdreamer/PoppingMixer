////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/freqverb.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneFreqverb_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneFreqverb_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/freqverb/freqverb.hpp"
#else
#include "effects/freqverb.hpp"
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

/// \typedef Freqverb
/// \brief \copybrief Effects::Freqverb
/// \details \code #include "sw_sdk/standalone/freqverb.hpp" \endcode
/// \see Effects::Freqverb
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Freqverb> Freqverb;
typedef boost::intrusive_ptr<Freqverb> FreqverbPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneFreqverb_hpp

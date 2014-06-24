////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/quantizer.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneQuantizer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneQuantizer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/quantizer/quantizer.hpp"
#else
#include "effects/quantizer.hpp"
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

/// \typedef Quantizer
/// \brief \copybrief Effects::Quantizer
/// \details \code #include "sw_sdk/standalone/quantizer.hpp" \endcode
/// \see Effects::Quantizer
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Quantizer> Quantizer;
typedef boost::intrusive_ptr<Quantizer> QuantizerPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneQuantizer_hpp

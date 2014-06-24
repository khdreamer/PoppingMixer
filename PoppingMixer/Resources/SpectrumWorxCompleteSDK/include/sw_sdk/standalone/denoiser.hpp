////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/denoiser.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneDenoiser_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneDenoiser_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/denoiser/denoiser.hpp"
#else
#include "effects/denoiser.hpp"
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

/// \typedef Denoiser
/// \brief \copybrief Effects::Denoiser
/// \details \code #include "sw_sdk/standalone/denoiser.hpp" \endcode
/// \see Effects::Denoiser
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Denoiser> Denoiser;
typedef boost::intrusive_ptr<Denoiser> DenoiserPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneDenoiser_hpp

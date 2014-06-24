////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/sumoPitch.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneSumoPitch_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneSumoPitch_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/sumo_pitch/sumoPitch.hpp"
#else
#include "effects/sumoPitch.hpp"
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

/// \typedef SumoPitch
/// \brief \copybrief Effects::SumoPitch
/// \details \code #include "sw_sdk/standalone/sumoPitch.hpp" \endcode
/// \see Effects::SumoPitch
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::SumoPitch> SumoPitch;
typedef boost::intrusive_ptr<SumoPitch> SumoPitchPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneSumoPitch_hpp

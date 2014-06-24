////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/robotizer.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneRobotizer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneRobotizer_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/robotizer/robotizer.hpp"
#else
#include "effects/robotizer.hpp"
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

/// \typedef Robotizer
/// \brief \copybrief Effects::Robotizer
/// \details \code #include "sw_sdk/standalone/robotizer.hpp" \endcode
/// \see Effects::Robotizer
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Robotizer> Robotizer;
typedef boost::intrusive_ptr<Robotizer> RobotizerPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneRobotizer_hpp

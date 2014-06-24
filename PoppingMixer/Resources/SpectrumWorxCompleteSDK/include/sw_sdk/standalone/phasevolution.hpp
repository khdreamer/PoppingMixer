////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/phasevolution.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standalonePhasevolution_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standalonePhasevolution_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/phasevolution/phasevolution.hpp"
#else
#include "effects/phasevolution.hpp"
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

/// \typedef Phasevolution
/// \brief \copybrief Effects::Phasevolution
/// \details \code #include "sw_sdk/standalone/phasevolution.hpp" \endcode
/// \see Effects::Phasevolution
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::Phasevolution> Phasevolution;
typedef boost::intrusive_ptr<Phasevolution> PhasevolutionPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standalonePhasevolution_hpp

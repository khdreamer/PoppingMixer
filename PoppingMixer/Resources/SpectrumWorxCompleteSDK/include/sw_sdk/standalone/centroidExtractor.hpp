////////////////////////////////////////////////////////////////////////////////
///
/// \file standalone/centroidExtractor.hpp
/// ----------------------------------------------------------------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef standaloneCentroidExtractor_hpp__F4162154_D024_4280_951D_7F314B6F159E
#define standaloneCentroidExtractor_hpp__F4162154_D024_4280_951D_7F314B6F159E
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "engine/standaloneModuleProcessor.hpp"
#ifdef DOXYGEN_ONLY
#include "effects/centroid_extractor/centroidExtractor.hpp"
#else
#include "effects/centroidExtractor.hpp"
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

/// \typedef CentroidExtractor
/// \brief \copybrief Effects::CentroidExtractor
/// \details \code #include "sw_sdk/standalone/centroidExtractor.hpp" \endcode
/// \see Effects::CentroidExtractor
/// \see Engine::StandaloneModuleProcessor
typedef Engine::StandaloneModuleProcessor<Effects::CentroidExtractor> CentroidExtractor;
typedef boost::intrusive_ptr<CentroidExtractor> CentroidExtractorPtr;

/// @} // group Standalone

//------------------------------------------------------------------------------
} // namespace Standalone
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // standaloneCentroidExtractor_hpp

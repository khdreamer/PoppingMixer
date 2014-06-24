////////////////////////////////////////////////////////////////////////////////
///
/// \internal
/// \file examplePresets.cpp
/// ------------------------
///
/// Internal, utility code used by the SW SDK sample application, not to be
/// confused with the documented SW SDK API.
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "examplePresets.hpp"

#ifndef _POSIX_
    #define _POSIX_
#endif // _POSIX_
#include <climits>
#include <cstring>
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------

ExampleCodePreset const * ExampleCodePreset::pExamplePresets( 0 );

char const * ExampleCodePreset::fullSamplePath( char const * const pSampleFileName )
{
    static char fullPath[ PATH_MAX ];
#if defined( _WIN32 )
    static char const samplesPath[] = "..\\samples\\";
#elif defined( __APPLE__ ) && !defined( __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ )
    static char const samplesPath[] = "../../samples/";
#else
    static char const samplesPath[] = "samples/";
#endif // _WIN32
    std::strcpy( fullPath, samplesPath     );
    std::strcat( fullPath, pSampleFileName );
    return fullPath;
}

//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

// Example code preset collection:

#include "presets/ExampleArmonizer.cpp"
#include "presets/ExampleBasic.cpp"
#include "presets/ExampleCreepyDeepy.cpp"
#include "presets/ExampleLeeps.cpp"
#include "presets/ExamplePitchShifter.cpp"
#include "presets/ExamplePitchSpring.cpp"
#include "presets/ExampleReverser.cpp"
#include "presets/ExampleTalkingWind.cpp"
#include "presets/ExampleTechnologic.cpp"
#include "presets/ExampleTuneWorx.cpp"


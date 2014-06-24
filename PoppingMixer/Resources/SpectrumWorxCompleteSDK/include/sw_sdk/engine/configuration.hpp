////////////////////////////////////////////////////////////////////////////////
///
/// \file configuration.hpp
/// -----------------------
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef configuration_hpp__58D224D7_933A_421B_98B8_CCB693BD44E7
#define configuration_hpp__58D224D7_933A_421B_98B8_CCB693BD44E7
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace Engine
{
//------------------------------------------------------------------------------

#ifdef _WIN32
#   if !defined( _MSC_VER ) || ( _MSC_VER < 1500 )
#       error SW SDK requires MSVC++ 9.0 or higer
#   endif
#else // OS
#   if ( !defined( __clang__ ) && !defined( __GNUC__ ) ) || ( defined( __GNUC__ ) && ( __GNUC__ < 4 ) )
#       error SW SDK requires Clang or GCC 4 or higher
#   endif
#endif // OS

////////////////////////////////////////////////////////////////////////////////
///
/// \brief LE Engine specific constants
///
////////////////////////////////////////////////////////////////////////////////

namespace Constants
{
    unsigned int const minimumFFTSize = 128 ;
    unsigned int const maximumFFTSize = 8192;
    unsigned int const defaultFFTSize = 2048;

    unsigned int const minimumOverlapFactor = 1;
    unsigned int const maximumOverlapFactor = 8;
    unsigned int const defaultOverlapFactor = 4;

    unsigned int const defaultSampleRate = 44100;

    /// \brief DFT WOLA windowing function
    enum Window
    {
        Hann,
        Hamming,
        Blackman,
        BlackmanHarris,
        Gaussian,
        FlatTop,
        Welch,
        Triangle,
        Rectangle,

        NumberOfWindows
    };

    Window const defaultWindow = Hann;
} // namespace Constants

//------------------------------------------------------------------------------
} // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // configuration_hpp

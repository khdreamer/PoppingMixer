////////////////////////////////////////////////////////////////////////////////
///
/// \internal
/// \file osAbstraction.hpp
/// -----------------------
///
/// Internal, utility code used by the SW SDK sample application, not to be
/// confused with the documented SW SDK API.
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef osAbstraction_hpp__69C8bE75_CBC6_48F0_93BE_9EA34BBAB746
#define osAbstraction_hpp__69C8bE75_CBC6_48F0_93BE_9EA34BBAB746
#pragma once
//------------------------------------------------------------------------------
#include <cstddef>
//------------------------------------------------------------------------------
#ifdef __ANDROID__
    struct AAssetManager;
#endif // __ANDROID__
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace OS ///< \internal
{
//------------------------------------------------------------------------------

void printError           ( char const * pString            );
void printMessage         ( char const * pString            );
void printFormattedMessage( char const * pFormatString, ... );
void printFormattedError  ( char const * pFormatString, ... );

char const * createFullOutputFilePath          ( char const * outputFileName                      );
char const * createFullOutputFilePathWithSuffix( char const * outputFileName, char const * suffix );

void sleep( unsigned int seconds );

#ifdef __ANDROID__
    AAssetManager & getResourceManager();
#endif // __ANDROID__

//------------------------------------------------------------------------------
} // namespace OS
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // osAbstraction_hpp

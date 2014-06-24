////////////////////////////////////////////////////////////////////////////////
///
/// \internal
/// osAbstraction.cpp/mm
/// --------------------
///
/// Internal, utility code used by the SW SDK sample application, not to be
/// confused with the documented SW SDK API.
///
/// Target platform specific boilerplate code.
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "osAbstraction.hpp"

#include "common/assert.hpp"

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #import "Foundation/Foundation.h"
    #else
        #include "mach-o/dyld.h"
    #endif // iOS
#endif // __APPLE__

#ifdef _MSC_VER
    #ifdef _M_AMD64
        #pragma comment( lib, "AudioIO_Win64_x86-64_SSE3.lib" )
        #pragma comment( lib, "SpectrumWorxCompleteSDK_Win64_x86-64_SSE3.lib" )
    #else // _M_IX86
        #pragma comment( lib, "AudioIO_Win32_x86-32_SSE2.lib" )
        #pragma comment( lib, "SpectrumWorxCompleteSDK_Win32_x86-32_SSE2.lib" )
    #endif // _M_IX86 / _M_AMD64
    #include "direct.h"
    unsigned int const maxPath = 260;
#else // POSIX implementation
    #include "sys/stat.h"
             int const accessFlags = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP;
    unsigned int const maxPath     = 2048;
#endif // POSIX implementation

#ifdef __ANDROID__
    #include "android/log.h"
    #include "android_native_app_glue.h"
    #include "jni.h"

    #include "unistd.h"
#endif // __ANDROID__

#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <new>
//------------------------------------------------------------------------------

bool processingExample();

#ifdef _WIN32
extern "C" void __stdcall Sleep( unsigned long dwMilliseconds );
#endif // _WIN32

//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace OS
{
//------------------------------------------------------------------------------

void printError( char const * const pString )
{
#ifdef __ANDROID__
    ::__android_log_write( ANDROID_LOG_ERROR, "*** SW error *** :", pString );
#else
    std::fputs( pString, stderr );
#endif // __ANDROID__
}

void printMessage( char const * const pString )
{
#ifdef __ANDROID__
    ::__android_log_write( ANDROID_LOG_INFO, "*** SW info *** :", pString );
#else
    std::puts( pString );
#endif // __ANDROID__
}

void printFormattedError( char const * const pFormatString, ... )
{
    va_list arglist;
    va_start( arglist, pFormatString );
#ifdef __ANDROID__
    ::__android_log_vprint( ANDROID_LOG_ERROR, "*** SW error *** :", pFormatString, arglist );
#else
    std::vfprintf( stderr, pFormatString, arglist );
#endif // __ANDROID__
    va_end( arglist );
}


void printFormattedMessage( char const * const pFormatString, ... )
{
    va_list arglist;
    va_start( arglist, pFormatString );
#ifdef __ANDROID__
    ::__android_log_vprint( ANDROID_LOG_INFO, "*** SW info *** :", pFormatString, arglist );
#else
    std::vprintf( pFormatString, arglist );
#endif // __ANDROID__
    va_end( arglist );
}


void sleep( unsigned int const seconds )
{
#ifdef _WIN32
    ::Sleep( seconds * 1000 );
#else
    ::sleep( seconds );
#endif // _WIN32
}


namespace
{
#ifdef __ANDROID__
    static ANativeActivity * pNativeActivity;
#endif // __ANDROID__

    char const * getOutputFilePath()
    {
    #if defined( __ANDROID__ )
        static char const sdCardPath[] = "/sdcard/SpectrumWorxExampleResults";
        static char const * pOutputFilePath( NULL );
        if ( !pOutputFilePath )
        {
            int const result( ::mkdir( sdCardPath, accessFlags ) );
            if ( ( result == 0 ) || ( errno == EEXIST ) )
                pOutputFilePath = sdCardPath;
            else
            {
                printMessage( "Unable to access sdcard, example results will be saved in the application's private storage." );
                pOutputFilePath = pNativeActivity->internalDataPath;
            }
        }
        return pOutputFilePath;
    #elif defined( __APPLE__ )
        static char appPath[ maxPath ] = { 0 };
        if ( !appPath[ 0 ] )
        {
        #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
            @autoreleasepool
            {
                NSArray  * const dirPaths( NSSearchPathForDirectoriesInDomains( NSDocumentDirectory, NSUserDomainMask, YES ) );
                NSString * const docsDir ( [dirPaths objectAtIndex:0] );
                LE_VERIFY( [docsDir getCString: appPath maxLength: maxPath - 1 encoding: NSUTF8StringEncoding] );
            }
        #else // OS X
            unsigned int appPathSize( maxPath );
            LE_VERIFY( ::_NSGetExecutablePath( appPath, &appPathSize ) == 0 );
            LE_ASSERT( appPathSize == maxPath );
            *std::strrchr( appPath, '/' ) = '\0';
        #endif
        }
        return appPath;
    #else
        static char cwd[ maxPath ] = { 0 };
        if ( !cwd[ 0 ] )
            LE_VERIFY( ::getcwd( cwd, maxPath ) == cwd );
        return cwd;
    #endif // platform
    }

    char * fullOutputPathHelper( char const * const outputFileName )
    {
        static char fullOutputFileName[ maxPath ];

        std::strcpy( fullOutputFileName, getOutputFilePath() );
    #ifdef _WIN32
        std::strcat( fullOutputFileName, "\\"                );
    #else
        std::strcat( fullOutputFileName, "/"                 );
    #endif // _WIN32
        std::strcat( fullOutputFileName, "Output-"           );
        std::strcat( fullOutputFileName, outputFileName      );

        LE_ASSERT( std::strlen( fullOutputFileName ) < maxPath );
        return fullOutputFileName;
    }
} // anonymous namespace


char const * createFullOutputFilePath( char const * const outputFileName ) { return fullOutputPathHelper( outputFileName ); }


char const * createFullOutputFilePathWithSuffix( char const * const outputFileName, char const * const suffix )
{
    char const * const extension( std::strrchr( outputFileName, '.' ) );

    char * const fullOutputFileName( fullOutputPathHelper( outputFileName ) );

    *std::strrchr( fullOutputFileName, '.' ) = '\0';
    std::strcat( fullOutputFileName, " ("                );
    std::strcat( fullOutputFileName, suffix              );
    std::strcat( fullOutputFileName, ")"                 );
    std::strcat( fullOutputFileName, extension           );

    LE_ASSERT( std::strlen( fullOutputFileName ) < maxPath );
    return fullOutputFileName;
}


#ifdef __ANDROID__

AAssetManager & getResourceManager()
{
    LE_ASSERT( pNativeActivity );
    return *pNativeActivity->assetManager;
}


extern "C" void android_main( android_app * const state )
{
    // Give the debugger time to attach:
    sleep( 3 );

    app_dummy();

    LE_ASSERT( state                             );
    LE_ASSERT( state->activity                   );
    LE_ASSERT( state->activity->assetManager     );
    LE_ASSERT( state->activity->internalDataPath );
    LE_ASSERT( state->savedState == NULL         );

    pNativeActivity = state->activity;

    bool const success( processingExample() );
    if ( success ) printMessage( "The LE SpectrumWorx SDK sample application finished successfully."   );
    else           printError  ( "The LE SpectrumWorx SDK sample application finished unsuccessfully." );

    ::ANativeActivity_finish( state->activity );
}

#else // target OS entry function

extern "C" int main( int const argc, char const * const /*argv*/[] )
{
    if ( argc > 1 )
    {
        printError( "The LE SpectrumWorx SDK sample application does not currently support any command line arguments." );
        return EXIT_FAILURE;
    }
    bool const success( processingExample() );
    if ( success ) printMessage( "\nThe LE SpectrumWorx SDK sample application finished successfully."   );
    else           printError  ( "\nThe LE SpectrumWorx SDK sample application finished unsuccessfully." );
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    ::pause();
#endif
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif // target OS

//------------------------------------------------------------------------------
} // namespace OS
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

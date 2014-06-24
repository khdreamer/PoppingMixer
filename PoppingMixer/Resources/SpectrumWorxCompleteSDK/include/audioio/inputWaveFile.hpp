////////////////////////////////////////////////////////////////////////////////
///
/// \file inputWaveFile.hpp
/// -----------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef inputWaveFile_hpp__CAE81353_A5A7_45C1_89A5_63EE5B8DF212
#define inputWaveFile_hpp__CAE81353_A5A7_45C1_89A5_63EE5B8DF212
#pragma once
//------------------------------------------------------------------------------
#include "common/abi.hpp"
#include "common/pimpl.hpp"
//------------------------------------------------------------------------------
#ifdef __ANDROID__
    struct AAssetManager;
#endif // __ANDROID__
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace AudioIO
{
//------------------------------------------------------------------------------

/// \addtogroup AudioIO
/// @{

typedef char const * error_msg_t; ///< A static error message string.

namespace Detail
{
    class InputWaveFileBase
    #ifndef DOXYGEN_ONLY
        :
        public Common::StackPImpl<InputWaveFileBase, 3 * sizeof( void * )>
    #endif // DOXYGEN_ONLY
    {
    public:
        /// <B>Effect:</B> Reads interleaved <VAR>numberOfSampleFrames</VAR> * numberOfChannels() samples into <VAR>pOutput</VAR> and adjusts the current file position (as reported by remainingSamples()).<BR>
        /// <B>Preconditions:</B>
        ///     - a successful open() call
        ///     - remainingSamples() >= samples
        ///     - the buffer pointed to by pOutput must be large enough to hold <VAR>numberOfSampleFrames</VAR> * numberOfChannels() samples.
        LE_NOTHROW        void           LE_FASTCALL_ABI read( float * pOutput, unsigned int numberOfSampleFrames ) const;

        LE_NOTHROWNOALIAS unsigned short LE_FASTCALL_ABI numberOfChannels() const; ///< Number of channels reported by the WAVE file. <BR> \detail <B>Preconditions:</B> A successful open() call.
        LE_NOTHROWNOALIAS unsigned int   LE_FASTCALL_ABI sampleRate      () const; ///< Sample rate reported by the WAVE file. <BR> \detail <B>Preconditions:</B> A successful open() call.
        LE_NOTHROWNOALIAS unsigned int   LE_FASTCALL_ABI remainingSamples() const; ///< Number of sample frames remaining/not yet read from the WAVE file. <BR> \detail <B>Preconditions:</B> A successful open() call.

        LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI operator!() const;
    }; // class InputWaveFileBase
} // Detail


////////////////////////////////////////////////////////////////////////////////
///
/// \class InputWaveFile
///
/// \brief Reads a WAVE file from the filesystem.
///
////////////////////////////////////////////////////////////////////////////////

class InputWaveFile
    :
#ifdef DOXYGEN_ONLY
    public Detail::InputWaveFileBase
#else
    public Common::StackPImpl<InputWaveFile, 4 * sizeof( void * ), sizeof( void * ), Detail::InputWaveFileBase>
#endif // DOXYGEN_ONLY
{
public:
    LE_NOTHROW  InputWaveFile();
    LE_NOTHROW ~InputWaveFile();

    /// <B>Effect:</B> Opens the file pointed to by <VAR>pathToFile</VAR> for reading.<BR>
    /// The function can be called many times, i.e. one instance of InputWaveFile can be used to read as many WAVE files as desired. Note that the function offers only the basic (error safety) guarantee.<BR>
    /// <B>Postconditions:</B> Unless an error is reported, the file was successfully opened and its header parsed making it ready for audio and metadata extraction.<BR>
    LE_NOTHROW error_msg_t LE_FASTCALL_ABI open( char const * pathToFile );
}; // class InputWaveFile


////////////////////////////////////////////////////////////////////////////////
///
/// \class ResourceWaveFile
///
/// \brief Reads a WAVE file from the app's resources or assets (iOS or Android
/// respectively).
///
/// \note On standard desktop systems (e.g. OSX and Windows) that do not use the
/// concept of sandboxed apps this class is equivalent to the InputWaveFile
/// class, i.e. the <VAR>resourceFilenameWithExtension</VAR> parameter is simply
/// interpreted as a path (absolute or relative to the CWD otherwise).
///
////////////////////////////////////////////////////////////////////////////////

#if defined( __ANDROID__ ) || defined( __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ ) || defined( DOXYGEN_ONLY )
class ResourceWaveFile
    :
#ifdef DOXYGEN_ONLY
    public Detail::InputWaveFileBase
#else
    public Common::StackPImpl<ResourceWaveFile, 4 * sizeof( void * ), sizeof( void * ), Detail::InputWaveFileBase>
#endif // DOXYGEN_ONLY
{
public:
    LE_NOTHROW  ResourceWaveFile();
    LE_NOTHROW ~ResourceWaveFile();

    /// <B>Effect:</B> Searches for resourceFilenameWithExtension in the app's resources and opens the file for reading.<BR>
    /// <B>Postconditions:</B> Unless an error is reported, the file was successfully opened and its header parsed making it ready for audio and metadata extraction.<BR>
    LE_NOTHROW error_msg_t LE_FASTCALL_ABI open( char const * resourceFilenameWithExtension );

#if defined( __ANDROID__ ) || defined( DOXYGEN_ONLY )
    /// <B>Android specific:</B> in order to access the app's assets AudioIO
    /// requires access to the app's AAssetManager object which should be
    /// set/provided once using this function before creating any
    /// ResourceWaveFile objects.
    LE_NOTHROW static void LE_FASTCALL_ABI setResourceManager( ::AAssetManager & );
#endif // __ANDROID__
}; // class ResourceWaveFile
#else
typedef InputWaveFile ResourceWaveFile;
#endif
/// @} // group AudioIO

//------------------------------------------------------------------------------
} // namespace AudioIO
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // inputWaveFile_hpp

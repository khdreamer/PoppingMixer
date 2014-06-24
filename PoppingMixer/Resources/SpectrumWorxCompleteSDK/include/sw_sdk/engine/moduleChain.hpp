////////////////////////////////////////////////////////////////////////////////
///
/// \file moduleChain.hpp
/// ---------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef moduleChain_hpp__BBD947F7_6595_4EBC_A7B6_80345BBE2A94
#define moduleChain_hpp__BBD947F7_6595_4EBC_A7B6_80345BBE2A94
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "common/abi.hpp"
#include "engine/moduleBase.hpp"

#include "boost/config/abi_prefix.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace Engine
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Engine
#endif // LE_SW_SINGLE_EFFECT
/// @{

////////////////////////////////////////////////////////////////////////////////
///
/// \class ModuleChain
///
/// \brief A linear list-like container of modules.
///
/// \note
/// - All preconditions are validated with asserts in debug/development builds.
///   Violating a precondition in release builds results in undefined behaviour.
/// - Functions that insert modules into the chain perform dynamic memory
///   allocation as part of the module setup. These therefore return a bool to
///   indicate success or failure (to allocate memory for the inserted module).
/// - ModuleChain instances retain/release ownership of inserted/removed
///   modules:
///    - shared pointers are used to pass module instance parameters instead of
///      plain references to emphasize this shared ownership semantics
///    - all pointers are assumed to be non-null.
///
////////////////////////////////////////////////////////////////////////////////

class ModuleChain
{
public:
    /// <B>Effect:</B> Inserts <VAR>newModule</VAR> before/in front of <VAR>followingModule</VAR>.<BR>
    /// <B>Preconditions:</B><BR> - <VAR>followingModule</VAR> must already be in the chain<BR> - <VAR>newModule</VAR> can already be in the chain but must not already be inserted in another chain<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI insertBefore( ModulePtr const & pFollowingModule, ModulePtr const & pNewModule ) { return insertBefore( *pFollowingModule, *pNewModule ); }
    /// <B>Effect:</B> Inserts <VAR>newModule</VAR> after/behind <VAR>precedingModule</VAR>.<BR>
    /// <B>Preconditions:</B><BR> - <VAR>precedingModule</VAR> must already be in the chain<BR> - <VAR>newModule</VAR> can already be in the chain but must not already be inserted in another chain<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI insertAfter ( ModulePtr const & pPrecedingModule, ModulePtr const & pNewModule ) { return insertAfter( *pPrecedingModule, *pNewModule ); }
    /// <B>Effect:</B> Inserts/appends a module at the end of the chain.<BR>
    /// <B>Preconditions:</B> <VAR>module</VAR> can already be in the chain but must not already be inserted in another chain.<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI append      ( ModulePtr const & pModule ) { return append( *pModule ); }
    /// <B>Effect:</B> Inserts/prepends a module at the beginning of the chain.<BR>
    /// <B>Preconditions:</B> <VAR>module</VAR> can already be in the chain but must not already be inserted in another chain.<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI prepend     ( ModulePtr const & pModule ) { return prepend( *pModule ); }
    /// <B>Effect:</B> Removes a module from the chain.<BR>
    /// <B>Preconditions:</B> <VAR>module</VAR> must be in the chain.<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI remove      ( ModulePtr const & pModule ) { return remove( *pModule ); }

    /// <B>Effect:</B> Reverses the order of modules in the chain.<BR>
    /// <B>Complexity:</B> Linear.<BR>
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI reverse       ();
    /// <B>Effect:</B> Moves backwards all the modules, so that the first module becomes the second, the second becomes the third... the last module becomes the first one. The shift is circular so if <VAR>amount</VAR> is larger than size() it will simply wrap around.<BR>
    /// <B>Complexity:</B> Linear.<BR>
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI shiftBackwards( unsigned int amount = 1 );
    /// <B>Effect:</B> Moves forwards all the modules, so that the second module becomes the first, the third becomes the second... the first module becomes the last one. The shift is circular so if <VAR>amount</VAR> is larger than size() it will simply wrap around.<BR>
    /// <B>Complexity:</B> Linear.<BR>
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI shiftForward  ( unsigned int amount = 1 );

    /// <B>Effect:</B> Swaps the positions of the two modules.<BR>
    /// <B>Preconditions:</B> Both modules must be in the chain.<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI swap( ModulePtr const &, ModulePtr const & );

    /// <B>Effect:</B> Removes all modules from the chain.<BR>
    /// <B>Complexity:</B> Linear.<BR>
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI clear();

    /// <B>Effect:</B> Returns the number of modules contained in the chain.<BR>
    /// <B>Complexity:</B> Linear.<BR>
    LE_NOTHROWNOALIAS unsigned int LE_FASTCALL_ABI size() const;

    /// <B>Effect:</B> Returns true if the chain contains no modules.<BR>
    /// <B>Complexity:</B> Constant.<BR>
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI empty() const;

    /// <B>Effect:</B> Returns a pointer to the module at the position given by <VAR>moduleIndex</VAR>.<BR>
    /// <B>Preconditions:</B> <VAR>moduleIndex</VAR> must be less than size().<BR>
    /// <B>Complexity:</B> Linear.<BR>
    LE_NOTHROWNOALIAS ModulePtr LE_FASTCALL_ABI operator[]( unsigned int moduleIndex );

private:
     ModuleChain(                     );
     ModuleChain( ModuleChain const & );
    ~ModuleChain(                     );

    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI insertBefore( ModuleBase & followingModule, ModuleBase & newModule );
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI insertAfter ( ModuleBase & precedingModule, ModuleBase & newModule );
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI append      ( ModuleBase &                                         );
    LE_NOTHROWNOALIAS bool LE_FASTCALL_ABI prepend     ( ModuleBase &                                         );
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI remove      ( ModuleBase &                                         );
    LE_NOTHROWNOALIAS void LE_FASTCALL_ABI swap        ( ModuleBase &,                 ModuleBase &           );
}; // class ModuleChain

/** @} */ // group Engine

//------------------------------------------------------------------------------
} // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

#include "boost/config/abi_suffix.hpp"

#endif // moduleChain_hpp

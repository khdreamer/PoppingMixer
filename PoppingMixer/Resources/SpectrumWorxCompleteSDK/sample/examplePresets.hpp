////////////////////////////////////////////////////////////////////////////////
///
/// \internal
/// \file examplePresets.hpp
/// ------------------------
///
/// Internal, utility code used by the SW SDK sample application, not to be
/// confused with the documented SW SDK API.
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef examplePresets_hpp__52603A53_887F_491E_B380_33EA674311E4
#define examplePresets_hpp__52603A53_887F_491E_B380_33EA674311E4
#pragma once
//------------------------------------------------------------------------------
#include "sw_sdk/engine/configuration.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \internal
/// \class ExampleCodePreset
/// Internal, utility code used by the SW SDK sample application, not to be
/// confused with the documented SW SDK API.
////////////////////////////////////////////////////////////////////////////////

namespace Engine { class ModuleChain; }

struct ExampleCodePreset
{
public:
    typedef bool (* callback_t)( Engine::ModuleChain &, unsigned int sampleRate );

    char              const * const name         ;
    char              const * const mainInput    ;
    char              const * const sideInput    ;
    unsigned int              const fftSize      ;
    unsigned int              const overlapFactor;
    callback_t                const setupEffects ;
    ExampleCodePreset const * const pNextPreset  ;

    ExampleCodePreset
    (
        callback_t             const presetSetupCallback_                                    ,
        char           const * const name_                                                   ,
        char           const * const mainInput_                                              ,
        char           const * const sideInput_     = 0                                      ,
        unsigned int           const fftSize_       = Engine::Constants::defaultFFTSize      ,
        unsigned int           const overlapFactor_ = Engine::Constants::defaultOverlapFactor
    )
        :
        name         ( name_                ),
        mainInput    ( mainInput_           ),
        sideInput    ( sideInput_           ),
        fftSize      ( fftSize_             ),
        overlapFactor( overlapFactor_       ),
        setupEffects ( presetSetupCallback_ ),
        pNextPreset  ( pExamplePresets      )
    {
        pExamplePresets = this;
    }

    static ExampleCodePreset const * examplePresets() { return pExamplePresets; }

    static char const * fullSamplePath( char const * );

private:
    static ExampleCodePreset const * pExamplePresets;
}; // struct ExampleCodePreset

//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // examplePresets_hpp

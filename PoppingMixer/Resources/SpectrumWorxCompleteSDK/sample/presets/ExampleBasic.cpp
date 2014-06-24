////////////////////////////////////////////////////////////////////////////////
///
/// ExampleBasic.cpp
/// ----------------
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/pitchShifter.hpp"
#include "sw_sdk/effects/slewLimiter.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
#include "osAbstraction.hpp"

#include <cstdlib>
#include <ctime>
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleBasic
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int const sampleRate )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create modules:
    Module<SlewLimiter>::Ptr const pSlewLimiter( createModule<SlewLimiter>() );
    if ( !pSlewLimiter )
    {
        OS::printFormattedError( "Out of memory: %s creation failed.", pSlewLimiter->title );
        return false;
    }

    Module<PitchShifter>::Ptr const pPitchShifter( createModule<PitchShifter>() );
    if ( !pPitchShifter )
    {
        OS::printFormattedError( "Out of memory: %s creation failed.", pPitchShifter->title );
        return false;
    }

    // Setup module parameters:
    {
        // Limit amplitude fall to 35.5 dB/second:
        pSlewLimiter->parameters().setSlewRate (                        35.5f );
        pSlewLimiter->parameters().setDirection( SlewLimiter::Direction::Fall );
        // Blend with the original signal:
        pSlewLimiter->sharedParameters().setWet(                        40    );


        // Pitch-shift only half of the frequency range:
        pPitchShifter->sharedParameters().setStartFrequency( 0.0f );
        pPitchShifter->sharedParameters().setStopFrequency ( 0.5f );
        // Or the equivalent (for a 44.1 kHz sampling rate):
        pPitchShifter->setStartFrequencyInHz(     0, sampleRate );
        pPitchShifter->setStopFrequencyInHz ( 11025, sampleRate );

        // Apply 3 dB at this module's output
        pPitchShifter->sharedParameters().setGain(  3 );
        // Blend 70% of pitch-shifted signal with 30% of original signal:
        pPitchShifter->sharedParameters().setWet ( 70 );

        // Pitch-shift 6.5 semitones up:
        pPitchShifter->parameters().setSemiTones(  6 );
        pPitchShifter->parameters().setCents    ( 50 );

        // ... or use the parameters meta interface to randomize pitch shifting:
        std::srand( static_cast<unsigned int>( std::time( 0 ) ) );
        unsigned int const semiTonesRangeSize
        (
            static_cast<unsigned int>
            (
                PitchShifter::SemiTones::maximum()
                    -
                PitchShifter::SemiTones::minimum()
            )
        );
        PitchShifter::SemiTones::value_type const randomPitch
        (
           ( std::rand() % semiTonesRangeSize )
               +
            PitchShifter::SemiTones::minimum()
        );
        pPitchShifter->set<PitchShifter::SemiTones>( randomPitch );
    }

    // Fill the module chain:
    if
    (
        !moduleChain.append( pPitchShifter ) ||
        !moduleChain.append( pSlewLimiter  )
    )
    {
        OS::printFormattedMessage( "Out of memory: adding modules to chain." );
        return false;
    }

    return true;
}

ExampleCodePreset const registeredPreset( &setup, "ExampleBasic", "SpectrumWorx.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleBasic
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

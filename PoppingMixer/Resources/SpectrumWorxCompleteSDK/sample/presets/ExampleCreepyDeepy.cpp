////////////////////////////////////////////////////////////////////////////////
///
/// ExampleCreepyDeepy.cpp
/// ----------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/pitchShifter.hpp"
#include "sw_sdk/effects/freqverb.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleCreepyDeepy
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effects:
    Module<PitchShifter>::Ptr const pPitchShifter( createModule<PitchShifter>() );
    Module<Freqverb    >::Ptr const pFreqverb    ( createModule<Freqverb    >() );

    // Setup effect parameters:
    pPitchShifter->set<PitchShifter::SemiTones>( -12 ); // Shift 12 semitones down.

    pFreqverb->set<Freqverb::Time60dB   >(  5 ); // 5 seconds long reverberation.
    pFreqverb->set<Freqverb::RoomSize   >( -3 ); // "Room" size.
    pFreqverb->set<Freqverb::ReverbPitch>(  0 ); // No pitch for reverb.

    // Fill the module chain:
    moduleChain.append( pPitchShifter );
    moduleChain.append( pFreqverb     );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleCreepyDeepy", "SpectrumWorx.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleCreepyDeepy
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

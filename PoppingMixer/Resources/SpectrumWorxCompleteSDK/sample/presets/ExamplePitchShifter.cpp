////////////////////////////////////////////////////////////////////////////////
///
/// ExamplePitchShifter.cpp
/// -----------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/pitchShifter.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExamplePitchShifter
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effect:
    Module<PitchShifter>::Ptr const pPitchShifter( createModule<PitchShifter>() );

    // Setup effect parameters:
    pPitchShifter->set<PitchShifter::SemiTones>(  6 );
    pPitchShifter->set<PitchShifter::Cents    >( 50 ); // Pitch shift 6.5 semitones.

    // Fill the module chain:
    moduleChain.append( pPitchShifter );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExamplePitchShifter", "SpectrumWorx.wav" );

//------------------------------------------------------------------------------
} // namespace ExamplePitchShifter
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

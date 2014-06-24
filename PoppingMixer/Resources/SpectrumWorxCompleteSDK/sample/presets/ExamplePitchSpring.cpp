////////////////////////////////////////////////////////////////////////////////
///
/// ExamplePitchSpring.cpp
/// ----------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/pitchSpring.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExamplePitchSpring
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effects:
    Module<PitchSpring>::Ptr const pPitchSpring( createModule<PitchSpring>() );


    // Setup effect parameters:
    pPitchSpring->set<PitchSpring::Depth >( 200 );  // Oscillate 0.2 semitones.
    pPitchSpring->set<PitchSpring::Period>( 125 );  // Oscillator period 0.125 seconds.

    // Fill the module chain:
    moduleChain.append( pPitchSpring );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExamplePitchSpring", "YeahYeahYeah.wav" );

//------------------------------------------------------------------------------
} // namespace ExamplePitchSpring
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

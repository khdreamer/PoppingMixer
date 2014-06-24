////////////////////////////////////////////////////////////////////////////////
///
/// ExampleArmonizer.cpp
/// --------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/armonizer.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleArmonizer
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effects:
    Module<Armonizer>::Ptr pArmonizer( createModule<Armonizer>() );

    // Setup effect parameters:
    pArmonizer->set<Armonizer::Interval  >(  8 );  // Harmonize with pitch interval of 8 semitones up.
    pArmonizer->set<SharedParameters::Wet>( 60 );  // Take 60% harmonized signal and 40% original signal.

    // Fill the module chain:
    moduleChain.append( pArmonizer );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleArmonizer", "YeahYeahYeah.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleArmonizer
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

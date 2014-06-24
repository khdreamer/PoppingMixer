////////////////////////////////////////////////////////////////////////////////
///
/// ExampleReverser.cpp
/// -------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/reverser.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleReverser
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effect:
    Module<Reverser>::Ptr const pReverser( createModule<Reverser>() );

    // Setup effect parameters:
    pReverser->set<Reverser::Length>( 300 ); // Reverse sound every 0.3 seconds.

    // Fill the module chain:
    moduleChain.append( pReverser );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleReverser", "SpectrumWorx.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleReverser
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

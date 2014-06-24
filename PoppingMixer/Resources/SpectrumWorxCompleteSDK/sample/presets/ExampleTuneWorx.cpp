////////////////////////////////////////////////////////////////////////////////
///
/// ExampleTuneWorx.cpp
/// -------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/tuneWorx.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleTuneWorx
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effects:
    Module<TuneWorx>::Ptr const pTuneWorx( createModule<TuneWorx>() );

    // Setup effect parameters:
    // - autotune to key A, first, fifth and eighth semitone:
    pTuneWorx->set<TuneWorx::Key   >( TuneWorx::Key::A );
    pTuneWorx->set<TuneWorx::Semi01>( true             );
    pTuneWorx->set<TuneWorx::Semi05>( true             );
    pTuneWorx->set<TuneWorx::Semi08>( true             );

    // Fill the module chain:
    moduleChain.append( pTuneWorx );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleTuneWorx", "YeahYeahYeah.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleTuneWorx
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

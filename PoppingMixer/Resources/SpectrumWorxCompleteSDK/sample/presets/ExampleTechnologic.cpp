////////////////////////////////////////////////////////////////////////////////
///
/// ExampleTechnologic.cpp
/// ----------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/slicer.hpp"
#include "sw_sdk/effects/tuneWorx.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleTechnologic
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effects:
    Module<TuneWorx>::Ptr const pTuneWorx( createModule<TuneWorx>() );
    Module<Slicer  >::Ptr const pSlicer  ( createModule<Slicer  >() );

    // Setup effect parameters:
    pTuneWorx->set<TuneWorx::Semi09>( true );
    pTuneWorx->set<TuneWorx::Semi12>( true );

    pSlicer->set<Slicer::TimeOn >( 200 ); // 0.2 seconds keep original signal.
    pSlicer->set<Slicer::TimeOff>( 100 ); // 0.1 seconds freeze the input signal.

    // Fill the module chain:
    moduleChain.append( pTuneWorx );
    moduleChain.append( pSlicer   );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleTechnologic", "SpectrumWorx.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleTechnologic
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

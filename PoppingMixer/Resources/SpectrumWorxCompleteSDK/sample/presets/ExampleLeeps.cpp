////////////////////////////////////////////////////////////////////////////////
///
/// ExampleLeeps.cpp
/// ----------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/colorifer.hpp"
#include "sw_sdk/effects/denoiser.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleLeeps
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effects:
    Module<Colorifer>::Ptr const pColorifer( createModule<Colorifer>() );
    Module<Denoiser >::Ptr const pDenoiser ( createModule<Denoiser >() );

    // Setup effect parameters:
    pDenoiser->set<Denoiser::Intensity>( 40 ); // 40% intensity.

    // Fill the module chain:
    moduleChain.append( pColorifer );
    moduleChain.append( pDenoiser  );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleLeeps", "SpectrumWorx.wav", "Sweep-20-2000.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleLeeps
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
///
/// ExampleTalkingWind.cpp
/// ----------------------
///
/// Copyright (c) 2012 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#include "sw_sdk/effects/talkingWind.hpp"
#include "sw_sdk/engine/moduleChain.hpp"
#include "sw_sdk/engine/moduleFactory.hpp"

#include "examplePresets.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace ExampleTalkingWind
{
//------------------------------------------------------------------------------

bool setup( LE::Engine::ModuleChain & moduleChain, unsigned int /*sampleRate*/ )
{
    using namespace LE::Engine;
    using namespace LE::Effects;

    // Create effect:
    Module<TalkingWind>::Ptr const pTalkingWind( createModule<TalkingWind>() );

    // Setup effect parameters:
    // talkingWind.set<TalkingWind::EnvelopeBorder>( 1000 );
    // talkingWind.set<TalkingWind::EnvelopeGain  >(    0 );

    // ...left default values for paramters.

    // Fill the module chain:
    moduleChain.append( pTalkingWind );

    // Assume all operations succeeded (error checking omitted for brevity,
    // please consult "ExampleBasic.cpp" for an example with proper error
    // handling).
    return true;
}

LE::ExampleCodePreset const registeredPreset( &setup, "ExampleTalkingWind", "SpectrumWorx.wav", "SpectrumWorxSide.wav" );

//------------------------------------------------------------------------------
} // namespace ExampleTalkingWind
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

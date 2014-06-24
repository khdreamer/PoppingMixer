////////////////////////////////////////////////////////////////////////////////
///
/// \file sharedParameters.hpp
/// --------------------------
///
/// Base parameters shared by all effects.
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef sharedParameters_hpp__8696E957_A8FB_469A_9725_CB6F63216163
#define sharedParameters_hpp__8696E957_A8FB_469A_9725_CB6F63216163
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "parameters.hpp"
#include "parameters/factoryMacro.hpp"
#include "parameters/parameter.hpp"
#include "parameters/boolean/parameter.hpp"
#include "parameters/linear/parameter.hpp"
#include "parameters/symmetric/parameter.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Effects
/// @{
#endif // LE_SW_SINGLE_EFFECT
    
namespace Effects
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Effects
/// @{
#endif // LE_SW_SINGLE_EFFECT

/// \brief Basic parameters shared by all effects
namespace SharedParameters
{
/// \name Common parameters
/// \brief Basic parameters shared by all effects
/// @{

LE_DEFINE_PARAMETERS
(
    ( ( Bypass         )( Boolean        )                                                              )
    ( ( Gain           )( SymmetricFloat )( MaximumOffset<20> )                         ( Unit<' dB'> ) )
    ( ( Wet            )( LinearFloat    )( Minimum<0> )( Maximum<100> )( Default<100> )( Unit<' %' > ) )
    ( ( StartFrequency )( LinearFloat    )( Minimum<0> )( Maximum<  1> )( Default<  0> )                )
    ( ( StopFrequency  )( LinearFloat    )( Minimum<0> )( Maximum<  1> )( Default<  1> )                )
);

/// \typedef Parameters
/// \brief Basic parameters shared/included by all effects.
///
/// - Bypass: Enables/disables the effect.
///
/// - Gain: Per effect attenuation or amplification, range [-20 dB, +20 dB]
///
/// - Wet: Dry/Wet blending between original and effected signal.
///
/// - StartFrequency: Normalized frequency value (range 0.0 to 1.0) representing
///                   starting frequency for the start-stop range where
///                   the effect will perform its action.
///
/// - StopFrequency: Normalized frequency value (range 0.0 to 1.0) representing
///                  ending frequency for the start-stop range where
///                  the effect will perform its action. Frequencies
///                  outside the range will remain unaffected.
///

/// @}
} // namespace SharedParameters
#ifndef LE_SW_SINGLE_EFFECT
/// @}
#endif // LE_SW_SINGLE_EFFECT

//------------------------------------------------------------------------------
} // namespace Effects
#ifndef LE_SW_SINGLE_EFFECT
/// @}
#endif // LE_SW_SINGLE_EFFECT
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // sharedParameters_hpp

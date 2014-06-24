////////////////////////////////////////////////////////////////////////////////
///
/// \file commonParameters.hpp
/// --------------------------
///
/// \brief Common parameters used by various effects.
///
/// Copyright (c) 2009 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef commonParameters_hpp__15BBAC13_C087_4CED_B108_E5130F26EE10
#define commonParameters_hpp__15BBAC13_C087_4CED_B108_E5130F26EE10
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "parameters/enumerated/parameter.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Effects
/// @{
#endif // LE_SW_SINGLE_EFFECT

/// \brief Effect classes
namespace Effects
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Effects
/// @{
#endif // LE_SW_SINGLE_EFFECT

/// \brief Common parameters used by various effects
namespace CommonParameters
{

/// \name Common parameters
/// \brief Common parameters used by various effects
/// @{

/// \typedef Mode
/// \brief Specifies what to operate on.
/// \details
///   - Both      : operate on both magnitudes and phases
///   - Magnitudes: operate only on magnitudes
///   - Phases    : operate only on phases
LE_ENUMERATED_PARAMETER( Mode      , ( Both )( Magnitudes )( Phases ) );
/// \typedef SpringType
/// \brief Specifies the direction for vibrato-like effects.
LE_ENUMERATED_PARAMETER( SpringType, ( Symmetric )( Up )( Down )      );

/// @}

} // namespace CommonParameters
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
#endif // commonParameters_hpp

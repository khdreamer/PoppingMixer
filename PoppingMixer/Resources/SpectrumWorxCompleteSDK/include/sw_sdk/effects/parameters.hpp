////////////////////////////////////////////////////////////////////////////////
///
/// \internal
/// \file parameters.hpp
/// --------------------
///
/// Shared LE parameter forward declarations required by all effects.
///
/// Copyright (c) 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef parameters_hpp__E052A5AB_F608_48B9_9C09_DC2497B4086D
#define parameters_hpp__E052A5AB_F608_48B9_9C09_DC2497B4086D
#pragma once
//------------------------------------------------------------------------------
#include "parameters/factoryMacro.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------

namespace Parameters
{
    template <class Traits> class Parameter; ///< \internal
    namespace Detail { struct BooleanParameterTraits; } ///< \internal

    typedef Parameter<Detail::BooleanParameterTraits> Boolean;

    struct LinearUnsignedInteger;
    struct LinearSignedInteger  ;
    struct LinearFloat          ;

    struct SymmetricInteger;
    struct SymmetricFloat  ;

    class TriggerParameter;
} // namespace Parameters

namespace Effects
{
//------------------------------------------------------------------------------

// Implementation note:
//   Import shared parameter types into the Effects namespace for less
// verbose effect parameters definitions with the LE_DEFINE_PARAMETERS macro.
//                                            (15.04.2011.) (Domagoj Saric)

using Parameters::Boolean;

using Parameters::LinearUnsignedInteger;
using Parameters::LinearSignedInteger  ;
using Parameters::LinearFloat          ;

using Parameters::SymmetricInteger;
using Parameters::SymmetricFloat  ;

using Parameters::TriggerParameter;

//------------------------------------------------------------------------------
} // namespace Effects
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // parameters_hpp

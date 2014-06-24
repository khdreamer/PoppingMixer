////////////////////////////////////////////////////////////////////////////////
///
/// \file enumerated/parameter.hpp
/// ------------------------------
///
/// Copyright (c) 2011-2013. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef parameter_hpp__5820E6B3_7684_4DF4_BC99_B0A5CCB0F3E9
#define parameter_hpp__5820E6B3_7684_4DF4_BC99_B0A5CCB0F3E9
#pragma once
//------------------------------------------------------------------------------
#include "tag.hpp"

#include "parameters/linear/parameter.hpp"

#include "boost/mpl/map/map0.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace Parameters
{
//------------------------------------------------------------------------------

namespace Detail ///< \internal
{
    template <unsigned int numberOfValues>
    struct EnumeratedParameterTraits
        :
        LinearParameterTraitsBase<0, numberOfValues - 1, 0>
    {
    public: // Types.
        typedef EnumeratedParameterTag Tag;

        typedef unsigned int value_type;
        typedef value_type   param_type;

        typedef boost::mpl::map1<Traits::Unit<0, 0>> Defaults;
        typedef boost::mpl::map0<>                   Traits  ; //...mrmlj...FMOD param info...

    public: // Values
        static unsigned int const rangeValuesDenominator = 1;

        static value_type minimum () { return                  0; }
        static value_type maximum () { return numberOfValues - 1; }
        static value_type default_() { return                  0; }

        static unsigned int const discreteValueDistance = 1;

        static unsigned int const numberOfDiscreteValues = numberOfValues;

        static bool isValidValue( value_type const value )
        {
            return isValueInRange<param_type>( value, minimum(), maximum() );
        }

    protected:
        static void increment( value_type & value ) { ++value; }
        static void decrement( value_type & value ) { --value; }
    };
} // namespace Detail

////////////////////////////////////////////////////////////////////////////////
/// \internal
/// \class EnumeratedParameter
////////////////////////////////////////////////////////////////////////////////

template <unsigned int numberOfValues>
class EnumeratedParameter
    :
    public Parameter<Detail::EnumeratedParameterTraits<numberOfValues> >
{
protected:
    typedef EnumeratedParameter EnumeratedBase;

public:
    typedef unsigned int binary_type;

    explicit EnumeratedParameter( unsigned int const initialValue = EnumeratedParameter::default_() ) : EnumeratedParameter::type( initialValue ) {}
};


////////////////////////////////////////////////////////////////////////////////
///
/// \def LE_ENUMERATED_PARAMETER
///
/// \brief Helps to define a parameter that has a discrete set of allowed
/// values.
///
///   It will assign automatically generated values to all the named values
/// specified in the valueSequence and will create a member enum with the enum
/// constants/"members" named just as specified in the valueSequence parameter.
///
////////////////////////////////////////////////////////////////////////////////

#define LE_ENUMERATED_PARAMETER( parameterName, valueSequence )                             \
    class parameterName                                                                     \
        : public LE::Parameters::EnumeratedParameter<BOOST_PP_SEQ_SIZE( valueSequence )>    \
    {                                                                                       \
    private:                                                                                \
        typedef EnumeratedBase Base;                                                        \
    public:                                                                                 \
        parameterName                                                                       \
            ( type::param_type const initialValue = Base::default_() )                      \
            : Base( initialValue ) {}                                                       \
        enum value_type { BOOST_PP_SEQ_ENUM( valueSequence ) };                             \
        operator value_type() const { return static_cast<value_type>( Base::getValue() ); } \
    }

//------------------------------------------------------------------------------
} // namespace Parameters
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // parameter_hpp

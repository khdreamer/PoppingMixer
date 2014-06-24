////////////////////////////////////////////////////////////////////////////////
///
/// \file moduleFactory.hpp
///
/// Copyright � 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef moduleFactory_hpp__699B8243_5BCB_4002_B0C7_136E93A06C27
#define moduleFactory_hpp__699B8243_5BCB_4002_B0C7_136E93A06C27
#if defined( _MSC_VER ) && !defined( DOXYGEN_ONLY )
#pragma once
#endif // MSVC && !Doxygen
//------------------------------------------------------------------------------
#include "common/abi.hpp"
#include "engine/moduleBase.hpp"

#include "boost/mpl/has_xxx.hpp"

#include "boost/config/abi_prefix.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace Engine
{
//------------------------------------------------------------------------------

#ifndef LE_SW_SINGLE_EFFECT
/// \addtogroup Engine
#endif // LE_SW_SINGLE_EFFECT
/// @{

////////////////////////////////////////////////////////////////////////////////
/**
 *  \class Module
 *  \nosubgrouping
 *
 *  \brief Implements the module concept for the specified effect.
 *
 *  The module concept is the SW SDK equivalent of a "plugin" or "audio unit" in
 *  the DAW world: generally an object capable of processing, analyzing,
 *  producing or passing through (audio) data. Currently, the SW SDK offers only
 *  modules that process data - i.e. effects. Because of this and because the
 *  public interface of the Module class template itself is rather simple,
 *  general effect related concepts will be described here also, in fact the
 *  terms module and effect will sometimes be used synonymously.
 *
 *  Each effect has a set of specific features (most notably its parameters)
 *  that the user needs to be able to access. Instead of a traditional COM-like
 *  approach (e.g. IPropertyBag), the SW SDK solves this by allowing direct
 *  access to the parameters and traits of an effect, not through an abstract
 *  interface but in a fully typed form. Because the entire set of available
 *  effects and their parameters is known in advance, in most situations you
 *  will find this approach more convenient, powerful and efficient.
 *
 *  Additionally, each effect class provides three, self-explanatory, public
 *  static data members:
 *   - char const title[]
 *   - char const description[]
 *   - bool const usesSideChannel.
 *  .
 *  All effects have a set of \link Effects::SharedParameters::Parameters
 *  basic parameters\endlink and most also have a set of specific parameters
 *  that alter their behaviour. In the SW SDK, effect parameters are not merely
 *  primitive built-in types but rather classes that implement a parameter
 *  concept. This approach enables several important features:
 *   - allows a certain level of introspection (e.g. querying the underlying
 *     fundamental type or the minimum and maximum allowed values of a
 *     parameter) which further allows parameter manipulation with generic
 *     algorithms (e.g. parameter randomization)
 *   - automatic sanity checks on the values that are assigned to them
 *   - various metaprograming techniques (such as automatic GUI generation).
 *  .
 *  Each class for an effect with parameters therefore defines a member type
 *  (whose name is the name of the parameter) for each of its own unique
 *  parameters and a type named "Parameters". The Parameters type is in effect a
 *  container type (a Boost.Fusion random-access sequence) that actually holds
 *  all of the parameters of an effect class, which need not be limited to those
 *  uniquely defined as its members but may also include common, globally
 *  defined, parameters. Let's examine this on the following example parameters:
 \verbatim
 LE_DEFINE_PARAMETERS
 (
     ( ( Mode   ) )
     ( ( Length ) ( LinearUnsignedInteger )( Minimum<1> )( Maximum<5000> )( Default<1000> )( Unit<' ms'> ) )
     ( ( Rate   ) ( SymmetricFloat        )( MaximumOffset<48> )                           ( Unit<' Hz'> ) )
 );
 \endverbatim
 * This will define a Parameters container that holds 3 parameters. One of those
 * (Mode) is an already previously defined parameter (in this case, a common
 * parameter defined in the commonParameters.hpp file). The Length and Rate
 * parameters would be unique to the effect class containing the above
 * Parameters definition. What we can read directly from the parameter
 * definitions/descriptions is that:
 *  - Length is an unsigned integer whose valid values range from 1 to 5000 in a
 *  linear fashion (i.e. it is not a logarithmic or power-of-two parameter), its
 *  default value is 1000 and it represents milliseconds
 *  - Rate is a floating point number whose values are symmetric around zero
 *  (which is also its default value) and range from -48 to +48 (all symmetric
 *  parameters are also linear) and its units are Hz.
 * .
 * As mentioned before, these parameter properties can be queried through code.
 * Each parameter provides:
 *  - a value_type typedef which denotes its underlying type (e.g. unsigned int
 *    for the above Length parameter)
 *  - minimum(), maximum() and default_() static member functions which simply
 *    return the respective values
 *  - reset() member function which effectively resets the parameter to its
 *    default value.
 *  .
 *  Besides the two relatively simple, linear parameter types described above
 *  there are other parameter types, for example boolean or enumerated
 *  parameters. Enumerated parameters require a bit more attention. Lets examine
 *  the above mentioned Mode parameter, it is defined in commonParameters.hpp
 *  as:
 \verbatim
 LE_ENUMERATED_PARAMETER( Mode, ( Both )( Magnitudes )( Phases ) );
 \endverbatim
 *  From this definition it can be seen that the Mode parameter class contains a
 *  nested enum (its value_type) with three values: Both, Magnitudes and Phases.
 *  This parameter is used by effects that allow you to choose whether you want
 *  them to operate only on the magnitudes/amplitudes or phases of individual
 *  frequencies of the given signal or on both the magnitudes and phases. All
 *  enumerated parameters have their first value as their default value. Their
 *  minimum and maximum values are, of course, their first and last enum values,
 *  respectively.
 *
 *  If the effect parameters' introspective/meta capabilities are not required,
 *  the SpectrumWorx SDK also provides "classic"/nontemplate accessors for
 *  effect parameters:
 *   - "classic" accessors:
 *     \code
 *     someEffect.sharedParameters().setWet          (        40 );
 *     someEffect.parameters      ().setSomeParameter( someValue );
 *     \endcode
 *   - template accessors:
 *     \code
 *     someEffect.set<SharedParameters::Wet          >(        40 );
 *     someEffect.set<SomeEffect      ::SomeParameter>( someValue );
 *     \endcode
 *
 *  The \link Effects::SharedParameters::Parameters frequency range parameters
 *  \endlink are defined as linear normalized values. This may be more
 *  convenient and/or efficient for internal usage but UI's will generally want
 *  to present those values in more human understandable units (decibels, hertz
 *  or percentages). As a convenience, the Hz based/non-normalized accessors
 *  for basic parameters are provided for this purpose.
 *
 *  As a convenience, each Module class template instance derives from the
 *  (empty) Effect class for which it was instantiated for to allow for
 *  less verbose user code (so that the static members of the Effect class can
 *  be accessed through it). It additionally provides a static bool constant
 *  "hasEffectSpecificParameters" which has the value true for effects with
 *  parameters other than the shared basic ones and false for those without.
 *
 *  Finally, each parameter has its defined default value and is guaranteed to
 *  be properly initialized with it on effect creation. Therefore it is not
 *  required to explicitly setup the parameters of an effect other than those
 *  whose defaults are not satisfactory for a given purpose.
 *
 *  \note Threading:
 *  Changing the parameters of an effect from a thread other than the processing
 *  thread while processing is active (i.e. the processing thread is inside the
 *  *ModuleProcessor::process() call) is safe in the sense of program
 *  correctness and stability (i.e. this will not cause a crash) but not
 *  necessarily in the sense of audio stability. The individual effects are not
 *  generally designed to cope with their parameters being changed
 *  asynchronously while they are processing a frame of data in any
 *  predetermined way, or, to put in strict wording, this invokes undefined
 *  behaviour. However, thanks to the internal engine design, you will almost
 *  always be safe to do it anyway without audible artefacts. If by some chance
 *  you find that asynchronous parameter changes do cause undesired audible
 *  artefacts in certain use cases with some effects, you can always create and
 *  hold a separate copy of the effect's Parameters and modify that instance
 *  and then, in between the calls to the ModuleProcessor::process() member
 *  function, simply assign your Parameters copy to the instance held by the
 *  corresponding module (thereby updating it).
 *
 */
////////////////////////////////////////////////////////////////////////////////

namespace Detail /// \internal
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF( Parameters );

    template <class Derived, class Effect, bool hasParameters>
    struct ParameterJoiner
    {
    public:
        template <class Parameter> Parameter const & get(                                            ) const { return const_cast<ParameterJoiner *>( this )->parameters( static_cast<Parameter *>( 0 ) ). template get<Parameter>(       ); }
        template <class Parameter> void              set( typename Parameter::param_type const value )       {                                       this  ->parameters( static_cast<Parameter *>( 0 ) ). template set<Parameter>( value ); }

        LE_NOTHROWNOALIAS typename Effect::Parameters       & parameters()       { LE_ASSUME( this ); return *EffectParameters<Effect, Derived>::get( *static_cast<Derived *>( this ) ); }
        LE_NOTHROWNOALIAS typename Effect::Parameters const & parameters() const { return const_cast<ParameterJoiner &>( *this ).parameters(); }

        static bool const hasEffectSpecificParameters = true;

    private:
        typename Effect::Parameters  & parameters( void                       * ) { return parameters         (); }
        ModuleBase::SharedParameters & parameters( ModuleBase::Bypass         * ) { return getSharedParameters(); }
        ModuleBase::SharedParameters & parameters( ModuleBase::Gain           * ) { return getSharedParameters(); }
        ModuleBase::SharedParameters & parameters( ModuleBase::Wet            * ) { return getSharedParameters(); }
        ModuleBase::SharedParameters & parameters( ModuleBase::StartFrequency * ) { return getSharedParameters(); }
        ModuleBase::SharedParameters & parameters( ModuleBase::StopFrequency  * ) { return getSharedParameters(); }

        ModuleBase::SharedParameters & getSharedParameters() { LE_ASSUME( this ); return static_cast<Derived *>( this )->sharedParameters(); }
    };

    template <class Derived, class Effect>
    struct ParameterJoiner<Derived, Effect, false>
    {
    public:
        template <class Parameter> Parameter const & get(                                            ) const { LE_ASSUME( this ); return static_cast<Derived       *>( this )->sharedParameters(). template get<Parameter>(       ); }
        template <class Parameter> void              set( typename Parameter::param_type const value )       { LE_ASSUME( this );        static_cast<Derived const *>( this )->sharedParameters(). template set<Parameter>( value ); }

        typedef void Parameters;

        static bool const hasEffectSpecificParameters = false;

        static void const * parameters() { return 0; }
    };
} // namespace Detail


template <class Effect>
class Module
    :
    public ModuleBase,
    public Effect
#ifndef DOXYGEN_ONLY
   ,public Detail::ParameterJoiner<Module<Effect>, Effect, Detail::has_Parameters<Effect>::value>
#endif // DOXYGEN_ONLY
{
#ifdef DOXYGEN_ONLY
public:
    static char const title[];
    static char const description[];
    static bool const usesSideChannel;
    static bool const hasEffectSpecificParameters;

    /// \name Parameters
    /// @{
    typedef typename Effects::SharedParameters::Parameters SharedParameters; ///< \brief Basic parameters provided by all effects.
    typedef typename Effect                   ::Parameters Parameters      ; ///< \brief Effect specific parameters (void if hasEffectSpecificParameters == false).
    /// @}
public:
    /// \name Classic parameter accessors
    ///@{
    SharedParameters       & sharedParameters()      ;
    SharedParameters const & sharedParameters() const;
    Parameters             & parameters      ()      ;
    Parameters       const & parameters      () const;
    ///@}

    /// \name Template parameter accessors
    ///@{
    template <class Parameter> Parameter const & get(                                      ) const;
    template <class Parameter> void              set( typename Parameter::param_type value )      ;
    /// @}
#endif // DOXYGEN_ONLY

public:
    /// \name Factory function
    ///@{

    typedef boost::intrusive_ptr<Module<Effect>      >  Ptr;
    typedef boost::intrusive_ptr<Module<Effect> const> CPtr;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Creates a new module for <VAR>Effect</VAR>
    /// \return A Module instance (or null in case of a memory allocation
    /// failure).
    ////////////////////////////////////////////////////////////////////////////

    static LE_NOTHROWNOALIAS Ptr create();

    ///@}

private:
    Module(); ///< \internal
};


////////////////////////////////////////////////////////////////////////////////
//
// createModule()
// --------------
//
////////////////////////////////////////////////////////////////////////////////
///
/// \brief Global module factory function.
/// \related Module
///
/// A convenience free function that simply calls Module<Effect>::create().
///
/// \throws none
///
////////////////////////////////////////////////////////////////////////////////

template <class Effect>
typename Module<Effect>::Ptr createModule() { return Module<Effect>::create(); }

/** @} */ // group Engine

//------------------------------------------------------------------------------
} // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------

#include "boost/config/abi_suffix.hpp"

#endif // moduleFactory_hpp

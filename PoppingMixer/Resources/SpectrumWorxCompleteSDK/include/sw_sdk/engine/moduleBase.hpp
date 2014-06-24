////////////////////////////////////////////////////////////////////////////////
///
/// \internal
/// \file moduleBase.hpp
///
/// Copyright � 2011 - 2014. Little Endian Ltd. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
#ifndef moduleBase_hpp__3A6E3E31_35A3_400F_8749_D655D2C7B921
#define moduleBase_hpp__3A6E3E31_35A3_400F_8749_D655D2C7B921
#pragma once
//------------------------------------------------------------------------------
#include "common/abi.hpp"
#include "effects/sharedParameters.hpp"

#include "boost/noncopyable.hpp"
/// \note Workaround for a possible compilation error on Android in
/// boost/smart_ptr/detail/sp_nullptr_t.hpp.
///                                           (29.10.2013.) (Domagoj Saric)
#if !defined( BOOST_NO_CXX11_NULLPTR ) && defined( __ANDROID__ ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __GLIBCXX__ )
    #define BOOST_NO_CXX11_NULLPTR
#endif // GCC w/o libstdc++
#include "boost/smart_ptr/intrusive_ptr.hpp"
//------------------------------------------------------------------------------
namespace LE
{
//------------------------------------------------------------------------------
namespace Engine
{
//------------------------------------------------------------------------------

class ModuleProcessor;

namespace Detail /// \internal
{
    LE_NOTHROWNOALIAS void  LE_FASTCALL_ABI setStartFrequencyInHz( float frequency, ModuleProcessor const *, Effects::SharedParameters::Parameters       * );
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI getStartFrequencyInHz(                  ModuleProcessor const *, Effects::SharedParameters::Parameters const * );
    LE_NOTHROWNOALIAS void  LE_FASTCALL_ABI setStartFrequencyInHz( float frequency, unsigned int sampleRate, Effects::SharedParameters::Parameters       * );
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI getStartFrequencyInHz(                  unsigned int sampleRate, Effects::SharedParameters::Parameters const * );

    LE_NOTHROWNOALIAS void  LE_FASTCALL_ABI setStopFrequencyInHz ( float frequency, ModuleProcessor const *, Effects::SharedParameters::Parameters       * );
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI getStopFrequencyInHz (                  ModuleProcessor const *, Effects::SharedParameters::Parameters const * );
    LE_NOTHROWNOALIAS void  LE_FASTCALL_ABI setStopFrequencyInHz ( float frequency, unsigned int sampleRate, Effects::SharedParameters::Parameters       * );
    LE_NOTHROWNOALIAS float LE_FASTCALL_ABI getStopFrequencyInHz (                  unsigned int sampleRate, Effects::SharedParameters::Parameters const * );

    template <class Derived>
    class SharedParametersHelper ///<
    {
    public:
        /// \name Basic parameters included by all effects
        /// @{
        typedef Effects::SharedParameters::Parameters SharedParameters;

        typedef Effects::SharedParameters::Bypass         Bypass        ;
        typedef Effects::SharedParameters::Gain           Gain          ;
        typedef Effects::SharedParameters::Wet            Wet           ;
        typedef Effects::SharedParameters::StartFrequency StartFrequency;
        typedef Effects::SharedParameters::StopFrequency  StopFrequency ;
        /// @}

    public:
        /// \name Hz based/non-normalized accessors for frequency range parameters
        ///@{
        void  setStartFrequencyInHz( float const frequency, ModuleProcessor const &       processor  )       { return Detail::setStartFrequencyInHz( frequency, &processor, &sharedParameters() ); }
        float getStartFrequencyInHz(                        ModuleProcessor const &       processor  ) const { return Detail::getStartFrequencyInHz(            &processor, &sharedParameters() ); }
        void  setStartFrequencyInHz( float const frequency, unsigned int            const sampleRate )       { return Detail::setStartFrequencyInHz( frequency, sampleRate, &sharedParameters() ); }
        float getStartFrequencyInHz(                        unsigned int            const sampleRate ) const { return Detail::getStartFrequencyInHz(            sampleRate, &sharedParameters() ); }

        void  setStopFrequencyInHz ( float const frequency, ModuleProcessor const &       processor  )       { return Detail::setStopFrequencyInHz ( frequency, &processor, &sharedParameters() ); }
        float getStopFrequencyInHz (                        ModuleProcessor const &       processor  ) const { return Detail::getStopFrequencyInHz (            &processor, &sharedParameters() ); }
        void  setStopFrequencyInHz ( float const frequency, unsigned int            const sampleRate )       { return Detail::setStopFrequencyInHz ( frequency, sampleRate, &sharedParameters() ); }
        float getStopFrequencyInHz (                        unsigned int            const sampleRate ) const { return Detail::getStopFrequencyInHz (            sampleRate, &sharedParameters() ); }
        ///@}

    private:
        SharedParameters       & sharedParameters()       { LE_ASSUME( this ); return static_cast<Derived       *>( this )->sharedParameters(); }
        SharedParameters const & sharedParameters() const { LE_ASSUME( this ); return static_cast<Derived const *>( this )->sharedParameters(); }
    };

    template <class Effect, class Holder>
    struct EffectParameters { LE_NOTHROWRESTRICTNOALIAS static typename Effect::Parameters * LE_FASTCALL_ABI get( Holder & ); };
} // namespace Detail


////////////////////////////////////////////////////////////////////////////////
/// \class ModuleBase
////////////////////////////////////////////////////////////////////////////////

class ModuleBase
    :
    public Detail::SharedParametersHelper<ModuleBase>,
    public boost::noncopyable
{
public:
    typedef boost::intrusive_ptr<ModuleBase      >  Ptr;
    typedef boost::intrusive_ptr<ModuleBase const> CPtr;

    SharedParameters       & sharedParameters()       { return sharedParameters_; }
    SharedParameters const & sharedParameters() const { return sharedParameters_; }

protected: /// \internal
     ModuleBase() {}
    ~ModuleBase() {};

private:
    SharedParameters sharedParameters_;
};

typedef ModuleBase::Ptr ModulePtr;

// boost::intrusive_ptr required details
void LE_NOTHROWNOALIAS LE_FASTCALL_ABI intrusive_ptr_add_ref( ModuleBase const * ); ///< \internal
void LE_NOTHROWNOALIAS LE_FASTCALL_ABI intrusive_ptr_release( ModuleBase const * ); ///< \internal

//------------------------------------------------------------------------------
} // namespace Engine
//------------------------------------------------------------------------------
} // namespace LE
//------------------------------------------------------------------------------
#endif // moduleBase_hpp

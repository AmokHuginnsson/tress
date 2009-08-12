/*
---           `yaal' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

	hcall.hxx - this file is integral part of `yaal' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/
/*! \file hcore/call.hxx
 * \brief Declaration and implementation of HCall<> template.
 */

#ifndef YAAL_HCORE_HCALL_HXX_INCLUDED
#define YAAL_HCORE_HCALL_HXX_INCLUDED

#include <yaal/config.hxx>

#include <yaal/hcore/hpointer.hxx>
#include <yaal/hcore/trait.hxx>

namespace yaal
{

namespace hcore
{

namespace free_standing_call_args
{

struct arg_base
	{
	typedef trait::no_type free_standing_call_arg_type_t;
	};

template<int arg_no>
struct arg : public arg_base
	{
	};

}

extern free_standing_call_args::arg<1> _1;
extern free_standing_call_args::arg<2> _2;
extern free_standing_call_args::arg<3> _3;
extern free_standing_call_args::arg<4> _4;
extern free_standing_call_args::arg<5> _5;
extern free_standing_call_args::arg<6> _6;
extern free_standing_call_args::arg<7> _7;
extern free_standing_call_args::arg<8> _8;
extern free_standing_call_args::arg<9> _9;
extern free_standing_call_args::arg<10> _10;

free_standing_call_args::arg<1> _1;
free_standing_call_args::arg<2> _2;
free_standing_call_args::arg<3> _3;
free_standing_call_args::arg<4> _4;
free_standing_call_args::arg<5> _5;
free_standing_call_args::arg<6> _6;
free_standing_call_args::arg<7> _7;
free_standing_call_args::arg<8> _8;
free_standing_call_args::arg<9> _9;
free_standing_call_args::arg<10> _10;

template<typename CLASS_t, typename METHOD_t,
	typename a0_t = trait::no_type, typename a1_t = trait::no_type,
	typename a2_t = trait::no_type, typename a3_t = trait::no_type,
	typename a4_t = trait::no_type, typename a5_t = trait::no_type,
	typename a6_t = trait::no_type, typename a7_t = trait::no_type,
	typename a8_t = trait::no_type, typename a9_t = trait::no_type>
struct call_calculator
	{
	struct free_standing_args
		{
		static int const value =
			ternary<trait::is_kind_of<a0_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a1_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a2_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a3_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a4_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a5_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a6_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a7_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a8_t, free_standing_call_args::arg_base>::value, 1, 0>::value
			+ ternary<trait::is_kind_of<a9_t, free_standing_call_args::arg_base>::value, 1, 0>::value;
		};
	};

/*! \brief Interface to abstration of any-method of any-class invocation.
 */
template<typename return_t = void>
class HCallInterface0
	{
public:
	typedef yaal::hcore::HPointer<HCallInterface0<return_t> > ptr_t;
	virtual ~HCallInterface0( void ) {}
	return_t operator()( void )
		{ return ( do_invoke() ); }
	return_t operator()( void ) const
		{ return ( do_invoke() ); }
	return_t invoke( void )
		{ return ( do_invoke() ); }
	return_t invoke( void ) const
		{ return ( do_invoke() ); }
	void const* id( void ) const
		{ return ( do_id() ); }
protected:
	virtual void do_invoke( void ) = 0;
	virtual void do_invoke( void ) const = 0;
	virtual void const* do_id( void ) const = 0;
	};

/*! \brief Make a functor from any standalone function.
 */
template<typename call_t,
	typename a0_t = trait::no_type,
	typename a1_t = trait::no_type,
	typename a2_t = trait::no_type,
	typename a3_t = trait::no_type,
	typename a4_t = trait::no_type,
	typename a5_t = trait::no_type,
	typename a6_t = trait::no_type,
	typename a7_t = trait::no_type,
	typename a8_t = trait::no_type,
	typename a9_t = trait::no_type>
class HFunctor
	{
	call_t& call;
public:
	HFunctor( call_t& a_call ) : call( a_call ) {}
	void method(
			a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4,
			a5_t a5, a6_t a6, a7_t a7, a8_t a8, a9_t a9 )
		{ call( a0, a1, a2, a3, a4, a5, a6, a7, a8, a9 ); }
	void method(
			a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4,
			a5_t a5, a6_t a6, a7_t a7, a8_t a8 )
		{ call( a0, a1, a2, a3, a4, a5, a6, a7, a8 ); }
	void method(
			a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4,
			a5_t a5, a6_t a6, a7_t a7 )
		{ call( a0, a1, a2, a3, a4, a5, a6, a7 ); }
	void method(
			a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4,
			a5_t a5, a6_t a6 )
		{ call( a0, a1, a2, a3, a4, a5, a6 ); }
	void method(
			a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4,
			a5_t a5 )
		{ call( a0, a1, a2, a3, a4, a5 ); }
	void method(
			a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4 )
		{ call( a0, a1, a2, a3, a4 ); }
	void method( a0_t a0, a1_t a1, a2_t a2, a3_t a3 )
		{ call( a0, a1, a2, a3 ); }
	void method( a0_t a0, a1_t a1, a2_t a2 )
		{ call( a0, a1, a2 ); }
	void method( a0_t a0, a1_t a1 )
		{ call( a0, a1 ); }
	void method( a0_t a0 )
		{ call( a0 ); }
	void method( void )
		{ call(); }
	void method( void ) const
		{ call(); }
	};

/*! \brief Base class for HCall<1..10>.
 */
template<typename CLASS_t, typename METHOD_t>
class HCallBase : public HCallInterface0<typename trait::return_type<METHOD_t>::type>
	{
protected:
	CLASS_t f_oObject;
	METHOD_t METHOD;
public:
	HCallBase( CLASS_t obj, METHOD_t A_METHOD ) : f_oObject( obj ), METHOD( A_METHOD ) {}
protected:
	virtual void const* do_id( void ) const
		{ return ( &f_oObject ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t = trait::no_type, typename a1_t = trait::no_type,
	typename a2_t = trait::no_type, typename a3_t = trait::no_type,
	typename a4_t = trait::no_type, typename a5_t = trait::no_type,
	typename a6_t = trait::no_type, typename a7_t = trait::no_type,
	typename a8_t = trait::no_type, typename a9_t = trait::no_type>
class HCall;

/*! \cond */
template<typename CLASS_t, typename METHOD_t>
class HCall<CLASS_t, METHOD_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD )
		: base_t( obj, A_METHOD ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)(); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)(); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t>
class HCall<CLASS_t, METHOD_t,
	a0_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t, a3_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t, a3_t, a4_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type,
	trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
	a4_t f_xArg4;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3, a4_t a4 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ), f_xArg4( a4 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t, a3_t, a4_t, a5_t,
	trait::no_type, trait::no_type,
	trait::no_type, trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
	a4_t f_xArg4;
	a5_t f_xArg5;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3, a4_t a4, a5_t a5 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ), f_xArg4( a4 ),
		f_xArg5( a5 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t, typename a6_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t,
	trait::no_type, trait::no_type,
	trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
	a4_t f_xArg4;
	a5_t f_xArg5;
	a6_t f_xArg6;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ), f_xArg4( a4 ),
		f_xArg5( a5 ), f_xArg6( a6 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t, typename a6_t, typename a7_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t,
	trait::no_type, trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
	a4_t f_xArg4;
	a5_t f_xArg5;
	a6_t f_xArg6;
	a7_t f_xArg7;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6, a7_t a7 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ), f_xArg4( a4 ),
		f_xArg5( a5 ), f_xArg6( a6 ), f_xArg7( a7 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6, f_xArg7 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6, f_xArg7 ); }
	};

template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t, typename a6_t, typename a7_t,
	typename a8_t>
class HCall<CLASS_t, METHOD_t,
	a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t,
	trait::no_type> : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
	a4_t f_xArg4;
	a5_t f_xArg5;
	a6_t f_xArg6;
	a7_t f_xArg7;
	a8_t f_xArg8;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6, a7_t a7,
			a8_t a8 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ), f_xArg4( a4 ),
		f_xArg5( a5 ), f_xArg6( a6 ), f_xArg7( a7 ), f_xArg8( a8 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6, f_xArg7, f_xArg8 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6, f_xArg7, f_xArg8 ); }
	};
/*! \endcond */

/*! \brief Implementation of abstration of any-method of any-class invocation.
 *
 * \tparam CLASS_t - class on which this invocation will operate.
 * \tparam METHOD_t - method of given class CLASS_t that shall be invoked.
 * \tparam a0_t - first argument to given METHOD_t of CLASS_t.
 * \tparam a1_t - second argument to given METHOD_t of CLASS_t.
 * \tparam aN_t - N-th argument to given METHOD_t of CLASS_t.
 */
template<typename CLASS_t, typename METHOD_t,
	typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t, typename a6_t, typename a7_t,
	typename a8_t, typename a9_t>
class HCall : public HCallBase<CLASS_t, METHOD_t>
	{
	typedef HCallBase<CLASS_t, METHOD_t> base_t;
protected:
	a0_t f_xArg0;
	a1_t f_xArg1;
	a2_t f_xArg2;
	a3_t f_xArg3;
	a4_t f_xArg4;
	a5_t f_xArg5;
	a6_t f_xArg6;
	a7_t f_xArg7;
	a8_t f_xArg8;
	a9_t f_xArg9;
public:
	HCall( CLASS_t obj, METHOD_t A_METHOD, a0_t a0, a1_t a1,
			a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6, a7_t a7,
			a8_t a8, a9_t a9 )
		: base_t( obj, A_METHOD ),
		f_xArg0( a0 ), f_xArg1( a1 ), f_xArg2( a2 ), f_xArg3( a3 ), f_xArg4( a4 ),
		f_xArg5( a5 ), f_xArg6( a6 ), f_xArg7( a7 ), f_xArg8( a8 ), f_xArg9( a9 ) {}
protected:
	virtual void do_invoke( void )
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6, f_xArg7, f_xArg8, f_xArg9 ); }
	virtual void do_invoke( void ) const
		{ (base_t::f_oObject.*base_t::METHOD)( f_xArg0, f_xArg1, f_xArg2, f_xArg3, f_xArg4, f_xArg5, f_xArg6, f_xArg7, f_xArg8, f_xArg9 ); }
	};

template<typename CLASS_t, typename METHOD_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t>(
					obj, A_METHOD ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t>(
					obj, A_METHOD, a0 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t,
	typename a1_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t>(
					obj, A_METHOD, a0, a1 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t,
	typename a1_t,
	typename a2_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t>(
					obj, A_METHOD, a0, a1, a2 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t,
	typename a1_t, typename a2_t, typename a3_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t>(
					obj, A_METHOD, a0, a1, a2, a3 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t,
	typename a1_t, typename a2_t, typename a3_t, typename a4_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t, a4_t>(
					obj, A_METHOD, a0, a1, a2, a3, a4 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t, typename a1_t,
	typename a2_t, typename a3_t, typename a4_t, typename a5_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4, a5_t a5 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t>(
					obj, A_METHOD, a0, a1, a2, a3, a4, a5 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t, typename a1_t,
	typename a2_t, typename a3_t, typename a4_t, typename a5_t, typename a6_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t>(
					obj, A_METHOD, a0, a1, a2, a3, a4, a5, a6 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t, typename a1_t,
	typename a2_t, typename a3_t, typename a4_t, typename a5_t, typename a6_t,
	typename a7_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6, a7_t a7 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t>(
					obj, A_METHOD, a0, a1, a2, a3, a4, a5, a6, a7 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t, typename a1_t,
	typename a2_t, typename a3_t, typename a4_t, typename a5_t, typename a6_t,
	typename a7_t, typename a8_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6, a7_t a7, a8_t a8 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t>(
					obj, A_METHOD, a0, a1, a2, a3, a4, a5, a6, a7, a8 ) ) ); }

template<typename CLASS_t, typename METHOD_t, typename a0_t, typename a1_t,
	typename a2_t, typename a3_t, typename a4_t, typename a5_t, typename a6_t,
	typename a7_t, typename a8_t, typename a9_t>
HCallInterface0<>::ptr_t call( CLASS_t obj, METHOD_t A_METHOD,
		a0_t a0, a1_t a1, a2_t a2, a3_t a3, a4_t a4, a5_t a5, a6_t a6, a7_t a7, a8_t a8, a9_t a9 )
	{ return ( HCallInterface0<>::ptr_t(
				new HCall<CLASS_t, METHOD_t, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t, a9_t>(
					obj, A_METHOD, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9 ) ) ); }

typedef HCallInterface0<> HCallInterface;

}

}


#endif /* not YAAL_HCORE_HCALL_HXX_INCLUDED */

/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hcall
	{
	struct SIGNATURE
		{
		typedef int signature_t;
		static int const INVALID;
		static int const FV;
		static int const F1I;
		static int const F2I;
		static int const F3I;
		static int const F4I;
		static int const F5I;
		static int const F6I;
		static int const F7I;
		static int const F8I;
		static int const F9I;
		static int const F10I;
		};
	SIGNATURE::signature_t _signature;
	int _int[10];
	double _double[10];
	tut_yaal_hcore_hcall( void ) : _signature( SIGNATURE::INVALID ) {}
	void reset( void )
		{
		_signature = SIGNATURE::INVALID;
		yaal::fill( _int, _int + sizeof( _int ) / sizeof ( int ), -1 );
		yaal::fill( _double, _double + sizeof( _double ) / sizeof ( double ), -1 );
		}
	void fv( void )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::FV;
		}
	void f1i( int i0 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F1I;
		_int[ 0 ] = i0;
		}
	void f2i( int i0, int i1 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F2I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		}
	void f3i( int i0, int i1, int i2 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F3I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		}
	void f4i( int i0, int i1, int i2, int i3 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F4I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		}
	void f5i( int i0, int i1, int i2, int i3, int i4 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F5I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		_int[ 4 ] = i4;
		}
	void f6i( int i0, int i1, int i2, int i3, int i4, int i5 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F6I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		_int[ 4 ] = i4;
		_int[ 5 ] = i5;
		}
	void f7i( int i0, int i1, int i2, int i3, int i4, int i5, int i6 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F7I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		_int[ 4 ] = i4;
		_int[ 5 ] = i5;
		_int[ 6 ] = i6;
		}
	void f8i( int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F8I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		_int[ 4 ] = i4;
		_int[ 5 ] = i5;
		_int[ 6 ] = i6;
		_int[ 7 ] = i7;
		}
	void f9i( int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F9I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		_int[ 4 ] = i4;
		_int[ 5 ] = i5;
		_int[ 6 ] = i6;
		_int[ 7 ] = i7;
		_int[ 8 ] = i8;
		}
	void f10i( int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9 )
		{
		cout << __PRETTY_FUNCTION__ << endl;
		_signature = SIGNATURE::F10I;
		_int[ 0 ] = i0;
		_int[ 1 ] = i1;
		_int[ 2 ] = i2;
		_int[ 3 ] = i3;
		_int[ 4 ] = i4;
		_int[ 5 ] = i5;
		_int[ 6 ] = i6;
		_int[ 7 ] = i7;
		_int[ 8 ] = i8;
		_int[ 9 ] = i9;
		}
	virtual ~tut_yaal_hcore_hcall( void )
		{}
	};

int const tut_yaal_hcore_hcall::SIGNATURE::INVALID = -1;
int const tut_yaal_hcore_hcall::SIGNATURE::FV = 0;
int const tut_yaal_hcore_hcall::SIGNATURE::F1I = 1;
int const tut_yaal_hcore_hcall::SIGNATURE::F2I = 2;
int const tut_yaal_hcore_hcall::SIGNATURE::F3I = 3;
int const tut_yaal_hcore_hcall::SIGNATURE::F4I = 4;
int const tut_yaal_hcore_hcall::SIGNATURE::F5I = 5;
int const tut_yaal_hcore_hcall::SIGNATURE::F6I = 6;
int const tut_yaal_hcore_hcall::SIGNATURE::F7I = 7;
int const tut_yaal_hcore_hcall::SIGNATURE::F8I = 8;
int const tut_yaal_hcore_hcall::SIGNATURE::F9I = 9;
int const tut_yaal_hcore_hcall::SIGNATURE::F10I = 10;

TUT_TEST_GROUP_N( tut_yaal_hcore_hcall, "yaal::hcore::HCall" );

TUT_UNIT_TEST_N( 1, "a member (no args)" )
	reset();
	static int const post[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::fv )> call_two_t;
	call_two_t c( *this, &tut_yaal_hcore_hcall::fv );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::FV );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "a member (one int arg)" )
	reset();
	static int const post[10] = { 0, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f1i ), int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f1i, 0 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F1I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "a member (two int arg)" )
	reset();
	static int const post[10] = { 0, 1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f2i ), int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f2i, 0, 1 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F2I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "a member (3 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, -1, -1, -1, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f3i ), int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f3i, 0, 1, 2 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F3I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "a member (4 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, -1, -1, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f4i ), int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f4i, 0, 1, 2, 3 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F4I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "a member (5 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, -1, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f5i ), int, int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f5i, 0, 1, 2, 3, 4 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F5I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "a member (6 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, -1, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f6i ), int, int, int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f6i, 0, 1, 2, 3, 4, 5 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F6I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "a member (7 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, -1, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f7i ), int, int, int, int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f7i, 0, 1, 2, 3, 4, 5, 6 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F7I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "a member (8 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, -1, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f8i ), int, int, int, int, int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f8i, 0, 1, 2, 3, 4, 5, 6, 7 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F8I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "a member (9 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, -1 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f9i ), int, int, int, int, int, int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f9i, 0, 1, 2, 3, 4, 5, 6, 7, 8 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F9I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "a member (10 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	typedef HCall<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f10i ), int, int, int, int, int, int, int, int, int, int> call_t;
	call_t c( *this, &tut_yaal_hcore_hcall::f10i, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F10I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

class Sumator
	{
	int _arg;
public:
	Sumator( int arg_ ) : _arg( arg_ ) {}
	int calculate( int arg_ )
		{ return ( _arg + arg_ ); }
	int calculate_const( int arg_ ) const
		{ return ( _arg + arg_ ); }
	int calculate_volatile( int arg_ ) volatile
		{ return ( _arg + arg_ ); }
	int calculate_const_volatile( int arg_ ) const volatile
		{ return ( _arg + arg_ ); }
	int sum( int a0, int a1, int a2, int a3, int a4, int a5 )
		{
		return ( _arg + a0 + a1 + a2 + a3 + a4 + a5 );
		}
	};

template<typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t>
int cf( a0_t = trait::no_type(), a1_t = trait::no_type(),
		a2_t = trait::no_type(), a3_t = trait::no_type(),
		a4_t = trait::no_type(), a5_t = trait::no_type() )
	{
	return ( call_calculator<int, int, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t>::free_standing_args::value );
	}

TUT_UNIT_TEST_N( 12, "4 free standing args" )
	Sumator s( 1 );
#if 0
	call( 2, _1, 4, 8, _2, 16 )( 100, 2000 );
#endif
	cout << cf( 2, _1, 4, 8, _2, 16 ) << endl;
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <set>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.h"

using namespace tut;
using namespace std;
using namespace boost;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal
	{
	};

typedef test_group<tut_yaal> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_group( "yaal" );

/* abstract call */

struct ci
	{
	struct dummy{};
	virtual ~ci() {}
	virtual void visit( void ) = 0;
	};

template<typename c_t, typename m_t,
	typename a1t = ci::dummy, typename a2t = ci::dummy>
struct call : public ci
	{
	c_t _obj;
	m_t M;
	a1t _a1;
	a2t _a2;
	call( c_t obj, m_t m, a1t a1 = a1t(), a2t a2 = a2t() )
		: _obj( obj ), M( m ), _a1( a1 ), _a2( a2 ) {}
	void visit( a1t const*, a2t const* )
		{ (_obj.*M)( _a1, _a2 ); }
	void visit( a1t const*, ci::dummy* )
		{ (_obj.*M)( _a1 ); }
	void visit( ci::dummy*, ci::dummy* )
		{ (_obj.*M)(); }
	virtual void visit( void )
		{ visit( static_cast<a1t*>( NULL ), static_cast<a2t*>( NULL ) ); }
	};

struct prod
	{
	void foo()
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void bar( int a1 )
		{ cout << __PRETTY_FUNCTION__ << ": " << a1 << endl; }
	void baz( int a1, int a2 )
		{ cout << __PRETTY_FUNCTION__ << ": " << a1 << ", " << a2 << endl; }
	};

template<>
template<>
void module::test<1>( void )
	{
	prod p;
	call<prod&, typeof( &prod::foo )> c0( p, &prod::foo );
	c0.visit();
	call<prod&, typeof( &prod::bar ), int> c1( p, &prod::bar, 3 );
	c1.visit();
	call<prod&, typeof( &prod::baz ), int, int> c2( p, &prod::baz, 11, -7 );
	c2.visit();
	}

bool greater( int long a, int long b )
	{
	return ( a > b );
	}

template<>
template<>
void module::test<2>( void )
	{
	bool p = yaal::bind2nd( &greater, 4 )( 3 );
	bool q = yaal::bind2nd( &greater, 1 )( 3 );
	cout << p << q << endl;
	}

class Derived;
class FunkyDerived;
class Visitor
	{
public:
	virtual ~Visitor( void ) { }
	virtual void visit( Derived& ) { };
	virtual void visit( Derived const& ) const { };
	virtual void visit( FunkyDerived& ) { };
	virtual void visit( FunkyDerived const& ) const { };
	};

class HVisitorInterface
	{
public:
	virtual ~HVisitorInterface( void ) { }
	virtual void accept( Visitor& ) { }
	virtual void accept( Visitor const& ) const { }
	};

struct Base : public HVisitorInterface
	{
	virtual ~Base( void ) {}
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	};

struct Derived : public Base
	{
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void baz( void ) const
		{ cout << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visit( *this ); }
	};

struct FunkyDerived : public Base
	{
	virtual void foo( void )
		{ cout << __PRETTY_FUNCTION__ << endl; }
	void bar( void ) const
		{ cout << __PRETTY_FUNCTION__ << endl; }
	virtual void accept( Visitor const& call ) const
		{ call.visit( *this ); }
	};

class FunkyDerivedBarCall : public Visitor
	{
public:
	void visit( FunkyDerived const& obj ) const
		{ obj.bar(); }
	};

class DerivedBazCall : public Visitor
	{
public:
	void visit( Derived const& obj ) const
		{ obj.baz(); }
	};

template<>
template<>
void module::test<3>( void )
	{
	typedef HPointer<Base> base_ptr_t;
	base_ptr_t a = base_ptr_t( new Derived );
	base_ptr_t b = base_ptr_t( new FunkyDerived );
	(*a).foo();
	(*b).foo();
	if ( dynamic_cast<FunkyDerived*>( a.raw() ) )
		dynamic_cast<FunkyDerived*>( a.raw() )->bar();
	else
		cout << "a is not proper type" << endl;
	if ( dynamic_cast<FunkyDerived*>( b.raw() ) )
		dynamic_cast<FunkyDerived*>( b.raw() )->bar();
	else
		cout << "b is not proper type" << endl;
	if ( dynamic_cast<Derived*>( a.raw() ) )
		dynamic_cast<Derived*>( a.raw() )->baz();
	else
		cout << "a is not proper type" << endl;
	if ( dynamic_cast<Derived*>( b.raw() ) )
		dynamic_cast<Derived*>( b.raw() )->baz();
	else
		cout << "b is not proper type" << endl;
	cout << "now the same but without dynamic cast" << endl;
	a->accept( FunkyDerivedBarCall() );
	b->accept( FunkyDerivedBarCall() );
	a->accept( DerivedBazCall() );
	b->accept( DerivedBazCall() );
	}

struct A
	{
	A( void ) { cout << __PRETTY_FUNCTION__ << endl; }
	~A( void ) { cout << __PRETTY_FUNCTION__ << endl; }
	};

struct B : public A
	{
	B( void ) { cout << __PRETTY_FUNCTION__ << endl; }
	~B( void ) { cout << __PRETTY_FUNCTION__ << endl; }
	};

template<>
template<>
void module::test<4>( void )
	{
	typedef HPointer<A> pa_t;

	pa_t p( new B );
	/*
	 * CUTE test
	 * ensure_equals( "Life, Universe and everything ...", 44, 42 );
	}

template<>
template<>
void module::test<5>( void )
	{
	}

template<>
template<>
void module::test<6>( void )
	{
	 * CUTE test
	 * fail( "just a test" );
	 */
	}

}


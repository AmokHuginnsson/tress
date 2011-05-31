/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hexception.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hexception
	{

class A
	{
	typedef A this_type;
public:
	virtual ~A( void ) { }
	virtual void foo( int a ) const
		{ do_foo( a ); }
private:
	virtual void do_foo( int a ) const
		{
		if ( ! a )
			M_THROW( "bad arg A", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<A> AE;

class B : public A
	{
public:
	virtual ~B( void ) { }
protected:
	typedef B this_type;
	typedef A base_type;
	virtual void do_foo( int a ) const
		{
		if ( ! a )
			M_THROW( "bad arg B", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<B,AE> BE;

class C : public B
	{
public:
	virtual ~C( void ) { }
protected:
	typedef C this_type;
	typedef B base_type;
	virtual void do_foo( int a ) const
		{
		if ( ! a )
			M_THROW( "bad arg C", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<C,BE> CE;

class P
	{
	typedef P this_type;
public:
	virtual ~P( void ) { }
	virtual void foo( int a ) const
		{ do_foo( a ); }
private:
	virtual void do_foo( int a ) const
		{
		if ( ! a )
			M_THROW( "bad arg P", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<P> PE;

class Q : public P
	{
public:
	virtual ~Q( void ) { }
private:
	typedef Q this_type;
	virtual void do_foo( int a ) const
		{
		if ( ! a )
			M_THROW( "bad arg Q", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<Q,PE> QE;

class R : public Q
	{
public:
	virtual ~R( void ) { }
protected:
	typedef R this_type;
	typedef Q base_type;
	virtual void do_foo( int a ) const
		{
		if ( ! a )
			M_THROW( "bad arg R", a );
		cout << a << endl;
		}
	};

typedef HExceptionT<R,QE> RE;

	virtual ~tut_yaal_hcore_hexception( void )
		{}
	};

TUT_TEST_GROUP( tut_yaal_hcore_hexception, "yaal::hcore::HException" );

TUT_UNIT_TEST( 1, "valid ex hier construct for full hier" )
	try
		{
		A x;
		x.foo( 0 );
		FAIL( "test bug, exception not thrown" );
		}
	catch ( CE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( BE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( AE const& e )
		{
		HString etype( demangle( typeid( e ).name() ) );
		HString aetype( demangle( typeid( AE ).name() ) );
		ENSURE_EQUALS( "bad generated type", etype, aetype );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		e.print_error();
		FAIL( "bad exception caught" );
		}
	catch ( ... )
		{
		FAIL( "bad exception caught" );
		}
	try
		{
		B x;
		x.foo( 0 );
		FAIL( "test bug, exception not thrown" );
		}
	catch ( CE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( BE const& e )
		{
		HString etype( demangle( typeid( e ).name() ) );
		HString aetype( demangle( typeid( BE ).name() ) );
		ENSURE_EQUALS( "bad generated type", etype, aetype );
		}
	catch ( AE const& e )
		{
		cout << e.what() << endl;
		e.print_error();
		FAIL( "bad exception caught" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		e.print_error();
		FAIL( "bad exception caught" );
		}
	catch ( ... )
		{
		FAIL( "bad exception caught" );
		}
	try
		{
		C x;
		x.foo( 0 );
		FAIL( "test bug, exception not thrown" );
		}
	catch ( CE const& e )
		{
		HString etype( demangle( typeid( e ).name() ) );
		HString aetype( demangle( typeid( CE ).name() ) );
		ENSURE_EQUALS( "bad generated type", etype, aetype );
		}
	catch ( BE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( AE const& e )
		{
		cout << e.what() << endl;
		e.print_error();
		FAIL( "bad exception caught" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		FAIL( "bad exception caught" );
		}
	catch ( ... )
		{
		FAIL( "bad exception caught" );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "degenerated hier" )
	try
		{
		P x;
		x.foo( 0 );
		FAIL( "test bug, exception not thrown" );
		}
	catch ( RE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( QE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( PE const& e )
		{
		HString etype( demangle( typeid( e ).name() ) );
		HString aetype( demangle( typeid( PE ).name() ) );
		ENSURE_EQUALS( "bad generated type", etype, aetype );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		e.print_error();
		FAIL( "bad exception caught" );
		}
	catch ( ... )
		{
		FAIL( "bad exception caught" );
		}
	try
		{
		Q x;
		x.foo( 0 );
		FAIL( "test bug, exception not thrown" );
		}
	catch ( RE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( QE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( PE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( HException const& )
		{
		}
	catch ( ... )
		{
		FAIL( "bad exception caught" );
		}
	try
		{
		R x;
		x.foo( 0 );
		FAIL( "test bug, exception not thrown" );
		}
	catch ( RE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( QE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( PE const& )
		{
		FAIL( "bad exception caught" );
		}
	catch ( HException const& )
		{
		}
	catch ( ... )
		{
		FAIL( "bad exception caught" );
		}
TUT_TEARDOWN()

char const HEXCEPTIONSAFEGLOBAL_TEST_VAR[] = "ala";
HExceptionSafeGlobal<HString> globalVarHolder( HEXCEPTIONSAFEGLOBAL_TEST_VAR );
HString& globalVar = globalVarHolder.instance();

TUT_UNIT_TEST( 3, "safe initialization of global variables" )
	ENSURE_EQUALS( "global variable not initialized correctly", globalVar, HEXCEPTIONSAFEGLOBAL_TEST_VAR );
TUT_TEARDOWN()

}


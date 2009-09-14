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
	tut_yaal_hcore_hcall( void ) : _signature( SIGNATURE::INVALID )
		{
		if ( getenv( "GEN_YAAL_HCORE_HCALL" ) )
			generate_yaal_hcore_hcall_tests();
		}
	virtual ~tut_yaal_hcore_hcall( void )
		{}
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
	void generate_yaal_hcore_hcall_tests( void );
	void generate_yaal_hcore_hcall_test( int, int, int );
	};

void tut_yaal_hcore_hcall::generate_yaal_hcore_hcall_tests( void )
	{
	int testNo = 0;
	for ( int arg = 0; arg <= 4; ++ arg )
		{
		for ( int freeArg = 0; freeArg <= arg; ++ freeArg, ++ testNo )
			{
			generate_yaal_hcore_hcall_test( testNo, arg, freeArg );
			}
		}
	}

void tut_yaal_hcore_hcall::generate_yaal_hcore_hcall_test( int testNo, int arg, int freeArg )
	{
	cout << "TUT_UNIT_TEST_N( " << testNo << ", \"" << ( arg ? HString( arg ) : HString( "no" )  )
		<< " arg" << ( arg == 1 ? "" : "s" ) << ", " << ( freeArg ? HString( freeArg ) : HString( "no" ) )
		<< " free arg" << ( freeArg == 1 ? "" : "s" ) << "\" )" << endl;
	cout << "\tENSURE_EQUALS( \"function bind failed\", call( foo" << arg;
	for ( int i = 1; i <= arg; ++ i )
		{
		cout << ", " << i;
		}
	cout << " )(" << ( freeArg ? " " : "" );
	for ( int i = 1; i <= freeArg; ++ i )
		{
		if ( i > 1 )
			cout << ", ";
		cout << -i;
		}
	cout << ( freeArg ? " " : "" ) << "), \"foo" << arg << ( arg ? ": " : "" );
	for ( int i = 1; i <= arg; ++ i )
		{
		if ( i > 1 )
			cout << ", ";
		cout << "a" << i << " = " << i;
		}

	cout << "\" );" << endl;
	cout << "TUT_TEARDOWN()" << endl;
	return;
	}

HString foo0( void )
	{
	HStringStream ss;
	ss << __FUNCTION__;
	return ( ss.string() );
	}

HString foo1( int a1 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1;
	return ( ss.string() );
	}

HString foo2( int a1, int a2 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2;
	return ( ss.string() );
	}

HString foo3( int a1, int a2, int a3 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3;
	return ( ss.string() );
	}

HString foo4( int a1, int a2, int a3, int a4 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4;
	return ( ss.string() );
	}

HString foo5( int a1, int a2, int a3, int a4, int a5 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5;
	return ( ss.string() );
	}

HString foo6( int a1, int a2, int a3, int a4, int a5, int a6 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6;
	return ( ss.string() );
	}

HString foo7( int a1, int a2, int a3, int a4, int a5, int a6, int a7 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7;
	return ( ss.string() );
	}

HString foo8( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8;
	return ( ss.string() );
	}

HString foo9( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8
		<< ", a9 = " << a9;
	return ( ss.string() );
	}

HString foo10( int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10 )
	{
	HStringStream ss;
	ss << __FUNCTION__ << ": a1 = " << a1 << ", a2 = " << a2
		<< ", a3 = " << a3 << ", a4 = " << a4
		<< ", a5 = " << a5 << ", a6 = " << a6
		<< ", a7 = " << a7 << ", a8 = " << a8
		<< ", a9 = " << a9 << ", a10 = " << a10;
	return ( ss.string() );
	}

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

TUT_UNIT_TEST_N( 1, "no args, no free args" )
	ENSURE_EQUALS( "function bind failed", call( foo0 )(), "foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "1 arg, no free args" )
	ENSURE_EQUALS( "function bind failed", call( foo1, 1 )(), "foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "1 arg, 1 free arg" )
	ENSURE_EQUALS( "function bind failed", call( foo1, _1 )( -1 ), "foo1: a1 = -1" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "2 args, no free args" )
	ENSURE_EQUALS( "function bind failed", call( foo2, 1, 2 )(), "foo2: a1 = 1, a2 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "2 args, 1 free arg" )
	ENSURE_EQUALS( "function bind failed", call( foo2, _1, 2 )( -1 ), "foo2: a1 = -1, a2 = 2" );
	ENSURE_EQUALS( "function bind failed", call( foo2, 1, _1 )( -2 ), "foo2: a1 = 1, a2 = -2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "2 args, 2 free args" )
	ENSURE_EQUALS( "function bind failed", call( foo2, _1, _2 )( -1, -2 ), "foo2: a1 = -1, a2 = -2" );
	ENSURE_EQUALS( "function bind failed", call( foo2, _2, _1 )( -2, -1 ), "foo2: a1 = -1, a2 = -2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "3 args, no free args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, 1, 2, 3 )(), "foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "3 args, 1 free arg" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, 2, 3 )( -1 ), "foo3: a1 = -1, a2 = 2, a3 = 3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 1, _1, 3 )( -2 ), "foo3: a1 = 1, a2 = -2, a3 = 3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 1, 2, _1 )( -3 ), "foo3: a1 = 1, a2 = 2, a3 = -3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "3 args, 2 free args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, _2, 3 )( -1, -2 ), "foo3: a1 = -1, a2 = -2, a3 = 3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, 2, _2 )( -1, -3 ), "foo3: a1 = -1, a2 = 2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 1, _1, _2 )( -2, -3 ), "foo3: a1 = 1, a2 = -2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, _1, 3 )( -2, -1 ), "foo3: a1 = -1, a2 = -2, a3 = 3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, 2, _1 )( -3, -1 ), "foo3: a1 = -1, a2 = 2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, 1, _2, _1 )( -3, -2 ), "foo3: a1 = 1, a2 = -2, a3 = -3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "3 args, 3 free args" )
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, _2, _3 )( -1, -2, -3 ), "foo3: a1 = -1, a2 = -2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _1, _3, _2 )( -1, -3, -2 ), "foo3: a1 = -1, a2 = -2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, _1, _3 )( -2, -1, -3 ), "foo3: a1 = -1, a2 = -2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _2, _3, _1 )( -3, -1, -2 ), "foo3: a1 = -1, a2 = -2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _3, _1, _2 )( -2, -3, -1 ), "foo3: a1 = -1, a2 = -2, a3 = -3" );
	ENSURE_EQUALS( "function bind failed", call( foo3, _3, _2, _1 )( -3, -2, -1 ), "foo3: a1 = -1, a2 = -2, a3 = -3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "4 args, no free args" )
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, 2, 3, 4 )(), "foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "4 args, 1 free arg" )
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, 2, 3, 4 )( -1 ), "foo4: a1 = -1, a2 = 2, a3 = 3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, _1, 3, 4 )( -2 ), "foo4: a1 = 1, a2 = -2, a3 = 3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, 2, _1, 4 )( -3 ), "foo4: a1 = 1, a2 = 2, a3 = -3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, 2, 3, _1 )( -4 ), "foo4: a1 = 1, a2 = 2, a3 = 3, a4 = -4" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "4 args, 2 free args" )
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, _2, 3, 4 )( -1, -2 ), "foo4: a1 = -1, a2 = -2, a3 = 3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, 2, _2, 4 )( -1, -3 ), "foo4: a1 = -1, a2 = 2, a3 = -3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, 2, 3, _2 )( -1, -4 ), "foo4: a1 = -1, a2 = 2, a3 = 3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, _1, _2, 4 )( -2, -3 ), "foo4: a1 = 1, a2 = -2, a3 = -3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, _1, 3, _2 )( -2, -4 ), "foo4: a1 = 1, a2 = -2, a3 = 3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, 2, _1, _2 )( -3, -4 ), "foo4: a1 = 1, a2 = 2, a3 = -3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _2, _1, 3, 4 )( -2, -1 ), "foo4: a1 = -1, a2 = -2, a3 = 3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _2, 2, _1, 4 )( -3, -1 ), "foo4: a1 = -1, a2 = 2, a3 = -3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _2, 2, 3, _1 )( -4, -1 ), "foo4: a1 = -1, a2 = 2, a3 = 3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, _2, _1, 4 )( -3, -2 ), "foo4: a1 = 1, a2 = -2, a3 = -3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, _2, 3, _1 )( -4, -2 ), "foo4: a1 = 1, a2 = -2, a3 = 3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, 2, _2, _1 )( -4, -3 ), "foo4: a1 = 1, a2 = 2, a3 = -3, a4 = -4" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "4 args, 3 free args" )
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, _2, _3, 4 )( -1, -2, -3 ), "foo4: a1 = -1, a2 = -2, a3 = -3, a4 = 4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, _2, 3, _3 )( -1, -2, -4 ), "foo4: a1 = -1, a2 = -2, a3 = 3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, _1, 2, _2, _3 )( -1, -3, -4 ), "foo4: a1 = -1, a2 = 2, a3 = -3, a4 = -4" );
	ENSURE_EQUALS( "function bind failed", call( foo4, 1, _1, _2, _3 )( -2, -3, -4 ), "foo4: a1 = 1, a2 = -2, a3 = -3, a4 = -4" );
	/* TODO: add rest of the cases here. */
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 31, "a member (no args)" )
	reset();
	static int const post[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::fv )> > call_two_t;
	call_two_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::fv )>( *this, &tut_yaal_hcore_hcall::fv ) );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::FV );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 32, "a member (one int arg)" )
	reset();
	static int const post[10] = { 0, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f1i )>, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f1i )>( *this, &tut_yaal_hcore_hcall::f1i ), 0 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F1I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 33, "a member (two int arg)" )
	reset();
	static int const post[10] = { 0, 1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f2i )>, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f2i )>( *this, &tut_yaal_hcore_hcall::f2i ), 0, 1 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F2I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 34, "a member (3 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, -1, -1, -1, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f3i )>, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f3i )>( *this, &tut_yaal_hcore_hcall::f3i ), 0, 1, 2 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F3I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 35, "a member (4 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, -1, -1, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f4i )>, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f4i )>( *this, &tut_yaal_hcore_hcall::f4i ), 0, 1, 2, 3 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F4I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 36, "a member (5 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, -1, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f5i )>, int, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f5i )>( *this, &tut_yaal_hcore_hcall::f5i ), 0, 1, 2, 3, 4 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F5I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 37, "a member (6 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, -1, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f6i )>, int, int, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f6i )>( *this, &tut_yaal_hcore_hcall::f6i ), 0, 1, 2, 3, 4, 5 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F6I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 38, "a member (7 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, -1, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f7i )>, int, int, int, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f7i )>( *this, &tut_yaal_hcore_hcall::f7i ), 0, 1, 2, 3, 4, 5, 6 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F7I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 39, "a member (8 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, -1, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f8i )>, int, int, int, int, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f8i )>( *this, &tut_yaal_hcore_hcall::f8i ), 0, 1, 2, 3, 4, 5, 6, 7 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F8I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 40, "a member (9 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, -1 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f9i )>, int, int, int, int, int, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f9i )>( *this, &tut_yaal_hcore_hcall::f9i ), 0, 1, 2, 3, 4, 5, 6, 7, 8 );
	cout << sizeof ( c ) << endl;
	c.invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F9I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 41, "a member (10 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	typedef HBoundCall<HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f10i )>, int, int, int, int, int, int, int, int, int, int> call_t;
	call_t c( HFunctor<tut_yaal_hcore_hcall&, __decltype ( &tut_yaal_hcore_hcall::f10i )>( *this, &tut_yaal_hcore_hcall::f10i ), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
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
	int calculate( void )
		{ return ( _arg ); }
	int calculate( int arg_ )
		{ return ( _arg + arg_ ); }
	int calculate_const( int arg_ ) const
		{ return ( _arg + arg_ ); }
	int calculate_volatile( int arg_ ) volatile
		{ return ( _arg + arg_ ); }
	int calculate_const_volatile( int arg_ ) const volatile
		{ return ( _arg + arg_ ); }
	int sum( int a1, int a2, int a3, int a4, int a5, int a6 )
		{
		return ( _arg + a1 + a2 + a3 + a4 + a5 + a6 );
		}
	};

template<typename a0_t, typename a1_t, typename a2_t, typename a3_t,
	typename a4_t, typename a5_t>
int cf( a0_t = trait::no_type(), a1_t = trait::no_type(),
		a2_t = trait::no_type(), a3_t = trait::no_type(),
		a4_t = trait::no_type(), a5_t = trait::no_type() )
	{
	return ( call_calculator<void(*)(void), int, a0_t, a1_t, a2_t, a3_t, a4_t, a5_t>::free_standing_args::value );
	}

void show_rectangle( int a, int b )
	{
	cout << "a: " << a << ", b: " << b << endl;
	}

TUT_UNIT_TEST_N( 42, "use call as a functor in an algorithm" )
	HArray<int> tab( 10 );
	generate_n( tab.begin(), tab.size(), inc( 1 ) );
	for_each( tab.begin(), tab.end(), call( show_rectangle, _1, 2 ) );
	for_each( tab.begin(), tab.end(), call( show_rectangle, 2, _1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 43, "4 free standing args" )
	Sumator s( 1 );
	call( static_cast<int (Sumator::*)( void )>( &Sumator::calculate ), &s );
#if 0
	call( 2, _1, 4, 8, _2, 16 )( 100, 2000 );
#endif
	cout << "free arg count: " << cf( 2, _1, 4, 8, _2, 16 ) << endl;
	cout << call( foo1, _1 )( 2 ) << endl;
	cout << call( foo2, _1, 2 )( 3 ) << endl;
	cout << call( foo2, 2, _1 )( 3 ) << endl;
	cout << call( foo2, _1, _2 )( 1, 2 ) << endl;
	cout << call( foo2, _2, _1 )( 1, 2 ) << endl;
	cout << call( foo3, 0, 1, 2 )() << endl;
	cout << call( foo3, _1, 1, 2 )( 3 ) << endl;
	cout << call( foo3, 0, _1, 2 )( 4 ) << endl;
	cout << call( foo3, 0, 1, _1 )( 5 ) << endl;
	cout << call( foo3, _1, _2, 2 )( 3, 4 ) << endl;
	cout << call( foo3, _2, _1, 2 )( 3, 4 ) << endl;
	cout << call( foo3, 0, _1, _2 )( 4, 5 ) << endl;
	cout << call( foo3, _2, 1, _1 )( 5, 6 ) << endl;
	cout << call( foo10, 0, 1, 2, _3, 4, _2, 6, _1, 8, _4 )( -1, -2, -3, -4 ) << endl;
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hboundcall.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hboundcall
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
	tut_yaal_hcore_hboundcall( void ) : _signature( SIGNATURE::INVALID )
		{}
	virtual ~tut_yaal_hcore_hboundcall( void )
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
	};

int const tut_yaal_hcore_hboundcall::SIGNATURE::INVALID = -1;
int const tut_yaal_hcore_hboundcall::SIGNATURE::FV = 0;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F1I = 1;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F2I = 2;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F3I = 3;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F4I = 4;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F5I = 5;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F6I = 6;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F7I = 7;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F8I = 8;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F9I = 9;
int const tut_yaal_hcore_hboundcall::SIGNATURE::F10I = 10;

TUT_TEST_GROUP_N( tut_yaal_hcore_hboundcall, "yaal::hcore::HBoundCall" );

TUT_UNIT_TEST_N( 1, "a member (no args)" )
	reset();
	static int const post[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::fv, this ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::FV );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "a member (one int arg)" )
	reset();
	static int const post[10] = { 0, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f1i, this, 0 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F1I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "a member (two int arg)" )
	reset();
	static int const post[10] = { 0, 1, -1, -1, -1, -1, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f2i, this, 0, 1 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F2I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "a member (3 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, -1, -1, -1, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f3i, this, 0, 1, 2 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F3I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "a member (4 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, -1, -1, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f4i, this, 0, 1, 2, 3 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F4I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "a member (5 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, -1, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f5i, this, 0, 1, 2, 3, 4 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F5I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "a member (6 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, -1, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f6i, this, 0, 1, 2, 3, 4, 5 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F6I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "a member (7 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, -1, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f7i, this, 0, 1, 2, 3, 4, 5, 6 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F7I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "a member (8 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, -1, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f8i, this, 0, 1, 2, 3, 4, 5, 6, 7 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F8I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "a member (9 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, -1 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f9i, this, 0, 1, 2, 3, 4, 5, 6, 7, 8 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F9I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "a member (10 int arg)" )
	reset();
	static int const post[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	HBoundCallInterface::ptr_t c( bound_call( &tut_yaal_hcore_hboundcall::f10i, this, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) );
	c->invoke();
	ENSURE_EQUALS( "bad method called", _signature, SIGNATURE::F10I );
	for ( int i = 0; i < 10; ++ i )
		ENSURE_EQUALS( "args persistance failed", _int[i], post[i] );
TUT_TEARDOWN()

}


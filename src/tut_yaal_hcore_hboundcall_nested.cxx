/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hboundcall_nested.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/hcore/hboundcall.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hcore_hcall.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hboundcall_nested );
TUT_TEST_GROUP( tut_yaal_hcore_hboundcall_nested, "yaal::hcore::HBoundCall,nested" );

namespace {
	char const err[] = "function bind failed";
}

TUT_UNIT_TEST( 1, "nested bound call (x, y) -> (y) -> ()" )
	HBoundCall<HString ( int )> f( call( &foo2, _1, 2 ) );
	char const expected[] = "foo2: a1 = 1, a2 = 2";
	ENSURE_EQUALS( err, f( 1 ), expected );
	ENSURE_EQUALS( err, call( f, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "nested bound call ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int )> f2( call( &foo3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo3: a1 = 1, a2 = 2, a3 = 3";
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "nested bound call ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int )> f3( call( &foo4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4";
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "nested bound call ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int, int )> f4( call( &foo5, _1, _2, _3, _4, 5 ) );
	HBoundCall<HString ( int, int, int )> f3( call( f4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo5: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5";
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "nested bound call ( u, v, w, x, y, z ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int, int, int )> f5( call( &foo6, _1, _2, _3, _4, _5, 6 ) );
	HBoundCall<HString ( int, int, int, int )> f4( call( f5, _1, _2, _3, _4, 5 ) );
	HBoundCall<HString ( int, int, int )> f3( call( f4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo6: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6";
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "nested bound call ( t, u, v, w, x, y, z ) -> ( u, v, w, x, y, z ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int, int, int, int )> f6( call( &foo7, _1, _2, _3, _4, _5, _6, 7 ) );
	HBoundCall<HString ( int, int, int, int, int )> f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	HBoundCall<HString ( int, int, int, int )> f4( call( f5, _1, _2, _3, _4, 5 ) );
	HBoundCall<HString ( int, int, int )> f3( call( f4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo7: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7";
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "nested bound call ( 8 args ) -> ( t, u, v, w, x, y, z ) -> ( u, v, w, x, y, z ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int, int, int, int, int )> f7( call( &foo8, _1, _2, _3, _4, _5, _6, _7, 8 ) );
	HBoundCall<HString ( int, int, int, int, int, int )> f6( call( f7, _1, _2, _3, _4, _5, _6, 7 ) );
	HBoundCall<HString ( int, int, int, int, int )> f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	HBoundCall<HString ( int, int, int, int )> f4( call( f5, _1, _2, _3, _4, 5 ) );
	HBoundCall<HString ( int, int, int )> f3( call( f4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo8: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8";
	ENSURE_EQUALS( err, f7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "nested bound call ( 9 args ) -> ( 8 args ) -> ( 7 args ) -> ( 6 args ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int, int, int, int, int, int )> f8( call( &foo9, _1, _2, _3, _4, _5, _6, _7, _8, 9 ) );
	HBoundCall<HString ( int, int, int, int, int, int, int )> f7( call( f8, _1, _2, _3, _4, _5, _6, _7, 8 ) );
	HBoundCall<HString ( int, int, int, int, int, int )> f6( call( f7, _1, _2, _3, _4, _5, _6, 7 ) );
	HBoundCall<HString ( int, int, int, int, int )> f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	HBoundCall<HString ( int, int, int, int )> f4( call( f5, _1, _2, _3, _4, 5 ) );
	HBoundCall<HString ( int, int, int )> f3( call( f4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo9: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9";
	ENSURE_EQUALS( err, f8( 1, 2, 3, 4, 5, 6, 7, 8 ), expected );
	ENSURE_EQUALS( err, f7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "nested bound call ( 10 args ) -> ( 9 args ) -> ( 8 args ) -> ( 7 args ) -> ( 6 args ) -> ( 5 args ) -> ( 4 args ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	HBoundCall<HString ( int, int, int, int, int, int, int, int, int )> f9( call( &foo10, _1, _2, _3, _4, _5, _6, _7, _8, _9, 10 ) );
	HBoundCall<HString ( int, int, int, int, int, int, int, int )> f8( call( f9, _1, _2, _3, _4, _5, _6, _7, _8, 9 ) );
	HBoundCall<HString ( int, int, int, int, int, int, int )> f7( call( f8, _1, _2, _3, _4, _5, _6, _7, 8 ) );
	HBoundCall<HString ( int, int, int, int, int, int )> f6( call( f7, _1, _2, _3, _4, _5, _6, 7 ) );
	HBoundCall<HString ( int, int, int, int, int )> f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	HBoundCall<HString ( int, int, int, int )> f4( call( f5, _1, _2, _3, _4, 5 ) );
	HBoundCall<HString ( int, int, int )> f3( call( f4, _1, _2, _3, 4 ) );
	HBoundCall<HString ( int, int )> f2( call( f3, _1, _2, 3 ) );
	HBoundCall<HString ( int )> f1( call( f2, _1, 2 ) );
	char const expected[] = "foo10: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10";
	ENSURE_EQUALS( err, f9( 1, 2, 3, 4, 5, 6, 7, 8, 9 ), expected );
	ENSURE_EQUALS( err, f8( 1, 2, 3, 4, 5, 6, 7, 8 ), expected );
	ENSURE_EQUALS( err, f7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

}


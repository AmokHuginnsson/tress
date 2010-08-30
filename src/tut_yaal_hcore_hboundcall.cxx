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
#include "tut_yaal_hcore_hcall.hxx"

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
	YaalHCoreHCallClass _callable;
	tut_yaal_hcore_hboundcall( void ) : _callable()
		{}
	virtual ~tut_yaal_hcore_hboundcall( void )
		{}
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hboundcall, "yaal::hcore::HBoundCall" );

TUT_UNIT_TEST_N( 1, "a member (no args)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo0, &_callable ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo0" );
	HBoundCall<HString ( void )> f( call( &tut::foo0 ) );
	ENSURE_EQUALS( "bad function called", f(), "foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "a member (one int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo1, &_callable, 1 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo1: a1 = 1" );
	HBoundCall<HString ( void )> f( call( &tut::foo1, 1 ) );
	ENSURE_EQUALS( "bad function called", f(), "foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "a member (two int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo2, &_callable, 1, 2 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo2: a1 = 1, a2 = 2" );
	HBoundCall<HString ( void )> f( call( &tut::foo2, 1, 2 ) );
	ENSURE_EQUALS( "bad function called", f(), "foo2: a1 = 1, a2 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "a member (3 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo3, &_callable, 1, 2, 3 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = 3" );
	HBoundCall<HString ( void )> f( call( &tut::foo3, 1, 2, 3 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "a member (4 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo4, &_callable, 1, 2, 3, 4 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
	HBoundCall<HString ( void )> f( call( &tut::foo4, 1, 2, 3, 4 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "a member (5 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo5, &_callable, 1, 2, 3, 4, 5 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo5: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5" );
	HBoundCall<HString ( void )> f( call( &tut::foo5, 1, 2, 3, 4, 5 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo5: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "a member (6 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo6, &_callable, 1, 2, 3, 4, 5, 6 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo6: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6" );
	HBoundCall<HString ( void )> f( call( &tut::foo6, 1, 2, 3, 4, 5, 6 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo6: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "a member (7 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo7, &_callable, 1, 2, 3, 4, 5, 6, 7 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo7: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7" );
	HBoundCall<HString ( void )> f( call( &tut::foo7, 1, 2, 3, 4, 5, 6, 7 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo7: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "a member (8 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo8, &_callable, 1, 2, 3, 4, 5, 6, 7, 8 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo8: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8" );
	HBoundCall<HString ( void )> f( call( &tut::foo8, 1, 2, 3, 4, 5, 6, 7, 8 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo8: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "a member (9 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo9, &_callable, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo9: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9" );
	HBoundCall<HString ( void )> f( call( &tut::foo9, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo9: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "a member (10 int arg)" )
	HBoundCall<HString ( void )> c( call( &YaalHCoreHCallClass::foo10, &_callable, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	ENSURE_EQUALS( "bad method called", c(), "YaalHCoreHCallClass: foo10: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10" );
	HBoundCall<HString ( void )> f( call( &tut::foo10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	ENSURE_EQUALS( "bad method called", f(), "foo10: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10" );
TUT_TEARDOWN()

class Boom
	{
	int _val;
public:
	Boom( int val_ ) : _val( val_ ) {}
	int foo( double val_ )
		{ return ( _val * static_cast<int>( val_ ) ); }
	int bar( double val_, int i )
		{ return ( _val * static_cast<int>( val_ ) + i ); }
	};

TUT_UNIT_TEST_N( 12, "free standing arg in method" )
	Boom b0( 7 );
	Boom b1( 4 );
	HBoundCall<int ( double )> c0( call( &Boom::foo, b0, _1 ) );
	ENSURE_EQUALS( "bad call: call( &Boom::foo, b0, _1 )( 2 )", c0( 2 ), 7 * 2 );
	HBoundCall<int ( int )> c1( call( &Boom::bar, b0, 4., _1 ) );
	ENSURE_EQUALS( "bad call: call( &Boom::bar, b0, 4., _1 )( 3 )", c1( 3 ), 7 * 4 + 3 );
	HBoundCall<int ( double )> c2( call( &Boom::bar, b0, _1, static_cast<int>( 3. ) ) );
	ENSURE_EQUALS( "bad call: call( &Boom::bar, b0, _1, static_cast<int>( 3. ) )( 5 )", c2( 5 ), 7 * 5 + 3 );
	HBoundCall<int ( Boom& )> c3( call( &Boom::bar, _1, 2, static_cast<int>( 3. ) ) );
	ENSURE_EQUALS( "bad call: call( &Boom::bar, _1, 2, static_cast<int>( 3. )( Boom( 7 ) )", c3( b0 ), 7 * 2 + 3 );
	ENSURE_EQUALS( "bad call: call( &Boom::bar, _1, 2, static_cast<int>( 3. )( Boom( 4 ) )", c3( b1 ), 4 * 2 + 3 );
TUT_TEARDOWN()

}


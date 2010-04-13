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
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo0, _callable ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo0" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo0 ) );
	ENSURE_EQUALS( "bad function called", f->invoke(), "foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "a member (one int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo1, _callable, 1 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo1: a1 = 1" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo1, 1 ) );
	ENSURE_EQUALS( "bad function called", f->invoke(), "foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "a member (two int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo2, _callable, 1, 2 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo2: a1 = 1, a2 = 2" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo2, 1, 2 ) );
	ENSURE_EQUALS( "bad function called", f->invoke(), "foo2: a1 = 1, a2 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "a member (3 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo3, _callable, 1, 2, 3 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = 3" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo3, 1, 2, 3 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "a member (4 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo4, _callable, 1, 2, 3, 4 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo4, 1, 2, 3, 4 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "a member (5 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo5, _callable, 1, 2, 3, 4, 5 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo5: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo5, 1, 2, 3, 4, 5 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo5: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "a member (6 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo6, _callable, 1, 2, 3, 4, 5, 6 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo6: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo6, 1, 2, 3, 4, 5, 6 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo6: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "a member (7 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo7, _callable, 1, 2, 3, 4, 5, 6, 7 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo7: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo7, 1, 2, 3, 4, 5, 6, 7 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo7: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "a member (8 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo8, _callable, 1, 2, 3, 4, 5, 6, 7, 8 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo8: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo8, 1, 2, 3, 4, 5, 6, 7, 8 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo8: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "a member (9 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo9, _callable, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo9: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo9, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo9: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "a member (10 int arg)" )
	HBoundCallInterface<0, HString>::ptr_t c( bound_call( &YaalHCoreHCallClass::foo10, _callable, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	ENSURE_EQUALS( "bad method called", c->invoke(), "YaalHCoreHCallClass: foo10: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10" );
	HBoundCallInterface<0, HString>::ptr_t f( bound_call( &tut::foo10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	ENSURE_EQUALS( "bad method called", f->invoke(), "foo10: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10" );
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
	Boom b( 7 );
	HBoundCallInterface<1, int, double>::ptr_t c( bound_call( &Boom::foo, b, _1 ) );
	cout << c->invoke( 3 ) << endl;
//	HBoundCallInterface<1, int, int>::ptr_t c2( bound_call( &Boom::bar, b, 4., _1 ) );
//	bound_call( &Boom::bar, b, 4., _1 );
//	cout << c2->invoke( 3 ) << endl;
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall_this.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hcall.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hcore_hcall.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hcall_this : public simple_mock<tut_yaal_hcore_hcall_this> {
	typedef simple_mock<tut_yaal_hcore_hcall_this> base_type;
	YaalHCoreHCallClass _callable;
	tut_yaal_hcore_hcall_this( void )
		: base_type(), _callable()
		{}
	virtual ~tut_yaal_hcore_hcall_this( void ) {}
};

TUT_TEST_GROUP( tut_yaal_hcore_hcall_this, "yaal::hcore::HCall,this" );

TUT_UNIT_TEST( 1, "no-op bind of this" )
	ENSURE_EQUALS( "bad method called", call( &YaalHCoreHCallClass::foo0, &_callable )(), "YaalHCoreHCallClass: foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "this and no args" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo0, _1 )( _callable ), "YaalHCoreHCallClass: foo0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "this and 1 arg, one free" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo1, _1, 1 )( _callable ), "YaalHCoreHCallClass: foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "this and 2 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo1, _1, _2 )( _callable, 1 ), "YaalHCoreHCallClass: foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "this and 2 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo1, _2, _1 )( 1, _callable ), "YaalHCoreHCallClass: foo1: a1 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "this and 3 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo2, _1, _2, _3 )( _callable, 1, 2 ), "YaalHCoreHCallClass: foo2: a1 = 1, a2 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "this and 3 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo2, _2, _1, _3 )( 1, _callable, 2 ), "YaalHCoreHCallClass: foo2: a1 = 1, a2 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "this and 3 free args, this is third" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo2, _3, _1, _2 )( 1, 2, _callable ), "YaalHCoreHCallClass: foo2: a1 = 1, a2 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "this and 4 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _1, _2, _3, _4 )( _callable, 1, 2, 3 ), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "this and 4 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _2, _1, _3, _4 )( 1, _callable, 2, 3 ), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "this and 4 free args, this is third" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _3, _1, _2, _4 )( 1, 2, _callable, 3 ), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "this and 4 free args, this is fourth" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _4, _1, _2, _3 )( 1, 2, 3, _callable ), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "this and 5 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _1, _2, _3, _4, _5 )( _callable, 1, 2, 3, 4 ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "this and 5 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _2, _1, _3, _4, _5 )( 1, _callable, 2, 3, 4 ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "this and 5 free args, this is third" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _3, _1, _2, _4, _5 )( 1, 2, _callable, 3, 4 ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "this and 5 free args, this is fourth" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _4, _1, _2, _3, _5 )( 1, 2, 3, _callable, 4 ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "this and 5 free args, this is fourth" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _5, _1, _2, _3, _4 )( 1, 2, 3, 4, _callable ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "this and 2 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo2, _1, -1, _2 )( _callable, 1 ), "YaalHCoreHCallClass: foo2: a1 = -1, a2 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 19, "this and 2 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo2, _2, _1, -1 )( 1, _callable ), "YaalHCoreHCallClass: foo2: a1 = 1, a2 = -1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "this and 2 free args, this is third" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo2, _1, -1, -2 )( _callable ), "YaalHCoreHCallClass: foo2: a1 = -1, a2 = -2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "this and 3 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _1, -1, _2, _3 )( _callable, 1, 2 ), "YaalHCoreHCallClass: foo3: a1 = -1, a2 = 1, a3 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "this and 3 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _2, _1, -1, _3 )( 1, _callable, 2 ), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = -1, a3 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "this and 3 free args, this is third" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _3, _1, _2, -1 )( 1, 2, _callable ), "YaalHCoreHCallClass: foo3: a1 = 1, a2 = 2, a3 = -1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "this and 3 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _1, -1, -2, _2 )( _callable, 1 ), "YaalHCoreHCallClass: foo3: a1 = -1, a2 = -2, a3 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 25, "this and 3 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo3, _2, -1, -2, _1 )( 1, _callable ), "YaalHCoreHCallClass: foo3: a1 = -1, a2 = -2, a3 = 1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "this and 4 free args, this is first" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _1, -1, _2, _3, _4 )( _callable, 1, 2, 3 ), "YaalHCoreHCallClass: foo4: a1 = -1, a2 = 1, a3 = 2, a4 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "this and 4 free args, this is second" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _2, _1, -1, _3, _4 )( 1, _callable, 2, 3 ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = -1, a3 = 2, a4 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "this and 4 free args, this is third" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _3, _1, _2, -1, _4 )( 1, 2, _callable, 3 ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = -1, a4 = 3" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "this and 4 free args, this is fourth" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _4, _1, _2, _3, -1 )( 1, 2, 3, _callable ), "YaalHCoreHCallClass: foo4: a1 = 1, a2 = 2, a3 = 3, a4 = -1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "this and 4 free args, this is fourth" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _1, -1, -2, _2, _3 )(  _callable, 1, 2 ), "YaalHCoreHCallClass: foo4: a1 = -1, a2 = -2, a3 = 1, a4 = 2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 31, "this and 4 free args, this is fourth" )
	ENSURE_EQUALS( "bind for free this failed", call( &YaalHCoreHCallClass::foo4, _2, -1, -2, _1, _3 )(  1, _callable, 2 ), "YaalHCoreHCallClass: foo4: a1 = -1, a2 = -2, a3 = 1, a4 = 2" );
TUT_TEARDOWN()

}


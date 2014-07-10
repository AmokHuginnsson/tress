/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_foreach.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/foreach.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/tools/assign.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_foreach );
TUT_TEST_GROUP( tut_yaal_foreach, "yaal::foreach" );

TUT_UNIT_TEST( 1, "on smart non-const container" )
	int_array_t arr( array( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	YAAL_FOREACH( int& a, arr ) {
		a *= a;
	}
	ENSURE_EQUALS( "forech failed", accumulate( arr.begin(), arr.end(), 0 ), 100 + 81 + 64 + 49 + 36 + 25 + 16 + 9 + 4 + 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "on smart const container" )
	int_array_t const arr( array( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	int sum( 0 );
	YAAL_FOREACH( int const& a, arr ) {
		sum += a;
	}
	ENSURE_EQUALS( "forech failed", sum, accumulate( arr.begin(), arr.end(), 0 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "on non-const C-array" )
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	YAAL_FOREACH( int& a, arr ) {
		a *= a;
	}
	ENSURE_EQUALS( "forech failed", accumulate( begin( arr ), end( arr ), 0 ), 100 + 81 + 64 + 49 + 36 + 25 + 16 + 9 + 4 + 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "on const C-array" )
	int const arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum( 0 );
	YAAL_FOREACH( int const& a, arr ) {
		sum += a;
	}
	ENSURE_EQUALS( "forech failed", sum, accumulate( begin( arr ), end( arr ), 0 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "break in foreach" )
	int_array_t arr( array( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
	YAAL_FOREACH( int& a, arr ) {
		if ( a >= 5 ) {
			break;
		}
		a *= a;
	}
	ENSURE_EQUALS( "break in forech failed", accumulate( arr.begin(), arr.end(), 0 ), 10 + 9 + 8 + 7 + 6 + 5 + 16 + 9 + 4 + 1 );
TUT_TEARDOWN()

namespace {

struct R {
	int _ctr;
	int _stop;
	struct IT {
		int& _ctr;
		int _stop;
		IT( int& ctr_, int stop_ )
			: _ctr( ctr_ ), _stop( stop_ ) {
		}
		bool operator != ( IT const& ) {
			return ( _ctr != _stop );
		}
		IT& operator ++ ( void ) {
			++ _ctr;
			return ( *this );
		}
		int operator*() {
			return ( 0 );
		}
	};
	R( int stop_ )
		: _ctr( 0 ), _stop( stop_ ) {
	}
	typedef R::IT iterator;
	typedef int value_type;
};

R::IT begin( R& r_ ) {
	return ( R::IT( r_._ctr, r_._stop ) );
}

R::IT end( R& r_ ) {
	return ( R::IT( r_._ctr, r_._stop ) );
}

}

TUT_UNIT_TEST( 6, "break in foreach" )
	static int const C( 111 );
	R r( C );
	int nop( 0 );
	YAAL_FOREACH( int const& a, r ) {
		nop += a;
	}
	ENSURE_EQUALS( "test framework failed", r._ctr, C );
	nop = 0;
	static int const S( 5 );
	r._ctr = 0;
	YAAL_FOREACH( int const& a, r ) {
		++ nop;
		if ( nop >= S ) {
			break;
		}
		nop += a;
	}
	ENSURE_EQUALS( "foreach break body failed", nop, S );
	ENSURE_EQUALS( "foreach begin iterator failed", r._ctr, S );
TUT_TEARDOWN()

}


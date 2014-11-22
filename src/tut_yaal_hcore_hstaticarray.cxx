/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hstaticarray.cxx - this file is integral part of `tress' project.

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

#include <vector>

#include <TUT/tut.hpp>

#include <yaal/hcore/hstaticarray.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hstaticarray : public simple_mock<tut_yaal_hcore_hstaticarray> {
	typedef std::vector<int> proto_t;
	~tut_yaal_hcore_hstaticarray( void ) {}
	void test_erase( int, int );
};

TUT_TEST_GROUP( tut_yaal_hcore_hstaticarray, "yaal::hcore::HStaticArray" );

TUT_UNIT_TEST( "Constructor and get_size()." )
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	HStaticArray<item_t, SIZE_FOR_ONE> one;
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	HStaticArray<item_t, SIZE_FOR_TWO> two;
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE + SIZE_FOR_TWO );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", two.get_size(), SIZE_FOR_TWO );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with filling." )
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	HStaticArray<item_t, SIZE_FOR_ARRAY> array( FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "array element not filled with default value", array[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with range initialization." )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 ); {
		HStaticArray<item_t, countof ( a )> array( begin( a ), end( a ) );
		ENSURE( "range initialization failed", safe_equal( array.begin(), array.end(), begin( a ), end( a ) ) );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Copy constructor." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	HStaticArray<item_t, SIZE> array;
	for ( int i = 0; i < SIZE; ++ i )
		array [ i ] = i;
	HStaticArray<item_t, SIZE> copy( array );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Operator [ ]." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	HStaticArray<item_t, SIZE> array;
	ENSURE_THROW( "access beyond size succed", array[ SIZE ] = 0, HException );
	ENSURE_THROW( "access with negative index succed", array[ - SIZE - 1 ] = 0, HException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_empty()" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	HStaticArray<item_t, 0> empty;
	ENSURE_EQUALS( "test for array emptiness failed", empty.is_empty(), true );
	HStaticArray<item_t, SIZE> normal;
	ENSURE_EQUALS( "test for array fullness failed", normal.is_empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign operator (=)" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	HStaticArray<item_t, countof ( a0 )> array( begin( a0 ), end( a0 ) );
	HStaticArray<item_t, countof ( a0 )> other( -1 );
	other = array;
	ENSURE_EQUALS( "assgin failed", array, other );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { 37, 12, 234, 29, 6, 5, 326, 149, 654, 12, 10, 306 };
	item_t::set_start_id( 0 );
	HStaticArray<item_t, countof ( a0 )> sa0( a0, countof ( a0 ) );
	HStaticArray<item_t, countof ( a0 )> t( a0, countof ( a0 ) );
	ENSURE_EQUALS( "init failed", sa0, t );
	HStaticArray<item_t, countof ( a0 )> sa1( a1, countof ( a1 ) );
	t.assign( a1, countof ( a1 ) );
	ENSURE_EQUALS( "init failed", sa1, t );
	sa0.swap( sa1 );
	ENSURE_EQUALS( "swap failed", sa0, t );
	t.assign( a0, countof ( a0 ) );
	ENSURE_EQUALS( "swap failed", sa1, t );
TUT_TEARDOWN()

}


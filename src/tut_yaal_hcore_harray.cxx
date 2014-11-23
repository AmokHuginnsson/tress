/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_harray.cxx - this file is integral part of `tress' project.

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

#include "tut_helpers.hxx"
#include <TUT/tut.hpp>

#include <yaal/hcore/harray.hxx>
M_VCSID( "$Id: " __ID__ " $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_harray : public simple_mock<tut_yaal_hcore_harray> {
	typedef std::vector<int> proto_t;
	~tut_yaal_hcore_harray( void ) {}
	void test_erase( int, int );
};

TUT_TEST_GROUP( tut_yaal_hcore_harray, "yaal::hcore::HArray" );

TUT_UNIT_TEST( "Constructor." )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	ENSURE_THROW( "array with negative size created", array_t array( BAD_SIZE ), HException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor and get_size()." )
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	array_t one( SIZE_FOR_ONE );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	array_t two( SIZE_FOR_TWO );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE + SIZE_FOR_TWO );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", two.get_size(), SIZE_FOR_TWO );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with filling." )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	ENSURE_THROW( "array with negative size created", array_t badArray( BAD_SIZE, FILLER_FOR_ARRAY ), HException );
	array_t array( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "array element not filled with default value", array[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with range initialization." )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 ); {
		array_t array( begin( a ), end( a ) );
		ENSURE( "range initialization failed", safe_equal( array.begin(), array.end(), begin( a ), end( a ) ) );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with curly braces initializer" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	array_t array( { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 } );
	ENSURE( "range initialization failed", safe_equal( array.begin(), array.end(), begin( a ), end( a ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Copy constructor." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	array_t array( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		array [ i ] = i;
	array_t copy( array );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Operator [ ]." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	array_t array ( SIZE );
	ENSURE_THROW( "access beyond size succed", array [ SIZE ] = 0, HException );
	ENSURE_THROW( "access with negative index succed", array[ - SIZE - 1 ] = 0, HException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Operator bool." )
	item_t::set_start_id( 0 );
	int const EMPTY = 0;
	int const SIZE = 7;
	array_t empty( EMPTY );
	ENSURE_EQUALS( "test for array emptiness failed", ! empty, true );
	array_t normal( SIZE );
	ENSURE_EQUALS( "test for array fullness failed", ! normal, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_back" )
	proto_t proto; {
		array_t array;
		for ( int long i( 0 ); i < 2048; ++ i ) {
			proto.push_back( static_cast<int>( i ) );
			array.push_back( static_cast<int>( i ) );
			ENSURE_EQUALS( "push_back failed", array, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_back( && )" )
	item_t::reset();
	int const C( 2048 );
	proto_t proto; {
		array_t array;
		array.reserve( C );
		for ( int long i( 0 ); i < C; ++ i ) {
			item_t a( static_cast<int>( i ) );
			proto.push_back( static_cast<int>( i ) );
			array.push_back( yaal::move( a ) );
			ENSURE_EQUALS( "push_back failed", array, proto );
		}
	}
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "invalid pass", item_t::get_move_count(), C );
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "emplace_back" )
	item_t::reset();
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
	int const C( 2048 );
	proto_t proto; {
		array_t array;
		for ( int long i( 0 ); i < C; ++ i ) {
			proto.emplace_back( static_cast<int>( i ) );
			array.emplace_back( static_cast<int>( i ) );
			ENSURE_EQUALS( "emplace_back failed", array, proto );
		}
	}
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	item_t::reset();
	/* move test */ {
		array_t array;
		array.reserve( C );
		proto.clear();
		for ( int long i( 0 ); i < C; ++ i ) {
			proto.emplace_back( static_cast<int>( i ) );
			array.emplace_back( static_cast<int>( i ) );
			ENSURE_EQUALS( "emplace_back failed", array, proto );
		}
	}
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy constructor (of empty)" )
	array_t a1;
	ENSURE( "construction of empty array", a1.is_empty() );
	array_t a2( a1 );
	ENSURE( "construction of empty array", a2.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "resize vs capacity" )
	array_t a;
	a.resize( 1 );
	ENSURE_EQUALS( "resize( 1 ) failed (resize)", a.size(), 1 );
	ENSURE_EQUALS( "resize( 1 ) failed (capacity)", a.capacity(), 1 );
	a.resize( 5 );
	ENSURE_EQUALS( "resize( 5 ) failed (resize)", a.size(), 5 );
	ENSURE_EQUALS( "resize( 5 ) failed (capacity)", a.capacity(), 5 );
	a.resize( 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (resize)", a.size(), 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (capacity)", a.capacity(), 13 );

	array_t large;
	large.resize( 7 );
	ENSURE_EQUALS( "resize( 7 ) failed (resize)", large.size(), 7 );
	ENSURE_EQUALS( "resize( 7 ) failed (capacity)", large.capacity(), 7 );
	large.resize( 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (resize)", large.size(), 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (capacity)", large.capacity(), 14 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert( pos, value )" )
	item_t::reset();
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	proto_t proto( begin( a ), end( a ) );
	array_t array( begin( a ), end( a ) );
	ENSURE_EQUALS( "insertion failed", array, proto );
	item_t a1( -7 );
	array.insert( array.begin(), a1 );
	proto.emplace( proto.begin(), -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	array.insert( array.begin() + 5, a1 );
	proto.emplace( proto.begin() + 5, -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	array.insert( array.end() - 1, a1 );
	proto.emplace( proto.end() - 1, -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	item_t a2( -99 );
	array.insert( array.end(), a2 );
	proto.emplace( proto.end(), -99 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	ENSURE_EQUALS( "invalid pass", item_t::get_copy_count(), 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert( pos, && )" )
	item_t::reset();
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	proto_t proto( begin( a ), end( a ) );
	array_t array( begin( a ), end( a ) );
	ENSURE_EQUALS( "insertion failed", array, proto );
	item_t a1( -7 );
	array.insert( array.begin(), yaal::move( a1 ) );
	proto.emplace( proto.begin(), -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	item_t a2( -7 );
	array.insert( array.begin() + 5, yaal::move( a2 ) );
	proto.emplace( proto.begin() + 5, -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	item_t a3( -7 );
	array.insert( array.end() - 1, yaal::move( a3 ) );
	proto.emplace( proto.end() - 1, -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	item_t a4( -99 );
	array.insert( array.end(), yaal::move( a4 ) );
	proto.emplace( proto.end(), -99 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "emplace( pos, value )" )
	item_t::reset();
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	proto_t proto( begin( a ), end( a ) );
	array_t array( begin( a ), end( a ) );
	ENSURE_EQUALS( "insertion (emplace) failed", array, proto );
	array.emplace( array.begin(), -7 );
	proto.emplace( proto.begin(), -7 );
	ENSURE_EQUALS( "insertion (emplace) failed", array, proto );
	array.emplace( array.begin() + 5, -7 );
	proto.emplace( proto.begin() + 5, -7 );
	ENSURE_EQUALS( "insertion (emplace) failed", array, proto );
	array.emplace( array.end() - 1, -7 );
	proto.emplace( proto.end() - 1, -7 );
	ENSURE_EQUALS( "insertion (emplace) failed", array, proto );
	array.emplace( array.end(), -99 );
	proto.emplace( proto.end(), -99 );
	ENSURE_EQUALS( "insertion (emplace) failed", array, proto );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign operator (=)" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { -36, -1, -4, -9 };
	item_t::set_start_id( 0 );
	array_t array( begin( a0 ), end( a0 ) );
	array_t small( begin( a1 ), end( a1 ) );
	array = small;
	ENSURE_EQUALS( "assgin failed", array, small );
	array_t big( begin( a0 ), end( a0 ) );
	array = big;
	ENSURE_EQUALS( "assgin failed", array, big );
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_back on resized" ) {
		array_t array( 2048 );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( array.begin(), array.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i ) {
			proto.pop_back();
			array.pop_back();
			ENSURE_EQUALS( "pop_back failed", array, proto );
		}
		ENSURE_EQUALS( "not empty!", array.is_empty(), true );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

void tut_yaal_hcore_harray::test_erase( int first_, int last_ ) { {
		clog << "testing erase - first: " << first_ << ", last: " << last_ << endl;
		item_t::set_start_id( 0 );
		array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		proto_t proto( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.erase( proto.begin() + first_, proto.begin() + last_ );
		array.erase( array.begin() + first_, array.begin() + last_ );
		ENSURE_EQUALS( "range initialization failed", array, proto );
	}

	ENSURE_EQUALS( "object leak", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( "ranged erase" )
	test_erase( 0, countof( _testData_[0] ) / 2 );
	test_erase( countof( _testData_[0] ) / 2, countof( _testData_[0] ) );
	test_erase( 0, countof( _testData_[0] ) );
	test_erase( 0, 1 );
	test_erase( countof ( _testData_[0] ) - 1, countof ( _testData_[0] ) );
	test_erase( 1, countof ( _testData_[0] ) - 1 );
	test_erase( 3, 6 );
	test_erase( countof ( _testData_[0] ) - 6, countof ( _testData_[0] ) - 3 );
	test_erase( countof ( _testData_[0] ) / 2 - 3, countof ( _testData_[0] ) / 2 + 3 );
	test_erase( 0, countof( _testData_[0] ) / 2 + countof ( _testData_[0] ) / 4 );
	test_erase( 3, countof( _testData_[0] ) / 2 + countof ( _testData_[0] ) / 4 );
	test_erase( countof ( _testData_[0] ) / 4, countof( _testData_[0] ) );
	test_erase( countof ( _testData_[0] ) / 4, countof( _testData_[0] ) - 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ranged insert" )
	item_t::set_start_id( 0 ); {
		int const len1( countof ( _testData_[1] ) );
		proto_t proto( begin( _testData_[0] ), end( _testData_[0] ) );
		array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.begin(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.end(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.end(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.end() - 1, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.begin() + array.size() / 2, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.begin() + array.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.begin() + array.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.begin() + array.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.end() - array.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.insert( array.end() - array.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 ); {
		int const len1( countof ( _testData_[1] ) );
		proto_t proto( begin( _testData_[0] ), end( _testData_[0] ) );
		array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.begin(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.end(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.end(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.end() - 1, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.begin() + array.size() / 2, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.begin() + array.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.begin() + array.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.begin() + array.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.end() - array.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
		array.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		proto.assign( begin( _testData_[0] ), end( _testData_[0] ) );
		array.insert( array.end() - array.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		ENSURE_EQUALS( "range insertion failed", array, proto );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	int const A1INIT( 10 );
	int const A2INIT( 100 );
	int const A1D( 11 );
	int const A2D( 101 );
	array_t a1( A1INIT );
	array_t a2( A2INIT );
	ENSURE_EQUALS( "bad size from constructor a1", a1.size(), A1INIT );
	ENSURE_EQUALS( "bad size from constructor a2", a2.size(), A2INIT );
	ENSURE_EQUALS( "bad capacity from constructor a1", a1.capacity(), A1INIT );
	ENSURE_EQUALS( "bad capacity from constructor a2", a2.capacity(), A2INIT );
	a1.resize( A1D );
	a2.resize( A2D );
	ENSURE_EQUALS( "bad size from resize a1", a1.size(), A1D );
	ENSURE_EQUALS( "bad size from resize a2", a2.size(), A2D );
	ENSURE_EQUALS( "bad capacity from resize a1", a1.capacity(), A1INIT * 2 );
	ENSURE_EQUALS( "bad capacity from resize a2", a2.capacity(), A2INIT * 2 );

	array_t::const_iterator a1it( a1.begin() );
	array_t::const_iterator a2it( a2.begin() );

	ENSURE( "inconsistent iterator from begin() a1", &*a1it == &a1.front() );
	ENSURE( "inconsistent iterator from begin() a2", &*a2it == &a2.front() );
	ENSURE( "ambiguous iterator ownership from begin() a1", &*a2it != &a1.front() );
	ENSURE( "ambiguous iterator ownership from begin() a2", &*a1it != &a2.front() );

	/* now the actual test */

	a1.swap( a2 );

	ENSURE_EQUALS( "bad size from resize a1 after swap", a1.size(), A2D );
	ENSURE_EQUALS( "bad size from resize a2 after swap", a2.size(), A1D );
	ENSURE_EQUALS( "bad capacity from resize a1 after swap", a1.capacity(), A2INIT * 2 );
	ENSURE_EQUALS( "bad capacity from resize a2 after swap", a2.capacity(), A1INIT * 2 );

/*
	ENSURE( "bad value retrieved from iterator a1 after swap", &*a1it == &a2.front() );
	ENSURE( "bad value retrieved from iterator a2 after swap", &*a2it == &a1.front() );
	ENSURE( "ambiguous iterator ownership a1 after swap", &*a2it != &a2.front() );
	ENSURE( "ambiguous iterator ownership a2 after swap", &*a1it != &a1.front() );
*/

TUT_TEARDOWN()

TUT_UNIT_TEST( "data" )
	array_t a;
	a.push_back( 1 );
	ENSURE_EQUALS( "bad data", *a.data(), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "speed test" )
	TIME_CONSTRAINT_EXEMPT();
	typedef HArray<int> array_type;
	proto_t proto;
	array_type array;
	double long st( 0 );
	double long yt( 0 );
	int long LOOPS( 10000000 ); {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_back( static_cast<int>( i ) );
		clog << "*speed* std::vector<>::push_back() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	} {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			array.push_back( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HArray<>::push_back() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	}
	clog << "*speed* HArray<>::push_back() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.pop_back();
		clog << "*speed* std::vector<>::pop_back() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	} {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			array.pop_back();
		clog << "*speed* yaal::hcore::HArray<>::pop_back() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
	}
	clog << "*speed* HArray<>::pop_back() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
TUT_TEARDOWN()

}


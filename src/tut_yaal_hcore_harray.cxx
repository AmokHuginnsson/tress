/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_harray.cxx - this file is integral part of `tress' project.

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

#include <vector>

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

TUT_SIMPLE_MOCK( tut_yaal_hcore_harray );
TUT_TEST_GROUP_N( tut_yaal_hcore_harray, "yaal::hcore::HArray" );

TUT_UNIT_TEST_N( 1, "/* Constructor. */" )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	try
		{
		array_t array( BAD_SIZE );
		FAIL( "array with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Constructor and get_size(). */" )
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

TUT_UNIT_TEST_N( 3, "/* Constructor with filling. */" )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	try
		{
		array_t badArray( BAD_SIZE, FILLER_FOR_ARRAY );
		FAIL( "array with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	array_t array( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "array element not filled with default value", array[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Constructor with range initialization. */" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
		{
		array_t array( a, a + countof ( a ) );
		ENSURE( "range initialization failed", safe_equal( array.begin(), array.end(), a, a + countof ( a ) ) );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Copy constructor. */" )
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

TUT_UNIT_TEST_N( 6, "/* Operator [ ]. */" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	array_t array ( SIZE );
	try
		{
		array [ SIZE ] = 0;
		FAIL( "access beyond size succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		array[ - SIZE - 1 ] = 0;
		FAIL( "access with negative index succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* Operator bool. */" )
	item_t::set_start_id( 0 );
	int const EMPTY = 0;
	int const SIZE = 7;
	array_t empty( EMPTY );
	ENSURE_EQUALS( "test for array emptiness faild", ! empty, true );
	array_t normal( SIZE );
	ENSURE_EQUALS( "test for array fullness faild", ! normal, false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "push_back" )
	typedef std::vector<int> proto_t;
	proto_t proto;
		{
		array_t array;
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.push_back( static_cast<int>( i ) );
			array.push_back( static_cast<int>( i ) );
			ENSURE_EQUALS( "push_back failed", array, proto );
			}
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "copy constructor (of empty)" )
	array_t a1;
	ENSURE( "construction of empty array", a1.is_empty() );
	array_t a2( a1 );
	ENSURE( "construction of empty array", a2.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "resize vs capacity" )
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

TUT_UNIT_TEST_N( 11, "/* insert( pos, value ) */" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	typedef std::vector<int> proto_t;
	proto_t proto( a, a + countof ( a ) );
	array_t array( a, a + countof ( a ) );
	ENSURE_EQUALS( "insertion failed", array, proto );
	array.insert( array.begin(), -7 );
	proto.insert( proto.begin(), -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	array.insert( array.begin() + 5, -7 );
	proto.insert( proto.begin() + 5, -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	array.insert( array.end() - 1, -7 );
	proto.insert( proto.end() - 1, -7 );
	ENSURE_EQUALS( "insertion failed", array, proto );
	array.insert( array.end(), -99 );
	proto.insert( proto.end(), -99 );
	ENSURE_EQUALS( "insertion failed", array, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* assign operator (=) */" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { -36, -1, -4, -9 };
	item_t::set_start_id( 0 );
	array_t array( a0, a0 + countof ( a0 ) );
	array_t small( a1, a1 + countof ( a1 ) );
	array = small;
	ENSURE_EQUALS( "assgin failed", array, small );
	array_t big( a0, a0 + countof ( a0 ) );
	array = big;
	ENSURE_EQUALS( "assgin failed", array, big );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "push_back" )
	typedef std::vector<int> proto_t;
		{
		array_t array( 2048 );
		proto_t proto( 2048 );
		generate( array.begin(), array.end(), inc( 0 ) );
		generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.pop_back();
			array.pop_back();
			ENSURE_EQUALS( "pop_back failed", array, proto );
			}
		ENSURE_EQUALS( "not empty!", array.is_empty(), true );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 50, "speed test" )
	typedef std::vector<int> proto_t;
	typedef HArray<int> array_type;
	int long LOOPS( 10000000 );
		{
		proto_t proto;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_back( static_cast<int>( i ) );
		clog << "*speed* std::vector<>::push_back() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
		{
		array_type deque;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.push_back( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HArray<>::push_back() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
TUT_TEARDOWN()

}


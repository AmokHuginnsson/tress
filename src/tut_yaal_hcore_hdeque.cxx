/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque.cxx - this file is integral part of `tress' project.

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

#include <deque>

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

struct tut_yaal_hcore_hdeque : public simple_mock<tut_yaal_hcore_hdeque>
	{
	typedef HDeque<item_t> deque_t;
	virtual ~tut_yaal_hcore_hdeque( void ) {}
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hdeque, "yaal::hcore::HDeque" );

TUT_UNIT_TEST_N( 1, "/* Constructor. */" )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	try
		{
		deque_t deque( BAD_SIZE );
		FAIL( "deque with negative size created" );
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
	deque_t one( SIZE_FOR_ONE );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	deque_t two( SIZE_FOR_TWO );
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
		deque_t badDeque( BAD_SIZE, FILLER_FOR_ARRAY );
		FAIL( "deque with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	deque_t deque( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "deque element not filled with default value", deque[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

#if 0

TUT_UNIT_TEST_N( 4, "/* Constructor with range initialization. */" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	deque_t deque( a, a + countof ( a ) );
	ENSURE( "range initialization failed", safe_equal( deque.begin(), deque.end(), a, a + countof ( a ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Copy constructor. */" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		deque [ i ] = i;
	deque_t copy( deque );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Operator [ ]. */" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque ( SIZE );
	try
		{
		deque [ SIZE ] = 0;
		FAIL( "access beyond size succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		deque[ - SIZE - 1 ] = 0;
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
	deque_t empty( EMPTY );
	ENSURE_EQUALS( "test for deque emptiness faild", ! empty, true );
	deque_t normal( SIZE );
	ENSURE_EQUALS( "test for deque fullness faild", ! normal, false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "push_back" )
	item_t::set_start_id( 0 );
	item_t i;
	deque_t a1;
	a1.resize( 5 );
	a1.resize( 2 );
	deque_t a2;
	a2.push_back( i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "copy constructor (of empty)" )
	deque_t a1;
	ENSURE( "construction of empty deque", a1.is_empty() );
	deque_t a2( a1 );
	ENSURE( "construction of empty deque", a2.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "/* insert( pos, value ) */" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	typedef std::deque<int> proto_t;
	proto_t proto( a, a + countof ( a ) );
	deque_t deque( a, a + countof ( a ) );
	ENSURE_EQUALS( "insertion failed", deque, proto );
	deque.insert( deque.begin(), -7 );
	proto.insert( proto.begin(), -7 );
	ENSURE_EQUALS( "insertion failed", deque, proto );
	deque.insert( deque.begin() + 5, -7 );
	proto.insert( proto.begin() + 5, -7 );
	ENSURE_EQUALS( "insertion failed", deque, proto );
	deque.insert( deque.end() - 1, -7 );
	proto.insert( proto.end() - 1, -7 );
	ENSURE_EQUALS( "insertion failed", deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* assign operator (=) */" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { -36, -1, -4, -9 };
	item_t::set_start_id( 0 );
	deque_t deque( a0, a0 + countof ( a0 ) );
	deque_t small( a1, a1 + countof ( a1 ) );
	deque = small;
	ENSURE_EQUALS( "assgin failed", deque, small );
	deque_t big( a0, a0 + countof ( a0 ) );
	deque = big;
	ENSURE_EQUALS( "assgin failed", deque, big );
TUT_TEARDOWN()

#endif

}


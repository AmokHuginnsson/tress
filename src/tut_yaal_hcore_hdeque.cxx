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

#define private public
#define protected public

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
	typedef std::deque<int> proto_t;
	virtual ~tut_yaal_hcore_hdeque( void ) {}
	template<typename deque_type>
	void check_consistency( deque_type const&, int = 0 );
	template<int const item_size>
	void test_resize( void );
	template<int const item_size>
	void test_erase( int, int );
	template<int const item_size>
	void test_erase( void );
	};

template<typename deque_type>
void tut_yaal_hcore_hdeque::check_consistency( deque_type const& deque_, int extraItems )
	{
	ENSURE_EQUALS( "deque size with respect to allocated objects", deque_.get_size(), deque_type::value_type::get_instance_count() - extraItems );
	int long firstChunkIndex( deque_._start / deque_type::VALUES_PER_CHUNK );
	int long lastChunkIndex( deque_._size > 0 ? ( ( deque_._start + deque_._size - 1 ) / deque_type::VALUES_PER_CHUNK ) : ( deque_._start / deque_type::VALUES_PER_CHUNK ) );
	int long chunksCount = deque_._chunks.template count_of<typename deque_type::value_type*>();
	if ( deque_._size > 0 )
		ENSURE( "chunk range bigger than chunks count", ( lastChunkIndex - firstChunkIndex ) < chunksCount );
	else
		ENSURE_EQUALS( "bad indexes for empty deque", lastChunkIndex, firstChunkIndex );
	int long startGap( firstChunkIndex );
	int long endGap( ( chunksCount - lastChunkIndex ) - 1 );
	if ( deque_._size > 0 )
		ENSURE( "chunks are not centered", abs( endGap - startGap ) <= 1 );
	typename deque_type::value_type const* const* chunks = deque_._chunks.template get<typename deque_type::value_type const*>();
	for ( int long i( 0 ); i < firstChunkIndex; ++ i )
		ENSURE_EQUALS( "not used chunks at the begining not cleared", chunks[ i ], static_cast<typename deque_type::value_type*>( NULL ) );
	for ( int long i( lastChunkIndex + 1 ); i < chunksCount; ++ i )
		ENSURE_EQUALS( "not used chunks at the end not cleared", chunks[ i ], static_cast<typename deque_type::value_type*>( NULL ) );
	if ( deque_._size > 0 )
		{
		for ( int long i( firstChunkIndex ); i < ( lastChunkIndex + 1 ); ++ i )
			ENSURE_EQUALS( "a nil in used chunks range", chunks[ i ] ? true : false, true );
		}
	}

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

template<int const item_size>
void tut_yaal_hcore_hdeque::test_resize( void )
	{
	clog << "testing resize: " << item_size << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
		{
		deque_type deque;
		check_consistency( deque );
		deque.resize( 1 );
		check_consistency( deque );
		deque.resize( 2 );
		check_consistency( deque );
		deque.resize( 3 );
		check_consistency( deque );
		deque.resize( 7 );
		check_consistency( deque );
		deque.resize( 15 );
		check_consistency( deque );
		deque.resize( 16 );
		check_consistency( deque );
		deque.resize( 17 );
		check_consistency( deque );
		deque.resize( 64 );
		check_consistency( deque );
		deque.resize( 128 );
		check_consistency( deque );
		deque.resize( 64 );
		check_consistency( deque );
		deque.resize( 17 );
		check_consistency( deque );
		deque.resize( 16 );
		check_consistency( deque );
		deque.resize( 15 );
		check_consistency( deque );
		deque.resize( 7 );
		check_consistency( deque );
		deque.resize( 3 );
		check_consistency( deque );
		deque.resize( 2 );
		check_consistency( deque );
		deque.resize( 1 );
		check_consistency( deque );
		deque.resize( 0 );
		check_consistency( deque );
		}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	return;
	}

TUT_UNIT_TEST_N( 2, "/* Constructor and get_size(). */" )
	{
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	deque_t one( SIZE_FOR_ONE );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	check_consistency( one );
	deque_t two( SIZE_FOR_TWO );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE + SIZE_FOR_TWO );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", two.get_size(), SIZE_FOR_TWO );
	check_consistency( two );
	}
	ENSURE_EQUALS( "object leak", item_t::get_instance_count(), 0 );
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
	check_consistency( deque );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "deque element not filled with default value", deque[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "resize" )
	test_resize<1>();
	test_resize<2>();
	test_resize<3>();
	test_resize<7>();
	test_resize<15>();
	test_resize<16>();
	test_resize<17>();
	test_resize<64>();
	test_resize<128>();
	test_resize<200>();
	test_resize<511>();
	test_resize<512>();
	test_resize<513>();
	test_resize<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Constructor with range initialization. */" )
	int a[] = { 7, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 13 };
	item_t::set_start_id( 0 );
	deque_t deque( a, a + countof ( a ) );
	proto_t proto( a, a + countof ( a ) );
	check_consistency( deque );
	ENSURE_EQUALS( "range initialization failed", deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* Copy constructor. */" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		deque[ i ] = i;
	check_consistency( deque );
	deque_t copy( deque );
	check_consistency( copy, SIZE );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Operator [ ]. */" )
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

TUT_UNIT_TEST_N( 9, "/* Operator bool. */" )
	item_t::set_start_id( 0 );
	int const EMPTY = 0;
	int const SIZE = 7;
	deque_t empty( EMPTY );
	ENSURE_EQUALS( "test for deque emptiness faild", ! empty, true );
	deque_t normal( SIZE );
	ENSURE_EQUALS( "test for deque fullness faild", ! normal, false );
TUT_TEARDOWN()

int a[] = { 7, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 13 };

template<int const item_size>
void tut_yaal_hcore_hdeque::test_erase( int first_, int last_ )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
		{
		clog << "testing erase: " << item_size << ", first: " << first_ << ", last: " << last_ << endl;
		item_type::set_start_id( 0 );
		deque_type deque( a, a + countof ( a ) );
		proto_t proto( a, a + countof ( a ) );
		proto.erase( proto.begin() + first_, proto.begin() + last_ );
		deque.erase( deque.begin() + first_, deque.begin() + last_ );
		check_consistency( deque );
		ENSURE_EQUALS( "range initialization failed", deque, proto );
		}

	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	}

template<int const item_size>
void tut_yaal_hcore_hdeque::test_erase( void )
	{
	test_erase<item_size>( 0, countof( a ) / 2 );
	test_erase<item_size>( countof( a ) / 2, countof( a ) );
	test_erase<item_size>( 0, countof( a ) );
	test_erase<item_size>( 0, 1 );
	test_erase<item_size>( countof ( a ) - 1, countof ( a ) );
	test_erase<item_size>( 1, countof ( a ) - 1 );
	test_erase<item_size>( 3, 6 );
	test_erase<item_size>( countof ( a ) - 6, countof ( a ) - 3 );
	test_erase<item_size>( countof ( a ) / 2 - 3, countof ( a ) / 2 + 3 );
	test_erase<item_size>( 0, countof( a ) / 2 + countof ( a ) / 4 );
	test_erase<item_size>( 3, countof( a ) / 2 + countof ( a ) / 4 );
	test_erase<item_size>( countof ( a ) / 4, countof( a ) );
	test_erase<item_size>( countof ( a ) / 4, countof( a ) - 3 );
	}

TUT_UNIT_TEST_N( 10, "/* range erase */" )
	test_erase<1>();
	test_erase<2>();
	test_erase<3>();
	test_erase<7>();
	test_erase<15>();
	test_erase<16>();
	test_erase<17>();
	test_erase<64>();
	test_erase<128>();
	test_erase<200>();
	test_erase<511>();
	test_erase<512>();
	test_erase<513>();
	test_erase<640>();
TUT_TEARDOWN()

#if 0

TUT_UNIT_TEST_N( 10, "push_back" )
	item_t::set_start_id( 0 );
	item_t i;
	deque_t a1;
	a1.resize( 5 );
	a1.resize( 2 );
	deque_t a2;
	a2.push_back( i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "copy constructor (of empty)" )
	deque_t a1;
	ENSURE( "construction of empty deque", a1.is_empty() );
	deque_t a2( a1 );
	ENSURE( "construction of empty deque", a2.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "/* insert( pos, value ) */" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
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
	deque.insert( deque.end(), -99 );
	proto.insert( proto.end(), -99 );
	ENSURE_EQUALS( "insertion failed", deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "/* assign operator (=) */" )
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

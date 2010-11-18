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
	struct StatePreserver
		{
		int long _size;
		int long _usedChunks;
		int long _availChunks;
		int long _firstChunkIndex;
		int long _lastChunkIndex;
		};
	StatePreserver _statePreserver;
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
	template<int const item_size>
	void test_push_back( void );
	template<int const item_size>
	void test_push_front( void );
	template<int const item_size>
	void test_pop_back( void );
	template<int const item_size>
	void test_pop_front( void );
	template<int const item_size>
	void test_insert_pos( void );
	tut_yaal_hcore_hdeque( void ) : _statePreserver() {}
	};

template<typename deque_type>
void tut_yaal_hcore_hdeque::check_consistency( deque_type const& deque_, int extraItems )
	{
	ENSURE_EQUALS( "deque size with respect to allocated objects", deque_.get_size(), deque_type::value_type::get_instance_count() - extraItems );
	int long firstChunkIndex( deque_._start / deque_type::VALUES_PER_CHUNK );
	int long lastChunkIndex( deque_._size > 0 ? ( ( deque_._start + deque_._size - 1 ) / deque_type::VALUES_PER_CHUNK ) : ( deque_._start / deque_type::VALUES_PER_CHUNK ) );
	int long chunksCount = deque_._chunks.template count_of<typename deque_type::value_type*>();
	int long usedChunks = deque_.used_chunks();
	if ( deque_._size > 0 )
		{
		ENSURE( "chunk range bigger than chunks count", ( lastChunkIndex - firstChunkIndex ) < chunksCount );
		ENSURE( "last chunk outside avail chunks", lastChunkIndex < chunksCount );
		}
	else
		ENSURE_EQUALS( "bad indexes for empty deque", lastChunkIndex, firstChunkIndex );
	ENSURE( "first chunk outsize avail chunks", deque_._start >= 0 );
	if ( ( chunksCount > _statePreserver._availChunks )
			|| ( ( firstChunkIndex < _statePreserver._firstChunkIndex ) && ( ( _statePreserver._firstChunkIndex + usedChunks ) >= _statePreserver._availChunks ) )
			|| ( ( lastChunkIndex > _statePreserver._lastChunkIndex ) && ( ( _statePreserver._lastChunkIndex + 1 - usedChunks ) < 0 ) ) )
		{
		int long startGap( firstChunkIndex );
		int long endGap( ( chunksCount - lastChunkIndex ) - 1 );
/*
		clog << "_lastChunkIndex: " << _statePreserver._lastChunkIndex << endl;
		clog << "chunksCount: " << chunksCount << ", firstChunkIndex: " << firstChunkIndex << ", lastChunkIndex: " << lastChunkIndex << ", startGap: " << startGap << ", endGap: " << endGap << endl;
*/
		if ( deque_._size > 0 )
			ENSURE_DISTANCE( "chunks are not centered", abs( endGap - startGap ), 0l, 2l );
		}
	else if ( ( firstChunkIndex > _statePreserver._firstChunkIndex ) || ( lastChunkIndex < _statePreserver._lastChunkIndex ) )
		{
/*
		clog << "firstChunkIndex: " << firstChunkIndex << ", _statePreserver._firstChunkIndex: " << _statePreserver._firstChunkIndex << ", lastChunkIndex: " << lastChunkIndex << ", _statePreserver._lastChunkIndex: " << _statePreserver._lastChunkIndex << ", deque_._size: " << deque_._size << ", _statePreserver._size: " << _statePreserver._size << ", chunksCount: " << chunksCount << ", _statePreserver._availChunks: " << _statePreserver._availChunks << endl;
*/
		ENSURE( "unnecesarry chunks move", ( deque_._size < _statePreserver._size ) || ( chunksCount > _statePreserver._availChunks ) );
		}
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
	_statePreserver._size = deque_._size;
	_statePreserver._usedChunks = usedChunks;
	_statePreserver._availChunks = chunksCount;
	_statePreserver._firstChunkIndex = firstChunkIndex;
	_statePreserver._lastChunkIndex = lastChunkIndex;
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
		deque.resize( 33 );
		check_consistency( deque );
		deque.resize( 333 );
		check_consistency( deque );
		deque.resize( 3333 );
		check_consistency( deque );
		deque.resize( 33 );
		check_consistency( deque );
		deque.resize( 333 );
		check_consistency( deque );
		deque.resize( 3 );
		check_consistency( deque );
		deque.resize( 3333 );
		check_consistency( deque );
		deque.resize( 333 );
		check_consistency( deque );
		deque.resize( 3 );
		check_consistency( deque );
		deque.resize( 0 );
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
	test_resize<4>();
	test_resize<5>();
	test_resize<6>();
	test_resize<7>();
	test_resize<8>();
	test_resize<9>();
	test_resize<10>();
	test_resize<11>();
	test_resize<12>();
	test_resize<13>();
	test_resize<14>();
	test_resize<15>();
	test_resize<16>();
	test_resize<17>();
	test_resize<18>();
	test_resize<19>();
	test_resize<20>();
	test_resize<21>();
	test_resize<22>();
	test_resize<23>();
	test_resize<24>();
	test_resize<25>();
	test_resize<26>();
	test_resize<27>();
	test_resize<28>();
	test_resize<29>();
	test_resize<30>();
	test_resize<31>();
	test_resize<32>();
	test_resize<33>();
	test_resize<34>();
	test_resize<35>();
	test_resize<36>();
	test_resize<37>();
	test_resize<38>();
	test_resize<39>();
	test_resize<40>();
	test_resize<41>();
	test_resize<42>();
	test_resize<43>();
	test_resize<44>();
	test_resize<45>();
	test_resize<46>();
	test_resize<47>();
	test_resize<48>();
	test_resize<49>();
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
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, 128> big_item_t;
	typedef HDeque<big_item_t> big_deque_t;
	big_deque_t big_deque( a, a + countof ( a ) );
	check_consistency( deque );
	ENSURE_EQUALS( "range initialization failed", big_deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Copy constructor. */" )
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

TUT_UNIT_TEST_N( 7, "/* Operator [ ]. */" )
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

TUT_UNIT_TEST_N( 8, "/* Operator bool. */" )
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

TUT_UNIT_TEST_N( 9, "/* range erase */" )
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

template<int const item_size>
void tut_yaal_hcore_hdeque::test_push_back( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
	clog << "testing push_back: " << item_size << endl;
		{
		deque_type deque;
		proto_t proto;
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.push_back( static_cast<int>( i ) );
			deque.push_back( static_cast<int>( i ) );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	}

TUT_UNIT_TEST_N( 10, "push_back" )
	test_push_back<1>();
	test_push_back<2>();
	test_push_back<3>();
	test_push_back<7>();
	test_push_back<15>();
	test_push_back<16>();
	test_push_back<17>();
	test_push_back<64>();
	test_push_back<128>();
	test_push_back<200>();
	test_push_back<511>();
	test_push_back<512>();
	test_push_back<513>();
	test_push_back<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_push_front( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
	clog << "testing push_front: " << item_size << endl;
		{
		deque_type deque;
		proto_t proto;
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.push_front( static_cast<int>( i ) );
			deque.push_front( static_cast<int>( i ) );
			check_consistency( deque );
			ENSURE_EQUALS( "push_front failed", deque, proto );
			}
		}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	}

TUT_UNIT_TEST_N( 11, "push_front" )
	test_push_front<1>();
	test_push_front<2>();
	test_push_front<3>();
	test_push_front<7>();
	test_push_front<15>();
	test_push_front<16>();
	test_push_front<17>();
	test_push_front<64>();
	test_push_front<128>();
	test_push_front<200>();
	test_push_front<511>();
	test_push_front<512>();
	test_push_front<513>();
	test_push_front<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_pop_back( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
	clog << "testing pop_back: " << item_size << endl;
		{
		deque_type deque( 2048 );
		check_consistency( deque );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( deque.begin(), deque.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.pop_back();
			deque.pop_back();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_back failed", deque, proto );
			}
		ENSURE_EQUALS( "not empty!", deque.is_empty(), true );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST_N( 12, "pop_back" )
	test_pop_back<1>();
	test_pop_back<2>();
	test_pop_back<3>();
	test_pop_back<7>();
	test_pop_back<15>();
	test_pop_back<16>();
	test_pop_back<17>();
	test_pop_back<64>();
	test_pop_back<128>();
	test_pop_back<200>();
	test_pop_back<511>();
	test_pop_back<512>();
	test_pop_back<513>();
	test_pop_back<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_pop_front( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
	clog << "testing pop_front: " << item_size << endl;
		{
		deque_type deque( 2048 );
		check_consistency( deque );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( deque.begin(), deque.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i )
			{
			proto.pop_front();
			deque.pop_front();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_front failed", deque, proto );
			}
		ENSURE_EQUALS( "not empty!", deque.is_empty(), true );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST_N( 13, "pop_front" )
	test_pop_front<1>();
	test_pop_front<2>();
	test_pop_front<3>();
	test_pop_front<7>();
	test_pop_front<15>();
	test_pop_front<16>();
	test_pop_front<17>();
	test_pop_front<64>();
	test_pop_front<128>();
	test_pop_front<200>();
	test_pop_front<511>();
	test_pop_front<512>();
	test_pop_front<513>();
	test_pop_front<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "copy constructor (of empty)" )
	deque_t a1;
	check_consistency( a1 );
	ENSURE( "construction of empty deque", a1.is_empty() );
	deque_t a2( a1 );
	check_consistency( a2 );
	ENSURE( "construction of empty deque", a2.is_empty() );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_insert_pos( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_t> deque_type;
	clog << "testing insert(pos): " << item_size << endl;
	item_t::set_start_id( 0 );
		{
		proto_t proto( a, a + countof ( a ) );
		deque_type deque( a, a + countof ( a ) );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.begin(), -7 );
		check_consistency( deque );
		proto.insert( proto.begin(), -7 );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.begin() + 5, -7 );
		check_consistency( deque );
		proto.insert( proto.begin() + 5, -7 );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.end() - 1, -7 );
		check_consistency( deque );
		proto.insert( proto.end() - 1, -7 );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.end(), -99 );
		check_consistency( deque );
		proto.insert( proto.end(), -99 );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST_N( 15, "/* insert( pos, value ) */" )
	test_insert_pos<1>();
	test_insert_pos<2>();
	test_insert_pos<3>();
	test_insert_pos<7>();
	test_insert_pos<15>();
	test_insert_pos<16>();
	test_insert_pos<17>();
	test_insert_pos<64>();
	test_insert_pos<128>();
	test_insert_pos<200>();
	test_insert_pos<511>();
	test_insert_pos<512>();
	test_insert_pos<513>();
	test_insert_pos<640>();
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 16, "/* assign operator (=) */" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { -36, -1, -4, -9 };
	item_t::set_start_id( 0 );
		{
		deque_t deque( a0, a0 + countof ( a0 ) );
		check_consistency( deque );
		deque_t small( a1, a1 + countof ( a1 ) );
		check_consistency( small );
		deque = small;
		check_consistency( deque );
		ENSURE_EQUALS( "assgin failed", deque, small );
		deque_t big( a0, a0 + countof ( a0 ) );
		check_consistency( big );
		deque = big;
		check_consistency( deque );
		ENSURE_EQUALS( "assgin failed", deque, big );
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 50, "speed test" )
	typedef HDeque<int> deque_type;
	int long LOOPS( 1000000 );
		{
		proto_t proto;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_back( static_cast<int>( i ) );
		clog << "*speed* std::deque<>::push_back() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
		{
		deque_type deque;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.push_back( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HDeque<>::push_back() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
		{
		proto_t proto;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_front( static_cast<int>( i ) );
		clog << "*speed* std::deque<>::push_front() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
		{
		deque_type deque;
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.push_front( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HDeque<>::push_front() = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
		}
TUT_TEARDOWN()

}


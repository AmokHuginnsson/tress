/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque_1.cxx - this file is integral part of `tress' project.

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

#include "tut_yaal_hcore_hdeque.hxx"

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hdeque_1 : public tut_yaal_hcore_hdeque_base<1> {
	virtual ~tut_yaal_hcore_hdeque_1( void ) {}
	template<int const item_size>
	void test_resize( void );
	template<int const item_size>
	void test_erase( int, int );
	template<int const item_size>
	void test_erase( void );
	template<int const item_size>
	void test_roll_forward_insert_erase( int, int, int );
	template<int const item_size>
	void test_roll_forward_greedy_insert_erase( int, int );
};

TUT_TEST_GROUP( tut_yaal_hcore_hdeque_1, "yaal::hcore::HDeque,1" );

TUT_UNIT_TEST( 5, "Constructor with range initialization." )
	item_t::set_start_id( 0 );
	deque_t deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	proto_t proto( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	check_consistency( deque );
	ENSURE_EQUALS( "range initialization failed", deque, proto );
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_1, 128> big_item_t;
	typedef HDeque<big_item_t> big_deque_t;
	big_deque_t big_deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	check_consistency( deque );
	check_consistency( big_deque );
	ENSURE_EQUALS( "range initialization failed", big_deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "Copy constructor." )
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

TUT_UNIT_TEST( 7, "Operator [ ]." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque ( SIZE );
	try {
		deque [ SIZE ] = 0;
		FAIL( "access beyond size succed" );
	} catch ( HException const& e ) {
		cout << e.what() << endl;
	}
	try {
		deque[ - SIZE - 1 ] = 0;
		FAIL( "access with negative index succed" );
	} catch ( HException const& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "Operator bool." )
	item_t::set_start_id( 0 );
	int const EMPTY = 0;
	int const SIZE = 7;
	deque_t empty( EMPTY );
	ENSURE_EQUALS( "test for deque emptiness faild", ! empty, true );
	deque_t normal( SIZE );
	ENSURE_EQUALS( "test for deque fullness faild", ! normal, false );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque_1::test_erase( int first_, int last_ ) {
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_1, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		clog << "testing erase: " << item_size << ", first: " << first_ << ", last: " << last_ << endl;
		item_type::set_start_id( 0 );
		deque_type deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		check_consistency( deque );
		proto_t proto( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		proto.erase( proto.begin() + first_, proto.begin() + last_ );
		deque.erase( deque.begin() + first_, deque.begin() + last_ );
		check_consistency( deque );
		ENSURE_EQUALS( "range initialization failed", deque, proto );
	}

	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
}

template<int const item_size>
void tut_yaal_hcore_hdeque_1::test_erase( void ) {
	test_erase<item_size>( 0, countof( _testData_[0] ) / 2 );
	test_erase<item_size>( countof( _testData_[0] ) / 2, countof( _testData_[0] ) );
	test_erase<item_size>( 0, countof( _testData_[0] ) );
	test_erase<item_size>( 0, 1 );
	test_erase<item_size>( countof ( _testData_[0] ) - 1, countof ( _testData_[0] ) );
	test_erase<item_size>( 1, countof ( _testData_[0] ) - 1 );
	test_erase<item_size>( 3, 6 );
	test_erase<item_size>( countof ( _testData_[0] ) - 6, countof ( _testData_[0] ) - 3 );
	test_erase<item_size>( countof ( _testData_[0] ) / 2 - 3, countof ( _testData_[0] ) / 2 + 3 );
	test_erase<item_size>( 0, countof( _testData_[0] ) / 2 + countof ( _testData_[0] ) / 4 );
	test_erase<item_size>( 3, countof( _testData_[0] ) / 2 + countof ( _testData_[0] ) / 4 );
	test_erase<item_size>( countof ( _testData_[0] ) / 4, countof( _testData_[0] ) );
	test_erase<item_size>( countof ( _testData_[0] ) / 4, countof( _testData_[0] ) - 3 );
}

TUT_UNIT_TEST( 9, "range erase" )
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
void tut_yaal_hcore_hdeque_1::test_roll_forward_insert_erase( int shift_, int pack_, int distance_ ) {
	clog << "testing roll forward insert erase: " << item_size << ", " << shift_ << ", " << pack_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_1, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i ) {
			proto.insert( proto.end(), i );
			deque.insert( deque.end(), i );
			check_consistency( deque );
			ENSURE_EQUALS( "insert back failed", deque, proto );
		} while ( i < distance_ ) {
			for ( int p( 0 ); p < pack_; ++ p, ++ i ) {
				proto.insert( proto.end(), i );
				deque.insert( deque.end(), i );
				check_consistency( deque );
				ENSURE_EQUALS( "insert back failed", deque, proto );
			}
			for ( int p( 0 ); p < pack_; ++ p ) {
				proto.erase( proto.begin() );
				deque.erase( deque.begin() );
				check_consistency( deque );
				ENSURE_EQUALS( "erase front failed", deque, proto );
			}
		}
		for ( i = 0; i < shift_; ++ i ) {
			proto.erase( proto.begin() );
			deque.erase( deque.begin() );
			check_consistency( deque );
			ENSURE_EQUALS( "erase front failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

template<int const item_size>
void tut_yaal_hcore_hdeque_1::test_roll_forward_greedy_insert_erase( int shift_, int distance_ ) {
	clog << "testing roll forward greedy insert erase: " << item_size << ", " << shift_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_1, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i ) {
			proto.insert( proto.end(), i );
			deque.insert( deque.end(), i );
			check_consistency( deque );
			ENSURE_EQUALS( "insert back failed", deque, proto );
		} while ( i < distance_ ) {
			for ( int s( 0 ); s < shift_; ++ s ) {
				proto.erase( proto.begin() );
				deque.erase( deque.begin() );
				check_consistency( deque );
				ENSURE_EQUALS( "erase front failed", deque, proto );
			}
			for ( int s( 0 ); s < shift_; ++ s, ++ i ) {
				proto.insert( proto.end(), i );
				deque.insert( deque.end(), i );
				check_consistency( deque );
				ENSURE_EQUALS( "insert back failed", deque, proto );
			}
		}
		for ( i = 0; i < shift_; ++ i ) {
			proto.erase( proto.begin() );
			deque.erase( deque.begin() );
			check_consistency( deque );
			ENSURE_EQUALS( "erase front failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( 18, "roll forward (push_back/pop_front) insert erase" )
	int shift[] = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 32 };
	int pack[] = { 1, 2, 3, 4, 5, 7, 8 };
	int distance( 1024 );
	for ( int s( 0 ); s < countof ( shift ); ++ s ) {
		for ( int p( 0 ); p < countof ( pack ); ++ p ) {
			test_roll_forward_insert_erase<1>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<2>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<3>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<7>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<15>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<16>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<17>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<64>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<128>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<200>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<511>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<512>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<513>( shift[s], pack[p], distance );
			test_roll_forward_insert_erase<640>( shift[s], pack[p], distance );
		}
	}
	for ( int s( 0 ); s < countof ( shift ); ++ s ) {
		test_roll_forward_greedy_insert_erase<1>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<2>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<3>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<7>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<15>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<16>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<17>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<64>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<128>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<200>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<511>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<512>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<513>( shift[s], distance );
		test_roll_forward_greedy_insert_erase<640>( shift[s], distance );
	}
TUT_TEARDOWN()

}


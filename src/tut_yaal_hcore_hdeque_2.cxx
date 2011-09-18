/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque_2.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hdeque_2 : public tut_yaal_hcore_hdeque_base<2> {
	virtual ~tut_yaal_hcore_hdeque_2( void ) {}
	template<int const item_size>
	void test_insert_pos( void );
	template<int const item_size>
	void test_insert( void );
	template<int const item_size>
	void test_roll_backward_insert_erase( int, int, int );
	template<int const item_size>
	void test_roll_backward_greedy_insert_erase( int, int );
};

TUT_TEST_GROUP( tut_yaal_hcore_hdeque_2, "yaal::hcore::HDeque,2" );

TUT_UNIT_TEST( 14, "copy constructor (of empty)" )
	deque_t a1;
	check_consistency( a1 );
	ENSURE( "construction of empty deque", a1.is_empty() );
	deque_t a2( a1 );
	check_consistency( a2 );
	ENSURE( "construction of empty deque", a2.is_empty() );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque_2::test_insert_pos( void ) {
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_2, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing insert(pos): " << item_size << endl;
	item_t::set_start_id( 0 ); {
		proto_t proto( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		deque_type deque( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.begin(), -7 );
		proto.insert( proto.begin(), -7 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.begin() + 5, -7 );
		proto.insert( proto.begin() + 5, -7 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.end() - 1, -7 );
		proto.insert( proto.end() - 1, -7 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
		deque.insert( deque.end(), -99 );
		proto.insert( proto.end(), -99 );
		check_consistency( deque );
		ENSURE_EQUALS( "insertion failed", deque, proto );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( 15, "insert( pos, value )" )
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

TUT_UNIT_TEST( 16, "assign operator (=)" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { -36, -1, -4, -9 };
	item_t::set_start_id( 0 ); {
		deque_t deque( a0, a0 + countof ( a0 ) );
		check_consistency( deque );
		deque_t small( a1, a1 + countof ( a1 ) );
		check_consistency( small, deque.get_size() );
		deque = small;
		check_consistency( deque, small.get_size() );
		ENSURE_EQUALS( "assgin failed", deque, small );
		deque_t big( a0, a0 + countof ( a0 ) );
		check_consistency( big, deque.get_size() + small.get_size() );
		deque = big;
		check_consistency( deque, big.get_size() + small.get_size() );
		ENSURE_EQUALS( "assgin failed", deque, big );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque_2::test_insert( void ) {
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_2, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing insert range: " << item_size << endl;
	item_t::set_start_id( 0 ); {
		int const len0( countof ( _testData_[0] ) );
		int const len1( countof ( _testData_[1] ) );
		proto_t proto( _testData_[0], _testData_[0] + len0 );
		deque_type deque( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
	} {
		int const len0( countof ( _testData_[0] ) );
		int const len1( countof ( _testData_[1] ) );
		proto_t proto( _testData_[0], _testData_[0] + len0 );
		deque_type deque( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end(), _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end(), _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - 1, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 2, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.begin() + deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.begin() + proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
		deque.assign( _testData_[0], _testData_[0] + len0 );
		proto.assign( _testData_[0], _testData_[0] + len0 );
		check_consistency( deque );
		deque.insert( deque.end() - deque.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		proto.insert( proto.end() - proto.size() / 3, _testData_[1], _testData_[1] + len1 / 2 );
		check_consistency( deque );
		ENSURE_EQUALS( "range insertion failed", deque, proto );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( 17, "insert range" )
	test_insert<1>();
	test_insert<2>();
	test_insert<3>();
	test_insert<7>();
	test_insert<15>();
	test_insert<16>();
	test_insert<17>();
	test_insert<64>();
	test_insert<128>();
	test_insert<200>();
	test_insert<511>();
	test_insert<512>();
	test_insert<513>();
	test_insert<640>();
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque_2::test_roll_backward_greedy_insert_erase( int shift_, int distance_ ) {
	clog << "testing roll backward greedy insert erase: " << item_size << ", " << shift_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_2, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i ) {
			proto.insert( proto.begin(), i );
			deque.insert( deque.begin(), i );
			check_consistency( deque );
			ENSURE_EQUALS( "insert front failed", deque, proto );
		} while ( i < distance_ ) {
			for ( int s( 0 ); s < shift_; ++ s ) {
				proto.erase( proto.end() - 1 );
				deque.erase( deque.end() - 1 );
				check_consistency( deque );
				ENSURE_EQUALS( "erase back failed", deque, proto );
			}
			for ( int s( 0 ); s < shift_; ++ s, ++ i ) {
				proto.insert( proto.begin(), i );
				deque.insert( deque.begin(), i );
				check_consistency( deque );
				ENSURE_EQUALS( "insert front failed", deque, proto );
			}
		}
		for ( i = 0; i < shift_; ++ i ) {
			proto.erase( proto.end() - 1 );
			deque.erase( deque.end() - 1 );
			check_consistency( deque );
			ENSURE_EQUALS( "erase back failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

template<int const item_size>
void tut_yaal_hcore_hdeque_2::test_roll_backward_insert_erase( int shift_, int pack_, int distance_ ) {
	clog << "testing roll backward insert erase: " << item_size << ", " << shift_ << ", " << pack_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_2, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i ) {
			proto.insert( proto.begin(), i );
			deque.insert( deque.begin(), i );
			check_consistency( deque );
			ENSURE_EQUALS( "insert front failed", deque, proto );
		} while ( i < distance_ ) {
			for ( int p( 0 ); p < pack_; ++ p, ++ i ) {
				proto.insert( proto.begin(), i );
				deque.insert( deque.begin(), i );
				check_consistency( deque );
				ENSURE_EQUALS( "insert front failed", deque, proto );
			}
			for ( int p( 0 ); p < pack_; ++ p ) {
				proto.erase( proto.end() - 1 );
				deque.erase( deque.end() - 1 );
				check_consistency( deque );
				ENSURE_EQUALS( "erase back failed", deque, proto );
			}
		}
		for ( i = 0; i < shift_; ++ i ) {
			proto.erase( proto.end() - 1 );
			deque.erase( deque.end() - 1 );
			check_consistency( deque );
			ENSURE_EQUALS( "erase back failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( 19, "roll backward (push_front/pop_back) insert erase" )
	int shift[] = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 32 };
	int pack[] = { 1, 2, 3, 4, 5, 7, 8 };
	int distance( 1024 );
	for ( int s( 0 ); s < countof ( shift ); ++ s ) {
		for ( int p( 0 ); p < countof ( pack ); ++ p ) {
			test_roll_backward_insert_erase<1>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<2>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<3>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<7>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<15>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<16>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<17>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<64>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<128>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<200>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<511>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<512>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<513>( shift[s], pack[p], distance );
			test_roll_backward_insert_erase<640>( shift[s], pack[p], distance );
		}
	}
	for ( int s( 0 ); s < countof ( shift ); ++ s ) {
		test_roll_backward_greedy_insert_erase<1>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<2>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<3>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<7>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<15>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<16>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<17>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<64>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<128>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<200>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<511>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<512>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<513>( shift[s], distance );
		test_roll_backward_greedy_insert_erase<640>( shift[s], distance );
	}
TUT_TEARDOWN()

}


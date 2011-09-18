/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque_3.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hdeque_3 : public tut_yaal_hcore_hdeque_base<3> {
	virtual ~tut_yaal_hcore_hdeque_3( void ) {}
	template<int const item_size>
	void test_push_back( void );
	template<int const item_size>
	void test_roll_forward( int, int, int );
	template<int const item_size>
	void test_roll_forward_greedy( int, int );
};

TUT_TEST_GROUP( tut_yaal_hcore_hdeque_3, "yaal::hcore::HDeque,3" );

template<int const item_size>
void tut_yaal_hcore_hdeque_3::test_push_back( void ) {
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_3, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing push_back: " << item_size << endl; {
		deque_type deque;
		proto_t proto;
		for ( int long i( 0 ); i < 2048; ++ i ) {
			proto.push_back( static_cast<int>( i ) );
			deque.push_back( static_cast<int>( i ) );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
}

TUT_UNIT_TEST( 10, "push_back" )
	TIME_CONSTRAINT_EXEMPT();
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
void tut_yaal_hcore_hdeque_3::test_roll_forward( int shift_, int pack_, int distance_ ) {
	clog << "testing roll forward: " << item_size << ", " << shift_ << ", " << pack_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_3, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i ) {
			proto.push_back( i );
			deque.push_back( i );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
		} while ( i < distance_ ) {
			for ( int p( 0 ); p < pack_; ++ p, ++ i ) {
				proto.push_back( i );
				deque.push_back( i );
				check_consistency( deque );
				ENSURE_EQUALS( "push_back failed", deque, proto );
			}
			for ( int p( 0 ); p < pack_; ++ p ) {
				proto.pop_front();
				deque.pop_front();
				check_consistency( deque );
				ENSURE_EQUALS( "pop_front failed", deque, proto );
			}
		}
		for ( i = 0; i < shift_; ++ i ) {
			proto.pop_front();
			deque.pop_front();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_front failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

template<int const item_size>
void tut_yaal_hcore_hdeque_3::test_roll_forward_greedy( int shift_, int distance_ ) {
	clog << "testing roll forward greedy: " << item_size << ", " << shift_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_3, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i ) {
			proto.push_back( i );
			deque.push_back( i );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
		} while ( i < distance_ ) {
			for ( int s( 0 ); s < shift_; ++ s ) {
				proto.pop_front();
				deque.pop_front();
				check_consistency( deque );
				ENSURE_EQUALS( "pop_front failed", deque, proto );
			}
			for ( int s( 0 ); s < shift_; ++ s, ++ i ) {
				proto.push_back( i );
				deque.push_back( i );
				check_consistency( deque );
				ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		}
		for ( i = 0; i < shift_; ++ i ) {
			proto.pop_front();
			deque.pop_front();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_front failed", deque, proto );
		}
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( 20, "roll forward (push_back/pop_front)" )
	int shift[] = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 32 };
	int pack[] = { 1, 2, 3, 4, 5, 7, 8 };
	int distance( 1024 );
	for ( int s( 0 ); s < countof ( shift ); ++ s ) {
		for ( int p( 0 ); p < countof ( pack ); ++ p ) {
			test_roll_forward<1>( shift[s], pack[p], distance );
			test_roll_forward<2>( shift[s], pack[p], distance );
			test_roll_forward<3>( shift[s], pack[p], distance );
			test_roll_forward<7>( shift[s], pack[p], distance );
			test_roll_forward<15>( shift[s], pack[p], distance );
			test_roll_forward<16>( shift[s], pack[p], distance );
			test_roll_forward<17>( shift[s], pack[p], distance );
			test_roll_forward<64>( shift[s], pack[p], distance );
			test_roll_forward<128>( shift[s], pack[p], distance );
			test_roll_forward<200>( shift[s], pack[p], distance );
			test_roll_forward<511>( shift[s], pack[p], distance );
			test_roll_forward<512>( shift[s], pack[p], distance );
			test_roll_forward<513>( shift[s], pack[p], distance );
			test_roll_forward<640>( shift[s], pack[p], distance );
		}
	}
	for ( int s( 0 ); s < countof ( shift ); ++ s ) {
		test_roll_forward_greedy<1>( shift[s], distance );
		test_roll_forward_greedy<2>( shift[s], distance );
		test_roll_forward_greedy<3>( shift[s], distance );
		test_roll_forward_greedy<7>( shift[s], distance );
		test_roll_forward_greedy<15>( shift[s], distance );
		test_roll_forward_greedy<16>( shift[s], distance );
		test_roll_forward_greedy<17>( shift[s], distance );
		test_roll_forward_greedy<64>( shift[s], distance );
		test_roll_forward_greedy<128>( shift[s], distance );
		test_roll_forward_greedy<200>( shift[s], distance );
		test_roll_forward_greedy<511>( shift[s], distance );
		test_roll_forward_greedy<512>( shift[s], distance );
		test_roll_forward_greedy<513>( shift[s], distance );
		test_roll_forward_greedy<640>( shift[s], distance );
	}
TUT_TEARDOWN()

}


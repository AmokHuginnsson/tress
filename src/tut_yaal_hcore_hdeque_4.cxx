/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque_4.cxx - this file is integral part of `tress' project.

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

namespace tut
{

struct tut_yaal_hcore_hdeque_4 : public tut_yaal_hcore_hdeque_base<4>
	{
	virtual ~tut_yaal_hcore_hdeque_4( void ) {}
	template<int const item_size>
	void test_push_front( void );
	template<int const item_size>
	void test_roll_backward( int, int, int );
	template<int const item_size>
	void test_roll_backward_greedy( int, int );
	};

TUT_TEST_GROUP( tut_yaal_hcore_hdeque_4, "yaal::hcore::HDeque,4" );

template<int const item_size>
void tut_yaal_hcore_hdeque_4::test_push_front( void )
	{
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_4, item_size> item_type;
	typedef HDeque<item_type> deque_type;
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

TUT_UNIT_TEST( 11, "push_front" )
	TIME_CONSTRAINT_EXEMPT();
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
void tut_yaal_hcore_hdeque_4::test_roll_backward( int shift_, int pack_, int distance_ )
	{
	clog << "testing roll backward: " << item_size << ", " << shift_ << ", " << pack_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_4, item_size> item_type;
	typedef HDeque<item_type> deque_type;
		{
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i )
			{
			proto.push_front( i );
			deque.push_front( i );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		while ( i < distance_ )
			{
			for ( int p( 0 ); p < pack_; ++ p, ++ i )
				{
				proto.push_front( i );
				deque.push_front( i );
				check_consistency( deque );
				ENSURE_EQUALS( "push_back failed", deque, proto );
				}
			for ( int p( 0 ); p < pack_; ++ p )
				{
				proto.pop_back();
				deque.pop_back();
				check_consistency( deque );
				ENSURE_EQUALS( "push_back failed", deque, proto );
				}
			}
		for ( i = 0; i < shift_; ++ i )
			{
			proto.pop_back();
			deque.pop_back();
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

template<int const item_size>
void tut_yaal_hcore_hdeque_4::test_roll_backward_greedy( int shift_, int distance_ )
	{
	clog << "testing roll backward greedy: " << item_size << ", " << shift_ << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_4, item_size> item_type;
	typedef HDeque<item_type> deque_type;
		{
		proto_t proto;
		deque_type deque;
		int i( 0 );
		for ( ; i < shift_; ++ i )
			{
			proto.push_front( i );
			deque.push_front( i );
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		while ( i < distance_ )
			{
			for ( int s( 0 ); s < shift_; ++ s )
				{
				proto.pop_back();
				deque.pop_back();
				check_consistency( deque );
				ENSURE_EQUALS( "push_back failed", deque, proto );
				}
			for ( int s( 0 ); s < shift_; ++ s, ++ i )
				{
				proto.push_front( i );
				deque.push_front( i );
				check_consistency( deque );
				ENSURE_EQUALS( "push_back failed", deque, proto );
				}
			}
		for ( i = 0; i < shift_; ++ i )
			{
			proto.pop_back();
			deque.pop_back();
			check_consistency( deque );
			ENSURE_EQUALS( "push_back failed", deque, proto );
			}
		}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	}

TUT_UNIT_TEST( 21, "roll backward (push_front/pop_back)" )
	int shift[] = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 32 };
	int pack[] = { 1, 2, 3, 4, 5, 7, 8 };
	int distance( 1024 );
	for ( int s( 0 ); s < countof ( shift ); ++ s )
		{
		for ( int p( 0 ); p < countof ( pack ); ++ p )
			{
			test_roll_backward<1>( shift[s], pack[p], distance );
			test_roll_backward<2>( shift[s], pack[p], distance );
			test_roll_backward<3>( shift[s], pack[p], distance );
			test_roll_backward<7>( shift[s], pack[p], distance );
			test_roll_backward<15>( shift[s], pack[p], distance );
			test_roll_backward<16>( shift[s], pack[p], distance );
			test_roll_backward<17>( shift[s], pack[p], distance );
			test_roll_backward<64>( shift[s], pack[p], distance );
			test_roll_backward<128>( shift[s], pack[p], distance );
			test_roll_backward<200>( shift[s], pack[p], distance );
			test_roll_backward<511>( shift[s], pack[p], distance );
			test_roll_backward<512>( shift[s], pack[p], distance );
			test_roll_backward<513>( shift[s], pack[p], distance );
			test_roll_backward<640>( shift[s], pack[p], distance );
			}
		}
	for ( int s( 0 ); s < countof ( shift ); ++ s )
		{
		test_roll_backward_greedy<1>( shift[s], distance );
		test_roll_backward_greedy<2>( shift[s], distance );
		test_roll_backward_greedy<3>( shift[s], distance );
		test_roll_backward_greedy<7>( shift[s], distance );
		test_roll_backward_greedy<15>( shift[s], distance );
		test_roll_backward_greedy<16>( shift[s], distance );
		test_roll_backward_greedy<17>( shift[s], distance );
		test_roll_backward_greedy<64>( shift[s], distance );
		test_roll_backward_greedy<128>( shift[s], distance );
		test_roll_backward_greedy<200>( shift[s], distance );
		test_roll_backward_greedy<511>( shift[s], distance );
		test_roll_backward_greedy<512>( shift[s], distance );
		test_roll_backward_greedy<513>( shift[s], distance );
		test_roll_backward_greedy<640>( shift[s], distance );
		}
TUT_TEARDOWN()

}


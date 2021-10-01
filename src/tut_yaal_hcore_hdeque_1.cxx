/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <deque>

#include "tut_yaal_hcore_hdeque.hxx"

#include <yaal/hcore/hdeque.hxx>
M_VCSID( "$Id: " __ID__ " $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
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

TUT_UNIT_TEST( "Constructor with range initialization." )
	item_t::set_start_id( 0 );
	deque_t deque( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	proto_t proto( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	check_consistency( deque );
	ENSURE_EQUALS( "range initialization failed", deque, proto );
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_1, 128> big_item_t;
	typedef HDeque<big_item_t> big_deque_t;
	big_deque_t big_deque( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
	check_consistency( deque );
	check_consistency( big_deque );
	ENSURE_EQUALS( "range initialization failed", big_deque, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with curly braces initializer" )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	deque_t deque( { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 } );
	ENSURE( "range initialization failed", safe_equal( deque.begin(), deque.end(), begin( a ), end( a ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Copy constructor." )
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

TUT_UNIT_TEST( "operator []" )
	item_t::set_start_id( 0 );
	deque_t deque( { 0, 1, 2, 3, 4, 5, 6 } );
	ENSURE_EQUALS( "access normal failed", deque[ 0 ], 0 );
	ENSURE_EQUALS( "access normal failed", deque[ 6 ], 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "at()" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	deque_t deque( { 0, 1, 2, 3, 4, 5, 6 } );
	ENSURE_EQUALS( "access normal failed", deque.at( 0 ), 0 );
	ENSURE_EQUALS( "access normal failed", deque.at( 6 ), 6 );
	ENSURE_EQUALS( "access from end failed", deque.at( -1 ), 6 );
	ENSURE_EQUALS( "access from end failed", deque.at( -SIZE ), 0 );
	ENSURE_THROW( "access beyond size succed", deque.at( SIZE ) = 0, HOutOfRangeException );
	ENSURE_THROW( "access with negative index succed", deque.at( - SIZE - 1 ) = 0, HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Operator bool." )
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
		deque_type deque( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
		check_consistency( deque );
		proto_t proto( _testData_[0], _testData_[0] + yaal::size( _testData_[0] ) );
		proto.erase( proto.begin() + first_, proto.begin() + last_ );
		deque.erase( deque.begin() + first_, deque.begin() + last_ );
		check_consistency( deque );
		ENSURE_EQUALS( "range initialization failed", deque, proto );
	}

	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
}

template<int const item_size>
void tut_yaal_hcore_hdeque_1::test_erase( void ) {
	test_erase<item_size>( 0, yaal::size( _testData_[0] ) / 2 );
	test_erase<item_size>( yaal::size( _testData_[0] ) / 2, yaal::size( _testData_[0] ) );
	test_erase<item_size>( 0, yaal::size( _testData_[0] ) );
	test_erase<item_size>( 0, 1 );
	test_erase<item_size>( yaal::size( _testData_[0] ) - 1, yaal::size( _testData_[0] ) );
	test_erase<item_size>( 1, yaal::size( _testData_[0] ) - 1 );
	test_erase<item_size>( 3, 6 );
	test_erase<item_size>( yaal::size( _testData_[0] ) - 6, yaal::size( _testData_[0] ) - 3 );
	test_erase<item_size>( yaal::size( _testData_[0] ) / 2 - 3, yaal::size( _testData_[0] ) / 2 + 3 );
	test_erase<item_size>( 0, yaal::size( _testData_[0] ) / 2 + yaal::size( _testData_[0] ) / 4 );
	test_erase<item_size>( 3, yaal::size( _testData_[0] ) / 2 + yaal::size( _testData_[0] ) / 4 );
	test_erase<item_size>( yaal::size( _testData_[0] ) / 4, yaal::size( _testData_[0] ) );
	test_erase<item_size>( yaal::size( _testData_[0] ) / 4, yaal::size( _testData_[0] ) - 3 );
	test_erase<item_size>( 5, 5 );
}

TUT_UNIT_TEST( "range erase" )
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

TUT_UNIT_TEST( "erase bug regression check" )
	typedef HInstanceTracker<tut_yaal_hcore_hdeque_1, 17> item_type;
	typedef HDeque<item_type> deque_type; {
		deque_type deque({1, 2, 3, 4, 5, 6, 7, 8, 9});
		proto_t proto({1, 2, 3, 4, 5, 6, 7, 8, 9});
		deque.erase( deque.begin() + 3, deque.begin() + 4 );
		proto.erase( proto.begin() + 3, proto.begin() + 4 );
		check_consistency( deque );
		ENSURE_EQUALS( "erase( k, k + 1) failed", deque, proto );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
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

TUT_UNIT_TEST( "roll forward (push_back/pop_front) insert erase" )
	int shift[] = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 32 };
	int pack[] = { 1, 2, 3, 4, 5, 7, 8 };
	int distance( 1024 );
	for ( int s( 0 ); s < yaal::size( shift ); ++ s ) {
		for ( int p( 0 ); p < yaal::size( pack ); ++ p ) {
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
	for ( int s( 0 ); s < yaal::size( shift ); ++ s ) {
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

TUT_UNIT_TEST( "emplace_back" )
	deque_t deque;
	item_t::reset();
	deque.emplace_back( 7 );
	check_consistency( deque );
	ENSURE_EQUALS( "emplace_back failed", deque[0], 7 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
	deque.emplace_back( 13 );
	ENSURE_EQUALS( "emplace_back failed", deque[0], 7 );
	ENSURE_EQUALS( "emplace_back failed", deque[1], 13 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "emplace_front" )
	deque_t deque;
	item_t::reset();
	deque.emplace_front( 7 );
	check_consistency( deque );
	ENSURE_EQUALS( "emplace_front failed", deque[0], 7 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
	deque.emplace_front( 13 );
	ENSURE_EQUALS( "emplace_front failed", deque[0], 13 );
	ENSURE_EQUALS( "emplace_front failed", deque[1], 7 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "emplace" )
	deque_t deque;
	item_t::reset();
	deque.emplace( deque.end(), 7 );
	check_consistency( deque );
	ENSURE_EQUALS( "emplace failed", deque[0], 7 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	ENSURE_EQUALS( "unnecessary move", item_t::get_move_count(), 0 );
	deque.emplace( deque.end(), 13 );
	ENSURE_EQUALS( "emplace failed", deque[0], 7 );
	ENSURE_EQUALS( "emplace failed", deque[1], 13 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
	deque.emplace( deque.begin() + 1, 42 );
	ENSURE_EQUALS( "emplace failed", deque[0], 7 );
	ENSURE_EQUALS( "emplace failed", deque[1], 42 );
	ENSURE_EQUALS( "emplace failed", deque[2], 13 );
	ENSURE_EQUALS( "unnecessary copy", item_t::get_copy_count(), 0 );
TUT_TEARDOWN()

}


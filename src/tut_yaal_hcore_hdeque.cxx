/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hdeque.cxx - this file is integral part of `tress' project.

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
#include <deque>

#include "tut_yaal_hcore_hdeque.hxx"

#include <yaal/hcore/hdeque.hxx>
M_VCSID( "$Id: " __ID__ " $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hdeque : public tut_yaal_hcore_hdeque_base<0> {
	virtual ~tut_yaal_hcore_hdeque( void ) {}
	template<int const item_size>
	void test_resize( void );
	template<int const item_size>
	void test_pop_back( void );
	template<int const item_size>
	void test_pop_front( void );
};

TUT_TEST_GROUP( tut_yaal_hcore_hdeque, "yaal::hcore::HDeque" );

TUT_UNIT_TEST( "CHUNK_SIZE, VALUES_PER_CHUNK and Constructor." )
	STATIC_ASSERT( sizeof ( FixedArray<1> ) == 1 );
	ENSURE_EQUALS( "2CHUNK_SIZE not optimal", HDeque<FixedArray<1> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<1> >::VALUES_PER_CHUNK, 512 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<2> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<2> >::VALUES_PER_CHUNK, 256 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<3> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<3> >::VALUES_PER_CHUNK, 171 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<4> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<4> >::VALUES_PER_CHUNK, 128 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<5> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<5> >::VALUES_PER_CHUNK, 102 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<6> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<6> >::VALUES_PER_CHUNK, 85 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<7> >::CHUNK_SIZE, 511 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<7> >::VALUES_PER_CHUNK, 73 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<8> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<8> >::VALUES_PER_CHUNK, 64 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<9> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<9> >::VALUES_PER_CHUNK, 57 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<10> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<10> >::VALUES_PER_CHUNK, 51 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<11> >::CHUNK_SIZE, 517 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<11> >::VALUES_PER_CHUNK, 47 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<12> >::CHUNK_SIZE, 516 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<12> >::VALUES_PER_CHUNK, 43 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<13> >::CHUNK_SIZE, 507 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<13> >::VALUES_PER_CHUNK, 39 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<14> >::CHUNK_SIZE, 518 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<14> >::VALUES_PER_CHUNK, 37 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<15> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<15> >::VALUES_PER_CHUNK, 34 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<16> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<16> >::VALUES_PER_CHUNK, 32 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<17> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<17> >::VALUES_PER_CHUNK, 30 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<18> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<18> >::VALUES_PER_CHUNK, 28 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<19> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<19> >::VALUES_PER_CHUNK, 27 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<20> >::CHUNK_SIZE, 520 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<20> >::VALUES_PER_CHUNK, 26 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<21> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<21> >::VALUES_PER_CHUNK, 24 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<22> >::CHUNK_SIZE, 506 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<22> >::VALUES_PER_CHUNK, 23 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<23> >::CHUNK_SIZE, 506 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<23> >::VALUES_PER_CHUNK, 22 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<24> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<24> >::VALUES_PER_CHUNK, 21 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<25> >::CHUNK_SIZE, 500 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<25> >::VALUES_PER_CHUNK, 20 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<26> >::CHUNK_SIZE, 520 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<26> >::VALUES_PER_CHUNK, 20 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<27> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<27> >::VALUES_PER_CHUNK, 19 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<28> >::CHUNK_SIZE, 504 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<28> >::VALUES_PER_CHUNK, 18 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<29> >::CHUNK_SIZE, 522 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<29> >::VALUES_PER_CHUNK, 18 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<30> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<30> >::VALUES_PER_CHUNK, 17 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<31> >::CHUNK_SIZE, 527 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<31> >::VALUES_PER_CHUNK, 17 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<32> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<32> >::VALUES_PER_CHUNK, 16 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<33> >::CHUNK_SIZE, 528 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<33> >::VALUES_PER_CHUNK, 16 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<34> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<34> >::VALUES_PER_CHUNK, 15 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<35> >::CHUNK_SIZE, 525 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<35> >::VALUES_PER_CHUNK, 15 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<255> >::CHUNK_SIZE, 510 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<255> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<256> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<256> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<257> >::CHUNK_SIZE, 514 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<257> >::VALUES_PER_CHUNK, 2 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<300> >::CHUNK_SIZE, 600 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<300> >::VALUES_PER_CHUNK, 2 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<340> >::CHUNK_SIZE, 680 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<340> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<341> >::CHUNK_SIZE, 682 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<341> >::VALUES_PER_CHUNK, 2 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<342> >::CHUNK_SIZE, 342 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<382> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<343> >::CHUNK_SIZE, 343 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<343> >::VALUES_PER_CHUNK, 1 );

	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<511> >::CHUNK_SIZE, 511 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<511> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<512> >::CHUNK_SIZE, 512 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<512> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<513> >::CHUNK_SIZE, 513 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<513> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<767> >::CHUNK_SIZE, 767 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<767> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<768> >::CHUNK_SIZE, 768 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<768> >::VALUES_PER_CHUNK, 1 );
	ENSURE_EQUALS( "CHUNK_SIZE not optimal", HDeque<FixedArray<769> >::CHUNK_SIZE, 769 );
	ENSURE_EQUALS( "VALUES_PER_CHUNK not optimal", HDeque<FixedArray<769> >::VALUES_PER_CHUNK, 1 );
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	ENSURE_THROW( "deque with negative size created", deque_t deque( BAD_SIZE ), HException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor and get_size()." ) {
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

TUT_UNIT_TEST( "Constructor with filling." )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	ENSURE_THROW( "deque with negative size created", deque_t badDeque( BAD_SIZE, FILLER_FOR_ARRAY ), HException );
	deque_t deque( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	check_consistency( deque );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "deque element not filled with default value", deque[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

template<int const item_size>
void tut_yaal_hcore_hdeque::test_resize( void ) {
	clog << "testing resize: " << item_size << endl;
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type; {
		deque_type deque;
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 1 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 2 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 7 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 15 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 16 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 17 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 64 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 128 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 64 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 17 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 16 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 15 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 7 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 2 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 1 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 33 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 33 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 33 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 3333 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 2 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( deque_type::VALUES_PER_CHUNK ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( deque_type::VALUES_PER_CHUNK + 1 ); );
		check_consistency( deque );
		TUT_INVOKE( deque.pop_front(); );
		check_consistency( deque );
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
		if ( deque_type::VALUES_PER_CHUNK > 1 ) {
			TUT_INVOKE( deque.resize( deque_type::VALUES_PER_CHUNK - 1 ); );
			check_consistency( deque );
			TUT_INVOKE( deque.pop_front(); );
			check_consistency( deque );
			TUT_INVOKE( deque.resize( 0 ); );
			check_consistency( deque );
		}
		TUT_INVOKE( deque.resize( 0 ); );
		check_consistency( deque );
	}
	ENSURE_EQUALS( "object leak", item_type::get_instance_count(), 0 );
	return;
}

TUT_UNIT_TEST( "resize" )
	TIME_CONSTRAINT_EXEMPT();
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

template<int const item_size>
void tut_yaal_hcore_hdeque::test_pop_back( void ) {
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing pop_back: " << item_size << endl; {
		deque_type deque( 2048 );
		check_consistency( deque );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( deque.begin(), deque.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i ) {
			proto.pop_back();
			deque.pop_back();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_back failed", deque, proto );
		}
		ENSURE_EQUALS( "not empty!", deque.is_empty(), true );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( "pop_back" )
	TIME_CONSTRAINT_EXEMPT();
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
void tut_yaal_hcore_hdeque::test_pop_front( void ) {
	typedef HInstanceTracker<tut_yaal_hcore_hdeque, item_size> item_type;
	typedef HDeque<item_type> deque_type;
	clog << "testing pop_front: " << item_size << endl; {
		deque_type deque( 2048 );
		check_consistency( deque );
		proto_t proto( 2048 );
		/* Bug in GCC 4.2.1 enforces namespace prefix here. */
		yaal::generate( deque.begin(), deque.end(), inc( 0 ) );
		yaal::generate( proto.begin(), proto.end(), inc( 0 ) );
		for ( int long i( 0 ); i < 2048; ++ i ) {
			proto.pop_front();
			deque.pop_front();
			check_consistency( deque );
			ENSURE_EQUALS( "pop_front failed", deque, proto );
		}
		ENSURE_EQUALS( "not empty!", deque.is_empty(), true );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
}

TUT_UNIT_TEST( "pop_front" )
	TIME_CONSTRAINT_EXEMPT();
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

TUT_UNIT_TEST( 50, "speed test" )
	TIME_CONSTRAINT_EXEMPT();
	typedef HDeque<int> deque_type;
	int long LOOPS( 1000000 );
	proto_t proto;
	deque_type deque;
	double long st( 0 );
	double long yt( 0 );
	/* std */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			proto.push_back( static_cast<int>( i ) );
		}
		clog << "*speed* std::deque<>::push_back() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	/* yaal */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			deque.push_back( static_cast<int>( i ) );
		}
		clog << "*speed* yaal::hcore::HDeque<>::push_back() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HDeque<>::push_back() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	/* std */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			proto.pop_back();
		}
		clog << "*speed* std::deque<>::pop_back() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	/* yaal */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			deque.pop_back();
		}
		clog << "*speed* yaal::hcore::HDeque<>::pop_back() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HDeque<>::pop_back() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	/* std */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			proto.push_front( static_cast<int>( i ) );
		}
		clog << "*speed* std::deque<>::push_front() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	/* yaal */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			deque.push_front( static_cast<int>( i ) );
		}
		clog << "*speed* yaal::hcore::HDeque<>::push_front() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HDeque<>::push_front() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	/* std */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			proto.pop_front();
		}
		clog << "*speed* std::deque<>::pop_front() = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	/* yaal */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			deque.pop_front();
		}
		clog << "*speed* yaal::hcore::HDeque<>::pop_front() = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HDeque<>::pop_front() result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
/* erase */
	for ( int long i( 0 ); i < LOOPS; ++ i ) {
		proto.push_back( static_cast<int>( i ) );
	}
	for ( int long i( 0 ); i < LOOPS; ++ i ) {
		deque.push_back( static_cast<int>( i ) );
	}
	/* std */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			proto.erase( proto.end() - 1 );
		}
		clog << "*speed* std::deque<>::erase() back = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	/* yaal */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			deque.erase( deque.end() - 1 );
		clog << "*speed* yaal::hcore::HDeque<>::erase() back = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HDeque<>::erase() back result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	for ( int long i( 0 ); i < LOOPS; ++ i ) {
		proto.push_front( static_cast<int>( i ) );
	}
	for ( int long i( 0 ); i < LOOPS; ++ i ) {
		deque.push_front( static_cast<int>( i ) );
	}
	/* std */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.erase( proto.begin() );
		clog << "*speed* std::deque<>::erase() front = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	/* yaal */ {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i ) {
			deque.erase( deque.begin() );
		}
		clog << "*speed* yaal::hcore::HDeque<>::erase() front = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) ) << endl;
	}
	clog << "*speed* HDeque<>::erase() front = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
TUT_TEARDOWN()

}


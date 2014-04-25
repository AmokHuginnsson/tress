/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hpool.cxx - this file is integral part of `tress' project.

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

#define private public

#include <TUT/tut.hpp>

#include <yaal/hcore/hpool.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/hrandomizer.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hpool : public simple_mock<tut_yaal_hcore_hpool> {
	typedef simple_mock<tut_yaal_hcore_hpool> base_type;
	typedef HPool<int> pool_t;
	typedef HArray<int*> log_t;
	typedef HArray<log_t> logs_t;
	virtual ~tut_yaal_hcore_hpool( void ) {}
	template <typename T>
	void check_consistency( HPool<T>& );
};

template <typename T>
void tut_yaal_hcore_hpool::check_consistency( HPool<T>& pool_ ) {
	ENSURE( "inconsistent blocks-count - blocks-capacity relation", pool_._poolBlockCount <= pool_._poolBlockCapacity );
	ENSURE( "inconsistent free - blocks-count relation", pool_._free < pool_._poolBlockCount );
	ENSURE( "inconsistent buffer state", ( ( pool_._poolBlocks == NULL ) && ( pool_._poolBlockCapacity == 0 ) ) || ( ( pool_._poolBlockCapacity > 0 ) && ( pool_._poolBlocks != NULL ) ) );
	bool freeFound( false );
	HArray<bool> exists( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_._poolBlockCount; ++ i ) {
		typename pool_t::HPoolBlock* pb( pool_._poolBlocks[i] );
		ENSURE( "null pool block", pb != NULL );
		ENSURE_EQUALS( "bad block index", pb->_index, i );
		if ( freeFound )
			ENSURE_NOT( "pool blocks out of order", pb->_used == pool_t::OBJECTS_PER_BLOCK );
		if ( ! freeFound && ( pb->_used < pool_t::OBJECTS_PER_BLOCK ) ) {
			freeFound = true;
			ENSURE_EQUALS( "inconsistent free index", pool_._free, i );
		}
		ENSURE( "invalid used", ( pb->_used >= 0 ) && ( pb->_used <= pool_t::OBJECTS_PER_BLOCK ) );
		if ( pb->_used < pool_t::OBJECTS_PER_BLOCK ) {
			int idx( pb->_free );
			fill( exists.begin(), exists.end(), false );
			int free( pool_t::OBJECTS_PER_BLOCK - pb->_used );
			for ( int k( 0 ); k < ( free - 1 ); ++ k ) {
				idx = *( reinterpret_cast<char unsigned*>( pb->_mem ) + ( idx * pool_t::OBJECT_SPACE ) );
				ENSURE( "bad free list", ! exists[idx] );
				exists[idx] = true;
			}
		}
	}
}

TUT_TEST_GROUP( tut_yaal_hcore_hpool, "yaal::hcore::HPool" );

TUT_UNIT_TEST( 1, "object space size" )
/* First test if tut_helpers::Sizer works as intentded. */
	STATIC_ASSERT( sizeof ( Sizer<1> ) == 1 );
	STATIC_ASSERT( sizeof ( Sizer<2> ) == 2 );
	STATIC_ASSERT( sizeof ( Sizer<3> ) == 3 );
	STATIC_ASSERT( sizeof ( Sizer<4> ) == 4 );
	STATIC_ASSERT( sizeof ( Sizer<5> ) == 5 );
	STATIC_ASSERT( sizeof ( Sizer<6> ) == 6 );
	STATIC_ASSERT( sizeof ( Sizer<7> ) == 7 );
	STATIC_ASSERT( sizeof ( Sizer<8> ) == 8 );
	STATIC_ASSERT( sizeof ( Sizer<9> ) == 9 );
	STATIC_ASSERT( sizeof ( Sizer<10> ) == 10 );
	STATIC_ASSERT( sizeof ( Sizer<11> ) == 11 );
	STATIC_ASSERT( sizeof ( Sizer<12> ) == 12 );
	STATIC_ASSERT( sizeof ( Sizer<13> ) == 13 );
	STATIC_ASSERT( sizeof ( Sizer<14> ) == 14 );
	STATIC_ASSERT( sizeof ( Sizer<15> ) == 15 );
	STATIC_ASSERT( sizeof ( Sizer<16> ) == 16 );
	STATIC_ASSERT( sizeof ( Sizer<17> ) == 17 );
	STATIC_ASSERT( sizeof ( Sizer<18> ) == 18 );
	STATIC_ASSERT( sizeof ( Sizer<19> ) == 19 );
	STATIC_ASSERT( sizeof ( Sizer<20> ) == 20 );
/* tut_helpers::Sizer works as intentded. */
	ENSURE_EQUALS( "bad object space size of char", HPool<char>::OBJECT_SPACE, 2 );
	ENSURE_EQUALS( "bad object space size of char", HPool<short>::OBJECT_SPACE, 4 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<3> >::OBJECT_SPACE, 4 );
	ENSURE_EQUALS( "bad object space size of char", HPool<int>::OBJECT_SPACE, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<5> >::OBJECT_SPACE, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<6> >::OBJECT_SPACE, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<7> >::OBJECT_SPACE, 8 );
#if TARGET_CPU_BITS == 64
	ENSURE_EQUALS( "bad object space size of char", HPool<int long long>::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<9> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<10> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<11> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<12> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<13> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<14> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<15> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<16> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<18> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<19> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<20> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<21> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<22> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<23> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<24> >::OBJECT_SPACE, 32 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<25> >::OBJECT_SPACE, 32 );
#elif TARGET_CPU_BITS == 32 /* #if TARGET_CPU_BITS == 64 */
	ENSURE_EQUALS( "bad object space size of char", HPool<int long long>::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<9> >::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<10> >::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<11> >::OBJECT_SPACE, 12 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<12> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<13> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<14> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<15> >::OBJECT_SPACE, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<16> >::OBJECT_SPACE, 20 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<18> >::OBJECT_SPACE, 20 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<19> >::OBJECT_SPACE, 20 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<20> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<21> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<22> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<23> >::OBJECT_SPACE, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<24> >::OBJECT_SPACE, 28 );
	ENSURE_EQUALS( "bad object space size of char", HPool<Sizer<25> >::OBJECT_SPACE, 28 );
#else /* #elif TARGET_CPU_BITS == 32 #if TARGET_CPU_BITS == 64 */
#error Unsupported CPU bitness.
#endif /* #else #elif TARGET_CPU_BITS == 32 #if TARGET_CPU_BITS == 64 */
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "constructor" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad pool block count after construction", p._poolBlockCount, 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "allocate one, deallocate, and allocate again" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	/*
	 * Make sure that we do not free the only free block we have.
	 */
	ENSURE_EQUALS( "allocation after deallocation failed", p.alloc(), p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "allocate second pool block" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( p0 );
	check_consistency( p );
	/*
	 * Make sure that we do not free the only free block we have.
	 */
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	ENSURE_EQUALS( "allocation after deallocation failed", p.alloc(), p0 );
	check_consistency( p );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "allocate second pool block, free first" )
	pool_t p;
	log_t allocated( pool_t::OBJECTS_PER_BLOCK );
	check_consistency( p );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocated[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( p0 );
	check_consistency( p );
	/*
	 * Make sure that we do not free the only free block we have.
	 */
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	ENSURE_EQUALS( "allocation after deallocation failed", p.alloc(), p0 );
	check_consistency( p );
	p.free( allocated[0] );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	check_consistency( p );
	for ( int i( 1 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocated[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "allocate full block, free in random order, reallocate full block" )
	pool_t p;
	log_t allocated( pool_t::OBJECTS_PER_BLOCK );
	log_t freeOrder( pool_t::OBJECTS_PER_BLOCK );
	check_consistency( p );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocated[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	HRandomizer r( randomizer_helper::make_randomizer() );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		int toFreeCount( ( pool_t::OBJECTS_PER_BLOCK - 1 ) - i );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		int* toFree( allocated[ toFreeIdx ] );
		freeOrder[i] = toFree;
		allocated.erase( allocated.begin() + toFreeIdx );
		p.free( toFree );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocated.push_back( p.alloc() );
		check_consistency( p );
	}
	reverse( allocated.begin(), allocated.end() );
	ENSURE_EQUALS( "bad free list", allocated, freeOrder );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "allocate 16 blocks, free odd elements in all of them, than free rest" )
	pool_t p;
	check_consistency( p );
	int workWith( pool_t::OBJECTS_PER_BLOCK * 16 );
	log_t allocated( workWith );
	for ( int i( 0 ); i < workWith; ++ i ) {
		allocated[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 16 );
	for ( int i( 0 ); i < workWith; i += 2 ) {
		p.free( allocated[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 16 );
	for ( int i( 1 ); i < workWith; i += 2 ) {
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, 16 - i / pool_t::OBJECTS_PER_BLOCK );
		p.free( allocated[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "alloc 3 blocks, free third, make room in second" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "alloc 3 blocks, make room in second, free third" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "alloc 3 blocks, make room in first, free third" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB0[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "alloc 3 blocks, make room in first, free second" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.alloc();
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB0[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "alloc 3 blocks, make room in second, free first" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.alloc();
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "alloc 3 blocks, free first, free second" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.alloc();
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "alloc 3 blocks, free second, free first" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.alloc();
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "alloc 3 blocks, free third, free first" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "alloc 3 blocks, free third, make room in second, free first" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "alloc 3 blocks, free third, make room in first, free second" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB0[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "alloc 3 blocks, free second, make room in first, free third" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( allocatedB0[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 19, "alloc 3 blocks, free first, make room in second, free third" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( allocatedB1[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "allocate two full blocks, free second in random order, reallocate full block" )
	pool_t p;
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	log_t freeOrder( pool_t::OBJECTS_PER_BLOCK );
	check_consistency( p );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	HRandomizer r( randomizer_helper::make_randomizer() );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		int toFreeCount( ( pool_t::OBJECTS_PER_BLOCK - 1 ) - i );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		int* toFree( allocatedB1[ toFreeIdx ] );
		freeOrder[i] = toFree;
		allocatedB1.erase( allocatedB1.begin() + toFreeIdx );
		p.free( toFree );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1.push_back( p.alloc() );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	reverse( allocatedB1.begin(), allocatedB1.end() );
	ENSURE_EQUALS( "bad free list", allocatedB1, freeOrder );
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "allocate 3 blocks, free all but one in first and second in random order, reallocate to full blocks" )
	pool_t p;
	log_t allocatedB0( pool_t::OBJECTS_PER_BLOCK );
	log_t allocatedB1( pool_t::OBJECTS_PER_BLOCK );
	log_t freeOrderB0( pool_t::OBJECTS_PER_BLOCK - 1 );
	log_t freeOrderB1( pool_t::OBJECTS_PER_BLOCK - 1 );
	check_consistency( p );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB0[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocatedB1[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	int* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	HRandomizer r( randomizer_helper::make_randomizer() );
	for ( int i( 0 ); i < ( pool_t::OBJECTS_PER_BLOCK - 1 ); ++ i ) {
		int toFreeCount( ( pool_t::OBJECTS_PER_BLOCK - 1 ) - i );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		int* toFree( allocatedB0[ toFreeIdx ] );
		freeOrderB0[i] = toFree;
		allocatedB0.erase( allocatedB0.begin() + toFreeIdx );
		p.free( toFree );
		check_consistency( p );
		toFreeIdx = ( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		toFree = allocatedB1[ toFreeIdx ];
		freeOrderB1[i] = toFree;
		allocatedB1.erase( allocatedB1.begin() + toFreeIdx );
		p.free( toFree );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	allocatedB0.clear();
	allocatedB1.clear();
	for ( int i( 0 ); i < ( pool_t::OBJECTS_PER_BLOCK - 1 ); ++ i ) {
		allocatedB1.push_back( p.alloc() );
		check_consistency( p );
	}
	for ( int i( 0 ); i < ( pool_t::OBJECTS_PER_BLOCK - 1 ); ++ i ) {
		allocatedB0.push_back( p.alloc() );
		check_consistency( p );
	}
	reverse( allocatedB0.begin(), allocatedB0.end() );
	reverse( allocatedB1.begin(), allocatedB1.end() );
	ENSURE_EQUALS( "bad free list b0", allocatedB0, freeOrderB0 );
	ENSURE_EQUALS( "bad free list b1", allocatedB1, freeOrderB1 );
	p.free( allocatedB0[0] );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "make N full blocks, make room in all of them in random order" )
	static int const N( 16 );
	log_t representants( N );
	pool_t p;
	for ( int b( 0 ); b < N; ++ b ) {
		representants[b] = p.alloc();
		check_consistency( p );
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b + 1 );
		for ( int i( 0 ); i < ( pool_t::OBJECTS_PER_BLOCK - 1 ); ++ i ) {
			p.alloc();
			check_consistency( p );
		}
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b + 1 );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, N );
	HRandomizer r( randomizer_helper::make_randomizer() );
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		p.free( representants[toFreeIdx] );
		representants.erase( representants.begin() + toFreeIdx );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, N );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "make N full blocks, free them in random order" )
	static int const N( 16 );
	logs_t allocated( N );
	pool_t p;
	for ( int b( 0 ); b < N; ++ b ) {
		allocated[b].resize( pool_t::OBJECTS_PER_BLOCK );
		for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
			allocated[b][i] = p.alloc();
			check_consistency( p );
		}
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b + 1 );
	}
	HRandomizer r( randomizer_helper::make_randomizer() );
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
			p.free( allocated[toFreeIdx][i] );
			check_consistency( p );
		}
		allocated.erase( allocated.begin() + toFreeIdx );
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, N - b );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "make N full blocks, make room in them in random order, free them in random order" )
	static int const N( 16 );
	logs_t allocated( N );
	log_t representants( N );
	pool_t p;
	for ( int b( 0 ); b < N; ++ b ) {
		allocated[b].resize( pool_t::OBJECTS_PER_BLOCK );
		for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
			allocated[b][i] = p.alloc();
			check_consistency( p );
		}
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b + 1 );
	}
	HRandomizer r( randomizer_helper::make_randomizer() );
	for ( int b( 0 ); b < N; ++ b )
		representants[b] = allocated[b][0];
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		p.free( representants[toFreeIdx] );
		representants.erase( representants.begin() + toFreeIdx );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, N );
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r( static_cast<u64_t>( toFreeCount ) ) ) : 0 );
		for ( int i( 1 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
			p.free( allocated[toFreeIdx][i] );
			check_consistency( p );
		}
		allocated.erase( allocated.begin() + toFreeIdx );
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b < ( N - 1 ) ? ( N - b ) - 1 : 1 );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

}


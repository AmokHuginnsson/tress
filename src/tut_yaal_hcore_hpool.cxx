/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <sstream>

#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wkeyword-macro"
#define private public
#pragma GCC diagnostic error "-Wkeyword-macro"
#pragma GCC diagnostic error "-Wpragmas"

#include <TUT/tut.hpp>

#include <yaal/hcore/hpool.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/random.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::random;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hpool : public simple_mock<tut_yaal_hcore_hpool> {
	typedef simple_mock<tut_yaal_hcore_hpool> base_type;
	typedef HPool<sizeof ( int )> pool_t;
	typedef HArray<void*> log_t;
	typedef HArray<log_t> logs_t;
	virtual ~tut_yaal_hcore_hpool( void ) {}
	template <int const size>
	void check_consistency( HPool<size>& );
	int gc( pool_t&, void**, int );
};

template <int const size>
void tut_yaal_hcore_hpool::check_consistency( HPool<size>& pool_ ) {
	ENSURE( "inconsistent blocks-count - blocks-capacity relation", pool_._poolBlockCount <= pool_._poolBlockCapacity );
	ENSURE( "inconsistent free - blocks-count relation", pool_._free < pool_._poolBlockCount );
	ENSURE( "inconsistent buffer state", ( ( pool_._poolBlocks == nullptr ) && ( pool_._poolBlockCapacity == 0 ) ) || ( ( pool_._poolBlockCapacity > 0 ) && ( pool_._poolBlocks != nullptr ) ) );
	bool freeFound( false );
	HArray<bool> exists( pool_t::OBJECTS_PER_BLOCK );
	for ( int i( 0 ); i < pool_._poolBlockCount; ++ i ) {
		typename pool_t::HPoolBlock* pb( pool_._poolBlocks[i] );
		ENSURE( "null pool block", pb != nullptr );
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

TUT_UNIT_TEST( "object space size" )
/* First test if tut_helpers::Sizer works as intentded. */
	static_assert( sizeof ( Sizer<1> ) == 1, "tut_helpers::sizer<1> failed" );
	static_assert( sizeof ( Sizer<2> ) == 2, "tut_helpers::sizer<2> failed" );
	static_assert( sizeof ( Sizer<3> ) == 3, "tut_helpers::sizer<3> failed" );
	static_assert( sizeof ( Sizer<4> ) == 4, "tut_helpers::sizer<4> failed" );
	static_assert( sizeof ( Sizer<5> ) == 5, "tut_helpers::sizer<5> failed" );
	static_assert( sizeof ( Sizer<6> ) == 6, "tut_helpers::sizer<6> failed" );
	static_assert( sizeof ( Sizer<7> ) == 7, "tut_helpers::sizer<7> failed" );
	static_assert( sizeof ( Sizer<8> ) == 8, "tut_helpers::sizer<8> failed" );
	static_assert( sizeof ( Sizer<9> ) == 9, "tut_helpers::sizer<9> failed" );
	static_assert( sizeof ( Sizer<10> ) == 10, "tut_helpers::sizer<10> failed" );
	static_assert( sizeof ( Sizer<11> ) == 11, "tut_helpers::sizer<11> failed" );
	static_assert( sizeof ( Sizer<12> ) == 12, "tut_helpers::sizer<12> failed" );
	static_assert( sizeof ( Sizer<13> ) == 13, "tut_helpers::sizer<13> failed" );
	static_assert( sizeof ( Sizer<14> ) == 14, "tut_helpers::sizer<14> failed" );
	static_assert( sizeof ( Sizer<15> ) == 15, "tut_helpers::sizer<15> failed" );
	static_assert( sizeof ( Sizer<16> ) == 16, "tut_helpers::sizer<16> failed" );
	static_assert( sizeof ( Sizer<17> ) == 17, "tut_helpers::sizer<17> failed" );
	static_assert( sizeof ( Sizer<18> ) == 18, "tut_helpers::sizer<18> failed" );
	static_assert( sizeof ( Sizer<19> ) == 19, "tut_helpers::sizer<19> failed" );
	static_assert( sizeof ( Sizer<20> ) == 20, "tut_helpers::sizer<20> failed" );
/* tut_helpers::Sizer works as intentded. */
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( char )>::OBJECT_SPACE + 0, 2 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( short )>::OBJECT_SPACE + 0, 4 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<3> )>::OBJECT_SPACE + 0, 4 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( int )>::OBJECT_SPACE + 0, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<5> )>::OBJECT_SPACE + 0, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<6> )>::OBJECT_SPACE + 0, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<7> )>::OBJECT_SPACE + 0, 8 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( int long long )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<9> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<10> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<11> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<12> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<13> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<14> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<15> )>::OBJECT_SPACE + 0, 16 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<16> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<18> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<19> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<20> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<21> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<22> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<23> )>::OBJECT_SPACE + 0, 24 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<24> )>::OBJECT_SPACE + 0, 32 );
	ENSURE_EQUALS( "bad object space size of char", HPool<sizeof ( Sizer<25> )>::OBJECT_SPACE + 0, 32 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "constructor" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad pool block count after construction", p._poolBlockCount, 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate one, deallocate, and allocate again" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	void* p0( p.alloc() );
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
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate second pool block" )
	pool_t p;
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 0 );
	log_t log;
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		log.push_back( p.alloc() );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	void* p0( p.alloc() );
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
	p.free( p0 );
	for ( void* v : log ) {
		p.free( v );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate second pool block, free first" )
	pool_t p;
	log_t allocated( pool_t::OBJECTS_PER_BLOCK );
	check_consistency( p );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocated[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	void* p0( p.alloc() );
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
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate full block, free in random order, reallocate full block" )
	pool_t p;
	log_t allocated( pool_t::OBJECTS_PER_BLOCK );
	log_t freeOrder( pool_t::OBJECTS_PER_BLOCK );
	check_consistency( p );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		allocated[i] = p.alloc();
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	distribution::HDiscrete r( rng_helper::make_random_number_generator() );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		int toFreeCount( ( pool_t::OBJECTS_PER_BLOCK - 1 ) - i );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( static_cast<u64_t>( r() ) % static_cast<u64_t>( toFreeCount ) ) : 0 );
		void* toFree( allocated[ toFreeIdx ] );
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
	yaal::reverse( allocated.begin(), allocated.end() );
	ENSURE_EQUALS( "bad free list", allocated, freeOrder );
	for ( void* v : allocated ) {
		p.free( v );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate 16 blocks, free odd elements in all of them, than free rest" )
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

TUT_UNIT_TEST( "alloc 3 blocks, free third, make room in second" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	allocatedB1.erase( allocatedB1.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, make room in second, free third" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	allocatedB1.erase( allocatedB1.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, make room in first, free third" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB0[0] );
	allocatedB0.erase( allocatedB0.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, make room in first, free second" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB0[0] );
	allocatedB0.erase( allocatedB0.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, make room in second, free first" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	allocatedB1.erase( allocatedB1.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free first, free second" )
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
	void* p0( p.alloc() );
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
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free second, free first" )
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
	void* p0( p.alloc() );
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
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free third, free first" )
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
	void* p0( p.alloc() );
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
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free third, make room in second, free first" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB1[0] );
	allocatedB1.erase( allocatedB1.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free third, make room in first, free second" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( allocatedB0[0] );
	allocatedB0.erase( allocatedB0.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free second, make room in first, free third" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB1[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( allocatedB0[0] );
	allocatedB0.erase( allocatedB0.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alloc 3 blocks, free first, make room in second, free third" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		p.free( allocatedB0[i] );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( allocatedB1[0] );
	allocatedB1.erase( allocatedB1.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate two full blocks, free second in random order, reallocate full block" )
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
	distribution::HDiscrete r( rng_helper::make_random_number_generator() );
	for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
		int toFreeCount( ( pool_t::OBJECTS_PER_BLOCK - 1 ) - i );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( static_cast<u64_t>( r() ) % static_cast<u64_t>( toFreeCount ) ) : 0 );
		void* toFree( allocatedB1[ toFreeIdx ] );
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
	yaal::reverse( allocatedB1.begin(), allocatedB1.end() );
	ENSURE_EQUALS( "bad free list", allocatedB1, freeOrder );
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocate 3 blocks, free all but one in first and second in random order, reallocate to full blocks" )
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
	void* p0( p.alloc() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	distribution::HDiscrete r( rng_helper::make_random_number_generator() );
	for ( int i( 0 ); i < ( pool_t::OBJECTS_PER_BLOCK - 1 ); ++ i ) {
		int toFreeCount( ( pool_t::OBJECTS_PER_BLOCK - 1 ) - i );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( static_cast<u64_t>( r() ) % static_cast<u64_t>( toFreeCount ) ) : 0 );
		void* toFree( allocatedB0[ toFreeIdx ] );
		freeOrderB0[i] = toFree;
		allocatedB0.erase( allocatedB0.begin() + toFreeIdx );
		p.free( toFree );
		check_consistency( p );
		toFreeIdx = ( toFreeCount > 0 ? static_cast<int>( r() % static_cast<i64_t>( toFreeCount ) ) : 0 );
		toFree = allocatedB1[ toFreeIdx ];
		freeOrderB1[i] = toFree;
		allocatedB1.erase( allocatedB1.begin() + toFreeIdx );
		p.free( toFree );
		check_consistency( p );
	}
	void* b0( allocatedB0[0] );
	void* b1( allocatedB1[0] );
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
	yaal::reverse( allocatedB0.begin(), allocatedB0.end() );
	yaal::reverse( allocatedB1.begin(), allocatedB1.end() );
	ENSURE_EQUALS( "bad free list b0", allocatedB0, freeOrderB0 );
	ENSURE_EQUALS( "bad free list b1", allocatedB1, freeOrderB1 );
	p.free( allocatedB0[0] );
	allocatedB0.erase( allocatedB0.begin() );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 3 );
	p.free( p0 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 2 );
	for ( void* v : allocatedB1 ) {
		p.free( v );
		check_consistency( p );
	}
	for ( void* v : allocatedB0 ) {
		p.free( v );
		check_consistency( p );
	}
	p.free( b0 );
	check_consistency( p );
	p.free( b1 );
	check_consistency( p );
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "make N full blocks, make room in all of them in random order" )
	static int const N( 16 );
	log_t representants( N );
	log_t log;
	pool_t p;
	for ( int b( 0 ); b < N; ++ b ) {
		representants[b] = p.alloc();
		check_consistency( p );
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b + 1 );
		for ( int i( 0 ); i < ( pool_t::OBJECTS_PER_BLOCK - 1 ); ++ i ) {
			log.push_back( p.alloc() );
			check_consistency( p );
		}
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b + 1 );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, N );
	distribution::HDiscrete r( rng_helper::make_random_number_generator() );
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r() % static_cast<i64_t>( toFreeCount ) ) : 0 );
		p.free( representants[toFreeIdx] );
		representants.erase( representants.begin() + toFreeIdx );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, N );
	for ( void* v : log ) {
		p.free( v );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "make N full blocks, free them in random order" )
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
distribution::HDiscrete r( rng_helper::make_random_number_generator() );
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r() % static_cast<i64_t>( toFreeCount ) ) : 0 );
		for ( int i( 0 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
			p.free( allocated[toFreeIdx][i] );
			check_consistency( p );
		}
		allocated.erase( allocated.begin() + toFreeIdx );
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, N - b );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "make N full blocks, make room in them in random order, free them in random order" )
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
	distribution::HDiscrete r( rng_helper::make_random_number_generator() );
	for ( int b( 0 ); b < N; ++ b )
		representants[b] = allocated[b][0];
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r() % static_cast<i64_t>( toFreeCount ) ) : 0 );
		p.free( representants[toFreeIdx] );
		representants.erase( representants.begin() + toFreeIdx );
		check_consistency( p );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, N );
	for ( int b( 0 ); b < N; ++ b ) {
		int toFreeCount( ( N - 1 ) - b );
		int toFreeIdx( toFreeCount > 0 ? static_cast<int>( r() % static_cast<i64_t>( toFreeCount ) ) : 0 );
		for ( int i( 1 ); i < pool_t::OBJECTS_PER_BLOCK; ++ i ) {
			p.free( allocated[toFreeIdx][i] );
			check_consistency( p );
		}
		allocated.erase( allocated.begin() + toFreeIdx );
		ENSURE_EQUALS( "bad block count", p._poolBlockCount, b < ( N - 1 ) ? ( N - b ) - 1 : 1 );
	}
	ENSURE_EQUALS( "bad block count", p._poolBlockCount, 1 );
TUT_TEARDOWN()

int tut_yaal_hcore_hpool::gc( pool_t& p_, void** data_, int size_ ) {
	int_array_t vals;
	for ( int i( 0 ); i < size_; ++ i ) {
		vals.push_back( *static_cast<int*>( data_[i] ) );
		p_.free( data_[i] );
	}
	sort( vals.begin(), vals.end() );
	ENSURE( "bad data in gc store", equal( vals.begin(), vals.end(), begin( _testData_[0] ) ) );
	return ( size_ );
}

TUT_UNIT_TEST( "garbage collection" )
	pool_t p;
	static int const ALLOC_COUNT( 1000 );
	log_t nums( ALLOC_COUNT );
	for ( int i( 0 ); i < ALLOC_COUNT; ++ i ) {
		nums[i] = p.alloc();
		*static_cast<int*>( nums[i] ) = i;
	}
	for ( int i( 0 ); i < ALLOC_COUNT; ++ i ) {
		if ( find( begin( _testData_[0] ), end( _testData_[0] ), i ) == end( _testData_[0] ) ) {
			p.free( nums[i] );
		}
	}
	p.run_gc( call( &tut_yaal_hcore_hpool::gc, this, ref( p ), _1, _2 ) );
TUT_TEARDOWN()

}


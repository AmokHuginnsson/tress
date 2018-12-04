/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <vector>

#include <TUT/tut.hpp>

#include <yaal/hcore/hstaticarray.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hstaticarray : public simple_mock<tut_yaal_hcore_hstaticarray> {
	typedef std::vector<int> proto_t;
	~tut_yaal_hcore_hstaticarray( void ) {}
	void test_erase( int, int );
};

TUT_TEST_GROUP( tut_yaal_hcore_hstaticarray, "yaal::hcore::HStaticArray" );

TUT_UNIT_TEST( "Constructor and get_size()." )
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	HStaticArray<item_t, SIZE_FOR_ONE> one;
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	HStaticArray<item_t, SIZE_FOR_TWO> two;
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE + SIZE_FOR_TWO );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", two.get_size(), SIZE_FOR_TWO );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with filling." )
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	HStaticArray<item_t, SIZE_FOR_ARRAY> array( FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "array element not filled with default value", array[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with range initialization." )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 ); {
		HStaticArray<item_t, yaal::size( a )> array( begin( a ), end( a ) );
		ENSURE( "range initialization failed", safe_equal( array.begin(), array.end(), begin( a ), end( a ) ) );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with initializer list." )
	int a[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 ); {
		HStaticArray<item_t, yaal::size( a )> array( { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 } );
		ENSURE( "range initialization failed", safe_equal( array.begin(), array.end(), begin( a ), end( a ) ) );
	}
	ENSURE_EQUALS( "object leak!", item_t::get_instance_count(), 0 );
	typedef HStaticArray<item_t, yaal::size( a )> static_array_t;
	typedef HExceptionT<static_array_t> StaticArrayException;
	ENSURE_THROW( "bad initializer size succeeded", (static_array_t( { 1, 2, 3 } )), StaticArrayException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Copy constructor." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	HStaticArray<item_t, SIZE> array;
	for ( int i = 0; i < SIZE; ++ i )
		array [ i ] = i;
	HStaticArray<item_t, SIZE> copy( array );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i ) {
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "at()" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	typedef HStaticArray<item_t, SIZE> static_array_t;
	typedef HExceptionT<static_array_t> StaticArrayException;
	static_array_t array;
	array.at( 1 ) = 100;
	array.at( -1 ) = -100;
	ENSURE_THROW( "access beyond size succed", array.at( SIZE ) = 0, StaticArrayException );
	ENSURE_THROW( "access with negative index succed", array.at( - SIZE - 1 ) = 0, StaticArrayException );
	ENSURE_EQUALS( "at() failed", array, static_array_t{ 0, 100, 2, 3, 4, 5, -100 } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Operator [ ]." )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	typedef HStaticArray<item_t, SIZE> static_array_t;
	static_array_t array;
	array[1] = 100;
	array[6] = 600;
	ENSURE_EQUALS( "at() failed", array, static_array_t{ 0, 100, 2, 3, 4, 5, 600 } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_empty()" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	HStaticArray<item_t, 0> empty;
	ENSURE_EQUALS( "test for array emptiness failed", empty.is_empty(), true );
	HStaticArray<item_t, SIZE> normal;
	ENSURE_EQUALS( "test for array fullness failed", normal.is_empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign operator (=)" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	item_t::set_start_id( 0 );
	HStaticArray<item_t, yaal::size( a0 )> array( begin( a0 ), end( a0 ) );
	HStaticArray<item_t, yaal::size( a0 )> other( -1 );
	other = array;
	ENSURE_EQUALS( "assgin failed", array, other );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	int a0[] = { 36, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 36 };
	int a1[] = { 37, 12, 234, 29, 6, 5, 326, 149, 654, 12, 10, 306 };
	item_t::set_start_id( 0 );
	HStaticArray<item_t, yaal::size( a0 )> sa0( a0, yaal::size( a0 ) );
	HStaticArray<item_t, yaal::size( a0 )> t( a0, yaal::size( a0 ) );
	ENSURE_EQUALS( "init failed", sa0, t );
	HStaticArray<item_t, yaal::size( a0 )> sa1( a1, yaal::size( a1 ) );
	t.assign( a1, yaal::size( a1 ) );
	ENSURE_EQUALS( "init failed", sa1, t );
	sa0.swap( sa1 );
	ENSURE_EQUALS( "swap failed", sa0, t );
	t.assign( a0, yaal::size( a0 ) );
	ENSURE_EQUALS( "swap failed", sa1, t );
TUT_TEARDOWN()

}


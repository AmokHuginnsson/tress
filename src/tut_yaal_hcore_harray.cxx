/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_harray.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_harray
	{
	typedef HInstanceTracker<tut_yaal_hcore_harray> item_t;
	typedef HArray<item_t> array_t;
	virtual ~tut_yaal_hcore_harray( void ) {}
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_harray, "yaal::hcore::HArray" );

TUT_UNIT_TEST_N( 1, "/* Constructor. */" )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	try
		{
		array_t array( BAD_SIZE );
		FAIL( "array with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Constructor and get_size(). */" )
	item_t::set_start_id( 0 );
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	array_t one( SIZE_FOR_ONE );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", one.get_size(), SIZE_FOR_ONE );
	array_t two( SIZE_FOR_TWO );
	ENSURE_EQUALS( "wrong number of items created", item_t::get_instance_count(), SIZE_FOR_ONE + SIZE_FOR_TWO );
	ENSURE_EQUALS( "inconsistient size with respect to constructor", two.get_size(), SIZE_FOR_TWO );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Constructor with filling. */" )
	item_t::set_start_id( 0 );
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	try
		{
		array_t badArray( BAD_SIZE, FILLER_FOR_ARRAY );
		FAIL( "array with negative size created" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	array_t array( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS( "array element not filled with default value", array[ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Copy constructor. */" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	array_t array( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		array [ i ] = i;
	array_t copy( array );
	ENSURE_EQUALS( "inconsistient size after copy constructor", copy.get_size(), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS( "wrong content after copy constructor", copy[ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Operator [ ]. */" )
	item_t::set_start_id( 0 );
	int const SIZE = 7;
	array_t array ( SIZE );
	try
		{
		array [ SIZE ] = 0;
		FAIL( "access beyond size succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		array[ - SIZE - 1 ] = 0;
		FAIL( "access with negative index succed" );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Operator bool. */" )
	item_t::set_start_id( 0 );
	int const EMPTY = 0;
	int const SIZE = 7;
	array_t empty( EMPTY );
	ENSURE_EQUALS( "test for array emptiness faild", ! empty, true );
	array_t normal( SIZE );
	ENSURE_EQUALS( "test for array fullness faild", ! normal, false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "push_back" )
	item_t::set_start_id( 0 );
	item_t i;
	array_t a1;
	a1.resize( 5 );
	a1.resize( 2 );
	array_t a2;
	a2.push_back( i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "copy constructor (of empty)" )
	array_t a1;
	ENSURE( "construction of empty array", a1.is_empty() );
	array_t a2( a1 );
	ENSURE( "construction of empty array", a2.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "resize vs capacity" )
	array_t a;
	a.resize( 1 );
	ENSURE_EQUALS( "resize( 1 ) failed (resize)", a.size(), 1 );
	ENSURE_EQUALS( "resize( 1 ) failed (capacity)", a.capacity(), 1 );
	a.resize( 5 );
	ENSURE_EQUALS( "resize( 5 ) failed (resize)", a.size(), 5 );
	ENSURE_EQUALS( "resize( 5 ) failed (capacity)", a.capacity(), 5 );
	a.resize( 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (resize)", a.size(), 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (capacity)", a.capacity(), 13 );

	array_t large;
	large.resize( 7 );
	ENSURE_EQUALS( "resize( 7 ) failed (resize)", large.size(), 7 );
	ENSURE_EQUALS( "resize( 7 ) failed (capacity)", large.capacity(), 7 );
	large.resize( 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (resize)", large.size(), 13 );
	ENSURE_EQUALS( "resize( 13 ) failed (capacity)", large.capacity(), 14 );
TUT_TEARDOWN()


}

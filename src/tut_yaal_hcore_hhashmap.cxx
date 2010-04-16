/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hhashmap.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hhashmap
	{
	typedef HHashMap<int, int> hash_map_t;
	static int const TEST_PRIME = 17;
	static int const ELEM_COUNT;
	static int const LARGE_TABLE;
	static int const FEW_ELEMENTS;
	virtual ~tut_yaal_hcore_hhashmap( void )
		{}
	};

int const tut_yaal_hcore_hhashmap::ELEM_COUNT = 32;
int const tut_yaal_hcore_hhashmap::LARGE_TABLE = 251;
int const tut_yaal_hcore_hhashmap::FEW_ELEMENTS = 4;

typedef test_group<tut_yaal_hcore_hhashmap> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hhashmap_group( "yaal::hcore::HHashMap" );

TUT_UNIT_TEST_N( 1, "/* Simple constructor. */" )
	try
		{
		hash_map_t map( 0 );
		FAIL ( "Created map with bad hash table size." );
		}
	catch ( HException const& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Quantity test. */" )
	hash_map_t map( 17 );
	ENSURE_EQUALS ( "newly created map is not empty", map.size(), 0 );
	map[ 0 ] = 7;
	ENSURE_EQUALS ( "wrong size after add", map.size(), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* element insertion */" )
	hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		ENSURE_EQUALS ( "wrong size after addition", map.size(), i + 1 );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* iterate */" )
	hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		map[ i ] = i;
	int i = 0;
	for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	ENSURE_EQUALS( "bad number of iterations", i, ELEM_COUNT );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* key, value access */" )
	hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		map[ i ] = i;
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		hash_map_t::iterator it( map.find( i ) );
		ENSURE( "key not present", it != map.end() );
		ENSURE_EQUALS ( "key/value mismatch", it->second, i );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* key removal */" )
	hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		ENSURE_EQUALS ( "wrong size after addition", map.size(), i + 1 );
		}
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map.erase( i );
		ENSURE_EQUALS ( "wrong size after add", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS ( "key/value mismatch", it->second, it->first );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* iteration on large table with few elements */" )
	hash_map_t map( LARGE_TABLE );
	for ( int i = 0; i < FEW_ELEMENTS; ++ i )
		map[ i ] = i;
	int i = 0;
	for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ENSURE_EQUALS ( "key/value mismatch", it->second, it->first );
	ENSURE_EQUALS ( "bad number of iterations", i, FEW_ELEMENTS );
TUT_TEARDOWN()

}

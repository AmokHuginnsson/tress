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

#define private public
#define protected public

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
	typedef HInstanceTracker<tut_yaal_hcore_hhashmap> item_t;
	typedef HHashMap<int long, item_t> hash_map_t;
	static int long const TEST_PRIME = 17;
	static int long const ELEM_COUNT;
	static int long const LARGE_TABLE;
	static int long const HUGE_TABLE;
	static int long const FEW_ELEMENTS;
	virtual ~tut_yaal_hcore_hhashmap( void )
		{}
	void check_consitency( hash_map_t const& );
	};

int long const tut_yaal_hcore_hhashmap::ELEM_COUNT = 32;
int long const tut_yaal_hcore_hhashmap::LARGE_TABLE = 251;
int long const tut_yaal_hcore_hhashmap::HUGE_TABLE = sizeof ( int long ) > 2 ? 2750 : 2048;
int long const tut_yaal_hcore_hhashmap::FEW_ELEMENTS = 4;

void tut_yaal_hcore_hhashmap::check_consitency( hash_map_t const& map_ )
	{
	typedef HHashContainer::HAtom<hash_map_t::value_type> atom_t;
	atom_t* const* buckets( map_._engine._buckets.get<atom_t*>() );
	int long bucketCount( map_._engine._buckets.get_size() / sizeof ( atom_t* ) );
	ENSURE( "wrong bucket count/prime", bucketCount >= map_._engine._prime );
	ENSURE( "wrong bucket prime/size", map_._engine._prime >= map_._engine._size );
	ENSURE( "wrong prime / alloc status", exor( buckets != NULL, map_._engine._prime != 0 ) );
	int long realSize( 0 );
	int long collisions( 0 );
	int long longestCollision( 0 );
	for ( int long i( 0 ); i < map_._engine._prime; ++ i )
		{
		atom_t* a( buckets[ i ] );
		int long localCollisions( 0 );
		while ( a )
			{
			ENSURE_EQUALS( "atom in wrong bucket", i, abs( map_._hasher( a->_value.first ) ) % map_._engine._prime );
			a = static_cast<atom_t*>( a->_next );
			if ( a )
				{
				++ collisions;
				++ localCollisions;
				}
			++ realSize;
			}
		if ( localCollisions > longestCollision )
			longestCollision = localCollisions;
		}
	for ( int long i( map_._engine._prime ); i < bucketCount; ++ i )
		ENSURE_EQUALS( "dirty bucket", buckets[ i ], static_cast<atom_t*>( NULL ) );
	ENSURE_EQUALS( "size inconsistent", map_._engine._size, realSize );
	if ( collisions )
		clog << "collisions: " << collisions << ", longest collision: " << longestCollision << endl;
	}

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
	{
	hash_map_t map( 17 );
	check_consitency( map );
	ENSURE_EQUALS( "newly created map is not empty", map.size(), 0 );
	map[ 0 ] = 7;
	check_consitency( map );
	ENSURE_EQUALS( "wrong size after add", map.size(), 1 );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* element insertion */" )
	{
	hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		}
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* iterate */" )
	{
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		check_consitency( map );
		}
	int long i( 0 );
	for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	ENSURE_EQUALS( "bad number of iterations", i, ELEM_COUNT );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* key, value access */" )
	{
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		check_consitency( map );
		}
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		hash_map_t::iterator it( map.find( i ) );
		ENSURE( "key not present", it != map.end() );
		ENSURE_EQUALS( "key/value mismatch", it->second, i );
		}
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* key removal */" )
	{
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		}
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map.erase( i );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* iteration on large table with few elements */" )
	{
	hash_map_t map( LARGE_TABLE );
	check_consitency( map );
	for ( int i = 0; i < FEW_ELEMENTS; ++ i )
		{
		map[ i ] = i;
		check_consitency( map );
		}
	int i = 0;
	for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	ENSURE_EQUALS( "bad number of iterations", i, FEW_ELEMENTS );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* copy contructor */" )
	{
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		}
	hash_map_t map2( map );
	check_consitency( map );
	check_consitency( map2 );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* contructor from sequence */" )
	{
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		}
	hash_map_t map2( map.begin(), map.end() );
	check_consitency( map );
	check_consitency( map2 );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "/* auto grow */" )
	{
	hash_map_t map;
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map[ i * 3 ] = i * 3;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	for ( int i = 0; i < ELEM_COUNT; ++ i )
		{
		map.erase( i * 3 );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* auto grow large table */" )
	{
	hash_map_t map;
	check_consitency( map );
	for ( int i = 0; i < LARGE_TABLE; ++ i )
		{
		map[ i * 3 ] = i * 3;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	for ( int i = 0; i < LARGE_TABLE; ++ i )
		{
		map.erase( i * 3 );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), LARGE_TABLE - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* auto grow huge table */" )
	{
	hash_map_t map;
	check_consitency( map );
	for ( int long i = 0; i < HUGE_TABLE; ++ i )
		{
		map[ i * i * i ] = i * i * i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	for ( int long i = 0; i < HUGE_TABLE; ++ i )
		{
		map.erase( i * i * i );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), HUGE_TABLE - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

}

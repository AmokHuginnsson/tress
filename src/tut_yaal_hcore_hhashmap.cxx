/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hhashmap.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hexception.hxx>

#include <TUT/tut.hpp>

#define private public
#define protected public

#include <yaal/hcore/hhashmap.hxx>

#undef protected
#undef private

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hhashmap : public simple_mock<tut_yaal_hcore_hhashmap> {
	typedef simple_mock<tut_yaal_hcore_hhashmap> base_type;
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
int long const tut_yaal_hcore_hhashmap::HUGE_TABLE = sizeof ( int long ) > 4 ? 2750 : 1290;
int long const tut_yaal_hcore_hhashmap::FEW_ELEMENTS = 4;

void tut_yaal_hcore_hhashmap::check_consitency( hash_map_t const& map_ ) {
	typedef hash_map_t::engine_t::HAtom atom_t;
	atom_t* const* buckets = map_._engine._buckets.get<atom_t*>();
	int long bucketCount( map_._engine._buckets.get_size() / static_cast<int>( sizeof ( atom_t* ) ) );
	ENSURE( "wrong bucket count/prime", bucketCount >= map_._engine._prime );
	ENSURE( "wrong bucket prime/size", map_._engine._prime >= map_._engine._size );
	ENSURE( "wrong prime / alloc status", xnor( buckets != NULL, map_._engine._prime != 0 ) );
	int long realSize( 0 );
	int long collisions( 0 );
	int long longestCollision( 0 );
	for ( int long i( 0 ); i < map_._engine._prime; ++ i ) {
		atom_t* a( buckets[ i ] );
		int long localCollisions( 0 );
		while ( a ) {
			ENSURE_EQUALS( "atom in wrong bucket", i,
					abs( map_._engine._hasher( a->_value.first ) ) % map_._engine._prime );
			a = static_cast<atom_t*>( a->_next );
			if ( a ) {
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

TUT_TEST_GROUP( tut_yaal_hcore_hhashmap, "yaal::hcore::HHashMap" );

TUT_UNIT_TEST( 1, "Simple constructor." )
	ENSURE_THROW( "Created map with bad hash table size.", hash_map_t map( 0 ), HException );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Quantity test." ) {
	hash_map_t map( 17 );
	check_consitency( map );
	ENSURE_EQUALS( "newly created map is not empty", map.size(), 0 );
	map[ 0 ] = 7;
	check_consitency( map );
	ENSURE_EQUALS( "wrong size after add", map.size(), 1 );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "element insertion" ) {
	hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "iterate" ) {
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
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

TUT_UNIT_TEST( 5, "key, value access" ) {
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
	}
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		hash_map_t::iterator it( map.find( i ) );
		ENSURE( "key not present", it != map.end() );
		ENSURE_EQUALS( "key/value mismatch", it->second, i );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "key removal" ) {
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map.erase( i );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "iteration on large table with few elements" ) {
	hash_map_t map( LARGE_TABLE );
	check_consitency( map );
	for ( int i = 0; i < FEW_ELEMENTS; ++ i ) {
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

TUT_UNIT_TEST( 8, "copy contructor" ) {
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
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

TUT_UNIT_TEST( 9, "contructor from sequence" ) {
	hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
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

TUT_UNIT_TEST( 10, "auto grow" ) {
	hash_map_t map;
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i * 3 ] = i * 3;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map.erase( i * 3 );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "auto grow large table" ) {
	hash_map_t map;
	check_consitency( map );
	for ( int i = 0; i < LARGE_TABLE; ++ i ) {
		map[ i * 3 ] = i * 3;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
	for ( int i = 0; i < LARGE_TABLE; ++ i ) {
		map.erase( i * 3 );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), LARGE_TABLE - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "auto grow huge table" )
	TIME_CONSTRAINT_EXEMPT(); {
	hash_map_t map;
	check_consitency( map );
	for ( int long i = 0; i < HUGE_TABLE; ++ i ) {
		map[ i * i * i ] = i * i * i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
	for ( int long i = 0; i < HUGE_TABLE; ++ i ) {
		map.erase( i * i * i );
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), HUGE_TABLE - ( i + 1 ) );
		for ( hash_map_t::iterator it = map.begin(); it != map.end(); ++ it )
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "find on empty map" )
	hash_map_t map;
	hash_map_t::iterator it( map.find( 0 ) );
	ENSURE( "find on empty returned bogus iterator", it == map.end() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "dereferencing non existing key with const map[key]" )
	hash_map_t m;
	hash_map_t const& cm( m );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm[ 0 ], HInvalidKeyException );
	ENSURE_EQUALS( "map extended during m[key] = val; although val evaluation throws.", m.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "const pointer as a key" )
	char const a[] = "a";
	char const b[] = "a";
	char const c[] = "a";
	char const d[] = "a";
	typedef HHashMap<char const*, int> map_t;
	map_t map;
	map[a] = 1;
	map[b] = 2;
	map[c] = 3;
	map[d] = 4;
	char const msg[] = "hashing const pointer failed";
	ENSURE_EQUALS( msg, map.find( a )->second, 1 );
	ENSURE_EQUALS( msg, map.find( b )->second, 2 );
	ENSURE_EQUALS( msg, map.find( c )->second, 3 );
	ENSURE_EQUALS( msg, map.find( d )->second, 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "sample data" )
	typedef HHashMap<HString, int> string_to_int_hashmap_t;
	string_to_int_hashmap_t map;
	map["one"] = 1;
	map["two"] = 2;
	map["three"] = 3;
	map["four"] = 4;
	map["five"] = 5;
	map["six"] = 6;
	map["seven"] = 7;
	ENSURE_EQUALS( "failed to insert [] (data)", map["one"], 1 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["two"], 2 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["three"], 3 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["four"], 4 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["five"], 5 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["six"], 6 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["seven"], 7 );
	ENSURE_EQUALS( "failed to insert [] (size)", map.size(), 7 );
TUT_TEARDOWN()


}

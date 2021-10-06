/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <yaal/hcore/hexception.hxx>

#include <TUT/tut.hpp>

#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wkeyword-macro"
#define private public
#define protected public
#pragma GCC diagnostic error "-Wkeyword-macro"
#pragma GCC diagnostic error "-Wpragmas"

#include <yaal/hcore/hhashmap.hxx>

#undef protected
#undef private

#include <yaal/hcore/random.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::random;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_horderedhashmap : public simple_mock<tut_yaal_hcore_horderedhashmap> {
	typedef simple_mock<tut_yaal_hcore_horderedhashmap> base_type;
	typedef HOrderedHashMap<int long, item_t> ordered_hash_map_t;
	static int long const TEST_PRIME = 17;
	static int long const ELEM_COUNT;
	static int long const LARGE_TABLE;
	static int long const HUGE_TABLE;
	static int long const FEW_ELEMENTS;
	virtual ~tut_yaal_hcore_horderedhashmap( void )
		{}
	void check_consitency( ordered_hash_map_t const&, bool = false );
};

int long const tut_yaal_hcore_horderedhashmap::ELEM_COUNT = 32;
int long const tut_yaal_hcore_horderedhashmap::LARGE_TABLE = 251;
int long const tut_yaal_hcore_horderedhashmap::HUGE_TABLE = sizeof ( int long ) > 4 ? 2750 : 1290;
int long const tut_yaal_hcore_horderedhashmap::FEW_ELEMENTS = 4;

void tut_yaal_hcore_horderedhashmap::check_consitency( ordered_hash_map_t const& map_, bool withOrdereding_ ) {
	typedef ordered_hash_map_t::engine_type::HAtom atom_t;
	int long slotCount( map_._engine._size + map_._engine._erased );
	int long storeSize( map_._engine._store.count_of<atom_t>() );
	ENSURE_GREATER_OR_EQUAL( "indexMap has more than of 2/3 slots taken", map_._engine._cover, slotCount * 3 / 2 );
	ENSURE_GREATER_OR_EQUAL( "wrong bucket prime/size", map_._engine._cover, slotCount );
	ENSURE_GREATER_OR_EQUAL( "wronge storage size", storeSize, slotCount );
	int valid( 0 );
	int erased( 0 );
	for ( int i( 0 ); i < map_._engine._cover; ++ i ) {
		int long storeIndex( map_._engine.get_index( static_cast<hash_value_t>( i ) ) );
		if ( storeIndex == ordered_hash_map_t::engine_type::ERASED ) {
			++ erased;
		} else if ( storeIndex != ordered_hash_map_t::engine_type::INVALID ) {
			++ valid;
		}
	}
	ENSURE_EQUALS( "invalid indexMap content", valid, map_._engine._size );
	ENSURE_GREATER_OR_EQUAL( "wrong erased count/indexMap content", map_._engine._erased, erased );
	if ( withOrdereding_ ) {
		ENSURE_GREATER_OR_EQUAL( "map not compacted", map_._engine._size / 2, map_._engine._erased );
		clog << "held erased: " << map_._engine._erased << endl;
	}
	atom_t const* store( map_._engine._store.get<atom_t>() );
	int validInStore( 0 );
	int longestCollision( 0 );
	int totalCollisions( 0 );
	for ( int i( 0 ); i < storeSize; ++ i ) {
		atom_t const& atom( store[i] );
		if ( atom._hash == ordered_hash_map_t::engine_type::EMPTY_SLOT ) {
			continue;
		}
		hash_value_t actualHash( static_cast<hash_value_t>( map_._engine._hasher( atom._value.first ) ) & ordered_hash_map_t::engine_type::HASH_MASK );
		ENSURE_EQUALS( "bad hash in store", atom._hash, actualHash );
		hash_value_t mapIndex( atom._hash % static_cast<hash_value_t>( map_._engine._cover ) );
		ENSURE_NOT( "bad indexMap content", map_._engine.get_index( mapIndex ) == ordered_hash_map_t::engine_type::INVALID );
		int collision( 0 );
		hash_value_t perturb( atom._hash );
		while ( map_._engine.get_index( mapIndex ) != i ) {
			perturb >>= ordered_hash_map_t::engine_type::HASH_PERTURBATION_SHIFT;
			mapIndex = ( 5 * mapIndex + 1 + perturb ) % static_cast<hash_value_t>( map_._engine._cover );
			ENSURE_NOT( "bad indexMap content", map_._engine.get_index( mapIndex ) == ordered_hash_map_t::engine_type::INVALID );
			++ collision;
			++ totalCollisions;
		}
		if ( collision > longestCollision ) {
			longestCollision = collision;
		}
		++ validInStore;
	}
	ENSURE_EQUALS( "invalid store content", validInStore, map_._engine._size );
	clog << "size = " << ( validInStore + erased ) << ", cover = " << map_._engine._cover << ", longest collision = " << longestCollision << ", totalCollisions = " << totalCollisions << endl;
}

TUT_TEST_GROUP( tut_yaal_hcore_horderedhashmap, "yaal::hcore::HOrderedHashMap" );

TUT_UNIT_TEST( "Simple constructor." )
	ENSURE_THROW( "Created map with bad hash table size.", ordered_hash_map_t map( 0 ), HException );
	ordered_hash_map_t map;
	ENSURE_EQUALS( "empty map size failed", map.get_size(), 0 );
	ENSURE( "is_empty in empty map failed", map.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Quantity test." ) {
	ordered_hash_map_t map( 17 );
	check_consitency( map );
	ENSURE_EQUALS( "newly created map is not empty", map.size(), 0 );
	map[ 0 ] = 7;
	check_consitency( map );
	ENSURE_EQUALS( "wrong size after add", map.size(), 1 );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "element insertion" ) {
	ordered_hash_map_t map( TEST_PRIME );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - copy count" )
	/* from lvalue */ {
		item_t::reset();
		ordered_hash_map_t m;
		item_t i( 1 );
		m.insert( make_pair( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - move count" )
	/* from lvalue */ {
		item_t::reset();
		ordered_hash_map_t m;
		item_t i( 1 );
		m.insert( make_pair( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 3 );
	}
	/* from rvalue */ {
		item_t::reset();
		ordered_hash_map_t m;
		m.insert( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "iterate" ) {
	ordered_hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
	}
	int long i( 0 );
	for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i )
		ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	ENSURE_EQUALS( "bad number of iterations", i, ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "key, value access" ) {
	ordered_hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
	}
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		ordered_hash_map_t::iterator it( map.find( i ) );
		ENSURE( "key not present", it != map.end() );
		ENSURE_EQUALS( "key/value mismatch", it->second, i );
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "key removal" ) {
	ordered_hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map.erase( i );
		check_consitency( map );
		map.compact();
		check_consitency( map, true );
		ENSURE_EQUALS( "wrong size after erase", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "iteration on large table with few elements" ) {
	ordered_hash_map_t map( LARGE_TABLE );
	check_consitency( map );
	for ( int i = 0; i < FEW_ELEMENTS; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
	}
	int i = 0;
	for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it, ++ i ) {
		ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
	}
	ENSURE_EQUALS( "bad number of iterations", i, FEW_ELEMENTS );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy contructor" ) {
	ordered_hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
	ordered_hash_map_t map2( map );
	check_consitency( map );
	check_consitency( map2 );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "contructor from sequence" ) {
	ordered_hash_map_t map( TEST_PRIME );
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
	ordered_hash_map_t map2( map.begin(), map.end() );
	check_consitency( map );
	check_consitency( map2 );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "auto grow" ) {
	ordered_hash_map_t map;
	check_consitency( map );
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i * 3 ] = i * 3;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map.erase( i * 3 );
		check_consitency( map );
		map.compact();
		check_consitency( map, true );
		ENSURE_EQUALS( "wrong size after erase", map.size(), ELEM_COUNT - ( i + 1 ) );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "auto grow large table" ) {
	ordered_hash_map_t map;
	check_consitency( map );
	for ( int i = 0; i < LARGE_TABLE; ++ i ) {
		map[ i * 3 ] = i * 3;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	for ( int i = 0; i < LARGE_TABLE; ++ i ) {
		map.erase( i * 3 );
		check_consitency( map );
		map.compact();
		check_consitency( map, true );
		ENSURE_EQUALS( "wrong size after erase", map.size(), LARGE_TABLE - ( i + 1 ) );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "auto grow huge table" )
	TIME_CONSTRAINT_EXEMPT(); {
	ordered_hash_map_t map;
	check_consitency( map );
	for ( int long i = 0; i < HUGE_TABLE; ++ i ) {
		map[ i * i * i ] = i * i * i;
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
	for ( int long i = 0; i < HUGE_TABLE; ++ i ) {
		map.erase( i * i * i );
		check_consitency( map );
		map.compact();
		check_consitency( map );
		ENSURE_EQUALS( "wrong size after erase", map.size(), HUGE_TABLE - ( i + 1 ) );
		for ( ordered_hash_map_t::iterator it = map.begin(); it != map.end(); ++ it ) {
			ENSURE_EQUALS( "key/value mismatch", it->second, it->first );
		}
	}
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find on empty map" )
	ordered_hash_map_t map;
	ordered_hash_map_t::iterator it( map.find( 0 ) );
	ENSURE( "find on empty returned bogus iterator", it == map.end() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "dereferencing non existing key with const map[key]" )
	ordered_hash_map_t m;
	ordered_hash_map_t const& cm( m );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm[ 0 ], HInvalidKeyException );
	ENSURE_EQUALS( "map extended during m[key] = val; although val evaluation throws.", m.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "at()" )
	ordered_hash_map_t m;
	ordered_hash_map_t const& cm( m );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm.at( 0 ), HInvalidKeyException );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", m.at( 0 ), HInvalidKeyException );
	ENSURE_EQUALS( "map extended during m.at(key)", m.is_empty(), true );
	m[0] = 7;
	ENSURE_EQUALS( "at() was unable to return value", m.at( 0 ), 7 );
	ENSURE_EQUALS( "at() was unable to return value", cm.at( 0 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "const pointer as a key" )
	char const a[] = "a";
	char const b[] = "a";
	char const c[] = "a";
	char const d[] = "a";
	typedef HOrderedHashMap<char const*, int> map_t;
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

TUT_UNIT_TEST( "sample data" )
	typedef HTaggedPOD<int, tut_yaal_hcore_horderedhashmap> tut_int_t;
	typedef HOrderedHashMap<HString, tut_int_t> string_to_int_hashmap_t;
	string_to_int_hashmap_t map;
	map["one"] = tut_int_t( 1 );
	map["two"] = tut_int_t( 2 );
	map["three"] = tut_int_t( 3 );
	map["four"] = tut_int_t( 4 );
	map["five"] = tut_int_t( 5 );
	map["six"] = tut_int_t( 6 );
	map["seven"] = tut_int_t( 7 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["two"], 2 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["one"], 1 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["two"], 2 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["three"], 3 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["four"], 4 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["five"], 5 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["six"], 6 );
	ENSURE_EQUALS( "failed to insert [] (data)", map["seven"], 7 );
	ENSURE_EQUALS( "failed to insert [] (size)", map.size(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare equals" )
	typedef HOrderedHashMap<HString, HString> hashmap_t;
	typedef HArray<HString> string_array_t;
	hashmap_t a;
	int const dataSize( 64 );
	for ( int i( 0 ); i < dataSize; ++ i ) {
		a.insert( make_pair( i, i * i ) );
	}
	hashmap_t b;
	for ( int i( dataSize - 1 ); i >= 0; -- i ) {
		b.insert( make_pair( i, i * i ) );
	}
	string_array_t ia;
	transform( a.begin(), a.end(), back_insert_iterator( ia ), select1st<hashmap_t::value_type>() );
	string_array_t ib;
	transform( b.begin(), b.end(), back_insert_iterator( ib ), select1st<hashmap_t::value_type>() );
	ENSURE_NOT( "test preparation failed", ia == ib );
	ENSURE_EQUALS( "compare equals operator failed", a, b );
	a.insert( make_pair( "kot", "Ala" ) );
	ENSURE_NOT( "compare equals operator failed", a == b );
	b.insert( make_pair( "kot", "Ola" ) );
	ENSURE( "compare equals operator failed", a != b );
TUT_TEARDOWN()

TUT_UNIT_TEST( "iteration" )
	ordered_hash_map_t map;
	for ( int i : _testData_[0] ) {
		map[i] = i * i;
		check_consitency( map );
	}
	int i( 0 );
	for ( ordered_hash_map_t::const_iterator it( map.begin() ), end( map.end() ); it != end; ++ it ) {
		ENSURE_EQUALS( "bad order of iteration", it->first, _testData_[0][i] );
		ENSURE_EQUALS( "bad order of iteration", it->second, _testData_[0][i] * _testData_[0][i] );
		++ i;
	}
	ENSURE_EQUALS( "not fully iterated", i, size( _testData_[0] ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reversed iteration" )
	ordered_hash_map_t map;
	for ( int const* p( begin( _testData_[0] ) ), * e( end( _testData_[0] ) ); p != e; ++ p ) {
		map[*p] = *p * *p;
		check_consitency( map );
	}
	int i( size( _testData_[0] ) - 1 );
	for ( ordered_hash_map_t::const_reverse_iterator it( map.rbegin() ), end( map.rend() ); it != end; ++ it ) {
		ENSURE_EQUALS( "bad order of iteration", it->first, _testData_[0][i] );
		ENSURE_EQUALS( "bad order of iteration", it->second, _testData_[0][i] * _testData_[0][i] );
		-- i;
	}
	ENSURE_EQUALS( "not fully iterated", i, -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "continuous insert/erase" )
	ordered_hash_map_t map;
	for ( int i : _testData_[0] ) {
		map[i] = i * i;
		check_consitency( map );
	}
	for ( int i : _testData_[0] ) {
		map[i * i + 100] = i * i * i;
		check_consitency( map );
	}
	for ( int i : _testData_[0] ) {
		map[i * i * i + 1000000] = i * i * i * i;
		check_consitency( map );
	}
	for ( int i : _testData_[0] ) {
		map[i * i * i + 2345678] = i * i * i * i * i;
		check_consitency( map );
	}
	for ( int trial( 1 ); trial < 128; ++ trial ) {
		clog << "trial: " << trial << endl;
		for ( int i : _testData_[0] ) {
			map[-i * trial] = -i * i;
			check_consitency( map );
		}
		if ( trial == 1 ) {
			continue;
		}
		for ( int i : _testData_[0] ) {
			map.erase( -i * ( trial - 1 ) );
			check_consitency( map );
			map.compact();
			check_consitency( map, true );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "auto grow humongous table" )
	TIME_CONSTRAINT_EXEMPT(); {
	ordered_hash_map_t map;
	check_consitency( map );
	HRandomNumberGenerator r;
#ifdef NDEBUG
	int long size( 10000000L );
#else
	int long size( 1000000L );
#endif
	for ( int long i( 0 ); i < size; ++ i ) {
		map[static_cast<int long>( r() )] = 0;
	}
	check_consitency( map );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

}

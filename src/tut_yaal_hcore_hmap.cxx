/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hmap.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#include <yaal/hcore/hmap.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hmap : public simple_mock<tut_yaal_hcore_hmap> {
	typedef simple_mock<tut_yaal_hcore_hmap> base_type;
	static int long const ELEM_COUNT;
	struct Crazy {
		Crazy() { throw 0; }
	};
	typedef HMap<int, int> i2i_t;
	typedef HMap<int, Crazy> i2c_t;
	virtual ~tut_yaal_hcore_hmap( void )
		{}
	void lower_bound_test( int );
	void upper_bound_test( int );
};

int long const tut_yaal_hcore_hmap::ELEM_COUNT = 32;

TUT_TEST_GROUP( tut_yaal_hcore_hmap, "yaal::hcore::HMap" );

TUT_UNIT_TEST( "Default constructor (size(), empty())." )
	i2i_t m;
	ENSURE_EQUALS( "bad size on new map", m.get_size(), 0 );
	ENSURE( "bad empty status on new map", m.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy contructor" ) {
	i2i_t map;
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
	i2i_t map2( map );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "contructor from sequence" ) {
	i2i_t map;
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		map[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", map.size(), i + 1 );
	}
	i2i_t map2( map.begin(), map.end() );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "One elem inserted (size(), empty())" )
	i2i_t m;
	ENSURE_EQUALS( "bad size on new map", m.get_size(), 0 );
	ENSURE( "bad empty status on new map", m.is_empty() );
	m.insert( make_pair( 1, 1 ) );
	ENSURE_EQUALS( "bad size on map with one elem", m.get_size(), 1 );
	ENSURE_NOT( "bad empty status on map with one elem", m.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find() on one elem map" )
	i2i_t m;
	m.insert( make_pair( 0, 0 ) );
	ENSURE( "find on one elem map failed", m.find( 0 ) != m.end() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find()" )
	i2i_t map;
	map.insert( make_pair( 1, 1 ) );
	map.insert( make_pair( 2, 2 ) );
	map.insert( make_pair( 4, 4 ) );
	map.insert( make_pair( 5, 5 ) );
	i2i_t::const_iterator it( map.find( 3 ) );
	ENSURE( "find with false positive", ! ( it != map.end() ) );
	map.insert( make_pair( 3, 3 ) );
	it = map.find( 3 );
	ENSURE( "find with false negative", it != map.end() );
	ENSURE_EQUALS( "find failed", it->first, 3 );
TUT_TEARDOWN()

void tut_yaal_hcore_hmap::lower_bound_test( int size_ ) {
	i2i_t map;
	for ( int i( 0 ); i < size_; i += 2 )
		map.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i ) {
		i2i_t::const_iterator it( map.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != map.end() );
		ENSURE_EQUALS( "lower_bound failed", it->first, ( i % 2 ) ? i + 1 : i );
	}
	map.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		map.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i ) {
		i2i_t::const_iterator it( map.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != map.end() );
		ENSURE_EQUALS( "lower_bound failed", it->first, ( i % 2 ) ? i + 1 : i );
	}
}

void tut_yaal_hcore_hmap::upper_bound_test( int size_ ) {
	i2i_t map;
	for ( int i( 0 ); i < size_; i += 2 )
		map.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i ) {
		i2i_t::const_iterator it( map.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != map.end() );
		ENSURE_EQUALS( "upper_bound failed", it->first, ( i % 2 ) ? i + 1 : i + 2 );
	}
	i2i_t::const_iterator end( map.upper_bound( map.rbegin()->first ) );
	ENSURE( "upper_bound found", !( end != map.end() ) );
	map.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		map.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i ) {
		i2i_t::const_iterator it( map.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != map.end() );
		ENSURE_EQUALS( "upper_bound failed", it->first, ( i % 2 ) ? i + 1 : i + 2 );
	}
	i2i_t::const_iterator end2( map.upper_bound( map.rbegin()->first ) );
	ENSURE( "upper_bound found", !( end2 != map.end() ) );
}

TUT_UNIT_TEST( "lower_bound()" )
	i2i_t map;
	map.insert( make_pair( 1, 1 ) );
	map.insert( make_pair( 2, 2 ) );
	map.insert( make_pair( 4, 5 ) );
	map.insert( make_pair( 5, 5 ) );
	i2i_t::const_iterator it( map.lower_bound( 3 ) );
	ENSURE( "lower_bound not found", it != map.end() );
	ENSURE_EQUALS( "lower_bound failed", it->first, 4 );
	map.insert( make_pair( 3, 3 ) );
	it = map.lower_bound( 3 );
	ENSURE( "lower_bound not found", it != map.end() );
	ENSURE_EQUALS( "lower_bound failed", it->first, 3 );

/* Let's be serious. */
	static int const RANGE( 1024 );
	for ( int i( 0 ); i < RANGE; i += 2 )
		lower_bound_test( i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "upper_bound()" )
	i2i_t map;
	map.insert( make_pair( 1, 1 ) );
	map.insert( make_pair( 2, 2 ) );
	map.insert( make_pair( 4, 4 ) );
	map.insert( make_pair( 5, 5 ) );
	i2i_t::const_iterator it( map.upper_bound( 3 ) );
	ENSURE( "upper_bound not found", it != map.end() );
	ENSURE_EQUALS( "upper_bound failed", it->first, 4 );
	map.insert( make_pair( 3, 3 ) );
	it = map.upper_bound( 3 );
	ENSURE( "upper_bound not found", it != map.end() );
	ENSURE_EQUALS( "upper_bound failed", it->first, 4 );

/* Let's be serious. */
	static int const RANGE( 1024 );
	for ( int i( 2 ); i < RANGE; i += 2 )
		upper_bound_test( i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HMap insert of already existing key")
	i2i_t m;
	static int const KEY = 1;
	static int const ORIGINAL_VAL = 2;
	static int const NEXT_VAL = 3;
	m.insert( yaal::hcore::make_pair( KEY, ORIGINAL_VAL ) );
	ENSURE( "element not inserted", m.find( KEY ) != m.end() );
	i2i_t::insert_result ir = m.insert( yaal::hcore::make_pair( KEY, NEXT_VAL ) );
	ENSURE_EQUALS( "insertion of already existing key reported successful", ir.second, false );
	ENSURE_EQUALS( "element with already existing key inserted", ir.first->second, ORIGINAL_VAL );
TUT_TEARDOWN()

TUT_UNIT_TEST( "exception during map[key] = val;" )
	i2c_t m;
	/*
	 * Should stay in explicit try/catch form.
	 */
	try {
		m[ 0 ] = Crazy();
		FAIL( "FATAL: bad exec path!" );
	} catch ( int ) {
		// ok
	}
	ENSURE_EQUALS( "map extended during m[key] = val; although val evaluation throws.", m.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "dereferencing non existing key with const map[key]" )
	i2c_t m;
	i2c_t const& cm( m );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm[ 0 ], HInvalidKeyException );
	ENSURE_EQUALS( "map extended during m[key] = val; although val evaluation throws.", m.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "at()" )
	i2i_t m;
	i2i_t const& cm( m );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm.at( 0 ), HInvalidKeyException );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", m.at( 0 ), HInvalidKeyException );
	ENSURE_EQUALS( "map extended during m.at(key)", m.is_empty(), true );
	m[0] = 7;
	ENSURE_EQUALS( "at() was unable to return value", m.at( 0 ), 7 );
	ENSURE_EQUALS( "at() was unable to return value", cm.at( 0 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sample data" )
	typedef HMap<HString, int> string_to_int_map_t;
	string_to_int_map_t map;
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


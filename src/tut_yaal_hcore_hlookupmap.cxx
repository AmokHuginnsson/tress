/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hlookupmap.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hlookupmap : public simple_mock<tut_yaal_hcore_hlookupmap> {
	typedef simple_mock<tut_yaal_hcore_hlookupmap> base_type;
	static int long const ELEM_COUNT;
	struct Crazy {
		Crazy() { throw 0; }
	};
	typedef HLookupMap<int, int> i2i_t;
	typedef HLookupMap<int, item_t> lookupmap_t;
	typedef HLookupMap<int, Crazy> i2c_t;
	virtual ~tut_yaal_hcore_hlookupmap( void )
		{}
	void lower_bound_test( int );
	void upper_bound_test( int );
};

int long const tut_yaal_hcore_hlookupmap::ELEM_COUNT = 32;

TUT_TEST_GROUP( tut_yaal_hcore_hlookupmap, "yaal::hcore::HLookupMap" );

TUT_UNIT_TEST( "Default constructor (size(), empty())." )
	i2i_t lm;
	ENSURE_EQUALS( "bad size on new lookupmap", lm.get_size(), 0 );
	ENSURE( "bad empty status on new lookupmap", lm.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy contructor" ) {
	i2i_t lookupmap;
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		lookupmap[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", lookupmap.size(), i + 1 );
	}
	i2i_t map2( lookupmap );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "contructor from sequence" ) {
	i2i_t lookupmap;
	for ( int i = 0; i < ELEM_COUNT; ++ i ) {
		lookupmap[ i ] = i;
		ENSURE_EQUALS( "wrong size after addition", lookupmap.size(), i + 1 );
	}
	i2i_t map2( lookupmap.begin(), lookupmap.end() );
	ENSURE_EQUALS( "wrong size after addition", map2.size(), ELEM_COUNT );
}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "One elem inserted (size(), empty())" )
	i2i_t lm;
	ENSURE_EQUALS( "bad size on new lookupmap", lm.get_size(), 0 );
	ENSURE( "bad empty status on new lookupmap", lm.is_empty() );
	lm.insert( make_pair( 1, 1 ) );
	ENSURE_EQUALS( "bad size on lookupmap with one elem", lm.get_size(), 1 );
	ENSURE_NOT( "bad empty status on lookupmap with one elem", lm.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - copy count" )
	/* from lvalue */ {
		item_t::reset();
		lookupmap_t lm;
		item_t i( 1 );
		lm.insert( make_pair( 1, i ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 1 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 2 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert - move count" )
	/* from lvalue */ {
		item_t::reset();
		lookupmap_t lm;
		item_t i( 1 );
		lm.insert( make_pair( 1, yaal::move( i ) ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 2 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 3 );
	}
	/* from rvalue */ {
		item_t::reset();
		lookupmap_t lm;
		lm.insert( make_pair( 1, 1 ) );
		ENSURE_EQUALS( "bad number of copies", item_t::get_copy_count(), 0 );
		ENSURE_EQUALS( "bad instance count", item_t::get_instance_count(), 1 );
		ENSURE_EQUALS( "bad move count", item_t::get_move_count(), 1 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "find() on one elem lookupmap" )
	i2i_t lm;
	lm.insert( make_pair( 0, 0 ) );
	ENSURE( "find on one elem lookupmap failed", lm.find( 0 ) != lm.end() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find()" )
	i2i_t lookupmap;
	lookupmap.insert( make_pair( 1, 1 ) );
	lookupmap.insert( make_pair( 2, 2 ) );
	lookupmap.insert( make_pair( 4, 4 ) );
	lookupmap.insert( make_pair( 5, 5 ) );
	i2i_t::const_iterator it( lookupmap.find( 3 ) );
	ENSURE( "find with false positive", ! ( it != lookupmap.end() ) );
	lookupmap.insert( make_pair( 3, 3 ) );
	it = lookupmap.find( 3 );
	ENSURE( "find with false negative", it != lookupmap.end() );
	ENSURE_EQUALS( "find failed", it->first, 3 );
TUT_TEARDOWN()

void tut_yaal_hcore_hlookupmap::lower_bound_test( int size_ ) {
	i2i_t lookupmap;
	for ( int i( 0 ); i < size_; i += 2 )
		lookupmap.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i ) {
		i2i_t::const_iterator it( lookupmap.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != lookupmap.end() );
		ENSURE_EQUALS( "lower_bound failed", it->first, ( i % 2 ) ? i + 1 : i );
	}
	lookupmap.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		lookupmap.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 1 ); ++i ) {
		i2i_t::const_iterator it( lookupmap.lower_bound( i ) );
		ENSURE( "lower_bound not found", it != lookupmap.end() );
		ENSURE_EQUALS( "lower_bound failed", it->first, ( i % 2 ) ? i + 1 : i );
	}
}

void tut_yaal_hcore_hlookupmap::upper_bound_test( int size_ ) {
	i2i_t lookupmap;
	for ( int i( 0 ); i < size_; i += 2 )
		lookupmap.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i ) {
		i2i_t::const_iterator it( lookupmap.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != lookupmap.end() );
		ENSURE_EQUALS( "upper_bound failed", it->first, ( i % 2 ) ? i + 1 : i + 2 );
	}
	i2i_t::const_iterator end( lookupmap.upper_bound( lookupmap.rbegin()->first ) );
	ENSURE( "upper_bound found", !( end != lookupmap.end() ) );
	lookupmap.clear();
	for ( int i( size_ - 2 ); i >= 0; i -= 2 )
		lookupmap.insert( make_pair( i, i ) );
	for ( int i( 0 ); i < ( size_ - 2 ); ++i ) {
		i2i_t::const_iterator it( lookupmap.upper_bound( i ) );
		ENSURE( "upper_bound not found", it != lookupmap.end() );
		ENSURE_EQUALS( "upper_bound failed", it->first, ( i % 2 ) ? i + 1 : i + 2 );
	}
	i2i_t::const_iterator end2( lookupmap.upper_bound( lookupmap.rbegin()->first ) );
	ENSURE( "upper_bound found", !( end2 != lookupmap.end() ) );
}

TUT_UNIT_TEST( "lower_bound()" )
	i2i_t lookupmap;
	lookupmap.insert( make_pair( 1, 1 ) );
	lookupmap.insert( make_pair( 2, 2 ) );
	lookupmap.insert( make_pair( 4, 5 ) );
	lookupmap.insert( make_pair( 5, 5 ) );
	i2i_t::const_iterator it( lookupmap.lower_bound( 3 ) );
	ENSURE( "lower_bound not found", it != lookupmap.end() );
	ENSURE_EQUALS( "lower_bound failed", it->first, 4 );
	lookupmap.insert( make_pair( 3, 3 ) );
	it = lookupmap.lower_bound( 3 );
	ENSURE( "lower_bound not found", it != lookupmap.end() );
	ENSURE_EQUALS( "lower_bound failed", it->first, 3 );

/* Let's be serious. */
	static int const RANGE( 1024 );
	for ( int i( 0 ); i < RANGE; i += 2 )
		lower_bound_test( i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "upper_bound()" )
	i2i_t lookupmap;
	lookupmap.insert( make_pair( 1, 1 ) );
	lookupmap.insert( make_pair( 2, 2 ) );
	lookupmap.insert( make_pair( 4, 4 ) );
	lookupmap.insert( make_pair( 5, 5 ) );
	i2i_t::const_iterator it( lookupmap.upper_bound( 3 ) );
	ENSURE( "upper_bound not found", it != lookupmap.end() );
	ENSURE_EQUALS( "upper_bound failed", it->first, 4 );
	lookupmap.insert( make_pair( 3, 3 ) );
	it = lookupmap.upper_bound( 3 );
	ENSURE( "upper_bound not found", it != lookupmap.end() );
	ENSURE_EQUALS( "upper_bound failed", it->first, 4 );

/* Let's be serious. */
	static int const RANGE( 1024 );
	for ( int i( 2 ); i < RANGE; i += 2 )
		upper_bound_test( i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HLookupMap insert of already existing key")
	i2i_t lm;
	static int const KEY = 1;
	static int const ORIGINAL_VAL = 2;
	static int const NEXT_VAL = 3;
	lm.insert( yaal::hcore::make_pair( KEY, ORIGINAL_VAL ) );
	ENSURE( "element not inserted", lm.find( KEY ) != lm.end() );
	i2i_t::insert_result ir = lm.insert( yaal::hcore::make_pair( KEY, NEXT_VAL ) );
	ENSURE_EQUALS( "insertion of already existing key reported successful", ir.second, false );
	ENSURE_EQUALS( "element with already existing key inserted", ir.first->second, ORIGINAL_VAL );
TUT_TEARDOWN()

TUT_UNIT_TEST( "exception during lookupmap[key] = val;" )
	i2c_t lm;
	/*
	 * Should stay in explicit try/catch form.
	 */
	try {
		lm[ 0 ] = Crazy();
		FAIL( "FATAL: bad exec path!" );
	} catch ( int ) {
		// ok
	}
	ENSURE_EQUALS( "lookupmap extended during lm[key] = val; although val evaluation throws.", lm.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "dereferencing non existing key with const lookupmap[key]" )
	i2c_t lm;
	i2c_t const& cm( lm );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm[ 0 ], HInvalidKeyException );
	ENSURE_EQUALS( "lookupmap extended during lm[key] = val; although val evaluation throws.", lm.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( "at()" )
	i2i_t lm;
	i2i_t const& cm( lm );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", cm.at( 0 ), HInvalidKeyException );
	ENSURE_THROW( "FATAL: dereferencing non-existing key succeeded!", lm.at( 0 ), HInvalidKeyException );
	ENSURE_EQUALS( "lookupmap extended during lm.at(key)", lm.is_empty(), true );
	lm[0] = 7;
	ENSURE_EQUALS( "at() was unable to return value", lm.at( 0 ), 7 );
	ENSURE_EQUALS( "at() was unable to return value", cm.at( 0 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sample data" )
	typedef HLookupMap<HString, int> string_to_int_map_t;
	string_to_int_map_t lookupmap;
	lookupmap["one"] = 1;
	lookupmap["two"] = 2;
	lookupmap["three"] = 3;
	lookupmap["four"] = 4;
	lookupmap["five"] = 5;
	lookupmap["six"] = 6;
	lookupmap["seven"] = 7;
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["one"], 1 );
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["two"], 2 );
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["three"], 3 );
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["four"], 4 );
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["five"], 5 );
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["six"], 6 );
	ENSURE_EQUALS( "failed to insert [] (data)", lookupmap["seven"], 7 );
	ENSURE_EQUALS( "failed to insert [] (size)", lookupmap.size(), 7 );
TUT_TEARDOWN()

}


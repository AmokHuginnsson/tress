/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_htwowaymap.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/htwowaymap.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_htwowaymap : public simple_mock<tut_yaal_tools_htwowaymap> {
	typedef HTwoWayMap<int, int> int2int_t;
	virtual ~tut_yaal_tools_htwowaymap( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_htwowaymap, "yaal::tools::HTwoWayMap" );

TUT_UNIT_TEST( 1, "Default constructor." )
	int2int_t twm;
	ENSURE_EQUALS( "should be empty", twm.is_empty(), true );
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "is_empty()" )
	int2int_t twm;
	ENSURE_EQUALS( "should be empty", twm.is_empty(), true );
	twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "should be empty", twm.is_empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "get_size()" )
	int2int_t twm;
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
	twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "should have non-0 number of elements", twm.get_size(), 1 );
	twm.insert( make_pair( 2, 3 ) );
	ENSURE_EQUALS( "bad number of elements", twm.get_size(), 2 );
	twm.insert( make_pair( 3, 4 ) );
	ENSURE_EQUALS( "bad number of elements", twm.get_size(), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "clear()" )
	int2int_t twm;
	ENSURE_EQUALS( "should be empty", twm.is_empty(), true );
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
	twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "should be empty", twm.is_empty(), false );
	ENSURE_EQUALS( "should have non-0 number of elements", twm.get_size(), 1 );
	twm.clear();
	ENSURE_EQUALS( "should be empty", twm.is_empty(), true );
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "insert()" )
	int2int_t twm;
	ENSURE_EQUALS( "should be empty", twm.is_empty(), true );
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
	int2int_t::insert_result ir = twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "false positive reported collision", ir.second, true );
	ENSURE_EQUALS( "should have non-0 number of elements", twm.get_size(), 1 );
	ENSURE_EQUALS( "should be empty", twm.is_empty(), false );
	int2int_t::const_iterator it = twm.begin();
	ENSURE( "bad iterator", it != twm.end() );
	ENSURE( "insert result iterator", ir.first == it );
	ENSURE_EQUALS( "bad left value", it->first, 1 );
	ENSURE_EQUALS( "bad right value", it->second, 2 );
	ENSURE_EQUALS( "bad left value", (*it).first, 1 );
	ENSURE_EQUALS( "bad right value", (*it).second, 2 );
	ir = twm.insert( make_pair( 1, 2 ) );
	it = twm.begin();
	ENSURE_EQUALS( "unreported collision", ir.second, false );
	ENSURE( "insert result iterator", ir.first == it );
	ir = twm.insert( make_pair( 1, 3 ) );
	it = twm.begin();
	ENSURE_EQUALS( "unreported collision", ir.second, false );
	ENSURE( "insert result iterator", ir.first == it );
	ir = twm.insert( make_pair( 2, 2 ) );
	it = twm.begin();
	ENSURE_EQUALS( "unreported collision", ir.second, false );
	ENSURE( "insert result iterator", ir.first == it );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "count()" )
	int2int_t twm;
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 0 );
	twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 1 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 2, 2 ) ), 0 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 3 ) ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "erase() by val" )
	int2int_t twm;
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 0 );
	twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "bad size", twm.get_size(), 1 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 1 );
	ENSURE_EQUALS( "bad number of erased", twm.erase( make_pair( 1, 2 ) ), 1 );
	ENSURE_EQUALS( "bad number of erased", twm.erase( make_pair( 1, 2 ) ), 0 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 0 );
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "erase() by position" )
	int2int_t twm;
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 0 );
	int2int_t::insert_result ir = twm.insert( make_pair( 1, 2 ) );
	ENSURE_EQUALS( "bad size", twm.get_size(), 1 );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 1 );
	twm.erase( ir.first );
	ENSURE_EQUALS( "bad count", twm.count( make_pair( 1, 2 ) ), 0 );
	ENSURE_EQUALS( "should have 0 elements", twm.get_size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "equals (==)" )
	int2int_t twm1;
	int2int_t twm2;
	ENSURE_EQUALS( "empty twowaymaps not equal", twm1, twm2 );
	twm1.insert( make_pair( 1, 2 ) );
	ENSURE_NOT( "equality test failed (false positive)", twm1 == twm2 );
	twm2.insert( make_pair( 2, 3 ) );
	ENSURE_NOT( "equality test failed (false positive)", twm1 == twm2 );
	twm2.insert( make_pair( 1, 2 ) );
	ENSURE_NOT( "equality test failed (false positive)", twm1 == twm2 );
	twm1.insert( make_pair( 2, 3 ) );
	ENSURE_EQUALS( "equality test failed (false negative)", twm1, twm2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "constructor with range initialization" )
	typedef HPair<int, int> int_pair_t;
	typedef HArray<int_pair_t> int_pair_array_t;
	int_pair_array_t arr;
	arr.push_back( make_pair( 1, 2) );
	arr.push_back( make_pair( 2, 3) );
	arr.push_back( make_pair( 1, 3) );
	arr.push_back( make_pair( 3, 4) );
	arr.push_back( make_pair( 2, 2) );
	arr.push_back( make_pair( 4, 5) );
	int2int_t twm( arr.begin(), arr.end() );
	int2int_t twmref;
	twmref.insert( make_pair( 4, 5 ) );
	twmref.insert( make_pair( 1, 2 ) );
	twmref.insert( make_pair( 2, 3 ) );
	twmref.insert( make_pair( 3, 4 ) );
	ENSURE_EQUALS( "range constructor failed", twm, twmref );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "assign" )
	typedef HPair<int, int> int_pair_t;
	typedef HArray<int_pair_t> int_pair_array_t;
	int_pair_array_t arr;
	arr.push_back( make_pair( 1, 2) );
	arr.push_back( make_pair( 2, 3) );
	arr.push_back( make_pair( 1, 3) );
	arr.push_back( make_pair( 3, 4) );
	arr.push_back( make_pair( 2, 2) );
	arr.push_back( make_pair( 4, 5) );
	int2int_t twm;
	twm.insert( make_pair( 6, 7 ) );
	twm.assign( arr.begin(), arr.end() );
	int2int_t twmref;
	twmref.insert( make_pair( 4, 5 ) );
	twmref.insert( make_pair( 1, 2 ) );
	twmref.insert( make_pair( 2, 3 ) );
	twmref.insert( make_pair( 3, 4 ) );
	ENSURE_EQUALS( "assign failed", twm, twmref );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "erase() ranged" )
	int2int_t twmref;
	twmref.insert( make_pair( 4, 5 ) );
	twmref.insert( make_pair( 5, 6 ) );
	twmref.insert( make_pair( 1, 2 ) );
	twmref.insert( make_pair( 2, 3 ) );
	twmref.insert( make_pair( 3, 4 ) );
	int2int_t twmref_erased;
	twmref_erased.insert( make_pair( 5, 6 ) );
	twmref_erased.insert( make_pair( 1, 2 ) );
	int2int_t twm;
	twm.insert( make_pair( 1, 2 ) );
	twm.insert( make_pair( 2, 3 ) );
	twm.insert( make_pair( 3, 4 ) );
	twm.insert( make_pair( 4, 5 ) );
	twm.insert( make_pair( 5, 6 ) );
	ENSURE_EQUALS( "assign failed", twm, twmref );
	int2int_t::iterator it( twm.begin() );
	++ it;
	twm.erase( it, twm.rbegin().base() );
	ENSURE_EQUALS( "assign failed", twm, twmref_erased );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "copy constructor" )
	typedef HPair<int, int> int_pair_t;
	int2int_t twmsrc;
	twmsrc.insert( make_pair( 1, 2) );
	twmsrc.insert( make_pair( 2, 3) );
	twmsrc.insert( make_pair( 3, 4) );
	twmsrc.insert( make_pair( 4, 5) );
	int2int_t twmdst( twmsrc );
	ENSURE_EQUALS( "copy constructor failed", twmdst, twmsrc );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "operator = ()" )
	typedef HPair<int, int> int_pair_t;
	int2int_t twmsrc;
	twmsrc.insert( make_pair( 1, 2) );
	twmsrc.insert( make_pair( 2, 3) );
	twmsrc.insert( make_pair( 3, 4) );
	twmsrc.insert( make_pair( 4, 5) );
	int2int_t twmdst;
	ENSURE_NOT( "equality test failed (false positive)", twmdst == twmsrc );
	twmdst.insert( make_pair( 6, 7 ) );
	ENSURE_NOT( "equality test failed (false positive)", twmdst == twmsrc );
	twmdst = twmsrc;
	ENSURE_EQUALS( "assign failed", twmdst, twmsrc );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "left()" )
	int2int_t twm;
	ENSURE( "empty left view iterators", twm.left().begin() == twm.left().end() );
	twm.insert( make_pair( 4, 5) );
	ENSURE( "empty range on view when twowaymap not empty", twm.left().begin() != twm.left().end() );
	twm.insert( make_pair( 1, 2) );
	twm.insert( make_pair( 3, 4) );
	twm.insert( make_pair( 2, 3) );
	copy( twm.left().begin(), twm.left().end(), stream_iterator( cout ) );
	cout << endl;
	copy( twm.right().begin(), twm.right().end(), stream_iterator( cout ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "view methods" )
	int2int_t twm;
	twm.insert( make_pair( 4, 5) );
	twm.insert( make_pair( 1, 2) );
	twm.insert( make_pair( 3, 4) );
	twm.insert( make_pair( 2, 3) );
	ENSURE_EQUALS( "count failed", twm.left().count( 1 ), 1 );
	ENSURE_EQUALS( "count failed", twm.left().count( 2 ), 1 );
	ENSURE_EQUALS( "count failed", twm.left().count( 3 ), 1 );
	ENSURE_EQUALS( "count failed", twm.left().count( 4 ), 1 );
	ENSURE_EQUALS( "count failed", twm.left().count( 5 ), 0 );
	ENSURE_EQUALS( "count failed", twm.right().count( 1 ), 0 );
	ENSURE_EQUALS( "count failed", twm.right().count( 2 ), 1 );
	ENSURE_EQUALS( "count failed", twm.right().count( 3 ), 1 );
	ENSURE_EQUALS( "count failed", twm.right().count( 4 ), 1 );
	ENSURE_EQUALS( "count failed", twm.right().count( 5 ), 1 );
TUT_TEARDOWN()

}


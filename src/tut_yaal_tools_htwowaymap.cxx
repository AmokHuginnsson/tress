/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_htwowaymap.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_htwowaymap : public simple_mock<tut_yaal_tools_htwowaymap>
	{
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

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hmap.cxx - this file is integral part of `tress' project.

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
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hmap
	{
	struct Crazy
		{
		Crazy() { throw 0; }
		};
	typedef HMap<int, int> i2i_t;
	typedef HMap<int, Crazy> i2c_t;
	virtual ~tut_yaal_hcore_hmap( void )
		{}
	};

TUT_TEST_GROUP( tut_yaal_hcore_hmap, "yaal::hcore::HMap" );

TUT_UNIT_TEST( 1, "HMap insert of already existing key")
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

TUT_UNIT_TEST( 2, "exception during map[key] = val;" )
	i2c_t m;
	try
		{
		m[ 0 ] = Crazy();
		FAIL( "FATAL: bad exec path!" );
		}
	catch ( int )
		{
		// ok
		}
	ENSURE_EQUALS( "map extended during m[key] = val; although val evaluation throws.", m.is_empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "sample data" )
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


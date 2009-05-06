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

TUT_TEST_GROUP_N( tut_yaal_hcore_hmap, "yaal::hcore::HMap" );

TUT_UNIT_TEST_N( 1, "HMap insert of already existing key")
	i2i_t m;
	static int const KEY = 1;
	static int const ORIGINAL_VAL = 2;
	static int const NEXT_VAL = 3;
	m.insert( yaal::hcore::make_pair( KEY, ORIGINAL_VAL ) );
	ensure( "element not inserted", m.find( KEY ) != m.end() );
	typedef HPair<i2i_t::iterator, bool> insert_result_t;
	insert_result_t ir = m.insert( yaal::hcore::make_pair( KEY, NEXT_VAL ) );
	ensure_equals( "insertion of already existing key reported successful", ir.second, false );
	ensure_equals( "element with already existing key inserted", ir.first->second, ORIGINAL_VAL );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "exception during map[key] = val;" )
	i2c_t m;
	try
		{
		m[ 0 ] = Crazy();
		fail( "FATAL: bad exec path!" );
		}
	catch ( int const& )
		{
		// ok
		}
	ensure_equals( "map extended during m[key] = val; although val evaluation throws.", m.is_empty(), true );
TUT_TEARDOWN()

}


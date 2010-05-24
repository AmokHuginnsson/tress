/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hmultimap.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hmultimap
	{
	virtual ~tut_yaal_hcore_hmultimap( void ) {}
	typedef HMultiMap<int, int, HMultiContainerStorage::HPacked> mmp_t;
	typedef HMultiMap<int, int, HMultiContainerStorage::HTransparent> mmt_t;
	};

TUT_TEST_GROUP_N( tut_yaal_hcore_hmultimap, "yaal::hcore::HMultiMap" );

TUT_UNIT_TEST_N( 1, "find/upper_bound on non existing" )
	mmp_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	mmp_t const& m = mm;
	for ( mmp_t::const_iterator it = m.find( 2 ), end = m.upper_bound( 2 ); it != end; ++ it )
		FAIL( "find/upper_bound ranges skewed" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "find/upper_bound on existing" )
	mmp_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 2, 7 ) );
	mm.insert( make_pair( 2, 8 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	int acc = 0;
	for ( mmp_t::const_iterator it = mm.find( 2 ), end = mm.upper_bound( 2 ); it != end; ++ it )
		acc += (*it).second;
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", acc, 15 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "modify packed by iterator" )
	mmp_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mmp_t::iterator it = mm.begin();
	int const VERIFY = 0;
	(*it).second = VERIFY;
	mmp_t::iterator it_ver = mm.begin();
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", (*it_ver).second, VERIFY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 31, "find/upper_bound on non existing" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	for ( mmt_t::const_iterator it = mm.find( 2 ), end = mm.upper_bound( 2 ); it != end; ++ it )
		FAIL( "find/upper_bound ranges skewed" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 32, "find/upper_bound on existing" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mm.insert( make_pair( 1, 3 ) );
	mm.insert( make_pair( 2, 7 ) );
	mm.insert( make_pair( 2, 8 ) );
	mm.insert( make_pair( 3, 4 ) );
	mm.insert( make_pair( 3, 5 ) );
	int acc = 0;
	for ( mmt_t::const_iterator it = mm.find( 2 ), end = mm.upper_bound( 2 ); it != end; ++ it )
		acc += (*it).second;
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", acc, 15 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 33, "modify transparent by iterator and operator*" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mmt_t::iterator it = mm.begin();
	int const VERIFY = 0;
	(*it).second = VERIFY;
	mmt_t::iterator it_ver = mm.begin();
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", (*it_ver).second, VERIFY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 34, "modify transparent by iterator and operator->" )
	mmt_t mm;
	mm.insert( make_pair( 1, 2 ) );
	mmt_t::iterator it = mm.begin();
	int const VERIFY = 0;
	it->second = VERIFY;
	mmt_t::iterator it_ver = mm.begin();
	ENSURE_EQUALS( "bad elements selected throu find/upper_bound", (*it_ver).second, VERIFY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 50, "/* sample data */" )
	typedef HMultiMap<HString, int> string_to_int_hmultimap_t;
	string_to_int_hmultimap_t map;
	map.insert( make_pair<HString>( "one", 1 ) );
	map.insert( make_pair<HString>( "two", 2 ) );
	map.insert( make_pair<HString>( "two", 2 ) );
	map.insert( make_pair<HString>( "three", 3 ) );
	map.insert( make_pair<HString>( "three", 3 ) );
	map.insert( make_pair<HString>( "three", 3 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "four", 4 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "five", 5 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "six", 6 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	map.insert( make_pair<HString>( "seven", 7 ) );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "one" ), 1 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "one" )->second, 1 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "two" ), 2 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "two" )->second, 2 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "three" ), 3 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "three" )->second, 3 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "four" ), 4 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "four" )->second, 4 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "five" ), 5 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "five" )->second, 5 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "six" ), 6 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "six" )->second, 6 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.count( "seven" ), 7 );
	ENSURE_EQUALS( "failed to insert insert (data)", map.lower_bound( "seven" )->second, 7 );
	ENSURE_EQUALS( "failed to insert insert (size)", map.size(), 1 + 2 + 3 + 4 + 5 + 6 + 7 );
TUT_TEARDOWN()

}


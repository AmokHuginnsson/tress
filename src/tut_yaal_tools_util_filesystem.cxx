/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_util_filesystem.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/util.hxx>
#include <yaal/tools/assign.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_util_filesystem );
TUT_TEST_GROUP( tut_yaal_tools_util_filesystem, "yaal::tools::utils::filesystem" );

TUT_UNIT_TEST( 1, "find" )
	filesystem::find_result fr( filesystem::find( "./data", ".*\\.sql" ) );
	sort( fr.begin(), fr.end() );
	filesystem::find_result expected = array<HString>( "./data/firebird.sql", "./data/mysql.sql", "./data/oracle.sql", "./data/postgresql.sql", "./data/sqlite.sql" );
	ENSURE_EQUALS( "filesystem::find failed", fr, expected );
TUT_TEARDOWN()

}

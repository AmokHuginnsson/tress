/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_filesystem.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/filesystem.hxx>
#include <yaal/tools/assign.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::filesystem;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_filesystem );
TUT_TEST_GROUP( tut_yaal_tools_filesystem, "yaal::tools::filesystem" );

TUT_UNIT_TEST( "normalize_path" )
	ENSURE_EQUALS( normalize_path( "" ),                                 "" );
	ENSURE_EQUALS( normalize_path( "/" ),                                "/" );
	ENSURE_EQUALS( normalize_path( ".." ),                               ".." );
	ENSURE_EQUALS( normalize_path( "/.." ),                              "/" );
	ENSURE_EQUALS( normalize_path( "../" ),                              ".." );
	ENSURE_EQUALS( normalize_path( "." ),                                "" );
	ENSURE_EQUALS( normalize_path( "./" ),                               "" );
	ENSURE_EQUALS( normalize_path( "./." ),                              "" );
	ENSURE_EQUALS( normalize_path( "/." ),                               "/" );
	ENSURE_EQUALS( normalize_path( "./.." ),                             ".." );
	ENSURE_EQUALS( normalize_path( "//" ),                               "/" );
	ENSURE_EQUALS( normalize_path( "../." ),                             ".." );
	ENSURE_EQUALS( normalize_path( "../.." ),                            "../.." );
	ENSURE_EQUALS( normalize_path( "../../" ),                           "../.." );
	ENSURE_EQUALS( normalize_path( "/../.." ),                           "/" );
	ENSURE_EQUALS( normalize_path( ".././." ),                           ".." );
	ENSURE_EQUALS( normalize_path( "/././." ),                           "/" );
	ENSURE_EQUALS( normalize_path( "/./././" ),                          "/" );
	ENSURE_EQUALS( normalize_path( "/././.././" ),                       "/" );
	ENSURE_EQUALS( normalize_path( "././././" ),                         "" );
	ENSURE_EQUALS( normalize_path( "./././.././" ),                      ".." );
	ENSURE_EQUALS( normalize_path( "///" ),                              "/" );
	ENSURE_EQUALS( normalize_path( "///.." ),                            "/" );
	ENSURE_EQUALS( normalize_path( "///." ),                             "/" );
	ENSURE_EQUALS( normalize_path( "a" ),                                "a" );
	ENSURE_EQUALS( normalize_path( "/a" ),                               "/a" );
	ENSURE_EQUALS( normalize_path( "a/" ),                               "a" );
	ENSURE_EQUALS( normalize_path( "./a/" ),                             "a" );
	ENSURE_EQUALS( normalize_path( "./a/." ),                            "a" );
	ENSURE_EQUALS( normalize_path( "/a/." ),                             "/a" );
	ENSURE_EQUALS( normalize_path( "a/." ),                              "a" );
	ENSURE_EQUALS( normalize_path( "a/b" ),                              "a/b" );
	ENSURE_EQUALS( normalize_path( "/a/b" ),                             "/a/b" );
	ENSURE_EQUALS( normalize_path( "a///b" ),                            "a/b" );
	ENSURE_EQUALS( normalize_path( "a/./b" ),                            "a/b" );
	ENSURE_EQUALS( normalize_path( "/a/../b/../" ),                      "/" );
	ENSURE_EQUALS( normalize_path( "a/../b/../" ),                       "" );
	ENSURE_EQUALS( normalize_path( "./a/./b/./" ),                       "a/b" );
	ENSURE_EQUALS( normalize_path( "./a/./b/." ),                        "a/b" );
	ENSURE_EQUALS( normalize_path( "../a/../b/../" ),                    ".." );
	ENSURE_EQUALS( normalize_path( "a/b/.." ),                           "a" );
	ENSURE_EQUALS( normalize_path( "a/b/../" ),                          "a" );
	ENSURE_EQUALS( normalize_path( "a/b/../." ),                         "a" );
	ENSURE_EQUALS( normalize_path( "/a/b/.." ),                          "/a" );
	ENSURE_EQUALS( normalize_path( "/a/b/../" ),                         "/a" );
	ENSURE_EQUALS( normalize_path( "/a/b/../." ),                        "/a" );
	ENSURE_EQUALS( normalize_path( "a/b/../.." ),                        "" );
	ENSURE_EQUALS( normalize_path( "a/b/../../" ),                       "" );
	ENSURE_EQUALS( normalize_path( "a/b/../../." ),                      "" );
	ENSURE_EQUALS( normalize_path( "a/./b/../.." ),                      "" );
	ENSURE_EQUALS( normalize_path( "a/b/.././../" ),                     "" );
	ENSURE_EQUALS( normalize_path( "a/./b/.././../." ),                  "" );
	ENSURE_EQUALS( normalize_path( "/a/b/../.." ),                       "/" );
	ENSURE_EQUALS( normalize_path( "/a/b/../../" ),                      "/" );
	ENSURE_EQUALS( normalize_path( "/a/b/../../." ),                     "/" );
	ENSURE_EQUALS( normalize_path( "/a/b/c/././././../../" ),            "/a" );
	ENSURE_EQUALS( normalize_path( "./a/b/c/././././../../" ),           "a" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e" ),                    "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/" ),                   "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/." ),                  "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/./.d./e" ),                  "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/.." ),                 "a/b./.c/.d." );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/../.." ),              "a/b./.c" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/../../.." ),           "a/b." );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/../../../.." ),        "a" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/../../../../.." ),     "" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d./e/../../../../../.." ),  ".." );
	ENSURE_EQUALS( normalize_path( "a/b././.c/.d./e" ),                  "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/.d././e" ),                  "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b././.c/./.d./e" ),                "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a//b.///.c////.d./////e" ),          "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b./../.c/../.d./../e" ),           "a/e" );
	ENSURE_EQUALS( normalize_path( "a/b./.c/../../../../../../.d./e" ),  "../../../.d./e" );
	ENSURE_EQUALS( normalize_path( "a/../b./../.c/../.d./../e/.." ),     "" );
	ENSURE_EQUALS( normalize_path( "./a/b./.c/.d./e" ),                  "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "./a/b./.c/.d./e/." ),                "a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e" ),                   "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/" ),                  "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/." ),                 "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/./.d./e" ),                 "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/.." ),                "/a/b./.c/.d." );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/../.." ),             "/a/b./.c" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/../../.." ),          "/a/b." );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/../../../.." ),       "/a" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/../../../../.." ),    "/" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d./e/../../../../../.." ), "/" );
	ENSURE_EQUALS( normalize_path( "/a/b././.c/.d./e" ),                 "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/.d././e" ),                 "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b././.c/./.d./e" ),               "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a//b.///.c////.d./////e" ),         "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/b./../.c/../.d./../e" ),          "/a/e" );
	ENSURE_EQUALS( normalize_path( "/a/b./.c/../../../../../../.d./e" ), "/.d./e" );
	ENSURE_EQUALS( normalize_path( "/a/../b./../.c/../.d./../e/.." ),    "/" );
	ENSURE_EQUALS( normalize_path( "/./a/b./.c/.d./e" ),                 "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/./a/b./.c/.d./e/." ),               "/a/b./.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "/./a/b./.../.c/.d./e/." ),           "/a/b./.../.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "..././a/b./.../.c/.d./e/." ),        ".../a/b./.../.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "..././a/b./.../.c/.d./e/..." ),      ".../a/b./.../.c/.d./e/..." );
	ENSURE_EQUALS( normalize_path( "/./a/b./../.../.c/.d./e/." ),        "/a/.../.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "./a/b./.../.../../.c/.d./e/." ),     "a/b./.../.c/.d./e" );
	ENSURE_EQUALS( normalize_path( "a/b../..c/..d../e" ),                "a/b../..c/..d../e" );
	ENSURE_EQUALS( normalize_path( "a/../../b/../../c" ),                "../../c" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "dirname" )
	ENSURE_EQUALS( dirname( "/usr/lib" ), "/usr" );
	ENSURE_EQUALS( dirname( "/usr/" ),    "/" );
	ENSURE_EQUALS( dirname( "usr" ),      "." );
	ENSURE_EQUALS( dirname( "/" ),        "/" );
	ENSURE_EQUALS( dirname( "." ),        "." );
	ENSURE_EQUALS( dirname( ".." ),       "." );

	ENSURE_EQUALS( dirname( "/home/amok/Makefile" ), "/home/amok" );
	ENSURE_EQUALS( dirname( "src/yaal/_aux/" ),      "src/yaal" );
	ENSURE_EQUALS( dirname( "src/yaal/_aux" ),       "src/yaal" );
	ENSURE_EQUALS( dirname( "/some/path/../../" ),   "/some/path/.." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "basename" )
	ENSURE_EQUALS( filesystem::basename( "/usr/lib" ), "lib" );
	ENSURE_EQUALS( filesystem::basename( "/usr/" ),    "usr" );
	ENSURE_EQUALS( filesystem::basename( "usr" ),      "usr" );
	ENSURE_EQUALS( filesystem::basename( "/" ),        "/" );
	ENSURE_EQUALS( filesystem::basename( "." ),        "." );
	ENSURE_EQUALS( filesystem::basename( ".." ),       ".." );
	ENSURE_EQUALS( filesystem::basename( "/../" ),     ".." );

	ENSURE_EQUALS( filesystem::basename( "/home/amok/Makefile" ), "Makefile" );
	ENSURE_EQUALS( filesystem::basename( "src/yaal/_aux/" ),      "_aux" );
	ENSURE_EQUALS( filesystem::basename( "src/yaal/_aux" ),       "_aux" );
	ENSURE_EQUALS( filesystem::basename( "/some/path/../../" ),   ".." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "create_directory" )
	char const dirA[] = "../tress/out/a";
	char const dirAB[] = "../tress/out/a/b";
	ENSURE_THROW( "nested dir created", create_directory( dirAB, 0700, DIRECTORY_MODIFICATION::EXACT ), HFileSystemException );
	create_directory( dirA, 0700, DIRECTORY_MODIFICATION::EXACT );
	ENSURE( "failed to create directory a", is_directory( dirA ) );
	create_directory( dirAB, 0700, DIRECTORY_MODIFICATION::EXACT );
	ENSURE( "failed to create directory a/b", is_directory( dirAB ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove_directory" )
	char const dirA[] = "../tress/out/a";
	char const dirAB[] = "../tress/out/a/b";
	ENSURE_THROW( "removed nested dir", remove_directory( dirA, DIRECTORY_MODIFICATION::EXACT ), HFileSystemException );
	remove_directory( dirAB, DIRECTORY_MODIFICATION::EXACT );
	ENSURE_NOT( "failed to remove directory", is_directory( dirAB ) );
	remove_directory( dirA, DIRECTORY_MODIFICATION::EXACT );
	ENSURE_NOT( "failed to remove directory", is_directory( dirA ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "create_directory (recursive)" )
	char const dir[] = "../tress/out/a/b";
	create_directory( dir, 0700, DIRECTORY_MODIFICATION::RECURSIVE );
	ENSURE( "failed to create directory", is_directory( dir ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove_directory (recursive)" )
	char const dir[] = "../tress/out/a";
	remove_directory( dir, DIRECTORY_MODIFICATION::RECURSIVE );
	ENSURE_NOT( "failed to remove directory", is_directory( dir ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find" )
	filesystem::find_result fr( filesystem::find( "./data", ".*\\.sql" ) );
	sort( fr.begin(), fr.end() );
	filesystem::find_result expected = array<HString>( "./data/firebird.sql", "./data/mysql.sql", "./data/oracle.sql", "./data/postgresql.sql", "./data/sqlite.sql" );
	ENSURE_EQUALS( "filesystem::find failed", fr, expected );
TUT_TEARDOWN()

}


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

#ifndef __MSVCXX__
TUT_UNIT_TEST( "readlink" )
	ENSURE_EQUALS( filesystem::readlink( "./data/libtressplugin-d.so" ), "../build/debug/tressplugin/1exec" );
	ENSURE_EQUALS( filesystem::readlink( "./data/libtressplugin.so" ), "../build/release/tressplugin/1exec" );
	ENSURE_THROW( "readlink on non-existing succeeded", filesystem::readlink( "./data/libtressplugin-x.so" ), HFileSystemException );
TUT_TEARDOWN()
#endif

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
	ENSURE_NOT( "failed to remove directory", exists( dirAB ) );
	remove_directory( dirA, DIRECTORY_MODIFICATION::EXACT );
	ENSURE_NOT( "failed to remove directory", exists( dirA ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "create_directory (recursive)" )
	char const dir[] = "../tress/out/a/b";
	create_directory( dir, 0700, DIRECTORY_MODIFICATION::RECURSIVE );
	ENSURE( "failed to create directory", is_directory( dir ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove_directory (recursive)" )
	char const dir[] = "../tress/out/a";
	remove_directory( dir, DIRECTORY_MODIFICATION::RECURSIVE );
	ENSURE_NOT( "failed to remove directory", exists( dir ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find" )
	filesystem::find_result fr( filesystem::find( "./data", ".*\\.sql" ) );
	sort( fr.begin(), fr.end() );
	filesystem::find_result expected = array<HString>( "./data/firebirdV2.sql", "./data/firebirdV3.sql", "./data/mysql.sql", "./data/oracle.sql", "./data/postgresql.sql", "./data/sqlite.sql" );
	ENSURE_EQUALS( "filesystem::find failed", fr, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "current_working_directory" )
	ENSURE_EQUALS( "current_working_directory failed", basename( current_working_directory() ), "tress" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "exists" )
	ENSURE( "exists (existing) failed", exists( "./data/karatsuba.bc" ) );
	ENSURE_NOT( "exists (non-existing) failed", exists( "./data/non-existing" ) );
TUT_TEARDOWN()

#ifndef __MSVCXX__
TUT_UNIT_TEST( "is_symbolic_link" )
	ENSURE( "is_symbolic_link (on symlink) failed", is_symbolic_link( "./data/broken" ) );
	ENSURE( "is_symbolic_link (on symlink) failed", is_symbolic_link( "./data/libtressplugin-d.so" ) );
	ENSURE_NOT( "is_symbolic_link (on non-symlink) failed", is_symbolic_link( "./data/karatsuba.bc" ) );
TUT_TEARDOWN()
#endif /* #ifndef __MSVCXX__ */

TUT_UNIT_TEST( "file_size" )
	ENSURE_EQUALS( "file_size failed", file_size( "./data/karatsuba.bc" ), 1137 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rename" )
	char const nf[] = "./out/name-from";
	char const nt[] = "./out/name-to";
	remove( nf );
	remove( nt );
	ENSURE_NOT( "incositent state, failed to remove name-from", exists( nf ) );
	ENSURE_NOT( "incositent state, failed to remove name-to", exists( nt ) );
	HFile f( nf, HFile::OPEN::WRITING );
	f.close();
	ENSURE( "incositent state, failed to create name-from", exists( nf ) );
	filesystem::rename( nf, nt );
	ENSURE_NOT( "rename failed", exists( nf ) );
	ENSURE( "rename failed", exists( nt ) );
TUT_TEARDOWN()

}


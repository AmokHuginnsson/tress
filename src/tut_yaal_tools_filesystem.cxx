/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/filesystem.hxx>
#include <yaal/tools/hfsitem.hxx>
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
	/* ./ prefix */ {
		filesystem::paths_t fr( filesystem::find( "./data", ".*\\.sql$" ) );
		sort( fr.begin(), fr.end() );
		filesystem::paths_t expected = array<HString>( "./data/firebirdV2.sql", "./data/firebirdV3.sql", "./data/mysql.sql", "./data/oracle.sql", "./data/postgresql.sql", "./data/sqlite.sql" );
		ENSURE_EQUALS( "filesystem::find failed", fr, expected );
	}
	/* no prefix */ {
		filesystem::paths_t fr( filesystem::find( "data", ".*\\.sql$" ) );
		sort( fr.begin(), fr.end() );
		filesystem::paths_t expected = array<HString>( "data/firebirdV2.sql", "data/firebirdV3.sql", "data/mysql.sql", "data/oracle.sql", "data/postgresql.sql", "data/sqlite.sql" );
		ENSURE_EQUALS( "filesystem::find failed", fr, expected );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "glob_to_re" )
	ENSURE_EQUALS( "glob_to_re 'ab' failed", glob_to_re( "ab" ), "^[a][b]$" );
	ENSURE_EQUALS( "glob_to_re 'a*b' failed", glob_to_re( "a*b" ), "^[a].*[b]$" );
	ENSURE_EQUALS( "glob_to_re 'a?b' failed", glob_to_re( "a?b" ), "^[a].[b]$" );
	ENSURE_EQUALS( "glob_to_re 'a\\*b' failed", glob_to_re( "a\\*b" ), "^[a][*][b]$" );
	ENSURE_EQUALS( "glob_to_re 'a\\?b' failed", glob_to_re( "a\\?b" ), "^[a][?][b]$" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "glob" )
	/* ./ prefix */ {
		filesystem::paths_t gr( filesystem::glob( "./*d*/*.cxx" ) );
		filesystem::paths_t expected = array<HString>( "child/main.cxx", "child/options.cxx", "child/setup.cxx", "data/child.cxx", "data/huginn_greeter.cxx", "data/plugin.cxx" );
		ENSURE_EQUALS( "filesystem::glob failed", gr, expected );
	}
	/* no prefix */ {
		filesystem::paths_t gr( filesystem::glob( "*d*/*.cxx" ) );
		filesystem::paths_t expected = array<HString>( "child/main.cxx", "child/options.cxx", "child/setup.cxx", "data/child.cxx", "data/huginn_greeter.cxx", "data/plugin.cxx" );
		ENSURE_EQUALS( "filesystem::glob failed", gr, expected );
	}
	/* no prefix, no glob on path */ {
		filesystem::paths_t gr( filesystem::glob( "data/*.cxx" ) );
		filesystem::paths_t expected = array<HString>( "data/child.cxx", "data/huginn_greeter.cxx", "data/plugin.cxx" );
		ENSURE_EQUALS( "filesystem::glob failed", gr, expected );
	}
	/* absolute path, no glob on path */ {
		filesystem::path_t cwd( filesystem::current_working_directory() );
		cwd.replace( "\\", "/" );
		filesystem::paths_t gr( filesystem::glob( cwd + "/data/*.cxx" ) );
		filesystem::paths_t expected = array<HString>( cwd + "/data/child.cxx", cwd + "/data/huginn_greeter.cxx", cwd + "/data/plugin.cxx" );
		ENSURE_EQUALS( "filesystem::glob failed", gr, expected );
	}
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

TUT_UNIT_TEST( "update_times" )
	char const n[] = "./out/utimes.ext";
	HFile f( n, HFile::OPEN::WRITING );
	f.close();
	HTime bday( 1978, 5, 24, 23, 30, 17 );
	HTime cons( 1989, 8, 25, 14, 11, 22 );
	filesystem::update_times( n, bday, cons );
	HFSItem fi( n );
	ENSURE_EQUALS( "update_times (mod) failed", fi.modified(), bday );
	ENSURE_EQUALS( "update_times (access) failed", fi.accessed(), cons );
TUT_TEARDOWN()

}


/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>
#include <TUT/tut.hpp>

#include <yaal/tools/hfsitem.hxx>
#include <yaal/tools/filesystem.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::filesystem;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_filesystem : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_filesystem( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_filesystem, "yaal::tools::HHuginn.FileSystem" );

namespace {

char const FILENAME[] = "./out/huginn-file.dat";
char const FILENAME_MOVED[] = "./out/huginn-file.alt";
char const DATA[] = "huginn-data";
char const DATA_APPEND[] = "huginn-data-append";

}

TUT_UNIT_TEST( "FileSystem" )
#ifdef __MSVCXX__
	char const openRes[] = "\"*anonymous stream*:1:44: The system cannot find the file specified: ./out/non-existing\"";
#else
	char const openRes[] = "\"*anonymous stream*:1:44: No such file or directory: ./out/non-existing\"";
#endif
	ENSURE_EQUALS(
		"open non-existing succeeded",
		execute(
			"import FileSystem as fs;"
			"main() {"
			"try{"
			"fs.open( \"./out/non-existing\", fs.OPEN_MODE.READ );"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		openRes
	);
	try {
		filesystem::remove( FILENAME );
	} catch ( HFileSystemException const& ) {
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "write+read" )
	execute(
		"import FileSystem as fs;"
		"main(){"
		"f=fs.open(\""_ys.append( FILENAME ).append( "\",fs.OPEN_MODE.WRITE);"
		"f.write_line(\"" ).append( DATA ).append( "\");"
		"return(0);"
		"}" )
	);
	HFile f( FILENAME, HFile::OPEN::READING );
	hcore::HString line;
	getline( f, line );
	f.close();
	ENSURE_EQUALS( "bad write from Huginn.FileSystem", line, DATA );
	ENSURE_EQUALS(
		"bad read from Huginn.FileSystem",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"f=fs.open(\""_ys.append( FILENAME ).append( "\",fs.OPEN_MODE.READ);"
			"return(f.read_line());"
			"}" )
		),
		"\""_ys.append( DATA ).append( '"' )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "append" )
	execute(
		"import FileSystem as fs;"
		"main(){"
		"f=fs.open(\""_ys.append( FILENAME ).append( "\",fs.OPEN_MODE.APPEND);"
		"f.write_line(\"" ).append( DATA_APPEND ).append( "\");"
		"return(0);"
		"}" )
	);
	HFile f( FILENAME, HFile::OPEN::READING );
	hcore::HString line;
	getline( f, line );
	f.close();
	ENSURE_EQUALS( "bad append from Huginn.FileSystem", line, to_string( DATA ) + DATA_APPEND );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rename" )
	execute(
		"import FileSystem as fs;"
		"main(){"
		"fs.rename(\""_ys.append( FILENAME ).append( "\",\"" ).append( FILENAME_MOVED ).append( "\");"
		"return(0);"
		"}" )
	);
	ENSURE_NOT( "Huginn.FileSystem.rename failed (src)", filesystem::exists( FILENAME ) );
	ENSURE( "Huginn.FileSystem.rename failed (dst)", filesystem::exists( FILENAME_MOVED ) );
#ifdef __MSVCXX__
	char const renameExpect[] = "\"*anonymous stream*:1:45: Failed to rename: `non-existing-a' to `non-existing-b': The system cannot find the file specified\"";
#else
	char const renameExpect[] = "\"*anonymous stream*:1:45: Failed to rename: `non-existing-a' to `non-existing-b': No such file or directory\"";
#endif
	ENSURE_EQUALS(
		"invalid rename succeeded",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"try{"
			"fs.rename(\"non-existing-a\",\"non-existing-b\");"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		renameExpect
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "chmod" )
#ifndef __MSVCXX__
	execute(
		"import FileSystem as fs;"
		"main(){"
		"fs.chmod(\""_ys.append( FILENAME_MOVED ).append( "\",0660);"
		"return(0);"
		"}" )
	);
	ENSURE_EQUALS( "Huginn.FileSystem.chmod failed", HFSItem( FILENAME_MOVED ).get_permissions(), 0660 );
#endif
	ENSURE_EQUALS(
		"invalid chmod succeeded",
		execute_except(
			"import FileSystem as fs;"
			"main(){"
			"fs.chmod(\""_ys.append( FILENAME_MOVED ).append( "\",017777);"
			"return(0);"
			"}" )
		),
		"*anonymous stream*:1:40: Bad mode: 8191"
	);
#ifdef __MSVCXX__
	char const chmodExpect[] = "\"*anonymous stream*:1:44: chmod failed: `non-existing': The system cannot find the file specified\"";
#else
	char const chmodExpect[] = "\"*anonymous stream*:1:44: chmod failed: `non-existing': No such file or directory\"";
#endif
	ENSURE_EQUALS(
		"invalid chmod succeeded",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"try{"
			"fs.chmod(\"non-existing\",0700);"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		chmodExpect
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove" )
	execute(
		"import FileSystem as fs;"
		"main(){"
		"fs.remove(\""_ys.append( FILENAME_MOVED ).append( "\");"
		"return(0);"
		"}" )
	);
	ENSURE_NOT( "Huginn.FileSystem.remove failed", filesystem::exists( FILENAME_MOVED ) );
#if defined( __HOST_OS_TYPE_FREEBSD__ ) || defined( __HOST_OS_TYPE_CYGWIN__ )
		char const removeRes[] = "\"*anonymous stream*:1:45: Failed to remove: `./out': Operation not permitted\"";
#elif defined( __MSVCXX__ )
		char const removeRes[] = "\"*anonymous stream*:1:45: Failed to remove: `./out': The data is invalid\"";
#elif defined( __HOST_OS_TYPE_SOLARIS__ )
		char const removeRes[] = "\"*anonymous stream*:1:45: Failed to remove: `./out': Not owner\"";
#else
		char const removeRes[] = "\"*anonymous stream*:1:45: Failed to remove: `./out': Is a directory\"";
#endif
	ENSURE_EQUALS(
		"invalid remove succeeded",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"try{"
			"fs.remove(\"./out\");"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		removeRes
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "readlink" )
	ENSURE_EQUALS(
		"FileSystem.dirname, FileSystem.basename, FileSystem.readlink, FileSystem.current_working_directory failed",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"return([fs.basename(fs.current_working_directory()),fs.dirname(\""_ys.append( FILENAME ).append( "\"),fs.readlink(\"./data/broken\")]);"
			"}" )
		),
		"[\"tress\", \"./out\", \"non-existing\"]"
	);
#ifdef __MSVCXX__
	char const readlinkExpect[] = "\"*anonymous stream*:1:47: readlink failed: `non-existing': The operation completed successfully\"";
#else
	char const readlinkExpect[] = "\"*anonymous stream*:1:47: readlink failed: `non-existing': No such file or directory\"";
#endif
	ENSURE_EQUALS(
		"invalid readlink succeeded",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"try{"
			"fs.readlink(\"non-existing\");"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		readlinkExpect
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "dir" )
	ENSURE_EQUALS(
		"FileSystem.dir failed",
		execute(
			"import FileSystem as fs;"
			"import Algorithms as algo;"
			"main(){"
			"return(algo.sorted(fs.dir(\"./FCTF\")));"
			"}"
		),
		"[\"a0_target-default.mk\", \"acxx\", \"make.mk\"]"
	);
#ifdef __MSVCXX__
	char const dirExpect[] = "\"*anonymous stream*:1:42: non-existing: The system cannot find the file specified\"";
#else
	char const dirExpect[] = "\"*anonymous stream*:1:42: non-existing: No such file or directory\"";
#endif
	ENSURE_EQUALS(
		"invalid dir succeeded",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"try{"
			"fs.dir(\"non-existing\");"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		dirExpect
	);
	ENSURE_EQUALS(
		"FileSystem.dir size succeeded",
		execute_except(
			"import FileSystem as fs;\n"
			"main(){\n"
			"ds = fs.dir(\"./FCTF\");\n"
			"return(size(ds));\n"
			"}"
		),
		"*anonymous stream*:4:12: Getting size of `DirectoryScan' is an invalid operation."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "stat" )
	HFSItem fi( "./data/karatsuba.bc" );
#ifdef __MSVCXX__
	int perm( 0666 );
	char const nonExtErr[] = "The system cannot find the file specified";
#else
	int perm( 0600 );
	char const nonExtErr[] = "No such file or directory";
#endif
	ENSURE_EQUALS(
		"FileSystem.stat failed",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"s=fs.stat(\"./data/karatsuba.bc\");"
			"return([s.id(),s.name(),s.size(),s.mode(),s.type(),s.user(),s.group(),string(s.modified())]);"
			"}"
		),
		"["_ys.append( fi.id() )
			.append( ", \"./data/karatsuba.bc\", 1137, " )
			.append( perm )
			.append( ", fs.FILE_TYPE.REGULAR, \"" )
			.append( fi.get_user() )
			.append( "\", \"" )
			.append( fi.get_group() )
			.append( "\", \"" )
			.append( fi.modified().string() )
			.append( "\"]" )
	);
	char const methods[][16] = {
		"id", "name", "size", "mode", "user", "group", "modified"
	};
	for ( char const* m : methods ) {
		clog << "m = " << m << endl;
		ENSURE_EQUALS(
			"invalid stat succeeded",
			execute(
				"import FileSystem as fs;\n"
				"main(){\n"
				"try{"
				"fs.stat(\"non-existing\")."_ys.append( m ).append( "();\n"
				"}catch(FileSystemException e){"
				"return ( e.message() );"
				"}"
				"}\n" )
			),
			"\"*anonymous stream*:3:"_ys.append( 29 + strlen( m ) ).append( ": non-existing: " ).append( nonExtErr ).append( "\"" )
		);
	}
	ENSURE_EQUALS(
		"invalid stat().type() succeeded",
		execute(
			"import FileSystem as fs;\n"
			"main(){\n"
			"try{"
			"fs.stat(\"non-existing\").type();\n"
			"}catch(FileSystemException e){"
			"return ( e.message() );"
			"}"
			"}\n"
		),
		"\"*anonymous stream*:3:33: Cannot acquire metadata for `non-existing': "_ys.append( nonExtErr ).append( "\"" )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "exists" )
	ENSURE_EQUALS(
		"invalid exists",
		execute(
			"import FileSystem as fs;\n"
			"main(){\n"
			"return ( [fs.exists(\"data/karatsuba.bc\"), fs.exists(\"data/non-existing\")] );"
			"}\n"
		),
		"[true, false]"
	);
TUT_TEARDOWN()

}


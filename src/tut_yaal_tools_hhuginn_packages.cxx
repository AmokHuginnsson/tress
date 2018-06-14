/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>
#include <csignal>
#include <TUT/tut.hpp>

#include <yaal/hcore/hsocket.hxx>
#include <yaal/hcore/hformat.hxx>
#include <yaal/hcore/hcore.hxx>
#include <yaal/tools/hhuginn.hxx>
#include <yaal/tools/hiodispatcher.hxx>
#include <yaal/tools/hmonitor.hxx>
#include <yaal/tools/filesystem.hxx>
#include <yaal/tools/hfsitem.hxx>
#include <yaal/tools/stringalgo.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hstringstream.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::filesystem;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_packages : public tress::tut_yaal_tools_hhuginn_base {
	static int const OBSCURE_PORT = 61930;
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_packages, "yaal::tools::HHuginn,packages" );

TUT_UNIT_TEST( "Algorithms" )
	ENSURE_EQUALS(
		"Algorithms.iterator failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"i = algo.iterator(l);"
			"return(algo.materialize(algo.zip(i,i), list));"
			"}"
		),
		"[(2, 3), (5, 7), (11, 13), (17, 19)]"
	);
	ENSURE_EQUALS(
		"Algorithms.iterator failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"i = algo.iterator(l);"
			"res = [];"
			"while(i.is_valid()) {"
			"res.push(i.value());"
			"i.next();"
			"}"
			"return(res);"
			"}"
		),
		"[2, 3, 5, 7, 11, 13, 17, 19]"
	);
	ENSURE_EQUALS(
		"Algorithms.iterator failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l=[2,3,5];\n"
			"i = algo.iterator(l);\n"
			"ci = copy( i );\n"
			"l.push(7);\n"
			"res = [];"
			"res.push( size( i ) );\n"
			"res.push( algo.materialize( i, list ) );\n"
			"res.push( algo.materialize( ci, list ) );\n"
			"return(res);"
			"}"
		),
		"[4, [2, 3, 5, 7], [2, 3, 5]]"
	);
	ENSURE_EQUALS(
		"Algorithms.zip failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l1=[2,3,5,7,11,13,17,19];"
			"l2=[2,4,8,16,32,64,128,256];"
			"z=algo.zip(l1,l2);"
			"r = [];"
			"for(x : copy(z)) {"
			"r.push(x);"
			"}"
			"return((r,size(z)));"
			"}"
		),
		"([(2, 2), (3, 4), (5, 8), (7, 16), (11, 32), (13, 64), (17, 128), (19, 256)], 8)"
	);
	ENSURE_EQUALS(
		"Algorithms.zip failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"i=algo.iterator(algo.zip(l));"
			"r = [];"
			"r.push(i.value());"
			"i.is_valid();"
			"r.push(i.value());"
			"return(r);"
			"}"
		),
		"[(2,), (2,)]"
	);
	ENSURE_EQUALS(
		"Algorithms.zip failed",
		execute_except(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5];"
			"i=algo.iterator(l);"
			"i=algo.iterator(algo.zip(i,i));"
			"r = [];"
			"r.push(i.value());"
			"i.next();"
			"r.push(i.value());"
			"return(r);"
			"}"
		),
		"*anonymous stream*:1:142: Getting value from an invalid iterator."
	);
	ENSURE_EQUALS(
		"Algorithms.enumerate failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"e=algo.enumerate(l,100);"
			"r = [];"
			"for(x : copy(e)) {"
			"r.push(x);"
			"}"
			"return((r,size(e)));"
			"}"
		),
		"([(100, 2), (101, 3), (102, 5), (103, 7), (104, 11), (105, 13), (106, 17), (107, 19)], 8)"
	);
	ENSURE_EQUALS(
		"Algorithms.map (fun) failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[];"
			"m=algo.map([3, 17, 4],@(x){x*x;});"
			"for(x : copy(m)) {"
			"l.push(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[9, 289, 16], 3]"
	);
	ENSURE_EQUALS(
		"Algorithms.map (method) failed",
		execute(
			"import Algorithms as algo;"
			"class M {\n"
			"do(x){\n"
			"return(x*x);\n"
			"}\n"
			"}\n"
			"main(){"
			"l=[];"
			"m=algo.map([3, 17, 4],M().do);"
			"for(x : copy(m)) {"
			"l.push(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[9, 289, 16], 3]"
	);
	ENSURE_EQUALS(
		"Algorithms.map (ubound method) failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[\"ala\",\"ma\",\"kota\"];"
			"m=algo.map(l,string.to_upper);"
			"l=[];\n"
			"for(x : copy(m)) {"
			"l.push(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[\"ALA\", \"MA\", \"KOTA\"], 3]"
	);
	ENSURE_EQUALS(
		"Algorithms.range failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"s=\"\";"
			"r = algo.range(3, 17, 4);"
			"for(x : copy(r)) {"
			"s=s+\":\"+string(x);"
			"}"
			"return([s,size(r)]);"
			"}"
		),
		"[\":3:7:11:15\", 4]"
	);
	ENSURE_EQUALS(
		"Algorithms.range invalid succeeded",
		execute_except(
			"import Algorithms as algo;"
			"main(){"
			"algo.range(1,2,-1);"
			"}"
		),
		"*anonymous stream*:1:44: Invalid range."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to tuple) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),tuple));\n"
			"}"
		),
		"(3, 7, 11, 15)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to list) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),list));\n"
			"}"
		),
		"[3, 7, 11, 15]"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to deque) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),deque));\n"
			"}"
		),
		"deque(3, 7, 11, 15)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to order) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),order));\n"
			"}"
		),
		"order(3, 7, 11, 15)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to set) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),set));\n"
			"}"
		),
		"{15, 3, 7, 11}"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize on invalid succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([],integer);\n"
			"}"
		),
		"*anonymous stream*:3:17: Invalid materialized type: `integer'."
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (function) failed",
		execute(
			"import Algorithms as algo;\n"
			"class R {\n"
			"do(x,y){\n"
			"return(x+y);\n"
			"}\n"
			"}\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),R().do));\n"
			"}"
		),
		"36"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (method) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),list.push,[]));\n"
			"}"
		),
		"[3, 7, 11, 15]"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (method) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),@(x,y){x+y;}));\n"
			"}"
		),
		"36"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce on empty succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.reduce([],@(x,y){x+y;});\n"
			"}"
		),
		"*anonymous stream*:3:12: reduce() on empty."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (function) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"f=algo.filter(algo.range(3, 44, 4),@(x){x%3==0;});\n"
			"return(size(f));\n"
			"}"
		),
		"*anonymous stream*:4:12: Getting size of `Filter' is an invalid operation."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (invalid function) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),@(x){x;}),list));\n"
			"}"
		),
		"*anonymous stream*:3:24: Filter function returned wrong type, expected `boolean' got: `integer'."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (function) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),@(x){x%3==0;}),list));\n"
			"}"
		),
		"[3, 15, 27, 39]"
	);
	ENSURE_EQUALS(
		"Algorithms.filter (method) failed",
		execute(
			"import Algorithms as algo;\n"
			"class F {\n"
			"do(x){\n"
			"return(x%3==0);\n"
			"}\n"
			"}\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),F().do),list));\n"
			"}"
		),
		"[3, 15, 27, 39]"
	);
	ENSURE_EQUALS(
		"Algorithms.filter (invalid bound method) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),[].push),list));\n"
			"}"
		),
		"*anonymous stream*:3:24: Filter functor returned wrong type, expected `boolean' got: `list'."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (unbound method) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"q = \"a1b2c3d4efgh78iop9zzz\";\n"
			"f = algo.filter(q,character.is_digit);\n"
			"F = copy(f);\n"
			"q += \"0\";\n"
			"return(algo.reduce(algo.materialize(f,list)+algo.materialize(F,list), @(x,y){x+string(y);},\"\"));\n"
			"}"
		),
		"\"123478901234789\""
	);
	ENSURE_EQUALS(
		"Algorithms.filter (invalid unbound method) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(['a','b','c'],character.to_upper),list));\n"
			"}"
		),
		"*anonymous stream*:3:24: Filter functor returned wrong type, expected `boolean' got: `character'."
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (tuple) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"t=(2,7,3,9,0,-5);\n"
			"return(algo.sorted(t));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (list) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l=[2,7,3,9,0,-5];\n"
			"return(algo.sorted(l));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (deque) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d=deque(2,7,3,9,0,-5);\n"
			"return(algo.sorted(d));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (set) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s=set(2,7,3,9,0,-5);\n"
			"return(algo.sorted(s));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (order) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"o=order(2,7,3,9,0,-5);\n"
			"return(algo.sorted(o));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (dict) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d=[2:0,7:0,3:0,9:0,0:0,-5:0];\n"
			"return(algo.sorted(d));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (lookup) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l={2:0,7:0,3:0,9:0,0:0,-5:0};\n"
			"return(algo.sorted(l));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (key retr func) failed",
		execute(
			"import Algorithms as algo;\n"
			"class Pair {\n"
			"_first = none;\n"
			"_second = none;\n"
			"constructor( first_, second_ ) {\n"
			"_first = first_;\n"
			"_second = second_;\n"
			"}\n"
			"to_string() {\n"
			"return(\"{{{},{}}}\".format(_first,_second));\n"
			"}\n"
			"}\n"
			"main(){\n"
			"l=[Pair(2,9),Pair(7,3),Pair(3,-1),Pair(9,4),Pair(0,2),Pair(-5,7)];\n"
			"sf = algo.materialize(algo.map(algo.sorted(l, @(x){x._first;}),string),list);\n"
			"ss = algo.materialize(algo.map(algo.sorted(l, @(x){x._second;}),string),list);\n"
			"return([sf,ss]);\n"
			"}"
		),
		"[[\"{-5,7}\", \"{0,2}\", \"{2,9}\", \"{3,-1}\", \"{7,3}\", \"{9,4}\"], [\"{3,-1}\", \"{0,2}\", \"{7,3}\", \"{9,4}\", \"{-5,7}\", \"{2,9}\"]]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (iterable) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"i=algo.map([2,7,3,9,0,-5],@(x){x;});\n"
			"return(algo.sorted(i));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (string) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s=\"502397\";"
			"return(algo.sorted(s));\n"
			"}"
		),
		"['0', '2', '3', '5', '7', '9']"
	);
	ENSURE_EQUALS(
		"Algorithms.max failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.max(77, 7, 39, 57, 80, 16, 72, 70, 87, 33));\n"
			"}"
		),
		"87"
	);
	ENSURE_EQUALS(
		"Algorithms.min failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.min(77, 7, 39, 57, 80, 16, 72, 70, 87, 33));\n"
			"}"
		),
		"7"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "FileSystem" )
#ifdef __MSVCXX__
	char const openRes[] = "\"*anonymous stream*:1:44: The system cannot find the file specified.\r\n: ./out/non-existing\"";
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
	hcore::HString filename( "./out/huginn-file.dat" );
	hcore::HString filenameMoved( "./out/huginn-file.alt" );
	hcore::HString data( "huginn-data" );
	try {
		filesystem::remove( filename );
	} catch ( HFileSystemException const& ) {
	}
	execute(
		"import FileSystem as fs;"
		"main(){"
		"f=fs.open(\""_ys.append( filename ).append( "\",fs.OPEN_MODE.WRITE);"
		"f.write_line(\"" ).append( data ).append( "\");"
		"return(0);"
		"}" )
	);
	HFile f( filename, HFile::OPEN::READING );
	hcore::HString line;
	getline( f, line );
	f.close();
	ENSURE_EQUALS( "bad write from Huginn.FileSystem", line, data );
	ENSURE_EQUALS(
		"bad read from Huginn.FileSystem",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"f=fs.open(\""_ys.append( filename ).append( "\",fs.OPEN_MODE.READ);"
			"return(f.read_line());"
			"}" )
		),
		"\""_ys.append( data ).append( '"' )
	);
	execute(
		"import FileSystem as fs;"
		"main(){"
		"fs.rename(\""_ys.append( filename ).append( "\",\"" ).append( filenameMoved ).append( "\");"
		"return(0);"
		"}" )
	);
	ENSURE_NOT( "Huginn.FileSystem.rename failed (src)", filesystem::exists( filename ) );
	ENSURE( "Huginn.FileSystem.rename failed (dst)", filesystem::exists( filenameMoved ) );
#ifdef __MSVCXX__
	char const renameExpect[] = "\"*anonymous stream*:1:45: Failed to rename: `non-existing-a' to `non-existing-b': The system cannot find the file specified.\r\n\"";
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
#ifndef __MSVCXX__
	execute(
		"import FileSystem as fs;"
		"main(){"
		"fs.chmod(\""_ys.append( filenameMoved ).append( "\",0660);"
		"return(0);"
		"}" )
	);
	ENSURE_EQUALS( "Huginn.FileSystem.chmod failed", HFSItem( filenameMoved ).get_permissions(), 0660 );
#endif
	ENSURE_EQUALS(
		"invalid chmod succeeded",
		execute_except(
			"import FileSystem as fs;"
			"main(){"
			"fs.chmod(\""_ys.append( filenameMoved ).append( "\",017777);"
			"return(0);"
			"}" )
		),
		"*anonymous stream*:1:40: Bad mode: 8191"
	);
#ifdef __MSVCXX__
	char const chmodExpect[] = "\"*anonymous stream*:1:44: chmod failed: `non-existing': The system cannot find the file specified.\r\n\"";
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
	execute(
		"import FileSystem as fs;"
		"main(){"
		"fs.remove(\""_ys.append( filenameMoved ).append( "\");"
		"return(0);"
		"}" )
	);
	ENSURE_NOT( "Huginn.FileSystem.remove failed", filesystem::exists( filenameMoved ) );
#if defined( __HOST_OS_TYPE_FREEBSD__ ) || defined( __HOST_OS_TYPE_CYGWIN__ )
		char const removeRes[] = "\"*anonymous stream*:1:45: Failed to remove: `./out': Operation not permitted\"";
#elif defined( __MSVCXX__ )
		char const removeRes[] = "\"*anonymous stream*:1:45: Failed to remove: `./out': The data is invalid.\r\n\"";
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
	ENSURE_EQUALS(
		"FileSystem.dirname, FileSystem.basename, FileSystem.readlink, FileSystem.current_working_directory failed",
		execute(
			"import FileSystem as fs;"
			"main(){"
			"return([fs.basename(fs.current_working_directory()),fs.dirname(\""_ys.append( filename ).append( "\"),fs.readlink(\"./data/broken\")]);"
			"}" )
		),
		"[\"tress\", \"./out\", \"non-existing\"]"
	);
#ifdef __MSVCXX__
	char const readlinkExpect[] = "\"*anonymous stream*:1:47: readlink failed: `non-existing': The data is invalid.\r\n\"";
#else
	char const readlinkExpect[] = "\"*anonymous stream*:1:47: readlink failed: `non-existing': No such file or directory\"";
#endif
	ENSURE_EQUALS(
		"invalid chmod succeeded",
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
	char const dirExpect[] = "\"*anonymous stream*:1:42: non-existing: The system cannot find the file specified.\r\n\"";
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
	HFSItem fi( "./data/karatsuba.bc" );
#ifdef __MSVCXX__
	int perm( 0666 );
	char const nonExtErr[] = "The system cannot find the file specified.\r\n";
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
			.append( ", FILE_TYPE.REGULAR, \"" )
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

TUT_UNIT_TEST( "Cryptography" )
	ENSURE_EQUALS(
		"Cryptography.md5 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.md5(\"\"));\n"
			"}"
		),
		"\"d41d8cd98f00b204e9800998ecf8427e\""
	);
	ENSURE_EQUALS(
		"Cryptography.sha1 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.sha1(\"\"));\n"
			"}"
		),
		"\"da39a3ee5e6b4b0d3255bfef95601890afd80709\""
	);
	ENSURE_EQUALS(
		"Cryptography.sha512 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.sha512(\"\"));\n"
			"}"
		),
		"\"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e\""
	);
	ENSURE_EQUALS(
		"Cryptography.hmac_md5 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.hmac_md5(\"\",\"\"));\n"
			"}"
		),
		"\"74e6f7298a9c2d168935f58c001bad88\""
	);
	ENSURE_EQUALS(
		"Cryptography.hmac_sha1 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.hmac_sha1(\"\",\"\"));\n"
			"}"
		),
		"\"fbdb1d1b18aa6c08324b7d64b71fb76370690e1d\""
	);
	ENSURE_EQUALS(
		"Cryptography.hmac_sha512 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.hmac_sha512(\"\",\"\"));\n"
			"}"
		),
		"\"b936cee86c9f87aa5d3c6f2e84cb5a4239a5fe50480a6ec66b70ab5b1f4ac6730c6c515421b327ec1d69402e53dfb49ad7381eb067b338fd7b0cb22247225d47\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "RegularExpressions" )
	ENSURE_EQUALS(
		"RegularExpressions.match failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"[0-9]-[0-9]\" );\n"
			"r = \"\";\n"
			"m = rec.match(\"[123+123+3123]\");\n"
			"if (m.matched()) {\n"
			"r = r + \"fail match\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"m = rec.match(\"[123-456-789]\");"
			"if (m.matched()) {\n"
			"for ( w : m ) {\n"
			"r = r + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no match\";\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok3-46-7\""
	);
	ENSURE_EQUALS(
		"RegularExpressions copy failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"[0-9]-[0-9]\" );\n"
			"r = \"\";\n"
			"for( rg : [rec,copy(rec)] ) {\n"
			"m = rg.match(\"[123+123+3123]\");\n"
			"if (m.matched()) {\n"
			"r = r + \"fail match\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"m = rg.match(\"[123-456-789]\");"
			"if (m.matched()) {\n"
			"for ( w : m ) {\n"
			"r = r + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no match\";\n"
			"}\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok3-46-7ok3-46-7\""
	);
	ENSURE_EQUALS(
		"RegularExpressions.groups failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"^([a-z]*)@([a-z.]*)$\" );\n"
			"r = \"\";\n"
			"g = rec.groups(\"user@example2.com\");\n"
			"if ( g != none ) {\n"
			"r = r + \"fail groups\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"g = rec.groups(\"user@example.com\");\n"
			"if ( g != none ) {\n"
			"for ( w : g ) {\n"
			"r = r + \"|\" + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no groups\";\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok|user@example.com|user|example.com\""
	);
	ENSURE_EQUALS(
		"RegularExpressions.replace failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"cre=re.compile(\"([0-9]+)\");\n"
			"return(cre.replace(\"abc012def789ghj\",\"$$$1}\"));\n"
			"}"
		),
		"\"abc$012}def$789}ghj\""
	);
	ENSURE_EQUALS(
		"RegularExpressions.replace failed",
		execute_except(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"cre=re.compile(\"([0-9]+)\");\n"
			"cre.replace(\"abc012def789ghj\",\"{$2}\");\n"
			"}"
		),
		"*anonymous stream*:4:12: Uncaught RegularExpressionsException: Invalid back-reference number in replacement string: 2."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Mathematics" )
	ENSURE_EQUALS( "Mathematics.{pi, e} failed", execute( "import Mathematics as math;main(){return([math.pi(real),math.e(number,200)]);}" ), "[3.14159265359, $2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901]" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){return(math.square_root(7.));}" ), "2.645751311065" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){return(math.square_root($7));}" ), "$2.6457513110645905905016157536392604257102591830824501803683344592010688232302836277603928864745436106" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){try{math.square_root(-1.);}catch(MathematicsException e){return(e.what());}}" ), "\"bad domain\"" );
	ENSURE_EQUALS( "Mathematics.natural_exponential failed", execute( "import Mathematics as math;main(){return(math.natural_exponential(7.));}" ), "1096.633158428459" );
	ENSURE_EQUALS( "Mathematics.natural_exponential failed", execute( "import Mathematics as math;main(){return(math.natural_exponential($7));}" ), "$1096.6331584284585992637202382881214324422191348336131437827392407761217693312331290224785687872498438842" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){return(math.natural_logarithm(7.));}" ), "1.945910149055" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){return(math.natural_logarithm($7));}" ), "$1.945910149055313305105352743443179729637084729581861188459390149937579862752069267787658498587871527" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){try{math.natural_logarithm(0.);}catch(MathematicsException e){return(e.what());}}" ), "\"bad domain\"" );
	ENSURE_EQUALS( "Mathematics.sinus failed", execute( "import Mathematics as math;main(){return(math.sinus(7.));}" ), "0.656986598719" );
	ENSURE_EQUALS( "Mathematics.sinus failed", execute( "import Mathematics as math;main(){return(math.sinus($7));}" ), "$0.6569865987187890903969990915936351779368700104974900746578543341892928371312270315099351216010552127" );
	ENSURE_EQUALS( "Mathematics.cosinus failed", execute( "import Mathematics as math;main(){return(math.cosinus(7.));}" ), "0.753902254343" );
	ENSURE_EQUALS( "Mathematics.cosinus failed", execute( "import Mathematics as math;main(){return(math.cosinus($7));}" ), "$0.7539022543433046381411975217191820122183133914601268395436138808138760267207174056254283910893024825" );
	ENSURE_EQUALS( "Mathematics.tangens failed", execute( "import Mathematics as math;main(){return(math.tangens(7.));}" ), "0.871447982724" );
	ENSURE_EQUALS( "Mathematics.tangens failed", execute( "import Mathematics as math;main(){return(math.tangens($7));}" ), "$0.8714479827243187364564508896003135663222034245984200644480154523301674476556679351044748556811165168" );
	ENSURE_EQUALS( "Mathematics.cotangens failed", execute( "import Mathematics as math;main(){return(math.cotangens(7.));}" ), "1.147515422405" );
	ENSURE_EQUALS( "Mathematics.cotangens failed", execute( "import Mathematics as math;main(){return(math.cotangens($7));}" ), "$1.1475154224051356850571278335968690125843802678361633445170108981521966892555002012462107148960973854" );
	ENSURE_EQUALS( "Mathematics.arcus_sinus failed", execute( "import Mathematics as math;main(){return(math.arcus_sinus(.7));}" ), "0.775397496611" );
	ENSURE_EQUALS( "Mathematics.arcus_sinus failed", execute( "import Mathematics as math;main(){return(math.arcus_sinus($0.7));}" ), "$0.7753974966107530637403533527149871135557887386411619935977199637327202118807111988654109034943728765" );
	ENSURE_EQUALS( "Mathematics.arcus_cosinus failed", execute( "import Mathematics as math;main(){return(math.arcus_cosinus(.7));}" ), "0.795398830184" );
	ENSURE_EQUALS( "Mathematics.arcus_cosinus failed", execute( "import Mathematics as math;main(){return(math.arcus_cosinus($0.7));}" ), "$0.7953988301841435554909683389247643285427959610463909168897523324211879912623933004486065091766856575" );
	ENSURE_EQUALS( "Mathematics.arcus_tangens failed", execute( "import Mathematics as math;main(){return(math.arcus_tangens(7.));}" ), "1.428899272191" );
	ENSURE_EQUALS( "Mathematics.arcus_tangens failed", execute( "import Mathematics as math;main(){return(math.arcus_tangens($7));}" ), "$1.4288992721907326964184700745371983590908029409590888381093422667904665763831733383698255510368120159" );
	ENSURE_EQUALS( "Mathematics.arcus_cotangens failed", execute( "import Mathematics as math;main(){return(math.arcus_cotangens(7.));}" ), "0.141897054604" );
	ENSURE_EQUALS( "Mathematics.arcus_cotangens failed", execute( "import Mathematics as math;main(){return(math.arcus_cotangens($7));}" ), "$0.1418970546041639228128516171025530830077817587284640723781300293634416267599311609441918616342465181" );
	hcore::HString hyperbolicSinusRes( execute( "import Mathematics as math;main(){return(math.hyperbolic_sinus(7.0));}" ) );
	hyperbolicSinusRes.pop_back();
	ENSURE_EQUALS( "Mathematics.hyperbolic_sinus failed", hyperbolicSinusRes, "548.31612327324" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_sinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_sinus($7));}" ), "$548.3161232732465223737561175760185115797963305545428538644492123213499399256719093579746212541216894919" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cosinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cosinus(7.0));}" ), "548.317035155212" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cosinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cosinus($7));}" ), "$548.3170351552120768899641207121029208624228042790702899182900284547718294055612196645039475331281543923" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_tangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_tangens(7.));}" ), "0.999998336944" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_tangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_tangens($7));}" ), "$0.9999983369439446717357164159506671128820569920922747109692404742809110481696115057511479211747076493" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cotangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cotangens(7.));}" ), "1.000001663059" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cotangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cotangens($7));}" ), "$1.0000016630588210883070615776102514764913523331922228239871821889401302787085050299163985440938683564" );
	ENSURE_EQUALS( "Mathematics.sigmoid failed", execute( "import Mathematics as math;main(){return(math.sigmoid(7.0));}" ), "0.999088948806" );
	ENSURE_EQUALS( "Mathematics.sigmoid failed", execute( "import Mathematics as math;main(){return(math.sigmoid($7));}" ), "$0.9990889488055993546421366762253058586758519397386814335751812177406547366392254595319805404147834436" );
	ENSURE_EQUALS( "Mathematics.error_function failed", execute( "import Mathematics as math;main(){return(math.error_function(0.7));}" ), "0.677801193837" );
	ENSURE_EQUALS( "Mathematics.error_function failed", execute( "import Mathematics as math;main(){return(math.error_function($0.7));}" ), "$0.677801193837" );
	ENSURE_EQUALS( "Mathematics.cumulative_distribution_function failed", execute( "import Mathematics as math;main(){return(math.cumulative_distribution_function(1.,-1.,2.));}" ), "0.841344746069" );
	ENSURE_EQUALS( "Mathematics.cumulative_distribution_function failed", execute( "import Mathematics as math;main(){return(math.cumulative_distribution_function($1,$-1,$2));}" ), "$0.8413447460685" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round(7.1234));}" ), "7.0" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round($7.12354321,3));}" ), "$7.124" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round(7.1235, 3));}" ), "7.124" );
	ENSURE_EQUALS( "Mathematics.round failed", execute_except( "import Mathematics as math;main(){return(math.round(7.1235, -1));}" ), "*anonymous stream*:1:52: Invalid requested round value: -1" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor(7.1234));}" ), "7.0" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor($7.123456));}" ), "$7" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor(-7.1234));}" ), "-8.0" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor($-7.123456));}" ), "$-8" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil(7.1234));}" ), "8.0" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil($7.123456));}" ), "$8" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil(-7.1234));}" ), "-7.0" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil($-7.123456));}" ), "$-7" );
	ENSURE_EQUALS( "Mathematics.differs_at failed", execute( "import Mathematics as math;main(){return(math.differs_at($7.1234567, $7.1235567));}" ), "3" );
	ENSURE_EQUALS( "Mathematics.differs_at failed", execute( "import Mathematics as math;main(){return(math.differs_at($2234.1234567, $1234.1234567));}" ), "-4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Matrix" )
	ENSURE_EQUALS(
		"Mathematics.Matrix (add) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m2=math.Matrix([9.,8.],[7.,6.]);"
			"m1+=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([10.0, 10.0], [10.0, 10.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (add) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.Matrix([$7.,$6.],[$9.,$8.]);"
			"m1+=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$8, $8], [$12, $12])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (sub) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m2=math.Matrix([9.,8.],[7.,6.]);"
			"m1-=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([-8.0, -6.0], [-4.0, -2.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (sub) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.Matrix([$9.,$8.],[$7.,$6.]);"
			"m1-=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$-8, $-6], [$-4, $-2])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (mul) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m2=math.Matrix([9.,8.],[7.,6.]);"
			"m1*=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([23.0, 20.0], [55.0, 48.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (mul) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.Matrix([$9.,$8.],[$7.,$6.]);"
			"m1*=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$23, $20], [$55, $48])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m1.scale(2.);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([2.0, 4.0], [6.0, 8.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m1.scale($2);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$2, $4], [$6, $8])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale_to) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m1.scale_to(12.);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([3.0, 6.0], [9.0, 12.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale_to) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m1.scale_to($12);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$3, $6], [$9, $12])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (det) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"return(m1.det());"
			"}"
		),
		"-2.0"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (det) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1,$2],[$3,$4]);"
			"return(math.round(m1.det(),50));"
			"}"
		),
		"$-2"
	);
	ENSURE_IN(
		"Mathematics.Matrix (inverse) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([1.,2.],[3.,4.]);"
			"return(string((m*m.inverse()).apply(@(x,y,v){x;y;math.round(v,9);})));"
			"}"
		),
		std::vector<char const*>( { "\"Matrix([1.0, 0.0], [-0.0, 1.0])\"", "\"Matrix([1.0, 0.0], [0.0, 1.0])\"" } )
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (inverse) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"return(string((m*m.inverse()).apply(@(x,y,v){x;y;math.round(v,7);})));"
			"}"
		),
		"\"Matrix([$1, $0], [$0, $1])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (transpose) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([1.,2.],[3.,4.],[5.,6.]);"
			"return(string(m.transpose()));"
			"}"
		),
		"\"Matrix([1.0, 3.0, 5.0], [2.0, 4.0, 6.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (transpose) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([$1.,$2.],[$3.,$4.],[$5,$6]);"
			"return(string(m.transpose()));"
			"}"
		),
		"\"Matrix([$1, $3, $5], [$2, $4, $6])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (set/get) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix(real,2,2);"
			"m1.set(0,0,1.);"
			"m1.set(0,1,2.);"
			"m1.set(1,0,3.);"
			"m1.set(1,1,4.);"
			"m1.scale(m1.get(0,1));"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([2.0, 4.0], [6.0, 8.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (set/get) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix(number,2,2);"
			"m1.set(0,0,$1.);"
			"m1.set(0,1,$2.);"
			"m1.set(1,0,$3.);"
			"m1.set(1,1,$4.);"
			"m1.scale(m1.get(0,1));"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$2, $4], [$6, $8])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix rows/columns (real) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix(real,3,2);"
			"return([m.rows(),m.columns()]);"
			"}"
		),
		"[3, 2]"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix rows/columns (number) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix(number,3,2);"
			"return([m.rows(),m.columns()]);"
			"}"
		),
		"[3, 2]"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (real) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"return(string(math.Matrix(real,2,2).apply(@(r,c,z){real(c+1+r*2)+z;})));"
			"}"
		),
		"\"Matrix([1.0, 2.0], [3.0, 4.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (real) (meth) failed",
		execute(
			"import Mathematics as math;"
			"class Apply {"
			"do(r,c,z) {"
			"real(c+1+r*2)+z;"
			"}"
			"}"
			"main(){"
			"return(string(math.Matrix(real,2,2).apply(Apply().do)));"
			"}"
		),
		"\"Matrix([1.0, 2.0], [3.0, 4.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (number) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"return(string(math.Matrix(number,2,2).apply(@(r,c,z){number(c+1+r*2)+z;})));"
			"}"
		),
		"\"Matrix([$1, $2], [$3, $4])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (number) (meth) failed",
		execute(
			"import Mathematics as math;"
			"class Apply {"
			"do(r,c,z) {"
			"number(c+1+r*2)+z;"
			"}"
			"}"
			"main(){"
			"return(string(math.Matrix(number,2,2).apply(Apply().do)));"
			"}"
		),
		"\"Matrix([$1, $2], [$3, $4])\""
	);
	ENSURE_IN(
		"Mathematics.NumberSetStatistics (real) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), real),list));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
	  std::vector<hcore::HString>({
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666667, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5779.999999999998, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]"
		})
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics (number) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), number),list));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
		"[15, $1, $239, $238, $120, $1800, $120, $120, $136, $5780, $5394.6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $76.026311234992849677911904736863392004981024226791874625210506343957711471685366580090089884878597349, $73.448394581955749284280964275663962120658982146661260896728683175175663615565836209204090274863582671, $63.4666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666]"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer failed",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(100);\n"
			"d=r.next(10);\n"
			"f=r.next_real(.5);\n"
			"return([r,d>=0,d<10,f>=0.,f<.5]);\n"
			"}\n"
		),
		"[math.Randomizer(100), true, true, true, true]"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer copy failed",
		execute(
			"import Mathematics as math;\n"
			"import Algorithms as algo;\n"
			"class RndGen {_rnd=none;constructor(rnd_){_rnd=rnd_;}do(x){x;_rnd.next();}}"
			"main(){\n"
			"range1=algo.range(100);\n"
			"range2=copy(range1);\n"
			"rnd1=math.Randomizer();\n"
			"rnd2=copy(rnd1);\n"
			"res1=algo.materialize(algo.map(range1,RndGen(rnd1).do),list);\n"
			"res2=algo.materialize(algo.map(range2,RndGen(rnd2).do),list);\n"
			"return(res1==res2);\n"
			"}\n"
		),
		"true"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer.seed failed",
		execute(
			"import Algorithms as algo;\n"
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(100);\n"
			"r.seed(0);\n"
			"l1 = algo.materialize(algo.map(algo.range(16),@[r](_){_;r.next();}),list);\n"
			"r.seed(0);\n"
			"l2 = algo.materialize(algo.map(algo.range(16),@[r](_){_;r.next();}),list);\n"
			"return((l1,l2, l1 == l2));\n"
			"}\n"
		),
		"([64, 52, 17, 53, 94, 11, 29, 1, 26, 25, 73, 11, 22, 98, 46, 38], [64, 52, 17, 53, 94, 11, 29, 1, 26, 25, 73, 11, 22, 98, 46, 38], true)"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer invalid cap succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Randomizer().next_real(0.);\n"
			"}\n"
		),
		"*anonymous stream*:3:28: Invalid range specified: 0.0"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Matrix err" )
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid rows succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix(real,0,1);"
			"}"
		),
		"*anonymous stream*:1:46: Invalid number of rows in matrix specification: 0."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid cols succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix(real,1,0);"
			"}"
		),
		"*anonymous stream*:1:46: Invalid number of columns in matrix specification: 0."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix(integer,1,1);"
			"}"
		),
		"*anonymous stream*:1:46: Bad matrix type: `integer'."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid cols from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([]);"
			"}"
		),
		"*anonymous stream*:1:46: Invalid number of columns in matrix specification: 0."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid type from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0]);"
			"}"
		),
		"*anonymous stream*:1:46: Matrix must have numeric data, either `number' or `real'."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix col count mismatch from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.],[0.,0.]);"
			"}"
		),
		"*anonymous stream*:1:46: Inconsistent number of columns across rows: 2 vs 1."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix non-uniform type from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.,$0]);"
			"}"
		),
		"*anonymous stream*:1:46: Non uniformly typed data in matrix definition, in row: 0, column: 1."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).get(-1,0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).get(-1,0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).get(0,-1);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).get(0,-1);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).set(-1,0,0.);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).set(-1,0,$0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).set(0,-1,0.);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).set(0,-1,$0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).set(0,0,$0);"
			"}"
		),
		"*anonymous stream*:1:56: Matrix.set() third argument must be a `real', not a `number'."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).set(0,0,0.);"
			"}"
		),
		"*anonymous stream*:1:56: Matrix.set() third argument must be a `number', not a `real'."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in add succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0])+math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:52: Non matching data types."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix dim mismatch in add succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.])+math.Matrix([0.,0.]);"
			"}"
		),
		"*anonymous stream*:1:52: columns dimensions do not match"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in sub succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0])-math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:52: Non matching data types."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix dim mismatch in sub succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.])-math.Matrix([0.,0.]);"
			"}"
		),
		"*anonymous stream*:1:52: columns dimensions do not match"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in mul succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0])*math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:52: Non matching data types."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix dim mismatch in mul succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.,0.])*math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:55: columns does not match rows"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix det on non-square succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.,0.]).det();"
			"}"
		),
		"*anonymous stream*:1:59: matrix is not square"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix scale on zero Matrix succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).scale_to(1.);"
			"}"
		),
		"*anonymous stream*:1:61: Zeroed matrix cannot be scaled."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix scale on zero Matrix succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).scale_to($1);"
			"}"
		),
		"*anonymous stream*:1:61: Zeroed matrix cannot be scaled."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix type mismatch on scale succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([1.]).scale_to($1);"
			"}"
		),
		"*anonymous stream*:1:61: Matrix.scale_to() argument must be a `real', not a `number'."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad apply return type succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"return(string(math.Matrix(real,2,2).apply(@(r,c,z){number(c+1+r*2)+number(z);})));"
			"}"
		),
		"*anonymous stream*:1:76: Applied transformation function shall return `real', but result was a `number' instead."
	);
#ifndef CONTINUOUS_INTEGRATION_TRAVIS
#if SIZEOF_INT_LONG == 8
	char const err[] = "*anonymous stream*:3:12: yaal::memory::new: new returned NULL";
#else
	char const err[] = "*anonymous stream*:3:12: Signed integer multiplication overflow.";
#endif
	ENSURE_EQUALS(
		"Allocation Matrix of absurd size succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Matrix(real,0x40000000,1);\n"
			"}\n"
		),
		err
	);
#endif /* #ifndef CONTINUOUS_INTEGRATION_TRAVIS */
TUT_TEARDOWN()

TUT_UNIT_TEST( "Mathematics Complex" )
	ENSURE_EQUALS(
		"Mathematics.Complex add",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a + b);\n"
			"}\n"
		),
		"math.Complex(4.0, 6.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex sub",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a - b);\n"
			"}\n"
		),
		"math.Complex(-2.0, -2.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex mul",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a * b);\n"
			"}\n"
		),
		"math.Complex(-5.0, 10.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex div",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a / b);\n"
			"}\n"
		),
		"math.Complex(0.44, 0.08)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex div (0+0i)",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(0.,0.);\n"
			"return(a / b);\n"
			"}\n"
		),
		"*anonymous stream*:5:10: Uncaught ArithmeticException: denominator equals 0"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex mod",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return(|b|);\n"
			"}\n"
		),
		"5.0"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex neg",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( - b );\n"
			"}\n"
		),
		"math.Complex(-3.0, -4.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex argument",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( b.argument() );\n"
			"}\n"
		),
		"0.927295218002"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex argument (0+0i)",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(0.,0.);\n"
			"return( b.argument() );\n"
			"}\n"
		),
		"*anonymous stream*:4:19: Uncaught ArithmeticException: Argument for 0 + 0i is undefined."
	);
	ENSURE_EQUALS(
		"Mathematics.Complex real/imaginary",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( ( b.real(), b.imaginary() ) );\n"
			"}\n"
		),
		"(3.0, 4.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex get",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( b.get() );\n"
			"}\n"
		),
		"(3.0, 4.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex set",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(0.,0.);\n"
			"b.set(3.,4.);\n"
			"return( b.get() );\n"
			"}\n"
		),
		"(3.0, 4.0)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Database" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	ENSURE_EQUALS(
		"DatabaseConnection.table_names",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"return(dbc.table_names());"
			"}"
		),
		"[\"config\", \"crud\", \"test\", \"test_dict\", \"test_item\"]"
	);
	ENSURE_EQUALS(
		"DatabaseConnection.column_names",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"return(dbc.column_names(\"config\"));"
			"}"
		),
		"[\"id\", \"name\", \"data\"]"
	);
	ENSURE_EQUALS(
		"DatabaseConnection.query, Query, QueryResult",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"q=dbc.query(\"SELECT name FROM config WHERE id != ?;\");"
			"q.bind(1, \"2\");"
			"qr=q.execute();"
			"res=\"\";"
			"i=0;"
			"fc=qr.field_count();"
			"while(i<fc){"
			"res+=qr.column_name(i);"
			"res+=\",\";"
			"i+=1;"
			"}"
			"if(qr.has_next()){"
			"for(r:qr){"
			"for(v:r){"
			"res+=v;"
			"res+=\",\";"
			"}"
			"}"
			"}"
			"q=dbc.query(\"SELECT name, data FROM config WHERE id = ?;\");"
			"q.bind(1, \"2\");"
			"qr=q.execute();"
			"while(qr.has_next()){"
			"for(v:qr.fetch_row()){"
			"res+=(v!=none ? v : \"none\");"
			"res+=\",\";"
			"}"
			"}"
			"q=dbc.query(\"INSERT INTO config ( name, data ) VALUES ( ?, ? );\");"
			"q.bind(1, \"special\");"
			"q.bind(2, \"special_value\");"
			"qr=q.execute();"
			"res += string(qr.insert_id());"
			"q=dbc.query(\"DELETE FROM config WHERE name = ?;\");"
			"q.bind(1, \"special\");"
			"qr = q.execute();"
			"res += \",\";"
			"res += string(size(qr));"
			"return(res);"
			"}"
		),
		"\"name,one,three,two,none,4,1\""
	);
	ENSURE_EQUALS(
		"DatabaseConnection.connect exception",
		execute(
			"import Database as db;"
			"main(){"
			"try{"
			"db.connect(\"sqlite3:///out/tress-non-existing\");"
			"}catch(DatabaseException  e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:44: Database file `out/tress-non-existing.sqlite' is not accessible.\""
	);
	ENSURE_EQUALS(
		"DatabaseConnection.copy exception",
		execute_except(
			"import Database as db;\n"
			"main(){\n"
			"dbc=db.connect(\"sqlite3:///out/tress\");\n"
			"copy(dbc);\n"
			"}\n"
		),
		"*anonymous stream*:4:5: Copy semantics is not supported on DatabaseConnection."
	);
	ENSURE_EQUALS(
		"DatabaseConnection.query exception",
		execute(
			"import Database as db;"
			"main(){"
			"try{"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"dbc.query(\"invalid;\");"
			"}catch(DatabaseException  e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:82: SQL prepare error: 'invalid;': near \"invalid\": syntax error\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "OperatingSystem" )
	ENSURE_EQUALS(
		"OperatingSystem.env",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.env(\"DEFAULT_TARGET\"));"
			"}"
		),
		"\"debug\""
	);
	ENSURE_EQUALS(
		"OperatingSystem.getuid",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.getuid());"
			"}"
		),
		to_string( system::get_user_id() )
	);
	ENSURE_EQUALS(
		"OperatingSystem.getgid",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.getgid());"
			"}"
		),
		to_string( system::get_group_id() )
	);
	ENSURE_EQUALS(
		"OperatingSystem.getpid",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.getpid());"
			"}"
		),
		to_string( system::getpid() )
	);
#ifndef __MSVCXX__
	char const expectedExec[] = "No such file or directory";
#else /* #ifndef __MSVCXX__ */
	char const expectedExec[] = "The system cannot find the file specified.\r\n";
#endif /* #else #ifndef __MSVCXX__ */
	ENSURE_EQUALS(
		"OperatingSystem.exec",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"try{"
			"os.exec(\"/non/existing\",\"arg1\");"
			"}catch(OperatingSystemException  e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:48: "_ys.append( expectedExec ).append( "\"" )
	);
	/* It is impossible to test exit(). */
	hcore::HString CHILD( "./data/child" EXE_SUFFIX );
	ENSURE_EQUALS(
		"OperatingSystem.spawn, is_alive, wait, in, out, err",
		execute(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"c=os.spawn(\"" + CHILD + "\");\n"
			"a0=c.is_alive();\n"
			"c.in().write_line(\"out\\n\");\n"
			"ro=c.out().read_line().strip();\n"
			"s=c.wait(8);\n"
			"a1=c.is_alive();\n"
			"c=os.spawn(\"" + CHILD + "\");\n"
			"c.in().write_line(\"err\\n\");\n"
			"re=c.err().read_line().strip();\n"
			"return([a0,ro,re,a1,s]);\n"
			"}\n"
		),
		"[true, \"hello-OUT\", \"hello-ERR\", false, 0]"
	);
	ENSURE_EQUALS(
		"OperatingSystem.spawn",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"try{"
			"os.spawn(\"non-existing\");"
			"}catch(OperatingSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:49: "_ys.append( expectedExec ).append( ": non-existing\"" )
	);
#ifndef __MSVCXX__
	HClock c;
	HHuginn h;
	HPipe io;
	h.set_output_stream( io.in() );
	HStringStream source(
		"import OperatingSystem as os;"
		"main(){"
		"c=os.spawn(\"/bin/sleep\", \"10\");"
		"os.stdout().write_line( \"{}\\n\".format( c.get_pid() ) );\n"
		"c.wait(5);\n"
		"}"
	);
	h.load( source );
	h.preprocess();
	ENSURE( "parsing failed", h.parse() );
	ENSURE( "compilation failed", h.compile() );
	HThread t;
	hcore::HString result;
	t.spawn(
		HThread::call_t(
			[&h, &result]() {
				try {
					result = h.execute() ? 1 : 0;
				} catch ( HException const& e ) {
					result = e.what();
				} catch ( std::exception const& e ) {
					result = e.what();
				} catch ( ... ) {
					result = "unknown exception type";
				}
			}
		)
	);
	HStreamInterface::ptr_t out( io.out() );
	hcore::HString line;
	getline( *out, line );
	int pid( lexical_cast<int>( line ) );
#ifndef SIGKILL
#define SIGKILL 9
#endif
	system::kill( pid, SIGKILL );
	t.finish();
	ENSURE_EQUALS( "Subprocess.wait() failed", result, "1" );
#ifndef __HOST_OS_TYPE_CYGWIN__ /* Cygwin implementation of process handling is buggy as hell. */
	ENSURE_EQUALS( "Subprocess.get_pid() failed", c.get_time_elapsed( time::UNIT::SECOND ), 0 );
	c.reset();
	ENSURE_EQUALS(
		"Subprocess.kill() failed",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"c=os.spawn(\"/bin/sleep\", \"10\");"
			"c.kill();\n"
			"}"
		),
		to_string( SIGKILL )
	);
	ENSURE( "Subprocess.kill() failed", c.get_time_elapsed( time::UNIT::SECOND ) <= 1 );
#endif /* #ifndef __HOST_OS_TYPE_CYGWIN__ */
#undef SIGKILL
#endif /* #ifndef __MSVCXX__ */
	ENSURE_EQUALS(
		"Subprocess bad wait succeded",
		execute_except(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"c=os.spawn(\"" + CHILD + "\");\n"
			"c.wait(-1);\n"
			"}\n"
		),
		"*anonymous stream*:4:7: invalid wait time: -1"
	);
#ifndef __HOST_OS_TYPE_CYGWIN__ /* Cygwin implementation of process handling is buggy as hell. */
	ENSURE_EQUALS(
		"Subprocess bad wait succeded",
		execute_except(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"copy(os.spawn(\"" + CHILD + "\"));\n"
			"}\n"
		),
		"*anonymous stream*:3:5: Copy semantics is not supported on Subprocess."
	);
#endif /* #ifndef __HOST_OS_TYPE_CYGWIN__ */
TUT_TEARDOWN()

TUT_UNIT_TEST( "DateTime" )
#if defined( __HOST_OS_TYPE_FREEBSD__ ) || defined( __HOST_OS_TYPE_SOLARIS__ )
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"0001-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"0011-04-02 14:55:14\"]";
#elif SIZEOF_TIME_T == 8
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"1-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"11-04-02 14:55:14\"]";
#elif defined( __MSVCXX__ )
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"0001-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"1981-04-02 14:55:14\"]";
#elif defined( __HOST_OS_TYPE_DEBIAN__ ) || defined( __HOST_OS_TYPE_RASPBIAN__ )
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"1-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"1981-04-02 14:55:14\"]";
#else
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"1901-12-13 22:30:17\", 1978, 5, 24, 23, 30, 17, \"1981-04-02 14:55:14\"]";
#endif
	ENSURE_EQUALS(
		"Time setters/getters failed",
		execute(
			"import DateTime as dt;"
			"import Algorithms as algo;"
			"main(){"
			"t = dt.now();"
			"t.set_datetime(1978,5,24,23,30,17);"
			"s = copy(t).from_string(\"1989-08-24 14:25:31\");"
			"r=[copy(t).mod_year(1),copy(t).set_time(1,2,3),copy(t).set_date(1,2,3),t.get_year(),t.get_month(),t.get_day(),t.get_hour(),t.get_minute(),t.get_second(),s-t];"
			"return(algo.materialize(algo.map(r,@(x){type(x)==type(dt.now())?string(x):x;}),list));"
			"}"
		),
		setterExpect
	);
	ENSURE_EQUALS(
		"Time bad setter succeeded",
		execute(
			"import DateTime as dt;"
			"main(){"
			"try{"
			"t = dt.now();"
			"t.set_date(1,13,1);"
			"}catch(DateTimeException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:57: bad month in year\""
	);
	ENSURE_EQUALS(
		"Time bad setter succeeded",
		execute(
			"import DateTime as dt;"
			"main(){"
			"try{"
			"t = dt.now();"
			"t.set_datetime(1,1,1,1,60,1);"
			"}catch(DateTimeException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:61: bad minute\""
	);
	ENSURE_EQUALS(
		"Time bad from_string succeeded",
		execute(
			"import DateTime as dt;"
			"main(){"
			"try{"
			"t = dt.now();"
			"t.from_string(\"invalid\");"
			"}catch(DateTimeException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:60: Could not parse `invalid' as `%Y-%m-%d %T'.\""
	);
	ENSURE_EQUALS(
		"DateTime.clock, DateTime.sleep falied",
		execute(
			"import DateTime as dt;"
			"main(){"
			"c = dt.clock();"
			"dt.sleep(1000000000);"
			"return(c.milliseconds()/100);"
			"}"
		),
		"10"
	);
	ENSURE_EQUALS(
		"Clock.reset, Clock.to_string falied",
		execute(
			"import DateTime as dt;"
			"main(){"
			"c = dt.clock();"
			"dt.sleep(1000000000);"
			"m = c.milliseconds()/100;"
			"c.reset();"
			"s=string(c);"
			"return([m,s.find(\"second\")>0 || s == \"0s\"]);"
			"}"
		),
		"[10, true]"
	);

	hcore::HString res(
		execute(
			"import DateTime as dt;"
			"main(){"
			"return(string(dt.now()));"
			"}"
		)
	);
	res.trim( "\"" );
	HTime now( now_local() );
	hcore::HString nowS0( now.string() );
	now.mod_second( -1 );
	hcore::HString nowSP( now.string() );
	now.mod_second( 2 );
	hcore::HString nowSN( now.string() );
	ENSURE( "DateTime.now falied", ( res == nowS0 ) || ( res == nowSP ) || ( res == nowSN ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Network" )
	hcore::HString res(
		execute(
			"import Network as net;"
			"main(){"
			"return(net.resolve(\"localhost\"));"
			"}"
		)
	);
	ENSURE( "Network.resolve falied", ( res == "\"127.0.0.1\"" ) || ( res == "\"0.0.0.0\"" ) );
	HThread serverRunner;
	HIODispatcher iod( 11, 1000 );
	HSocket::ptr_t serv( make_pointer<HSocket>( HSocket::TYPE::NETWORK | HSocket::TYPE::BLOCKING, 1 ) );
	serv->listen( "127.0.0.1", OBSCURE_PORT );
	iod.register_file_descriptor_handler(
		serv,
		HIODispatcher::callback_t(
			[&iod, &serv]( HIODispatcher::stream_t& ) {
				clog << "ENTER: acceptor" << endl;
				HSocket::ptr_t client( serv->accept() );
				iod.register_file_descriptor_handler(
					client,
					HIODispatcher::callback_t(
						[&iod]( HIODispatcher::stream_t& stream_ ) {
							clog << "ENTER: message hangler" << endl;
							hcore::HString line;
							if ( stream_->read_until( line ) > 0 ) {
								clog << "serv got: [" << line << "]" << endl;
								reverse( line.begin(), line.end() );
								*stream_ << line << endl;
							} else {
								iod.unregister_file_descriptor_handler( stream_ );
							}
							clog << "LEAVE: message hangler" << endl;
						}
					)
				);
				clog << "LEAVE: acceptor" << endl;
			}
		)
	);
	serverRunner.spawn(
		HThread::call_t(
			[&iod]() -> void {
				try {
					clog << "ENTER: server" << endl;
					iod.run();
					clog << "LEAVE: server" << endl;
				} catch ( HException const& e ) {
					cerr << "exception caught: " << e.what() << endl;
				} catch ( std::exception const& e ) {
					cerr << "exception caught: " << e.what() << endl;
				} catch ( ... ) {
					cerr << "unknown exception type" << endl;
				}
			}
		)
	);
	ENSURE_EQUALS(
		"Network.connect failed",
		execute(
			"import Network as net;\n"
			"main() {\n"
			"s = net.connect( \"127.0.0.1\", 61930 );\n"
			"s.write_line( \"Huginn is best!\\n\" );\n"
			"return ( s.read_line() );\n"
			"}\n"
		),
		"\"!tseb si nniguH\n\""
	);
	iod.stop();
	serverRunner.finish();
	ENSURE_EQUALS(
		"Network.connect bad port ok",
		execute_except(
			"import Network as net;\n"
			"main() {\n"
			"net.connect( \"127.0.0.1\", -1 );\n"
			"}\n"
		),
		"*anonymous stream*:3:12: Uncaught NetworkException: Bad port: -1"
	);
#ifdef __MSVCXX__
	char const errExpect[] = "No connection could be made because the target machine actively refused it.\r\n";
#else
	char const errExpect[] = "Connection refused";
#endif
	ENSURE_EQUALS(
		"Network.connect failed connect not signaled",
		execute(
			"import Network as net;\n"
			"main() {\n"
			"try{"
			"net.connect( \"127.0.0.1\", 5 );\n"
			"}catch(NetworkException e){\n"
			"return(e.message());\n"
			"}\n"
			"}\n"
		),
		"\"*anonymous stream*:3:16: "_ys.append( errExpect ).append( ": 127.0.0.1:5\"" )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Text" )
	ENSURE_EQUALS(
		"Text.repeat failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.repeat(\"Huginn\",7);"
			"}\n"
		),
		"\"HuginnHuginnHuginnHuginnHuginnHuginnHuginn\""
	);
	ENSURE_EQUALS(
		"Text.join on non collection succeeded",
		execute_except(
			"import Text as text;\n"
			"main() {\n"
			"text.repeat(\"\",-1);"
			"}\n"
		),
		"*anonymous stream*:3:12: Negative repeat count: -1"
	);
	ENSURE_EQUALS(
		"Text.split failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.split(\"Ala ma kota.\",\" \");"
			"}\n"
		),
		"[\"Ala\", \"ma\", \"kota.\"]"
	);
	ENSURE_EQUALS(
		"Text.join failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.join([\"Ala\", \"ma\", \"kota.\"], \"+\");"
			"}\n"
		),
		"\"Ala+ma+kota.\""
	);
	ENSURE_EQUALS(
		"Text.join on non collection succeeded",
		execute_except(
			"import Text as text;\n"
			"main() {\n"
			"text.join(\"\",\"\");"
			"}\n"
		),
		"*anonymous stream*:3:10: Text.join() first argument must be a flat uniform collection of strings, not a `string'."
	);
	ENSURE_EQUALS(
		"Text.join on non uniform succeeded",
		execute_except(
			"import Text as text;\n"
			"main() {\n"
			"text.join([\"\",'x'],\"\");"
			"}\n"
		),
		"*anonymous stream*:3:10: Text.join() first argument must be a flat uniform collection of strings, but it contains a `character'."
	);
	ENSURE_EQUALS(
		"Text.distance failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"text.distance(\"Ala ma kota.\",\"Ola ma psa.\");"
			"}\n"
		),
		"4"
	);
	ENSURE_EQUALS(
		"Text.distance failed",
		execute(
			"import Text as text;\n"
			"main() {\n"
			"[text.hex(100),text.oct(100),text.bin(100)];"
			"}\n"
		),
		"[\"0x64\", \"0o144\", \"0b1100100\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Introspection" )
	typedef yaal::hcore::HArray<yaal::hcore::HString> tokens_t;
	tokens_t yaalVersion( string::split<tokens_t>( yaal_version( true ), character_class( CHARACTER_CLASS::WHITESPACE ).data(), HTokenizer::DELIMITED_BY_ANY_OF ) );
	ENSURE_EQUALS(
		"Introspection.version failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"return ( intro.version() );"
			"}\n"
		),
		format( "(\"%s\", \"%s\")", yaalVersion[0], yaalVersion[1] )
	);
	ENSURE_EQUALS(
		"Introspection.symbol (built-in function) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"s = intro.symbol(\"size\");\n"
			"return ( s(\"Huginn\") );"
			"}\n"
		),
		"6"
	);
	ENSURE_EQUALS(
		"Introspection.symbol (user function) failed",
		execute(
			"import Introspection as intro;\n"
			"triple(x){x*3;}\n"
			"main() {\n"
			"triple;\n"
			"t = intro.symbol(\"triple\");\n"
			"return ( t(7) );"
			"}\n"
		),
		"21"
	);
	ENSURE_EQUALS(
		"Introspection.symbol (package) failed",
		execute(
			"import Algorithms as algo;"
			"import Introspection as intro;\n"
			"main() {\n"
			"algo;\n"
			"a = intro.symbol(\"algo\");\n"
			"return ( a.max(1,3) );"
			"}\n"
		),
		"3"
	);
	ENSURE_EQUALS(
		"Introspection.attribute (built-in, unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"tu = intro.attribute(string, \"to_upper\");\n"
			"return ( tu( \"Huginn\" ) );"
			"}\n"
		),
		"\"HUGINN\""
	);
	ENSURE_EQUALS(
		"Introspection.attribute (built-in, bound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"h = \"Huginn\";\n"
			"H = intro.attribute(h, \"to_upper\");\n"
			"return ( H() );"
			"}\n"
		),
		"\"HUGINN\""
	);
	ENSURE_EQUALS(
		"Introspection.attribute (user, unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; }"
			"main() {\n"
			"A().x;\n"
			"f = intro.attribute(A, \"x\");\n"
			"return ( f );"
			"}\n"
		),
		"17"
	);
	ENSURE_EQUALS(
		"Introspection.attribute (user, bound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; }"
			"main() {\n"
			"A().x;\n"
			"a = A();\n"
			"f = intro.attribute(a, \"x\");\n"
			"return ( f );"
			"}\n"
		),
		"17"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (built-in unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"return ( intro.list_attributes(number) );"
			"}\n"
		),
		"(\"is_exact\", \"is_integral\", \"get_precision\", \"set_precision\")"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (built-in bound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"return ( intro.list_attributes($0) );"
			"}\n"
		),
		"(\"is_exact\", \"is_integral\", \"get_precision\", \"set_precision\")"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (user unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; y = none; }\n"
			"main() {\n"
			"a=A();a.x;a.y;\n"
			"return ( intro.list_attributes(A) );"
			"}\n"
		),
		"(\"x\", \"y\")"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (user bound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; y = none; }\n"
			"main() {\n"
			"a=A();a.x;a.y;\n"
			"return ( intro.list_attributes(a) );"
			"}\n"
		),
		"(\"x\", \"y\")"
	);
	ENSURE_EQUALS(
		"Introspection.import failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"t = intro.import(\"Tress\");\n"
			"return ( t.diagonal(3., 4.) );"
			"}\n",
			{ "./data/" }
		),
		"5.0"
	);
	ENSURE_EQUALS(
		"Introspection.call_stack failed",
		execute(
			"import Introspection as intro;\n"
			"foo( n ) {\n"
			"r = none;\n"
			"if ( n > 0 ) {\n"
			"r = foo( n - 1 );\n"
			"} else {\n"
			"r = intro.call_stack();\n"
			"}\n"
			"return ( r );\n"
			"}\n"
			"main() {\n"
			"return ( foo( 3 ) );"
			"}\n"
		),
		"[*anonymous stream*:7:21:foo, *anonymous stream*:5:8:foo, *anonymous stream*:5:8:foo, *anonymous stream*:5:8:foo, *anonymous stream*:12:13:main]"
	);
TUT_TEARDOWN()

}


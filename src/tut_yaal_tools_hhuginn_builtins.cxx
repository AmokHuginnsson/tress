/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;
using namespace yaal::tools::executing_parser;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_builtins : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_builtins, "yaal::tools::HHuginn,builtins" );

TUT_UNIT_TEST( "size" )
	ENSURE_EQUALS( "size failed", execute( "class A{get_size(){7;}}main(){return([size(\"Ala\"),size([1,2,3,4]),size(A())]);}" ), "[3, 4, 7]" );
	ENSURE_EQUALS( "invalid get_size succeeded (type)", execute_except( "class A{get_size(){0.;}}main(){size(A());}" ), "*anonymous stream*:1:36: User supplied `get_size` method returned an invalid type a `real` instead of an `integer`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "string()" )
	ENSURE_EQUALS( "str to str failed", execute( "main(){return(string(\"7\"));}" ), "\"7\"" );
	ENSURE_EQUALS( "int to str failed", execute( "main(){return(string(7));}" ), "\"7\"" );
	ENSURE_EQUALS( "char to str failed", execute( "main(){return(string('7'));}" ), "\"7\"" );
	ENSURE_EQUALS( "real to str failed", execute( "main(){return(string(7.));}" ), "\"7.0\"" );
	ENSURE_EQUALS( "number to str failed", execute( "main(){return(string($7));}" ), "\"7\"" );
	ENSURE_EQUALS( "boolean (true) to str failed", execute( "main(){return(string(true));}" ), "\"true\"" );
	ENSURE_EQUALS( "boolean (false) to str failed", execute( "main(){return(string(false));}" ), "\"false\"" );
	ENSURE_EQUALS( "func ref to str failed", execute( "main(){return(string(type(\"\")));}" ), "\"string\"" );
	ENSURE_EQUALS( "string.find() failed", execute( "main(){s=\"ala ma kota\";return([s.find(\"kot\"),s.find(\"pies\")]);}" ), "[7, -1]" );
	ENSURE_EQUALS( "string.find(str,after) failed", execute( "main(){s=\"ala ma kota i kotka.\";return([s.find(\"kot\"),s.find(\"kot\",8)]);}" ), "[7, 14]" );
	ENSURE_EQUALS( "string.replace() failed", execute( "main(){s=\"ala ma kota i kotka\";return(s.replace(\"kot\",\"pies\"));}" ), "\"ala ma piesa i pieska\"" );
	ENSURE_EQUALS( "string.to_upper(), string.to_lower() failed", execute( "main(){s=\"Huginn\";return([copy(s).to_upper(),s.to_lower()]);}" ), "[\"HUGINN\", \"huginn\"]" );
	ENSURE_EQUALS( "string.find_last() failed", execute( "main(){s=\"ala ma kota i kotka\";return([s.find_last(\"kot\"),s.find_last(\"pies\")]);}" ), "[14, -1]" );
	ENSURE_EQUALS( "string.find_last() failed", execute( "main(){s=\"ala ma kota i kotka\";return([s.find_last(\"kot\"),s.find_last(\"kot\",13)]);}" ), "[14, 7]" );
	ENSURE_EQUALS( "string.find_one_of(), string.find_last_one_of() failed", execute( "main(){s=\"ala ma kota i kotka\";return([s.find_one_of(\"mk\"),s.find_last_one_of(\"mk\"),s.find_one_of(\"xyz\"),s.find_last_one_of(\"xyz\")]);}" ), "[4, 17, -1, -1]" );
	ENSURE_EQUALS( "string.find_one_of(), string.find_last_one_of() failed", execute( "main(){s=\"ala ma kota i kotka\";return([s.find_one_of(\"mk\"),s.find_one_of(\"mk\",8)]);}" ), "[4, 14]" );
	ENSURE_EQUALS( "string.find_other_than(), string.find_last_other_than() failed", execute( "main(){s=\"ala ma kota i kotka\";return([s.find_other_than(\"akmil \"),s.find_last_other_than(\"akmil \"),s.find_other_than(\"akmotil \"),s.find_last_other_than(\"akmotil \")]);}" ), "[8, 16, -1, -1]" );
	ENSURE_EQUALS(
		"string.starts_with() failed",
		execute(
			"main(){\n"
			"s=\"abcdefghij\";\n"
			"return([s.starts_with(\"abc\"), s.starts_with(\"abd\"), s.starts_with(\"bcd\"), s.starts_with(\"\")]);\n"
			"}"
		),
		"[true, false, false, true]"
	);
	ENSURE_EQUALS(
		"string.ends_with() failed",
		execute(
			"main(){\n"
			"s=\"abcdefghij\";\n"
			"return([s.ends_with(\"hij\"), s.ends_with(\"gij\"), s.ends_with(\"ghi\"), s.ends_with(\"\")]);\n"
			"}"
		),
		"[true, false, false, true]"
	);
	ENSURE_EQUALS( "copy( str ) failed", execute( "main(){x=\"a\";y=x;z=copy(x);x+=\"b\";return([x,y,z]);}" ), "[\"ab\", \"ab\", \"a\"]" );
	ENSURE_EQUALS( "string.strip() failed", execute( "main(){s=\"~huginn~\";return(s.strip(\"~\"));}" ), "\"huginn\"" );
	ENSURE_EQUALS( "string.clear() failed", execute( "main(){s=\"ala ma kota\";s.clear();return(s);}" ), "\"\"" );
	ENSURE_EQUALS(
		"string reversed() failed",
		execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed(\"Huginn\"),list);}" ),
		"['n', 'n', 'i', 'g', 'u', 'H']"
	);
	ENSURE_EQUALS(
		"string reversed() copy/size failed",
		execute( "import Algorithms as algo;main(){x=algo.reversed(\"Huginn\");algo.materialize(copy(x),list).push(size(x));}" ),
		"['n', 'n', 'i', 'g', 'u', 'H', 6]"
	);
	ENSURE_EQUALS(
		"string.format() failed",
		execute(
			"main(){\n"
			"s=\"a {} {{ {:} b\";\n"
			"return(s.format(7,13));\n"
			"}\n"
		),
		"\"a 7 { 13 b\""
	);
	ENSURE_EQUALS(
		"string.format() failed",
		execute(
			"main(){\n"
			"s = \"[{:f}] [{:3f}] [{:.3f}] [{:0.3f}] [{:5.3f}] [{:6.3f}]\";\n"
			"x = 7.312584;\n"
			"return(s.format(x,x,x,x,x,x));\n"
			"}\n"
		),
		"\"[7.312584] [7.312584] [7.313] [7.313] [7.313] [ 7.313]\""
	);
	ENSURE_EQUALS(
		"string.format() failed",
		execute(
			"main(){\n"
			"s=\"a {1} }} {0} b\";\n"
			"return(s.format(7,13));\n"
			"}\n"
		),
		"\"a 13 } 7 b\""
	);
	ENSURE_EQUALS(
		"string.format() failed",
		execute(
			"main(){\n"
			"s=\"a {:#7x} {:#07x} {:02d} {:02x} b\";\n"
			"return(s.format(123, 0x123, 1, 10));\n"
			"}\n"
		),
		"\"a    0x7b 0x00123 01 0a b\""
	);
	ENSURE_EQUALS(
		"string.format() alignment failed",
		execute(
			"main(){\n"
			"s=\"[{:<10s}] [{:>10s}] [{:^10s}]\";\n"
			"return(s.format(\"ala\", \"kot\", \"pies\"));\n"
			"}\n"
		),
		"\"[ala       ] [       kot] [   pies   ]\""
	);
	ENSURE_EQUALS(
		"string.format() def align failed",
		execute(
			"main(){\n"
			"s=\"[{:10s}] [{:10d}] [{:10c}] [{:10n}]\";\n"
			"return(s.format(\"ala\", 678, '✓', $345));\n"
			"}\n"
		),
		"\"[ala       ] [       678] [✓         ] [       345]\""
	);
	ENSURE_EQUALS(
		"string.format() fill failed",
		execute(
			"main(){\n"
			"s=\"[{:~>7s}] [{:06d}] [{:6d}]\";\n"
			"return(s.format(\"ala\", 567, 234));\n"
			"}\n"
		),
		"\"[~~~~ala] [000567] [   234]\""
	);
	ENSURE_EQUALS( "string.format() n-ary with format spec failed", execute( "main(){return(\"{:4d} {}\".format(17,\"q\"));}" ), "\"  17 q\"" );
	ENSURE_EQUALS(
		"string.format() float with prec spec failed",
		execute( "main(){return(\"[{:6.2f}, {:6.2f}, {:12.6f}, {:6.0f}, {:6.2n}, {:6.0n}]\".format(13.5, 3.1415, 3.1415, 3.1415, $3, $3.1415));}" ),
		"\"[ 13.50,   3.14,     3.141500,     3.,   3.00,     3.]\""
	);
	ENSURE_EQUALS( "string.format() on too few args succeeded", execute_except( "main(){s=\"a {} b\";s.format();}" ), "*anonymous stream*:1:27: Wrong value index at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a b\";s.format(1);}" ), "*anonymous stream*:1:24: Not all values used in format at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a {\";s.format();}" ), "*anonymous stream*:1:24: Single '{' encountered in format string at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a { b\";s.format();}" ), "*anonymous stream*:1:26: Invalid format specification at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a } b\";s.format();}" ), "*anonymous stream*:1:26: Single '}' encountered in format string at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a {} {{}} {0} b\";s.format(0, 0);}" ), "*anonymous stream*:1:36: Cannot mix manual and automatic field numbering at: 12" );
	ENSURE_EQUALS( "string.format() on too few args succeeded", execute_except( "main(){s=\"a {9999999999999999999} b\";s.format();}" ), "*anonymous stream*:1:46: Out of range value in conversion: 9999999999999999999" );
	ENSURE_EQUALS( "string.format() on too few args succeeded", execute_except( "main(){s=\"a {99999999999999999} b\";s.format();}" ), "*anonymous stream*:1:44: Cast would lose data." );
	ENSURE_EQUALS( "string.format() invalid type (int) succeeded", execute_except( "main(){s=\"a {:d} b\";s.format(1.);}" ), "*anonymous stream*:1:29: Expected an `integer` type at: 5" );
	ENSURE_EQUALS( "string.format() invalid type (real) succeeded", execute_except( "main(){s=\"a {:f} b\";s.format(1);}" ), "*anonymous stream*:1:29: Expected a `real` type at: 5" );
	ENSURE_EQUALS( "string.format() invalid type (str) succeeded", execute_except( "main(){s=\"a {:s} b\";s.format(1);}" ), "*anonymous stream*:1:29: Expected a `string` type at: 5" );
	ENSURE_EQUALS( "string.format() invalid type (char) succeeded", execute_except( "main(){s=\"a {:c} b\";s.format(1);}" ), "*anonymous stream*:1:29: Expected a `character` type at: 5" );
	ENSURE_EQUALS( "string.format() invalid type succeeded", execute_except( "main(){s=\"a {:q} b\";s.format(1);}" ), "*anonymous stream*:1:29: Invalid type specification at: 5" );
	ENSURE_EQUALS( "string.format() invalid width succeeded", execute_except( "main(){s=\"a {:kd} b\";s.format(1);}" ), "*anonymous stream*:1:30: Invalid argument in conversion: k at: 6" );
	ENSURE_EQUALS( "user to str failed", execute( "class A{_x=none;constructor(x){_x=x;}to_string(){return(\"~\"+string(_x)+\"~\");}}main(){return(string(A(7)));}" ), "\"~7~\"" );
	ENSURE_EQUALS( "bad user to str succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(string(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:59: Class `A` does not have `to_string` method." );
	ENSURE_EQUALS( "bad user to str (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_string(){return(this);}}main(){return(string(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:85: User supplied `to_string` function returned an invalid type an `A` instead of a `string`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "integer()" )
	ENSURE_EQUALS( "int to int failed", execute( "main(){return(integer(7));}" ), "7" );
	ENSURE_EQUALS( "bad string to int succeeded", execute_except( "main(){return(integer(\"bad\"));}" ), "*anonymous stream*:1:22: Uncaught ConversionException: not a number: `bad`" );
	ENSURE_EQUALS( "real to int failed", execute( "main(){return(integer(7.));}" ), "7" );
	ENSURE_EQUALS( "num to int failed", execute( "main(){return(integer($7));}" ), "7" );
	ENSURE_EQUALS( "char to int failed", execute( "main(){return(integer('7'));}" ), "55" );
	ENSURE_EQUALS( "string to int failed", execute( "main(){return(integer(\"7\"));}" ), "7" );
	ENSURE_EQUALS( "copy( int ) failed", execute( "main(){x=0;y=x;z=copy(x);x+=1;return([x,y,z]);}" ), "[1, 1, 0]" );
	ENSURE_EQUALS( "user to int failed", execute( "class A{_x=none;constructor(x){_x=x;}to_integer(){return(_x);}}main(){return(integer(A(7)));}" ), "7" );
	ENSURE_EQUALS( "bad user to int succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(integer(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:60: Class `A` does not have `to_integer` method." );
	ENSURE_EQUALS( "bad user to int (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_integer(){return(this);}}main(){return(integer(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:87: User conversion method returned invalid type an `A` instead of an `integer`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean()" )
	ENSURE_EQUALS( "boolean to boolean failed", execute( "main(){return([boolean(true),boolean(false)]);}" ), "[true, false]" );
	ENSURE_EQUALS( "int to boolean succeeded", execute_except( "main(){return(boolean(7));}" ), "*anonymous stream*:1:22: Conversion from an `integer` to a `boolean` is not supported." );
	ENSURE_EQUALS( "bad user to int succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(boolean(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:60: Class `A` does not have `to_boolean` method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "real()" )
	ENSURE_EQUALS( "real to real failed", execute( "main(){return(real(7));}" ), "7.0" );
	ENSURE_EQUALS( "bad string to real succeeded", execute_except( "main(){return(real(\"bad\"));}" ), "*anonymous stream*:1:19: Uncaught ConversionException: syntax error - unknown mnemonic for: bad, at: 0" );
	ENSURE_EQUALS( "real to real failed", execute( "main(){return(real(7.));}" ), "7.0" );
	ENSURE_EQUALS( "num to real failed", execute( "main(){return(real($7));}" ), "7.0" );
	ENSURE_EQUALS( "string to real failed", execute( "main(){return(real(\"7\"));}" ), "7.0" );
	ENSURE_EQUALS( "copy( real ) failed", execute( "main(){x=0.;y=x;z=copy(x);x+=1.;return([x,y,z]);}" ), "[1.0, 1.0, 0.0]" );
	ENSURE_EQUALS( "user to real failed", execute( "class A{_x=none;constructor(x){_x=x;}to_real(){return(_x);}}main(){return(real(A(7.)));}" ), "7.0" );
	ENSURE_EQUALS( "bad user to real succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(real(A(7.)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:57: Class `A` does not have `to_real` method." );
	ENSURE_EQUALS( "char to real succeeded", execute_except( "main(){return(real('7'));}" ), "*anonymous stream*:1:19: Conversion from a `character` to a `real` is not supported." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number()" )
	ENSURE_EQUALS( "number to number failed", execute( "main(){return(number(7));}" ), "$7" );
	ENSURE_EQUALS( "bad string to number succeeded", execute_except( "main(){return(number(\"bad\"));}" ), "*anonymous stream*:1:21: Uncaught ConversionException: Not a number." );
	ENSURE_EQUALS( "bad real to number succeeded", execute_except( "import Text as T;main(){return(number(real(T.repeat(\"9\",5000))));}" ), "*anonymous stream*:1:38: Uncaught ConversionException: Not a number." );
	ENSURE_EQUALS( "number to number failed", execute( "main(){return(number(7.));}" ), "$7" );
	ENSURE_EQUALS( "num to number failed", execute( "main(){return(number($7));}" ), "$7" );
	ENSURE_EQUALS( "string to number failed", execute( "main(){return(number(\"7\"));}" ), "$7" );
	ENSURE_EQUALS( "copy( number ) failed", execute( "main(){x=$0;y=x;z=copy(x);x+=$1;return([x,y,z]);}" ), "[$1, $1, $0]" );
	ENSURE_EQUALS( "user to number failed", execute( "class A{_x=none;constructor(x){_x=x;}to_number(){return(_x);}}main(){return(number(A($7)));}" ), "$7" );
	ENSURE_EQUALS( "bad user to number succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(number(A(7.)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:59: Class `A` does not have `to_number` method." );
	ENSURE_EQUALS( "char to number succeeded", execute_except( "main(){return(number('7'));}" ), "*anonymous stream*:1:21: Conversion from a `character` to a `number` is not supported." );
	ENSURE_EQUALS( "number.is_exact() failed", execute( "main(){return([($2/$5).is_exact(),($2/$3).is_exact()]);}" ), "[true, false]" );
	ENSURE_EQUALS( "number.is_integral() failed", execute( "main(){return([($15/$5).is_integral(),($15/$6).is_integral()]);}" ), "[true, false]" );
	ENSURE_EQUALS( "number.set_precision()/number.get_precision() failed", execute( "main(){a=$1;a.set_precision(200);b=$3;b.set_precision(300);return([a.get_precision(),b.get_precision()]);}" ), "[200, 300]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "character()" )
	ENSURE_EQUALS( "character to character failed", execute( "main(){return(character('7'));}" ), "'7'" );
	ENSURE_EQUALS( "integer to character failed", execute( "main(){return(character(97));}" ), "'a'" );
	ENSURE_EQUALS( "copy( character ) failed", execute( "main(){x='a';y=x;z=copy(x);x.to_upper();return([x,y,z]);}" ), "['A', 'A', 'a']" );
	ENSURE_EQUALS( "real to character succeeded", execute_except( "main(){return(character(7.));}" ), "*anonymous stream*:1:24: Conversion from a `real` to a `character` is not supported." );
	ENSURE_EQUALS( "character.to_upper() failed", execute( "main(){x='a';x.to_upper();return(x);}" ), "'A'" );
	ENSURE_EQUALS( "character.to_lower() failed", execute( "main(){x='A';x.to_lower();return(x);}" ), "'a'" );
	ENSURE_EQUALS(
		"character.is_*() failed",
		execute(
			"main(){\n"
			"return([\n"
			"'a'.is_lower(),\n"  // 0
			"'a'.is_upper(),\n"  // 1
			"'A'.is_lower(),\n"  // 2
			"'A'.is_upper(),\n"  // 3
			"'a'.is_digit(),\n"  // 4
			"'a'.is_xdigit(),\n" // 5
			"'0'.is_digit(),\n"  // 6
			"'0'.is_xdigit(),\n" // 7
			"'a'.is_space(),\n"  // 8
			"' '.is_space(),\n"  // 9
			"'a'.is_alpha(),\n"  // 10
			"'0'.is_alpha(),\n"  // 11
			"'a'.is_alnum(),\n"  // 12
			"'_'.is_alnum()\n"   // 13
			"]);\n"
			"}\n"
		),
		//0     1      2      3     4      5     6     7     8      9     10    11     12    13
		"[true, false, false, true, false, true, true, true, false, true, true, false, true, false]"
	);
	ENSURE_EQUALS( "bad user to character succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(character(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:62: Class `A` does not have `to_character` method." );
	ENSURE_EQUALS( "bad user to character (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_character(){return(this);}}main(){return(character(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:91: User conversion method returned invalid type an `A` instead of a `character`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "blob" )
	ENSURE_EQUALS(
		"blob copy",
		execute(
			"main(){\n"
			"b=blob(100);\n"
			"bc = copy( b );"
			"return(size(bc));\n"
			"}\n"
		),
		"100"
	);
	ENSURE_EQUALS(
		"blob bad size",
		execute_except(
			"main(){\n"
			"blob(0);\n"
			"}\n"
		),
		"*anonymous stream*:2:5: Invalid `blob` size requested: 0"
	);
#ifdef __HOST_OS_TYPE_DARWIN__
	if ( setup._jobs > 1 ) {
		return;
	}
#endif /* #ifdef __HOST_OS_TYPE_DARWIN__ */
#if ( SIZEOF_INT_LONG == 8 )
	char const errMsg[] = "*anonymous stream*:2:5: Uncaught RuntimeException: memory::realloc: realloc returned NULL";
#else
	char const errMsg[] = "*anonymous stream*:2:5: Requested `blob` size is too big: 2305843009213693952";
#endif
	ENSURE_EQUALS(
		"blob bad size",
		execute_except(
			"main(){\n"
			"blob(2305843009213693952);\n"
			"}\n"
		),
		errMsg
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream" )
	ENSURE_EQUALS(
		"(de)serialization - none",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(none);"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[none, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - boolean",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(true).serialize(false);"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[true, false, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - integer",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize( -1000000000000000000 ).serialize( 0 ).serialize( 1000000000000000000 );"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[-1000000000000000000, 0, 1000000000000000000, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - real",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize( -3.1415926535897932 ).serialize( 0. ).serialize( 2.718281828459045 );"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[-3.14159265359, 0.0, 2.718281828459, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - string",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(\"Huginn ✓\").serialize(\"\");"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[\"Huginn ✓\", \"\", \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - number",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize( $-123456789012345678901234567890.012345678901234567890123456789 ).serialize( $0 ).serialize( $123456789012345678901234567890.012345678901234567890123456789 );"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[$-123456789012345678901234567890.012345678901234567890123456789, $0, $123456789012345678901234567890.012345678901234567890123456789, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - character",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize('H').serialize('✓');"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"['H', '✓', \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - function",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(type);"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[type, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - tuple",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize((1,2,3)).serialize(());"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[(1, 2, 3), (), \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - list",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize([1,2,3]).serialize([]);"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[[1, 2, 3], [], \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - deque",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(deque(1,2,3)).serialize(deque());"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[deque(1, 2, 3), deque(), \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - dict",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize([1:2,2:4,3:8]).serialize(dict());"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[[1: 2, 2: 4, 3: 8], dict(), \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - lookup",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize({1:2,2:4,3:8}).serialize({});"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[{3: 8, 1: 2, 2: 4}, {}, \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - order",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(order(1,2,3)).serialize(order());"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[order(1, 2, 3), order(), \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - set",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize({1,2,3}).serialize(set());"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[{3, 1, 2}, set(), \"Not enough data in the stream.\"]"
	);
	ENSURE_EQUALS(
		"(de)serialization - heap",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize(heap(1,2,3)).serialize(heap());"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [f.deserialize(),f.deserialize()];"
			"try {\n"
			"f.deserialize();\n"
			"}catch(Exception e) {\n"
			"res.push(e.what());\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[heap(3, 2, 1), heap(), \"Not enough data in the stream.\"]"
	);
	ENSURE_IN(
		"serialization",
		execute(
			"import Algorithms as algo;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"myDict = [1:2,2:4,3:8];"
			"myLookup = {1:2,\"abc\":3,2.718281828459045:type,'π':$3.1415926535897932};\n"
			"myList = [1,2,3,4,5];\n"
			"str = \"Huginn\";\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE )"
			".serialize(13)"
			".serialize('✓')"
			".serialize(str)"
			".serialize($123456789012345678901234567890)"
			".serialize(myList)"
			".serialize(9.87654321)"
			".serialize(myDict)"
			".serialize((7,6,5))"
			".serialize(myLookup);\n"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"res = [];"
			"for( i : algo.range( 9 ) ) {\n"
			"try {\n"
			"res.push(f.deserialize());\n"
			"}catch(Exception e) {\n"
			"res.push(\"{} {}\".format(e.what(),i));\n"
			"}\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		std::vector<hcore::HString>({
			"[13, '✓', \"Huginn\", $123456789012345678901234567890, [1, 2, 3, 4, 5], 9.87654321, [1: 2, 2: 4, 3: 8], (7, 6, 5), {1: 2, \"abc\": 3, 2.718281828459: type, 'π': $3.1415926535897932}]",
			"[13, '✓', \"Huginn\", $123456789012345678901234567890, [1, 2, 3, 4, 5], 9.87654321, [1: 2, 2: 4, 3: 8], (7, 6, 5), {1: 2, 2.718281828459: type, \"abc\": 3, 'π': $3.1415926535897932}]"
		} )
	);
TUT_TEARDOWN()

// 012345678901234567890
// tppppcccciiiisddddddd

TUT_UNIT_TEST( "Stream deserialize number errors" )
	ENSURE_EQUALS(
		"deserialization - number (1)",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"{fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).serialize($3.141592653589793);}\n"
			"b = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ).read_blob(1000);\n"
			"res = [];\n"
			"for( l : [1, 5, 9, 12, 13, 24, 25 ] ) {\n"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).write_blob(b, l + 1);\n"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"try {\n"
			"res.push(f.deserialize());\n"
			"}catch(Exception e) {\n"
			"res.push( e.what() );\n"
			"}\n"
			"}\n"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"t = f.read_integer(1);"
			"fs.open( \"./out/huginn.hds\", fs.OPEN_MODE.WRITE ).write_integer(t,1).write_integer(24,4).write_integer(3,4).write_integer(7,4).write_integer(3,4).write_integer(14159265,4).write_integer(3589793,4);\n"
			"f = fs.open(\"./out/huginn.hds\",fs.OPEN_MODE.READ);\n"
			"try {\n"
			"res.push(f.deserialize());\n"
			"}catch(Exception e) {\n"
			"res.push( e.what() );\n"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[\"Not enough data in the stream.\", "
		"\"Not enough data in the stream.\", "
		"\"Not enough data in the stream.\", "
		"\"Not enough data in the stream.\", "
		"\"Not enough data in the stream.\", "
		"\"Not enough data in the stream.\", "
		"$3.141592653589793, "
		"\"Malformed Huginn data stream.\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream read/write integer" )
	ENSURE_EQUALS(
		"read/write of integers 1 byte failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(127,1);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer(1), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(127, 1)"
	);
	ENSURE_EQUALS(
		"read/write of integers 1 byte overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(128,1);\n"
			"}\n"
		),
		"*anonymous stream*:4:16: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of integers 2 bytes failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(32767,2);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer(2), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(32767, 2)"
	);
	ENSURE_EQUALS(
		"read/write of integers 2 bytes overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(32768,2);\n"
			"}\n"
		),
		"*anonymous stream*:4:16: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of integers 4 bytes failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(2147483647,4);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer(4), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(2147483647, 4)"
	);
	ENSURE_EQUALS(
		"read/write of integers 4 bytes overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(2147483648,4);\n"
			"}\n"
		),
		"*anonymous stream*:4:16: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of integers 8 bytes failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(9223372036854775807,8);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer(8), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(9223372036854775807, 8)"
	);
	ENSURE_EQUALS(
		"read/write of integers, bad write size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer(100,3);\n"
			"}\n"
		),
		"*anonymous stream*:4:16: Invalid write size."
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers, bad read size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"f.read_integer(3);\n"
			"}\n"
		),
		"*anonymous stream*:4:15: Invalid read size."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream read/write unsigned 1 byte integer" )
	ENSURE_EQUALS(
		"read/write of unsigned integers failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(255,1);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer_unsigned(1), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(255, 1)"
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers 1 byte overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(256,1);\n"
			"}\n"
		),
		"*anonymous stream*:4:25: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers 2 bytes failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(65535,2);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer_unsigned(2), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(65535, 2)"
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers 2 bytes overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(65536,2);\n"
			"}\n"
		),
		"*anonymous stream*:4:25: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers 4 bytes failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(4294967295,4);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer_unsigned(4), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(4294967295, 4)"
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers 4 bytes overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(4294967296,4);\n"
			"}\n"
		),
		"*anonymous stream*:4:25: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers 8 bytes failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(9223372036854775807,8);\n"
			"f = none;\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_integer_unsigned(8), fs.stat(\"./out/integer.hds\").size()));"
			"}\n"
		),
		"(9223372036854775807, 8)"
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers, invalid write size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_integer_unsigned(100,3);\n"
			"}\n"
		),
		"*anonymous stream*:4:25: Invalid write size."
	);
	ENSURE_EQUALS(
		"read/write of unsigned integers, invalid read size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/integer.hds\", fs.OPEN_MODE.READ);\n"
			"f.read_integer_unsigned(3);\n"
			"}\n"
		),
		"*anonymous stream*:4:24: Invalid read size."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream read/write character" )
	ENSURE_EQUALS(
		"read/write of character 8-bit failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_character('ó',1);\n"
			"f = none;\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_character(1), fs.stat(\"./out/character.hds\").size()));"
			"}\n"
		),
		"('ó', 1)"
	);
	ENSURE_EQUALS(
		"read/write of character 8-bit overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_character('ą',1);\n"
			"}\n"
		),
		"*anonymous stream*:4:18: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of character 16 bits failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_character('ą',2);\n"
			"f = none;\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_character(2), fs.stat(\"./out/character.hds\").size()));"
			"}\n"
		),
		"('ą', 2)"
	);
	ENSURE_EQUALS(
		"read/write of character 16-bits overflow failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_character('🐍',2);\n"
			"}\n"
		),
		"*anonymous stream*:4:18: Uncaught FileSystemException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"read/write of character 32-bits failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_character('🐍',4);\n"
			"f = none;\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_character(4), fs.stat(\"./out/character.hds\").size()));"
			"}\n"
		),
		"('🐍', 4)"
	);
	ENSURE_EQUALS(
		"read/write of character, invalid write size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_character('🐍',3);\n"
			"}\n"
		),
		"*anonymous stream*:4:18: Invalid write size."
	);
	ENSURE_EQUALS(
		"read/write of character, invalid read size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/character.hds\", fs.OPEN_MODE.READ);\n"
			"f.read_character(3);\n"
			"}\n"
		),
		"*anonymous stream*:4:17: Invalid read size."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream read/write real" )
	ENSURE_EQUALS(
		"read/write of real (float) failed",
		execute(
			"import Mathematics as math;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_real(3.141592653589793," M_STRINGIFY( SIZEOF_FLOAT ) ");\n"
			"f = none;\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.READ);\n"
			"return((math.round(f.read_real(" M_STRINGIFY( SIZEOF_FLOAT ) "), 5), fs.stat(\"./out/real.hds\").size()));"
			"}\n"
		),
		"(3.14159, " M_STRINGIFY( SIZEOF_FLOAT ) ")"
	);
	ENSURE_EQUALS(
		"read/write of real (double) failed",
		execute(
			"import Mathematics as math;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_real(3.141592653589793," M_STRINGIFY( SIZEOF_DOUBLE ) ");\n"
			"f = none;\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.READ);\n"
			"return((math.round(f.read_real(" M_STRINGIFY( SIZEOF_DOUBLE ) "), 8), fs.stat(\"./out/real.hds\").size()));"
			"}\n"
		),
		"(3.14159265, " M_STRINGIFY( SIZEOF_DOUBLE ) ")"
	);
	ENSURE_EQUALS(
		"read/write of real (double long) failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_real(3.141592653589793," M_STRINGIFY( SIZEOF_DOUBLE_LONG ) ");\n"
			"f = none;\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.READ);\n"
			"return((f.read_real(" M_STRINGIFY( SIZEOF_DOUBLE_LONG ) "), fs.stat(\"./out/real.hds\").size()));"
			"}\n"
		),
		"(3.14159265359, " M_STRINGIFY( SIZEOF_DOUBLE_LONG ) ")"
	);
	ENSURE_EQUALS(
		"read/write of real, invalid write size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.WRITE);\n"
			"f.write_real(3.141592653589793,3);\n"
			"}\n"
		),
		"*anonymous stream*:4:13: Invalid write size."
	);
	ENSURE_EQUALS(
		"read/write of real, invalid read size failed",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./out/real.hds\", fs.OPEN_MODE.READ);\n"
			"f.read_real(3);\n"
			"}\n"
		),
		"*anonymous stream*:4:12: Invalid read size."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream pump_to" )
	filesystem::remove( "./out/pump.to" );
	ENSURE_EQUALS(
		"pump_to ( default )",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"i = fs.open(\"./data/karatsuba.bc\", fs.OPEN_MODE.READ);\n"
			"o = fs.open(\"./out/pump.to\", fs.OPEN_MODE.WRITE);\n"
			"i.pump_to(o);\n"
			"}\n"
		),
		"1137"
	);
	filesystem::remove( "./out/pump.to" );
	ENSURE_EQUALS(
		"pump_to ( 1 byte buffer )",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"i = fs.open(\"./data/karatsuba.bc\", fs.OPEN_MODE.READ);\n"
			"o = fs.open(\"./out/pump.to\", fs.OPEN_MODE.WRITE);\n"
			"i.pump_to(o,1);\n"
			"}\n"
		),
		"1137"
	);
	ENSURE_EQUALS(
		"pump_to ( buffer size too big )",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"i = fs.open(\"./data/karatsuba.bc\", fs.OPEN_MODE.READ);\n"
			"o = fs.open(\"./out/pump.to\", fs.OPEN_MODE.WRITE);\n"
			"i.pump_to(o,8589934592);\n"
			"}\n"
		),
		"*anonymous stream*:5:10: Uncaught ArithmeticException: Cast would lose data."
	);
	ENSURE_EQUALS(
		"pump_to ( 0 byte buffer )",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"i = fs.open(\"./data/karatsuba.bc\", fs.OPEN_MODE.READ);\n"
			"o = fs.open(\"./out/pump.to\", fs.OPEN_MODE.WRITE);\n"
			"i.pump_to(o,0);\n"
			"}\n"
		),
		"*anonymous stream*:5:10: Invalid buffer size: 0"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream read_lines" )
	ENSURE_EQUALS(
		"read_lines ( with new line on last line )",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./data/lines-nl.txt\", fs.OPEN_MODE.READ);\n"
			"f.read_lines();\n"
			"}\n"
		),
		"[\"one\\n\", \"two\\n\", \"three\\n\"]"
	);
	ENSURE_EQUALS(
		"read_lines ( with *NO* new line on last line )",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"f = fs.open(\"./data/lines-no-nl.txt\", fs.OPEN_MODE.READ);\n"
			"f.read_lines();\n"
			"}\n"
		),
		"[\"one\\n\", \"two\\n\", \"three\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "to_string" )
	ENSURE_EQUALS(
		"cycle detection failed",
		execute(
			"main() {\n"
			"t = ( 0, 1 );\n"
			"x = [t];\n"
			"l = [ 0, 1 ];\n"
			"d = [ 0: 3.14159, 1: 2.71828 ];\n"
			"h = { 0: 3.14159, 1: 2.71828 };\n"
			"t += ( x, );\n"
			"l.push( l );\n"
			"d[2] = d;\n"
			"h[2] = h;\n"
			"s = string( ( t, l, d, h ) );\n"
			"x.clear();\n"
			"l[2] = none;\n"
			"d.erase( 2 );\n"
			"h.erase( 2 );\n"
			"return ( s );\n"
			"}\n"
		),
		"\"((0, 1, [none/*(cycle)*/]), [0, 1, none/*[cycle]*/], [0: 3.14159, 1: 2.71828, 2: none/*cycle*/], {0: 3.14159, 1: 2.71828, 2: none/*{cycle}*/})\""
	);
	ENSURE_EQUALS(
		"to_string function_reference with origin failed",
		execute(
			"import Mathematics as math;"
			"main() {\n"
			"return ( type( math.Complex( 0., 0. ) ) );\n"
			"}\n"
		),
		"math.Complex"
	);
	HHuginn h;
	HStringStream ss( "class A{x=none;}main(){x=A();return((x,type));}" );
	h.load( ss );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	ENSURE_EQUALS( "to_string out of Huginn failed", tools::to_string( h.result() ), "(A, *function_reference*)" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Time" )
	ENSURE_EQUALS( "Time() failed", execute( "main() {\nTime(1978,5,24,23,30,17);\n}\n" ), "Time(1978, 5, 24, 23, 30, 17)" );
	ENSURE_EQUALS( "invalid month hi Time() succeeded", execute_except( "main() {\nTime(2000,13,1,0,0,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `month` in Time constructor: 13." );
	ENSURE_EQUALS( "invalid month lo Time() succeeded", execute_except( "main() {\nTime(2000,0,1,0,0,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `month` in Time constructor: 0." );
	ENSURE_EQUALS( "invalid day hi Time() succeeded", execute_except( "main() {\nTime(2000,1,32,0,0,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `day` in Time constructor: 32." );
	ENSURE_EQUALS( "invalid day lo Time() succeeded", execute_except( "main() {\nTime(2000,1,0,0,0,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `day` in Time constructor: 0." );
	ENSURE_EQUALS( "invalid hour hi Time() succeeded", execute_except( "main() {\nTime(2000,1,1,24,0,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `hour` in Time constructor: 24." );
	ENSURE_EQUALS( "invalid hour lo Time() succeeded", execute_except( "main() {\nTime(2000,1,1,-1,0,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `hour` in Time constructor: -1." );
	ENSURE_EQUALS( "invalid minute hi Time() succeeded", execute_except( "main() {\nTime(2000,1,1,0,60,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `minute` in Time constructor: 60." );
	ENSURE_EQUALS( "invalid minute lo Time() succeeded", execute_except( "main() {\nTime(2000,1,1,0,-1,0);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `minute` in Time constructor: -1." );
	ENSURE_EQUALS( "invalid second hi Time() succeeded", execute_except( "main() {\nTime(2000,1,1,0,0,60);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `second` in Time constructor: 60." );
	ENSURE_EQUALS( "invalid second lo Time() succeeded", execute_except( "main() {\nTime(2000,1,1,0,0,-1);\n}\n" ), "*anonymous stream*:2:5: Invalid value for `second` in Time constructor: -1." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "√" )
	ENSURE_EQUALS( "√ failed", execute( "main() {\n√(4.);\n}\n" ), "2.0" );
	ENSURE_EQUALS( "√ on bad domain succeeded", execute_except( "main() {\n√(-4.);\n}\n" ), "*anonymous stream*:2:2: Uncaught ArithmeticException: bad domain" );
	ENSURE_EQUALS( "√ on bad type succeeded", execute_except( "main() {\n√(4);\n}\n" ), "*anonymous stream*:2:2: √() argument must be a numeric type, either a `number` or a `real`, not an `integer`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "∑" )
	ENSURE_EQUALS( "∑ failed", execute( "main() {\n∑([1, 2, 4]);\n}\n" ), "7" );
	ENSURE_EQUALS( "∑ on bad domain succeeded", execute_except( "main() {\n∑([]);\n}\n" ), "*anonymous stream*:2:2: ∑ on empty." );
	ENSURE_EQUALS( "∑ on bad type succeeded", execute_except( "main() {\n∑([1,2.]);\n}\n" ), "*anonymous stream*:2:2: A non-uniform set under ∑." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "∏" )
	ENSURE_EQUALS( "∏ failed", execute( "main() {\n∏([1, 2, 4]);\n}\n" ), "8" );
	ENSURE_EQUALS( "∏ on bad domain succeeded", execute_except( "main() {\n∏([]);\n}\n" ), "*anonymous stream*:2:2: ∏ on empty." );
	ENSURE_EQUALS( "∏ on bad type succeeded", execute_except( "main() {\n∏([1,2.]);\n}\n" ), "*anonymous stream*:2:2: A non-uniform set under ∏." );
TUT_TEARDOWN()

}


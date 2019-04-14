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
	ENSURE_EQUALS( "bad user to str (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_string(){return(this);}}main(){return(string(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:85: User conversion method returned invalid type an `A` instead of a `string`." );
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

TUT_UNIT_TEST( "tuple()" )
	ENSURE_EQUALS(
		"tuple failed (explicit)",
		execute( "main(){x=tuple(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS(
		"tuple failed (literal)",
		execute( "main(){x=(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS( "tuple failed (crazy)", execute( "f(a){return(\"X\"+a+\"X\");}main(){return((f,)[0](\"hi\"));}" ), "\"XhiX\"" );
	ENSURE_EQUALS(
		"list find failed",
		execute(
			"main(){"
			"x=(2,3,2,5,3,2,7);"
			"return((x.find(2),x.find(3),x.find(5),x.find(7),x.find(0),x.find(2,2), x.find(2,3), x.find(2,2,2)));"
			"}"
		),
		"(0, 1, 3, 6, -1, 2, 5, -1)"
	);
	ENSURE_EQUALS(
		"tuple to_string failed",
		execute( "main(){x=tuple(2,3,5,7);return(x);}" ),
		"(2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"tuple append failed",
		execute( "main(){x=(2,3,5,7);x += (4,8,16);return(x);}" ),
		"(2, 3, 5, 7, 4, 8, 16)"
	);
	ENSURE_EQUALS( "tuple reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed((2,3,5,7)),tuple);}" ), "(7, 5, 3, 2)" );
	ENSURE_EQUALS( "tuple size/copy reversed() failed", execute( "import Algorithms as algo;main(){x=algo.reversed((2,3,5,7));(algo.materialize(copy(x),tuple),size(x));}" ), "((7, 5, 3, 2), 4)" );
	ENSURE_EQUALS(
		"tuple equals failed",
		execute(
			"main(){"
			"t1=(1,2,3);"
			"t2=(1,2,3);"
			"t3=(1,2,4);"
			"return((t1==t2,t1==t3));}"
		),
		"(true, false)"
	);
	ENSURE_EQUALS(
		"tuple equals failed",
		execute(
			"main(){"
			"t1=(1,2,3);"
			"t2=(1,2,3);"
			"t3=(1,2,4);"
			"return((t1<t2,t1<t3));}"
		),
		"(false, true)"
	);
	ENSURE_EQUALS(
		"tuple() iterator failed",
		execute( "main(){x=(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"tuple copy failed",
		execute( "main(){s=\"orig\";x=tuple(2,3,s);y=copy(x);s+=\"new\";return((x,y));}" ),
		"((2, 3, \"orignew\"), (2, 3, \"orig\"))"
	);
	ENSURE_EQUALS(
		"tuple hash failed",
		execute( "main(){(().hash(),(1,).hash());}" ),
		"(7, 22)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "list()" )
	ENSURE_EQUALS(
		"list failed (explicit)",
		execute( "main(){x=list(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS(
		"list failed (literal)",
		execute( "main(){x=[\"a\",\"b\",\"c\"];v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS( "list failed (crazy)", execute( "f(a){return(\"X\"+a+\"X\");}main(){return([f][0](\"hi\"));}" ), "\"XhiX\"" );
	ENSURE_EQUALS(
		"list to_string failed",
		execute( "main(){x=list(2,3,5,7);return(x);}" ),
		"[2, 3, 5, 7]"
	);
	ENSURE_EQUALS(
		"list push failed",
		execute( "main(){x=list(2,3,5,7);x.push(0);return(x);}" ),
		"[2, 3, 5, 7, 0]"
	);
	ENSURE_EQUALS(
		"list append failed",
		execute( "main(){x=[2,3,5,7];x.append([4,8,16]).append(deque(20)).append(order(30)).append({40}).append((11,22,33));return(x);}" ),
		"[2, 3, 5, 7, 4, 8, 16, 20, 30, 40, 11, 22, 33]"
	);
	ENSURE_EQUALS(
		"list insert failed",
		execute( "main(){x=[2,3,5,7];x.insert(2, 0).insert(5, -1);return(x);}" ),
		"[2, 3, 0, 5, 7, -1]"
	);
	ENSURE_EQUALS(
		"list insert on invalid position succeeded",
		execute_except( "main(){x=[2,3,5,7];x.insert(5,-1);}" ),
		"*anonymous stream*:1:28: invalid insertion position: 5"
	);
	ENSURE_EQUALS(
		"list resize failed",
		execute( "main(){x=[].resize(5,0);x[0]+=1;y=copy(x).resize(3,none);return((x,y));}" ),
		"([1, 0, 0, 0, 0], [1, 0, 0])"
	);
	ENSURE_EQUALS(
		"list resize with invalid size succeeded",
		execute_except( "main(){[].resize(-1,none);}" ),
		"*anonymous stream*:1:17: invalid new size: -1"
	);
	ENSURE_EQUALS(
		"list pop failed",
		execute( "main(){x=list(2,3,5,7);x.pop();return(x);}" ),
		"[2, 3, 5]"
	);
	ENSURE_EQUALS(
		"list sort failed",
		execute(
			"main(){\n"
			"l=[2,7,3,9,0,-5];\n"
			"return(l.sort());\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"list sort (key retr func) failed",
		execute(
			"class Pair {\n"
			"_first = none;\n"
			"_second = none;\n"
			"constructor( first_, second_ ) {\n"
			"_first = first_;\n"
			"_second = second_;\n"
			"}\n"
			"to_string() {\n"
			"return(\"{{{}, {}}}\".format(_first,_second));\n"
			"}\n"
			"}\n"
			"main(){\n"
			"l=[Pair(2,9),Pair(7,3),Pair(3,-1),Pair(9,4),Pair(0,2),Pair(-5,7)];\n"
			"return((copy(l).sort(@(x){x._first;}),l.sort(@(x){x._second;})));\n"
			"}"
		),
		"([{-5, 7}, {0, 2}, {2, 9}, {3, -1}, {7, 3}, {9, 4}], [{3, -1}, {0, 2}, {7, 3}, {9, 4}, {-5, 7}, {2, 9}])"
	);
	ENSURE_EQUALS(
		"list clear failed",
		execute( "main(){x=list(2,3,5,7);x.clear();return(x);}" ),
		"[]"
	);
	ENSURE_EQUALS(
		"list find failed",
		execute(
			"main(){"
			"x=[2,3,2,5,3,2,7];"
			"return([x.find(2),x.find(3),x.find(5),x.find(7),x.find(0),x.find(2,2), x.find(2,3), x.find(2,2,2)]);"
			"}"
		),
		"[0, 1, 3, 6, -1, 2, 5, -1]"
	);
	ENSURE_EQUALS( "list reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed([2,3,5,7]),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "list size/copy reversed() failed", execute( "import Algorithms as algo;main(){x=algo.reversed([2,3,5,7]);algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"list equals failed",
		execute(
			"main(){"
			"l1=[1,2,3];"
			"l2=[1,2,3];"
			"l3=[1,2,4];"
			"return([l1==l2,l1==l3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"list equals failed",
		execute(
			"main(){"
			"l1=[1,2,3];"
			"l2=[1,2,3];"
			"l3=[1,2,4];"
			"return([l1<l2,l1<l3]);}"
		),
		"[false, true]"
	);
	ENSURE_EQUALS(
		"list() iterator failed",
		execute( "main(){x=[2,3,5,7];v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"list copy failed",
		execute( "main(){x=list(2,3,5);y=copy(x);x.push(7);return([x,y]);}" ),
		"[[2, 3, 5, 7], [2, 3, 5]]"
	);
	ENSURE_EQUALS(
		"list hash failed",
		execute( "main(){[[].hash(),[1].hash()];}" ),
		"[8, 25]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "deque()" )
	ENSURE_EQUALS(
		"deque failed (explicit)",
		execute( "main(){x=deque(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS(
		"deque to_string failed",
		execute( "main(){x=deque(2,3,5,7);return(x);}" ),
		"deque(2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque push failed",
		execute( "main(){x=deque(2,3,5,7);x.push(0);return(x);}" ),
		"deque(2, 3, 5, 7, 0)"
	);
	ENSURE_EQUALS(
		"deque push_front failed",
		execute( "main(){x=deque(2,3,5,7);x.push_front(0);return(x);}" ),
		"deque(0, 2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque pop failed",
		execute( "main(){x=deque(2,3,5,7);x.pop();return(x);}" ),
		"deque(2, 3, 5)"
	);
	ENSURE_EQUALS(
		"deque append failed",
		execute( "main(){x=deque(2,3,5,7);x.append([4,8,16]).append(deque(20)).append(order(30)).append({40}).append((11,22,33));return(x);}" ),
		"deque(2, 3, 5, 7, 4, 8, 16, 20, 30, 40, 11, 22, 33)"
	);
	ENSURE_EQUALS(
		"deque prepend failed",
		execute( "main(){x=deque(2,3,5,7);x.prepend([4,8,16]).prepend(deque(20)).prepend(order(30)).prepend({40}).prepend((11,22,33));return(x);}" ),
		"deque(11, 22, 33, 40, 30, 20, 4, 8, 16, 2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque insert failed",
		execute( "main(){x=deque(2,3,5,7);x.insert(2, 0).insert(5,-1);return(x);}" ),
		"deque(2, 3, 0, 5, 7, -1)"
	);
	ENSURE_EQUALS(
		"deque insert on invalid position succeeded",
		execute_except( "main(){x=deque(2,3,5,7);x.insert(5,-1);}" ),
		"*anonymous stream*:1:33: invalid insertion position: 5"
	);
	ENSURE_EQUALS(
		"deque pop_front failed",
		execute( "main(){x=deque(2,3,5,7);x.pop_front();return(x);}" ),
		"deque(3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque clear failed",
		execute( "main(){x=deque(2,3,5,7);x.clear();return(x);}" ),
		"deque()"
	);
	ENSURE_EQUALS(
		"deque find failed",
		execute(
			"main(){"
			"x=deque(2,3,2,5,3,2,7);"
			"return(deque(x.find(2),x.find(3),x.find(5),x.find(7),x.find(0),x.find(2,2), x.find(2,3), x.find(2,2,2)));"
			"}"
		),
		"deque(0, 1, 3, 6, -1, 2, 5, -1)"
	);
	ENSURE_EQUALS( "deque reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed(deque(2,3,5,7)),deque);}" ), "deque(7, 5, 3, 2)" );
	ENSURE_EQUALS( "deque reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed(deque(2,3,5,7));algo.materialize(copy(x),deque).push(size(x));}" ), "deque(7, 5, 3, 2, 4)" );
	ENSURE_EQUALS(
		"deque equals failed",
		execute(
			"main(){"
			"d1=deque(1,2,3);"
			"d2=deque(1,2,3);"
			"d3=deque(1,2,4);"
			"return([d1==d2,d1==d3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"deque equals failed",
		execute(
			"main(){"
			"d1=deque(1,2,3);"
			"d2=deque(1,2,3);"
			"d3=deque(1,2,4);"
			"return([d1<d2,d1<d3]);}"
		),
		"[false, true]"
	);
	ENSURE_EQUALS(
		"deque() iterator failed",
		execute( "main(){x=deque(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"deque copy failed",
		execute( "main(){x=deque(2,3,5);y=copy(x);x.push_front(7);return([x,y]);}" ),
		"[deque(7, 2, 3, 5), deque(2, 3, 5)]"
	);
	ENSURE_EQUALS(
		"deque hash failed",
		execute( "main(){[deque().hash(),deque(1).hash()];}" ),
		"[9, 28]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "dict()" )
	ENSURE_EQUALS(
		"dict() iterator failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ),
		"\"Ala0kota.2ma1\""
	);
	ENSURE_EQUALS(
		"dict() failed (explicit)",
		execute( "main(){x=dict();x[\"Ala\"]=0;x[\"ma\"]=1;x[\"kota.\"]=2;return(x);}" ),
		"[\"Ala\": 0, \"kota.\": 2, \"ma\": 1]"
	);
	ENSURE_EQUALS(
		"dict() failed (literal)",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(x);}" ),
		"[\"Ala\": 0, \"kota.\": 2, \"ma\": 1]"
	);
	ENSURE_EQUALS(
		"dict() size() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(size(x));}" ),
		"3"
	);
	ENSURE_EQUALS(
		"dict.kas_key() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return([x.has_key(\"kota.\"),x.has_key(\"psa.\")]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"dict.get()/dict.try_get() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return([x.get(\"ma\"),x.get(\"psa.\",3)]);}" ),
		"[1, 3]"
	);
	ENSURE_EQUALS(
		"dict.ensure() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return((x.ensure(\"data\", 7),x.ensure( \"ma\", 99 ),x));}" ),
		"(7, 1, [\"Ala\": 0, \"data\": 7, \"kota.\": 2, \"ma\": 1])"
	);
	ENSURE_EQUALS(
		"dict.get() on non existing succeeded",
		execute_except( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(x.get(\"psa\"));}" ),
		"*anonymous stream*:1:49: Key does not exist in `dict`."
	);
	ENSURE_EQUALS(
		"dict.erase() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];x.erase(\"kota.\");return(x);}" ),
		"[\"Ala\": 0, \"ma\": 1]"
	);
	ENSURE_EQUALS(
		"dict.clear()/dict.clone() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];y=copy(x);x.clear();return([x,y]);}" ),
		"[dict(), [\"Ala\": 0, \"kota.\": 2, \"ma\": 1]]"
	);
	ENSURE_EQUALS( "dict reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed([2:0,3:1,5:-1,7:-2]),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "dict reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed([2:0,3:1,5:-1,7:-2]);algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"dict equals failed",
		execute(
			"main(){"
			"d1=[1:1,2:2,3:3];"
			"d2=[1:1,2:2,3:3];"
			"d3f=[1:1,2:2,4:3];"
			"d3s=[1:1,2:2,3:4];"
			"return([d1==d2,d1==d3f,d1==d3s]);}"
		),
		"[true, false, false]"
	);
	ENSURE_EQUALS(
		"dict values() failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"d = [0:1,1:2,2:4,3:8];"
			"algo.materialize(d.values(),list);"
			"}"
		),
		"[(0, 1), (1, 2), (2, 4), (3, 8)]"
	);
	ENSURE_EQUALS(
		"dict values() size/copy failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"d = [0:1,1:2,2:4,3:8];"
			"v = copy(d.values());"
			"algo.materialize(v,list).push(size(v));"
			"}"
		),
		"[(0, 1), (1, 2), (2, 4), (3, 8), 4]"
	);
	ENSURE_EQUALS(
		"dict on non-uniform succeeded",
		execute_except( "main(){[1:2,2.:3.];}" ),
		"*anonymous stream*:1:13: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"dict on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){x=[A():0];return(x);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:28: Key type `A` is not a comparable."
	);
	ENSURE_EQUALS(
		"dict update failed",
		execute(
			"main(){\n"
			"d1=[2:2,3:3,5:5];\n"
			"d2=[2:2,4:4,8:8];\n"
			"d1.update(d2);\n"
			"return(d1);\n"
			"}\n"
		),
		"[2: 2, 3: 3, 4: 4, 5: 5, 8: 8]"
	);
	ENSURE_EQUALS(
		"dict.update on non-uniform succeeded",
		execute_except( "main(){[1:2].update([2.:3.]);}" ),
		"*anonymous stream*:1:20: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"dict hash failed",
		execute( "main(){[dict().hash(),[1:2].hash()];}" ),
		"[10, 95]"
	);
	ENSURE_EQUALS(
		"dict clear in for",
		execute(
			"main(){\n"
			"d=[2:2,3:3,5:5];\n"
			"r = [];"
			"for(e:d){d.clear();r.push(e);}\n"
			"r.push(d);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, dict()]"
	);
	ENSURE_EQUALS(
		"dict erase in for",
		execute(
			"main(){\n"
			"d=[2:2,3:3,5:5];\n"
			"r = [];"
			"for(e:d){d.erase(e);r.push(e);}\n"
			"r.push(d);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 3, 5, dict()]"
	);
	ENSURE_EQUALS(
		"dict erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d=[2:2,3:3,5:5];\n"
			"r = [];"
			"for(e:algo.reversed(d)){d.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[5, 3, 2]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "lookup()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected1[] = "{none: 7, true: false, 1: \"ma\", \"Ala\": 0, \"kota.\": 2}";
#else
	char const expected1[] = "{none: 7, true: false, 1: \"ma\", \"kota.\": 2, \"Ala\": 0}";
#endif
	ENSURE_EQUALS(
		"lookup() iterator failed",
		execute( "main(){x={\"Ala\":0,1:\"ma\",\"kota.\":2,none:7,true:false};return(x);}" ),
		expected1
	);
	ENSURE_EQUALS(
		"hash on user succeeded",
		execute_except( "class A{_x=none;}main(){l=lookup();return(l[A()]=0);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:44: Class `A` does not have `hash` method."
	);
	ENSURE_EQUALS(
		"lookup() iterator failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return([x.has_key(1),x.has_key(2)]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"lookup() size failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return(size(x));}" ),
		"5"
	);
	ENSURE_EQUALS(
		"lookup() clear failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;s=size(x);x.clear();return([s,size(x)]);}" ),
		"[5, 0]"
	);
	ENSURE_EQUALS(
		"lookup reversed() failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"algo.materialize(algo.reversed(x),list);"
			"}"
		),
		"[7, 5, 3, 2]"
	);
	ENSURE_EQUALS(
		"lookup reversed() size/copy failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"y=algo.reversed(x);"
			"algo.materialize(copy(y),list).push(size(y));"
			"}"
		),
		"[7, 5, 3, 2, 4]"
	);
	ENSURE_EQUALS(
		"lookup values() failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"algo.materialize(x.values(),list);"
			"}"
		),
		"[(2, 0), (3, 1), (5, -1), (7, -2)]"
	);
	ENSURE_EQUALS(
		"lookup values() size/copy failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"y=x.values();"
			"algo.materialize(copy(y),list).push(size(y));"
			"}"
		),
		"[(2, 0), (3, 1), (5, -1), (7, -2), 4]"
	);
#if ( TARGET_CPU_BITS == 64 )
	char const expected2[] = "\"none7truefalse1maAla0kota.2|1maAla0kota.2\"";
#else
	char const expected2[] = "\"none7truefalse1makota.2Ala0|1makota.2Ala0\"";
#endif
	ENSURE_EQUALS(
		"lookup() erase failed",
		execute( "d(x){v=\"\";for(e:x){v+=string(e);v+=string(x[e]);}return(v);}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;v=d(x);v+=\"|\";x.erase(none);x.erase(true);v+=d(x);return(v);}" ),
		expected2
	);
	ENSURE_EQUALS(
		"lookup() get failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return([x.get(1),x.get(2,7)]);}" ),
		"[\"ma\", 7]"
	);
#if ( TARGET_CPU_BITS == 64 )
	char const expected4[] = "(\"data\", \"ma\", {1: \"ma\", 7: \"data\", \"Ala\": 0, \"kota.\": 2})";
#else
	char const expected4[] = "(\"data\", \"ma\", {1: \"ma\", \"kota.\": 2, 7: \"data\", \"Ala\": 0})";
#endif
	ENSURE_EQUALS(
		"lookup.ensure() failed",
		execute( "main(){x={\"Ala\":0,1:\"ma\",\"kota.\":2};return((x.ensure(7,\"data\"),x.ensure( 1, \"je\" ),x));}" ),
		expected4
	);
	ENSURE_EQUALS(
		"lookup equals failed",
		execute(
			"main(){"
			"l1=lookup();l1[1]=1;l1[2]=2;l1[3]=3;"
			"l2=lookup();l2[1]=1;l2[2]=2;l2[3]=3;"
			"l3f=lookup();l3f[1]=1;l3f[2]=2;l3f[4]=3;"
			"l3s=lookup();l3s[1]=1;l3s[2]=2;l3s[3]=4;"
			"return([l1==l2,l1==l3f,l1==l3s]);}"
		),
		"[true, false, false]"
	);
#if ( TARGET_CPU_BITS == 64 )
	char const expected3[] = "[\"1maAla0kota.2\", \"none7truefalse1maAla0kota.2\"]";
#else
	char const expected3[] = "[\"1makota.2Ala0\", \"none7truefalse1makota.2Ala0\"]";
#endif
	ENSURE_EQUALS(
		"lookup() copy() failed",
		execute( "d(x){v=\"\";for(e:x){v+=string(e);v+=string(x[e]);}return(v);}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;y=copy(x);x.erase(none);x.erase(true);return([d(x),d(y)]);}" ),
		expected3
	);
	ENSURE_EQUALS(
		"lookup update failed",
		execute(
			"main(){\n"
			"l1=lookup();l1[2]=2;l1[3]=3;l1[5]=5;"
			"l2=lookup();l2[2]=2;l2[4]=4;l2[8]=8;"
			"l1.update(l2);\n"
			"r=\"\";\n"
			"for(k:l1) {\n"
			"r+=\"{} -> {}, \".format(k, l1[k]);\n"
			"}\n"
			"return(r);\n"
			"}\n"
		),
		"\"2 -> 2, 3 -> 3, 4 -> 4, 5 -> 5, 8 -> 8, \""
	);
	ENSURE_EQUALS(
		"lookup hash failed",
		execute( "main(){l = lookup();l[1] = 2;[lookup().hash(),l.hash()];}" ),
		"[12, 113]"
	);
	ENSURE_EQUALS(
		"lookup clear in for",
		execute(
			"main(){\n"
			"l={2:2,3:3,5:5};\n"
			"r = [];"
			"for(e:l){l.clear();r.push(e);}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, {}]"
	);
	ENSURE_EQUALS(
		"lookup erase in for",
		execute(
			"main(){\n"
			"l={2:2,3:3,5:5};\n"
			"r = [];"
			"for(e:l){l.erase(e);r.push(e);}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, 5, 2, {}]"
	);
	ENSURE_EQUALS(
		"lookup erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l={2:2,3:3,5:5};\n"
			"r = [];"
			"for(e:algo.reversed(l)){l.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 5, 3]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "order()" )
	ENSURE_EQUALS(
		"order() failed",
		execute( "main(){x=order(2,3,1,4,7,5);x.insert(10).insert(0);return(x);}" ),
		"order(0, 1, 2, 3, 4, 5, 7, 10)"
	);
	ENSURE_EQUALS(
		"order iterator failed",
		execute( "main(){x=order(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"order has_key failed",
		execute( "main(){x=order(2,3,1,4,7,5);return([x.has_key(3),x.has_key(0)]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"order erase failed",
		execute( "main(){x=order(2,3,1,4,7,5);x.erase(3).erase(4);return(x);}" ),
		"order(1, 2, 5, 7)"
	);
	ENSURE_EQUALS(
		"order equals failed",
		execute(
			"main(){"
			"o1=order(1,2,3);"
			"o2=order(1,2,3);"
			"o3=order(1,2,4);"
			"return([o1==o2,o1==o3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"order clear/copy failed",
		execute( "main(){x=order(2,3,1,4,7,5);y=copy(x);x.clear();return([x,y,size(y)]);}" ),
		"[order(), order(1, 2, 3, 4, 5, 7), 6]"
	);
	ENSURE_EQUALS( "order reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed(order(2,3,5,7)),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "order reversed() copy/size failed", execute( "import Algorithms as algo;main(){x=algo.reversed(order(2,3,5,7));algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"order on non-uniform succeeded",
		execute_except( "main(){order(1,2.);}" ),
		"*anonymous stream*:1:13: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"order on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){order(A());}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:30: Key type `A` is not a comparable."
	);
	ENSURE_EQUALS(
		"order update failed",
		execute(
			"main(){\n"
			"o1=order(2,3,5);\n"
			"o2=order(2,4,8);\n"
			"o1.update(o2);\n"
			"return(o1);\n"
			"}\n"
		),
		"order(2, 3, 4, 5, 8)"
	);
	ENSURE_EQUALS(
		"order.update on non-uniform succeeded",
		execute_except( "main(){order(1).update(order(2.));}" ),
		"*anonymous stream*:1:23: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"order hash failed",
		execute( "main(){[order().hash(),order(1).hash()];}" ),
		"[11, 34]"
	);
	ENSURE_EQUALS(
		"order clear in for",
		execute(
			"main(){\n"
			"o=order(2,3,5);\n"
			"r = [];"
			"for(e:o){o.clear();r.push(e);}\n"
			"r.push(o);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, order()]"
	);
	ENSURE_EQUALS(
		"order erase in for",
		execute(
			"main(){\n"
			"o=order(2,3,5);\n"
			"r = [];"
			"for(e:o){o.erase(e);r.push(e);}\n"
			"r.push(o);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 3, 5, order()]"
	);
	ENSURE_EQUALS(
		"order erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"o=order(2,3,5);\n"
			"r = [];"
			"for(e:algo.reversed(o)){o.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[5, 3, 2]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected[] = "{2, 'Q', 3.14, $7.34, \"ala\"}";
#else
	char const expected[] = "{2, 'Q', $7.34, \"ala\", 3.14}";
#endif
	ENSURE_EQUALS(
		"set() failed",
		execute( "main(){x=set(2,\"ala\",3.14);x.insert($7.34).insert('Q');return(x);}" ),
		expected
	);
	ENSURE_EQUALS(
		"set() iterator failed",
		execute( "main(){x=set(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"set has_key failed",
		execute( "main(){x=set(2,\"ala\",3.14);return([x.has_key(\"ala\"),x.has_key(3.145)]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"set erase failed",
		execute( "main(){x=set(2,\"ala\",3.14,$7.34,'Q');x.erase($7.34).erase(\"ala\");return(x);}" ),
		"{2, 'Q', 3.14}"
	);
	ENSURE_EQUALS(
		"set equals failed",
		execute(
			"main(){"
			"s1=set(1,2,3);"
			"s2=set(1,2,3);"
			"s3=set(1,2,4);"
			"return([s1==s2,s1==s3]);}"
		),
		"[true, false]"
	);
	ENSURE_IN(
		"set copy/clear failed",
		execute( "main(){x=set(2,\"ala\",3.14,$7.34,'Q');y=copy(x);x.clear();return([x,y,size(y)]);}" ),
		std::vector<hcore::HString>({ "[set(), {2, 3.14, 'Q', $7.34, \"ala\"}, 5]", "[set(), {2, 'Q', $7.34, \"ala\", 3.14}, 5]" } )
	);
	ENSURE_EQUALS( "set reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed({2,3,5,7}),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "set reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed({2,3,5,7});algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"set update failed",
		execute(
			"main(){\n"
			"s1={2,3,5};\n"
			"s2={2,4,8};\n"
			"s1.update(s2);\n"
			"return(s1);\n"
			"}\n"
		),
		"{2, 3, 4, 5, 8}"
	);
	ENSURE_EQUALS(
		"set hash failed",
		execute( "main(){[set().hash(),{1}.hash()];}" ),
		"[13, 40]"
	);
	ENSURE_EQUALS(
		"set clear in for",
		execute(
			"main(){\n"
			"s={2,3,5};\n"
			"r = [];"
			"for(e:s){s.clear();r.push(e);}\n"
			"r.push(s);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, set()]"
	);
	ENSURE_EQUALS(
		"set erase in for",
		execute(
			"main(){\n"
			"s={2,3,5};\n"
			"r = [];"
			"for(e:s){s.erase(e);r.push(e);}\n"
			"r.push(s);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, 5, 2, set()]"
	);
	ENSURE_EQUALS(
		"set erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s={2,3,5};\n"
			"r = [];"
			"for(e:algo.reversed(s)){s.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 5, 3]"
	);
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
		"read/write of real (doble long) failed",
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


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
	ENSURE_EQUALS( "invalid get_size succeeded (type)", execute_except( "class A{get_size(){0.;}}main(){size(A());}" ), "*anonymous stream*:1:36: User supplied `get_size' method returned an invalid type a `real' instead of an `integer'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add" )
	ENSURE_EQUALS( "add int failed", execute( "main(){return(1+2);}" ), "3" );
	ENSURE_EQUALS( "add-assign int failed", execute( "main(){x=1;x+=2;return(x);}" ), "3" );
	ENSURE_EQUALS( "add real failed", execute( "main(){return(1.+2.);}" ), "3.0" );
	ENSURE_EQUALS( "add number failed", execute( "main(){return($1+$2);}" ), "$3" );
	ENSURE_EQUALS( "add string failed", execute( "main(){return(\"1\"+\"2\");}" ), "\"12\"" );
	ENSURE_EQUALS( "add user succeeded", execute_except( "class A{_x=none;}main(){return(A()+A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `add' method." );
	ENSURE_EQUALS( "add char succeeded", execute_except( "main(){c=character;return(c('1')+c('2'));}" ), "*anonymous stream*:1:33: There is no `+' operator for a `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sub" )
	ENSURE_EQUALS( "sub int failed", execute( "main(){return(7-3);}" ), "4" );
	ENSURE_EQUALS( "sub-assign int failed", execute( "main(){x=7;x-=3;return(x);}" ), "4" );
	ENSURE_EQUALS( "sub real failed", execute( "main(){return(7.-3.);}" ), "4.0" );
	ENSURE_EQUALS( "sub number failed", execute( "main(){return($7-$3);}" ), "$4" );
	ENSURE_EQUALS( "sub user succeeded", execute_except( "class A{_x=none;}main(){return(A()-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `subtract' method." );
	ENSURE_EQUALS( "sub char succeeded", execute_except( "main(){c=character;return(c('7')-c('3'));}" ), "*anonymous stream*:1:33: There is no `-' operator for a `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mul" )
	ENSURE_EQUALS( "mul int failed", execute( "main(){return(2*3);}" ), "6" );
	ENSURE_EQUALS( "mul-assign int failed", execute( "main(){x=2;x*=3;return(x);}" ), "6" );
	ENSURE_EQUALS( "mul real failed", execute( "main(){return(2.*3.);}" ), "6.0" );
	ENSURE_EQUALS( "mul number failed", execute( "main(){return($2*$3);}" ), "$6" );
	ENSURE_EQUALS( "mul user succeeded", execute_except( "class A{_x=none;}main(){return(A()*A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `multiply' method." );
	ENSURE_EQUALS( "mul char succeeded", execute_except( "main(){c=character;return(c('2')*c('3'));}" ), "*anonymous stream*:1:33: There is no `*' operator for a `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "div" )
	ENSURE_EQUALS( "div int failed", execute( "main(){return(7/2);}" ), "3" );
	ENSURE_EQUALS( "div-assign int failed", execute( "main(){x=7;x/=2;return(x);}" ), "3" );
	ENSURE_EQUALS( "div real failed", execute( "main(){return(7./2.);}" ), "3.5" );
	ENSURE_EQUALS( "div number failed", execute( "main(){return($7/$2);}" ), "$3.5" );
	ENSURE_EQUALS( "div user succeeded", execute_except( "class A{_x=none;}main(){return(A()/A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `divide' method." );
	ENSURE_EQUALS( "div char succeeded", execute_except( "main(){c=character;return(c('7')/c('2'));}" ), "*anonymous stream*:1:33: There is no `/' operator for a `character'." );
	ENSURE_EQUALS( "div 0 int succeeded", execute_except( "main(){return(1/0);}" ), "*anonymous stream*:1:16: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "div min_int/-1 int succeeded", execute_except( "main(){return(-9223372036854775808/-1);}" ), "*anonymous stream*:1:35: Uncaught exception: Division overflow." );
	ENSURE_EQUALS( "div 0 real succeeded", execute_except( "main(){return(1./0.);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "div 0 num succeeded", execute_except( "main(){return($1/$0);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod" )
	ENSURE_EQUALS( "mod int failed", execute( "main(){return(11%3);}" ), "2" );
	ENSURE_EQUALS( "mod-assign int failed", execute( "main(){x=11;x%=3;return(x);}" ), "2" );
	ENSURE_EQUALS( "mod real failed", execute( "main(){return(11.%3.);}" ), "2.0" );
	ENSURE_EQUALS( "mod number failed", execute( "main(){return($11%$3);}" ), "$2" );
	ENSURE_EQUALS( "mod user succeeded", execute_except( "class A{_x=none;}main(){return(A()%A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `modulo' method." );
	ENSURE_EQUALS( "mod char succeeded", execute_except( "main(){c=character;return(c('8')%c('3'));}" ), "*anonymous stream*:1:33: There is no `%' operator for a `character'." );
	ENSURE_EQUALS( "mod 0 int succeeded", execute_except( "main(){return(1%0);}" ), "*anonymous stream*:1:16: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "mod min_int%-1 int succeeded", execute_except( "main(){return(-9223372036854775808%-1);}" ), "*anonymous stream*:1:35: Uncaught exception: Division overflow." );
	ENSURE_EQUALS( "mod 0 real succeeded", execute_except( "main(){return(1.%0.);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "mod 0 num succeeded", execute_except( "main(){return($1%$0);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "pow" )
	ENSURE_EQUALS( "pow real failed", execute( "main(){return(2.^3.);}" ), "8.0" );
	ENSURE_EQUALS( "pow number failed", execute( "main(){return($2^$3);}" ), "$8" );
	ENSURE_EQUALS( "pow-assign number failed", execute( "main(){x=$2;x^=$3;return(x);}" ), "$8" );
	ENSURE_EQUALS( "pow user succeeded", execute_except( "class A{_x=none;}main(){return(A()^A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `power' method." );
	ENSURE_EQUALS( "pow char succeeded", execute_except( "main(){c=character;return(c('2')^c('3'));}" ), "*anonymous stream*:1:33: There is no `^' operator for a `character'." );
	ENSURE_EQUALS( "too big exponent succeeded", execute_except( "main(){x=$2;x^=x;x^=x;x^=x;x^=x;}" ), "*anonymous stream*:1:29: Uncaught exception: Exponent too big: 32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389437335543602135433229604645318478604952148193555853611059596230656" );
	ENSURE_EQUALS( "pow 0^0 real succeeded", execute_except( "main(){return(0.^0.);}" ), "*anonymous stream*:1:17: Uncaught exception: indeterminate form 0^0" );
	ENSURE_EQUALS( "pow 0^0 number succeeded", execute_except( "main(){return($0^$0);}" ), "*anonymous stream*:1:17: Uncaught exception: indeterminate form 0^0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "factorial" )
	ENSURE_EQUALS( "neg factorial succeeded", execute_except( "main(){return($-1!);}" ), "*anonymous stream*:1:18: Uncaught exception: Factorial from negative." );
	ENSURE_EQUALS( "fractional factorial succeeded", execute_except( "main(){return($1.5!);}" ), "*anonymous stream*:1:19: Uncaught exception: Factorial from fraction." );
	ENSURE_EQUALS( "int factorial succeeded", execute_except( "main(){return(1!);}" ), "*anonymous stream*:1:16: There is no `!` operator for `integer'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "absolute" )
	ENSURE_EQUALS( "abs int failed", execute( "main(){return([|1|,|-1|]);}" ), "[1, 1]" );
	ENSURE_EQUALS( "abs min_int succeeded", execute_except( "main(){return(|-9223372036854775808|);}" ), "*anonymous stream*:1:36: Uncaught exception: Integer overflow." );
	ENSURE_EQUALS( "abs real failed", execute( "main(){return([|1.|,|-1.|]);}" ), "[1.0, 1.0]" );
	ENSURE_EQUALS( "abs num failed", execute( "main(){return([|$1|,|$-1|]);}" ), "[$1, $1]" );
	ENSURE_EQUALS( "abs char succeeded", execute_except( "main(){c=character;return(|c('1')|);}" ), "*anonymous stream*:1:34: There is no `|...|' operator for a `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "neg" )
	ENSURE_EQUALS( "neg user succeeded", execute_except( "class A{_x=none;}main(){return(-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:32: Class `A' does not have `negate' method." );
	ENSURE_EQUALS( "neg char succeeded", execute_except( "main(){c=character;return(-c('1'));}" ), "*anonymous stream*:1:27: There is no `-x' operator for a `character'." );
	ENSURE_EQUALS( "neg min_int succeeded", execute_except( "main(){return(--9223372036854775808);}" ), "*anonymous stream*:1:15: Uncaught exception: Integer overflow." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equals" )
	ENSURE_EQUALS( "equals none failed", execute( "n(){}main(){return([n()==n(),n()==0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals int failed", execute( "main(){return([1==1,1==0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals real failed", execute( "main(){return([1.==1.,1.==0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals number failed", execute( "main(){return([$1==$1,$1==$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals character failed", execute( "main(){return(['1'=='1','1'=='0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals string failed", execute( "main(){return([\"1\"==\"1\",\"1\"==\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "user failed", execute( "class A{_x=none;constructor(x){_x=x;}equals(x){return(_x==x._x);}}main(){return([A(1)==A(1),A(1)==A(0)]);}", HHuginn::COMPILER::BE_SLOPPY ), "[true, false]" );
	ENSURE_EQUALS( "bad equals user succeeded", execute_except( "class A{equals(x){return(none);}}main(){return(A()==A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:51: Comparison method `equals' returned non-boolean result of a `*none*' type." );
	ENSURE_EQUALS( "missing equals user succeeded", execute_except( "class A{_x=none;}main(){return(A()==A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `equals' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "less" )
	ENSURE_EQUALS( "less int failed", execute( "main(){return([0<1,0<0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "less real failed", execute( "main(){return([0.<1.,0.<0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "less number failed", execute( "main(){return([$0<$1,$0<$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "less character failed", execute( "main(){return(['0'<'1','0'<'0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "less string failed", execute( "main(){return([\"0\"<\"1\",\"0\"<\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "bad less user succeeded", execute_except( "class A{less(x){return(none);}}main(){return(A()<A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:49: Comparison method `less' returned non-boolean result of a `*none*' type." );
	ENSURE_EQUALS( "missing less user succeeded", execute_except( "class A{_x=none;}main(){return(A()<A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `less' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greater" )
	ENSURE_EQUALS( "greater int failed", execute( "main(){return([1>0,0>0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater real failed", execute( "main(){return([1.>0.,0.>0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater number failed", execute( "main(){return([$1>$0,$0>$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater character failed", execute( "main(){return(['1'>'0','0'>'0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater string failed", execute( "main(){return([\"1\">\"0\",\"0\">\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "bad greater user succeeded", execute_except( "class A{greater(x){return(none);}}main(){return(A()>A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:52: Comparison method `greater' returned non-boolean result of a `*none*' type." );
	ENSURE_EQUALS( "missing greater user succeeded", execute_except( "class A{_x=none;}main(){return(A()>A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `greater' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "less_or_equal" )
	ENSURE_EQUALS( "less_or_equal int failed", execute( "main(){return([0<=1,0<=0,1<=0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal real failed", execute( "main(){return([0.<=1.,0.<=0.,1<=0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal number failed", execute( "main(){return([$0<=$1,$0<=$0,$1<=$0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal character failed", execute( "main(){return(['0'<='1','0'<='0','1'<='0']);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal string failed", execute( "main(){return([\"0\"<=\"1\",\"0\"<=\"0\",\"1\"<=\"0\"]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "bad less_or_equal user succeeded", execute_except( "class A{less_or_equal(x){return(none);}}main(){return(A()<=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:58: Comparison method `less_or_equal' returned non-boolean result of a `*none*' type." );
	ENSURE_EQUALS( "missing less_or_equal user succeeded", execute_except( "class A{_x=none;}main(){return(A()<=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `less_or_equal' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greater_or_equal" )
	ENSURE_EQUALS( "greater_or_equal int failed", execute( "main(){return([1>=0,0>=0,0>=1]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal real failed", execute( "main(){return([1.>=0.,0.>=0.,0.>=1.]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal number failed", execute( "main(){return([$1>=$0,$0>=$0,$0>=$1]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal character failed", execute( "main(){return(['1'>='0','0'>='0','0'>='1']);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal string failed", execute( "main(){return([\"1\">=\"0\",\"0\">=\"0\",\"0\">=\"1\"]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "bad greater_or_equal user succeeded", execute_except( "class A{greater_or_equal(x){return(none);}}main(){return(A()>=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:61: Comparison method `greater_or_equal' returned non-boolean result of a `*none*' type." );
	ENSURE_EQUALS( "missing greater_or_equal user succeeded", execute_except( "class A{_x=none;}main(){return(A()>=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `greater_or_equal' method." );
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
	ENSURE_EQUALS( "copy( str ) failed", execute( "main(){x=\"a\";y=x;z=copy(x);x+=\"b\";return([x,y,z]);}" ), "[\"ab\", \"ab\", \"a\"]" );
	ENSURE_EQUALS( "string.strip() failed", execute( "main(){s=\"~huginn~\";return(s.strip(\"~\"));}" ), "\"huginn\"" );
	ENSURE_EQUALS( "string.clear() failed", execute( "main(){s=\"ala ma kota\";s.clear();return(s);}" ), "\"\"" );
	ENSURE_EQUALS( "string reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed(\"Huginn\"),list);}" ), "['n', 'n', 'i', 'g', 'u', 'H']" );
	ENSURE_EQUALS( "string reversed() copy/size failed", execute( "import Algorithms as algo;main(){x=algo.reversed(\"Huginn\");algo.materialize(copy(x),list).push(size(x));}" ), "['n', 'n', 'i', 'g', 'u', 'H', 6]" );
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
			"s=\"a {:#7x} {:02d} b\";\n"
			"return(s.format(123, 1));\n"
			"}\n"
		),
		"\"a    0x7b 01 b\""
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
	ENSURE_EQUALS( "string.format() invalid width succeeded", execute_except( "main(){s=\"a {:kd} b\";s.format(1);}" ), "*anonymous stream*:1:30: not a number: k at: 6" );
	ENSURE_EQUALS( "user to str failed", execute( "class A{_x=none;constructor(x){_x=x;}to_string(){return(\"~\"+string(_x)+\"~\");}}main(){return(string(A(7)));}" ), "\"~7~\"" );
	ENSURE_EQUALS( "bad user to str succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(string(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:59: Class `A' does not have `to_string' method." );
	ENSURE_EQUALS( "bad user to str (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_string(){return(this);}}main(){return(string(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:85: User conversion method returned invalid type an `A' instead of a `string'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "integer()" )
	ENSURE_EQUALS( "int to int failed", execute( "main(){return(integer(7));}" ), "7" );
	ENSURE_EQUALS( "bad string to int succeeded", execute_except( "main(){return(integer(\"bad\"));}" ), "*anonymous stream*:1:22: Uncaught exception: not a number: bad" );
	ENSURE_EQUALS( "real to int failed", execute( "main(){return(integer(7.));}" ), "7" );
	ENSURE_EQUALS( "num to int failed", execute( "main(){return(integer($7));}" ), "7" );
	ENSURE_EQUALS( "char to int failed", execute( "main(){return(integer('7'));}" ), "55" );
	ENSURE_EQUALS( "string to int failed", execute( "main(){return(integer(\"7\"));}" ), "7" );
	ENSURE_EQUALS( "copy( int ) failed", execute( "main(){x=0;y=x;z=copy(x);x+=1;return([x,y,z]);}" ), "[1, 1, 0]" );
	ENSURE_EQUALS( "user to int failed", execute( "class A{_x=none;constructor(x){_x=x;}to_integer(){return(_x);}}main(){return(integer(A(7)));}" ), "7" );
	ENSURE_EQUALS( "bad user to int succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(integer(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:60: Class `A' does not have `to_integer' method." );
	ENSURE_EQUALS( "bad user to int (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_integer(){return(this);}}main(){return(integer(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:87: User conversion method returned invalid type an `A' instead of an `integer'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean()" )
	ENSURE_EQUALS( "boolean to boolean failed", execute( "main(){return([boolean(true),boolean(false)]);}" ), "[true, false]" );
	ENSURE_EQUALS( "int to boolean succeeded", execute_except( "main(){return(boolean(7));}" ), "*anonymous stream*:1:22: Conversion from `integer' to `boolean' is not supported." );
	ENSURE_EQUALS( "bad user to int succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(boolean(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:60: Class `A' does not have `to_boolean' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "real()" )
	ENSURE_EQUALS( "real to real failed", execute( "main(){return(real(7));}" ), "7.0" );
	ENSURE_EQUALS( "bad string to real succeeded", execute_except( "main(){return(real(\"bad\"));}" ), "*anonymous stream*:1:19: Uncaught exception: syntax error - unknown mnemonic for: bad, at: 0" );
	ENSURE_EQUALS( "real to real failed", execute( "main(){return(real(7.));}" ), "7.0" );
	ENSURE_EQUALS( "num to real failed", execute( "main(){return(real($7));}" ), "7.0" );
	ENSURE_EQUALS( "string to real failed", execute( "main(){return(real(\"7\"));}" ), "7.0" );
	ENSURE_EQUALS( "copy( real ) failed", execute( "main(){x=0.;y=x;z=copy(x);x+=1.;return([x,y,z]);}" ), "[1.0, 1.0, 0.0]" );
	ENSURE_EQUALS( "user to real failed", execute( "class A{_x=none;constructor(x){_x=x;}to_real(){return(_x);}}main(){return(real(A(7.)));}" ), "7.0" );
	ENSURE_EQUALS( "bad user to real succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(real(A(7.)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:57: Class `A' does not have `to_real' method." );
	ENSURE_EQUALS( "char to real succeeded", execute_except( "main(){return(real('7'));}" ), "*anonymous stream*:1:19: Conversion from `character' to `real' is not supported." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number()" )
	ENSURE_EQUALS( "number to number failed", execute( "main(){return(number(7));}" ), "$7" );
	ENSURE_EQUALS( "bad string to number succeeded", execute_except( "main(){return(number(\"bad\"));}" ), "*anonymous stream*:1:21: Uncaught exception: Not a number." );
	ENSURE_EQUALS( "bad real to number succeeded", execute_except( "import Text as T;main(){return(number(real(T.repeat(\"9\",5000))));}" ), "*anonymous stream*:1:38: Uncaught exception: Not a number." );
	ENSURE_EQUALS( "number to number failed", execute( "main(){return(number(7.));}" ), "$7" );
	ENSURE_EQUALS( "num to number failed", execute( "main(){return(number($7));}" ), "$7" );
	ENSURE_EQUALS( "string to number failed", execute( "main(){return(number(\"7\"));}" ), "$7" );
	ENSURE_EQUALS( "copy( number ) failed", execute( "main(){x=$0;y=x;z=copy(x);x+=$1;return([x,y,z]);}" ), "[$1, $1, $0]" );
	ENSURE_EQUALS( "user to number failed", execute( "class A{_x=none;constructor(x){_x=x;}to_number(){return(_x);}}main(){return(number(A($7)));}" ), "$7" );
	ENSURE_EQUALS( "bad user to number succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(number(A(7.)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:59: Class `A' does not have `to_number' method." );
	ENSURE_EQUALS( "char to number succeeded", execute_except( "main(){return(number('7'));}" ), "*anonymous stream*:1:21: Conversion from `character' to `number' is not supported." );
	ENSURE_EQUALS( "number.is_exact() failed", execute( "main(){return([($2/$5).is_exact(),($2/$3).is_exact()]);}" ), "[true, false]" );
	ENSURE_EQUALS( "number.is_integral() failed", execute( "main(){return([($15/$5).is_integral(),($15/$6).is_integral()]);}" ), "[true, false]" );
	ENSURE_EQUALS( "number.set_precision()/number.get_precision() failed", execute( "main(){a=$1;a.set_precision(200);b=$3;b.set_precision(300);return([a.get_precision(),b.get_precision()]);}" ), "[200, 300]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "character()" )
	ENSURE_EQUALS( "character to character failed", execute( "main(){return(character('7'));}" ), "'7'" );
	ENSURE_EQUALS( "integer to character failed", execute( "main(){return(character(97));}" ), "'a'" );
	ENSURE_EQUALS( "copy( character ) failed", execute( "main(){x='a';y=x;z=copy(x);x.to_upper();return([x,y,z]);}" ), "['A', 'A', 'a']" );
	ENSURE_EQUALS( "real to character succeeded", execute_except( "main(){return(character(7.));}" ), "*anonymous stream*:1:24: Conversion from `real' to `character' is not supported." );
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
	ENSURE_EQUALS( "bad user to character succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(character(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:62: Class `A' does not have `to_character' method." );
	ENSURE_EQUALS( "bad user to character (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_character(){return(this);}}main(){return(character(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:91: User conversion method returned invalid type an `A' instead of a `character'." );
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
		"dict.get() on non existing succeeded",
		execute_except( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(x.get(\"psa\"));}" ),
		"*anonymous stream*:1:49: Key does not exist in `dict'."
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
		"*anonymous stream*:1:13: Non-uniform key types, got a `real' instead of an `integer'."
	);
	ENSURE_EQUALS(
		"dict on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){x=[A():0];return(x);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:28: Key type `A' is not a comparable."
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
		"*anonymous stream*:1:20: Non-uniform key types, got a `real' instead of an `integer'."
	);
	ENSURE_EQUALS(
		"dict hash failed",
		execute( "main(){[dict().hash(),[1:2].hash()];}" ),
		"[10, 95]"
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
		"*anonymous stream*:1:44: Class `A' does not have `hash' method."
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
		"*anonymous stream*:1:13: Non-uniform key types, got a `real' instead of an `integer'."
	);
	ENSURE_EQUALS(
		"order on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){order(A());}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:30: Key type `A' is not a comparable."
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
		"*anonymous stream*:1:23: Non-uniform key types, got a `real' instead of an `integer'."
	);
	ENSURE_EQUALS(
		"order hash failed",
		execute( "main(){[order().hash(),order(1).hash()];}" ),
		"[11, 34]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected[] = "{$7.34, 2, 'Q', 3.14, \"ala\"}";
#else
	char const expected[] = "{$7.34, 2, 'Q', \"ala\", 3.14}";
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
		std::vector<hcore::HString>({ "[set(), {$7.34, 2, 3.14, 'Q', \"ala\"}, 5]", "[set(), {$7.34, 2, 'Q', \"ala\", 3.14}, 5]" } )
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
TUT_TEARDOWN()

}


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

struct tut_yaal_tools_hhuginn_instructions : public tress::tut_yaal_tools_hhuginn_base {
	void test_subscript( HHuginn::TYPE, char const*, char const* );
	void test_range( HHuginn::TYPE, char const*, char const* );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_instructions, "yaal::tools::HHuginn,instructions" );

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
	ENSURE_EQUALS( "div 0 int succeeded", execute_except( "main(){return(1/0);}" ), "*anonymous stream*:1:16: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "div min_int/-1 int succeeded", execute_except( "main(){return(-9223372036854775808/-1);}" ), "*anonymous stream*:1:35: Uncaught ArithmeticException: Division overflow." );
	ENSURE_EQUALS( "div 0 real succeeded", execute_except( "main(){return(1./0.);}" ), "*anonymous stream*:1:17: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "div 0 num succeeded", execute_except( "main(){return($1/$0);}" ), "*anonymous stream*:1:17: Uncaught ArithmeticException: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod" )
	ENSURE_EQUALS( "mod int failed", execute( "main(){return(11%3);}" ), "2" );
	ENSURE_EQUALS( "mod-assign int failed", execute( "main(){x=11;x%=3;return(x);}" ), "2" );
	ENSURE_EQUALS( "mod real failed", execute( "main(){return(11.%3.);}" ), "2.0" );
	ENSURE_EQUALS( "mod number failed", execute( "main(){return($11%$3);}" ), "$2" );
	ENSURE_EQUALS( "mod user succeeded", execute_except( "class A{_x=none;}main(){return(A()%A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `modulo' method." );
	ENSURE_EQUALS( "mod char succeeded", execute_except( "main(){c=character;return(c('8')%c('3'));}" ), "*anonymous stream*:1:33: There is no `%' operator for a `character'." );
	ENSURE_EQUALS( "mod 0 int succeeded", execute_except( "main(){return(1%0);}" ), "*anonymous stream*:1:16: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "mod min_int%-1 int succeeded", execute_except( "main(){return(-9223372036854775808%-1);}" ), "*anonymous stream*:1:35: Uncaught ArithmeticException: Division overflow." );
	ENSURE_EQUALS( "mod 0 real succeeded", execute_except( "main(){return(1.%0.);}" ), "*anonymous stream*:1:17: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "mod 0 num succeeded", execute_except( "main(){return($1%$0);}" ), "*anonymous stream*:1:17: Uncaught ArithmeticException: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "pow" )
	ENSURE_EQUALS( "pow real failed", execute( "main(){return(2.^3.);}" ), "8.0" );
	ENSURE_EQUALS( "pow number failed", execute( "main(){return($2^$3);}" ), "$8" );
	ENSURE_EQUALS( "pow-assign number failed", execute( "main(){x=$2;x^=$3;return(x);}" ), "$8" );
	ENSURE_EQUALS( "pow user succeeded", execute_except( "class A{_x=none;}main(){return(A()^A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `power' method." );
	ENSURE_EQUALS( "pow char succeeded", execute_except( "main(){c=character;return(c('2')^c('3'));}" ), "*anonymous stream*:1:33: There is no `^' operator for a `character'." );
	ENSURE_EQUALS( "too big exponent succeeded", execute_except( "main(){x=$2;x^=x;x^=x;x^=x;x^=x;}" ), "*anonymous stream*:1:29: Uncaught ArithmeticException: Exponent too big: 32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389437335543602135433229604645318478604952148193555853611059596230656" );
	ENSURE_EQUALS( "pow 0^0 real succeeded", execute_except( "main(){return(0.^0.);}" ), "*anonymous stream*:1:17: Uncaught ArithmeticException: indeterminate form 0^0" );
	ENSURE_EQUALS( "pow 0^0 number succeeded", execute_except( "main(){return($0^$0);}" ), "*anonymous stream*:1:17: Uncaught ArithmeticException: indeterminate form 0^0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "factorial" )
	ENSURE_EQUALS( "neg factorial succeeded", execute_except( "main(){return($-1!);}" ), "*anonymous stream*:1:18: Uncaught ArithmeticException: Factorial from negative." );
	ENSURE_EQUALS( "fractional factorial succeeded", execute_except( "main(){return($1.5!);}" ), "*anonymous stream*:1:19: Uncaught ArithmeticException: Factorial from fraction." );
	ENSURE_EQUALS( "int factorial succeeded", execute_except( "main(){return(1!);}" ), "*anonymous stream*:1:16: There is no `!` operator for an `integer'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "absolute" )
	ENSURE_EQUALS( "abs int failed", execute( "main(){return([|1|,|-1|]);}" ), "[1, 1]" );
	ENSURE_EQUALS( "abs min_int succeeded", execute_except( "main(){return(|-9223372036854775808|);}" ), "*anonymous stream*:1:36: Uncaught ArithmeticException: Integer overflow." );
	ENSURE_EQUALS( "abs real failed", execute( "main(){return([|1.|,|-1.|]);}" ), "[1.0, 1.0]" );
	ENSURE_EQUALS( "abs num failed", execute( "main(){return([|$1|,|$-1|]);}" ), "[$1, $1]" );
	ENSURE_EQUALS( "abs char succeeded", execute_except( "main(){c=character;return(|c('1')|);}" ), "*anonymous stream*:1:34: There is no `|...|' operator for a `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "neg" )
	ENSURE_EQUALS( "neg user succeeded", execute_except( "class A{_x=none;}main(){return(-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:32: Class `A' does not have `negate' method." );
	ENSURE_EQUALS( "neg char succeeded", execute_except( "main(){c=character;return(-c('1'));}" ), "*anonymous stream*:1:27: There is no `-x' operator for a `character'." );
	ENSURE_EQUALS( "neg min_int succeeded", execute_except( "main(){return(--9223372036854775808);}" ), "*anonymous stream*:1:15: Uncaught ArithmeticException: Integer overflow." );
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
	ENSURE_EQUALS(
		"less on *function reference*",
		execute(
			"main() {\n"
			"return((size < type, type < copy, size < copy, type < size, copy < type, copy < size ));\n"
			"}\n"
		),
		"(true, true, true, false, false, false)"
	);
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

TUT_UNIT_TEST( "is_element_of" )
	ENSURE_EQUALS( "is_element_of tuple failed", execute( "main(){x = (2, 3, 5, 7, 11, 17 );return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of list failed", execute( "main(){x = [2, 3, 5, 7, 11, 17 ];return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of deque failed", execute( "main(){x = deque(2, 3, 5, 7, 11, 17 );return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of dict failed", execute( "main(){x = [2:1, 3:2, 5:3, 7:4, 11:5, 17:6];return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of lookup failed", execute( "main(){x = {2:1, 3:2, 5:3, 7:4, 11:5, 17:6};return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of order failed", execute( "main(){x = order(2, 3, 5, 7, 11, 17 );return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of set failed", execute( "main(){x = {2, 3, 5, 7, 11, 17 };return([7 ∈ x, 8 ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of string failed", execute( "main(){x = \"2 3 5 7 11 17\";return(['7' ∈ x, '8' ∈ x]);}" ), "[true, false]" );
	ENSURE_EQUALS( "is_element_of enumeral failed", execute( "from FileSystem import *;main(){return([Stream.SEEK.BEGIN ∈ Stream.SEEK, OPEN_MODE.READ ∈ Stream.SEEK]);}" ), "[true, false]" );
	ENSURE_EQUALS( "missing is_element_of user succeeded", execute_except( "import Algorithms as algo;main(){return(0∈algo.reversed([]));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:42: There is no `∈' operator for a `ReversedListView'." );
	ENSURE_EQUALS( "missing is_element_of user succeeded", execute_except( "class A{_x=none;}main(){return(0∈A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:33: Class `A' does not have `contains' method." );
	ENSURE_EQUALS(
		"is_element_of on user defined (contains) failed",
		execute(
			"import Algorithms as algo;\n"
			"main()\n{"
			"x = (\n"
			"  3 ∈ algo.range( 5 ),\n"          // true
			"  3 ∈ algo.range( 2, 5 ),\n"       // true
			"  3 ∈ algo.range( 3, 5 ),\n"       // true
			"  3 ∈ algo.range( 4, 10 ),\n"      // false
			"  3 ∈ algo.range( 0, 4 ),\n"       // true
			"  3 ∈ algo.range( 0, 3 ),\n"       // false
			"  3 ∈ algo.range( 0, 10, 2 ),\n"   // false
			"  3 ∈ algo.range( 0, 10, 3 ),\n"   // true
			"  3 ∈ algo.range( 1, 10, 3 ),\n"   // false
			"  5 ∈ algo.range( 2, 10, 3 ),\n"   // true

			"  3 ∈ algo.range( 10, 0, -1),\n"   // true
			" 10 ∈ algo.range( 10, 0, -1),\n"   // true
			"  0 ∈ algo.range( 10, 0, -1),\n"   // false
			"  7 ∈ algo.range( 10, 0, -3),\n"   // true

			" -3 ∈ algo.range( -10, 0 ),\n"     // true
			" -3 ∈ algo.range( -10, 0, 3 ),\n"  // false
			" -4 ∈ algo.range( -10, 0, 3 ),\n"  // true

			" -3 ∈ algo.range( 0, -10, -1),\n"  // true
			" -4 ∈ algo.range( -2, -10, -3),\n" // false
			" -5 ∈ algo.range( -2, -10, -3)\n"  // true
			");\n"
			"return(x);\n"
			"}"
		),
		"(true, true, true, false, true, false, false, true, false, true, true, true, false, true, true, false, true, true, false, true)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_not_element_of" )
	ENSURE_EQUALS( "is_not_element_of tuple failed", execute( "main(){x = (2, 3, 5, 7, 11, 17 );return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of list failed", execute( "main(){x = [2, 3, 5, 7, 11, 17 ];return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of deque failed", execute( "main(){x = deque(2, 3, 5, 7, 11, 17 );return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of dict failed", execute( "main(){x = [2:1, 3:2, 5:3, 7:4, 11:5, 17:6];return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of lookup failed", execute( "main(){x = {2:1, 3:2, 5:3, 7:4, 11:5, 17:6};return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of order failed", execute( "main(){x = order(2, 3, 5, 7, 11, 17 );return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of set failed", execute( "main(){x = {2, 3, 5, 7, 11, 17 };return([7 ∉ x, 8 ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "is_not_element_of string failed", execute( "main(){x = \"2 3 5 7 11 17\";return(['7' ∉ x, '8' ∉ x]);}" ), "[false, true]" );
	ENSURE_EQUALS( "missing is_not_element_of user succeeded", execute_except( "import Algorithms as algo;main(){return(0∉algo.reversed([]));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:42: There is no `∉' operator for a `ReversedListView'." );
	ENSURE_EQUALS( "missing is_not_element_of user succeeded", execute_except( "class A{_x=none;}main(){return(0∉A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:33: Class `A' does not have `contains' method." );
TUT_TEARDOWN()

void tut_yaal_tools_hhuginn_instructions::test_subscript( HHuginn::TYPE type_, char const* index_, char const* result_ ) {
	hcore::HString src( "main(){x=" );
	switch ( type_ ) {
		case ( HHuginn::TYPE::STRING ): {
			src.append( "\"abcdefghijklmnopqrstuvwxyz\"" );
		} break;
		case ( HHuginn::TYPE::TUPLE ): {
			src.append( "('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')" );
		} break;
		case ( HHuginn::TYPE::LIST ): {
			src.append( "['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']" );
		} break;
		case ( HHuginn::TYPE::DEQUE ): {
			src.append( "deque('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')" );
		} break;
		default: {
			M_ASSERT( ! "bad path"[0] );
		}
	}
	src.append( ";return(string(x[" ).append( index_ ).append( "]));}" );
	ENSURE_EQUALS( "subscript failed", execute( src ), to_string( '"' ).append( result_ ).append( '"' ) );
	return;
}

TUT_UNIT_TEST( "subscript" )
	HHuginn::TYPE types[] = {
		HHuginn::TYPE::STRING,
		HHuginn::TYPE::TUPLE,
		HHuginn::TYPE::LIST,
		HHuginn::TYPE::DEQUE
	};
	for ( HHuginn::TYPE t : types ) {
		test_subscript( t, "0", "a" );
		test_subscript( t, "25", "z" );
		test_subscript( t, "-26", "a" );
		test_subscript( t, "-1", "z" );
		test_subscript( t, "13", "n" );
		test_subscript( t, "-13", "n" );
		test_subscript( t, "12", "m" );
		test_subscript( t, "-12", "o" );
	}
	ENSURE_EQUALS(
		"user subscript failed",
		execute(
			"class A{_x=[2,4,8]; subscript(idx_){_x[idx_];}}main(){a = A();return((a[0],a[1],a[2]));}"
		),
		"(2, 4, 8)"
	);
	ENSURE_EQUALS(
		"user subscript with invalid key succeeded",
		execute_except(
			"class A{_x=[2,4,8]; subscript(idx_){_x[idx_];}}main(){a = A();return(a[3]);}"
		),
		"*anonymous stream*:1:39: Bad index."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "member" )
	ENSURE_EQUALS(
		"user member failed",
		execute(
			"class A{_x=none;constructor(){_x = {\"a\":2,\"test\": \"value\",\"sum\":@(x,y){x+y;}};}member(name_){_x[name_];}}main(){a = A();return((a.a,a.test,a.sum(7,12)));}"
		),
		"(2, \"value\", 19)"
	);
	ENSURE_EQUALS(
		"user member with invalid name succeeded",
		execute_except(
			"class A{_x=none;constructor(){_x = {\"a\":2,\"test\": \"value\",\"sum\":@(x,y){x+y;}};}member(name_){_x[name_];}}main(){a = A();return(a.b);}"
		),
		"*anonymous stream*:1:96: Key does not exist in `lookup'."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript repeat" )
	ENSURE_EQUALS( "subscript repeat failed", execute( "main(){x=list(list(11,12,13),list(21,22,23),list(31,32,33));return(x[1][1]);}" ), "22" );
TUT_TEARDOWN()

void tut_yaal_tools_hhuginn_instructions::test_range( HHuginn::TYPE type_, char const* range_, char const* result_ ) {
	hcore::HString src;
	char const x[] = "('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')";
	if ( type_ == HHuginn::TYPE::TUPLE ) {
		src.append( "import Text as T;import Algorithms as A;main(){return(T.join(A.materialize(A.map(" ).append( x ).append( "[" ).append( range_ ).append( "],string),list),\"\"));}" );
	} else if ( type_ == HHuginn::TYPE::STRING ) {
		src.append( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[" ).append( range_ ).append( "]);}" );
	} else {
		src.append( "import Text as t;apply(x,T){i=0;s=size(x);while(i<s){x[i]=T(x[i]);i+=1;}return(x);}main(){return(t.join(apply(" )
			.append( type_ == HHuginn::TYPE::LIST ? "list" : "deque" )
			.append( x )
			.append( "[" )
			.append( range_ )
			.append( "],string),\"\"));}" );
	}
	ENSURE_EQUALS( "range failed", execute( src ), to_string( '"' ).append( result_ ).append( '"' ) );
	return;
}

TUT_UNIT_TEST( "range(slice)" )
	HHuginn::TYPE types[] = {
		HHuginn::TYPE::STRING,
		HHuginn::TYPE::TUPLE,
		HHuginn::TYPE::LIST,
		HHuginn::TYPE::DEQUE
	};
	for ( HHuginn::TYPE t : types ) {
		test_range( t, ":", "abcdefghijklmnopqrstuvwxyz" );
		test_range( t, ":0", "" );
		test_range( t, "5:5", "" );
		test_range( t, "5:4", "" );
		test_range( t, ":1", "a" );
		test_range( t, ":2", "ab" );
		test_range( t, ":24", "abcdefghijklmnopqrstuvwx" );
		test_range( t, ":25", "abcdefghijklmnopqrstuvwxy" );
		test_range( t, ":26", "abcdefghijklmnopqrstuvwxyz" );
		test_range( t, "0:", "abcdefghijklmnopqrstuvwxyz" );
		test_range( t, "1:", "bcdefghijklmnopqrstuvwxyz" );
		test_range( t, "2:", "cdefghijklmnopqrstuvwxyz" );
		test_range( t, "24:", "yz" );
		test_range( t, "25:", "z" );
		test_range( t, "26:", "" );
		test_range( t, "1:25", "bcdefghijklmnopqrstuvwxy" );
		test_range( t, "2:24", "cdefghijklmnopqrstuvwx" );
		test_range( t, "4:8", "efgh" );
		test_range( t, ":-1", "abcdefghijklmnopqrstuvwxy" );
		test_range( t, ":-10", "abcdefghijklmnop" );
		test_range( t, ":-100", "" );
		test_range( t, "-1:", "z" );
		test_range( t, "-10:", "qrstuvwxyz" );
		test_range( t, "-100:", "abcdefghijklmnopqrstuvwxyz" );
		test_range( t, "-8:-4", "stuv" );
		test_range( t, ":100", "abcdefghijklmnopqrstuvwxyz" );
		test_range( t, "::", "abcdefghijklmnopqrstuvwxyz" );
		test_range( t, "::2", "acegikmoqsuwy" );
		test_range( t, "::13", "an" );
		test_range( t, "::25", "az" );
		test_range( t, "::26", "a" );
		test_range( t, "::100", "a" );
		test_range( t, "5:5:-1", "" );
		test_range( t, "4:5:-1", "" );
		test_range( t, "::-1", "zyxwvutsrqponmlkjihgfedcba" );
		test_range( t, "::-2", "zxvtrpnljhfdb" );
		test_range( t, "::-3", "zwtqnkheb" );
		test_range( t, ":20:-1", "zyxwv" );
		test_range( t, "-15:-3:2", "lnprtv" );
		test_range( t, "-3:-15:-2", "xvtrpn" );
		test_range( t, "10:-28:-1", "kjihgfedcba" );
		test_range( t, "-4::-1", "wvutsrqponmlkjihgfedcba" );
		test_range( t, "-4::", "wxyz" );
	}
TUT_TEARDOWN()

}


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
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_instructions, "yaal::tools::HHuginn,instructions" );

TUT_UNIT_TEST( "add" )
	ENSURE_EQUALS( "add int const failed", execute( "main(){return(1+2);}" ), "3" );
	ENSURE_EQUALS( "add int var failed", execute( "main(){x = 1;y = 2;return(x+y);}" ), "3" );
	ENSURE_EQUALS( "add-assign int const failed", execute( "main(){x=1;x+=2;return(x);}" ), "3" );
	ENSURE_EQUALS( "add-assign int var failed", execute( "main(){x=1;y=2;x+=y;return(x);}" ), "3" );
	ENSURE_EQUALS( "add real const failed", execute( "main(){return(1.+2.);}" ), "3.0" );
	ENSURE_EQUALS( "add real var failed", execute( "main(){x=1.;y=2.;return(x+y);}" ), "3.0" );
	ENSURE_EQUALS( "add-assign real const failed", execute( "main(){x=1.;x+=2.;return(x);}" ), "3.0" );
	ENSURE_EQUALS( "add-assign real var failed", execute( "main(){x=1.;y=2.;x+=y;return(x);}" ), "3.0" );
	ENSURE_EQUALS( "add number const failed", execute( "main(){return($1+$2);}" ), "$3" );
	ENSURE_EQUALS( "add number var failed", execute( "main(){x=$1;y=$2;return(x+y);}" ), "$3" );
	ENSURE_EQUALS( "add string const failed", execute( "main(){return(\"1\"+\"2\");}" ), "\"12\"" );
	ENSURE_EQUALS( "add string var failed", execute( "main(){x=\"1\";y=\"2\";return(x+y);}" ), "\"12\"" );
	ENSURE_EQUALS( "add user succeeded", execute_except( "class A{_x=none;}main(){return(A()+A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `add` method." );
	ENSURE_EQUALS( "add char succeeded", execute_except( "main(){c=character;return(c('1')+c('2'));}" ), "*anonymous stream*:1:33: There is no `+` operator for a `character`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sub" )
	ENSURE_EQUALS( "sub int const failed", execute( "main(){return(7-3);}" ), "4" );
	ENSURE_EQUALS( "sub int var failed", execute( "main(){x=7;y=3;return(x-y);}" ), "4" );
	ENSURE_EQUALS( "sub-assign int const failed", execute( "main(){x=7;x-=3;return(x);}" ), "4" );
	ENSURE_EQUALS( "sub-assign int var failed", execute( "main(){x=7;y=3;x-=y;return(x);}" ), "4" );
	ENSURE_EQUALS( "sub real const failed", execute( "main(){return(7.-3.);}" ), "4.0" );
	ENSURE_EQUALS( "sub real var failed", execute( "main(){x=7.;y=3.;return(x-y);}" ), "4.0" );
	ENSURE_EQUALS( "sub-assign real const failed", execute( "main(){x=7.;x-=3.;return(x);}" ), "4.0" );
	ENSURE_EQUALS( "sub-assign real var failed", execute( "main(){x=7.;y=3.;x-=y;return(x);}" ), "4.0" );
	ENSURE_EQUALS( "sub number const failed", execute( "main(){return($7-$3);}" ), "$4" );
	ENSURE_EQUALS( "sub number var failed", execute( "main(){x=$7;y=$3;return(x-y);}" ), "$4" );
	ENSURE_EQUALS( "sub user succeeded", execute_except( "class A{_x=none;}main(){return(A()-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `subtract` method." );
	ENSURE_EQUALS( "sub char succeeded", execute_except( "main(){c=character;return(c('7')-c('3'));}" ), "*anonymous stream*:1:33: There is no `-` operator for a `character`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mul" )
	ENSURE_EQUALS( "mul int const failed", execute( "main(){return(2*3);}" ), "6" );
	ENSURE_EQUALS( "mul int var failed", execute( "main(){x=2;y=3;return(x*y);}" ), "6" );
	ENSURE_EQUALS( "mul-assign int const failed", execute( "main(){x=2;x*=3;return(x);}" ), "6" );
	ENSURE_EQUALS( "mul-assign int var failed", execute( "main(){x=2;y=3;x*=y;return(x);}" ), "6" );
	ENSURE_EQUALS( "mul real const failed", execute( "main(){return(2.*3.);}" ), "6.0" );
	ENSURE_EQUALS( "mul real var failed", execute( "main(){x=2.;y=3.;return(x*y);}" ), "6.0" );
	ENSURE_EQUALS( "mul-assign real const failed", execute( "main(){x=2.;x*=3.;return(x);}" ), "6.0" );
	ENSURE_EQUALS( "mul-assign real var failed", execute( "main(){x=2.;y=3.;x*=y;return(x);}" ), "6.0" );
	ENSURE_EQUALS( "mul number const failed", execute( "main(){return($2*$3);}" ), "$6" );
	ENSURE_EQUALS( "mul number var failed", execute( "main(){x=$2;y=$3;return(x*y);}" ), "$6" );
	ENSURE_EQUALS( "mul user succeeded", execute_except( "class A{_x=none;}main(){return(A()*A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `multiply` method." );
	ENSURE_EQUALS( "mul char succeeded", execute_except( "main(){c=character;return(c('2')*c('3'));}" ), "*anonymous stream*:1:33: There is no `*` operator for a `character`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "div" )
	ENSURE_EQUALS( "div int const failed", execute( "main(){return(7/2);}" ), "3" );
	ENSURE_EQUALS( "div int var failed", execute( "main(){x=7;y=2;return(x/y);}" ), "3" );
	ENSURE_EQUALS( "div-assign int const failed", execute( "main(){x=7;x/=2;return(x);}" ), "3" );
	ENSURE_EQUALS( "div-assign int var failed", execute( "main(){x=7;y=2;x/=y;return(x);}" ), "3" );
	ENSURE_EQUALS( "div real const failed", execute( "main(){return(7./2.);}" ), "3.5" );
	ENSURE_EQUALS( "div real var failed", execute( "main(){x=7.;y=2.;return(x/y);}" ), "3.5" );
	ENSURE_EQUALS( "div-assign real const failed", execute( "main(){x=7.;x/=2.;return(x);}" ), "3.5" );
	ENSURE_EQUALS( "div-assign real var failed", execute( "main(){x=7.;y=2.;x/=y;return(x);}" ), "3.5" );
	ENSURE_EQUALS( "div number const failed", execute( "main(){return($7/$2);}" ), "$3.5" );
	ENSURE_EQUALS( "div number var failed", execute( "main(){x=$7;y=$2;return(x/y);}" ), "$3.5" );
	ENSURE_EQUALS( "div user succeeded", execute_except( "class A{_x=none;}main(){return(A()/A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `divide` method." );
	ENSURE_EQUALS( "div char succeeded", execute_except( "main(){c=character;return(c('7')/c('2'));}" ), "*anonymous stream*:1:33: There is no `/` operator for a `character`." );
	ENSURE_EQUALS( "div 0 int succeeded", execute_except( "main(){x = 1;return(x/0);}" ), "*anonymous stream*:1:22: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "div min_int/-1 int succeeded", execute_except( "main(){x = -1;return(-9223372036854775808/x);}" ), "*anonymous stream*:1:42: Uncaught ArithmeticException: Division overflow." );
	ENSURE_EQUALS( "div 0 real succeeded", execute_except( "main(){x = 1.;return(x/0.);}" ), "*anonymous stream*:1:23: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "div 0 num succeeded", execute_except( "main(){x=$1;return(x/$0);}" ), "*anonymous stream*:1:21: Uncaught ArithmeticException: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod" )
	ENSURE_EQUALS( "mod int const failed", execute( "main(){return(11%3);}" ), "2" );
	ENSURE_EQUALS( "mod int var failed", execute( "main(){x=11;y=3;return(x%y);}" ), "2" );
	ENSURE_EQUALS( "mod-assign int const failed", execute( "main(){x=11;x%=3;return(x);}" ), "2" );
	ENSURE_EQUALS( "mod-assign int var failed", execute( "main(){x=11;y=3;x%=y;return(x);}" ), "2" );
	ENSURE_EQUALS( "mod real const failed", execute( "main(){return(11.%3.);}" ), "2.0" );
	ENSURE_EQUALS( "mod real var failed", execute( "main(){x=11.;y=3.;return(x%y);}" ), "2.0" );
	ENSURE_EQUALS( "mod-assign real const failed", execute( "main(){x=11.;x%=3.;return(x);}" ), "2.0" );
	ENSURE_EQUALS( "mod-assign real var failed", execute( "main(){x=11.;y=3.;x%=y;return(x);}" ), "2.0" );
	ENSURE_EQUALS( "mod number const failed", execute( "main(){return($11%$3);}" ), "$2" );
	ENSURE_EQUALS( "mod number var failed", execute( "main(){x=$11;y=$3;return(x%y);}" ), "$2" );
	ENSURE_EQUALS( "mod user succeeded", execute_except( "class A{_x=none;}main(){return(A()%A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `modulo` method." );
	ENSURE_EQUALS( "mod char succeeded", execute_except( "main(){c=character;return(c('8')%c('3'));}" ), "*anonymous stream*:1:33: There is no `%` operator for a `character`." );
	ENSURE_EQUALS( "mod 0 int succeeded", execute_except( "main(){x=1;return(x%0);}" ), "*anonymous stream*:1:20: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "mod min_int%-1 int succeeded", execute_except( "main(){x=-1;return(-9223372036854775808%x);}" ), "*anonymous stream*:1:40: Uncaught ArithmeticException: Division overflow." );
	ENSURE_EQUALS( "mod 0 real succeeded", execute_except( "main(){x=1.;return(x%0.);}" ), "*anonymous stream*:1:21: Uncaught ArithmeticException: Division by zero." );
	ENSURE_EQUALS( "mod 0 num succeeded", execute_except( "main(){x=$1;return(x%$0);}" ), "*anonymous stream*:1:21: Uncaught ArithmeticException: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "pow" )
	ENSURE_EQUALS( "pow real const failed", execute( "main(){return(2.^3.);}" ), "8.0" );
	ENSURE_EQUALS( "pow real var failed", execute( "main(){x=2.;y=3.;return(x^y);}" ), "8.0" );
	ENSURE_EQUALS( "pow number const failed", execute( "main(){return($2^$3);}" ), "$8" );
	ENSURE_EQUALS( "pow number var failed", execute( "main(){x=$2;y=$3;return(x^y);}" ), "$8" );
	ENSURE_EQUALS( "pow-assign number failed", execute( "main(){x=$2;x^=$3;return(x);}" ), "$8" );
	ENSURE_EQUALS( "pow user succeeded", execute_except( "class A{_x=none;}main(){return(A()^A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `power` method." );
	ENSURE_EQUALS( "pow char succeeded", execute_except( "main(){c=character;return(c('2')^c('3'));}" ), "*anonymous stream*:1:33: There is no `^` operator for a `character`." );
	ENSURE_EQUALS( "too big exponent succeeded", execute_except( "main(){x=$2;x^=x;x^=x;x^=x;x^=x;}" ), "*anonymous stream*:1:29: Uncaught ArithmeticException: Exponent too big: 32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389437335543602135433229604645318478604952148193555853611059596230656" );
	ENSURE_EQUALS( "pow 0^0 real succeeded", execute_except( "main(){x=0.;return(x^0.);}" ), "*anonymous stream*:1:21: Uncaught ArithmeticException: indeterminate form 0^0" );
	ENSURE_EQUALS( "pow 0^0 number succeeded", execute_except( "main(){x=$0;return(x^$0);}" ), "*anonymous stream*:1:21: Uncaught ArithmeticException: indeterminate form 0^0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "factorial" )
	ENSURE_EQUALS( "factorial const", execute( "main(){$6!;}" ), "$720" );
	ENSURE_EQUALS( "factorial var", execute( "main(){x = $6;x!;}" ), "$720" );
	ENSURE_EQUALS( "neg factorial succeeded", execute_except( "main(){x=$-1;return(x!);}" ), "*anonymous stream*:1:22: Uncaught ArithmeticException: Factorial from negative." );
	ENSURE_EQUALS( "fractional factorial succeeded", execute_except( "main(){x=$1.5;return(x!);}" ), "*anonymous stream*:1:23: Uncaught ArithmeticException: Factorial from fraction." );
	ENSURE_EQUALS( "int factorial succeeded", execute_except( "main(){x=[1];return(x[0]!);}" ), "*anonymous stream*:1:25: There is no `!` operator for an `integer`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "absolute" )
	ENSURE_EQUALS( "abs int const failed", execute( "main(){return([|1|,|-1|]);}" ), "[1, 1]" );
	ENSURE_EQUALS( "abs int var failed", execute( "main(){x=1;y=-1;return([|x|,|y|]);}" ), "[1, 1]" );
	ENSURE_EQUALS( "abs min_int succeeded", execute_except( "main(){x=-9223372036854775808;return(|x|);}" ), "*anonymous stream*:1:40: Uncaught ArithmeticException: Integer overflow." );
	ENSURE_EQUALS( "abs real const failed", execute( "main(){return([|1.|,|-1.|]);}" ), "[1.0, 1.0]" );
	ENSURE_EQUALS( "abs real var failed", execute( "main(){x=1.;y=-1.;return([|x|,|y|]);}" ), "[1.0, 1.0]" );
	ENSURE_EQUALS( "abs num const failed", execute( "main(){return([|$1|,|$-1|]);}" ), "[$1, $1]" );
	ENSURE_EQUALS( "abs num var failed", execute( "main(){x=$1;y=$-1;return([|x|,|y|]);}" ), "[$1, $1]" );
	ENSURE_EQUALS( "abs char succeeded", execute_except( "main(){c=character;return(|c('1')|);}" ), "*anonymous stream*:1:34: There is no `|...|` operator for a `character`." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "neg" )
	ENSURE_EQUALS( "neg int const, real const, number const failed", execute( "main(){return([-1,-1.,-$1]);}" ), "[-1, -1.0, $-1]" );
	ENSURE_EQUALS( "neg int var, real var, number var failed", execute( "main(){x=1;y=1.;z=$1;return([-x,-y,-z]);}" ), "[-1, -1.0, $-1]" );
	ENSURE_EQUALS( "neg user succeeded", execute_except( "class A{_x=none;}main(){return(-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:32: Class `A` does not have `negate` method." );
	ENSURE_EQUALS( "neg char succeeded", execute_except( "main(){c=character;return(-c('1'));}" ), "*anonymous stream*:1:27: There is no `-x` operator for a `character`." );
	ENSURE_EQUALS( "neg min_int succeeded", execute_except( "main(){x=8;return(-(-9223372036854775800-x));}" ), "*anonymous stream*:1:19: Uncaught ArithmeticException: Integer overflow." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equals" )
	ENSURE_EQUALS( "equals none failed", execute( "n(){}main(){return([n()==n(),n()==0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals int failed", execute( "main(){return([1==1,1==0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals real failed", execute( "main(){return([1.==1.,1.==0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals number failed", execute( "main(){return([$1==$1,$1==$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals character failed", execute( "main(){return(['1'=='1','1'=='0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals string failed", execute( "main(){return([\"1\"==\"1\",\"1\"==\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "user failed", execute( "class A{_x=none;constructor(x){_x=x;}equals(x){return(_x==x._x);}}main(){return([A(1)==A(1),A(1)==A(0)]);}", HHuginn::COMPILER::BE_SLOPPY ), "[true, false]" );
	ENSURE_EQUALS( "bad equals user succeeded", execute_except( "class A{equals(x){return(none);}}main(){return(A()==A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:51: Comparison method `equals` returned non-boolean result of a `*none*` type." );
	ENSURE_EQUALS( "missing equals user succeeded", execute_except( "class A{_x=none;}main(){return(A()==A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `equals` method." );
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
	ENSURE_EQUALS( "bad less user succeeded", execute_except( "class A{less(x){return(none);}}main(){return(A()<A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:49: Comparison method `less` returned non-boolean result of a `*none*` type." );
	ENSURE_EQUALS( "missing less user succeeded", execute_except( "class A{_x=none;}main(){return(A()<A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `less` method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greater" )
	ENSURE_EQUALS( "greater int failed", execute( "main(){return([1>0,0>0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater real failed", execute( "main(){return([1.>0.,0.>0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater number failed", execute( "main(){return([$1>$0,$0>$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater character failed", execute( "main(){return(['1'>'0','0'>'0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater string failed", execute( "main(){return([\"1\">\"0\",\"0\">\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "bad greater user succeeded", execute_except( "class A{greater(x){return(none);}}main(){return(A()>A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:52: Comparison method `greater` returned non-boolean result of a `*none*` type." );
	ENSURE_EQUALS( "missing greater user succeeded", execute_except( "class A{_x=none;}main(){return(A()>A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `greater` method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "less_or_equal" )
	ENSURE_EQUALS( "less_or_equal int failed", execute( "main(){return([0<=1,0<=0,1<=0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal real failed", execute( "main(){return([0.<=1.,0.<=0.,1<=0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal number failed", execute( "main(){return([$0<=$1,$0<=$0,$1<=$0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal character failed", execute( "main(){return(['0'<='1','0'<='0','1'<='0']);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal string failed", execute( "main(){return([\"0\"<=\"1\",\"0\"<=\"0\",\"1\"<=\"0\"]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "bad less_or_equal user succeeded", execute_except( "class A{less_or_equal(x){return(none);}}main(){return(A()<=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:58: Comparison method `less_or_equal` returned non-boolean result of a `*none*` type." );
	ENSURE_EQUALS( "missing less_or_equal user succeeded", execute_except( "class A{_x=none;}main(){return(A()<=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `less_or_equal` method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greater_or_equal" )
	ENSURE_EQUALS( "greater_or_equal int failed", execute( "main(){return([1>=0,0>=0,0>=1]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal real failed", execute( "main(){return([1.>=0.,0.>=0.,0.>=1.]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal number failed", execute( "main(){return([$1>=$0,$0>=$0,$0>=$1]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal character failed", execute( "main(){return(['1'>='0','0'>='0','0'>='1']);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal string failed", execute( "main(){return([\"1\">=\"0\",\"0\">=\"0\",\"0\">=\"1\"]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "bad greater_or_equal user succeeded", execute_except( "class A{greater_or_equal(x){return(none);}}main(){return(A()>=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:61: Comparison method `greater_or_equal` returned non-boolean result of a `*none*` type." );
	ENSURE_EQUALS( "missing greater_or_equal user succeeded", execute_except( "class A{_x=none;}main(){return(A()>=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A` does not have `greater_or_equal` method." );
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
	ENSURE_EQUALS( "missing is_element_of user succeeded", execute_except( "import Algorithms as algo;main(){return(0∈algo.reversed([]));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:42: There is no `∈` operator for a `ReversedListView`." );
	ENSURE_EQUALS( "missing is_element_of user succeeded", execute_except( "class A{_x=none;}main(){return(0∈A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:33: Class `A` does not have `contains` method." );
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
	ENSURE_EQUALS( "missing is_not_element_of user succeeded", execute_except( "import Algorithms as algo;main(){return(0∉algo.reversed([]));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:42: There is no `∈` operator for a `ReversedListView`." );
	ENSURE_EQUALS( "missing is_not_element_of user succeeded", execute_except( "class A{_x=none;}main(){return(0∉A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:33: Class `A` does not have `contains` method." );
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
	ENSURE_EQUALS(
		"user subscript assign failed",
		execute(
			"class A{_x=[2,4,8]; set_subscript(idx_, val_){_x[idx_]=val_;} subscript(idx_){_x[idx_];}}main(){a = A();a[1]=7;return((a[0],a[1],a[2]));}"
		),
		"(2, 7, 8)"
	);
	ENSURE_EQUALS(
		"user subscript assign with invalid key succeeded",
		execute_except(
			"class A{\n"
			"_x=[2,4,8];\n"
			"set_subscript(idx_, val_){\n"
			"_x[idx_]=val_;\n"
			"}\n"
			"subscript(idx_){_x[idx_];}\n"
			"}\n"
			"main(){\n"
			"a = A();\n"
			"return(a[3] = 0);\n"
			"}"
		),
		"*anonymous stream*:4:3: Bad index."
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
		"*anonymous stream*:1:96: Key does not exist in `lookup`."
	);
	ENSURE_EQUALS(
		"user set_member failed",
		execute(
			"class A{_x={};member(name_){_x[name_];}set_member(name_, val_){_x[name_] = val_;}}main(){a = A();a.z=7;a.q=\"ff\";a.z+=4;return((a.q,a.z));}"
		),
		"(\"ff\", 11)"
	);
	ENSURE_EQUALS(
		"user set_member with invalid name succeeded",
		execute_except(
			"class A{\n"
			"_x={};\n"
			"member(name_){\n"
			"_x[name_];\n"
			"}\n"
			"set_member(name_, val_){\n"
			"val_;\n"
			"throw Exception(\"forbidden member: \" + name_);\n"
			"}\n"
			"}\n"
			"main(){\n"
			"a = A();\n"
			"a.QQQ = 11;\n"
			"}"
		),
		"*anonymous stream*:8:1: Uncaught Exception: forbidden member: QQQ"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript repeat" )
	ENSURE_EQUALS( "subscript repeat failed", execute( "main(){x=list(list(11,12,13),list(21,22,23),list(31,32,33));return(x[1][1]);}" ), "22" );
TUT_TEARDOWN()

}


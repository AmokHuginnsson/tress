/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hhuginn.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hstringstream.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn : public tress::tut_yaal_tools_hhuginn_base {
	void test_subscript( HHuginn::TYPE, char const*, char const* );
	void test_range( HHuginn::TYPE, char const*, char const* );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn", 80 );

TUT_UNIT_TEST( "grammar test" )
	HHuginn h;
	HRule hg( h.make_engine() );
	HGrammarDescription gd( hg );

#define IDENTIFIER "[a-zA-Z\\x{0391}-\\x{03c9}_][a-zA-Z\\x{0391}-\\x{03c9}0-9_]*"

	char const expected[][460] = {
		"huginnGrammar = +( classDefinition | functionDefinition | importStatement )",
		"classDefinition = ( \"class\" >> classIdentifier >> -( ':' >> baseIdentifier ) >> '{' >> +( field | functionDefinition ) >> '}' )",
		"functionDefinition = ( functionDefinitionIdentifier >> '(' >> -nameList >> ')' >> '{' >> *statement >> '}' )",
		"importStatement = ( \"import\" >> packageName >> \"as\" >> importName >> ';' )",
		"classIdentifier = regex( \"" IDENTIFIER "\" )",
		"baseIdentifier = regex( \"" IDENTIFIER "\" )",
		"field = ( fieldIdentifier >> '=' >> expression >> ';' )",
		"functionDefinitionIdentifier = regex( \"" IDENTIFIER "\" )",
		"nameList = ( parameter >> *( ',' >> parameter ) )",
		"statement = ( ifStatement | whileStatement | forStatement | switchStatement | tryCatchStatement | throwStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope )",
		"packageName = regex( \"" IDENTIFIER "\" )",
		"importName = regex( \"" IDENTIFIER "\" )",
		"fieldIdentifier = regex( \"" IDENTIFIER "\" )",
		"expression = ( *( ( assignable >> ( \"=\" | \"+=\" | \"-=\" | \"*=\" | \"/=\" | \"%=\" | \"^=\" ) ) ^ '=' ) >> value )",
		"parameter = ( parameterIdentifier >> -( '=' >> expression ) )",
		"ifStatement = ( ifClause >> *( \"else\" >> ifClause ) >> -( \"else\" >> scope ) )",
		"whileStatement = ( \"while\" >> '(' >> expression >> ')' >> scope )",
		"forStatement = ( \"for\" >> '(' >> assignable >> ':' >> expression >> ')' >> scope )",
		"switchStatement = ( \"switch\" >> '(' >> expression >> ')' >> '{' >> +caseStatement >> -defaultStatement >> '}' )",
		"tryCatchStatement = ( \"try\" >> scope >> +catchStatement )",
		"throwStatement = ( \"throw\" >> expression >> ';' )",
		"breakStatement = ( \"break\" >> ';' )",
		"continueStatement = ( \"continue\" >> ';' )",
		"returnStatement = ( \"return\" >> -( '(' >> expression >> ')' ) >> ';' )",
		"expressionStatement = ( expression >> ';' )",
		"scope = ( '{' >> *statement >> '}' )",
		"assignable = ( subscript | variableSetter )",
		"value = ternary",
		"parameterIdentifier = regex( \"" IDENTIFIER "\" )",
		"ifClause = ( \"if\" >> '(' >> expression >> ')' >> scope )",
		"caseStatement = ( \"case\" >> '(' >> expression >> ')' >> ':' >> scope >> -breakStatement )",
		"defaultStatement = ( \"default\" >> ':' >> scope )",
		"catchStatement = ( \"catch\" >> '(' >> exceptionType >> assignable >> ')' >> scope )",
		"subscript = ( reference >> +( subscriptOperator | functionCallOperator | memberAccess ) )",
		"variableSetter = regex( \"" IDENTIFIER "\" )",
		"ternary = ( ( booleanOr >> -( \"^^\" >> booleanOr ) ) >> -( '?' >> expression >> ':' >> expression ) )",
		"exceptionType = regex( \"" IDENTIFIER "\" )",
		"reference = regex( \"" IDENTIFIER "\" )",
		"subscriptOperator = ( '[' >> ( ( ( rangeOper >> -argument ) | ( argument >> -( rangeOper >> -argument ) ) ) >> -( rangeOper >> -argument ) ) >> ']' )",
		"functionCallOperator = ( '(' >> -argList >> ')' )",
		"memberAccess = ( '.' >> member )",
		"booleanOr = ( booleanAnd >> *( \"||\" >> booleanAnd ) )",
		"rangeOper = ':'",
		"argument = expression",
		"argList = ( argument >> *( ',' >> argument ) )",
		"member = regex( \"" IDENTIFIER "\" )",
		"booleanAnd = ( equality >> *( \"&&\" >> equality ) )",
		"equality = ( compare >> -( ( \"==\" | \"!=\" ) >> compare ) )",
		"compare = ( sum >> -( ( \"<=\" | \">=\" | \"<\" | \">\" ) >> sum ) )",
		"sum = ( multiplication >> *( '+-' >> multiplication ) )",
		"multiplication = ( negation >> *( '*/%' >> negation ) )",
		"negation = ( ( '-' >> negation ) | power )",
		"power = ( booleanNot >> *( '^' >> negation ) )",
		"booleanNot = ( ( '!' >> factorial ) | factorial )",
		"factorial = ( atom >> -( ( '!' & \"==\" ) | ( '!' ^ '=' ) ) )",
		"atom = ( absoluteValue | ( parenthesis >> -( memberAccess >> dereference ) ) | real | integer | ( ( numberLiteral | character_literal ) >> -( memberAccess >> functionCallOperator ) ) | ( ( listLiteral | dictLiteral | stringLiteral ) >> -( ( subscriptOperator | memberAccess ) >> dereference ) ) | ( setLiteral >> -( memberAccess >> dereference ) ) | none | true | false | ( reference >> dereference ) | ( lambda >> -( functionCallOperator >> dereference ) ) )",
		"absoluteValue = ( '|' >> expression >> '|' )",
		"parenthesis = ( '(' >> expression >> ')' )",
		"dereference = *( subscriptOperator | functionCallOperator | memberAccess )",
		"numberLiteral = ( '$' >> real )",
		"listLiteral = ( '[' >> -argList >> ']' )",
		"dictLiteral = ( '{' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> '}' )",
		"stringLiteral = string_literal",
		"setLiteral = ( '{' >> argument >> *( ',' >> argument ) >> '}' )",
		"none = \"none\"",
		"true = \"true\"",
		"false = \"false\"",
		"lambda = ( ( '@' >> -( '[' >> captureList >> ']' ) ) >> '(' >> -nameList >> ')' >> '{' >> *statement >> '}' )",
		"dictLiteralElement = ( argument >> ':' >> argument )",
		"captureList = ( capture >> *( ',' >> capture ) )",
		"capture = regex( \"" IDENTIFIER "\" )"
	};

	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		cout << *it << endl;
		ENSURE( "too many rules in Huginn grammar", i < countof ( expected ) );
		ENSURE_EQUALS( "bad rule in Huginn grammar", *it, expected[i] );
	}
	ENSURE_EQUALS( "not all rules found for Huginn grammar", i, countof ( expected ) );
TUT_TEARDOWN()

char const simpleProg[] =
	"/*\n"
	" * Sample code in huginn.\n"
	" */\n"
	"\n"
	"sum( a, b ) {\n"
	"\treturn ( a + b );\n"
	"}\n"
	"\n"
	"main( args ) {\n"
	"\ta = integer( args[0] );\n"
	"\tb = integer( args[1] );\n"
	"\treturn ( sum( 3 + a, sum( 4, ( b + 1 ) * 2 ) ) );\n"
	"}\n"
	"\n"
;

TUT_UNIT_TEST( "program return types and values" )
	/* none */ {
		OHuginnResult hr( execute_result( "main(){return(none);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::NONE );
	}
	/* integer */ {
		OHuginnResult hr( execute_result( "main(){return(0);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::INTEGER );
		ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( hr._result.raw() )->value(), 0 );
	}
	/* real */ {
		OHuginnResult hr( execute_result( "main(){return(3.14);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::REAL );
		ENSURE_DISTANCE( "bad value returned", static_cast<HHuginn::HReal*>( hr._result.raw() )->value(), 3.14L, epsilon );
	}
	/* string */ {
		OHuginnResult hr( execute_result( "main(){return(\"hello world\");}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::STRING );
		ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HString*>( hr._result.raw() )->value(), "hello world" );
	}
	/* character */ {
		OHuginnResult hr( execute_result( "main(){return('X');}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::CHARACTER );
		ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HCharacter*>( hr._result.raw() )->value(), code_point_t( 'X' ) );
	}
	/* number */ {
		OHuginnResult hr( execute_result( "main(){return($7);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::NUMBER );
		ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HNumber*>( hr._result.raw() )->value(), 7_yn );
	}
	/* boolean */ {
		OHuginnResult hr( execute_result( "main(){return(true);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::BOOLEAN );
		ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HBoolean*>( hr._result.raw() )->value(), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "set variable" )
	OHuginnResult hr( execute_result( "main(){a=7;return(a);}" ) );
	ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( hr._result.raw() )->value(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "functions (definition)" )
	ENSURE_EQUALS( "function result failed", execute( "f(){return(7);}main(){return(f());}" ), 7 );
	ENSURE_EQUALS(
		"dafult arguments failed",
		execute(
			"f(a1=-1,a2=-2,a3=-3,a4=-4){\n"
			"return([a1,a2,a3,a4]);\n"
			"}\n"
			"main(){\n"
			"return(f(1,2));\n"
			"}\n"
		),
		"[1, 2, -3, -4]"
	);
	ENSURE_EQUALS(
		"lambda as default argument failed",
		execute(
			"f(x,l=@(y){y;}){l(x);}\n"
			"main(){\n"
			"return([f(1),f(3),f(1,@(x){x*7;}),f(3,@(x){x*13;})]);"
			"}\n"
		),
		"[1, 3, 7, 39]"
	);
TUT_TEARDOWN()

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
	ENSURE_EQUALS( "abs char succeeded", execute_except( "main(){c=character;return(|c('1')|);}" ), "*anonymous stream*:1:34: There is no |.| operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "neg" )
	ENSURE_EQUALS( "neg user succeeded", execute_except( "class A{_x=none;}main(){return(-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:32: Class `A' does not have `negate' method." );
	ENSURE_EQUALS( "neg char succeeded", execute_except( "main(){c=character;return(-c('1'));}" ), "*anonymous stream*:1:27: There is no `negate` operator for `character'." );
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

TUT_UNIT_TEST( "if" )
	ENSURE_EQUALS( "if (true) failed", execute( "main(){x=2;if(x>0){x=x*x;}return(x);}" ), "4" );
	ENSURE_EQUALS( "if (false) failed", execute( "main(){x=2;if(x>2){x=x*x;}return(x);}" ), "2" );
	ENSURE_EQUALS(
		"if else if else chain failed",
		execute(
			"foo(b,v) {\n"
			"if(b) {\n"
			"v+=\"foo\";\n"
			"} else {\n"
			"throw Exception(\"ex\");\n"
			"}\n"
			"}\n"
			"main(){\n"
			"r=\"\";\n"
			"try{\n"
			"v=0;\n"
			"if(v>0){\n"
			"r+=\"bad\";\n"
			"} else if(foo(false, v) > 0){\n"
			"r+=\"bad2\";\n"
			"} else if(foo(true, v) > 0){\n"
			"r+=\"bad3\";\n"
			"} else {\n"
			"r+=\"bad4\";\n"
			"}\n"
			"}catch(Exception e){\n"
			"r+=e.what();"
			"}\n"
			"return(r);\n"
			"}\n"
		),
		"\"ex\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "while" )
	ENSURE_EQUALS( "while failed", execute( "main(){x=2;while(x<100){x=x*x;}return(x);}" ), "256" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "for" )
	ENSURE_EQUALS( "for failed", execute( "main(){x=list(1,2,3);s=0;for(e:x){s=s+e;}return(s);}" ), "6" );
	ENSURE_EQUALS( "for(expr:) failed", execute( "main(){x=list(1,2,3);s=0;l=[0];for(l[0]:x){s=s+l[0];}return(string(s)+string(l[0]));}" ), "\"63\"" );
	ENSURE_EQUALS(
		"for(user-def) failed",
		execute(
			"class LN {"
			"_data = none;"
			"_next = none;"
			"constructor( data_, next_ ) {"
			"_data = data_;"
			"_next = next_;"
			"}"
			"}"
			"class LI {"
			"_cur = none;"
			"constructor( cur_ ) {"
			"_cur = cur_;"
			"}"
			"is_valid() {"
			"return ( _cur != none );"
			"}"
			"value() {"
			"return ( _cur._data );"
			"}"
			"next() {"
			"_cur = _cur._next;"
			"}"
			"}"
			"class L {"
			"_head = none;"
			"add( data_ ) {"
			"_head = LN( data_, _head );"
			"return(this);"
			"}"
			"iterator() {"
			"return ( LI( _head ) );"
			"}"
			"}"
			"main() {"
			"s=\"\";"
			"l=L();"
			"l.add(\"one\").add(\"two\").add(\"three\");"
			"for ( e : l ) {"
			"s+=e;"
			"s+=\"+\";"
			"}"
			"return(s);"
			"}"
		),
		"\"three+two+one+\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "switch" )
	ENSURE_EQUALS( "switch (no match, no default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}}return(x);}" ), "\"x\"" );
	ENSURE_EQUALS( "switch (no match, with default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}default:{x=\"y\";}}return(x);}" ), "\"y\"" );
	ENSURE_EQUALS( "switch (match, fallthrough, no default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}case(1):{x=x+\"y\";}case(2):{x=x+\"z\";}}return(x);}" ), "\"xyz\"" );
	ENSURE_EQUALS(
		"switch (match, fallthrough, default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}case(1):{x=x+\"y\";}case(2):{x=x+\"z\";}default:{x=x+\"!\";}}return(x);}" ),
		"\"xyz!\""
	);
	ENSURE_EQUALS(
		"switch (match, no fallthrough, no default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}break;case(1):{x=x+\"y\";}break;case(2):{x=x+\"z\";}break;}return(x);}" ),
		"\"xy\""
	);
	ENSURE_EQUALS(
		"switch (match, no fallthrough, default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}break;case(1):{x=x+\"y\";}break;case(2):{x=x+\"z\";}break;default:{x=x+\"!\";}}return(x);}" ),
		"\"xy\""
	);
	ENSURE_EQUALS(
		"switch, case expression failed",
		execute(
			"foo(b,v) {\n"
			"if(b) {\n"
			"v+=\"foo\";\n"
			"} else {\n"
			"throw Exception(\"ex\");\n"
			"}\n"
			"}\n"
			"main(){\n"
			"r=\"\";\n"
			"try{\n"
			"v=0;\n"
			"switch(v){\n"
			"case(7):{\n"
			"r+=\"bad\";\n"
			"}break;\n"
			"case(foo(false, v)):{\n"
			"r+=\"bad2\";\n"
			"}break;\n"
			"case(foo(true, v)):{\n"
			"r+=\"bad3\";\n"
			"} break;\n"
			"default: {\n"
			"r+=\"bad4\";\n"
			"}\n"
			"}\n"
			"}catch(Exception e){\n"
			"r+=e.what();"
			"}\n"
			"return(r);\n"
			"}\n"
		),
		"\"ex\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "break;" )
	ENSURE_EQUALS( "break; failed (while)", execute( "main(){x=0;y=0;while(y<100){y=y+1;if(x>100){break;}x=x+y*y;}return(x);}" ), "140" );
	ENSURE_EQUALS( "break; failed (for)", execute( "main(){x=[\"A\",\"a\",\"B\",\"b\",\"C\",\"c\"];v=\"\";for(e:x){if(size(v)>2){break;}v=v+e;}return(v);}" ), "\"AaB\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "continue;" )
	ENSURE_EQUALS(
		"continue; failed (while)",
		execute(
			"main(){\n"
			"x=\"ALAMAKOTA\";\n"
			"y=\"alamakota\";\n"
			"i=0;\n"
			"c=size(x);\n"
			"z=\"\";\n"
			"while(i<c){\n"
			"idx=i;\n"
			"i=i+1;\n"
			"z=z+string(x[idx]);\n"
			"if(i>(c/2)){continue;}\n"
			"z=z+string(y[idx]);\n"
			"}\n"
			"return(z);}"
		),
		"\"AaLlAaMmAKOTA\""
	);
	ENSURE_EQUALS(
		"continue; failed (for)",
		execute(
			"main(){\n"
			"i=0;\n"
			"x=\"Ala ma kota.\";\n"
			"z=\"\";\n"
			"for(e:x){\n"
			"z=z+string(e);\n"
			"if(i>4){continue;}\n"
			"z=z+\"+\";\n"
			"i=i+1;\n"
			"}\n"
			"return(z);}"
		),
		"\"A+l+a+ +m+a kota.\""
	);
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
	ENSURE_EQUALS( "string.format() on too few args succeeded", execute_except( "main(){s=\"a {} b\";s.format();}" ), "*anonymous stream*:1:27: Wrong value index at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a b\";s.format(1);}" ), "*anonymous stream*:1:24: Not all values used in format at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a {\";s.format();}" ), "*anonymous stream*:1:24: Single '{' encountered in format string at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a { b\";s.format();}" ), "*anonymous stream*:1:26: Invalid format specification at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a } b\";s.format();}" ), "*anonymous stream*:1:26: Single '}' encountered in format string at: 3" );
	ENSURE_EQUALS( "string.format() on too many args succeeded", execute_except( "main(){s=\"a {} {{}} {0} b\";s.format(0, 0);}" ), "*anonymous stream*:1:36: Cannot mix manual and automatic field numbering at: 12" );
	ENSURE_EQUALS( "string.format() on too few args succeeded", execute_except( "main(){s=\"a {9999999999999999999} b\";s.format();}" ), "*anonymous stream*:1:46: Out of range value in conversion: 9999999999999999999" );
	ENSURE_EQUALS( "string.format() on too few args succeeded", execute_except( "main(){s=\"a {99999999999999999} b\";s.format();}" ), "*anonymous stream*:1:44: Cast would lose data." );
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

TUT_UNIT_TEST( "exceptions()" )
	ENSURE_EQUALS(
		"exception failed",
		execute(
			"main(){\n"
			"r=none;\n"
			"try{\n"
			"1/0;\n"
			"}catch(ArithmeticException e) {\n"
			"r=[e.message(),e.where(),e.what()];\n"
			"}\n"
			"return(r);\n"
			"}\n" ),
		"[\"*anonymous stream*:4:2: Division by zero.\", \"*anonymous stream*:4:2\", \"Division by zero.\"]"
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
		execute( "main(){x=[2,3,5,7];x.append([4,8,16]).append(deque(20)).append(order(30)).append({40});return(x);}" ),
		"[2, 3, 5, 7, 4, 8, 16, 20, 30, 40]"
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
		"list pop failed",
		execute( "main(){x=list(2,3,5,7);x.pop();return(x);}" ),
		"[2, 3, 5]"
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
		"list() iterator failed",
		execute( "main(){x=[2,3,5,7];v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"list copy failed",
		execute( "main(){x=list(2,3,5);y=copy(x);x.push(7);return([x,y]);}" ),
		"[[2, 3, 5, 7], [2, 3, 5]]"
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
		execute( "main(){x=deque(2,3,5,7);x.append([4,8,16]).append(deque(20)).append(order(30)).append({40});return(x);}" ),
		"deque(2, 3, 5, 7, 4, 8, 16, 20, 30, 40)"
	);
	ENSURE_EQUALS(
		"deque prepend failed",
		execute( "main(){x=deque(2,3,5,7);x.prepend([4,8,16]).prepend(deque(20)).prepend(order(30)).prepend({40});return(x);}" ),
		"deque(40, 30, 20, 4, 8, 16, 2, 3, 5, 7)"
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
		"deque() iterator failed",
		execute( "main(){x=deque(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"deque copy failed",
		execute( "main(){x=deque(2,3,5);y=copy(x);x.push_front(7);return([x,y]);}" ),
		"[deque(7, 2, 3, 5), deque(2, 3, 5)]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "dict()" )
	ENSURE_EQUALS(
		"dict() iterator failed",
		execute( "main(){x=dict();x={\"Ala\":0,\"ma\":1,\"kota.\":2};v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ),
		"\"Ala0kota.2ma1\""
	);
	ENSURE_EQUALS(
		"dict() failed (explicit)",
		execute( "main(){x=dict();x[\"Ala\"]=0;x[\"ma\"]=1;x[\"kota.\"]=2;return(x);}" ),
		"{\"Ala\": 0, \"kota.\": 2, \"ma\": 1}"
	);
	ENSURE_EQUALS(
		"dict() failed (literal)",
		execute( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};return(x);}" ),
		"{\"Ala\": 0, \"kota.\": 2, \"ma\": 1}"
	);
	ENSURE_EQUALS(
		"dict() size() failed",
		execute( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};return(size(x));}" ),
		"3"
	);
	ENSURE_EQUALS(
		"dict.kas_key() failed",
		execute( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};return([x.has_key(\"kota.\"),x.has_key(\"psa.\")]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"dict.get()/dict.try_get() failed",
		execute( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};return([x.get(\"ma\"),x.get(\"psa.\",3)]);}" ),
		"[1, 3]"
	);
	ENSURE_EQUALS(
		"dict.get() on non existing succeeded",
		execute_except( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};return(x.get(\"psa\"));}" ),
		"*anonymous stream*:1:49: Key does not exist in `dict'."
	);
	ENSURE_EQUALS(
		"dict.erase() failed",
		execute( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};x.erase(\"kota.\");return(x);}" ),
		"{\"Ala\": 0, \"ma\": 1}"
	);
	ENSURE_EQUALS(
		"dict.clear()/dict.clone() failed",
		execute( "main(){x={\"Ala\":0,\"ma\":1,\"kota.\":2};y=copy(x);x.clear();return([x,y]);}" ),
		"[{}, {\"Ala\": 0, \"kota.\": 2, \"ma\": 1}]"
	);
	ENSURE_EQUALS( "dict reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed({2:0,3:1,5:-1,7:-2}),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "dict reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed({2:0,3:1,5:-1,7:-2});algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"dict equals failed",
		execute(
			"main(){"
			"d1={1:1,2:2,3:3};"
			"d2={1:1,2:2,3:3};"
			"d3f={1:1,2:2,4:3};"
			"d3s={1:1,2:2,3:4};"
			"return([d1==d2,d1==d3f,d1==d3s]);}"
		),
		"[true, false, false]"
	);
	ENSURE_EQUALS(
		"dict on non-uniform succeeded",
		execute_except( "main(){{1:2,2.:3.};}" ),
		"*anonymous stream*:1:13: Non-uniform key types, got a `real' instead of an `integer'."
	);
	ENSURE_EQUALS(
		"dict on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){x={A():0};return(x);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:28: Key type `A' is not a comparable."
	);
	ENSURE_EQUALS(
		"dict update failed",
		execute(
			"main(){\n"
			"d1={2:2,3:3,5:5};\n"
			"d2={2:2,4:4,8:8};\n"
			"d1.update(d2);\n"
			"return(d1);\n"
			"}\n"
		),
		"{2: 2, 3: 3, 4: 4, 5: 5, 8: 8}"
	);
	ENSURE_EQUALS(
		"dict.update on non-uniform succeeded",
		execute_except( "main(){{1:2}.update({2.:3.});}" ),
		"*anonymous stream*:1:20: Non-uniform key types, got a `real' instead of an `integer'."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "lookup()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected1[] = "\"none7truefalse1maAla0kota.2\"";
#else
	char const expected1[] = "\"none7truefalse1makota.2Ala0\"";
#endif
	ENSURE_EQUALS(
		"lookup() iterator failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;v=\"\";for(e:x){v=v+string(e);v=v+string(x[e]);}return(v);}" ),
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
	ENSURE_EQUALS( "lookup reversed() failed", execute( "import Algorithms as algo;main(){x=lookup();x[2]=0;x[3]=1;x[5]=-1;x[7]=-2;algo.materialize(algo.reversed(x),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "lookup reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=lookup();x[2]=0;x[3]=1;x[5]=-1;x[7]=-2;y=algo.reversed(x);algo.materialize(copy(y),list).push(size(y));}" ), "[7, 5, 3, 2, 4]" );
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
		std::vector<hcore::HString>({ "[{}, {$7.34, 2, 3.14, 'Q', \"ala\"}, 5]", "[{}, {$7.34, 2, 'Q', \"ala\", 3.14}, 5]" } )
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
TUT_TEARDOWN()

void tut_yaal_tools_hhuginn::test_subscript( HHuginn::TYPE type_, char const* index_, char const* result_ ) {
	hcore::HString src( "main(){x=" );
	switch ( type_ ) {
		case ( HHuginn::TYPE::STRING ): {
			src.append( "\"abcdefghijklmnopqrstuvwxyz\"" );
		} break;
		case ( HHuginn::TYPE::LIST ): {
			src.append( "list('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')" );
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
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript repeat" )
	ENSURE_EQUALS( "subscript repeat failed", execute( "main(){x=list(list(11,12,13),list(21,22,23),list(31,32,33));return(x[1][1]);}" ), "22" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "function ref" )
	ENSURE_EQUALS( "function ref failed", execute( "f(){return(\"x\");}g(){return(f);}main(){return(g()());}" ), "\"x\"" );
TUT_TEARDOWN()

void tut_yaal_tools_hhuginn::test_range( HHuginn::TYPE type_, char const* range_, char const* result_ ) {
	hcore::HString src;
	if ( type_ == HHuginn::TYPE::STRING ) {
		src.append( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[" ).append( range_ ).append( "]);}" );
	} else {
		src.append( "import Text as t;apply(x,T){i=0;s=size(x);while(i<s){x[i]=T(x[i]);i+=1;}return(x);}main(){return(t.join(apply(" )
			.append( type_ == HHuginn::TYPE::LIST ? "list" : "deque" )
			.append( "('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')[" )
			.append( range_ )
			.append( "],string),\"\"));}" );
	}
	ENSURE_EQUALS( "range failed", execute( src ), to_string( '"' ).append( result_ ).append( '"' ) );
	return;
}

TUT_UNIT_TEST( "range(slice)" )
	HHuginn::TYPE types[] = {
		HHuginn::TYPE::STRING,
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

TUT_UNIT_TEST( "lambda, closure" )
	ENSURE_EQUALS( "lambda failed", execute( "main(){s=[\"fail\"];l=@(x){x[0]=\"ok\";};l(s);return(s[0]);}" ), "\"ok\"" );
	ENSURE_EQUALS(
		"lambda failed",
		execute(
			"main(){\n"
			"a=2;\n"
			"b=7;\n"
			"x=@[a,b](c){(a-b)*c;};\n"
			"return(x(4));\n"
			"}\n"
		),
		"-20"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "ternary" )
	ENSURE_EQUALS( "ternary failed", execute( "main(){a=\"A\";b=\"B\";q=7;x=q>5?(a=\"1\"):(b=\"2\");return(a+b+x);}" ), "\"1B1\"" );
	ENSURE_EQUALS( "ternary failed", execute( "main(){a=\"A\";b=\"B\";q=7;x=q<5?(a=\"1\"):(b=\"2\");return(a+b+x);}" ), "\"A22\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "short circuit in boolean `and'" )
	char const p0[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) && ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T && T)", execute( p0 ), "\"12T\"" );
	char const p1[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) && ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T && F)", execute( p1 ), "\"12F\"" );
	char const p2[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) && ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F && T)", execute( p2 ), "\"10F\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "short circuit in boolean `or'" )
	char const p0[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) || ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F || T)", execute( p0 ), "\"12T\"" );
	char const p1[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) || ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T || F)", execute( p1 ), "\"10T\"" );
	char const p2[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) || ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T || T)", execute( p2 ), "\"10T\"" );
	char const p3[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) || ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F || F)", execute( p3 ), "\"12F\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean xor" )
	char const p[] =
		"main() {"
		" a = 1;"
		" b = 2;"
		" w = ( a == 1 ) ^^ ( b == 2 );"
		" x = ( a == 1 ) ^^ ( b == 0 );"
		" y = ( a == 0 ) ^^ ( b == 2 );"
		" z = ( a == 0 ) ^^ ( b == 0 );"
		" s = \"\";"
		" s = s + ( w ? \"T\" : \"F\" );"
		" s = s + ( x ? \"T\" : \"F\" );"
		" s = s + ( y ? \"T\" : \"F\" );"
		" s = s + ( z ? \"T\" : \"F\" );"
		" return ( s );"
		"}"
	;
	ENSURE_EQUALS( "boolean xor fqailed", execute( p ), "\"FTTF\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "print" )
	HHuginn h;
	HStringStream src( "main(){print(\"Hello World!\\n\");print(13);print(3.14);print($2.71);print('X');print(true);return(7);}" );
	HStringStream out;
	h.set_output_stream( out );
	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile() );
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 7 );
	ENSURE_EQUALS( "print failed", out.string(), "Hello World!\n133.142.71X1" );
	ENSURE_EQUALS(
		"print of bad type succeded",
		execute_except(
			"main(){print(size);}"
		),
		"*anonymous stream*:1:13: Printing `*function_reference*'s is not supported."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "input" )
	HHuginn h;
	HStringStream src( "main(){s=input();print(\"[\"+s+\"]\");return(13);}" );
	HStringStream in( "Amok" );
	HStringStream out;
	h.set_input_stream( in );
	h.set_output_stream( out );
	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile() );
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 13 );
	ENSURE_EQUALS( "print failed", out.string(), "[Amok]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "class" )
	ENSURE_EQUALS( "class failed", execute( "class A{_d=none;}main(){o=A();o._d=\"ok\";return(o._d);}" ), "\"ok\"" );
	ENSURE_EQUALS( "constructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}}main(){o=A(\"ok\");return(o._d);}" ), "\"ok\"" );
	ENSURE_EQUALS( "destructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}destructor(){_d.push(\"ok\");}}main(){l=list();{o=A(l);type(o);}return(l[0]);}" ), "\"ok\"" );
	ENSURE_EQUALS(
		"super failed",
		execute(
			"class B{_d=none;constructor(d_){_d=d_;}destructor(){_d.push(\"ok\");}}\n"
			"class D:B{_n=none;constructor(l_,n_){super.constructor(l_);_n=n_;}}\n"
			"main(){\n"
			"s=none;\n"
			"l=list();\n"
			"{\n"
			"o=D(l,\"arg\");\n"
			"s=o._n;\n"
			"}\n"
			"return(l[0]+s);\n"
			"}"
		),
		"\"okarg\""
	);
	ENSURE_EQUALS(
		"destructor chain failed",
		execute(
			"class B{_d=none;constructor(d_){_d=d_;}destructor(){_d.push(\"base\");}}"
			"class D:B{constructor(l_){super.constructor(l_);}destructor(){_d.push(\"derived\");}}"
			"main(){l=list();{o=D(l);type(o);}return(l[0]+l[1]);}"
		),
		"\"derivedbase\""
	);
	ENSURE_EQUALS(
		"class this failed",
		execute(
			"class A{_d=\"\";f(s_){_d=_d+s_;return(this);}}"
			"main(){a=A();a.f(\"this\").f(\"ok\");return(a._d);}"
		),
		"\"thisok\""
	);
	ENSURE_EQUALS(
		"class to_string failed",
		execute(
			"class A{_d=none;_x=none;constructor(d_,x_){_d=d_;_x=x_;}to_string(){return(string(_d)+\":\"+string(_x));}}"
			"main(){a=A(7,'Q');return(string(a));}"
		),
		"\"7:Q\""
	);
	ENSURE_EQUALS(
		"class copy failed",
		execute(
			"class A{"
			"_x=none;"
			"constructor(x_){_x=x_;}"
			"to_string(){return(string(_x));}"
			"mod(x_){_x=x_;}"
			"}"
			"main(){"
			"a=A(7);b=a;c=copy(a);a.mod(3);"
			"return([string(a),string(b),string(c)]);"
			"}"
		),
		"[\"3\", \"3\", \"7\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "throw,try,catch" )
	ENSURE_EQUALS(
		"throw,try,catch failed",
		execute(
			"f( x ) {\n"
			"\tif ( x < 0 ) {\n"
			"\t\tthrow Exception( \"neg arg\" );\n"
			"\t}\n"
			"\treturn( x * x );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tv = \"\";\n"
			"\ttry {\n"
			"\t\tv = string( f( 2 ) );\n"
			"\t\tv = v + string( f( -2 ) );\n"
			"\t\tv = v + \"end\";\n"
			"\t} catch( Exception e ) {\n"
			"\t\tv = v + e.what();\n"
			"\t}\n"
			"\treturn ( v );\n"
			"}\n"
		),
		"\"4neg arg\""
	);
	ENSURE_EQUALS(
		"throw,try,catch(Type expr) failed",
		execute(
			"f( x ) {\n"
			"\tif ( x < 0 ) {\n"
			"\t\tthrow Exception( \"neg arg\" );\n"
			"\t}\n"
			"\treturn( x * x );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tv = \"\";\n"
			"\ttry {\n"
			"\t\tl = [0];"
			"\t\tv = string( f( 2 ) );\n"
			"\t\tv = v + string( f( -2 ) );\n"
			"\t\tv = v + \"end\";\n"
			"\t} catch( Exception2 e ) {\n"
			"\t\tl = e;\n"
			"\t} catch( Exception l[0] ) {\n"
			"\t\tv = v + l[0].what();\n"
			"\t}\n"
			"\treturn ( v );\n"
			"}\n"
		),
		"\"4neg arg\""
	);
	ENSURE_EQUALS(
		"throw,try,catch(Type expr) failed",
		execute(
			"f( x ) {\n"
			"\tif ( x < 0 ) {\n"
			"\t\tthrow Exception( \"neg arg\" );\n"
			"\t}\n"
			"\treturn( x * x );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tv = \"\";\n"
			"\tl = [\"x\"];"
			"\ttry {\n"
			"\t\tv = string( f( 2 ) );\n"
			"\t\tv = v + string( f( -2 ) );\n"
			"\t\tv = v + \"end\";\n"
			"\t} catch( Exception2 e ) {\n"
			"\t\tl = e;\n"
			"\t} catch( Exception l[0] ) {\n"
			"\t\tv = v + l[0].what();\n"
			"\t}\n"
			"\tv = v + l[0].what();\n"
			"\treturn ( v );\n"
			"}\n"
		),
		"\"4neg argneg arg\""
	);
	ENSURE_EQUALS(
		"catch by base failed",
		execute(
			"main() {"
			"v=\"\";"
			"try {"
			"1/0;"
			"} catch( Exception e ) {"
			"v = e.what();"
			"}"
			"return ( v );"
			"}"
		),
		"\"Division by zero.\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "assert" )
	/* no message */ {
		HHuginn h;
		HStringStream src(
			"main( argv_ ) {\n"
			"\tassert( type( argv_ ) == list );\n"
			"\tassert( size( argv_ ) > 1 );\n"
			"\treturn( 0 );\n"
			"}"
		);
		h.add_argument( "assert" );
		h.load( src );
		h.preprocess();
		ENSURE( "parse failed", h.parse() );
		ENSURE( "compile", h.compile() );
		ENSURE_NOT( "execute", h.execute() );
		ENSURE_EQUALS( "reporting failed assertion failed", h.error_message(), "*anonymous stream*:3:8: size( argv_ ) > 1" );
		ENSURE_EQUALS( "reporting error position for failed assert failed", h.error_position(), 57 );
		ENSURE_EQUALS( "reporting error line for failed assert failed", h.error_coordinate().line(), 3 );
		ENSURE_EQUALS( "reporting error column for failed assert failed", h.error_coordinate().column(), 8 );
	}
	/* with message */ {
		HHuginn h;
		HStringStream src(
			"main( argv_ ) {\n"
			"\tassert( size( argv_ ) > 1, \"bad number of arguments\" );\n"
			"\treturn( 0 );\n"
			"}"
		);
		h.add_argument( "assert" );
		h.load( src );
		h.preprocess();
		ENSURE( "parse failed", h.parse() );
		ENSURE( "compile", h.compile() );
		ENSURE_NOT( "execute", h.execute() );
		ENSURE_EQUALS( "reporting failed assertion failed", h.error_message(), "*anonymous stream*:2:8: size( argv_ ) > 1, bad number of arguments" );
		ENSURE_EQUALS( "reporting error position for failed assert failed", h.error_position(), 23 );
		ENSURE_EQUALS( "reporting error line for failed assert failed", h.error_coordinate().line(), 2 );
		ENSURE_EQUALS( "reporting error column for failed assert failed", h.error_coordinate().column(), 8 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "empty return" )
	ENSURE_EQUALS(
		"empty return failed",
		execute(
			"f(l_) {\n"
			"l_.push(1);\n"
			"return;\n"
			"l_.push(2);\n"
			"return(3);\n"
			"}\n"
			"main(){\n"
			"l = list();\n"
			"s = string(type(f(l)));\n"
			"s = s + string(size(l));\n"
			"s = s + string(l[0]);\n"
			"return(s);\n"
			"}",
			HHuginn::COMPILER::BE_SLOPPY
		),
		"\"*none*11\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean not" )
	ENSURE_EQUALS(
		"boolean not failed (lval)",
		execute(
			"main(){s=\"\";a=0==1;\n"
			"if(!a) {\n"
			"s=\"ok\";"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\"ok\""
	);
	ENSURE_EQUALS(
		"boolean not failed (rval)",
		execute(
			"main(){s=\"\";a=0;\n"
			"if(!(a==1)) {\n"
			"s=\"ok\";"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\"ok\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator precedence" )
	ENSURE_EQUALS(
		"boolean not failed",
		execute(
			"main(){"
			"s=\"\";"
			"s+=string(2-3+5);s+=\":\";"
			"s+=string(2+3*5);s+=\":\";"
			"s+=string($2+$3^$5);s+=\":\";"
			"s+=string($2*$3^$5);s+=\":\";"
			"s+=string($5^$3^$2);s+=\":\";"
			"s+=string(7/2*5);s+=\":\";"
			"s+=string(3%2*5);s+=\":\";"
			"x=$3;"
			"s+=string(-x!);s+=\":\";"
			"s+=string(|-2|-|-3|);s+=\":\";"
			"s+=string($2+$3!);s+=\":\";"
			"return(s);"
			"}"
		),
		"\"4:17:245:486:1953125:15:5:-6:-1:8:\""
	);
	ENSURE_EQUALS(
		"boolean not failed",
		execute(
			"main(){"
			"s=\"\";"
			"s+=string(2-(3+5));s+=\":\";"
			"s+=string((2+3)*5);s+=\":\";"
			"s+=string(($2+$3)^$5);s+=\":\";"
			"s+=string(($2*$3)^$5);s+=\":\";"
			"s+=string(($2^$3)^$5);s+=\":\";"
			"s+=string(7/(2*3));s+=\":\";"
			"s+=string(3%(2*5));s+=\":\";"
			"x=$-3;"
			"s+=string((-x)!);s+=\":\";"
			"s+=string(($2+$3)!);s+=\":\";"
			"return(s);"
			"}"
		),
		"\"-6:25:3125:7776:32768:1:3:6:120:\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "are constants constant? (immutable)" )
	ENSURE_EQUALS(
		"constant in assignment was modified",
		execute(
			"main(){"
			"s=\"\";"
			"for(e:[1,1]) {"
			"x=0;"
			"x+=e;"
			"s+=string(x);"
			"}"
			"return(s);"
			"}"
		),
		"\"11\""
	);
	ENSURE_EQUALS(
		"constant in function call was modified",
		execute(
			"inc(x){"
			"x+=1;"
			"return(x);"
			"}"
			"main(){"
			"s=\"\";"
			"for(e:[0,0]) {"
			"x=inc(0);"
			"x+=e;"
			"s+=string(x);"
			"}"
			"return(s);"
			"}"
		),
		"\"11\""
	);
	ENSURE_EQUALS(
		"constant in function call (second arg) was modified",
		execute(
			"inc(x, y){"
			"y+=x;"
			"return(y);"
			"}"
			"main(){"
			"s=\"\";"
			"for(e:[1,1]) {"
			"x=inc(e, 0);"
			"s+=string(x);"
			"}"
			"return(s);"
			"}"
		),
		"\"11\""
	);
	ENSURE_EQUALS(
		"constant as map's key was modified",
		execute(
			"f(m){"
			"m[0]=0;"
			"}"
			"main(){"
			"m=lookup();"
			"f(m);"
			"for(k:m){"
			"k+=1;"
			"}"
			"m2=dict();"
			"f(m2);"
			"s=\"\";"
			"for(k:m2){"
			"s=string(k);"
			"}"
			"return(s);"
			"}"
		),
		"\"0\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "bugs regressions checks" )
	ENSURE_EQUALS(
		"definition of many variables in one expression failed",
		execute(
			"main(){"
			"a=b=c=d=e=f=g=h=i=j=k=l=m=n=o=p=q=r=s=t=u=v=w=x=y=z=1;"
			"return(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z);"
			"}"
		),
		"26"
	);
	ENSURE_EQUALS(
		"order of operations failed",
		execute(
			"main(){"
			"return($-284650292555885^$3+$66229832190556^$3+$283450105697727^$3);"
			"}"
		),
		"$74"
	);
	ENSURE_EQUALS(
		"invalid construction from type(expr)(...) succeeded",
		execute_except(
			"import Mathematics as M;\n"
			"main(){\n"
			"m=M.matrix(real,1,1);\n"
			"type(m)();\n"
			"}\n"
		),
		"*anonymous stream*:4:8: Explicit construction of class `Matrix' objects (instances) is forbidden."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "bound call as field value" )
	ENSURE_EQUALS(
		"bound call as field value failed",
		execute(
			"class A{_val=none;constructor(val_){_val=val_;}do(val_){return(_val*val_);}}"
			"class B{_call=none;constructor(call_){_call=call_;}do(val_){return(_call(val_));}}"
			"main(){"
			"a=A(7);"
			"return (B(a.do).do(13));"
			"}"
		),
		"91"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream" )
	ENSURE_EQUALS(
		"Stream.iterator failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"res=[];"
			"for ( l : fs.open(\"./data/nl.txt\",fs.reading())) {\n"
			"res.push(l.strip());"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[\"Ala\", \"ma\", \"kota.\", \"\"]"
	);
	ENSURE_EQUALS(
		"Stream.read failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(fs.open(\"./data/nl.txt\",fs.reading()).read(100));\n"
			"}\n"
		),
		"\"Ala\nma\nkota.\n\n\""
	);
	ENSURE_EQUALS(
		"Stream copy succeeded",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(copy(fs.open(\"./data/nl.txt\",fs.reading())));\n"
			"}\n"
		),
		"*anonymous stream*:3:8: Copy semantics is not supported on Stream."
	);
	ENSURE_EQUALS(
		"Stream size succeeded",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(size(fs.open(\"./data/nl.txt\",fs.reading())));\n"
			"}\n"
		),
		"*anonymous stream*:3:8: Getting size of `Stream' is an invalid operation."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "standard streams" )
	HHuginn h;
	HStringStream src(
		"import OperatingSystem as os;"
		"main() {"
		"os.stdout().write(\"stdout\");"
		"os.stderr().write(\"stderr\");"
		"os.stdlog().write(\"stdlog\");"
		"return (integer(os.stdin().read_line()));"
		"}"
	);
	HStreamInterface::ptr_t inS( make_pointer<HStringStream>() );
	HStreamInterface::ptr_t outS( make_pointer<HStringStream>() );
	HStreamInterface::ptr_t errS( make_pointer<HStringStream>() );
	HStreamInterface::ptr_t logS( make_pointer<HStringStream>() );
	h.set_input_stream( inS );
	h.set_output_stream( outS );
	h.set_error_stream( errS );
	h.set_log_stream( logS );
	ENSURE_EQUALS( "bad smart input", &h.input_stream(), inS.raw() );
	ENSURE_EQUALS( "bad smart output", &h.output_stream(), outS.raw() );
	ENSURE_EQUALS( "bad smart error", &h.error_stream(), errS.raw() );
	ENSURE_EQUALS( "bad smart log", &h.log_stream(), logS.raw() );
	HStringStream in;
	HStringStream out;
	HStringStream err;
	HStringStream log;
	h.set_input_stream( in );
	h.set_output_stream( out );
	h.set_error_stream( err );
	h.set_log_stream( log );
	ENSURE_EQUALS( "bad raw input", &h.input_stream(), &in );
	ENSURE_EQUALS( "bad raw output", &h.output_stream(), &out );
	ENSURE_EQUALS( "bad raw error", &h.error_stream(), &err );
	ENSURE_EQUALS( "bad raw log", &h.log_stream(), &log );

	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile() );
	in << "123";
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "stdin", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 123 );
	ENSURE_EQUALS( "stdout failed", out.string(), "stdout" );
	ENSURE_EQUALS( "stderr failed", err.string(), "stderr" );
	ENSURE_EQUALS( "stdlog failed", log.string(), "stdlog" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modules" )
	HHuginn h;
	HStringStream src(
		"import Mathematics as M;"
		"import Tress as tress;"
		"main() {"
		"return ([tress.rectangle(2,3), tress.diagonal(3,4), tress.wrap(\"yaal\"), tress.math().floor(3.14), string(tress.Object($7)), type(M)]);"
		"}"
	);
	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile( { "./data/" } ) );
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::LIST );
	ENSURE_EQUALS( "using module failed", to_string( r, &h ), "[6, 5.0, \"#yaal#\", 3.0, \"7\", Mathematics]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "incremental mode" )
	lines_t l0{
		{ "x=0;" },
		{ "print(\"x\");" },
		{ "x+=1;" },
		{ "x;" }
	};
	ENSURE_EQUALS( "incremental mode failed", execute_incremental( l0 ), "0xnone11" );
	lines_t l1{
		{ "class X{x=0;}", OLine::TYPE::DEFINITION },
		{ "X(){}", OLine::TYPE::DEFINITION }
	};
	ENSURE_EQUALS( "creation of function of name that is used by class succeeded", execute_incremental( l1 ), "none*anonymous stream*:2:1: Class of the same name `X' is already defined." );
	lines_t l2{
		{ "x=0;x+=1;" }
	};
	ENSURE_EQUALS( "multiple statements in single input in incremental mode failed", execute_incremental( l2 ), "1" );
	lines_t l3{
		{ "@(x){x;};" },
		{ "@(x){x;};" }
	};
	ENSURE_EQUALS( "bug in incremental mode management of statement counter resurfaced", execute_incremental( l3 ), "@2:1@3:1" );
	lines_t l4{
		{ "main();" }
	};
	ENSURE_EQUALS( "bug in incremental mode management recursive main resurfaced", execute_incremental( l4 ), "*anonymous stream*:2:1: Referencing main() function in incremental mode is forbidden." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "max call stack size" )
	HHuginn h;
	ENSURE_THROW( "invalid max call stack size accepted", h.set_max_call_stack_size( 100 ), HHuginnException );
	ENSURE_EQUALS(
		"max call stack size check failed",
		execute_except( "main(){\nmain();\n}\n" ),
		"*anonymous stream*:2:5: Call stack size limit exceeded: 129"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "observe/use" )
	ENSURE_EQUALS(
		"obseve/use basic failed",
		execute(
			"main(){"
			"r=[];"
			"x=none;"
			"y=7;"
			"x=observe(y);"
			"r.push(type(x));"
			"z=use(x);"
			"r.push(type(z));"
			"r.push(copy(z));"
			"z=none;"
			"y=none;"
			"z=use(x);"
			"r.push(type(z));"
			"return(r);"
			"}"
		),
		"[*observer*, integer, 7, *none*]"
	);
	ENSURE_EQUALS(
		"obseve/use complex failed",
		execute(
			"class Node {"
			"	_data = none;"
			"	_ref = none;"
			"	_next = none;"
			"	_prev = none;"
			"	constructor( data_, ref_ ) {"
			"		_data = data_;"
			"		_ref = ref_;"
			"		_ref += 1;"
			"	}"
			"	prev_data() {"
			"		x = use( _prev );"
			"		return ( x._data );"
			"	}"
			"	destructor() {"
			"		_ref -= 1;"
			"	}"
			"}"
			""
			"main() {"
			"	ref = 0;"
			"	res = \"\";"
			"	/* scope */ {"
			"		n1 = Node( \"a\", ref );"
			"		n2 = Node( \"b\", ref );"
			"		n1._next = n2;"
			"		n2._prev = observe( n1 );"
			"		res += string( ref );"
			"		res += n2.prev_data();"
			"	}"
			"	res += string( ref );"
			"	return ( res );"
			"}"
		),
		"\"2a0\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "simple program" )
	clog << simpleProg << endl;
	HHuginn h;
	HStringStream src( simpleProg );
	h.load( src );
	h.preprocess();
	if ( ! h.parse() ) {
		clog << h.error_message() << endl;
	}
	h.compile();
	h.add_argument( "7" );
	h.add_argument( "13" );
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 42 );
TUT_TEARDOWN()


}


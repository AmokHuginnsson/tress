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

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn", 70 );

TUT_UNIT_TEST( "grammar test" )
	HHuginn h;
	HRule hg( h.make_engine() );
	HGrammarDescription gd( hg );

	char const expected[][440] = {
		"huginnGrammar = +( classDefinition | functionDefinition | importStatement )",
		"classDefinition = ( \"class\" >> classIdentifier >> -( ':' >> baseIdentifier ) >> '{' >> +( field | functionDefinition ) >> '}' )",
		"functionDefinition = ( functionDefinitionIdentifier >> '(' >> -nameList >> ')' >> scope )",
		"importStatement = ( \"import\" >> packageName >> \"as\" >> importName >> ';' )",
		"classIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"baseIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"field = ( fieldIdentifier >> '=' >> expression >> ';' )",
		"functionDefinitionIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"nameList = ( parameter >> *( ',' >> parameter ) )",
		"scope = ( '{' >> *statement >> '}' )",
		"packageName = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"importName = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"fieldIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"expression = ( *( ( assignable >> ( \"=\" | \"+=\" | \"-=\" | \"*=\" | \"/=\" | \"%=\" | \"^=\" ) ) ^ '=' ) >> value )",
		"parameter = ( parameterIdentifier >> -( '=' >> expression ) )",
		"statement = ( ifStatement | whileStatement | forStatement | switchStatement | tryCatchStatement | throwStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope )",
		"assignable = ( subscript | variableSetter )",
		"value = ternary",
		"parameterIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
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
		"subscript = ( reference >> +( subscriptOperator | functionCallOperator | memberAccess ) )",
		"variableSetter = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"ternary = ( ( booleanOr >> -( \"^^\" >> booleanOr ) ) >> -( '?' >> expression >> ':' >> expression ) )",
		"ifClause = ( \"if\" >> '(' >> expression >> ')' >> scope )",
		"caseStatement = ( \"case\" >> '(' >> expression >> ')' >> ':' >> scope >> -breakStatement )",
		"defaultStatement = ( \"default\" >> ':' >> scope )",
		"catchStatement = ( \"catch\" >> '(' >> exceptionType >> assignable >> ')' >> scope )",
		"reference = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"subscriptOperator = ( '[' >> ( ( ( rangeOper >> -argument ) | ( argument >> -( rangeOper >> -argument ) ) ) >> -( rangeOper >> -argument ) ) >> ']' )",
		"functionCallOperator = ( '(' >> -argList >> ')' )",
		"memberAccess = ( '.' >> member )",
		"booleanOr = ( booleanAnd >> *( \"||\" >> booleanAnd ) )",
		"exceptionType = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"rangeOper = ':'",
		"argument = expression",
		"argList = ( argument >> *( ',' >> argument ) )",
		"member = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"booleanAnd = ( equality >> *( \"&&\" >> equality ) )",
		"equality = ( compare >> -( ( \"==\" | \"!=\" ) >> compare ) )",
		"compare = ( sum >> -( ( \"<=\" | \">=\" | \"<\" | \">\" ) >> sum ) )",
		"sum = ( multiplication >> *( '+-' >> multiplication ) )",
		"multiplication = ( power >> *( '*/%' >> power ) )",
		"power = ( booleanNot >> *( '^' >> booleanNot ) )",
		"booleanNot = ( ( '!' >> negation ) | negation )",
		"negation = ( ( '-' >> factorial ) | factorial )",
		"factorial = ( atom >> -( ( '!' & \"==\" ) | ( '!' ^ '=' ) ) )",
		"atom = ( absoluteValue | ( parenthesis >> -( memberAccess >> dereference ) ) | real | integer | ( ( numberLiteral | character_literal ) >> -( memberAccess >> functionCallOperator ) ) | ( ( listLiteral | dictLiteral | stringLiteral ) >> -( ( subscriptOperator | memberAccess ) >> dereference ) ) | none | true | false | ( reference >> dereference ) | ( lambda >> -( functionCallOperator >> dereference ) ) )",
		"absoluteValue = ( '|' >> expression >> '|' )",
		"parenthesis = ( '(' >> expression >> ')' )",
		"dereference = *( subscriptOperator | functionCallOperator | memberAccess )",
		"numberLiteral = ( '$' >> real )",
		"listLiteral = ( '[' >> -argList >> ']' )",
		"dictLiteral = ( '{' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> '}' )",
		"stringLiteral = string_literal",
		"none = \"none\"",
		"true = \"true\"",
		"false = \"false\"",
		"lambda = ( '@' >> '(' >> -nameList >> ')' >> scope )",
		"dictLiteralElement = ( argument >> ':' >> argument )"
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

TUT_UNIT_TEST( "simplest program" )
	HHuginn h;
	HStringStream src( "main(){return(0);}" );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simplest program (return real)" )
	HHuginn h;
	HStringStream src( "main(){return(3.14);}" );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::REAL );
	ENSURE_DISTANCE( "bad value returned", static_cast<HHuginn::HReal*>( r.raw() )->value(), 3.14L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simplest program (return string)" )
	HHuginn h;
	HStringStream src( "main(){return(\"hello world\");}" );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::STRING );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HString*>( r.raw() )->value(), "hello world" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simplest program (return character)" )
	HHuginn h;
	HStringStream src( "main(){return('X');}" );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::CHARACTER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HCharacter*>( r.raw() )->value(), 'X' );
TUT_TEARDOWN()

TUT_UNIT_TEST( "call function" )
	HHuginn h;
	HStringStream src( "f(){return(7);}main(){return(f());}" );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set variable" )
	HHuginn h;
	HStringStream src( "main(){a=7;return(a);}" );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add" )
	ENSURE_EQUALS( "add int failed", execute( "main(){return(1+2);}" ), "3" );
	ENSURE_EQUALS( "add real failed", execute( "main(){return(1.+2.);}" ), "3.000000000000" );
	ENSURE_EQUALS( "add number failed", execute( "main(){return($1+$2);}" ), "$3" );
	ENSURE_EQUALS( "add string failed", execute( "main(){return(\"1\"+\"2\");}" ), "\"12\"" );
	ENSURE_EQUALS( "add user succeeded", execute_except( "class A{_x=none;}main(){return(A()+A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `add' method." );
	ENSURE_EQUALS( "add char succeeded", execute_except( "main(){return(character('1')+character('2'));}" ), "*anonymous stream*:1:29: There is no `+' operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sub" )
	ENSURE_EQUALS( "sub int failed", execute( "main(){return(7-3);}" ), "4" );
	ENSURE_EQUALS( "sub real failed", execute( "main(){return(7.-3.);}" ), "4.000000000000" );
	ENSURE_EQUALS( "sub number failed", execute( "main(){return($7-$3);}" ), "$4" );
	ENSURE_EQUALS( "sub user succeeded", execute_except( "class A{_x=none;}main(){return(A()-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `substract' method." );
	ENSURE_EQUALS( "sub char succeeded", execute_except( "main(){return(character('7')-character('3'));}" ), "*anonymous stream*:1:29: There is no `-' operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mul" )
	ENSURE_EQUALS( "mul int failed", execute( "main(){return(2*3);}" ), "6" );
	ENSURE_EQUALS( "mul real failed", execute( "main(){return(2.*3.);}" ), "6.000000000000" );
	ENSURE_EQUALS( "mul number failed", execute( "main(){return($2*$3);}" ), "$6" );
	ENSURE_EQUALS( "mul user succeeded", execute_except( "class A{_x=none;}main(){return(A()*A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `multiply' method." );
	ENSURE_EQUALS( "mul char succeeded", execute_except( "main(){return(character('2')*character('3'));}" ), "*anonymous stream*:1:29: There is no `*' operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "div" )
	ENSURE_EQUALS( "div int failed", execute( "main(){return(7/2);}" ), "3" );
	ENSURE_EQUALS( "div real failed", execute( "main(){return(7./2.);}" ), "3.500000000000" );
	ENSURE_EQUALS( "div number failed", execute( "main(){return($7/$2);}" ), "$3.5" );
	ENSURE_EQUALS( "div user succeeded", execute_except( "class A{_x=none;}main(){return(A()/A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `divide' method." );
	ENSURE_EQUALS( "div char succeeded", execute_except( "main(){return(character('7')/character('2'));}" ), "*anonymous stream*:1:29: There is no `/' operator for `character'." );
	ENSURE_EQUALS( "div 0 int succeeded", execute_except( "main(){return(1/0);}" ), "*anonymous stream*:1:16: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "div 0 real succeeded", execute_except( "main(){return(1./0.);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "div 0 num succeeded", execute_except( "main(){return($1/$0);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod" )
	ENSURE_EQUALS( "mod int failed", execute( "main(){return(11%3);}" ), "2" );
	ENSURE_EQUALS( "mod real failed", execute( "main(){return(11.%3.);}" ), "2.000000000000" );
	ENSURE_EQUALS( "mod number failed", execute( "main(){return($11%$3);}" ), "$2" );
	ENSURE_EQUALS( "mod user succeeded", execute_except( "class A{_x=none;}main(){return(A()%A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `modulo' method." );
	ENSURE_EQUALS( "mod char succeeded", execute_except( "main(){return(character('8')%character('3'));}" ), "*anonymous stream*:1:29: There is no `%' operator for `character'." );
	ENSURE_EQUALS( "mod 0 int succeeded", execute_except( "main(){return(1%0);}" ), "*anonymous stream*:1:16: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "mod 0 real succeeded", execute_except( "main(){return(1.%0.);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
	ENSURE_EQUALS( "mod 0 num succeeded", execute_except( "main(){return($1%$0);}" ), "*anonymous stream*:1:17: Uncaught exception: Division by zero." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "pow" )
	ENSURE_EQUALS( "pow real failed", execute( "main(){return(2.^3.);}" ), "8.000000000000" );
	ENSURE_EQUALS( "pow number failed", execute( "main(){return($2^$3);}" ), "$8" );
	ENSURE_EQUALS( "pow user succeeded", execute_except( "class A{_x=none;}main(){return(A()^A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `power' method." );
	ENSURE_EQUALS( "pow char succeeded", execute_except( "main(){return(character('2')^character('3'));}" ), "*anonymous stream*:1:29: There is no `^' operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "factorial" )
	ENSURE_EQUALS( "neg factorial succeeded", execute_except( "main(){return($-1!);}" ), "*anonymous stream*:1:18: Uncaught exception: Factorial from negative." );
	ENSURE_EQUALS( "fractional factorial succeeded", execute_except( "main(){return($1.5!);}" ), "*anonymous stream*:1:19: Uncaught exception: Factorial from fraction." );
	ENSURE_EQUALS( "int factorial succeeded", execute_except( "main(){return(1!);}" ), "*anonymous stream*:1:16: There is no `!` operator for `integer'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "absolute" )
	ENSURE_EQUALS( "abs int failed", execute( "main(){return([|1|,|-1|]);}" ), "[1, 1]" );
	ENSURE_EQUALS( "abs real failed", execute( "main(){return([|1.|,|-1.|]);}" ), "[1.000000000000, 1.000000000000]" );
	ENSURE_EQUALS( "abs num failed", execute( "main(){return([|$1|,|$-1|]);}" ), "[$1, $1]" );
	ENSURE_EQUALS( "abs char succeeded", execute_except( "main(){return(|character('1')|);}" ), "*anonymous stream*:1:30: There is no |.| operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "neg" )
	ENSURE_EQUALS( "neg user succeeded", execute_except( "class A{_x=none;}main(){return(-A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:32: Class `A' does not have `negate' method." );
	ENSURE_EQUALS( "neg char succeeded", execute_except( "main(){return(-character('1'));}" ), "*anonymous stream*:1:15: There is no `negate` operator for `character'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equals" )
	ENSURE_EQUALS( "equals none failed", execute( "n(){}main(){return([n()==n(),n()==0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals int failed", execute( "main(){return([1==1,1==0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals real failed", execute( "main(){return([1.==1.,1.==0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals number failed", execute( "main(){return([$1==$1,$1==$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals character failed", execute( "main(){return(['1'=='1','1'=='0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "equals string failed", execute( "main(){return([\"1\"==\"1\",\"1\"==\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "user failed", execute( "class A{_x=none;constructor(x){_x=x;}equals(x){return(_x==x._x);}}main(){return([A(1)==A(1),A(1)==A(0)]);}", HHuginn::COMPILER::BE_SLOPPY ), "[true, false]" );
	ENSURE_EQUALS( "bad equals user succeeded", execute_except( "class A{equals(x){return(none);}}main(){return(A()==A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:51: Comparision method `equals' returned non-boolean result `none'." );
	ENSURE_EQUALS( "missing equals user succeeded", execute_except( "class A{_x=none;}main(){return(A()==A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `equals' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "less" )
	ENSURE_EQUALS( "less int failed", execute( "main(){return([0<1,0<0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "less real failed", execute( "main(){return([0.<1.,0.<0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "less number failed", execute( "main(){return([$0<$1,$0<$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "less character failed", execute( "main(){return(['0'<'1','0'<'0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "less string failed", execute( "main(){return([\"0\"<\"1\",\"0\"<\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "bad less user succeeded", execute_except( "class A{less(x){return(none);}}main(){return(A()<A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:49: Comparision method `less' returned non-boolean result `none'." );
	ENSURE_EQUALS( "missing less user succeeded", execute_except( "class A{_x=none;}main(){return(A()<A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `less' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greater" )
	ENSURE_EQUALS( "greater int failed", execute( "main(){return([1>0,0>0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater real failed", execute( "main(){return([1.>0.,0.>0.]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater number failed", execute( "main(){return([$1>$0,$0>$0]);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater character failed", execute( "main(){return(['1'>'0','0'>'0']);}" ), "[true, false]" );
	ENSURE_EQUALS( "greater string failed", execute( "main(){return([\"1\">\"0\",\"0\">\"0\"]);}" ), "[true, false]" );
	ENSURE_EQUALS( "bad greater user succeeded", execute_except( "class A{greater(x){return(none);}}main(){return(A()>A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:52: Comparision method `greater' returned non-boolean result `none'." );
	ENSURE_EQUALS( "missing greater user succeeded", execute_except( "class A{_x=none;}main(){return(A()>A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `greater' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "less_or_equal" )
	ENSURE_EQUALS( "less_or_equal int failed", execute( "main(){return([0<=1,0<=0,1<=0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal real failed", execute( "main(){return([0.<=1.,0.<=0.,1<=0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal number failed", execute( "main(){return([$0<=$1,$0<=$0,$1<=$0]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal character failed", execute( "main(){return(['0'<='1','0'<='0','1'<='0']);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "less_or_equal string failed", execute( "main(){return([\"0\"<=\"1\",\"0\"<=\"0\",\"1\"<=\"0\"]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "bad less_or_equal user succeeded", execute_except( "class A{less_or_equal(x){return(none);}}main(){return(A()<=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:58: Comparision method `less_or_equal' returned non-boolean result `none'." );
	ENSURE_EQUALS( "missing less_or_equal user succeeded", execute_except( "class A{_x=none;}main(){return(A()<=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `less_or_equal' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greater_or_equal" )
	ENSURE_EQUALS( "greater_or_equal int failed", execute( "main(){return([1>=0,0>=0,0>=1]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal real failed", execute( "main(){return([1.>=0.,0.>=0.,0.>=1.]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal number failed", execute( "main(){return([$1>=$0,$0>=$0,$0>=$1]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal character failed", execute( "main(){return(['1'>='0','0'>='0','0'>='1']);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "greater_or_equal string failed", execute( "main(){return([\"1\">=\"0\",\"0\">=\"0\",\"0\">=\"1\"]);}" ), "[true, true, false]" );
	ENSURE_EQUALS( "bad greater_or_equal user succeeded", execute_except( "class A{greater_or_equal(x){return(none);}}main(){return(A()>=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:61: Comparision method `greater_or_equal' returned non-boolean result `none'." );
	ENSURE_EQUALS( "missing greater_or_equal user succeeded", execute_except( "class A{_x=none;}main(){return(A()>=A());}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:35: Class `A' does not have `greater_or_equal' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "if" )
	ENSURE_EQUALS( "if (true) failed", execute( "main(){x=2;if(x>0){x=x*x;}return(x);}" ), "4" );
	ENSURE_EQUALS( "if (false) failed", execute( "main(){x=2;if(x>2){x=x*x;}return(x);}" ), "2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "while" )
	ENSURE_EQUALS( "while failed", execute( "main(){x=2;while(x<100){x=x*x;}return(x);}" ), "256" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "for" )
	ENSURE_EQUALS( "for failed", execute( "main(){x=list(1,2,3);s=0;for(e:x){s=s+e;}return(s);}" ), "6" );
	ENSURE_EQUALS( "for(expr:) failed", execute( "main(){x=list(1,2,3);s=0;l=[0];for(l[0]:x){s=s+l[0];}return(string(s)+string(l[0]));}" ), "\"63\"" );
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

TUT_UNIT_TEST( "integer()" )
	ENSURE_EQUALS( "int to int failed", execute( "main(){return(integer(7));}" ), "7" );
	ENSURE_EQUALS( "bad string to int succeeded", execute_except( "main(){return(integer(\"bad\"));}" ), "*anonymous stream*:1:22: Uncaught exception: not a number: bad" );
	ENSURE_EQUALS( "real to int failed", execute( "main(){return(integer(7.));}" ), "7" );
	ENSURE_EQUALS( "num to int failed", execute( "main(){return(integer($7));}" ), "7" );
	ENSURE_EQUALS( "char to int failed", execute( "main(){return(integer('7'));}" ), "55" );
	ENSURE_EQUALS( "string to int failed", execute( "main(){return(integer(\"7\"));}" ), "7" );
	ENSURE_EQUALS( "user to int failed", execute( "class A{_x=none;constructor(x){_x=x;}to_integer(){return(_x);}}main(){return(integer(A(7)));}" ), "7" );
	ENSURE_EQUALS( "bad user to int succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(integer(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:60: Class `A' does not have `to_integer' method." );
	ENSURE_EQUALS( "bad user to int (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_integer(){return(this);}}main(){return(integer(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:87: User conversion method returned invalid type `A' instead of `integer'." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean()" )
	ENSURE_EQUALS( "boolean to boolean failed", execute( "main(){return([boolean(true),boolean(false)]);}" ), "[true, false]" );
	ENSURE_EQUALS( "int to boolean succeeded", execute_except( "main(){return(boolean(7));}" ), "*anonymous stream*:1:22: Conversion from `integer' to `boolean' is not supported." );
	ENSURE_EQUALS( "bad user to int succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(boolean(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:60: Class `A' does not have `to_boolean' method." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "real()" )
	ENSURE_EQUALS( "real to real failed", execute( "main(){return(real(7));}" ), "7.000000000000" );
	ENSURE_EQUALS( "bad string to real succeeded", execute_except( "main(){return(real(\"bad\"));}" ), "*anonymous stream*:1:19: Uncaught exception: syntax error - unknown mnemonic for: bad, at: 0" );
	ENSURE_EQUALS( "real to real failed", execute( "main(){return(real(7.));}" ), "7.000000000000" );
	ENSURE_EQUALS( "num to real failed", execute( "main(){return(real($7));}" ), "7.000000000000" );
	ENSURE_EQUALS( "string to real failed", execute( "main(){return(real(\"7\"));}" ), "7.000000000000" );
	ENSURE_EQUALS( "user to real failed", execute( "class A{_x=none;constructor(x){_x=x;}to_real(){return(_x);}}main(){return(real(A(7.)));}" ), "7.000000000000" );
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
	ENSURE_EQUALS( "user to number failed", execute( "class A{_x=none;constructor(x){_x=x;}to_number(){return(_x);}}main(){return(number(A($7)));}" ), "$7" );
	ENSURE_EQUALS( "bad user to number succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(number(A(7.)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:59: Class `A' does not have `to_number' method." );
	ENSURE_EQUALS( "char to number succeeded", execute_except( "main(){return(number('7'));}" ), "*anonymous stream*:1:21: Conversion from `character' to `number' is not supported." );
	ENSURE_EQUALS( "number.is_exact() failed", execute( "main(){return([($2/$5).is_exact(),($2/$3).is_exact()]);}" ), "[true, false]" );
	ENSURE_EQUALS( "number.is_integral() failed", execute( "main(){return([($15/$5).is_integral(),($15/$6).is_integral()]);}" ), "[true, false]" );
	ENSURE_EQUALS( "number.set_precision()/number.get_precision() failed", execute( "main(){a=$1;a.set_precision(200);b=$3;b.set_precision(300);return([a.get_precision(),b.get_precision()]);}" ), "[200, 300]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "character()" )
	ENSURE_EQUALS( "character to character failed", execute( "main(){return(character('7'));}" ), "'7'" );
	ENSURE_EQUALS( "real to character succeeded", execute_except( "main(){return(character(7.));}" ), "*anonymous stream*:1:24: Conversion from `real' to `character' is not supported." );
	ENSURE_EQUALS( "bad user to character succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}}main(){return(character(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:62: Class `A' does not have `to_character' method." );
	ENSURE_EQUALS( "bad user to character (invalid type) succeeded", execute_except( "class A{_x=none;constructor(x){_x=x;}to_character(){return(this);}}main(){return(character(A(7)));}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:91: User conversion method returned invalid type `A' instead of `character'." );
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
TUT_TEARDOWN()

TUT_UNIT_TEST( "deque()" )
	ENSURE_EQUALS(
		"deque failed (explicit)",
		execute( "main(){x=deque(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
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
	ENSURE_EQUALS(
		"dict on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){x={A():0};return(x);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:28: Key type `A' is not a comparable."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "lookup()" )
	ENSURE_EQUALS(
		"lookup() iterator failed",
		execute( "ts(x){return(type(x)==\"boolean\"?(x?\"true\":\"false\"):(x!=none?string(x):\"none\"));}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;v=\"\";for(e:x){v=v+ts(e);v=v+ts(x[e]);}return(v);}" ),
		"\"none7Ala0truefalse1makota.2\""
	);
	ENSURE_EQUALS( "hash on user succeeded", execute_except( "class A{_x=none;}main(){l=lookup();return(l[A()]=0);}", HHuginn::COMPILER::BE_SLOPPY ), "*anonymous stream*:1:1: There is no `hash' operator for `A'." );
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
		"lookup() erase failed",
		execute( "ts(x){return(type(x)==\"boolean\"?(x?\"true\":\"false\"):(x!=none?string(x):\"none\"));}d(x){v=\"\";for(e:x){v+=ts(e);v+=ts(x[e]);}return(v);}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;v=d(x);v+=\"|\";x.erase(none);x.erase(true);v+=d(x);return(v);}" ),
		"\"none7Ala0truefalse1makota.2|Ala01makota.2\""
	);
	ENSURE_EQUALS(
		"lookup() get failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return([x.get(1),x.get(2,7)]);}" ),
		"[\"ma\", 7]"
	);
	ENSURE_EQUALS(
		"lookup() copy() failed",
		execute( "ts(x){return(type(x)==\"boolean\"?(x?\"true\":\"false\"):(x!=none?string(x):\"none\"));}d(x){v=\"\";for(e:x){v+=ts(e);v+=ts(x[e]);}return(v);}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;y=copy(x);x.erase(none);x.erase(true);return([d(x),d(y)]);}" ),
		"[\"Ala01makota.2\", \"none7Ala01matruefalsekota.2\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "order()" )
	ENSURE_EQUALS(
		"order() failed",
		execute( "main(){x=order(2,3,1,4,7,5);x.add(10).add(0);v=\"\";for(e:x){v=v+string(e);}return(v);}" ),
		"\"012345710\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected[] = "\"|7.34|2|Q|3.140000000000|ala\"";
#else
	char const expected[] = "\"|7.34|2|Q|ala|3.140000000000\"";
#endif
	ENSURE_EQUALS(
		"set() failed",
		execute( "main(){x=set(2,\"ala\",3.14);x.add($7.34).add('Q');v=\"\";for(e:x){v=v+\"|\"+string(e);}return(v);}" ),
		expected
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

TUT_UNIT_TEST( "lambda" )
	ENSURE_EQUALS( "lambda failed", execute( "main(){s=[\"fail\"];l=@(x){x[0]=\"ok\";};l(s);return(s[0]);}" ), "\"ok\"" );
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
	HStringStream src( "main(){print(\"Hello World!\\n\");print(13);print(3.14);print($2.71);print('X');return(7);}" );
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
	ENSURE_EQUALS( "print failed", out.string(), "Hello World!\n133.142.71X" );
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

TUT_UNIT_TEST( "simple class" )
	ENSURE_EQUALS( "class failed", execute( "class A{_d=none;}main(){o=A();o._d=\"ok\";return(o._d);}" ), "\"ok\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "class constructor" )
	ENSURE_EQUALS( "constructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}}main(){o=A(\"ok\");return(o._d);}" ), "\"ok\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "class destructor" )
	ENSURE_EQUALS( "destructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}destructor(){_d.add(\"ok\");}}main(){l=list();{o=A(l);type(o);}return(l[0]);}" ), "\"ok\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "class super" )
	ENSURE_EQUALS(
		"super failed",
		execute(
			"class B{_d=none;constructor(d_){_d=d_;}destructor(){_d.add(\"ok\");}}\n"
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
TUT_TEARDOWN()

TUT_UNIT_TEST( "destructor chain" )
	ENSURE_EQUALS(
		"destructor chain failed",
		execute(
			"class B{_d=none;constructor(d_){_d=d_;}destructor(){_d.add(\"base\");}}"
			"class D:B{constructor(l_){super.constructor(l_);}destructor(){_d.add(\"derived\");}}"
			"main(){l=list();{o=D(l);type(o);}return(l[0]+l[1]);}"
		),
		"\"derivedbase\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "class this" )
	ENSURE_EQUALS(
		"class this failed",
		execute(
			"class A{_d=\"\";f(s_){_d=_d+s_;return(this);}}"
			"main(){a=A();a.f(\"this\").f(\"ok\");return(a._d);}"
		),
		"\"thisok\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "class to_string" )
	ENSURE_EQUALS(
		"class this failed",
		execute(
			"class A{_d=none;_x=none;constructor(d_,x_){_d=d_;_x=x_;}to_string(){return(string(_d)+\":\"+string(_x));}}"
			"main(){a=A(7,'Q');return(string(a));}"
		),
		"\"7:Q\""
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
TUT_TEARDOWN()

TUT_UNIT_TEST( "catch by base" )
#ifdef __MSVCXX__
	char const res[] = "\"The system cannot find the file specified.\r\n: ./out/non-existing\"";
#else
	char const res[] = "\"No such file or directory: ./out/non-existing\"";
#endif
	ENSURE_EQUALS(
		"throw,try,catch failed",
		execute(
			"import FileSystem as fs;"
			"main() {"
			"v=\"\";"
			"try {"
			"fs.open( \"./out/non-existing\", fs.reading() );"
			"} catch( Exception e ) {"
			"v = e.what();"
			"}"
			"return ( v );"
			"}"
		),
		res
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "assert" )
	/* no message */ {
		HHuginn h;
		HStringStream src(
			"main( argv_ ) {\n"
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
		ENSURE_EQUALS( "reporting failed assertion failed", h.error_message(), "*anonymous stream*:2:8: size( argv_ ) > 1" );
		ENSURE_EQUALS( "reporting error position for failed assert failed", h.error_position(), 23 );
		ENSURE_EQUALS( "reporting error line for failed assert failed", h.error_coordinate().line(), 2 );
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
			"l_.add(1);\n"
			"return;\n"
			"l_.add(2);\n"
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
		"\"none11\""
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

TUT_UNIT_TEST( "many variables definition in one expression" )
	ENSURE_EQUALS(
		"definition of many variables failed",
		execute(
			"main(){"
			"a=b=c=d=e=f=g=h=i=j=k=l=m=n=o=p=q=r=s=t=u=v=w=x=y=z=1;"
			"return(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z);"
			"}"
		),
		"26"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "sum of pows" )
	ENSURE_EQUALS(
		"definition of many variables failed",
		execute(
			"main(){"
			"return($-284650292555885^$3+$66229832190556^$3+$283450105697727^$3);"
			"}"
		),
		"$74"
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


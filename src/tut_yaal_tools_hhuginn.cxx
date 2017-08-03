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
using namespace tress;
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

TUT_UNIT_TEST( "exceptions" )
	ENSURE_EQUALS(
		"exception failed",
		execute(
			"main(){\n"
			"r=none;\n"
			"try{\n"
			"1/0;\n"
			"}catch(ArithmeticException e) {\n"
			"ce = copy(e);\n"
			"f=ce.trace()[0];"
			"r=[ce.message(),ce.where(),ce.what(),f.file(),f.line(),f.column(),f.context(),string(f)];\n"
			"}\n"
			"return(r);\n"
			"}\n" ),
		"[\"*anonymous stream*:4:2: Division by zero.\", \"*anonymous stream*:4:2\", \"Division by zero.\", \"*anonymous stream*\", 4, 2, \"main\", \"*anonymous stream*:4:2:main\"]"
	);
	ENSURE_EQUALS(
		"StackFrameInfo copy succeeded",
		execute_except(
			"main() {\n"
			"\tcopy(Exception(\"\").trace()[0]);\n"
			"}\n"
		),
		"*anonymous stream*:2:6: Copy semantics is not supported on StackFrameInfo."
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
		"recursive user destructor",
		execute(
			"class Crash {\n"
			"	_next = none;\n"
			"	_prev = none;\n"
			"}\n"
			"\n"
			"main() {\n"
			"	handle = none;\n"
			"	/* scope */ {\n"
			"		n1 = Crash();\n"
			"		n2 = Crash();\n"
			"		n1._next = n2;\n"
			"		n2._prev = n1;\n"
			"		handle = observe( n1 );\n"
			"	}\n"
			"	use( handle )._next = none;\n"
			"	return ( 0 );\n"
			"}\n"
		),
		"0"
	);
	ENSURE_EQUALS(
		"invalid destructor signature",
		execute_except(
			"class Crash {\n"
			"	_name = none;\n"
			"	_next = none;\n"
			"	_prev = none;\n"
			"	constructor( name_ ) {\n"
			"		_name = name_;\n"
			"		_name.clear();\n"
			"	}\n"
			"	destructor( name_ ) {\n"
			"	}\n"
			"}\n"
			"\n"
			"main() {\n"
			"	handle = none;\n"
			"	/* scope */ {\n"
			"		n1 = Crash( \"one\" );\n"
			"		n2 = Crash( \"two\" );\n"
			"		n1._next = n2;\n"
			"		n2._prev = n1;\n"
			"		handle = observe( n1 );\n"
			"	}\n"
			"	use( handle )._next = none;\n"
			"	return ( 0 );\n"
			"}\n"
		),
		"*anonymous stream*:1:1: Bad number of parameters in call to: `destructor()', expected exactly: 1, got: 0."
	);
	ENSURE_EQUALS(
		"throw from destructor",
		execute_except(
			"class Crash {\n"
			"	_name = none;\n"
			"	constructor( name_ ) {\n"
			"		_name = name_;\n"
			"	}\n"
			"	destructor() {\n"
			"		throw Exception( \"Boom!: \" + _name );\n"
			"	}\n"
			"}\n"
			"\n"
			"main() {\n"
			"	res = none;\n"
			"	try {\n"
			"		Crash( \"one\" );\n"
			"	} catch ( Exception e ) {\n"
			"		res = e.message();\n"
			"	}\n"
			"	return ( res );\n"
			"}\n"
		),
		"*anonymous stream*:7:3: Uncaught exception from destructor: Boom!: one"
	);
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
		"*anonymous stream*:3:12: Copy semantics is not supported on Stream."
	);
	ENSURE_EQUALS(
		"Stream size succeeded",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(size(fs.open(\"./data/nl.txt\",fs.reading())));\n"
			"}\n"
		),
		"*anonymous stream*:3:12: Getting size of `Stream' is an invalid operation."
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
	ENSURE_EQUALS(
		"invalid field access failure",
		execute_except(
			"import Tress as tress;\n"
			"main() {\n"
			"tress.bug(0);\n"
			"}\n",
			{ "./data/" }
		),
		"./data//Tress.hgn:50:15: `Mathematics' does not have `square_foot' member (did you mean `square_root'?)."
	);
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
	lines_t l5{
		{ "2+2;" },
		{ "import CannotParse as cp;", OLine::TYPE::IMPORT },
		{ "3*4;" }
	};
	ENSURE_EQUALS( "Parser errors in incemental mode while importing user defined submodule", execute_incremental( l5 ), "4*anonymous stream*:1:8: ./data/CannotParse.hgn:3:1: expected one of characters: -12" );
	lines_t l6{
		{ "2+2;" },
		{ "import CannotCompile as cp;", OLine::TYPE::IMPORT },
		{ "3*4;" }
	};
	ENSURE_EQUALS( "Compiler errors in incemental mode while importing user defined submodule", execute_incremental( l6 ), "4*anonymous stream*:1:8: ./data/CannotCompile.hgn:2:4: Operand types for `+' do not match: `integer' vs `real'.12" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "introspection" )
	HIntrospector introspector;
	ENSURE_EQUALS(
		"Stream.read failed",
		execute(
			"foo( x ) {\n"
			"\ty = x + 1;\n"
			"\treturn ( y );\n"
			"}\n"
			"\n"
			"bar( p ) {\n"
			"\tq = foo( p ) * 2;\n"
			"\treturn ( q );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tbar( 0 );\n"
			"}\n",
			HHuginn::COMPILER::DEFAULT,
			&introspector
		),
		"2"
	);
	HIntrospecteeInterface::call_stack_t const* callStack( introspector.get_stack( "*anonymous stream*", 2 ) );
	char const expected[][64] = {
		"*anonymous stream*:2:2:foo",
		"*anonymous stream*:7:9:bar",
		"*anonymous stream*:12:5:main"
	};
	HStringStream ss;
	int row( 0 );
	for ( HIntrospecteeInterface::HCallSite const& cs : *callStack ) {
		ss << cs.file() << ":" << cs.line() << ":" << cs.column() << ":" << cs.context();
		ENSURE_EQUALS( "getting call stack failed", ss.str(), expected[row] );
		ss.reset();
		++ row;
	}
	/* top frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals( "*anonymous stream*", 2 ) );
		hcore::HString names;
		for ( hcore::HString const& n : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( n );
		}
		ENSURE_EQUALS( "get_locals failed", names, "x y" );
	}
	/* second frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals_up( "*anonymous stream*", 2 ) );
		hcore::HString names;
		for ( hcore::HString const& n : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( n );
		}
		ENSURE_EQUALS( "get_locals failed", names, "p q" );
	}
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


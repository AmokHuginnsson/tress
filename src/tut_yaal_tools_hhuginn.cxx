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
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn" );

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
		"atom = ( absoluteValue | parenthesis | real | numberLiteral | integer | character_literal | ( listLiteral >> -( subscriptOperator >> dereference ) ) | ( dictLiteral >> -( subscriptOperator >> dereference ) ) | none | true | false | ( reference >> dereference ) | ( stringLiteral >> -subscriptOperator ) | ( lambda >> -( functionCallOperator >> dereference ) ) )",
		"absoluteValue = ( '|' >> expression >> '|' )",
		"parenthesis = ( '(' >> expression >> ')' )",
		"numberLiteral = ( '$' >> real )",
		"listLiteral = ( '[' >> -argList >> ']' )",
		"dereference = *( subscriptOperator | functionCallOperator | memberAccess )",
		"dictLiteral = ( '{' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> '}' )",
		"none = \"none\"",
		"true = \"true\"",
		"false = \"false\"",
		"stringLiteral = string_literal",
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

TUT_UNIT_TEST( "if" )
	ENSURE_EQUALS( "if (true) failed", execute( "main(){x=2;if(x>0){x=x*x;}return(string(x));}" ), "4" );
	ENSURE_EQUALS( "if (false) failed", execute( "main(){x=2;if(x>2){x=x*x;}return(string(x));}" ), "2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "while" )
	ENSURE_EQUALS( "while failed", execute( "main(){x=2;while(x<100){x=x*x;}return(string(x));}" ), "256" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "for" )
	ENSURE_EQUALS( "for failed", execute( "main(){x=list(1,2,3);s=0;for(e:x){s=s+e;}return(string(s));}" ), "6" );
	ENSURE_EQUALS( "for(expr:) failed", execute( "main(){x=list(1,2,3);s=0;l=[0];for(l[0]:x){s=s+l[0];}return(string(s)+string(l[0]));}" ), "63" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "switch" )
	ENSURE_EQUALS( "switch (no match, no default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}}return(x);}" ), "x" );
	ENSURE_EQUALS( "switch (no match, with default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}default:{x=\"y\";}}return(x);}" ), "y" );
	ENSURE_EQUALS( "switch (match, fallthrough, no default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}case(1):{x=x+\"y\";}case(2):{x=x+\"z\";}}return(x);}" ), "xyz" );
	ENSURE_EQUALS(
		"switch (match, fallthrough, default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}case(1):{x=x+\"y\";}case(2):{x=x+\"z\";}default:{x=x+\"!\";}}return(x);}" ),
		"xyz!"
	);
	ENSURE_EQUALS(
		"switch (match, no fallthrough, no default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}break;case(1):{x=x+\"y\";}break;case(2):{x=x+\"z\";}break;}return(x);}" ),
		"xy"
	);
	ENSURE_EQUALS(
		"switch (match, no fallthrough, default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}break;case(1):{x=x+\"y\";}break;case(2):{x=x+\"z\";}break;default:{x=x+\"!\";}}return(x);}" ),
		"xy"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "break;" )
	ENSURE_EQUALS( "break; failed (while)", execute( "main(){x=0;y=0;while(y<100){y=y+1;if(x>100){break;}x=x+y*y;}return(string(x));}" ), "140" );
	ENSURE_EQUALS( "break; failed (for)", execute( "main(){x=[\"A\",\"a\",\"B\",\"b\",\"C\",\"c\"];v=\"\";for(e:x){if(size(v)>2){break;}v=v+e;}return(v);}" ), "AaB" );
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
		"AaLlAaMmAKOTA"
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
		"A+l+a+ +m+a kota."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "list()" )
	ENSURE_EQUALS(
		"list failed (explicit)",
		execute( "main(){x=list(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"3abc"
	);
	ENSURE_EQUALS(
		"list failed (literal)",
		execute( "main(){x=[\"a\",\"b\",\"c\"];v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"3abc"
	);
	ENSURE_EQUALS( "list failed (crazy)", execute( "f(a){return(\"X\"+a+\"X\");}main(){return([f][0](\"hi\"));}" ), "XhiX" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "deque()" )
	ENSURE_EQUALS(
		"deque failed (explicit)",
		execute( "main(){x=deque(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"3abc"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "dict()" )
	ENSURE_EQUALS(
		"dict() failed (explicit)",
		execute( "main(){x=dict();x[\"Ala\"]=0;x[\"ma\"]=1;x[\"kota.\"]=2;v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ),
		"Ala0kota.2ma1"
	);
	ENSURE_EQUALS(
		"dict() failed (literal)",
		execute( "main(){x=dict();x={\"Ala\":0,\"ma\":1,\"kota.\":2};v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ),
		"Ala0kota.2ma1"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "lookup()" )
	ENSURE_EQUALS(
		"lookup() failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;v=\"\";for(e:x){v=v+string(e);v=v+string(x[e]);}return(v);}" ),
		"Ala01makota.2"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "order()" )
	ENSURE_EQUALS(
		"order() failed",
		execute( "main(){x=order(2,3,1,4,7,5);x.add(10).add(0);v=\"\";for(e:x){v=v+string(e);}return(v);}" ),
		"012345710"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected[] = "|7.34|2|Q|3.140000000000|ala";
#else
	char const expected[] = "|7.34|2|Q|ala|3.140000000000";
#endif
	ENSURE_EQUALS(
		"set() failed",
		execute( "main(){x=set(2,\"ala\",3.14);x.add($7.34).add('Q');v=\"\";for(e:x){v=v+\"|\"+string(e);}return(v);}" ),
		expected
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript" )
	ENSURE_EQUALS( "subscript failed", execute( "main(){x=list(1,2,3);return(string(x[1]));}" ), "2" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[0]));}" ), "a" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[25]));}" ), "z" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[-26]));}" ), "a" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[-1]));}" ), "z" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[13]));}" ), "n" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[-13]));}" ), "n" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[12]));}" ), "m" );
	ENSURE_EQUALS( "subscript failed", execute( "main(){return(string(\"abcdefghijklmnopqrstuvwxyz\"[-12]));}" ), "o" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript repeat" )
	ENSURE_EQUALS( "subscript repeat failed", execute( "main(){x=list(list(11,12,13),list(21,22,23),list(31,32,33));return(string(x[1][1]));}" ), "22" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "function ref" )
	ENSURE_EQUALS( "function ref failed", execute( "f(){return(\"x\");}g(){return(f);}main(){return(g()());}" ), "x" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "range(slice)" )
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:]);}" ), "abcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:0]);}" ), "" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:1]);}" ), "a" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:2]);}" ), "ab" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:24]);}" ), "abcdefghijklmnopqrstuvwx" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:25]);}" ), "abcdefghijklmnopqrstuvwxy" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:26]);}" ), "abcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[0:]);}" ), "abcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[1:]);}" ), "bcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[2:]);}" ), "cdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[24:]);}" ), "yz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[25:]);}" ), "z" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[26:]);}" ), "" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[1:25]);}" ), "bcdefghijklmnopqrstuvwxy" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[2:24]);}" ), "cdefghijklmnopqrstuvwx" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[4:8]);}" ), "efgh" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:-1]);}" ), "abcdefghijklmnopqrstuvwxy" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:-10]);}" ), "abcdefghijklmnop" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:-100]);}" ), "" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-1:]);}" ), "z" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-10:]);}" ), "qrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-100:]);}" ), "abcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-8:-4]);}" ), "stuv" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:100]);}" ), "abcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::]);}" ), "abcdefghijklmnopqrstuvwxyz" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::2]);}" ), "acegikmoqsuwy" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::13]);}" ), "an" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::25]);}" ), "az" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::26]);}" ), "a" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::100]);}" ), "a" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::-1]);}" ), "zyxwvutsrqponmlkjihgfedcba" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::-2]);}" ), "zxvtrpnljhfdb" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[::-3]);}" ), "zwtqnkheb" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[:20:-1]);}" ), "zyxwv" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-15:-3:2]);}" ), "lnprtv" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-3:-15:-2]);}" ), "xvtrpn" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-4::-1]);}" ), "wvutsrqponmlkjihgfedcba" );
	ENSURE_EQUALS( "range failed", execute( "main(){return(\"abcdefghijklmnopqrstuvwxyz\"[-4::]);}" ), "wxyz" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "lambda" )
	ENSURE_EQUALS( "lambda failed", execute( "main(){s=[\"fail\"];l=@(x){x[0]=\"ok\";};l(s);return(s[0]);}" ), "ok" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ternary" )
	ENSURE_EQUALS( "ternary failed", execute( "main(){a=\"A\";b=\"B\";q=7;x=q>5?(a=\"1\"):(b=\"2\");return(a+b+x);}" ), "1B1" );
	ENSURE_EQUALS( "ternary failed", execute( "main(){a=\"A\";b=\"B\";q=7;x=q<5?(a=\"1\"):(b=\"2\");return(a+b+x);}" ), "A22" );
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
	ENSURE_EQUALS( "ternary failed (T && T)", execute( p0 ), "12T" );
	char const p1[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) && ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T && F)", execute( p1 ), "12F" );
	char const p2[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) && ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F && T)", execute( p2 ), "10F" );
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
	ENSURE_EQUALS( "ternary failed (F || T)", execute( p0 ), "12T" );
	char const p1[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) || ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T || F)", execute( p1 ), "10T" );
	char const p2[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) || ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T || T)", execute( p2 ), "10T" );
	char const p3[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) || ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F || F)", execute( p3 ), "12F" );
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
	ENSURE_EQUALS( "boolean xor fqailed", execute( p ), "FTTF" );
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
	ENSURE_EQUALS( "class failed", execute( "class A{_d=none;}main(){o=A();o._d=\"ok\";return(o._d);}" ), "ok" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "class constructor" )
	ENSURE_EQUALS( "constructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}}main(){o=A(\"ok\");return(o._d);}" ), "ok" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "class destructor" )
	ENSURE_EQUALS( "destructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}destructor(){_d.add(\"ok\");}}main(){l=list();{o=A(l);type(o);}return(l[0]);}" ), "ok" );
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
		"okarg"
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
		"derivedbase"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "class this" )
	ENSURE_EQUALS(
		"class this failed",
		execute(
			"class A{_d=\"\";f(s_){_d=_d+s_;return(this);}}"
			"main(){a=A();a.f(\"this\").f(\"ok\");return(a._d);}"
		),
		"thisok"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "class to_string" )
	ENSURE_EQUALS(
		"class this failed",
		execute(
			"class A{_d=none;_x=none;constructor(d_,x_){_d=d_;_x=x_;}to_string(){return(string(_d)+\":\"+string(_x));}}"
			"main(){a=A(7,'Q');return(string(a));}"
		),
		"7:Q"
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
		"4neg arg"
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
		"none11"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean not" )
	ENSURE_EQUALS(
		"boolean not failed",
		execute(
			"main(){s=\"\";a=0;\n"
			"if(!(a==1)) {\n"
			"s=\"ok\";"
			"}\n"
			"return(s);\n"
			"}"
		),
		"ok"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "simple program" )
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


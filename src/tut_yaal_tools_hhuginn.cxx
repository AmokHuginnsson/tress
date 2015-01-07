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

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

namespace yaal {
namespace tools {
inline std::ostream& operator << ( std::ostream& out, HHuginn::HValue::TYPE t_ ) {
	out << HHuginn::HValue::type_name( t_ );
	return ( out );
}
}
}

namespace tut {

struct tut_yaal_tools_hhuginn : public simple_mock<tut_yaal_tools_hhuginn> {
	typedef char const* prog_src_t;
	virtual ~tut_yaal_tools_hhuginn( void ) {}
	void test_preprocessing( prog_src_t, prog_src_t, int );
	void test_parse( prog_src_t, int const[3], int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn" );

TUT_UNIT_TEST( "grammar test" )
	HHuginn h;
	HRule hg( h.make_engine() );
	HGrammarDescription gd( hg );

	char const expected[][200] = {
		"huginnGrammar = +( functionDefinition )",
		"functionDefinition = functionDefinitionIdentifier >> '(' >> -( nameList ) >> ')' >> scope",
		"functionDefinitionIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"nameList = variableIdentifier >> *( ',' >> variableIdentifier )",
		"scope = '{' >> *( statement ) >> '}'",
		"variableIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"statement = ifStatement | whileStatement | forStatement | switchStatement | breakStatement | continueStatement | returnStatement | expressionList",
		"ifStatement = \"if\" >> '(' >> booleanExpression >> ')' >> scope >> -( \"else\" >> scope )",
		"whileStatement = \"while\" >> '(' >> booleanExpression >> ')' >> scope",
		"forStatement = \"for\" >> '(' >> variableIdentifier >> ':' >> expression >> ')' >> scope",
		"switchStatement = \"switch\" >> '(' >> expression >> ')' >> '{' >> +( caseStatement ) >> -( defaultStatement ) >> '}'",
		"breakStatement = \"break\" >> ';'",
		"continueStatement = \"continue\" >> ';'",
		"returnStatement = \"return\" >> -( '(' >> expression >> ')' ) >> ';'",
		"expressionList = +( expression >> ';' )",
		"booleanExpression = booleanEquals | booleanNotEquals | booleanLess | booleanGreater | booleanLessEq | booleanGreaterEq | booleanAnd | booleanOr | booleanXor | booleanNot",
		"expression = *( variableIdentifier >> '=' ) >> ref",
		"caseStatement = \"case\" >> '(' >> integer >> ')' >> ':' >> scope >> -( breakStatement )",
		"defaultStatement = \"default\" >> ':' >> scope",
		"booleanEquals = expression >> \"==\" >> expression",
		"booleanNotEquals = expression >> \"!=\" >> expression",
		"booleanLess = expression >> \"<\" >> expression",
		"booleanGreater = expression >> \">\" >> expression",
		"booleanLessEq = expression >> \"<=\" >> expression",
		"booleanGreaterEq = expression >> \">=\" >> expression",
		"booleanAnd = booleanValue >> \"&&\" >> booleanValue",
		"booleanOr = booleanValue >> \"||\" >> booleanValue",
		"booleanXor = booleanValue >> \"^^\" >> booleanValue",
		"booleanNot = '!' >> booleanValue",
		"ref = value >> *( '[' >> value >> ']' )",
		"booleanValue = \"true\" | \"false\" | '(' >> booleanExpression >> ')'",
		"value = multiplication >> *( '+-' >> multiplication )",
		"multiplication = power >> *( '*/%' >> power )",
		"power = atom >> *( '^' >> atom )",
		"atom = absoluteValue | parenthesis | functionCall | real | integer | string_literal | character_literal | variableIdentifier",
		"absoluteValue = '|' >> expression >> '|'",
		"parenthesis = '(' >> expression >> ')'",
		"functionCall = functionCallIdentifier >> '(' >> -( argList ) >> ')'",
		"functionCallIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"argList = argument >> *( ',' >> argument )",
		"argument = *( variableIdentifier >> '=' ) >> ref"
	};

	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "too many rules in Huginn grammar", i < countof ( expected ) );
		ENSURE_EQUALS( "bad rule in Huginn grammar", *it, expected[i] );
		cout << *it << endl;
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

char const progPost0[] =
	"\n"
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

char const progPre1[] =
	"main(/* no arg */) {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progPost1[] =
	"main() {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progPre2[] =
	"main(/* no arg */) {\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost2[] =
	"main() {\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre3[] =
	"main(/* no arg */) {\n"
	"\tprint( \"/* keep this */\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost3[] =
	"main() {\n"
	"\tprint( \"/* keep this */\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre4[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost4[] =
	"main() {\n"
	"\tprint( \"keep // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre5[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost5[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre6[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\"\n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost6[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre7[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\" // but remove this \n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost7[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre8[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\" // but remove this \n"
	"\t/* and \"this\" too */\n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost8[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre9[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\" /* but remove this */ \n"
	"\t/* and \"this\" too */\n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
	"/* and this is unfinished comment"
;

char const progPost9[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre10[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\" /* but remove this */ \n"
	"\t/* and \"this\" too */\n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
	"/* and this is unfinished comment *"
;

char const progPost10[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre11[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\" /* but remove this\n"
	"\t* and \"this\" too\n"
	"\t* and 'this' also */\n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const progPost11[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const progPre12[] =
	"main(/* no arg */) {\n"
	"\treturn ( 0 );\n"
	"}\n"
	"\n"
	"foo() {\n"
	"\tx = 33 /* hi there */ /\n"
;

char const progPost12[] =
	"main() {\n"
	"\treturn ( 0 );\n"
	"}\n"
	"\n"
	"foo() {\n"
	"\tx = 33  /\n"
;

char const progPre13[] =
	"main(/* no arg */) {\n"
	"\treturn /* first *//* second */ ( 0 );\n"
	"}\n"
;

char const progPost13[] =
	"main() {\n"
	"\treturn  ( 0 );\n"
	"}\n"
;

char const progPre14[] =
	"main(/* no arg */) {\n"
	"\treturn /* first */ /* second */ ( 0 );\n"
	"}\n"
;

char const progPost14[] =
	"main() {\n"
	"\treturn   ( 0 );\n"
	"}\n"
;

char const progPre15[] =
	"main(/* no arg */) { /* first */// second\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progPost15[] =
	"main() { \n"
	"\treturn ( 0 );\n"
	"}\n"
;

void tut_yaal_tools_hhuginn::test_preprocessing( prog_src_t pre_, prog_src_t post_, int index_ ) {
	HStringStream pre( pre_ );
	HStringStream post;
	HHuginn h;
	h.load( pre );
	clog << "preprocessing: " << index_ << endl;
	h.preprocess();
	h.dump_preprocessed_source( post );
	ENSURE_EQUALS( "prepocessing failed " + to_string( index_ ), post.string(), post_ );
	return;
}

TUT_UNIT_TEST( "preprocessor" )
	prog_src_t progPre[] = {
		simpleProg,
		progPre1,
		progPre2,
		progPre3,
		progPre4,
		progPre5,
		progPre6,
		progPre7,
		progPre8,
		progPre9,
		progPre10,
		progPre11,
		progPre12,
		progPre13,
		progPre14,
		progPre15,
		NULL
	};
	prog_src_t progPost[] = {
		progPost0,
		progPost1,
		progPost2,
		progPost3,
		progPost4,
		progPost5,
		progPost6,
		progPost7,
		progPost8,
		progPost9,
		progPost10,
		progPost11,
		progPost12,
		progPost13,
		progPost14,
		progPost15,
		NULL
	};
	for ( prog_src_t* pre( begin( progPre ) ), * preEnd( end( progPre ) ), * post( begin( progPost ) ); pre != preEnd; ++ pre, ++ post ) {
		if ( *pre ) {
			test_preprocessing( *pre, *post, static_cast<int>( pre - begin( progPre ) ) );
		}
	}
TUT_TEARDOWN()

char const progParse0[] =
	"main() {\n"
	"\treturn #( 0 );\n"
	"}\n"
;

char const progParse1[] =
	"main(/* no arg */) {\n"
	"\treturn #( 0 );\n"
	"}\n"
;

char const progParse2[] =
	"/*\n"
	" * Sample code in huginn.\n"
	" */\n"
	"\n"
	"main(/* no arg */) {\n"
	"\treturn #( 0 );\n"
	"}\n"
;

char const progParse3[] =
	"#main() {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progParse4[] =
	"main() {\n"
	"\treturn /* before */#( 0 );\n"
	"}\n"
;

char const progParse5[] =
	"main() {\n"
	"\treturn #/* after */( 0 );\n"
	"}\n"
;

char const progParse6[] =
	"main() {\n"
	"\treturn /* before */#/* after */( 0 );\n"
	"}\n"
;

char const progParse7[] =
	"main() {#\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progParse8[] =
	"main() {\n"
	"#\treturn ( 0 );\n"
	"}\n"
;

void tut_yaal_tools_hhuginn::test_parse( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	clog << "parsing: " << index_ << endl;
	h.parse();
	ENSURE_EQUALS( "reporting error position failed " + to_string( index_ ), h.error_position(), err_[0] );
	ENSURE_EQUALS( "reporting error line failed " + to_string( index_ ), h.error_coordinate().line(), err_[1] );
	ENSURE_EQUALS( "reporting error column failed " + to_string( index_ ), h.error_coordinate().column(), err_[2] );
	clog << h.error_message() << endl;
}

TUT_UNIT_TEST( "report parsing error" )
	prog_src_t progParse[] = {
		progParse0,
		progParse1,
		progParse2,
		progParse3,
		progParse4,
		progParse5,
		progParse6,
		progParse7,
		progParse8,
		NULL
	};
	int const err[][3] = {
		{ 17, 2, 9 },  // 0
		{ 29, 2, 9 },  // 1
		{ 63, 6, 9 },  // 2
		{ 0, 1, 1 },   // 3
		{ 29, 2, 21 }, // 4
		{ 17, 2, 9 },  // 5
		{ 29, 2, 21 }, // 6
		{ 8, 1, 9 },   // 7
		{ 9, 2, 1 },   // 8
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progParse ) ), * progEnd( end( progParse ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_parse( *prog, *e, static_cast<int>( prog - begin( progParse ) ) );
		}
	}
TUT_TEARDOWN()

char const progCompile0[] =
	"main() {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

TUT_UNIT_TEST( "compile" )
	HStringStream prog( progCompile0 );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	TUT_EVAL( h.parse() );
	h.compile();
	h.dump_vm_state( clog );
TUT_TEARDOWN()

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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::HValue::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", dynamic_cast<HHuginn::HInteger*>( r.raw() )->value(), 0 );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::HValue::TYPE::REAL );
	ENSURE_DISTANCE( "bad value returned", dynamic_cast<HHuginn::HReal*>( r.raw() )->value(), 3.14L, epsilon );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::HValue::TYPE::STRING );
	ENSURE_EQUALS( "bad value returned", dynamic_cast<HHuginn::HString*>( r.raw() )->value(), "hello world" );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::HValue::TYPE::CHARACTER );
	ENSURE_EQUALS( "bad value returned", dynamic_cast<HHuginn::HCharacter*>( r.raw() )->value(), 'X' );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::HValue::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", dynamic_cast<HHuginn::HInteger*>( r.raw() )->value(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "simple program" )
	HHuginn h;
	HStringStream src( simpleProg );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	//h.execute();
TUT_TEARDOWN()


}


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

namespace yaal { namespace tools { namespace executing_parser {
HRule huginn_grammar( void );
} } }

namespace tut {

struct tut_yaal_tools_hhuginn : public simple_mock<tut_yaal_tools_hhuginn> {
	typedef char const* prog_src_t;
	virtual ~tut_yaal_tools_hhuginn( void ) {}
	void test_preprocessing( prog_src_t, prog_src_t );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn" );

TUT_UNIT_TEST( 1, "grammar test" )
	HRule hg( huginn_grammar() );
	HGrammarDescription gd( hg );

	char const expected[][200] = {
		"huginnGrammar = +( functionDefinition )",
		"functionDefinition = name >> '(' >> -( nameList ) >> ')' >> scope",
		"name = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"nameList = name >> *( ',' >> name )",
		"scope = '{' >> *( statement ) >> '}'",
		"statement = ifStatement | whileStatement | foreachStatement | switchStatement | returnStatement | expressionList",
		"ifStatement = \"if\" >> '(' >> booleanExpression >> ')' >> scope >> -( \"else\" >> scope )",
		"whileStatement = \"while\" >> '(' >> booleanExpression >> ')' >> loopScope",
		"booleanExpression = booleanEquals | booleanNotEquals | booleanLess | booleanGreater | booleanLessEq | booleanGreaterEq | booleanAnd | booleanOr | booleanXor | booleanNot",
		"loopScope = '{' >> *( loopStatement ) >> '}'",
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
		"loopStatement = ifStatement | whileStatement | foreachStatement | switchStatement | breakStatement | continueStatement | returnStatement | expressionList",
		"expression = *( name >> '=' ) >> ref",
		"booleanValue = \"true\" | \"false\" | '(' >> booleanExpression >> ')'",
		"foreachStatement = \"foreach\" >> '(' >> name >> ':' >> expression >> ')' >> loopScope",
		"switchStatement = \"switch\" >> '(' >> expression >> ')' >> '{' >> +( caseStatement ) >> -( defaultStatement ) >> '}'",
		"continueStatement = \"continue\" >> ';'",
		"returnStatement = \"return\" >> '(' >> expression >> ')' >> ';'",
		"expressionList = +( expression >> ';' )",
		"ref = value >> *( '[' >> value >> ']' )",
		"caseStatement = \"case\" >> '(' >> integer >> ')' >> ':' >> scope >> -( breakStatement )",
		"defaultStatement = \"default\" >> ':' >> scope",
		"value = multiplication >> *( '+' >> multiplication )",
		"breakStatement = \"break\" >> ';'",
		"multiplication = power >> *( '*' >> power )",
		"power = atom >> *( '^' >> atom )",
		"atom = absoluteValue | parenthesis | functionCall | real | integer | string_literal | character_literal | name",
		"absoluteValue = '|' >> expression >> '|'",
		"parenthesis = '(' >> expression >> ')'",
		"functionCall = name >> '(' >> -( argList ) >> ')'",
		"argList = expression >> *( ',' >> expression )"
	};

	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		ENSURE( "too many rules in Huginn grammar", i < countof ( expected ) );
		ENSURE_EQUALS( "bad rule in Huginn grammar", *it, expected[i] );
		cout << *it << endl;
	}
	ENSURE_EQUALS( "not all rules found for Huginn grammar", i, countof ( expected ) );
TUT_TEARDOWN()

char const prog0[] =
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

char const prog0post[] =
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

char const prog1[] =
	"main(/* no arg */) {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const prog1post[] =
	"main() {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const prog2[] =
	"main(/* no arg */) {\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const prog2post[] =
	"main() {\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const prog3[] =
	"main(/* no arg */) {\n"
	"\tprint( \"/* keep this */\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const prog3post[] =
	"main() {\n"
	"\tprint( \"/* keep this */\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const prog4[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const prog4post[] =
	"main() {\n"
	"\tprint( \"keep // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const prog5[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const prog5post[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

char const prog6[] =
	"main(/* no arg */) {\n"
	"\tprint( \"keep \\\"\"\n"
	"\t\t\" // this too\" );\n"
	"\treturn ( 0 ); // We shall return 0.\n"
	"}\n"
;

char const prog6post[] =
	"main() {\n"
	"\tprint( \"keep \\\" // this too\" );\n"
	"\treturn ( 0 ); \n"
	"}\n"
;

void tut_yaal_tools_hhuginn::test_preprocessing( prog_src_t pre_, prog_src_t post_ ) {
	HStringStream pre( pre_ );
	HStringStream post;
	HHuginn h;
	h.load( pre );
	h.preprocess();
	h.dump_preprocessed_source( post );
	ENSURE_EQUALS( "prepocessing failed", post.string(), post_ );
	return;
}

TUT_UNIT_TEST( 2, "preprocessor" )
	prog_src_t progpre[] = {
		prog0,
		prog1,
		prog2,
		prog3,
		prog4,
		prog5,
		prog6,
		NULL
	};
	prog_src_t progpost[] = {
		prog0post,
		prog1post,
		prog2post,
		prog3post,
		prog4post,
		prog5post,
		prog6post,
		NULL
	};
	for ( prog_src_t* pre( begin( progpre ) ), * preEnd( end( progpre ) ), * post( begin( progpost ) ); pre != preEnd; ++ pre, ++ post ) {
		if ( *pre ) {
			test_preprocessing( *pre, *post );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "simple program" )
	HHuginn h;
	HStringStream src( prog0 );
	h.load( src );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
TUT_TEARDOWN()


}


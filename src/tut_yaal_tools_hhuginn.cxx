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

#include <yaal/tools/filesystem.hxx>
#include <yaal/tools/hstringstream.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

namespace yaal {
namespace tools {
inline std::ostream& operator << ( std::ostream& out, HHuginn::type_t t_ ) {
	out << t_->name();
	return ( out );
}
}
}

namespace tut {

struct tut_yaal_tools_hhuginn : public simple_mock<tut_yaal_tools_hhuginn> {
	typedef char const* prog_src_t;
	hcore::HString _resultCache;
	HStringStream _sourceCache;
	tut_yaal_tools_hhuginn( void )
		: _resultCache(), _sourceCache() {
		return;
	}
	virtual ~tut_yaal_tools_hhuginn( void ) {}
	void test_preprocessing( prog_src_t, prog_src_t, int );
	void test_parse( prog_src_t, int const[3], int );
	void test_compile( prog_src_t, int const[3], int );
	void test_execute( prog_src_t, int const[3], int );
	void test_file( hcore::HString const& );
	hcore::HString const& execute( hcore::HString const& );
};

void tut_yaal_tools_hhuginn::test_file( hcore::HString const& name_ ) {
	filesystem::path_t p( "./data/" );
	p.append( name_ );
	HFile s( p, HFile::OPEN::READING );
	HHuginn h;
	s.read_until( _resultCache );
	_resultCache.shift_left( 2 );
	h.load( s );
	h.preprocess();
	h.parse();
	h.compile();
	h.execute();
	HHuginn::value_t res( h.result() );
	ENSURE_EQUALS( "bad result type", res->type(), HHuginn::TYPE::STRING );
	ENSURE_EQUALS( "bad result value", static_cast<HHuginn::HString*>( res.raw() )->value(), _resultCache );
	return;
}

hcore::HString const& tut_yaal_tools_hhuginn::execute( hcore::HString const& source_ ) {
	HHuginn h;
	_sourceCache.set_buffer( source_ );
	h.load( _sourceCache );
	h.preprocess();
	bool p( h.parse() );
	if ( !p ) {
		clog << h.error_message() << endl;
	}
	ENSURE( "parse failed", p );
	bool c( h.compile() );
	if ( !c ) {
		clog << h.error_message() << endl;
	}
	ENSURE( "compilation failed", c );
	bool e( h.execute() );
	if ( !e ) {
		clog << h.error_message() << endl;
	}
	ENSURE( "execution failed", e );
	HHuginn::value_t res( h.result() );
	ENSURE_EQUALS( "bad result type", res->type(), HHuginn::TYPE::STRING );
	_resultCache.assign( static_cast<HHuginn::HString*>( res.raw() )->value() );
	return ( _resultCache );
}

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn" );

TUT_UNIT_TEST( "grammar test" )
	HHuginn h;
	HRule hg( h.make_engine() );
	HGrammarDescription gd( hg );

	char const expected[][480] = {
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
		"expression = ( *( ( ( subscript | variableSetter ) >> '=' ) ^ '=' ) >> value )",
		"parameter = ( parameterIdentifier >> -( '=' >> expression ) )",
		"statement = ( ifStatement | whileStatement | forStatement | switchStatement | tryCatchStatement | throwStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope )",
		"subscript = ( reference >> +( subscriptOperator | functionCallOperator | memberAccess ) )",
		"variableSetter = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"value = ternary",
		"parameterIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"ifStatement = ( ifClause >> *( \"else\" >> ifClause ) >> -( \"else\" >> scope ) )",
		"whileStatement = ( \"while\" >> '(' >> expression >> ')' >> scope )",
		"forStatement = ( \"for\" >> '(' >> forIdentifier >> ':' >> expression >> ')' >> scope )",
		"switchStatement = ( \"switch\" >> '(' >> expression >> ')' >> '{' >> +caseStatement >> -defaultStatement >> '}' )",
		"tryCatchStatement = ( \"try\" >> scope >> +catchStatement )",
		"throwStatement = ( \"throw\" >> expression >> ';' )",
		"breakStatement = ( \"break\" >> ';' )",
		"continueStatement = ( \"continue\" >> ';' )",
		"returnStatement = ( \"return\" >> -( '(' >> expression >> ')' ) >> ';' )",
		"expressionStatement = ( expression >> ';' )",
		"reference = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"subscriptOperator = ( '[' >> ( ( ( rangeOper >> -argument ) | ( argument >> -( rangeOper >> -argument ) ) ) >> -( rangeOper >> -argument ) ) >> ']' )",
		"functionCallOperator = ( '(' >> -argList >> ')' )",
		"memberAccess = ( '.' >> member )",
		"ternary = ( ( booleanOr >> -( \"^^\" >> booleanOr ) ) >> -( '?' >> expression >> ':' >> expression ) )",
		"ifClause = ( \"if\" >> '(' >> expression >> ')' >> scope )",
		"forIdentifier = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"caseStatement = ( \"case\" >> '(' >> expression >> ')' >> ':' >> scope >> -breakStatement )",
		"defaultStatement = ( \"default\" >> ':' >> scope )",
		"catchStatement = ( \"catch\" >> '(' >> exceptionType >> exceptionVariable >> ')' >> scope )",
		"rangeOper = ':'",
		"argument = expression",
		"argList = ( argument >> *( ',' >> argument ) )",
		"member = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"booleanOr = ( booleanAnd >> *( \"||\" >> booleanAnd ) )",
		"exceptionType = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"exceptionVariable = regex( \"" YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END "\" )",
		"booleanAnd = ( equality >> *( \"&&\" >> equality ) )",
		"equality = ( compare >> -( ( \"==\" | \"!=\" ) >> compare ) )",
		"compare = ( sum >> -( ( \"<=\" | \">=\" | \"<\" | \">\" ) >> sum ) )",
		"sum = ( multiplication >> *( '+-' >> multiplication ) )",
		"multiplication = ( power >> *( '*/%' >> power ) )",
		"power = ( booleanNot >> *( '^' >> booleanNot ) )",
		"booleanNot = ( ( '!' >> negation ) | negation )",
		"negation = ( ( '-' >> atom ) | atom )",
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

char const progPre16[] =
	"#! /usr/bin/env huginn\n"
	"main(/* no arg */) {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progPost16[] =
	"main() {\n"
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
		progPre16,
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
		progPost16,
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

char const progParse9[] =
	"class A {\n"
	"}\n"
	"main() {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

void tut_yaal_tools_hhuginn::test_parse( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	clog << "parsing: " << index_ << endl;
	ENSURE_NOT( "parser invalid", h.parse() );
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
		progParse9,
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
		{ 10, 2, 1 },   // 9
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progParse ) ), * progEnd( end( progParse ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_parse( *prog, *e, static_cast<int>( prog - begin( progParse ) ) );
		}
	}
TUT_TEARDOWN()

char const progCompileErr0[] =
	"main() {\n"
	"\tx = 1 + 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr1[] =
	"main() {\n"
	"\tx = 1 - 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr2[] =
	"main() {\n"
	"\tx = 1 * 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr3[] =
	"main() {\n"
	"\tx = 1 / 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr4[] =
	"main() {\n"
	"\tx = 1 % 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr5[] =
	"main() {\n"
	"\tx = 1 ^ 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr6[] =
	"main() {\n"
	"\tx = 2 ^ 2 ^ 2.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr7[] =
	"main() {\n"
	"\tx = 2 ^ 2.5 ^ 2;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr8[] =
	"main() {\n"
	"\tx = 2.5 ^ 2 ^ 2;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr9[] =
	"main() {\n"
	"\tx = 1 == 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr10[] =
	"main() {\n"
	"\tx = 1 != 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr11[] =
	"main() {\n"
	"\tx = 1 < 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr12[] =
	"main() {\n"
	"\tx = 1 > 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr13[] =
	"main() {\n"
	"\tx = 1 <= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr14[] =
	"main() {\n"
	"\tx = 1 >= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr15[] =
	"main() {\n"
	"\tbreak;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr16[] =
	"main() {\n"
	"\tcontinue;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr17[] =
	"main() {\n"
	"\tx = 0;\n"
	"\tswitch( x ) {\n"
	"\t\tcase ( 1 ): {\n"
	"\t\t\tcontinue;\n"
	"\t\t} break;\n"
	"\t}\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr18[] =
	"main() {\n"
	"\tv = true;\n"
	"\tx = v < false;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr19[] =
	"main() {\n"
	"\tx = 'a' + 'b';\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr20[] =
	"main() {\n"
	"\tx = 'a' - 'b';\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr21[] =
	"main() {\n"
	"\tx = 'a' * 'b';\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr22[] =
	"main() {\n"
	"\tx = 'a' / 'b';\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr23[] =
	"main() {\n"
	"\tx = 'a' % 'b';\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr24[] =
	"main() {\n"
	"\tx = 'a' ^ 'b';\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr25[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v + 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr26[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v - 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr27[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v * 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr28[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v / 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr29[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v % 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr30[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v ^ 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr31[] =
	"main() {\n"
	"\tv = 2;\n"
	"\tx = v ^ 2.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr32[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v == 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr33[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v != 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr34[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v < 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr35[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v > 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr36[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v <= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr37[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v >= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr38[] =
	"main() {\n"
	"\tbreak;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr39[] =
	"main() {\n"
	"\tcontinue;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr40[] =
	"main() {\n" //9
	"\tx = 0;\n" //8
	"\tswitch ( x ) {\n" //16
	"\t\tcase ( 0 ): {\n" //16
	"\t\t\tcontinue;\n"
	"\t\t} break;\n"
	"\t}\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr41[] =
	"class A : B {_x=0;}\n"
	"class B : C {_y=0;}\n"
	"class C : A {_z=0;}\n"
	"main(){}"
;

char const progCompileErr42[] =
	"class A {_x=0;}\n"
	"class A {_y=0;}\n"
	"main(){}"
;

char const progCompileErr43[] =
	"class A : B {_x=0;}\n"
	"main(){}"
;

char const progCompileErr44[] =
	"integer() {}\n"
	"main(){}"
;

char const progCompileErr45[] =
	"class integer { _value = 0; }\n"
	"main(){}"
;

char const progCompileErr46[] =
	"f(x=0,y) {}\n"
	"main(){}"
;

char const progCompileErr47[] =
	"class A : integer {_x=0;}\n"
	"main(){}"
;

char const progCompileErr48[] =
	"class A { integer=0;}\n"
	"main(){}"
;

void tut_yaal_tools_hhuginn::test_compile( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	ENSURE( "failed to parse valid", h.parse() );
	clog << "compiling: " << index_ << endl;
	ENSURE_NOT( "compiled invalid", h.compile() );
	ENSURE_EQUALS( "reporting error position failed " + to_string( index_ ), h.error_position(), err_[0] );
	ENSURE_EQUALS( "reporting error line failed " + to_string( index_ ), h.error_coordinate().line(), err_[1] );
	ENSURE_EQUALS( "reporting error column failed " + to_string( index_ ), h.error_coordinate().column(), err_[2] );
	clog << h.error_message() << endl;
}

TUT_UNIT_TEST( "report compilation error" )
	prog_src_t progCompileErr[] = {
		progCompileErr0,
		progCompileErr1,
		progCompileErr2,
		progCompileErr3,
		progCompileErr4,
		progCompileErr5,
		progCompileErr6,
		progCompileErr7,
		progCompileErr8,
		progCompileErr9,
		progCompileErr10,
		progCompileErr11,
		progCompileErr12,
		progCompileErr13,
		progCompileErr14,
		progCompileErr15,
		progCompileErr16,
		progCompileErr17,
		progCompileErr18,
		progCompileErr19,
		progCompileErr20,
		progCompileErr21,
		progCompileErr22,
		progCompileErr23,
		progCompileErr24,
		progCompileErr25,
		progCompileErr26,
		progCompileErr27,
		progCompileErr28,
		progCompileErr29,
		progCompileErr30,
		progCompileErr31,
		progCompileErr32,
		progCompileErr33,
		progCompileErr34,
		progCompileErr35,
		progCompileErr36,
		progCompileErr37,
		progCompileErr38,
		progCompileErr39,
		progCompileErr40,
		progCompileErr41,
		progCompileErr42,
		progCompileErr43,
		progCompileErr44,
		progCompileErr45,
		progCompileErr46,
		progCompileErr47,
		progCompileErr48,
		NULL
	};
	int const err[][3] = {
		{ 16, 2, 8 },   // 0
		{ 16, 2, 8 },   // 1
		{ 16, 2, 8 },   // 2
		{ 16, 2, 8 },   // 3
		{ 16, 2, 8 },   // 4
		{ 16, 2, 8 },   // 5
		{ 20, 2, 12 },  // 6
		{ 22, 2, 14 },  // 7
		{ 18, 2, 10 },  // 8
		{ 16, 2, 8 },   // 9
		{ 16, 2, 8 },   // 10
		{ 16, 2, 8 },   // 11
		{ 16, 2, 8 },   // 12
		{ 16, 2, 8 },   // 13
		{ 16, 2, 8 },   // 14
		{ 10, 2, 2 },   // 15
		{ 10, 2, 2 },   // 16
		{ 51, 5, 4 },   // 17
		{ 27, 3, 8 },   // 18
		{ 18, 2, 10 },  // 19
		{ 18, 2, 10 },  // 20
		{ 18, 2, 10 },  // 21
		{ 18, 2, 10 },  // 22
		{ 18, 2, 10 },  // 23
		{ 18, 2, 10 },  // 24
		{ 24, 3, 8 },   // 25
		{ 24, 3, 8 },   // 26
		{ 24, 3, 8 },   // 27
		{ 24, 3, 8 },   // 28
		{ 24, 3, 8 },   // 29
		{ 24, 3, 8 },   // 30
		{ 24, 3, 8 },   // 31
		{ 24, 3, 8 },   // 32
		{ 24, 3, 8 },   // 33
		{ 24, 3, 8 },   // 34
		{ 24, 3, 8 },   // 35
		{ 24, 3, 8 },   // 36
		{ 24, 3, 8 },   // 37
		{ 10, 2, 2 },   // 38
		{ 10, 2, 2 },   // 39
		{ 52, 5, 4 },   // 40
		{ 10, 1, 11 },  // 41
		{ 22, 2, 7 },   // 42
		{ 10, 1, 11 },  // 43
		{ 0, 1, 1 },    // 44
		{ 6, 1, 7 },    // 45
		{ 7, 1, 8 },    // 46
		{ 10, 1, 11 },  // 47
		{ 10, 1, 11 },  // 48
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progCompileErr ) ), * progEnd( end( progCompileErr ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_compile( *prog, *e, static_cast<int>( prog - begin( progCompileErr ) ) );
		}
	}
TUT_TEARDOWN()

char const progExecuteErr0[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() + 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr1[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() - 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr2[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() * 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr3[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() / 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr4[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() % 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr5[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() ^ 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr6[] =
	"main() {\n"
	"\tv = @(){ return( 2 ); };\n"
	"\tx = v() ^ 2.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr7[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() == 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr8[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() != 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr9[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() < 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr10[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() > 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr11[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() <= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr12[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() >= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr13[] =
	"foo() {\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr14[] =
	"main() {\n"
	"\t{1:2,1.5:3};\n"
	"\treturn ( 0 );\n"
	"}\n"
;

void tut_yaal_tools_hhuginn::test_execute( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	ENSURE( "failed to parse valid", h.parse() );
	ENSURE( "failed to compile valid", h.compile() );
	clog << "executing: " << index_ << endl;
	ENSURE_NOT( "executed invalid", h.execute() );
	ENSURE_EQUALS( "reporting error position failed " + to_string( index_ ), h.error_position(), err_[0] );
	ENSURE_EQUALS( "reporting error line failed " + to_string( index_ ), h.error_coordinate().line(), err_[1] );
	ENSURE_EQUALS( "reporting error column failed " + to_string( index_ ), h.error_coordinate().column(), err_[2] );
	clog << h.error_message() << endl;
}

TUT_UNIT_TEST( "report execution error" )
	prog_src_t progExecuteErr[] = {
		progExecuteErr0,
		progExecuteErr1,
		progExecuteErr2,
		progExecuteErr3,
		progExecuteErr4,
		progExecuteErr5,
		progExecuteErr6,
		progExecuteErr7,
		progExecuteErr8,
		progExecuteErr9,
		progExecuteErr10,
		progExecuteErr11,
		progExecuteErr12,
		progExecuteErr13,
		progExecuteErr14,
		NULL
	};
	int const err[][3] = {
		{ 44, 3, 10 },   // 0
		{ 44, 3, 10 },   // 1
		{ 44, 3, 10 },   // 2
		{ 44, 3, 10 },   // 3
		{ 44, 3, 10 },   // 4
		{ 44, 3, 10 },   // 5
		{ 44, 3, 10 },   // 6
		{ 44, 3, 10 },   // 7
		{ 44, 3, 10 },   // 8
		{ 44, 3, 10 },   // 9
		{ 44, 3, 10 },   // 10
		{ 44, 3, 10 },   // 11
		{ 44, 3, 10 },   // 12
		{ 0, 1, 1 },     // 13
		{ 15, 2, 7 },    // 14
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progExecuteErr ) ), * progEnd( end( progExecuteErr ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_execute( *prog, *e, static_cast<int>( prog - begin( progExecuteErr ) ) );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::INTEGER );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::REAL );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::STRING );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::CHARACTER );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::INTEGER );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::INTEGER );
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
	ENSURE_EQUALS( "while failed", execute( "main(){x=list(1,2,3);s=0;for(e:x){s=s+e;}return(string(s));}" ), "6" );
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
	ENSURE_EQUALS(
		"set() failed",
		execute( "main(){x=set(2,\"ala\",3.14);x.add($7.34).add('Q');v=\"\";for(e:x){v=v+\"|\"+string(e);}return(v);}" ),
		"|7.34|2|Q|3.140000000000|ala"
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::INTEGER );
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::INTEGER );
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
	ENSURE_EQUALS( "destructor failed", execute( "class A{_d=none;constructor(d_){_d=d_;}destructor(){_d.add(\"ok\");}}main(){l=list();{o=A(l);}return(l[0]);}" ), "ok" );
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
			"main(){l=list();{o=D(l);}return(l[0]+l[1]);}"
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
			"f(x){\n"
			"if(x<0){\n"
			"throw Exception(\"neg arg\");\n"
			"}\n"
			"return(x*x);\n"
			"}\n"
			"main(){\n"
			"v=\"\";\n"
			"try{\n"
			"v=string(f(2));v=v+string(f(-2));v=v+\"end\";\n"
			"}\n"
			"catch(Exception e){\n"
			"v=v+e.what();\n"
			"}\n"
			"return(v);\n"
			"}\n"
		),
		"4neg arg"
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
	ENSURE_EQUALS( "bad result type", r->type(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<HHuginn::HInteger*>( r.raw() )->value(), 42 );
TUT_TEARDOWN()


}


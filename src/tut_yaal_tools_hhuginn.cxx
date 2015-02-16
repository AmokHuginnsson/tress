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
inline std::ostream& operator << ( std::ostream& out, HHuginn::TYPE t_ ) {
	out << HHuginn::HValue::type_name( t_ );
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
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compilation failed", h.compile() );
	ENSURE( "execution failed", h.execute() );
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

	char const expected[][370] = {
		"huginnGrammar = +( classDefinition | functionDefinition )",
		"classDefinition = ( \"class\" >> classIdentifier >> -( ':' >> baseIdentifier ) >> '{' >> +( field | functionDefinition ) >> '}' )",
		"functionDefinition = ( functionDefinitionIdentifier >> '(' >> -nameList >> ')' >> scope )",
		"classIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"baseIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"field = ( fieldIdentifier >> '=' >> expression >> ';' )",
		"functionDefinitionIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"nameList = ( parameter >> *( ',' >> parameter ) )",
		"scope = ( '{' >> *statement >> '}' )",
		"fieldIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"expression = ( *( ( ( subscript | variableSetter ) >> '=' ) ^ '=' ) >> value )",
		"parameter = ( parameterIdentifier >> -( '=' >> expression ) )",
		"statement = ( ifStatement | whileStatement | forStatement | switchStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope )",
		"subscript = ( reference >> +( subscriptOperator | functionCallOperator ) )",
		"variableSetter = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"value = ternary",
		"parameterIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"ifStatement = ( ifClause >> *( \"else\" >> ifClause ) >> -( \"else\" >> scope ) )",
		"whileStatement = ( \"while\" >> '(' >> expression >> ')' >> scope )",
		"forStatement = ( \"for\" >> '(' >> forIdentifier >> ':' >> expression >> ')' >> scope )",
		"switchStatement = ( \"switch\" >> '(' >> expression >> ')' >> '{' >> +caseStatement >> -defaultStatement >> '}' )",
		"breakStatement = ( \"break\" >> ';' )",
		"continueStatement = ( \"continue\" >> ';' )",
		"returnStatement = ( \"return\" >> -( '(' >> expression >> ')' ) >> ';' )",
		"expressionStatement = ( expression >> ';' )",
		"reference = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"subscriptOperator = ( '[' >> expression >> ']' )",
		"functionCallOperator = ( '(' >> -argList >> ')' )",
		"ternary = ( ( booleanOr >> -( \"^^\" >> booleanOr ) ) >> -( '?' >> expression >> ':' >> expression ) )",
		"ifClause = ( \"if\" >> '(' >> expression >> ')' >> scope )",
		"forIdentifier = regex( \"\\<[a-zA-Z_][a-zA-Z0-9_]*\\>\" )",
		"caseStatement = ( \"case\" >> '(' >> expression >> ')' >> ':' >> scope >> -breakStatement )",
		"defaultStatement = ( \"default\" >> ':' >> scope )",
		"argList = ( argument >> *( ',' >> argument ) )",
		"booleanOr = ( booleanAnd >> *( \"||\" >> booleanAnd ) )",
		"argument = expression",
		"booleanAnd = ( equality >> *( \"&&\" >> equality ) )",
		"equality = ( compare >> -( ( \"==\" | \"!=\" ) >> compare ) )",
		"compare = ( sum >> -( ( \"<=\" | \">=\" | \"<\" | \">\" ) >> sum ) )",
		"sum = ( multiplication >> *( '+-' >> multiplication ) )",
		"multiplication = ( power >> *( '*/%' >> power ) )",
		"power = ( booleanNot >> *( '^' >> booleanNot ) )",
		"booleanNot = ( ( '!' >> negation ) | negation )",
		"negation = ( ( '-' >> atom ) | atom )",
		"atom = ( absoluteValue | parenthesis | real | numberLiteral | integer | character_literal | ( listLiteral >> -( subscriptOperator >> *( subscriptOperator | functionCallOperator ) ) ) | ( mapLiteral >> -( subscriptOperator >> *( subscriptOperator | functionCallOperator ) ) ) | none | true | false | dereference | ( stringLiteral >> -subscriptOperator ) | lambda )",
		"absoluteValue = ( '|' >> expression >> '|' )",
		"parenthesis = ( '(' >> expression >> ')' )",
		"numberLiteral = ( '$' >> real )",
		"listLiteral = ( '[' >> -argList >> ']' )",
		"mapLiteral = ( '{' >> -( mapLiteralElement >> *( ',' >> mapLiteralElement ) ) >> '}' )",
		"none = \"none\"",
		"true = \"true\"",
		"false = \"false\"",
		"dereference = ( reference >> *( subscriptOperator | functionCallOperator ) )",
		"stringLiteral = string_literal",
		"lambda = ( '@' >> '(' >> -nameList >> ')' >> scope )",
		"mapLiteralElement = ( argument >> ':' >> argument )"
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
	"\tv = 1;\n"
	"\tx = v + 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr1[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v - 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr2[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v * 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr3[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v / 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr4[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v % 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr5[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v ^ 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr6[] =
	"main() {\n"
	"\tv = 2;\n"
	"\tx = v ^ 2.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr7[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v == 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr8[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v != 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr9[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v < 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr10[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tx = v > 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr11[] =
	"foo() {\n"
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
		NULL
	};
	int const err[][3] = {
		{ 24, 3, 8 },   // 0
		{ 24, 3, 8 },   // 1
		{ 24, 3, 8 },   // 2
		{ 24, 3, 8 },   // 3
		{ 24, 3, 8 },   // 4
		{ 24, 3, 8 },   // 5
		{ 24, 3, 8 },   // 6
		{ 24, 3, 8 },   // 7
		{ 24, 3, 8 },   // 8
		{ 24, 3, 8 },   // 9
		{ 24, 3, 8 },   // 10
		{ 0, 1, 1 },    // 11
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

TUT_UNIT_TEST( "list()" )
	ENSURE_EQUALS( "list failed (explicit)", execute( "main(){x=list(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ), "3abc" );
	ENSURE_EQUALS( "list failed (literal)", execute( "main(){x=[\"a\",\"b\",\"c\"];v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ), "3abc" );
	ENSURE_EQUALS( "list failed (crazy)", execute( "f(a){return(\"X\"+a+\"X\");}main(){return([f][0](\"hi\"));}" ), "XhiX" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "map()" )
	ENSURE_EQUALS( "map() failed (explicit)", execute( "main(){x=map();x[\"Ala\"]=0;x[\"ma\"]=1;x[\"kota.\"]=2;v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ), "Ala0kota.2ma1" );
	ENSURE_EQUALS( "map() failed (literal)", execute( "main(){x=map();x={\"Ala\":0,\"ma\":1,\"kota.\":2};v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ), "Ala0kota.2ma1" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript" )
	ENSURE_EQUALS( "subscript failed", execute( "main(){x=list(1,2,3);return(string(x[1]));}" ), "2" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript repeat" )
	ENSURE_EQUALS( "subscript repeat failed", execute( "main(){x=list(list(11,12,13),list(21,22,23),list(31,32,33));return(string(x[1][1]));}" ), "22" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "function ref" )
	ENSURE_EQUALS( "function ref failed", execute( "f(){return(\"x\");}g(){return(f);}main(){return(g()());}" ), "x" );
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


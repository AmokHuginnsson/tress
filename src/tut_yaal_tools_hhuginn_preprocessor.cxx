/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_preprocessor.cxx - this file is integral part of `tress' project.

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

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_preprocessor : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_preprocessor( void ) {}
	void test_preprocessing( prog_src_t, prog_src_t, int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_preprocessor, "yaal::tools::HHuginn,preprocessor" );

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

void tut_yaal_tools_hhuginn_preprocessor::test_preprocessing( prog_src_t pre_, prog_src_t post_, int index_ ) {
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

TUT_UNIT_TEST( "comments" )
	char const srcRaw[] =
		"/*\n"
		" * My class Foo,\n"
		" * a nice doc."
		" */\n"
		"class Foo {\n"
		"// Some uninitialized data...\n"
		"_x = none;\n"
		"}\n";
	HHuginn h;
	HStringStream src( srcRaw );
	h.load( src );
	h.preprocess();
	ENSURE( "parsing docs filed", h.parse() );
	ENSURE( "compilation of docs failed", h.compile( HHuginn::COMPILER::BE_SLOPPY ) );
	HStringStream doc;
	h.dump_docs( doc );
	HString line;
	char const expected[][48] = {
		"Foo:My class Foo, a nice doc.",
		"Foo._x:Some uninitialized data..."
	};
	int i( 0 );
	while ( getline( doc, line ).good() ) {
		if ( line.find( "Foo" ) != HString::npos ) {
			ENSURE_EQUALS( "setting doc failed", line, expected[i] );
			++ i;
		}
	}
TUT_TEARDOWN()

}


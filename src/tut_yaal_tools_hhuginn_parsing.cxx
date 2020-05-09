/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_parsing : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_parsing( void ) {}
	void test_parse( prog_src_t, ErrInfo const&, int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_parsing, "yaal::tools::HHuginn,parsing" );

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
	"~main() {\n"
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

char const progParse10[] =
	"classA {\n"
	"\t_data = none;\n"
	"}\n"
	"main() {\n"
	"\treturn ( A() );\n"
	"}\n"
;

char const progParse11[] =
	"main() {\n"
	"#     \n"
	"}\n"
;

char const progParse12[] =
	"main() {\n"
	"    #\n"
	"}\n"
;

char const progParse13[] =
	"main() {\n"
	"\t\"\n"
	"}\n"
;

char const progParse14[] =
	"f(a, b..., c) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse15[] =
	"f(a, b... = 0) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse16[] =
	"f(a, b:::, c) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse17[] =
	"f(a, b::: = 0) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse18[] =
	"f(a, b:::, c...) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse19[] =
	"f(a, b..., c...) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse20[] =
	"f(a, b:::, c:::) {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progParse21[] =
	"main() {\n"
	"$ 2;\n"
	"}\n"
;

void tut_yaal_tools_hhuginn_parsing::test_parse( prog_src_t prog_, ErrInfo const& err_, int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	clog << "parsing: " << index_ << endl;
	ENSURE_NOT( "parsed invalid", h.parse() );
	ENSURE_EQUALS( "reporting error position failed " + to_string( index_ ), h.error_position(), err_._pos );
	ENSURE_EQUALS( "reporting error line failed " + to_string( index_ ), h.error_coordinate().line(), err_._line );
	ENSURE_EQUALS( "reporting error column failed " + to_string( index_ ), h.error_coordinate().column(), err_._col );
	ENSURE_EQUALS( "reporting error message failed " + to_string( index_ ), h.error_message(), err_._msg );
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
		progParse10,
		progParse11,
		progParse12,
		progParse13,
		progParse14,
		progParse15,
		progParse16,
		progParse17,
		progParse18,
		progParse19,
		progParse20,
		progParse21,
		nullptr
	};
	ErrInfo const err[] = {
		/*  0 */ { 17, 2, 9, "*anonymous stream*:2:9: expected one of characters: (" },
		/*  1 */ { 29, 2, 9, "*anonymous stream*:2:9: expected one of characters: (" },
		/*  2 */ { 63, 6, 9, "*anonymous stream*:6:9: expected one of characters: (" },
		/*  3 */ { 0, 1, 1, "*anonymous stream*:1:1: expected string: \"class\"" },
		/*  4 */ { 29, 2, 21, "*anonymous stream*:2:21: expected one of characters: (" },
		/*  5 */ { 17, 2, 9, "*anonymous stream*:2:9: expected one of characters: (" },
		/*  6 */ { 29, 2, 21, "*anonymous stream*:2:21: expected one of characters: (" },
		/*  7 */ { 8, 1, 9, "*anonymous stream*:1:9: expected string: \"if\"" },
		/*  8 */ { 9, 2, 1, "*anonymous stream*:2:1: expected string: \"if\"" },
		/*  9 */ { 10, 2, 1, "*anonymous stream*:2:1: expected a fieldIdentifier" },
		/* 10 */ { 7, 1, 8, "*anonymous stream*:1:8: expected one of characters: (" },
		/* 11 */ { 9, 2, 1, "*anonymous stream*:2:1: expected string: \"if\"" },
		/* 12 */ { 13, 2, 5, "*anonymous stream*:2:5: expected string: \"if\"" },
		/* 13 */ { 11, 2, 3, "*anonymous stream*:2:3: expected literal string" },
		/* 14 */ { 12, 1, 13, "*anonymous stream*:1:13: expected string: \":::\"" },
		/* 15 */ { 10, 1, 11, "*anonymous stream*:1:11: expected one of characters: ," },
		/* 16 */ { 9, 1, 10, "*anonymous stream*:1:10: expected one of characters: )" },
		/* 17 */ { 10, 1, 11, "*anonymous stream*:1:11: expected one of characters: )" },
		/* 18 */ { 9, 1, 10, "*anonymous stream*:1:10: expected one of characters: )" },
		/* 19 */ { 12, 1, 13, "*anonymous stream*:1:13: expected string: \":::\"" },
		/* 20 */ { 9, 1, 10, "*anonymous stream*:1:10: expected one of characters: )" },
		/* 21 */ { 10, 2, 2, "*anonymous stream*:2:2: expected real number" },
		/**/ { 0, 0, 0, nullptr }
	};
	ErrInfo const* e( err );
	for ( prog_src_t* prog( begin( progParse ) ), * progEnd( end( progParse ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_parse( *prog, *e, static_cast<int>( prog - begin( progParse ) ) );
		}
	}
TUT_TEARDOWN()

}


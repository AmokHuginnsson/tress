/* Read tress/LICENSE.md file for copyright and licensing information. */

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

struct tut_yaal_tools_hhuginn_parsing : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_parsing( void ) {}
	void test_parse( prog_src_t, int const[3], int );
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

void tut_yaal_tools_hhuginn_parsing::test_parse( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	clog << "parsing: " << index_ << endl;
	ENSURE_NOT( "parsed invalid", h.parse() );
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
		{ 10, 2, 1 },  // 9
		{ 7, 1, 8 },   // 10
		{ 9, 2, 1 },   // 11
		{ 13, 2, 5 },  // 12
		{ 11, 2, 3 },  // 13
		{ 12, 1, 13 }, // 14
		{ 10, 1, 11 }, // 15
		{ 9, 1, 10 },  // 16
		{ 10, 1, 11 }, // 17
		{ 9, 1, 10 },  // 18
		{ 12, 1, 13 }, // 19
		{ 9, 1, 10 },  // 20
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progParse ) ), * progEnd( end( progParse ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_parse( *prog, *e, static_cast<int>( prog - begin( progParse ) ) );
		}
	}
TUT_TEARDOWN()

}


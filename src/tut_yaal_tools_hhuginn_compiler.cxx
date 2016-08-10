/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_compiler.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_hhuginn_compiler : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_compiler( void ) {}
	void test_compile( prog_src_t, int const[3], int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_compiler, "yaal::tools::HHuginn,compiler" );

void tut_yaal_tools_hhuginn_compiler::test_compile( prog_src_t prog_, int const err_[3], int index_ ) {
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
	"main( a, b, a ) {\n"
	"\treturn ( a + b );"
	"}"
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
	"class A { integer=0; }\n"
	"main(){}"
;

char const progCompileErr49[] =
	"main(){\n"
	"x = return;"
	"}"
;

char const progCompileErr50[] =
	"main(){\n"
	"x = this;"
	"}"
;

char const progCompileErr51[] =
	"main(){\n"
	"x = y.return;"
	"}"
;

char const progCompileErr52[] =
	"main(){\n"
	"x = y.constructor;"
	"}"
;

char const progCompileErr53[] =
	"main(){\n"
	"if = 0;\n"
	"}"
;

char const progCompileErr54[] =
	"main(){\n"
	"f() = 0;\n"
	"}"
;

char const progCompileErr55[] =
	"main(){\n"
	"if ( ! 1 ) {\n"
	"}\n"
	"}"
;

char const progCompileErr56[] =
	"main(){\n"
	"return (|'Q'|);\n"
	"}"
;

char const progCompileErr57[] =
	"main(){\n"
	"return (-'Q');\n"
	"}"
;

char const progCompileErr58[] =
	"main(){\n"
	"return ( assert.field );\n"
	"}"
;

char const progCompileErr59[] =
	"main(){\n"
	"return ( assert[0] );\n"
	"}"
;

char const progCompileErr60[] =
	"main(){\n"
	"return ( x[0:'q'] );\n"
	"}"
;

char const progCompileErr61[] =
	"class A {\n"
	"_x=0;\n"
	"_x=0;\n"
	"}\n"
	"main(){}"
;

char const progCompileErr62[] =
	"main(){\n"
	"return ( 'q' ? 0 : 1 );\n"
	"}"
;

char const progCompileErr63[] =
	"main(){\n"
	"return ( ( x == 0 ) && 1 );\n"
	"}"
;

char const progCompileErr64[] =
	"import return as pck;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr65[] =
	"class Package {_x = none;}\n"
	"import Package as pck;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr66[] =
	"import Algorithms as pck;\n"
	"import Algorithms as pckNew;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr67[] =
	"import Algorithms as pck;\n"
	"class Algorithms {_x = none;}\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr68[] =
	"import Algorithms as pck;\n"
	"class pck {_x = none;}\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr69[] =
	"import NonExisting as nonExisting;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr70[] =
	"import Algorithms as return;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr71[] =
	"class pck {_x = none;}\n"
	"import Algorithms as pck;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;

char const progCompileErr72[] =
	"import Algorithms as pck;\n"
	"import Cryptography as pck;\n"
	"main(){\n"
	"return ( 0 );\n"
	"}"
;


char const progCompileErr73[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tv += 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr74[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tv -= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr75[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tv *= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr76[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tv /= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr77[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tv %= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr78[] =
	"main() {\n"
	"\tv = 1;\n"
	"\tv ^= 1.5;\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progCompileErr79[] =
	"main() {\n"
	"\tx = y;\n"
	"\ty = 0;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progCompileErr80[] =
	"main() {\n"
	"\tx += 2;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progCompileErr81[] =
	"class A {\n"
	"\t_x = a;\n"
	"}\n"
	"main() {\n"
	"\treturn ( A() );\n"
	"}\n"
;

char const progCompileErr82[] =
	"class A {\n"
	"\t_x = ( a = 0 );\n"
	"}\n"
	"main() {\n"
	"\treturn ( A() );\n"
	"}\n"
;

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
		progCompileErr49,
		progCompileErr50,
		progCompileErr51,
		progCompileErr52,
		progCompileErr53,
		progCompileErr54,
		progCompileErr55,
		progCompileErr56,
		progCompileErr57,
		progCompileErr58,
		progCompileErr59,
		progCompileErr60,
		progCompileErr61,
		progCompileErr62,
		progCompileErr63,
		progCompileErr64,
		progCompileErr65,
		progCompileErr66,
		progCompileErr67,
		progCompileErr68,
		progCompileErr69,
		progCompileErr70,
		progCompileErr71,
		progCompileErr72,
		progCompileErr73,
		progCompileErr74,
		progCompileErr75,
		progCompileErr76,
		progCompileErr77,
		progCompileErr78,
		progCompileErr79,
		progCompileErr80,
		progCompileErr81,
		progCompileErr82,
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
		{ 12, 1, 13 },  // 41
		{ 22, 2, 7 },   // 42
		{ 10, 1, 11 },  // 43
		{ 0, 1, 1 },    // 44
		{ 6, 1, 7 },    // 45
		{ 7, 1, 8 },    // 46
		{ 10, 1, 11 },  // 47
		{ 10, 1, 11 },  // 48
		{ 12, 2, 5 },   // 49
		{ 12, 2, 5 },   // 50
		{ 14, 2, 7 },   // 51
		{ 14, 2, 7 },   // 52
		{ 8, 2, 1 },    // 53
		{ 8, 2, 1 },    // 54
		{ 13, 2, 6 },   // 55
		{ 16, 2, 9 },   // 56
		{ 16, 2, 9 },   // 57
		{ 23, 2, 16 },  // 58
		{ 23, 2, 16 },  // 59
		{ 21, 2, 14 },  // 60
		{ 16, 3, 1 },   // 61
		{ 21, 2, 14 },  // 62
		{ 28, 2, 21 },  // 63
		{ 7, 1, 8 },    // 64
		{ 34, 2, 8 },   // 65
		{ 26, 2, 1 },   // 66
		{ 32, 2, 7 },   // 67
		{ 32, 2, 7 },   // 68
		{ 7, 1, 8 },    // 69
		{ 21, 1, 22 },  // 70
		{ 44, 2, 22 },  // 71
		{ 26, 2, 1 },   // 72
		{ 20, 3, 4 },   // 73
		{ 20, 3, 4 },   // 74
		{ 20, 3, 4 },   // 75
		{ 20, 3, 4 },   // 76
		{ 20, 3, 4 },   // 77
		{ 20, 3, 4 },   // 78
		{ 14, 2, 6 },   // 79
		{ 10, 2, 2 },   // 80
		{ 16, 2, 7 },   // 81
		{ 18, 2, 9 },   // 82
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progCompileErr ) ), * progEnd( end( progCompileErr ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_compile( *prog, *e, static_cast<int>( prog - begin( progCompileErr ) ) );
		}
	}
TUT_TEARDOWN()


TUT_UNIT_TEST( "detect derivation cycle" )
	char const code[] =
		"class A : B {_x=0;}\n"
		"class B : C {_y=0;}\n"
		"class C : A {_z=0;}\n"
		"main(){}"
	;
	HStringStream prog( code );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	ENSURE( "failed to parse valid", h.parse() );
	ENSURE_NOT( "compiled invalid", h.compile() );
	ENSURE( "reporting error position failed", ( h.error_position() == 10 ) || ( h.error_position() == 30 ) || ( h.error_position() == 50 ) );
	ENSURE( "reporting error line failed", ( h.error_coordinate().line() == 1 ) || ( h.error_coordinate().line() == 2 ) || ( h.error_coordinate().line() == 3 ) );
	ENSURE_EQUALS( "reporting error column failed", h.error_coordinate().column(), 11 );
	clog << h.error_message() << endl;
TUT_TEARDOWN()

}


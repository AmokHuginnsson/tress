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

#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct ErrInfo {
	int _pos;
	int _line;
	int _col;
	char const* _msg;
};

struct tut_yaal_tools_hhuginn_compiler : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_compiler( void ) {}
	void test_compile( prog_src_t, ErrInfo const&, int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_compiler, "yaal::tools::HHuginn,compiler" );

void tut_yaal_tools_hhuginn_compiler::test_compile( prog_src_t prog_, ErrInfo const& err_, int index_ ) {
	if ( setup._verbose && setup._debug ) {
		clog << "// HUGINN TEST CASE START" << endl;
		clog << prog_ << endl;
		clog << "// HUGINN TEST CASE FINISH" << endl;
	}
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
	h.preprocess();
	ENSURE( "failed to parse valid", h.parse() );
	clog << "compiling: " << index_ << endl;
	ENSURE_NOT( "compiled invalid", h.compile( { "./data" } ) );
	ENSURE_EQUALS( "reporting error position failed " + to_string( index_ ), h.error_position(), err_._pos );
	ENSURE_EQUALS( "reporting error line failed " + to_string( index_ ), h.error_coordinate().line(), err_._line );
	ENSURE_EQUALS( "reporting error column failed " + to_string( index_ ), h.error_coordinate().column(), err_._col );
	ENSURE_EQUALS( "reporting error message failed " + to_string( index_ ), h.error_message(), err_._msg );
	clog << h.error_message() << endl;
}

char const progCompile0[] =
	"import Algorithms as algo;\n"
	"class Base {\n"
	"\tfoo() {\n"
	"\t}\n"
	"\tbar() {\n"
	"\t}\n"
	"}\n"
	"class Derived : Base {\n"
	"\tfoo() {\n"
	"\t}\n"
	"\tbaz() {\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\treturn ( [ algo, Derived().foo().bar().baz() ] );\n"
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

char const progCompileErr83[] =
	"import Algorithms as algo;\n"
	"main() {\n"
	"\treturn ( Algorithms() + algo );\n"
	"}\n"
;

char const progCompileErr84[] =
	"main() {\n"
	"\tx = x;\n"
	"}\n"
;

char const progCompileErr85[] =
	"main() {\n"
	"\tx = y = z = x;\n"
	"\tx = y + z;\n"
	"}\n"
;

char const progCompileErr86[] =
	"main() {\n"
	"\tx = y = z = ( x + 0 );\n"
	"\tx = y + z;\n"
	"}\n"
;

char const progCompileErr87[] =
	"class A {\n"
	"\tx = 0;\n"
	"\tdo( x ) {\n"
	"\t\tx;\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\ta = A();\n"
	"\ta.do();\n"
	"}\n"
;

char const progCompileErr88[] =
	"class A {\n"
	"\tx = 0;\n"
	"}\n"
	"class B : A {\n"
	"\tdo( x ) {\n"
	"\t\tx;\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\ta = B();\n"
	"\ta.do();\n"
	"}\n"
;

char const progCompileErr89[] =
	"main() {\n"
	"}\n"
	"main() {\n"
	"}\n"
;

char const progCompileErr90[] =
	"class main {\n"
	"\t_x = none;\n"
	"}\n"
	"main() {\n"
	"\treturn ( main()._x );\n"
	"}\n"
;

char const progCompileErr91[] =
	"main() {\n"
	"\ta=0;\n"
	"\tb=@[a,a](){a;};\n"
	"\treturn ( b );\n"
	"}\n"
;

char const progCompileErr92[] =
	"main() {\n"
	"\ta=0;\n"
	"\tb=@[a](a){a;};\n"
	"\treturn ( b );\n"
	"}\n"
;

char const progCompileErr93[] =
	"main() {\n"
	"x=0;\n"
	"}\n"
;

char const progCompileErr94[] =
	"class C{constructor(){}}\n"
	"main() {\n"
	"}\n"
;

char const progCompileErr95[] =
	"class C{_x=none;}\n"
	"main() {\n"
	"C();\n"
	"}\n"
;

char const progCompileErr96[] =
	"f(){}\n"
	"main() {\n"
	"}\n"
;

char const progCompileErr97[] =
	"import Algorithms as algo;\n"
	"main() {\n"
	"}\n"
;

char const progCompileErr98[] =
	"main() {\n"
	"return;\n"
	"return;\n"
	"}\n"
;

char const progCompileErr99[] =
	"main() {\n"
	"'a'!;\n"
	"}\n"
;

char const progCompileErr100[] =
	"main() {\n"
	"x='a';\n"
	"x+='a';\n"
	"}\n"
;

char const progCompileErr101[] =
	"main() {\n"
	"x='a';\n"
	"x*='a';\n"
	"}\n"
;


char const progCompileErr102[] =
	"import CannotParse as cp;\n"
	"main() {\n"
	"foo();\n"
	"}\n"
;

char const progCompileErr103[] =
	"import CannotCompile as cc;\n"
	"main() {\n"
	"foo();\n"
	"}\n"
;

char const progCompileErr104[] =
	"f( a, b = 0, c, d... ) {}\n"
	"main(){}"
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
		progCompileErr83,
		progCompileErr84,
		progCompileErr85,
		progCompileErr86,
		progCompileErr87,
		progCompileErr88,
		progCompileErr89,
		progCompileErr90,
		progCompileErr91,
		progCompileErr92,
		progCompileErr93,
		progCompileErr94,
		progCompileErr95,
		progCompileErr96,
		progCompileErr97,
		progCompileErr98,
		progCompileErr99,
		progCompileErr100,
		progCompileErr101,
		progCompileErr102,
		progCompileErr103,
		progCompileErr104,
		NULL
	};

	ErrInfo const err[] = {
/*   0 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `+' do not match: `integer' vs `real'." },
/*   1 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `-' do not match: `integer' vs `real'." },
/*   2 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `*' do not match: `integer' vs `real'." },
/*   3 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `/' do not match: `integer' vs `real'." },
/*   4 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `%' do not match: `integer' vs `real'." },
/*   5 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `^' do not match: `integer' vs `real'." },
/*   6 */ { 20, 2, 12, "*anonymous stream*:2:12: Operand types for `^' do not match: `integer' vs `real'." },
/*   7 */ { 22, 2, 14, "*anonymous stream*:2:14: Operand types for `^' do not match: `real' vs `integer'." },
/*   8 */ { 18, 2, 10, "*anonymous stream*:2:10: Operand types for `^' do not match: `real' vs `integer'." },
/*   9 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `==' do not match: `integer' vs `real'." },
/*  10 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `!=' do not match: `integer' vs `real'." },
/*  11 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `<' do not match: `integer' vs `real'." },
/*  12 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `>' do not match: `integer' vs `real'." },
/*  13 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `<=' do not match: `integer' vs `real'." },
/*  14 */ { 16, 2, 8,  "*anonymous stream*:2:8: Operand types for `>=' do not match: `integer' vs `real'." },
/*  15 */ { 10, 2, 2,  "*anonymous stream*:2:2: Invalid context for `break' statement." },
/*  16 */ { 10, 2, 2,  "*anonymous stream*:2:2: Invalid context for `continue' statement." },
/*  17 */ { 51, 5, 4,  "*anonymous stream*:5:4: Invalid context for `continue' statement." },
/*  18 */ { 27, 3, 8,  "*anonymous stream*:3:8: Operands are not comparable: boolean, boolean" },
/*  19 */ { 18, 2, 10, "*anonymous stream*:2:10: Operands are not summable: character, character" },
/*  20 */ { 18, 2, 10, "*anonymous stream*:2:10: Operands are not subtractable: character, character" },
/*  21 */ { 18, 2, 10, "*anonymous stream*:2:10: Operands are not multipliable: character, character" },
/*  22 */ { 18, 2, 10, "*anonymous stream*:2:10: Operands are not divisible: character, character" },
/*  23 */ { 18, 2, 10, "*anonymous stream*:2:10: Operands are not divisible: character, character" },
/*  24 */ { 18, 2, 10, "*anonymous stream*:2:10: Operands are not exponentiationable: character, character" },
/*  25 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `+' do not match: `integer' vs `real'." },
/*  26 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `-' do not match: `integer' vs `real'." },
/*  27 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `*' do not match: `integer' vs `real'." },
/*  28 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `/' do not match: `integer' vs `real'." },
/*  29 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `%' do not match: `integer' vs `real'." },
/*  30 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `^' do not match: `integer' vs `real'." },
/*  31 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `^' do not match: `integer' vs `real'." },
/*  32 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `==' do not match: `integer' vs `real'." },
/*  33 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `!=' do not match: `integer' vs `real'." },
/*  34 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `<' do not match: `integer' vs `real'." },
/*  35 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `>' do not match: `integer' vs `real'." },
/*  36 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `<=' do not match: `integer' vs `real'." },
/*  37 */ { 24, 3, 8,  "*anonymous stream*:3:8: Operand types for `>=' do not match: `integer' vs `real'." },
/*  38 */ { 10, 2, 2,  "*anonymous stream*:2:2: Invalid context for `break' statement." },
/*  39 */ { 10, 2, 2,  "*anonymous stream*:2:2: Invalid context for `continue' statement." },
/*  40 */ { 52, 5, 4,  "*anonymous stream*:5:4: Invalid context for `continue' statement." },
/*  41 */ { 12, 1, 13, "*anonymous stream*:1:13: Parameter `a' was already defined." },
/*  42 */ { 22, 2, 7,  "*anonymous stream*:2:7: Class `A' is already defined." },
/*  43 */ { 10, 1, 11, "*anonymous stream*:1:11: Base class `B' was not defined." },
/*  44 */ { 0, 1, 1,   "*anonymous stream*:1:1: `integer' is a restricted name." },
/*  45 */ { 6, 1, 7,   "*anonymous stream*:1:7: `integer' is a restricted name." },
/*  46 */ { 6, 1, 7,   "*anonymous stream*:1:7: Missing default argument." },
/*  47 */ { 10, 1, 11, "*anonymous stream*:1:11: `integer' is a restricted keyword." },
/*  48 */ { 10, 1, 11, "*anonymous stream*:1:11: `integer' is a restricted name." },
/*  49 */ { 12, 2, 5,  "*anonymous stream*:2:5: `return' is a restricted keyword." },
/*  50 */ { 12, 2, 5,  "*anonymous stream*:2:5: Keyword `this' can be used only in class context." },
/*  51 */ { 14, 2, 7,  "*anonymous stream*:2:7: `return' is a restricted keyword." },
/*  52 */ { 14, 2, 7,  "*anonymous stream*:2:7: Keyword `constructor' can be used only in class context." },
/*  53 */ { 8, 2, 1,   "*anonymous stream*:2:1: `if' is a restricted name." },
/*  54 */ { 8, 2, 1,   "*anonymous stream*:2:1: Assignment to function result." },
/*  55 */ { 13, 2, 6,  "*anonymous stream*:2:6: Operand is not a boolean value: integer" },
/*  56 */ { 16, 2, 9,  "*anonymous stream*:2:9: Operand is not a numeric value: character" },
/*  57 */ { 16, 2, 9,  "*anonymous stream*:2:9: Operand is not a numeric value: character" },
/*  58 */ { 23, 2, 16, "*anonymous stream*:2:16: `assert' is a restricted keyword." },
/*  59 */ { 23, 2, 16, "*anonymous stream*:2:16: `assert' is a restricted keyword." },
/*  60 */ { 21, 2, 14, "*anonymous stream*:2:14: Range specifier is not an integer." },
/*  61 */ { 16, 3, 1,  "*anonymous stream*:3:1: Field `_x' is already defined in `A'." },
/*  62 */ { 21, 2, 14, "*anonymous stream*:2:14: Operand is not a boolean value: character" },
/*  63 */ { 28, 2, 21, "*anonymous stream*:2:21: Operands are not boolean values: boolean, integer" },
/*  64 */ { 7, 1, 8,   "*anonymous stream*:1:8: `return' is a restricted name." },
/*  65 */ { 34, 2, 8,  "*anonymous stream*:2:8: Class `Package' named is already defined." },
/*  66 */ { 33, 2, 8,  "*anonymous stream*:2:8: Package `Algorithms' was already imported." },
/*  67 */ { 32, 2, 7,  "*anonymous stream*:2:7: Package of the same name `Algorithms' is already imported." },
/*  68 */ { 32, 2, 7,  "*anonymous stream*:2:7: Package alias of the same name `pck' is already defined." },
/*  69 */ { 7, 1, 8,   "*anonymous stream*:1:8: Package `NonExisting' does not exist." },
/*  70 */ { 21, 1, 22, "*anonymous stream*:1:22: `return' is a restricted name." },
/*  71 */ { 44, 2, 22, "*anonymous stream*:2:22: Class `pck' named is already defined." },
/*  72 */ { 49, 2, 24, "*anonymous stream*:2:24: Import alias `pck' is already defined." },
/*  73 */ { 20, 3, 4,  "*anonymous stream*:3:4: Operand types for `+=' do not match: `integer' vs `real'." },
/*  74 */ { 20, 3, 4,  "*anonymous stream*:3:4: Operand types for `-=' do not match: `integer' vs `real'." },
/*  75 */ { 20, 3, 4,  "*anonymous stream*:3:4: Operand types for `*=' do not match: `integer' vs `real'." },
/*  76 */ { 20, 3, 4,  "*anonymous stream*:3:4: Operand types for `/=' do not match: `integer' vs `real'." },
/*  77 */ { 20, 3, 4,  "*anonymous stream*:3:4: Operand types for `%=' do not match: `integer' vs `real'." },
/*  78 */ { 20, 3, 4,  "*anonymous stream*:3:4: Operand types for `^=' do not match: `integer' vs `real'." },
/*  79 */ { 14, 2, 6,  "*anonymous stream*:2:6: Symbol `y' is not defined in this context (did you mean `x'?)." },
/*  80 */ { 10, 2, 2,  "*anonymous stream*:2:2: Symbol `x' is not defined in this context (did you mean `use'?)." },
/*  81 */ { 16, 2, 7,  "*anonymous stream*:2:7: Dereferencing symbol `a' in field definition is forbidden." },
/*  82 */ { 18, 2, 9,  "*anonymous stream*:2:9: Defining symbol `a' in field definition is forbidden." },
/*  83 */ { 46, 3, 11, "*anonymous stream*:3:11: Making a direct reference to a package is forbidden." },
/*  84 */ { 14, 2, 6,  "*anonymous stream*:2:6: Symbol `x' is not yet defined in this expression." },
/*  85 */ { 22, 2, 14, "*anonymous stream*:2:14: Symbol `x' is not yet defined in this expression." },
/*  86 */ { 24, 2, 16, "*anonymous stream*:2:16: Symbol `x' is not yet defined in this expression." },
/*  87 */ { 23, 3, 6,  "*anonymous stream*:3:6: Method argument name `x' conflicts with class `A' field name." },
/*  88 */ { 39, 5, 6,  "*anonymous stream*:5:6: Method argument name `x' conflicts with class `B' field name." },
/*  89 */ { 11, 3, 1,  "*anonymous stream*:3:1: Function `main' was already defined." },
/*  90 */ { 6, 1, 7,   "*anonymous stream*:1:7: Function of the same name `main' is already defined." },
/*  91 */ { 22, 3, 8,  "*anonymous stream*:3:8: Capture `a' was already defined." },
/*  92 */ { 23, 3, 9,  "*anonymous stream*:3:9: Symbol `a' is a already used as a capture." },
/*  93 */ { 9, 2, 1,   "*anonymous stream*:2:1: Variable `x' is never used (did you mean `use'?)." },
/*  94 */ { 6, 1, 7,   "*anonymous stream*:1:7: Class `C' is never used (did you mean `use'?)." },
/*  95 */ { 8, 1, 9,   "*anonymous stream*:1:9: Field `_x' is never used (did you mean `C'?)." },
/*  96 */ { 0, 1, 1,   "*anonymous stream*:1:1: Function `f' is never used (did you mean `use'?)." },
/*  97 */ { 21, 1, 22, "*anonymous stream*:1:22: Package `algo' is never used (did you mean `add'?)." },
/*  98 */ { 17, 3, 1,  "*anonymous stream*:3:1: Statement is unreachable." },
/*  99 */ { 12, 2, 4,  "*anonymous stream*:2:4: Operand is not a numeric value: character" },
/* 100 */ { 17, 3, 2,  "*anonymous stream*:3:2: Operands are not summable: character, character" },
/* 101 */ { 17, 3, 2,  "*anonymous stream*:3:2: Operands are not multipliable: character, character" },
/* 102 */ { 7, 1, 8,   "*anonymous stream*:1:8: ./data/CannotParse.hgn:3:1: expected one of characters: -" },
/* 103 */ { 7, 1, 8,   "*anonymous stream*:1:8: ./data/CannotCompile.hgn:2:4: Operand types for `+' do not match: `integer' vs `real'." },
/* 104 */ { 13, 1, 14, "*anonymous stream*:1:14: Missing default argument." },
		{ 0, 0, 0, nullptr }
	};
	ErrInfo const* e( err );
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


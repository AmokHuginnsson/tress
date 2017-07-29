/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_execute.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_hhuginn_execute : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_execute( void ) {}
	void test_execute( prog_src_t, int const[3], int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_execute, "yaal::tools::HHuginn,execution" );

char const progExecuteErr0[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() + 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr1[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() - 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr2[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() * 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr3[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() / 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr4[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() % 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr5[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() ^ 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr6[] =
	"main() {\n"
	"\tv = @(){ return( 2 ); };\n"
	"\tx = v() ^ 2.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr7[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() == 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr8[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() != 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr9[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() < 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr10[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() > 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr11[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() <= 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr12[] =
	"main() {\n"
	"\tv = @(){ return( 1 ); };\n"
	"\tx = v() >= 1.5;\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr13[] =
	"foo() {\n"
	"\treturn ( foo() );\n"
	"}\n"
;

char const progExecuteErr14[] =
	"main() {\n"
	"\t{1:2,1.5:3};\n"
	"\treturn ( 0 );\n"
	"}\n"
;

char const progExecuteErr15[] =
	"main() {\n"
	"\tx='a';\n"
	"\tl=[0,1];\n"
	"\tx=l[x];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr16[] =
	"main() {\n"
	"\tl=[0,1];\n"
	"\tx=l[2];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr17[] =
	"main() {\n"
	"\tl=[0,1];\n"
	"\tx=l[-3];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr18[] =
	"main() {\n"
	"\tv=0;\n"
	"\tx=v[0];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr19[] =
	"f(x){return (x);}\n"
	"main() {\n"
	"\ts=\"Ala ma kota.\";\n"
	"\ti=f('0');\n"
	"\tx=s[i:5];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr20[] =
	"f(x){return (x);}\n"
	"main() {\n"
	"\ts=\"Ala ma kota.\";\n"
	"\ti=f('5');\n"
	"\tx=s[0:i];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr21[] =
	"f(x){return (x);}\n"
	"main() {\n"
	"\ts=\"Ala ma kota.\";\n"
	"\ti=f('2');\n"
	"\tx=s[0:10:i];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr22[] =
	"main() {\n"
	"\ts=\"Ala ma kota.\";\n"
	"\tx=s[0:10:0];\n"
	"\treturn ( x );\n"
	"}\n"
;

char const progExecuteErr23[] =
	"main() {\n"
	"\tv=0;\n"
	"\tx=v[0:2];\n"
	"\treturn ( x );\n"
	"}\n"
;

/* would crash without fix for User-Defined-Destructor problem in case of low-level implementation exception. */
char const progExecuteErr24[] =
	"class A {\n"
	"\tdestructor(){\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\ta=A();\n"
	"\ta+0;\n"
	"}\n"
;

char const progExecuteErr25[] =
	"class L {\n"
	"\t_head = none;\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te._head;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr26[] =
	"class L {\n"
	"\t_head = none;\n"
	"\titerator() {\n"
	"\t\treturn ( 0 );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te._head;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr27[] =
	"class LI {\n"
	"\t_cur = none;\n"
	"\tconstructor( cur_ ) {\n"
	"\t\t_cur = cur_;\n"
	"\t}\n"
	"}\n"
	"class L {\n"
	"\t_head = none;\n"
	"\titerator() {\n"
	"\t\treturn ( LI( _head ) );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te._cur;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr28[] =
	"class LI {\n"
	"\t_cur = none;\n"
	"\tconstructor( cur_ ) {\n"
	"\t\t_cur = cur_;\n"
	"\t}\n"
	"\tis_valid = none;\n"
	"}\n"
	"class L {\n"
	"\t_head = none;\n"
	"\titerator() {\n"
	"\t\treturn ( LI( _head ) );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te._cur;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr29[] =
	"class LI {\n"
	"\t_cur = none;\n"
	"\tconstructor( cur_ ) {\n"
	"\t\t_cur = cur_;\n"
	"\t}\n"
	"\tis_valid() {\n"
	"\t\treturn ( 0 );\n"
	"\t}\n"
	"}\n"
	"class L {\n"
	"\t_head = none;\n"
	"\titerator() {\n"
	"\t\treturn ( LI( _head ) );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te._cur;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr30[] =
	"class LN {\n"
	"\t_data = none;\n"
	"\t_next = none;\n"
	"\tconstructor( data_, next_ ) {\n"
	"\t\t_data = data_;\n"
	"\t\t_next = next_;\n"
	"\t}\n"
	"}\n"
	"class LI {\n"
	"\t_cur = none;\n"
	"\tconstructor( cur_ ) {\n"
	"\t\t_cur = cur_;\n"
	"\t}\n"
	"\tis_valid() {\n"
	"\t\treturn ( 0 );\n"
	"\t}\n"
	"\tvalue() {\n"
	"\t\treturn ( _cur._data );\n"
	"\t}\n"
	"}\n"
	"class L {\n"
	"\t_head = none;\n"
	"\tadd( data_ ) {\n"
	"\t\t_head = LN( data_, _head );\n"
	"\t}\n"
	"\titerator() {\n"
	"\t\treturn ( LI( _head ) );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te._next;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr31[] =
	"class LN {\n"
	"\t_data = none;\n"
	"\t_next = none;\n"
	"\tconstructor( data_, next_ ) {\n"
	"\t\t_data = data_;\n"
	"\t\t_next = next_;\n"
	"\t}\n"
	"}\n"
	"class LI {\n"
	"\t_cur = none;\n"
	"\tconstructor( cur_ ) {\n"
	"\t\t_cur = cur_;\n"
	"\t}\n"
	"\tis_valid() {\n"
	"\t\treturn ( 0 );\n"
	"\t}\n"
	"\tvalue() {\n"
	"\t\treturn ( _cur._data );\n"
	"\t}\n"
	"\tnext() {\n"
	"\t\t_cur = _cur._next;\n"
	"\t}\n"
	"}\n"
	"class L {\n"
	"\t_head = none;\n"
	"\tadd( data_ ) {\n"
	"\t\t_head = LN( data_, _head );\n"
	"\t}\n"
	"\titerator() {\n"
	"\t\treturn ( LI( _head ) );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\tfor ( e : L() ) {\n"
	"\t\te;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr32[] =
	"main() {\n"
	"\tfor ( e : 0 ) {\n"
	"\t\te;\n"
	"\t}\n"
	"}\n"
;

char const progExecuteErr33[] =
	"class A {\n"
	"\tdo() {\n"
	"\t\treturn ( super );\n"
	"\t}\n"
	"}\n"
	"main() {\n"
	"\treturn ( A().do() );\n"
	"}\n"
;

char const progExecuteErr34[] =
	"main() {\n"
	"l = @(){\n"
	"x = 0;\n"
	"y = observe( x );\n"
	"y;\n"
	"};\n"
	"z = l();\n"
	"z += 1;\n"
	"}\n"
;

char const progExecuteErr35[] =
	"main() {\n"
	"x=0;\n"
	"y=observe(x);\n"
	"z=observe(y);\n"
	"z;\n"
	"}\n"
;

char const progExecuteErr36[] =
	"main() {\n"
	"x=0;\n"
	"y=use(x);\n"
	"y;\n"
	"}\n"
;

char const progExecuteErr37[] =
	"f(){}\n"
	"main() {\n"
	"f(0);\n"
	"}\n"
;

char const progExecuteErr38[] =
	"f(a=0){a;}\n"
	"main() {\n"
	"f(0,0);\n"
	"}\n"
;

char const progExecuteErr39[] =
	"f(a,b=0){a+b;}\n"
	"main() {\n"
	"f();\n"
	"}\n"
;

char const progExecuteErr40[] =
	"main() {\n"
	"\"\".find(0);\n"
	"}\n"
;

char const progExecuteErr41[] =
	"main() {\n"
	"($0).set_precision(0.);\n"
	"}\n"
;

char const progExecuteErr42[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.square_root(0);\n"
	"}\n"
;

char const progExecuteErr43[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.round(0);\n"
	"}\n"
;

char const progExecuteErr44[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.statistics(0);\n"
	"}\n"
;

char const progExecuteErr45[] =
	"import Algorithms as A;\n"
	"main() {\n"
	"A.sorted(0);\n"
	"}\n"
;

char const progExecuteErr46[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.statistics([0]);\n"
	"}\n"
;

char const progExecuteErr47[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.statistics([0.,$0]);\n"
	"}\n"
;

char const progExecuteErr48[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.statistics(deque(0));\n"
	"}\n"
;

char const progExecuteErr49[] =
	"import Mathematics as M;\n"
	"main() {\n"
	"M.statistics(set(0));\n"
	"}\n"
;

char const progExecuteErr50[] =
	"import Algorithms as A;\n"
	"main() {\n"
	"A.reduce([],0);\n"
	"}\n"
;

char const progExecuteErr51[] =
	"main() {\n"
	"true && @(){}();\n"
	"}\n"
;

char const progExecuteErr52[] =
	"main() {\n"
	"if(1){}\n"
	"}\n"
;

char const progExecuteErr53[] =
	"main() {\n"
	"switch([]){case(0):{}}\n"
	"}\n"
;

char const progExecuteErr54[] =
	"main() {\n"
	"switch(0){\n"
	"case('0'):{}\n"
	"}\n"
	"}\n"
;

char const progExecuteErr55[] =
	"main() {\n"
	"v=$0;\n"
	"v.clear();\n"
	"}\n"
;

char const progExecuteErr56[] =
	"class Base {\n"
	"foo() {}\n"
	"}\n"
	"class Derived : Base {\n"
	"bar() {\n"
	"super.bar();\n"
	"}\n"
	"}\n"
	"main() {\n"
	"d=Derived();\n"
	"d.bar();\n"
	"d.foo();\n"
	"}\n"
;

char const progExecuteErr57[] =
	"class Base {\n"
	"foo() {}\n"
	"}\n"
	"class Derived : Base {\n"
	"foo() {\n"
	"super.foo=0;\n"
	"}\n"
	"}\n"
	"main() {\n"
	"d=Derived();\n"
	"d.foo();\n"
	"}\n"
;

char const progExecuteErr58[] =
	"main() {\n"
	"v=0;\n"
	"v.clear();\n"
	"}\n"
;

char const progExecuteErr59[] =
	"main() {\n"
	"v=\"\";\n"
	"v.clear = 0;\n"
	"}\n"
;

char const progExecuteErr60[] =
	"class A {\n"
	"x=0;\n"
	"}\n"
	"main() {\n"
	"A().x = 0;\n"
	"}\n"
;

char const progExecuteErr61[] =
	"main() {\n"
	"v=\"ala\";\n"
	"v[0] = 'A';\n"
	"}\n"
;

char const progExecuteErr62[] =
	"class A{\n"
	"add(x){x;0;}\n"
	"}\n"
	"main(){\n"
	"A()+A();\n"
	"}\n"
;

char const progExecuteErr63[] =
	"class A{\n"
	"hash(){0.;}\n"
	"}\n"
	"main(){\n"
	"set(A());\n"
	"}\n"
;

char const progExecuteErr64[] =
	"f(x){x;}\n"
	"main(){\n"
	"f(size)<f(type);\n"
	"}\n"
;

char const progExecuteErr65[] =
	"main(){\n"
	"set(\"\".clear);\n"
	"}\n"
;

char const progExecuteErr66[] =
	"main(){\n"
	"x=0;\n"
	"x();\n"
	"}\n"
;

char const progExecuteErr67[] =
	"main(){\n"
	"x=0;\n"
	"x[0:1];\n"
	"}\n"
;

char const progExecuteErr68[] =
	"main() {\n"
	"true ^^ @(){}();\n"
	"}\n"
;

char const progExecuteErr69[] =
	"main() {\n"
	"!@(){}();\n"
	"}\n"
;

char const progExecuteErr70[] =
	"main() {\n"
	"while(1){}\n"
	"}\n"
;

char const progExecuteErr71[] =
	"main() {\n"
	"type(type)();\n"
	"}\n"
;

void tut_yaal_tools_hhuginn_execute::test_execute( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog, "*tress*" );
	h.preprocess();
	ENSURE( "failed to parse valid", h.parse() );
	bool compiled( h.compile() );
	if ( ! compiled ) {
		clog << "COMPILATION ERROR: " << h.error_message() << endl;
	}
	ENSURE( "failed to compile valid", compiled );
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
		progExecuteErr15,
		progExecuteErr16,
		progExecuteErr17,
		progExecuteErr18,
		progExecuteErr19,
		progExecuteErr20,
		progExecuteErr21,
		progExecuteErr22,
		progExecuteErr23,
		progExecuteErr24,
		progExecuteErr25,
		progExecuteErr26,
		progExecuteErr27,
		progExecuteErr28,
		progExecuteErr29,
		progExecuteErr30,
		progExecuteErr31,
		progExecuteErr32,
		progExecuteErr33,
		progExecuteErr34,
		progExecuteErr35,
		progExecuteErr36,
		progExecuteErr37,
		progExecuteErr38,
		progExecuteErr39,
		progExecuteErr40,
		progExecuteErr41,
		progExecuteErr42,
		progExecuteErr43,
		progExecuteErr44,
		progExecuteErr45,
		progExecuteErr46,
		progExecuteErr47,
		progExecuteErr48,
		progExecuteErr49,
		progExecuteErr50,
		progExecuteErr51,
		progExecuteErr52,
		progExecuteErr53,
		progExecuteErr54,
		progExecuteErr55,
		progExecuteErr56,
		progExecuteErr57,
		progExecuteErr58,
		progExecuteErr59,
		progExecuteErr60,
		progExecuteErr61,
		progExecuteErr62,
		progExecuteErr63,
		progExecuteErr64,
		progExecuteErr65,
		progExecuteErr66,
		progExecuteErr67,
		progExecuteErr68,
		progExecuteErr69,
		progExecuteErr70,
		progExecuteErr71,
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
		{ 31, 4, 5 },    // 15
		{ 23, 3, 5 },    // 16
		{ 23, 3, 5 },    // 17
		{ 19, 3, 5 },    // 18
		{ 61, 5, 5 },    // 19
		{ 61, 5, 5 },    // 20
		{ 61, 5, 5 },    // 21
		{ 32, 3, 5 },    // 22
		{ 19, 3, 5 },    // 23
		{ 49, 7, 3 },    // 24
		{ 46, 5, 11 },   // 25
		{ 79, 8, 11 },   // 25
		{ 157, 14, 11 }, // 27
		{ 175, 15, 11 }, // 28
		{ 190, 17, 11 }, // 29
		{ 389, 31, 11 }, // 30
		{ 423, 34, 11 }, // 31
		{ 19, 2, 11 },   // 32
		{ 29, 3, 12 },   // 33
		{ 60, 8, 3 },    // 34
		{ 37, 4, 10 },   // 35
		{ 19, 3, 6 },    // 36
		{ 16, 3, 2 },    // 37
		{ 21, 3, 2 },    // 38
		{ 25, 3, 2 },    // 39
		{ 16, 2, 8 },    // 40
		{ 27, 2, 19 },   // 41
		{ 47, 3, 14 },   // 42
		{ 41, 3, 8 },    // 43
		{ 46, 3, 13 },   // 44
		{ 41, 3, 9 },    // 45
		{ 46, 3, 13 },   // 46
		{ 46, 3, 13 },   // 47
		{ 46, 3, 13 },   // 48
		{ 46, 3, 13 },   // 49
		{ 41, 3, 9 },    // 50
		{ 14, 2, 6 },    // 51
		{ 12, 2, 4 },    // 52
		{ 16, 2, 8 },    // 53
		{ 25, 3, 6 },    // 54
		{ 16, 3, 2 },    // 55
		{ 60, 6, 6 },    // 56
		{ 60, 6, 6 },    // 57
		{ 15, 3, 2 },    // 58
		{ 16, 3, 2 },    // 59
		{ 29, 5, 4 },    // 60
		{ 23, 3, 6 },    // 61
		{ 35, 5, 4 },    // 62
		{ 34, 5, 4 },    // 63
		{ 24, 3, 8 },    // 64
		{ 11, 2, 4 },    // 65
		{ 14, 3, 2 },    // 66
		{ 14, 3, 2 },    // 67
		{ 14, 2, 6 },    // 68
		{ 9, 2, 1 },     // 69
		{ 15, 2, 7 },    // 70
		{ 19, 2, 11 },   // 71
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progExecuteErr ) ), * progEnd( end( progExecuteErr ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_execute( *prog, *e, static_cast<int>( prog - begin( progExecuteErr ) ) );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "bad number of arguments to main()" )
	HHuginn h;
	HStringStream s( "main(){}" );
	h.load( s );
	h.preprocess();
	h.parse();
	h.compile();
	h.add_argument( "dummy" );
	h.execute();
	ENSURE_EQUALS( "would crash", h.error_message(), "*anonymous stream*:1:1: Bad number of parameters in call to: `main()', expected exactly: 0, got: 1." );
TUT_TEARDOWN()

}


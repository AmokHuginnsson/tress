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
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_execute : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_execute( void ) {}
	void test_execute( prog_src_t, ErrInfo const&, int );
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
	"\t[1:2,1.5:3];\n"
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
	"class A { _x = none; }\n"
	"main() {\n"
	"a = A();\n"
	"switch(A()){case(a):{a._x;}}\n"
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
	"f(\"\".to_upper)<f(\"\".to_lower);\n"
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

char const progExecuteErr72[] =
	"f(x,y,a...) {\n"
	"[x,y,a];\n"
	"}\n"
	"main() {\n"
	"f(0);\n"
	"}\n"
;

char const progExecuteErr73[] =
	"f(x,y,z = 0, a...) {\n"
	"[x,y,z,a];\n"
	"}\n"
	"main() {\n"
	"f(0);\n"
	"}\n"
;

char const progExecuteErr74[] =
	"f(x,y,k:::) {\n"
	"[x,y,k];\n"
	"}\n"
	"main() {\n"
	"f(0);\n"
	"}\n"
;

char const progExecuteErr75[] =
	"f(x,y,z = 0, k:::) {\n"
	"[x,y,z,k];\n"
	"}\n"
	"main() {\n"
	"f(0);\n"
	"}\n"
;

char const progExecuteErr76[] =
	"f(x,y,a...) {\n"
	"[x,y,a];\n"
	"}\n"
	"main() {\n"
	"f(y:0);\n"
	"}\n"
;

char const progExecuteErr77[] =
	"f(x,y,z = 0, a...) {\n"
	"[x,y,z,a];\n"
	"}\n"
	"main() {\n"
	"f(y:0);\n"
	"}\n"
;

char const progExecuteErr78[] =
	"f(x,y,k:::) {\n"
	"[x,y,k];\n"
	"}\n"
	"main() {\n"
	"f(y:0);\n"
	"}\n"
;

char const progExecuteErr79[] =
	"f(x,y,z = 0, k:::) {\n"
	"[x,y,z,k];\n"
	"}\n"
	"main() {\n"
	"f(y:0);\n"
	"}\n"
;

char const progExecuteErr80[] =
	"f(x,y) {\n"
	"[x,y];\n"
	"}\n"
	"main() {\n"
	"f(1,x:0);\n"
	"}\n"
;

char const progExecuteErr81[] =
	"f(x) {\n"
	"[x];\n"
	"}\n"
	"main() {\n"
	"f(1,y:0);\n"
	"}\n"
;

char const progExecuteErr82[] =
	"f(x) {\n"
	"[x];\n"
	"}\n"
	"main() {\n"
	"f(0,0);\n"
	"}\n"
;

char const progExecuteErr83[] =
	"f(x,y=0) {\n"
	"[x,y];\n"
	"}\n"
	"main() {\n"
	"f(0,0,0);\n"
	"}\n"
;

char const progExecuteErr84[] =
	"main() {\n"
	"size();\n"
	"}\n"
;

char const progExecuteErr85[] =
	"main() {\n"
	"\"\".find(0,0,0);\n"
	"}\n"
;

char const progExecuteErr86[] =
	"main() {\n"
	"\"\".find();\n"
	"}\n"
;

char const progExecuteErr87[] =
	"main() {\n"
	"\"\".find(0);\n"
	"}\n"
;

char const progExecuteErr88[] =
	"f(){0;}\n"
	"main() {\n"
	"f()[0:1];\n"
	"}\n"
;

void tut_yaal_tools_hhuginn_execute::test_execute( prog_src_t prog_, ErrInfo const& err_, int index_ ) {
	if ( setup._verbose && setup._debug ) {
		clog << "// HUGINN TEST CASE START" << endl;
		clog << prog_ << endl;
		clog << "// HUGINN TEST CASE FINISH" << endl;
	}
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
	ENSURE_EQUALS( "reporting error position failed " + to_string( index_ ), h.error_position(), err_._pos );
	ENSURE_EQUALS( "reporting error line failed " + to_string( index_ ), h.error_coordinate().line(), err_._line );
	ENSURE_EQUALS( "reporting error column failed " + to_string( index_ ), h.error_coordinate().column(), err_._col );
	ENSURE_EQUALS( "reporting error message failed " + to_string( index_ ), h.error_message(), err_._msg );
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
		progExecuteErr72,
		progExecuteErr73,
		progExecuteErr74,
		progExecuteErr75,
		progExecuteErr76,
		progExecuteErr77,
		progExecuteErr78,
		progExecuteErr79,
		progExecuteErr80,
		progExecuteErr81,
		progExecuteErr82,
		progExecuteErr83,
		progExecuteErr84,
		progExecuteErr85,
		progExecuteErr86,
		progExecuteErr87,
		progExecuteErr88,
		NULL
	};
	ErrInfo const err[] = {
/*   0 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `+' do not match: `integer' vs `real'." },
/*   1 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `-' do not match: `integer' vs `real'." },
/*   2 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `*' do not match: `integer' vs `real'." },
/*   3 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `/' do not match: `integer' vs `real'." },
/*   4 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `%' do not match: `integer' vs `real'." },
/*   5 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `^' do not match: `integer' vs `real'." },
/*   6 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `^' do not match: `integer' vs `real'." },
/*   7 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `==' do not match: `integer' vs `real'." },
/*   8 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `!=' do not match: `integer' vs `real'." },
/*   9 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `<' do not match: `integer' vs `real'." },
/*  10 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `>' do not match: `integer' vs `real'." },
/*  11 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `<=' do not match: `integer' vs `real'." },
/*  12 */ { 44, 3, 10,   "*tress*:3:10: Operand types for `>=' do not match: `integer' vs `real'." },
/*  13 */ { 0, 1, 1,     "*tress*:1:1: Function `main(...)' is not defined." },
/*  14 */ { 15, 2, 7,    "*tress*:2:7: Non-uniform key types, got a `real' instead of an `integer'." },
/*  15 */ { 31, 4, 5,    "*tress*:4:5: Subscript is not an integer: character" },
/*  16 */ { 23, 3, 5,    "*tress*:3:5: Bad index." },
/*  17 */ { 23, 3, 5,    "*tress*:3:5: Bad index." },
/*  18 */ { 19, 3, 5,    "*tress*:3:5: Subscript is not supported on `integer'." },
/*  19 */ { 61, 5, 5,    "*tress*:5:5: Range operand `from' is not an integer." },
/*  20 */ { 61, 5, 5,    "*tress*:5:5: Range operand `to' is not an integer." },
/*  21 */ { 61, 5, 5,    "*tress*:5:5: Range operand `step' is not an integer." },
/*  22 */ { 32, 3, 5,    "*tress*:3:5: Range step cannot be zero." },
/*  23 */ { 19, 3, 5,    "*tress*:3:5: Range operator is not supported on `integer'." },
/*  24 */ { 49, 7, 3,    "*tress*:7:3: Operand types for `+' do not match: `*unknown*' vs `integer'." },
/*  25 */ { 46, 5, 11,   "*tress*:5:11: Class `L' does not have `iterator' method." },
/*  25 */ { 79, 8, 11,   "*tress*:8:11: `For' source returned invalid iterator object." },
/*  27 */ { 157, 14, 11, "*tress*:14:11: Class `LI' does not have `is_valid' method." },
/*  28 */ { 175, 15, 11, "*tress*:15:11: `is_valid' in class `LI' is not a method." },
/*  29 */ { 190, 17, 11, "*tress*:17:11: Class `LI' does not have `value' method." },
/*  30 */ { 389, 31, 11, "*tress*:31:11: Class `LI' does not have `next' method." },
/*  31 */ { 423, 34, 11, "*tress*:34:11: `For' source iterator is_valid returned non-boolean value." },
/*  32 */ { 19, 2, 11,   "*tress*:2:11: `For' source is not an iterable." },
/*  33 */ { 29, 3, 12,   "*tress*:3:12: `A' does not have superclass." },
/*  34 */ { 60, 8, 3,    "*tress*:8:3: Operand types for `+=' do not match: `*observer*' vs `integer'." },
/*  35 */ { 37, 4, 10,   "*tress*:4:10: Making an *observer* out of an *observer*." },
/*  36 */ { 19, 3, 6,    "*tress*:3:6: use() argument must be an `*observer*', not an `integer'." },
/*  37 */ { 16, 3, 2,    "*tress*:3:2: Function `f()` accepts exactly 0 positional arguments, but 1 were given." },
/*  38 */ { 21, 3, 2,    "*tress*:3:2: Function `f()` accepts from 0 to 1 positional arguments, but 2 were given." },
/*  39 */ { 25, 3, 2,    "*tress*:3:2: In call to `f()`, missing required positional argument: `a`." },
/*  40 */ { 16, 2, 8,    "*tress*:2:8: string.find() first argument must be a `string', not an `integer'." },
/*  41 */ { 27, 2, 19,   "*tress*:2:19: number.set_precision() argument must be an `integer', not a `real'." },
/*  42 */ { 47, 3, 14,   "*tress*:3:14: Mathematics.square_root() argument must be a numeric type, either a `number' or a `real', not an `integer'." },
/*  43 */ { 41, 3, 8,    "*tress*:3:8: Mathematics.round() first argument must be a numeric type, either a `number' or a `real', not an `integer'." },
/*  44 */ { 46, 3, 13,   "*tress*:3:13: NumberSetStatistics.constructor() argument must be a `list', not an `integer'." },
/*  45 */ { 41, 3, 9,    "*tress*:3:9: Algorithms.sorted() first argument must be a collection type, not an `integer'." },
/*  46 */ { 46, 3, 13,   "*tress*:3:13: NumberSetStatistics.constructor() a collection contains value of an unexpected type: an `integer', at position: 0" },
/*  47 */ { 46, 3, 13,   "*tress*:3:13: NumberSetStatistics.constructor() a collection is not uniformly typed: a `number', at position: 1" },
/*  48 */ { 46, 3, 13,   "*tress*:3:13: NumberSetStatistics.constructor() argument must be a `list', not a `deque'." },
/*  49 */ { 46, 3, 13,   "*tress*:3:13: NumberSetStatistics.constructor() argument must be a `list', not a `set'." },
/*  50 */ { 41, 3, 9,    "*tress*:3:9: Algorithms.reduce() second argument must be one of {a `*function_reference*', a `*bound_method*'}, not an `integer'." },
/*  51 */ { 14, 2, 6,    "*tress*:2:6: Operands are not boolean values: *none*" },
/*  52 */ { 12, 2, 4,    "*tress*:2:4: `If' argument is not a boolean." },
/*  53 */ { 58, 4, 18,   "*tress*:4:18: Class `A' does not have `equals' method." },
/*  54 */ { 25, 3, 6,    "*tress*:3:6: Case type does not match switch type." },
/*  55 */ { 16, 3, 2,    "*tress*:3:2: `number' does not have `clear' member (did you mean `is_exact'?)." },
/*  56 */ { 60, 6, 6,    "*tress*:6:6: `*object_reference*' does not have `bar' member (did you mean `add'?)." },
/*  57 */ { 60, 6, 6,    "*tress*:6:6: Changing upcasted reference." },
/*  58 */ { 15, 3, 2,    "*tress*:3:2: `integer' is not a compound object." },
/*  59 */ { 16, 3, 2,    "*tress*:3:2: Assignment to read-only location." },
/*  60 */ { 29, 5, 4,    "*tress*:5:4: Assignment to temporary." },
/*  61 */ { 19, 3, 2,    "*tress*:3:2: `string` does not support item assignment." },
/*  62 */ { 35, 5, 4,    "*tress*:5:4: Arithmetic method `add' on an `A' returned result of incompatible type an `integer'." },
/*  63 */ { 34, 5, 4,    "*tress*:5:4: User supplied `hash' function returned an invalid type a `real' instead of an `integer'." },
/*  64 */ { 31, 3, 15,   "*tress*:3:15: There is no `<' operator for `*bound_method*'." },
/*  65 */ { 11, 2, 4,    "*tress*:2:4: There is no `hash' operator for a `*bound_method*'." },
/*  66 */ { 14, 3, 2,    "*tress*:3:2: Reference `integer' is not a function." },
/*  67 */ { 14, 3, 2,    "*tress*:3:2: Range operator is not supported on `integer'." },
/*  68 */ { 14, 2, 6,    "*tress*:2:6: Operands are not boolean values: boolean, *none*" },
/*  69 */ { 9, 2, 1,     "*tress*:2:1: Operand is not a boolean value: *none*" },
/*  70 */ { 15, 2, 7,    "*tress*:2:7: `While' argument is not a boolean." },
/*  71 */ { 19, 2, 11,   "*tress*:2:11: Direct creation of instances of `*function_reference*' is not allowed." },
/*  72 */ { 35, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `y`." },
/*  73 */ { 44, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `y`." },
/*  74 */ { 35, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `y`." },
/*  75 */ { 44, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `y`." },
/*  76 */ { 35, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `x`." },
/*  77 */ { 44, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `x`." },
/*  78 */ { 35, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `x`." },
/*  79 */ { 44, 5, 2,    "*tress*:5:2: In call to `f()`, missing required positional argument: `x`." },
/*  80 */ { 28, 5, 2,    "*tress*:5:2: In call to `f()`, positional argument `x` was already set." },
/*  81 */ { 24, 5, 2,    "*tress*:5:2: Call to `f()` got unexpected keyword arguments." },
/*  82 */ { 24, 5, 2,    "*tress*:5:2: Function `f()` accepts exactly 1 positional argument, but 2 were given." },
/*  83 */ { 30, 5, 2,    "*tress*:5:2: Function `f()` accepts from 1 to 2 positional arguments, but 3 were given." },
/*  84 */ { 13, 2, 5,    "*tress*:2:5: Bad number of parameters in call to: `size()', expected exactly: 1, got: 0." },
/*  85 */ { 16, 2, 8,    "*tress*:2:8: Bad number of parameters in call to: `string.find()', expected at most: 2, got: 3." },
/*  86 */ { 16, 2, 8,    "*tress*:2:8: Bad number of parameters in call to: `string.find()', expected at least: 1, got: 0." },
/*  87 */ { 16, 2, 8,    "*tress*:2:8: string.find() first argument must be a `string', not an `integer'." },
/*  87 */ { 20, 3, 4,    "*tress*:3:4: Range operator is not supported on `integer'." },
		{ 0, 0, 0, nullptr }
	};
	ErrInfo const* e( err );
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
	ENSURE_EQUALS( "would crash", h.error_message(), "*anonymous stream*:1:1: Function `main()` accepts exactly 0 positional arguments, but 1 were given." );
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_execution.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_hhuginn_execution : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_execution( void ) {}
	void test_execute( prog_src_t, int const[3], int );
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_execution, "yaal::tools::HHuginn,execution" );

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

void tut_yaal_tools_hhuginn_execution::test_execute( prog_src_t prog_, int const err_[3], int index_ ) {
	HStringStream prog( prog_ );
	HHuginn h;
	h.load( prog );
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
		{ 0, 0, 0 }
	};
	int const (*e)[3]( err );
	for ( prog_src_t* prog( begin( progExecuteErr ) ), * progEnd( end( progExecuteErr ) ); prog != progEnd; ++ prog, ++ e ) {
		if ( *prog ) {
			test_execute( *prog, *e, static_cast<int>( prog - begin( progExecuteErr ) ) );
		}
	}
TUT_TEARDOWN()

}


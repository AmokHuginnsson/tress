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

void tut_yaal_tools_hhuginn_execution::test_execute( prog_src_t prog_, int const err_[3], int index_ ) {
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

}


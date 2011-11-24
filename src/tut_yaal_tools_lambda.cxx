/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_lambda.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/macro.hxx>
#include <yaal/hcore/static_assert.hxx>
#include <yaal/tools/lambda.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

static int const MAX_DATA = 9;
STATIC_ASSERT(( MAX_DATA <= countof ( _testData_[0] ) ));

TUT_SIMPLE_MOCK( tut_yaal_tools_lambda );
TUT_TEST_GROUP( tut_yaal_tools_lambda, "yaal::tools::lambda" );

TUT_UNIT_TEST( 1, "lambda value" )
	ENSURE_EQUALS( "_1 value failed", _1( 1 ), 1 );
	ENSURE_EQUALS( "_2 value failed", _2( 1, 2 ), 2 );
	ENSURE_EQUALS( "_3 value failed", _3( 1, 2, 3 ), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "preincrement" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), ++ _1 );
	ENSURE_EQUALS( "preincrement lambda failed", ss.string(), "3 4 6 8 12 14 18 20 24 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "postincrement" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 ++ );
	ENSURE_EQUALS( "postincrement lambda failed", ss.string(), "2 3 5 7 11 13 17 19 23 " );
	ss.clear();
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "postincrement lambda failed", ss.string(), "3 4 6 8 12 14 18 20 24 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "predecrement" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), -- _1 );
	ENSURE_EQUALS( "predecrement lambda failed", ss.string(), "1 2 4 6 10 12 16 18 22 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "postdecrement" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 -- );
	ENSURE_EQUALS( "postdecrement lambda failed", ss.string(), "2 3 5 7 11 13 17 19 23 " );
	ss.clear();
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "postdecrement lambda failed", ss.string(), "1 2 4 6 10 12 16 18 22 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "plus" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), 1 + _1 );
	ENSURE_EQUALS( "plus lambda failed", ss.string(), "3 4 6 8 12 14 18 20 24 " );
	ss.clear();
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 + 1 );
	ENSURE_EQUALS( "plus lambda failed", ss.string(), "3 4 6 8 12 14 18 20 24 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "plus both args are free" )
	ENSURE_EQUALS( "plus failed", ( _1 + _2 )( 3, 4 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "plus both args are free, one integral, one floating point" )
	ENSURE_EQUALS( "plus failed", ( _1 + _2 )( 3.14, 4 ), 3.14 + 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "plus both args are free, at least one floating point, but we force return type" )
	ENSURE_EQUALS( "forcing return type failed", ret<int>( _1 + _2 )( 3.14, 4 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "combined lambda operations" )
	ENSURE_EQUALS( "combined + * lambda failed", ( _1 + _2 * _3 )( 1, 2, 3 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 48, "streams" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	for_each( l.begin(), l.end(), ss << *_1 << ", " );
	ENSURE_EQUALS( "stream lambda failed", ss.string(), "2, 3, 5, 7, 11, 13, 17, 19, 23, " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 49, "experiment" )
	int i( 0 );
	( ++ _1, ++ _1 )( i );
	ENSURE_EQUALS( "coma filed", i, 2 );
TUT_TEARDOWN()

}


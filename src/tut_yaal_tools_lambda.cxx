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

TUT_UNIT_TEST( 10, "minus" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), 1 - _1 );
	ENSURE_EQUALS( "minus lambda failed", ss.string(), "-1 -2 -4 -6 -10 -12 -16 -18 -22 " );
	ss.clear();
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 - 1 );
	ENSURE_EQUALS( "minus lambda failed", ss.string(), "1 2 4 6 10 12 16 18 22 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "minus both args are free" )
	ENSURE_EQUALS( "minus failed", ( _1 - _2 )( 3, 4 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "minus both args are free, one integral, one floating point" )
	ENSURE_EQUALS( "minus failed", ( _1 - _2 )( 3.14, 4 ), 3.14 - 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "minus both args are free, at least one floating point, but we force return type" )
	ENSURE_EQUALS( "forcing return type failed", ret<int>( _1 - _2 )( 3.14, 4 ), 0 );
TUT_TEARDOWN()

	/* 2 3 5 7 11 13 17 19 23 */

TUT_UNIT_TEST( 14, "multiplies" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), 2 * _1 );
	ENSURE_EQUALS( "multiplies lambda failed", ss.string(), "4 6 10 14 22 26 34 38 46 " );
	ss.clear();
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 * 2 );
	ENSURE_EQUALS( "multiplies lambda failed", ss.string(), "4 6 10 14 22 26 34 38 46 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "multiplies both args are free" )
	ENSURE_EQUALS( "multiplies failed", ( _1 * _2 )( 3, 4 ), 12 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "multiplies both args are free, one integral, one floating point" )
	ENSURE_EQUALS( "multiplies failed", ( _1 * _2 )( 3.14, 4 ), 3.14 * 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "multiplies both args are free, at least one floating point, but we force return type" )
	ENSURE_EQUALS( "forcing return type failed", ret<int>( _1 * _2 )( 3.14, 4 ), 12 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "divides" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), 223092870 / _1 );
	ENSURE_EQUALS( "divides lambda failed", ss.string(), "111546435 74364290 44618574 31870410 20281170 17160990 13123110 11741730 9699690 " );
	ss.clear();
	transform( l.begin(), l.end(), l.begin(), _1 * 2 );
	copy( l.begin(), l.end(), stream_iterator( ss, " " ) );
	ENSURE_EQUALS( "divides lambda failed", ss.string(), "4 6 10 14 22 26 34 38 46 " );
	ss.clear();
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 / 2 );
	ENSURE_EQUALS( "divides lambda failed", ss.string(), "2 3 5 7 11 13 17 19 23 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 19, "divides both args are free" )
	ENSURE_EQUALS( "divides failed", ( _1 / _2 )( 3, 4 ), 0 );
	ENSURE_EQUALS( "divides failed", ( _1 / _2 )( 4, 3 ), 1 );
	ENSURE_EQUALS( "divides failed", ( _1 / _2 )( 12, 3 ), 4 );
	ENSURE_EQUALS( "divides failed", ( _1 / _2 )( 12, 4 ), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "divides both args are free, one integral, one floating point" )
	ENSURE_EQUALS( "divides failed", ( _1 / _2 )( 3.14, 4 ), 3.14 / 4 );
	TUT_EVAL(( ( _1 / _2 )( 3.14, 4 ) ));
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "divides both args are free, at least one floating point, but we force return type" )
	ENSURE_EQUALS( "forcing return type failed", ret<int>( _1 / _2 )( 3.14, 4 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "modulo" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), 1000 % _1 );
	ENSURE_EQUALS( "modulo lambda failed", ss.string(), "0 1 0 6 10 12 14 12 11 " );
	ss.clear();
	transform( l.begin(), l.end(), stream_iterator( ss, " " ), _1 % 10 );
	ENSURE_EQUALS( "modulo lambda failed", ss.string(), "2 3 5 7 1 3 7 9 3 " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "modulo both args are free" )
	ENSURE_EQUALS( "modulo failed", ( _1 % _2 )( 3, 4 ), 3 );
	ENSURE_EQUALS( "modulo failed", ( _1 % _2 )( 4, 3 ), 1 );
	ENSURE_EQUALS( "modulo failed", ( _1 % _2 )( 12, 3 ), 0 );
	ENSURE_EQUALS( "modulo failed", ( _1 % _2 )( 12, 4 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "combined lambda plus operations" )
	ENSURE_EQUALS( "combined + const + lambda failed", ( _1 + 2 + _2 )( 1, 3 ), 6 );
	ENSURE_EQUALS( "combined + const + lambda failed", ( _1 + _2 + 3 )( 1, 2 ), 6 );
	ENSURE_EQUALS( "combined const + const + lambda failed", ( 1 + ( 2 + _1  ) )( 3 ), 6 );
	ENSURE_EQUALS( "combined + const + const lambda failed", ( ( _1 + 2 ) + 3 )( 1 ), 6 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 25, "combined lambda minus operations" )
	ENSURE_EQUALS( "combined - const - lambda failed", ( _1 - 2 - _2 )( 1, 3 ), -4 );
	ENSURE_EQUALS( "combined - const - lambda failed", ( _1 - _2 - 3 )( 1, 2 ), -4 );
	ENSURE_EQUALS( "combined const - const - lambda failed", ( 1 - ( 2 - _1  ) )( 3 ), 2 );
	ENSURE_EQUALS( "combined - const - const lambda failed", ( ( _1 - 2 ) - 3 )( 1 ), -4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "combined lambda multiplies operations" )
	ENSURE_EQUALS( "combined * const * lambda failed", ( _1 * 3 * _2 )( 2, 5 ), 30 );
	ENSURE_EQUALS( "combined * const * lambda failed", ( _1 * _2 * 5 )( 2, 3 ), 30 );
	ENSURE_EQUALS( "combined const * const * lambda failed", ( 2 * ( 3 * _1  ) )( 5 ), 30 );
	ENSURE_EQUALS( "combined * const * const lambda failed", ( ( _1 * 3 ) * 5 )( 2 ), 30 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "combined lambda divides operations" )
	ENSURE_EQUALS( "combined / const / lambda failed", ( _1 / 24 / _2 )( 96, 2 ), 2 );
	ENSURE_EQUALS( "combined / const / lambda failed", ( _1 / _2 / 2 )( 96, 24 ), 2 );
	ENSURE_EQUALS( "combined const / const / lambda failed", ( 96 / ( 24 / _1  ) )( 2 ), 8 );
	ENSURE_EQUALS( "combined / const / const lambda failed", ( ( _1 / 24 ) / 2 )( 96 ), 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "combined lambda modulo operations" )
	ENSURE_EQUALS( "combined % const % lambda failed", ( _1 % 29 % _2 )( 97, 13 ), 10 );
	ENSURE_EQUALS( "combined % const % lambda failed", ( _1 % _2 % 13 )( 97, 29 ), 10 );
	ENSURE_EQUALS( "combined const % const % lambda failed", ( 97 % ( 29 % _1  ) )( 13 ), 1 );
	ENSURE_EQUALS( "combined % const % const lambda failed", ( ( _1 % 29 ) % 13 )( 97 ), 10 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "assign" )
	int a( 0 );
	( _::_1 = 7 )( a );
	ENSURE_EQUALS( "assign const failed", a, 7 );
	( _::_1 = _2 )( a, 13 );
	ENSURE_EQUALS( "assign lambda var failed", a, 13 );
	( _::_1 = _2 * 2 )( a, 7 );
	ENSURE_EQUALS( "assign lambda expr failed", a, 14 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "plus assign" )
	int a( 3 );
	( _1 += 7 )( a );
	ENSURE_EQUALS( "plus assign const failed", a, 10 );
	a = 3;
	( _1 += _2 )( a, 13 );
	ENSURE_EQUALS( "plus assign lambda var failed", a, 16 );
	a = 3;
	( _1 += ( _2 * 2 ) )( a, 7 );
	ENSURE_EQUALS( "plus assign lambda expr failed", a, 17 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 31, "minus assign" )
	int a( 3 );
	( _1 -= 7 )( a );
	ENSURE_EQUALS( "minus assign const failed", a, -4 );
	a = 3;
	( _1 -= _2 )( a, 13 );
	ENSURE_EQUALS( "minus assign lambda var failed", a, -10 );
	a = 3;
	( _1 -= ( _2 * 2 ) )( a, 7 );
	ENSURE_EQUALS( "minus assign lambda expr failed", a, -11 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "multiplies assign" )
	int a( 3 );
	( _1 *= 7 )( a );
	ENSURE_EQUALS( "multiplies assign const failed", a, 21 );
	a = 3;
	( _1 *= _2 )( a, 13 );
	ENSURE_EQUALS( "multiplies assign lambda var failed", a, 39 );
	a = 3;
	( _1 *= ( _2 * 2 ) )( a, 7 );
	ENSURE_EQUALS( "multiplies assign lambda expr failed", a, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 33, "divides assign" )
	int a( 3 * 7 );
	( _1 /= 7 )( a );
	ENSURE_EQUALS( "divides assign const failed", a, 3 );
	a = 39;
	( _1 /= _2 )( a, 13 );
	ENSURE_EQUALS( "divides assign lambda var failed", a, 3 );
	a = 42;
	( _1 /= ( _2 * 2 ) )( a, 7 );
	ENSURE_EQUALS( "divides assign lambda expr failed", a, 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 34, "modulo assign" )
	int a( 19 );
	( _1 %= 7 )( a );
	ENSURE_EQUALS( "modulo assign const failed", a, 5 );
	a = 19;
	( _1 %= _2 )( a, 13 );
	ENSURE_EQUALS( "modulo assign lambda var failed", a, 6 );
	a = 19;
	( _1 %= ( _2 * 2 ) )( a, 7 );
	ENSURE_EQUALS( "modulo assign lambda expr failed", a, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 35, "equality" )
	ENSURE( "equality failed", ( _1 == 1 )( 1 ) );
	ENSURE_NOT( "equality failed", ( _1 == 1 )( 2 ) );
	ENSURE( "equality failed", ( _1 == _2 )( 1, 1 ) );
	ENSURE_NOT( "equality failed", ( _1 == _2 )( 1, 2 ) );
	ENSURE( "equality failed", ( 1 == _1 )( 1 ) );
	ENSURE_NOT( "equality failed", ( 1 == _1 )( 2 ) );
	ENSURE( "equality failed", ( _1 == ( _2 * 2 ) )( 4, 2 ) );
	ENSURE_NOT( "equality failed", ( _1 == ( _2 * 2 ) )( 7, 2 ) );
	ENSURE( "equality failed", ( ( _2 * 2 ) == _1 )( 4, 2 ) );
	ENSURE_NOT( "equality failed", ( ( _2 * 2 ) == _1 )( 7, 2 ) );
	ENSURE( "equality failed", ( 4 == ( _1 * 2 ) )( 2 ) );
	ENSURE_NOT( "equality failed", ( 7 == ( _1 * 2 ) )( 2 ) );
	ENSURE( "equality failed", ( ( _1 * 2 ) == 4 )( 2 ) );
	ENSURE_NOT( "equality failed", ( ( _1 * 2 ) == 7 )( 2 ) );
	ENSURE( "equality failed", ( ( _1 * 2 ) == ( _2 * 3 ) )( 3, 2 ) );
	ENSURE_NOT( "equality failed", ( ( _1 * 2 ) == ( _2 * 3 ) )( 3, 3 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 36, "non-equality" )
	ENSURE_NOT( "non-equality failed", ( _1 != 1 )( 1 ) );
	ENSURE( "non-equality failed", ( _1 != 1 )( 2 ) );
	ENSURE_NOT( "non-equality failed", ( _1 != _2 )( 1, 1 ) );
	ENSURE( "non-equality failed", ( _1 != _2 )( 1, 2 ) );
	ENSURE_NOT( "non-equality failed", ( 1 != _1 )( 1 ) );
	ENSURE( "non-equality failed", ( 1 != _1 )( 2 ) );
	ENSURE_NOT( "non-equality failed", ( _1 != ( _2 * 2 ) )( 4, 2 ) );
	ENSURE( "non-equality failed", ( _1 != ( _2 * 2 ) )( 7, 2 ) );
	ENSURE_NOT( "non-equality failed", ( ( _2 * 2 ) != _1 )( 4, 2 ) );
	ENSURE( "non-equality failed", ( ( _2 * 2 ) != _1 )( 7, 2 ) );
	ENSURE_NOT( "non-equality failed", ( 4 != ( _1 * 2 ) )( 2 ) );
	ENSURE( "non-equality failed", ( 7 != ( _1 * 2 ) )( 2 ) );
	ENSURE_NOT( "non-equality failed", ( ( _1 * 2 ) != 4 )( 2 ) );
	ENSURE( "non-equality failed", ( ( _1 * 2 ) != 7 )( 2 ) );
	ENSURE_NOT( "non-equality failed", ( ( _1 * 2 ) != ( _2 * 3 ) )( 3, 2 ) );
	ENSURE( "non-equality failed", ( ( _1 * 2 ) != ( _2 * 3 ) )( 3, 3 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 37, "less" )
	ENSURE( "less failed", ( _1 < 1 )( 0 ) );
	ENSURE_NOT( "less failed", ( _1 < 1 )( 1 ) );
	ENSURE( "less failed", ( _1 < _2 )( 0, 1 ) );
	ENSURE_NOT( "less failed", ( _1 < _2 )( 1, 1 ) );
	ENSURE( "less failed", ( 1 < _1 )( 2 ) );
	ENSURE_NOT( "less failed", ( 1 < _1 )( 1 ) );
	ENSURE( "less failed", ( _1 < ( _2 * 2 ) )( 2, 2 ) );
	ENSURE_NOT( "less failed", ( _1 < ( _2 * 2 ) )( 4, 2 ) );
	ENSURE( "less failed", ( ( _2 * 2 ) < _1 )( 7, 2 ) );
	ENSURE_NOT( "less failed", ( ( _2 * 2 ) < _1 )( 4, 2 ) );
	ENSURE( "less failed", ( 4 < ( _1 * 2 ) )( 3 ) );
	ENSURE_NOT( "less failed", ( 4 < ( _1 * 2 ) )( 2 ) );
	ENSURE( "less failed", ( ( _1 * 2 ) < 7 )( 2 ) );
	ENSURE_NOT( "less failed", ( ( _1 * 2 ) < 4 )( 2 ) );
	ENSURE( "less failed", ( ( _1 * 2 ) < ( _2 * 3 ) )( 2, 2 ) );
	ENSURE_NOT( "less failed", ( ( _1 * 2 ) < ( _2 * 3 ) )( 3, 2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 38, "greater" )
	ENSURE( "greater failed", ( _1 > 1 )( 2 ) );
	ENSURE_NOT( "greater failed", ( _1 > 1 )( 1 ) );
	ENSURE( "greater failed", ( _1 > _2 )( 2, 1 ) );
	ENSURE_NOT( "greater failed", ( _1 > _2 )( 1, 1 ) );
	ENSURE( "greater failed", ( 1 > _1 )( 0 ) );
	ENSURE_NOT( "greater failed", ( 1 > _1 )( 1 ) );
	ENSURE( "greater failed", ( _1 > ( _2 * 2 ) )( 7, 2 ) );
	ENSURE_NOT( "greater failed", ( _1 > ( _2 * 2 ) )( 4, 2 ) );
	ENSURE( "greater failed", ( ( _2 * 2 ) > _1 )( 2, 2 ) );
	ENSURE_NOT( "greater failed", ( ( _2 * 2 ) > _1 )( 4, 2 ) );
	ENSURE( "greater failed", ( 7 > ( _1 * 2 ) )( 2 ) );
	ENSURE_NOT( "greater failed", ( 4 > ( _1 * 2 ) )( 2 ) );
	ENSURE( "greater failed", ( ( _1 * 2 ) > 4 )( 3 ) );
	ENSURE_NOT( "greater failed", ( ( _1 * 2 ) > 4 )( 2 ) );
	ENSURE( "greater failed", ( ( _1 * 2 ) > ( _2 * 3 ) )( 4, 2 ) );
	ENSURE_NOT( "greater failed", ( ( _1 * 2 ) > ( _2 * 3 ) )( 3, 2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 39, "less-or-equal" )
	ENSURE( "less-or-equal failed", ( _1 <= 1 )( 0 ) );
	ENSURE( "less-or-equal failed", ( _1 <= 1 )( 1 ) );
	ENSURE_NOT( "less-or-equal failed", ( _1 <= 1 )( 2 ) );
	ENSURE( "less-or-equal failed", ( _1 <= _2 )( 0, 1 ) );
	ENSURE( "less-or-equal failed", ( _1 <= _2 )( 1, 1 ) );
	ENSURE_NOT( "less-or-equal failed", ( _1 <= _2 )( 2, 1 ) );
	ENSURE( "less-or-equal failed", ( 1 <= _1 )( 2 ) );
	ENSURE( "less-or-equal failed", ( 1 <= _1 )( 1 ) );
	ENSURE_NOT( "less-or-equal failed", ( 1 <= _1 )( 0 ) );
	ENSURE( "less-or-equal failed", ( _1 <= ( _2 * 2 ) )( 2, 2 ) );
	ENSURE( "less-or-equal failed", ( _1 <= ( _2 * 2 ) )( 4, 2 ) );
	ENSURE_NOT( "less-or-equal failed", ( _1 <= ( _2 * 2 ) )( 7, 2 ) );
	ENSURE( "less-or-equal failed", ( ( _2 * 2 ) <= _1 )( 7, 2 ) );
	ENSURE( "less-or-equal failed", ( ( _2 * 2 ) <= _1 )( 4, 2 ) );
	ENSURE_NOT( "less-or-equal failed", ( ( _2 * 2 ) <= _1 )( 2, 2 ) );
	ENSURE( "less-or-equal failed", ( 4 <= ( _1 * 2 ) )( 3 ) );
	ENSURE( "less-or-equal failed", ( 4 <= ( _1 * 2 ) )( 2 ) );
	ENSURE_NOT( "less-or-equal failed", ( 7 <= ( _1 * 2 ) )( 2 ) );
	ENSURE( "less-or-equal failed", ( ( _1 * 2 ) <= 7 )( 2 ) );
	ENSURE( "less-or-equal failed", ( ( _1 * 2 ) <= 4 )( 2 ) );
	ENSURE_NOT( "less-or-equal failed", ( ( _1 * 2 ) <= 4 )( 4 ) );
	ENSURE( "less-or-equal failed", ( ( _1 * 2 ) <= ( _2 * 3 ) )( 2, 2 ) );
	ENSURE( "less-or-equal failed", ( ( _1 * 2 ) <= ( _2 * 3 ) )( 3, 2 ) );
	ENSURE_NOT( "less-or-equal failed", ( ( _1 * 2 ) <= ( _2 * 3 ) )( 4, 2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 40, "greater-or-equal" )
	ENSURE( "greater-or-equal failed", ( _1 >= 1 )( 2 ) );
	ENSURE( "greater-or-equal failed", ( _1 >= 1 )( 1 ) );
	ENSURE_NOT( "greater-or-equal failed", ( _1 >= 1 )( 0 ) );
	ENSURE( "greater-or-equal failed", ( _1 >= _2 )( 2, 1 ) );
	ENSURE( "greater-or-equal failed", ( _1 >= _2 )( 1, 1 ) );
	ENSURE_NOT( "greater-or-equal failed", ( _1 >= _2 )( 0, 1 ) );
	ENSURE( "greater-or-equal failed", ( 1 >= _1 )( 0 ) );
	ENSURE( "greater-or-equal failed", ( 1 >= _1 )( 1 ) );
	ENSURE_NOT( "greater-or-equal failed", ( 1 >= _1 )( 2 ) );
	ENSURE( "greater-or-equal failed", ( _1 >= ( _2 * 2 ) )( 7, 2 ) );
	ENSURE( "greater-or-equal failed", ( _1 >= ( _2 * 2 ) )( 4, 2 ) );
	ENSURE_NOT( "greater-or-equal failed", ( _1 >= ( _2 * 2 ) )( 2, 2 ) );
	ENSURE( "greater-or-equal failed", ( ( _2 * 2 ) >= _1 )( 2, 2 ) );
	ENSURE( "greater-or-equal failed", ( ( _2 * 2 ) >= _1 )( 4, 2 ) );
	ENSURE_NOT( "greater-or-equal failed", ( ( _2 * 2 ) >= _1 )( 7, 2 ) );
	ENSURE( "greater-or-equal failed", ( 7 >= ( _1 * 2 ) )( 2 ) );
	ENSURE( "greater-or-equal failed", ( 4 >= ( _1 * 2 ) )( 2 ) );
	ENSURE_NOT( "greater-or-equal failed", ( 3 >= ( _1 * 2 ) )( 2 ) );
	ENSURE( "greater-or-equal failed", ( ( _1 * 2 ) >= 3 )( 2 ) );
	ENSURE( "greater-or-equal failed", ( ( _1 * 2 ) >= 4 )( 2 ) );
	ENSURE_NOT( "greater-or-equal failed", ( ( _1 * 2 ) >= 7 )( 2 ) );
	ENSURE( "greater-or-equal failed", ( ( _1 * 2 ) >= ( _2 * 3 ) )( 4, 2 ) );
	ENSURE( "greater-or-equal failed", ( ( _1 * 2 ) >= ( _2 * 3 ) )( 3, 2 ) );
	ENSURE_NOT( "greater-or-equal failed", ( ( _1 * 2 ) >= ( _2 * 3 ) )( 2, 2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 47, "mixed lambda operations" )
	ENSURE_EQUALS( "combined + * lambda failed", ( _1 + _2 * _3 )( 1, 2, 3 ), 7 );
	ENSURE_EQUALS( "combined ( + ) * lambda failed", ( ( _1 + _2 ) * _3 )( 1, 2, 3 ), 9 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 48, "streams" )
	int_list_t l( _testData_[0], _testData_[0] + MAX_DATA );
	HStringStream ss;
	for_each( l.begin(), l.end(), ss << _1 << ", " );
	ENSURE_EQUALS( "stream lambda failed", ss.string(), "2, 3, 5, 7, 11, 13, 17, 19, 23, " );
	ss.clear();
	for_each( l.begin(), l.end(), ss << ( _1 * 2 ) << ", " );
	ENSURE_EQUALS( "stream lambda failed", ss.string(), "4, 6, 10, 14, 22, 26, 34, 38, 46, " );
TUT_TEARDOWN()

TUT_UNIT_TEST( 49, "experiment" )
	int i( 0 );
	( ++ _1, ++ _1 )( i );
	ENSURE_EQUALS( "coma filed", i, 2 );
TUT_TEARDOWN()

}


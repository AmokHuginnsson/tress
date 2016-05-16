/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hexpression.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hexpression.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hexpression );
TUT_TEST_GROUP( tut_yaal_tools_hexpression, "yaal::tools::HExpression" );

TUT_UNIT_TEST( "empty expression variables" )
	HExpression e;
	for ( int i( 0 ); i < HExpression::MAX_VARIABLE_COUNT; ++ i )
		ENSURE_EQUALS( "variables not initialized", e[ i ], 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy semantics" )
	static int const MAGIC = 7;
	static int const SPOOKY = 13;
	HExpression e( "1" );
	double long* v = e.variables();
	v[ 0 ] = MAGIC;
	HExpression e2( e );
	v = e2.variables();
	e[ 0 ] = SPOOKY;
	ENSURE_EQUALS( "variables not copied", v[ 0 ], MAGIC );
	e2 = e;
	ENSURE_EQUALS( "variables not copied", v[ 0 ], SPOOKY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "variable index range" )
	HExpression e;
	ENSURE_THROW( "bad variable index accepted", e[ -1 ],	HExpressionException );
	ENSURE_THROW( "bad variable index accepted", e[ HExpression::MAX_VARIABLE_COUNT ], HExpressionException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "addition" )
	HExpression e( "2+3" );
	ENSURE_EQUALS( "addition failed", e.evaluate(), 5l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "substraction" )
	HExpression e( "2-3" );
	ENSURE_EQUALS( "substraction failed", e.evaluate(), -1l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "multiplication" )
	HExpression e( "2*3" );
	ENSURE_EQUALS( "multiplication failed", e.evaluate(), 6l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "division" )
	HExpression e( "3/2" );
	ENSURE_EQUALS( "division failed", e.evaluate(), 1.5l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modulo" )
	HExpression e( "3%2" );
	ENSURE_EQUALS( "modulo failed", e.evaluate(), 1l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "power" )
	HExpression e( "2^3" );
	ENSURE_EQUALS( "power failed", e.evaluate(), 8l );
	HExpression e2( "4^3^2" );
	ENSURE_EQUALS( "power failed", e2.evaluate(), 262144l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "negate" )
	HExpression e( "-(2)" );
	ENSURE_EQUALS( "negate failed", e.evaluate(), -2l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "factorial" )
	HExpression e( "6!" );
	ENSURE_EQUALS( "factorial failed", e.evaluate(), 720l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parenthesis" )
	HExpression e( "2*(3+1)" );
	ENSURE_EQUALS( "parenthesis failed", e.evaluate(), 8l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "absolute value" )
	HExpression e( "2*|1-3|" );
	ENSURE_EQUALS( "absolute value failed", e.evaluate(), 4l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "order of addition and multiplication" )
	HExpression e( "2+2*2" );
	ENSURE_EQUALS( "order of addition and multiplication failed", e.evaluate(), 6l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "order of power" )
	HExpression e( "4^3^2" );
	ENSURE_EQUALS( "order of power failed", e.evaluate(), 262144l );
TUT_TEARDOWN()

TUT_UNIT_TEST( "elementary func" )
	HExpression e;
	e.compile( "sqrt(7)" );
	ENSURE_DISTANCE( "sqrt failed", e.evaluate(), 2.645751311065L, epsilon );
	e.compile( "exp(7)" );
	ENSURE_DISTANCE( "exp failed", e.evaluate(), 1096.633158428459L, epsilon );
	e.compile( "ln(7)" );
	ENSURE_DISTANCE( "ln failed", e.evaluate(), 1.945910149055L, epsilon );
	e.compile( "sin(7)" );
	ENSURE_DISTANCE( "sin failed", e.evaluate(), .656986598719L, epsilon );
	e.compile( "cos(7)" );
	ENSURE_DISTANCE( "cos failed", e.evaluate(), .753902254343L, epsilon );
	e.compile( "tg(7)" );
	ENSURE_DISTANCE( "tg failed", e.evaluate(), .871447982724L, epsilon );
	e.compile( "ctg(7)" );
	ENSURE_DISTANCE( "ctg failed", e.evaluate(), 1.147515422405L, epsilon );
	e.compile( "arcsin(0.7)" );
	ENSURE_DISTANCE( "arcsin failed", e.evaluate(), 0.775397496611L, epsilon );
	e.compile( "arccos(0.7)" );
	ENSURE_DISTANCE( "arccos failed", e.evaluate(), 0.795398830184L, epsilon );
	e.compile( "arctg(7)" );
	ENSURE_DISTANCE( "arctg failed", e.evaluate(), 1.428899272191L, epsilon );
	e.compile( "arcctg(7)" );
	ENSURE_DISTANCE( "arcctg failed", e.evaluate(), 0.141897054604L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "complex and valid expression" )
	HExpression x;
	HString eq( "(((2+3+5)*4*6*8)/123)^2^3" );
	x.compile( eq );
	double long x1 = x.evaluate();
	double long x2 = ((2.+3.+5.)*4.*6.*8.)/123.;
	x2 *= x2;
	x2 *= x2;
	x2 *= x2;
	ENSURE_DISTANCE( "wrong computation", x1, x2, epsilon * 4 );
	std::cout << eq << "=" << std::setprecision( 20 ) << x1 << std::endl;
	eq = "Y";
	x.compile( eq );
	x [ 'Y' ] = 3.;
	cout << eq << "=" << x.evaluate() << endl;
	x [ 'Y' ] = 2.;
	cout << eq << "=" << x.evaluate() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "invalid expression" )
	HString eq( "7+10+(4*)" );
	HExpression x;
	ENSURE_THROW( "parsing invalid expression succeded", x.compile( eq ), HExpressionException );
TUT_TEARDOWN()

}


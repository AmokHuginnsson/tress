/* Read tress/LICENSE.md file for copyright and licensing information. */

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
	e.compile( "1/0" );
	ENSURE_THROW( "div by 0 succeded", e.evaluate(), HExpressionException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modulo" )
	HExpression e( "3%2" );
	ENSURE_EQUALS( "modulo failed", e.evaluate(), 1l );
	e.compile( "1%0" );
	ENSURE_THROW( "mod by 0 succeded", e.evaluate(), HExpressionException );
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
	e.compile( "log(100)" );
	ENSURE_DISTANCE( "log failed", e.evaluate(), 2.0L, epsilon );
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
	e.compile( "sinh(7)" );
	ENSURE_DISTANCE( "sinh failed", e.evaluate(), 548.316123273247L, epsilon );
	e.compile( "cosh(7)" );
	ENSURE_DISTANCE( "cosh failed", e.evaluate(), 548.317035155212L, epsilon );
	e.compile( "tgh(7)" );
	ENSURE_DISTANCE( "tgh failed", e.evaluate(), 0.999998336944L, epsilon );
	e.compile( "ctgh(7)" );
	ENSURE_DISTANCE( "ctgh failed", e.evaluate(), 1.000001663059L, epsilon );
	e.compile( "arcsin(-2)" );
	ENSURE_THROW( "arcsin(x) on invalid succeded", e.evaluate(), HExpressionException );
	e.compile( "arcsin(2)" );
	ENSURE_THROW( "arcsin(x) on invalid succeded", e.evaluate(), HExpressionException );
	e.compile( "arccos(-4)" );
	ENSURE_THROW( "arccos(x) on invalid succeded", e.evaluate(), HExpressionException );
	e.compile( "arccos(4)" );
	ENSURE_THROW( "arccos(x) on invalid succeded", e.evaluate(), HExpressionException );
	e.compile( "tg(1.570796326795)" );
	ENSURE_THROW( "tg(x) on pi/2 succeded", e.evaluate(), HExpressionException );
	e.compile( "ctg(0)" );
	ENSURE_THROW( "ctg(x) on 0 succeded", e.evaluate(), HExpressionException );
	e.compile( "sqrt(-1)" );
	ENSURE_THROW( "sqrt(x) on negative succeded", e.evaluate(), HExpressionException );
	e.compile( "ln(0)" );
	ENSURE_THROW( "ln(x) on 0 succeded", e.evaluate(), HExpressionException );
	e.compile( "ln(-1)" );
	ENSURE_THROW( "ln(x) on negative succeded", e.evaluate(), HExpressionException );
	e.compile( "log(0)" );
	ENSURE_THROW( "log(x) on 0 succeded", e.evaluate(), HExpressionException );
	e.compile( "log(-1)" );
	ENSURE_THROW( "log(x) on negative succeded", e.evaluate(), HExpressionException );
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
	std::clog << eq << "=" << std::setprecision( 20 ) << x1 << std::endl;
	eq = "Y";
	x.compile( eq );
	x[ 'Y' ] = 3.;
	ENSURE_DISTANCE( "referencing variable failed", x.evaluate(), 3.L, epsilon );
	x[ 'Y' ] = 2.;
	ENSURE_DISTANCE( "reseting variable failed", x.evaluate(), 2.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "invalid expression" )
	HString eq( "7+10+(4*)" );
	HExpression x;
	ENSURE_THROW( "parsing invalid expression succeded", x.compile( eq ), HExpressionException );
TUT_TEARDOWN()


TUT_UNIT_TEST( "parser errors" )
#define ENSURE_ERROR( expr, message ) \
	try { \
		e.compile( expr ); \
	} catch ( HExpressionException const& ) { \
		ENSURE_EQUALS( "bad error", e.get_error(), to_string( message ) ); \
	}
	HExpression e;
	ENSURE_ERROR( "(|0)", "closing absolute bracket expected" );
	ENSURE_ERROR( "|(0|", "closing bracket expected" );
	ENSURE_ERROR( "(.)", "digit expected" );
	ENSURE_ERROR( "(0+)", "unexpected token" );
	ENSURE_ERROR( "sin|0|", "opening function bracket expected" );
	ENSURE_ERROR( "|sin(0|", "closing function bracket expected" );
	ENSURE_THROW( "eval on not compiled succeded", e.evaluate(), HExpressionException );
#undef ENSURE_ERROR
TUT_TEARDOWN()

}


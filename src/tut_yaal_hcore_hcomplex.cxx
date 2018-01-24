/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/math.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/tools/streamtools.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hcomplex );
TUT_TEST_GROUP( tut_yaal_hcore_hcomplex, "yaal::hcore::HComplex" );

TUT_UNIT_TEST( "Default constructor" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re(), 0.L, epsilon );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Constructor with initialization." )
	HComplex a( math::PI );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	HComplex b( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", b.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", b.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy constructor." )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	HComplex b( a );
	ENSURE_DISTANCE( "re incrorrectly set by copy constructor", b.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by copy constructor", b.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_real()" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re(), 0.L, epsilon );
	a.set_real( math::PI );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_imaginary()" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
	a.set_imaginary( math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set both real and imaginary" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re(), 0.L, epsilon );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
	a.set( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modulus()" )
	HComplex a( 3, 4 );
	ENSURE_DISTANCE( "bad modulus value calculted", a.modulus(), 5.L, epsilon );
	HComplex b( 3 );
	ENSURE_DISTANCE( "bad modulus value calculted", b.modulus(), 3.L, epsilon );
	HComplex c( 0, 4 );
	ENSURE_DISTANCE( "bad modulus value calculted", c.modulus(), 4.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "argument()" )
	HComplex a( 1, 0 );
	ENSURE_DISTANCE( "bad argument of a value calculted", a.argument(), 0.L, epsilon );
	HComplex b( 1, 1 );
	ENSURE_DISTANCE( "bad argument of b value calculted", b.argument(), math::PI / 4.L, epsilon );
	HComplex c( -1, 1 );
	ENSURE_DISTANCE( "bad argument of c value calculted", c.argument(), math::PI - math::PI / 4.L, epsilon );
	HComplex d( -1, -1 );
	ENSURE_DISTANCE( "bad argument of d value calculted", d.argument(), - ( math::PI - math::PI / 4.L ), epsilon );
	HComplex e( 1, -1 );
	ENSURE_DISTANCE( "bad argument of e value calculted", e.argument(), - math::PI / 4.L, epsilon );
	HComplex f( 0, 1 );
	ENSURE_DISTANCE( "bad argument of f value calculted", f.argument(), math::PI / 2.L, epsilon );
	HComplex g( 0, -1 );
	ENSURE_DISTANCE( "bad argument of g value calculted", g.argument(), - math::PI / 2.L, epsilon );
	HComplex h( -1, 0 );
	ENSURE_DISTANCE( "bad argument of h value calculted", h.argument(), math::PI, epsilon );
	HComplex z;
	ENSURE_THROW( "getting argument from 0 + 0i succeeded", z.argument(), HComplexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assignment operator" )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	HComplex b;
	b = a;
	ENSURE_DISTANCE( "re incrorrectly set by assignment operator", b.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by assignment operator", b.im(), math::E, epsilon );
	HComplex c( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", c.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", c.im(), math::E, epsilon );
	double long val( 7 );
	c = val;
	ENSURE_DISTANCE( "re incrorrectly set by assignment operator", c.re(), val, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by assignment operator", c.im(), 0.l, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equality test" )
	HComplex a( math::PI, math::E );
	HComplex b;
	ENSURE_EQUALS( "not equal as equal", a == b, false );
	b = a;
	ENSURE_EQUALS( "equality test failed", a, b );
TUT_TEARDOWN()

TUT_UNIT_TEST( "differentiness test" )
	HComplex a( math::PI, math::E );
	HComplex b;
	ENSURE_EQUALS( "not equal as equal", a != b, true );
	b = a;
	ENSURE_EQUALS( "differentiness test failed", a != b, false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator +=" )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	double long valR( 7 );
	double long valI( 3 );
	a += valR;
	ENSURE_DISTANCE( "re incrorrectly set by operator +=", a.re(), math::PI + valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator +=", a.im(), math::E, epsilon );
	a += HComplex( 0, valI );
	ENSURE_DISTANCE( "re incrorrectly set by operator +=", a.re(), math::PI + valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator +=", a.im(), math::E + valI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator -=" )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	double long valR( 7 );
	double long valI( 3 );
	a -= valR;
	ENSURE_DISTANCE( "re incrorrectly set by operator -=", a.re(), math::PI - valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator -=", a.im(), math::E, epsilon );
	a -= HComplex( 0, valI );
	ENSURE_DISTANCE( "re incrorrectly set by operator -=", a.re(), math::PI - valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator -=", a.im(), math::E - valI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator *=" )
	HComplex aOrig( math::PI, math::E );
	HComplex a( aOrig );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	double long valR( 7 );
	double long valI( 3 );
	a *= valR;
	ENSURE_DISTANCE( "re incrorrectly set by operator *=", a.re(), math::PI * valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *=", a.im(), math::E * valR, epsilon );
	a = aOrig;
	a *= HComplex( valR, 0 );
	ENSURE_DISTANCE( "re incrorrectly set by operator *=", a.re(), math::PI * valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *=", a.im(), math::E * valR, epsilon );
	a = aOrig;
	TUT_EVAL( a *= HComplex( 0, valI ) );
	ENSURE_DISTANCE( "re incrorrectly set by operator *=", a.re(), -( math::E * valI ), epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *=", a.im(), math::PI * valI, epsilon );
	a = aOrig;
	TUT_EVAL( a *= HComplex( valR, valI ) );
	ENSURE_DISTANCE( "re incrorrectly set by operator *=", a.re(), ( math::PI * valR ) - ( math::E * valI ), epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *=", a.im(), math::E * valR + math::PI * valI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator /=" )
	HComplex c( -14, 23 );
	HComplex divisor( 2, 5 );
	TUT_EVAL( c /= divisor );
	ENSURE_DISTANCE( "re incrorrectly set by operator /=", c.re(), 3.L, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /=", c.im(), 4.L, epsilon );
	c.set( -14, 8 );
	TUT_EVAL( c /= 2 );
	ENSURE_DISTANCE( "re incrorrectly set by operator /=", c.re(), -7.L, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /=", c.im(), 4.L, epsilon );
	c.set( -14, 8 );
	TUT_EVAL( c /= 2_yi );
	ENSURE_DISTANCE( "re incrorrectly set by operator /=", c.re(), 4.L, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /=", c.im(), 7.L, epsilon );
	ENSURE_THROW( "division by 0 ignored", c /= 0, HComplexException );
	ENSURE_THROW( "division by 0 ignored", c /= 0_yi, HComplexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator +" )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	double long valR( 7 );
	double long valI( 3 );
	a = a + valR;
	ENSURE_DISTANCE( "re incrorrectly set by operator +", a.re(), math::PI + valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator +", a.im(), math::E, epsilon );
	a = a + HComplex( 0, valI );
	ENSURE_DISTANCE( "re incrorrectly set by operator +", a.re(), math::PI + valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator +", a.im(), math::E + valI, epsilon );
	a = valR + a;
	ENSURE_DISTANCE( "re incrorrectly set by operator +", a.re(), math::PI + 2. * valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator +", a.im(), math::E + valI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator -" )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	double long valR( 7 );
	double long valI( 3 );
	a = a - valR;
	ENSURE_DISTANCE( "re incrorrectly set by operator -", a.re(), math::PI - valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator -", a.im(), math::E, epsilon );
	a = a - HComplex( 0, valI );
	ENSURE_DISTANCE( "re incrorrectly set by operator -", a.re(), math::PI - valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator -", a.im(), math::E - valI, epsilon );
	a = valR - a;
	ENSURE_DISTANCE( "re incrorrectly set by operator -", a.re(), -math::PI + 2 * valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator -", a.im(), -math::E + valI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator *" )
	HComplex aOrig( math::PI, math::E );
	HComplex a( aOrig );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	double long valR( 7 );
	double long valI( 3 );
	a = a * valR;
	ENSURE_DISTANCE( "re incrorrectly set by operator *", a.re(), math::PI * valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *", a.im(), math::E * valR, epsilon );
	a = aOrig;
	a = a * HComplex( valR, 0 );
	ENSURE_DISTANCE( "re incrorrectly set by operator *", a.re(), math::PI * valR, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *", a.im(), math::E * valR, epsilon );
	a = aOrig;
	TUT_EVAL( a = a * HComplex( 0, valI ) );
	ENSURE_DISTANCE( "re incrorrectly set by operator *", a.re(), -( math::E * valI ), epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *", a.im(), math::PI * valI, epsilon );
	a = aOrig;
	TUT_EVAL( a = a * HComplex( valR, valI ) );
	ENSURE_DISTANCE( "re incrorrectly set by operator *", a.re(), ( math::PI * valR ) - ( math::E * valI ), epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *", a.im(), math::E * valR + math::PI * valI, epsilon );
	TUT_EVAL( a = 2. * a );
	ENSURE_DISTANCE( "re incrorrectly set by operator *", a.re(), 2. * ( ( math::PI * valR ) - ( math::E * valI ) ), epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator *", a.im(), 2. * ( math::E * valR + math::PI * valI ), epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator /" )
	HComplex c( -14, 23 );
	HComplex divisor( 2, 5 );
	TUT_EVAL( c = c / divisor );
	ENSURE_DISTANCE( "re incrorrectly set by operator /", c.re(), 3.L, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /", c.im(), 4.L, epsilon );
	c.set( -14, 8 );
	TUT_EVAL( c = c / 2 );
	ENSURE_DISTANCE( "re incrorrectly set by operator /", c.re(), -7.L, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /", c.im(), 4.L, epsilon );
	c.set( -14, 8 );
	TUT_EVAL( c = c / 2_yi );
	ENSURE_DISTANCE( "re incrorrectly set by operator /", c.re(), 4.L, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /", c.im(), 7.L, epsilon );
	ENSURE_THROW( "division by 0 ignored", c / 0, HComplexException );
	ENSURE_THROW( "division by 0 ignored", c / 0.0_yi, HComplexException );
	HComplex n( 2.L );
	n /= c;
	TUT_EVAL( c = 2.L / c );
	ENSURE_DISTANCE( "re incrorrectly set by operator /", c.re(), n.re(), epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by operator /", c.im(), n.im(), epsilon );
TUT_TEARDOWN()

}


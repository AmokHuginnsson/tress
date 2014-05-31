/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hcomplex.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/math.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hcomplex );
TUT_TEST_GROUP( tut_yaal_hcore_hcomplex, "yaal::hcore::HComplex" );

TUT_UNIT_TEST( 1, "Default constructor" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re(), 0.L, epsilon );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Constructor with initialization." )
	HComplex a( math::PI );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	HComplex b( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", b.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", b.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy constructor." )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	HComplex b( a );
	ENSURE_DISTANCE( "re incrorrectly set by copy constructor", b.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by copy constructor", b.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "set_real()" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re(), 0.L, epsilon );
	a.set_real( math::PI );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "set_imaginary()" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
	a.set_imaginary( math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "set both real and imaginary" )
	HComplex a;
	ENSURE_DISTANCE( "non zero new complex number (re)", a.re(), 0.L, epsilon );
	ENSURE_DISTANCE( "non zero new complex number (im)", a.im(), 0.L, epsilon );
	a.set( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "modulus()" )
	HComplex a( 3, 4 );
	ENSURE_DISTANCE( "bad modulus value calculted", a.modulus(), 5.L, epsilon );
	HComplex b( 3 );
	ENSURE_DISTANCE( "bad modulus value calculted", b.modulus(), 3.L, epsilon );
	HComplex c( 0, 4 );
	ENSURE_DISTANCE( "bad modulus value calculted", c.modulus(), 4.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "argument()" )
	HComplex a( 1, 0 );
	ENSURE_DISTANCE( "bad argument value calculted", a.argument(), 0.L, epsilon );
	HComplex b( 1, 1 );
	ENSURE_DISTANCE( "bad argument value calculted", b.argument(), math::PI / 4.L, epsilon );
	HComplex c( -1, 1 );
	ENSURE_DISTANCE( "bad argument value calculted", c.argument(), math::PI - math::PI / 4.L, epsilon );
	HComplex d( -1, -1 );
	ENSURE_DISTANCE( "bad argument value calculted", d.argument(), - ( math::PI - math::PI / 4.L ), epsilon );
	HComplex e( 1, -1 );
	ENSURE_DISTANCE( "bad argument value calculted", e.argument(), - math::PI / 4.L, epsilon );
	HComplex z;
	ENSURE_THROW( "getting argument from 0 + 0i succeeded", z.argument(), HComplexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "asignment operator" )
	HComplex a( math::PI, math::E );
	ENSURE_DISTANCE( "re incrorrectly set by constructor", a.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by constructor", a.im(), math::E, epsilon );
	HComplex b;
	b = a;
	ENSURE_DISTANCE( "re incrorrectly set by copy constructor", b.re(), math::PI, epsilon );
	ENSURE_DISTANCE( "im incrorrectly set by copy constructor", b.im(), math::E, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "equality test" )
	HComplex a( math::PI, math::E );
	HComplex b;
	ENSURE_EQUALS( "not equal as equal", a == b, false );
	b = a;
	ENSURE_EQUALS( "equality test failed", a, b );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "differentiness test" )
	HComplex a( math::PI, math::E );
	HComplex b;
	ENSURE_EQUALS( "not equal as equal", a != b, true );
	b = a;
	ENSURE_EQUALS( "differentiness test failed", a != b, false );
TUT_TEARDOWN()

}


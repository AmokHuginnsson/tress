/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hinterval.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hinterval.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hinterval );
TUT_TEST_GROUP( tut_yaal_hcore_hinterval, "yaal::hcore::HInterval" );

TUT_UNIT_TEST( 1, "default constructor" )
	HInterval<int> i;
	ENSURE_EQUALS( "default constructor set bad infimum", i.inf(), 0 );
	ENSURE_EQUALS( "default constructor set bad supremum", i.sup(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "construction with custom initialization" )
	HInterval<int> i( -1, 1 );
	ENSURE_EQUALS( "custom initialization set bad infimum", i.inf(), -1 );
	ENSURE_EQUALS( "custom initialization set bad supremum", i.sup(), 1 );
	try {
		HInterval<int> bad( 1, -1 );
		FAIL( "creation in invalid interval succeeded" );
	} catch ( HExceptionT<HInterval<int> > const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "addition" )
	HInterval<int> i1( 1, 2 );
	HInterval<int> i2( 3, 4 );
	i1 += i2;
	ENSURE_EQUALS( "addition set bad infimum", i1.inf(), 4 );
	ENSURE_EQUALS( "addition set bad supremum", i1.sup(), 6 );
TUT_TEARDOWN()

}

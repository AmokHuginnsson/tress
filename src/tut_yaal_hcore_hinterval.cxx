/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hinterval.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hinterval );
TUT_TEST_GROUP( tut_yaal_hcore_hinterval, "yaal::hcore::HInterval" );

TUT_UNIT_TEST( "default constructor" )
	HInterval<int> i;
	ENSURE_EQUALS( "default constructor set bad infimum", i.inf(), 0 );
	ENSURE_EQUALS( "default constructor set bad supremum", i.sup(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "construction with custom initialization" )
	HInterval<int> i( -1, 1 );
	ENSURE_EQUALS( "custom initialization set bad infimum", i.inf(), -1 );
	ENSURE_EQUALS( "custom initialization set bad supremum", i.sup(), 1 );
	ENSURE_THROW( "creation in invalid interval succeeded", HInterval<int> bad( 1, -1 ), HExceptionT<HInterval<int> > );
TUT_TEARDOWN()

TUT_UNIT_TEST( "addition" )
	HInterval<int> i1( 1, 2 );
	HInterval<int> i2( 3, 4 );
	i1 += i2;
	ENSURE_EQUALS( "addition set bad infimum", i1.inf(), 4 );
	ENSURE_EQUALS( "addition set bad supremum", i1.sup(), 6 );
TUT_TEARDOWN()

}


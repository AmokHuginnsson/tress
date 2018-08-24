/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/math.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::math;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_math );
TUT_TEST_GROUP( tut_yaal_math, "yaal::math" );

TUT_UNIT_TEST( "greatest_common_divisor" )
	ENSURE_EQUALS( "greatest_common_divisor 0 0 failed", greatest_common_divisor( 0, 0 ), 0L );
	ENSURE_EQUALS( "greatest_common_divisor 0 1 failed", greatest_common_divisor( 0, 1 ), 1L );
	ENSURE_EQUALS( "greatest_common_divisor 2 0 failed", greatest_common_divisor( 2, 0 ), 2L );
	ENSURE_EQUALS( "greatest_common_divisor 13 17 failed", greatest_common_divisor( 13, 17 ), 1L );
	ENSURE_EQUALS( "greatest_common_divisor 16 24 failed", greatest_common_divisor( 16, 24 ), 8L );
	ENSURE_EQUALS( "greatest_common_divisor 814001929 6324168833 failed", greatest_common_divisor( 814001929, 6324168833 ), 62615533L );
TUT_TEARDOWN()

}


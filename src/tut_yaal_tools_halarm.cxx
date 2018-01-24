/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/halarm.hxx>
#include <yaal/tools/sleep.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_halarm );
TUT_TEST_GROUP( tut_yaal_tools_halarm, "yaal::tools::HAlarm" );

TUT_UNIT_TEST( "alarm wake" )
#ifdef __HOST_OS_TYPE_CYGWIN__
/* *FIXME TODO*: Try to enable on Cygwin eventually. */
	SKIP( "Cygwin platform error." );
#endif /* #ifdef __HOST_OS_TYPE_CYGWIN__ */
	TIME_CONSTRAINT_EXEMPT();
	static int const ALARM_TIME( 2000 );
	HAlarm alarm( ALARM_TIME );
	HClock c;
	bool interrupted( ! sleep_for( duration( 128, time::UNIT::SECOND ) ) );
	if ( ! interrupted ) {
		cerr << "sleep ended after: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << " miliseconds" << endl;
	}
	ENSURE( "alarm failed to interrupt sleep", interrupted );
TUT_TEARDOWN()

TUT_UNIT_TEST( "alarm deregistered" )
#ifdef __MSVCXX__
	if ( tress::setup._jobs > 1 ) {
		SKIP( "Alien signal can messup this test." );
	}
#endif
	TIME_CONSTRAINT_EXEMPT();
	static int const ALARM_TIME( 500 ); {
		HAlarm alarm( ALARM_TIME );
		ENSURE( "alarm interrupted sleep prematurely", sleep_for( duration( 100, time::UNIT::MILLISECOND ) ) );
	}
	ENSURE( "alaram did not deregister!", sleep_for( duration( 1, time::UNIT::SECOND ) ) );
TUT_TEARDOWN()

}


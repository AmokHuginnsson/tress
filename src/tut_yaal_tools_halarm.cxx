/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_halarm.cxx - this file is integral part of `tress' project.

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


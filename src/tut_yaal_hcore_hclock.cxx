/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hclock.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hclock.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::meta;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hclock );
TUT_TEST_GROUP( tut_yaal_hcore_hclock, "yaal::hcore::HClock" );

TUT_UNIT_TEST( 1, "1 second accuracy" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	TUT_EVAL( util::sleep::second( SLEEP ) );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "1 mili-second accuracy" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,3>::value;
	static int long const QUALITY = get_speed( HClock::UNIT::MILISECOND ) + 2;
	HClock clk;
	TUT_EVAL( util::sleep::second( SLEEP ) );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( HClock::UNIT::MILISECOND ), PASSED, QUALITY );
	cout << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "1 micro-second accuracy" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,6>::value;
	static int long const QUALITY = get_speed( HClock::UNIT::MICROSECOND ) + 2 * power<10,3>::value;
	HClock clk;
	TUT_EVAL( util::sleep::second( SLEEP ) );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( HClock::UNIT::MICROSECOND ), PASSED, QUALITY );
	cout << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "1 nano-second accuracy" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,9>::value;
	static int long const QUALITY = get_speed( HClock::UNIT::NANOSECOND ) + 2 * power<10,6>::value;
	HClock clk;
	TUT_EVAL( util::sleep::second( SLEEP ) );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( HClock::UNIT::NANOSECOND ), PASSED, QUALITY );
	cout << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "measured twice without reset" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	TUT_EVAL( util::sleep::second( SLEEP ) );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::SECOND, false ), PASSED );
	TUT_EVAL( util::sleep::second( SLEEP ) );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED + PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "measured twice with reset" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	TUT_EVAL( util::sleep::second( SLEEP ) );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::SECOND, true ), PASSED );
	TUT_EVAL( util::sleep::second( SLEEP ) );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED );
TUT_TEARDOWN()

}


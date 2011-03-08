/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hclock.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
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

namespace tut
{

struct tut_yaal_hcore_hclock
	{
	int long get_speed( HClock::UNIT::unit_t const& );
	virtual ~tut_yaal_hcore_hclock( void )
		{}
	};

int long tut_yaal_hcore_hclock::get_speed( HClock::UNIT::unit_t const& u )
	{
	double long PI = 3.14159265;
	static int long const LOOPS = 320000L;
	double long x = PI;
	HClock c;
	for ( int i = 0; i < LOOPS; ++ i )
		x *= PI;
	return ( static_cast<int long>( c.get_time_elapsed( u ) ) );
	}

TUT_TEST_GROUP_N( tut_yaal_hcore_hclock, "yaal::hcore::HClock" );

TUT_UNIT_TEST_N( 1, "1 second accuracy" )
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	util::sleep::second( SLEEP );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "1 mili-second accuracy" )
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,3>::value;
	static int long const QUALITY = get_speed( HClock::UNIT::MILISECOND ) + 2;
	HClock clk;
	util::sleep::second( SLEEP );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( HClock::UNIT::MILISECOND ), PASSED, QUALITY );
	cout << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "1 micro-second accuracy" )
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,6>::value;
	static int long const QUALITY = get_speed( HClock::UNIT::MICROSECOND ) + 2 * power<10,3>::value;
	HClock clk;
	util::sleep::second( SLEEP );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( HClock::UNIT::MICROSECOND ), PASSED, QUALITY );
	cout << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "1 nano-second accuracy" )
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,9>::value;
	static int long const QUALITY = get_speed( HClock::UNIT::NANOSECOND ) + 2 * power<10,6>::value;
	HClock clk;
	util::sleep::second( SLEEP );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( HClock::UNIT::NANOSECOND ), PASSED, QUALITY );
	cout << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "measured twice without reset" )
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	util::sleep::second( SLEEP );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::SECOND, false ), PASSED );
	util::sleep::second( SLEEP );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED + PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "measured twice with reset" )
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	util::sleep::second( SLEEP );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::SECOND, true ), PASSED );
	util::sleep::second( SLEEP );
	get_speed( HClock::UNIT::MILISECOND ); /* Additional sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED );
TUT_TEARDOWN()

}


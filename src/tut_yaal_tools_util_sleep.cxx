/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_util_sleep.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_util_sleep
	{
	virtual ~tut_yaal_tools_util_sleep( void )
		{}
	int long get_speed( HClock::UNIT::unit_t const& );
	};

TUT_TEST_GROUP_N( tut_yaal_tools_util_sleep, "yaal::tools::util::sleep" );

TUT_UNIT_TEST_N( 1, "the 1 second granularity sleep" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const SHOULD_SLEEP_MS = power<10,3>::value;
	int long SKEW( 2 );
	HClock clk;
	cout << "E" << util::sleep::second( SLEEP, true ) << "E" << endl;
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND, false ) << "$" << endl;
	ENSURE_DISTANCE( "under slept by miliseconds", yaal::max( SHOULD_SLEEP_MS - clk.get_time_elapsed( HClock::UNIT::MILISECOND, false ), 0l ), SKEW, SKEW + 1 );
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND ) << "$" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "the 1 milisecond granularity sleep" )
	static int long const SLEEP = 333;
	static int long const SHOULD_SLEEP_MS = 333;
	int long SKEW( 2 );
	HClock clk;
	cout << "E" << util::sleep::milisecond( SLEEP, true ) << "E" << endl;
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND, false ) << "$" << endl;
	ENSURE_DISTANCE( "under slept by miliseconds", yaal::max( SHOULD_SLEEP_MS - clk.get_time_elapsed( HClock::UNIT::MILISECOND, false ), 0l ), SKEW, SKEW + 1 );
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND, false ) << "$" << endl;
TUT_TEARDOWN()

}


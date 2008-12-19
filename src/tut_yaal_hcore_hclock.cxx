/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hclock.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
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
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hclock
	{
	};

TUT_TEST_GROUP( tut_yaal_hcore_hclock, "yaal::hcore::HClock" );

TUT_UNIT_TEST_N( 1, "1 second accuracy" )
	static int long const D_SLEEP = 1;
	static int long const D_PASSED = 1;
	HClock clk;
	::sleep( D_SLEEP );
	ensure_equals( "time measured incorrectly", clk.get_time_elapsed(), D_PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "1 mili-second accuracy" )
	static int long const D_SLEEP = 1;
	static int long const D_PASSED = power<10,3>::value;
	HClock clk;
	::sleep( D_SLEEP );
	ensure_equals( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::D_MILISECOND ), D_PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "1 micro-second accuracy" )
	static int long const D_SLEEP = 1;
	static int long const D_PASSED = power<10,6>::value;
	static int long const D_QUALITY = 50;
	HClock clk;
	::sleep( D_SLEEP );
	ensure_distance( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::D_MICROSECOND ), D_PASSED, D_QUALITY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "1 nano-second accuracy" )
	static int long const D_SLEEP = 1;
	static int long const D_PASSED = power<10,9>::value;
	static int long const D_QUALITY = 20000;
	HClock clk;
	::sleep( D_SLEEP );
	ensure_distance( "time measured incorrectly", clk.get_time_elapsed( HClock::UNIT::D_NANOSECOND ), D_PASSED, D_QUALITY );
TUT_TEARDOWN()

}


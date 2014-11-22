/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_sleep.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/sleep.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::meta;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_sleep : public simple_mock<tut_yaal_tools_sleep> {
	typedef simple_mock<tut_yaal_tools_sleep> base_type;
	virtual ~tut_yaal_tools_sleep( void )
		{}
	int long get_speed( HClock::UNIT::unit_t const& );
};

TUT_TEST_GROUP( tut_yaal_tools_sleep, "yaal::tools::sleep" );

TUT_UNIT_TEST( "the 1 second granularity sleep" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const SHOULD_SLEEP_MS = power<10,3>::value;
	int long SKEW( 2 );
	HClock clk;
	cout << "E" << tools::sleep::second( SLEEP, true ) << "E" << endl;
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND ) << "$" << endl;
	ENSURE_DISTANCE( "under slept by miliseconds", yaal::max( SHOULD_SLEEP_MS - static_cast<int long>( clk.get_time_elapsed( HClock::UNIT::MILISECOND ) ), 0l ), SKEW, SKEW + 1 );
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND ) << "$" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "the 1 milisecond granularity sleep" )
	static int long const SLEEP = 333;
	static int long const SHOULD_SLEEP_MS = 333;
	int long SKEW( 3 );
	HClock clk;
	cout << "E" << tools::sleep::milisecond( SLEEP, true ) << "E" << endl;
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND ) << "$" << endl;
	ENSURE_DISTANCE( "under slept by miliseconds", yaal::max( SHOULD_SLEEP_MS - static_cast<int long>( clk.get_time_elapsed( HClock::UNIT::MILISECOND ) ), 0l ), SKEW, SKEW + 1 );
	cout << "$" << clk.get_time_elapsed( HClock::UNIT::MILISECOND ) << "$" << endl;
TUT_TEARDOWN()

}


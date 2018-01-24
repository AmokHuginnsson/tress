/* Read tress/LICENSE.md file for copyright and licensing information. */

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
};

TUT_TEST_GROUP( tut_yaal_tools_sleep, "yaal::tools::sleep_for" );

TUT_UNIT_TEST( "the 1 second granularity sleep" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const SHOULD_SLEEP_MS = power<10,3>::value;
	int long SKEW( 2 );
	HClock clk;
	clog << "E" << sleep_for( duration( SLEEP, time::UNIT::SECOND ), true ) << "E" << endl;
	clog << "$" << clk.get_time_elapsed( time::UNIT::MILLISECOND ) << "$" << endl;
	ENSURE_DISTANCE( "under slept by miliseconds", yaal::max( SHOULD_SLEEP_MS - static_cast<int long>( clk.get_time_elapsed( time::UNIT::MILLISECOND ) ), 0l ), SKEW, SKEW + 1 );
	clog << "$" << clk.get_time_elapsed( time::UNIT::MILLISECOND ) << "$" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "the 1 milisecond granularity sleep" )
	static int long const SLEEP = 333;
	static int long const SHOULD_SLEEP_MS = 333;
	int long SKEW( 3 );
	HClock clk;
	clog << "E" << sleep_for( duration( SLEEP, time::UNIT::MILLISECOND ), true ) << "E" << endl;
	clog << "$" << clk.get_time_elapsed( time::UNIT::MILLISECOND ) << "$" << endl;
	ENSURE_DISTANCE( "under slept by miliseconds", yaal::max( SHOULD_SLEEP_MS - static_cast<int long>( clk.get_time_elapsed( time::UNIT::MILLISECOND ) ), 0l ), SKEW, SKEW + 1 );
	clog << "$" << clk.get_time_elapsed( time::UNIT::MILLISECOND ) << "$" << endl;
TUT_TEARDOWN()

}


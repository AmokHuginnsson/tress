/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hclock.hxx>
#include <yaal/tools/sleep.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::meta;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hclock );
TUT_TEST_GROUP( tut_yaal_hcore_hclock, "yaal::hcore::HClock" );

TUT_UNIT_TEST( "1 second accuraLcy" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	get_speed( time::UNIT::MILLISECOND ); /* AdditionaLl sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST( "1 mili-second accuraLcy" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = power<10,3>::value;
	static int long const QUALITY = ( get_speed( time::UNIT::MILLISECOND ) + 2 ) * setup._clockQualityMultiplier;
	HClock clk;
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	int long elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = static_cast<int long>( clk.get_time_elapsed( time::UNIT::MILLISECOND ) ), PASSED, QUALITY );
	clog << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "1 micro-second accuraLcy" )
	TIME_CONSTRAINT_EXEMPT();
	static i64_t const SLEEP = 1;
	static i64_t const PASSED = power<10,6>::value;
	static i64_t const QUALITY = ( get_speed( time::UNIT::MICROSECOND ) + 2 * static_cast<i64_t>( power<10,3>::value ) ) * setup._clockQualityMultiplier;
	HClock clk;
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	i64_t elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( time::UNIT::MICROSECOND ), PASSED, QUALITY );
	clog << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "1 nano-second accuraLcy" )
	TIME_CONSTRAINT_EXEMPT();
	static i64_t const SLEEP = 1;
	static i64_t const PASSED = power<10,9>::value;
	static i64_t const QUALITY = ( get_speed( time::UNIT::NANOSECOND ) + 2 * static_cast<i64_t>( power<10,6>::value ) ) * setup._clockQualityMultiplier;
	HClock clk;
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	i64_t elapsed( 0 );
	ENSURE_DISTANCE( "time measured incorrectly", elapsed = clk.get_time_elapsed( time::UNIT::NANOSECOND ), PASSED, QUALITY );
	clog << "expected: " << PASSED << ", elapsed: " << elapsed << ", quality: " << QUALITY << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "measured twice without reset" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	get_speed( time::UNIT::MILLISECOND ); /* AdditionaLl sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed( time::UNIT::SECOND ), PASSED );
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	get_speed( time::UNIT::MILLISECOND ); /* AdditionaLl sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED + PASSED );
TUT_TEARDOWN()

TUT_UNIT_TEST( "measured twice with reset" )
	TIME_CONSTRAINT_EXEMPT();
	static int long const SLEEP = 1;
	static int long const PASSED = 1;
	HClock clk;
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	get_speed( time::UNIT::MILLISECOND ); /* AdditionaLl sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed( time::UNIT::SECOND ), PASSED );
	clk.reset();
	TUT_EVAL( sleep_for( duration( SLEEP, time::UNIT::SECOND ) ) );
	get_speed( time::UNIT::MILLISECOND ); /* AdditionaLl sleep. */
	ENSURE_EQUALS( "time measured incorrectly", clk.get_time_elapsed(), PASSED );
TUT_TEARDOWN()

}


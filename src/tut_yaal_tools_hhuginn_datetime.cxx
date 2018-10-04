/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_datetime : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_datetime( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_datetime, "yaal::tools::HHuginn.DateTime" );

namespace {

#ifdef CONTINUOUS_INTEGRATION_APPVEYOR
char const WAIT[] = "dt.sleep(10000000000);m = c.milliseconds()/1000;";
#else
char const WAIT[] = "dt.sleep(1000000000);m = c.milliseconds()/100;";
#endif

}

TUT_UNIT_TEST( "setters & getters" )
#if defined( __HOST_OS_TYPE_FREEBSD__ ) || defined( __HOST_OS_TYPE_SOLARIS__ )
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"0001-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"0011-04-02 14:55:14\"]";
#elif SIZEOF_TIME_T == 8
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"1-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"11-04-02 14:55:14\"]";
#elif defined( __MSVCXX__ )
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"0001-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"1981-04-02 14:55:14\"]";
#elif defined( __HOST_OS_TYPE_DEBIAN__ ) || defined( __HOST_OS_TYPE_RASPBIAN__ )
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"1-02-03 23:30:17\", 1978, 5, 24, 23, 30, 17, \"1981-04-02 14:55:14\"]";
#else
	char const setterExpect[] = "[\"1979-05-24 23:30:17\", \"1978-05-24 01:02:03\", \"1901-12-13 22:30:17\", 1978, 5, 24, 23, 30, 17, \"1981-04-02 14:55:14\"]";
#endif
	ENSURE_EQUALS(
		"Time setters/getters failed",
		execute(
			"import DateTime as dt;"
			"import Algorithms as algo;"
			"main(){"
			"t = dt.now();"
			"t.set_datetime(1978,5,24,23,30,17);"
			"s = copy(t).from_string(\"1989-08-24 14:25:31\");"
			"r=[copy(t).mod_year(1),copy(t).set_time(1,2,3),copy(t).set_date(1,2,3),t.get_year(),t.get_month(),t.get_day(),t.get_hour(),t.get_minute(),t.get_second(),s-t];"
			"return(algo.materialize(algo.map(r,@(x){type(x)==type(dt.now())?string(x):x;}),list));"
			"}"
		),
		setterExpect
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_date/set_datetime invalid" )
	ENSURE_EQUALS(
		"Time bad setter succeeded",
		execute(
			"import DateTime as dt;"
			"main(){"
			"try{"
			"t = dt.now();"
			"t.set_date(1,13,1);"
			"}catch(DateTimeException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:57: bad month in year\""
	);
	ENSURE_EQUALS(
		"Time bad setter succeeded",
		execute(
			"import DateTime as dt;"
			"main(){"
			"try{"
			"t = dt.now();"
			"t.set_datetime(1,1,1,1,60,1);"
			"}catch(DateTimeException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:61: bad minute\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "from_string invalid" )
	ENSURE_EQUALS(
		"Time bad from_string succeeded",
		execute(
			"import DateTime as dt;"
			"main(){"
			"try{"
			"t = dt.now();"
			"t.from_string(\"invalid\");"
			"}catch(DateTimeException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:60: Could not parse `invalid' as `%Y-%m-%d %T'.\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "clock, sleep" )
	ENSURE_EQUALS(
		"DateTime.clock, DateTime.sleep falied",
		execute(
			"import DateTime as dt;"
			"main(){"
			"c = dt.clock();"_ys.append(
				WAIT
			).append(
				"return(m);"
				"}"
			)
		),
		"10"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Clock.reset" )
	ENSURE_EQUALS(
		"Clock.reset, Clock.to_string falied",
		execute(
			"import DateTime as dt;"
			"main(){"
			"c = dt.clock();"_ys.append(
				WAIT
			).append(
				"c.reset();"
				"s=string(c);"
				"return([m,s.find(\"second\")>0 || s == \"0s\"]);"
				"}"
			)
		),
		"[10, true]"
	);

	hcore::HString res(
		execute(
			"import DateTime as dt;"
			"main(){"
			"return(string(dt.now()));"
			"}"
		)
	);
	res.trim( "\"" );
	HTime now( now_local() );
	hcore::HString nowS0( now.string() );
	now.mod_second( -1 );
	hcore::HString nowSP( now.string() );
	now.mod_second( 2 );
	hcore::HString nowSN( now.string() );
	ENSURE( "DateTime.now falied", ( res == nowS0 ) || ( res == nowSP ) || ( res == nowSN ) );
TUT_TEARDOWN()

}

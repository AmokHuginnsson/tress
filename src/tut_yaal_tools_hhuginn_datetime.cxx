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

TUT_UNIT_TEST( "get_day_of_week invalid" )
	ENSURE_EQUALS(
		"get_day_of_week failed",
		execute(
			"import DateTime as dt;"
			"main(){"
			"t=dt.now();"
			"return (("
			" t.set_date(1978,5,24).get_day_of_week(),"
			" t.set_date(1,1,1).get_day_of_week()"
			"));"
			"}"
		),
		"(2, 0)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_days_in_month invalid" )
	ENSURE_EQUALS(
		"get_days_in_month failed",
		execute(
			"import DateTime as dt;"
			"main(){"
			"t=dt.now();"
			"return (("
			" t.set_date(2012,2,1).get_days_in_month(),"
			" t.set_date(1900,2,1).get_days_in_month(),"
			" t.set_date(2000,2,1).get_days_in_month(),"
			" t.set_date(2011,2,1).get_days_in_month(),"
			" t.set_date(1,1,1).get_days_in_month(),"
			" t.set_date(1989,4,1).get_days_in_month()"
			"));"
			"}"
		),
		"(29, 28, 29, 28, 31, 30)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "format invalid" )
	ENSURE_EQUALS(
		"format failed",
		execute(
			"import DateTime as dt;"
			"main(){"
			"t=dt.now().set_datetime(1978,5,24,23,30,17);"
			"return (("
			" dt.format(\"%Y %B %d\",t),"
			" dt.format(\"%A %T\",t),"
			" dt.format(\"%FT%T\",t)"
			"));"
			"}"
		),
		"(\"1978 May 24\", \"Wednesday 23:30:17\", \"1978-05-24T23:30:17\")"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "equals invalid" )
	ENSURE_EQUALS(
		"equals failed",
		execute(
			"import DateTime as dt;"
			"main(){"
			"t1=dt.now().set_datetime(1978,5,24,23,30,17);"
			"t2=dt.now().set_datetime(1978,5,24,23,30,17);"
			"t3=dt.now();"
			"return (("
			" t1 == t2,"
			" t1 == t3"
			"));"
			"}"
		),
		"(true, false)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "less invalid" )
	ENSURE_EQUALS(
		"less failed",
		execute(
			"import DateTime as dt;"
			"main(){"
			"t1=dt.now().set_datetime(1978,5,24,23,30,17);"
			"t2=dt.now().set_datetime(1978,5,24,23,30,17);"
			"t3=dt.now();"
			"return (("
			" t1 < t2,"
			" t1 < t3"
			"));"
			"}"
		),
		"(false, true)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "hash invalid" )
	ENSURE_IN(
		"hash failed",
		execute(
			"import DateTime as dt;"
			"import Introspection as intro;"
			"main(){"
			"t1=dt.now().set_datetime(1978,5,24,23,30,17);"
			"t2=dt.now().set_datetime(1,1,1,0,0,0);"
			"return (( intro.hash(t1), intro.hash(t2) ));"
			"}"
		),
		std::vector<HString>({
			"(62432112617, 62167219199)",
			"(62432112617, 31617360)",
			"(62432112617, 31621839)",
			"(2302570473, 2037677055)",
			"(-1992396823, 2037677055)"
		})
	);
TUT_TEARDOWN()

}


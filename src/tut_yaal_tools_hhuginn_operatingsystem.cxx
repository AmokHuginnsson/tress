/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hpipe.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hstringstream.hxx>
#include <yaal/tools/sleep.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_operatingsystem : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_operatingsystem( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_operatingsystem, "yaal::tools::HHuginn.OperatingSystem" );

namespace {

char const CHILD[] = "./data/child" EXE_SUFFIX;
#ifndef __MSVCXX__
	char const EXPECTED_EXEC[] = "No such file or directory";
#else /* #ifndef __MSVCXX__ */
	char const EXPECTED_EXEC[] = "The system cannot find the file specified";
#endif /* #else #ifndef __MSVCXX__ */

}

TUT_UNIT_TEST( "env" )
	ENSURE_EQUALS(
		"OperatingSystem.env",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return( ["
			"	os.env(\"DEFAULT_TARGET\"),"
			"	os.env(\"DEFAULT_TARGET\", \"relassert\"),"
			"	os.env(\"MY_TARGET\", \"relassert\")"
			"] );"
			"}"
		),
		"[\"debug\", \"debug\", \"relassert\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_env" )
	ENSURE_EQUALS(
		"OperatingSystem.set_env failed",
		execute(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"res = [os.env(\"NEW_ENV_HUGINN_VAR\")];\n"
			"os.set_env(\"NEW_ENV_HUGINN_VAR\", \"value\");\n"
			"res.push(os.env(\"NEW_ENV_HUGINN_VAR\"));\n"
			"return(res);\n"
			"}\n"
		),
		"[none, \"value\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "getuid" )
	ENSURE_EQUALS(
		"OperatingSystem.getuid",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.getuid());"
			"}"
		),
		to_string( system::get_user_id() )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "getgid" )
	ENSURE_EQUALS(
		"OperatingSystem.getgid",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.getgid());"
			"}"
		),
		to_string( system::get_group_id() )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "getpid" )
	ENSURE_EQUALS(
		"OperatingSystem.getpid",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.getpid());"
			"}"
		),
		to_string( system::getpid() )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "exec (invalid)" )
	ENSURE_EQUALS(
		"OperatingSystem.exec",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"try{"
			"os.exec(\"/non/existing\",\"arg1\");"
			"}catch(OperatingSystemException  e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:48: "_ys.append( EXPECTED_EXEC ).append( "\"" )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn" )
	/* It is impossible to test exit(). */
	ENSURE_EQUALS(
		"OperatingSystem.spawn, is_alive, wait, in, out, err",
		execute(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"c=os.spawn(\""_ys.append( CHILD ).append(
				"\");\n"
				"a0=c.is_alive();\n"
				"c.in().write_line(\"out\\n\");\n"
				"ro=c.out().read_line().strip();\n"
				"s=c.wait(8);\n"
				"a1=c.is_alive();\n"
				"c=os.spawn(\""
			).append( CHILD ).append(
				"\");\n"
				"c.in().write_line(\"err\\n\");\n"
				"re=c.err().read_line().strip();\n"
				"return([a0,ro,re,a1,s]);\n"
				"}\n"
			)
		),
		"[true, \"hello-OUT\", \"hello-ERR\", false, 0]"
	);
	ENSURE_EQUALS(
		"OperatingSystem.spawn",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"try{"
			"os.spawn(\"non-existing\");"
			"}catch(OperatingSystemException e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:49: "_ys.append( EXPECTED_EXEC ).append( ": non-existing\"" )
	);
TUT_TEARDOWN()

#ifndef SIGTERM
#define SIGTERM 15
#endif
#ifndef __MSVCXX__

TUT_UNIT_TEST( "wait" )
	HClock c;
	HHuginn h;
	HPipe io;
	h.set_output_stream( io.in() );
	HStringStream source(
		"import OperatingSystem as os;"
		"main(){"
		"c=os.spawn(\"/bin/sleep\", \"10\");"
		"os.stdout().write_line( \"{}\\n\".format( c.get_pid() ) );\n"
		"c.wait(5);\n"
		"}"
	);
	h.load( source );
	h.preprocess();
	ENSURE( "parsing failed", h.parse() );
	ENSURE( "compilation failed", h.compile() );
	HThread t;
	hcore::HString result;
	t.spawn(
		HThread::call_t(
			[&h, &result]() {
				try {
					result = h.execute() ? 1 : 0;
				} catch ( HException const& e ) {
					result = e.what();
				} catch ( std::exception const& e ) {
					result = e.what();
				} catch ( ... ) {
					result = "unknown exception type";
				}
			}
		)
	);
	HStreamInterface::ptr_t out( io.out() );
	hcore::HString line;
	getline( *out, line );
	int pid( lexical_cast<int>( line ) );
	for ( int i( 0 ); i < 256; ++ i ) {
		if ( system::kill( pid, SIGTERM ) != 0 ) {
			break;
		}
		sleep_for( time::duration( 256, time::UNIT::MICROSECOND ) );
	}
	t.finish();
	ENSURE_EQUALS( "Subprocess.wait() failed", result, "1" );
#ifndef __HOST_OS_TYPE_CYGWIN__ /* Cygwin implementation of process handling is buggy as hell. */
	ENSURE_EQUALS( "Subprocess.get_pid() failed", c.get_time_elapsed( time::UNIT::SECOND ), 0 );
#endif /* #ifndef __HOST_OS_TYPE_CYGWIN__ */
TUT_TEARDOWN()

#ifndef __HOST_OS_TYPE_CYGWIN__ /* Cygwin implementation of process handling is buggy as hell. */
TUT_UNIT_TEST( "kill" )
	HClock c;
	ENSURE_EQUALS(
		"Subprocess.kill() failed",
		execute(
			"import OperatingSystem as os;"
			"import DateTime as dt;"
			"main(){"
			"c=os.spawn(\"/bin/sleep\", \"10\");"
			"dt.sleep(100000000);\n"
			"c.kill();\n"
			"}"
		),
		to_string( SIGTERM )
	);
	ENSURE( "Subprocess.kill() failed", c.get_time_elapsed( time::UNIT::SECOND ) <= 1 );
TUT_TEARDOWN()

#undef SIGTERM
#endif /* #ifndef __HOST_OS_TYPE_CYGWIN__ */
#endif /* #ifndef __MSVCXX__ */

TUT_UNIT_TEST( "invalid wait" )
	ENSURE_EQUALS(
		"Subprocess bad wait succeded",
		execute_except(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"c=os.spawn(\""_ys.append( CHILD ).append(
				"\");\n"
				"c.wait(-1);\n"
				"}\n"
			)
		),
		"*anonymous stream*:4:7: invalid wait time: -1"
	);
TUT_TEARDOWN()

#ifndef __HOST_OS_TYPE_CYGWIN__ /* Cygwin implementation of process handling is buggy as hell. */
TUT_UNIT_TEST( "spawn no wait" )
	ENSURE_EQUALS(
		"Subprocess bad wait succeded",
		execute_except(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"copy(os.spawn(\""_ys.append( CHILD ).append(
				"\"));\n"
				"}\n"
			)
		),
		"*anonymous stream*:3:5: Copy semantics is not supported on Subprocess."
	);
TUT_TEARDOWN()
#endif /* #ifndef __HOST_OS_TYPE_CYGWIN__ */

}


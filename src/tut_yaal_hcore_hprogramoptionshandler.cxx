/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hprogramoptionshandler.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hprogram_options_handler : simple_mock<tut_yaal_hcore_hprogram_options_handler> {
	typedef simple_mock<tut_yaal_hcore_hprogram_options_handler> base_type;
	bool _restartable;
	int _jobs;
	int _testNumber;
	HString _logPath;
	HString _testGroup;
	HString _testGroupPattern;
	tut_yaal_hcore_hprogram_options_handler( void )
		: base_type(),
		_restartable( false ), _jobs( 0 ), _testNumber( 0 ),
		_logPath(), _testGroup(), _testGroupPattern()
		{}
	virtual ~tut_yaal_hcore_hprogram_options_handler( void ) {}
};

TUT_TEST_GROUP( tut_yaal_hcore_hprogram_options_handler, "yaal::hcore::HProgramOptionsHandler" );

TUT_UNIT_TEST( "duplicated long option" )
	HProgramOptionsHandler po;
	try {
		int otherValue( 0 );
		po(
			HProgramOptionsHandler::HOption()
			.long_form( "log_path" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "path pointing to file for application logs" )
			.recipient( _logPath )
			.argument_name( "path" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'j' )
			.long_form( "jobs" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "number of concurrent jobs" )
			.recipient( _jobs )
			.argument_name( "count" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'G' )
			.long_form( "group" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test group" )
			.recipient( _testGroup )
			.argument_name( "name" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'P' )
			.long_form( "pattern" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test groups that are matching pattern" )
			.recipient( _testGroupPattern )
			.argument_name( "pattern" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'N' )
			.long_form( "number" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( _testNumber )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'X' )
			.long_form( "number" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( otherValue )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'R' )
			.long_form( "restartable" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
			.description( "run tests in restartable mode" )
			.recipient( _restartable )
		);
		FAIL( "program options handler with duplicated long option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated short option" )
	HProgramOptionsHandler po;
	try {
		int otherValue( 0 );
		po(
			HProgramOptionsHandler::HOption()
			.long_form( "log_path" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "path pointing to file for application logs" )
			.recipient( _logPath )
			.argument_name( "path" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'j' )
			.long_form( "jobs" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "number of concurrent jobs" )
			.recipient( _jobs )
			.argument_name( "count" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'G' )
			.long_form( "group" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test group" )
			.recipient( _testGroup )
			.argument_name( "name" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'P' )
			.long_form( "pattern" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test groups that are matching pattern" )
			.recipient( _testGroupPattern )
			.argument_name( "pattern" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'N' )
			.long_form( "number" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( _testNumber )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'N' )
			.long_form( "other" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
			.description( "select test number for a given group" )
			.recipient( otherValue )
			.argument_name( "number" )
		)(
			HProgramOptionsHandler::HOption()
			.short_form( 'R' )
			.long_form( "restartable" )
			.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
			.description( "run tests in restartable mode" )
			.recipient( _restartable )
		);
		FAIL( "program options handler with duplicated short option created" );
	} catch ( HProgramOptionsHandlerException const& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated long option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log_path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( _logPath )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( _jobs )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'G' )
		.long_form( "group" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test group" )
		.recipient( _testGroup )
		.argument_name( "name" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'P' )
		.long_form( "pattern" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test groups that are matching pattern" )
		.recipient( _testGroupPattern )
		.argument_name( "pattern" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'X' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( _restartable )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "duplicated short option, duplication is legeal due to usage of the same physical value destination" )
	HProgramOptionsHandler po;
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log_path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( _logPath )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( _jobs )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'G' )
		.long_form( "group" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test group" )
		.recipient( _testGroup )
		.argument_name( "name" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'P' )
		.long_form( "pattern" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test groups that are matching pattern" )
		.recipient( _testGroupPattern )
		.argument_name( "pattern" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "other" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( _testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( _restartable )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "command line" )
	HProgramOptionsHandler po;
	int i( 0 );
	double d( 0 );
	HString s;
	HString optO;
	HString optP;
	bool optS( false );
	bool flag( false );
	bool b( false );
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log-path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( s )
		.default_value( "log.txt" )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( i )
		.default_value( 7 )
		.argument_name( "count" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'r' )
		.long_form( "ratio" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "expected pass/fail ratio" )
		.recipient( d )
		.default_value( .5 )
		.argument_name( "value" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( b )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'O' )
		.long_form( "option" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "argument is optional" )
		.recipient(	optO )
		.argument_name( "arg" )
		.default_value( "defArg" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'P' )
		.long_form( "parameter" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "argument is required" )
		.recipient(	optP )
		.argument_name( "arg" )
		.default_value( "defParam" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'F' )
		.long_form( "flag" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "flags argument is forbidden" )
		.recipient(	flag )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'S' )
		.long_form( "switch" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "switches argument is forbidden" )
		.recipient(	optS )
	);
	char const cmdLineData[][20] = {
		"prog",
		"-FS",
		"-r7",
		"nonOpt",
		"--parameter=XX",
		"nonOpt2",
		"--option"
	};
	char* cmdLine[countof ( cmdLineData )];
	int n( 0 );
	for ( char const* p : cmdLineData ) {
		cmdLine[n] = const_cast<char*>( p );
		++ n;
	}
	int nonOpt( po.process_command_line( countof ( cmdLine ), cmdLine ) );
	ENSURE( "flag not set", flag );
	ENSURE( "switch not set", optS );
	ENSURE_NOT( "restartable set", b );
	ENSURE_DISTANCE( "bad ratio", d, 7., static_cast<double>( epsilon ) );
	ENSURE_EQUALS( "bad param", optP, "XX" );
	ENSURE_EQUALS( "bad param", optO, "" );
	ENSURE_EQUALS( "bad nonOpt score", nonOpt, countof ( cmdLineData ) - 2 );
TUT_TEARDOWN()

}


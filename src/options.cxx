/*
---       `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	options.cxx - this file is integral part of `tress' project.

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

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <libintl.h>

#include "config.hxx"

#include <yaal/hcore/hprogramoptionshandler.hxx>
#include <yaal/hcore/hlog.hxx>
#include <yaal/hcore/base.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )

#include "options.hxx"
#include "setup.hxx"
#include "commit_id.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace yaal {

template<>
yaal::hcore::HString lexical_cast( yaal::hcore::HDeque<yaal::hcore::HString> const& ) {
	return ( "" );
}

}

namespace tress {

namespace {

bool set_variables( HString& option_, HString& value_ ) {
	static bool const TRESS_RC_DEBUG( !! ::getenv( "TRESS_RC_DEBUG" ) );
	if ( TRESS_RC_DEBUG ) {
		cout << "option: [" << option_ << "], value: [" << value_ << "]" << endl;
	}
	return ( true );
}

void version( void ) {
	cout << PACKAGE_STRING << ( setup._verbose ? " " COMMIT_ID : "" ) << endl;
	return;
}

}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */
int handle_program_options( int argc_, char** argv_ ) {
	M_PROLOG
	HProgramOptionsHandler po;
	OOptionInfo info( po, setup._programName, "yaal stress testing suite", NULL );
	bool help( false );
	bool dumpConf( false );
	bool vers( false );
	bool noColor( false );
	int dummyValue( 0 );
	HString ignore;
	HString testFilter;
	po(
		HProgramOptionsHandler::HOption()
		.long_form( "log-path" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "path pointing to file for application logs" )
		.recipient( setup._logPath )
		.argument_name( "path" )
		.default_value( "tress.log" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'j' )
		.long_form( "jobs" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "number of concurrent jobs" )
		.recipient( setup._jobs )
		.argument_name( "count" )
		.default_value( OSetup::DEFAULT_JOB_COUNT )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'A' )
		.long_form( "force-run-all" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "force all tests to be run, even explicitly marked as those to be skipped" )
		.recipient( setup._forceRunAll )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'r' )
		.long_form( "reporter" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "generator for reporting test results =(TUT|boost|google|cppunit|xml|QT|cute)" )
		.recipient( setup._reporter )
		.argument_name( "framework" )
		.default_value( "tut" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'I' )
		.long_form( "error-line" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "line format for error reporting =(console|vim|eclipse|visualstudio)" )
		.recipient( setup._errorLine )
		.argument_name( "IDE" )
		.default_value( "console" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'C' )
		.long_form( "color" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "colorize output" )
		.recipient( setup._color )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "fancy" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "provide fancy test run output" )
		.recipient( setup._fancy )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "no-color" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "disable output colorizing" )
		.recipient( noColor )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'T' )
		.long_form( "time-constraint" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "constrain time for execution of single unit test" )
		.recipient( setup._timeConstraint )
		.argument_name( "duration" )
		.default_value( to_string( OSetup::DEFAULT_TIME_CONSTRAINT ).append( "s" ) )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'G' )
		.long_form( "group" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test group" )
		.recipient( setup._testGroups )
		.argument_name( "name" )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "output_format" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "boost reporter option (ignored)" )
		.recipient( ignore )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "log_level" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "boost reporter option (ignored)" )
		.recipient( ignore )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "report_level" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "boost reporter option (ignored)" )
		.recipient( ignore )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "run_test" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "boost runner option (converted to -G)" )
		.recipient( testFilter )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "gtest_repeat" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "google reporter option (ignored)" )
		.recipient( ignore )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "gtest_print_time" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "google reporter option (ignored)" )
		.recipient( ignore )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "gtest_color" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "google reporter option (converted to -C)" )
		.recipient( setup._color )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "gtest_filter" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "google runner option (converted to -G)" )
		.recipient( testFilter )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "gtest_list_tests" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "google runner option (converted to -L)" )
		.recipient( setup._listGroups )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'S' )
		.long_form( "set" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test group and particular tests within it" )
		.recipient( setup._testSets )
		.argument_name( "name@no1,no2,..." )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'P' )
		.long_form( "pattern" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test groups that are matching pattern" )
		.recipient( setup._testGroupPattern )
		.argument_name( "pattern" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'N' )
		.long_form( "number" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "select test number for a given group" )
		.recipient( setup._testNumber )
		.argument_name( "number" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'R' )
		.long_form( "restartable" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "run tests in restartable mode" )
		.recipient( setup._restartable )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'L' )
		.long_form( "list" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "list known test groups" )
		.recipient( setup._listGroups )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'F' )
		.long_form( "file" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED )
		.description( "read test group names from given file" )
		.recipient( setup._testGroupListFilePath )
		.argument_name( "path" )
	)(
		HProgramOptionsHandler::HOption()
		.long_form( "selftest" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "perform framework tests" )
		.recipient( setup._selftest )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'O' )
		.long_form( "option" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "this is not a real option, it was added here to test automated help generation capabilities,"
			" this description must be long enought to trigger description wrap, more over it must look good" )
		.recipient( dummyValue )
		.argument_name( "param" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'O' )
		.long_form( "absolute" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL )
		.description( "" )
		.recipient( dummyValue )
		.argument_name( "param" )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'E' )
		.long_form( "exit" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "exit program gracefuly and do not perform any test" )
		.recipient( setup._exit )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'q' )
		.long_form( "quiet" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "inhibit usual output" )
		.recipient( setup._quiet )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'q' )
		.long_form( "silent" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "inhibit usual output" )
		.recipient( setup._quiet )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'v' )
		.long_form( "verbose" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "print more information" )
		.recipient( setup._verbose )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'd' )
		.long_form( "debug" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "print debugging information about tress internals" )
		.recipient( setup._debug )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'h' )
		.long_form( "help" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "display this help and stop" )
		.recipient( help )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'W' )
		.long_form( "dump-configuration" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "dump current configuration" )
		.recipient( dumpConf )
	)(
		HProgramOptionsHandler::HOption()
		.short_form( 'V' )
		.long_form( "version" )
		.switch_type( HProgramOptionsHandler::HOption::ARGUMENT::NONE )
		.description( "output version information and stop" )
		.recipient( vers )
	);
	po.process_rc_file( "", set_variables );
	int unknown( 0 );
	int nonOption( po.process_command_line( argc_, argv_, &unknown ) );
	if ( help || dumpConf || vers || ( unknown > 0 ) ) {
		if ( unknown > 0 ) {
			if ( setup._reporter == "qt" )
				cerr << "NOTICE: Remember to add options terminator `--' as last argument while using QT reporter." << endl;
			util::show_help( info );
		} else if ( help ) {
			util::show_help( info );
		} else if ( dumpConf ) {
			util::dump_configuration( info );
		} else if ( vers ) {
			version();
		}
		HLog::disable_auto_rehash();
		throw unknown;
	}
	if ( noColor )
		setup._color = false;
	if ( !testFilter.is_empty() ) {
		int long dot( testFilter.find_one_of( "./" ) );
		if ( dot != HString::npos ) {
			setup._testGroups.push_back( testFilter.left( dot ) );
			HString no( testFilter.mid( dot + 2 ) );
			if ( ! no.is_empty() && ( testFilter[dot + 1] == '<' ) )
				setup._testNumber = lexical_cast<int>( no );
		} else
			setup._testGroups.push_back( testFilter );
	}
	if ( setup._debug ) {
		hcore::log << "arguments:";
		for ( int i( 0 ); i < argc_; ++ i ) {
			hcore::log << " " << argv_[i];
		}
		hcore::log << endl;
	}
	setup._argc = ( argc_ - nonOption ) + 1;
	setup._argv = argv_ + nonOption - 1;
	argv_[ nonOption - 1 ] = argv_[ 0 ];
	return ( nonOption );
	M_EPILOG
}


}


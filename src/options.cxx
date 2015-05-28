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

#include <yaal/hcore/hprogramoptionshandler.hxx>
#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )

#include "options.hxx"
#include "config.hxx"
#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

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
	cout << PACKAGE_STRING << endl;
	return;
}

}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */
int handle_program_options( int argc_, char** argv_ ) {
	M_PROLOG
	HProgramOptionsHandler po;
	OOptionInfo info( po, setup._programName, "yaal stress testing suite", NULL );
	bool stop( false );
	bool noColor( false );
	int dummyValue( 0 );
	HString ignore;
	HString testFilter;
	namespace poh = program_options_helper;
	po(
		"log_path",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"path pointing to file for application logs",
		poh::option_value( setup._logPath ),
		"path"
	)(
		'j',
		"jobs",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"number of concurrent jobs",
		poh::option_value( setup._jobs ),
		"count"
	)(
		'r',
		"reporter",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"generator for reporting test results =(TUT|boost|google|cppunit|xml|QT|cute)",
		poh::option_value( setup._reporter ),
		"framework"
	)(
		'I',
		"error-line",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"line format for error reporting =(console|vim|eclipse|visualstudio)",
		poh::option_value( setup._errorLine ),
		"IDE"
	)(
		'C',
		"color",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"colorize output",
		poh::option_value( setup._color )
	)(
		"fancy",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"provide fancy test run output",
		poh::option_value( setup._fancy )
	)(
		"no-color",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"disable output colorizing",
		poh::option_value( noColor )
	)(
		'T',
		"time-constraint",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"constrain time for execution of single unit test",
		poh::option_value( setup._timeConstraint ),
		"miliseconds"
	)(
		'G',
		"group",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test group",
		poh::option_value( setup._testGroups ),
		"name"
	)(
		"output_format",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"boost reporter option (ignored)",
		poh::option_value( ignore )
	)(
		"log_level",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"boost reporter option (ignored)",
		poh::option_value( ignore )
	)(
		"report_level",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"boost reporter option (ignored)",
		poh::option_value( ignore )
	)(
		"run_test",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"boost runner option (converted to -G)",
		poh::option_value( testFilter )
	)(
		"gtest_repeat",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"google reporter option (ignored)",
		poh::option_value( ignore )
	)(
		"gtest_print_time",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"google reporter option (ignored)",
		poh::option_value( ignore )
	)(
		"gtest_color",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"google reporter option (converted to -C)",
		poh::option_value( setup._color )
	)(
		"gtest_filter",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"google runner option (converted to -G)",
		poh::option_value( testFilter )
	)(
		"gtest_list_tests",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"google runner option (converted to -L)",
		poh::option_value( setup._listGroups )
	)(
		'S',
		"set",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test group and particular tests within it",
		poh::option_value( setup._testSets ),
		"name@no1,no2,..."
	)(
		'P',
		"pattern",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test groups that are matching pattern",
		poh::option_value( setup._testGroupPattern ),
		"pattern"
	)(
		'N',
		"number",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"select test number for a given group",
		poh::option_value( setup._testNumber ),
		"number"
	)(
		'R',
		"restartable",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"run tests in restartable mode",
		poh::option_value( setup._restartable )
	)(
		'L',
		"list",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"list known test groups",
		poh::option_value( setup._listGroups )
	)(
		'F',
		"file",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"read test group names from given file",
		poh::option_value( setup._testGroupListFilePath ),
		"path"
	)(
		"selftest",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"perform framework tests",
		poh::option_value( setup._selftest )
	)(
		'O',
		"option",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"this is not a real option, it was added here to test automated help generation capabilities,"
		" this description must be long enought to trigger description wrap, more over it must look good",
		poh::option_value( dummyValue ),
		"param"
	)(
		'O',
		"absolute",
		HProgramOptionsHandler::HOption::ARGUMENT::OPTIONAL,
		"",
		poh::option_value( dummyValue ),
		"param"
	)(
		'E',
		"exit",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"exit program gracefuly and do not perform any test",
		poh::option_value( setup._exit )
	)(
		'q',
		"quiet",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"inhibit usual output",
		poh::option_value( setup._quiet )
	)(
		'q',
		"silent",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"inhibit usual output",
		poh::option_value( setup._quiet )
	)(
		'v',
		"verbose",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"print more information",
		poh::option_value( setup._verbose )
	)(
		'd',
		"debug",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"print debugging information about tress internals",
		poh::option_value( setup._debug )
	)(
		'h',
		"help",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"display this help and stop",
		poh::option_value( stop ),
		"",
		"",
		call( &util::show_help, &info )
	)(
		'W',
		"dump-configuration",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"dump current configuration",
		poh::option_value( stop ),
		"",
		"",
		call( &util::dump_configuration, &info )
	)(
		'V',
		"version",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"output version information and stop",
		poh::option_value( stop ),
		"",
		"",
		call( &version )
	);
	po.process_rc_file( "tress", "", set_variables );
	if ( setup._logPath.is_empty() )
		setup._logPath = "tress.log";
	int unknown( 0 );
	int nonOption( po.process_command_line( argc_, argv_, &unknown ) );
	if ( stop || ( unknown > 0 ) ) {
		if ( unknown > 0 ) {
			if ( setup._reporter == "qt" )
				cerr << "NOTICE: Remember to add options terminator `--' as last argument while using QT reporter." << endl;
			util::show_help( &info );
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
		log << "arguments:";
		for ( int i( 0 ); i < argc_; ++ i )
			log << " " << argv_[i];
		log << endl;
	}
	setup._argc = ( argc_ - nonOption ) + 1;
	setup._argv = argv_ + nonOption - 1;
	argv_[ nonOption - 1 ] = argv_[ 0 ];
	return ( nonOption );
	M_EPILOG
}


}


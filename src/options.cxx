/*
---       `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	options.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <libintl.h>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "options.hxx"
#include "config.hxx"
#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tress
{

bool set_variables( HString& option_, HString& value_ )
	{
	::fprintf( stdout, "option: [%s], value: [%s]\n",
			option_.raw(), value_.raw() );
	return ( false );
	}

void version( void* ) __attribute__(( __noreturn__ ));
void version( void* )
	{
	cout << PACKAGE_STRING << endl;
	throw ( 0 );
	}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */
int handle_program_options( int argc_, char** argv_ )
	{
	M_PROLOG
	HProgramOptionsHandler po;
	OOptionInfo info( po, setup._programName, "yaal stress testing suite", NULL );
	bool stop( false );
	bool noColor( false );
	int dummyValue( 0 );
	po( "log_path", program_options_helper::option_value( setup._logPath ), HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path pointing to file for application logs", "path" )
		( "jobs", program_options_helper::option_value( setup._jobs ), 'j', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "number of concurrent jobs", "count" )
		( "error-line", program_options_helper::option_value( setup._errorLine ), 'I', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "generator for reporting errors", "IDE" )
		( "color", program_options_helper::option_value( setup._color ), 'C', HProgramOptionsHandler::OOption::TYPE::NONE, "colorize output" )
		( "fancy", program_options_helper::option_value( setup._fancy ), HProgramOptionsHandler::OOption::TYPE::NONE, "provide fancy test run output" )
		( "no-color", program_options_helper::option_value( noColor ), HProgramOptionsHandler::OOption::TYPE::NONE, "disable output colorizing" )
		( "time-constraint", program_options_helper::option_value( setup._timeConstraint ), 'T', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "constrain time for execution of single unit test", "miliseconds" )
		( "group", program_options_helper::option_value( setup._testGroups ), 'G', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test group", "name" )
		( "pattern", program_options_helper::option_value( setup._testGroupPattern ), 'P', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test groups that are matching pattern", "pattern" )
		( "number", program_options_helper::option_value( setup._testNumber ), 'N', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "select test number for a given group", "number" )
		( "restartable", program_options_helper::option_value( setup._restartable ), 'R', HProgramOptionsHandler::OOption::TYPE::NONE, "run tests in restartable mode" )
		( "list", program_options_helper::option_value( setup._listGroups ), 'L', HProgramOptionsHandler::OOption::TYPE::NONE, "list known test groups" )
		( "file", program_options_helper::option_value( setup._testGroupListFilePath ), 'F', HProgramOptionsHandler::OOption::TYPE::REQUIRED, "read test group names from given file", "path" )
		( "option", program_options_helper::option_value( dummyValue ), 'O', HProgramOptionsHandler::OOption::TYPE::OPTIONAL, "this is not a real option, it was added here to test automated help generation capabilities, this description must be long enought to trigger description wrap, more over it must look good", "param" )
		( "absolute", program_options_helper::option_value( dummyValue ), 'O', HProgramOptionsHandler::OOption::TYPE::OPTIONAL, NULL, "param" )
		( "exit", program_options_helper::option_value( setup._exit ), 'E', HProgramOptionsHandler::OOption::TYPE::NONE, "exit program gracefuly and do not perform any test" )
		( "quiet", program_options_helper::option_value( setup._quiet ), 'q', HProgramOptionsHandler::OOption::TYPE::NONE, "inhibit usual output" )
		( "silent", program_options_helper::option_value( setup._quiet ), 'q', HProgramOptionsHandler::OOption::TYPE::NONE, "inhibit usual output" )
		( "verbose", program_options_helper::option_value( setup._verbose ), 'v', HProgramOptionsHandler::OOption::TYPE::NONE, "print more information" )
		( "debug", program_options_helper::option_value( setup._debug ), 'd', HProgramOptionsHandler::OOption::TYPE::NONE, "print debugging information about tress internals" )
		( "help", program_options_helper::option_value( stop ), 'h', HProgramOptionsHandler::OOption::TYPE::NONE, "display this help and stop", program_options_helper::callback( util::show_help, &info ) )
		( "dump-configuration", program_options_helper::option_value( stop ), 'W', HProgramOptionsHandler::OOption::TYPE::NONE, "dump current configuration", program_options_helper::callback( util::dump_configuration, &info ) )
		( "version", program_options_helper::no_value, 'V', HProgramOptionsHandler::OOption::TYPE::NONE, "output version information and stop", program_options_helper::callback( version, NULL ) );
	po.process_rc_file( "tress", "", NULL );
	if ( setup._logPath.is_empty() )
		setup._logPath = "tress.log";
	int unknown = 0, nonOption = 0;
	nonOption = po.process_command_line( argc_, argv_, &unknown );
	if ( unknown > 0 )
		{
		util::show_help( &info );
		throw unknown;
		}
	if ( stop )
		throw 0;
	if ( noColor )
		setup._color = false;
	setup._argc = ( argc_ - nonOption ) + 1;
	setup._argv = argv_ + nonOption - 1;
	argv_[ nonOption - 1 ] = argv_[ 0 ];
	return ( nonOption );
	M_EPILOG
	}


}


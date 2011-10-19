/*
---       `child' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	options.cxx - this file is integral part of `child' project.

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
#include <cstdio>
#include <cstring>

#include <yaal/hcore/hprogramoptionshandler.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "options.hxx"
#include "config.hxx"
#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace child {

bool set_variables( HString& option_, HString& value_ ) {
	::fprintf( stdout, "option: [%s], value: [%s]\n",
			option_.raw(), value_.raw() );
	return ( false );
}

void version( void* ) __attribute__(( __noreturn__ ));
void version( void* ) {
	cout << PACKAGE_STRING << endl;
	throw ( 0 );
}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */
int handle_program_options( int argc_, char** argv_ ) {
	M_PROLOG
	HProgramOptionsHandler po;
	OOptionInfo info( po, setup._programName, "does very much usefull things ... really", NULL );
	bool stop = false;
	po( "log_path", program_options_helper::option_value( setup._logPath ), HProgramOptionsHandler::OOption::TYPE::REQUIRED, "path pointing to file for application logs", "path" )
		( "exit_status", program_options_helper::option_value( setup._exitStatus ), 'E' ,HProgramOptionsHandler::OOption::TYPE::REQUIRED, "set exit status for child", "status" )
		( "terminate", program_options_helper::option_value( setup._terminate ), 'T' ,HProgramOptionsHandler::OOption::TYPE::REQUIRED, "terminate process abruptly", "signal" )
		( "script", program_options_helper::option_value( setup._script ), 'S' ,HProgramOptionsHandler::OOption::TYPE::REQUIRED, "run this script in child session", "code" )
		( "quiet", program_options_helper::option_value( setup._quiet ), 'q', HProgramOptionsHandler::OOption::TYPE::NONE, "inhibit usual output" )
		( "silent", program_options_helper::option_value( setup._quiet ), 'q', HProgramOptionsHandler::OOption::TYPE::NONE, "inhibit usual output" )
		( "verbose", program_options_helper::option_value( setup._verbose ), 'v', HProgramOptionsHandler::OOption::TYPE::NONE, "print more information" )
		( "help", program_options_helper::option_value( stop ), 'h', HProgramOptionsHandler::OOption::TYPE::NONE, "display this help and stop", program_options_helper::callback( util::show_help, &info ) )
		( "dump-configuration", program_options_helper::option_value( stop ), 'W', HProgramOptionsHandler::OOption::TYPE::NONE, "dump current configuration", program_options_helper::callback( util::dump_configuration, &info ) )
		( "version", program_options_helper::no_value, 'V', HProgramOptionsHandler::OOption::TYPE::NONE, "output version information and stop", program_options_helper::callback( version, NULL ) );
	po.process_rc_file( "child", "", NULL );
	if ( setup._logPath.is_empty() )
		setup._logPath = "child.log";
	int unknown = 0, nonOption = 0;
	nonOption = po.process_command_line( argc_, argv_, &unknown );
	if ( unknown > 0 ) {
		util::show_help( &info );
		throw unknown;
	}
	if ( stop )
		throw 0;
	return ( nonOption );
	M_EPILOG
}


}


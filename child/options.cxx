/*
---       `child' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	options.cxx - this file is integral part of `child' project.

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
#include <cstdio>
#include <cstring>

#include <yaal/hcore/hprogramoptionshandler.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )

#include "options.hxx"
#include "config.hxx"
#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace child {

#ifndef __clang__
void version( void ) __attribute__(( __noreturn__ ));
#endif /* #ifndef __clang__ */
void version( void ) {
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
	po(
		"log_path",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"path pointing to file for application logs",
		program_options_helper::option_value( setup._logPath ),
		"path"
	)(
		'E',
		"exit_status",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"set exit status for child",
		program_options_helper::option_value( setup._exitStatus ),
		"status"
	)(
		'T',
		"terminate",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"terminate process abruptly",
		program_options_helper::option_value( setup._terminate ),
		"signal"
	)(
		'S',
		"script",
		HProgramOptionsHandler::HOption::ARGUMENT::REQUIRED,
		"run this script in child session",
		program_options_helper::option_value( setup._script ),
		"code"
	)(
		'q',
		"quiet",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"inhibit usual output",
		program_options_helper::option_value( setup._quiet )
	)(
		'q',
		"silent",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"inhibit usual output",
		program_options_helper::option_value( setup._quiet )
	)(
		'v',
		"verbose",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"print more information",
		program_options_helper::option_value( setup._verbose )
	)(
		'h',
		"help",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"display this help and stop",
		program_options_helper::option_value( stop ),
		"",
		"",
		call( &util::show_help, &info )
	)(
		'W',
		"dump-configuration",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"dump current configuration",
		program_options_helper::option_value( stop ),
		"",
		"",
		call( &util::dump_configuration, &info )
	)(
		'V',
		"version",
		HProgramOptionsHandler::HOption::ARGUMENT::NONE,
		"output version information and stop",
		program_options_helper::no_value,
		"",
		"",
		call( &version )
	);
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


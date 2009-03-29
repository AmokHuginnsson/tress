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
#include "version.hxx"
#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tress
{

bool set_variables( HString& a_roOption, HString& a_roValue )
	{
	::fprintf( stdout, "option: [%s], value: [%s]\n",
			a_roOption.raw(), a_roValue.raw() );
	return ( false );
	}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */

void usage( void* ) __attribute__((__noreturn__));
void usage( void* arg )
	{
	OOptionInfo* info = static_cast<OOptionInfo*>( arg );
	info->PROC( info->_opt, setup.f_pcProgramName, "yaal stress testing suite", NULL );
	throw ( setup.f_bHelp ? 0 : 1 );
	}

void version( void* ) __attribute__ ( ( __noreturn__ ) );
void version( void* )
	{
	printf ( "`tress' %s\n", VER );
	throw ( 0 );
	}

namespace
{

HProgramOptionsHandler::simple_callback_t help( usage, NULL );
HProgramOptionsHandler::simple_callback_t dump( usage, NULL );
HProgramOptionsHandler::simple_callback_t version_call( version, NULL );

}

int handle_program_options( int a_iArgc, char** a_ppcArgv )
	{
	M_PROLOG
	HProgramOptionsHandler po;
	po( "log_path", program_options_helper::option_value( setup.f_oLogPath ), NULL, HProgramOptionsHandler::OOption::TYPE::D_REQUIRED, "path", "path pointing to file for application logs", NULL )
		( "jobs", program_options_helper::option_value( setup.f_iJobs ), "j", HProgramOptionsHandler::OOption::TYPE::D_REQUIRED, "count", "number of concurrent jobs", NULL )
		( "group", program_options_helper::option_value( setup.f_oTestGroup ), "G", HProgramOptionsHandler::OOption::TYPE::D_REQUIRED, "name", "select test group", NULL )
		( "pattern", program_options_helper::option_value( setup.f_oTestGroupPattern ), "P", HProgramOptionsHandler::OOption::TYPE::D_REQUIRED, "pattern", "select test groups that are matching pattern", NULL )
		( "number", program_options_helper::option_value( setup.f_iTestNumber ), "N", HProgramOptionsHandler::OOption::TYPE::D_REQUIRED, "number", "select test number for a given group", NULL )
		( "restartable", program_options_helper::option_value( setup.f_bRestartable ), "R", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "run tests in restartable mode", NULL )
		( "list", program_options_helper::option_value( setup.f_bListGroups ), "L", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "list known test groups", NULL )
		( "file", program_options_helper::option_value( setup.f_oTestGroupListFilePath ), "F", HProgramOptionsHandler::OOption::TYPE::D_REQUIRED, "path", "read test group names from given file", NULL )
		( "option", program_options_helper::no_value, "O", HProgramOptionsHandler::OOption::TYPE::D_OPTIONAL, "param", "this is not a real option, it was added here to test automated help generation capabilities, this description must be long enought to trigger description wrap, more over is must look good", NULL )
		( "absolute", program_options_helper::no_value, "O", HProgramOptionsHandler::OOption::TYPE::D_OPTIONAL, "param", NULL, NULL )
		( "quiet", program_options_helper::option_value( setup.f_bQuiet ), "q", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "inhibit usual output", NULL )
		( "silent", program_options_helper::option_value( setup.f_bQuiet ), "q", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "inhibit usual output", NULL )
		( "verbose", program_options_helper::option_value( setup.f_bVerbose ), "v", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "print more information", NULL )
		( "help", program_options_helper::option_value( setup.f_bHelp ), "h", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "display this help and exit", &help )
		( "dump-configuration", program_options_helper::no_value, "W", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "dump current configuration", &dump )
		( "version", program_options_helper::no_value, "V", HProgramOptionsHandler::OOption::TYPE::D_NONE, NULL, "output version information and exit", &version_call );
	po.process_rc_file( "tress", "", NULL );
	if ( setup.f_oLogPath.is_empty() )
		setup.f_oLogPath = "tress.log";
	int l_iUnknown = 0, l_iNonOption = 0;
	OOptionInfo info( po.get_options(), util::show_help );
	OOptionInfo infoConf( po.get_options(), util::dump_configuration );
	help.second = &info;
	dump.second = &infoConf;
	l_iNonOption = po.process_command_line( a_iArgc, a_ppcArgv, &l_iUnknown );
	if ( l_iUnknown > 0 )
		usage( &info );
	return ( l_iNonOption );
	M_EPILOG
	}


}


/*
---       `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski         ---

	options.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <libintl.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

#include "options.h"
#include "version.h"
#include "setup.h"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tress
{

bool set_variables( HString& a_roOption, HString& a_roValue )
	{
	::fprintf( stdout, "option: [%s], value: [%s]\n",
			static_cast<char const* const>( a_roOption ),
			static_cast<char const* const>( a_roValue ) );
	return ( false );
	}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */

void usage( void* ) __attribute__((__noreturn__));
void usage( void* arg )
	{
	OOptionInfo* info = static_cast<OOptionInfo*>( arg );
	info->PROC( info->_opt, info->_size, setup.f_pcProgramName, "yaal stress testing suite", NULL );
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

simple_callback_t help( usage, NULL );
simple_callback_t dump( usage, NULL );
simple_callback_t version_call( version, NULL );
OOption n_psOptions[] =
	{
		{ "log_path", D_HSTRING, &setup.f_oLogPath, NULL, OOption::D_REQUIRED, "path", "path pointing to file for application logs", NULL },
		{ "jobs", D_INT, &setup.f_iJobs, "j", OOption::D_REQUIRED, "count", "number of concurrent jobs", NULL },
		{ "group", D_HSTRING, &setup.f_oTestGroup, "G", OOption::D_REQUIRED, "name", "select test group", NULL },
		{ "pattern", D_HSTRING, &setup.f_oTestGroupPattern, "P", OOption::D_REQUIRED, "pattern", "select test groups that are matching pattern", NULL },
		{ "number", D_INT, &setup.f_iTestNumber, "N", OOption::D_REQUIRED, "number", "select test number for a given group", NULL },
		{ "restartable", D_BOOL, &setup.f_bRestartable, "R", OOption::D_NONE, NULL, "run tests in restartable mode", NULL },
		{ "list", D_BOOL, &setup.f_bListGroups, "L", OOption::D_NONE, NULL, "list known test groups", NULL },
		{ "file", D_HSTRING, &setup.f_oTestGroupListFilePath, "F", OOption::D_REQUIRED, "path", "read test group names from given file", NULL },
		{ "option", D_VOID, NULL, "O", OOption::D_OPTIONAL, "param", "this is not a real option, it was added here to test automated help generation capabilities, this description must be long enought to trigger description wrap, more over is must look good", NULL },
		{ "absolute", D_VOID, NULL, "O", OOption::D_OPTIONAL, "param", NULL, NULL },
		{ "quiet", D_BOOL, &setup.f_bQuiet, "q", OOption::D_NONE, NULL, "inhibit usual output", NULL },
		{ "silent", D_BOOL, &setup.f_bQuiet, "q", OOption::D_NONE, NULL, "inhibit usual output", NULL },
		{ "verbose", D_BOOL, &setup.f_bVerbose, "v", OOption::D_NONE, NULL, "print more information", NULL },
		{ "help", D_BOOL, &setup.f_bHelp, "h", OOption::D_NONE, NULL, "display this help and exit", &help },
		{ "dump-configuration", D_VOID, NULL, "W", OOption::D_NONE, NULL, "dump current configuration", &dump },
		{ "version", D_VOID, NULL, "V", OOption::D_NONE, NULL, "output version information and exit", &version_call },
		{ NULL, D_VOID, NULL, NULL, OOption::D_NONE, NULL, NULL, NULL }
	};

}

int process_tressrc_file( void )
	{
	rc_file::process_rc_file ( "tress", NULL, n_psOptions, NULL );
	if ( ! setup.f_oLogPath )
		setup.f_oLogPath = "tress.log";
	return ( 0 );
	}

int decode_switches( int a_iArgc, char** a_ppcArgv )
	{
	M_PROLOG
	int l_iUnknown = 0, l_iNonOption = 0;
	OOptionInfo info( n_psOptions, sizeof ( n_psOptions ) / sizeof ( OOption ), util::show_help );
	OOptionInfo infoConf( n_psOptions, sizeof ( n_psOptions ) / sizeof ( OOption ), util::dump_configuration );
	help.second = &info;
	dump.second = &infoConf;
	l_iNonOption = cl_switch::decode_switches( a_iArgc, a_ppcArgv, n_psOptions,
			info._size, &l_iUnknown );
	if ( l_iUnknown > 0 )
		usage( &info );
	if ( setup.f_bListGroups
			&& ( setup.f_bRestartable || setup.f_oTestGroupListFilePath || setup.f_oTestGroup
				|| setup.f_oTestGroupPattern || setup.f_iTestNumber ) )
		M_THROW ( _ ( "group listing conflicts with other switches" ),
				setup.f_iTestNumber );
	if ( setup.f_bRestartable
			&& ( setup.f_oTestGroupListFilePath || setup.f_oTestGroup || setup.f_oTestGroupPattern
				|| setup.f_iTestNumber ) )
		M_THROW ( _ ( "restartable conflicts with other switches" ),
				setup.f_iTestNumber );
	if ( setup.f_oTestGroupListFilePath
			&& ( setup.f_oTestGroup || setup.f_oTestGroupPattern || setup.f_iTestNumber ) )
		M_THROW ( _ ( "group names file is an exclusive switch" ),
				setup.f_iTestNumber );
	if ( setup.f_oTestGroup && setup.f_oTestGroupPattern )
		M_THROW ( _ ( "pattern and group switches are exclusive" ), errno );
	if ( setup.f_oTestGroupPattern && setup.f_iTestNumber )
		M_THROW ( _ ( "setting test number for pattern makes no sense" ),
				setup.f_iTestNumber );
	if ( setup.f_iTestNumber && ! setup.f_oTestGroup )
		M_THROW ( _ ( "must specify test group for test number" ),
				setup.f_iTestNumber );
	return ( l_iNonOption );
	M_EPILOG
	}

}


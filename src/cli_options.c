/*
---             `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski              ---

	cli_options.c - this file is integral part of `tress' project.

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

#include <stdlib.h>
#include <stdio.h>
#include <libintl.h>

#include <stdhapi.h>

#include "cli_options.h"
#include "version.h"
#include "setup.h"

using namespace stdhapi;
using namespace stdhapi::hcore;
  
/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */

void usage ( void ) __attribute__ ( ( __noreturn__ ) );
void usage ( void )
	{
	printf ( "%s - \
stdhapi stress testing suite\n", setup.f_pcProgramName );
	printf ( "Usage: %s [OPTION]... [FILE]...\n", setup.f_pcProgramName );
	printf (
"Options:\n"
"  -G --group                 select test group\n"
"  -P --pattern               select test groups that are matching pattern\n"
"  -N --number                select test number for a given group\n"
"  -R --restartable           run tests in restartable mode\n"
"  -F --file                  read test group names from given file\n"
"  -L --list                  list known test groups\n"
"  -q, --quiet, --silent      inhibit usual output\n"
"  --verbose                  print more information\n"
"  -h, --help                 display this help and exit\n"
"  -V, --version              output version information and exit\n" );
	exit ( setup.f_bHelp ? 0 : 1 );
	}

void version ( void ) __attribute__ ( ( __noreturn__ ) );
void version ( void )
	{
	printf ( "`tress' %s\n", VER );
	exit ( 0 );
	}

int decode_switches ( int a_iArgc, char ** a_ppcArgv )
	{
	M_PROLOG
	int l_iUnknown = 0, l_iNonOption = 0;
	OOption l_psOptions [ ] =
		{
			{ "group",				'G', OOption::D_REQUIRED,	D_HSTRING,	& setup.f_oTestGroup,							NULL },
			{ "pattern",			'P', OOption::D_REQUIRED,	D_HSTRING,	& setup.f_oTestGroupPattern,			NULL },
			{ "number",				'N', OOption::D_REQUIRED,	D_INT,			& setup.f_iTestNumber,						NULL },
			{ "restartable",	'R', OOption::D_NONE,			D_BOOL,			& setup.f_bRestartable,						NULL },
			{ "list",					'L', OOption::D_NONE,			D_BOOL,			& setup.f_bListGroups,						NULL },
			{ "file",					'F', OOption::D_REQUIRED,	D_HSTRING,	& setup.f_oTestGroupListFilePath,	NULL },
			{ "quiet",				'q', OOption::D_NONE,			D_BOOL,			& setup.f_bQuiet,									NULL },
			{ "silent",				'q', OOption::D_NONE,			D_BOOL,			& setup.f_bQuiet,									NULL },
			{ "verbose",			'v', OOption::D_NONE,			D_BOOL,			& setup.f_bVerbose,								NULL },
			{ "help",					'h', OOption::D_NONE,			D_BOOL,			& setup.f_bHelp,									usage },
			{ "version",			'V', OOption::D_NONE,			D_VOID,			NULL,															version }
		};
	l_iNonOption = cl_switch::decode_switches ( a_iArgc, a_ppcArgv, l_psOptions,
			sizeof ( l_psOptions ) / sizeof ( OOption ), & l_iUnknown );
	if ( l_iUnknown > 0 )
		usage ( );
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
		M_THROW ( _ ( "pattern and group switches are exclusive" ), g_iErrNo );
	if ( setup.f_oTestGroupPattern && setup.f_iTestNumber )
		M_THROW ( _ ( "setting test number for pattern makes no sense" ),
				setup.f_iTestNumber );
	if ( setup.f_iTestNumber && ! setup.f_oTestGroup )
		M_THROW ( _ ( "must specify test group for test number" ),
				setup.f_iTestNumber );
	return ( l_iNonOption );
	M_EPILOG
	}


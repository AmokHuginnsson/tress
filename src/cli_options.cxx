/*
---             `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski              ---

	cli_options.cxx - this file is integral part of `tress' project.

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

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

#include "cli_options.h"
#include "version.h"
#include "setup.h"

using namespace yaal;
using namespace yaal::hcore;

#define D_GROUP_SHORT				"G"
#define D_GROUP_LONG				"group"
#define D_PATTERN_SHORT			"P"
#define D_PATTERN_LONG			"pattern"
#define D_NUMBER_SHORT			"N"
#define D_NUMBER_LONG				"number"
#define D_RESTARTABLE_SHORT	"R"
#define D_RESTARTABLE_LONG	"restartable"
#define D_FILE_SHORT				"F"
#define D_FILE_LONG					"file"
#define D_LIST_SHORT				"L"
#define D_LIST_LONG					"list"
#define D_QUIET_SHORT				"q"
#define D_QUIET_LONG				"quiet"
#define D_SILENT_LONG				"silent"
#define D_VERBOSE_SHORT			"v"
#define D_VERBOSE_LONG			"verbose"
#define D_HELP_SHORT				"h"
#define D_HELP_LONG					"help"
#define D_VERSION_SHORT			"V"
#define D_VERSION_LONG			"version"

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.                    */

void usage ( void ) __attribute__ ( ( __noreturn__ ) );
void usage ( void )
	{
	printf ( "%s - \
yaal stress testing suite\n", setup.f_pcProgramName );
	printf ( "Usage: %s [OPTION]... [FILE]...\n", setup.f_pcProgramName );
	printf (
"Options:\n"
"  -"D_GROUP_SHORT" --"D_GROUP_LONG"                 select test group\n"
"  -"D_PATTERN_SHORT" --"D_PATTERN_LONG"               select test groups that are matching pattern\n"
"  -"D_NUMBER_SHORT" --"D_NUMBER_LONG"                select test number for a given group\n"
"  -"D_RESTARTABLE_SHORT" --"D_RESTARTABLE_LONG"           run tests in restartable mode\n"
"  -"D_FILE_SHORT" --"D_FILE_LONG"                  read test group names from given file\n"
"  -"D_LIST_SHORT" --"D_LIST_LONG"                  list known test groups\n"
"  -"D_QUIET_SHORT			", --"D_QUIET_LONG", --"D_SILENT_LONG"      inhibit usual output\n"
"  -"D_VERBOSE_SHORT		", --"D_VERBOSE_LONG		""    "              print more information\n"
"  -"D_HELP_SHORT				", --"D_HELP_LONG				"" "                 display this help and exit\n"
"  -"D_VERSION_SHORT		", --"D_VERSION_LONG		""    "              output version information and exit\n" );
	throw ( setup.f_bHelp ? 0 : 1 );
	}

void version ( void ) __attribute__ ( ( __noreturn__ ) );
void version ( void )
	{
	printf ( "`tress' %s\n", VER );
	throw ( 0 );
	}

int decode_switches ( int a_iArgc, char ** a_ppcArgv )
	{
	M_PROLOG
	int l_iUnknown = 0, l_iNonOption = 0;
	OOption l_psOptions [ ] =
		{
			{ D_GROUP_LONG,				D_GROUP_SHORT, OOption::D_REQUIRED,	D_HSTRING,	& setup.f_oTestGroup,							NULL },
			{ D_PATTERN_LONG,			D_PATTERN_SHORT, OOption::D_REQUIRED,	D_HSTRING,	& setup.f_oTestGroupPattern,			NULL },
			{ D_NUMBER_LONG,			D_NUMBER_SHORT, OOption::D_REQUIRED,	D_INT,			& setup.f_iTestNumber,						NULL },
			{ D_RESTARTABLE_LONG,	D_RESTARTABLE_SHORT, OOption::D_NONE,			D_BOOL,			& setup.f_bRestartable,						NULL },
			{ D_LIST_LONG,				D_LIST_SHORT, OOption::D_NONE,			D_BOOL,			& setup.f_bListGroups,						NULL },
			{ D_FILE_LONG,				D_FILE_SHORT, OOption::D_REQUIRED,	D_HSTRING,	& setup.f_oTestGroupListFilePath,	NULL },
			{ D_QUIET_LONG	,			D_QUIET_SHORT,			OOption::D_NONE,	D_BOOL,	&setup.f_bQuiet,		NULL },
			{ D_SILENT_LONG,			D_QUIET_SHORT,			OOption::D_NONE,	D_BOOL,	&setup.f_bQuiet,		NULL },
			{ D_VERBOSE_LONG,			D_VERBOSE_SHORT,		OOption::D_NONE,	D_BOOL,	&setup.f_bVerbose,	NULL },
			{ D_HELP_LONG,				D_HELP_SHORT,				OOption::D_NONE,	D_BOOL,	&setup.f_bHelp,		usage },
			{ D_VERSION_LONG,			D_VERSION_SHORT,		OOption::D_NONE,	D_VOID,	NULL,								version }
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


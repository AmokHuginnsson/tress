/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	prog.c - this file is integral part of `tress' project.

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

#include "TUT/tut_restartable.h"
#include "TUT/tut_reporter.h"

#include <unistd.h>
#include <stdhapi.h>    /* all hAPI headers */

#include "version.h"
#include "define.h"
#include "variables.h"
#include "cli_options.h"
#include "rc_options.h"

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

namespace tut
	{
  test_runner_singleton runner;
	}

int main ( int a_iArgc, char * a_ppcArgv [ ] )
	{
	M_PROLOG
/*	variables declarations for main loop:                                 */
	int l_iOpt = 0;
	HString l_oLine;
	FILE * l_psFile = NULL;
	tut::reporter l_oVisitor ( cerr );
	tut::restartable_wrapper l_oRestartable;
	list < string > l_oGroupNames;
/*	end.                                                                  */
	try
		{
/*	TO-DO:				enter main loop code here                               */
		signals::set_handlers ( );
		g_pcProgramName = a_ppcArgv [ 0 ];
		process_tressrc_file ( );
		l_iOpt = decode_switches ( a_iArgc, a_ppcArgv );
		hcore::log.rehash ( g_oLogPath, g_pcProgramName );
		g_iArgc = ( a_iArgc - l_iOpt ) + 1;
		if ( g_iArgc > 1 )
			{
			g_ppcArgv = a_ppcArgv + l_iOpt - 1;
			a_ppcArgv [ l_iOpt - 1 ] = a_ppcArgv [ 0 ];
			}
//		if ( ! is_enabled ( ) )enter_curses (); /* enabling ncurses ablilities*/
/* *BOOM* */
		g_iErrNo = 0;
		try
			{
			if ( g_bListGroups )
				{
				std::cerr << "registered test groups:" << std::endl;
				tut::groupnames gl = tut::runner.get ( ).list_groups();
				tut::groupnames::const_iterator i = gl.begin();
				tut::groupnames::const_iterator e = gl.end();
				while ( i != e )
					{
					std::cout << "  " << *i << std::endl;
					++ i;
					}
				}
			else if ( g_bRestartable )
				{
				l_oRestartable.set_callback ( & l_oVisitor );
				l_oRestartable.run_tests ( );
				}
			else
				{
				runner.get ( ).set_callback ( & l_oVisitor );
				if ( g_oTestGroupListFilePath )
					{
					if ( g_oTestGroupListFilePath == "-" )
						l_psFile = stdin;
					HFile l_oFile ( HFile::D_READING, l_psFile );
					if ( ! l_psFile && l_oFile.open ( g_oTestGroupListFilePath ) )
						{
						cout << l_oFile.get_error ( ) << ": " << l_oFile.get_path ( ) << endl;
						throw 0;
						}
					while ( l_oFile.read_line ( l_oLine,
								HFile::D_UNBUFFERED_READS | HFile::D_STRIP_NEWLINES ) >= 0 )
						{
						l_oLine.trim_left ( );
						l_oLine.trim_right ( );
						l_oGroupNames.push_back ( static_cast < char const * > ( l_oLine ) );
						}
					l_oFile.close ( );
					runner.get ( ).run_tests ( l_oGroupNames );
					}
				else if ( g_oTestGroupPattern )
					runner.get ( ).run_pattern_tests (
							static_cast < char * > ( g_oTestGroupPattern ) );
				else if ( g_oTestGroup && g_iTestNumber )
					runner.get ( ).run_test ( static_cast < char * > ( g_oTestGroup ),
							g_iTestNumber );
				else if ( g_oTestGroup )
					{
					l_oGroupNames.push_back ( static_cast < char * > ( g_oTestGroup ) );
					runner.get ( ).run_tests ( l_oGroupNames );
					}
				else
					runner.get ( ).run_tests ( );
				}
			}
		catch ( const std::exception & e )
			{
			std::cerr << "tut raised ex: " << e.what ( ) << std::endl;
			}
//		if ( is_enabled ( ) )leave_curses ();  /* ending ncurses sesion    */
		M_ENSURE ( ! g_iErrNo );
/*	... there is the place main loop ends. :OD-OT                         */
		}
	catch ( int& )
		{
		/* escape from main loop */
		}
	catch ( ... ) 
		{
/* ending ncurses sesion        */
		if ( is_enabled ( ) )leave_curses ();
		throw;
		}
	fprintf ( stderr, "Done.\n" );
	return ( 0 );
	M_FINAL
	}


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

#include <tut_restartable.h>
#include <tut_reporter.h>

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

typedef enum
	{
	ONE,
	TWO,
	THREE
	} my_en;

M_DEFINE_ENUM_OPERATORS ( my_en );

namespace tut
	{
  test_runner_singleton n_oRunner;
	}

int main ( int a_iArgc, char * a_ppcArgv [ ] )
	{
	M_PROLOG
/*	variables declarations for main loop:                                 */
	int l_iOpt = 0;
/*	end.                                                                  */
	try
		{
/*	TO-DO:				enter main loop code here                               */
		signals::set_handlers ( );
		g_pcProgramName = a_ppcArgv [ 0 ];
		process_tressrc_file ( );
		l_iOpt = decode_switches ( a_iArgc, a_ppcArgv );
		hcore::log.rehash ( g_oLogPath, g_pcProgramName );
//		if ( ! is_enabled ( ) )enter_curses (); /* enabling ncurses ablilities*/
/* *BOOM* */
		g_iErrNo = 0;
		if ( g_iTestNumber && ! g_oTestGroup )
			M_THROW ( _ ( "must specify test group for test number" ), g_iTestNumber );
		try
			{
	    tut::reporter l_oVisitor;
  	  tut::restartable_wrapper l_oRestartable;
			l_oRestartable.set_callback ( & l_oVisitor );
			if ( ! ( g_iTestNumber || g_oTestGroup ) )
				l_oRestartable.run_tests ( );
			else if ( ! g_iTestNumber )
				n_oRunner.get ( ).run_tests ( static_cast < char * > ( g_oTestGroup ) );
			else
				n_oRunner.get ( ).run_test ( static_cast < char * > ( g_oTestGroup ), g_iTestNumber );
			}
		catch ( const std::exception & e )
			{
			std::cerr << "tut raised ex: " << e.what ( ) << std::endl;
			}
//		if ( is_enabled ( ) )leave_curses ();  /* ending ncurses sesion    */
		M_ENSURE ( ! g_iErrNo );
/*	... there is the place main loop ends. :OD-OT                         */
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


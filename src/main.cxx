/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	main.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <TUT/tut.hpp>
#include <TUT/tut_reporter.hpp>
#include <TUT/tut_restartable.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "tut_helpers.hxx"
#include "version.hxx"
#include "setup.hxx"
#include "options.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut
{

test_runner_singleton runner;

}

namespace tress
{

OSetup setup;

typedef std::list<std::string> string_list_t;
void gather_groups_from_file( string_list_t& );

}

int main( int a_iArgc, char* a_ppcArgv[] )
	{
	M_PROLOG
	HClock clk;
/*	variables declarations for main loop:                                 */
	int l_iOpt = 0;
	HLogger logger;
	tut::reporter<HLogger> l_oVisitor( std::cerr, logger );
	HException::set_error_stream( stdout );
	tut::restartable_wrapper l_oRestartable;
/*	end.                                                                  */
	try
		{
/*	TO-DO:				enter main loop code here                               */
		HSignalServiceFactory::get_instance();
		setup.f_pcProgramName = a_ppcArgv[ 0 ];
		l_iOpt = handle_program_options( a_iArgc, a_ppcArgv );
		hcore::log.rehash( setup.f_oLogPath, setup.f_pcProgramName );
		setup.test_setup();
		setup.f_iArgc = ( a_iArgc - l_iOpt ) + 1;
		if ( setup.f_iArgc > 1 )
			{
			setup.f_ppcArgv = a_ppcArgv + l_iOpt - 1;
			a_ppcArgv [ l_iOpt - 1 ] = a_ppcArgv [ 0 ];
			}
//		if ( ! is_enabled ( ) )enter_curses (); /* enabling ncurses ablilities*/
/* *BOOM* */
		try
			{
			if ( ! setup.f_bListGroups )
				cout << "TUT: " << static_cast<char const*>( HTime() ) << endl;
			errno = 0;
			if ( setup.f_bListGroups )
				{
				std::cerr << "registered test groups:" << std::endl;
				tut::groupnames gl = tut::runner.get().list_groups();
				tut::groupnames::const_iterator i = gl.begin();
				tut::groupnames::const_iterator e = gl.end();
				while ( i != e )
					{
					std::cout << "  " << *i << std::endl;
					++ i;
					}
				errno = 0;
				}
			else if ( setup.f_bRestartable )
				{
				l_oRestartable.set_callback( &l_oVisitor );
				l_oRestartable.run_tests();
				}
			else
				{
				runner.get().set_callback( &l_oVisitor );
				string_list_t l_oGroupNames;
				if ( ! setup.f_oTestGroupListFilePath.is_empty() )
					{
					gather_groups_from_file( l_oGroupNames );
					runner.get().run_tests( l_oGroupNames );
					}
				else if ( ! setup.f_oTestGroupPattern.is_empty() )
					runner.get().run_pattern_tests( setup.f_oTestGroupPattern.raw() );
				else if ( ! setup.f_oTestGroup.is_empty() && setup.f_iTestNumber )
					runner.get().run_test( setup.f_oTestGroup.raw(),
							setup.f_iTestNumber );
				else if ( ! setup.f_oTestGroup.is_empty() )
					{
					l_oGroupNames.push_back( setup.f_oTestGroup.raw() );
					runner.get().run_tests( l_oGroupNames );
					}
				else
					runner.get().run_tests();
				}
			if ( ! setup.f_bListGroups )
				cout << "TUT: " << static_cast<char const*>( HTime() ) << endl;
			}
		catch ( const std::exception& e )
			{
			std::cerr << "tut raised ex: " << e.what() << std::endl;
			}
//		if ( is_enabled ( ) )leave_curses ();  /* ending ncurses sesion    */
		M_ENSURE ( ! errno );
/*	... there is the place main loop ends. :OD-OT                         */
		}
	catch ( int const& e )
		{
		l_oVisitor._exceptionsCount += e;
		/* escape from main loop */
		}
	catch ( ... )
		{
/* ending ncurses sesion        */
		if ( HCons::get_instance().is_enabled() )
			HCons::get_instance().leave_curses();
		throw;
		}
	fprintf( stderr, "Done in %ld miliseconds.\n", clk.get_time_elapsed( HClock::UNIT::MILISECOND ) );
	return ( l_oVisitor._exceptionsCount
			+ l_oVisitor._failuresCount
			+ l_oVisitor._terminationsCount
			+ l_oVisitor._warningsCount
			+ l_oVisitor._setupCount );
	M_FINAL
	}

namespace tress
{

void gather_groups_from_file( string_list_t& lst )
	{
	M_PROLOG
	FILE* l_psFile = NULL;
	if ( setup.f_oTestGroupListFilePath == "-" )
		l_psFile = stdin;
	HFile l_oFile( HFile::OPEN::READING, l_psFile );
	if ( ! l_psFile && l_oFile.open( setup.f_oTestGroupListFilePath ) )
		{
		cout << l_oFile.get_error() << ": " << l_oFile.get_path() << endl;
		throw 0;
		}
	HString l_oLine;
	while ( l_oFile.read_line( l_oLine,
				HFile::read_t( HFile::READ::STRIP_NEWLINES )
				| ( ( l_psFile == stdin ) ? HFile::READ::UNBUFFERED_READS : HFile::READ::BUFFERED_READS ) ) >= 0 )
		{
		l_oLine.trim_left();
		l_oLine.trim_right();
		lst.push_back( l_oLine.raw() );
		}
	l_oFile.close();
	return;
	M_EPILOG
	}

}


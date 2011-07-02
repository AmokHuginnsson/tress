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
#include <libintl.h>
#include <TUT/tut.hpp>
#include <TUT/tut_reporter.hpp>
#include <TUT/tut_restartable.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )

#include "setup.hxx"
#include "tut_helpers.hxx"
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
void gather_groups_from_file( OSetup::set_definitions_t& );
void list_groups( void );
tut::test_runner::test_sets_t prepare_testsets( OSetup::set_definitions_t const& );

}

M_EXPORT_SYMBOL
int main( int argc_, char* argv_[] )
	{
	M_AT_END_OF_SCOPE( HSignalService::get_instance().stop(); );
	M_PROLOG
	init_locale( PACKAGE_NAME );
	HClock clk;
/*	variables declarations for main loop:                                 */
	tut::reporter<HLog> visitor( std::cerr, hcore::log );
	HException::set_error_stream( stdout );
	tut::restartable_wrapper restartable;
/*	end.                                                                  */
	try
		{
/*	TO-DO:				enter main loop code here                               */
		HSignalService::get_instance();
		setup._programName = argv_[ 0 ];
		handle_program_options( argc_, argv_ );
		hcore::log.rehash( setup._logPath, setup._programName );
		setup.test_setup();
		if ( setup._errorLine == "vim" )
			visitor.set_error_line( &vim_error_line );
		else if ( setup._errorLine == "eclipse" )
			visitor.set_error_line( &vim_error_line );
		else if ( setup._errorLine == "visualstudio" )
			visitor.set_error_line( &visual_studio_error_line );
		else if ( setup._errorLine == "cute" )
			{
			setup._fancy = false;
			setup._color = false;
			if ( setup._jobs > 1 )
				setup._jobs = 1;
			visitor.set_error_line( &cute_error_line );
			}
		else
			visitor.set_error_line( &console_error_line );
		tut::runner.get().set_time_constraint( setup._timeConstraint );
/* *BOOM* */
		try
			{
			if ( ! setup._listGroups )
				cout << "TUT: " << HTime().string() << endl;
			errno = 0;
			if ( setup._exit )
				;
			else if ( setup._listGroups )
				list_groups();
			else if ( setup._restartable )
				{
				restartable.set_callback( &visitor );
				restartable.run_tests();
				}
			else
				{
				runner.get().set_callback( &visitor );
				if ( ! setup._testGroupListFilePath.is_empty() )
					{
					OSetup::set_definitions_t sets;
					gather_groups_from_file( sets );
					tut::test_runner::test_sets_t testSets( prepare_testsets( sets ) );
					runner.get().run_tests( testSets );
					}
				else if ( ! setup._testGroupPattern.is_empty() )
					runner.get().run_pattern_tests( setup._testGroupPattern.raw() );
				else if ( ! setup._testGroups.is_empty() && setup._testNumber )
					runner.get().run_test( setup._testGroups.begin()->raw(),
							setup._testNumber );
				else if ( ! setup._testGroups.is_empty() )
					{
					string_list_t groupNames;
					for ( OSetup::group_names_t::iterator it( setup._testGroups.begin() ), end( setup._testGroups.end() ); it != end; ++ it )
						groupNames.push_back( it->raw() );
					runner.get().run_tests( groupNames );
					}
				else if ( ! setup._testSets.is_empty() )
					{
					tut::test_runner::test_sets_t testSets( prepare_testsets( setup._testSets ) );
					runner.get().run_tests( testSets );
					}
				else
					runner.get().run_tests();
				}
			if ( ! setup._listGroups )
				cout << "TUT: " << HTime().string() << endl;
			}
		catch ( const std::exception& e )
			{
			std::cerr << "tut raised ex: " << e.what() << std::endl;
			}
		M_ENSURE( ! errno );
/*	... there is the place main loop ends. :OD-OT                         */
		}
	catch ( int e )
		{
		visitor._exceptionsCount += e;
		/* escape from main loop */
		}
	catch ( ... )
		{
/* ending ncurses sesion        */
		if ( HConsole::get_instance().is_enabled() )
			HConsole::get_instance().leave_curses();
		throw;
		}
	cerr << ( HFormat( _( "Done in %ld miliseconds." ) ) % clk.get_time_elapsed( HClock::UNIT::MILISECOND ) ).string() << endl;
	if ( yaal::_isKilled_ )
		cerr << "Killed" << endl;
	return ( ( yaal::_isKilled_ ? 1 : 0 )
			+ visitor._exceptionsCount
			+ visitor._failuresCount
			+ visitor._terminationsCount
			+ visitor._warningsCount
			+ visitor._setupCount );
	M_FINAL
	}

namespace tress
{

void gather_groups_from_file( OSetup::set_definitions_t& lst )
	{
	M_PROLOG
	HFile file;
	if ( setup._testGroupListFilePath == "-" )
		file.open( stdin );
	if ( ! file && file.open( setup._testGroupListFilePath, HFile::OPEN::READING ) )
		{
		cout << file.get_error() << ": " << file.get_path() << endl;
		throw 0;
		}
	HString line;
	while ( file.read_line( line, ( setup._testGroupListFilePath == "-" ) ? HFile::READ::UNBUFFERED_READS : HFile::READ::BUFFERED_READS ) >= 0 )
		{
		line.trim_left();
		line.trim_right();
		lst.push_back( line.raw() );
		}
	file.close();
	return;
	M_EPILOG
	}

void list_groups( void )
	{
	M_PROLOG
	std::cerr << "registered test groups:" << std::endl;
	tut::test_runner::groups groups( tut::runner.get().get_groups() );
	tut::test_runner::const_iterator i = groups.begin();
	tut::test_runner::const_iterator e = groups.end();
	int totalTestsCount( 0 );
	while ( i != e )
		{
		int realTestCount( i->second->get_real_test_count() );
		totalTestsCount += realTestCount;
		std::cout << "  " << std::setw( 36 ) << std::left << i->first;
		if ( setup._verbose && realTestCount )
			std::cout << " " << std::right << std::setw( 2 ) << realTestCount;
		std::cout << std::endl;
		++ i;
		}
	if ( setup._verbose )
		std::cout << "total test count: " << totalTestsCount << std::endl;
	errno = 0;
	return;
	M_EPILOG
	}

tut::test_runner::test_sets_t prepare_testsets( OSetup::set_definitions_t const& sets_ )
	{
	M_PROLOG
	tut::test_runner::groups groups( tut::runner.get().get_groups() );
	tut::test_runner::test_sets_t tss;
	HTokenizer tokenizer( "@", HTokenizer::SKIP_EMPTY );
	HTokenizer noTokenizer( ",", HTokenizer::SKIP_EMPTY );
	int setIdx( 1 );
	for ( OSetup::set_definitions_t::const_iterator it( sets_.begin() ), end( sets_.end() ); it != end; ++ it, ++ setIdx )
		{
		if ( it->is_empty() )
			tools::util::failure( setIdx, "empty set\n" );
		tokenizer.assign( *it );
		HTokenizer::iterator token( tokenizer.begin() );
		if ( token->is_empty() )
			tools::util::failure( setIdx, "empty set name\n" );
		tut::test_runner::test_set_t ts;
		ts.first = token->raw();
		++ token;
		if ( token != tokenizer.end() )
			{
			noTokenizer.assign( *token );
			for ( HTokenizer::iterator no( noTokenizer.begin() ), noEnd( noTokenizer.end() ); no != noEnd; ++ no )
				ts.second.push_back( lexical_cast<int>( *no ) );
			}
		tss.push_back( ts );
		}
	return ( tss );
	M_EPILOG
	}

}


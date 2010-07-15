/*
---            `child' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	main.cxx - this file is integral part of `child' project.

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

#include <cstring>
#include <cstdlib>
#include <csignal>

#include <yaal/yaal.hxx> /* all hAPI headers */
M_VCSID( "$Id: "__ID__" $" )

#include "setup.hxx"
#include "options.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace child;

namespace child
{

OSetup setup;

}

int main( int argc_, char* argv_[] )
	{
//	M_AT_END_OF_SCOPE( HSignalService::get_instance().stop(); );
	M_PROLOG
/* variables declarations for main loop: */
	int opt = 0;
/* end. */
	try
		{
		setup._programName = argv_[ 0 ];
		opt = handle_program_options( argc_, argv_ );
		hcore::log.rehash( "x_child.log", setup._programName );
		setup.test_setup();
		if ( !! setup._script )
			{
			HString nonWord;
			int const SIZE = static_cast<int>( ::strlen( _word_ ) );
			for ( int c = 1; c < 256; ++ c )
				{
				if ( ! memchr( _word_, c, SIZE ) )
					nonWord += static_cast<char>( c );
				}
			HTokenizer t( setup._script, ";", HTokenizer::SKIP_EMPTY );
			for ( HTokenizer::HIterator it = t.begin(), end = t.end(); it != end; ++ it )
				{
				HTokenizer w( *it, nonWord, HTokenizer::SKIP_EMPTY );
				HString cmd;
				HString arg;
				HTokenizer::HIterator word = w.begin();
				if ( word != w.end() )
					{
					cmd = *word;
					++ word;
					if ( word != w.end() )
						arg = *word;
					}
				if ( cmd == "write" )
					cout << arg << endl;
				else if ( cmd == "errlog" )
					cerr << arg << endl;
				else if ( cmd == "read" )
					cin >> arg;
				else if ( cmd == "close" )
					system::close( lexical_cast<int>( arg ) );
				else
					M_THROW( "syntax error at: " + cmd, errno );
				}
			}
		if ( !! setup._terminate )
			{
			typedef HMap<HString, int> str2int_dict_t;
			str2int_dict_t signalNames;
			signalNames.insert( make_pair<char const* const>( "ALRM", SIGALRM ) );
			signalNames.insert( make_pair<char const* const>( "HUP", SIGHUP ) );
			signalNames.insert( make_pair<char const* const>( "INT", SIGINT ) );
			signalNames.insert( make_pair<char const* const>( "KILL", SIGKILL ) );
			signalNames.insert( make_pair<char const* const>( "PIPE", SIGPIPE ) );
			signalNames.insert( make_pair<char const* const>( "TERM", SIGTERM ) );
			signalNames.insert( make_pair<char const* const>( "TSTP", SIGTSTP ) );
			signalNames.insert( make_pair<char const* const>( "CONT", SIGCONT ) );
			signalNames.insert( make_pair<char const* const>( "CHLD", SIGCHLD ) );
			signalNames.insert( make_pair<char const* const>( "ABRT", SIGABRT ) );
			signalNames.insert( make_pair<char const* const>( "ILL", SIGILL ) );
			signalNames.insert( make_pair<char const* const>( "FPE", SIGFPE ) );
			signalNames.insert( make_pair<char const* const>( "QUIT", SIGQUIT ) );
			signalNames.insert( make_pair<char const* const>( "TRAP", SIGTRAP ) );
			signalNames.insert( make_pair<char const* const>( "SEGV", SIGSEGV ) );
			str2int_dict_t::const_iterator it = signalNames.find( setup._terminate );
			if ( it != signalNames.end() )
				system::kill( system::getpid(), it->second );
			M_THROW( "unknown signal: " + setup._terminate, errno );
			}
		}
	catch ( ... )
		{
		hcore::log << "Unexpected exception cauht!" << endl;
		}
	return ( setup._exitStatus );
	M_FINAL
	}


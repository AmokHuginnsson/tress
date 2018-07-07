/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>
#include <cstdlib>
#include <csignal>

#include <yaal/hcore/hfile.hxx>
#include <yaal/hcore/htokenizer.hxx>
#include <yaal/hcore/hlog.hxx>
M_VCSID( "$Id: " __ID__ " $" )

#include "setup.hxx"
#include "options.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace child;

namespace child {

OSetup setup;

}

int main( int argc_, char* argv_[] ) {
//	M_AT_END_OF_SCOPE( HSignalService::get_instance().stop(); );
	M_PROLOG
/* variables declarations for main loop: */
/* end. */
	try {
		setup._programName = argv_[ 0 ];
		handle_program_options( argc_, argv_ );
		hcore::log.rehash( "x_child.log", setup._programName );
		setup.test_setup();
		if ( !! setup._script ) {
			HString nonWord;
			for ( code_point_t::value_type c = 1; c < 256; ++ c ) {
				if ( ! character_class<CHARACTER_CLASS::WORD>().has( code_point_t( c ) ) ) {
					nonWord.push_back( code_point_t( c ) );
				}
			}
			HTokenizer t( setup._script, ";", HTokenizer::SKIP_EMPTY );
			for ( HTokenizer::HIterator it = t.begin(), end = t.end(); it != end; ++ it ) {
				HTokenizer w( *it, nonWord, HTokenizer::SKIP_EMPTY );
				HString cmd;
				HString arg;
				HTokenizer::HIterator word = w.begin();
				if ( word != w.end() ) {
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
					hcore::system::close( lexical_cast<int>( arg ) );
				else
					M_THROW( "syntax error at: " + cmd, errno );
			}
		}
		if ( !! setup._terminate ) {
			typedef HMap<HString, int> str2int_dict_t;
			str2int_dict_t signalNames;
			signalNames.insert( make_pair( "ALRM", SIGALRM ) );
			signalNames.insert( make_pair( "HUP", SIGHUP ) );
			signalNames.insert( make_pair( "INT", SIGINT ) );
			signalNames.insert( make_pair( "KILL", SIGKILL ) );
			signalNames.insert( make_pair( "PIPE", SIGPIPE ) );
			signalNames.insert( make_pair( "TERM", SIGTERM ) );
			signalNames.insert( make_pair( "TSTP", SIGTSTP ) );
			signalNames.insert( make_pair( "CONT", SIGCONT ) );
			signalNames.insert( make_pair( "CHLD", SIGCHLD ) );
			signalNames.insert( make_pair( "ABRT", SIGABRT ) );
			signalNames.insert( make_pair( "ILL", SIGILL ) );
			signalNames.insert( make_pair( "FPE", SIGFPE ) );
			signalNames.insert( make_pair( "QUIT", SIGQUIT ) );
			signalNames.insert( make_pair( "TRAP", SIGTRAP ) );
			signalNames.insert( make_pair( "SEGV", SIGSEGV ) );
			str2int_dict_t::const_iterator it = signalNames.find( setup._terminate );
			if ( it != signalNames.end() )
				hcore::system::kill( hcore::system::getpid(), it->second );
			M_THROW( "unknown signal: " + setup._terminate, errno );
		}
	} catch ( ... ) {
		hcore::log << "Unexpected exception cauht!" << endl;
	}
	return ( setup._exitStatus );
	M_FINAL
}


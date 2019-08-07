/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <memory>
#include <cstdio>
#include <libintl.h>
#include <TUT/tut.hpp>
#include "tut_helpers.hxx"
#include <TUT/tut_reporter.hpp>
#include <TUT/tut_reporter_boost.hpp>
#include <TUT/tut_reporter_google.hpp>
#include <TUT/tut_reporter_cppunit.hpp>
#include <TUT/tut_reporter_xml.hpp>
#include <TUT/tut_reporter_qt.hpp>
#include <TUT/tut_reporter_cute.hpp>
#include <TUT/tut_restartable.hpp>

#include <yaal/hcore/hcore.hxx>
#include <yaal/hcore/hlog.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/hcore/hformat.hxx>
#include <yaal/hcore/htokenizer.hxx>
#include <yaal/tools/util.hxx>
#include <yaal/tools/streamtools.hxx>
#include <yaal/tools/hterminal.hxx>
#include <yaal/tools/signals.hxx>
#include <yaal/tools/hthreadpool.hxx>
#include <yaal/tools/hmonitor.hxx>
#include <yaal/tools/filesystem.hxx>

#ifdef __HOST_OS_TYPE_LINUX__
#include <unistd.h>
#include <fcntl.h>
#endif

M_VCSID( "$Id: " __ID__ " $" )

#include "setup.hxx"
#include "options.hxx"
#include "tut_selftest.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

test_runner_singleton runner;

}

namespace tress {

OSetup setup;

typedef std::list<std::string> string_list_t;
void gather_groups_from_file( OSetup::set_definitions_t& );
void list_groups( void );
tut::test_runner::test_sets_t prepare_testsets( OSetup::set_definitions_t const& );
void cleanup( void );

}

M_EXPORT_SYMBOL
int main( int argc_, char* argv_[] ) {
	HScopeExitCall secTP( call( &HThreadPool::stop, &HThreadPool::get_instance() ) );
	HScopeExitCall secSS( call( &HSignalService::stop, &HSignalService::get_instance() ) );
	M_PROLOG
	HMonitor::get_instance();
	init_locale( PACKAGE_NAME );
	HClock clk;
/*	variables declarations for main loop:                                 */
	typedef std::unique_ptr<tut::callback> reporter_ptr;
	reporter_ptr visitor;
	HResource<FILE, int (*)( FILE* )> errorDump( ::fopen( "./out/error.dump", "wb" ), fclose );
	HException::set_error_stream( stdout );
	tut::restartable_wrapper restartable;
	int err( 0 );
/*	end.                                                                  */
	try {
/*	TO-DO:				enter main loop code here                               */
		HSignalService::get_instance();
		setup._programName = argv_[ 0 ];
		handle_program_options( argc_, argv_ );
		hcore::log.rehash( setup._logPath, setup._programName );
		setup.test_setup();
		if ( setup._quiet && !! errorDump ) {
			HException::set_error_stream( errorDump.raw() );
		}
		if ( setup._reporter == "tut" ) {
			typedef tut::reporter<HLog> reporter_console;
			reporter_console* rep( nullptr );
			visitor = reporter_ptr( rep = new reporter_console( std::cerr, hcore::log ) );
			if ( setup._errorLine == "vim" ) {
				rep->set_error_line( &vim_error_line );
			} else if ( setup._errorLine == "eclipse" ) {
				rep->set_error_line( &vim_error_line );
			} else if ( setup._errorLine == "visualstudio" ) {
				rep->set_error_line( &visual_studio_error_line );
			} else {
				rep->set_error_line( &console_error_line );
			}
		} else {
			setup._fancy = false;
			if ( setup._jobs > 1 ) {
				setup._jobs = 1;
			}
			if ( setup._reporter == "boost" ) {
				visitor = reporter_ptr( new tut::reporter_boost<HLog>( std::cerr, hcore::log ) );
			} else if ( setup._reporter == "google" ) {
				visitor = reporter_ptr( new tut::reporter_google<HLog>( std::cerr, hcore::log ) );
			} else if ( setup._reporter == "cppunit" ) {
				visitor = reporter_ptr( new tut::reporter_cppunit( std::cerr ) );
			} else if ( setup._reporter == "xml" ) {
				visitor = reporter_ptr( new tut::reporter_xml( std::cerr ) );
			} else if ( setup._reporter == "qt" ) {
				visitor = reporter_ptr( new tut::reporter_qt<HLog>( std::cerr, hcore::log ) );
			} else if ( setup._reporter == "cute" ) {
				visitor = reporter_ptr( new tut::reporter_cute<HLog>( std::cerr, hcore::log ) );
			}
		}
		if ( setup._selftest ) {
			register_selftest();
		}
		tut::runner.get().set_time_constraint( static_cast<int long>( time::in_units<time::UNIT::MILLISECOND>( setup._timeConstraint ) ) );
/* *BOOM* */
		try {
			if ( ! setup._listGroups ) {
				cout << "TUT: " << now_local() << endl;
			}
			errno = 0;
			if ( setup._exit ) {
				;
			} else if ( setup._listGroups ) {
				list_groups();
			} else if ( setup._restartable ) {
				restartable.set_callback( visitor.get() );
				restartable.run_tests();
			} else {
				runner.get().set_callback( visitor.get() );
				if ( ! setup._testGroupListFilePath.is_empty() ) {
					OSetup::set_definitions_t sets;
					gather_groups_from_file( sets );
					tut::test_runner::test_sets_t testSets( prepare_testsets( sets ) );
					runner.get().run_tests( testSets );
				} else if ( ! setup._testGroupPattern.is_empty() ) {
					runner.get().run_pattern_tests( yaal::lexical_cast<std::string>( setup._testGroupPattern ) );
				} else if ( ! setup._testGroups.is_empty() && setup._testNumber ) {
					runner.get().run_test( yaal::lexical_cast<std::string>( setup._testGroups.front() ), setup._testNumber );
				} else if ( ! setup._testGroups.is_empty() ) {
					string_list_t groupNames;
					for ( OSetup::group_names_t::iterator it( setup._testGroups.begin() ), end( setup._testGroups.end() ); it != end; ++ it ) {
						groupNames.push_back( lexical_cast<std::string>( *it ) );
					}
					runner.get().run_tests( groupNames );
				} else if ( ! setup._testSets.is_empty() ) {
					tut::test_runner::test_sets_t testSets( prepare_testsets( setup._testSets ) );
					runner.get().run_tests( testSets );
				} else {
					runner.get().run_tests();
				}
			}
			if ( ! setup._listGroups )
				cout << "TUT: " << now_local() << endl;
		} catch ( const std::exception& e ) {
			std::cerr << "tut raised ex: " << e.what() << std::endl;
		}
/*	... there is the place main loop ends. :OD-OT                         */
	} catch ( int e ) {
		err = e;
		/* escape from main loop */
	}
	cleanup();
	if ( visitor.get() && ( setup._reporter == "tut" ) ) {
		cerr << ( HFormat( _( "Done in %ld miliseconds." ) ) % static_cast<int long>( clk.get_time_elapsed( time::UNIT::MILLISECOND ) ) ).string() << endl;
		M_ENSURE( ! errno );
	}
	if ( yaal::_isKilled_ ) {
		cerr << "Killed" << endl;
	}
	return ( ( yaal::_isKilled_ ? 1 : 0 ) + err + ( visitor.get() ? visitor->fail_count() : 0 ) );
	M_FINAL
}

namespace tress {

void gather_groups_from_file( OSetup::set_definitions_t& lst ) {
	M_PROLOG
	HFile file;
	if ( setup._testGroupListFilePath == "-" ) {
		file.open( stdin, HFile::OWNERSHIP::EXTERNAL );
	}
	if ( ! file && file.open( setup._testGroupListFilePath, HFile::OPEN::READING ) ) {
		cout << file.get_error() << ": " << file.get_path() << endl;
		throw 0;
	}
	HString line;
	while ( file.read_line( line, ( setup._testGroupListFilePath == "-" ) ? HFile::READ::UNBUFFERED_READS : HFile::READ::BUFFERED_READS ).good() ) {
		line.trim_left();
		line.trim_right();
		lst.push_back( line );
	}
	file.close();
	return;
	M_EPILOG
}

void list_groups( void ) {
	M_PROLOG
	std::cerr << "registered test groups:" << std::endl;
	tut::test_runner::groups groups( tut::runner.get().get_groups() );
	tut::test_runner::const_iterator i = groups.begin();
	tut::test_runner::const_iterator e = groups.end();
	int totalTestsCount( 0 );
	while ( i != e ) {
		if ( setup._testGroups.is_empty() || ( setup._testGroups[0] == i->second->get_name().c_str() ) ) {
			int realTestCount( i->second->get_real_test_count() );
			totalTestsCount += realTestCount;
			std::cout << "  " << std::setw( 36 ) << std::left << i->first;
			if ( setup._verbose && realTestCount ) {
				std::cout << " " << std::right << std::setw( 2 ) << realTestCount;
			}
			if ( setup._debug ) {
				tut::group_base::titles_t const& titles( i->second->get_test_titles() );
				for ( tut::group_base::titles_t::const_iterator t( titles.begin() ), te( titles.end() ); t != te; ++ t ) {
					std::cout << "\n\t<" << t->first << ">::" << t->second;
				}
			}
			std::cout << std::endl;
		}
		++ i;
	}
	if ( setup._verbose ) {
		std::cout << "total test count: " << totalTestsCount << std::endl;
	}
	errno = 0;
	return;
	M_EPILOG
}

tut::test_runner::test_sets_t prepare_testsets( OSetup::set_definitions_t const& sets_ ) {
	M_PROLOG
	tut::test_runner::groups groups( tut::runner.get().get_groups() );
	tut::test_runner::test_sets_t tss;
	HTokenizer tokenizer( "@", HTokenizer::SKIP_EMPTY );
	HTokenizer noTokenizer( ",", HTokenizer::SKIP_EMPTY );
	int setIdx( 1 );
	for ( OSetup::set_definitions_t::const_iterator it( sets_.begin() ), end( sets_.end() ); it != end; ++ it, ++ setIdx ) {
		if ( it->is_empty() ) {
			tools::util::failure( setIdx, "empty set\n" );
		}
		tokenizer.assign( *it );
		HTokenizer::iterator token( tokenizer.begin() );
		if ( token->is_empty() ) {
			tools::util::failure( setIdx, "empty set name\n" );
		}
		tut::test_runner::test_set_t ts;
		ts.first = lexical_cast<std::string>( *token );
		++ token;
		if ( token != tokenizer.end() ) {
			noTokenizer.assign( *token );
			for ( HTokenizer::iterator no( noTokenizer.begin() ), noEnd( noTokenizer.end() ); no != noEnd; ++ no ) {
				ts.second.push_back( lexical_cast<int>( *no ) );
			}
		}
		tss.push_back( ts );
	}
	return ( tss );
	M_EPILOG
}

void cleanup( void ) {
	M_PROLOG
	HScopedValueReplacement<int> saveErrno( errno, 0 );
#ifdef __HOST_OS_TYPE_LINUX__
	static int const MAX_FD( 1024 );
	for ( int i( 0 ); i < MAX_FD; ++ i ) {
		if ( fcntl( i, F_GETFD ) >= 0 ) {
			HString p( filesystem::readlink( "/proc/self/fd/"_ys.append( i ) ) );
			if ( p.find( "firebird.msg" ) != HString::npos ) {
				close( i );
			}
		}
	}
#endif
	return;
	M_EPILOG
}

}


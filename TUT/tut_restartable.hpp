#ifndef TUT_RESTARTABLE_H_GUARD
#define TUT_RESTARTABLE_H_GUARD

#include <fstream>
#include <iostream>

#include "tut.hpp"

/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * Optional restartable wrapper for test_runner. Allows to restart test runs
 * finished due to abnormal test application termination (such as segmentation
 * fault or math error).
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */

namespace tut {

namespace util {

/**
 * Escapes non-alphabetical characters in string.
 */
std::string escape( const std::string& );
std::string escape( const std::string& orig ) {
	std::string rc;
	std::string::const_iterator i, e;

	i = orig.begin();
	e = orig.end();

	while ( i != e ) {
		if ( ( ( *i >= 'a' ) && ( *i <= 'z' ) )
		     || ( ( *i >= 'A' ) && ( *i <= 'Z' ) )
				 || ( ( *i >= '0' ) && ( *i <= '9' ) ) ) {
			rc += *i;
		} else {
			rc += '\\';
			rc += static_cast<char>( 'a' + ( static_cast<unsigned int>( *i ) >> 4 ) );
			rc += static_cast<char>( 'a' + ( static_cast<unsigned int>( *i ) & 0xF ) );
		}

		++ i;
	}

	return ( rc );
}

/**
 * Un-escapes string.
 */
std::string unescape( const std::string& );
std::string unescape( const std::string& orig ) {
	std::string rc;
	std::string::const_iterator i, e;

	i = orig.begin();
	e = orig.end();

	while ( i != e ) {
		if ( *i != '\\' ) {
			rc += *i;
		} else {
			++ i;
			if ( i == e ) {
				throw std::invalid_argument( "unexpected end of string" );
			}

			unsigned int c1 = *i;
			++ i;
			if ( i == e ) {
				throw std::invalid_argument( "unexpected end of string" );
			}

			unsigned int c2 = *i;
			rc += static_cast<char>( ( ( c1 - 'a' ) << 4 ) + ( c2 - 'a' ) );
		}

		++ i;
	}

	return ( rc );
}

/**
 * Serialize test_result avoiding interfering with operator <<.
 */
void serialize( std::ostream&, const tut::test_result& );
void serialize( std::ostream& os, const tut::test_result& tr ) {
	os << escape( tr._group->get_name() ) << std::endl;
	os << tr._testNo << ' ';
	switch ( tr._result ) {
		case test_result::ok:
			os << 0;
		break;
		case test_result::fail:
			os << 1;
		break;
		case test_result::ex:
			os << 2;
		break;
		case test_result::warn:
			os << 3;
		break;
		case test_result::term:
			os << 4;
		break;
		default:
			throw std::logic_error( "operator << : bad result_type" );
	}
	os << ' ' << escape( tr._name ) << std::endl;
	os << escape( tr._file ) << std::endl;
	os << ' ' << tr._line;
	os << ' ' << escape( tr._message ) << std::endl;
}

/**
 * deserialization for test_result
 */
void deserialize( std::istream&, tut::test_result& );
void deserialize( std::istream& is, tut::test_result& tr ) {
	std::string name;
	std::getline( is, name );
	if ( is.eof() ) {
		throw tut::no_more_tests();
	}

	tr._group->set_name( unescape( name ) );

	tr._testNo = -1;
	is >> tr._testNo;
	if ( tr._testNo < 0 ) {
		throw std::logic_error( "operator >> : bad test number" );
	}

	int n = -1;
	is >> n;
	switch ( n ) {
		case 0:
			tr._result = test_result::ok;
		break;
		case 1:
			tr._result = test_result::fail;
		break;
		case 2:
			tr._result = test_result::ex;
		break;
		case 3:
			tr._result = test_result::warn;
		break;
		case 4:
			tr._result = test_result::term;
		break;
		default:
			throw std::logic_error( "operator >> : bad result_type" );
	}

	is.ignore( 1 );    // space
	std::getline( is, tr._name );
	tr._name = unescape( tr._name );
	std::getline( is, tr._file );
	tr._file = unescape( tr._file );
	is.ignore( 1 );    // space
	is >> tr._line;
	is.ignore( 1 );    // space
	std::getline( is, tr._message );
	tr._message = unescape( tr._message );
	if ( !is.good() ) {
		throw std::logic_error( "malformed test result" );
	}
}
}

/**
 * Restartable test runner wrapper.
 */
class restartable_wrapper : public tut_listener {
	test_runner& _runner;
	callback* _callback;

	std::string _dir;
	std::string _log;     // log file: last test being executed
	std::string _journal;     // journal file: results of all executed tests

public:
	/**
	 * Default constructor.
	 * @param dir Directory where to search/put log and journal files
	 */
	restartable_wrapper( const std::string& dir = "." )
		: _runner( runner.get() ), _callback( 0 ), _dir( dir ),
		_log( _dir + '/' + "log.tut" ), _journal( _dir + '/' + "journal.tut" ) {
		_runner.set_listener( this );
		// dozen: it works, but it would be better to use system path separator
	}

	virtual ~restartable_wrapper( void )
		{ }

	/**
	 * Stores another group for getting by name.
	 */
	void register_group( const std::string& name, group_base* gr ) {
		_runner.register_group( name, gr );
	}

	/**
	 * Stores callback object.
	 */
	void set_callback( callback* cb ) {
		_callback = cb;
	}

	/**
	 * Returns callback object.
	 */
	callback& get_callback() const {
		return ( _runner.get_callback() ) ;
	}

	/**
	 * Returns list of known test groups.
	 */
	groupnames list_groups() const {
		return ( _runner.list_groups() ) ;
	}

	/**
	 * Runs all tests in all groups.
	 */
	void run_tests() const {
		// where last run was failed
		std::string fail_group;
		int fail_test;

		read_log( fail_group, fail_test );
		bool fail_group_reached = ( fail_group == "" );

		// iterate over groups
		tut::groupnames gn = list_groups();
		tut::groupnames::const_iterator gni, gne;
		gni = gn.begin();
		gne = gn.end();
		while ( gni != gne ) {
			// skip all groups before one that failed
			if ( ! fail_group_reached ) {
				if ( *gni != fail_group ) {
					++ gni;
					continue;
				}

				fail_group_reached = true;
			}

			// first or restarted run
			int test = ( ( *gni == fail_group ) && ( fail_test >= 0 ) ) ? fail_test + 1 : 1;
			while ( true ) {
				// last executed test pos

				try {
					tut::test_result tr = _runner.run_test( *gni, test );
					register_test( tr );
				} catch ( const tut::beyond_last_test& ) {
					break;
				} catch ( const tut::no_such_test& ) {
					// it's ok
				}

				++ test;
			}

			++ gni;
		}

		// show final results to user
		invoke_callback();

		// truncate files as mark of successful finish
		truncate();
	}

private:
	/**
	 * Shows results from journal file.
	 */
	void invoke_callback() const {
		_runner.set_callback( _callback );
		_runner.get_callback().run_started( 0, 0 );

		std::string current_group;
		std::ifstream ijournal( _journal.c_str() );
		while ( ijournal.good() ) {
			// read next test result
			try {
				tut::test_result tr;
				util::deserialize( ijournal, tr );
				_runner.get_callback().test_completed( tr );
			} catch ( const no_more_tests& ) {
				break;
			}
		}

		_runner.get_callback().run_completed();
	}

	/**
	 * Register test into journal.
	 */
	void register_test( const test_result& tr ) const {
		std::ofstream ojournal( _journal.c_str(), std::ios::app );

		util::serialize( ojournal, tr );
		ojournal << std::flush;
		if ( !ojournal.good() )
			throw std::runtime_error( "unable to register test result in file " + _journal );
	}

	/**
	 * Mark the fact test going to be executed
	 */
	virtual void do_register_execution( const std::string& grp, int test, std::string const& name, std::string const& file, int const& line ) const {
		// last executed test pos
		std::ofstream olog( _log.c_str() );

		olog << util::escape( grp ) << std::endl
			<< test << std::endl
			<< util::escape( name ) << std::endl
			<< util::escape( file ) << std::endl
			<< line << std::endl << std::flush;
		if ( !olog.good() )
			throw std::runtime_error( "unable to register execution in file " + _log );
	}

	/**
	 * Truncate tests.
	 */
	void truncate() const {
		std::ofstream olog( _log.c_str() );
		std::ofstream ojournal( _journal.c_str() );
	}

	/**
	 * Read log file
	 */
	void read_log( std::string& fail_group, int& fail_test ) const {
		int failLine = 0;
		// read failure point, if any
		std::ifstream ilog( _log.c_str() );
		ilog >> fail_group;
		fail_group = util::unescape( fail_group );
		ilog >> fail_test;
		std::string failName;
		ilog >> failName;
		failName = util::unescape( failName );
		std::string failFile;
		ilog >> failFile;
		failFile = util::unescape( failFile );
		ilog >> failLine;
		if ( ! ilog.good() ) {
			fail_group = "";
			fail_test = -1;
			truncate();
		} else {
			// test was terminated...
			tut::test_result tr( _runner.get_group( fail_group ), fail_test );
			tr.set_meta( tut::test_result::term );
			tr.set_meta( failName, failFile.c_str(), failLine );
			register_test( tr );
		}
	}
private:
	restartable_wrapper( restartable_wrapper const& );
	restartable_wrapper& operator = ( restartable_wrapper const& );
};
}

#endif

#ifndef TUT_EXCEPTION_H_GUARD
#define TUT_EXCEPTION_H_GUARD

#include <stdexcept>

#include "tut_result.hpp"

namespace tut {

/**
 * The base for all TUT exceptions.
 */
struct tut_error : public std::exception {
	tut_error( const std::string& msg )
		: _errMsg( msg ) {
	}

	virtual test_result::result_type_t result() const {
		return ( test_result::ex ) ;
	}

	const char* what() const throw ( ) {
		return ( _errMsg.c_str() ) ;
	}

	~tut_error() throw () {
	}

	private:

	std::string _errMsg;
};

/**
 * Exception to be throwed when attempted to execute
 * missed test by number.
 */
struct no_such_test : public tut_error {
	no_such_test()
		: tut_error( "no such test" ) {
	}
	~no_such_test() throw () {
	}
};

/**
 * No such test and passed test number is higher than
 * any test number in current group. Used in one-by-one
 * test running when upper bound is not known.
 */
struct beyond_last_test : public no_such_test {
	beyond_last_test() {
	}
	~beyond_last_test() throw () {
	}
};

/**
 * Group not found exception.
 */
struct no_such_group : public tut_error {
	no_such_group( std::string const& grp )
		: tut_error( std::string( "no such group: " ) + grp ) {
	}
	~no_such_group() throw () {
	}
};

/**
 * Internal exception to be throwed when
 * no more tests left in group or journal.
 */
struct no_more_tests {
	no_more_tests() {
	}
	~no_more_tests() throw () {
	}
};

/**
 * Internal exception to be throwed when
 * test constructor has failed.
 */
struct bad_ctor : public tut_error {
	bad_ctor( std::string const& msg )
		: tut_error( msg ) {
	}
	virtual test_result::result_type_t result() const {
		return ( test_result::ex_ctor );
	}
	~bad_ctor() throw () {
	}
};

/**
 * Exception to be throwed when ensure() fails or fail() called.
 */
struct failure : public tut_error {
	int _line;
	char const* _file;
	failure( char const* const file, int line, const std::string& msg )
		: tut_error( msg )
		, _line( line )
		, _file( file ) {
	}
	failure( failure const& fi )
		: tut_error( fi )
		, _line( fi._line )
		, _file( fi._file ) {
	}
	failure& operator = ( failure const& fi ) {
		if ( &fi != this ) {
			using std::swap;
			failure tmp( fi );
			swap( _line, tmp._line );
			swap( _file, tmp._file );
		}
		return ( *this );
	}
	virtual test_result::result_type_t result() const {
		return ( test_result::fail );
	}
	~failure() throw ()
		{}
};

/**
 * Exception to be throwed when test desctructor throwed an exception.
 */
struct warning : public tut_error {
	warning( std::string const& msg )
		: tut_error( msg ) {
	}
	virtual test_result::result_type_t result() const {
		return ( test_result::warn );
	}
	~warning() throw ()
		{}
};

/**
 * Exception to be throwed when child processes fail.
 */
struct rethrown : public failure {
	explicit rethrown( const test_result& res )
		: failure( nullptr, 0, res._message )
		, _tr( res ) {
	}

	virtual test_result::result_type_t result() const {
		return ( test_result::rethrown );
	}

	~rethrown() throw ( )
		  {}

	const test_result _tr;
};

/**
 * Exception to be throwed to skip rest of the test.
 */
struct skipper : public tut_error {
	int _line;
	char const* _file;
	skipper( char const* const file, int const& line, const std::string& msg )
		: tut_error( msg )
		, _line( line )
		, _file( file ) {
	}
	skipper( skipper const& fi )
		: tut_error( fi )
		, _line( fi._line )
		, _file( fi._file ) {
	}
	skipper& operator = ( skipper const& fi ) {
		if ( &fi != this ) {
			using std::swap;
			skipper tmp( fi );
			swap( _line, tmp._line );
			swap( _file, tmp._file );
		}
		return ( *this );
	}
	virtual test_result::result_type_t result() const {
		return ( test_result::skipped );
	}
	~skipper() throw () {
	}
};

}

#endif

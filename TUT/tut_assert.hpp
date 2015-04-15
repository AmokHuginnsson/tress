#ifndef TUT_ASSERT_H_GUARD
#define TUT_ASSERT_H_GUARD

#include "tut_exception.hpp"

#if defined(TUT_USE_POSIX)
#include <cerrno>
#include <cstring>
#endif

#include <yaal/hcore/hclock.hxx>

namespace tut {

namespace {

/**
 * Tests provided condition.
 * Throws if false.
 */
void ensure_real( char const* file, int line, char const* msg, bool cond ) {
	if ( !cond ) {
		// TODO: default ctor?
		throw failure( file, line, msg );
	}
}
void ensure( char const*, bool ) __attribute__((used));
void ensure( char const* msg, bool cond ) {
	ensure_real( NULL, 0, msg, cond );
}

/**
 * Tests provided condition.
 * Throws if false.
 */
void ensure_real( char const*, int, char const*, char const*, bool ) __attribute__((used));
void ensure_real( char const* file, int line, char const*, char const* msg, bool cond ) {
	if ( !cond )
		throw failure( file, line, msg );
}
void ensure_real( char const*, int, char const*, yaal::hcore::HString const&, bool ) __attribute__((used));
void ensure_real( char const* file, int line, char const*, yaal::hcore::HString const& msg, bool cond ) {
	ensure_real( file, line, msg.raw(), cond );
}
template<typename T>
void ensure( T const& msg, bool cond ) {
	ensure_real( NULL, 0, NULL, msg, cond );
}

/**
 * Tests provided condition.
 * Throws if true.
 */
void ensure_not_real( char const* file, int const& line, char const* msg, bool cond ) {
	if ( cond ) {
		// TODO: default ctor?
		throw failure( file, line, msg );
	}
}
void ensure_not( char const*, bool ) __attribute__((used));
void ensure_not( char const* msg, bool cond ) {
	ensure_not_real( NULL, 0, msg, cond );
}

/**
 * Tests provided condition.
 * Throws if true.
 */
template<typename T>
void ensure_not_real( char const* file, int line, char const*, T const& msg, bool cond ) {
	if ( cond )
		throw failure( file, line, msg );
}
template<typename T>
void ensure_not( T const& msg, bool cond ) {
	ensure_not_real( NULL, 0, NULL, msg, cond );
}

template<typename T>
T const& stream_escape( T const& val_ ) {
	return ( val_ );
}
char const* stream_escape( char const* ) __attribute__((used));
char const* stream_escape( char const* val_ ) {
	return ( val_ ? val_ : "(null)" );
}
/**
 * Tests two objects for being equal.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
template<class T, class Q>
void ensure_equals_real( char const* file, int line, char const*, const char* msg, const Q& actual,
	const T& expected ) {
	if ( ! ( actual == expected ) ) {
		std::stringstream ss;
		ss << ( msg ? msg : "" )
		<< ( msg ? ":" : "" )
		<< " expected [" << stream_escape( expected ) << "] actual [" << stream_escape( actual ) << "]";
		throw failure( file, line, ss.str().c_str() );
	}
}
template<class T, class Q>
void ensure_equals( const char* msg, const Q& actual, const T& expected ) {
	ensure_equals_real( NULL, 0, NULL, msg, actual, expected );
}

template<class T, class Q>
void ensure_equals_real( char const* file,
	int const& line,
	char const*,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const T& expected ) {
	ensure_equals_real<>( file, line, NULL, msg.raw(), actual, expected );
}
template<class T, class Q>
void ensure_equals( yaal::hcore::HString const& msg, const Q& actual, const T& expected ) {
	ensure_equals_real( NULL, 0, NULL, msg, actual, expected );
}

template<class T, class Q>
void ensure_equals_real( char const* file, int const& line, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_equals_real<>( file, line, NULL, msg, actual, expected );
}

/**
 * Tests two objects for being at most in given distance one from another.
 * Borders are excluded.
 * Throws if false.
 *
 * NB: T must have operator << defined somewhere, or
 * client code will not compile at all! Also, T shall have
 * operators + and -, and be comparable.
 */
template<class T>
void ensure_distance_real( char const* file, int const& line, char const*, const char* msg, const T& actual,
	const T& expected, const T& distance ) {
	if ( ( ( expected - distance ) >= actual ) || ( ( expected + distance ) <= actual ) ) {
		std::stringstream ss;
		ss << ( msg ? msg : "" )
		<< ( msg ? ":" : "" )
		<< " expected ("
		<< expected - distance
		<< ";" << expected + distance << ") actual [" << actual << "] distance <" << distance << ">";
		throw failure( file, line, ss.str().c_str() );
	}
}
template<class T>
void ensure_distance( const char* msg, const T& actual, const T& expected, const T& distance ) {
	ensure_distance_real( NULL, 0, NULL, msg, actual, expected, distance );
}

template<class T>
void ensure_distance_real( char const* file, int line, const char* msg, const T& actual,
	const T& expected, const T& distance ) {
	ensure_distance_real<>( file, line, NULL, msg, actual, expected, distance );
}

void ensure_errno_real( char const* file, int const& line, char const*, char const* msg, bool cond ) {
	if( ! cond ) {
#if defined(TUT_USE_POSIX)
		char e[512];
		std::stringstream ss;
		ss << ( msg ? msg : "" )
			<< ( msg? ": " : "" )
			<< strerror_r( errno, e, sizeof ( e ) );
		throw failure( file, line, ss.str() );
#else
		throw failure( file, line, msg );
#endif
	}
}
void ensure_errno( char const*, bool ) __attribute__((used));
void ensure_errno( char const* msg, bool cond ) {
	ensure_errno_real( NULL, 0, NULL, msg, cond );
}

/**
 * Unconditionally fails with message.
 */
void fail_real( char const*, int, const char* = "" ) __attribute__( ( __noreturn__ ) );
void fail_real( char const* file, int line, const char* msg ) {
	throw failure( file, line, msg );
}
void fail( const char* ) __attribute__((used));
void fail( const char* msg ) {
	fail_real( NULL, 0, msg );
}

void fail_real( char const* file, int line, std::string const& msg ) {
	throw failure( file, line, msg );
}

class time_constraint {
	int long _constraint;
	char const* _path;
	int _line;
	yaal::hcore::HClock _timer;
public:
	time_constraint( int long ms_, char const* path_ = NULL, int line_ = 0 )
		: _constraint( ms_ ), _path( path_ ), _line( line_ ), _timer() {}
	~time_constraint( void ) {
		int long elapsed( static_cast<int long>( _timer.get_time_elapsed( yaal::hcore::time::UNIT::MILISECOND ) ) );
		if ( _constraint && ( elapsed > _constraint ) ) {
			std::stringstream ss;
			ss << "time constraint exceeded: expected [" << _constraint
				<< "ms] actual [" << elapsed << "ms]";
			fail_real( _path, _line, ss.str() );
		}
	}
	void reset( void ) {
		_timer.reset();
	}
	void disable( void ) {
		_constraint = 0;
	}
private:
	time_constraint( time_constraint const& );
	time_constraint& operator = ( time_constraint const& );
};

}       // end of namespace

}

#endif


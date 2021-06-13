#ifndef TUT_ASSERT_H_GUARD
#define TUT_ASSERT_H_GUARD

#include "tut_exception.hpp"

#if defined(TUT_USE_POSIX)
#include <cerrno>
#include <cstring>
#endif

#include <algorithm>
#include <vector>
#include <fstream>

#include <yaal/hcore/hclock.hxx>

namespace tut {

namespace {

/**
 * Tests provided condition.
 * Throws if false.
 */
void ensure_impl( char const* file, int line, std::string const& msg, bool cond ) {
	if ( !cond ) {
		// TODO: default ctor?
		throw failure( file, line, msg );
	}
}
void ensure( char const*, bool ) __attribute__((used));
void ensure( char const* msg, bool cond ) {
	ensure_impl( nullptr, 0, msg, cond );
}

/**
 * Tests provided condition.
 * Throws if false.
 */
void ensure_impl( char const*, int, char const*, char const*, bool ) __attribute__((used));
void ensure_impl( char const* file, int line, char const*, char const* msg, bool cond ) {
	if ( !cond ) {
		throw failure( file, line, msg );
	}
}
void ensure_impl( char const*, int, char const*, yaal::hcore::HString const&, bool ) __attribute__((used));
void ensure_impl( char const* file, int line, char const*, yaal::hcore::HString const& msg, bool cond ) {
	ensure_impl( file, line, yaal::lexical_cast<std::string>( msg ), cond );
}
template<typename T>
void ensure( T const& msg, bool cond ) {
	ensure_impl( nullptr, 0, nullptr, msg, cond );
}

/**
 * Tests provided condition.
 * Throws if true.
 */
void ensure_not_impl( char const* file, int const& line, char const* msg, bool cond ) {
	if ( cond ) {
		// TODO: default ctor?
		throw failure( file, line, msg );
	}
}
void ensure_not( char const*, bool ) __attribute__((used));
void ensure_not( char const* msg, bool cond ) {
	ensure_not_impl( nullptr, 0, msg, cond );
}

/**
 * Tests provided condition.
 * Throws if true.
 */
template<typename T>
void ensure_not_impl( char const* file, int line, char const*, T const& msg, bool cond ) {
	if ( cond )
		throw failure( file, line, msg );
}
template<typename T>
void ensure_not( T const& msg, bool cond ) {
	ensure_not_impl( nullptr, 0, nullptr, msg, cond );
}

template<typename T>
T const& stream_escape( T const& val_ ) {
	return val_;
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
void ensure_equals_impl(
	char const* file, int line, std::string const& msg,
	char const* actualExpr, char const* expectedExpr,
	T const& actual, Q const& expected
) {
	if ( actual == expected ) {
		return;
	}
	std::stringstream ss;
	ss << msg
		<< ( ! msg.empty() ? ":" : "" )
		<< " actual [" << stream_escape( actual ) << "] expected [" << stream_escape( expected ) << "] (" << actualExpr << " == " << expectedExpr << ")";
	throw failure( file, line, ss.str().c_str() );
}
template<class T, class Q>
void ensure_equals_impl(
	char const* file, int line, yaal::hcore::HString const& msg,
	char const* actualExpr, char const* expectedExpr,
	T const& actual, Q const& expected
) {
	ensure_equals_impl( file, line, yaal::lexical_cast<std::string>( msg ), actualExpr, expectedExpr, actual, expected );
}
template<class T, class Q>
void ensure_equals_impl(
	char const* file, int line, char const* msg,
	char const* actualExpr, char const* expectedExpr,
	T const& actual, Q const& expected
) {
	ensure_equals_impl( file, line, std::string( msg ), actualExpr, expectedExpr, actual, expected );
}
template<class T, class Q>
void ensure_equals_impl( char const* file, int line, char const*, std::string const& msg, T const& actual, Q const& expected ) {
	if ( actual == expected ) {
		return;
	}
	std::stringstream ss;
	ss << msg
		<< ( ! msg.empty() ? ":" : "" )
		<< " actual [" << stream_escape( actual ) << "] expected [" << stream_escape( expected ) << "]";
	throw failure( file, line, ss.str().c_str() );
}
template<class T, class Q>
void ensure_equals( const char* msg, T const& actual, Q const& expected ) {
	ensure_equals_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_equals_impl( char const* file,
	int line,
	char const*,
	yaal::hcore::HString const& msg,
	T const& actual, Q const& expected ) {
	ensure_equals_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected );
}
template<class T, class Q>
void ensure_equals( yaal::hcore::HString const& msg, T const& actual, Q const& expected ) {
	ensure_equals_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_equals_impl( char const* file, int line, char const*, char const* msg, T const& actual, Q const& expected ) {
	ensure_equals_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

template<class T, class Q>
void ensure_equals_impl( char const* file, int line, char const* msg, T const& actual, Q const& expected ) {
	ensure_equals_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

/**
 * Tests if object is in given set.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
template<class T, class Q>
void ensure_in_impl( char const* file, int line, char const*, std::string const& msg, const Q& actual,
	const std::vector<T>& expected ) {
	if ( ! ( std::find( expected.begin(), expected.end(), actual ) != expected.end() ) ) {
		std::stringstream ss;
		ss << msg
			<< ( ! msg.empty() ? ":" : "" )
			<< " expected one of";
		for ( T const& v : expected ) {
			ss << " [" << stream_escape( v ) << "]";
		}
		ss << " actual [" << stream_escape( actual ) << "]";
		throw failure( file, line, ss.str().c_str() );
	}
}
template<class T, class Q>
void ensure_in( const char* msg, const Q& actual, const std::vector<T>& expected ) {
	ensure_in_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_in_impl( char const* file,
	int const& line,
	char const*,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const std::vector<T>& expected ) {
	ensure_in_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected );
}
template<class T, class Q>
void ensure_in( yaal::hcore::HString const& msg, const Q& actual, const std::vector<T>& expected ) {
	ensure_in_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_in_impl( char const* file, int const& line, char const*, char const* msg, const Q& actual,
	const std::vector<T>& expected ) {
	ensure_in_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

template<class T, class Q>
void ensure_in_impl( char const* file, int const& line, char const* msg, const Q& actual,
	const std::vector<T>& expected ) {
	ensure_in_impl<>( file, line, nullptr, msg, actual, expected );
}

/**
 * Tests two objects for first being less then second.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
template<class T, class Q>
void ensure_less_impl( char const* file, int line, char const*, std::string const& msg, const Q& actual,
	const T& expected ) {
	if ( ! ( actual < expected ) ) {
		std::stringstream ss;
		ss << msg
		<< ( ! msg.empty() ? ":" : "" )
		<< " [" << stream_escape( actual ) << "] expected being less than [" << stream_escape( expected ) << "]";
		throw failure( file, line, ss.str().c_str() );
	}
}
template<class T, class Q>
void ensure_less( const char* msg, const Q& actual, const T& expected ) {
	ensure_less_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_less_impl( char const* file,
	int const& line,
	char const*,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const T& expected ) {
	ensure_less_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected );
}
template<class T, class Q>
void ensure_less( yaal::hcore::HString const& msg, const Q& actual, const T& expected ) {
	ensure_less_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_less_impl( char const* file, int const& line, char const*, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_less_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

template<class T, class Q>
void ensure_less_impl( char const* file, int const& line, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_less_impl<>( file, line, nullptr, msg, actual, expected );
}

/**
 * Tests two objects for first being greater then second.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
template<class T, class Q>
void ensure_greater_impl( char const* file, int line, char const*, std::string const& msg, const Q& actual,
	const T& expected ) {
	if ( ! ( actual > expected ) ) {
		std::stringstream ss;
		ss << msg
		<< ( ! msg.empty() ? ":" : "" )
		<< " [" << stream_escape( actual ) << "] expected being greater than [" << stream_escape( expected ) << "]";
		throw failure( file, line, ss.str().c_str() );
	}
}
template<class T, class Q>
void ensure_greater( const char* msg, const Q& actual, const T& expected ) {
	ensure_greater_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_greater_impl( char const* file,
	int const& line,
	char const*,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const T& expected ) {
	ensure_greater_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected );
}
template<class T, class Q>
void ensure_greater( yaal::hcore::HString const& msg, const Q& actual, const T& expected ) {
	ensure_greater_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_greater_impl( char const* file, int const& line, char const*, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_greater_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

template<class T, class Q>
void ensure_greater_impl( char const* file, int const& line, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_greater_impl<>( file, line, nullptr, msg, actual, expected );
}

/**
 * Tests two objects for first being less_or_equal then second.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
template<class T, class Q>
void ensure_less_or_equal_impl( char const* file, int line, char const*, std::string const& msg, const Q& actual,
	const T& expected ) {
	if ( ! ( actual <= expected ) ) {
		std::stringstream ss;
		ss << msg
		<< ( ! msg.empty() ? ":" : "" )
		<< " [" << stream_escape( actual ) << "] expected being less or equal than [" << stream_escape( expected ) << "]";
		throw failure( file, line, ss.str().c_str() );
	}
}
template<class T, class Q>
void ensure_less_or_equal( const char* msg, const Q& actual, const T& expected ) {
	ensure_less_or_equal_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_less_or_equal_impl( char const* file,
	int const& line,
	char const*,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const T& expected ) {
	ensure_less_or_equal_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected );
}
template<class T, class Q>
void ensure_less_or_equal( yaal::hcore::HString const& msg, const Q& actual, const T& expected ) {
	ensure_less_or_equal_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_less_or_equal_impl( char const* file, int const& line, char const*, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_less_or_equal_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

template<class T, class Q>
void ensure_less_or_equal_impl( char const* file, int const& line, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_less_or_equal_impl<>( file, line, nullptr, msg, actual, expected );
}

/**
 * Tests two objects for first being greater_or_equal then second.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
template<class T, class Q>
void ensure_greater_or_equal_impl( char const* file, int line, char const*, std::string const& msg, const Q& actual,
	const T& expected ) {
	if ( ! ( actual >= expected ) ) {
		std::stringstream ss;
		ss << msg
			<< ( ! msg.empty() ? ":" : "" )
			<< " [" << stream_escape( actual ) << "] expected being greater or equal than [" << stream_escape( expected ) << "]";
		throw failure( file, line, ss.str().c_str() );
	}
}

template<class T, class Q>
void ensure_greater_or_equal( const char* msg, const Q& actual, const T& expected ) {
	ensure_greater_or_equal_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_greater_or_equal_impl( char const* file,
	int const& line,
	char const*,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const T& expected ) {
	ensure_greater_or_equal_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected );
}
template<class T, class Q>
void ensure_greater_or_equal( yaal::hcore::HString const& msg, const Q& actual, const T& expected ) {
	ensure_greater_or_equal_impl( nullptr, 0, nullptr, msg, actual, expected );
}

template<class T, class Q>
void ensure_greater_or_equal_impl( char const* file, int const& line, char const*, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_greater_or_equal_impl<>( file, line, nullptr, std::string( msg ), actual, expected );
}

template<class T, class Q>
void ensure_greater_or_equal_impl( char const* file, int const& line, char const* msg, const Q& actual,
	const T& expected ) {
	ensure_greater_or_equal_impl<>( file, line, nullptr, msg, actual, expected );
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
void ensure_distance_impl( char const* file, int const& line, char const*, std::string const& msg, const T& actual,
	const T& expected, const T& distance ) {
	if ( ( ( expected - distance ) >= actual ) || ( ( expected + distance ) <= actual ) ) {
		std::stringstream ss;
		ss << msg
			<< ( ! msg.empty() ? ":" : "" )
			<< " expected ("
			<< expected - distance
			<< ";" << expected + distance << ") actual [" << actual << "] distance <" << distance << ">";
		throw failure( file, line, ss.str().c_str() );
	}
}

template<class T>
void ensure_distance( const char* msg, const T& actual, const T& expected, const T& distance ) {
	ensure_distance_impl( nullptr, 0, nullptr, msg, actual, expected, distance );
}

template<class T>
void ensure_distance_impl( char const* file, int const& line, char const*,
	yaal::hcore::HString const& msg, const T& actual,
	const T& expected, const T& distance ) {
	ensure_distance_impl<>( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual, expected, distance );
}
template<class T>
void ensure_distance( yaal::hcore::HString const& msg, const T& actual, const T& expected, const T& distance ) {
	ensure_distance_impl( nullptr, 0, nullptr, msg, actual, expected, distance );
}

template<class T>
void ensure_distance_impl( char const* file, int line, char const*, const char* msg, const T& actual,
	const T& expected, const T& distance ) {
	ensure_distance_impl<>( file, line, nullptr, std::string( msg ), actual, expected, distance );
}

template<class T>
void ensure_distance_impl( char const* file, int line, const char* msg, const T& actual,
	const T& expected, const T& distance ) {
	ensure_distance_impl<>( file, line, nullptr, msg, actual, expected, distance );
}

void ensure_same_content_impl( char const* file, int const& line, char const*, std::string const& msg, std::string const& actual_, std::string const& expected_ ) {
	std::ifstream actual( actual_.c_str() );
	std::ifstream expected( expected_.c_str() );
	std::string actualLine;
	std::string expectedLine;
	int lineNo( 1 );
	std::stringstream ss;
	while ( true ) {
		bool actualStatus( std::getline( actual, actualLine ).good() );
		bool expectedStatus( std::getline( expected, expectedLine ).good() );
		if ( actualStatus && expectedStatus ) {
			if ( actualLine == expectedLine ) {
				++ lineNo;
				continue;
			}
			ss << msg
				<< ( ! msg.empty() ? ": " : " " )
				<< "line [" << lineNo << "] actual [" << stream_escape( actualLine ) << "] expected [" << stream_escape( expectedLine ) << "]";
		} else if ( expectedStatus && ! actualStatus ) {
			ss << msg
				<< ( ! msg.empty() ? ": " : " " )
				<< actual_ << " is missing data, expected [" << stream_escape( expectedLine ) << "]";
		} else if ( actualStatus && ! expectedStatus ) {
			ss << msg
				<< ( ! msg.empty() ? ": " : " " )
				<< actual_ << " conatins extra data: [" << stream_escape( actualLine ) << "]";
		} else {
			break;
		}
		throw failure( file, line, ss.str().c_str() );
	}
	return;
}

inline void ensure_same_content( std::string const& msg, std::string const& actual_, std::string const& expected_ ) {
	ensure_same_content_impl( nullptr, 0, nullptr, msg, actual_, expected_ );
}

void ensure_same_content_impl( char const* file, int const& line, char const*, yaal::hcore::HString const& msg, std::string const& actual_, std::string const& expected_ ) {
	ensure_same_content_impl( file, line, nullptr, yaal::lexical_cast<std::string>( msg ), actual_, expected_ );
}

inline void ensure_same_content( yaal::hcore::HString const& msg, std::string const& actual_, std::string const& expected_ ) {
	ensure_same_content_impl( nullptr, 0, nullptr, msg, actual_, expected_ );
}

inline void ensure_same_content_impl( char const* file, int const& line, char const*, char const* msg, std::string const& actual_, std::string const& expected_ ) {
	ensure_same_content_impl( file, line, nullptr, std::string( msg ), actual_, expected_ );
}

inline void ensure_same_content_impl( char const* file, int const& line, char const* msg, std::string const& actual_, std::string const& expected_ ) {
	ensure_same_content_impl( file, line, nullptr, std::string( msg ), actual_, expected_ );
}

void ensure_errno_impl( char const* file, int const& line, char const*, char const* msg, bool cond ) {
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
	ensure_errno_impl( nullptr, 0, nullptr, msg, cond );
}

/**
 * Unconditionally fails with message.
 */
void fail_impl( char const*, int, const char* = "" ) __attribute__( ( __noreturn__ ) );
void fail_impl( char const* file, int line, const char* msg ) {
	throw failure( file, line, msg );
}
void fail( const char* ) __attribute__((used));
void fail( const char* msg ) {
	fail_impl( nullptr, 0, msg );
}

void fail_impl( char const* file, int line, std::string const& msg ) {
	throw failure( file, line, msg );
}

class time_constraint {
	int long _constraint;
	char const* _path;
	int _line;
	yaal::hcore::HClock _timer;
public:
	time_constraint( int long ms_, char const* path_ = nullptr, int line_ = 0 )
		: _constraint( ms_ )
		, _path( path_ )
		, _line( line_ )
		, _timer() {
	}
	~time_constraint( void ) {
		int long elapsed( static_cast<int long>( _timer.get_time_elapsed( yaal::hcore::time::UNIT::MILLISECOND ) ) );
		if ( _constraint && ( elapsed > _constraint ) ) {
			std::stringstream ss;
			ss << "time constraint exceeded: expected [" << _constraint
				<< "ms] actual [" << elapsed << "ms]";
			fail_impl( _path, _line, ss.str() );
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

/**
 * Unconditionally skip with message.
 */
void skip_impl( char const*, int, const char* = "" ) __attribute__((__noreturn__, __used__));
void skip_impl( char const* file, int line, const char* msg ) {
	throw skipper( file, line, msg );
}
void skip( const char* ) __attribute__((used));
void skip( const char* msg ) {
	skip_impl( nullptr, 0, msg );
}

void skip_impl( char const*, int, std::string const& ) __attribute__((__noreturn__, __used__));
void skip_impl( char const* file, int line, std::string const& msg ) {
	throw skipper( file, line, msg );
}

}       // end of namespace

}

#endif


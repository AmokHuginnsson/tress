#ifndef TUT_ASSERT_H_GUARD
#define TUT_ASSERT_H_GUARD

#include "tut_exception.hpp"

#if defined(TUT_USE_POSIX)
#include <errno.h>
#include <cstring>
#endif

namespace tut
{

namespace
{
/**
 * Tests provided condition.
 * Throws if false.
 */
#define ensure( ... ) ensure_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )

void ensure_real( char const* const file, int const& line, char const* const msg, bool cond )
	{
	if ( !cond )
		{
		// TODO: default ctor?
		throw failure( file, line, msg );
		}
	}

/**
 * Tests provided condition.
 * Throws if false.
 */
template<typename T>
void ensure_real( char const* const file, int const& line, char const* const, const T msg, bool cond )
	{
	if ( !cond )
		throw failure( file, line, msg );
	}

#define ensure_not( ... ) ensure_not_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )

/**
 * Tests provided condition.
 * Throws if true.
 */
void ensure_not_real( char const* const file, int const& line, char const* const msg, bool cond )
	{
	if ( cond )
		{
		// TODO: default ctor?
		throw failure( file, line, msg );
		}
	}

/**
 * Tests provided condition.
 * Throws if true.
 */
template<typename T>
void ensure_not_real( char const* const file, int const& line, char const* const, const T msg, bool cond )
	{
	if ( cond )
		throw failure( file, line, msg );
	}

/**
 * Tests two objects for being equal.
 * Throws if false.
 *
 * NB: both T and Q must have operator << defined somewhere, or
 * client code will not compile at all!
 */
#define ensure_equals( ... ) ensure_equals_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )

template<class T, class Q>
void ensure_equals_real( char const* const file, int const& line, char const* const, const char* msg, const Q& actual,
	const T& expected )
	{
	if ( expected != actual )
		{
		std::stringstream ss;
		ss << ( msg ? msg : "" )
		<< ( msg ? ":" : "" )
		<< " expected [" << expected << "] actual [" << actual << "]";
		throw failure( file, line, ss.str().c_str() );
		}
	}

template<class T, class Q>
void ensure_equals_real( char const* const file,
	int const& line,
	char const* const,
	yaal::hcore::HString const& msg,
	const Q& actual,
	const T& expected )
	{
	ensure_equals_real<>( file, line, NULL, msg.raw(), actual, expected );
	}

template<class T, class Q>
void ensure_equals_real( char const* const file, int const& line, char const* const msg, const Q& actual,
	const T& expected )
	{
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
#define ensure_distance( ... ) ensure_distance_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
template<class T>
void ensure_distance_real( char const* const file, int const& line, char const* const, const char* msg, const T& actual,
	const T& expected, const T& distance )
	{
	if ( ( expected - distance >= actual ) || ( expected + distance <= actual ) )
		{
		std::stringstream ss;
		ss << ( msg ? msg : "" )
		<< ( msg ? ":" : "" )
		<< "expected ("
		<< expected - distance
		<< ";" << expected + distance << ") actual [" << actual << "]";
		throw failure( file, line, ss.str().c_str() );
		}
	}

template<class T>
void ensure_distance_real( char const* const file, int const& line, const char* msg, const T& actual,
	const T& expected, const T& distance )
	{
	ensure_distance_real<>( file, line, NULL, msg, actual, expected, distance );
	}

/**
 * Unconditionally fails with message.
 */

#define fail( msg ) fail_real( __FILE__, __LINE__, ( msg ) )
void fail_real( char const* const, int const&, const char* = "" ) __attribute__( ( __noreturn__ ) );
void fail_real( char const* const file, int const& line, const char* msg )
	{
	throw failure( file, line, msg );
	}
}       // end of namespace

}

#endif


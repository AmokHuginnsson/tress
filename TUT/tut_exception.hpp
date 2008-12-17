#ifndef TUT_EXCEPTION_H_GUARD
#define TUT_EXCEPTION_H_GUARD

#include <stdexcept>

namespace tut
{

/**
 * The base for all TUT exceptions.
 */
struct tut_error : public std::exception
	{
	tut_error( const std::string& msg ) : _errMsg( msg )
		{}

	~tut_error() throw ( )
		{}

	const char* what() const throw ( )
		{
		return ( _errMsg.c_str() ) ;
		}

	private:

	std::string _errMsg;
	};

/**
 * Exception to be throwed when attempted to execute
 * missed test by number.
 */
struct no_such_test : public tut_error
	{
	no_such_test() : tut_error( "no such test" )
		{}
	~no_such_test() throw ( )
		{}
	};

/**
 * No such test and passed test number is higher than
 * any test number in current group. Used in one-by-one
 * test running when upper bound is not known.
 */
struct beyond_last_test : public no_such_test
	{
	beyond_last_test()
		{}
	~beyond_last_test() throw ()
		{}
	};

/**
 * Group not found exception.
 */
struct no_such_group : public tut_error
	{
	no_such_group( std::string const& grp ) : tut_error( grp )
		{}
	~no_such_group() throw ()
		{}
	};

/**
 * Internal exception to be throwed when
 * no more tests left in group or journal.
 */
struct no_more_tests
	{
	no_more_tests()
		{}
	~no_more_tests() throw ()
		{}
	};

/**
 * Internal exception to be throwed when
 * test constructor has failed.
 */
struct bad_ctor : public tut_error
	{
	bad_ctor( std::string const& msg ) : tut_error( msg )
		{}
	~bad_ctor() throw ()
		{}
	};

/**
 * Exception to be throwed when ensure() fails or fail() called.
 */
struct failure : public tut_error
	{
	std::string _file;
	int _line;
	failure( char const* const file, int const& line, const std::string& msg ) : tut_error( msg ), _file( file ), _line( line )
		{}
	~failure() throw ()
		{}
	};

/**
 * Exception to be throwed when test desctructor throwed an exception.
 */
struct warning : public tut_error
	{
	warning( std::string const& msg ) : tut_error( msg )
		{}
	~warning() throw ()
		{}
	};

}

#endif

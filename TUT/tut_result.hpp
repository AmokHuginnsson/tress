#ifndef TUT_RESULT_H_GUARD
#define TUT_RESULT_H_GUARD

#include <string>

namespace tut
{
#if defined ( TUT_USE_POSIX )
struct test_result_posix
	{
	test_result_posix() : pid( getpid() )
		  {}

	pid_t pid;
	};
#else
struct test_result_posix
	{};
#endif

/**
 * Return type of runned test/test group.
 *
 * For test: contains result of test and, possible, message
 * for failure or exception.
 */
struct test_result : public test_result_posix
	{
	/**
	* Test group name.
	*/
	std::string _group;

	/**
	* Test number in group.
	*/
	int _testNo;

	/**
	* Test name (optional)
	*/
	std::string _name;

	/**
	* ok - test finished successfully
	* fail - test failed with ensure() or fail() methods
	* ex - test throwed an exceptions
	* warn - test finished successfully, but test destructor throwed
	* term - test forced test application to terminate abnormally
	* setup - bad test setup (no such group or no such test number)
	*/
	typedef enum { ok, fail, ex, warn, term, ex_ctor, setup, rethrown } result_type_t;

	result_type_t _result;

	/**
	* Exception message for failed test.
	*/
	std::string _message;
	std::string _exceptionTypeId;
	std::string _file;
	int _line;

	/**
	* Default constructor.
	*/
	test_result() : _testNo( 0 ), _result( ok ), _line( -1 )
		{}

	/**
	* Constructor.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		char const* const file, int const& line )
		: _group( grp ), _testNo( pos ), _name( test_name ), _result( res ), _file( file ), _line( line )
		{}

	/**
	* Constructor with exception.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const std::exception& exc, char const* const file, int const& line )
		: _group( grp ), _testNo( pos ), _name( test_name ), _result( res ),
		_message( exc.what() ), _exceptionTypeId( typeid ( exc ).name() ), _file( file ), _line( line )
		{}

	/**
	* Constructor with failure.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const failure_info& f )
		: _group( grp ), _testNo( pos ), _name( test_name ), _result( res ),
		_message( f._msg ), _exceptionTypeId( typeid ( f ).name() ), _file( f._file ), _line( f._line )
		{}

	/**
	* Constructor with exception.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const yaal::hcore::HException& exc, char const* const file, int const& line )
		: _group( grp ), _testNo( pos ), _name( test_name ), _result( res ),
		_message( exc.what() ), _exceptionTypeId( typeid ( exc ).name() ), _file( file ), _line( line )
		{}

	/** Constructor with typeid.
	 */
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const std::string& ex_typeid,
		const std::string& msg )
		: _group( grp ),	_testNo( pos ), _name( test_name ), _result( res ),
		_message( msg ), _exceptionTypeId( ex_typeid )
		  {}
	};

}

#endif


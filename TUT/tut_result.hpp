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
	virtual ~test_result_posix( void )
		{}

	pid_t pid;
	};
#else
struct test_result_posix
	{
	virtual ~test_result_posix( void )
		{}
	};
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
	test_result() : _group(), _testNo( 0 ), _name(), _result( ok ), _message(), _exceptionTypeId(), _file( "" ), _line( -1 )
		{}

	/**
	 * Constructor.
	 */
	test_result( std::string const& grp, int pos )
		: _group( grp ), _testNo( pos ), _name(), _result( ok ), _message(), _exceptionTypeId(), _file( "" ), _line( -1 )
		{}

	/**
	 * Set addtional per-exception information (that is always available/meaningful.
	 */
	void set_meta( std::string const& test_name, char const* const file, int const& line )
		{
		_name = test_name;
		_file = file;
		_line = line;
		}

	/**
	 * Set exception specific informational data.
	 */
	void set_meta( result_type_t res, std::string const& ex_typeid = std::string(), std::string const& msg = std::string() )
		{
		_result = res;
		_exceptionTypeId = ex_typeid;
		_message = msg;
		}

	};

}

#endif


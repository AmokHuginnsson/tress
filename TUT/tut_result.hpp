#ifndef TUT_RESULT_H_GUARD
#define TUT_RESULT_H_GUARD

#include <string>

namespace tut {
#if defined ( TUT_USE_POSIX )
struct test_result_posix {
	test_result_posix() : pid( getpid() )
		  {}
	virtual ~test_result_posix( void )
		{}

	pid_t pid;
};
#else
struct test_result_posix {
	virtual ~test_result_posix( void )
		{}
};
#endif

struct group_base;

/**
 * Return type of runned test/test group.
 *
 * For test: contains result of test and, possible, message
 * for failure or exception.
 */
struct test_result : public test_result_posix {
	/**
	* Test group name.
	*/
	group_base* _group;

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
	* setup - bad test setup no such group
	* setup_test_number - bad test setup no such test number
	*/
	typedef enum { ok, fail, ex, warn, term, ex_ctor, setup, setup_test_number, rethrown } result_type_t;

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
	test_result()
		: test_result_posix(),
		_group( NULL ), _testNo( 0 ), _name(), _result( ok ), _message(), _exceptionTypeId(), _file( "" ), _line( -1 )
		{}

	/**
	 * Constructor.
	 */
	test_result( group_base* grp, int pos )
		: test_result_posix(),
		_group( grp ), _testNo( pos ), _name(), _result( ok ), _message(), _exceptionTypeId(), _file( "" ), _line( -1 )
		{}

	test_result( test_result const& tr_ )
		: test_result_posix(),
		_group( tr_._group ), _testNo( tr_._testNo ),
		_name( tr_._name ), _result( tr_._result ), _message( tr_._message ),
		_exceptionTypeId( tr_._exceptionTypeId ), _file( tr_._file ),
		_line( tr_._line )
		{}

	/**
	 * Set addtional per-exception information (that is always available/meaningful.
	 */
	void set_meta( std::string const& testName_, char const* const file = NULL, int const& line = -1 ) {
		_name = testName_;
		if ( file )
			_file = file;
		_line = line;
	}

	/**
	 * Set exception specific informational data.
	 */
	void set_meta( result_type_t res, std::string const& ex_typeid = std::string(), std::string const& msg = std::string() ) {
		_result = res;
		_exceptionTypeId = ex_typeid;
		_message = msg;
	}

	test_result& operator = ( test_result const& tr_ ) {
		if ( &tr_ != this ) {
			test_result tmp( tr_ );
			swap( tmp );
		}
		return ( *this );
	}

	void swap( test_result& tr_ ) {
		if ( &tr_ != this ) {
			using std::swap;
			swap( _group, tr_._group );
			swap( _testNo, tr_._testNo );
			swap( _name, tr_._name );
			swap( _result, tr_._result );
			swap( _message, tr_._message );
			swap( _exceptionTypeId, tr_._exceptionTypeId );
			swap( _file, tr_._file );
			swap( _line, tr_._line );
		}
		return;
	}

};

}

#endif


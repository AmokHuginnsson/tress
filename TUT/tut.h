#ifndef TUT_H_GUARD
#define TUT_H_GUARD

#include <errno.h>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <typeinfo>
#include <stdexcept>

#define GET_YAAL_CONFIG
#include <yaal/yaal.h>
#undef GET_YAAL_CONFIG
#undef __YAAL_H

#include <yaal/hcore/base.h>
#include <yaal/hcore/hcall.h>
#include <yaal/tools/hworkflow.h>

#include "src/setup.h"

/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */
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

/**
 * Return type of runned test/test group.
 *
 * For test: contains result of test and, possible, message
 * for failure or exception.
 */
struct test_result
	{
	/**
	* Test group name.
	*/
	std::string group;

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
	typedef enum { ok, fail, ex, warn, term, ex_ctor, setup } result_type_t;

	result_type_t result;

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
	test_result() : _testNo( 0 ), result( ok ), _line( -1 )
		{}

	/**
	* Constructor.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		char const* const file, int const& line )
		: group( grp ), _testNo( pos ), _name( test_name ), result( res ), _file( file ), _line( line )
		{}

	/**
	* Constructor with exception.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const std::exception& exc, char const* const file, int const& line )
		: group( grp ), _testNo( pos ), _name( test_name ), result( res ),
		_message( exc.what() ), _exceptionTypeId( typeid ( exc ).name() ), _file( file ), _line( line )
		{}

	/**
	* Constructor with failure.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const failure& f )
		: group( grp ), _testNo( pos ), _name( test_name ), result( res ),
		_message( f.what() ), _exceptionTypeId( typeid ( f ).name() ), _file( f._file ), _line( f._line )
		{}

	/**
	* Constructor with exception.
	*/
	test_result( const std::string& grp, int pos,
		const std::string& test_name, result_type_t res,
		const yaal::hcore::HException& exc, char const* const file, int const& line )
		: group( grp ), _testNo( pos ), _name( test_name ), result( res ),
		_message( exc.what() ), _exceptionTypeId( typeid ( exc ).name() ), _file( file ), _line( line )
		{}
	};

/**
 * Interface.
 * Test group operations.
 */
struct group_base
	{
	virtual ~group_base()
		{}

	// execute tests iteratively
	virtual void rewind() = 0;
	virtual test_result run_next() = 0;
	virtual bool has_next() = 0;
	virtual int next() = 0;

	// execute one test
	virtual test_result run_test( int n ) = 0;
	};

/**
 * Test runner callback interface.
 * Can be implemented by caller to update
 * tests results in real-time. User can implement
 * any of callback methods, and leave unused
 * in default implementation.
 */
struct callback
	{
	/**
	* Virtual destructor is a must for subclassed types.
	*/
	virtual ~callback()
		{}

	/**
	* Called when new test run started.
	*/
	virtual void run_started()
		{}

	/**
	* Called when a group started
	* @param name Name of the group
	*/
	virtual void group_started( const std::string& /*name */ )
		{}

	/**
	* Called when a test finished.
	* @param tr Test results.
	*/
	virtual void test_completed( const test_result& /*tr */ )
		{}

	/**
	* Called when a group is completed
	* @param name Name of the group
	*/
	virtual void group_completed( const std::string& /*name */ )
		{}

	/**
	* Called when a test is about to start.
	*/
	virtual void test_started( const int& /*n */ )
		{}

	/**
	* Called when all tests in run completed.
	*/
	virtual void run_completed()
		{}
	};

/**
 * Typedef for runner::list_groups()
 */
typedef std::list<std::string> groupnames;

/**
 * Listener of tut events.
 */
class tut_listener
	{
public:
	void register_execution( const std::string& grp, int test, std::string const& name, std::string const& file, int const& line ) const
		{ do_register_execution( grp, test, name, file, line ); }
	virtual ~tut_listener( void ) { }
protected:
	virtual void do_register_execution( const std::string&, int, std::string const&, std::string const&, int const& ) const = 0;
	};

/**
 * Test runner.
 */
class test_runner
	{
	public:

	/**
	* Constructor
	*/
	test_runner() : _callback( &default_callback_ ), _tutListener( NULL )
		{}

	/**
	* Stores another group for getting by name.
	*/
	void register_group( const std::string& name, group_base* gr )
		{
		if ( gr == 0 )
			{
			throw std::invalid_argument( "group shall be non-null" );
			}

		// TODO: inline variable
		groups::iterator found = groups_.find( name );
		if ( found != groups_.end() )
			{
			std::string msg( "attempt to add already existent group " + name );

			// this exception terminates application so we use cerr also
			// TODO: should this message appear in stream?
			std::cerr << msg << std::endl;
			throw tut_error( msg );
			}

		groups_[ name ] = gr;
		}

	/**
	* Stores callback object.
	*/
	void set_callback( callback* cb )
		{
		_callback = cb == 0 ? &default_callback_ : cb;
		}

	/**
	* Stores callback object.
	*/
	void set_listener( tut_listener* tl )
		{
		_tutListener = tl;
		}
	
	tut_listener* get_listener( void )
		{
		return ( _tutListener );
		}

	/**
	* Returns callback object.
	*/
	callback& get_callback() const
		{
		return ( *_callback ) ;
		}

	/**
	* Returns list of known test groups.
	*/
	const groupnames list_groups() const
		{
		groupnames ret;
		const_iterator i = groups_.begin();
		const_iterator e = groups_.end();

		while ( i != e )
			{
			ret.push_back( i->first );
			++ i;
			}

		return ( ret ) ;
		}

	/**
	* Runs all tests in all groups.
	* @param callback Callback object if exists; null otherwise
	*/
	void run_tests() const
		{
		_callback->run_started();

			{
			const_iterator e = groups_.end();
			yaal::tools::HWorkFlow w( tress::setup.f_iJobs );
			for ( const_iterator i = groups_.begin(); i != e; ++ i )
				{
				group_runner_t::ptr_t gr( new group_runner_t( *this, &test_runner::run_group, i ) );
				w.push_task( gr );
				}
			}

		_callback->run_completed();
		}

	/**
	* Runs all tests in specified groups.
	*/
	void run_tests( const std::list<std::string>& group_names ) const
		{
		_callback->run_started();

			{
			yaal::tools::HWorkFlow w( tress::setup.f_iJobs );
			for ( std::list<std::string>::const_iterator k = group_names.begin();
					k != group_names.end(); ++ k )
				{
				const_iterator i = groups_.find( *k );
				if ( i == groups_.end() )
					{
					test_result tr( *k, 0, "", test_result::setup,
							tress::setup.f_oTestGroupListFilePath.raw(),
							static_cast<int>( std::distance( group_names.begin(), k ) ) );
					_callback->test_completed( tr );
					}
				else
					{
					group_runner_t::ptr_t gr( new group_runner_t( *this, &test_runner::run_group, i ) );
					w.push_task( gr );
					}
				}
			}

		_callback->run_completed();
		}

	/**
	* Runs all tests in all groups that are matching pattern.
	* @param callback Callback object if exists; null otherwise
	*/
	void run_pattern_tests( char const* pattern ) const
		{
		_callback->run_started();

			{
			yaal::tools::HWorkFlow w( tress::setup.f_iJobs );
			const_iterator e = groups_.end();
			for ( const_iterator i = groups_.begin(); i != e; ++ i )
				{
				if ( i->first.find( pattern ) != std::string::npos )
					{
					group_runner_t::ptr_t gr( new group_runner_t( *this, &test_runner::run_group, i ) );
					w.push_task( gr );
					}
				}
			}

		_callback->run_completed();
		}

	/**
	* Runs one test in specified group.
	*/
	test_result run_test( const std::string& group_name, int n ) const
		{
		_callback->run_started();

		const_iterator i = groups_.find( group_name );
		if ( i == groups_.end() )
			{
			_callback->run_completed();
			throw no_such_group( group_name );
			}

		_callback->group_started( group_name );
		_callback->test_started( n );

		try
			{
			test_result tr = i->second->run_test( n );
			_callback->test_completed( tr );
			_callback->group_completed( group_name );
			_callback->run_completed();
			return ( tr ) ;
			}
		catch ( const beyond_last_test& )
			{
			_callback->group_completed( group_name );
			_callback->run_completed();
			throw;
			}
		catch ( const no_such_test& )
			{
			_callback->group_completed( group_name );
			_callback->run_completed();
			throw;
			}
		}

	protected:

	typedef std::map<std::string, group_base*>groups;
	typedef groups::iterator iterator;
	typedef groups::const_iterator const_iterator;
	typedef void ( test_runner::* group_call_t )( const_iterator ) const;
	typedef yaal::hcore::HCall<test_runner, group_call_t, const_iterator> group_runner_t;
	groups groups_;

	callback default_callback_;
	callback* _callback;
	tut_listener* _tutListener;

	private:

	void run_group( const_iterator i ) const
		{
		_callback->group_started( i->first );
		try
			{
			run_all_tests_in_group_( i );
			}
		catch ( const no_more_tests& )
			{
			_callback->group_completed( i->first );
			}
		}

	void run_all_tests_in_group_( const_iterator i ) const
		{
		i->second->rewind();
		if ( i != i )
			return;

		for ( int n = 1;; ++ n )
			{
			if ( i->second->has_next() )
				_callback->test_started( i->second->next() );

			test_result tr = i->second->run_next();
			_callback->test_completed( tr );

			if ( tr.result == test_result::ex_ctor )
				{
				throw no_more_tests();
				}
			}
		}
	};

/**
 * Singleton for test_runner implementation.
 * Instance with name runner_singleton shall be implemented
 * by user.
 */
class test_runner_singleton
	{
	public:

	static test_runner& get()
		{
		static test_runner tr;

		return ( tr ) ;
		}
	};

extern test_runner_singleton runner;

/**
 * Test object. Contains data test run upon and default test method
 * implementation. Inherited from Data to allow tests to
 * access test data as members.
 */
template<class Data>
class test_object : public Data
	{
	std::string _group;
	int _testNo;
	char const* _file;
	int _line;
	public:

	/**
	* Default constructor
	*/
	test_object() : _group(), _testNo( 0 ), _file( "" ), _line( 0 ), _currentTestName()
		{}

	void set_test_tut( std::string const& groupName, int const& testNo )
		{
		_group = groupName;
		_testNo = testNo;
		}

	void set_test_meta( const std::string& current_test_name, char const* const file, int const& line )
		{
		_currentTestName = current_test_name;
		_file = file;
		_line = line;
		tut_listener* tl = runner.get().get_listener();
		if ( tress::setup.f_bRestartable && tl )
			tl->register_execution( _group, _testNo, _currentTestName, _file, _line );
		}

	const std::string& get_test_name() const
		{
		return ( _currentTestName ) ;
		}

	char const* get_test_file( void )
		{
		return ( _file );
		}

	int get_test_line( void )
		{
		return ( _line );
		}

	/**
	* Default do-nothing test.
	*/
	template<int n> void test()
		{
		called_method_was_a_dummy_test_ = true;
		}

	/**
	* The flag is set to true by default (dummy) test.
	* Used to detect usused test numbers and avoid unnecessary
	* test object creation which may be time-consuming depending
	* on operations described in Data::Data() and Data::~Data().
	* TODO: replace with throwing special exception from default test.
	*/
	bool called_method_was_a_dummy_test_;

	private:

	std::string _currentTestName;
	};

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

/**
 * Walks through test tree and stores address of each
 * test method in group. Instantiation stops at 0.
 */
template<class Test, class Group, int n> struct tests_registerer
	{
	static void register_test_method( Group& group )
		{
		group.register_test_method( n, &Test::template test<n> );
		tests_registerer<Test, Group, n - 1>::register_test_method( group );
		}
	};

template<class Test, class Group>
struct tests_registerer<Test, Group, 0>
	{
	static void register_test_method( Group& )
		{}
	};

/**
 * Test group; used to recreate test object instance for
 * each new test since we have to have reinitialized
 * Data base class.
 */
template<typename Data, int MaxTestsInGroup = 50>
class test_group : public group_base
	{
	const char* _name;
	typedef test_object<Data> test_object_data;
	typedef void ( test_object_data::* testmethod )();
	typedef std::map<int, testmethod> tests_t;
	typedef typename tests_t::iterator tests_iterator;
	typedef typename tests_t::const_iterator tests_const_iterator;
	typedef typename tests_t::const_reverse_iterator
	tests_const_reverse_iterator;
	typedef typename tests_t::size_type size_type;

	tests_t _tests;
	tests_iterator _currentTest;

	/**
	* Exception-in-destructor-safe smart-pointer class.
	*/
	template<class T>
	class safe_holder
		{
		T* _obj;
		bool permit_throw_in_dtor;

		safe_holder( const safe_holder& );
		safe_holder& operator =( const safe_holder& );

		public:
		safe_holder() : _obj( 0 ), permit_throw_in_dtor( false )
			{}

		~safe_holder()
			{
			release();
			}

		T* operator ->() const
			{
			return ( _obj ) ;
			}

		T* get() const
			{
			return ( _obj ) ;
			}

		/**
		* Tell ptr it can throw from destructor. Right way is to
		* use std::uncaught_exception(), but some compilers lack
		* correct implementation of the function.
		*/
		void permit_throw()
			{
			permit_throw_in_dtor = true;
			}

		/**
		* Specially treats exceptions in test object destructor;
		* if test itself failed, exceptions in destructor
		* are ignored; if test was successful and destructor failed,
		* warning exception throwed.
		*/
		void release()
			{
			try
				{
				delete_obj();
				}
			catch ( const std::exception& ex )
				{
				if ( permit_throw_in_dtor )
					{
					std::string msg = "destructor of test object raised"
					" exception: ";
					msg += ex.what();
					throw warning( msg );
					}
				}
			catch ( ... )
				{
				if ( permit_throw_in_dtor )
					{
					throw warning( "destructor of test object raised an"
						" exception" );
					}
				}
			}

		/**
		* Re-init holder to get brand new object.
		*/
		void reset()
			{
			release();
			permit_throw_in_dtor = false;
			_obj = new T();
			}

		bool delete_obj()
			{
			T* p = _obj;
			_obj = 0;
			delete p;
			return ( true ) ;
			}
		};

	public:

	typedef test_object<Data> object;

	/**
	* Creates and registers test group with specified name.
	*/
	test_group( const char* name ) : _name( name )
		{
		// register itself
		runner.get().register_group( _name, this );

		// register all tests
		tests_registerer<object, test_group, MaxTestsInGroup>::register_test_method( *this );
		}

	/**
	* This constructor is used in self-test run only.
	*/
	test_group( const char* name, test_runner& another_runner ) : _name( name )
		{
		// register itself
		another_runner.register_group( _name, this );

		// register all tests
		tests_registerer<test_object<Data>, test_group, MaxTestsInGroup>::register_test_method( *this );
		}

	/**
	* Registers test method under given number.
	*/
	void register_test_method( int n, testmethod tm )
		{
		_tests[ n ] = tm;
		}

	/**
	* Reset test position before first test.
	*/
	void rewind()
		{
		_currentTest = _tests.begin();
		}

	virtual bool has_next( void )
		{
		return ( _currentTest != _tests.end() );
		}

	virtual int next( void )
		{
		return ( _currentTest != _tests.end() ? _currentTest->first : -1 );
		}

	/**
	* Runs next test.
	*/
	test_result run_next()
		{
		if ( _currentTest == _tests.end() )
			{
			throw no_more_tests();
			}

		// find next user-specialized test
		safe_holder<object> obj;
		while ( _currentTest != _tests.end() )
			{
			try
				{
				return ( run_test( _currentTest ++, obj ) ) ;
				}
			catch ( const no_such_test& )
				{
				continue;
				}
			}

		throw no_more_tests();
		}

	/**
	* Runs one test by position.
	*/
	test_result run_test( int n )
		{
		// beyond tests is special case to discover upper limit
		if ( _tests.rbegin() == _tests.rend() )
			{
			throw beyond_last_test();
			}

		if ( _tests.rbegin()->first < n )
			{
			throw beyond_last_test();
			}

		// withing scope; check if given test exists
		_currentTest = _tests.find( n );
		if ( _currentTest == _tests.end() )
			{
			throw no_such_test();
			}

		safe_holder<object> obj;
		return ( run_test( _currentTest, obj ) ) ;
		}

	private:

	/**
	* VC allows only one exception handling type per function,
	* so I have to split the method.
	*
	* TODO: refactoring needed!
	*/
	test_result run_test( const tests_iterator& ti,
		safe_holder<object>&obj )
		{
		std::string current_test_name;
		char const* file = "";
		int line = -1;

		try
			{
			errno = 0;
			run_test( ti->second, obj, current_test_name );
			}
		catch ( const no_such_test& )
			{
			throw;
			}
		catch ( const warning& ex )
			{
			// test ok, but destructor failed
			if ( obj.get() )
				{
				current_test_name = obj->get_test_name();
				file = obj->get_test_file();
				}

			test_result tr( _name, ti->first, current_test_name, test_result::warn, ex, file, 1 );
			return ( tr ) ;
			}
		catch ( const failure& ex )
			{
			// test failed because of ensure() or similar method
			if ( obj.get() )
				{
				current_test_name = obj->get_test_name();
				}

			test_result tr( _name, ti->first, current_test_name, test_result::fail, ex );
			return ( tr ) ;
			}
		catch ( const bad_ctor& ex )
			{
			// test failed because test ctor failed; stop the whole group
			if ( obj.get() )
				{
				current_test_name = obj->get_test_name();
				file = obj->get_test_file();
				}

			test_result tr( _name, ti->first, current_test_name, test_result::ex_ctor, ex, file, 1 );
			return ( tr ) ;
			}
		catch ( const std::exception& ex )
			{
			// test failed with std::exception
			if ( obj.get() )
				{
				current_test_name = obj->get_test_name();
				file = obj->get_test_file();
				line = obj->get_test_line();
				}

			test_result tr( _name, ti->first, current_test_name, test_result::ex, ex, file, line );
			return ( tr ) ;
			}
		catch ( const yaal::hcore::HException& ex )
			{
			// test failed with yaal::hcore::HException
			if ( obj.get() )
				{
				current_test_name = obj->get_test_name();
				file = obj->get_test_file();
				line = obj->get_test_line();
				}

			test_result tr( _name, ti->first, current_test_name, test_result::ex, ex, file, line );
			return ( tr ) ;
			}
		catch ( ... )
			{
			// test failed with unknown exception
			if ( obj.get() )
				{
				current_test_name = obj->get_test_name();
				file = obj->get_test_file();
				line = obj->get_test_line();
				}
			test_result tr( _name, ti->first, current_test_name, test_result::ex, file, line );
			return ( tr ) ;
			}

		// test passed
		if ( obj.get() )
			{
			file = obj->get_test_file();
			line = obj->get_test_line();
			}
		test_result tr( _name, ti->first, current_test_name, test_result::ok, file, line );
		return ( tr ) ;
		}

	/**
	* Runs one.
	*/
	bool run_test( testmethod tm, safe_holder<object>&obj,
		std::string& current_test_name )
		{
		if ( obj.get() == 0 )
			{
			reset_holder_( obj );
			}

		obj->called_method_was_a_dummy_test_ = false;

		obj->set_test_tut( _name, _currentTest->first );
		( obj.get()->*tm )();

		if ( obj->called_method_was_a_dummy_test_ )
			{
			// do not call obj.release(); reuse object
			throw no_such_test();
			}

		current_test_name = obj->get_test_name();
		obj.permit_throw();
		obj.release();
		return ( true );
		}

	void reset_holder_( safe_holder<object>&obj )
		{
		try
			{
			obj.reset();
			}

		catch ( const std::exception& ex )
			{
			throw bad_ctor( ex.what() );
			}

		catch ( ... )
			{
			throw bad_ctor( "test constructor has generated an exception;"
				" group execution is terminated" );
			}
		}
	};

}

#endif


#ifndef TUT_H_GUARD
#define TUT_H_GUARD

#include <cerrno>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <typeinfo>

#include <yaal/hcore/base.hxx>
#include <yaal/hcore/hcall.hxx>
#include <yaal/tools/hworkflow.hxx>

#include "src/setup.hxx"

namespace tut
{
struct failure_info
	{
	int _line;
	char const* _file;
	std::string _msg;
	failure_info( int const& line, char const* file, std::string const& msg ) : _line( line ), _file( file ), _msg( msg ) {}
	failure_info( failure_info const& fi ) : _line( fi._line ), _file( fi._file ), _msg( fi._msg ) {}
	failure_info& operator = ( failure_info const& fi )
		{
		if ( &fi != this )
			{
			using std::swap;
			failure_info tmp( fi );
			swap( _line, tmp._line );
			swap( _file, tmp._file );
			swap( _msg, tmp._msg );
			}
		return ( *this );
		}
	};
}

#include "tut_exception.hpp"
#include "tut_result.hpp"
#include "tut_posix.hpp"
#include "tut_assert.hpp"
#include "tut_runner.hpp"

#define ENSURE( ... ) ensure_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_NOT( ... ) ensure_not_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_EQUALS( ... ) ensure_equals_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_DISTANCE( ... ) ensure_distance_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define ENSURE_ERRNO( ... ) ensure_errno_real( __FILE__, __LINE__, # __VA_ARGS__, __VA_ARGS__ )
#define FAIL( msg ) fail_real( __FILE__, __LINE__, ( msg ) )
#define TIME_CONSTRAINT( ms ) time_constraint M_CONCAT( time_constraint_at_, __LINE__ )( ( ms ), __FILE__, __LINE__ )

/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */
namespace tut
{

/**
 * Test object. Contains data test run upon and default test method
 * implementation. Inherited from Data to allow tests to
 * access test data as members.
 */
template<class Data>
class test_object : public Data, public test_object_posix
	{
	std::string _group;
	int _testNo;
	char const* _file;
	int _line;
	bool _slow;
public:

	/**
	* Default constructor
	*/
	test_object()
		: _group(), _testNo( 0 ), _file( "" ), _line( 0 ), _slow( false ),
		called_method_was_a_dummy_test_( false ), _currentTestName()
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
		if ( tress::setup._restartable && tl )
			tl->register_execution( _group, _testNo, _currentTestName, _file, _line );
		}

	std::string const& get_test_name( void ) const
		{
		return ( _currentTestName ) ;
		}

	std::string const& get_test_group( void ) const
		{
		return ( _group ) ;
		}

	char const* get_test_file( void )
		{
		return ( _file );
		}

	int get_test_line( void )
		{
		return ( _line );
		}

	virtual void time_constraint_exempt( void )
		{
		_slow = true;
		}

	void reset( void )
		{
		_slow = false;
		}

	bool is_slow( void )
		{
		return ( _slow );
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
private:
	test_object( test_object const& );
	test_object& operator = ( test_object const& );
	};

/**
 * Walks through test tree and stores address of each
 * test method in group. Instantiation stops at 0.
 */
template<class Test, class Group, int n>
struct tests_registerer
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
class test_group : public group_base, public test_group_posix
	{
	typedef test_object<Data> test_object_data;
	typedef void ( test_object_data::* testmethod )();
	typedef std::map<int, testmethod> tests_t;
	typedef typename tests_t::iterator tests_iterator;
	typedef typename tests_t::const_iterator tests_const_iterator;
	typedef typename tests_t::const_reverse_iterator
	tests_const_reverse_iterator;
	typedef typename tests_t::size_type size_type;
	typedef std::map<int, char const*> titles_t;

	std::string _name;
	titles_t _titles;
	int long _timeConstraint;
	tests_t _tests;
	tests_iterator _currentTest;
	int _passed;
	int _runned;

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
	test_group( const char* name )
		: _name( name ), _titles(), _timeConstraint( 0 ), _tests(), _currentTest(), _passed( 0 ), _runned( 0 )
		{
		// register itself
		runner.get().register_group( _name, this );

		// register all tests
		tests_registerer<object, test_group, MaxTestsInGroup>::register_test_method( *this );
		}

	/**
	* This constructor is used in self-test run only.
	*/
	test_group( const char* name, test_runner& another_runner )
		: _name( name ), _titles(), _timeConstraint( 0 ), _tests(), _currentTest(), _passed( 0 ), _runned( 0 )
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

	int register_test( int no_, char const* const title_ )
		{
		_titles[ no_ ] = title_;
		return ( 0 );
		}

	char const* get_test_title( int no_ ) const
		{
		titles_t::const_iterator it( _titles.find( no_ ) );
		return ( ( it != _titles.end() ) ? it->second : NULL );
		}

	virtual int get_real_test_count( void ) const
		{
		return ( static_cast<int>( _titles.size() ) );
		}

	virtual void set_time_constraint( int long timeConstraint_ )
		{
		_timeConstraint = timeConstraint_;
		}

	virtual std::string const& get_name() const
		{
		return ( _name );
		}

	virtual void set_name( std::string const& name_ )
		{
		_name = name_;
		}

	virtual run_stat_t get_stat() const
		{
		return ( std::make_pair( _passed, _runned ) );
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
				tests_iterator current_test = _currentTest ++;

				test_result tr( run_test( current_test, obj ) );

				return ( tr ) ;
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
		test_result tr = run_test( _currentTest, obj );

		return ( tr ) ;
		}

	/**
	 * VC allows only one exception handling type per function,
	 * so I have to split the method.
	 */
	test_result run_test( const tests_iterator& ti, safe_holder<object>& obj )
		{
		test_result tr( this, ti->first );

		char const* file = NULL;
		int line = -1;
		try
			{
			errno = 0;
			run_test( ti->second, obj );
			++ _passed;
			}
		catch ( const no_such_test& )
			{
			throw;
			}
		catch ( const rethrown& ex )
			{
			tr = ex._tr;
			tr._result = test_result::rethrown;
			}
		catch ( const failure& ex )
			{
			// test failed because of ensure() or similar method

			line = ex._line;
			file = ex._file;
			tr.set_meta( ex.result(), typeid( ex ).name(), ex.what() );
			}
		catch ( const tut_error& ex )
			{
			tr.set_meta( ex.result(), typeid( ex ).name(), ex.what() );
			}
		catch ( const std::exception& ex )
			{
			// test failed with std::exception

			tr.set_meta( test_result::ex, typeid( ex ).name(), ex.what() );
			}
		catch ( const yaal::hcore::HException& ex )
			{
			// test failed with yaal::hcore::HException

			tr.set_meta( test_result::ex, typeid( ex ).name(), ex.what() );
			}
		catch ( ... )
			{
			// test failed with unknown exception

			tr.set_meta( test_result::ex );
			}

		if ( obj.get() )
			tr.set_meta( obj->get_test_name(), file ? file : obj->get_test_file(), line > 0 ? line : obj->get_test_line() );

		// test passed

		return ( tr );
		}

	/**
	* Runs one.
	*/
	bool run_test( testmethod tm, safe_holder<object>&obj )
		{
		if ( obj.get() == 0 )
			{
			reset_holder_( obj );
			}

		obj->called_method_was_a_dummy_test_ = false;
		if ( _currentTest != _tests.end() )
			obj->set_test_tut( _name, _currentTest->first );

		/* Scope for time constraint. */
			{
			time_constraint timeConstraint( _timeConstraint );
			obj->reset();
			++ _runned;
			( obj.get()->*tm )();
			if ( obj->is_slow() )
				timeConstraint.disable();
			}

		if ( obj->called_method_was_a_dummy_test_ )
			{
			// do not call obj.release(); reuse object
			-- _runned;
			throw no_such_test();
			}

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
private:
	test_group( test_group const& );
	test_group& operator = ( test_group const& );
	};

}

#endif


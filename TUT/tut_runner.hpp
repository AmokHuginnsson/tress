#ifndef TUT_RUNNER_H_GUARD
#define TUT_RUNNER_H_GUARD

#include <string>
#include <vector>
#include "tut_exception.hpp"

namespace tut
{


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
	test_runner() : _groups(), _defaultCallback(), _callback( &_defaultCallback ), _tutListener( NULL )
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

		if ( _groups.find( name ) != _groups.end() )
			{
			std::string msg( "attempt to add already existent group " + name );

			// this exception terminates application so we use cerr also
			// TODO: should this message appear in stream?
			std::cerr << msg << std::endl;
			throw tut_error( msg );
			}

		_groups.insert( std::make_pair( name, gr ) );
		}

	/**
	* Stores callback object.
	*/
	void set_callback( callback* cb )
		{
		_callback = cb == 0 ? &_defaultCallback : cb;
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
		const_iterator i = _groups.begin();
		const_iterator e = _groups.end();

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
			const_iterator e = _groups.end();
			yaal::tools::HWorkFlow w( tress::setup.f_iJobs );
			for ( const_iterator i = _groups.begin(); i != e; ++ i )
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
				const_iterator i = _groups.find( *k );
				if ( i == _groups.end() )
					{
					test_result tr( *k, 0 );
					tr.set_meta( test_result::setup, "", "no such group" );
					tr.set_meta( tress::setup.f_oTestGroupListFilePath.raw(), "-", static_cast<int>( std::distance( group_names.begin(), k ) ) );
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
			const_iterator e = _groups.end();
			for ( const_iterator i = _groups.begin(); i != e; ++ i )
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

		const_iterator i = _groups.find( group_name );
		if ( i == _groups.end() )
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
	typedef yaal::hcore::HCall<test_runner const&, group_call_t, const_iterator> group_runner_t;
	groups _groups;

	callback _defaultCallback;
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

		for ( ;; )
			{
			if ( i->second->has_next() )
				_callback->test_started( i->second->next() );

			test_result tr = i->second->run_next();
			_callback->test_completed( tr );

			if ( tr._result == test_result::ex_ctor )
				{
				throw no_more_tests();
				}
			}
		}
private:
	test_runner( test_runner const& );
	test_runner& operator = ( test_runner const& );
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

}

#endif


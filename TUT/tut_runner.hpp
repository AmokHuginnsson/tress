#ifndef TUT_RUNNER_H_GUARD
#define TUT_RUNNER_H_GUARD

#include <string>
#include <vector>
#include <map>

#include <yaal/tools/hworkflow.hxx>

#include "tut_exception.hpp"

#include "src/setup.hxx"


namespace tut {

/**
 * Interface.
 * Test group operations.
 */
struct group_base {
	typedef std::pair<int, int> run_stat_t;
	typedef std::map<int, char const*> titles_t;
	virtual ~group_base()
		{}

	// execute tests iteratively
	virtual void rewind() = 0;
	virtual test_result run_next() = 0;
	virtual bool has_next() = 0;
	virtual int next() = 0;

	// execute one test
	virtual test_result run_test( int n ) = 0;
	virtual int get_real_test_count( void ) const = 0;
	virtual char const* get_test_title( int ) const = 0;
	virtual titles_t const& get_test_titles( void ) const = 0;
	virtual void set_time_constraint( int long ) = 0;
	virtual std::string const& get_name() const = 0;
	virtual void set_name( std::string const& ) = 0;
	virtual run_stat_t get_stat() const = 0;
};

class test_runner;

/**
 * Test runner callback interface.
 * Can be implemented by caller to update
 * tests results in real-time. User can implement
 * any of callback methods, and leave unused
 * in default implementation.
 */
struct callback {
	/**
	* Virtual destructor is a must for subclassed types.
	*/
	virtual ~callback()
		{}

	/**
	* Called when new test run started.
	*/
	virtual void run_started( int, int ) = 0;

	/**
	* Called when a group started
	* @param name Name of the group
	*/
	virtual void group_started( const std::string& /*name */, int /* total test count for group */ ) = 0;

	/**
	* Called when a test finished.
	* @param tr Test results.
	*/
	virtual void test_completed( const test_result& /*tr */ ) = 0;

	/**
	* Called when a group is completed
	* @param name Name of the group
	*/
	virtual void group_completed( const std::string& /*name */ ) = 0;

	/**
	* Called when a test is about to start.
	*/
	virtual void test_started( char const* const, int /*n */, char const* const ) = 0;

	/**
	* Called when all tests in run completed.
	*/
	virtual void run_completed() = 0;

	virtual bool all_ok( void ) const = 0;

	virtual int fail_count( void ) const = 0;

	virtual void set_test_runner( test_runner* ) {}
};

/**
 * Typedef for runner::list_groups()
 */
typedef std::list<std::string> groupnames;

/**
 * Listener of tut events.
 */
class tut_listener {
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
class test_runner {
public:

	typedef std::map<std::string, group_base*> groups;
	typedef groups::iterator iterator;
	typedef groups::const_iterator const_iterator;

	typedef std::vector<int> test_numbers_t;
	typedef std::pair<std::string, test_numbers_t> test_set_t;
	typedef std::list<test_set_t> test_sets_t;

	/**
	* Constructor
	*/
	test_runner( void )
		: _groups(), _callback( NULL ), _tutListener( NULL )
		{}

	/**
	* Stores another group for getting by name.
	*/
	void register_group( const std::string& name, group_base* gr ) {
		if ( gr == 0 )
			throw std::invalid_argument( "group shall be non-null" );

		if ( _groups.find( name ) != _groups.end() ) {
			std::string msg( "attempt to add already existent group " + name );
			throw tut_error( msg );
		}

		_groups.insert( std::make_pair( name, gr ) );
	}

	/**
	* Stores callback object.
	*/
	void set_callback( callback* cb ) {
		_callback = cb;
		_callback->set_test_runner( this );
	}

	/**
	* Stores callback object.
	*/
	void set_listener( tut_listener* tl ) {
		_tutListener = tl;
	}
	
	tut_listener* get_listener( void ) {
		return ( _tutListener );
	}

	/**
	* Returns callback object.
	*/
	callback& get_callback() const {
		return ( *_callback ) ;
	}

	/**
	* Returns list of known test groups.
	*/
	const groupnames list_groups() const {
		groupnames ret;
		const_iterator i = _groups.begin();
		const_iterator e = _groups.end();

		while ( i != e ) {
			ret.push_back( i->first );
			++ i;
		}

		return ( ret ) ;
	}

	groups const& get_groups( void ) const {
		return ( _groups );
	}

	group_base* get_group( std::string const& name_ ) {
		iterator it( _groups.find( name_ ) );
		return ( it != _groups.end() ? it->second : NULL );
	}

	void set_time_constraint( int long timeConstraint_ ) {
		for ( const_iterator i( _groups.begin() ), e( _groups.end() ); i != e; ++ i )
			i->second->set_time_constraint( timeConstraint_ );
	}

	/**
	* Runs all tests in all groups.
	* @param callback Callback object if exists; null otherwise
	*/
	void run_tests() const {
 		/* scope for workflow */ {
			yaal::tools::HWorkFlow::ptr_t w( tress::setup._jobs > 0
					? yaal::hcore::make_pointer<yaal::tools::HWorkFlow>( tress::setup._jobs )
					: yaal::tools::HWorkFlow::ptr_t() );
			int total( 0 );
			for ( const_iterator i( _groups.begin() ), e( _groups.end() ); ! yaal::_isKilled_ && ( i != e ); ++ i )
				total += i->second->get_real_test_count();
			_callback->run_started( static_cast<int>( _groups.size() ), total );
			for ( const_iterator i( _groups.begin() ), e( _groups.end() ); ! yaal::_isKilled_ && ( i != e ); ++ i ) {
				if ( !! w )
					w->push_task( yaal::hcore::call( &test_runner::run_group, this, i ) );
				else
					run_group( i );
			}
		}
		_callback->run_completed();
	}

	/**
	* Runs all tests in specified groups.
	*/
	void run_tests( const std::list<std::string>& group_names ) const {
 		/* scope for workflow */ {
			yaal::tools::HWorkFlow::ptr_t w( tress::setup._jobs > 0
					? yaal::hcore::make_pointer<yaal::tools::HWorkFlow>( tress::setup._jobs )
					: yaal::tools::HWorkFlow::ptr_t() );
			int total( 0 );
			for ( std::list<std::string>::const_iterator k( group_names.begin() ), e( group_names.end() );
					! yaal::_isKilled_ && ( k != e ); ++ k ) {
				const_iterator i = _groups.find( *k );
				if ( i == _groups.end() )
					++ total;
				else
					total += i->second->get_real_test_count();
			}
			_callback->run_started( static_cast<int>( group_names.size() ), total );
			for ( std::list<std::string>::const_iterator k( group_names.begin() ), e( group_names.end() );
					! yaal::_isKilled_ && ( k != e ); ++ k ) {
				const_iterator i = _groups.find( *k );
				if ( i == _groups.end() ) {
					test_result tr;
					tr.set_meta( test_result::setup, "", *k );
					tr.set_location( tress::setup._testGroupListFilePath.raw(), "-", static_cast<int>( std::distance( group_names.begin(), k ) ) );
					_callback->test_completed( tr );
				} else {
					if ( !! w )
						w->push_task( yaal::hcore::call( &test_runner::run_group, this, i ) );
					else
						run_group( i );
				}
			}
		}
		_callback->run_completed();
	}

	/**
	* Runs specific tests from specified groups.
	*/
	void run_tests( test_sets_t const& testSets_ ) const {
 		/* scope for workflow */ {
			yaal::tools::HWorkFlow::ptr_t w( tress::setup._jobs > 0
					? yaal::hcore::make_pointer<yaal::tools::HWorkFlow>( tress::setup._jobs )
					: yaal::tools::HWorkFlow::ptr_t() );
			int total( 0 );
			for ( test_sets_t::const_iterator k( testSets_.begin() ), e( testSets_.end() );
					! yaal::_isKilled_ && ( k != e ); ++ k ) {
				const_iterator i = _groups.find( k->first );
				if ( i == _groups.end() )
					++ total;
				else {
					int selected( static_cast<int>( k->second.size() ) );
					total += selected ? selected : i->second->get_real_test_count();
				}
			}
			_callback->run_started( static_cast<int>( testSets_.size() ), total );
			for ( test_sets_t::const_iterator k = testSets_.begin();
					! yaal::_isKilled_ && ( k != testSets_.end() ); ++ k ) {
				const_iterator i = _groups.find( k->first );
				if ( i == _groups.end() ) {
					test_result tr;
					tr.set_meta( test_result::setup, "", k->first );
					tr.set_location( tress::setup._testGroupListFilePath.raw(), "-", static_cast<int>( std::distance( testSets_.begin(), k ) ) );
					_callback->test_completed( tr );
				} else {
					if ( !! w )
						w->push_task( yaal::hcore::call( &test_runner::run_in_group, this, i, k->second ) );
					else
						run_in_group( i, k->second );
				}
			}
		}
		_callback->run_completed();
	}

	/**
	* Runs all tests in all groups that are matching pattern.
	* @param callback Callback object if exists; null otherwise
	*/
	void run_pattern_tests( std::string const& pattern ) const {
		size_t at( pattern.find( "@" ) );
		if ( at != std::string::npos ) {
			std::string groupNamePattern( pattern.substr( 0, at ) );
			std::string testNamePattern( pattern.substr( at + 1 ) );
			test_sets_t ts;
			for ( const_iterator i = _groups.begin(), e( _groups.end() ); i != e; ++ i ) {
				if ( groupNamePattern.empty() || ( i->first.find( groupNamePattern ) != std::string::npos ) ) {
					test_numbers_t tn;
					group_base::titles_t const& tt( i->second->get_test_titles() );
					for ( group_base::titles_t::const_iterator t( tt.begin() ), te( tt.end() ); t != te; ++ t ) {
						if ( testNamePattern.empty() || ( std::string( t->second ).find( testNamePattern ) != std::string::npos ) )
							tn.push_back( t->first );
					}
					if ( ! tn.empty() )
						ts.push_back( make_pair( i->first, tn ) );
				}
			}
			run_tests( ts );
		} else {
			groupnames gn;
			for ( const_iterator i = _groups.begin(), e( _groups.end() ); i != e; ++ i ) {
				if ( i->first.find( pattern ) != std::string::npos ) {
					gn.push_back( i->first );
				}
			}
			run_tests( gn );
		}
	}

	/**
	* Runs one test in specified group.
	*/
	test_result run_test( const std::string& group_name, int n ) const {

		const_iterator i = _groups.find( group_name );
		if ( i == _groups.end() ) {
			_callback->run_started( 1, 1 );
			_callback->run_completed();
			throw no_such_group( group_name );
		}

		_callback->run_started( 1, 1 );
		_callback->group_started( group_name, 1 );
		_callback->test_started( group_name.c_str(), n, i->second->get_test_title( n ) );

		try {
			test_result tr = i->second->run_test( n );
			_callback->test_completed( tr );
			_callback->group_completed( group_name );
			_callback->run_completed();
			return ( tr );
		} catch ( const beyond_last_test& ) {
			_callback->group_completed( group_name );
			_callback->run_completed();
			throw;
		} catch ( const no_such_test& ) {
			_callback->group_completed( group_name );
			_callback->run_completed();
			throw;
		}
	}

protected:
	groups _groups;

	callback* _callback;
	tut_listener* _tutListener;

private:

	void run_group( const_iterator i ) const {
		yaal::hcore::HThread::set_name( i->first.c_str() + std::max( 0, static_cast<int>( i->first.length() - 15 ) ) );
		_callback->group_started( i->first, i->second->get_real_test_count() );
		try {
			run_all_tests_in_group_( i );
		} catch ( const no_more_tests& ) {
			_callback->group_completed( i->first );
		}
	}

	void run_in_group( const_iterator i, test_numbers_t const& testNumbers_ ) const {
		yaal::hcore::HThread::set_name( i->first.c_str() + std::max( 0, static_cast<int>( i->first.length() - 15 ) ) );
		int selected( static_cast<int>( testNumbers_.size() ) );
		_callback->group_started( i->first, selected ? selected : i->second->get_real_test_count() );
		if ( testNumbers_.empty() ) {
			try {
				run_all_tests_in_group_( i );
			} catch ( const no_more_tests& ) {
				_callback->group_completed( i->first );
			}
		} else {
			for ( test_numbers_t::const_iterator no( testNumbers_.begin() ), noEnd( testNumbers_.end() ); no != noEnd; ++ no ) {
				_callback->test_started( i->first.c_str(), *no, i->second->get_test_title( *no ) );

				try {
					test_result tr = i->second->run_test( *no );
					_callback->test_completed( tr );
				} catch ( const beyond_last_test& ) {
					break;
				} catch ( const no_such_test& ) {
					test_result tr( i->second, *no );
					tr.set_meta( test_result::setup_test_number, "", "no such test number" );
					tr.set_location( "no such test" );
					_callback->test_completed( tr );
				}
			}
			_callback->group_completed( i->first );
		}
	}

	void run_all_tests_in_group_( const_iterator i ) const {
		i->second->rewind();
		if ( i != i )
			return;

		for ( ; ! yaal::_isKilled_ ; ) {
			if ( i->second->has_next() ) {
				int no( i->second->next() );
				_callback->test_started( i->first.c_str(), no, i->second->get_test_title( no ) );
			}

			test_result tr = i->second->run_next();
			_callback->test_completed( tr );

			if ( tr._result == test_result::ex_ctor ) {
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
class test_runner_singleton {
	public:

	static test_runner& get() {
		static test_runner tr;

		return ( tr ) ;
	}
};

extern test_runner_singleton runner;

}

#endif


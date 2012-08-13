#ifndef TUT_REPORTER_GOOGLE
#define TUT_REPORTER_GOOGLE

#include <set>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "tut.hpp"

#ifdef __MSVCXX__
#include <windows.h>
#include <yaal/cleanup.hxx>
#endif /* __MSVCXX__ */


/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */
namespace tut {

/**
 * Cute TUT callback handler.
 */
template<typename stream_t = std::ostream>
class reporter_google : public tut::callback {
	typedef stream_t stream_type;
	std::ostream& _os;
	yaal::hcore::HMutex _mutex;
	stream_type& _ls;
	int _run;
	test_runner* _testRunner;
	typedef std::vector<tut::test_result> not_passed_list_t;
	typedef std::set<std::string> group_names_t;
	not_passed_list_t _notPassed;
	group_names_t _groupNames;
public:
	reporter_google()
		: _os( std::cout ), _mutex(), _ls( std::cerr ),
		_run( 0 ), _testRunner( NULL ), _notPassed(), _groupNames() {
		clear();
	}

	reporter_google( std::ostream& out )
		: _os( out ), _mutex(), _ls( &out == &std::cout ? std::cerr : std::cout ),
		_run( 0 ), _testRunner( NULL ), _notPassed(), _groupNames() {
	}

	reporter_google( std::ostream& out, stream_type& logger )
		: _os( out ), _mutex(), _ls( logger ),
		_run( 0 ), _testRunner( NULL ), _notPassed(), _groupNames() {
	}

	virtual void set_test_runner( test_runner* testRunner_ ) {
		_testRunner = testRunner_;
	}

	virtual void run_started( int groupCount_, int testCount_ ) {
		clear();
		_os << "Running main() from gtest_main.cc\n"
			<< "[==========] Running " << testCount_ << " tests from " << groupCount_ << " test cases.\n"
			<< "[----------] Global test environment set-up.\n";
	}

	virtual void group_started( std::string const& name, int count_ ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: group: [" << name << "]" << std::endl;
		_os << "[----------] " << count_ << " tests from " << name << std::endl;
	}

	void group_completed( std::string const& name_ ) {
		group_base* g( _testRunner->get_group( name_ ) );
		_os << "[----------] " << ( g ? g->get_real_test_count() : 0 ) << " tests from " << name_ << " (0 ms total)\n" << std::endl;
	}

	virtual void test_started( char const* const group_, int n, char const* const title_ ) {
		if ( group_ )
			_groupNames.insert( group_ );
		if ( title_ ) {
			yaal::hcore::HLock l( _mutex );
			using std::operator <<;
			_ls << "TUT: module::test<" << n << "> " << title_ << std::endl;
			_os << "[ RUN      ] " << group_ << "." << title_ << std::endl;
		}
	}

	virtual void test_completed( const tut::test_result& tr_ ) {
		yaal::hcore::HLock l( _mutex );
		++ _run;
		if ( tr_._result == tut::test_result::ok )
			_os << "[       OK ] " << tr_._group->get_name() << "." << tr_._name << " (0 ms)" << std::endl;
		else {
			_notPassed.push_back( tr_ );
			std::string file( tr_._file );
			size_t prjRootIdx( file.find( PACKAGE_NAME ) );
			if ( prjRootIdx != std::string::npos ) {
				file.erase( 0, prjRootIdx + sizeof ( PACKAGE_NAME ) );
				file.insert( 0, "./" );
			}
			std::stringstream ss;
			if ( tr_._line >= 0 )
				ss << file << ":" << tr_._line << ": Failure\n";
			if ( tr_._result == tut::test_result::ex ) {
				ss <<  "Unexpected exception: " << tr_._exceptionTypeId << ": ";
			} else if ( tr_._result == tut::test_result::term )
				ss << "Segvfault: ";
			ss << tr_._message << std::endl;
			_os << ss.str();
			_os << "[  FAILED  ] " << tr_._group->get_name() << "." << tr_._name << " (0 ms)" << std::endl;
		}
	}

	virtual void run_completed( void ) {
		_os << "[----------] Global test environment tear-down\n"
			<< "[==========] " << _run << " tests from " << _groupNames.size() << " test cases ran. (0 ms total)\n"
			<< "[  PASSED  ] " << ( _run - _notPassed.size() ) << " tests." << std::endl;
		if ( !_notPassed.empty() ) {
			_os << "[  FAILED  ] " << _notPassed.size() << " test" << ( _notPassed.size() > 1 ? "s" : "" ) << ", listed below:\n";
			for ( not_passed_list_t::const_iterator it( _notPassed.begin() ), end( _notPassed.end() ); it != end; ++ it )
				_os << "[  FAILED  ] " << it->_group->get_name() << "." << it->_name << std::endl;
			_os << "\n " << _notPassed.size() << " FAILED TESTS" << std::endl;
		}
	}

	virtual bool all_ok( void ) const {
		return ( !_notPassed.empty() ) ;
	}

	virtual int fail_count( void ) const {
		return ( static_cast<int>( _notPassed.size() ) );
	}

private:
	reporter_google( reporter_google const& );
	reporter_google& operator = ( reporter_google const& );
	void clear() {
		_notPassed.clear();
	}
};

}

#endif

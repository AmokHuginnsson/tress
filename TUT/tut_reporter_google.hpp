#ifndef TUT_REPORTER_GOOGLE
#define TUT_REPORTER_GOOGLE

#include <set>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "tut.hpp"
#include "tut_terminal.hpp"

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
		: _os( std::cout )
		, _mutex()
		, _ls( std::cerr )
		, _run( 0 )
		, _testRunner( nullptr )
		, _notPassed()
		, _groupNames() {
		clear();
	}

	reporter_google( std::ostream& out )
		: _os( out )
		, _mutex()
		, _ls( &out == &std::cout ? std::cerr : std::cout )
		, _run( 0 )
		, _testRunner( nullptr )
		, _notPassed()
		, _groupNames() {
	}

	reporter_google( std::ostream& out, stream_type& logger )
		: _os( out )
		, _mutex()
		, _ls( logger )
		, _run( 0 )
		, _testRunner( nullptr )
		, _notPassed()
		, _groupNames() {
	}

	virtual void set_test_runner( test_runner* testRunner_ ) {
		_testRunner = testRunner_;
	}

	virtual void run_started( int groupCount_, int testCount_ ) {
		clear();
		_os << "Running main() from gtest_main.cc\n"
			<< yaal::ansi::green << "[==========]"
			<< yaal::ansi::reset << " Running " << testCount_ << " tests from " << groupCount_ << " test cases.\n"
			<< yaal::ansi::green << "[----------]"
			<< yaal::ansi::reset << " Global test environment set-up.\n";
	}

	virtual void group_started( std::string const& name, int count_ ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: group: [" << name << "]" << std::endl;
		_os << yaal::ansi::green << "[----------] " << yaal::ansi::reset << count_ << " tests from " << escape( name ) << std::endl;
	}

	void group_completed( group_base const* group_ ) {
		_os << yaal::ansi::green << "[----------] "
			<< yaal::ansi::reset << group_->get_real_test_count() << " tests from " << escape( group_->get_name() ) << " (0 ms total)\n" << std::endl;
	}

	virtual void test_started( std::string const& group_, int n, std::string const& title_ ) {
		yaal::hcore::HLock l( _mutex );
		if ( ! group_.empty() ) {
			_groupNames.insert( group_ );
		}
		using std::operator <<;
		_ls << "TUT: module::test<" << n << "> " << title_ << std::endl;
		_os << yaal::ansi::green << "[ RUN      ] " << yaal::ansi::reset << escape( group_ ) << ".<" << n << "> " << escape( title_ ) << std::endl;
	}

	virtual void test_completed( const tut::test_result& tr_ ) {
		yaal::hcore::HLock l( _mutex );
		++ _run;
		if ( tr_._result == tut::test_result::ok ) {
			_os << yaal::ansi::green
				<< "[       OK ] " << yaal::ansi::reset << escape( tr_._group->get_name() )
				<< ".<" << tr_._testNo << "> " << escape( tr_._name )
				<< " (" << tr_._time << " ms)" << std::endl;
		} else {
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
			_os << "[  FAILED  ] " << ( tr_._group ? escape( tr_._group->get_name() ) : "no such group" )
				<< ".<" << tr_._testNo << "> " << escape( tr_._name )
				<< " (" << tr_._time << " ms)" << std::endl;
		}
	}

	virtual void run_completed( void ) {
		_os << yaal::ansi::green << "[----------]"
			<< yaal::ansi::reset << " Global test environment tear-down\n"
			<< yaal::ansi::green << "[==========] "
			<< yaal::ansi::reset << _run << " tests from " << _groupNames.size() << " test cases ran. (0 ms total)\n"
			<< yaal::ansi::green << "[  PASSED  ] "
			<< yaal::ansi::reset << ( _run - static_cast<int>( _notPassed.size() ) ) << " tests." << std::endl;
		if ( !_notPassed.empty() ) {
			_os << yaal::ansi::red << "[  FAILED  ] "
				<< yaal::ansi::reset << _notPassed.size()
				<< " test" << ( _notPassed.size() > 1 ? "s" : "" ) << ", listed below:\n";
			for ( not_passed_list_t::const_iterator it( _notPassed.begin() ), end( _notPassed.end() ); it != end; ++ it ) {
				_os << yaal::ansi::red << "[  FAILED  ] "
					<< yaal::ansi::reset << ( it->_group ? it->_group->get_name() : "no such group" ) << "." << it->_name << std::endl;
			}
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
	static std::string escape( const std::string& text ) {
		std::string out;

		for ( unsigned int i = 0; i < text.length(); ++ i ) {
			char c = text[ i ];
			switch ( c ) {
				case '[':
				case ']':
				case '.':
				case ',':
				case '(':
				case ')':
					out += "_";
				break;
				default:
					out += c;
			}
		}
		return ( out );
	}
};

}

#endif

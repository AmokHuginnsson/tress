#ifndef TUT_REPORTER_BOOST
#define TUT_REPORTER_BOOST

#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "tut.hpp"
#include "tut_reporter_cppunit.hpp"

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
class reporter_boost : public tut::callback {
	typedef stream_t stream_type;
	std::ostream& _os;
	yaal::hcore::HMutex _mutex;
	stream_type& _ls;
	int _failed;
public:
	reporter_boost()
		: _os( std::cout ), _mutex(), _ls( std::cerr ), _failed( 0 ) {
		clear();
	}

	reporter_boost( std::ostream& out )
		: _os( out ), _mutex(), _ls( &out == &std::cout ? std::cerr : std::cout ), _failed( 0 ) {
	}

	reporter_boost( std::ostream& out, stream_type& logger )
		: _os( out ), _mutex(), _ls( logger ), _failed( 0 ) {
	}

	virtual void run_started( int, int ) {
		clear();
		_os << "<TestLog>\n<TestSuite name=\"Master Suite\">" << std::endl;
	}

	virtual void group_started( std::string const& name, int ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: group: [" << name << "]" << std::endl;
		_os << "\t<TestSuite name=\"" << name << "\">" << std::endl;
	}

	void group_completed( group_base const* ) {
		_os << "\t</TestSuite>" << std::endl;
	}

	virtual void test_started( char const*, int n, char const* title_, bool ) {
		if ( title_ ) {
			yaal::hcore::HLock l( _mutex );
			using std::operator <<;
			_ls << "TUT: module::test<" << n << "> " << title_ << std::endl;
			_os << "\t\t<TestCase name=\"&lt;" << n << "&gt; " << reporter_cppunit::encode( title_ ) << "\">" << std::endl;
		}
	}

	virtual void test_completed( const tut::test_result& tr_ ) {
		yaal::hcore::HLock l( _mutex );
		if ( tr_._result != tut::test_result::ok ) {
			++ _failed;
			std::string file( tr_._file );
			size_t prjRootIdx( file.find( PACKAGE_NAME ) );
			if ( prjRootIdx != std::string::npos ) {
				file.erase( 0, prjRootIdx + sizeof ( PACKAGE_NAME ) );
				file.insert( 0, "./" );
			}
			std::stringstream ss;
			if ( tr_._result == tut::test_result::fail ) {
				ss << "\t\t\t<FatalError file=\"" << file << "\" line=\"" << tr_._line << "\">" << std::endl;
				ss << "\t\t\t\t<![CDATA[critical check " << tr_._message << "]]>\n\t\t\t</FatalError>" << std::endl;
			} else if ( tr_._result == tut::test_result::ex ) {
				if ( tr_._line >= 0 ) {
					ss << "\t\t\t<Exception file=\"" << file << "\" line=\"" << tr_._line << "\">\n"
						<< "\t\t\t\t<![CDATA[" << tr_._exceptionTypeId << ": " << tr_._message << "]]>\n"
						<< "\t\t\t\t<LastCheckpoint file=\"" << file << "\" line=\"" << tr_._line << "\">\n"
						<< "\t\t\t\t\t<![CDATA[]]>\n"
						<< "\t\t\t\t</LastCheckpoint>\n"
						<< "\t\t\t</Exception>" << std::endl;
				}
			} else if ( tr_._result == tut::test_result::term )
				ss << "#segv " << file << ":" << tr_._line << " ";
			_os << ss.str();
		}
		_os << "\t\t\t<TestingTime>" << ( tr_._time * 1000 ) << "</TestingTime>" << std::endl;
		_os << "\t\t</TestCase>" << std::endl;
	}

	virtual void run_completed( void ) {
		_os << "</TestSuite>\n</TestLog>" << std::endl;
	}

	virtual bool all_ok( void ) const {
		return ( _failed == 0 ) ;
	}

	virtual int fail_count( void ) const {
		return ( _failed );
	}

private:

	void clear() {
		_failed = 0;
	}
};

}

#endif

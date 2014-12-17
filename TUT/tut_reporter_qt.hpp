#ifndef TUT_REPORTER_QT
#define TUT_REPORTER_QT

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
class reporter_qt : public tut::callback {
	typedef stream_t stream_type;
	std::ostream& _os;
	yaal::hcore::HMutex _mutex;
	stream_type& _ls;
	int _failed;
public:
	reporter_qt()
		: _os( std::cout ), _mutex(), _ls( std::cerr ), _failed( 0 ) {
		clear();
	}

	reporter_qt( std::ostream& out )
		: _os( out ), _mutex(), _ls( &out == &std::cout ? std::cerr : std::cout ), _failed( 0 ) {
	}

	reporter_qt( std::ostream& out, stream_type& logger )
		: _os( out ), _mutex(), _ls( logger ), _failed( 0 ) {
	}

	virtual void run_started( int, int ) {
		clear();
		_os <<
			"<?xml version=\"1.0\" encoding=\"ISO-8859-2\"?>\n"
			"<TestCase name=\"Master Suite\">" << std::endl;
	}

	virtual void group_started( std::string const& name, int ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: group: [" << name << "]" << std::endl;
		_os << "\t<TestCase name=\"" << name << "\">" << std::endl;
	}

	void group_completed( group_base const* ) {
		_os << "\t</TestCase>" << std::endl;
	}

	virtual void test_started( std::string const&, int n, std::string const& title_ ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: module::test<" << n << "> " << title_ << std::endl;
		_os << "\t\t<TestFunction name=\"&lt;" << n << "&gt; " << reporter_cppunit::encode( title_ ) << "\">" << std::endl;
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
				std::string msg;
				size_t expected( tr_._message.find( "expected [" ) );
				if ( expected != std::string::npos ) {
					size_t actual( tr_._message.find( "] actual [", expected ) );
					if ( actual != std::string::npos ) {
						size_t expectedEnd( actual );
						actual += 10;
						msg = tr_._message.substr( 0, expected );
						msg += "\n Actual (";
						msg += tr_._message.substr( actual, tr_._message.length() - actual - 1 );
						msg += "): ";
						msg += tr_._message.substr( actual, tr_._message.length() - actual - 1 );
						msg += "\n Expected (";
						expected += 10;
						msg += tr_._message.substr( expected, expectedEnd - expected );
						msg += "): ";
						msg += tr_._message.substr( expected, expectedEnd - expected );
					} else
						msg = tr_._message;
				} else
					msg = tr_._message;
				ss << "\t\t\t<Incident type=\"fail\" file=\"" << file << "\" line=\"" << tr_._line << "\">" << std::endl;
				ss << "\t\t\t\t<Description><![CDATA[" << msg << "]]></Description>\n\t\t\t</Incident>" << std::endl;
			} else if ( tr_._result == tut::test_result::ex ) {
				if ( tr_._line >= 0 ) {
					ss << "\t\t\t<Incident type=\"fail\" file=\"" << file << "\" line=\"" << tr_._line << "\">\n"
						<< "\t\t\t\t<Description><![CDATA[Caught unhandled exception: " << tr_._exceptionTypeId << ": " << tr_._message
						<< "]]></Description>\n\t\t\t</Incident>" << std::endl;
				}
			}
			_os << ss.str();
		} else
			_os << "\t\t\t<Incident type=\"pass\" file=\"\" line=\"0\" />\n";
		_os << "\t\t</TestFunction>" << std::endl;
	}

	virtual void run_completed( void ) {
		_os << "</TestCase>" << std::endl;
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

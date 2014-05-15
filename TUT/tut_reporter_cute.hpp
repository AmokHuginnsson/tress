#ifndef TUT_REPORTER_CUTE
#define TUT_REPORTER_CUTE

#include <cstdlib>
#include <algorithm>
#include <iostream>

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
class reporter_cute : public tut::callback {
	typedef stream_t stream_type;
	std::ostream& _os;
	yaal::hcore::HMutex _mutex;
	stream_type& _ls;
	int _failed;
public:
	reporter_cute()
		: _os( std::cout ), _mutex(), _ls( std::cerr ), _failed( 0 ) {
		clear();
	}

	reporter_cute( std::ostream& out )
		: _os( out ), _mutex(), _ls( &out == &std::cout ? std::cerr : std::cout ), _failed( 0 ) {
	}

	reporter_cute( std::ostream& out, stream_type& logger )
		: _os( out ), _mutex(), _ls( logger ), _failed( 0 ) {
	}

	virtual void run_started( int, int ) {
		clear();
	}

	virtual void group_started( std::string const& name, int count_ ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: group: [" << name << "]" << std::endl;
		_os << "#beginning " << name << " " << count_ << std::endl;
	}

	void group_completed( group_base const* group_ ) {
		_os << "#ending " << group_->get_name() << std::endl;
	}

	virtual void test_started( char const*, int n, char const* title_, bool ) {
		if ( title_ ) {
			yaal::hcore::HLock l( _mutex );
			using std::operator <<;
			_ls << "TUT: module::test<" << n << "> " << title_ << std::endl;
			_os << "#starting " << title_ << std::endl;
		}
	}

	virtual void test_completed( const tut::test_result& tr_ ) {
		yaal::hcore::HLock l( _mutex );
		if ( tr_._result == tut::test_result::ok )
			_os << "#success " << tr_._name << " OK" << std::endl;
		else {
			++ _failed;
			std::string file( tr_._file );
			size_t prjRootIdx( file.find( PACKAGE_NAME ) );
			if ( prjRootIdx != std::string::npos ) {
				file.erase( 0, prjRootIdx + sizeof ( PACKAGE_NAME ) );
				file.insert( 0, "./" );
			}
			std::stringstream ss;
			if ( tr_._result == tut::test_result::fail )
				ss << "#failure " << tr_._name << ( ! tr_._name.empty() ? " " : "" ) << file << ":" << tr_._line << " ";
			else if ( tr_._result == tut::test_result::ex ) {
				if ( tr_._line >= 0 )
					ss <<  "#exception " << tr_._name << ( ! tr_._name.empty() ? " " : "" ) << file << ":" << tr_._line << " ";
			} else if ( tr_._result == tut::test_result::term )
				ss << "#segv " << file << ":" << tr_._line << " ";
			ss << tr_._message << std::endl;
			_os << ss.str();
		}
	}

	virtual void run_completed( void ) {
		_os << std::endl;
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

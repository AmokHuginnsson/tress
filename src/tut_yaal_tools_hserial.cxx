/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hserial.hxx>
#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/tools.hxx>
#include <yaal/tools/hpipedchild.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hserial : public simple_mock<tut_yaal_tools_hserial> {
	typedef simple_mock<tut_yaal_tools_hserial> base_type;
	virtual ~tut_yaal_tools_hserial(){}
	HPipedChild _socat;
	HString _path;
	tut_yaal_tools_hserial( void )
		: _socat()
		, _path() {
		try {
			_socat.spawn( "/usr/bin/socat", { "-d", "-d", "pty,raw,echo=0", "pty,raw,echo=0" } );
			_socat.err().read_until( _path );
			int long pathStart( _path.find_last( ' '_ycp ) );
			M_ENSURE( pathStart != HString::npos );
			_path.shift_left( pathStart + 1 );
		} catch ( HPipedChildException const& e ) {
			hcore::log << e.what() << endl;
		}
	}
};

#ifdef __HOST_OS_TYPE_CYGWIN__
#	define TUT_SUITE_PREFIX "000"
#else
#	define TUT_SUITE_PREFIX ""
#endif

TUT_TEST_GROUP( tut_yaal_tools_hserial, TUT_SUITE_PREFIX "yaal::tools::HSerial" );

#ifndef __HOST_OS_TYPE_CYGWIN__

TUT_UNIT_TEST( "default constructor" )
	if ( ! _socat.is_running() ) {
		SKIP( "failed to start sockat" );
	}
	HSerial s( _path );
	ENSURE_NOT( "bad validity state before open", s.is_valid() );
	s.open();
	ENSURE( "bad validity state after open", s.is_valid() );
TUT_TEARDOWN()

#endif

}


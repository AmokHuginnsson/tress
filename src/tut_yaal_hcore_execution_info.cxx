/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/introspect.hxx>
#include <yaal/hcore/hlog.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_execution_info );
TUT_TEST_GROUP( tut_yaal_hcore_execution_info, "yaal::hcore::execution_info" );

TUT_UNIT_TEST( "dump call stack" )
	dump_call_stack( hcore::log, 10 );
	dump_call_stack( hcore::log, 20 );
TUT_TEARDOWN()

}


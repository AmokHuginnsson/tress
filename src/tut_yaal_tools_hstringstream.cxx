/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hstringstream.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hstringstream );
TUT_TEST_GROUP( tut_yaal_tools_hstringstream, "yaal::tools::HStringStream" );

TUT_UNIT_TEST( "basic stringstream operations" )
	HStringStream stream;
	clog << ( stream << "hello" << ':' << 1024 << ":" << 3.14159265 << '!' << endl << stream ) << flush;
	clog << ( stream << "hello2" << ':' << 17 << ":" << 2.17 << '!' << endl << stream ) << flush;
TUT_TEARDOWN()

}


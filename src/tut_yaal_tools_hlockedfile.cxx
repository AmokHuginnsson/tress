/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hlockedfile.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hlockedfile );
TUT_TEST_GROUP( tut_yaal_tools_hlockedfile, "yaal::tools::HLockedFile" );

TUT_UNIT_TEST( "open file first time" )
	HLockedFile lf( "out/locked.txt", HFile::OPEN::WRITING );
TUT_TEARDOWN()

}


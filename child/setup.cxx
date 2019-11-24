/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdio>
#include <libintl.h>

#include <yaal/hcore/hfile.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "setup.hxx"

using namespace yaal::hcore;

namespace child {

void OSetup::test_setup( void ) {
	M_PROLOG
	if ( _quiet && _verbose )
		yaal::tools::util::failure( 1, "%s",
				_( "quiet and verbose options are exclusive\n" ) );
	if ( _verbose ) {
		clog.reset_owned( make_pointer<HFile>( stdout, HFile::OWNERSHIP::ACQUIRED ) );
	}
	if ( _quiet ) {
		cout.reset_owned();
	}
	return;
	M_EPILOG
}

}


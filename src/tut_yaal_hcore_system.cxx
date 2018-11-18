/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/system.hxx>
#include <yaal/hcore/hcore.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_system );
TUT_TEST_GROUP( tut_yaal_hcore_system, "yaal::hcore::system" );

TUT_UNIT_TEST( "free memory" )
	hcore::system::HResourceInfo ri( hcore::system::get_memory_size_info() );
	clog << "\nTotal memory:           " << setw( 14 ) << ri.total() << " (" << setw( 8 ) << ( ri.total() / 1024 ) << " KiB)" << " (" << setw( 5 ) << ( ri.total() / ( 1024ll * 1024ll ) ) << " MiB)" << endl;
	clog << "Free memory:            " << setw( 14 ) << ri.free() << " (" << setw( 8 ) << ( ri.free() / 1024 ) << " KiB)" << " (" << setw( 5 ) << ( ri.free() / ( 1024ll * 1024ll ) ) << " MiB)" << endl;
	clog << "Available memory:       " << setw( 14 ) << ri.available() << " (" << setw( 8 ) << ( ri.available() / 1024 ) << " KiB)" << " (" << setw( 5 ) << ( ri.available() / ( 1024ll * 1024ll ) ) << " MiB)" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "free disk space" )
	char const fspath[] = "/";
	hcore::system::HResourceInfo ri( hcore::system::get_disk_space_info( fspath ) );
	clog << "\nTotal space on `" << fspath << "':     "
		<< setw( 14 ) << ri.total()
		<< " (" << setw( 8 ) << ( ri.total() / ( 1024 * 1024 ) ) << " MiB)"
		<< " (" << setw( 5 ) << ( ri.total() / ( 1024ll * 1024ll * 1024ll ) ) << " GiB)" << endl;
	clog << "Free space on `" << fspath << "':      "
		<< setw( 14 ) << ri.free()
		<< " (" << setw( 8 ) << ( ri.free() / ( 1024 * 1024 ) ) << " MiB)"
		<< " (" << setw( 5 ) << ( ri.free() / ( 1024ll * 1024ll * 1024ll ) ) << " GiB)" << endl;
	clog << "Available space on `" << fspath << "': "
		<< setw( 14 ) << ri.available()
		<< " (" << setw( 8 ) << ( ri.available() / ( 1024 * 1024 ) ) << " MiB)"
		<< " (" << setw( 5 ) << ( ri.available() / ( 1024ll * 1024ll * 1024ll ) ) << " GiB)" << endl;
	try {
		hcore::system::get_disk_space_info( "invalid" );
	} catch ( HException const& e ) {
		clog << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "available core count" )
	clog << "\nAvailable CPU cores: " << hcore::system::get_core_count_info() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "substitute_environment" )
	/* one layer */ {
		HString s( "HOME=${HOME}:/path/${DEFAULT_TARGET}/subdir/" );
		substitute_environment( s, ENV_SUBST_MODE::ONE_LAYER );
		HString expected( "HOME=" );
		char const* HOME( getenv( "HOME" ) );
		expected.append( HOME ? HOME : "" ).append( ":/path/debug/subdir/" );
		ENSURE_EQUALS( "substitute_environment( ONE_LAYER ) failed", s, expected );
	}
	/* one layer but recursive in nature */ {
		set_env( "LAYER", "${HOME}:/path/" );
		HString s( "HOME=${LAYER}${DEFAULT_TARGET}/subdir/" );
		substitute_environment( s, ENV_SUBST_MODE::ONE_LAYER );
		ENSURE_EQUALS( "substitute_environment( ONE_LAYER ) failed", s, "HOME=${HOME}:/path/debug/subdir/" );
	}
	/* recursive  */ {
		set_env( "LAYER", "${HOME}:/path/" );
		HString s( "HOME=${LAYER}${DEFAULT_TARGET}/subdir/" );
		substitute_environment( s, ENV_SUBST_MODE::RECURSIVE );
		HString expected( "HOME=" );
		char const* HOME( getenv( "HOME" ) );
		expected.append( HOME ? HOME : "" ).append( ":/path/debug/subdir/" );
		ENSURE_EQUALS( "substitute_environment( ONE_LAYER ) failed", s, expected );
	}
TUT_TEARDOWN()

}


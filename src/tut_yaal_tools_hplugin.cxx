/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/hplugin.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

#define RESOLE_MACRO_FOR_MAKE_C_STRING( x ) ( #x )
#define MAKE_C_STRING( x ) RESOLE_MACRO_FOR_MAKE_C_STRING( x )

#define SELF_SUMATOR self_sumator
extern "C"
M_EXPORT_SYMBOL int SELF_SUMATOR( int, int );
extern "C"
M_EXPORT_SYMBOL int SELF_SUMATOR( int a, int b ) {
	return ( a + b );
}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hplugin );
TUT_TEST_GROUP( tut_yaal_tools_hplugin, "yaal::tools::HPlugin" );

typedef int ( * sumator_t )( int, int );
static char const* const TRESS_PLUGIN = "./data/" LIB_PREFIX "tressplugin" LIB_INFIX "." LIB_EXT;

TUT_UNIT_TEST( "load external library and resolve symbol" )
	int const T1 = 7;
	int const T2 = 13;
	HPlugin p;
	p.load( TRESS_PLUGIN );
	ENSURE( "failed to load plugin", p.is_loaded() );
	sumator_t my_sum( nullptr );
	p.resolve( "tut_yaal_tools_hplugin_sum", my_sum );
	ENSURE( "failed to resolve symbol", my_sum != nullptr );
	ENSURE_EQUALS( "cound not utilize plugin", my_sum( T1, T2 ), T1 + T2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "resolve symbol from self" )
#ifdef __HOST_OS_TYPE_CYGWIN__
/* *FIXME TODO*: Try to enable on Cygwin eventually. */
	SKIP( "Cygwin platform error." );
#endif /* #ifdef __HOST_OS_TYPE_CYGWIN__ */
	int const T1 = 7;
	int const T2 = 13;
	HPlugin p;
	p.load( HString() );
	sumator_t my_sum;
	p.resolve( MAKE_C_STRING( SELF_SUMATOR ), my_sum );
	ENSURE_EQUALS( "cound not utilise self-contained symbols", my_sum( T1, T2 ), T1 + T2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "load non-existing plugin" )
	HPlugin p;
	ENSURE_THROW( "non-existing plugin loaded", p.load( "/non/existing/plugin" ), HPluginException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "resolve non-existing symbol" )
	bool loaded( false );
	HPlugin p;
	p.load( TRESS_PLUGIN );
	loaded = p.is_loaded();
	void (*sym)(void) = nullptr;
	ENSURE_THROW( "non-existing plugin loaded", p.resolve( "non_existing_symbol", sym ), HPluginException );
	ENSURE( "failed to load plugin", loaded );
TUT_TEARDOWN()

}


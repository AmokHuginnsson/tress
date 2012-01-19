#include <yaal/hcore/macro.hxx>

extern "C" {

M_EXPORT_SYMBOL int tut_yaal_tools_hplugin_sum( int, int );
M_EXPORT_SYMBOL int tut_yaal_tools_hplugin_sum( int a, int b ) {
	return ( a + b );
}

}


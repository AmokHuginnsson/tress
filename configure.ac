pushdef([MY_PACKAGE_VERSION],[0.0.0-esyscmd(date +%Y%m%d|tr -d '\n')])
AC_INIT([[tress]],[MY_PACKAGE_VERSION],[[amok@codestation.org]])
dnl It is expected that client applications have link to yaal's _aux.
dnl This macro has to be here due to primitivism of libtoolize.
AC_CONFIG_AUX_DIR([_aux])
m4_include([_aux/client-configure.m4])
YAAL_CONFIGURE_CLIENT_INIT(tress,MY_PACKAGE_VERSION)
YAAL_DETECT_FLAGS(SONAME_FLAG, [-Wl,-soname,foo], [C++])
YAAL_DETECT_FLAGS(EXTRA_LXXFLAGS, [-Wl,--export-all-symbols], [C++])
if test ["x${SONAME_FLAG}"] != ["x"] ; then
	SONAME_FLAG="-Wl,-soname,\$(SONAME_\$(NAME))"
fi
AC_SUBST([SONAME_FLAG],[${SONAME_FLAG}])
CXXFLAGS_ORIG="${CXXFLAGS}"
CXXFLAGS="${CXXFLAGS} -Wno-long-long"
m4_include([_aux.local/m4_ax_boost_base.m4])
m4_include([_aux.local/m4_ax_boost_system.m4])
m4_include([_aux.local/m4_ax_boost_filesystem.m4])
m4_include([_aux.local/m4_ax_boost_date_time.m4])
AC_MSG_CHECKING([whether you have SGI STL extensions])
AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#ifdef __GNUC__
#include <ext/functional>
using namespace __gnu_cxx;
#else
#define _HAS_TRADITIONAL_STL 1
#include <functional>
#endif

using namespace std;

int main( int, char** )
	{
	compose1( negate<int>(), negate<int>() )( 7 );
	return ( 0 );
	}
]])], [AC_DEFINE([HAVE_SGI_STL_EXTENSIONS],[],[Do you have SGI STL extensions?])] RESULT=["yes"])
AC_MSG_RESULT([$RESULT])
AC_CHECK_PROG(HAS_TNSPING,[tnsping],["yes"],["no"])
AC_MSG_CHECKING([Oracle DB instance availability])
if test ["$HAS_TNSPING"] = ["yes"] ; then
	ORACLE_INSTANCE=`tnsping spoon | grep '^OK\>' 2> /dev/null`
	if test ["x${ORACLE_INSTANCE}"] != ["x"] ; then
		AC_DEFINE([HAVE_ORACLE_INSTANCE],[],[Do we have Oracle DB instance available?])
		AC_MSG_RESULT([yes])
	else
		AC_MSG_RESULT([no])
	fi
fi
AX_BOOST_BASE([1.35])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_DATE_TIME
CXXFLAGS="${CXXFLAGS_ORIG}"
YAAL_CONFIGURE_CLIENT_FINALIZE

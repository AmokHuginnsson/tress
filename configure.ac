pushdef([MY_PACKAGE_VERSION],[0.0.0-esyscmd(date +%Y%m%d|tr -d '\n')])
AC_INIT([[tress]],[MY_PACKAGE_VERSION],[[amok@codestation.org]])
dnl It is expected that client applications have link to yaal's _aux.
dnl This macro has to be here due to primitivism of libtoolize.
AC_CONFIG_AUX_DIR([_aux])
m4_include([_aux/client-configure.m4])
YAAL_CONFIGURE_CLIENT_INIT(tress, MY_PACKAGE_VERSION)
YAAL_DETECT_FLAGS(SONAME_FLAG, [-Wl,-soname,foo], [C++])
YAAL_DETECT_FLAGS(EXTRA_LXXFLAGS, [-Wl,--export-all-symbols], [C++])
YAAL_DETECT_FLAGS(EXCLUDE_ALL_SYMBOLS, [-Wl,--exclude-all-symbols], [C++])
if test ["x${SONAME_FLAG}"] != ["x"] ; then
	SONAME_FLAG="-Wl,-soname,\$(SONAME_\$(NAME))"
fi
AC_SUBST([SONAME_FLAG],[${SONAME_FLAG}])
AC_SUBST([EXCLUDE_ALL_SYMBOLS],[${EXCLUDE_ALL_SYMBOLS}])
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

int main( int, char** ) {
	compose1( negate<int>(), negate<int>() )( 7 );
	return ( 0 );
}
]])], [AC_DEFINE([HAVE_SGI_STL_EXTENSIONS],[],[Do you have SGI STL extensions?])] RESULT=["yes"])
AC_MSG_RESULT([$RESULT])
AC_COMPILE_IFELSE([AC_LANG_SOURCE([[
#include <functional>

using namespace std;

int main( int, char** ) {
	std::bind2nd( std::less<int>(), 0 );
	return ( 0 );
}
]])], [AC_DEFINE([HAVE_PRE_CXX17_STL],[],[Do you have pre C++17 parts of Standard Template Library?])] RESULT=["yes"])
AC_MSG_RESULT([$RESULT])
AC_CHECK_DECLS([RTLD_NEXT],[],[],[#include <dlfcn.h>])
AC_CHECK_HEADERS([ncurses/curses.h],_NCURSES_HEADER=['ncurses/curses.h'],
	[AC_CHECK_HEADERS([curses.h],_NCURSES_HEADER=['curses.h'],
			[AC_MSG_ERROR([Cannot continue without ncurses devel!])])])
AC_CHECK_SIZEOF([chtype],[],[#include <$_NCURSES_HEADER>])
AC_CHECK_SIZEOF([mmask_t],[],[#include <$_NCURSES_HEADER>])
AC_SEARCH_LIBS([dlopen],[dl],,[AC_MSG_ERROR([Cannot continue without dynamic dynamic linker library.])])
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
if test ["x${CONTINUOUS_INTEGRATION_SYSTEM}"] != ["x"] ; then
	define(
		CONTINUOUS_INTEGRATION_SYSTEM,
		esyscmd(echo -n ["CONTINUOUS_INTEGRATION_${CONTINUOUS_INTEGRATION_SYSTEM}"] | awk '{ printf( toupper( $0 ) ) }')) dnl No newline is significant.
	AC_DEFINE_UNQUOTED(
		[CONTINUOUS_INTEGRATION_SYSTEM],
		[],
		[We are at this continuous integration system.]
	)
fi
AX_BOOST_BASE([1.35])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_DATE_TIME
CXXFLAGS="${CXXFLAGS_ORIG}"
YAAL_CONFIGURE_CLIENT_FINALIZE

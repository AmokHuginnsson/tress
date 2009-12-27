dnl configure.ac is integral part of tress project.

dnl Initialization data.
m4_include([_aux/aclib.m4])
pushdef([MY_PACKAGE_VERSION],[0.0.0-esyscmd(date +%Y%m%d|tr -d '\n')])
AC_INIT([[tress]],[MY_PACKAGE_VERSION],[[amok@codestation.org]])

AC_MSG_RESULT([--- Welcome to tress configurator ---                    [[0%]]])
AC_MSG_RESULT([--- Initialization ... ---                               [[6%]]])

dnl Unique file in project: tressrc is sample configuration file.
AC_MSG_RESULT([--- Finding base directory ... ---                      [[12%]]])
AC_CONFIG_SRCDIR([[tressrc]])
AC_CONFIG_AUX_DIR([../yaal/_aux])

dnl tress is not Free Software.
AC_COPYRIGHT([[tress (c) 2003 All rights reserved.]])

AC_CHECK_PROG(HAS_GIT,[git],["true"],["false"])
AC_MSG_CHECKING([git id sub-command])
AC_SUBST(GITID,[true])
if test ["$HAS_GIT"] = ["true"] ; then
	THIS_ID=`git id ${0}.ac 2> /dev/null`
	if test ["x${THIS_ID}"] != ["x"] ; then
		AC_SUBST(GITID,["git id"])
		AC_MSG_RESULT([ok])
	else
		AC_MSG_WARN([not present])
	fi
else
	AC_MSG_WARN([no git in the first place])
fi

dnl tress is still in alpha stage.
AC_REVISION(${THIS_ID})

dnl We select default language.
AC_LANG([C++])
CXXFLAGS=["-L~/lib -L/usr/local/lib -I~/usr/include -I/usr/local/include"]

dnl Set up how configure will handle header checks.
AC_CONFIG_HEADERS([config.hxx])

dnl Cheching for machine type.
AC_MSG_RESULT([--- Checking for machine type ... ---                   [[14%]]])
AC_CANONICAL_HOST()

dnl Testing presence of c compiler
if test ["$CXX"] = ["colorgcc"] -o ["$CXX"] = ["colorg++"] ; then
	CXX=["g++"]
fi
if test ["$CC"] = ["colorgcc"] ; then
	CC=["gcc"]
fi
AC_MSG_RESULT([--- Testing presence of c compiler ... ---              [[19%]]])
AC_PROG_CC
dnl and for c++ compiler
AC_MSG_RESULT([--- Testing presence of c++ compiler ... ---            [[25%]]])
AC_PROG_CXX
dnl and for c preprocesor
AC_MSG_RESULT([--- Looking standrad development software ... ---       [[33%]]])
AC_PROG_CPP
AC_PROG_CXXCPP
AC_CHECK_PROG([CTAGS],[exctags],[exctags],[ctags])

dnl Check compiler version.
AC_MSG_CHECKING([compiler version])
GCC_MAJOR=`echo | cpp -dM | grep __GNUC__ | awk '{print $3}'`
GCC_MINOR=`echo | cpp -dM | grep __GNUC_MINOR__ | awk '{print $3}'`
AC_MSG_RESULT([major $GCC_MAJOR, minor $GCC_MINOR. ])

dnl Looking for main libc headers
AC_MSG_RESULT([--- Looking for main libc headers ... ---               [[41%]]])
AC_HEADER_MAJOR

YAAL_DETECT_OPERATING_SYSTEM
YAAL_DETECT_PHYSICAL_MEMORY

dnl What special compiler flags we can set?
AC_MSG_RESULT([--- Guessing specific compiler/linker features ... ---  [[71%]]])

YAAL_DETECT_FLAGS(EXTRA_CXXFLAGS, [-fPIC], [C++])
YAAL_DETECT_FLAGS(RDYNAMIC, [-rdynamic], [C++])
YAAL_DETECT_FLAGS(EXTRA_LXXFLAGS, [-Wl,--fatal-warnings], [C++])
YAAL_DETECT_FLAGS(EXTRA_LXXFLAGS, [-Wl,--export-dynamic], [C++])
YAAL_DETECT_FLAGS(EXTRA_LXXFLAGS, [-Wl,--no-undefined], [C++])
YAAL_DETECT_FLAGS(EXTRA_LXXFLAGS, [-Wl,--enable-auto-import], [C++])
YAAL_DETECT_FLAGS(START_GROUP, [-Wl,--start-group], [C++])
YAAL_DETECT_FLAGS(SONAME_FLAG, [-Wl,-soname,foo], [C++])
if test ["x${START_GROUP}"] != ["x"] ; then
	END_GROUP="-Wl,--end-group"
fi
if test ["x${SONAME_FLAG}"] != ["x"] ; then
	SONAME_FLAG="-Wl,-soname,\$(SONAME_\$(NAME))"
fi
_FLAGS=''
CXXFLAGS_ORIG=$CXXFLAGS;
CXXFLAGS=["-Wextra"]
AC_MSG_CHECKING([does gcc support -Wextra])
RESULT=["no"]
AC_COMPILE_IFELSE([ ],
							[EXTRA_CXXFLAGS=["${EXTRA_CXXFLAGS} -Wextra"]]
							[RESULT=["yes"]],
							[EXTRA_CXXFLAGS=["${EXTRA_CXXFLAGS} -W]"])
AC_MSG_RESULT([$RESULT])
CXXFLAGS=["-Wshadow -Werror"]
AC_COMPILE_IFELSE([#include <pthread.h>],
							[EXTRA_CXXFLAGS=["${EXTRA_CXXFLAGS} -Wshadow"]
							_FLAGS=["-Wshadow"]],
							[AC_MSG_WARN([[Cannot use -Wshadow!]])])
CXXFLAGS=$CXXFLAGS_ORIG
CXXFLAGS=["-pedantic-errors"]
AC_COMPILE_IFELSE([#include <cstdlib>],
							[EXTRA_CXXFLAGS=["${EXTRA_CXXFLAGS} -pedantic-errors"]
							_FLAGS=["$_FLAGS -pedantic-errors"]],
							[AC_MSG_WARN([[Cannot use -pedantic-errors!]])])
CXXFLAGS_ORIG=${CXXFLAGS}
CXXFLAGS=${CXXFLAGS_ORIG}
if test ["$_FLAGS"] = [""] ; then
	_FLAGS='none. ---                      [[76%]]'
fi
AC_MSG_RESULT([--- Guessed fetures are: $_FLAGS])

dnl Now we can look for all needed libraries.
CPPFLAGS=$CXXFLAGS;
AC_MSG_RESULT([--- Looking for needed libraries ... ---                [[77%]]])
AC_SEARCH_LIBS([libintl_gettext],[intl],,[AC_SEARCH_LIBS([gettext],[intl],,[AC_MSG_ERROR([Cannot continue without localization library.])])])
AC_CHECK_LIB([ncurses],[initscr],
							[],[AC_MSG_ERROR([Can not continue without ncurses.])])
AC_CHECK_LIB([hcore],[yaal_hcore_main],
							[],[AC_MSG_ERROR([Can not continue without hcore.])])
AC_CHECK_LIB([hconsole],[yaal_hconsole_main],
							[],[AC_MSG_ERROR([Can not continue without hconsole.])])
AC_CHECK_LIB([tools],[yaal_tools_main],
							[],[AC_MSG_ERROR([Can not continue without tools.])])
AC_CHECK_LIB([dbwrapper],[yaal_dbwrapper_main],
							[],[AC_MSG_ERROR([Can not continue without dbwrapper.])])
AC_CHECK_LIB([hdata],[yaal_hdata_main],
							[],[AC_MSG_ERROR([Can not continue without hdata.])])
AC_MSG_RESULT([--- All needed libraries found. ---                     [[83%]]])

AC_MSG_RESULT([--- Looking for needed headers ... ---                  [[84%]]])
AC_CHECK_HEADERS([yaal/yaal.hxx],,
			[AC_MSG_ERROR([[Can not continue without yaal devel!]])])
AC_MSG_RESULT([--- Done looking for needed header, all found. ---      [[92%]]])

dnl We need to check if out ncurses devel is not brain-damaged.
AC_MSG_RESULT([--- Libraries/environment sanity check ... ---          [[93%]]])

AC_SUBST([EXTRA_CXXFLAGS],[${EXTRA_CXXFLAGS}])
AC_SUBST([EXTRA_LXXFLAGS],[${EXTRA_LXXFLAGS}])
AC_SUBST([START_GROUP],[${START_GROUP}])
AC_SUBST([END_GROUP],[${END_GROUP}])
AC_SUBST([RDYNAMIC],[${RDYNAMIC}])

AH_TOP([/* $Id$ */

#ifndef TRESS_CONFIG_HXX_INCLUDED
#define TRESS_CONFIG_HXX_INCLUDED

/* Define core behavior here. */])
AH_BOTTOM([
#endif /* not TRESS_CONFIG_HXX_INCLUDED */
])

dnl We have to set up proper compiler/linker flags.
AC_OUTPUT([Makefile.mk])
AC_MSG_RESULT([--- All ok, good luck! ---                     	       [[100%]]])
AC_MSG_RESULT([[Now you can type \`make'.]])


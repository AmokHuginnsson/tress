pushdef([MY_PACKAGE_VERSION],[0.0.0-esyscmd(date +%Y%m%d|tr -d '\n')])
AC_INIT([[tress]],[MY_PACKAGE_VERSION],[[amok@codestation.org]])
m4_include([_aux/client-configure.m4])
YAAL_CONFIGURE_CLIENT_INIT(tress,MY_PACKAGE_VERSION)
YAAL_DETECT_FLAGS(SONAME_FLAG, [-Wl,-soname,foo], [C++])
if test ["x${SONAME_FLAG}"] != ["x"] ; then
	SONAME_FLAG="-Wl,-soname,\$(SONAME_\$(NAME))"
fi
AC_SUBST([SONAME_FLAG],[${SONAME_FLAG}])
YAAL_CONFIGURE_CLIENT_FINALIZE

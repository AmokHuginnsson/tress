pushdef([MY_PACKAGE_VERSION],[0.0.0-esyscmd(date +%Y%m%d|tr -d '\n')])
AC_INIT([[tress]],[MY_PACKAGE_VERSION],[[amok@codestation.org]])
dnl It is expected that client applications have link to yaal's _aux.
dnl This macro has to be here due to primitivism of libtoolize.
AC_CONFIG_AUX_DIR([_aux])
m4_include([_aux/client-configure.m4])
YAAL_CONFIGURE_CLIENT_INIT(tress,MY_PACKAGE_VERSION)
YAAL_DETECT_FLAGS(SONAME_FLAG, [-Wl,-soname,foo], [C++])
if test ["x${SONAME_FLAG}"] != ["x"] ; then
	SONAME_FLAG="-Wl,-soname,\$(SONAME_\$(NAME))"
fi
AC_SUBST([SONAME_FLAG],[${SONAME_FLAG}])
m4_include([_aux.local/m4_ax_boost_base.m4])
m4_include([_aux.local/m4_ax_boost_system.m4])
m4_include([_aux.local/m4_ax_boost_filesystem.m4])
m4_include([_aux.local/m4_ax_boost_date_time.m4])
AX_BOOST_BASE([1.35])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_DATE_TIME
YAAL_CONFIGURE_CLIENT_FINALIZE

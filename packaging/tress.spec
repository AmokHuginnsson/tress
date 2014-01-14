Name:	tress
Version:	0.0.0
Release:	1%{?dist}
Summary:	Yet Another Abstraction Layer - general purpose C++ library.

Group:		System Environment/Libraries
License:	Commercial
URL:			http://codestation.org/
Source:	%{name}-%{version}.tar.gz
# Source: https://codestation.org/repo/tress.git
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:	make, autoconf, libtool, yaal-devel, ncurses-devel, boost-devel, boost-date_time, boost-filesystem, boost-system
Requires:	yaal

%description

%define flagfilter sed -e 's/-O2\\>//g' -e 's/-g\\>//g' -e 's/-Wall\\>//g' -e 's/-Werror\\>//g' -e 's/-Wformat-security\\>//g' -e 's/-Wformat\\>//g'
%define clearflags export CFLAGS=`echo ${CFLAGS} | %{flagfilter}`;export CXXFLAGS=`echo ${CXXFLAGS} | %{flagfilter}`

%prep
umask 0077
if [ -f "${RPM_SOURCE_DIR}/%{name}-%{version}.tar.gz" ] ; then
%setup
else
	cd -
	/bin/rm -rf "${RPM_BUILD_DIR}/%{name}-%{version}"
	mkdir "${RPM_BUILD_DIR}/%{name}-%{version}"
	tar cf - --exclude build . | tar -x -C "${RPM_BUILD_DIR}/%{name}-%{version}"
	cd -
fi
cd "${RPM_BUILD_DIR}/%{name}-%{version}"
if [ ! -f GNUmakefile ] ; then
	if [ -f %{_datadir}/yaal/_aux/mk/GNUmakefile ] ; then
		ln -nsf %{_datadir}/yaal/_aux/ .
	fi
fi
make purge

%build
umask 0077
%{clearflags}
make debug PREFIX=%{_prefix} SYSCONFDIR=%{_sysconfdir} LIBDIR=%{_libdir}

%install
rm -rf ${RPM_BUILD_ROOT}
umask 0077
make install-debug DESTDIR=${RPM_BUILD_ROOT}
rm -f ${RPM_BUILD_ROOT}/%{_libdir}/ld.so.conf ${RPM_BUILD_ROOT}/%{_libdir}/ld.so.cache ${RPM_BUILD_ROOT}/%{_libdir}/mkcache

%clean
rm -rf ${RPM_BUILD_ROOT}
umask 0077
make purge

%files
%defattr(-,root,root,-)
%{_bindir}/tress
#%{_libdir}/lib*[a-z]?.so*
%{_sysconfdir}/*
%{_datadir}/doc
%doc

%changelog


#! /bin/sh

VER=`echo | isql-fb -q -z | awk -F '[ .-]' '/Version:/{print $4}'`

USER="root"
PASS="r00t"

if [ "x${VER}" = "xV3" ] ; then
	USER="sysdba"
	PASS="masterkey"
fi

set -x
exec isql-fb -e -r 'RDB$ADMIN' -u "${USER}" -p "${PASS}" localhost: < data/firebird${VER}.sql


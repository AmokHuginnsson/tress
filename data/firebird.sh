#! /bin/sh

VER=`echo | isql-fb -q -z | awk -F '[ .-]' '/Version:/{print $4}'`

DB="security2.fdb"
if [ "x${VER}" = "xV3" ] ; then
	DB="template"
fi

set -x
exec isql-fb -e -r 'RDB$ADMIN' -u 'root' -p 'r00t' "localhost:${DB}" < data/firebird${VER}.sql


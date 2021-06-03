#! /bin/sh

version=$(echo | isql-fb -q -z | awk -F '[ .-]' '/Version:/{print $4}')

database="security2.fdb"
if [ "x${version}" = "xV4" ] ; then
	version="V3"
fi
if [ "x${version}" = "xV3" ] ; then
	database="template"
fi

set -x
exec isql-fb -e -r 'RDB$ADMIN' -u 'root' -p 'r00t' "localhost:${database}" < data/firebird${version}.sql


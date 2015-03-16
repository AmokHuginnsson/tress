#! /bin/sh

exec isql-fb -e -r 'RDB$ADMIN' -u root -p r00t localhost: < data/firebird.sql


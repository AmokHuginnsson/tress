/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_dbwrapper_hrecordset.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace yaal::dbwrapper;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_dbwrapper_hrecordset );
TUT_TEST_GROUP( tut_yaal_dbwrapper_hrecordset, "yaal::dbwrapper::HRecordSet" );

void dump_query_result( HDataBase::ptr_t db, char const* const query ) {
	M_PROLOG
	HRecordSet::ptr_t rs = db->query( query );
	for ( HRecordSet::iterator it = rs->begin(); it != rs->end(); ++ it ) {
		cout << "|";
		int fc = rs->get_field_count();
		for ( int i = 0; i < fc; ++ i )
			cout << *it[ i ] << "|";
		cout << endl;
	}
	return;
	M_EPILOG
}

static char const* const QUERY = "SELECT * FROM config;";

TUT_UNIT_TEST( 1, "simple query on default engine" )
	HDataBase::ptr_t db = HDataBase::get_connector();
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "SQLite engine" )
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY );
#else /* defined( HAVE_SQLITE3_H ) */

#endif /* not defined( HAVE_SQLITE3_H ) */
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "PostgreSQL engine" )
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "MySQL engine" )
#if defined( HAVE_MYSQL_MYSQL_H )
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::MYSQL );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "different engines all in one" )
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t dbSQLite = HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 );
	dbSQLite->connect( "./out/tress", "", "" );
	dump_query_result( dbSQLite, QUERY );
#endif /* defined( HAVE_SQLITE3_H ) */
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	HDataBase::ptr_t dbPostgreSQL = HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL );
	dbPostgreSQL->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbPostgreSQL, QUERY );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
#if defined( HAVE_MYSQL_MYSQL_H )
	HDataBase::ptr_t dbMySQL = HDataBase::get_connector( ODBConnector::DRIVER::MYSQL );
	dbMySQL->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbMySQL, QUERY );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
TUT_TEARDOWN()

static char const* const SPECIAL_QUERY = "SELECT * FROM config WHERE name = 'special';";
static char const* const SPECIAL_INSERT = "INSERT INTO config ( name, value ) VALUES( 'special', 'first' );";
static char const* const SPECIAL_UPDATE = "UPDATE config SET value = 'second' WHERE name = 'special';";
static char const* const SPECIAL_DELETE = "DELETE FROM config WHERE name = 'special';";

void test_dml( HDataBase::ptr_t db ) {
	M_PROLOG
	TUT_DECLARE( HRecordSet::ptr_t rs( db->query( SPECIAL_QUERY ) ); );
	ENSURE( "empty result not entirelly empty ???", ! rs || ( rs->begin() == rs->end() ) );
	ENSURE_EQUALS( "bad COUNT(*)", rs->get_size(), 0 );
	TUT_INVOKE( rs = db->query( SPECIAL_INSERT ); );
	int long lastInsertId( rs->get_insert_id() );
	clog << "lastInsertId: " << lastInsertId << endl;
	ENSURE_EQUALS( "bad last insert id", lastInsertId > 4, true );
	TUT_INVOKE( rs = db->query( SPECIAL_QUERY ); );
	ENSURE_EQUALS( "bad COUNT(*) after SELECT", rs->get_size(), 1 );
	ENSURE( "INSERT failed?", !! rs && ( rs->begin() != rs->end() ) && rs->begin()[1] && ( *(rs->begin()[1]) == "special" ) && rs->begin()[2] && ( *(rs->begin()[2]) == "first" ) );
	TUT_INVOKE( rs = db->query( SPECIAL_UPDATE ); );
	ENSURE_EQUALS( "bad COUNT(*) after UPDATE", rs->get_size(), 1 );
	TUT_INVOKE( rs = db->query( SPECIAL_QUERY ); );
	ENSURE_EQUALS( "bad COUNT(*) after SELECT", rs->get_size(), 1 );
	ENSURE( "UPDATE failed?", !! rs && ( rs->begin() != rs->end() ) && rs->begin()[1] && ( *(rs->begin()[1]) == "special" ) && rs->begin()[2] && ( *(rs->begin()[2]) == "second" ) );
	TUT_INVOKE( rs = db->query( SPECIAL_DELETE ); );
	ENSURE_EQUALS( "bad COUNT(*) after DELETE", rs->get_size(), 1 );
	TUT_INVOKE( rs = db->query( SPECIAL_QUERY ); );
	ENSURE_EQUALS( "bad COUNT(*) after SELECT", rs->get_size(), 0 );
	ENSURE( "DELETE failed?", ! rs || ( rs->begin() == rs->end() ) );
	return;
	M_EPILOG
}

TUT_UNIT_TEST( 6, "dml on SQLite" )
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 );
	db->connect( "./out/tress", "", "" );
	test_dml( db );
#endif /* defined( HAVE_SQLITE3_H ) */
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "PostgreSQL engine" )
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "MySQL engine" )
#if defined( HAVE_MYSQL_MYSQL_H )
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::MYSQL );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_dbwrapper_hrecordset.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/dbwrapper/dbwrapper.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_dbwrapper_hrecordset );
TUT_TEST_GROUP( tut_yaal_dbwrapper_hrecordset, "yaal::dbwrapper::HRecordSet" );

void dump_query_result( HDataBase::ptr_t db, char const* const query, char const* dbType_ ) {
	M_PROLOG
	HRecordSet::ptr_t rs = db->query( query );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", NULL },
		{ "2", "two", NULL },
		{ "3", "three", "Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!" }
	};
	cout << "|";
	for ( int i( 0 ), COUNT( rs->get_field_count() ); i < COUNT; ++ i ) {
		HString cn( rs->get_column_name( i ) );
		cn.lower();
		ENSURE_EQUALS( "bad column name", cn, COLUMN_NAMES[i] );
		cout << cn << "|";
	}
	cout << endl;
	int row( 0 );
	for ( HRecordSet::iterator it = rs->begin(); it != rs->end(); ++ it, ++ row ) {
		cout << "|";
		int fc = rs->get_field_count();
		for ( int i = 0; i < fc; ++ i ) {
			HRecordSet::value_t v( it[i] );
			if ( ( row == 0 ) && ( i == 2 ) ) {
				if ( dbType_ )
					ENSURE_EQUALS( "wrong database accessed", *v, dbType_ );
			} else {
				if ( !!v )
					ENSURE_EQUALS( "wrong value", *v, DATA[row][i] );
				else
					ENSURE_EQUALS( "wrong value", static_cast<char const*>( NULL ), DATA[row][i] );
			}
			cout << ( !v ? HString( "(NULL)" ) : *v ) << "|";
		}
		cout << endl;
	}
	return;
	M_EPILOG
}

static char const* const QUERY = "SELECT * FROM config;";

TUT_UNIT_TEST( 1, "simple query on default engine" )
	HDataBase::ptr_t db( HDataBase::get_connector() );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY, NULL );
TUT_TEARDOWN()

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 2, "SQLite engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 3, "PostgreSQL engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 4, "MySQL engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 5, "Firebird engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if 0 && defined( HAVE_OCI_H )
TUT_UNIT_TEST( 6, "Oracle engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) */

#if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_OCI_H )
TUT_UNIT_TEST( 7, "different engines all in one" )
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t dbSQLite( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	dbSQLite->connect( "./out/tress", "", "" );
	dump_query_result( dbSQLite, QUERY, "sqlite3" );
#endif /* defined( HAVE_SQLITE3_H ) */
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	HDataBase::ptr_t dbPostgreSQL( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	dbPostgreSQL->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbPostgreSQL, QUERY, "PostgreSQL" );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
#if defined( HAVE_MYSQL_MYSQL_H )
	HDataBase::ptr_t dbMySQL( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	dbMySQL->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbMySQL, QUERY, "MySQL" );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
#if defined( HAVE_IBASE_H )
	HDataBase::ptr_t dbFirebird( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	dbFirebird->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbFirebird, QUERY, "Firebird" );
#endif /* defined( HAVE_IBASE_H ) */
#if 0 && defined( HAVE_OCI_H )
	HDataBase::ptr_t dbOracle( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	dbOracle->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbOracle, QUERY, "Oracle" );
#endif /* defined( HAVE_OCI_H ) */
TUT_TEARDOWN()
#endif /* #if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_OCI_H ) */

static char const* const SPECIAL_QUERY = "SELECT * FROM config WHERE name = 'special';";
static char const* const SPECIAL_INSERT = "INSERT INTO config ( name, data ) VALUES( 'special', 'first' );";
static char const* const SPECIAL_UPDATE = "UPDATE config SET data = 'second' WHERE name = 'special';";
static char const* const SPECIAL_DELETE = "DELETE FROM config WHERE name = 'special';";

void test_dml( HDataBase::ptr_t db ) {
	M_PROLOG
	TUT_DECLARE( HRecordSet::ptr_t rs( db->query( SPECIAL_QUERY ) ); );
	ENSURE( "empty result not entirelly empty ???", ! rs || ( rs->begin() == rs->end() ) );
	ENSURE_EQUALS( "bad COUNT(*)", rs->get_size(), 0 );
	TUT_INVOKE( rs = db->query( SPECIAL_INSERT ); );
	int long lastInsertId( rs->get_insert_id() );
	clog << "lastInsertId: " << lastInsertId << endl;
	ENSURE_EQUALS( "bad last insert id", lastInsertId > 3, true );
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

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 8, "dml on SQLite" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 9, "PostgreSQL engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 10, "MySQL engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 11, "Firebird engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if 0 && defined( HAVE_OCI_H )
TUT_UNIT_TEST( 12, "Oracle engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) */

void test_schema( HDataBase::ptr_t db_ ) {
	M_PROLOG
	HDataBase::table_list_t tl( db_->get_tables() );
	ENSURE_EQUALS( "bad table list size", tl.get_size(), 1 );
	HDataBase::table_list_t tlExpect;
	tlExpect.push_back( "config" );
	ENSURE_EQUALS( "bad table list contents", tl, tlExpect );
	HDataBase::column_list_t cl( db_->get_columns( tl[0] ) );
	ENSURE_EQUALS( "bad column list count", cl.get_size(), 3 );
	HDataBase::column_list_t clExpect;
	clExpect.push_back( "id" );
	clExpect.push_back( "name" );
	clExpect.push_back( "data" );
	ENSURE_EQUALS( "bad column list contents", cl, clExpect );
	return;
	M_EPILOG
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 13, "sqlite3 schema" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 14, "PostgreSQL schema" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 15, "MySQL schema" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 16, "Firebird schema" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if 0 && defined( HAVE_OCI_H )
TUT_UNIT_TEST( 17, "Oracle schema" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) */

#if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_OCI_H )
TUT_UNIT_TEST( 18, "different engines all in one by DSN" )
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t dbSQLite( util::connect( "sqlite3:///out/tress.sqlite" ) );
	dump_query_result( dbSQLite, QUERY, "sqlite3" );
#endif /* defined( HAVE_SQLITE3_H ) */
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	HDataBase::ptr_t dbPostgreSQL( util::connect( "postgresql://tress:tr3ss@/tress" ) );
	dump_query_result( dbPostgreSQL, QUERY, "PostgreSQL" );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
#if defined( HAVE_MYSQL_MYSQL_H )
	HDataBase::ptr_t dbMySQL( util::connect( "mysql://tress:tr3ss@/tress" ) );
	dump_query_result( dbMySQL, QUERY, "MySQL" );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
#if defined( HAVE_IBASE_H )
	HDataBase::ptr_t dbFirebird( util::connect( "firebird://tress:tr3ss@/tress" ) );
	dump_query_result( dbFirebird, QUERY, "Firebird" );
#endif /* defined( HAVE_IBASE_H ) */
#if 0 && defined( HAVE_OCI_H )
	HDataBase::ptr_t dbOracle( util::connect( "oracle://tress:tr3ss@/tress" ) );
	dump_query_result( dbOracle, QUERY, "Oracle" );
#endif /* defined( HAVE_OCI_H ) */
TUT_TEARDOWN()
#endif /* #if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_OCI_H ) */

}


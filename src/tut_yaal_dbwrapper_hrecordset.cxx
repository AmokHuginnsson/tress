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
#include <yaal/tools/hmonitor.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_dbwrapper_hrecordset : public simple_mock<tut_yaal_dbwrapper_hrecordset> {
	virtual ~tut_yaal_dbwrapper_hrecordset( void ) {}
	void dump_query_result( HDataBase::ptr_t, char const*, char const* );
	void test_dml( HDataBase::ptr_t );
	void test_schema( HDataBase::ptr_t );
	void row_by_row_test( HDataBase::ptr_t, char const*, char const* );
	void bind_test( HDataBase::ptr_t, char const* );
};
TUT_TEST_GROUP( tut_yaal_dbwrapper_hrecordset, "yaal::dbwrapper::HRecordSet" );

void tut_yaal_dbwrapper_hrecordset::dump_query_result( HDataBase::ptr_t db, char const* query, char const* dbType_ ) {
	M_PROLOG
	HRecordSet::ptr_t rs = db->execute_query( query );
	ENSURE_EQUALS( "bad column count", rs->get_field_count(), 3 );
	ENSURE_EQUALS( "bad result size", rs->get_size(), 3 );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", NULL },
		{ "2", "two", NULL },
		{ "3", "three", "M�ny b�d�, chro� pu�k tw�j i sze�� flag!" }
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
		int fc( rs->get_field_count() );
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
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector() );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY, NULL );
TUT_TEARDOWN()

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 2, "SQLite engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 3, "PostgreSQL engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 4, "MySQL engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 5, "Firebird engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( 6, "Oracle engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

#if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) )
TUT_UNIT_TEST( 7, "different engines all in one" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
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
#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
	HDataBase::ptr_t dbOracle( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	dbOracle->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbOracle, QUERY, "Oracle" );
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */
TUT_TEARDOWN()
#endif /* #if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) ) */

static char const* const SPECIAL_QUERY = "SELECT * FROM config WHERE name = 'special';";
static char const* const SPECIAL_INSERT = "INSERT INTO config ( name, data ) VALUES( 'special', 'first' );";
static char const* const SPECIAL_UPDATE = "UPDATE config SET data = 'second' WHERE name = 'special';";
static char const* const SPECIAL_DELETE = "DELETE FROM config WHERE name = 'special';";

void tut_yaal_dbwrapper_hrecordset::test_dml( HDataBase::ptr_t db ) {
	M_PROLOG
	TUT_DECLARE( HRecordSet::ptr_t rs( db->execute_query( SPECIAL_QUERY ) ); );
	ENSURE( "empty result not entirelly empty ???", ! rs || ( rs->begin() == rs->end() ) );
	ENSURE_EQUALS( "bad COUNT(*)", rs->get_size(), 0 );
	TUT_INVOKE( rs = db->execute_query( SPECIAL_INSERT ); );
	int long lastInsertId( rs->get_insert_id() );
	clog << "lastInsertId: " << lastInsertId << endl;
	ENSURE_EQUALS( "bad last insert id", lastInsertId > 3, true );
	TUT_INVOKE( rs = db->execute_query( SPECIAL_QUERY ); );
	ENSURE_EQUALS( "bad COUNT(*) after SELECT", rs->get_size(), 1 );
	ENSURE( "INSERT failed?", !! rs && ( rs->begin() != rs->end() ) && rs->begin()[1] && ( *(rs->begin()[1]) == "special" ) && rs->begin()[2] && ( *(rs->begin()[2]) == "first" ) );
	TUT_INVOKE( rs = db->execute_query( SPECIAL_UPDATE ); );
	ENSURE_EQUALS( "bad COUNT(*) after UPDATE", rs->get_size(), 1 );
	TUT_INVOKE( rs = db->execute_query( SPECIAL_QUERY ); );
	ENSURE_EQUALS( "bad COUNT(*) after SELECT", rs->get_size(), 1 );
	ENSURE( "UPDATE failed?", !! rs && ( rs->begin() != rs->end() ) && rs->begin()[1] && ( *(rs->begin()[1]) == "special" ) && rs->begin()[2] && ( *(rs->begin()[2]) == "second" ) );
	TUT_INVOKE( rs = db->execute_query( SPECIAL_DELETE ); );
	ENSURE_EQUALS( "bad COUNT(*) after DELETE", rs->get_size(), 1 );
	TUT_INVOKE( rs = db->execute_query( SPECIAL_QUERY ); );
	ENSURE_EQUALS( "bad COUNT(*) after SELECT", rs->get_size(), 0 );
	ENSURE( "DELETE failed?", ! rs || ( rs->begin() == rs->end() ) );
	return;
	M_EPILOG
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 8, "dml on SQLite" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 9, "dml on PostgreSQL engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 10, "dml on MySQL engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 11, "dml on Firebird engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( 12, "dml on Oracle engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

void tut_yaal_dbwrapper_hrecordset::test_schema( HDataBase::ptr_t db_ ) {
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
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 14, "PostgreSQL schema" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 15, "MySQL schema" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 16, "Firebird schema" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( 17, "Oracle schema" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

#if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) )
TUT_UNIT_TEST( 18, "different engines all in one by DSN" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
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
#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
	HDataBase::ptr_t dbOracle( util::connect( "oracle://tress:tr3ss@/tress" ) );
	dump_query_result( dbOracle, QUERY, "Oracle" );
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */
TUT_TEARDOWN()
#endif /* #if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) ) */

void tut_yaal_dbwrapper_hrecordset::row_by_row_test( HDataBase::ptr_t db, char const* query, char const* dbType_ ) {
	M_PROLOG
	HRecordSet::ptr_t rs = db->execute_query( query, HRecordSet::CURSOR::FORWARD );
	ENSURE_EQUALS( "bad column count", rs->get_field_count(), 3 );
	ENSURE_THROW( "recieved record count in row-by-row mode", rs->get_size(), HRecordSetException );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", NULL },
		{ "2", "two", NULL },
		{ "3", "three", "M�ny b�d�, chro� pu�k tw�j i sze�� flag!" }
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
		int fc( rs->get_field_count() );
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

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 19, "SQLite engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	row_by_row_test( db, QUERY, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( 20, "PostgreSQL engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	row_by_row_test( db, QUERY, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( 21, "MySQL engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	row_by_row_test( db, QUERY, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H )
TUT_UNIT_TEST( 22, "Firebird engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	row_by_row_test( db, QUERY, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( 23, "Oracle engine" )
	external_lock_t l( HMonitor::get_instance().acquire( "locale" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	row_by_row_test( db, QUERY, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

void tut_yaal_dbwrapper_hrecordset::bind_test( HDataBase::ptr_t db, char const* dbType_ ) {
	HQuery::ptr_t q( db->prepare_query( "SELECT data FROM config WHERE id = ?" ) );
	q->bind( 1, "1" );
	HRecordSet::ptr_t r( q->execute() );
	ENSURE_EQUALS( "bad field count", r->get_field_count(), 1 );
	HRecordSet::HIterator it( r->begin() );
	HRecordSet::HIterator end( r->end() );
	ENSURE( "empty set", it != end );
	HRecordSet::value_t v( it[0] );
	ENSURE( "empty value", !!v );
	ENSURE_EQUALS( "bad value", *v, dbType_ );
	++ it;
	ENSURE( "set too large", ! ( it != end ) );
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( 24, "Bind SQLite engine" )
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	bind_test( db, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

}


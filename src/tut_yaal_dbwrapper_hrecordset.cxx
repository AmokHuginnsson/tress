/* Read tress/LICENSE.md file for copyright and licensing information. */

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
	void row_by_row_test( HDataBase::ptr_t, char const*, char const* );
};
TUT_TEST_GROUP( tut_yaal_dbwrapper_hrecordset, "yaal::dbwrapper::HRecordSet" );

void tut_yaal_dbwrapper_hrecordset::dump_query_result( HDataBase::ptr_t db, char const* query, char const* dbType_ ) {
	M_PROLOG
	HRecordSet::ptr_t rs = db->execute_query( query );
	ENSURE_EQUALS( "bad column count", rs->get_field_count(), 3 );
	ENSURE_EQUALS( "bad result size", rs->get_size(), 3 );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", dbType_ },
		{ "2", "two", nullptr },
		{ "3", "three", "Mężny bądź, chroń pułk twój i sześć flag!" }
	};
	clog << "|";
	for ( int i( 0 ), COUNT( rs->get_field_count() ); i < COUNT; ++ i ) {
		HString cn( rs->get_column_name( i ) );
		cn.lower();
		ENSURE_EQUALS( "bad column name", cn, COLUMN_NAMES[i] );
		clog << cn << "|";
	}
	clog << endl;
	int row( 0 );
	ENSURE_NOT( "is_empty() failed", rs->is_empty() );
	for ( HRecordSet::iterator it = rs->begin(); it != rs->end(); it ++, ++ row ) {
		clog << "|";
		int fc( rs->get_field_count() );
		for ( int i = 0; i < fc; ++ i ) {
			HRecordSet::value_t v( it[i] );
			if ( !!v ) {
				if ( dbType_ || ( row != 0 ) || ( i != 2 ) ) {
					ENSURE_EQUALS( "wrong value", *v, DATA[row][i] );
				}
			} else {
				ENSURE_EQUALS( "wrong value", static_cast<char const*>( nullptr ), DATA[row][i] );
			}
			clog << ( !v ? HString( "(nullptr)" ) : *v ) << "|";
		}
		clog << endl;
	}
	int fc( rs->get_field_count() );
	for ( int r( 0 ), count( static_cast<int>( rs->get_size() ) ); r < count; ++ r ) {
		for ( int i = 0; i < fc; ++ i ) {
			HRecordSet::value_t v( rs->get( r, i ) );
			if ( ( r == 0 ) && ( i == 2 ) ) {
				if ( dbType_ ) {
					ENSURE_EQUALS( "wrong database accessed", *v, dbType_ );
				}
			} else {
				if ( !!v ) {
					ENSURE_EQUALS( "wrong value", *v, DATA[r][i] );
				} else {
					ENSURE_EQUALS( "wrong value", static_cast<char const*>( nullptr ), DATA[r][i] );
				}
			}
		}
	}
	row = static_cast<int>( rs->get_size() - 1 );
	for ( HRecordSet::iterator it = rs->rbegin(); it != rs->rend(); -- it, -- row ) {
		HRecordSet::iterator copy( it );
		copy = it;
		for ( int i = 0; i < fc; ++ i ) {
			HRecordSet::value_t v( copy[i] );
			if ( ( row == 0 ) && ( i == 2 ) ) {
				if ( dbType_ ) {
					ENSURE_EQUALS( "wrong database accessed", *v, dbType_ );
				}
			} else {
				if ( !!v ) {
					ENSURE_EQUALS( "wrong value", *v, DATA[row][i] );
				} else {
					ENSURE_EQUALS( "wrong value", static_cast<char const*>( nullptr ), DATA[row][i] );
				}
			}
		}
	}
	return;
	M_EPILOG
}

static char const* const QUERY = "SELECT * FROM config;";

TUT_UNIT_TEST( "simple query on default engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector() );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY, nullptr );
TUT_TEARDOWN()

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( "SQLite engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	char const* host( getenv( "TRESS_POSTGRESQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	dump_query_result( db, QUERY, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	char const* host( getenv( "TRESS_MYSQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	dump_query_result( db, QUERY, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	char const* host( getenv( "TRESS_FIREBIRD_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "localhost" );
	dump_query_result( db, QUERY, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

#if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) )
TUT_UNIT_TEST( "different engines all in one" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t dbSQLite( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	dbSQLite->connect( "./out/tress", "", "" );
	dump_query_result( dbSQLite, QUERY, "sqlite3" );
#endif /* defined( HAVE_SQLITE3_H ) */
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	HDataBase::ptr_t dbPostgreSQL( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	char const* postgresqlHost( getenv( "TRESS_POSTGRESQL_HOST" ) );
	dbPostgreSQL->connect( "tress", "tress", "tr3ss", postgresqlHost ? postgresqlHost : "" );
	dump_query_result( dbPostgreSQL, QUERY, "PostgreSQL" );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
#if defined( HAVE_MYSQL_MYSQL_H )
	HDataBase::ptr_t dbMySQL( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	char const* mysqlHost( getenv( "TRESS_MYSQL_HOST" ) );
	dbMySQL->connect( "tress", "tress", "tr3ss", mysqlHost ? mysqlHost : "" );
	dump_query_result( dbMySQL, QUERY, "MySQL" );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
	HDataBase::ptr_t dbFirebird( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	char const* firebirdHost( getenv( "TRESS_FIREBIRD_HOST" ) );
	dbFirebird->connect( "tress", "tress", "tr3ss", firebirdHost ? firebirdHost : "localhost" );
	dump_query_result( dbFirebird, QUERY, "Firebird" );
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */
#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
	HDataBase::ptr_t dbOracle( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	dbOracle->connect( "tress", "tress", "tr3ss" );
	dump_query_result( dbOracle, QUERY, "Oracle" );
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */
TUT_TEARDOWN()
#endif /* #if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) ) */

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
TUT_UNIT_TEST( "dml on SQLite" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "dml on PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	char const* host( getenv( "TRESS_POSTGRESQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "dml on MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	char const* host( getenv( "TRESS_MYSQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "dml on Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	char const* host( getenv( "TRESS_FIREBIRD_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "localhost" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "dml on Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

#if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) )
TUT_UNIT_TEST( "different engines all in one by DSN" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
#if defined( HAVE_SQLITE3_H )
	HDataBase::ptr_t dbSQLite( util::connect( "sqlite3:///out/tress.sqlite" ) );
	dump_query_result( dbSQLite, QUERY, "sqlite3" );
#endif /* defined( HAVE_SQLITE3_H ) */
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	char const* postgresqlHost( getenv( "TRESS_POSTGRESQL_HOST" ) );
	HDataBase::ptr_t dbPostgreSQL( util::connect( "postgresql://tress:tr3ss@"_ys.append( postgresqlHost ? postgresqlHost : "" ).append( "/tress" ) ) );
	dump_query_result( dbPostgreSQL, QUERY, "PostgreSQL" );
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
#if defined( HAVE_MYSQL_MYSQL_H )
	char const* mysqlHost( getenv( "TRESS_MYSQL_HOST" ) );
	HDataBase::ptr_t dbMySQL( util::connect( "mysql://tress:tr3ss@"_ys.append( mysqlHost ? mysqlHost : "" ).append( "/tress" ) ) );
	dump_query_result( dbMySQL, QUERY, "MySQL" );
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
	char const* firebirdHost( getenv( "TRESS_FIREBIRD_HOST" ) );
	HDataBase::ptr_t dbFirebird( util::connect( "firebird://tress:tr3ss@"_ys.append( firebirdHost ? firebirdHost: "localhost" ).append( "/tress" ) ) );
	dump_query_result( dbFirebird, QUERY, "Firebird" );
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */
#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
	HDataBase::ptr_t dbOracle( util::connect( "oracle://tress:tr3ss@/tress" ) );
	dump_query_result( dbOracle, QUERY, "Oracle" );
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */
TUT_TEARDOWN()
#endif /* #if defined( HAVE_SQLITE3_H ) || defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) || defined( HAVE_MYSQL_MYSQL_H ) || defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) || ( defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) ) */

void tut_yaal_dbwrapper_hrecordset::row_by_row_test( HDataBase::ptr_t db, char const* query, char const* dbType_ ) {
	M_PROLOG
	HRecordSet::ptr_t rs = db->execute_query( query, HRecordSet::CURSOR::FORWARD );
	ENSURE_EQUALS( "bad column count", rs->get_field_count(), 3 );
	ENSURE_THROW( "recieved record count in row-by-row mode", rs->get_size(), HRecordSetException );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", dbType_ },
		{ "2", "two", nullptr },
		{ "3", "three", "Mężny bądź, chroń pułk twój i sześć flag!" }
	};
	clog << "|";
	for ( int i( 0 ), COUNT( rs->get_field_count() ); i < COUNT; ++ i ) {
		HString cn( rs->get_column_name( i ) );
		cn.lower();
		ENSURE_EQUALS( "bad column name", cn, COLUMN_NAMES[i] );
		clog << cn << "|";
	}
	clog << endl;
	int row( 0 );
	for ( HRecordSet::iterator it = rs->begin(); it != rs->end(); ++ it, ++ row ) {
		clog << "|";
		int fc( rs->get_field_count() );
		for ( int i = 0; i < fc; ++ i ) {
			HRecordSet::value_t v( it[i] );
			if ( !!v ) {
				if ( dbType_ || ( row != 0 ) || ( i != 2 ) ) {
					ENSURE_EQUALS( "wrong value", *v, DATA[row][i] );
				}
			} else {
				ENSURE_EQUALS( "wrong value", static_cast<char const*>( nullptr ), DATA[row][i] );
			}
			clog << ( !v ? HString( "(nullptr)" ) : *v ) << "|";
		}
		clog << endl;
	}
	return;
	M_EPILOG
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( "SQLite engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	row_by_row_test( db, QUERY, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	char const* host( getenv( "TRESS_POSTGRESQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	row_by_row_test( db, QUERY, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	char const* host( getenv( "TRESS_MYSQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	row_by_row_test( db, QUERY, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	char const* host( getenv( "TRESS_FIREBIRD_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "localhost" );
	row_by_row_test( db, QUERY, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	row_by_row_test( db, QUERY, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

}


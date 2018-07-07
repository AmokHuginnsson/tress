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

struct tut_yaal_dbwrapper_hquery : public simple_mock<tut_yaal_dbwrapper_hquery> {
	virtual ~tut_yaal_dbwrapper_hquery( void ) {}
	void bind_test( HDataBase::ptr_t, char const* );
	void test_dml_bind( HDataBase::ptr_t, bool = false );
	void fetch_result_after_query_reset( HDataBase::ptr_t, char const* );
	void execute_twice( HDataBase::ptr_t, char const* );
};
TUT_TEST_GROUP( tut_yaal_dbwrapper_hquery, "yaal::dbwrapper::HQuery" );

void tut_yaal_dbwrapper_hquery::bind_test( HDataBase::ptr_t db, char const* dbType_ ) {
	HQuery::ptr_t q( db->prepare_query( "SELECT data FROM config WHERE id = ?;" ) );
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
TUT_UNIT_TEST( "Bind SQLite engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	bind_test( db, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "Bind PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	bind_test( db, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "Bind MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	bind_test( db, "MySQL" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "Bind Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	bind_test( db, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "Bind  Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	bind_test( db, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

void tut_yaal_dbwrapper_hquery::test_dml_bind( HDataBase::ptr_t db, bool reset_ ) {
	M_PROLOG
	char const QUERY_BIND[] = "SELECT * FROM config WHERE name = ?;";
	TUT_DECLARE( HQuery::ptr_t query( db->prepare_query( QUERY_BIND ) ); );
	TUT_INVOKE( query->bind( 1, "special" ); );
	TUT_DECLARE( HRecordSet::ptr_t rs( query->execute() ); );
	ENSURE( "empty result not entirelly empty ???", ! rs || ( rs->begin() == rs->end() ) );
	ENSURE_THROW( "recieved record count in prepared query mode", rs->get_size(), HRecordSetException );

	TUT_DECLARE( HQuery::ptr_t queryInsert( db->prepare_query( "INSERT INTO config ( name, data ) VALUES( ?, ? );" ) ); );
	TUT_INVOKE( queryInsert->bind( 1, "special" ); );
	TUT_INVOKE( queryInsert->bind( 2, "first" ); );
	TUT_INVOKE( rs = queryInsert->execute(); );
	int long lastInsertId( rs->get_insert_id() );
	clog << "lastInsertId: " << lastInsertId << endl;
	ENSURE_EQUALS( "bad last insert id", lastInsertId > 3, true );

	if ( reset_ ) {
		queryInsert.reset();
		rs.reset();
	}

	TUT_INVOKE( rs = query->execute(); );
	TUT_DECLARE( HRecordSet::HIterator it( rs->begin() ); );
	ENSURE( "record not inserted", !! rs && ( it != rs->end() ) );
	ENSURE_THROW( "recieved record count in prepared query mode", rs->get_size(), HRecordSetException );
	ENSURE( "INSERT failed?", it[1] && (*it[1] == "special" ) && it[2] && ( *it[2] == "first" ) );

	queryInsert.reset();

	TUT_DECLARE( HQuery::ptr_t queryUpdate( db->prepare_query( "UPDATE config SET data = ? WHERE name = ?;" ) ); );
	TUT_INVOKE( queryUpdate->bind( 1, "second" ); );
	TUT_INVOKE( queryUpdate->bind( 2, "special" ); );
	TUT_INVOKE( rs = queryUpdate->execute(); );
	ENSURE_EQUALS( "bad number of rows affected by UPDATE", rs->get_dml_size(), 1 );

	if ( reset_ ) {
		queryUpdate.reset();
		rs.reset();
	}

	TUT_INVOKE( rs = query->execute(); );
	TUT_INVOKE( it = rs->begin(); );
	ENSURE( "special record lost", !! rs && ( it != rs->end() ) );
	ENSURE_THROW( "recieved record count in prepared query mode", rs->get_size(), HRecordSetException );
	ENSURE( "UPDATE failed?", it[1] && ( *(it[1]) == "special" ) && it[2] && ( *(it[2]) == "second" ) );

	queryUpdate.reset();

	TUT_DECLARE( HQuery::ptr_t queryDelete( db->prepare_query( "DELETE FROM config WHERE name = ?;" ) ); );
	TUT_INVOKE( queryDelete->bind( 1, "special" ); );
	TUT_INVOKE( rs = queryDelete->execute(); );
	ENSURE_EQUALS( "bad number of rows affected by DELETE", rs->get_dml_size(), 1 );

	if ( reset_ ) {
		queryDelete.reset();
		rs.reset();
	}

	TUT_INVOKE( rs = query->execute(); );
	ENSURE( "empty result not entirelly empty ???", ! rs || ( rs->begin() == rs->end() ) );
	ENSURE_THROW( "recieved record count in prepared query mode", rs->get_size(), HRecordSetException );
	return;
	M_EPILOG
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( "dml bind on SQLite" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_dml_bind( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "dml bind on PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml_bind( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "dml bind on MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml_bind( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "dml bind on Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml_bind( db, true );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "dml bind on Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_dml_bind( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

void tut_yaal_dbwrapper_hquery::fetch_result_after_query_reset( HDataBase::ptr_t db_, char const* dbType_ ) {
	static char const* const QUERY = "SELECT * FROM config;";
	HQuery::ptr_t q( db_->prepare_query( QUERY ) );
	HRecordSet::ptr_t rs( q->execute() );
	q.reset();
	ENSURE_EQUALS( "bad column count", rs->get_field_count(), 3 );
	ENSURE_THROW( "recieved record count in row-by-row mode", rs->get_size(), HRecordSetException );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", dbType_ },
		{ "2", "two", NULL },
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
			clog << ( !v ? HString( "(NULL)" ) : *v ) << "|";
		}
		clog << endl;
	}
	ENSURE_EQUALS( "bad number of rows returned", row, yaal::size( DATA ) );
	return;
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( "fetch result after query reset: SQLite engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	fetch_result_after_query_reset( db, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "fetch result after query reset: PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	fetch_result_after_query_reset( db, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "fetch result after query reset: MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	fetch_result_after_query_reset( db, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "fetch result after query reset: Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	fetch_result_after_query_reset( db, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "fetch result after query reset: Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	fetch_result_after_query_reset( db, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

void tut_yaal_dbwrapper_hquery::execute_twice( HDataBase::ptr_t db_, char const* dbType_ ) {
	static char const* const QUERY = "SELECT * FROM config;";
	HQuery::ptr_t q( db_->prepare_query( QUERY ) );
	HRecordSet::ptr_t rs( q->execute() );
	HRecordSet::iterator drop( rs->begin() );
	*drop; ++ drop; *drop; ++ drop;
	rs.reset();
	rs = q->execute();
	ENSURE_EQUALS( "bad column count", rs->get_field_count(), 3 );
	ENSURE_THROW( "recieved record count in row-by-row mode", rs->get_size(), HRecordSetException );
	char const* const COLUMN_NAMES[] = { "id", "name", "data" };
	char const* const DATA[][3] = {
		{ "1", "one", dbType_ },
		{ "2", "two", NULL },
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
			clog << ( !v ? HString( "(NULL)" ) : *v ) << "|";
		}
		clog << endl;
	}
	ENSURE_EQUALS( "bad number of rows returned", row, yaal::size( DATA ) );
	return;
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( "execute twice: SQLite engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	execute_twice( db, "sqlite3" );
TUT_TEARDOWN()
#endif /* not defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "execute twice: PostgreSQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	execute_twice( db, "PostgreSQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "execute twice: MySQL engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	db->connect( "tress", "tress", "tr3ss" );
	execute_twice( db, "MySQL" );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "execute twice: Firebird engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	db->connect( "tress", "tress", "tr3ss" );
	execute_twice( db, "Firebird" );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "execute twice: Oracle engine" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	execute_twice( db, "Oracle" );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

TUT_UNIT_TEST( "double execute" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector() );
	db->connect( "./out/tress", "", "" );
	HQuery::ptr_t q( db->prepare_query( "SELECT * FROM config;" ) );
	HRecordSet::ptr_t rs( q->execute() );
	ENSURE_THROW( "double execute accepted", q->execute(), HQueryException );
TUT_TEARDOWN()

}


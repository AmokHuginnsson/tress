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

struct tut_yaal_dbwrapper_hdatabase : public simple_mock<tut_yaal_dbwrapper_hdatabase> {
	virtual ~tut_yaal_dbwrapper_hdatabase( void ) {}
	void test_schema( HDataBase::ptr_t, bool = false );
};
TUT_TEST_GROUP( tut_yaal_dbwrapper_hdatabase, "yaal::dbwrapper::HDatabase" );

void tut_yaal_dbwrapper_hdatabase::test_schema( HDataBase::ptr_t db_, bool extra_ ) {
	M_PROLOG
	HDataBase::table_list_t tl( db_->get_tables() );
	HDataBase::table_list_t tlExpect;
	tlExpect.push_back( "config" );
	tlExpect.push_back( "crud" );
	if ( extra_ ) {
		tlExpect.push_back( "test" );
		tlExpect.push_back( "test_dict" );
		tlExpect.push_back( "test_item" );
	}
	sort( tl.begin(), tl.end() );
	ENSURE_EQUALS( "bad table list size", tl.get_size(), tlExpect.get_size() );
	ENSURE_EQUALS( "bad table list contents", tl, tlExpect );
	HDataBase::column_list_t cl( db_->get_columns( tl[0] ) );
	ENSURE_EQUALS( "bad column list count", cl.get_size(), 3 );
	HDataBase::column_list_t clExpect;
	clExpect.push_back( "id" );
	clExpect.push_back( "name" );
	clExpect.push_back( "data" );
	ENSURE_EQUALS( "bad column list contents", cl, clExpect );
	ENSURE_THROW( "execute_query in invalid succeeded", db_->execute_query( "invalid;" ), HDataBaseException );
	clog << db_->get_error() << endl;
	return;
	M_EPILOG
}

#if defined( HAVE_SQLITE3_H )
TUT_UNIT_TEST( "sqlite3 schema" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 ) );
	db->connect( "./out/tress", "", "" );
	test_schema( db, true );
TUT_TEARDOWN()
#endif /* defined( HAVE_SQLITE3_H ) */

#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
TUT_UNIT_TEST( "PostgreSQL schema" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL ) );
	char const* host( getenv( "TRESS_POSTGRESQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */

#if defined( HAVE_MYSQL_MYSQL_H )
TUT_UNIT_TEST( "MySQL schema" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::MYSQL ) );
	char const* host( getenv( "TRESS_MYSQL_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */

#if defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H )
TUT_UNIT_TEST( "Firebird schema" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::FIREBIRD ) );
	char const* host( getenv( "TRESS_FIREBIRD_HOST" ) );
	db->connect( "tress", "tress", "tr3ss", host ? host : "localhost" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_IBASE_H ) || defined( HAVE_FIREBIRD_IBASE_H ) */

#if defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE )
TUT_UNIT_TEST( "Oracle schema" )
	HLock l( HMonitor::get_instance().acquire( "locale" ) );
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HDataBase::ptr_t db( HDataBase::get_connector( ODBConnector::DRIVER::ORACLE ) );
	db->connect( "tress", "tress", "tr3ss" );
	test_schema( db );
TUT_TEARDOWN()
#endif /* defined( HAVE_OCI_H ) && defined( HAVE_ORACLE_INSTANCE ) */

namespace {
HString gen( int no ) {
	return ( to_string( '$' ) + no );
}
}

TUT_UNIT_TEST( "transform_sql" )
	ENSURE_EQUALS( "transform_sql failed",
			transform_sql( "SELECT * FROM t WHERE a = ? AND b = '?' OR c = ? AND d = \"?\" OR f = ?;", &gen ),
			"SELECT * FROM t WHERE a = $1 AND b = '?' OR c = $2 AND d = \"?\" OR f = $3;" );
TUT_TEARDOWN()

}


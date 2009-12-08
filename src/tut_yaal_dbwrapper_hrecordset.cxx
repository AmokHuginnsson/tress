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

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_dbwrapper_hrecordset );
TUT_TEST_GROUP_N( tut_yaal_dbwrapper_hrecordset, "yaal::dbwrapper::HRecordSet" );

void dump_query_result( HDataBase::ptr_t db, char const* const query )
	{
	M_PROLOG
	HRecordSet::ptr_t rs = db->query( query );
	for ( HRecordSet::iterator it = rs->begin(); it != rs->end(); ++ it )
		{
		cout << "|";
		int fc = rs->get_field_count();
		for ( int i = 0; i < fc; ++ i )
			cout << it[ i ] << "|";
		cout << endl;
		}
	return;
	M_EPILOG
	}

static char const* const QUERY = "SELECT * FROM config;";

TUT_UNIT_TEST_N( 1, "simple query" )
	HDataBase::ptr_t db = HDataBase::get_connector();
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "different engines" )
#if defined( HAVE_SQLITE3_H )
	{
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::SQLITE3 );
	db->connect( "./out/tress", "", "" );
	dump_query_result( db, QUERY );
	}
#endif /* defined( HAVE_SQLITE3_H ) */
#if defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H )
	{
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::POSTGRESQL );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY );
	}
#endif /* defined( HAVE_POSTGRESQL_LIBPQ_FE_H ) || defined( HAVE_LIBPQ_FE_H ) */
#if defined( HAVE_MYSQL_MYSQL_H )
	{
	HDataBase::ptr_t db = HDataBase::get_connector( ODBConnector::DRIVER::MYSQL );
	db->connect( "tress", "tress", "tr3ss" );
	dump_query_result( db, QUERY );
	}
#endif /* defined( HAVE_MYSQL_MYSQL_H ) */
TUT_TEARDOWN()

}


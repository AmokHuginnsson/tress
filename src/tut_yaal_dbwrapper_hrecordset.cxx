/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
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
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace yaal::dbwrapper;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_dbwrapper_hrecordset
	{
	};

typedef test_group<tut_yaal_dbwrapper_hrecordset> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_dbwrapper_hrecordset_group( "yaal::dbwrapper::HRecordSet" );

TUT_UNIT_TEST_N( 1, "simple query" )
	static char const* const D_QUERY = "SELECT * FROM config;";
	HDataBase::ptr_t db = HDataBase::get_connector();
	db->connect( "./out/tress", "", "" );
	HRecordSet::ptr_t rs = db->query( D_QUERY );
	for ( HRecordSet::iterator it = rs->begin(); it != rs->end(); ++ it )
		{
		cout << "|";
		int fc = rs->get_field_count();
		for ( int i = 0; i < fc; ++ i )
			cout << it[ i ] << "|";
		cout << endl;
		}
TUT_TEARDOWN()

}


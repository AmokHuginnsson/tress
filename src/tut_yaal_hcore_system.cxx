/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_system.cxx - this file is integral part of `tress' project.

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
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_system );
TUT_TEST_GROUP( tut_yaal_hcore_system, "yaal::hcore::system" );

TUT_UNIT_TEST( 1, "free memory" )
	hcore::system::HResourceInfo ri( hcore::system::get_memory_size_info() );
	cout << "\nTotal memory:           " << setw( 14 ) << ri.total() << " (" << setw( 8 ) << ( ri.total() / 1024 ) << " KiB)" << " (" << setw( 5 ) << ( ri.total() / ( 1024ll * 1024ll ) ) << " MiB)" << endl;
	cout << "Free memory:            " << setw( 14 ) << ri.free() << " (" << setw( 8 ) << ( ri.free() / 1024 ) << " KiB)" << " (" << setw( 5 ) << ( ri.free() / ( 1024ll * 1024ll ) ) << " MiB)" << endl;
	cout << "Available memory:       " << setw( 14 ) << ri.available() << " (" << setw( 8 ) << ( ri.available() / 1024 ) << " KiB)" << " (" << setw( 5 ) << ( ri.available() / ( 1024ll * 1024ll ) ) << " MiB)" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "free disk space" )
	char const fspath[] = "/";
	hcore::system::HResourceInfo ri( hcore::system::get_disk_space_info( fspath ) );
	cout << "\nTotal space on `" << fspath << "':     "
		<< setw( 14 ) << ri.total()
		<< " (" << setw( 8 ) << ( ri.total() / ( 1024 * 1024 ) ) << " MiB)"
		<< " (" << setw( 5 ) << ( ri.total() / ( 1024ll * 1024ll * 1024ll ) ) << " GiB)" << endl;
	cout << "Free space on `" << fspath << "':      "
		<< setw( 14 ) << ri.free()
		<< " (" << setw( 8 ) << ( ri.free() / ( 1024 * 1024 ) ) << " MiB)"
		<< " (" << setw( 5 ) << ( ri.free() / ( 1024ll * 1024ll * 1024ll ) ) << " GiB)" << endl;
	cout << "Available space on `" << fspath << "': "
		<< setw( 14 ) << ri.available()
		<< " (" << setw( 8 ) << ( ri.available() / ( 1024 * 1024 ) ) << " MiB)"
		<< " (" << setw( 5 ) << ( ri.available() / ( 1024ll * 1024ll * 1024ll ) ) << " GiB)" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "available core count" )
	cout << "\nAvailable CPU cores: " << hcore::system::get_core_count_info() << endl;
TUT_TEARDOWN()

}


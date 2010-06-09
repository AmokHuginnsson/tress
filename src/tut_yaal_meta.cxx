/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_meta.cxx - this file is integral part of `tress' project.

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
using namespace yaal::meta;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_meta );
TUT_TEST_GROUP_N( tut_yaal_meta, "yaal::meta" );

TUT_UNIT_TEST_N( 1, "max_signed" )
	cout << "char = " << hex << static_cast<int>( max_signed<char>::value ) << endl;
	cout << "short = " << hex << max_signed<short>::value << endl;
	cout << "int = " << hex << max_signed<int>::value << endl;
	cout << "long = " << hex << max_signed<long>::value << endl;
	cout << dec;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "xor" )
	ENSURE_NOT( "xor failed", meta::boolean_xor<false, false>::value );
	ENSURE( "xor failed", meta::boolean_xor<false, true>::value );
	ENSURE( "xor failed", meta::boolean_xor<true, false>::value );
	ENSURE_NOT( "xor failed", meta::boolean_xor<true, true>::value );
TUT_TEARDOWN()

}


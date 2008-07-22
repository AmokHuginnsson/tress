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

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID( "$Id: "__ID__" $" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_tools_hash_md5
	{
	};

TUT_TEST_GROUP( tut_yaal_tools_hash_md5, "yaal::tools::hash::md5" );

TUT_UNIT_TEST( "from string" )
	static char const D_INPUT[] = "Ala ma kota";
	static char const D_HASH[] = "91162629d258a876ee994e9233b2ad87";
	ensure_equals( "bad hash", hash::md5( HBitSourceMemory( D_INPUT, sizeof ( D_INPUT ) - 1 ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from string (small alternation)" )
	static char const D_INPUT[] = "Ala ma koty";
	static char const D_HASH[] = "6a645004f620c691731b5a292c25d37f";
	ensure_equals( "bad hash", hash::md5( HBitSourceMemory( D_INPUT, sizeof ( D_INPUT ) - 1 ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from file" )
	cout << hash::md5( HBitSourceFile( "./data/karatsuba.bc" ) ) << endl;
TUT_TEARDOWN()

}


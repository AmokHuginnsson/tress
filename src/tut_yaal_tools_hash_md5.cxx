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
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;
using namespace tress;

namespace tut
{

struct tut_yaal_tools_hash_md5
	{
	};

TUT_TEST_GROUP_N( tut_yaal_tools_hash_md5, "yaal::tools::hash::md5" );

TUT_UNIT_TEST_N( 1, "original suite <0> (empty)" )
	static char const D_INPUT[] = "";
	static char const D_HASH[] = "d41d8cd98f00b204e9800998ecf8427e";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "original suite <1>" )
	static char const D_INPUT[] = "a";
	static char const D_HASH[] = "0cc175b9c0f1b6a831c399e269772661";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "original suite <2>" )
	static char const D_INPUT[] = "abc";
	static char const D_HASH[] = "900150983cd24fb0d6963f7d28e17f72";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "original suite <3>" )
	static char const D_INPUT[] = "message digest";
	static char const D_HASH[] = "f96b697d7cb7938d525a2f31aaf161d0";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "original suite <4>" )
	static char const D_INPUT[] = "abcdefghijklmnopqrstuvwxyz";
	static char const D_HASH[] = "c3fcd3d76192e4007dfb496cca67e13b";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "original suite <5>" )
	static char const D_INPUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static char const D_HASH[] = "d174ab98d277d9f5a5611c2c9f419d9f";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "original suite <6>" )
	static char const D_INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	static char const D_HASH[] = "57edf4a22be3c955ac49da2e2107b67a";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "special A for o.s.<6>" )
	static char const D_INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234";
	static char const D_HASH[] = "eb6c4179c0a7c82cc2828c1e6338e165";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "special B for o.s.<6>" )
	static char const D_INPUT[] = "123456789012345678901234567890123456789012345678901234567890123";
	static char const D_HASH[] = "c3eb67ece68488bb394241d4f6a54244";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "from string" )
	static char const D_INPUT[] = "Ala ma kota";
	static char const D_HASH[] = "91162629d258a876ee994e9233b2ad87";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "from string (small alternation)" )
	static char const D_INPUT[] = "Ala ma koty";
	static char const D_HASH[] = "6a645004f620c691731b5a292c25d37f";
	HStringStream s( D_INPUT );
	ensure_equals( "bad hash", hash::md5( s ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "from file" )
	static char const* const D_INPUT = ( setup.f_iArgc > 1 ) ? setup.f_ppcArgv[ 1 ] : "./data/karatsuba.bc";
	static char const D_HASH[] = "afc851d03c5761909554cc48d1d6c6d2";
	HFile f( D_INPUT );
	if ( setup.f_iArgc > 1 )
		cout << hash::md5( f ) << endl;
	else
		ensure_equals( "bad hash", hash::md5( f ), D_HASH );
TUT_TEARDOWN()

}


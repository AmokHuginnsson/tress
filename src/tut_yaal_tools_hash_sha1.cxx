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

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

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

struct tut_yaal_tools_hash_sha1
	{
	};

TUT_TEST_GROUP_N( tut_yaal_tools_hash_sha1, "yaal::tools::hash::sha1" );

TUT_UNIT_TEST_N( 1, "original suite <0> (empty)" )
	static char const D_INPUT[] = "";
	static char const D_HASH[] = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "original suite <1>" )
	static char const D_INPUT[] = "a";
	static char const D_HASH[] = "86f7e437faa5a7fce15d1ddcb9eaeaea377667b8";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "original suite <2>" )
	static char const D_INPUT[] = "abc";
	static char const D_HASH[] = "a9993e364706816aba3e25717850c26c9cd0d89d";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "original suite <3>" )
	static char const D_INPUT[] = "message digest";
	static char const D_HASH[] = "c12252ceda8be8994d5fa0290a47231c1d16aae3";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "original suite <4>" )
	static char const D_INPUT[] = "abcdefghijklmnopqrstuvwxyz";
	static char const D_HASH[] = "32d10c7b8cf96570ca04ce37f2a19d84240d3a89";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "original suite <5>" )
	static char const D_INPUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static char const D_HASH[] = "761c457bf73b14d27e9e9265c46f4b4dda11f940";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "original suite <6>" )
	static char const D_INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	static char const D_HASH[] = "50abf5706a150990a08b2c5ea40fa0e585554732";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "special A for o.s.<6>" )
	static char const D_INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234";
	static char const D_HASH[] = "c71490fc24aa3d19e11282da77032dd9cdb33103";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "special B for o.s.<6>" )
	static char const D_INPUT[] = "123456789012345678901234567890123456789012345678901234567890123";
	static char const D_HASH[] = "98b4b1764ea88d6c3fa63b70799dbd0c03372d1a";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "from string" )
	static char const D_INPUT[] = "Ala ma kota";
	static char const D_HASH[] = "43fd70009a97a7d311c5644047ccc700f8d08a9d";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "from string (small alternation)" )
	static char const D_INPUT[] = "Ala ma koty";
	static char const D_HASH[] = "fdc7d487efc734591715120c187909014d90135b";
	ensure_equals( "bad hash", hash::sha1( HStringStream( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "from file" )
	static char const* const D_INPUT = ( setup.f_iArgc > 1 ) ? setup.f_ppcArgv[ 1 ] : "./data/karatsuba.bc";
	static char const D_HASH[] = "a9e370f394cff1faa63cda940544a7a031d8cb88";
	if ( setup.f_iArgc > 1 )
		cout << hash::sha1( HFile( D_INPUT ) ) << endl;
	else
		ensure_equals( "bad hash", hash::sha1( HFile( D_INPUT ) ), D_HASH );
TUT_TEARDOWN()

}


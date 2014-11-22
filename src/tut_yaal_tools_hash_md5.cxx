/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hash_md5.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/tools/hash.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;
using namespace tress;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hash_md5 );
TUT_TEST_GROUP( tut_yaal_tools_hash_md5, "yaal::tools::hash::md5" );

TUT_UNIT_TEST( "original suite <0> (empty)" )
	static char const INPUT[] = "";
	static char const HASH[] = "d41d8cd98f00b204e9800998ecf8427e";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <1>" )
	static char const INPUT[] = "a";
	static char const HASH[] = "0cc175b9c0f1b6a831c399e269772661";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <2>" )
	static char const INPUT[] = "abc";
	static char const HASH[] = "900150983cd24fb0d6963f7d28e17f72";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <3>" )
	static char const INPUT[] = "message digest";
	static char const HASH[] = "f96b697d7cb7938d525a2f31aaf161d0";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <4>" )
	static char const INPUT[] = "abcdefghijklmnopqrstuvwxyz";
	static char const HASH[] = "c3fcd3d76192e4007dfb496cca67e13b";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <5>" )
	static char const INPUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static char const HASH[] = "d174ab98d277d9f5a5611c2c9f419d9f";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "original suite <6>" )
	static char const INPUT[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	static char const HASH[] = "57edf4a22be3c955ac49da2e2107b67a";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "special A for o.s.<6>" )
	static char const INPUT[] = "1234567890123456789012345678901234567890123456789012345678901234";
	static char const HASH[] = "eb6c4179c0a7c82cc2828c1e6338e165";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "special B for o.s.<6>" )
	static char const INPUT[] = "123456789012345678901234567890123456789012345678901234567890123";
	static char const HASH[] = "c3eb67ece68488bb394241d4f6a54244";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from string" )
	static char const INPUT[] = "Ala ma kota";
	static char const HASH[] = "91162629d258a876ee994e9233b2ad87";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from string (small alternation)" )
	static char const INPUT[] = "Ala ma koty";
	static char const HASH[] = "6a645004f620c691731b5a292c25d37f";
	HStringStream s( INPUT );
	ENSURE_EQUALS( "bad hash", hash::md5( s ), HASH );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from file" )
	static char const* const INPUT = ( setup._argc > 1 ) ? setup._argv[ 1 ] : "./data/karatsuba.bc";
	static char const HASH[] = "afc851d03c5761909554cc48d1d6c6d2";
	HFile f( INPUT, HFile::OPEN::READING );
	if ( setup._argc > 1 )
		cout << hash::md5( f ) << endl;
	else
		ENSURE_EQUALS( "bad hash", hash::md5( f ), HASH );
TUT_TEARDOWN()

}


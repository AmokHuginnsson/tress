/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_collections.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/collections.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::collections;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_collections );
TUT_TEST_GROUP( tut_yaal_tools_collections, "yaal::tools::collections" );

TUT_UNIT_TEST( 1, "add_orderly" )
	Stringifier stringifier;
	HList<char> l;
	add_orderly( l, 'd' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 1 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "d" );
	add_orderly( l, 'g' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 2 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "dg" );
	add_orderly( l, 'b' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 3 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "bdg" );
	add_orderly( l, 'e' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 4 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "bdeg" );
	add_orderly( l, 'c' );
	add_orderly( l, 'a' );
	add_orderly( l, 'h' );
	add_orderly( l, 'f' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 8 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "abcdefgh" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "n_th" )
	list_t l;
	l.push_back( '1' );
	l.push_back( '2' );
	l.push_back( '3' );
	l.push_back( '4' );
	l.push_back( '5' );
	l.push_back( '6' );
	for ( int i = 0; i < 6; ++ i ) {
		ENSURE_EQUALS( "n_th( n ) gives bogus result", *n_th( l, i ), i + '1' );
	}
	try {
		n_th( l, 6 );
		FAIL( "index too big and ok ??" );
	} catch ( HException& ) {
		// ok
	}
	try {
		n_th( l, -7 );
		FAIL( "index out of range and ok ??" );
	} catch ( HException& ) {
		// ok
	}
TUT_TEARDOWN()


}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hregex.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hregex.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hregex );
TUT_TEST_GROUP( tut_yaal_hcore_hregex, "yaal::hcore::HRegex" );

TUT_UNIT_TEST( 1, "empty pattern" )
	HRegex r;
	try {
		r.matches( "a" );
		FAIL( "match on unitialized regex succeeded" );
	} catch ( HRegexException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "buggy pattern (NULL) in constructor" )
	try {
		HRegex r( NULL );
	} catch ( HFailedAssertion const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "simple match" )
	HRegex r( "ala" );
	HRegex::HMatchIterator it( r.find( "xxxalayyy" ) );
	HString m( it->raw(), it->size() );
	ENSURE_EQUALS( "bad match", m, "ala" );
	ENSURE_NOT( "invalid match", r.matches( "Ala" ) );
	clog << r.error() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "ignorecase match" )
	HRegex r( "ala", HRegex::COMPILE::IGNORE_CASE );
	HRegex::HMatchIterator it( r.find( "xxxAlayyy" ) );
	HString m( it->raw(), it->size() );
	ENSURE_EQUALS( "bad match", m, "Ala" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "bad regex constructor" )
	try {
		HRegex r( "[a-z" );
		FAIL( "bad regex constucted" );
	} catch ( HRegexException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "bad regex constructor no exception" )
	HRegex r( "[a-z", HRegex::COMPILE::NO_EXCEPTION );
	try {
		r.matches( "a" );
		FAIL( "match on unitialized regex succeeded" );
	} catch ( HRegexException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

}

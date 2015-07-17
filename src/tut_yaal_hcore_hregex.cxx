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
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hregex );
TUT_TEST_GROUP( tut_yaal_hcore_hregex, "yaal::hcore::HRegex" );

TUT_UNIT_TEST( "empty pattern" )
	HRegex r;
	ENSURE_THROW( "match on unitialized regex succeeded", r.matches( "a" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "simple match" )
	HRegex r( "ala" );
	char const str[] = "xxxalayyy";
	HRegex::HMatchIterator it( r.find( str ) );
	HString m( str + it->start(), it->size() );
	ENSURE_EQUALS( "bad match", m, "ala" );
	ENSURE_NOT( "invalid match", r.matches( "Ala" ) );
	clog << r.error() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "ignorecase match" )
	HRegex r( "ala", HRegex::COMPILE::IGNORE_CASE );
	char const str[] = "xxxAlayyy";
	HRegex::HMatchIterator it( r.find( str ) );
	HString m( str + it->start(), it->size() );
	ENSURE_EQUALS( "bad match", m, "Ala" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "bad regex constructor" )
	ENSURE_THROW( "bad regex constucted", HRegex r( "[a-z" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "bad regex constructor no exception" )
	HRegex r( "[a-z", HRegex::COMPILE::NO_EXCEPTION );
	ENSURE_THROW( "match on unitialized regex succeeded", r.matches( "a" ), HRegexException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "match of empty" )
	HRegex r;
	ENSURE( "compilation of loose failed", r.compile( ".*" ) );
	ENSURE( "match of empty failed", r.matches( "" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "huginn identifier from huginn program" )
	hcore::HString identifier( YAAL_REGEX_WORD_START "[a-zA-Z_][a-zA-Z0-9_]*" YAAL_REGEX_WORD_END );
	HRegex r( identifier, HRegex::COMPILE::EXTENDED );
	char const str[] = "main() {\n\treturn( 0 );\n}\n";
	HRegex::HMatchIterator it( r.find( str ) );
	HString m( str + it->start(), it->size() );
	ENSURE_EQUALS( "bad match", m, "main" );
	clog << r.error() << endl;
TUT_TEARDOWN()

}


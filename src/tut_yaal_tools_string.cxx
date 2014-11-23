/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_string.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/stringalgo.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::string;
using namespace tress::tut_helpers;

namespace tut {

char const* const msgLevFail = "failed to calculate levenshtein distance";

TUT_SIMPLE_MOCK( tut_yaal_tools_string );
TUT_TEST_GROUP( tut_yaal_tools_string, "yaal::tools::string" );

TUT_UNIT_TEST( "levenshtein distance same strings" )
	ENSURE_EQUALS( msgLevFail,
			distance::levenshtein_damerau( "tut_yaal_tools_string", "tut_yaal_tools_string", true ), 0 );
	ENSURE_EQUALS( msgLevFail,
			distance::levenshtein_damerau( "tut_yaal_tools_string", "tut_yaal_tools_string", false ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "levenshtein distance different strings" )
	ENSURE_EQUALS( msgLevFail,
			distance::levenshtein_damerau( "ala", "ola" ), 1 );
	ENSURE_EQUALS( msgLevFail,
			distance::levenshtein_damerau( "ala", "Cola" ), 2 );
	ENSURE_EQUALS( msgLevFail,
			distance::levenshtein_damerau( "Sunday", "Saturday" ), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "split" )
	typedef HArray<HString> str_arr_t;
	str_arr_t sa( split<str_arr_t>( "Ala ma kota.", " " ) );
	ENSURE_EQUALS( "bad number of words", sa.get_size(), 3 );
	ENSURE_EQUALS( "bad word", sa[0], "Ala" );
	ENSURE_EQUALS( "bad word", sa[1], "ma" );
	ENSURE_EQUALS( "bad word", sa[2], "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "join" )
	typedef HArray<HString> str_arr_t;
	str_arr_t sa( { "Ala", "ma", "kota." } );
	ENSURE_EQUALS( "join failed", join( sa, " " ), "Ala ma kota." );
TUT_TEARDOWN()

}


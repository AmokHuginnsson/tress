/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_util_distance.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/util.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

char const* const failMsg = "failed to calculate levenshtein distance";

TUT_SIMPLE_MOCK( tut_yaal_tools_util_distance );
TUT_TEST_GROUP( tut_yaal_tools_util_distance, "yaal::tools::util::distance" );

TUT_UNIT_TEST( 1, "same strings" )
	ENSURE_EQUALS( failMsg,
			distance::levenshtein_damerau( "tut_yaal_tools_util_distance", "tut_yaal_tools_util_distance", true ), 0 );
	ENSURE_EQUALS( failMsg,
			distance::levenshtein_damerau( "tut_yaal_tools_util_distance", "tut_yaal_tools_util_distance", false ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "different strings" )
	ENSURE_EQUALS( failMsg,
			distance::levenshtein_damerau( "ala", "ola" ), 1 );
	ENSURE_EQUALS( failMsg,
			distance::levenshtein_damerau( "ala", "Cola" ), 2 );
	ENSURE_EQUALS( failMsg,
			distance::levenshtein_damerau( "Sunday", "Saturday" ), 3 );
TUT_TEARDOWN()

}

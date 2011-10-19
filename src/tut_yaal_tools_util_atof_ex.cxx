/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_util_atof_ex.cxx - this file is integral part of `tress' project.

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
#include <yaal/tools/hexpression.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_util_atof_ex );
TUT_TEST_GROUP( tut_yaal_tools_util_atof_ex, "yaal::tools::util::atof_ex" );

TUT_UNIT_TEST( 1, "complex and valid number" )
	HString formula = "2*(3+5)/sin(3.1415926535/2)";
	ENSURE_DISTANCE ( "Wrong counting.", atof_ex ( formula, true ), 16.L, 0.0001L );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "simple but invalid number" )
	HString formula = "4/e";
	try {
		atof_ex( formula, true );
	} catch ( HExpressionException& ) {
		// ok
	}
TUT_TEARDOWN()

}


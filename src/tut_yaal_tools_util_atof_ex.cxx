/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_util_atof_ex.cxx - this file is integral part of `tress' project.

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
#include "tut_helpers.h"

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

struct tut_yaal_tools_util_atof_ex
	{
	};

TUT_TEST_GROUP_N( tut_yaal_tools_util_atof_ex, "yaal::tools::util::atof_ex" );

TUT_UNIT_TEST_N( 1, "complex and valid number" )
	HString formula = "2*(3+5)/sin(3.1415926535/2)";
	ensure_distance ( "Wrong counting.", atof_ex ( formula, true ), 16.L, 0.0001L );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "simple but invalid number" )
	HString formula = "4/e";
	try
		{
		atof_ex( formula, true );
		}
	catch ( HExpressionException& )
		{
		// ok
		}
TUT_TEARDOWN()

}

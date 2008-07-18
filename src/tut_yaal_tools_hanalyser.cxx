/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hanalyser.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_hanalyser
	{
	};

typedef test_group < tut_yaal_tools_hanalyser > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_tools_hanalyser_group ( "yaal::tools::HAnalyser" );

template<>
template<>
void module::test<1>( void )
	{
	HAnalyser x;
	HString eq( "((2+3+5)*4*6*8)^2^3" );
	x.analyse( eq );
	double x1 = x.count();
	double x2 = ((2+3+5)*4*6*8);
	x2 *= x2;
	x2 *= x2;
	x2 *= x2;
	ensure_equals( "wrong computation", x1, x2 );
	cout << eq << "=" << setprecision( 20 ) << x1 << endl;
	eq = "Y";
	x.analyse( eq );
	x [ 'Y' ] = 3.;
	cout << eq << "=" << x.count() << endl;
	x [ 'Y' ] = 2.;
	cout << eq << "=" << x.count() << endl;
	eq = "7+10+(4*)";
	x.analyse( eq );
	}

}


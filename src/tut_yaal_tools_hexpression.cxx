/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hanalyser.cxx - this file is integral part of `tress' project.

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

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_tools_hanalyser );
TUT_TEST_GROUP( tut_yaal_tools_hanalyser, "yaal::tools::HExpression" );

TUT_UNIT_TEST( 1, "complex and valid expression" )
	HExpression x;
	HString eq( "(((2+3+5)*4*6*8)/123)^2^3" );
	x.compile( eq );
	double long x1 = x.evaluate();
	double long x2 = ((2.+3.+5.)*4.*6.*8.)/123.;
	x2 *= x2;
	x2 *= x2;
	x2 *= x2;
	ENSURE_DISTANCE( "wrong computation", x1, x2, static_cast<double long>( 0.00001 ) );
	std::cout << eq << "=" << std::setprecision( 20 ) << x1 << std::endl;
	eq = "Y";
	x.compile( eq );
	x [ 'Y' ] = 3.;
	cout << eq << "=" << x.evaluate() << endl;
	x [ 'Y' ] = 2.;
	cout << eq << "=" << x.evaluate() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "invalid expression" )
	try
		{
		HString eq( "7+10+(4*)" );
		HExpression x;
		x.compile( eq );
		FAIL( "parsing invalid expression succeded" );
		}
	catch ( HExpressionException& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy semantics" )
	static int const MAGIC = 7;
	static int const SPOOKY = 13;
	HExpression e( "1" );
	double long* v = e.variables();
	v[ 0 ] = MAGIC;
	HExpression e2( e );
	v = e2.variables();
	e[ 0 ] = SPOOKY;
	ENSURE_EQUALS( "variables not copied", v[ 0 ], MAGIC );
	e2 = e;
	ENSURE_EQUALS( "variables not copied", v[ 0 ], SPOOKY );
TUT_TEARDOWN()

}


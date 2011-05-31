/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hvector.cxx - this file is integral part of `tress' project.

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
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_hcore_hvector );
TUT_TEST_GROUP( tut_yaal_hcore_hvector, "yaal::hcore::HVector" );

TUT_UNIT_TEST( 1, "basic vector operations" )
	HVector<double> v( 3 );
	HVector<double> w( 3 );
	std::cout << "<<< vector >>>" << std::endl;
	v[ 0 ] = 1.2;	v[ 1 ] = 2.4; v[ 2 ] = 3.5;
	w[ 0 ] = 4.7;	w[ 1 ] = 5.1; w[ 2 ] = 6.6;
	std::cout << "    v = " << v << std::endl;
	std::cout << "    w = " << w << std::endl;
	std::cout << "v + w = " << v + w << std::endl;
	std::cout << "v * 2 = " << v * 2. << std::endl;
	std::cout << "3 * w = " << 3. * w << std::endl;
	std::cout << "w - v = " << w - v << std::endl;
	std::cout << "w / 2 = " << w / 2. << std::endl;
	std::cout << "  ! v = " << ! v << std::endl;
	std::cout << "v | w = " << ( v | w ) << std::endl;
	std::cout << "  - v = " << - v << std::endl;
TUT_TEARDOWN()

}


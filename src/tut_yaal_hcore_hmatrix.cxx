/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hmatrix.cxx - this file is integral part of `tress' project.

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

TUT_SIMPLE_MOCK( tut_yaal_hcore_hmatrix );
TUT_TEST_GROUP_N( tut_yaal_hcore_hmatrix, "yaal::hcore::HMatrix" );

template<>
template<>
void module::test<1> ( void )
	{
	HMatrix < double > V ( 3, 3 );
	HMatrix < double > W ( 3, 3 );
	HMatrix < double > X ( 2, 2 );
	std::cout << "<<< matrix >>>" << std::endl;
	V [ 0 ] [ 0 ] = 1.2, V [ 0 ] [ 1 ] = 2.3, V [ 0 ] [ 2 ] = 3.4;
	V [ 1 ] [ 0 ] = 4.3, V [ 1 ] [ 1 ] = 3.2, V [ 1 ] [ 2 ] = 2.1;
	V [ 2 ] [ 0 ] = 2.4, V [ 2 ] [ 1 ] = 5.6, V [ 2 ] [ 2 ] = 7.7;
	X [ 0 ] [ 0 ] = 1.2, X [ 0 ] [ 1 ] = 2.3;
	X [ 1 ] [ 0 ] = 4.3, X [ 1 ] [ 1 ] = 3.2;
	W = V;
	W *= 2;
	std::cout << "V = ..." << std::endl << V << std::endl;
	std::cout << "W = ..." << std::endl << W << std::endl;
	std::cout << "V + W = ..." << std::endl << V + W << std::endl;
	std::cout << "X = ..." << std::endl << X << std::endl;
	std::cout << "X ^ - 1 = ..." << std::endl << X._1 ( ) << std::endl;
	std::cout << "X * X ^ - 1 = ..." << std::endl << X * X._1 ( ) << std::endl;
	std::cout << "V ^ - 1 = ..." << std::endl << V._1 ( ) << std::endl;
	std::cout << "V * V ^ - 1 = ..." << std::endl << V * V._1 ( ) << std::endl;
	}

}


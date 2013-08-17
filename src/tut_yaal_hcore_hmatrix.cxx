/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hmatrix.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hmatrix.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hmatrix );
TUT_TEST_GROUP( tut_yaal_hcore_hmatrix, "yaal::hcore::HMatrix" );

TUT_UNIT_TEST( 1, "basic matrix operations" )
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
TUT_TEARDOWN()

}


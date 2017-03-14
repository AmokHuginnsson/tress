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

TUT_UNIT_TEST( "matrix determinant, non-triwial row swap" )
	HMatrix<double long> m( 3, 3 );
	m[0][2] = m[1][0] = m[1][1] = m[2][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 1", m.det(), -1.L, epsilon );
	m[0][2] = m[1][0] = m[1][1] = m[2][0] = 0.;
	m[0][2] = m[2][0] = m[2][1] = m[1][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 2", m.det(), 1.L, epsilon );
	m[0][2] = m[2][0] = m[2][1] = m[1][0] = 0.;
	m[1][2] = m[0][0] = m[0][1] = m[2][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 3", m.det(), 1.L, epsilon );
	m[1][2] = m[0][0] = m[0][1] = m[2][0] = 0.;
	m[1][2] = m[2][0] = m[2][1] = m[0][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 4", m.det(), -1.L, epsilon );
	m[1][2] = m[2][0] = m[2][1] = m[0][0] = 0.;
	m[2][2] = m[0][0] = m[0][1] = m[1][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 5", m.det(), -1.L, epsilon );
	m[2][2] = m[0][0] = m[0][1] = m[1][0] = 0.;
	m[2][2] = m[1][0] = m[1][1] = m[0][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 6", m.det(), 1.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "inverse" )
	HMatrix<double long> m( 5, 5 );
	double long const data[][5] = {
		{  6, 13, -10, -3,  4 },
		{ 12, -6,  -4,  3,  5 },
		{ -7, -5,   2,  9, 11 },
		{ -1,  1,   8, 10, -8 },
		{  0,  7,  14, -9, -2 }
	};
	for ( int r( 0 ); r < 5; ++ r ) {
		for ( int c( 0 ); c < 5; ++ c ) {
			m[r][c] = data[r][c];
		}
	}
	ENSURE_DISTANCE( "det failed", m.det(), 780000.L, epsilon );
	double long const res[][5] = {
		{  0.011987,  0.068077, -0.018462,  0.018077,  0.020321 },
		{  0.060064, -0.020385,  0.012308,  0.029615,  0.018397 },
		{ -0.013333,  0.020000,  0.020000,  0.020000,  0.053333 },
		{  0.021603,  0.010385,  0.027692,  0.060385, -0.020064 },
		{  0.019679,  0.021923,  0.058462, -0.028077,  0.028013 }
	};
	HMatrix<double long> im( m._1() );
	for ( int r( 0 ); r < 5; ++ r ) {
		for ( int c( 0 ); c < 5; ++ c ) {
			ENSURE_DISTANCE( "inverse failed", im[r][c], res[r][c], epsilon );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "basic matrix operations" )
	HMatrix<double> V( 3, 3 );
	HMatrix<double> W( 3, 3 );
	HMatrix<double> X( 2, 2 );
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


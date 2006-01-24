/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_stdhapi_hcore_hmatrix.c - this file is integral part of `tress' project.

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

#include "TUT/tut.h"

#include <stdhapi.h>
M_CVSID ( "$CVSHeader$" )

#include "tut_helpers.h"

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

namespace tut
{

struct tut_stdhapi_hcore_hmatrix
	{
	};

typedef test_group < tut_stdhapi_hcore_hmatrix > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_hcore_hmatrix_group ( "stdhapi::hcore::HMatrix" );

template < >
template < >
void module::test<1> ( void )
	{
	HMatrix < double > V ( 3, 3 );
	HMatrix < double > W ( 3, 3 );
	HMatrix < double > X ( 2, 2 );
	cout << "<<< matrix >>>" << endl;
	V [ 0 ] [ 0 ] = 1.2, V [ 0 ] [ 1 ] = 2.3, V [ 0 ] [ 2 ] = 3.4;
	V [ 1 ] [ 0 ] = 4.3, V [ 1 ] [ 1 ] = 3.2, V [ 1 ] [ 2 ] = 2.1;
	V [ 2 ] [ 0 ] = 2.4, V [ 2 ] [ 1 ] = 5.6, V [ 2 ] [ 2 ] = 7.7;
	X [ 0 ] [ 0 ] = 1.2, X [ 0 ] [ 1 ] = 2.3;
	X [ 1 ] [ 0 ] = 4.3, X [ 1 ] [ 1 ] = 3.2;
	W = V;
	W *= 2;
	cout << "V = ..." << endl << V << endl;
	cout << "W = ..." << endl << W << endl;
	cout << "V + W = ..." << endl << V + W << endl;
	cout << "X = ..." << endl << X << endl;
	cout << "X ^ - 1 = ..." << endl << X._1 ( ) << endl;
	cout << "X * X ^ - 1 = ..." << endl << X * X._1 ( ) << endl;
	cout << "V ^ - 1 = ..." << endl << V._1 ( ) << endl;
	cout << "V * V ^ - 1 = ..." << endl << V * V._1 ( ) << endl;
	}

}


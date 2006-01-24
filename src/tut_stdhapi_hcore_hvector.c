/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_stdhapi_hcore_hvector.c - this file is integral part of `tress' project.

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

struct tut_stdhapi_hcore_hvector
	{
	};

typedef test_group < tut_stdhapi_hcore_hvector > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_hcore_hvector_group ( "stdhapi::hcore::HVector" );

template < >
template < >
void module::test<1> ( void )
	{
	HVector < double > v ( 3 );
	HVector < double > w ( 3 );
	cout << "<<< vector >>>" << endl;
	v [ 0 ] = 1.2;	v [ 1 ] = 2.4; v [ 2 ] = 3.5;
	w [ 0 ] = 4.7;	w [ 1 ] = 5.1; w [ 2 ] = 6.6;
	cout << "    v = " << v << endl;
	cout << "    w = " << w << endl;
	cout << "v + w = " << v + w << endl;
	cout << "v * 2 = " << v * 2. << endl;
	cout << "3 * w = " << 3. * w << endl;
	cout << "w - v = " << w - v << endl;
	cout << "w / 2 = " << w / 2. << endl;
	cout << "  ! v = " << ! v << endl;
	cout << "v | w = " << ( v | w ) << endl;
	cout << "  - v = " << - v << endl;
	}

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_stdhapi_hcore_hcomplex.c - this file is integral part of `tress' project.

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

#include "tut_helpers.h"

#include "TUT/tut.h"

#include <stdhapi.h>

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

namespace tut
{

struct tut_stdhapi_hcore_hcomplex
	{
	};

typedef test_group < tut_stdhapi_hcore_hcomplex > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_hcore_hcomplex_group ( "stdhapi::hcore::HComplex" );

template < >
template < >
void module::test<1> ( void )
	{
	HComplex a ( 1., 3. );
	HComplex b ( 2., 1. );
	HComplex c ( 4, 8. );
	cout << "<<< complex >>>" << endl;
	cout << "        a = " << a << endl;
	cout << "        b = " << b << endl;
	cout << "        c = " << c << endl;
	cout << "    c / c = " << c / c << endl;
	cout << "    a + b = " << a + b << endl;
	cout << "c = a / b = " << ( c = a / b ) << endl;
	cout << "    c * b = " << c * b << endl;
	cout << "      - a = " << - a << endl;
	}

}


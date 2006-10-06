/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hstring.cxx - this file is integral part of `tress' project.

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
M_VCSID ( "$Id$" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hstring
	{
	};

typedef test_group < tut_yaal_hcore_hstring > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hstring_group ( "yaal::hcore::HString" );

template < >
template < >
void module::test<1> ( void )
	{
	HString str ( 1024 );
	HString exemplar ( "1024" );
	ensure_equals ( "construction from int or c-string does not work", str, exemplar );
	}

/* shift_left */
template < >
template < >
void module::test<2> ( void )
	{
	HString str ( "Ala ma kota" );
	HString exemplar ( "ma kota" );
	str.shift_left ( 4 );
	ensure_equals ( "left_shift failed", str, exemplar );
	try
		{
		str.shift_left ( - 1 );
		fail ( "no check for negative shift" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	str.shift_left ( 100000 );
	exemplar = "";
	ensure_equals ( "left_shift failed", str, exemplar );
	}

/* shift_right */
template < >
template < >
void module::test<3> ( void )
	{
	HString str ( "Ala ma kota" );
	HString exemplar ( "    Ala ma kota" );
	str.shift_right ( 4 );
	ensure_equals ( "right_shift failed", str, exemplar );
	try
		{
		str.shift_right ( - 1 );
		fail ( "no check for negative shift" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

}


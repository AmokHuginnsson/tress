/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_lambda.cxx - this file is integral part of `tress' project.

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

TUT_SIMPLE_MOCK( tut_yaal_tools_lambda );
TUT_TEST_GROUP_N( tut_yaal_tools_lambda, "yaal::tools::lambda" );

TUT_UNIT_TEST_N( 1, "streams" )
	int a[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
	int_list_t l( a, a + countof ( a ) );
	for_each( l.begin(), l.end(), cout << *_1 << endl );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "plus" )
	int a[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
	int_list_t l( a, a + countof ( a ) );
	transform( l.begin(), l.end(), stream_iterator( cout, " " ), 1 + _1 );
	transform( l.begin(), l.end(), stream_iterator( cout, " " ), _1 + 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "plus both args are free" )
	cout << ( _1 + _2 )( 3, 4 ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "plus both args are free, one integral, one floating point" )
	cout << ( _1 + _2 )( 3.14, 4 ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "plus both args are free, at least one floating point, but we force return type" )
	cout << ret<int>( _1 + _2 )( 3.14, 4 ) << endl;
TUT_TEARDOWN()

}

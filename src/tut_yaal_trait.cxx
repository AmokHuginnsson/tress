/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_.cxx - this file is integral part of `tress' project.

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
using namespace yaal::trait;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_trait
	{
	virtual ~tut_yaal_trait( void ) {}
	};

TUT_TEST_GROUP_N( tut_yaal_trait, "yaal::trait" );

TUT_UNIT_TEST_N( 1, "same stype" )
	ensure( "int, int", same_type<int, int>::value );
	ensure_not( "int, int const", same_type<int, int const>::value );
	ensure_not( "int, int*", same_type<int, int*>::value );
	ensure_not( "int, int&", same_type<int, int&>::value );
	ensure_not( "int, int short", same_type<int, int short>::value );
	ensure( "int (char, double), int (char, double)", same_type<int (char, double), int (char, double)>::value );
	ensure_not( "int (char, double), int (char, double long)", same_type<int (*)(char, double), int (*)(char, double long)>::value );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "return type" )
	ensure( "int, int (char, double)", same_type<int, return_type<int (*)(char, double)>::type>::value );
	ensure( "int*, int* (char, double)", same_type<int*, return_type<int* (*)(char, double)>::type>::value );
	ensure_not( "int*, int (char, double)", same_type<int*, return_type<int (*)(char, double)>::type>::value );
	ensure_not( "int, int* (char, double)", same_type<int, return_type<int* (*)(char, double)>::type>::value );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "count types" )
	ensure_equals( "type count is wrong", count_type<int, char, double, int, float, int, void*>::value, 2 );
TUT_TEARDOWN()

}


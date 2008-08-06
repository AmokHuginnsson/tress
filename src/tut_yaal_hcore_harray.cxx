/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

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
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.h"

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

struct tut_stahapi_hcore_harray
	{
	};

typedef test_group < tut_stahapi_hcore_harray > tut_group;
typedef tut_group::object module;
tut_group tut_group_group ( "yaal::hcore::HArray" );

/* Constructor. */
template<>
template<>
void module::test<1> ( void )
	{
	int const BAD_SIZE = - 1;
	try
		{
		HArray<int> l_oArray ( BAD_SIZE );
		fail ( "array with negative size created" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Constructor and get_size(). */
template<>
template<>
void module::test<2> ( void )
	{
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	HArray<int> l_oOne ( SIZE_FOR_ONE );
	ensure_equals ( "inconsistient size with respect to constructor", l_oOne.get_size ( ), SIZE_FOR_ONE );
	HArray<int> l_oTwo ( SIZE_FOR_TWO );
	ensure_equals ( "inconsistient size with respect to constructor", l_oTwo.get_size ( ), SIZE_FOR_TWO );
	}

/* Constructor with filling. */
template<>
template<>
void module::test<3> ( void )
	{
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	try
		{
		HArray<int> l_oBadArray ( BAD_SIZE, FILLER_FOR_ARRAY );
		fail ( "array with negative size created" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	HArray<int> l_oArray ( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ensure_equals ( "array element not filled with default value", l_oArray [ i ], FILLER_FOR_ARRAY );
	}

/* Copy constructor. */
template<>
template<>
void module::test<4> ( void )
	{
	int const SIZE = 7;
	HArray<int> l_oArray ( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		l_oArray [ i ] = i;
	HArray<int> l_oCopy ( l_oArray );
	ensure_equals ( "inconsistient size after copy constructor", l_oCopy.get_size ( ), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ensure_equals ( "wrong content after copy constructor", l_oCopy [ i ], i );
	}

/* Operator [ ]. */
template<>
template<>
void module::test<5> ( void )
	{
	int const SIZE = 7;
	HArray<int> l_oArray ( SIZE );
	try
		{
		l_oArray [ SIZE ] = 0;
		fail ( "access beyond size succed" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	try
		{
		l_oArray [ - SIZE - 1 ] = 0;
		fail ( "access with negative index succed" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Operator bool. */
template<>
template<>
void module::test<6> ( void )
	{
	int const EMPTY = 0;
	int const SIZE = 7;
	HArray<int> l_oEmpty ( EMPTY );
	ensure_equals ( "test for array emptiness faild", ! l_oEmpty, true );
	HArray<int> l_oNormal ( SIZE );
	ensure_equals ( "test for array fullness faild", ! l_oNormal, false );
	}

}

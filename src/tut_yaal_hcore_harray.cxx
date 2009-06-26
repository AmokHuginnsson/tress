/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_stahapi_hcore_harray.cxx - this file is integral part of `tress' project.

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

TUT_SIMPLE_MOCK( tut_stahapi_hcore_harray );
TUT_TEST_GROUP_N( tut_stahapi_hcore_harray, "yaal::hcore::HArray" );

TUT_UNIT_TEST_N( 1, "/* Constructor. */" )
	int const BAD_SIZE = - 1;
	try
		{
		HArray<int> l_oArray ( BAD_SIZE );
		FAIL ( "array with negative size created" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Constructor and get_size(). */" )
	int const SIZE_FOR_ONE = 0;
	int const SIZE_FOR_TWO = 7;
	HArray<int> l_oOne ( SIZE_FOR_ONE );
	ENSURE_EQUALS ( "inconsistient size with respect to constructor", l_oOne.get_size ( ), SIZE_FOR_ONE );
	HArray<int> l_oTwo ( SIZE_FOR_TWO );
	ENSURE_EQUALS ( "inconsistient size with respect to constructor", l_oTwo.get_size ( ), SIZE_FOR_TWO );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Constructor with filling. */" )
	int const BAD_SIZE = - 1;
	int const SIZE_FOR_ARRAY = 7;
	int const FILLER_FOR_ARRAY = 13;
	try
		{
		HArray<int> l_oBadArray ( BAD_SIZE, FILLER_FOR_ARRAY );
		FAIL ( "array with negative size created" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	HArray<int> l_oArray ( SIZE_FOR_ARRAY, FILLER_FOR_ARRAY );
	for ( int i = 0; i < SIZE_FOR_ARRAY; ++ i )
		ENSURE_EQUALS ( "array element not filled with default value", l_oArray [ i ], FILLER_FOR_ARRAY );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Copy constructor. */" )
	int const SIZE = 7;
	HArray<int> l_oArray ( SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		l_oArray [ i ] = i;
	HArray<int> l_oCopy ( l_oArray );
	ENSURE_EQUALS ( "inconsistient size after copy constructor", l_oCopy.get_size ( ), SIZE );
	for ( int i = 0; i < SIZE; ++ i )
		ENSURE_EQUALS ( "wrong content after copy constructor", l_oCopy [ i ], i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Operator [ ]. */" )
	int const SIZE = 7;
	HArray<int> l_oArray ( SIZE );
	try
		{
		l_oArray [ SIZE ] = 0;
		FAIL ( "access beyond size succed" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	try
		{
		l_oArray [ - SIZE - 1 ] = 0;
		FAIL ( "access with negative index succed" );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Operator bool. */" )
	int const EMPTY = 0;
	int const SIZE = 7;
	HArray<int> l_oEmpty ( EMPTY );
	ENSURE_EQUALS ( "test for array emptiness faild", ! l_oEmpty, true );
	HArray<int> l_oNormal ( SIZE );
	ENSURE_EQUALS ( "test for array fullness faild", ! l_oNormal, false );
TUT_TEARDOWN()

}

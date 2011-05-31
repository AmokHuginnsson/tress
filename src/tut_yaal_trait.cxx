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
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_trait );
TUT_TEST_GROUP( tut_yaal_trait, "yaal::trait" );

TUT_UNIT_TEST( 1, "same stype" )
	ENSURE( "int, int", same_type<int, int>::value );
	ENSURE_NOT( "int, int const", same_type<int, int const>::value );
	ENSURE_NOT( "int, int*", same_type<int, int*>::value );
	ENSURE_NOT( "int, int&", same_type<int, int&>::value );
	ENSURE_NOT( "int, int short", same_type<int, int short>::value );
	ENSURE( "int (char, double), int (char, double)", same_type<int (char, double), int (char, double)>::value );
	ENSURE_NOT( "int (char, double), int (char, double long)", same_type<int (*)(char, double), int (*)(char, double long)>::value );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "return type" )
	ENSURE( "int, int (char, double)", same_type<int, return_type<int (*)(char, double)>::type>::value );
	ENSURE( "int*, int* (char, double)", same_type<int*, return_type<int* (*)(char, double)>::type>::value );
	ENSURE_NOT( "int*, int (char, double)", same_type<int*, return_type<int (*)(char, double)>::type>::value );
	ENSURE_NOT( "int, int* (char, double)", same_type<int, return_type<int* (*)(char, double)>::type>::value );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "count types" )
	ENSURE_EQUALS( "type count is wrong", count_type<int, char, double, int, float, int, void*>::value, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "ref vs const" )
	cout << trait::is_reference<int&>::value << endl;
	cout << trait::is_reference<int*&>::value << endl;
	cout << trait::is_reference<int const&>::value << endl;
	cout << trait::is_reference<int const*&>::value << endl;
	cout << trait::is_reference<int* const&>::value << endl;
	cout << trait::is_reference<int* const*&>::value << endl << endl;

	cout << trait::is_reference<trait::strip_reference<int&>::type>::value << endl;
	cout << trait::is_reference<trait::strip_reference<int*&>::type>::value << endl;
	cout << trait::is_reference<trait::strip_reference<int const&>::type>::value << endl;
	cout << trait::is_reference<trait::strip_reference<int const*&>::type>::value << endl;
	cout << trait::is_reference<trait::strip_reference<int* const&>::type>::value << endl;
	cout << trait::is_reference<trait::strip_reference<int* const*&>::type>::value << endl;

	typedef trait::make_const_ref_ptr<trait::strip_reference<int&>::type>::type T1;
	typedef trait::make_const_ref_ptr<trait::strip_reference<int*&>::type>::type T2;
	typedef trait::make_const_ref_ptr<trait::strip_reference<int const&>::type>::type T3;
	typedef trait::make_const_ref_ptr<trait::strip_reference<int const*&>::type>::type T4;
	typedef trait::make_const_ref_ptr<trait::strip_reference<int* const&>::type>::type T5;
	typedef trait::make_const_ref_ptr<trait::strip_reference<int* const*&>::type>::type T6;
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "arg type deduction on functional functors :)" )
	cout << trait::same_type<trait::argument_type<less<int>, 0>::type, int>::value << endl;
	cout << trait::same_type<trait::argument_type<less<int>, 1>::type, int>::value << endl;
	cout << trait::same_type<trait::argument_type<less<int>, 0>::type, double>::value << endl;
	cout << trait::same_type<trait::argument_type<less<int>, 1>::type, double>::value << endl;
	cout << "neg " << trait::same_type<trait::argument_type<negate<int>, 0>::type, int>::value << endl;
	cout << "neg " << trait::same_type<trait::argument_type<negate<int>, 3>::type, int>::value << endl;
	cout << "binary " << trait::same_type<trait::argument_type<binary_function<bool, int, double>, 0>::type, int>::value << endl;
	cout << "binary " << trait::same_type<trait::argument_type<binary_function<bool, int, double>, 1>::type, double>::value << endl;
	cout << "binary composition " << trait::same_type<trait::argument_type<binary_composition<plus<int>, negate<int>, negate<int> >, 0>::type, int >::value << endl;
	cout << "binary composition " << trait::same_type<trait::argument_type<binary_composition<plus<int>, negate<int>, negate<int> >, 1>::type, int >::value << endl;
TUT_TEARDOWN()

}


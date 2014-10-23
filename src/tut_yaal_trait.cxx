/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/trait.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::trait;
using namespace yaal::hcore;
using namespace tress::tut_helpers;

namespace tut {

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

TUT_UNIT_TEST( 4, "is_reference" )
	ENSURE( trait::is_reference<int&>::value == true );
	ENSURE( trait::is_reference<int*&>::value == true );
	ENSURE( trait::is_reference<int const&>::value == true );
	ENSURE( trait::is_reference<int const*&>::value == true );
	ENSURE( trait::is_reference<int* const&>::value == true );
	ENSURE( trait::is_reference<int* const*&>::value == true );

	ENSURE( trait::is_reference<trait::strip_reference<int&>::type>::value == false );
	ENSURE( trait::is_reference<trait::strip_reference<int*&>::type>::value == false );
	ENSURE( trait::is_reference<trait::strip_reference<int const&>::type>::value == false );
	ENSURE( trait::is_reference<trait::strip_reference<int const*&>::type>::value == false );
	ENSURE( trait::is_reference<trait::strip_reference<int* const&>::type>::value == false );
	ENSURE( trait::is_reference<trait::strip_reference<int* const*&>::type>::value == false );

	/* rest is just compilability test */
	typedef trait::make_const_ref_ptr<trait::strip_reference<int&>::type>::type T1 __attribute__((unused));
	typedef trait::make_const_ref_ptr<trait::strip_reference<int*&>::type>::type T2 __attribute__((unused));
	typedef trait::make_const_ref_ptr<trait::strip_reference<int const&>::type>::type T3 __attribute__((unused));
	typedef trait::make_const_ref_ptr<trait::strip_reference<int const*&>::type>::type T4 __attribute__((unused));
	typedef trait::make_const_ref_ptr<trait::strip_reference<int* const&>::type>::type T5 __attribute__((unused));
	typedef trait::make_const_ref_ptr<trait::strip_reference<int* const*&>::type>::type T6 __attribute__((unused));
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "is_pointer" )
	ENSURE( trait::is_pointer<int*>::value == true );
	ENSURE( trait::is_pointer<int const*>::value == true );
	ENSURE( trait::is_pointer<int* const*>::value == true );

	ENSURE( trait::is_pointer<int&>::value == false );
	ENSURE( trait::is_pointer<int const&>::value == false );
	ENSURE( trait::is_pointer<int* const&>::value == false );

	ENSURE( trait::is_pointer<trait::strip_pointer<int*>::type>::value == false );
	ENSURE( trait::is_pointer<trait::strip_pointer<int const*>::type>::value == false );
	ENSURE( trait::is_pointer<trait::strip_pointer<int* const*>::type>::value == true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "is_const" )
	ENSURE( trait::is_const<int const>::value == true );
	ENSURE( trait::is_const<int const&>::value == true );
	ENSURE( trait::is_const<int const* const>::value == true );
	ENSURE( trait::is_const<int>::value == false );
	ENSURE( trait::is_const<int const*>::value == false );
	ENSURE( trait::is_const<int*>::value == false );
	ENSURE( trait::is_const<int&>::value == false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "is_array" )
	typedef int arr_t[3];
	typedef int const arr_const_t[3];
	typedef int* int_ptr_t;
	ENSURE( trait::is_array<arr_t>::value == true );
	ENSURE( trait::is_array<arr_const_t>::value == true );
	ENSURE( trait::is_array<int_ptr_t>::value == false );
	ENSURE( trait::is_array<int>::value == false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "arg type deduction on functional functors :)" )
	ENSURE( trait::same_type<trait::argument_type<less<int>, 0>::type, int>::value == true );
	ENSURE( trait::same_type<trait::argument_type<less<int>, 1>::type, int>::value == true );
	ENSURE( trait::same_type<trait::argument_type<less<int>, 0>::type, double>::value == false );
	ENSURE( trait::same_type<trait::argument_type<less<int>, 1>::type, double>::value == false );
	ENSURE( trait::same_type<trait::argument_type<negate<int>, 0>::type, int>::value == true );
	ENSURE( trait::same_type<trait::argument_type<negate<int>, 3>::type, int>::value == false );
	ENSURE( trait::same_type<trait::argument_type<negate<int>, 3>::type, trait::no_type>::value == true );
	ENSURE( trait::same_type<trait::argument_type<binary_function<bool, int, double>, 0>::type, int>::value == true );
	ENSURE( trait::same_type<trait::argument_type<binary_function<bool, int, double>, 1>::type, double>::value == true );
	ENSURE( trait::same_type<trait::argument_type<binary_composition<plus<int>, negate<int>, negate<int> >, 0>::type, int>::value == true );
	ENSURE( trait::same_type<trait::argument_type<binary_composition<plus<int>, negate<int>, negate<int> >, 1>::type, int>::value == true );
TUT_TEARDOWN()

}


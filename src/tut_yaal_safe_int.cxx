/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_safe_int.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/safe_int.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_safe_int );
TUT_TEST_GROUP( tut_yaal_safe_int, "yaal::safe_int" );


TUT_UNIT_TEST( "add" )
	ENSURE_EQUALS( +safe_int::add<char signed>( 1, 2 ), 3 );
	ENSURE_EQUALS( +safe_int::add<char signed>( -1, -2 ), -3 );
	ENSURE_EQUALS( +safe_int::add<char signed>( 1, -2 ), -1 );
	ENSURE_EQUALS( +safe_int::add<char signed>( -2, 1 ), -1 );
	ENSURE_THROW_AUTO( safe_int::add<char signed>( 110, 110 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::add<char signed>( -110, -110 ), HOutOfRangeException );
	ENSURE_EQUALS( +safe_int::add<char unsigned>( 1, 2 ), 3 );
	ENSURE_THROW_AUTO( safe_int::add<char unsigned>( 140, 130 ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sub" )
	ENSURE_EQUALS( +safe_int::sub<char signed>( 2, 1 ), 1 );
	ENSURE_EQUALS( +safe_int::sub<char signed>( -2, 1 ), -3 );
	ENSURE_EQUALS( +safe_int::sub<char signed>( 1, -2 ), 3 );
	ENSURE_EQUALS( +safe_int::sub<char signed>( -1, -2 ), 1 );
	ENSURE_THROW_AUTO( safe_int::sub<char signed>( -100, 100 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::sub<char signed>( 100, -100 ), HOutOfRangeException );
	ENSURE_EQUALS( +safe_int::sub<char unsigned>( 2, 1 ), 1 );
	ENSURE_THROW_AUTO( safe_int::sub<char unsigned>( 1, 2 ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mul" )
	ENSURE_EQUALS( +safe_int::mul<char signed>( 2, 3 ), 6 );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( 22, 33 ), HOutOfRangeException );
	ENSURE_EQUALS( +safe_int::mul<char signed>( -2, 3 ), -6 );
	ENSURE_EQUALS( +safe_int::mul<char signed>( -2, -3 ), 6 );
	ENSURE_EQUALS( +safe_int::mul<char signed>( 2, -3 ), -6 );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( -22, -33 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( -22, 33 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( 22, -33 ), HOutOfRangeException );
	ENSURE_EQUALS( safe_int::mul<char unsigned>( 2, 3 ), 6 );
	ENSURE_THROW_AUTO( safe_int::mul<char unsigned>( 22, 33 ), HOutOfRangeException );
TUT_TEARDOWN()

}


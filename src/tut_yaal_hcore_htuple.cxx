/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_htuple.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/htuple.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/tools/streamtools.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_htuple );
TUT_TEST_GROUP( tut_yaal_hcore_htuple, "yaal::hcore::HTuple" );

TUT_UNIT_TEST( "constructor" )
	typedef HTuple<int, HString, HNumber, void*, HTime> tuple_t;
	tuple_t t( 7, "Ala ma kota", 3.141592653589793, NULL, HTime::TZ::LOCAL );
	ENSURE_EQUALS( "tuple val[0] failed", t.get<0>(), 7 );
	ENSURE_EQUALS( "tuple val[1] failed", t.get<1>(), "Ala ma kota" );
	ENSURE_EQUALS( "tuple val[2] failed", t.get<2>(), 3.141592653589793 );
	ENSURE_EQUALS( "tuple val[3] failed", t.get<3>(), static_cast<void*>( NULL ) );
	ENSURE_EQUALS( "tuple val[4] failed", t.get<4>(), HTime::TZ::LOCAL );
TUT_TEARDOWN()

TUT_UNIT_TEST( "make_tuple" )
	typedef HTuple<int, HString, HNumber, void*, HTime> tuple_t;
	tuple_t t( make_tuple<int, HString, HNumber, void*, HTime>( 7, "Ala ma kota", 3.141592653589793, NULL, HTime::TZ::LOCAL ) );
	ENSURE_EQUALS( "tuple val[0] failed", t.get<0>(), 7 );
	ENSURE_EQUALS( "tuple val[1] failed", t.get<1>(), "Ala ma kota" );
	ENSURE_EQUALS( "tuple val[2] failed", t.get<2>(), 3.141592653589793 );
	ENSURE_EQUALS( "tuple val[3] failed", t.get<3>(), static_cast<void*>( NULL ) );
	ENSURE_EQUALS( "tuple val[4] failed", t.get<4>(), HTime::TZ::LOCAL );
TUT_TEARDOWN()

}


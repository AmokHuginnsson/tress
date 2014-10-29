/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hsignal.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hsignal.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {


TUT_SIMPLE_MOCK( tut_yaal_tools_hsignal );
TUT_TEST_GROUP( tut_yaal_tools_hsignal, "yaal::tools::HSignal" );

TUT_UNIT_TEST( 1, "single slot (no arg)" )
	int var( 0 );
	HSignal<void ()> sig;
	sig.connect( call( &setter<int>::set, ref( var ), 7 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched", var, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "single slot (with arg)" )
	int var( 0 );
	HSignal<void ( int )> sig;
	sig.connect( call( &setter<int>::set, ref( var ), _1 ) );
	sig( 7 );
	ENSURE_EQUALS( "signal not dispatched", var, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "multiple slots" )
	int var1( 0 );
	int var2( 0 );
	int var3( 0 );
	HSignal<void ()> sig;
	sig.connect( call( &setter<int>::set, ref( var1 ), 7 ) );
	sig.connect( call( &setter<int>::set, ref( var2 ), 13 ) );
	sig.connect( call( &setter<int>::set, ref( var3 ), 42 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "signal not dispatched", var2, 13 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
TUT_TEARDOWN()

}


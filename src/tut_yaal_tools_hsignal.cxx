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

TUT_UNIT_TEST( "single slot (no arg)" )
	int var( 0 );
	HSignal<void ()> sig;
	sig.connect( call( &defer<int>::set, ref( var ), 7 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched", var, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "single slot (with arg)" )
	int var( 0 );
	HSignal<void ( int )> sig;
	sig.connect( call( &defer<int>::set, ref( var ), _1 ) );
	sig( 7 );
	ENSURE_EQUALS( "signal not dispatched", var, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "multiple slots" )
	int var1( 0 );
	int var2( 0 );
	int var3( 0 );
	HSignal<void ()> sig;
	sig.connect( call( &defer<int>::set, ref( var1 ), 7 ) );
	sig.connect( call( &defer<int>::set, ref( var2 ), 13 ) );
	sig.connect( call( &defer<int>::set, ref( var3 ), 42 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "signal not dispatched", var2, 13 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "disable slot" )
	int var1( 0 );
	int var2( 0 );
	int var3( 0 );
	typedef HSignal<void ()> sig_t;
	sig_t sig;
	sig.connect( call( &defer<int>::set, ref( var1 ), 7 ) );
	sig_t::HConnection c( sig.connect( call( &defer<int>::set, ref( var2 ), 13 ) ) );
	sig.connect( call( &defer<int>::set, ref( var3 ), 42 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "signal not dispatched", var2, 13 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
	c.disable();
	var1 = var2 = var3 = 0;
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "slot not disabled", var2, 0 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "enable slot" )
	int var1( 0 );
	int var2( 0 );
	int var3( 0 );
	typedef HSignal<void ()> sig_t;
	sig_t sig;
	sig.connect( call( &defer<int>::set, ref( var1 ), 7 ) );
	sig_t::HConnection c( sig.connect( call( &defer<int>::set, ref( var2 ), 13 ) ) );
	sig.connect( call( &defer<int>::set, ref( var3 ), 42 ) );
	c.disable();
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "slot not disabled", var2, 0 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
	c.enable();
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "slot not enabled", var2, 13 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "disconnect slot" )
	int var1( 0 );
	int var2( 0 );
	int var3( 0 );
	typedef HSignal<void ()> sig_t;
	sig_t sig;
	sig.connect( call( &defer<int>::set, ref( var1 ), 7 ) );
	sig_t::HConnection c( sig.connect( call( &defer<int>::set, ref( var2 ), 13 ) ) );
	sig.connect( call( &defer<int>::set, ref( var3 ), 42 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "signal not dispatched", var2, 13 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
	c.disconnect();
	var1 = var2 = var3 = 0;
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "slot not disconnected", var2, 0 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
	var1 = var2 = var3 = 0;
	c.enable();
	sig();
	ENSURE_EQUALS( "signal not dispatched", var1, 7 );
	ENSURE_EQUALS( "slot not disconnected", var2, 0 );
	ENSURE_EQUALS( "signal not dispatched", var3, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "early slots and late slots" )
	/* automatic order */ {
		int var( 1 );
		typedef HSignal<void ()> sig_t;
		sig_t sig;
		sig.connect( call( &defer<int>::add, ref( var ), 1 ) );
		sig.connect( call( &defer<int>::mul, ref( var ), 2 ) );
		sig();
		ENSURE_EQUALS( "signal not dispatched", var, 4 );
	}
	/* manual order */ {
		int var( 1 );
		typedef HSignal<void ()> sig_t;
		sig_t sig;
		sig.connect( call( &defer<int>::add, ref( var ), 1 ) );
		sig.connect( call( &defer<int>::mul, ref( var ), 2 ), signal::POSITION::AT_FRONT );
		sig();
		ENSURE_EQUALS( "signal not dispatched in correct order", var, 3 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "prio slots" )
	int var( 1 );
	typedef HSignal<void ()> sig_t;
	sig_t sig;
	sig.connect( 3, call( &defer<int>::add, ref( var ), 1 ) );
	sig.connect( 2, call( &defer<int>::mul, ref( var ), 2 ), signal::POSITION::AT_FRONT );
	sig.connect( 1, call( &defer<int>::add, ref( var ), 1 ) );
	sig();
	ENSURE_EQUALS( "signal not dispatched in correct order", var, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "prio slots - late/early" )
	int var( 1 );
	typedef HSignal<void ()> sig_t;
	sig_t sig;
	sig.connect( 0, call( &defer<int>::add, ref( var ), 1 ) );
	sig.connect( 0, call( &defer<int>::mul, ref( var ), 2 ), signal::POSITION::AT_FRONT );
	sig();
	ENSURE_EQUALS( "signal not dispatched in correct order", var, 3 );
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hconsole_hinfo.cxx - this file is integral part of `tress' project.

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

#include <yaal/hconsole/hinfo.hxx>
#include <yaal/hconsole/hinfointeger.hxx>
#include <yaal/hconsole/hinfotime.hxx>
#include <yaal/hconsole/heditwidget.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hconsole_hinfo );
TUT_TEST_GROUP( tut_yaal_hconsole_hinfo, "yaal::hconsole::HInfo" );

TUT_UNIT_TEST( "from int" )
	HInfoMultiVal imv( 7LL );
	ENSURE_EQUALS( "int as int failed", imv.get_integer(), 7LL );
	ENSURE_EQUALS( "int as str failed", imv.get_string(), "7" );
	ENSURE_EQUALS( "int as real failed", imv.get_real(), 7.L );
	ENSURE_EQUALS( "int as time failed", imv.get_time(), HTime( HTime::TZ::UTC, 7 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from string" )
	HInfoMultiVal imv( "7" );
	ENSURE_EQUALS( "int as str failed", imv.get_string(), "7" );
	ENSURE_EQUALS( "int as int failed", imv.get_integer(), 7LL );
	ENSURE_EQUALS( "int as real failed", imv.get_real(), 7.L );
	ENSURE_THROW( "time from invalid succeeded", imv.get_time(), HTimeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from real" )
	HInfoMultiVal imv( 7.L );
	ENSURE_EQUALS( "real as real failed", imv.get_real(), 7.L );
	ENSURE_EQUALS( "real as str failed", imv.get_string(), "7.0" );
	ENSURE_EQUALS( "real as int failed", imv.get_integer(), 7LL );
	ENSURE_EQUALS( "real as time failed", imv.get_time(), HTime( HTime::TZ::UTC, 7 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from time" )
	HTime bday( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 7 );
	HInfoMultiVal imv( bday );
#ifdef __MSVCXX__
	int long long expInt( 62432116207LL );
	double long expReal( 62432116207.L );
#else
	int long long expInt( 62432112607LL );
	double long expReal( 62432112607.L );
#endif
	ENSURE_EQUALS( "time as time failed", imv.get_time(), bday );
	ENSURE_EQUALS( "time as int failed", imv.get_integer(), expInt );
	ENSURE_EQUALS( "time as str failed", imv.get_string(), "1978-05-24 23:30:07" );
	ENSURE_EQUALS( "time as real failed", imv.get_real(), expReal );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set/get all types" )
	HInfoMultiVal imv;
	yaal::i64_t boobs( 80085 );
	imv.set_integer( boobs );
	double long pi( 3.141592653589793 );
	imv.set_real( pi );
	HTime bday( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 7 );
	imv.set_time( bday );
	HString text( "Ala ma kota" );
	imv.set_string( text );
	ENSURE_EQUALS( "set/get int failed", imv.get_integer(), boobs );
	ENSURE_EQUALS( "set/get str failed", imv.get_string(), text );
	ENSURE_EQUALS( "set/get real failed", imv.get_real(), pi );
	ENSURE_EQUALS( "set/get as time failed", imv.get_time(), bday );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	HInfoMultiVal imv;
	yaal::i64_t boobs( 80085 );
	imv.set_integer( boobs );
	double long pi( 3.141592653589793 );
	imv.set_real( pi );
	HTime bday( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 7 );
	imv.set_time( bday );
	HString text( "Ala ma kota" );
	imv.set_string( text );
	ENSURE_EQUALS( "set/get int failed", imv.get_integer(), boobs );
	ENSURE_EQUALS( "set/get str failed", imv.get_string(), text );
	ENSURE_EQUALS( "set/get real failed", imv.get_real(), pi );
	ENSURE_EQUALS( "set/get time failed", imv.get_time(), bday );

	HInfoMultiVal imv2;
	yaal::i64_t eleet( 31337 );
	imv2.set_integer( eleet );
	double long e( 2.718281828459045 );
	imv2.set_real( e );
	HTime scbday( HTime::TZ::LOCAL, 1989, 8, 24, 14, 25, 13 );
	imv2.set_time( scbday );
	HString tag( "Huginn programming language" );
	imv2.set_string( tag );
	ENSURE_EQUALS( "set/get int failed", imv2.get_integer(), eleet );
	ENSURE_EQUALS( "set/get str failed", imv2.get_string(), tag );
	ENSURE_EQUALS( "set/get real failed", imv2.get_real(), e );
	ENSURE_EQUALS( "set/get time failed", imv2.get_time(), scbday );

	using yaal::swap;
	swap( imv, imv2 );

	ENSURE_EQUALS( "swap of int failed", imv.get_integer(), eleet );
	ENSURE_EQUALS( "swap of str failed", imv.get_string(), tag );
	ENSURE_EQUALS( "swap of real failed", imv.get_real(), e );
	ENSURE_EQUALS( "swap of time failed", imv.get_time(), scbday );

	ENSURE_EQUALS( "swap of int failed", imv2.get_integer(), boobs );
	ENSURE_EQUALS( "swap of str failed", imv2.get_string(), text );
	ENSURE_EQUALS( "swap of real failed", imv2.get_real(), pi );
	ENSURE_EQUALS( "swap of time failed", imv2.get_time(), bday );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign oper" )
	HInfoMultiVal imv;
	yaal::i64_t boobs( 80085 );
	imv.set_integer( boobs );
	double long pi( 3.141592653589793 );
	imv.set_real( pi );
	HTime bday( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 7 );
	imv.set_time( bday );
	HString text( "Ala ma kota" );
	imv.set_string( text );
	ENSURE_EQUALS( "set/get int failed", imv.get_integer(), boobs );
	ENSURE_EQUALS( "set/get str failed", imv.get_string(), text );
	ENSURE_EQUALS( "set/get real failed", imv.get_real(), pi );
	ENSURE_EQUALS( "set/get as time failed", imv.get_time(), bday );

	HInfoMultiVal imv2;

	imv2 = imv;

	ENSURE_EQUALS( "assign of int failed", imv2.get_integer(), boobs );
	ENSURE_EQUALS( "assign of str failed", imv2.get_string(), text );
	ENSURE_EQUALS( "assign of real failed", imv2.get_real(), pi );
	ENSURE_EQUALS( "assign of as time failed", imv2.get_time(), bday );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HInfoInteger" )
	HInfoInteger ii( 7 );
	ENSURE_THROW( "get real on HInfoInteger succeeded", ii.get_real(), HFailedAssertion );
	ENSURE_THROW( "get string on HInfoInteger succeeded", ii.get_string(), HFailedAssertion );
	ENSURE_THROW( "get time on HInfoInteger succeeded", ii.get_time(), HFailedAssertion );
	ENSURE_THROW( "set real on HInfoInteger succeeded", ii.set_real( 0.0L ), HFailedAssertion );
	ENSURE_EQUALS( "bad HInfoInteger from constructor", ii.get_integer(), 7 );
	ii.set_string( "19" );
	ENSURE_EQUALS( "bad HInfoInteger from set_string", ii.get_integer(), 19 );
	ii.set_time( HTime( HTime::TZ::UTC, 0, 1, 1, 1, 0, 0 ) );
	ENSURE_EQUALS( "bad HInfoInteger from set_time", ii.get_integer(), 3600 );
	ii.set_integer( 13 );
	ENSURE_EQUALS( "bad HInfoInteger from set_integer", ii.get_integer(), 13 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HInfoTime" )
	HTime time( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 17 );
	HInfoTime it( time );
	ENSURE_THROW( "get real on HInfoTime succeeded", it.get_real(), HFailedAssertion );
	ENSURE_THROW( "get string on HInfoTime succeeded", it.get_string(), HFailedAssertion );
	ENSURE_EQUALS( "bad time from constructor", it.get_time(), time );
	it.set_integer( 3600 );
	ENSURE_EQUALS( "bad time from set_integer", it.get_integer(), 3600 );
	ENSURE_THROW( "set real on HInfoInteger succeeded", it.set_real( 0.0L ), HFailedAssertion );
	it.set_string( "1978-05-24 23:30:29" );
	ENSURE_EQUALS( "bad time from string", it.get_time(), HTime( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 29 ) );
	HTime consc( HTime::TZ::LOCAL, 1989, 8, 24, 14, 24, 56 );
	it.set_time( consc );
	ENSURE_EQUALS( "bad time from set_time", it.get_time(), consc );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HInfoString" )
	HString s( "ala" );
	HInfoString is( s );
	ENSURE_EQUALS( "bad string from ctor", is.get_string(), "ala" );
	ENSURE_THROW( "get time on HInfoString succeeded", is.get_time(), HFailedAssertion );
	is.set_integer( 7 );
	ENSURE_EQUALS( "bad string from set_integer", is.get_string(), "7" );
	is.set_real( 13.5 );
	ENSURE_EQUALS( "bad string from set_real", is.get_string(), "13.5" );
	is.set_string( "kot" );
	ENSURE_EQUALS( "bad string from set_string", is.get_string(), "kot" );
	is.set_time( HTime( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 17 ) );
	ENSURE_EQUALS( "bad string from set_time", is.get_string(), "1978-05-24 23:30:17" );
TUT_TEARDOWN()

}


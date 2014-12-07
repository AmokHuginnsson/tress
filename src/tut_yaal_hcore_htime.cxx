/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_htime.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/htime.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_htime );
TUT_TEST_GROUP( tut_yaal_hcore_htime, "yaal::hcore::HTime" );

/*
 * On Solaris all time functions:
 * mktime(), gmtime(_r)(), localtime(_r)(),
 * are broken.
 * They are unable to handle dates in year 0.
 * Where year 0 is equivalent of year 1 BCE.
 */

TUT_UNIT_TEST( "mkgmtime" )
	struct tm b;
	int years( -1 );
#ifdef __HOST_OS_TYPE_SOLARIS__
	i64_t start( 31622400 );
#else /* #ifdef __HOST_OS_TYPE_SOLARIS__ */
	i64_t start( 0 );
#endif /* #else #ifdef __HOST_OS_TYPE_SOLARIS__ */
#if SIZEOF_TIME_T == 8
	int end( 4000 );
#else /* #if SIZEOF_TIME_T == 8 */
	int end( 2038 );
	start = HTime::SECONDS_TO_UNIX_EPOCH;
#endif /* #else #if SIZEOF_TIME_T == 8 */
	for ( i64_t i( start ); years < end; i += 7193 ) {
		time_t t( static_cast<time_t>( i - HTime::SECONDS_TO_UNIX_EPOCH ) );
		gmtime_r( &t, &b );
		if ( years != ( b.tm_year + 1900 ) ) {
			years = b.tm_year + 1900;
			if ( years )
				clog << ",";
			clog << years << flush;
		}
		i64_t res( mkgmtime( &b ) + HTime::SECONDS_TO_UNIX_EPOCH );
		if ( res != i ) {
			cout << endl << "ex: " << HTime( i ).to_string() << "\nac: " << HTime( res ).to_string() << endl;
		}
		ENSURE_EQUALS( "mkgmtime failed", res, i );
	}
	clog << "years: " << years << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "get current time" )
	HTime nowLocal( now_local() );
	HTime nowUTC( now_utc() );
	i64_t now( time( NULL ) + HTime::SECONDS_TO_UNIX_EPOCH );
	i64_t nowLocalRaw( nowLocal.raw() );
	i64_t nowUTCRaw( nowUTC.raw() );
	nowLocalRaw -= ( nowLocalRaw % 100 );
	nowUTCRaw -= ( nowUTCRaw % 100 );
	now -= ( now % 100 );
	ENSURE_EQUALS( "raw local differs from raw UTC", nowLocalRaw, nowUTCRaw );
	ENSURE_EQUALS( "current time is not real", nowLocalRaw, now );
	clog << nowLocal << endl;
	clog << nowUTC << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "time from string" )
	HTime bday( "1978-05-24 23:30:00" );
	ENSURE_EQUALS( "bad year from string", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from string", bday.get_month(), 5 );
	ENSURE_EQUALS( "bad day from string", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from string", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from string", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from string", bday.get_second(), 0 );
	clog << bday << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "time explicit, each part separetely" )
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), 5 );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	clog << bday << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "time from raw" )
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	HTime t( now_local() );
	t.set( bday.raw() );
	ENSURE_EQUALS( "bad year from raw", t.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from raw", t.get_month(), 5 );
	ENSURE_EQUALS( "bad day from raw", t.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from raw", t.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from raw", t.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from raw", t.get_second(), 0 );
	clog << t << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	HTime now( now_local() );
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	HTime nowCopy( now );
	HTime bdayCopy( bday );
	bday.swap( now );
	ENSURE_EQUALS( "swap failed", bday, nowCopy );
	ENSURE_EQUALS( "swap failed2", now, bdayCopy );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assignment" )
	HTime now( now_local() );
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	now = bday;
	ENSURE_EQUALS( "bad year from assignment", now.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from assignment", now.get_month(), 5 );
	ENSURE_EQUALS( "bad day from assignment", now.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from assignment", now.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from assignment", now.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from assignment", now.get_second(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "time diff" )
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	HTime consciousness( 1989, 8, 24, 14, 30, 0 );
	HTime idle( consciousness );
	idle.set_tz( HTime::TZ::UTC );
	idle -= bday;
	clog << idle << endl;
	/*
	 * Read comment in htime.hxx header.
	 */
#if SIZEOF_TIME_T == 8
	int compensate( 0 );
#else /* #if SIZEOF_TIME_T == 8 */
	int compensate( 1970 );
#endif /* #else #if SIZEOF_TIME_T == 8 */
	ENSURE_EQUALS( "bad year from diff", idle.get_year() - compensate, 11 );
	ENSURE_EQUALS( "bad month from diff", idle.get_month() - 1, 3 );
	ENSURE_EQUALS( "bad day from diff", idle.get_day(), 2 );
	ENSURE_EQUALS( "bad hour from diff", idle.get_hour(), 15 );
	ENSURE_EQUALS( "bad minute from diff", idle.get_minute(), 0 );
	ENSURE_EQUALS( "bad seconds from diff", idle.get_second(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_format" )
	HTime bday( 1978, 5, 24, 23, 30, 0, _rfc2822DateTimeFormat_ );
	HString bdayBadFromat( bday.string() );
	bday.set_format( _iso8601DateTimeFormat_ );
	HString bdayString( bday.string() );
	ENSURE( "test setup fail", bdayString != bdayBadFromat );
	ENSURE_EQUALS( "set_format fail", bdayString, "1978-05-24 23:30:00" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_year" )
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), 5 );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	bday.mod_year( 1 );
	ENSURE_EQUALS( "bad year from mod_year", bday.get_year(), 1979 );
	ENSURE_EQUALS( "bad month from mod_year", bday.get_month(), 5 );
	ENSURE_EQUALS( "bad day from mod_year", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_year", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_year", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_year", bday.get_second(), 0 );
	bday.mod_year( -99 );
	ENSURE_EQUALS( "bad year from mod_year", bday.get_year(), 1880 );
	ENSURE_EQUALS( "bad month from mod_year", bday.get_month(), 5 );
	ENSURE_EQUALS( "bad day from mod_year", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_year", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_year", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_year", bday.get_second(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_month" )
	HTime bday( 1978, 5, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), 5 );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	bday.mod_month( 1 );
	ENSURE_EQUALS( "bad year from mod_month", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_month", bday.get_month(), 6 );
	ENSURE_EQUALS( "bad day from mod_month", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_month", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_month", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_month", bday.get_second(), 0 );
	bday.mod_month( -99 );
	ENSURE_EQUALS( "bad year from mod_month", bday.get_year(), 1970 );
	ENSURE_EQUALS( "bad month from mod_month", bday.get_month(), 3 );
	ENSURE_EQUALS( "bad day from mod_month", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_month", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_month", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_month", bday.get_second(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "epoch" )
	HTime epoch( HTime::TZ::UTC, 0, 1, 1, 0, 0, 0 );
	HTime epochRaw( HTime::TZ::UTC, 0LL, _iso8601DateTimeFormat_ );
	ENSURE_EQUALS( "bad epoch", epoch, epochRaw );
	HTime now( HTime::TZ::LOCAL );
	now -= now;
	ENSURE_EQUALS( "bad zero duration", now, epochRaw );
#undef unix
	HTime unix( 1970_yY );
	ENSURE_EQUALS( "bad diff from unix", unix.raw(), static_cast<i64_t>( HTime::SECONDS_TO_UNIX_EPOCH ) );
TUT_TEARDOWN()

#ifndef __HOST_OS_TYPE_SOLARIS__
#if SIZEOF_TIME_T == 8
TUT_UNIT_TEST( "user defined literal" )
	ENSURE_EQUALS( "udl failed", ( 1978_yY + ( 4_yM ).set_time( 0, 0, 0 ) + 23_yD + 23_yh + 30_ym - 1_yD - 2_yh ).set_tz( HTime::TZ::LOCAL ), HTime( 1978, 5, 24, 23, 30, 0 ) );
TUT_TEARDOWN()
#endif /* #if SIZEOF_TIME_T == 8 */
#endif /* #ifndef __HOST_OS_TYPE_SOLARIS__ */

}


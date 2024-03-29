/* Read tress/LICENSE.md file for copyright and licensing information. */

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

#ifdef __MSVCXX__
inline struct tm *gmtime_r(const time_t *timep, struct tm *result) {
	gmtime_s( result, timep );
	return result;
}
#endif /* #ifdef __MSVCXX__ */

namespace yaal {

namespace hcore {

std::ostream& operator << ( std::ostream&, HTime::DAY_OF_WEEK );
std::ostream& operator << ( std::ostream& out, HTime::DAY_OF_WEEK wd ) {
	std::string name;
	switch ( wd ) {
		case ( HTime::DAY_OF_WEEK::MONDAY ): name = "monday"; break;
		case ( HTime::DAY_OF_WEEK::TUESDAY ): name = "tuesday"; break;
		case ( HTime::DAY_OF_WEEK::WEDNESDAY ): name = "wednesday"; break;
		case ( HTime::DAY_OF_WEEK::THURSDAY ): name = "thursday"; break;
		case ( HTime::DAY_OF_WEEK::FRIDAY ): name = "friday"; break;
		case ( HTime::DAY_OF_WEEK::SATURDAY ): name = "saturday"; break;
		case ( HTime::DAY_OF_WEEK::SUNDAY ): name = "sunday"; break;
	}
	out << name;
	return out;
}
std::ostream& operator << ( std::ostream&, HTime::MONTH::month_t );
std::ostream& operator << ( std::ostream& out, HTime::MONTH::month_t mon ) {
	std::string name;
	switch ( mon ) {
		case ( HTime::MONTH::JANUARY ): name = "january"; break;
		case ( HTime::MONTH::FEBRUARY ): name = "february"; break;
		case ( HTime::MONTH::MARCH ): name = "march"; break;
		case ( HTime::MONTH::APRIL ): name = "april"; break;
		case ( HTime::MONTH::MAY ): name = "may"; break;
		case ( HTime::MONTH::JUNE ): name = "june"; break;
		case ( HTime::MONTH::JULY ): name = "july"; break;
		case ( HTime::MONTH::AUGUST ): name = "august"; break;
		case ( HTime::MONTH::SEPTEMBER ): name = "september"; break;
		case ( HTime::MONTH::OCTOBER ): name = "october"; break;
		case ( HTime::MONTH::NOVEMBER ): name = "november"; break;
		case ( HTime::MONTH::DECEMBER ): name = "december"; break;
	}
	out << name;
	return out;
}

}

}

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
	start = unix_epoch_to_yaal_epoch( 0 );
#endif /* #else #if SIZEOF_TIME_T == 8 */
	for ( i64_t i( start ); years < end; i += 7193 ) {
		time_t t( static_cast<time_t>( i - unix_epoch_to_yaal_epoch( 0 ) ) );
		gmtime_r( &t, &b );
		if ( years != ( b.tm_year + 1900 ) ) {
			years = b.tm_year + 1900;
			if ( years )
				clog << ",";
			clog << years << flush;
		}
		i64_t res( mkgmtime( &b ) + unix_epoch_to_yaal_epoch( 0 ) );
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
	i64_t now( ::time( nullptr ) + unix_epoch_to_yaal_epoch( 0 ) );
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
	ENSURE_EQUALS( "bad month from string", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from string", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from string", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from string", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from string", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	clog << bday << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "time explicit, each part separetely" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	clog << bday << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "time from raw" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	HTime t( now_local() );
	t.set( bday.raw() );
	ENSURE_EQUALS( "bad year from raw", t.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from raw", t.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from raw", t.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from raw", t.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from raw", t.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from raw", t.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	clog << t << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_time" )
	HTime t( now_local() );
	HTime orig( t );
	int hour( t.get_hour() );
	int minute( t.get_minute() );
	int second( t.get_second() );
	t.set_time( hour != 10 ? 10 : 20, minute != 10 ? 10 : 20, second != 10 ? 10 : 20 );
	ENSURE( "time stayed same", t != orig );
	ENSURE_EQUALS( "bad year", t.get_year(), orig.get_year() );
	ENSURE_EQUALS( "bad month", t.get_month(), orig.get_month() );
	ENSURE_EQUALS( "bad day", t.get_day(), orig.get_day() );
	ENSURE_EQUALS( "bad hour", t.get_hour(), hour != 10 ? 10 : 20 );
	ENSURE_EQUALS( "bad minute", t.get_minute(), minute != 10 ? 10 : 20 );
	ENSURE_EQUALS( "bad second", t.get_second(), second != 10 ? 10 : 20 );
	ENSURE_THROW( "bad hour accepted", t.set_time( -1, 0, 0 ), HTimeException );
	ENSURE_THROW( "bad hour accepted", t.set_time( 24, 0, 0 ), HTimeException );
	ENSURE_THROW( "bad minute accepted", t.set_time( 0, -1, 0 ), HTimeException );
	ENSURE_THROW( "bad minute accepted", t.set_time( 0, 60, 0 ), HTimeException );
	ENSURE_THROW( "bad second accepted", t.set_time( 0, 0, -1 ), HTimeException );
	ENSURE_THROW( "bad second accepted", t.set_time( 0, 0, 60 ), HTimeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set_date" )
	HTime t( now_local() );
	HTime orig( t );
	int month( t.get_month() );
	int day( t.get_day() );
	t.set_date( 1978, month != 5 ? 5 : 8, day != 24 ? 24 : 25 );
	ENSURE( "date stayed same", t != orig );
	ENSURE_EQUALS( "bad hour", t.get_hour(), orig.get_hour() );
	ENSURE_EQUALS( "bad minute", t.get_minute(), orig.get_minute() );
	ENSURE_EQUALS( "bad second", t.get_second(), orig.get_second() );
	ENSURE_EQUALS( "bad year", t.get_year(), 1978 );
	ENSURE_EQUALS( "bad month", t.get_month(), month != 5 ? 5 : 8 );
	ENSURE_EQUALS( "bad day", t.get_day(), day != 24 ? 24 : 25 );
	ENSURE_THROW( "bad month accepted", t.set_date( 1989, 0, 1 ), HTimeException );
	ENSURE_THROW( "bad month accepted", t.set_date( 1989, 13, 1 ), HTimeException );
	ENSURE_THROW( "bad day accepted", t.set_date( 1989, 8, 0 ), HTimeException );
	ENSURE_THROW( "bad day accepted", t.set_date( 1989, 8, 32 ), HTimeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "from_string" )
	HTime t( now_local().raw(), "%Y/%m/%d %H/%M/%S" );
	t.from_string( "1978-05-24 23:30:05" );
	ENSURE_EQUALS( "bad date time from string", t, HTime( 1978, 5, 24, 23, 30, 5 ) );
	t.set_now();
	t.set_time();
	t.from_string( "1978-05-24" );
	ENSURE_EQUALS( "bad date from string", t, HTime( 1978, 5, 24, 0, 0, 0 ) );
#ifndef __HOST_OS_TYPE_SOLARIS__
	t.set_now();
	t.set_date( 0 );
	t.from_string( "13:45:57" );
	ENSURE_EQUALS( "bad time from string", t, HTime( 0, 1, 1, 13, 45, 57 ) );
#endif /* #ifndef __HOST_OS_TYPE_SOLARIS__ */
	ENSURE_THROW( "date time from bad string accepted", t.from_string( "1978+05+24 23+30+04" ), HTimeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	HTime now( now_local() );
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	HTime nowCopy( now );
	HTime bdayCopy( bday );
	bday.swap( now );
	ENSURE_EQUALS( "swap failed", bday, nowCopy );
	ENSURE_EQUALS( "swap failed2", now, bdayCopy );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assignment" )
	HTime now( now_local() );
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	now = bday;
	ENSURE_EQUALS( "bad year from assignment", now.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from assignment", now.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from assignment", now.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from assignment", now.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from assignment", now.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from assignment", now.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "time diff" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
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
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0, _rfc2822DateTimeFormat_ );
	HString bdayBadFromat( bday.string() );
	bday.set_format( _iso8601DateTimeFormat_ );
	HString bdayString( bday.string() );
	ENSURE( "test setup fail", bdayString != bdayBadFromat );
	ENSURE_EQUALS( "set_format fail", bdayString, "1978-05-24 23:30:00" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_year" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_year( 1 );
	ENSURE_EQUALS( "bad year from mod_year", bday.get_year(), 1979 );
	ENSURE_EQUALS( "bad month from mod_year", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_year", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_year", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_year", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_year", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::THURSDAY );
#if SIZEOF_TIME_T != 8
	SKIP( "sizeof ( time_t ) != 8" );
#endif /* #if SIZEOF_TIME_T == 8 */
	bday.mod_year( -99 );
	ENSURE_EQUALS( "bad year from mod_year", bday.get_year(), 1880 );
	ENSURE_EQUALS( "bad month from mod_year", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_year", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_year", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_year", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_year", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::MONDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_month" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_month( 1 );
	ENSURE_EQUALS( "bad year from mod_month", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_month", bday.get_month(), 6 );
	ENSURE_EQUALS( "bad day from mod_month", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_month", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_month", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_month", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::SATURDAY );
	bday.mod_month( -99 );
	ENSURE_EQUALS( "bad year from mod_month", bday.get_year(), 1970 );
	ENSURE_EQUALS( "bad month from mod_month", bday.get_month(), 3 );
	ENSURE_EQUALS( "bad day from mod_month", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_month", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_month", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_month", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::TUESDAY );
	bday.mod_month( -4 );
	ENSURE_EQUALS( "bad year from mod_month", bday.get_year(), 1969 );
	ENSURE_EQUALS( "bad month from mod_month", bday.get_month(), 11 );
	ENSURE_EQUALS( "bad day from mod_month", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_month", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_month", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_month", bday.get_second(), 0 );
	bday.mod_month( 4 );
	ENSURE_EQUALS( "bad year from mod_month", bday.get_year(), 1970 );
	ENSURE_EQUALS( "bad month from mod_month", bday.get_month(), 3 );
	ENSURE_EQUALS( "bad day from mod_month", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_month", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_month", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_month", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::TUESDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_day" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_day( 1 );
	ENSURE_EQUALS( "bad year from mod_day", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_day", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_day", bday.get_day(), 25 );
	ENSURE_EQUALS( "bad hour from mod_day", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_day", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_day", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::THURSDAY );
	bday.mod_day( -99 );
	ENSURE_EQUALS( "bad year from mod_day", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_day", bday.get_month(), 2 );
	ENSURE_EQUALS( "bad day from mod_day", bday.get_day(), 15 );
	/* DST change happend 30 of March */
	ENSURE_EQUALS( "bad hour from mod_day", bday.get_hour(), 22 );
	ENSURE_EQUALS( "bad minute from mod_day", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_day", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_hour" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_hour( 1 );
	ENSURE_EQUALS( "bad year from mod_hour", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_hour", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_hour", bday.get_day(), 25 );
	ENSURE_EQUALS( "bad hour from mod_hour", bday.get_hour(), 0 );
	ENSURE_EQUALS( "bad minute from mod_hour", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_hour", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::THURSDAY );
	bday.mod_hour( -99 );
	ENSURE_EQUALS( "bad year from mod_hour", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_hour", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_hour", bday.get_day(), 20 );
	ENSURE_EQUALS( "bad hour from mod_hour", bday.get_hour(), 21 );
	ENSURE_EQUALS( "bad minute from mod_hour", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_hour", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::SATURDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_minute" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_minute( 1 );
	ENSURE_EQUALS( "bad year from mod_minute", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_minute", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_minute", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_minute", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_minute", bday.get_minute(), 31 );
	ENSURE_EQUALS( "bad seconds from mod_minute", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_minute( -99 );
	ENSURE_EQUALS( "bad year from mod_minute", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_minute", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_minute", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_minute", bday.get_hour(), 21 );
	ENSURE_EQUALS( "bad minute from mod_minute", bday.get_minute(), 52 );
	ENSURE_EQUALS( "bad seconds from mod_minute", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mod_second" )
	HTime bday( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 );
	ENSURE_EQUALS( "bad year from set", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from set", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from set", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from set", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from set", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from set", bday.get_second(), 0 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_second( 1 );
	ENSURE_EQUALS( "bad year from mod_second", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_second", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_second", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_second", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_second", bday.get_minute(), 30 );
	ENSURE_EQUALS( "bad seconds from mod_second", bday.get_second(), 1 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
	bday.mod_second( -99 );
	ENSURE_EQUALS( "bad year from mod_second", bday.get_year(), 1978 );
	ENSURE_EQUALS( "bad month from mod_second", bday.get_month(), HTime::MONTH::MAY );
	ENSURE_EQUALS( "bad day from mod_second", bday.get_day(), 24 );
	ENSURE_EQUALS( "bad hour from mod_second", bday.get_hour(), 23 );
	ENSURE_EQUALS( "bad minute from mod_second", bday.get_minute(), 28 );
	ENSURE_EQUALS( "bad seconds from mod_second", bday.get_second(), 22 );
	ENSURE_EQUALS( "bad week day", bday.get_day_of_week(), HTime::DAY_OF_WEEK::WEDNESDAY );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap" )
	HTime const ts1( HTime::TZ::LOCAL, 1978, 5, 24, 23, 30, 0, _iso8601DateTimeFormat_ );
	HTime const ts2( HTime::TZ::UTC, 1989, 8, 25, 14, 17, 52, _rfc2822DateTimeFormat_ );
	HTime t1( ts1 );
	HTime t2( ts2 );
	ENSURE_EQUALS( "copy ctor failed", t1, ts1 );
	ENSURE_EQUALS( "copy ctor failed", t2, ts2 );
	using yaal::swap;
	swap( t1, t2 );
	ENSURE_EQUALS( "swap failed", t1, ts2 );
	ENSURE_EQUALS( "swap failed", t2, ts1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "comparison" )
	ENSURE( "<= failed", HTime( 1978, 5, 24, 23, 30, 5 ) <= HTime( 1978, 5, 24, 23, 30, 5 ) );
	ENSURE( "<= failed", HTime( 1978, 5, 24, 23, 30, 4 ) <= HTime( 1978, 5, 24, 23, 30, 5 ) );
	ENSURE_NOT( "<= failed", HTime( 1978, 5, 24, 23, 30, 5 ) <= HTime( 1978, 5, 24, 23, 30, 4 ) );

	ENSURE( ">= failed", HTime( 1978, 5, 24, 23, 30, 5 ) >= HTime( 1978, 5, 24, 23, 30, 5 ) );
	ENSURE( ">= failed", HTime( 1978, 5, 24, 23, 30, 5 ) >= HTime( 1978, 5, 24, 23, 30, 4 ) );
	ENSURE_NOT( ">= failed", HTime( 1978, 5, 24, 23, 30, 4 ) >= HTime( 1978, 5, 24, 23, 30, 5 ) );

	ENSURE( "< failed", HTime( 1978, 5, 24, 23, 30, 4 ) < HTime( 1978, 5, 24, 23, 30, 5 ) );
	ENSURE_NOT( "< failed", HTime( 1978, 5, 24, 23, 30, 5 ) < HTime( 1978, 5, 24, 23, 30, 5 ) );

	ENSURE( "> failed", HTime( 1978, 5, 24, 23, 30, 5 ) > HTime( 1978, 5, 24, 23, 30, 4 ) );
	ENSURE_NOT( "> failed", HTime( 1978, 5, 24, 23, 30, 5 ) > HTime( 1978, 5, 24, 23, 30, 5 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "epoch" )
	HTime epoch( HTime::TZ::UTC, 0, 1, 1, 0, 0, 0 );
	HTime epochRaw( HTime::TZ::UTC, 0LL, _iso8601DateTimeFormat_ );
	ENSURE_EQUALS( "bad epoch", epoch, epochRaw );
	HTime now( HTime::TZ::LOCAL );
	now -= static_cast<HTime&>( now );
	ENSURE_EQUALS( "bad zero duration", now, epochRaw );
#undef unix
	HTime unix( 1970_yY );
	ENSURE_EQUALS( "bad diff from unix", unix.raw(), unix_epoch_to_yaal_epoch( 0 ) );
	ENSURE_EQUALS( "bad week day", epoch.get_day_of_week(), HTime::DAY_OF_WEEK::SATURDAY );
TUT_TEARDOWN()

#ifndef __HOST_OS_TYPE_SOLARIS__
#if SIZEOF_TIME_T == 8
TUT_UNIT_TEST( "user defined literal" )
	ENSURE_EQUALS( "udl failed",
		( 1978_yY + ( 4_yM ).set_time( 0, 0, 0 ) + 23_yD + 23_yh + 30_ym - 1_yD - 2_yh ).set_tz( HTime::TZ::LOCAL ),
		HTime( 1978, HTime::MONTH::MAY, 24, 23, 30, 0 ) );
	ENSURE_EQUALS( "udl _yt failed", "1978-05-24 23:30:07"_yt, HTime( 1978, 5, 24, 23, 30, 7 ) );
	ENSURE_EQUALS( "udl _ys failed", 62167219200_ys, HTime( HTime::TZ::UTC, 1970, 1, 1, 0, 0, 0 ) );
TUT_TEARDOWN()
#endif /* #if SIZEOF_TIME_T == 8 */
#endif /* #ifndef __HOST_OS_TYPE_SOLARIS__ */

#define ENSURE_DURATION( x, y, z ) ENSURE_EQUALS( x " failed", time::duration_to_string( lexical_cast<time::duration_t>( to_string( x ) ), time::UNIT::NANOSECOND, z ), y )
#define ENSURE_DURATION_UNIT( x, y, z ) ENSURE_EQUALS( x " failed for " #z, time::duration_to_string( lexical_cast<time::duration_t>( to_string( x ) ), time::UNIT::z ), y )
TUT_UNIT_TEST( "duration" )
	ENSURE_DURATION( "3s 4 m 5hour", "5 hours 4 minutes 3 seconds", time::UNIT_FORM::FULL );
	ENSURE_DURATION_UNIT( "3s 4 m 5hour", "5 hours 4 minutes", MINUTE );
	ENSURE_DURATION( "1 sec 2 hour 3 milliseconds 4us 5min 8 nanosecond 6 days 7 week", "7 weeks 6 days 2 hours 5 minutes 1 second 3 milliseconds 4 microseconds 8 nanoseconds", time::UNIT_FORM::FULL );
	ENSURE_DURATION_UNIT( "1 sec 2 hour 3 milliseconds 4us 5min 8 nanosecond 6 days 7 w", "7 weeks 6 days 2 hours 5 minutes 1 second 3 milliseconds", MILLISECOND );
TUT_TEARDOWN()

TUT_UNIT_TEST( "duration abbreviated" )
	ENSURE_DURATION( "3s 4 m 5hour", "5h 4m 3s", time::UNIT_FORM::ABBREVIATED );
	ENSURE_DURATION_UNIT( "3s 4 m 5hour", "5 hours 4 minutes", MINUTE );
	ENSURE_DURATION( "1 sec 2 hour 3 milliseconds 4us 5min 8 nanosecond 6 days 7 week", "7w 6d 2h 5m 1s 3ms 4μs 8ns", time::UNIT_FORM::ABBREVIATED );
	ENSURE_DURATION_UNIT( "1 sec 2 hour 3 milliseconds 4μs 5min 8 nanosecond 6 days 7 w", "7 weeks 6 days 2 hours 5 minutes 1 second 3 milliseconds", MILLISECOND );
TUT_TEARDOWN()
#undef ENSURE_DURATION_UNIT
#undef ENSURE_DURATION

}


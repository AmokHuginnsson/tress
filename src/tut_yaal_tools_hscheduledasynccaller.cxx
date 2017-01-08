/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hscheduledasynccaller.cxx - this file is integral part of `tress' project.

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

#include <ctime>
#include <TUT/tut.hpp>

#include <yaal/tools/hscheduledasynccaller.hxx>
#include <yaal/tools/sleep.hxx>
#include <yaal/hcore/hlog.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hscheduledasynccaller : public simple_mock<tut_yaal_tools_hscheduledasynccaller> {
	typedef simple_mock<tut_yaal_tools_hscheduledasynccaller> base_type;
	HScheduledAsyncCaller& _sac;
	HMutex _mutex;
	int _val;
	tut_yaal_tools_hscheduledasynccaller( void )
		: base_type()
		, _sac( HScheduledAsyncCaller::get_instance() )
		, _mutex()
		, _val( 0 ) {
	}
	void action( int val_ ) {
		HLock l( _mutex );
		_val = val_;
	}
};

TUT_TEST_GROUP( tut_yaal_tools_hscheduledasynccaller, "yaal::tools::HScheduledAsyncCaller" );

TUT_UNIT_TEST( "call_at" )
	int const expect( 7 );
	_val = 0;
	_sac.call_at(
		now_local().mod_second( 1 ),
		call( &tut_yaal_tools_hscheduledasynccaller::action, this, expect )
	);
	ENSURE_EQUALS( "scheduled call did not wait", _val, 0 );
#ifdef _MSC_VER
	static int const WAIT( 16 );
#else /* #ifdef _MSC_VER */
	static int const WAIT( 8 );
#endif /* #else #ifdef _MSC_VER */
	for ( int i( 0 ); i < WAIT; ++ i ) {
		if ( ! sleep_for( duration( 500, time::UNIT::MILLISECOND ) ) ) {
			log_trace << "sleep interrupted!" << endl;
		}
		HLock l( _mutex );
		if ( _val == expect ) {
			ENSURE( "too soon", i > 0 );
			break;
		}
	}
	HLock l( _mutex );
	ENSURE_EQUALS( "scheduled call misfired", _val, expect );
TUT_TEARDOWN()

TUT_UNIT_TEST( "call_in" )
	int const expect( 7 );
	_val = 0;
	_sac.call_in(
		duration( 1, time::UNIT::SECOND ),
		call( &tut_yaal_tools_hscheduledasynccaller::action, this, expect )
	);
	ENSURE_EQUALS( "scheduled call did not wait", _val, 0 );
#ifdef _MSC_VER
	static int const WAIT( 16 );
#else /* #ifdef _MSC_VER */
	static int const WAIT( 8 );
#endif /* #else #ifdef _MSC_VER */
	for ( int i( 0 ); i < WAIT; ++ i ) {
		if ( ! sleep_for( duration( 500, time::UNIT::MILLISECOND ) ) ) {
			log_trace << "sleep interrupted!" << endl;
		}
		HLock l( _mutex );
		if ( _val == expect ) {
			ENSURE( "too soon", i > 0 );
			break;
		}
	}
	HLock l( _mutex );
	ENSURE_EQUALS( "scheduled call misfired", _val, expect );
TUT_TEARDOWN()

TUT_UNIT_TEST( "flush" )
	_val = 0;
	_sac.call_in(
		duration( 2, time::UNIT::SECOND ),
		call( &tut_yaal_tools_hscheduledasynccaller::action, this, 7 )
	);
	ENSURE_EQUALS( "scheduled call did not wait", _val, 0 );
#ifdef _MSC_VER
	static int const WAIT( 8 );
#else /* #ifdef _MSC_VER */
	static int const WAIT( 4 );
#endif /* #else #ifdef _MSC_VER */
	if ( ! sleep_for( duration( 100, time::UNIT::MILLISECOND ) ) ) {
		log_trace << "sleep interrupted!" << endl;
	}
	_sac.flush( this );
	if ( ! sleep_for( duration( WAIT, time::UNIT::SECOND ) ) ) {
		log_trace << "sleep interrupted!" << endl;
	}
	HLock l( _mutex );
	ENSURE_EQUALS( "scheduled call did not flush", _val, 0 );
TUT_TEARDOWN()

}


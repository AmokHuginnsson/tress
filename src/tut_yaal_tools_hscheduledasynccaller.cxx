/* Read tress/LICENSE.md file for copyright and licensing information. */

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
		now_local().mod_second( 2 ),
		call( &tut_yaal_tools_hscheduledasynccaller::action, this, expect )
	);
	ENSURE_EQUALS( "scheduled call did not wait", _val, 0 );
#ifdef _MSC_VER
	static int const WAIT( 32 );
#else /* #ifdef _MSC_VER */
	static int const WAIT( 16 );
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


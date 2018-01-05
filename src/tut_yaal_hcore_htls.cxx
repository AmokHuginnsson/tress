/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_htls.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/htls.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

class TLSTest {
public:
	TLSTest( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
	}
	~TLSTest( void ) {
		clog << __PRETTY_FUNCTION__ << endl;
	}
	void foo( void ) const {}
};

struct tut_yaal_hcore_htls : public simple_mock<tut_yaal_hcore_htls> {
	typedef simple_mock<tut_yaal_hcore_htls> base_type;
	typedef HTLS<TLSTest> tls_t;
	HMutex _mutex;
	HCondition _cond;
	HEvent _allOn;
	int _instances;
	tut_yaal_hcore_htls( void )
		: base_type(), _mutex( HMutex::TYPE::RECURSIVE ), _cond( _mutex ), _allOn(), _instances( 0 )
		{}
	virtual ~tut_yaal_hcore_htls( void ) { }
	void run( tls_t& tls_ ) {
		M_PROLOG
		HThread::set_name( "tut::HThread" );
		HLock l( _mutex );
		++ _instances;
		tls_->foo();
		if ( _instances == 3 ) {
			clog << "all on" << endl;
			_allOn.signal();
		}
		_cond.wait_for( duration( 10, time::UNIT::SECOND ) );
		clog << "leaving ..." << endl;
		return;
		M_EPILOG
	}
	void schedule_stop( void ) {
		M_PROLOG
		HLock l( _mutex );
		_cond.broadcast();
		return;
		M_EPILOG
	}
	void wait_for_all( void ) {
		M_PROLOG
		_allOn.wait();
		return;
		M_EPILOG
	}
};
TUT_TEST_GROUP( tut_yaal_hcore_htls, "yaal::hcore::HTLS" );

TUT_UNIT_TEST( "tls in main thread" )
	tls_t tls;
	tls->foo();
	HLock l( tls.acquire() );
	tls_t::iterator it( tls.begin() );
	ENSURE( "inconsitient state", tls.operator->() == (*it)->operator->() );
	(**it)->foo();
TUT_TEARDOWN()

TUT_UNIT_TEST( "multiple instances" )
	tls_t tls;
	tls->foo();
	HThread t1;
	HThread t2;
	HThread t3;
	TUT_INVOKE( t1.spawn( call( &tut_yaal_hcore_htls::run, this, ref( tls ) ) ); );
	t2.spawn( call( &tut_yaal_hcore_htls::run, this, ref( tls ) ) );
	t3.spawn( call( &tut_yaal_hcore_htls::run, this, ref( tls ) ) );
	TUT_INVOKE( wait_for_all(); );
	HLock l( tls.acquire() );
	tls_t::iterator it( tls.begin() );
	ENSURE_EQUALS( "bad instance count", tls.get_instance_count(), 4 );
	TUT_INVOKE( schedule_stop(); );
TUT_TEARDOWN()

}


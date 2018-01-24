/* Read tress/LICENSE.md file for copyright and licensing information. */

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


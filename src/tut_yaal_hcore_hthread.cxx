/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hthread.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <TUT/tut.hpp>

#include <yaal/hcore/hthread.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/tools/sleep.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

#if defined( __HOST_OS_TYPE_CYGWIN__ ) || defined( __HOST_OS_TYPE_WINDOWS__ )
static int const FINISH_DELAY = 160;
static int const TOLERANCE = 16;
#else /* #if defined( __HOST_OS_TYPE_CYGWIN__ ) || defined( __HOST_OS_TYPE_WINDOWS__ ) */
static int const FINISH_DELAY = 20;
static int const TOLERANCE = 2;
#endif /* #else #if defined( __HOST_OS_TYPE_CYGWIN__ ) || defined( __HOST_OS_TYPE_WINDOWS__ ) */

#define M_DSLEEP( count ) tools::sleep::milisecond( ( count ) * 100 );

class HCool {
protected:
	/*{*/
	bool		_wasStarted;
	int			_lifeLength;
	HString _name;
	/*}*/
public:
	/*{*/
	HCool( char const* );
	virtual ~HCool( void );
	void set( int );
	void run( HThread const* );
	/*}*/
};

HCool::HCool( char const* name_ )
	: _wasStarted( false ), _lifeLength( 0 ), _name( name_ ) {
	M_PROLOG
	cout << "Object [" << _name << "] constructed." << endl;
	return;
	M_EPILOG
}

HCool::~HCool( void ) {
	M_PROLOG
	cout << "Object [" << _name << "] destructed." << endl;
	return;
	M_EPILOG
}

namespace {

void simple( HThread const* const caller_ ) {
	M_PROLOG
	HThread::set_name( "tut::HThread(simple)" );
	cout << "Thread [simple] started." << endl;
	int ctr = 50;
	while ( caller_->is_alive() && ctr -- ) {
		cout << ctr << ' ' << flush;
		M_DSLEEP( 1 );
	}
	cout << "Thread [simple] finished." << endl;
	return;
	M_EPILOG
}

void a_fast_one( HThread const* const ) {
	return;
}

void busy_wait( void ) {
	HThread::set_name( "tut::HThread(busy_wait)" );
/* cppcheck-suppress unreadVariable */
	volatile long q = 3;
	for ( int i= 0; i < 1000; ++ i ) {
		for ( int j= 0; j < 1000; ++ j ) {
			for ( int k= 0; k < 20; ++ k )
				q *= 3;
		}
	}
}

}

void HCool::run( HThread const* caller_ ) {
	M_PROLOG
	HThread::set_name( "tut::HThread(cool)" );
	int ctr = _lifeLength;
	_wasStarted = true;
	cout << "Thread [" << _name << "] started ... ";
	while ( caller_->is_alive() && ctr -- ) {
		cout << ctr << ' ' << flush;
		if ( _name == "busy" )
			busy_wait();
		else
			M_DSLEEP( 1 );
	}
	cout << " ... and finished" << endl;
	return;
	M_EPILOG
}

void HCool::set( int length_ ) {
	M_PROLOG
	_lifeLength = length_;
	return;
	M_EPILOG
}

class CVTest {
	HThread _thread;
	HMutex _mutex;
	HCondition _cV;
	bool _loop;
public:
	CVTest( void );
	~CVTest( void );
	void run( void );
	void eat( void );
};

CVTest::CVTest( void ) : _thread(), _mutex(), _cV( _mutex ), _loop( false ) {
}

CVTest::~CVTest( void ) {
	_thread.finish();
}

void CVTest::run( void ) {
	_loop = true;
	int ctr = 0;
	while ( _loop ) {
		/**/ {
			HLock l( _mutex );
			_cV.signal();
		}
		cout << "+" << flush;
		/**/ {
			HLock l( _mutex );
			_cV.signal();
		}
		cout << "+" << flush;
		ctr += 2;
	}
	return;
}

void CVTest::eat( void ) {
	int cnt = 80;
	HLock l( _mutex );
	_thread.spawn( call( &CVTest::run, this ) );
	while ( cnt -- ) {
		_cV.wait( 1, 0 );
		cout << "\b" << flush;
	}
	_loop = false;
}

namespace {

void unstable( HThread* caller_ ) {
	M_PROLOG
	try {
		throw HFileException( "testing hthread exception propagation" );
	} catch ( HException& e ) {
		e.log( __FILE__, __LINE__, __PRETTY_FUNCTION__ );
		caller_->stack_exception( e.what(), e.code() );
	}
	return;
	M_EPILOG
}

}

TUT_SIMPLE_MOCK( tut_yaal_hcore_hthread );
TUT_TEST_GROUP( tut_yaal_hcore_hthread, "yaal::hcore::HThread" );

TUT_UNIT_TEST( "Construction and destruction" )
	HThread a;
	ENSURE_EQUALS( "bad status on fresh thread", a.is_alive(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting new thread and allowing it to finish" )
	TIME_CONSTRAINT_EXEMPT();
	HCool ca( "a" );
	HThread a;
	ca.set( 5 );
	a.spawn( call( &HCool::run, &ca, &a ) );
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( FINISH_DELAY );
	ENSURE_EQUALS( "thread failed to finish", a.is_alive(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting new thread and finishing it prematurely (sleeping body)" )
	TIME_CONSTRAINT_EXEMPT();
	HTime start( now_local() ), stop( now_local() );
	HCool ca( "sleeping" );
	HThread a;
	ca.set( 40 );
	a.spawn( call( &HCool::run, &ca, &a ) );
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 8 );
	start.set_now();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	a.finish();
	stop.set_now();
	stop -= start;
	ENSURE_EQUALS( "thread failed to stop", a.is_alive(), false );
	ENSURE_DISTANCE( "thread failed to interrupt",
			stop.get_second(), 0, TOLERANCE );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting new thread and finishing it prematurely (busy body)" )
	TIME_CONSTRAINT_EXEMPT();
	HTime start( now_local() ), stop( now_local() );
	HCool ca( "busy" );
	HThread a;
	ca.set( 40 );
	a.spawn( call( &HCool::run, &ca, &a ) );
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 5 );
	start.set_now();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	a.finish();
	stop.set_now();
	stop -= start;
	ENSURE_EQUALS( "thread failed to stop", a.is_alive(), false );
	ENSURE_DISTANCE( "thread failed to interrupt",
			static_cast<double>( stop.get_second() ), 0., TOLERANCE + .5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting new thread and finishing it prematurely by destructor" )
	HTime start( now_local() ), stop( now_local() ); {
		HCool ca( "a" );
		HThread a;
		ca.set( 50 );
		a.spawn( call( &HCool::run, &ca, &a ) );
		ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
		start.set_now();
	}
	stop.set_now();
	stop -= start;
	ENSURE_DISTANCE( "thread failed to interrupt from destructor",
			stop.get_second(), 0, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting and immediatelly finishing thread" )
	HCool ca( "a" );
	HThread a;
	ca.set( 50 );
	a.spawn( call( &HCool::run, &ca, &a ) );
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	a.finish();
	ENSURE_EQUALS( "thread failed to finish", a.is_alive(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting already started thread" )
	HCool ca( "6" );
	HThread a;
	ca.set( 5 );
	a.spawn( call( &HCool::run, &ca, &a ) );
	ENSURE_THROW( "Started already started thread.", a.spawn( call( &HCool::run, &ca, &a ) ), HThreadException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Finishing thread that was not started" )
	HThread a;
	ENSURE_THROW( "Finishing not started thread successful.", a.finish(), HThreadException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Simple thread (plain function)" )
	TIME_CONSTRAINT_EXEMPT();
	HTime start( now_local() ), stop( now_local() );
	HThread a;
	a.spawn( call( &simple, &a ) );
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 10 );
	start.set_now();
	a.finish();
	stop.set_now();
	stop -= start;
	ENSURE_EQUALS( "thread failed to stop", a.is_alive(), false );
	ENSURE_DISTANCE( "thread failed to interrupt",
			stop.get_second(), 0, TOLERANCE );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Starting new thread and allowing it to finish, the finish is actualy invoked." )
	TIME_CONSTRAINT_EXEMPT();
	HCool ca( "a" );
	HThread a;
	ca.set( 5 );
	a.spawn( call( &HCool::run, &ca, &a ) );
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( FINISH_DELAY );
	ENSURE_EQUALS( "thread failed to finish", a.is_alive(), false );
	a.finish();
TUT_TEARDOWN()

TUT_UNIT_TEST( "Very short living thread." )
	HTime start( now_local() ), stop( now_local() );
	HThread a;
	a.spawn( call( a_fast_one, &a ) );
	cout << __PRETTY_FUNCTION__ << endl;
	a.finish();
	/* In case of wrong implementation this test case will hang foreveer. */
TUT_TEARDOWN()

TUT_UNIT_TEST( "Very short living thread, spawned delayed." )
	HTime start( now_local() ), stop( now_local() );
	HThread a;
	a.spawn( call( a_fast_one, &a ) );
	M_DSLEEP( 1 );
	cout << __PRETTY_FUNCTION__ << endl;
	a.finish();
	/* In case of wrong implementation this test case will hang foreveer. */
TUT_TEARDOWN()

TUT_UNIT_TEST( "Conditional variable test." )
	CVTest cvTest;
	cvTest.eat();
TUT_TEARDOWN()

TUT_UNIT_TEST( "Conditional variable timeout." )
	/*
	 * Test for msvcxx port problem in timeout reporting.
	 */
	HMutex m;
	HLock l( m );
	HCondition c( m );
	ENSURE_EQUALS( "bad wait status", static_cast<int>( c.wait( 0, 100 ) ), static_cast<int>( HCondition::TIMEOUT ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Exception propagation." )
	HThread a;
	a.spawn( call( unstable, &a ) );
	ENSURE_THROW( "Exception not propagated!", a.finish(), HThreadException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rwlock test" )
	HReadWriteLock rwlock;
	/* read lock */ {
		HReadWriteLockReadLock rl( rwlock );
	}
	/* write lock */ {
		HReadWriteLockWriteLock wl( rwlock );
	}
	/* two read locks */ {
		HReadWriteLockReadLock rl( rwlock );
		HReadWriteLockReadLock rl2( rwlock );
	}
	/* two write locks */ {
		HReadWriteLockWriteLock wl( rwlock );
		HReadWriteLockWriteLock wl2( rwlock );
	}
	/* three read locks */ {
		HReadWriteLockReadLock rl( rwlock );
		HReadWriteLockReadLock rl2( rwlock );
		HReadWriteLockReadLock rl3( rwlock );
	}
	/* three write locks */ {
		HReadWriteLockWriteLock wl( rwlock );
		HReadWriteLockWriteLock wl2( rwlock );
		HReadWriteLockWriteLock wl3( rwlock );
	}
	/* read lock after write lock */ {
		HReadWriteLockWriteLock wl( rwlock );
		HReadWriteLockReadLock rwl( rwlock );
	}
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hthread.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <cstdio>
#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

#define M_DSLEEP( count ) util::sleep::milisecond( ( count ) * 100 );

class HCool
	{
protected:
	/*{*/
	bool		f_bWasStarted;
	int			f_iLifeLength;
	HString f_oName;
	/*}*/
public:
	/*{*/
	HCool( char const* );
	virtual ~HCool( void );
	void set( int );
	int operator() ( HThread const* const );
	/*}*/
	};

HCool::HCool( char const* a_pcName )
	: f_bWasStarted( false ), f_iLifeLength( 0 ), f_oName( a_pcName )
	{
	M_PROLOG
	cout << "Object [" << f_oName << "] constructed." << endl;
	return;
	M_EPILOG
	}

HCool::~HCool( void )
	{
	M_PROLOG
	cout << "Object [" << f_oName << "] destructed." << endl;
	return;
	M_EPILOG
	}

int simple( HThread const* const a_poCaller )
	{
	M_PROLOG
	cout << "Thread [simple] started." << endl;
	int l_iCtr = 50;
	while ( a_poCaller->is_alive() && l_iCtr -- )
		{
		cout << l_iCtr << ' ' << flush;
		M_DSLEEP( 1 );
		}
	cout << "Thread [simple] finished." << endl;
	return ( 0 );
	M_EPILOG
	}

int a_fast_one( HThread const* const )
	{
	return ( 0 );
	}

void busy_wait( void )
	{
	long q = 3;
	for ( int i= 0; i < 1000; ++ i )
		{
		for ( int j= 0; j < 1000; ++ j )
			{
			for ( int k= 0; k < 20; ++ k )
				q *= 3;
			}
		}
	}

int HCool::operator() ( HThread const* const a_poCaller )
	{
	M_PROLOG
	int l_iCtr = f_iLifeLength;
	f_bWasStarted = true;
	cout << "Thread [" << f_oName << "] started ... ";
	while ( a_poCaller->is_alive() && l_iCtr -- )
		{
		cout << l_iCtr << ' ' << flush;
		if ( f_oName == "busy" )
			busy_wait();
		else
			M_DSLEEP( 1 );
		}
	cout << " ... and finished" << endl;
	return ( 0 );
	M_EPILOG
	}

void HCool::set( int a_iLength )
	{
	M_PROLOG
	f_iLifeLength = a_iLength;
	return;
	M_EPILOG
	}

class CVTest
	{
	typedef HThreadT<CVTest> worker_t;
	worker_t f_oWorker;
	HMutex f_oMutex;
	HCondition f_oCV;
	bool f_bLoop;
public:
	CVTest( void );
	~CVTest( void );
	int operator() ( HThread const* const );
	void eat( void );
	};

CVTest::CVTest( void ) : f_oWorker( *this ), f_oMutex(), f_oCV( f_oMutex ), f_bLoop( false )
	{
	}

CVTest::~CVTest( void )
	{
	f_oWorker.finish();
	}

int CVTest::operator()( HThread const* const )
	{
	f_bLoop = true;
	int ctr = 0;
	while ( f_bLoop )
		{
		f_oCV.signal();
		cout << "+" << flush;
		f_oCV.signal();
		cout << "+" << flush;
		ctr += 2;
		}
	return ( ctr );
	}

void CVTest::eat( void )
	{
	int cnt = 80;
	HLock l( f_oMutex );
	f_oWorker.spawn();
	while ( cnt -- )
		{
		f_oCV.wait( 1, 0 );
		cout << "\b" << flush;
		}
	f_bLoop = false;
	}

typedef HThreadT<HCool> cool_t;
typedef HThreadT<typeof( simple )> simple_t;

TUT_SIMPLE_MOCK( tut_yaal_hcore_hthread );
TUT_TEST_GROUP_N( tut_yaal_hcore_hthread, "yaal::hcore::HThread" );

TUT_UNIT_TEST_N( 1, "/* Construction and destruction */" )
	HCool ca( "a" );
	cool_t a( ca );
	ENSURE_EQUALS( "bad status on fresh thread", a.is_alive(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Starting new thread and allowing it to finish */" )
	HCool ca( "a" );
	cool_t a( ca );
	ca.set( 5 );
	a.spawn();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 10 );
	ENSURE_EQUALS( "thread failed to finish", a.is_alive(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Starting new thread and finishing it prematurely (sleeping body) */" )
	HTime start, stop;
	HCool ca( "sleeping" );
	cool_t a( ca );
	ca.set( 50 );
	a.spawn();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 10 );
	start.set_now();
	a.finish();
	stop.set_now();
	stop -= start;
	ENSURE_EQUALS( "thread failed to stop", a.is_alive(), false );
	ENSURE_DISTANCE( "thread failed to interrupt",
			stop.get_second(), 0, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 33, "/* Starting new thread and finishing it prematurely (busy body) */" )
	HTime start, stop;
	HCool ca( "busy" );
	cool_t a( ca );
	ca.set( 50 );
	a.spawn();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 10 );
	start.set_now();
	a.finish();
	stop.set_now();
	stop -= start;
	ENSURE_EQUALS( "thread failed to stop", a.is_alive(), false );
	ENSURE_DISTANCE( "thread failed to interrupt",
			static_cast<double>( stop.get_second() ), 0., 2.5 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Starting new thread and finishing it prematurely by destructor */" )
	HTime start, stop;
		{
		HCool ca( "a" );
		cool_t a( ca );
		ca.set( 50 );
		a.spawn();
		ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
		start.set_now();
		}
	stop.set_now();
	stop -= start;
	ENSURE_DISTANCE( "thread failed to interrupt from destructor",
			stop.get_second(), 0, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Starting and immediatelly finishing thread */" )
	HCool ca( "a" );
	cool_t a( ca );
	ca.set( 50 );
	a.spawn();
	a.finish();
	ENSURE_EQUALS( "thread failed to finish", a.is_alive(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Starting already started thread */" )
	HCool ca( "6" );
	cool_t a( ca );
	ca.set( 5 );
	a.spawn();
	try
		{
		a.spawn();
		FAIL( "Started already started thread." );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* Finishing thread that was not started */" )
	HCool ca( "a" );
	cool_t a( ca );
	try
		{
		a.finish();
		FAIL( "Finishing not started thread successful." );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Simple thread (plain function) */" )
	HTime start, stop;
	simple_t a( simple );
	a.spawn();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 10 );
	start.set_now();
	a.finish();
	stop.set_now();
	stop -= start;
	ENSURE_EQUALS( "thread failed to stop", a.is_alive(), false );
	ENSURE_DISTANCE( "thread failed to interrupt",
			stop.get_second(), 0, 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* Starting new thread and allowing it to finish, the finich is actualy invoked. */" )
	HCool ca( "a" );
	cool_t a( ca );
	ca.set( 5 );
	a.spawn();
	ENSURE_EQUALS( "thread failed to start", a.is_alive(), true );
	M_DSLEEP( 10 );
	ENSURE_EQUALS( "thread failed to finish", a.is_alive(), false );
	a.finish();
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "/* Very short living thread. */" )
	HTime start, stop;
	simple_t a( a_fast_one );
	a.spawn();
	cout << __PRETTY_FUNCTION__ << endl;
	a.finish();
	/* In case of wrong implementation this test case will hang foreveer. */
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* Very short living thread, spawned delayed. */" )
	HTime start, stop;
	simple_t a( a_fast_one );
	a.spawn();
	M_DSLEEP( 1 );
	cout << __PRETTY_FUNCTION__ << endl;
	a.finish();
	/* In case of wrong implementation this test case will hang foreveer. */
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* Conditional variable test. */" )
	CVTest cvTest;
	cvTest.eat();
TUT_TEARDOWN()

}

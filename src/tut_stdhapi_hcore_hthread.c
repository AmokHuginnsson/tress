/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_stdhapi_hcore_hthread.c - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <unistd.h>

#include "header"
M_CVSID ( "$CVSHeader$" )

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

namespace tut
{

#define M_DSLEEP( count ) usleep ( ( count ) * 100 * 1000 );

class HCool : public HThread
	{
protected:
	/*{*/
	bool		f_bWasStarted;
	int			f_iLifeLength;
	HString f_oName;
	/*}*/
public:
	/*{*/
	HCool ( char const * );
	virtual ~HCool ( void );
	void set ( int );
	/*}*/
protected:
	/*{*/
	virtual int run ( void );
	/*}*/
	};

HCool::HCool ( char const * a_pcName )
	: f_bWasStarted ( false ), f_iLifeLength ( 0 ), f_oName ( a_pcName )
	{
	M_PROLOG
	cout << "Object [" << f_oName << "] constructed." << endl;
	return;
	M_EPILOG
	}

HCool::~HCool ( void )
	{
	M_PROLOG
	if ( ( f_oName == "6" ) && is_alive ( ) )
		finish ( ); /* this is necesarry to avoid pure virtuall call to run */
	cout << "Object [" << f_oName << "] destructed." << endl;
	return;
	M_EPILOG
	}

int HCool::run ( void )
	{
	M_PROLOG
	int l_iCtr = f_iLifeLength;
	f_bWasStarted = true;
	cout << "Thread [" << f_oName << "] started ... ";
	while ( is_alive ( ) && l_iCtr -- )
		{
		HLock l_oLock ( f_oMutex );
		cout << l_iCtr << ' ' << flush;
		M_DSLEEP ( 1 );
		}
	cout << " ... and finished" << endl;
	return ( 0 );
	M_EPILOG
	}

void HCool::set ( int a_iLength )
	{
	M_PROLOG
	f_iLifeLength = a_iLength;
	return;
	M_EPILOG
	}

struct tut_stdhapi_hcore_HThread
	{
	};

typedef test_group < tut_stdhapi_hcore_HThread > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_hcore_HThread_group ( "stdhapi::hcore::HThread" );

/* Construction and destruction */
template < >
template < >
void module::test<1> ( void )
	{
	HCool a ( "a" );
	ensure_equals ( "bad status on fresh thread", a.is_alive ( ), false );
	}

/* Starting new thread and allowing it to finish */
template < >
template < >
void module::test<2> ( void )
	{
	HCool a ( "a" );
	a.set ( 5 );
	a.spawn ( );
	ensure_equals ( "thread failed to start", a.is_alive ( ), true );
	M_DSLEEP ( 10 );
	ensure_equals ( "thread failed to finish", a.is_alive ( ), false );
	}

/* Starting new thread and finishing it prematurely */
template < >
template < >
void module::test<3> ( void )
	{
	HTime start, stop;
	HCool a ( "a" );
	a.set ( 50 );
	a.spawn ( );
	ensure_equals ( "thread failed to start", a.is_alive ( ), true );
	M_DSLEEP ( 10 );
	start.set_now ( );
	a.finish ( );
	stop.set_now ( );
	stop -= start;
	ensure_equals ( "thread failed to stop", a.is_alive ( ), false );
	ensure_distance ( "thread failed to interrupt",
			stop.get_second ( ), 0, 2 );
	}

/* Starting new thread and finishing it prematurely by destructor */
template < >
template < >
void module::test<4> ( void )
	{
	HTime start, stop;
		{
		HCool a ( "a" );
		a.set ( 50 );
		a.spawn ( );
		ensure_equals ( "thread failed to start", a.is_alive ( ), true );
		start.set_now ( );
		a.finish ( );
		}
	stop.set_now ( );
	stop -= start;
	ensure_distance ( "thread failed to interrupt from destructor",
			stop.get_second ( ), 0, 2 );
	}

/* Starting and immediatelly finishing thread */
template < >
template < >
void module::test<5> ( void )
	{
	HCool a ( "a" );
	a.set ( 50 );
	a.spawn ( );
	a.finish ( );
	ensure_equals ( "thread failed to finish", a.is_alive ( ), false );
	}

/* Starting already started thread */
template < >
template < >
void module::test<6> ( void )
	{
	HCool a ( "6" );
	a.set ( 5 );
	a.spawn ( );
	try
		{
		a.spawn ( );
		fail ( "Started already started thread." );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

/* Finishing thread that was not started */
template < >
template < >
void module::test<7> ( void )
	{
	HCool a ( "a" );
	try
		{
		a.finish ( );
		fail ( "Finishing not started thread successful." );
		}
	catch ( HException & e )
		{
		cout << e.what ( ) << endl;
		}
	}

}

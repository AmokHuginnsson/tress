/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_hthread.c - this file is integral part of `tress' project.

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

#include <tut.h>

#include <unistd.h>

#include <stdhapi.h>

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

class HCool : public HThread
	{
protected:
	/*{*/
	bool		f_bWasStarted;
	HString f_oName;
	/*}*/
public:
	/*{*/
	HCool ( char const * );
	virtual ~HCool ( void );
	/*}*/
protected:
	/*{*/
	virtual int run ( void );
	/*}*/
	};

HCool::HCool ( char const * a_pcName ) : f_bWasStarted ( false ), f_oName ( a_pcName )
	{
	M_PROLOG
	return;
	M_EPILOG
	}

HCool::~HCool ( void )
	{
	M_PROLOG
	if ( f_bWasStarted )
		fprintf ( stderr, "%s bye\n", static_cast < char * > ( f_oName ) );
	return;
	M_EPILOG
	}

int HCool::run ( void )
	{
	M_PROLOG
	int l_iCtr = 5;
	f_bWasStarted = true;
	while ( l_iCtr -- )
		{
		fprintf ( stderr, "%s %d\n", static_cast < char * > ( f_oName ), l_iCtr );
		sleep ( 1 );
		listen ( );
		}
	return ( 0 );
	M_EPILOG
	}

struct tut_HThread
	{
	HCool a;
	HCool b;
	tut_HThread ( ) : a ( "a" ), b ( "b" )
		{
		
		}
	};

typedef test_group < tut_HThread > tut_group;
typedef tut_group::object module;
tut_group tut_HThread_group ( "stdhapi/hcore/HThread" );

template < >
template < >
void module::test<1> ( void )
	{
	a.spawn ( );
	b.spawn ( );
	sleep ( 2 );
	}

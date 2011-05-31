/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hworkflow.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_tools_hworkflow
	{
	typedef HInstanceTracker<tut_yaal_tools_hworkflow> counter_t;
	virtual ~tut_yaal_tools_hworkflow( void )
		{}
	static void foo( int, char, int );
	static void bar( counter_t );
	};

TUT_TEST_GROUP( tut_yaal_tools_hworkflow, "yaal::tools::HWorkFlow" );

void tut_yaal_tools_hworkflow::foo( int id, char symbol, int waitTime )
	{
	cout << "foo" << id << flush;
	HClock c;
	for ( int i = 0; i < 3; ++ i )
		{
		util::sleep::milisecond( waitTime );
		cout << symbol << flush;
		}
	cout << "[" << id << "]" << endl;
	}

void tut_yaal_tools_hworkflow::bar( counter_t c )
	{
	cout << c.to_string() << endl;
	}

TUT_UNIT_TEST( 1, "Pushing tasks." )
	TIME_CONSTRAINT_EXEMPT();
	HWorkFlow w( 3 );
	for ( int i = 0; i < 3; ++ i )
		{
		w.push_task( call( tut_yaal_tools_hworkflow::foo, 0, '+', 100 ) );
		w.push_task( call( tut_yaal_tools_hworkflow::foo, 1, '*', 200 ) );
		w.push_task( call( tut_yaal_tools_hworkflow::foo, 2, '@', 300 ) );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Cleanup of finished tasks." )
	{
	HWorkFlow w( 3 );
	w.push_task( call( tut_yaal_tools_hworkflow::bar, counter_t() ) );
	util::sleep::milisecond( 100 );
	ENSURE_EQUALS( "HWorkFlow did not cleaned its task list.", counter_t::get_instance_count(), 0 );
	}
TUT_TEARDOWN()

}


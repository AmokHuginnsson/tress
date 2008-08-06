/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.h"

using namespace tut;
using namespace std;
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
	static void foo( int, char, int );
	typedef HFunctor<typeof( tut_yaal_tools_hworkflow::foo ), int, char, int> simple_functor_t;
	typedef void ( simple_functor_t::* simple_functor_forwarder_t )( int, char, int );
	typedef HCall<simple_functor_t&, simple_functor_forwarder_t, int, char, int> my_task_t;
	};

typedef test_group<tut_yaal_tools_hworkflow> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_tools_hworkflow_group( "yaal::tools::HWorkFlow" );

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

template<>
template<>
void module::test<1>( void )
	{
	simple_functor_t tf( tut_yaal_tools_hworkflow::foo );
	my_task_t::ptr_t f0( new my_task_t( tf, &simple_functor_t::method, 0, '+', 100 ) );
	my_task_t::ptr_t f1( new my_task_t( tf, &simple_functor_t::method, 1, '*', 200 ) );
	my_task_t::ptr_t f2( new my_task_t( tf, &simple_functor_t::method, 2, '@', 300 ) );
	HWorkFlow w( HWorkFlow::MODE::D_FLAT, 3 );
	for ( int i = 0; i < 3; ++ i )
		{
		w.push_task( f0 );
		w.push_task( f1 );
		w.push_task( f2 );
		}
	cout << "All tasks pushed." << endl;
	w.run();
	}

template<>
template<>
void module::test<2>( void )
	{
	simple_functor_t tf( tut_yaal_tools_hworkflow::foo );
	my_task_t::ptr_t f0( new my_task_t( tf, &simple_functor_t::method, 0, '+', 100 ) );
	my_task_t::ptr_t f1( new my_task_t( tf, &simple_functor_t::method, 1, '*', 200 ) );
	my_task_t::ptr_t f2( new my_task_t( tf, &simple_functor_t::method, 2, '@', 300 ) );
	HWorkFlow w( HWorkFlow::MODE::D_PIPE, 3 );
	for ( int i = 0; i < 3; ++ i )
		{
		w.push_task( f0 );
		w.push_task( f1 );
		w.push_task( f2 );
		}
	cout << "All tasks pushed." << endl;
	util::sleep::second( 4 );
	}

}


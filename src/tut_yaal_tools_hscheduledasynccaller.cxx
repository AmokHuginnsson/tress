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

#include <TUT/tut.hpp>

#include <yaal/tools/hscheduledasynccaller.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hscheduledasynccaller : public simple_mock<tut_yaal_tools_hscheduledasynccaller> {
	HScheduledAsyncCaller& _sac;
	HMutex _mutex;
	int _val;
	tut_yaal_tools_hscheduledasynccaller( void )
		: _sac( HScheduledAsyncCaller::get_instance() ), _mutex(), _val( 0 )
		{}
	virtual ~tut_yaal_tools_hscheduledasynccaller( void ) {}
	void action( int val_ ) {
		_val = val_;
	}
};

//TUT_SIMPLE_MOCK( tut_yaal_tools_hscheduledasynccaller );
TUT_TEST_GROUP( tut_yaal_tools_hscheduledasynccaller, "yaal::tools::HScheduledAsyncCaller" );

TUT_UNIT_TEST( 1, "functional test" )
	int const expect( 7 );
	_sac.register_call( time( NULL ) + 1, call( &tut_yaal_tools_hscheduledasynccaller::action, this, expect ) );
	util::sleep::second( 2 );
	ENSURE_EQUALS( "scheduled call mifired", _val, expect );
TUT_TEARDOWN()

}


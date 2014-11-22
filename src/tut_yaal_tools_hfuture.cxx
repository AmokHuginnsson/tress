/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tool_hfuture.cxx - this file is integral part of `tress' project.

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

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "yaal/tools/hfuture.hxx"
#include "yaal/tools/sleep.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tool_hfuture : public simple_mock<tut_yaal_tool_hfuture> {
	int _data;
	tut_yaal_tool_hfuture( void )
		: _data( 0 )
		{}
	virtual ~tut_yaal_tool_hfuture( void ) {}
	int long long power_of_three( int power_ ) {
		int long long val( 1 );
		for ( int i = 0; i  < power_; ++ i ) {
			tools::sleep::milisecond( 50 );
			val *= 3;
		}
		return ( val );
	}
	int& give_val( void ) {
		return ( _data );
	}
	int const& give_val_const( void ) {
		return ( _data );
	}
};

TUT_TEST_GROUP( tut_yaal_tool_hfuture, "yaal::tools::HFuture" );

TUT_UNIT_TEST( "slow operation" )
	HFuture<int long long> f( call( &tut_yaal_tool_hfuture::power_of_three, this, 7 ) );
	cout << "3 ^ 7 = " << f.get() << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "reference returned" )
	HFuture<int&> f( call( &tut_yaal_tool_hfuture::give_val, this ) );
	int& rval( f.get() );
	ENSURE_EQUALS( "returning reference failed", &rval, &_data );
TUT_TEARDOWN()

TUT_UNIT_TEST( "const reference returned" )
	HFuture<int const&> f( call( &tut_yaal_tool_hfuture::give_val_const, this ) );
	int const& rcVal( f.get() );
	ENSURE_EQUALS( "returning const reference failed", &rcVal, &_data );
TUT_TEARDOWN()

}


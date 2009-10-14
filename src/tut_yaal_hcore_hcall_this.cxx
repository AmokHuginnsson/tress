/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall_this.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hcall_this
	{
	static int const CORRECT_ANSWER;
	virtual ~tut_yaal_hcore_hcall_this( void ) {}
	int square( int x )
		{ return ( x * x ); }
	int life_the_universe_and_everything( void ) const
		{ return ( CORRECT_ANSWER ); }
	};

int const tut_yaal_hcore_hcall_this::CORRECT_ANSWER = 42;

TUT_TEST_GROUP_N( tut_yaal_hcore_hcall_this, "yaal::hcore::HCall,this" );

TUT_UNIT_TEST_N( 1, "no-op bind of this" )
	ENSURE_EQUALS( "bind for this failed", call( &tut_yaal_hcore_hcall_this::life_the_universe_and_everything, this )(), CORRECT_ANSWER );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "this and no args" )
	ENSURE_EQUALS( "bind for this failed", call( &tut_yaal_hcore_hcall_this::life_the_universe_and_everything, _1 )( this ), CORRECT_ANSWER );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "this and 1 arg, one free" )
	ENSURE_EQUALS( "bind for this failed", call( &tut_yaal_hcore_hcall_this::square, _1, 2 )( this ), 2 * 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "this and 2 free args, this is first" )
	ENSURE_EQUALS( "bind for this failed", call( &tut_yaal_hcore_hcall_this::square, _1, _2 )( this, 2 ), 2 * 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "this and 2 free args, this is second" )
	ENSURE_EQUALS( "bind for this failed", call( &tut_yaal_hcore_hcall_this::square, _2, _1 )( 2, this ), 2 * 2 );
TUT_TEARDOWN()

}


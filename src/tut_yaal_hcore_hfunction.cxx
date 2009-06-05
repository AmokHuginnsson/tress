/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_.cxx - this file is integral part of `tress' project.

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

int sum( int a, int b )
	{
	return ( a + b );
	}

class Sumator
	{
	int _arg;
public:
	Sumator( int arg_ ) : _arg( arg_ ) {}
	int calculate( int arg_ )
		{ return ( _arg + arg_ ); }
	int calculate_const( int arg_ ) const
		{ return ( _arg + arg_ ); }
	int calculate_volatile( int arg_ ) volatile
		{ return ( _arg + arg_ ); }
	int calculate_const_volatile( int arg_ ) const volatile
		{ return ( _arg + arg_ ); }
	};

class HFunction
	{
	HCallInterface::ptr_t _call;
public:
	HFunction( HCallInterface::ptr_t );
	};

template<typename CLASS_t>
HFunction function( CLASS_t c )
	{
	return ( HFunction( call( c ) ) );
	}

template<typename unknown_t>
bool member( unknown_t )
	{
	return ( trait::is_member<unknown_t>::value );
	}

TUT_SIMPLE_MOCK( tut_yaal_hcore_hfunction );

TUT_TEST_GROUP_N( tut_yaal_hcore_hfunction, "yaal::hcore::HFunction" );

TUT_UNIT_TEST_N( 1, "one arg function call" )
	Sumator s( 2 );
//	ensure_equals( "function call failed", function( sum, 2, _1 )( 3 ), 5 );
//	ensure_equals( "function call failed", function( s, &Sumator::calculate, _1 )( 3 ), 5 );
	cout << "member: " << member( &Sumator::calculate ) << endl;
	cout << "member const: " << member( &Sumator::calculate_const ) << endl;
	cout << "member volatile: " << member( &Sumator::calculate_volatile ) << endl;
	cout << "member const volatile: " << member( &Sumator::calculate_const_volatile ) << endl;
	cout << "function: " << member( sum ) << endl;
TUT_TEARDOWN()

}


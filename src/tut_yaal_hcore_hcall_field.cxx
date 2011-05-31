/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall_field.cxx - this file is integral part of `tress' project.

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

struct tut_yaal_hcore_hcall_field
	{
	typedef HInstanceTracker<tut_yaal_hcore_hcall_field> item_t;
	typedef HPair<HString, HString> person_t;
	virtual ~tut_yaal_hcore_hcall_field( void ) {}
	void foo( void ) {}
	};

HString full_name( tut_yaal_hcore_hcall_field::person_t const& p_ )
	{
	return ( p_.first + " " + p_.second );
	}

TUT_TEST_GROUP( tut_yaal_hcore_hcall_field, "yaal::hcore::HCall,field" );

TUT_UNIT_TEST( 1, "call field read (holder set)" )
	person_t p( "Ala", "Nowak" );
	ENSURE_EQUALS( "field access failed",  call( &person_t::second, &p )(), p.second );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "call field read (holder variable)" )
	person_t p1( "Ala", "Nowak" );
	person_t p2( "Ola", "Kowalska" );
	ENSURE_EQUALS( "field access failed",  call( &person_t::second, _1 )( p1 ), p1.second );
	ENSURE_EQUALS( "field access failed",  call( &person_t::second, _1 )( p2 ), p2.second );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "call field less comparator" )
	person_t p1( "Ala", "Nowak" );
	person_t p2( "Ola", "Kowalska" );
	ENSURE( "comparation failed", call( &person_t::second, _1 )( p1 ) > call( &person_t::second, _1 )( p2 ) );
	ENSURE( "comparation failed", ( call( &person_t::second, _1 ) > call( &person_t::second, _1 ) )( p1, p2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "call field operator overloading with generic HCall<>" )
	person_t p1( "Ala", "Nowak" );
	person_t const p2( "Ola", "Kowalska" );
	cout << ( call( &full_name, _1 ) < call( &person_t::second, _1 ) )( p1, p2 ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "call field bind in algorithm" )
	person_t a[] = { person_t( "Ala", "Kowalska" ), person_t( "Diana", "B³aszczyk" ), person_t( "Marcin", "Konarski" ), person_t( "Magdalena", "Rêbowska" ), person_t( "Wojciech", "Peisert" ) };
	transform( a, a + countof( a ), stream_iterator( cout, " " ), call( &person_t::first, _1 ) );
	cout << endl;
	transform( a, a + countof( a ), stream_iterator( cout, " " ), call( &person_t::second, _1 ) );
	cout << endl;
TUT_TEARDOWN()

}


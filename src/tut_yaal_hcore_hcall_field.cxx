/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hcall.hxx>
#include <yaal/hcore/bound.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hcall_field : public simple_mock<tut_yaal_hcore_hcall_field> {
	typedef simple_mock<tut_yaal_hcore_hcall_field> base_type;
	typedef HInstanceTracker<tut_yaal_hcore_hcall_field> item_t;
	typedef HPair<HString, HString> person_t;
	virtual ~tut_yaal_hcore_hcall_field( void ) {}
};

inline HString full_name( tut_yaal_hcore_hcall_field::person_t const& p_ ) {
	return ( p_.first + " " + p_.second );
}

TUT_TEST_GROUP( tut_yaal_hcore_hcall_field, "yaal::hcore::HCall,field" );

TUT_UNIT_TEST( "call field read (holder set)" )
	person_t p( "Ala", "Nowak" );
	ENSURE_EQUALS( "field access failed",  call( &person_t::second, &p )(), p.second );
TUT_TEARDOWN()

TUT_UNIT_TEST( "call field read (holder variable)" )
	person_t p1( "Ala", "Nowak" );
	person_t p2( "Ola", "Kowalska" );
	ENSURE_EQUALS( "field access failed",  call( &person_t::second, _1 )( p1 ), p1.second );
	ENSURE_EQUALS( "field access failed",  call( &person_t::second, _1 )( p2 ), p2.second );
TUT_TEARDOWN()

TUT_UNIT_TEST( "call field less comparator" )
	person_t p1( "Ala", "Nowak" );
	person_t p2( "Ola", "Kowalska" );
	ENSURE( "comparation failed", call( &person_t::second, _1 )( p1 ) > call( &person_t::second, _1 )( p2 ) );
	ENSURE( "comparation failed", ( call( &person_t::second, _1 ) > call( &person_t::second, _1 ) )( p1, p2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "call field operator overloading with generic HCall<>" )
	person_t p1( "Ala", "Nowak" );
	person_t const p2( "Ola", "Kowalska" );
	clog << ( call( &full_name, _1 ) < call( &person_t::second, _1 ) )( p1, p2 ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "call field bind in algorithm" )
	person_t a[] = { person_t( "Ala", "Kowalska" ), person_t( "Gall", "Anonim" ), person_t( "Marcin", "Konarski" ), person_t( "Magdalena", "Nowak" ), person_t( "Wojciech", "Igrekowski" ) };
	transform( a, a + countof( a ), stream_iterator( clog, " " ), call( &person_t::first, _1 ) );
	clog << endl;
	transform( a, a + countof( a ), stream_iterator( clog, " " ), call( &person_t::second, _1 ) );
	clog << endl;
TUT_TEARDOWN()

}


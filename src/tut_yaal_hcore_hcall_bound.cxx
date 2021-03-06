/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/bound.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hcall_bound : public simple_mock<tut_yaal_hcore_hcall_bound> {
	typedef simple_mock<tut_yaal_hcore_hcall_bound> base_type;
	virtual ~tut_yaal_hcore_hcall_bound( void ) {}
/* cppcheck-suppress functionConst */
	void foo( void ) {}
	void foo_const( void ) const {}
};

TUT_TEST_GROUP( tut_yaal_hcore_hcall_bound, "yaal::hcore::HCall,bound" );

TUT_UNIT_TEST( "Constructor." )
	HBoundCall<> c( call( &tut_yaal_hcore_hcall_bound::foo, this ) );
	HBoundCall<> cc( call( &tut_yaal_hcore_hcall_bound::foo_const, this ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare with constant less." )
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator( l ), call( &item_t::id, _1 ) < 50 );
	copy( l.begin(), l.end(), stream_iterator( clog, " " ) );
	clog << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare with constant greater." )
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator( l ), call( &item_t::id, _1 ) > 50 );
	copy( l.begin(), l.end(), stream_iterator( clog, " " ) );
	clog << endl;
TUT_TEARDOWN()

}


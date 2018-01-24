/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/allocator.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hcore/hlist.hxx>
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_allocator );
TUT_TEST_GROUP( tut_yaal_allocator, "yaal::allocator" );

TUT_UNIT_TEST( "allocator::system" )
	HList<int, allocator::system<int> > l;
	l.push_back( 1 );
TUT_TEARDOWN()


TUT_UNIT_TEST( "allocator::pool" )
	HList<int, allocator::pool<int> > l;
	l.push_back( 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocator::ref<allocator::system>" )
	typedef allocator::system<int> allocator_type;
	typedef HList<int, allocator::ref<int, allocator_type> > list_on_ref_t;
	typedef list_on_ref_t::allocator_type ref_allocator;
	typedef ref_allocator::allocator_type true_allocator;
	true_allocator ta;
	ref_allocator ra( &ta );
	list_on_ref_t l( ra );
	l.push_back( 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "allocator::shared_pool" )
	HPool<HList<int>::node_size::value> pool;
	allocator::shared_pool<HList<int>::node_type> alloc( pool );
	HList<int, allocator::shared_pool<int> > l( alloc );
	l.push_back( 1 );
TUT_TEARDOWN()

}


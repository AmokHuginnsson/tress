/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_allocator.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/allocator.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include <yaal/hcore/hlist.hxx>
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_allocator );
TUT_TEST_GROUP( tut_yaal_allocator, "yaal::allocator" );

TUT_UNIT_TEST( 1, "allocator::system" )
	HList<int, allocator::system<int> > l;
	l.push_back( 1 );
TUT_TEARDOWN()


TUT_UNIT_TEST( 2, "allocator::pool" )
	HList<int, allocator::pool<int> > l;
	l.push_back( 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "allocator::ref<allocator::system>" )
	typedef allocator::system<int> allocator_type;
	typedef HList<int, allocator::ref<int, allocator_type> > list_on_ref_t;
	typedef list_on_ref_t::allocator_type ref_allocator;
	typedef ref_allocator::allocator_type true_allocator;
	true_allocator ta;
	ref_allocator ra( &ta );
	list_on_ref_t l( ra );
	l.push_back( 1 );
TUT_TEARDOWN()

}


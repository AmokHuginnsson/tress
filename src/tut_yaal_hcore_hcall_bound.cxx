/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcall_bound.cxx - this file is integral part of `tress' project.

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

TUT_UNIT_TEST( 1, "Constructor." )
	HBoundCall<> c( call( &tut_yaal_hcore_hcall_bound::foo, this ) );
	HBoundCall<> cc( call( &tut_yaal_hcore_hcall_bound::foo_const, this ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "compare with constant less." )
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ), call( &item_t::id, _1 ) < 50 );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "compare with constant greater." )
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator( l ), call( &item_t::id, _1 ) > 50 );
	copy( l.begin(), l.end(), stream_iterator( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

}


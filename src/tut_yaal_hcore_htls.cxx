/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_htls.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/htls.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

class TLSTest {
public:
	TLSTest( void ) {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	~TLSTest( void ) {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	void foo( void ) const {}
};

struct tut_yaal_hcore_htls : public simple_mock<tut_yaal_hcore_htls> {
	virtual ~tut_yaal_hcore_htls( void ) {}
	typedef HTLS<TLSTest> tls_t;
};
TUT_TEST_GROUP( tut_yaal_hcore_htls, "yaal::hcore::HTLS" );

TUT_UNIT_TEST( 1, "the test" )
	tls_t tls;
	tls->foo();
	external_lock_t l( tls.acquire() );
	tls_t::iterator it( tls.begin() );
	ENSURE( "inconsitient state", tls.operator->() == it->get() );
TUT_TEARDOWN()

}


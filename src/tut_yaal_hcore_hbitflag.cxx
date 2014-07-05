/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hbitflag.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hbitflag.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hbitflag );
TUT_TEST_GROUP( tut_yaal_hcore_hbitflag, "yaal::hcore::HBitFlag" );

struct A1 {};

TUT_UNIT_TEST( 1, "new flag" )
	typedef HBitFlag<A1> a_flag_t;
	a_flag_t const f1 = a_flag_t::new_flag();
	ENSURE_EQUALS( "bad flag index", f1.index(), 0 );
	ENSURE_NOT( "default flag have non zero value", f1 );
	a_flag_t const f2 = a_flag_t::new_flag();
	ENSURE_EQUALS( "bad flag index", f2.index(), 1 );
	ENSURE( "next flag has no value", f2 );
	a_flag_t const f3 = a_flag_t::new_flag();
	ENSURE_EQUALS( "bad flag index", f3.index(), 2 );
	ENSURE( "next flag has no value", f3 );
	ENSURE( "new_flag failed", f2 != f3 );
	a_flag_t::new_flag(); /* Can fail assertion if buggy. */
TUT_TEARDOWN()

struct A1c {};

TUT_UNIT_TEST( 0x1c, "copy constructor" )
	typedef HBitFlag<A1c> a_flag_t;
	a_flag_t const f1 = a_flag_t::new_flag();
	ENSURE_NOT( "default flag have non zero value", f1 );
	a_flag_t const f2 = a_flag_t::new_flag();
	ENSURE( "next flag has no value", f2 );
	a_flag_t const f3 = a_flag_t::new_flag();
	ENSURE( "next flag has no value", f3 );
	ENSURE( "new_flag failed", f2 != f3 );
	a_flag_t::new_flag(); /* Can fail assertion if buggy. */
	a_flag_t f1c( f1 );
	a_flag_t f2c( f2 );
	a_flag_t f3c( f3 );
	ENSURE( "copy constructor failed", f1c == f1 );
	ENSURE( "copy constructor failed", f2c == f2 );
	ENSURE( "copy constructor failed", f3c == f3 );
TUT_TEARDOWN()

struct A2 {};

TUT_UNIT_TEST( 2, "or" )
	typedef HBitFlag<A2> a_flag_t;
	a_flag_t::new_flag();
	a_flag_t const f1 = a_flag_t::new_flag();
	a_flag_t const f2 = a_flag_t::new_flag();
	ENSURE( "or failed", ( f1 | f2 ) != f1 );
	ENSURE( "or failed", ( f1 | f2 ) != f2 );
	a_flag_t::new_flag(); /* Can fail assertion if buggy. */
TUT_TEARDOWN()

struct A3 {};

TUT_UNIT_TEST( 3, "and" )
	typedef HBitFlag<A3> a_flag_t;
	a_flag_t::new_flag();
	a_flag_t const f1 = a_flag_t::new_flag();
	a_flag_t const f2 = a_flag_t::new_flag();
	a_flag_t const f3 = f1 | f2;
	ENSURE( "mew failed", f1 != f2 );
	ENSURE( "or failed", f1 != f3 );
	ENSURE( "or failed", f2 != f3 );
	ENSURE( "or failed", ( f1 | f2 ) == f3 );
	ENSURE_NOT( "and failed", f1 & f2 );
	ENSURE( "and failed", ( f1 & f3 ) == f1 );
	ENSURE( "and failed", ( f2 & f3 ) == f2 );
	a_flag_t::new_flag(); /* Can fail assertion if buggy. */
TUT_TEARDOWN()

struct A4 {};

TUT_UNIT_TEST( 4, "xor" )
	typedef HBitFlag<A4> a_flag_t;
	a_flag_t::new_flag();
	a_flag_t const f1 = a_flag_t::new_flag();
	a_flag_t const f2 = a_flag_t::new_flag();
	a_flag_t const fx12 = f1 ^ f2;
	ENSURE_THROW( "composite flag returned index", fx12.index(), HFailedAssertion );
	ENSURE( "xor failed", ( fx12 & f1 ) == f1 );
	ENSURE( "xor failed", ( fx12 & f2 ) == f2 );
	a_flag_t const fx121 = fx12 ^ f1;
	a_flag_t const fx122 = fx12 ^ f2;
	ENSURE( "xor failed", fx121 == f2 );
	ENSURE( "xor failed", fx122 == f1 );
TUT_TEARDOWN()

struct A5 {};

TUT_UNIT_TEST( 5, "not" )
	typedef HBitFlag<A5> a_flag_t;
	a_flag_t const def = a_flag_t::new_flag();
	a_flag_t const f1 = a_flag_t::new_flag();
	a_flag_t const f2 = a_flag_t::new_flag();
	a_flag_t const f1n = ~f1;
	a_flag_t const f2n = ~f2;
	ENSURE_NOT( "not failed", f1 & f1n );
	ENSURE_NOT( "not failed", f2 & f2n );
	ENSURE( "not failed", ( f1 | f1n ) == ~def );
	ENSURE( "not failed", ( f2 | f2n ) == ~def );
TUT_TEARDOWN()

}


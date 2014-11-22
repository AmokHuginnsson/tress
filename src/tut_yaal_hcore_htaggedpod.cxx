/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_htaggedpod.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/htaggedpod.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace std {

template<typename type, typename tag>
std::ostream& operator << ( std::ostream& out, yaal::hcore::HTaggedPOD<type, tag> const& tp_ ) {
	out << tp_.get();
	return ( out );
}

}

namespace tut {

#define DEFINE_TAGGED_TYPE( type, tagged_name ) \
	struct type##tagged_name {}; \
	typedef HTaggedPOD<type, type##tagged_name> tagged_name;

#define VERIFY_EXPRESSION_TYPE( expr, type ) \
	do { \
		struct M_YAAL_AUTO_ID( type ) { \
			static void f( type ) {} \
			static void f( ... ) { \
				FAIL( "bad overload called for " #type ); \
			} \
		}; \
		M_YAAL_AUTO_ID( type )::f( expr ); \
	} while ( false )

TUT_SIMPLE_MOCK( tut_yaal_hcore_htaggedpod );
TUT_TEST_GROUP( tut_yaal_hcore_htaggedpod, "yaal::hcore::HTaggedPOD" );

DEFINE_TAGGED_TYPE(i32_t, Uid)
DEFINE_TAGGED_TYPE(i64_t, Uid64)
DEFINE_TAGGED_TYPE(i32_t, Gid)

TUT_UNIT_TEST( "all tests" )
	Uid u1 = 10;
	Uid u2 = 20;

	// ... have all operators that a normal integer has
	ENSURE(u1 < u2);
	ENSURE(u1 != u2);

	u1 << 1;
	VERIFY_EXPRESSION_TYPE( u1 && u2, bool );
	VERIFY_EXPRESSION_TYPE( u1 || u2, bool );
	VERIFY_EXPRESSION_TYPE( !u1, bool );
//	VERIFY_TYPES_EQUAL(~u1, u1);
	ENSURE_EQUALS( ( u1 && u2 ), u1.get() && u2.get() );
	ENSURE_EQUALS( ( u1 || u2 ), u1.get() || u2.get() );
	ENSURE_EQUALS( ( ~u1 ).get(), ~( u1.get() ) );
	ENSURE_EQUALS( !u1, !( u1.get() ) );
	ENSURE_EQUALS( u1 << 1, ( u1.get() ) << 1 );

//	VERIFY_TYPES_EQUAL(-u1 + u2 + u1, u2);
//	VERIFY_TYPES_EQUAL(~u1, u1);
	ENSURE_EQUALS( +u1 - u2 - u1, -u2 );
	ENSURE_EQUALS( ( ~u1 ).get(), ~( u1.get() ) );

	// ... it can also be mixed with all integer plan types
	u1 = 1;
	ENSURE_EQUALS( u1, Uid( 1 ) );
	u1 = u1 + u2;
	ENSURE_EQUALS( u1, Uid( 21 ) );
	u1 = u2 + 1;
	ENSURE_EQUALS( u1, Uid( 21 ) );
	u1 = 1 + u2;
	ENSURE_EQUALS( u1, Uid( 21 ) );
	ENSURE_NOT( 1 == u1 );

	Uid64 u64_1 = u32_t(50);
	u64_1 = i8_t(1);
	u64_1 = u16_t(1);
	u64_1 = u64_1 + i32_t(1);
	u64_1 = u64_t(1) + u64_1;

	//// However mixing one type with another and all types of casts between them are forbidden:
	// Gid g1 = 30;
	// Gid g2 = 40;
	//
	// Gid g = u1; // Doesn't compile!
	//
	// Uid uu = g1; // Doesn't compile!
	// Uid uu2(g1); // Doesn't compile!
	// u1 = g1; // Doesn't compile!
	// u64_1 = u1; // Doesn't compile!
	//
	// u1 = u2 + g1; // Doesn't compile!
	// u1 = g1 + u2; // Doesn't compile!
	// u1 = 1 + g1; // Doesn't compile!
	// u1 = g1 + 1; // Doesn't compile!
	//
	// u1 == g1; // Doesn't compile!
	// ASSERT_NE(u1, g1); // Doesn't compile!
TUT_TEARDOWN()

}


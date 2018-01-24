/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/htaggedpod.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

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
	Uid u1{ 10 };
	Uid u2{ 20 };

	// ... have all operators that a normal integer has
	ENSURE(u1 < u2);
	ENSURE(u1 != u2);

	u1 << 1;
	VERIFY_EXPRESSION_TYPE( !u1, bool );
//	VERIFY_TYPES_EQUAL(~u1, u1);
	ENSURE_EQUALS( ( ~u1 ).get(), ~( u1.get() ) );
	ENSURE_EQUALS( !u1, !( u1.get() ) );
	ENSURE_EQUALS( u1 << 1, ( u1.get() ) << 1 );

//	VERIFY_TYPES_EQUAL(-u1 + u2 + u1, u2);
//	VERIFY_TYPES_EQUAL(~u1, u1);
	ENSURE_EQUALS( +u1 - u2 - u1, -u2 );
	ENSURE_EQUALS( ( ~u1 ).get(), ~( u1.get() ) );

	// ... it can also be mixed with all integer plan types
	u1 = Uid( 1 );
	ENSURE_EQUALS( u1, Uid( 1 ) );
	u1 = u1 + u2;
	ENSURE_EQUALS( u1, Uid( 21 ) );
	u1 = u2 + 1;
	ENSURE_EQUALS( u1, Uid( 21 ) );
	u1 = 1 + u2;
	ENSURE_EQUALS( u1, Uid( 21 ) );
	ENSURE_NOT( 1 == u1 );

	Uid64 u64_1{ u32_t(50) };
	u64_1 = Uid64( i8_t(1) );
	u64_1 = Uid64( u16_t(1) );
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


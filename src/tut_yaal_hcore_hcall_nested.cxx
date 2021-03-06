/* Read tress/LICENSE.md file for copyright and licensing information. */
#include <TUT/tut.hpp>

#include <yaal/hcore/hcall.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hcore_hcall.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_hcore_hcall_nested );
TUT_TEST_GROUP( tut_yaal_hcore_hcall_nested, "yaal::hcore::HCall,nested" );

namespace {
	char const err[] = "function bind failed";
}

TUT_UNIT_TEST( "nested call (x, y) -> (y) -> ()" )
	typedef call_calculator<HString (*)( int, int ), higher_order::placeholder<1> const&, int>::type::type func1_t;
	func1_t f( call( &foo2, _1, 2 ) );
	char const expected[] = "foo2: a1 = 1, a2 = 2";
	ENSURE_EQUALS( err, f( 1 ), expected );
	ENSURE_EQUALS( err, call( f, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int ), higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func2_t f2( call( &foo3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo3: a1 = 1, a2 = 2, a3 = 3";
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int ), higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func3_t f3( call( &foo4, _1, _2, _3, 4 ) );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo4: a1 = 1, a2 = 2, a3 = 3, a4 = 4";
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int, int ), higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, higher_order::placeholder<4> const&, int>::type::type func4_t;
	typedef call_calculator<func4_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func4_t f4( call( &foo5, _1, _2, _3, _4, 5 ) );
	func3_t f3( call( f4, _1, _2, _3, 4 ) );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo5: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5";
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( u, v, w, x, y, z ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int, int, int ),
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, int>::type::type func5_t;
	typedef call_calculator<func5_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, higher_order::placeholder<4> const&, int>::type::type func4_t;
	typedef call_calculator<func4_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func5_t f5( call( &foo6, _1, _2, _3, _4, _5, 6 ) );
	func4_t f4( call( f5, _1, _2, _3, _4, 5 ) );
	func3_t f3( call( f4, _1, _2, _3, 4 ) );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo6: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6";
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( t, u, v, w, x, y, z ) -> ( u, v, w, x, y, z ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int, int, int, int ),
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&, int>::type::type func6_t;
	typedef call_calculator<func6_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, int>::type::type func5_t;
	typedef call_calculator<func5_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, higher_order::placeholder<4> const&, int>::type::type func4_t;
	typedef call_calculator<func4_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func6_t f6( call( &foo7, _1, _2, _3, _4, _5, _6, 7 ) );
	func5_t f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	func4_t f4( call( f5, _1, _2, _3, _4, 5 ) );
	func3_t f3( call( f4, _1, _2, _3, 4 ) );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo7: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7";
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

#ifndef __sun__

TUT_UNIT_TEST( "nested call ( 8 args ) -> ( t, u, v, w, x, y, z ) -> ( u, v, w, x, y, z ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int, int, int, int, int ),
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&,
					higher_order::placeholder<7> const&, int>::type::type func7_t;
	typedef call_calculator<func7_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&, int>::type::type func6_t;
	typedef call_calculator<func6_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, int>::type::type func5_t;
	typedef call_calculator<func5_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, higher_order::placeholder<4> const&, int>::type::type func4_t;
	typedef call_calculator<func4_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func7_t f7( call( &foo8, _1, _2, _3, _4, _5, _6, _7, 8 ) );
	func6_t f6( call( f7, _1, _2, _3, _4, _5, _6, 7 ) );
	func5_t f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	func4_t f4( call( f5, _1, _2, _3, _4, 5 ) );
	func3_t f3( call( f4, _1, _2, _3, 4 ) );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo8: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8";
	ENSURE_EQUALS( err, f7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( 9 args ) -> ( 8 args ) -> ( 7 args ) -> ( 6 args ) -> ( v, w, x, y, z ) -> ( w, x, y, z ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int, int, int, int, int, int ),
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&,
					higher_order::placeholder<7> const&, higher_order::placeholder<8> const&, int>::type::type func8_t;
	typedef call_calculator<func8_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&,
					higher_order::placeholder<7> const&, int>::type::type func7_t;
	typedef call_calculator<func7_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&, int>::type::type func6_t;
	typedef call_calculator<func6_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, int>::type::type func5_t;
	typedef call_calculator<func5_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, higher_order::placeholder<4> const&, int>::type::type func4_t;
	typedef call_calculator<func4_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	func8_t f8( call( &foo9, _1, _2, _3, _4, _5, _6, _7, _8, 9 ) );
	func7_t f7( call( f8, _1, _2, _3, _4, _5, _6, _7, 8 ) );
	func6_t f6( call( f7, _1, _2, _3, _4, _5, _6, 7 ) );
	func5_t f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	func4_t f4( call( f5, _1, _2, _3, _4, 5 ) );
	func3_t f3( call( f4, _1, _2, _3, 4 ) );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func1_t f1( call( f2, _1, 2 ) );
	char const expected[] = "foo9: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9";
	ENSURE_EQUALS( err, f8( 1, 2, 3, 4, 5, 6, 7, 8 ), expected );
	ENSURE_EQUALS( err, f7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, call( f1, 1 )(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "nested call ( 10 args ) -> ( 9 args ) -> ( 8 args ) -> ( 7 args ) -> ( 6 args ) -> ( 5 args ) -> ( 4 args ) -> ( x, y, z ) -> ( y, z ) -> ( z ) -> ()" )
	typedef call_calculator<HString (*)( int, int, int, int, int, int, int, int, int, int ),
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&,
					higher_order::placeholder<7> const&, higher_order::placeholder<8> const&,
					higher_order::placeholder<9> const&, int>::type::type func9_t;
	typedef call_calculator<func9_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&,
					higher_order::placeholder<7> const&, higher_order::placeholder<8> const&, int>::type::type func8_t;
	typedef call_calculator<func8_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&,
					higher_order::placeholder<7> const&, int>::type::type func7_t;
	typedef call_calculator<func7_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, higher_order::placeholder<6> const&, int>::type::type func6_t;
	typedef call_calculator<func6_t&,
					higher_order::placeholder<1> const&, higher_order::placeholder<2> const&,
					higher_order::placeholder<3> const&, higher_order::placeholder<4> const&,
					higher_order::placeholder<5> const&, int>::type::type func5_t;
	typedef call_calculator<func5_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, higher_order::placeholder<4> const&, int>::type::type func4_t;
	typedef call_calculator<func4_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, higher_order::placeholder<3> const&, int>::type::type func3_t;
	typedef call_calculator<func3_t&, higher_order::placeholder<1> const&, higher_order::placeholder<2> const&, int>::type::type func2_t;
	typedef call_calculator<func2_t&, higher_order::placeholder<1> const&, int>::type::type func1_t;
	typedef call_calculator<func1_t&, int>::type::type func0_t;
	func9_t f9( call( &foo10, _1, _2, _3, _4, _5, _6, _7, _8, _9, 10 ) );
	func9_t const& fc9( f9 );
	func8_t f8( call( f9, _1, _2, _3, _4, _5, _6, _7, _8, 9 ) );
	func8_t const& fc8( f8 );
	func7_t f7( call( f8, _1, _2, _3, _4, _5, _6, _7, 8 ) );
	func7_t const& fc7( f7 );
	func6_t f6( call( f7, _1, _2, _3, _4, _5, _6, 7 ) );
	func6_t const& fc6( f6 );
	func5_t f5( call( f6, _1, _2, _3, _4, _5, 6 ) );
	func5_t const& fc5( f5 );
	func4_t f4( call( f5, _1, _2, _3, _4, 5 ) );
	func4_t const& fc4( f4 );
	func3_t f3( call( f4, _1, _2, _3, 4 ) );
	func3_t const& fc3( f3 );
	func2_t f2( call( f3, _1, _2, 3 ) );
	func2_t const& fc2( f2 );
	func1_t f1( call( f2, _1, 2 ) );
	func1_t const& fc1( f1 );
	char const expected[] = "foo10: a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10";
	ENSURE_EQUALS( err, f9( 1, 2, 3, 4, 5, 6, 7, 8, 9 ), expected );
	ENSURE_EQUALS( err, fc9( 1, 2, 3, 4, 5, 6, 7, 8, 9 ), expected );
	ENSURE_EQUALS( err, f8( 1, 2, 3, 4, 5, 6, 7, 8 ), expected );
	ENSURE_EQUALS( err, fc8( 1, 2, 3, 4, 5, 6, 7, 8 ), expected );
	ENSURE_EQUALS( err, f7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, fc7( 1, 2, 3, 4, 5, 6, 7 ), expected );
	ENSURE_EQUALS( err, f6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, fc6( 1, 2, 3, 4, 5, 6 ), expected );
	ENSURE_EQUALS( err, f5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, fc5( 1, 2, 3, 4, 5 ), expected );
	ENSURE_EQUALS( err, f4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, fc4( 1, 2, 3, 4 ), expected );
	ENSURE_EQUALS( err, f3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, fc3( 1, 2, 3 ), expected );
	ENSURE_EQUALS( err, f2( 1, 2 ), expected );
	ENSURE_EQUALS( err, fc2( 1, 2 ), expected );
	ENSURE_EQUALS( err, f1( 1 ), expected );
	ENSURE_EQUALS( err, fc1( 1 ), expected );
#ifndef _MSC_VER
	func0_t f0( call( f1, 1 ) );
	func0_t const& fc0( f0 );
	ENSURE_EQUALS( err, f0(), expected );
	ENSURE_EQUALS( err, fc0(), expected );
#endif /* #ifndef _MSC_VER */
TUT_TEARDOWN()

#endif /* #ifndef __sun__ */

}


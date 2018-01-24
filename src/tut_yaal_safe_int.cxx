/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/safe_int.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_safe_int );
TUT_TEST_GROUP( tut_yaal_safe_int, "yaal::safe_int" );


TUT_UNIT_TEST( "add" )
	ENSURE_EQUALS( +safe_int::add<char signed>( 1, 2 ), 3 );
	ENSURE_EQUALS( +safe_int::add<char signed>( -1, -2 ), -3 );
	ENSURE_EQUALS( +safe_int::add<char signed>( 1, -2 ), -1 );
	ENSURE_EQUALS( +safe_int::add<char signed>( -2, 1 ), -1 );
	ENSURE_THROW_AUTO( safe_int::add<char signed>( 110, 110 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::add<char signed>( -110, -110 ), HOutOfRangeException );
	ENSURE_EQUALS( +safe_int::add<char unsigned>( 1, 2 ), 3 );
	ENSURE_THROW_AUTO( safe_int::add<char unsigned>( 140, 130 ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sub" )
	ENSURE_EQUALS( +safe_int::sub<char signed>( 2, 1 ), 1 );
	ENSURE_EQUALS( +safe_int::sub<char signed>( -2, 1 ), -3 );
	ENSURE_EQUALS( +safe_int::sub<char signed>( 1, -2 ), 3 );
	ENSURE_EQUALS( +safe_int::sub<char signed>( -1, -2 ), 1 );
	ENSURE_THROW_AUTO( safe_int::sub<char signed>( -100, 100 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::sub<char signed>( 100, -100 ), HOutOfRangeException );
	ENSURE_EQUALS( +safe_int::sub<char unsigned>( 2, 1 ), 1 );
	ENSURE_THROW_AUTO( safe_int::sub<char unsigned>( 1, 2 ), HOutOfRangeException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "mul" )
	ENSURE_EQUALS( +safe_int::mul<char signed>( 2, 3 ), 6 );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( 22, 33 ), HOutOfRangeException );
	ENSURE_EQUALS( +safe_int::mul<char signed>( -2, 3 ), -6 );
	ENSURE_EQUALS( +safe_int::mul<char signed>( -2, -3 ), 6 );
	ENSURE_EQUALS( +safe_int::mul<char signed>( 2, -3 ), -6 );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( -22, -33 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( -22, 33 ), HOutOfRangeException );
	ENSURE_THROW_AUTO( safe_int::mul<char signed>( 22, -33 ), HOutOfRangeException );
	ENSURE_EQUALS( safe_int::mul<char unsigned>( 2, 3 ), 6 );
	ENSURE_THROW_AUTO( safe_int::mul<char unsigned>( 22, 33 ), HOutOfRangeException );
TUT_TEARDOWN()

}


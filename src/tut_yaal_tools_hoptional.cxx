/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hoptional.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hoptional );
TUT_TEST_GROUP( tut_yaal_tools_hoptional, "yaal::tools::HOptional" );

TUT_UNIT_TEST( "default constructor" )
	HOptional<int> opt;
	ENSURE_EQUALS( "bad initialization status", opt ? true : false, false );
	ENSURE_THROW( "dereferencing unititialized optional", *opt, HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "initialized optional" )
	HOptional<int> opt( 7 );
	ENSURE_EQUALS( "bad initialization status", opt ? true : false, true );
	ENSURE_EQUALS( "bad value stored/retrieved", *opt, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy constructor" )
	HOptional<HString> opt( "Ala" );
	HOptional<HString> str( opt );
	ENSURE_EQUALS( "bad value", *opt, "Ala" );
	ENSURE_EQUALS( "bad copy", *str, "Ala" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "const reference" )
	HString const ala( "ala" );
	HOptional<HString const&> opt( ala );
	ENSURE_EQUALS( "bad value", &*opt, &ala );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap on const reference" )
	HString const ala( "ala" );
	HString const kot( "kot" );
	HOptional<HString const&> optAla( ala );
	HOptional<HString const&> optKot( kot );
	ENSURE_EQUALS( "bad value", &*optAla, &ala );
	ENSURE_EQUALS( "bad value", &*optKot, &kot );
	swap( optAla, optKot );
	ENSURE_EQUALS( "bad value", &*optAla, &kot );
	ENSURE_EQUALS( "bad value", &*optKot, &ala );
TUT_TEARDOWN()

TUT_UNIT_TEST( "non-const reference to const reference" )
	HString ala( "ala" );
	HString const kot( "kot" );
	HOptional<HString&> optAla( ala );
	HOptional<HString const&> optKot( kot );
	optKot = optAla;
TUT_TEARDOWN()

TUT_UNIT_TEST( "non-const to const" )
	HOptional<HString> const optAla( "ala" );
	HOptional<HString> optKot( "kot" );
	optKot = optAla;
TUT_TEARDOWN()

}


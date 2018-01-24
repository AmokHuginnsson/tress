/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/collections.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::collections;
using namespace yaal::ansi;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_collections );
TUT_TEST_GROUP( tut_yaal_tools_collections, "yaal::tools::collections" );

TUT_UNIT_TEST( "add_orderly" )
	Stringifier stringifier;
	HList<char> l;
	add_orderly( l, 'd' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 1 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "d" );
	add_orderly( l, 'g' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 2 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "dg" );
	add_orderly( l, 'b' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 3 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "bdg" );
	add_orderly( l, 'e' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 4 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "bdeg" );
	add_orderly( l, 'c' );
	add_orderly( l, 'a' );
	add_orderly( l, 'h' );
	add_orderly( l, 'f' );
	ENSURE_EQUALS( "add_orderly failed", l.size(), 8 );
	ENSURE_EQUALS( "add_orderly failed", stringifier.to_string<char>( l ), "abcdefgh" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "n_th" )
	list_t l;
	l.push_back( '1' );
	l.push_back( '2' );
	l.push_back( '3' );
	l.push_back( '4' );
	l.push_back( '5' );
	l.push_back( '6' );
	for ( int i = 0; i < 6; ++ i ) {
		ENSURE_EQUALS( "n_th( n ) gives bogus result", *n_th( l, i ), i + '1' );
	}
	ENSURE_THROW( "index too big and ok ??", n_th( l, 6 ), HException );
	ENSURE_THROW( "index out of range and ok ??", n_th( l, -7 ), HException );
TUT_TEARDOWN()


}


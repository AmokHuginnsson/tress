/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/prime.hxx>
#include <yaal/tools/assign.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_find_primes );
TUT_TEST_GROUP( tut_yaal_tools_find_primes, "yaal::tools::find_primes" );

TUT_UNIT_TEST( "input sanity check" )
	primes_t p;
	ENSURE_THROW( "invalid range accepted in find_primes()", find_primes( p, 10, 1 ), HException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_primes( 0, 20 )" )
	primes_t p;
	find_primes( p, 0, 20 );
	primes_t expect = array<primes_t::value_type>( 2, 3, 5, 7, 11, 13, 17, 19 );
	ENSURE_EQUALS( "find_primes failed", p, expect );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_primes( huge, huge + 3 )" )
	int long unsigned primeToFind( 1073741789 );
	primes_t p;
	find_primes( p, primeToFind - 1, primeToFind + 1 );
	ENSURE_EQUALS( "find_primes on huge failed", p.get_size(), 1 );
	ENSURE_EQUALS( "find_primes on huge failed", p[0], primeToFind );
TUT_TEARDOWN()

TUT_UNIT_TEST( "find_primes() - no primes" )
	primes_t p;
	find_primes( p, 524, 540 );
	ENSURE( "find_primes found bogus prime", p.is_empty() );
TUT_TEARDOWN()

}


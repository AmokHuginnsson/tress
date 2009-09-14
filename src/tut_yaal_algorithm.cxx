/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_algorithm.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You cannot use any part of sources of this software.
  2. You cannot redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you cannot demand any fees
     for this software.
     You cannot even demand cost of the carrier (CD for example).
  5. You cannot include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_yaal_algorithm );
TUT_TEST_GROUP_N( tut_yaal_algorithm, "yaal::algorithm" );

TUT_UNIT_TEST_N( 1, "reverse" )
	int const LENE = 4;
	HPointer<char, HPointerArray> spe( new char[ LENE ] );
	char* se( spe.raw() );
	char const* datae = "1234";
	char const* revdatae = "4321";
	copy_n( datae, LENE, se );
	ENSURE_EQUALS( "test init failed (even)", HString( se ), HString( datae ) );
	reverse( se, se + LENE );
	ENSURE_EQUALS( "reverse of even number of elements failed", HString( se ), HString( revdatae ) );

	int const LENO = 5;
	HPointer<char, HPointerArray> spo( new char[ LENO ] );
	char* so( spo.raw() );
	char const* datao = "12345";
	char const* revdatao = "54321";
	copy_n( datao, LENO, so );
	ENSURE_EQUALS( "test init failed (odd)", HString( so ), HString( datao ) );
	reverse( so, so + LENO );
	ENSURE_EQUALS( "reverse of even number of elements failed", HString( so ), HString( revdatao ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "next_permutation" )
	int const LEN = 4;
	HPointer<char, HPointerArray> sp( new char[ LEN ] );
	char* s( sp.raw() );
	copy_n( "1234", LEN, s );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "2134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "2143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "2314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "2341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "2413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "2431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "3124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "3142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "3214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "3241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "3412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "3421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "4123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "4132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "4213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "4231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "4312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "4321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1234" ) );
TUT_TEARDOWN()

}


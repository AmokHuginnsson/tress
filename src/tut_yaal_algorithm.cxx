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

#include <algorithm>
#ifdef __GNUC__
#include <ext/algorithm>
#endif /* #ifdef __GNUC__ */

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
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
	HPointer<char, HPointerArray> spe( new char[ LENE + 1 ] );
	char* se( spe.raw() );
	char const* datae = "1234\0";
	char const* revdatae = "4321\0";
	copy_n( datae, LENE + 1, se );
	ENSURE_EQUALS( "test init failed (even)", HString( se ), HString( datae ) );
	reverse( se, se + LENE );
	ENSURE_EQUALS( "reverse of even number of elements failed", HString( se ), HString( revdatae ) );

	int const LENO = 5;
	HPointer<char, HPointerArray> spo( new char[ LENO + 1 ] );
	char* so( spo.raw() );
	char const* datao = "12345\0";
	char const* revdatao = "54321\0";
	copy_n( datao, LENO + 1, so );
	ENSURE_EQUALS( "test init failed (odd)", HString( so ), HString( datao ) );
	reverse( so, so + LENO );
	ENSURE_EQUALS( "reverse of even number of elements failed", HString( so ), HString( revdatao ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "next_permutation, len = 1 (even)" )
	int const LEN = 1;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "next_permutation, len = 2 (even)" )
	int const LEN = 2;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "12\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "next_permutation (odd)" )
	int const LEN = 3;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "123\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "123" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "next_permutation (even)" )
	int const LEN = 4;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1234\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "2431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "3421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "4321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1234" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "next_permutation (odd)" )
	int const LEN = 5;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "12345\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12345" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12354" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12435" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12453" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12534" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12543" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13245" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13254" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13425" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13452" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13524" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "13542" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14235" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14253" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14325" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14352" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14523" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "14532" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "15432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21345" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21354" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21435" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21453" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21534" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "21543" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23145" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23154" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23415" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23451" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23514" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "23541" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24135" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24153" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24315" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24351" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24513" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "24531" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "25431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31245" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31254" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31425" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31452" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31524" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "31542" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32145" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32154" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32415" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32451" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32514" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "32541" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34125" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34152" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34215" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34251" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34512" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "34521" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "35421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41235" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41253" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41325" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41352" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41523" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "41532" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42135" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42153" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42315" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42351" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42513" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "42531" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43125" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43152" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43215" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43251" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43512" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "43521" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "45321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "51432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "52431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "53421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "54321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "12345" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "prev_permutation, len = 1 (even)" )
	int const LEN = 1;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "prev_permutation, len = 2 (even)" )
	int const LEN = 2;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "21\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "prev_permutation (odd)" )
	int const LEN = 3;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "321\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "321" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "prev_permutation (even)" )
	int const LEN = 4;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "4321\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3421" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3412" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3241" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3214" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3142" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "3124" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2431" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2413" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2341" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2314" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2143" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "2134" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1432" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1423" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1342" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1324" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1243" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1234" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "4321" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "prev_permutation (odd)" )
	int const LEN = 5;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "54321\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53421" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53412" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53241" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53214" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53142" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "53124" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52431" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52413" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52341" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52314" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52143" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "52134" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51432" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51423" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51342" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51324" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51243" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "51234" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45321" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45312" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45231" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45213" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45132" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "45123" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43521" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43512" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43251" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43215" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43152" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "43125" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42531" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42513" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42351" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42315" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42153" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "42135" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41532" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41523" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41352" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41325" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41253" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "41235" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35421" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35412" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35241" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35214" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35142" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "35124" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34521" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34512" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34251" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34215" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34152" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "34125" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32541" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32514" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32451" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32415" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32154" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "32145" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31542" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31524" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31452" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31425" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31254" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "31245" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25431" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25413" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25341" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25314" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25143" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "25134" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24531" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24513" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24351" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24315" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24153" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "24135" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23541" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23514" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23451" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23415" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23154" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "23145" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21543" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21534" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21453" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21435" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21354" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "21345" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15432" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15423" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15342" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15324" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15243" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "15234" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14532" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14523" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14352" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14325" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14253" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "14235" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13542" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13524" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13452" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13425" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13254" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "13245" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12543" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12534" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12453" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12435" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12354" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "12345" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "54321" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "is_heap" )
	std_vector_t v( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	for ( int i( 2 ); i < countof ( _testData_[0] ); ++ i )
		{
#ifndef _MSC_VER
		ENSURE_EQUALS( "stdext::is_heap false positive: " + lexical_cast<HString>( i ), stdext::is_heap( v.begin(), v.begin() + i ), false );
#endif /* #ifndef _MSC_VER */
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( v.begin(), v.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		ENSURE_EQUALS( "yaal::is_heap false negative: " + lexical_cast<HString>( i ), yaal::is_heap( v.begin(), v.begin() + i ), true );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "push_heap" )
	std_vector_t v( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	int_array_t a( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	for ( int i( 2 ); i <= countof ( _testData_[0] ); ++ i )
		{
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::push_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
		ENSURE_EQUALS( "yaal::push_heap wrong: " + lexical_cast<HString>( i ), a, v );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "pop_heap" )
	std_vector_t v( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	int_array_t a( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	for ( int i( 2 ); i <= countof ( _testData_[0] ); ++ i )
		{
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::push_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
		ENSURE_EQUALS( "yaal::push_heap wrong: " + lexical_cast<HString>( i ), a, v );
		}

	for ( int i( countof ( _testData_[0] ) ); i > 0; -- i )
		{
		std::pop_heap( v.begin(), v.begin() + i );
		pop_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::pop_heap wrong: " + lexical_cast<HString>( i ), a, v );
		ENSURE_EQUALS( "yaal::pop_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i - 1 ), true );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "make_heap" )
	std_vector_t v( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	int_array_t a( _testData_[0], _testData_[0] + countof ( _testData_[0] ) );
	ENSURE_EQUALS( "yaal::is_heap false positive", yaal::is_heap( a.begin(), a.end() ), false );
	std::make_heap( v.begin(), v.end() );
	make_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::make_heap failed", yaal::is_heap( a.begin(), a.end() ), true );
	ENSURE_EQUALS( "yaal::make_heap wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 16, "sort_heap" )
	std_vector_t v( 100 );
	int_array_t a( 100 );
	std::generate( v.begin(), v.end(), HRandomizer( 0, 255 ) );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0, 255 ) );
	*v.rbegin() = -1;
	*a.rbegin() = -1;
	ENSURE_EQUALS( "wrong generation", a, v );
	clog << a << endl;
	ENSURE_EQUALS( "yaal::is_heap false positive", yaal::is_heap( a.begin(), a.end() ), false );
	std::make_heap( v.begin(), v.end() );
	make_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::make_heap failed", yaal::is_heap( a.begin(), a.end() ), true );
	/* ENSURE_EQUALS( "yaal::make_heap wrong", a, v ); */
	std::sort_heap( v.begin(), v.end() );
	sort_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::sort_heap wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 17, "sort" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0, 255 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::sort( v.begin(), v.end() );
	sort( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 18, "unique" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0, 255 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::sort( v.begin(), v.end() );
	sort( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::sort wrong", a, v );
	clog << a << endl;
	v.erase( std::unique( v.begin(), v.end() ), v.end() );
	a.erase( unique( a.begin(), a.end() ), a.end() );
	ENSURE_EQUALS( "yaal::sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 19, "rotate" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	int_array_t::iterator it( rotate( a.begin(), a.begin() + 33, a.end() ) );
	std::rotate( v.begin(), v.begin() + 33, v.end() );
	ENSURE_EQUALS( "yaal::rotate wrong", a, v );
	clog << "(" << *it << ") " << a << endl;
	int_array_t::iterator it2( rotate( a.begin(), it, a.end() ) );
	std::rotate( v.begin(), v.begin() + 67, v.end() );
	ENSURE_EQUALS( "yaal::rotate wrong", a, v );
	clog << "(" << *it2 << ") " << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 20, "inplace_merge" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	int_array_t::iterator it( rotate( a.begin(), a.begin() + 33, a.end() ) );
	std::rotate( v.begin(), v.begin() + 33, v.end() );
	ENSURE_EQUALS( "yaal::rotate wrong", a, v );
	clog << "(" << *it << ") " << a << endl;
	inplace_merge( a.begin(), it, a.end() );
	std::inplace_merge( v.begin(), v.begin() + 67, v.end() );
	ENSURE_EQUALS( "yaal::inplace_merge wrong", a, v );
	clog << a << endl;
	int arrTempl[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 3, 6, 9, 15, 18, 21, 24, 27, 30 };
	int_array_t arr( arrTempl, arrTempl + countof ( arrTempl ) );
	std_vector_t varr( &*arr.begin(), &*arr.begin() + arr.get_size() );
	std::clog << varr << std::endl;
	std::inplace_merge( varr.begin(), varr.begin() + 9, varr.end() );
	std::clog << varr << std::endl;
	clog << arr << endl;
	inplace_merge( arr.begin(), arr.begin() + 9, arr.end() );
	clog << arr << endl;
	ENSURE_EQUALS( "yaal::inplace_merge wrong", arr, varr );
	std::copy( arrTempl, arrTempl + countof ( arrTempl ), varr.begin() );
	std::rotate( varr.begin(), varr.begin() + 9, varr.end() );
	std::clog << varr << std::endl;
	copy( arrTempl, arrTempl + countof ( arrTempl ), arr.begin() );
	rotate( arr.begin(), arr.begin() + 9, arr.end() );
	clog << arr << endl;
	ENSURE_EQUALS( "yaal::copy + yaal::rotate wrong", arr, varr );
	std::inplace_merge( varr.begin(), varr.begin() + 9, varr.end() );
	std::clog << varr << std::endl;
	inplace_merge( arr.begin(), arr.begin() + 9, arr.end() );
	clog << arr << endl;
	ENSURE_EQUALS( "yaal::inplace_merge wrong", arr, varr );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 21, "insert_sort" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0, 255 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::sort( v.begin(), v.end() );
	insert_sort( a.begin(), a.end(), less<int>() );
	ENSURE_EQUALS( "yaal::insert_sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "stable_sort" )
	int_array_t a( 100 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0, 255 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	clog << a << endl;
	std::stable_sort( v.begin(), v.end() );
	stable_sort( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
	clog << a << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 50, "sort speed" )
	int_array_t a( 50000 );
		{
		yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
			{
			HClock c;
			std::stable_sort( v.begin(), v.end() );
			clog << "*speed* std::stable_sort = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
			}
			{
			HClock c;
			stable_sort( a.begin(), a.end() );
			clog << "*speed* yaal::stable_sort = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
			}
		ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
		}
		{
		yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
			{
			HClock c;
			std::sort( v.begin(), v.end() );
			clog << "*speed* std::sort = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
			}
			{
			HClock c;
			sort( a.begin(), a.end() );
			clog << "*speed* yaal::sort = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
			}
		ENSURE_EQUALS( "yaal::sort wrong", a, v );
		}
TUT_TEARDOWN()

}


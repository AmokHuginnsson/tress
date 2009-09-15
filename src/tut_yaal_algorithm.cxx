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
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "next_permutation, len = 2 (even)" )
	int const LEN = 2;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "12\0", LEN + 1, s );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "next_permutation (odd)" )
	int const LEN = 3;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "123\0", LEN + 1, s );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "123" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "next_permutation (even)" )
	int const LEN = 4;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1234\0", LEN + 1, s );
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

TUT_UNIT_TEST_N( 6, "next_permutation (odd)" )
	int const LEN = 5;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "12345\0", LEN + 1, s );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12345" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12354" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12435" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12453" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12534" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12543" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "13245" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "13254" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "13425" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "13452" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "13524" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "13542" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "14235" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "14253" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "14325" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "14352" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "14523" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "14532" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "15234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "15243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "15324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "15342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "15423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "15432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21345" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21354" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21435" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21453" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21534" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "21543" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "23145" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "23154" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "23415" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "23451" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "23514" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "23541" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "24135" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "24153" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "24315" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "24351" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "24513" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "24531" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "25134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "25143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "25314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "25341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "25413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "25431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "31245" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "31254" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "31425" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "31452" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "31524" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "31542" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "32145" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "32154" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "32415" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "32451" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "32514" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "32541" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "34125" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "34152" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "34215" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "34251" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "34512" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "34521" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "35124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "35142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "35214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "35241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "35412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "35421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "41235" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "41253" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "41325" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "41352" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "41523" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "41532" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "42135" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "42153" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "42315" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "42351" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "42513" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "42531" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "43125" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "43152" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "43215" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "43251" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "43512" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "43521" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "45123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "45132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "45213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "45231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "45312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "45321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "51234" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "51243" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "51324" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "51342" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "51423" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "51432" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "52134" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "52143" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "52314" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "52341" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "52413" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "52431" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "53124" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "53142" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "53214" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "53241" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "53412" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "53421" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "54123" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "54132" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "54213" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "54231" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "54312" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), true );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "54321" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_premutation failed", HString( s ), HString( "12345" ) );
TUT_TEARDOWN()

}

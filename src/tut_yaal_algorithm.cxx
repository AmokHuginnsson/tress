/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_algorithm.cxx - this file is integral part of `tress' project.

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

#include <algorithm>
#ifdef __GNUC__
#include <ext/algorithm>
#endif /* #ifdef __GNUC__ */

#include "tut_helpers.hxx"
#include <TUT/tut.hpp>

#include <yaal/hcore/algorithm.hxx>
#include <yaal/hcore/hhashset.hxx>
#include <yaal/hcore/hrandomizer.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::ansi;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_algorithm );
TUT_TEST_GROUP( tut_yaal_algorithm, "yaal::algorithm" );

TUT_UNIT_TEST( 1, "reverse" )
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
	HString s1( "!ABCa#$q%^&w0def1ghi2@" );
	HString s2( "@2ihg1fed0w&^%q$#aCBA!" );
	reverse( s2.begin(), s2.end() );
	ENSURE_EQUALS( "reverse on HString failed", s2, s1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "next_permutation, len = 1 (even)" )
	int const LEN = 1;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1\0", LEN + 1, s );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "last permutation test failed", next_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "next_permutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "next_permutation, len = 2 (even)" )
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

TUT_UNIT_TEST( 4, "next_permutation, len = 3 (odd)" )
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

TUT_UNIT_TEST( 5, "next_permutation len = 4 (even)" )
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

TUT_UNIT_TEST( 6, "next_permutation len = 5 (odd)" )
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

TUT_UNIT_TEST( 7, "prev_permutation, len = 1 (even)" )
	int const LEN = 1;
	HPointer<char, HPointerArray> sp( new char[ LEN + 1 ] );
	char* s( sp.raw() );
	copy_n( "1\0", LEN + 1, s );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1" ) );
	ENSURE_EQUALS( "first permutation test failed", prev_permutation( s, s + LEN ), false );
	ENSURE_EQUALS( "prev_permutation failed", HString( s ), HString( "1" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "prev_permutation, len = 2 (even)" )
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

TUT_UNIT_TEST( 9, "prev_permutation len = 3 (odd)" )
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

TUT_UNIT_TEST( 10, "prev_permutation len = 4 (even)" )
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

TUT_UNIT_TEST( 11, "prev_permutation len = 5 (odd)" )
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

TUT_UNIT_TEST( 12, "is_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	for ( int i( 2 ); i < countof ( _testData_[0] ); ++ i ) {
#ifndef _MSC_VER
		ENSURE_EQUALS( "stdext::is_heap false positive: " + lexical_cast<HString>( i ), stdext::is_heap( v.begin(), v.begin() + i ), false );
#endif /* #ifndef _MSC_VER */
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( v.begin(), v.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		ENSURE_EQUALS( "yaal::is_heap false negative: " + lexical_cast<HString>( i ), yaal::is_heap( v.begin(), v.begin() + i ), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "push_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	for ( int i( 2 ); i <= countof ( _testData_[0] ); ++ i ) {
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::push_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
		ENSURE_EQUALS( "yaal::push_heap wrong: " + lexical_cast<HString>( i ), a, v );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "pop_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	for ( int i( 2 ); i <= countof ( _testData_[0] ); ++ i ) {
		ENSURE_EQUALS( "yaal::is_heap false positive: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), false );
		std::push_heap( v.begin(), v.begin() + i );
		push_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::push_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i ), true );
		ENSURE_EQUALS( "yaal::push_heap wrong: " + lexical_cast<HString>( i ), a, v );
	}

	for ( int i( countof ( _testData_[0] ) ); i > 0; -- i ) {
		std::pop_heap( v.begin(), v.begin() + i );
		pop_heap( a.begin(), a.begin() + i );
		ENSURE_EQUALS( "yaal::pop_heap wrong: " + lexical_cast<HString>( i ), a, v );
		ENSURE_EQUALS( "yaal::pop_heap failed: " + lexical_cast<HString>( i ), yaal::is_heap( a.begin(), a.begin() + i - 1 ), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "make_heap" )
	std_vector_t v( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t a( begin( _testData_[0] ), end( _testData_[0] ) );
	ENSURE_EQUALS( "yaal::is_heap false positive", yaal::is_heap( a.begin(), a.end() ), false );
	std::make_heap( v.begin(), v.end() );
	make_heap( a.begin(), a.end() );
	ENSURE_EQUALS( "yaal::make_heap failed", yaal::is_heap( a.begin(), a.end() ), true );
	ENSURE_EQUALS( "yaal::make_heap wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "sort_heap" )
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

TUT_UNIT_TEST( 17, "sort" )
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

TUT_UNIT_TEST( 18, "unique" )
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

TUT_UNIT_TEST( 19, "rotate" )
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

TUT_UNIT_TEST( 20, "inplace_merge" )
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

TUT_UNIT_TEST( 21, "insert_sort" )
	TIME_CONSTRAINT_EXEMPT(); {
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::forward() );
		clog << "*speed* yaal::insert_sort(forward) = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(forward) wrong", a, v ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::forward() );
		clog << "*speed* yaal::insert_sort(forward) sorted = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(forward) wrong", a, v );
} {
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::random_access() );
		clog << "*speed* yaal::insert_sort(random_access) = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(random_access) wrong", a, v ); {
		HClock c;
		insert_sort( a.begin(), a.end(), less<int>(), iterator_category::random_access() );
		clog << "*speed* yaal::insert_sort(random_access) = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
	}
	ENSURE_EQUALS( "yaal::insert_sort(random_access) wrong", a, v );
}
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "selection_sort" )
	TIME_CONSTRAINT_EXEMPT();
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() );
	HClock c;
	selection_sort( a.begin(), a.end(), less<int>() );
	clog << "*speed* yaal::selection_sort = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
	ENSURE_EQUALS( "yaal::selection_sort wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "heap_sort" )
	int_array_t a( 8000 );
	yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
	*a.rbegin() = -1;
	std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() );
	std::sort( v.begin(), v.end() );
	HClock c;
	heap_sort( a.begin(), a.end() );
	clog << "*speed* yaal::heap_sort = " << c.get_time_elapsed( HClock::UNIT::MILISECOND ) << endl;
	ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "stable_sort" )
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

TUT_UNIT_TEST( 25, "distance" )
	HArray<int> array( begin( _testData_[0] ), end( _testData_[0] ) );
	HDeque<int> deque( begin( _testData_[0] ), end( _testData_[0] ) );
	HList<int> list( begin( _testData_[0] ), end( _testData_[0] ) );
	HSet<int> set( begin( _testData_[0] ), end( _testData_[0] ) );
	HHashSet<int> hashSet( begin( _testData_[0] ), end( _testData_[0] ) );
	HRing<int> ring( ring::capacity( countof ( _testData_[0] ) * 2 ),
		begin( _testData_[0] ), end( _testData_[0] ) );
	using yaal::distance;
	ENSURE_EQUALS( "distance on HArray<> failed", distance( array.begin(), array.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HDeque<> failed", distance( deque.begin(), deque.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HList<> failed", distance( list.begin(), list.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HSet<> failed", distance( set.begin(), set.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HHashSet<> failed", distance( hashSet.begin(), hashSet.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "distance on HRing<> failed", distance( ring.begin(), ring.end() ), countof ( _testData_[0] ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "swap" )
	HArray<int> array( begin( _testData_[0] ), end( _testData_[0] ) );
	HDeque<int> deque( begin( _testData_[0] ), end( _testData_[0] ) );
	HList<int> list( begin( _testData_[0] ), end( _testData_[0] ) );
	HSet<int> set( begin( _testData_[0] ), end( _testData_[0] ) );
	HHashSet<int> hashSet( begin( _testData_[0] ), end( _testData_[0] ) );
	HRing<int> ring( ring::capacity( countof ( _testData_[0] ) * 2 ),
		begin( _testData_[0] ), end( _testData_[0] ) );
	using yaal::distance;
	HArray<int> array2;
	HDeque<int> deque2;
	HList<int> list2;
	HSet<int> set2;
	HHashSet<int> hashSet2;
	HRing<int> ring2;
	swap( array, array2 );
	swap( deque, deque2 );
	swap( list, list2 );
	swap( set, set2 );
	swap( hashSet, hashSet2 );
	swap( ring, ring2 );
	ENSURE_EQUALS( "swap on HArray<> failed", distance( array2.begin(), array2.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HDeque<> failed", distance( deque2.begin(), deque2.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HList<> failed", distance( list2.begin(), list2.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HSet<> failed", distance( set2.begin(), set2.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HHashSet<> failed", distance( hashSet2.begin(), hashSet2.end() ), countof ( _testData_[0] ) );
	ENSURE_EQUALS( "swap on HRing<> failed", distance( ring2.begin(), ring2.end() ), countof ( _testData_[0] ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "search" )
	char const S1[] = "Hello, world!";
	char const S2[] = "world";
	char const* p( search( S1, ( S1 + countof ( S1 ) - 1 ), S2, ( S2 + countof( S2 ) ) - 1 ) );
	ENSURE_EQUALS( "search failed", p, S1 + 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "find_first_of" )
	char const S1[] = "Hello, world!";
	char const S2[] = "world";
	char const S3[] = "word";
	char const* p( find_first_of( S1, ( S1 + countof ( S1 ) - 1 ), S2, ( S2 + countof( S2 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_of failed (world)", p, S1 + 2 );
	char const* p2( find_first_of( S1, ( S1 + countof ( S1 ) - 1 ), S3, ( S3 + countof( S3 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_of failed (word)", p2, S1 + 4 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "find_first_of(cond)" )
	typedef HPair<HString, HString> person_t;
	person_t a[] = { person_t( "Ala", "Kowalska" ), person_t( "Diana", "B³aszczyk" ), person_t( "Marcin", "Konarski" ), person_t( "Magdalena", "Rêbowska" ), person_t( "Wojciech", "Peisert" ) };
	HString n[] = { "Marcin", "Wojciech", "Magdalena" };
	person_t* p( find_first_of( a, a + countof( a ), n, n + countof ( n ), compose_binary( equal_to<HString>(), select1st<person_t>(), identity<HString>() ) ) );
	ENSURE_EQUALS( "find_first_of failed (word)", p, a + 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "find_first_not_of" )
	char const S1[] = "Hello, world!";
	char const S2[] = "worldH";
	char const S3[] = "worldHe";
	char const* p( find_first_not_of( S1, ( S1 + countof ( S1 ) - 1 ), S2, ( S2 + countof( S2 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_not_of failed (worldH)", p, S1 + 1 );
	char const* p2( find_first_not_of( S1, ( S1 + countof ( S1 ) - 1 ), S3, ( S3 + countof( S3 ) ) - 1 ) );
	ENSURE_EQUALS( "find_first_not_of failed (worldHe)", p2, S1 + 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 31, "find_first_not_of(cond)" )
	typedef HPair<HString, HString> person_t;
	person_t a[] = { person_t( "Ala", "Kowalska" ), person_t( "Diana", "B³aszczyk" ), person_t( "Marcin", "Konarski" ), person_t( "Magdalena", "Rêbowska" ), person_t( "Wojciech", "Peisert" ) };
	HString n[] = { "Ala", "Diana", "Magdalena" };
	person_t* p( find_first_not_of( a, a + countof( a ), n, n + countof ( n ), compose_binary( equal_to<HString>(), select1st<person_t>(), identity<HString>() ) ) );
	ENSURE_EQUALS( "find_first_not_of failed (word)", p, a + 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "lower_bound() on list" )
	/* distinct */ {
		int_list_t list( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i <= _testData_[0][countof ( _testData_[0] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( lower_bound( list.begin(), list.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[0], p ) );
		}
		int_list_t::const_iterator first( lower_bound( list.begin(), list.end(), _testData_[0][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( lower_bound( list.begin(), list.end(), _testData_[0][countof ( _testData_[0] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating */ {
		int_list_t list( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i <= _testData_[2][countof ( _testData_[2] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( lower_bound( list.begin(), list.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_list_t::const_iterator first( lower_bound( list.begin(), list.end(), _testData_[2][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( lower_bound( list.begin(), list.end(), _testData_[2][countof ( _testData_[2] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	int_list_t empty;
	int_list_t::const_iterator it( lower_bound( empty.begin(), empty.end(), 0 ) );
	ENSURE( "lower_bound on empty failed", it == empty.begin() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 33, "lower_bound() on array" )
	/* distinct */ {
		int_array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i <= _testData_[0][countof ( _testData_[0] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( lower_bound( array.begin(), array.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance( _testData_[0], p ) );
		}
		int_array_t::const_iterator first( lower_bound( array.begin(), array.end(), _testData_[0][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( lower_bound( array.begin(), array.end(), _testData_[0][countof ( _testData_[0] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
	/* repeating */ {
		int_array_t array( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i <= _testData_[2][countof ( _testData_[2] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( lower_bound( array.begin(), array.end(), i ) );
			int const* p( std::lower_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "lower_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_array_t::const_iterator first( lower_bound( array.begin(), array.end(), _testData_[2][0] - 1 ) );
		ENSURE( "lower_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( lower_bound( array.begin(), array.end(), _testData_[2][countof ( _testData_[2] ) - 1] + 1 ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 34, "upper_bound() on list" )
	/* distinct */ {
		int_list_t list( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][countof ( _testData_[0] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( upper_bound( list.begin(), list.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[0], p ) );
		}
		int_list_t::const_iterator first( upper_bound( list.begin(), list.end(), _testData_[0][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( upper_bound( list.begin(), list.end(), _testData_[0][countof ( _testData_[0] ) - 1] ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	/* repeating */ {
		int_list_t list( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][countof ( _testData_[2] ) - 1]; ++ i ) {
			int_list_t::const_iterator it( upper_bound( list.begin(), list.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_list_t::const_iterator>( list.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_list_t::const_iterator first( upper_bound( list.begin(), list.end(), _testData_[2][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == list.begin() );
		int_list_t::const_iterator last( upper_bound( list.begin(), list.end(), _testData_[2][countof ( _testData_[2] ) - 1] ) );
		ENSURE( "lower_bound after range failed", last == list.end() );
	}
	int_list_t empty;
	int_list_t::const_iterator it( upper_bound( empty.begin(), empty.end(), 0 ) );
	ENSURE( "lower_bound on empty failed", it == empty.begin() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 35, "upper_bound() on array" )
	/* distinct */ {
		int_array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][countof ( _testData_[0] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( upper_bound( array.begin(), array.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[0] ), end( _testData_[0] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
		}
		int_array_t::const_iterator first( upper_bound( array.begin(), array.end(), _testData_[0][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( upper_bound( array.begin(), array.end(), _testData_[0][countof ( _testData_[0] ) - 1] ) );
		ENSURE( "upper_bound after range failed", last == array.end() );
	}
	/* repeating */ {
		int_array_t array( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][countof ( _testData_[2] ) - 1]; ++ i ) {
			int_array_t::const_iterator it( upper_bound( array.begin(), array.end(), i ) );
			int const* p( std::upper_bound( begin( _testData_[2] ), end( _testData_[2] ), i ) );
			ENSURE_EQUALS( "upper_bound in range failed", *it, *p );
			ENSURE_EQUALS( "lower_bound on repeating failed", distance<int_array_t::const_iterator>( array.begin(), it ), std::distance( _testData_[2], p ) );
		}
		int_array_t::const_iterator first( upper_bound( array.begin(), array.end(), _testData_[2][0] - 1 ) );
		ENSURE( "upper_bound before range failed", first == array.begin() );
		int_array_t::const_iterator last( upper_bound( array.begin(), array.end(), _testData_[2][countof ( _testData_[2] ) - 1] ) );
		ENSURE( "lower_bound after range failed", last == array.end() );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 36, "binary_search() on list" )
	/* distinct */ {
		int_list_t list( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][countof ( _testData_[0] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( list.begin(), list.end(), i ),
					std::binary_search( begin( _testData_[0] ), end( _testData_[0] ), i ) );
		}
	}
	/* repeating */ {
		int_list_t list( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][countof ( _testData_[2] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( list.begin(), list.end(), i ),
					std::binary_search( begin( _testData_[2] ), end( _testData_[2] ), i ) );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 37, "binary_search() on array" )
	/* distinct */ {
		int_array_t array( begin( _testData_[0] ), end( _testData_[0] ) );
		for ( int i( _testData_[0][0] - 1 ); i < _testData_[0][countof ( _testData_[0] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( array.begin(), array.end(), i ),
					std::binary_search( begin( _testData_[0] ), end( _testData_[0] ), i ) );
		}
	}
	/* repeating */ {
		int_array_t array( begin( _testData_[2] ), end( _testData_[2] ) );
		for ( int i( _testData_[2][0] - 1 ); i < _testData_[2][countof ( _testData_[2] ) - 1] + 1; ++ i ) {
			ENSURE_EQUALS( "binary_search on range failed",
					binary_search( array.begin(), array.end(), i ),
					std::binary_search( begin( _testData_[2] ), end( _testData_[2] ), i ) );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 38, "is_sorted" )
	ENSURE( "is_sorted on empty failed", is_sorted( _testData_[0], _testData_[0] ) );
	ENSURE( "is_sorted on large failed", is_sorted( begin( _testData_[0] ), end( _testData_[0] ) ) );
	int left[] = { 2, 1, 3, 4, 5, 6, 7 };
	int mid[] = { 1, 2, 3, 5, 4, 6, 7 };
	int right[] = { 1, 2, 3, 4, 5, 7, 6 };
	ENSURE_NOT( "is_sorted false positive on left", is_sorted( left, left + countof ( left ) ) );
	ENSURE_NOT( "is_sorted false positive on mid", is_sorted( mid, mid + countof ( mid ) ) );
	ENSURE_NOT( "is_sorted false positive on right", is_sorted( right, right + countof ( right ) ) );
	ENSURE( "is_sorted on one elem failed", is_sorted( _testData_[0], _testData_[0] + 1 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 39, "partition" )
	static int const range = 100;
	int_array_t a( range );
	HRandomizer r( randomizer_helper::make_randomizer( range ) );
	for ( int_array_t::iterator it( a.begin() ), end( a.end() ); it != end; ++ it )
		*it = static_cast<int>( r() ) - range / 2;
	clog << a << endl;
	int_array_t::iterator m( partition( a.begin(), a.end(), bind1st( less<int>(), 0 ) ) );
	clog << a << endl;
	for ( int_array_t::iterator it( a.begin() ); it != m; ++ it )
		ENSURE( "partition failed (*it > 0)", *it > 0 );
	for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it )
		ENSURE( "partition failed (*it <= 0)", *it <= 0 );
	generate( a.begin(), a.end(), inc( -50 ) );
	clog << a << endl;
	for ( int i( 0 ); i < ( range / 2 ); i += 20 ) {
		swap_ranges( a.begin() + i, a.begin() + i + 10, a.begin() + i + 50 );
	}
	clog << a << endl;
	m = partition( a.begin(), a.end(), bind1st( less<int>(), 0 ) );
	clog << a << endl;
	for ( int_array_t::iterator it( a.begin() ); it != m; ++ it )
		ENSURE( "partition failed (*it > 0)", *it > 0 );
	for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it )
		ENSURE( "partition failed (*it <= 0)", *it <= 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 40, "stable_partition" )
	static int const range( 100 );
	int_array_t a( range );
	HRandomizer r( randomizer_helper::make_randomizer( range ) );
	for ( int_array_t::iterator it( a.begin() ), end( a.end() ); it != end; ++ it )
		*it = static_cast<int>( r() ) - range / 2;
	clog << a << endl;
	sort( a.begin(), a.end() );
	clog << a << endl;
	int_array_t::iterator m( stable_partition( a.begin(), a.end(), bind1st( less<int>(), 0 ) ) );
	clog << a << endl;
	for ( int_array_t::iterator it( a.begin() ); it != m; ++ it )
		ENSURE( "stable_partition failed (*it > 0)", *it > 0 );
	for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it )
		ENSURE( "stable_partition failed (*it <= 0)", *it <= 0 );
	ENSURE( "stable_partition failed (left is_sorted)", is_sorted( a.begin(), m ) );
	ENSURE( "stable_partition failed (right is_sorted)", is_sorted( m, a.end() ) );
	for ( int i( 0 ); i < ( range / 20 ); ++ i ) {
		generate( a.begin() + i * 20, a.begin() + i * 20 + 10, inc( -49 + i * 10 ) );
		generate( a.begin() + i * 20 + 10, a.begin() + i * 20 + 20, inc( i * 10 + 1 ) );
	}
	clog << a << endl;
	m = stable_partition( a.begin(), a.end(), bind1st( less<int>(), 0 ) );
	clog << a << endl;
	for ( int_array_t::iterator it( a.begin() ); it != m; ++ it )
		ENSURE( "stable_partition failed (*it > 0)", *it > 0 );
	for ( int_array_t::iterator it( m ), end( a.end() ); it != end; ++ it )
		ENSURE( "stable_partition failed (*it <= 0)", *it <= 0 );
	ENSURE( "stable_partition failed (left is_sorted)", is_sorted( a.begin(), m ) );
	ENSURE( "stable_partition failed (right is_sorted)", is_sorted( m, a.end() ) );
TUT_TEARDOWN()

struct incUnary {
	int _n;
	incUnary( int n )
		: _n( n )
		{}
	template<typename T>
	int operator()( T const& lim_ ) {
		int lim( static_cast<int>( lim_ - 1 ) );
		int val( _n < lim ? _n : lim );
		++ _n;
		return ( val );
	}
};

TUT_UNIT_TEST( 41, "random_shuffle" )
	static int const range( 100 );
	int_array_t a( range );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	int_array_t b( a );
	random_shuffle( a.begin(), a.end() );
	ENSURE_NOT( "Probability of every element staying in its original position after random shuffle is N! which for this test is 100!, go play a lottery",  a == b );
	clog << a << endl;
	sort( a.begin(), a.end() );
	ENSURE_EQUALS( "random_shuffle lost some elements!", a, b );
	random_shuffle( a.begin(), a.end(), incUnary( 0 ) );
	clog << a << endl;
	reverse( a.begin(), a.end() );
	ENSURE_EQUALS( "random_shuffle did not use given randomizer properly", a, b );
TUT_TEARDOWN()

TUT_UNIT_TEST( 42, "random_sample" )
	static int const range( 1024 );
	int_array_t a( range );
	yaal::generate( a.begin(), a.end(), inc( 1 ) );
	int_array_t b( range / 2, -1 );
	int loTotal( 0 );
	static int const tries( 256 );
	for ( int t( 0 ); t < tries; ++ t ) {
		random_sample( a.begin(), a.end(), b.begin(), b.end(), HRandomizer( static_cast<u64_t>( t ) ) );
		int lo( static_cast<int>( count_if( b.begin(), b.end(), bind1st( less<int>(), range / 2 ) ) ) );
		loTotal += lo;
	}
	int loAverage( loTotal / tries );
	clog << loAverage << endl;
	ENSURE_DISTANCE( "random sample not uniformly random", loAverage, tries, 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "sort speed" )
	TIME_CONSTRAINT_EXEMPT();
	double long st( 0 );
	double long yt( 0 );
	int_array_t a( 100000 ); {
		yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() ); {
			HClock c;
			std::stable_sort( v.begin(), v.end() );
			clog << "*speed* std::stable_sort = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		} {
			HClock c;
			stable_sort( a.begin(), a.end() );
			clog << "*speed* yaal::stable_sort = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::stable_sort wrong", a, v );
		clog << "*speed* stable_sort result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
			HClock c;
			std::stable_sort( v.begin(), v.end() );
			clog << "*speed* std::stable_sort (on sorted) = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		} {
			HClock c;
			stable_sort( a.begin(), a.end() );
			clog << "*speed* yaal::stable_sort (on sorted) = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::stable_sort (on sorted) wrong", a, v );
		clog << "*speed* stable_sort (on sorted) result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	} {
		yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() ); {
			HClock c;
			std::sort( v.begin(), v.end() );
			clog << "*speed* std::sort = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		} {
			HClock c;
			sort( a.begin(), a.end() );
			clog << "*speed* yaal::sort = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::sort wrong", a, v );
		clog << "*speed* sort result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
			HClock c;
			std::sort( v.begin(), v.end() );
			clog << "*speed* std::sort (on sorted) = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		} {
			HClock c;
			sort( a.begin(), a.end() );
			clog << "*speed* yaal::sort (on sorted) = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::sort (on sorted) wrong", a, v );
		clog << "*speed* sort (on sorted) result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	} {
		yaal::generate( a.begin(), a.end(), HRandomizer( 0 ) );
		*a.rbegin() = -1;
		std_vector_t v( &*a.begin(), &*a.begin() + a.get_size() ); {
			HClock c;
			std::make_heap( v.begin(), v.end() );
			std::sort_heap( v.begin(), v.end() );
			clog << "*speed* std::heap_sort = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		} {
			HClock c;
			heap_sort( a.begin(), a.end() );
			clog << "*speed* yaal::heap_sort = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::heap_sort wrong", a, v );
		clog << "*speed* heap_sort result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl; {
			HClock c;
			std::make_heap( v.begin(), v.end() );
			std::sort_heap( v.begin(), v.end() );
			clog << "*speed* std::heap_sort (on sorted) = " << static_cast<int long>( st = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		} {
			HClock c;
			heap_sort( a.begin(), a.end() );
			clog << "*speed* yaal::heap_sort (on sorted) = " << static_cast<int long>( yt = static_cast<int long>( c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) ) << endl;
		}
		ENSURE_EQUALS( "yaal::heap_sort (on sorted) wrong", a, v );
		clog << "*speed* heap_sort (on sorted) result = " << ( ( st > yt ) ? green : red ) << ( yt / st ) << lightgray << endl;
	}
TUT_TEARDOWN()

}


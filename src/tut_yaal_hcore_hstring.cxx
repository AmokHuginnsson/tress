/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hstring.cxx - this file is integral part of `tress' project.

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

#include <iterator>
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

TUT_SIMPLE_MOCK( tut_yaal_hcore_hstring );
TUT_TEST_GROUP_N( tut_yaal_hcore_hstring, "yaal::hcore::HString" );

TUT_UNIT_TEST_N( 1, "/* trivial constructor */" )
	HString str;
	ensure_equals( "trivial construction failed", str, "" );
	ensure_equals( "trivial construction failed (size)", str.size(), 0 );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), -1 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* construction from char* */" )
	static char const CORRECT[] = "1024";
	HString str( CORRECT );
	ensure_equals ( "construction from c-string does not work", str, CORRECT );
	ensure_equals( "construction from char* failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "construction from char* failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from char* failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* copy construction */" )
	static char const CORRECT[] = "1024";
	HString str( CORRECT );
	HString copy( str );
	ensure_equals ( "copy construction does not work", copy, CORRECT );
	ensure_equals( "copy construction failed (size)",
			copy.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "copy construction failed (capacity)", copy.capacity(), 7 );
	ensure_equals( "copy construction failed (is_empty)", copy.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* construction from int */" )
	static int const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ensure_equals ( "construction from int does not work", str, CORRECT );
	ensure_equals( "construction from int failed (size)",
			str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "construction from int failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* construction from int long */" )
	static int long const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ensure_equals ( "construction from int long does not work", str, CORRECT );
	ensure_equals( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "construction from int long failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int long failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* construction from int unsigned */" )
	static int unsigned const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ensure_equals ( "construction from int unsigned does not work", str, CORRECT );
	ensure_equals( "construction from int unsigned failed (size)",
			str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "construction from int unsigned failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int unsigned failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* construction from int long unsigned */" )
	static int long unsigned const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ensure_equals ( "construction from int long unsigned does not work", str, CORRECT );
	ensure_equals( "construction from int long unsigned failed (size)",
			str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "construction from int long unsigned failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int long unsigned failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* construction from char */" )
	static char const CORRECT = '1';
	HString str( CORRECT );
	ensure_equals ( "construction from char does not work", str, CORRECT );
	ensure_equals( "construction from char failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) ) );
	ensure_equals( "construction from char failed (capacity)", str.capacity(), 1 );
	ensure_equals( "construction from char failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* construction from double */" )
	static double INIT = 3.141593;
	static char const* const CORRECT = "3.141593";
	HString str( INIT );
	ensure_equals ( "construction from double does not work", str, CORRECT );
	ensure_equals( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ensure_equals( "construction from double failed (capacity)", str.capacity(), 15 );
	ensure_equals( "construction from double failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "/* construction from double long */" )
	static double long INIT = 3.141592653589;
	static char const* const CORRECT = "3.141592653589";
	HString str( INIT );
	ensure_equals ( "construction from double does not work", str, CORRECT );
	ensure_equals( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ensure_equals( "construction from double failed (capacity)", str.capacity(), 15 );
	ensure_equals( "construction from double failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* construction from void* */" )
	static size_t const tmp = 0xdeadbeef;
	static void* INIT = reinterpret_cast<void*>( tmp );
	static char const* const CORRECT = "0xdeadbeef";
	HString str( INIT );
	ensure_equals ( "construction from void* does not work", str, CORRECT );
	ensure_equals( "construction from void* failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ensure_equals( "construction from void* failed (capacity)", str.capacity(), 15 );
	ensure_equals( "construction from void* failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* operator += */" )
	static char const INIT[] = "1024";
	static char const* const TEST = "0xdeadbeef";
	static char const CORRECT[] = "10240xdeadbeef";
	HString str( INIT );
	ensure_equals ( "char* constructor does not work", str, INIT );
	ensure_equals( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ensure_equals( "char* constructor failed (capacity)", str.capacity(), 7 );
	ensure_equals( "char* constructor failed (is_empty)", str.empty(), false );
	str += TEST;
	ensure_equals ( "operator+= does not work", str, CORRECT );
	ensure_equals( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ensure_equals( "operator+= failed (capacity)", str.capacity(), 15 );
	ensure_equals( "operator+= failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "/* clear */" )
	HString str;
	static char const INIT[] = "1024";
	ensure_equals( "trivial construction failed", str, "" );
	ensure_equals( "trivial construction failed (size)", str.size(), 0 );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), -1 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), true );
	str += INIT;
	ensure_equals ( "operator+= does not work", str, INIT );
	ensure_equals( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ensure_equals( "operator+= failed (capacity)", str.capacity(), 7 );
	ensure_equals( "operator+= failed (is_empty)", str.empty(), false );
	str.clear();
	ensure_equals ( "clear does not work", str, "" );
	ensure_equals( "clear failed (size)", str.size(), 0 );
	ensure_equals( "clear failed (capacity)", str.capacity(), 7 );
	ensure_equals( "clear failed (is_empty)", str.empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "/* replace */" )
	static char const INIT[] = "aarererererebb";
	static char const PAT1[] = "rere";
	static char const PAT2[] = "OKOK";
	static char const CORRECT12[] = "aaOKOKOKOKrebb";
	static char const PAT3[] = "rok";
	static char const CORRECT23[] = "aarokrokrebb";
	static char const PAT4[] = "I";
	static char const CORRECT34[] = "aaIIrebb";
	static char const PAT5[] = "II";
	static char const PAT6[] = "";
	static char const CORRECT56[] = "aarebb";

	HString str( INIT );
	ensure_equals ( "char* constructor does not work", str, INIT );
	ensure_equals( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ensure_equals( "char* constructor failed (capacity)", str.capacity(), 15 );
	ensure_equals( "char* constructor failed (is_empty)", str.empty(), false );

	str.replace( PAT1, PAT2 );
	ensure_equals ( "replace 1->2 does not work", str, CORRECT12 );
	ensure_equals( "replace 1->2 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT12 ) - 1 ) );
	ensure_equals( "replace 1->2 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 1->2 failed (is_empty)", str.empty(), false );

	str.replace( PAT2, PAT3 );
	ensure_equals ( "replace 2->3 does not work", str, CORRECT23 );
	ensure_equals( "replace 2->3 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT23 ) - 1 ) );
	ensure_equals( "replace 2->3 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 2->3 failed (is_empty)", str.empty(), false );

	str.replace( PAT3, PAT4 );
	ensure_equals ( "replace 3->4 does not work", str, CORRECT34 );
	ensure_equals( "replace 3->4 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT34 ) - 1 ) );
	ensure_equals( "replace 3->4 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 3->4 failed (is_empty)", str.empty(), false );

	str.replace( PAT5, PAT6 );
	ensure_equals ( "replace 5->6 does not work", str, CORRECT56 );
	ensure_equals( "replace 5->6 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT56 ) - 1 ) );
	ensure_equals( "replace 5->6 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 5->6 failed (is_empty)", str.empty(), false );

	static char const INIT0[] = "./${NEST}/app/";
	static char const PATA[] = "${NEST}";
	static char const PATB[] = "";
	static char const CORRECT_AB[] = ".//app/";
	
	str = INIT0;
	str.replace( PATA, PATB );
	ensure_equals ( "replace A->B does not work", str, CORRECT_AB );
	ensure_equals( "replace A->B failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_AB ) - 1 ) );
	ensure_equals( "replace A->B failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace A->B failed (is_empty)", str.empty(), false );

		{
		static char const INIT1[] = "@c@";
		static char const PAT1A[] = "@";
		static char const PAT1B[] = "UU";
		static char const CORRECT_1AB[] = "UUcUU";
		str = INIT1;
		str.replace( PAT1A, PAT1B );
		ensure_equals ( "replace A1->B1 does not work", str, CORRECT_1AB );
		ensure_equals( "replace A1->B1 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_1AB ) - 1 ) );
		ensure_equals( "replace A1->B1 failed (capacity)", str.capacity(), 15 );
		ensure_equals( "replace A1->B1 failed (is_empty)", str.empty(), false );
		ensure_equals( "bad lenght calculations", str.get_length(), static_cast<int long>( ::strlen( str.raw() ) ) );
		}
		{
		static char const INIT1[] = "c@cc@cc@cc@cc@cc@cc";
		static char const PAT1A[] = "@";
		static char const PAT1B[] = "@@";
		static char const CORRECT_1AB[] = "c@@cc@@cc@@cc@@cc@@cc@@cc";
		str = INIT1;
		str.replace( PAT1A, PAT1B );
		ensure_equals ( "replace A1->B1 does not work", str, CORRECT_1AB );
		ensure_equals( "replace A1->B1 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_1AB ) - 1 ) );
		ensure_equals( "replace A1->B1 failed (capacity)", str.capacity(), 31 );
		ensure_equals( "replace A1->B1 failed (is_empty)", str.empty(), false );
		ensure_equals( "bad lenght calculations", str.get_length(), static_cast<int long>( ::strlen( str.raw() ) ) );
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 22, "/* shift_left */" )
	static char const CORRECT[] = "Ala ma kota";
	static int const SHIFT = 4;
	HString str( CORRECT );
	str.shift_left( SHIFT );
	ensure_equals( "left_shift failed", str, CORRECT + SHIFT );
	try
		{
		str.shift_left( -1 );
		fail ( "no check for negative shift" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	str.shift_left( 100000 );
	ensure_equals( "left_shift failed", str, "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 23, "/* shift_right */" )
	static char const CORRECT[] = "    Ala ma kota";
	static int const SHIFT = 4;
	HString str( CORRECT + SHIFT );
	str.shift_right( SHIFT );
	ensure_equals( "right_shift failed", str, CORRECT );
	try
		{
		str.shift_right( -1 );
		fail( "no check for negative shift" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 24, "/* mid */" )
	char source[] = "abecadlo";
	HString str( source );
	char mid_failed[] = "mid failed";
	ensure_equals( mid_failed, str.mid( -10, 100 ), source );
	ensure_equals( mid_failed, str.mid( 3, 100 ), "cadlo" );
	ensure_equals( mid_failed, str.mid( 3, -1 ), "" );
	ensure_equals( mid_failed, str.mid( 35, 5 ), "" );
	ensure_equals( mid_failed, str.mid( -15, 3 ), "" );
	ensure_equals( mid_failed, str.mid( -15, 18 ), "abe" );
	ensure_equals( mid_failed, str.mid( 2, 2 ), "ec" );
	ensure_equals( mid_failed, str.mid( 2 ), "ecadlo" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 26, "/* right */" )
	HString str( "ala/." );
	ensure_equals( "wrong right part extraction", str.right( 1 ), "." );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 27, "/* erase */" )
	HString str;
	char s[] = "Ala ma kota";
	char erase_failed[] = "erase failed";
	str = s;ensure_equals( erase_failed, str.erase( 0, 4 ), "ma kota" );
	str = s;ensure_equals( erase_failed, str.erase( 2, 4 ), "Al kota" );
	str = s;ensure_equals( erase_failed, str.erase( -2, 4 ), "a ma kota" );
	str = s;str.erase( 4, 100 );
	ensure_equals( "erase 3 failed (size)", str.size(), 4 );
	ensure_equals( erase_failed, str, "Ala " );
	str = s;ensure_equals( erase_failed, str.erase( 0, 100 ), "" );
	HString str2( "|==--|[100%]" );
	ensure_equals( erase_failed, str2.erase( 7, 4 ), "|==--|[]" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 28, "/* insert */" )
	HString str;
	char s[] = "abcdef";
	char insert_failed[] = "insert failed";
	char overflow[] = "overflow passed";
	str = s;ensure_equals( insert_failed, str.insert( 0, 3, "ABCD" ), "ABCabcdef" );
	str = s;ensure_equals( insert_failed, str.insert( 2, 3, "ABCD" ), "abABCcdef" );
	str = s;ensure_equals( insert_failed, str.insert( -2, 2, "ABCD" ), "abcdef" );
	str = s;ensure_equals( insert_failed, str.insert( -2, 4, "ABCD" ), "CDabcdef" );
	try
		{
		str = s;ensure_equals( insert_failed, str.insert( -5, 3, "ABCD" ), "any" );
		fail( overflow );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	try
		{
		str = s;ensure_equals( insert_failed, str.insert( 0, 5, "ABCD" ), "any" );
		fail( overflow );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	str = s;ensure_equals( insert_failed, str.insert( 20, 3, "ABCD" ), "abcdef" );
	str = s;ensure_equals( insert_failed, str.insert( 2, -5, "ABCD" ), "abcdef" );
	str = s;ensure_equals( insert_failed, str.insert( 5, 3, "ABCD" ), "abcdeABCf" );
	str = s;ensure_equals( insert_failed, str.insert( 6, 3, "ABCD" ), "abcdefABC" );
	str = s;ensure_equals( insert_failed, str.insert( 7, 3, "ABCD" ), "abcdef" );
	HString str2( "|==--|[]" );
	ensure_equals( insert_failed, str2.insert( 7, 4, "done" ), "|==--|[done]" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 29, "/* find */" )
	HString str = "abcXYdeYXf";
	char failed[] = "find failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.find( 'A' ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.find( 'X' ), 3 );
	ensure_equals( HString().format( failed, 2 ), str.find( 'Y' ), 4 );
	ensure_equals( HString().format( failed, 3 ), str.find( 'X', -10 ), 3 );
	ensure_equals( HString().format( failed, 4 ), str.find( 'Y', -10 ), 4 );
	ensure_equals( HString().format( failed, 5 ), str.find( 'X', 3 ), 3 );
	ensure_equals( HString().format( failed, 6 ), str.find( 'Y', 3 ), 4 );
	ensure_equals( HString().format( failed, 7 ), str.find( 'X', 5 ), 8 );
	ensure_equals( HString().format( failed, 8 ), str.find( 'Y', 5 ), 7 );
	ensure_equals( HString().format( failed, 9 ), str.find( 'X', 9 ), -1 );
	ensure_equals( HString().format( failed, 10 ), str.find( 'Y', 9 ), -1 );
	ensure_equals( HString().format( failed, 11 ), str.find( 'X', 90 ), -1 );
	ensure_equals( HString().format( failed, 12 ), str.find( 'Y', 90 ), -1 );
	static char const* const PREF = "---> group: ";
	static char const* const SUFF = "yaal, tra la la";
	HString line( PREF );
	line += SUFF;
	ensure_equals( HString().format( failed, 13 ), line.find( PREF ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 30, "/* find_one_of */" )
	HString str = "abcXYdeYXf";
	char failed[] = "find_one_of failed";
	ensure_equals( failed, str.find_one_of( "ABCD" ), -1 );
	ensure_equals( failed, str.find_one_of( "AXYB" ), 3 );
	ensure_equals( failed, str.find_one_of( "AYD" ), 4 );
	ensure_equals( failed, str.find_one_of( "AXYB", -10 ), 3 );
	ensure_equals( failed, str.find_one_of( "AYD", -10 ), 4 );
	ensure_equals( failed, str.find_one_of( "AXYB", 3 ), 3 );
	ensure_equals( failed, str.find_one_of( "AYD", 3 ), 4 );
	ensure_equals( failed, str.find_one_of( "AXYB", 5 ), 7 );
	ensure_equals( failed, str.find_one_of( "AYD", 5 ), 7 );
	ensure_equals( failed, str.find_one_of( "AXYB", 9 ), -1 );
	ensure_equals( failed, str.find_one_of( "AYD", 9 ), -1 );
	ensure_equals( failed, str.find_one_of( "AXYB", 90 ), -1 );
	ensure_equals( failed, str.find_one_of( "AYD", 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 31, "/* find_other_than */" )
	HString str = "abcXYdeYXfg";
	char failed[] = "find_other_than failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.find_other_than( "abcXYdeYXfg" ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.find_other_than( "abXYdeYXfg" ), 2 );
	ensure_equals( HString().format( failed, 2 ), str.find_other_than( "abXYdeYXfg", 2 ), 2 );
	ensure_equals( HString().format( failed, 3 ), str.find_other_than( "abXYdeYXfg", 3 ), -1 );
	ensure_equals( HString().format( failed, 4 ), str.find_other_than( "abcdefg" ), 3 );
	ensure_equals( HString().format( failed, 5 ), str.find_other_than( "abcdefg", 5 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 32, "/* reverse_find */" )
	HString str = "fXYedYXcba";
	char failed[] = "reverse_find failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.reverse_find( 'A' ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.reverse_find( 'X' ), 3 );
	ensure_equals( HString().format( failed, 2 ), str.reverse_find( 'Y' ), 4 );
	ensure_equals( HString().format( failed, 3 ), str.reverse_find( 'X', -10 ), 3 );
	ensure_equals( HString().format( failed, 4 ), str.reverse_find( 'Y', -10 ), 4 );
	ensure_equals( HString().format( failed, 5 ), str.reverse_find( 'X', 3 ), 3 );
	ensure_equals( HString().format( failed, 6 ), str.reverse_find( 'Y', 3 ), 4 );
	ensure_equals( HString().format( failed, 7 ), str.reverse_find( 'X', 5 ), 8 );
	ensure_equals( HString().format( failed, 8 ), str.reverse_find( 'Y', 5 ), 7 );
	ensure_equals( HString().format( failed, 9 ), str.reverse_find( 'X', 9 ), -1 );
	ensure_equals( HString().format( failed, 10 ), str.reverse_find( 'Y', 9 ), -1 );
	ensure_equals( HString().format( failed, 11 ), str.reverse_find( 'X', 90 ), -1 );
	ensure_equals( HString().format( failed, 12 ), str.reverse_find( 'Y', 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 33, "/* reverse_find_one_of */" )
	HString str = "fXYedYXcba";
	char failed[] = "reverse_find_one_of failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.reverse_find_one_of( "ABCD" ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.reverse_find_one_of( "AXYB" ), 3 );
	ensure_equals( HString().format( failed, 2 ), str.reverse_find_one_of( "AYD" ), 4 );
	ensure_equals( HString().format( failed, 3 ), str.reverse_find_one_of( "AXYB", -10 ), 3 );
	ensure_equals( HString().format( failed, 4 ), str.reverse_find_one_of( "AYD", -10 ), 4 );
	ensure_equals( HString().format( failed, 5 ), str.reverse_find_one_of( "AXYB", 3 ), 3 );
	ensure_equals( HString().format( failed, 6 ), str.reverse_find_one_of( "AYD", 3 ), 4 );
	ensure_equals( HString().format( failed, 7 ), str.reverse_find_one_of( "AXYB", 5 ), 7 );
	ensure_equals( HString().format( failed, 8 ), str.reverse_find_one_of( "AYD", 5 ), 7 );
	ensure_equals( HString().format( failed, 9 ), str.reverse_find_one_of( "AXYB", 9 ), -1 );
	ensure_equals( HString().format( failed, 10 ), str.reverse_find_one_of( "AYD", 9 ), -1 );
	ensure_equals( HString().format( failed, 11 ), str.reverse_find_one_of( "AXYB", 90 ), -1 );
	ensure_equals( HString().format( failed, 12 ), str.reverse_find_one_of( "AYD", 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 34, "/* reverse_find_other_than */" )
	HString str = "gfXYedYXcba";
	char failed[] = "reverse_find_other_than failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.reverse_find_other_than( "abcXYdeYXfg" ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.reverse_find_other_than( "abXYdeYXfg" ), 2 );
	ensure_equals( HString().format( failed, 2 ), str.reverse_find_other_than( "abXYdeYXfg", 2 ), 2 );
	ensure_equals( HString().format( failed, 3 ), str.reverse_find_other_than( "abXYdeYXfg", 3 ), -1 );
	ensure_equals( HString().format( failed, 4 ), str.reverse_find_other_than( "abcdefg" ), 3 );
	ensure_equals( HString().format( failed, 5 ), str.reverse_find_other_than( "abcdefg", 5 ), 7 );
TUT_TEARDOWN()

int confirm( char const* const str, int const& size, char const* const pat, int const& len )
	{
	static HString fastpat;
	fastpat = pat;
	if ( len < fastpat.get_length() )
		fastpat.set_at( len, 0 );
	char const* p = ( len <= size ) ? strstr( str, fastpat.raw() ) : NULL;
	return ( p ? static_cast<int>( p - str ) : -1 );
	}

struct gen_char
	{
	HRandomizer _rnd;
	gen_char( void ) : _rnd()
		{ randomizer_helper::init_randomizer_from_time( _rnd ); }
	char operator()( void )
		{ return ( static_cast<char>( _rnd.rnd( 1 + 'z' - 'a' ) + 'a' ) ); }
	};

TUT_UNIT_TEST_N( 35, "/* find("") */" )
	static int const SAMPLE_SIZE = 128;
	char sample[ SAMPLE_SIZE + 1 ];
	sample[ SAMPLE_SIZE ] = 0;
	yaal::generate( sample, sample + SAMPLE_SIZE, gen_char() );
	yaal::copy( sample, sample + SAMPLE_SIZE, stream_iterator( cout ) ); cout << endl;
	HString str( sample );
	HString msg;
	for ( int len = 1; len <= SAMPLE_SIZE; ++ len )
		{
		for ( int offset = 0; offset < SAMPLE_SIZE; ++ offset )
			{
			int where = -1;
			do
				{
				int newwhere = ( ( len + offset ) <= SAMPLE_SIZE ) ? confirm( sample + where + 1,
						SAMPLE_SIZE - ( where + 1 ), sample + offset, len ) : -1;
				if ( newwhere >= 0 )
					newwhere += ( where + 1 );
				msg.format( "find(\"\") failed: %d,%d,%d", len, offset, where );
				ensure_equals( msg,
						where = ( offset + len <= SAMPLE_SIZE ) ? static_cast<int>( str.nfind( sample + offset, len, where + 1 ) ) : -1,
						newwhere );
				}
			while ( where >= 0 );
			}
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 36, "/* trim_left("") */" )
	static char const* const SPACE = "   ";
	static HString const TEXT = "ala ma";
	static char const* const FINE = "1234";
	HString str( SPACE + TEXT );
	ensure_equals( "trim failed", str.trim_left(), str );
	HString fine( FINE );
	ensure_equals( "trim failed", fine.trim_left(), fine );
	HString space( SPACE );
	ensure_equals( "trim failed", space.trim_left(), "" );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 37, "/* trim_right("") */" )
	static char const* const SPACE = "   ";
	static HString const TEXT = "ala ma";
	static char const* const FINE = "1234";
	HString str( TEXT + SPACE );
	ensure_equals( "trim 0 failed", str.trim_right(), str );
	HString fine( FINE );
	ensure_equals( "trim 1 failed", fine.trim_right(), fine );
	HString space( SPACE );
	ensure_equals( "trim 2 failed", space.trim_right(), "" );
TUT_TEARDOWN()

}


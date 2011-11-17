/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hstring.cxx - this file is integral part of `tress' project.

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

#include <cstring>
#include <iterator>
#include <TUT/tut.hpp>

#include <yaal/hcore/hstring.hxx>
#include <yaal/hcore/hrandomizer.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

static int const MIN_CAPACITY = sizeof ( HString ) - 2;

TUT_SIMPLE_MOCK( tut_yaal_hcore_hstring );
TUT_TEST_GROUP( tut_yaal_hcore_hstring, "yaal::hcore::HString" );

TUT_UNIT_TEST( 1, "trivial constructor" )
	HString str;
	ENSURE_EQUALS( "trivial construction failed", str, "" );
	ENSURE_EQUALS( "trivial construction failed (size)", str.size(), 0 );
	ENSURE_EQUALS( "trivial construction failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "trivial construction failed (is_empty)", str.empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "construction from char*" )
	static char const CORRECT[] = "1024";
	HString str( CORRECT );
	ENSURE_EQUALS ( "construction from c-string does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from char* failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from char* failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from char* failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy construction" )
	static char const CORRECT[] = "1024";
	HString str( CORRECT );
	HString copy( str );
	ENSURE_EQUALS ( "copy construction does not work", copy, CORRECT );
	ENSURE_EQUALS( "copy construction failed (size)",
			copy.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "copy construction failed (capacity)", copy.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "copy construction failed (is_empty)", copy.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "construction from int" )
	static int const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int failed (size)",
			str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "construction from int long" )
	static int long const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int long does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "construction from int unsigned" )
	static int unsigned const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int unsigned does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int unsigned failed (size)",
			str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int unsigned failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int unsigned failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "construction from int long unsigned" )
	static int long unsigned const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int long unsigned does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int long unsigned failed (size)",
			str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int long unsigned failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int long unsigned failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "construction from char" )
	static char const CORRECT = '1';
	HString str( CORRECT );
	ENSURE_EQUALS ( "construction from char does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from char failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) ) );
	ENSURE_EQUALS( "construction from char failed (capacity)", str.capacity(), max( 1, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from char failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "construction from double" )
	static double INIT = 3.141593;
	static char const* const CORRECT = "3.141593";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from double does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ENSURE_EQUALS( "construction from double failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "construction from double failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "construction from double long" )
	static double long INIT = 3.141592653589;
	static char const* const CORRECT = "3.141592653589";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from double does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ENSURE_EQUALS( "construction from double failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from double failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "construction from void*" )
	static size_t const tmp = 0xdeadbeef;
	static void* INIT = reinterpret_cast<void*>( tmp );
	static char const* const CORRECT = "0xdeadbeef";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from void* does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from void* failed (size)", str.size(), static_cast<int long>( ::strlen( CORRECT ) ) );
	ENSURE_EQUALS( "construction from void* failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "construction from void* failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "operator +=" )
	static char const INIT[] = "1024";
	static char const* const TEST = "0xdeadbeef";
	static char const CORRECT[] = "10240xdeadbeef";
	HString str( INIT );
	ENSURE_EQUALS ( "char* constructor does not work", str, INIT );
	ENSURE_EQUALS( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ENSURE_EQUALS( "char* constructor failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "char* constructor failed (is_empty)", str.empty(), false );
	str += TEST;
	ENSURE_EQUALS ( "operator+= does not work", str, CORRECT );
	ENSURE_EQUALS( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "operator+= failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "operator+= failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "clear" )
	HString str;
	static char const INIT[] = "1024";
	ENSURE_EQUALS( "trivial construction failed", str, "" );
	ENSURE_EQUALS( "trivial construction failed (size)", str.size(), 0 );
	ENSURE_EQUALS( "trivial construction failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "trivial construction failed (is_empty)", str.empty(), true );
	str += INIT;
	ENSURE_EQUALS ( "operator+= does not work", str, INIT );
	ENSURE_EQUALS( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ENSURE_EQUALS( "operator+= failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "operator+= failed (is_empty)", str.empty(), false );
	str.clear();
	ENSURE_EQUALS ( "clear does not work", str, "" );
	ENSURE_EQUALS( "clear failed (size)", str.size(), 0 );
	ENSURE_EQUALS( "clear failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "clear failed (is_empty)", str.empty(), true );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "replace" )
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
	ENSURE_EQUALS ( "char* constructor does not work", str, INIT );
	ENSURE_EQUALS( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( INIT ) - 1 ) );
	ENSURE_EQUALS( "char* constructor failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "char* constructor failed (is_empty)", str.empty(), false );

	str.replace( PAT1, PAT2 );
	ENSURE_EQUALS ( "replace 1->2 does not work", str, CORRECT12 );
	ENSURE_EQUALS( "replace 1->2 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT12 ) - 1 ) );
	ENSURE_EQUALS( "replace 1->2 failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 1->2 failed (is_empty)", str.empty(), false );

	str.replace( PAT2, PAT3 );
	ENSURE_EQUALS ( "replace 2->3 does not work", str, CORRECT23 );
	ENSURE_EQUALS( "replace 2->3 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT23 ) - 1 ) );
	ENSURE_EQUALS( "replace 2->3 failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 2->3 failed (is_empty)", str.empty(), false );

	str.replace( PAT3, PAT4 );
	ENSURE_EQUALS ( "replace 3->4 does not work", str, CORRECT34 );
	ENSURE_EQUALS( "replace 3->4 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT34 ) - 1 ) );
	ENSURE_EQUALS( "replace 3->4 failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 3->4 failed (is_empty)", str.empty(), false );

	str.replace( PAT5, PAT6 );
	ENSURE_EQUALS ( "replace 5->6 does not work", str, CORRECT56 );
	ENSURE_EQUALS( "replace 5->6 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT56 ) - 1 ) );
	ENSURE_EQUALS( "replace 5->6 failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace 5->6 failed (is_empty)", str.empty(), false );

	static char const INIT0[] = "./${NEST}/app/";
	static char const PATA[] = "${NEST}";
	static char const PATB[] = "";
	static char const CORRECT_AB[] = ".//app/";
	
	str = INIT0;
	str.replace( PATA, PATB );
	ENSURE_EQUALS ( "replace A->B does not work", str, CORRECT_AB );
	ENSURE_EQUALS( "replace A->B failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_AB ) - 1 ) );
	ENSURE_EQUALS( "replace A->B failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
	ENSURE_EQUALS( "replace A->B failed (is_empty)", str.empty(), false );
 {
		static char const INIT1[] = "@c@";
		static char const PAT1A[] = "@";
		static char const PAT1B[] = "UU";
		static char const CORRECT_1AB[] = "UUcUU";
		str = INIT1;
		str.replace( PAT1A, PAT1B );
		ENSURE_EQUALS ( "replace A1->B1 does not work", str, CORRECT_1AB );
		ENSURE_EQUALS( "replace A1->B1 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_1AB ) - 1 ) );
		ENSURE_EQUALS( "replace A1->B1 failed (capacity)", str.capacity(), max( 15, MIN_CAPACITY ) );
		ENSURE_EQUALS( "replace A1->B1 failed (is_empty)", str.empty(), false );
		ENSURE_EQUALS( "bad lenght calculations", str.get_length(), static_cast<int long>( ::strlen( str.raw() ) ) );
	} {
		static char const INIT1[] = "c@cc@cc@cc@cc@cc@cc";
		static char const PAT1A[] = "@";
		static char const PAT1B[] = "@@";
		static char const CORRECT_1AB[] = "c@@cc@@cc@@cc@@cc@@cc@@cc";
		str = INIT1;
		str.replace( PAT1A, PAT1B );
		ENSURE_EQUALS ( "replace A1->B1 does not work", str, CORRECT_1AB );
		ENSURE_EQUALS( "replace A1->B1 failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT_1AB ) - 1 ) );
		ENSURE_EQUALS( "replace A1->B1 failed (capacity)", str.capacity(), max( 31, MIN_CAPACITY ) );
		ENSURE_EQUALS( "replace A1->B1 failed (is_empty)", str.empty(), false );
		ENSURE_EQUALS( "bad lenght calculations", str.get_length(), static_cast<int long>( ::strlen( str.raw() ) ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "construction from int short" )
	static int short const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int long does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "construction from int short unsigned" )
	static int short unsigned const INIT = 1024;
	static char const CORRECT[] = "1024";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int long does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 7, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "construction from char unsigned" )
	static char unsigned const INIT = static_cast<char unsigned>( '±' );
	static char const CORRECT[] = "±";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int long does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), max( 1, MIN_CAPACITY ) );
	ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "construction from float" )
	static float const INIT = static_cast<float>( 2.718281828459045 );
	static char const CORRECT[] = "2.718282";
	HString str( INIT );
	ENSURE_EQUALS ( "construction from int long does not work", str, CORRECT );
	ENSURE_EQUALS( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( CORRECT ) - 1 ) );
	ENSURE_EQUALS( "construction from int long failed (capacity)", str.capacity(), MIN_CAPACITY );
	ENSURE_EQUALS( "construction from int long failed (is_empty)", str.empty(), false );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "shift_left" )
	static char const CORRECT[] = "Ala ma kota";
	static int const SHIFT = 4;
	HString str( CORRECT );
	str.shift_left( SHIFT );
	ENSURE_EQUALS( "left_shift failed", str, CORRECT + SHIFT );
	try {
		str.shift_left( -1 );
		FAIL ( "no check for negative shift" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
	str.shift_left( 100000 );
	ENSURE_EQUALS( "left_shift failed", str, "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "shift_right" )
	static char const CORRECT[] = "    Ala ma kota";
	static int const SHIFT = 4;
	HString str( CORRECT + SHIFT );
	str.shift_right( SHIFT );
	ENSURE_EQUALS( "right_shift failed", str, CORRECT );
	try {
		str.shift_right( -1 );
		FAIL( "no check for negative shift" );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "mid" )
	char source[] = "abecadlo";
	HString str( source );
	char mid_failed[] = "mid failed";
	ENSURE_EQUALS( mid_failed, str.mid( -10, 100 ), source );
	ENSURE_EQUALS( mid_failed, str.mid( 3, 100 ), "cadlo" );
	ENSURE_EQUALS( mid_failed, str.mid( 3, -1 ), "" );
	ENSURE_EQUALS( mid_failed, str.mid( 35, 5 ), "" );
	ENSURE_EQUALS( mid_failed, str.mid( -15, 3 ), "" );
	ENSURE_EQUALS( mid_failed, str.mid( -15, 18 ), "abe" );
	ENSURE_EQUALS( mid_failed, str.mid( 2, 2 ), "ec" );
	ENSURE_EQUALS( mid_failed, str.mid( 2 ), "ecadlo" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "right" )
	HString str( "ala/." );
	ENSURE_EQUALS( "wrong right part extraction", str.right( 1 ), "." );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "erase" )
	HString str;
	char s[] = "Ala ma kota";
	char erase_failed[] = "erase failed";
	str = s;ENSURE_EQUALS( erase_failed, str.erase( 0, 4 ), "ma kota" );
	str = s;ENSURE_EQUALS( erase_failed, str.erase( 2, 4 ), "Al kota" );
	str = s;ENSURE_EQUALS( erase_failed, str.erase( -2, 4 ), "a ma kota" );
	str = s;str.erase( 4, 100 );
	ENSURE_EQUALS( "erase 3 failed (size)", str.size(), 4 );
	ENSURE_EQUALS( erase_failed, str, "Ala " );
	str = s;str.erase( 4 );
	ENSURE_EQUALS( "erase 3 failed (size)", str.size(), 4 );
	ENSURE_EQUALS( erase_failed, str, "Ala " );
	str = s;str.erase();
	ENSURE_EQUALS( erase_failed, str.is_empty(), true );
	str = s;ENSURE_EQUALS( erase_failed, str.erase( 0, 100 ), "" );
	HString str2( "|==--|[100%]" );
	ENSURE_EQUALS( erase_failed, str2.erase( 7, 4 ), "|==--|[]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "insert" )
	HString str;
	char s[] = "abcdef";
	char insert_failed[] = "insert failed";
	char overflow[] = "overflow passed";
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 0, 3, "ABCD" ), "ABCabcdef" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 2, 3, "ABCD" ), "abABCcdef" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( -2, 2, "ABCD" ), "abcdef" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( -2, 4, "ABCD" ), "CDabcdef" );
	try {
		str = s;ENSURE_EQUALS( insert_failed, str.insert( -5, 3, "ABCD" ), "any" );
		FAIL( overflow );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
	try {
		str = s;ENSURE_EQUALS( insert_failed, str.insert( 0, 5, "ABCD" ), "any" );
		FAIL( overflow );
	} catch ( HException& e ) {
		cout << e.what() << endl;
	}
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 20, 3, "ABCD" ), "abcdef" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 2, -5, "ABCD" ), "abcdef" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 5, 3, "ABCD" ), "abcdeABCf" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 6, 3, "ABCD" ), "abcdefABC" );
	str = s;ENSURE_EQUALS( insert_failed, str.insert( 7, 3, "ABCD" ), "abcdef" );
	HString str2( "|==--|[]" );
	ENSURE_EQUALS( insert_failed, str2.insert( 7, 4, "done" ), "|==--|[done]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "find" )
	HString str = "abcXYdeYXf";
	char failed[] = "find failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.find( 'A' ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.find( 'X' ), 3 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.find( 'Y' ), 4 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.find( 'X', -10 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.find( 'Y', -10 ), 4 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.find( 'X', 3 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 6 ), str.find( 'Y', 3 ), 4 );
	ENSURE_EQUALS( HString().format( failed, 7 ), str.find( 'X', 5 ), 8 );
	ENSURE_EQUALS( HString().format( failed, 8 ), str.find( 'Y', 5 ), 7 );
	ENSURE_EQUALS( HString().format( failed, 9 ), str.find( 'X', 9 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 10 ), str.find( 'Y', 9 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 11 ), str.find( 'X', 90 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 12 ), str.find( 'Y', 90 ), -1 );
	static char const* const PREF = "---> group: ";
	static char const* const SUFF = "yaal, tra la la";
	HString line( PREF );
	line += SUFF;
	ENSURE_EQUALS( HString().format( failed, 13 ), line.find( PREF ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "find_one_of" )
	HString str = "abcXYdeYXf";
	char failed[] = "find_one_of failed";
	ENSURE_EQUALS( failed, str.find_one_of( "ABCD" ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB" ), 3 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD" ), 4 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", -10 ), 3 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", -10 ), 4 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 3 ), 3 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 3 ), 4 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 5 ), 7 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 5 ), 7 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 9 ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 9 ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AXYB", 90 ), -1 );
	ENSURE_EQUALS( failed, str.find_one_of( "AYD", 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 31, "find_other_than" )
	HString str = "abcXYdeYXfg";
	char failed[] = "find_other_than failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.find_other_than( "abcXYdeYXfg" ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.find_other_than( "abXYdeYXfg" ), 2 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.find_other_than( "abXYdeYXfg", 2 ), 2 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.find_other_than( "abXYdeYXfg", 3 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.find_other_than( "abcdefg" ), 3 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.find_other_than( "abcdefg", 5 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "reverse_find" )
	HString str = "fXYedYXcba";
	char failed[] = "reverse_find failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.reverse_find( 'A' ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.reverse_find( 'X' ), 3 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.reverse_find( 'Y' ), 4 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.reverse_find( 'X', -10 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.reverse_find( 'Y', -10 ), 4 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.reverse_find( 'X', 3 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 6 ), str.reverse_find( 'Y', 3 ), 4 );
	ENSURE_EQUALS( HString().format( failed, 7 ), str.reverse_find( 'X', 5 ), 8 );
	ENSURE_EQUALS( HString().format( failed, 8 ), str.reverse_find( 'Y', 5 ), 7 );
	ENSURE_EQUALS( HString().format( failed, 9 ), str.reverse_find( 'X', 9 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 10 ), str.reverse_find( 'Y', 9 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 11 ), str.reverse_find( 'X', 90 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 12 ), str.reverse_find( 'Y', 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 33, "reverse_find_one_of" )
	HString str = "fXYedYXcba";
	char failed[] = "reverse_find_one_of failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.reverse_find_one_of( "ABCD" ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.reverse_find_one_of( "AXYB" ), 3 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.reverse_find_one_of( "AYD" ), 4 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.reverse_find_one_of( "AXYB", -10 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.reverse_find_one_of( "AYD", -10 ), 4 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.reverse_find_one_of( "AXYB", 3 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 6 ), str.reverse_find_one_of( "AYD", 3 ), 4 );
	ENSURE_EQUALS( HString().format( failed, 7 ), str.reverse_find_one_of( "AXYB", 5 ), 7 );
	ENSURE_EQUALS( HString().format( failed, 8 ), str.reverse_find_one_of( "AYD", 5 ), 7 );
	ENSURE_EQUALS( HString().format( failed, 9 ), str.reverse_find_one_of( "AXYB", 9 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 10 ), str.reverse_find_one_of( "AYD", 9 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 11 ), str.reverse_find_one_of( "AXYB", 90 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 12 ), str.reverse_find_one_of( "AYD", 90 ), -1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 34, "reverse_find_other_than" )
	HString str = "gfXYedYXcba";
	char failed[] = "reverse_find_other_than failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.reverse_find_other_than( "abcXYdeYXfg" ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.reverse_find_other_than( "abXYdeYXfg" ), 2 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.reverse_find_other_than( "abXYdeYXfg", 2 ), 2 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.reverse_find_other_than( "abXYdeYXfg", 3 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.reverse_find_other_than( "abcdefg" ), 3 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.reverse_find_other_than( "abcdefg", 5 ), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 35, "find_last" )
	HString str = "fXYedYXcba";
	char failed[] = "find_last failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.find_last( 'A' ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.find_last( 'X' ), 6 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.find_last( 'Y' ), 5 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.find_last( 'X', -10 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.find_last( 'Y', -10 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.find_last( 'X', 3 ), 1 );
	ENSURE_EQUALS( HString().format( failed, 6 ), str.find_last( 'Y', 3 ), 2 );
	ENSURE_EQUALS( HString().format( failed, 7 ), str.find_last( 'X', 5 ), 1 );
	ENSURE_EQUALS( HString().format( failed, 8 ), str.find_last( 'Y', 5 ), 5 );
	ENSURE_EQUALS( HString().format( failed, 9 ), str.find_last( 'X', 9 ), 6 );
	ENSURE_EQUALS( HString().format( failed, 10 ), str.find_last( 'Y', 9 ), 5 );
	ENSURE_EQUALS( HString().format( failed, 11 ), str.find_last( 'X', 90 ), 6 );
	ENSURE_EQUALS( HString().format( failed, 12 ), str.find_last( 'Y', 90 ), 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 36, "find_last_one_of" )
	HString str = "fXYedYXcba";
	char failed[] = "find_last_one_of failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.find_last_one_of( "ABCD" ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.find_last_one_of( "AXYB" ), 6 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.find_last_one_of( "AYD" ), 5 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.find_last_one_of( "AXYB", -10 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.find_last_one_of( "AYD", -10 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.find_last_one_of( "AXYB", 3 ), 2 );
	ENSURE_EQUALS( HString().format( failed, 6 ), str.find_last_one_of( "AXB", 3 ), 1 );
	ENSURE_EQUALS( HString().format( failed, 7 ), str.find_last_one_of( "AYD", 3 ), 2 );
	ENSURE_EQUALS( HString().format( failed, 8 ), str.find_last_one_of( "AXYB", 5 ), 5 );
	ENSURE_EQUALS( HString().format( failed, 9 ), str.find_last_one_of( "AXB", 5 ), 1 );
	ENSURE_EQUALS( HString().format( failed, 10 ), str.find_last_one_of( "AYD", 5 ), 5 );
	ENSURE_EQUALS( HString().format( failed, 11 ), str.find_last_one_of( "AXYB", 9 ), 6 );
	ENSURE_EQUALS( HString().format( failed, 12 ), str.find_last_one_of( "AYD", 9 ), 5 );
	ENSURE_EQUALS( HString().format( failed, 13 ), str.find_last_one_of( "AXYB", 90 ), 6 );
	ENSURE_EQUALS( HString().format( failed, 14 ), str.find_last_one_of( "AYD", 90 ), 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 37, "find_last_other_than" )
	HString str = "gfXYedYXcba";
	char failed[] = "find_last_other_than failed[%d]";
	ENSURE_EQUALS( HString().format( failed, 0 ), str.find_last_other_than( "abcXYdeYXfg" ), -1 );
	ENSURE_EQUALS( HString().format( failed, 1 ), str.find_last_other_than( "abXYdeYXfg" ), 8 );
	ENSURE_EQUALS( HString().format( failed, 2 ), str.find_last_other_than( "abXYdeYXfg", 2 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 3 ), str.find_last_other_than( "abXYdeYXfg", 7 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 4 ), str.find_last_other_than( "abXYdeYXfg", 8 ), 8 );
	ENSURE_EQUALS( HString().format( failed, 5 ), str.find_last_other_than( "abXYdeYXfg", 100 ), 8 );
	ENSURE_EQUALS( HString().format( failed, 6 ), str.find_last_other_than( "abcdefg" ), 7 );
	ENSURE_EQUALS( HString().format( failed, 7 ), str.find_last_other_than( "abcdefg", 1 ), -1 );
	ENSURE_EQUALS( HString().format( failed, 8 ), str.find_last_other_than( "abcdefg", 2 ), 2 );
	ENSURE_EQUALS( HString().format( failed, 9 ), str.find_last_other_than( "abcdefg", 3 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 10 ), str.find_last_other_than( "abcdefg", 4 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 11 ), str.find_last_other_than( "abcdefg", 5 ), 3 );
	ENSURE_EQUALS( HString().format( failed, 12 ), str.find_last_other_than( "abcdefg", 6 ), 6 );
	ENSURE_EQUALS( HString().format( failed, 13 ), str.find_last_other_than( "abcdefg", 7 ), 7 );
	ENSURE_EQUALS( HString().format( failed, 14 ), str.find_last_other_than( "abcdefg", 8 ), 7 );
TUT_TEARDOWN()

int confirm( char const* const str, int size, char const* const pat, int len ) {
	static HString fastpat;
	fastpat = pat;
	if ( len < fastpat.get_length() )
		fastpat.set_at( len, 0 );
	char const* p = ( len <= size ) ? strstr( str, fastpat.raw() ) : NULL;
	return ( p ? static_cast<int>( p - str ) : -1 );
}

struct gen_char {
	HRandomizer _rnd;
	gen_char( void )
		: _rnd( randomizer_helper::make_randomizer() )
		{ }
	char operator()( void )
		{ return ( static_cast<char>( _rnd( 1 + 'z' - 'a' ) + 'a' ) ); }
};

TUT_UNIT_TEST( 38, "find("")" )
	static int const SAMPLE_SIZE = 128;
	char sample[ SAMPLE_SIZE + 1 ];
	sample[ SAMPLE_SIZE ] = 0;
	yaal::generate( sample, sample + SAMPLE_SIZE, gen_char() );
	yaal::copy( sample, sample + SAMPLE_SIZE, stream_iterator( cout ) ); cout << endl;
	HString str( sample );
	HString msg;
	for ( int len = 1; len <= SAMPLE_SIZE; ++ len ) {
		for ( int offset = 0; offset < SAMPLE_SIZE; ++ offset ) {
			int where = -1;
			do {
				int newwhere = ( ( len + offset ) <= SAMPLE_SIZE ) ? confirm( sample + where + 1,
						SAMPLE_SIZE - ( where + 1 ), sample + offset, len ) : -1;
				if ( newwhere >= 0 )
					newwhere += ( where + 1 );
				msg.format( "find(\"\") failed: %d,%d,%d", len, offset, where );
				ENSURE_EQUALS( msg,
						where = ( offset + len <= SAMPLE_SIZE ) ? static_cast<int>( str.nfind( sample + offset, len, where + 1 ) ) : -1,
						newwhere );
			} while ( where >= 0 );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 39, "trim_left("")" )
	static char const* const SPACE = "   ";
	static HString const TEXT = "ala ma";
	static char const* const FINE = "1234";
	HString str( SPACE + TEXT );
	ENSURE_EQUALS( "trim failed", str.trim_left(), str );
	HString fine( FINE );
	ENSURE_EQUALS( "trim failed", fine.trim_left(), fine );
	HString space( SPACE );
	ENSURE_EQUALS( "trim failed", space.trim_left(), "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 40, "trim_right("")" )
	static char const* const SPACE = "   ";
	static HString const TEXT = "ala ma";
	static char const* const FINE = "1234";
	HString str( TEXT + SPACE );
	ENSURE_EQUALS( "trim 0 failed", str.trim_right(), str );
	HString fine( FINE );
	ENSURE_EQUALS( "trim 1 failed", fine.trim_right(), fine );
	HString space( SPACE );
	ENSURE_EQUALS( "trim 2 failed", space.trim_right(), "" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 41, "hs_realloc( size )" )
	HString str;
	ENSURE_EQUALS( "bad capacity on never-used empty string", str.get_capacity(), MIN_CAPACITY );
	str.hs_realloc( 1 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 0, MIN_CAPACITY ) );
	str.hs_realloc( 2 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 1, MIN_CAPACITY ) );
	str.hs_realloc( 3 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 3, MIN_CAPACITY ) );
	str.hs_realloc( 5 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 7, MIN_CAPACITY ) );
	str.hs_realloc( 7 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), max( 7, MIN_CAPACITY ) );
	str.hs_realloc( 11 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.hs_realloc( MIN_CAPACITY - 1 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.hs_realloc( MIN_CAPACITY );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.hs_realloc( MIN_CAPACITY + 1 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), MIN_CAPACITY );
	str.hs_realloc( MIN_CAPACITY + 2 );
	ENSURE_EQUALS( "bad capacity after reallocation", str.get_capacity(), ( MIN_CAPACITY < 16 ? 15 : 31 ) );
	try {
		str.hs_realloc( -1 );
		FAIL( "absurd reallocation size allowed" );
	} catch ( HStringException const& ) {
		/* ok */
	}
	try {
		str.hs_realloc( str.get_max_size() + 2 );
		FAIL( "huge (too big) reallocation size allowed" );
	} catch ( HStringException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 42, "assign( HString ... )" )
	static char const ss[] = "Ala ma kota.";
	static char const sl[] = "Ala ma kota, a kot ma mleczko.";
	HString source( ss );
	HString dest( "dummy" );
	char const err[] = "assign failed";
	dest = source;
	ENSURE_EQUALS( err, dest.assign( source, 0, 0 ), "" );
	dest = source;
	ENSURE_EQUALS( err, dest.assign( source, source.get_length() * 2, source.get_length() ), "" );
	ENSURE_EQUALS( err, dest.assign( source, 0, HString::MAX_STRING_LENGTH ), source );
	ENSURE_EQUALS( err, dest.assign( source, 0, 5 ), "Ala m" );
	ENSURE_EQUALS( err, dest.assign( source, 4, 5 ), "ma ko" );
	ENSURE_EQUALS( err, dest.assign( source, 7, 5 ), "kota." );
	ENSURE_EQUALS( err, dest.assign( source, 8, 5 ), "ota." );
	ENSURE_EQUALS( err, dest.assign( source, sizeof ( ss ) - 2, 5 ), "." );
	ENSURE_EQUALS( err, dest.assign( source, sizeof ( ss ) - 1, 5 ), "" );
	ENSURE_EQUALS( err, dest.assign( source, sizeof ( ss ), 5 ), "" );
	source.assign( sl, sizeof ( sl ) - 1 );
	try {
		dest.assign( source, -1, 2 );
		FAIL( "assign with negative offset succeeded" );
	} catch ( HStringException const& ) {
		// ok
	}
	try {
		dest.assign( source, 0, -1 );
		FAIL( "assign with negative lenght succeeded" );
	} catch ( HStringException const& ) {
		// ok
	}
TUT_TEARDOWN()

}


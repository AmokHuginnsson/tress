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

/* trivial constructor */
template<>
template<>
void module::test<1>( void )
	{
	HString str;
	ensure_equals( "trivial construction failed", str, "" );
	ensure_equals( "trivial construction failed (size)", str.size(), 0 );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), -1 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), true );
	}

/* construction from char* */
template<>
template<>
void module::test<2>( void )
	{
	static char const D_CORRECT[] = "1024";
	HString str( D_CORRECT );
	ensure_equals ( "construction from c-string does not work", str, D_CORRECT );
	ensure_equals( "construction from char* failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "construction from char* failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from char* failed (is_empty)", str.empty(), false );
	}

/* copy construction */
template<>
template<>
void module::test<3>( void )
	{
	static char const D_CORRECT[] = "1024";
	HString str( D_CORRECT );
	HString copy( str );
	ensure_equals ( "copy construction does not work", copy, D_CORRECT );
	ensure_equals( "copy construction failed (size)",
			copy.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "copy construction failed (capacity)", copy.capacity(), 7 );
	ensure_equals( "copy construction failed (is_empty)", copy.empty(), false );
	}

/* construction from int */
template<>
template<>
void module::test<4>( void )
	{
	static int const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int does not work", str, D_CORRECT );
	ensure_equals( "construction from int failed (size)",
			str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "construction from int failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int failed (is_empty)", str.empty(), false );
	}

/* construction from int long */
template<>
template<>
void module::test<5>( void )
	{
	static int long const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int long does not work", str, D_CORRECT );
	ensure_equals( "construction from int long failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "construction from int long failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int long failed (is_empty)", str.empty(), false );
	}

/* construction from int unsigned */
template<>
template<>
void module::test<6>( void )
	{
	static int unsigned const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int unsigned does not work", str, D_CORRECT );
	ensure_equals( "construction from int unsigned failed (size)",
			str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "construction from int unsigned failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int unsigned failed (is_empty)", str.empty(), false );
	}

/* construction from int long unsigned */
template<>
template<>
void module::test<7>( void )
	{
	static int long unsigned const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int long unsigned does not work", str, D_CORRECT );
	ensure_equals( "construction from int long unsigned failed (size)",
			str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "construction from int long unsigned failed (capacity)", str.capacity(), 7 );
	ensure_equals( "construction from int long unsigned failed (is_empty)", str.empty(), false );
	}

/* construction from char */
template<>
template<>
void module::test<8>( void )
	{
	static char const D_CORRECT = '1';
	HString str( D_CORRECT );
	ensure_equals ( "construction from char does not work", str, D_CORRECT );
	ensure_equals( "construction from char failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) ) );
	ensure_equals( "construction from char failed (capacity)", str.capacity(), 1 );
	ensure_equals( "construction from char failed (is_empty)", str.empty(), false );
	}

/* construction from double */
template<>
template<>
void module::test<9>( void )
	{
	static double D_INIT = 3.141593;
	static char const* const D_CORRECT = "3.141593";
	HString str( D_INIT );
	ensure_equals ( "construction from double does not work", str, D_CORRECT );
	ensure_equals( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( D_CORRECT ) ) );
	ensure_equals( "construction from double failed (capacity)", str.capacity(), 15 );
	ensure_equals( "construction from double failed (is_empty)", str.empty(), false );
	}

/* construction from double long */
template<>
template<>
void module::test<10>( void )
	{
	static double long D_INIT = 3.141592653589;
	static char const* const D_CORRECT = "3.141592653589";
	HString str( D_INIT );
	ensure_equals ( "construction from double does not work", str, D_CORRECT );
	ensure_equals( "construction from double failed (size)", str.size(), static_cast<int long>( ::strlen( D_CORRECT ) ) );
	ensure_equals( "construction from double failed (capacity)", str.capacity(), 15 );
	ensure_equals( "construction from double failed (is_empty)", str.empty(), false );
	}

/* construction from void* */
template<>
template<>
void module::test<11>( void )
	{
	static size_t const tmp = 0xdeadbeef;
	static void* D_INIT = reinterpret_cast<void*>( tmp );
	static char const* const D_CORRECT = "0xdeadbeef";
	HString str( D_INIT );
	ensure_equals ( "construction from void* does not work", str, D_CORRECT );
	ensure_equals( "construction from void* failed (size)", str.size(), static_cast<int long>( ::strlen( D_CORRECT ) ) );
	ensure_equals( "construction from void* failed (capacity)", str.capacity(), 15 );
	ensure_equals( "construction from void* failed (is_empty)", str.empty(), false );
	}

/* operator += */
template<>
template<>
void module::test<12>( void )
	{
	static char const D_INIT[] = "1024";
	static char const* const D_TEST = "0xdeadbeef";
	static char const D_CORRECT[] = "10240xdeadbeef";
	HString str( D_INIT );
	ensure_equals ( "char* constructor does not work", str, D_INIT );
	ensure_equals( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( D_INIT ) - 1 ) );
	ensure_equals( "char* constructor failed (capacity)", str.capacity(), 7 );
	ensure_equals( "char* constructor failed (is_empty)", str.empty(), false );
	str += D_TEST;
	ensure_equals ( "operator+= does not work", str, D_CORRECT );
	ensure_equals( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "operator+= failed (capacity)", str.capacity(), 15 );
	ensure_equals( "operator+= failed (is_empty)", str.empty(), false );
	}

/* clear */
template<>
template<>
void module::test<13>( void )
	{
	HString str;
	static char const D_INIT[] = "1024";
	ensure_equals( "trivial construction failed", str, "" );
	ensure_equals( "trivial construction failed (size)", str.size(), 0 );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), -1 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), true );
	str += D_INIT;
	ensure_equals ( "operator+= does not work", str, D_INIT );
	ensure_equals( "operator+= failed (size)", str.size(), static_cast<int long>( sizeof ( D_INIT ) - 1 ) );
	ensure_equals( "operator+= failed (capacity)", str.capacity(), 7 );
	ensure_equals( "operator+= failed (is_empty)", str.empty(), false );
	str.clear();
	ensure_equals ( "clear does not work", str, "" );
	ensure_equals( "clear failed (size)", str.size(), 0 );
	ensure_equals( "clear failed (capacity)", str.capacity(), 7 );
	ensure_equals( "clear failed (is_empty)", str.empty(), true );
	}

/* replace */
template<>
template<>
void module::test<14>( void )
	{
	static char const D_INIT[] = "aarererererebb";
	static char const D_PAT1[] = "rere";
	static char const D_PAT2[] = "OKOK";
	static char const D_CORRECT12[] = "aaOKOKOKOKrebb";
	static char const D_PAT3[] = "rok";
	static char const D_CORRECT23[] = "aarokrokrebb";
	static char const D_PAT4[] = "I";
	static char const D_CORRECT34[] = "aaIIrebb";
	static char const D_PAT5[] = "II";
	static char const D_PAT6[] = "";
	static char const D_CORRECT56[] = "aarebb";

	HString str( D_INIT );
	ensure_equals ( "char* constructor does not work", str, D_INIT );
	ensure_equals( "char* constructor failed (size)", str.size(), static_cast<int long>( sizeof ( D_INIT ) - 1 ) );
	ensure_equals( "char* constructor failed (capacity)", str.capacity(), 15 );
	ensure_equals( "char* constructor failed (is_empty)", str.empty(), false );

	str.replace( D_PAT1, D_PAT2 );
	ensure_equals ( "replace 1->2 does not work", str, D_CORRECT12 );
	ensure_equals( "replace 1->2 failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT12 ) - 1 ) );
	ensure_equals( "replace 1->2 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 1->2 failed (is_empty)", str.empty(), false );

	str.replace( D_PAT2, D_PAT3 );
	ensure_equals ( "replace 2->3 does not work", str, D_CORRECT23 );
	ensure_equals( "replace 2->3 failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT23 ) - 1 ) );
	ensure_equals( "replace 2->3 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 2->3 failed (is_empty)", str.empty(), false );

	str.replace( D_PAT3, D_PAT4 );
	ensure_equals ( "replace 3->4 does not work", str, D_CORRECT34 );
	ensure_equals( "replace 3->4 failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT34 ) - 1 ) );
	ensure_equals( "replace 3->4 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 3->4 failed (is_empty)", str.empty(), false );

	str.replace( D_PAT5, D_PAT6 );
	ensure_equals ( "replace 5->6 does not work", str, D_CORRECT56 );
	ensure_equals( "replace 5->6 failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT56 ) - 1 ) );
	ensure_equals( "replace 5->6 failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace 5->6 failed (is_empty)", str.empty(), false );

	static char const D_INIT0[] = "./${NEST}/app/";
	static char const D_PATA[] = "${NEST}";
	static char const D_PATB[] = "";
	static char const D_CORRECT_AB[] = ".//app/";
	
	str = D_INIT0;
	str.replace( D_PATA, D_PATB );
	ensure_equals ( "replace A->B does not work", str, D_CORRECT_AB );
	ensure_equals( "replace A->B failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT_AB ) - 1 ) );
	ensure_equals( "replace A->B failed (capacity)", str.capacity(), 15 );
	ensure_equals( "replace A->B failed (is_empty)", str.empty(), false );

		{
		static char const D_INIT1[] = "@c@";
		static char const D_PAT1A[] = "@";
		static char const D_PAT1B[] = "UU";
		static char const D_CORRECT_1AB[] = "UUcUU";
		str = D_INIT1;
		str.replace( D_PAT1A, D_PAT1B );
		ensure_equals ( "replace A1->B1 does not work", str, D_CORRECT_1AB );
		ensure_equals( "replace A1->B1 failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT_1AB ) - 1 ) );
		ensure_equals( "replace A1->B1 failed (capacity)", str.capacity(), 15 );
		ensure_equals( "replace A1->B1 failed (is_empty)", str.empty(), false );
		ensure_equals( "bad lenght calculations", str.get_length(), static_cast<int long>( ::strlen( str.raw() ) ) );
		}
		{
		static char const D_INIT1[] = "c@cc@cc@cc@cc@cc@cc";
		static char const D_PAT1A[] = "@";
		static char const D_PAT1B[] = "@@";
		static char const D_CORRECT_1AB[] = "c@@cc@@cc@@cc@@cc@@cc@@cc";
		str = D_INIT1;
		str.replace( D_PAT1A, D_PAT1B );
		ensure_equals ( "replace A1->B1 does not work", str, D_CORRECT_1AB );
		ensure_equals( "replace A1->B1 failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT_1AB ) - 1 ) );
		ensure_equals( "replace A1->B1 failed (capacity)", str.capacity(), 31 );
		ensure_equals( "replace A1->B1 failed (is_empty)", str.empty(), false );
		ensure_equals( "bad lenght calculations", str.get_length(), static_cast<int long>( ::strlen( str.raw() ) ) );
		}
	}

/* shift_left */
template<>
template<>
void module::test<22>( void )
	{
	static char const D_CORRECT[] = "Ala ma kota";
	static int const D_SHIFT = 4;
	HString str( D_CORRECT );
	str.shift_left( D_SHIFT );
	ensure_equals( "left_shift failed", str, D_CORRECT + D_SHIFT );
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
	}

/* shift_right */
template<>
template<>
void module::test<23> ( void )
	{
	static char const D_CORRECT[] = "    Ala ma kota";
	static int const D_SHIFT = 4;
	HString str( D_CORRECT + D_SHIFT );
	str.shift_right( D_SHIFT );
	ensure_equals( "right_shift failed", str, D_CORRECT );
	try
		{
		str.shift_right( -1 );
		fail( "no check for negative shift" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	}

/* mid */
template<>
template<>
void module::test<24>( void )
	{
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
	}

/* split */
template<>
template<>
void module::test<25>( void )
	{
	char a[] = ",aa,bb";
	char b[] = "aa,bb";
	char c[] = "aa,bb,";
	char d[] = ",aa,";
	char e[] = ",,,aa,,";
	char f[] = "a";
	HString str;
	char split_failed[] = "split failed";
	str = f;
	ensure_equals( split_failed, str.split( ";", 0 ), "a" );
	ensure_equals( split_failed, str.split( ";", 1 ), "" );
	ensure_equals( split_failed, str.split( ";", 2 ), "" );
	ensure_equals( split_failed, str.split( "a", 0 ), "" );
	ensure_equals( split_failed, str.split( "a", 1 ), "" );
	ensure_equals( split_failed, str.split( "a", 2 ), "" );
	str = a;
	ensure_equals( split_failed, str.split( ",", 0 ), "" );
	ensure_equals( split_failed, str.split( ",", 1 ), "aa" );
	ensure_equals( split_failed, str.split( ",", 2 ), "bb" );
	ensure_equals( split_failed, str.split( ",", 3 ), "" );
	str = b;
	ensure_equals( split_failed, str.split( ",", 0 ), "aa" );
	ensure_equals( split_failed, str.split( ",", 1 ), "bb" );
	ensure_equals( split_failed, str.split( ",", 2 ), "" );
	ensure_equals( split_failed, str.split( ",", 3 ), "" );
	str = c;
	ensure_equals( split_failed, str.split( ",", 0 ), "aa" );
	ensure_equals( split_failed, str.split( ",", 1 ), "bb" );
	ensure_equals( split_failed, str.split( ",", 2 ), "" );
	ensure_equals( split_failed, str.split( ",", 3 ), "" );
	str = d;
	ensure_equals( split_failed, str.split( ",", 0 ), "" );
	ensure_equals( split_failed, str.split( ",", 1 ), "aa" );
	ensure_equals( split_failed, str.split( ",", 2 ), "" );
	ensure_equals( split_failed, str.split( ",", 3 ), "" );
	str = e;
	ensure_equals( split_failed, str.split( ",", 0 ), "" );
	ensure_equals( split_failed, str.split( ",", 1 ), "" );
	ensure_equals( split_failed, str.split( ",", 2 ), "" );
	ensure_equals( split_failed, str.split( ",", 3 ), "aa" );
	ensure_equals( split_failed, str.split( ",", 4 ), "" );
	ensure_equals( split_failed, str.split( ",", 5 ), "" );
	}

/* right */
template<>
template<>
void module::test<26>( void )
	{
	HString str( "ala/." );
	ensure_equals( "wrong right part extraction", str.right( 1 ), "." );
	}

/* erase */
template<>
template<>
void module::test<27>( void )
	{
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
	}

/* insert */
template<>
template<>
void module::test<28>( void )
	{
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
	}

/* find */
template<>
template<>
void module::test<29>( void )
	{
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
	static char const* const D_PREF = "---> group: ";
	static char const* const D_SUFF = "yaal, tra la la";
	HString line( D_PREF );
	line += D_SUFF;
	ensure_equals( HString().format( failed, 13 ), line.find( D_PREF ), 0 );
	}

/* find_one_of */
template<>
template<>
void module::test<30>( void )
	{
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
	}

/* find_other_than */
template<>
template<>
void module::test<31>( void )
	{
	HString str = "abcXYdeYXfg";
	char failed[] = "find_other_than failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.find_other_than( "abcXYdeYXfg" ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.find_other_than( "abXYdeYXfg" ), 2 );
	ensure_equals( HString().format( failed, 2 ), str.find_other_than( "abXYdeYXfg", 2 ), 2 );
	ensure_equals( HString().format( failed, 3 ), str.find_other_than( "abXYdeYXfg", 3 ), -1 );
	ensure_equals( HString().format( failed, 4 ), str.find_other_than( "abcdefg" ), 3 );
	ensure_equals( HString().format( failed, 5 ), str.find_other_than( "abcdefg", 5 ), 7 );
	}

/* reverse_find */
template<>
template<>
void module::test<32>( void )
	{
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
	}

/* reverse_find_one_of */
template<>
template<>
void module::test<33>( void )
	{
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
	}

/* reverse_find_other_than */
template<>
template<>
void module::test<34>( void )
	{
	HString str = "gfXYedYXcba";
	char failed[] = "reverse_find_other_than failed[%d]";
	ensure_equals( HString().format( failed, 0 ), str.reverse_find_other_than( "abcXYdeYXfg" ), -1 );
	ensure_equals( HString().format( failed, 1 ), str.reverse_find_other_than( "abXYdeYXfg" ), 2 );
	ensure_equals( HString().format( failed, 2 ), str.reverse_find_other_than( "abXYdeYXfg", 2 ), 2 );
	ensure_equals( HString().format( failed, 3 ), str.reverse_find_other_than( "abXYdeYXfg", 3 ), -1 );
	ensure_equals( HString().format( failed, 4 ), str.reverse_find_other_than( "abcdefg" ), 3 );
	ensure_equals( HString().format( failed, 5 ), str.reverse_find_other_than( "abcdefg", 5 ), 7 );
	}

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

/* find("") */
template<>
template<>
void module::test<35>( void )
	{
	static int const D_SAMPLE_SIZE = 128;
	char sample[ D_SAMPLE_SIZE + 1 ];
	sample[ D_SAMPLE_SIZE ] = 0;
	yaal::generate( sample, sample + D_SAMPLE_SIZE, gen_char() );
	yaal::copy( sample, sample + D_SAMPLE_SIZE, stream_iterator( cout ) ); cout << endl;
	HString str( sample );
	HString msg;
	for ( int len = 1; len <= D_SAMPLE_SIZE; ++ len )
		{
		for ( int offset = 0; offset < D_SAMPLE_SIZE; ++ offset )
			{
			int where = -1;
			do
				{
				int newwhere = ( ( len + offset ) <= D_SAMPLE_SIZE ) ? confirm( sample + where + 1,
						D_SAMPLE_SIZE - ( where + 1 ), sample + offset, len ) : -1;
				if ( newwhere >= 0 )
					newwhere += ( where + 1 );
				msg.format( "find(\"\") failed: %d,%d,%d", len, offset, where );
				ensure_equals( msg,
						where = ( offset + len <= D_SAMPLE_SIZE ) ? static_cast<int>( str.nfind( sample + offset, len, where + 1 ) ) : -1,
						newwhere );
				}
			while ( where >= 0 );
			}
		}
	}

/* trim_left("") */
template<>
template<>
void module::test<36>( void )
	{
	static char const* const D_SPACE = "   ";
	static HString const D_TEXT = "ala ma";
	static char const* const D_FINE = "1234";
	HString str( D_SPACE + D_TEXT );
	ensure_equals( "trim failed", str.trim_left(), str );
	HString fine( D_FINE );
	ensure_equals( "trim failed", fine.trim_left(), fine );
	HString space( D_SPACE );
	ensure_equals( "trim failed", space.trim_left(), "" );
	}

/* trim_right("") */
template<>
template<>
void module::test<37>( void )
	{
	static char const* const D_SPACE = "   ";
	static HString const D_TEXT = "ala ma";
	static char const* const D_FINE = "1234";
	HString str( D_TEXT + D_SPACE );
	ensure_equals( "trim 0 failed", str.trim_right(), str );
	HString fine( D_FINE );
	ensure_equals( "trim 1 failed", fine.trim_right(), fine );
	HString space( D_SPACE );
	ensure_equals( "trim 2 failed", space.trim_right(), "" );
	}

}


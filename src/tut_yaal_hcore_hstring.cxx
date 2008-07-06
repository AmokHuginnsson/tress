/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_hcore_hstring.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <iterator>
#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

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

struct tut_yaal_hcore_hstring
	{
	};

typedef test_group < tut_yaal_hcore_hstring > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hstring_group ( "yaal::hcore::HString" );

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
	ensure_equals( "trivial construction failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), 7 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), false );
	}

/* copy construction */
template<>
template<>
void module::test<3>( void )
	{
	static char const D_CORRECT[] = "1024";
	HString str( D_CORRECT );
	HString copy( str );
	ensure_equals ( "construction from c-string does not work", copy, D_CORRECT );
	ensure_equals( "trivial construction failed (size)", copy.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "trivial construction failed (capacity)", copy.capacity(), 7 );
	ensure_equals( "trivial construction failed (is_empty)", copy.empty(), false );
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
	ensure_equals( "trivial construction failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), 7 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), false );
	}

/* construction from int long */
template<>
template<>
void module::test<5>( void )
	{
	static int long const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int does not work", str, D_CORRECT );
	ensure_equals( "trivial construction failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), 7 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), false );
	}

/* construction from int unsigned */
template<>
template<>
void module::test<6>( void )
	{
	static int unsigned const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int does not work", str, D_CORRECT );
	ensure_equals( "trivial construction failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), 7 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), false );
	}

/* construction from int long unsigned */
template<>
template<>
void module::test<7>( void )
	{
	static int long unsigned const D_INIT = 1024;
	static char const D_CORRECT[] = "1024";
	HString str( D_INIT );
	ensure_equals ( "construction from int does not work", str, D_CORRECT );
	ensure_equals( "trivial construction failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) - 1 ) );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), 7 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), false );
	}

/* construction from char */
template<>
template<>
void module::test<8>( void )
	{
	static char const D_CORRECT = '1';
	HString str( D_CORRECT );
	ensure_equals ( "construction from int does not work", str, D_CORRECT );
	ensure_equals( "trivial construction failed (size)", str.size(), static_cast<int long>( sizeof ( D_CORRECT ) ) );
	ensure_equals( "trivial construction failed (capacity)", str.capacity(), 1 );
	ensure_equals( "trivial construction failed (is_empty)", str.empty(), false );
	}

#if 0
	double l1 = 22.;
	double m1 = 7.;
	HString d1( l1 / m1 );
	cout << "| d1 = " << d1 << " |" << endl;
	double long l2 = 22.;
	double long m2 = 7.;
	HString d2( l2 / m2 );
	cout << "| d2 = " << d2 << " |" << endl;
	d2.shift_left( 1 );
	double long x = strtold( d2, NULL );
	double y = strtod( d2, NULL );
	double long z = strtod( d2, NULL );
	cout << "| x = " << x << " |" << endl;
	cout << "| y = " << y << " |" << endl;
	d2 = z;
	cout << "| d2 = " << d2 << " |" << endl;
#endif

/* shift_left */
template<>
template<>
void module::test<22>( void )
	{
	HString str( "Ala ma kota" );
	HString exemplar( "ma kota" );
	str.shift_left( 4 );
	ensure_equals( "left_shift failed", str, exemplar );
	try
		{
		str.shift_left( - 1 );
		fail ( "no check for negative shift" );
		}
	catch ( HException& e )
		{
		cout << e.what() << endl;
		}
	str.shift_left( 100000 );
	exemplar = "";
	ensure_equals( "left_shift failed", str, exemplar );
	}

/* shift_right */
template<>
template<>
void module::test<23> ( void )
	{
	HString str( "Ala ma kota" );
	HString exemplar( "    Ala ma kota" );
	str.shift_right( 4 );
	ensure_equals( "right_shift failed", str, exemplar );
	try
		{
		str.shift_right( - 1 );
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
	HString str;
	char split_failed[] = "split failed";
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
	str = s;ensure_equals( erase_failed, str.erase( 4, 100 ), "Ala " );
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
	fastpat.set_at( len, 0 );
	char* p = ( len <= size ) ? strstr( str, fastpat.raw() ) : NULL;
	return ( p ? p - str : -1 );
	}

struct gen_char
	{
	HRandomizer _rnd;
	gen_char( void )
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
	yaal::copy( sample, sample + D_SAMPLE_SIZE, ostream_iterator<char>( cout ) ); cout << endl;
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
						where = ( offset + len <= D_SAMPLE_SIZE ) ? str.nfind( sample + offset, len, where + 1 ) : -1,
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
	ensure_equals( "trim filed", str.trim_left(), str );
	HString fine( D_FINE );
	ensure_equals( "trim filed", fine.trim_left(), fine );
	HString space( D_SPACE );
	ensure_equals( "trim filed", space.trim_left(), "" );
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
	ensure_equals( "trim filed", str.trim_right(), str );
	HString fine( D_FINE );
	ensure_equals( "trim filed", fine.trim_right(), fine );
	HString space( D_SPACE );
	ensure_equals( "trim filed", space.trim_right(), "" );
	}

}


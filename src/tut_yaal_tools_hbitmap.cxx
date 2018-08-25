/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hbitmap.hxx>
#include <yaal/tools/streamtools.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace yaal {

namespace tools {

inline bool operator == ( HBitmap const& bmp_, HString const& pat_ ) {
	HStringStream ss;
	ss << bmp_;
	return ( ss.str() == pat_ );
}

inline HStreamInterface& operator << ( HStreamInterface& stream_, HBitmap::HBit const& bit_ ) {
	stream_ << static_cast<bool>( bit_ );
	return ( stream_ );
}

inline std::ostream& operator << ( std::ostream& stream_, HBitmap::HBit const& bit_ ) {
	stream_ << static_cast<bool>( bit_ );
	return ( stream_ );
}

inline std::ostream& operator << ( std::ostream& stream_, HBitmap const& bmp_ ) {
	HStringStream ss;
	ss << bmp_;
	stream_ << ss.string();
	return ( stream_ );
}

}

}

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hbitmap );
TUT_TEST_GROUP( tut_yaal_tools_hbitmap, "yaal::tools::HBitmap" );

TUT_UNIT_TEST( "simple use" )
	static char const BUFF[] = "ala ma kota";
	static int const BUFF_BIT_SIZE( ( static_cast<int>( sizeof ( BUFF ) ) - 1 ) * 8 );
	HBitmap bmp;
	bmp.copy( BUFF, BUFF_BIT_SIZE );
	HBitmap const x( bmp );
	HStringStream ss;
	yaal::copy( x.begin(), x.end(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bitmap init failed", ss.str(), "0110000101101100011000010010000001101101011000010010000001101011011011110111010001100001" );
	yaal::fill_n( bmp.begin(), BUFF_BIT_SIZE / 2, true );
	HBitmap const y( bmp );
	ss.reset();
	yaal::copy( y.begin(), y.end(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bitmap partial fill failed", ss.str(), "1111111111111111111111111111111111111111111100010010000001101011011011110111010001100001" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Default constructor" )
	HBitmap bmp;
	ENSURE_EQUALS( "size", bmp.get_size(), 0 );
	ENSURE_EQUALS( "raw", bmp.raw(), static_cast<void*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "assign" )
	HBitmap bmpOwn;
	bmpOwn.copy( "a", 7 );
	char data[] = "b";
	HBitmap bmpUse;
	bmpUse.use( data, 7 );
	HBitmap bmp;
	bmp = bmpOwn;
	ENSURE_EQUALS( "own assign failed", bmpOwn, bmp );
	bmp = bmpUse;
	ENSURE_EQUALS( "use assign failed", bmpUse, bmp );
TUT_TEARDOWN()

TUT_UNIT_TEST( "constructor from size" )
	static int const SIZE = 7;
	HBitmap bmp( SIZE );
	ENSURE_EQUALS( "constructor from size size", bmp.get_size(), SIZE );
	ENSURE( "default constructor raw", bmp.raw() != static_cast<void*>( NULL ) );
	ENSURE( "default constructor ", bmp.raw() != static_cast<void*>( NULL ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "set" )
	HBitmap bmp;
	ENSURE_THROW( "default constructor set", bmp.set( 0, true ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get" )
	HBitmap bmp;
	ENSURE_THROW( "default constructor set", bmp.get( 0 ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rotate_left" )
	HBitmap bmp( 7 );
	ENSURE_EQUALS( "bad ctor", bmp, "0000000" );
	bmp[1] = bmp[3] = bmp[5] = bmp[2] = true;
	ENSURE_EQUALS( "bad [] init", bmp, "0111010" );
	ENSURE_THROW( "default constructor set", bmp.rotate_left( -1, 2, 1 ), HFailedAssertion );
	ENSURE_THROW( "default constructor set", bmp.rotate_left( 0, 0, 0 ), HFailedAssertion );
	ENSURE_THROW( "default constructor set", bmp.rotate_left( 0, 1, 1 ), HFailedAssertion );
	bmp.rotate_left( 0, 7, 2 );
	ENSURE_EQUALS( "bad rotate_left(2)", bmp, "1101001" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rotate_right" )
	HBitmap bmp( 7 );
	ENSURE_EQUALS( "bad ctor", bmp, "0000000" );
	bmp[1] = bmp[3] = bmp[5] = bmp[2] = true;
	ENSURE_EQUALS( "bad [] init", bmp, "0111010" );
	ENSURE_THROW( "default constructor set", bmp.rotate_right( -1, 2, 1 ), HFailedAssertion );
	ENSURE_THROW( "default constructor set", bmp.rotate_right( 0, 0, 0 ), HFailedAssertion );
	ENSURE_THROW( "default constructor set", bmp.rotate_right( 0, 1, 1 ), HFailedAssertion );
	bmp.rotate_right( 0, 7, 2 );
	ENSURE_EQUALS( "bad rotate_left(2)", bmp, "1001110" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse iteration" )
	static char const BUFF[] = "ala ma kota";
	static int const BUFF_BIT_SIZE( ( static_cast<int>( sizeof ( BUFF ) ) - 1 ) * 8 );
	HBitmap bmp;
	bmp.copy( BUFF, BUFF_BIT_SIZE );
	HStringStream ss;
	ss << bmp;
	HString s( ss.string() );
	ss.reset();
	yaal::copy( bmp.rbegin(), bmp.rend(), stream_iterator( ss ) );
	reverse( s.begin(), s.end() );
	ENSURE_EQUALS( "bad reverse iterator", ss.string(), s );
	ss.reset();
	HBitmap const& cbmp( bmp );
	yaal::copy( cbmp.rbegin(), cbmp.rend(), stream_iterator( ss ) );
	ENSURE_EQUALS( "bad reverse iterator", ss.string(), s );
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator[]" )
	HBitmap bmp( 7 );
	HBitmap const& constBmp( bmp );
	ENSURE_EQUALS( "bad constructor", bmp, "0000000" );
	ENSURE_EQUALS( "bad [] oper", constBmp[1], false );
	bmp[1] = true;
	ENSURE_EQUALS( "bad [] oper", constBmp[1], true );
	ENSURE_EQUALS( "bad [] oper", constBmp[0], false );
	ENSURE_EQUALS( "bad [] oper", constBmp[2], false );
	ENSURE_EQUALS( "bad operator[] or HBit ref", bmp, "0100000" );
	bmp[5] = true;
	ENSURE_EQUALS( "bad operator[] or HBit ref", bmp, "0100010" );
	bmp[0] = bmp[6] = bmp[1] && bmp[5];
	ENSURE_EQUALS( "bad operator[] or HBit ref", bmp, "1100011" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "push_back, size" )
	HBitmap bmp;
	bmp.push_back( true );
	bmp.push_back( false );
	bmp.push_back( true );
	bmp.push_back( true );
	bmp.push_back( false );
	bmp.push_back( true );
	bmp.push_back( false );
	ENSURE_EQUALS( "bad size", bmp.size(), 7 );
	ENSURE_EQUALS( "bad data", bmp, "1011010" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "clear" )
	HBitmap bmp;
	bmp.copy( "abc", 22 );
	ENSURE_EQUALS( "bad size", bmp.size(), 22 );
	HBitmap empty;
	bmp = empty;
	ENSURE_EQUALS( "bad size", bmp.size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "fill, reserve" )
	HBitmap bmp( 7 );
	ENSURE_EQUALS( "bad size", bmp.size(), 7 );
	ENSURE_EQUALS( "bad ctor", bmp, "0000000" );
	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "1111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "false true failed", bmp, "0000000" );
	bmp.fill( 0, 7, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "1111111" );
	bmp.fill( 1, 5, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "1000001" );
	bmp.fill( 2, 3, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "1011101" );
	bmp.fill( 3, 1, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "1010101" );
	bmp.fill( 0, 0, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "1010101" );
	ENSURE_THROW( "fill on neg offset succeeded", bmp.fill( -1, 0, false ), HBitmapException );
	ENSURE_THROW( "fill on neg amount succeeded", bmp.fill( 0, -1, false ), HBitmapException );

	bmp.reserve( 15 );
	ENSURE_EQUALS( "bad size", bmp.size(), 15 );

	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "111111111111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "fill false failed", bmp, "000000000000000" );
	bmp.fill( 0, 15, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "111111111111111" );
	bmp.fill( 1, 13, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "100000000000001" );
	bmp.fill( 2, 11, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "101111111111101" );
	bmp.fill( 3, 9, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "101000000000101" );
	bmp.fill( 4, 7, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "101011111110101" );
	bmp.fill( 5, 5, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "101010000010101" );
	bmp.fill( 6, 3, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "101010111010101" );
	bmp.fill( 7, 1, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "101010101010101" );

	bmp.reserve( 23 );
	ENSURE_EQUALS( "bad size", bmp.size(), 23 );

	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "11111111111111111111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "fill false failed", bmp, "00000000000000000000000" );
	bmp.fill( 0, 23, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "11111111111111111111111" );
	bmp.fill( 1, 21, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10000000000000000000001" );
	bmp.fill( 2, 19, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10111111111111111111101" );
	bmp.fill( 3, 17, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10100000000000000000101" );
	bmp.fill( 4, 15, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101111111111111110101" );
	bmp.fill( 5, 13, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101000000000000010101" );
	bmp.fill( 6, 11, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101011111111111010101" );
	bmp.fill( 7, 9, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101010000000001010101" );
	bmp.fill( 8, 7, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101010111111101010101" );
	bmp.fill( 9, 5, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101010100000101010101" );
	bmp.fill( 10, 3, true );
	ENSURE_EQUALS( "fill(range) true failed", bmp, "10101010101110101010101" );
	bmp.fill( 11, 1, false );
	ENSURE_EQUALS( "fill(range) false failed", bmp, "10101010101010101010101" );

	bmp.reserve( 32 );
	ENSURE_EQUALS( "bad size", bmp.size(), 32 );

	bmp.fill( true );
	ENSURE_EQUALS( "fill true failed", bmp, "11111111111111111111111111111111" );
	bmp.fill( false );
	ENSURE_EQUALS( "fill false failed", bmp, "00000000000000000000000000000000" );
	bmp.fill( 8, 16, true );
	ENSURE_EQUALS( "fill false failed", bmp, "00000000111111111111111100000000" );
	bmp.fill( true );
	bmp.fill( 8, 16, false );
	ENSURE_EQUALS( "fill false failed", bmp, "11111111000000000000000011111111" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "equality operator" )
	HBitmap bmpOwn;
	bmpOwn.copy( "a", 7 );
	char data[] = "b";
	HBitmap bmpUse;
	bmpUse.use( data, 7 );
	HBitmap bmp;
	bmp.copy( "a", 7 );
	ENSURE( "own equals on equal failed", bmpOwn == bmp );
	ENSURE_NOT( "own not equals on equal size succeeded", bmpOwn != bmp );
	bmp.copy( "a", 6 );
	ENSURE( "own equals on diff size failed", bmpOwn != bmp );
	ENSURE_NOT( "own not equals on diff size failed", bmpOwn == bmp );

	bmp.use( data, 7 );
	ENSURE( "use equals on equal failed", bmpUse == bmp );
	ENSURE_NOT( "use not equals on equal size succeeded", bmpUse != bmp );
	bmp.use( data, 6 );
	ENSURE( "use equals on diff size failed", bmpUse != bmp );
	ENSURE_NOT( "use not equals on diff size failed", bmpUse == bmp );

	bmpOwn.copy( "b", 8 );
	bmp.use( data, 8 );

	ENSURE( "own equals on equal failed", bmpOwn == bmp );
	ENSURE_NOT( "own not equals on equal succeeded", bmpOwn != bmp );
TUT_TEARDOWN()

TUT_UNIT_TEST( "or" )
	HBitmap bmp1( 7 );
	HBitmap bmp2( 7 );
	bmp1[1] = bmp1[3] = true;
	bmp2[1] = bmp2[4] = true;
	ENSURE_EQUALS( "or failed", bmp1 | bmp2, "0101100" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "and" )
	HBitmap bmp1( 7 );
	HBitmap bmp2( 7 );
	bmp1[1] = bmp1[3] = bmp1[5] = bmp1[2] = true;
	bmp2[1] = bmp2[4] = bmp2[5] = bmp2[0] = true;
	ENSURE_EQUALS( "and failed", bmp1 & bmp2, "0100010" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "xor" )
	HBitmap bmp1( 7 );
	HBitmap bmp2( 7 );
	bmp1[1] = bmp1[3] = bmp1[5] = bmp1[2] = true;
	bmp2[1] = bmp2[4] = bmp2[5] = bmp2[0] = true;
	ENSURE_EQUALS( "xor failed", bmp1 ^ bmp2, "1011100" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "concat +=" )
	HBitmap bmp( 7 );
	bmp[1] = bmp[3] = bmp[5] = bmp[2] = true;
	HBitmap bmp2( 5 );
	bmp2[1] = bmp2[3] = true;
	bmp += bmp2;
	ENSURE_EQUALS( "concat failed", bmp, "011101001010" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HBit::swap, HBit::==, find" )
	HBitmap bmp( 7 );
	bmp[1] = bmp[3] = bmp[5] = bmp[2] = true;
	ENSURE_EQUALS( "ctor failed", bmp, "0111010" );
	using yaal::swap;
	swap( bmp[0], bmp[1] );
	ENSURE_EQUALS( "ctor failed", bmp, "1011010" );
	ENSURE( "HBit::== (on same) failed", bmp[0] == bmp[2] );
	ENSURE_NOT( "HBit::== (on different) failed", bmp[0] == bmp[1] );
	ENSURE( "HBit::!= (on different) failed", bmp[0] != bmp[1] );
	ENSURE_NOT( "HBit::!= (on same) failed", bmp[0] != bmp[2] );
	HBitmap::iterator it( bmp.find( 1 ) );
	HBitmap const& constBmp( bmp );
	HBitmap::const_iterator cit( constBmp.find( 2 ) );
	ENSURE( "bad it from find", bmp[1] == *it );
	ENSURE( "bad cit from find", bmp[2] == *cit );
	HBitmap::HBit bit( *it );
	ENSURE_EQUALS( "inconsistent test state", bmp[1], false );
	bit = true;
	ENSURE_EQUALS( "using bit failed", bmp[1], true );
TUT_TEARDOWN()

}


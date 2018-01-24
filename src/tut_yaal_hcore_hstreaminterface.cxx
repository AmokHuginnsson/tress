/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hstreaminterface.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hstreaminterface : public tress::tut_helpers::simple_mock<tut_yaal_hcore_hstreaminterface> {
	HSynchronizedStream _ss;
	tut_yaal_hcore_hstreaminterface( void )
		: _ss( make_pointer<HStringStream>() ) {
	}
	virtual ~tut_yaal_hcore_hstreaminterface( void ) {
	}
	yaal::hcore::HString data( void ) {
		HString s;
		_ss.read_until( s );
		return ( s );
	}
	yaal::tools::HStringStream& string_stream( void ) {
		HStreamInterface::ptr_t si( make_pointer<HStringStream>() );
		_ss.reset( si );
		return ( static_cast<HStringStream&>( *si ) );
	}
};
TUT_TEST_GROUP( tut_yaal_hcore_hstreaminterface, "yaal::hcore::HStreamInterface" );

TUT_UNIT_TEST( "HSynchronizedStream::reset" )
	HStringStream ss;
	HStringStream::ptr_t nss( make_pointer<HStringStream>() );
	_ss << 7 << endl;
	_ss.reset( ss );
	ENSURE_EQUALS( "reset (unowning) failed", data(), "" );
	_ss << 13 << endl;
	HString s;
	ss.read_until( s );
	ENSURE_EQUALS( "read (unowning) failed", s, "13" );
	_ss << "xxx" << endl;
	_ss.reset( nss );
	ENSURE_EQUALS( "read (owning) failed", data(), "" );
	ss.read_until( s );
	ENSURE_EQUALS( "read (owning) failed", s, "xxx" );
	_ss << "abc" << endl;
	nss->read_until( s );
	ENSURE_EQUALS( "read (owning) failed", s, "abc" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "manipulators" )
	int i( 7 );
	_ss << "i = '" << i << "'" << endl;
	ENSURE_EQUALS( "plain int", data(), "i = '7'" );
	_ss << "i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	ENSURE_EQUALS( "setw() int", data(), "i = '    7' \tsetw( 5 )" );
	_ss << "i = '" << setfill( '0'_ycp ) << i << "'" << " \tsetfill( '0' )" << endl;
	ENSURE_EQUALS( "setfill() int", data(), "i = '7' \tsetfill( '0' )" );
	_ss << "i = '" << setfill( '0'_ycp ) << setw( 5 ) << i << "'" << " \tsetfill( '0' ), setw( 5 )" << endl;
	ENSURE_EQUALS( "setfill() setw() int", data(), "i = '00007' \tsetfill( '0' ), setw( 5 )" );
	_ss << "i = '" << setw( 5 ) << i << "'" << " \tsetw( 5 )" << endl;
	ENSURE_EQUALS( "setw() int", data(), "i = '00007' \tsetw( 5 )" );
	_ss << "i = '" << setfill( '0'_ycp ) << i << "'" << " \tsetfill( '0' )" << endl;
	ENSURE_EQUALS( "setfill() int", data(), "i = '7' \tsetfill( '0' )" );
	int prec( _ss.get_precision() );
	_ss << fixed << setprecision( 2 ) << "pi = " << math::PI << setprecision( prec ) << natural << " \tsetprecision( 2 )" << endl;
	ENSURE_EQUALS( "setprecicion() int", data(), "pi = 3.14 \tsetprecision( 2 )" );
	int k( 103 );
	_ss << "k = '" << k << "'" << endl;
	ENSURE_EQUALS( "dec int", data(), "k = '103'" );
	_ss << "k = '" << hex << k << "' \thex" << endl;
	ENSURE_EQUALS( "get_base", static_cast<int>( _ss.get_base() ), static_cast<int>( HStreamInterface::BASE::HEX ) );
	ENSURE_EQUALS( "dec int hex", data(), "k = '67' \thex" );
	_ss << "k = '" << k << "'" << endl;
	ENSURE_EQUALS( "dec int", data(), "k = '67'" );
	_ss << dec;
	ENSURE_EQUALS( "set_base/get_base", static_cast<int>( _ss.get_base() ), static_cast<int>( HStreamInterface::BASE::DEC ) );
	_ss << "k = '" << k << "'" << endl;
	ENSURE_EQUALS( "dec int", data(), "k = '103'" );
	ENSURE_EQUALS( "getfill/setfill", _ss.get_fill(), '0'_ycp );
	_ss << setfill( ' '_ycp ) << "[" << setw( 10 ) << right << "yaal" << "]" << endl;
	ENSURE_EQUALS( "right", data(), "[      yaal]" );
	ENSURE_EQUALS( "get_adjustment", static_cast<int>( _ss.get_adjust() ), static_cast<int>( HStreamInterface::ADJUST::RIGHT ) );
	_ss << setw( 13 );
	ENSURE_EQUALS( "setw/get_width", _ss.get_width(), 13 );
	_ss << left << setw( 0 ) << "[" << setw( 10 ) << center << "yaal" << "]" << endl;
	ENSURE_EQUALS( "center", data(), "[   yaal   ]" );
	_ss << left << "[" << setw( 10 ) << "yaal" << "]" << endl;
	ENSURE_EQUALS( "left", data(), "[yaal      ]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until (delims stripped)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_while()" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	char sink( 0 );
	char peek( 0 );
	nRead = _ss.read_while( line, character_class( CHARACTER_CLASS::LETTER ).data() );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	peek = static_cast<char>( _ss.peek() );
	_ss.read( &sink, 1 );
	ENSURE_EQUALS( "bad peek", peek, sink );
	nRead = _ss.read_while( line, character_class( CHARACTER_CLASS::LETTER ).data() );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	peek = static_cast<char>( _ss.peek() );
	_ss.read( &sink, 1 );
	ENSURE_EQUALS( "bad peek", peek, sink );
	nRead = _ss.read_while( line, character_class( CHARACTER_CLASS::LETTER ).data() );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "kota" );
	peek = static_cast<char>( _ss.peek() );
	_ss.read( &sink, 1 );
	ENSURE_EQUALS( "bad peek", peek, sink );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_while_n()" )
	static char src[] = "Alamakotaxxx";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_while_n( line, 3, character_class( CHARACTER_CLASS::LETTER ).data() );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_while_n( line, 2, character_class( CHARACTER_CLASS::LETTER ).data() );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_while_n( line, 4, character_class( CHARACTER_CLASS::LETTER ).data() );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "kota" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until (delims not stripped)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "Ala\n" );
	nRead = _ss.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "ma\n" );
	nRead = _ss.read_until( line, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until_n (delim stripped, by delim)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 4 );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_until_n( line, 3 );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_until_n( line, 5 );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until_n (delim stripped, by size)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 3 );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = _ss.read_until_n( line, 2 );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = _ss.read_until_n( line, 5 );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until_n (delim not stripped, by delim)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 4, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "Ala\n" );
	nRead = _ss.read_until_n( line, 3, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "ma\n" );
	nRead = _ss.read_until_n( line, 5, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read_until_n (delim not stripped, by size)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream() );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 3, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = _ss.read_until_n( line, 2, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 0 );
	nRead = _ss.read_until_n( line, 5, HStreamInterface::eols, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN()

TUT_UNIT_TEST( "input float" )
	static char src[] = "3.1415 -2.7182";
	HStringStream& ss( string_stream() );
	ss.str( src );
	float val( 0 );
	_ss >> val;
	ENSURE_DISTANCE( "float value read fail", val, static_cast<float>( 3.1415 ), static_cast<float>( epsilon ) );
	_ss >> val;
	ENSURE_DISTANCE( "float negative value read fail", val, static_cast<float>( -2.7182 ), static_cast<float>( epsilon ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "outputs" )
	_ss << true;
	ENSURE_EQUALS( "bool output failed", data(), "1" );
	_ss << boolalpha << true;
	ENSURE_EQUALS( "bool output failed", data(), "true" );
	_ss << noboolalpha << false;
	ENSURE_EQUALS( "bool output failed", data(), "0" );
	_ss << boolalpha << false;
	ENSURE_EQUALS( "bool output failed", data(), "false" );
#ifdef __MSVCXX__
	code_point_t cp( 945_ycp );
#else
	code_point_t cp( U'α'_ycp );
#endif
	_ss << cp;
	ENSURE_EQUALS( "char output failed", data(), "α" );
	_ss << 'a';
	ENSURE_EQUALS( "char output failed", data(), "a" );
	_ss << static_cast<char unsigned>( 'a' );
	ENSURE_EQUALS( "char unsigned output failed", data(), "a" );
	_ss << static_cast<short int>( 12345 );
	ENSURE_EQUALS( "short int output failed", data(), "12345" );
	_ss << static_cast<short int unsigned>( 54321 );
	ENSURE_EQUALS( "short int unsigned output failed", data(), "54321" );
	_ss << static_cast<int>( 2147483647 );
	ENSURE_EQUALS( "int output failed", data(), "2147483647" );
	_ss << static_cast<int unsigned>( 4294967295 );
	ENSURE_EQUALS( "int unsigned output failed", data(), "4294967295" );
#if SIZEOF_INT_LONG == 8
	_ss << static_cast<int long>( 9223372036854775807L );
	ENSURE_EQUALS( "long int output failed", data(), "9223372036854775807" );
	_ss << static_cast<int long unsigned>( 18446744073709551615LLU );
	ENSURE_EQUALS( "long int unsigned output failed", data(), "18446744073709551615" );
#else
	_ss << static_cast<int>( 2147483647 );
	ENSURE_EQUALS( "long int output failed", data(), "2147483647" );
	_ss << static_cast<int unsigned>( 4294967295 );
	ENSURE_EQUALS( "long int unsigned output failed", data(), "4294967295" );
#endif
	_ss << static_cast<int long long>( 9223372036854775807L );
	ENSURE_EQUALS( "long long int output failed", data(), "9223372036854775807" );
	_ss << static_cast<int long long unsigned>( 18446744073709551615LLU );
	ENSURE_EQUALS( "unsigned long long int output failed", data(), "18446744073709551615" );
	_ss << 3.141592653589793L;
	ENSURE_EQUALS( "double long output failed", data(), "3.14159265359" );
	_ss << 3.14159;
	ENSURE_EQUALS( "double output failed", data(), "3.14159" );
	_ss << 3.14f;
	ENSURE_EQUALS( "float output failed", data(), "3.14" );
	_ss << "Ala ma kota";
	ENSURE_EQUALS( "char const* output failed", data(), "Ala ma kota" );
	_ss << "Ala ma kota"_ys;
	ENSURE_EQUALS( "HString output failed", data(), "Ala ma kota" );
	_ss << static_cast<void*>( nullptr );
	ENSURE_EQUALS( "HString output failed", data(), "0x0" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "inputs" )
#if SIZEOF_INT_LONG == 8
	_ss << "true false αol 32767 32768 32768 2147483647 2147483648 2147483648 9223372036854775807 9223372036854775808 9223372036854775808 9223372036854775807 9223372036854775808 9223372036854775808 3.1415 2.7182828 1.414213562373 Ala+ma|kota; 0x1234";
#else
	_ss << "true false αol 32767 32768 32768 2147483647 2147483648 2147483648 2147483647 2147483648 2147483648 9223372036854775807 9223372036854775808 9223372036854775808 3.1415 2.7182818 1.414213562373 Ala+ma|kota; 0x1234";
#endif
	bool b( false );
	_ss >> b;
	ENSURE( "bool input failed", b );
	_ss >> b;
	ENSURE_NOT( "bool input failed", b );
	code_point_t cp( 0 );
	_ss >> cp;
#ifdef __MSVCXX__
	code_point_t exp( 945_ycp );
#else
	code_point_t exp( U'α'_ycp );
#endif
	ENSURE_EQUALS( "char input failed", cp, exp );
	char c( 0 );
	_ss >> c;
	ENSURE_EQUALS( "char input failed", c, 'o' );
	char unsigned cu( 0 );
	_ss >> cu;
	ENSURE_EQUALS( "char unsigned input failed", cu, 'l' );
	int short is( 0 );
	_ss >> is;
	ENSURE_EQUALS( "int short input failed", is, 32767 );
	ENSURE_THROW( "data clobbered", _ss >> is, HOutOfRangeException );
	int short unsigned isu( 0 );
	_ss >> isu;
	ENSURE_EQUALS( "int short unsigned input failed", isu, 32768 );
	int i( 0 );
	_ss >> i;
	ENSURE_EQUALS( "int input failed", i, 2147483647 );
	ENSURE_THROW( "data clobbered", _ss >> i, HOutOfRangeException );
	int unsigned iu( 0 );
	_ss >> iu;
	ENSURE_EQUALS( "int unsigned input failed", iu, 2147483648u );

#if SIZEOF_INT_LONG == 8
	int long il( 0 );
	_ss >> il;
	ENSURE_EQUALS( "int long input failed", il, 9223372036854775807LL );
	ENSURE_THROW( "data clobbered", _ss >> il, HOutOfRangeException );
	int long unsigned ilu( 0 );
	_ss >> ilu;
	ENSURE_EQUALS( "int long unsigned input failed", ilu, 9223372036854775808ULL );
#else
	int long il( 0 );
	_ss >> il;
	ENSURE_EQUALS( "int long input failed", il, 2147483647 );
	ENSURE_THROW( "data clobbered", _ss >> il, HOutOfRangeException );
	int long unsigned ilu( 0 );
	_ss >> ilu;
	ENSURE_EQUALS( "int long unsigned input failed", ilu, 2147483648u );
#endif

	int long long ill( 0 );
	_ss >> ill;
	ENSURE_EQUALS( "int long long input failed", ill, 9223372036854775807LL );
	ENSURE_THROW( "data clobbered", _ss >> ill, HOutOfRangeException );
	int long long unsigned illu( 0 );
	_ss >> illu;
	ENSURE_EQUALS( "int long long unsigned input failed", illu, 9223372036854775808ULL );

	float f( 0 );
	_ss >> f;
	ENSURE_DISTANCE( "float input failed", f, 3.1415f, static_cast<float>( epsilon ) );

	double d( 0 );
	_ss >> d;
	ENSURE_DISTANCE( "double input failed", d, 2.7182818, static_cast<double>( epsilon ) );

	double long dl( 0 );
	_ss >> dl;
	ENSURE_DISTANCE( "double long input failed", dl, 1.414213562373L, epsilon );

	HString s;
	_ss >> s;
	ENSURE_EQUALS( "HString input failed", s, "Ala+ma|kota;" );

	void const* p( nullptr );
	_ss >> hex >>  p;
	ENSURE_EQUALS( "pointer input failed", p, reinterpret_cast<void*>( static_cast<size_t>( 0x1234 ) ) );
TUT_TEARDOWN()

}


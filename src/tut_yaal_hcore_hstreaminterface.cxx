/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hstreaminterface.hxx>
#include <yaal/hcore/hstring.hxx>
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
		getline( _ss, s );
		return s;
	}
	yaal::tools::HStringStream& string_stream( bool buffered_ ) {
		HStreamInterface::ptr_t si( make_pointer<HStringStream>() );
		si->set_buffered_io( buffered_ );
		_ss.reset_owned( si );
		_ss.set_buffered_io( buffered_ );
		return ( static_cast<HStringStream&>( *si ) );
	}
};
TUT_TEST_GROUP( tut_yaal_hcore_hstreaminterface, "yaal::hcore::HStreamInterface" );
#define TUT_UNIT_TEST_S( ... ) TUT_UNIT_TEST( __VA_ARGS__ ) for ( int buffered( 0 ); buffered < 2; ++ buffered ) { clog << "buffered: " << buffered << endl; string_stream( buffered );
#define TUT_TEARDOWN_S( ... ) } TUT_TEARDOWN( __VA_ARGS__ )

TUT_UNIT_TEST_S( "HSynchronizedStream::reset_owned" )
	HStringStream ss;
	HStringStream::ptr_t nss( make_pointer<HStringStream>() );
	ss.set_buffered_io( buffered ? true : false );
	nss->set_buffered_io( buffered ? true : false );
	_ss << 7 << endl;
	_ss.reset_referenced( ss );
	ENSURE_EQUALS( "reset_owned (unowning) failed", data(), "" );
	_ss << 13 << endl;
	HString s;
	getline( ss, s );
	ENSURE_EQUALS( "read (unowning) failed", s, "13" );
	_ss << "xxx" << endl;
	_ss.reset_owned( nss );
	ENSURE_EQUALS( "read (owning) failed", data(), "" );
	getline( ss, s );
	ENSURE_EQUALS( "read (owning) failed", s, "xxx" );
	_ss << "abc" << endl;
	getline( *nss, s );
	ENSURE_EQUALS( "read (owning) failed", s, "abc" );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "manipulators" )
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
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_until (delims extracted)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "Ala\n" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "ma\n" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_while()" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	char sink( 0 );
	char peek( 0 );
	nRead = _ss.read_while( line, character_class<CHARACTER_CLASS::LETTER>().data() );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	peek = static_cast<char>( _ss.peek() );
	_ss.read( &sink, 1 );
	ENSURE_EQUALS( "bad peek", peek, sink );
	nRead = _ss.read_while( line, character_class<CHARACTER_CLASS::LETTER>().data() );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	peek = static_cast<char>( _ss.peek() );
	_ss.read( &sink, 1 );
	ENSURE_EQUALS( "bad peek", peek, sink );
	nRead = _ss.read_while( line, character_class<CHARACTER_CLASS::LETTER>().data() );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "kota" );
	peek = static_cast<char>( _ss.peek() );
	_ss.read( &sink, 1 );
	ENSURE_EQUALS( "bad peek", peek, sink );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_while_n()" )
	static char src[] = "Alamakotaxxx";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_while_n( line, 3, character_class<CHARACTER_CLASS::LETTER>().data() );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_while_n( line, 2, character_class<CHARACTER_CLASS::LETTER>().data() );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_while_n( line, 4, character_class<CHARACTER_CLASS::LETTER>().data() );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "kota" );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_until (delims not extracted)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until( line, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	char nl( 0 );
	ENSURE_EQUALS( "bad len of delim read",  _ss.read( &nl, 1 ), 1 );
	ENSURE_EQUALS( "bad delim read", nl, '\n' );
	nRead = _ss.read_until( line, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nl = 0;
	ENSURE_EQUALS( "bad len of delim read",  _ss.read( &nl, 1 ), 1 );
	ENSURE_EQUALS( "bad delim read", nl, '\n' );
	nRead = _ss.read_until( line, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_until_n (delim extracted, by delim)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 4 );
	ENSURE_EQUALS( "wrong read size", nRead, 4 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 4 );
	ENSURE_EQUALS( "bad data read", line, "Ala\n" );
	nRead = _ss.read_until_n( line, 3 );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "ma\n" );
	nRead = _ss.read_until_n( line, 5 );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_until_n (delim extracted, by size)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 3 );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 1 );
	nRead = _ss.read_until_n( line, 2 );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 1 );
	nRead = _ss.read_until_n( line, 5 );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_until_n (delim not extracted, by delim)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 4, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	char nl( 0 );
	ENSURE_EQUALS( "bad len of delim read",  _ss.read( &nl, 1 ), 1 );
	ENSURE_EQUALS( "bad delim read", nl, '\n' );
	nRead = _ss.read_until_n( line, 3, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nl = 0;
	ENSURE_EQUALS( "bad len of delim read",  _ss.read( &nl, 1 ), 1 );
	ENSURE_EQUALS( "bad delim read", nl, '\n' );
	nRead = _ss.read_until_n( line, 5, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "read_until_n (delim not extracted, by size)" )
	static char src[] = "Ala\nma\nkota.";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	HString line;
	int long nRead( 0 );
	nRead = _ss.read_until_n( line, 3, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 3 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 3 );
	ENSURE_EQUALS( "bad data read", line, "Ala" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 1 );
	nRead = _ss.read_until_n( line, 2, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 2 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 2 );
	ENSURE_EQUALS( "bad data read", line, "ma" );
	nRead = _ss.read_until( line );
	ENSURE_EQUALS( "wrong read size", nRead, 1 );
	ENSURE_EQUALS( "delim not stripped", line.get_length(), 1 );
	nRead = _ss.read_until_n( line, 5, HStreamInterface::eol, false );
	ENSURE_EQUALS( "wrong read size", nRead, 5 );
	ENSURE_EQUALS( "delim stripped", line.get_length(), 5 );
	ENSURE_EQUALS( "bad data read", line, "kota." );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input float" )
	static char src[] = "3.1415 -2.7182";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	float val( 0 );
	_ss >> val;
	ENSURE_DISTANCE( "float value read fail", val, static_cast<float>( 3.1415 ), static_cast<float>( epsilon ) );
	_ss >> val;
	ENSURE_DISTANCE( "float negative value read fail", val, static_cast<float>( -2.7182 ), static_cast<float>( epsilon ) );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input double long after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	double long dl[3] = { 0.L, 0.L, 0.L };
	for ( double long& d : dl ) {
		try {
			_ss >> d;
		} catch ( ... ) {
		}
	}
	ENSURE_DISTANCE( "double long value read fail", dl[0], 1.L, epsilon );
	ENSURE_DISTANCE( "spurious double long value read", dl[1], 0.L, epsilon );
	ENSURE_DISTANCE( "spurious double long value read", dl[2], 0.L, epsilon );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input double after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	double d[3] = { 0.L, 0.L, 0.L };
	for ( double& x : d ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_DISTANCE( "double value read fail", d[0], 1., static_cast<double>( epsilon ) );
	ENSURE_DISTANCE( "spurious double value read", d[1], 0., static_cast<double>( epsilon ) );
	ENSURE_DISTANCE( "spurious double value read", d[2], 0., static_cast<double>( epsilon ) );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input float after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	float d[3] = { 0.L, 0.L, 0.L };
	for ( float& x : d ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_DISTANCE( "float value read fail", d[0], 1.F, static_cast<float>( epsilon ) );
	ENSURE_DISTANCE( "spurious float value read", d[1], 0.F, static_cast<float>( epsilon ) );
	ENSURE_DISTANCE( "spurious float value read", d[2], 0.F, static_cast<float>( epsilon ) );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int long long after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int long long ill[3] = { 0, 0, 0 };
	for ( int long long& x : ill ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int long long value read fail", ill[0], 1 );
	ENSURE_EQUALS( "spurious int long long value read", ill[1], 0 );
	ENSURE_EQUALS( "spurious int long lomg value read", ill[2], 0 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int long long unsigned after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int long long unsigned ill[3] = { 0, 0, 0 };
	for ( int long long unsigned& x : ill ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int long long unsigned value read fail", ill[0], 1ULL );
	ENSURE_EQUALS( "spurious int long long unsigned value read", ill[1], 0ULL );
	ENSURE_EQUALS( "spurious int long lomg value read", ill[2], 0ULL );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int long after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int long il[3] = { 0, 0, 0 };
	for ( int long& x : il ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int long value read fail", il[0], 1 );
	ENSURE_EQUALS( "spurious int long value read", il[1], 0 );
	ENSURE_EQUALS( "spurious int long value read", il[2], 0 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int long unsigned after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int long unsigned il[3] = { 0, 0, 0 };
	for ( int long unsigned& x : il ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int long unsigned value read fail", il[0], 1UL );
	ENSURE_EQUALS( "spurious int long unsigned value read", il[1], 0UL );
	ENSURE_EQUALS( "spurious int long unsigned value read", il[2], 0UL );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int i[3] = { 0, 0, 0 };
	for ( int& ii : i ) {
		try {
			_ss >> ii;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int value read fail", i[0], 1 );
	ENSURE_EQUALS( "spurious int value read", i[1], 0 );
	ENSURE_EQUALS( "spurious int value read", i[2], 0 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int unsigned after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int unsigned i[3] = { 0, 0, 0 };
	for ( int unsigned& ii : i ) {
		try {
			_ss >> ii;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int unsigned value read fail", i[0], 1u );
	ENSURE_EQUALS( "spurious int unsigned value read", i[1], 0u );
	ENSURE_EQUALS( "spurious int unsigned value read", i[2], 0u );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int short after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int short is[3] = { 0, 0, 0 };
	for ( int short& x : is ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int short value read fail", is[0], 1 );
	ENSURE_EQUALS( "spurious int short value read", is[1], 0 );
	ENSURE_EQUALS( "spurious int short value read", is[2], 0 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "input int short unsigned after fail" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int short unsigned is[3] = { 0, 0, 0 };
	for ( int short unsigned& x : is ) {
		try {
			_ss >> x;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int short unsigned value read fail", is[0], 1 );
	ENSURE_EQUALS( "spurious int short unsigned value read", is[1], 0 );
	ENSURE_EQUALS( "spurious int short unsigned value read", is[2], 0 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "outputs" )
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
	_ss.set_boolalpha( false );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "inputs" )
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
	_ss.clear();
	_ss >> isu;
	ENSURE_EQUALS( "int short unsigned input failed", isu, 32768 );
	int i( 0 );
	_ss >> i;
	ENSURE_EQUALS( "int input failed", i, 2147483647 );
	ENSURE_THROW( "data clobbered", _ss >> i, HOutOfRangeException );
	int unsigned iu( 0 );
	_ss.clear();
	_ss >> iu;
	ENSURE_EQUALS( "int unsigned input failed", iu, 2147483648u );

#if SIZEOF_INT_LONG == 8
	int long il( 0 );
	_ss >> il;
	ENSURE_EQUALS( "int long input failed", il, 9223372036854775807LL );
	ENSURE_THROW( "data clobbered", _ss >> il, HOutOfRangeException );
	int long unsigned ilu( 0 );
	_ss.clear();
	_ss >> ilu;
	ENSURE_EQUALS( "int long unsigned input failed", ilu, 9223372036854775808ULL );
#else
	int long il( 0 );
	_ss >> il;
	ENSURE_EQUALS( "int long input failed", il, 2147483647 );
	ENSURE_THROW( "data clobbered", _ss >> il, HOutOfRangeException );
	int long unsigned ilu( 0 );
	_ss.clear();
	_ss >> ilu;
	ENSURE_EQUALS( "int long unsigned input failed", ilu, 2147483648u );
#endif

	int long long ill( 0 );
	_ss >> ill;
	ENSURE_EQUALS( "int long long input failed", ill, 9223372036854775807LL );
	ENSURE_THROW( "data clobbered", _ss >> ill, HOutOfRangeException );
	int long long unsigned illu( 0 );
	_ss.clear();
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
TUT_TEARDOWN_S()

TUT_UNIT_TEST( "full text from stream to string" )
	char const expected[] = "żółćżółćżółćżółćżółćżółćżółćżółć";
	HStringStream ss( expected );
	HString s;
	ss >> s;
	ENSURE_EQUALS( "getting full text to single string from stream failed", s, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST_S( "binary I/O" )
	char const PATH[] = "./out/binary.bin";
	HFile f( PATH, HFile::OPEN::WRITING );
	bool cBool1( false );
	bool cBool2( true );
	char cChar( 0 );
	char unsigned cCharUnsigned( 0 );
	int short cIntShort( 0 );
	int short unsigned cIntShortUnsigned( 0 );
	int cInt( 0 );
	int unsigned cIntUnsigned( 0 );
	int long cIntLong( 0 );
	int long unsigned cIntLongUnsigned( 0 );
	int long long cIntLongLong( 0 );
	int long long unsigned cIntLongLongUnsigned( 0 );
	code_point_t cCodePoint( 0 );
	double long cDoubleLong( 0 );
	double cDouble( 0 );
	float cFloat( 0 );
	HString cString;
	void const* cPointer( nullptr );
	f << binary
		<< ( cBool1 = true )
		<< ( cBool2 = false )
		<< ( cChar = 7 )
		<< ( cCharUnsigned = 77 )
		<< ( cIntShort = -1024 )
		<< ( cIntShortUnsigned = 2048 )
		<< ( cInt = -87654 )
		<< ( cIntUnsigned = 87654 )
		<< ( cIntLong = -9876543 )
		<< ( cIntLongUnsigned = 9876543 )
		<< ( cIntLongLong = -987654321098765432LL )
		<< ( cIntLongLongUnsigned = 987654321098765432LL )
#ifndef __MSVCXX__
		<< ( cCodePoint = code_point_t( U'✓'_ycp ) )
#else
		<< ( cCodePoint = code_point_t( 10003_ycp ) )
#endif
		<< ( cDoubleLong = 3.1415926535897932L )
		<< ( cDouble = 2.718281828459045 )
		<< ( cFloat = 123.456f )
		<< ( cString = "Yet Another Abstraction Layer ✓" )
		<< ( cPointer = static_cast<void const*>( &f ) );
	f.close();
	f.open( PATH, HFile::OPEN::READING );
	bool vBool1( false );
	bool vBool2( true );
	char vChar( 0 );
	char unsigned vCharUnsigned( 0 );
	int short vIntShort( 0 );
	int short unsigned vIntShortUnsigned( 0 );
	int vInt( 0 );
	int unsigned vIntUnsigned( 0 );
	int long vIntLong( 0 );
	int long unsigned vIntLongUnsigned( 0 );
	int long long vIntLongLong( 0 );
	int long long unsigned vIntLongLongUnsigned( 0 );
	code_point_t vCodePoint( 0 );
	double long vDoubleLong( 0 );
	double vDouble( 0 );
	float vFloat( 0 );
	HString vString;
	void const* vPointer( nullptr );
	f >> binary
		>> vBool1
		>> vBool2
		>> vChar
		>> vCharUnsigned
		>> vIntShort
		>> vIntShortUnsigned
		>> vInt
		>> vIntUnsigned
		>> vIntLong
		>> vIntLongUnsigned
		>> vIntLongLong
		>> vIntLongLongUnsigned
		>> vCodePoint
		>> vDoubleLong
		>> vDouble
		>> vFloat
		>> vString
		>> vPointer;
	ENSURE_EQUALS( "bool bin I/O failed", vBool1, cBool1 );
	ENSURE_EQUALS( "bool bin I/O failed", vBool2, cBool2 );
	ENSURE_EQUALS( "char bin I/O failed", vChar, cChar );
	ENSURE_EQUALS( "char unsigned bin I/O failed", vCharUnsigned, cCharUnsigned );
	ENSURE_EQUALS( "int short bin I/O failed", vIntShort, cIntShort );
	ENSURE_EQUALS( "int short unsigned bin I/O failed", vIntShortUnsigned, cIntShortUnsigned );
	ENSURE_EQUALS( "int bin I/O failed", vInt, cInt );
	ENSURE_EQUALS( "int unsigned bin I/O failed", vIntUnsigned, cIntUnsigned );
	ENSURE_EQUALS( "int long bin I/O failed", vIntLong, cIntLong );
	ENSURE_EQUALS( "int long unsigned bin I/O failed", vIntLongUnsigned, cIntLongUnsigned );
	ENSURE_EQUALS( "int long long bin I/O failed", vIntLongLong, cIntLongLong );
	ENSURE_EQUALS( "int long long unsigned bin I/O failed", vIntLongLongUnsigned, cIntLongLongUnsigned );
	ENSURE_EQUALS( "code_point_t bin I/O failed", vCodePoint, cCodePoint );
	ENSURE_EQUALS( "double long bin I/O failed", vDoubleLong, cDoubleLong );
	ENSURE_EQUALS( "double bin I/O failed", vDouble, cDouble );
	ENSURE_EQUALS( "float bin I/O failed", vFloat, cFloat );
	ENSURE_EQUALS( "HString bin I/O failed", vString, cString );
	ENSURE_EQUALS( "void* bin I/O failed", vPointer, cPointer );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "ignore" )
	static char src[] = "1 a 2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int i0( 0 );
	int i1( 0 );
	_ss >> i0;
	_ss.ignore( 2 );
	_ss >> i1;
	ENSURE_EQUALS( "int value read fail", i0, 1 );
	ENSURE_EQUALS( "int value read fail", i1, 2 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "consume" )
	static char src[] = "1kot2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int i0( 0 );
	int i1( 0 );
	_ss >> i0;
	_ss.consume( "ala" );
	_ss >> i1;
	ENSURE_EQUALS( "int value read fail", i0, 1 );
	ENSURE_EQUALS( "consume failed", i1, 0 );
	_ss.clear();
	_ss.consume( "kot" );
	_ss >> i1;
	ENSURE_EQUALS( "int value read fail", i1, 2 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST_S( "unread" )
	static char src[] = "ot2";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int i0( 0 );
	int i1( 0 );
	_ss.unread( "1k", 2 );
	_ss >> i0;
	_ss.consume( "ala" );
	_ss >> i1;
	ENSURE_EQUALS( "int value read fail", i0, 1 );
	ENSURE_EQUALS( "consume failed", i1, 0 );
	_ss.clear();
	_ss.consume( "kot" );
	_ss >> i1;
	ENSURE_EQUALS( "int value read fail", i1, 2 );
TUT_TEARDOWN_S()

TUT_UNIT_TEST( "unread after unflushed write" )
	HFile f( "out/unflushed-unread.txt", HFile::OPEN::WRITING );
	f << "prev text next word";
	f.close();
	f.open( "out/unflushed-unread.txt", HFile::OPEN::READING | HFile::OPEN::WRITING );
	f.set_buffered_io( true );
	f << "some data";
	HString s;
	f >> s;
	ENSURE_EQUALS( "read in RW mode failed", s, "next" );
	f.close();
	f.open( "out/unflushed-unread.txt", HFile::OPEN::READING | HFile::OPEN::WRITING );
	f << "SOME DATA";
	f.unread( " byte", 5 );
	f >> s;
	ENSURE_EQUALS( "read of unread after write in RW mode failed", s, "byte" );
	f >> s;
	ENSURE_EQUALS( "read after unread in RW mode failed", s, "next" );
	f.close();
	f.open( "out/unflushed-unread.txt", HFile::OPEN::READING );
	getline( f, s );
	ENSURE_EQUALS( "auto-flush after unread in RW mode failed", s, "SOME DATA next word" );
TUT_TEARDOWN()

TUT_UNIT_TEST_S( "input skipws fail bit" )
	static char src[] = "1 2 3";
	HStringStream& ss( string_stream( buffered ? true : false ) );
	ss.str( src );
	int i[3] = { 0, 0, 0 };
	_ss >> noskipws;
	for ( int& ii : i ) {
		try {
			_ss >> ii;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int value read fail", i[0], 1 );
	ENSURE_EQUALS( "spurious int value read", i[1], 0 );
	ENSURE_EQUALS( "spurious int value read", i[2], 0 );
	ss.str( src );
	i[0] = 0;
	_ss >> skipws;
	for ( int& ii : i ) {
		try {
			_ss >> ii;
		} catch ( ... ) {
		}
	}
	ENSURE_EQUALS( "int value read fail", i[0], 1 );
	ENSURE_EQUALS( "int value read fail", i[1], 2 );
	ENSURE_EQUALS( "int value read fail", i[2], 3 );
TUT_TEARDOWN_S()

}


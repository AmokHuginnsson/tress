/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cstdio>

#include "config.hxx"
#include <yaal/hcore/macro.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/tools/hterminal.hxx>
#include <yaal/hcore/hcharacterencodingconverter.hxx>

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools;

namespace yaal {

namespace {

yaal::hcore::HString const& output_encoding( void ) {
	static HString encoding;
	static bool iniialized( false );
	char const DEF_ENC[] = "UTF-8";
	if ( ! iniialized ) {
		iniialized = true;
		char const* ctype( ::getenv( "LC_CTYPE" ) );
		if ( ! ctype ) {
			ctype = ::getenv( "LC_ALL" );
		}
		if ( ! ctype ) {
			ctype = DEF_ENC;
		}
		encoding = ctype;
		int long pos( encoding.find( '.'_ycp ) );
		if ( pos != yaal::hcore::HString::npos ) {
			encoding = encoding.substr( pos + 1 );
		}
		try {
			HCharacterEncodingConverter( "utf-8", encoding );
		} catch ( ... ) {
			encoding = DEF_ENC;
		}
	}
	return encoding;
}

HString const& _outputEncoding_( output_encoding() );

}

template<>
std::string lexical_cast( yaal::hcore::HString const& str_ ) {
	yaal::hcore::HCharacterEncodingConversionResult out;
	yaal::hcore::HCharacterEncodingConverter encConv( "utf-8", _outputEncoding_ );
	yaal::hcore::HUTF8String utf8( str_ );
	encConv.convert( utf8.c_str(), utf8.byte_count(), out );
	return ( out.size() > 0 ? out.c_str() : "" );
}

}

#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tress::tut_helpers;

namespace std {

std::ostream& operator << ( std::ostream& out, HComplex const& complex_ ) {
	M_PROLOG
	double long re, im;
	re = complex_.re();
	im = complex_.im();
	if ( im >= 0 )
		out << re << "+i" << im;
	else
		out << re << "-i" << - im;
	return out;
	M_EPILOG
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HString const& s ) {
	out << lexical_cast<std::string>( s );
	return out;
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HUTF8String const& s ) {
	out.write( s.raw(), s.byte_count() );
	return out;
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HNumber const& n ) {
	out << n.to_string();
	return out;
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HTime const& t ) {
	out << lexical_cast<std::string>( t.string() );
	return out;
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::time::duration_t const& d ) {
	out << duration_to_string( d, time::UNIT::NANOSECOND );
	return out;
}

HStreamInterface& operator << ( HStreamInterface& os, std::string const& s ) {
	os << s.c_str();
	return os;
}

}

namespace yaal {

namespace tools {

template<>
bool is_a_tty( std::ostream const& stream_ ) {
	bool isTty( false );
	if ( ( &stream_ == &std::cout ) || ( &stream_ == &std::clog ) )
		isTty = yaal::tools::is_a_tty( yaal::hcore::cout ) ? true : false;
	else if ( &stream_ == &std::cerr )
		isTty = yaal::tools::is_a_tty( yaal::hcore::cerr ) ? true : false;
	return isTty;
}

template<>
bool is_a_tty( std::istream const& stream_ ) {
	bool isTty( false );
	if ( &stream_ == &std::cin )
		isTty = yaal::tools::is_a_tty( yaal::hcore::cin ) ? true : false;
	return isTty;
}

}

}

namespace tress {

namespace tut_helpers {

double long PI = 3.141592653589793L;
double long E =  2.718281828459045L;

int const _testData_[3][ 100 ] = { {
	  2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
	 31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
	 73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541
}, {
	  -2,   -3,   -5,   -7,  -11,  -13,  -17,  -19,  -23,  -29,
	 -31,  -37,  -41,  -43,  -47,  -53,  -59,  -61,  -67,  -71,
	 -73,  -79, - -83, -89,  -97, -101, -103, -107, -109, -113,
	-127, -131, -137, -139, -149, -151, -157, -163, -167, -173,
	-179, -181, -191, -193, -197, -199, -211, -223, -227, -229,
	-233, -239, -241, -251, -257, -263, -269, -271, -277, -281,
	-283, -293, -307, -311, -313, -317, -331, -337, -347, -349,
	-353, -359, -367, -373, -379, -383, -389, -397, -401, -409,
	-419, -421, -431, -433, -439, -443, -449, -457, -461, -463,
	-467, -479, -487, -491, -499, -503, -509, -521, -523, -541
}, {
	  2,   2,   2,   2,   2,   3,   3,   3,   3,   5,
		5,   5,   7,   7,  11,  13,  17,  19,  23,  29,
	 31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
	 73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 191, 191, 191, 191, 191, 191, 191,
	191, 191, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 331, 331, 337,
	337, 337, 337, 337, 347, 347, 347, 347, 347, 347
}
};


HEventDetector::HEventDetector( void )
	: _mutex()
	, _condition( _mutex )
	, _detected{ false } {
	return;
}

void HEventDetector::signal( void ) {
	HLock l( _mutex );
	_detected = true;
	_condition.broadcast();
	return;
}

bool HEventDetector::wait( yaal::hcore::time::duration_t duration_ ) {
	HLock l( _mutex );
	HClock c( HClock::TYPE::REAL );
	while ( ! _detected ) {
		time::duration_t waited( c.get_time_elapsed( time::UNIT::NANOSECOND ) );
		if ( waited > duration_ ) {
			break;
		}
		_condition.wait_for( duration_ - waited );
	}
	return ( _detected );
}

void HEventDetector::reset( void ) {
	HLock l( _mutex );
	_detected = false;
	return;
}

void HSTDGlobalScopeExceptionHandlingPolicy::handle_exception( void ) {
	try {
		throw;
	} catch ( HException const& e ) {
		std::cerr << "Exception `" << e.what() << "' thrown from outside of main() scope." << std::endl;
	} catch ( std::exception const& e ) {
		std::cerr << "Exception `" << e.what() << "' thrown from outside of main() scope." << std::endl;
	} catch ( ... ) {
		std::cerr << "Exception of unknown type thrown from outside of main() scope." << std::endl;
	}
	exit( 1 );
}

bool file_binary_compare( yaal::hcore::HString const& path1_, yaal::hcore::HString const& path2_ ) {
	HFile f1( path1_, HFile::OPEN::READING );
	HFile f2( path2_, HFile::OPEN::READING );
	static int const BUF_SIZE( 1024 );
	char buf1[BUF_SIZE];
	char buf2[BUF_SIZE];
	bool different( false );
	int long nRead1( 0 );
	do {
		nRead1 = f1.read( buf1, BUF_SIZE );
		int long nRead2( f2.read( buf2, BUF_SIZE ) );
		different = ( nRead1 != nRead2 ) || ( ::memcmp( buf1, buf2, static_cast<size_t>( nRead1 ) ) != 0 );
	} while ( ! different && ( nRead1 == BUF_SIZE ) );
	return ( ! different );
}

int long get_speed( time::UNIT u ) {
	static int long const LOOPS = 320000L;
	volatile double long x = PI;
	HClock c;
	for ( int i = 0; i < LOOPS; ++ i )
		x *= PI;
	return ( static_cast<int long>( c.get_time_elapsed( u ) ) );
}

}

}


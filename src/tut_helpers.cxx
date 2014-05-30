/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.cxx - this file is integral part of `tress' project.

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
#include <cstdlib>
#include <iostream>
#include <cstdio>

#include <yaal/hcore/macro.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/hconsole/hterminal.hxx>

#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;
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
	return ( out );
	M_EPILOG
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HString const& s ) {
	out << s.raw();
	return ( out );
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HNumber const& n ) {
	out << n.to_string();
	return ( out );
}

std::ostream& operator << ( std::ostream& out, yaal::hcore::HTime const& t ) {
	out << t.string().raw();
	return ( out );
}

HStreamInterface& operator << ( HStreamInterface& os, std::string const& s ) {
	os << s.c_str();
	return ( os );
}

yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& os, stream_mod_t const& mod ) {
	if ( mod == static_cast<stream_mod_t const&>( std::endl ) )
		os << hcore::endl;
	else if ( mod == static_cast<stream_mod_t const&>( std::flush ) )
		os << hcore::flush;
	else {
		M_ASSERT( !"unsupported stream modifier"[0] );
	}
	return ( os );
}

}

namespace yaal {

namespace hconsole {

template<>
bool is_a_tty( std::ostream const& stream_ ) {
	bool isTty( false );
	if ( ( &stream_ == &std::cout ) || ( &stream_ == &std::clog ) )
		isTty = yaal::hconsole::is_a_tty( yaal::hcore::cout ) ? true : false;
	else if ( &stream_ == &std::cerr )
		isTty = yaal::hconsole::is_a_tty( yaal::hcore::cerr ) ? true : false;
	return ( isTty );
}

template<>
bool is_a_tty( std::istream const& stream_ ) {
	bool isTty( false );
	if ( &stream_ == &std::cin )
		isTty = yaal::hconsole::is_a_tty( yaal::hcore::cin ) ? true : false;
	return ( isTty );
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

bool file_compare( yaal::hcore::HString const& path1_, yaal::hcore::HString const& path2_ ) {
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
	return ( different );
}

int long get_speed( HClock::UNIT::unit_t u ) {
	static int long const LOOPS = 320000L;
	volatile double long x = PI;
	HClock c;
	for ( int i = 0; i < LOOPS; ++ i )
		x *= PI;
	return ( static_cast<int long>( c.get_time_elapsed( u ) ) );
}

}

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_helpers.cxx - this file is integral part of `tress' project.

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

#include <cstring>
#include <cstdlib>
#include <iostream>

#include <yaal/hcore/macro.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

#include "setup.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
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

HStreamInterface& operator << ( HStreamInterface& os, std::string const& s ) {
	os << s.c_str();
	return ( os );
}

yaal::hcore::HStreamInterface& operator << ( yaal::hcore::HStreamInterface& os, stream_mod_t const& mod ) {
	if ( mod == static_cast<stream_mod_t const&>( std::endl ) )
		os << hcore::endl;
	else if ( mod == static_cast<stream_mod_t const&>( std::flush ) )
		os << hcore::flush;
	else
		M_ASSERT( !"unsupported stream modifier" );
	return ( os );
}

}

namespace tress {

namespace tut_helpers {

double long PI = 3.141592653589793L;
double long E =  2.718281828459045L;

int const _testData_[2][ 100 ] = { {
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
		different = ( nRead1 != nRead2 ) || ( memcmp( buf1, buf2, nRead1 ) != 0 );
	} while ( ! different && ( nRead1 == BUF_SIZE ) );
	return ( different );
}

int long get_speed( HClock::UNIT::unit_t u ) {
	static int long const LOOPS = 320000L;
	double long x = PI;
	HClock c;
	for ( int i = 0; i < LOOPS; ++ i )
		x *= PI;
	return ( static_cast<int long>( c.get_time_elapsed( u ) ) );
}

}

}


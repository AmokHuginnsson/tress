/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_streamtools.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#include <yaal/tools/streamtools.hxx>
#include <yaal/hcore/hlog.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_streamtools );
TUT_TEST_GROUP( tut_yaal_tools_streamtools, "yaal::tools::streamtools" );

TUT_UNIT_TEST( "binary manipulator for stream" )
	HStringStream ss;
	u64_t pattern8( 89 );
	u64_t pattern16( ( pattern8 << 8 ) | pattern8 );
	u64_t pattern32( ( pattern16 << 16 ) | pattern16 );
	u64_t pattern64( ( pattern32 << 32 ) | pattern32 );
	ENSURE_EQUALS( "char failed", ( ss << bin << static_cast<char>( pattern8 ) << flush, ss.consume() ), "01011001" );
	ENSURE_EQUALS( "char unsigned failed", ( ss << bin << static_cast<char unsigned>( pattern8 ), ss.consume() ), "01011001" );
	ENSURE_EQUALS( "short int failed", ( ss << bin << static_cast<short int>( pattern16 ), ss.consume() ), "0101100101011001" );
	ENSURE_EQUALS( "short int unsigned failed", ( ss << bin << static_cast<short int unsigned>( pattern16 ), ss.consume() ), "0101100101011001" );
	ENSURE_EQUALS( "int failed", ( ss << bin << static_cast<int>( pattern32 ), ss.consume() ), "01011001010110010101100101011001" );
	ENSURE_EQUALS( "int unsigned failed", ( ss << bin << static_cast<int unsigned>( pattern32 ), ss.consume() ), "01011001010110010101100101011001" );
#if SIZEOF_INT_LONG == 8
	ENSURE_EQUALS( "int long failed", ( ss << bin << static_cast<int long>( pattern64 ), ss.consume() ), "0101100101011001010110010101100101011001010110010101100101011001" );
	ENSURE_EQUALS( "int long unsigned failed", ( ss << bin << static_cast<int long unsigned>( pattern64 ), ss.consume() ), "0101100101011001010110010101100101011001010110010101100101011001" );
#else
	ENSURE_EQUALS( "int long failed", ( ss << bin << static_cast<int long>( pattern32 ), ss.consume() ), "01011001010110010101100101011001" );
	ENSURE_EQUALS( "int long unsigned failed", ( ss << bin << static_cast<int long unsigned>( pattern32 ), ss.consume() ), "01011001010110010101100101011001" );
#endif
	ENSURE_EQUALS( "int long long failed", ( ss << bin << static_cast<int long long>( pattern64 ), ss.consume() ), "0101100101011001010110010101100101011001010110010101100101011001" );
	ENSURE_EQUALS( "int long long unsigned failed", ( ss << bin << static_cast<int long long unsigned>( pattern64 ), ss.consume() ), "0101100101011001010110010101100101011001010110010101100101011001" );
#if SIZEOF_FLOAT == 4
	ENSURE_EQUALS( "float failed", ( ss << bin << bit_cast<float>( static_cast<u32_t>( pattern32 ) ), ss.consume() ), "01011001010110010101100101011001" );
#endif
#if SIZEOF_DOUBLE == 8
	ENSURE_EQUALS( "double failed", ( ss << bin << bit_cast<double>( pattern64 ), ss.consume() ), "0101100101011001010110010101100101011001010110010101100101011001" );
#endif
#if SIZEOF_DOUBLE_LONG == 16
	double long dl( 0 );
	::memcpy( &dl, &pattern64, 8 );
	::memcpy( static_cast<char*>( static_cast<void*>( &dl ) ) + 8, &pattern64, 8 );
	ss << bin << dl;
	ENSURE_EQUALS( "double long failed", ss.consume(), "01011001010110010101100101011001010110010101100101011001010110010101100101011001" );
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "tee" )
	HStringStream ss1;
	HStringStream ss2;
	tee( ss1, ss2 ) << "test" << 7;
	ENSURE_EQUALS( "tee failed(1)", ss1.str(), "test7" );
	ENSURE_EQUALS( "tee failed(2)", ss2.str(), "test7" );
	HStringStream::ptr_t ss3( make_pointer<HStringStream>() );
	HStringStream::ptr_t ss4( make_pointer<HStringStream>() );
	tee( ss3, ss4 ) << "test" << 7;
	ENSURE_EQUALS( "tee failed(3)", pointer_static_cast<HStringStream>( ss3 )->str(), "test7" );
	ENSURE_EQUALS( "tee failed(4)", pointer_static_cast<HStringStream>( ss4 )->str(), "test7" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_stream_id" )
	ENSURE_EQUALS( "bad is on stdin", get_stream_id( &yaal::hcore::cin ), "*standard input*" );
	ENSURE_EQUALS( "bad is on stdout", get_stream_id( &yaal::hcore::cout ), "*standard output*" );
	ENSURE_EQUALS( "bad is on stderr", get_stream_id( &yaal::hcore::cerr ), "*standard error*" );
	ENSURE_EQUALS( "bad is on stdlog", get_stream_id( &yaal::hcore::clog ), "*standard log*" );
	ENSURE_EQUALS( "bad is on log", get_stream_id( &yaal::hcore::log ), "*log*" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "ensure" )
	HFile f( "./data/karatsuba.bc", HFile::OPEN::READING );
tools::ensure( f );
	f.close();
	ENSURE_THROW( "ensure on closed succeeded", tools::ensure( f ), HException );
TUT_TEARDOWN()

}


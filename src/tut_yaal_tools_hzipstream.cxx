/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hzipstream.cxx - this file is integral part of `tress' project.

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

#include <cstdio>
#include <TUT/tut.hpp>

#include <yaal/tools/hzipstream.hxx>
#include <yaal/tools/tools.hxx>
#include <yaal/tools/hmemory.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hzipstream );
TUT_TEST_GROUP( tut_yaal_tools_hzipstream, "yaal::tools::HZipStream" );

namespace {

bool test_zipstream( int long zipBufSize_, int long clientBufSize_ ) {
	HScopedValueReplacement<int long> t( _zBufferSize_, zipBufSize_ );
	static char const* const INPUT( "./data/karatsuba.bc" );
	static char const* const OUTPUT_ZIP( "./out/karatsuba.bc.z" );
	static char const* const OUTPUT_RAW( "./out/karatsuba.bc" );
	int long nRead( 0 );
	HChunk buf( clientBufSize_ ); {
		HFile	inRaw( INPUT, HFile::OPEN::READING );
		HFile outZip( OUTPUT_ZIP, HFile::OPEN::WRITING );
		HZipStream zOut( outZip, HZipStream::MODE::DEFLATE );
		while ( ( nRead = inRaw.read( buf.raw(), buf.get_size() ) ) > 0 )
			zOut.write( buf.raw(), nRead );
	} {
		HFile	inZip( OUTPUT_ZIP, HFile::OPEN::READING );
		HFile outRaw( OUTPUT_RAW, HFile::OPEN::WRITING );
		HZipStream zIn( inZip, HZipStream::MODE::INFLATE );
		while ( ( nRead = zIn.read( buf.raw(), buf.get_size() ) ) > 0 )
			outRaw.write( buf.raw(), nRead );
	}
	return ( file_compare( INPUT, OUTPUT_RAW ) );
}

void zpipe_compress( HString const& src_, HString const& dst_ ) {
	M_PROLOG
	HChunk buf( 128 );
	HFile in;
	HFile out;
	if ( src_ == "-" )
		in.open( stdin, HFile::OWNERSHIP::EXTERNAL );
	else
		in.open( src_, HFile::OPEN::READING );
	if ( dst_ == "-" )
		out.open( stdout, HFile::OWNERSHIP::EXTERNAL );
	else
		out.open( dst_, HFile::OPEN::WRITING );
	HZipStream z( out, HZipStream::MODE::DEFLATE );
	int long nRead( 0 );
	while ( ( nRead = in.read( buf.raw(), buf.get_size() ) ) > 0 )
		z.write( buf.raw(), nRead );
	return;
	M_EPILOG
}

void zpipe_decompress( HString const& src_, HString const& dst_ ) {
	M_PROLOG
	HChunk buf( 128 );
	HFile in;
	HFile out;
	if ( src_ == "-" )
		in.open( stdin, HFile::OWNERSHIP::EXTERNAL );
	else
		in.open( src_, HFile::OPEN::READING );
	if ( dst_ == "-" )
		out.open( stdout, HFile::OWNERSHIP::EXTERNAL );
	else
		out.open( dst_, HFile::OPEN::WRITING );
	HZipStream z( in, HZipStream::MODE::INFLATE );
	int long nRead( 0 );
	while ( ( nRead = z.read( buf.raw(), buf.get_size() ) ) > 0 )
		out.write( buf.raw(), nRead );
	return;
	M_EPILOG
}

}

TUT_UNIT_TEST( 1, "default zipstream buffer, client buffer 128 octets" )
	if ( setup._argc > 2 )
		zpipe_compress( setup._argv[ 1 ], setup._argv[ 2 ] );
	else
		ENSURE_NOT( "(de)compression failed", test_zipstream( _zBufferSize_, 128 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "default zipstream buffer, client buffer same size" )
	if ( setup._argc > 2 )
		zpipe_decompress( setup._argv[ 1 ], setup._argv[ 2 ] );
	else
		ENSURE_NOT( "(de)compression failed", test_zipstream( _zBufferSize_, _zBufferSize_ ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "zpipe: compress file, or auto 192, 128" )
	ENSURE_NOT( "(de)compression failed", test_zipstream( 192, 128 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "zpipe: decompress file, or auto 128, 192" )
	ENSURE_NOT( "(de)compression failed", test_zipstream( 128, 192 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "auto 128, 128" )
	ENSURE_NOT( "(de)compression failed", test_zipstream( 128, 128 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "compress big buffer all at once" )
	static int const SIZE( 5 * 1024 * 16 );
	HChunk c( SIZE );
	int* p( c.get<int>() );
	for ( int i( 0 ); i < ( SIZE / static_cast<int>( sizeof ( int ) ) ); ++ i )
		p[i] = i;
	HChunk out;
	HMemoryProvider mp( out );
	HMemory m( mp );
	HZipStream z( m, HZipStream::MODE::DEFLATE );
	int long compressedSize( z.write( p, SIZE ) );
	clog << "buffer of size " << SIZE << " compressed to size " << compressedSize << endl;
TUT_TEARDOWN()

}


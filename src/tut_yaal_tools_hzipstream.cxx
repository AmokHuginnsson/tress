/* Read tress/LICENSE.md file for copyright and licensing information. */

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
	return ( file_binary_compare( INPUT, OUTPUT_RAW ) );
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

TUT_UNIT_TEST( "default zipstream buffer, client buffer 128 octets" )
	if ( setup._argc > 2 ) {
		zpipe_compress( setup._argv[ 1 ], setup._argv[ 2 ] );
	} else {
		ENSURE( "(de)compression failed", test_zipstream( _zBufferSize_, 128 ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "default zipstream buffer, client buffer same size" )
	if ( setup._argc > 2 ) {
		zpipe_decompress( setup._argv[ 1 ], setup._argv[ 2 ] );
	} else {
		ENSURE( "(de)compression failed", test_zipstream( _zBufferSize_, _zBufferSize_ ) );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "zpipe: compress file, or auto 192, 128" )
	ENSURE( "(de)compression failed", test_zipstream( 192, 128 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "zpipe: decompress file, or auto 128, 192" )
	ENSURE( "(de)compression failed", test_zipstream( 128, 192 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "auto 128, 128" )
	ENSURE( "(de)compression failed", test_zipstream( 128, 128 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "compress big buffer all at once" )
	static int const SIZE( 5 * 1024 * 16 );
	HChunk c( SIZE );
	int* p( c.get<int>() );
	for ( int i( 0 ); i < ( SIZE / static_cast<int>( sizeof ( int ) ) ); ++ i )
		p[i] = i;
	HChunk out;
	HMemory m( make_resource<HMemoryProvider>( out, 0 ) );
	HZipStream z( m, HZipStream::MODE::DEFLATE );
	int long compressedSize( z.write( p, SIZE ) );
	clog << "buffer of size " << SIZE << " compressed to size " << compressedSize << endl;
TUT_TEARDOWN()

}


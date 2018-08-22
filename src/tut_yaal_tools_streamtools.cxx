/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstring>

#include <TUT/tut.hpp>

#include <yaal/tools/streamtools.hxx>
#include <yaal/hcore/hlog.hxx>
#include <yaal/hcore/hnumber.hxx>
#include <yaal/hcore/hcomplex.hxx>
#include <yaal/hcore/htime.hxx>
#include <yaal/tools/hmemory.hxx>
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

TUT_UNIT_TEST( "stream + HNumber" )
	HStringStream ss;
	HNumber exp( "3.1415926535897932"_yn );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	HNumber n;
	ss >> n;
	ENSURE_EQUALS( "HNumber text streams failed", n, "3.141593"_yn );
	HChunk c;
	HMemoryProvider mp( c, 100 );
	HMemory m( mp );
	m << binary << exp;
	m >> n;
	ENSURE_EQUALS( "HNumber binary streams failed", n, exp );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HTime" )
	HStringStream ss;
	HTime exp( 1978, 5, 24, 23, 30, 17 );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	HTime t( HTime::TZ::LOCAL );
	ss >> t;
	t.set_time( 0, 0, 0 );
	ENSURE_EQUALS( "HTime text streams failed", t, HTime( exp ).set_time( 0, 0, 0 ) );
	HChunk buf;
	HMemoryProvider mp( buf, 100 );
	HMemory m( mp );
	m << binary << exp;
	t.set_now();
	m >> t;
	ENSURE_EQUALS( "HTime binary streams failed", t, exp );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HComplex" )
	HStringStream ss;
	HComplex exp( -3.14159265, 2.718281828 );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	HComplex c;
	ss >> c;
	ENSURE_EQUALS( "HComplex text streams failed", c, exp );
	HChunk buf;
	HMemoryProvider mp( buf, 100 );
	HMemory m( mp );
	m << binary << exp;
	c.set( 0, 0 );
	m >> c;
	ENSURE_EQUALS( "HComplex binary streams failed", c, exp );
	ss.reset();
	ss << "(1+2i)";
	ss >> c;
	ENSURE_EQUALS( "HComplex text minimal streams failed", c, HComplex( 1, 2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HPair" )
	HStringStream ss;
	typedef HPair<int, int> pair_t;
	pair_t exp( 7, -13 );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	pair_t p;
	ss >> p;
	ENSURE_EQUALS( "HComplex text streams failed", p, exp );
	HChunk buf;
	HMemoryProvider mp( buf, 100 );
	HMemory m( mp );
	m << binary << exp;
	p = make_pair( 0, 0 );
	m >> p;
	ENSURE_EQUALS( "HComplex binary streams failed", p, exp );
	ss.reset();
	ss << "pair<1,2>";
	ss >> p;
	ENSURE_EQUALS( "HComplex text minimal streams failed", p, make_pair( 1, 2 ) );
TUT_TEARDOWN()

}


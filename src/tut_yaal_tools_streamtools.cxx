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
#	ifdef __aarch64__
	char const expected[] = "01011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101011001";
#	else
	char const expected[] = "01011001010110011011001010110010101100101011001010110010101100101011001010110010000000000000000000000000000000000000000000000000";
#	endif
	ENSURE_EQUALS( "double long failed", ss.consume(), expected );
#endif
TUT_TEARDOWN()

TUT_UNIT_TEST( "cat" )
	HString s1( "żółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółćżółć" );
	HString s2( "ŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆŻÓŁĆ" );
	HStringStream ss1( s1 );
	HStringStream ss2( s2 );
	HString s;
	cat( &ss1, &ss2 ) >> s;
	ENSURE_EQUALS( "cat failed", s, s1 + s2 );
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
	HMemory m( make_resource<HMemoryProvider>( c, 100 ) );
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
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
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
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
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
	ENSURE_EQUALS( "HArray text streams failed", p, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	p = make_pair( 0, 0 );
	m >> p;
	ENSURE_EQUALS( "HArray binary streams failed", p, exp );
	ss.reset();
	ss << "pair<1,2>";
	ss >> p;
	ENSURE_EQUALS( "HArray text minimal streams failed", p, make_pair( 1, 2 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HArray" )
	HStringStream ss;
	int_array_t exp( { 1, 2, 3, 7, 19 } );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	int_array_t a;
	ss >> a;
	ENSURE_EQUALS( "HArray text streams failed", a, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	a.clear();
	m >> a;
	ENSURE_EQUALS( "HArray binary streams failed", a, exp );
	ss.reset();
	ss << "array(13)";
	ss >> a;
	ENSURE_EQUALS( "HArray text minimal streams failed", a, int_array_t( { 13 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HStaticArray" )
	typedef HStaticArray<int, 5> int_static_array_t;
	HStringStream ss;
	int_static_array_t exp( { 1, 2, 3, 7, 19 } );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	int_static_array_t a;
	ss >> a;
	ENSURE_EQUALS( "HStaticArray text streams failed", a, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	fill( a.begin(), a.end(), 0 );
	m >> a;
	ENSURE_EQUALS( "HStaticArray binary streams failed", a, exp );
	ss.reset();
	ss << "staticarray(13 17 13 17 13)";
	ss >> a;
	ENSURE_EQUALS( "HStaticArray text minimal streams failed", a, int_static_array_t( { 13, 17, 13, 17, 13 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HDeque" )
	HStringStream ss;
	int_deque_t exp( { 1, 2, 3, 7, 19 } );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	int_deque_t d;
	ss >> d;
	ENSURE_EQUALS( "HDeque text streams failed", d, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	d.clear();
	m >> d;
	ENSURE_EQUALS( "HDeque binary streams failed", d, exp );
	ss.reset();
	ss << "deque(13)";
	ss >> d;
	ENSURE_EQUALS( "HDeque text minimal streams failed", d, int_deque_t( { 13 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HList" )
	HStringStream ss;
	int_list_t exp( { 1, 2, 3, 7, 19 } );
	ss << "ala " << exp << " kot";
	HString s;
	ss >> s;
	int_list_t l;
	ss >> l;
	ENSURE_EQUALS( "HList text streams failed", l, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	l.clear();
	m >> l;
	ENSURE_EQUALS( "HList binary streams failed", l, exp );
	ss.reset();
	ss << "list(13)";
	ss >> l;
	ENSURE_EQUALS( "HList text minimal streams failed", l, int_list_t( { 13 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HSet" )
	HStringStream ss;
	int_set_t exp( { 1, 2, 3, 7, 19 } );
	ss << "ala " << exp << " kot";
	HString str;
	ss >> str;
	int_set_t s;
	ss >> s;
	ENSURE_EQUALS( "HSet text streams failed", s, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	s.clear();
	m >> s;
	ENSURE_EQUALS( "HSet binary streams failed", s, exp );
	ss.reset();
	ss << "set(13)";
	ss >> s;
	ENSURE_EQUALS( "HSet text minimal streams failed", s, int_set_t( { 13 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HHashSet" )
	HStringStream ss;
	int_array_t exp( { 1, 2, 3, 7, 19 } );
	int_hash_set_t data( exp.begin(), exp.end() );
	ss << "ala " << data << " kot";
	HString str;
	ss >> str;
	int_hash_set_t hs;
	ss >> hs;
	int_array_t sorted( hs.begin(), hs.end() );
	sort( sorted.begin(), sorted.end() );
	ENSURE_EQUALS( "HHashSet text streams failed", sorted, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << data;
	hs.clear();
	m >> hs;
	sorted.assign( hs.begin(), hs.end() );
	sort( sorted.begin(), sorted.end() );
	ENSURE_EQUALS( "HHashSet binary streams failed", sorted, exp );
	ss.reset();
	ss << "hash_set(13)";
	ss >> hs;
	ENSURE_EQUALS( "HHashSet text minimal streams failed", hs, int_hash_set_t( { 13 } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HMap" )
	typedef yaal::hcore::HMap<int, int> int_map_t;
	HStringStream ss;
	int_map_t exp( { { 1, 0 }, { 2, 1 }, { 3, 2 }, { 7, 3 }, { 19, 4 } } );
	ss << "ala " << exp << " kot";
	HString str;
	ss >> str;
	int_map_t s;
	ss >> s;
	ENSURE_EQUALS( "HMap text streams failed", s, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << exp;
	s.clear();
	m >> s;
	ENSURE_EQUALS( "HMap binary streams failed", s, exp );
	ss.reset();
	ss << "map(pair<13,7>)";
	ss >> s;
	ENSURE_EQUALS( "HMap text minimal streams failed", s, int_map_t( { { 13, 7 } } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HHashMap" )
	typedef yaal::hcore::HPair<int, int> int_pair_t;
	typedef yaal::hcore::HArray<int_pair_t> int_pair_array_t;
	typedef yaal::hcore::HHashMap<int, int> int_hash_map_t;
	HStringStream ss;
	int_pair_array_t exp( { { 1, 0 }, { 2, 1 }, { 3, 2 }, { 7, 3 }, { 19, 4 } } );
	int_hash_map_t data( exp.begin(), exp.end() );
	ss << "ala " << data << " kot";
	HString str;
	ss >> str;
	int_hash_map_t hm;
	ss >> hm;
	int_pair_array_t sorted( hm.begin(), hm.end() );
	sort( sorted.begin(), sorted.end() );
	ENSURE_EQUALS( "HHashMap text streams failed", sorted, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << data;
	hm.clear();
	m >> hm;
	sorted.assign( hm.begin(), hm.end() );
	sort( sorted.begin(), sorted.end() );
	ENSURE_EQUALS( "HHashMap binary streams failed", sorted, exp );
	ss.reset();
	ss << "hash_map(pair<13,7>))";
	ss >> hm;
	ENSURE_EQUALS( "HHashMap text minimal streams failed", hm, int_hash_map_t( { { 13, 7 } } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stream + HOrderedHashMap" )
	typedef yaal::hcore::HPair<int, int> int_pair_t;
	typedef yaal::hcore::HArray<int_pair_t> int_pair_array_t;
	typedef yaal::hcore::HOrderedHashMap<int, int> int_ordered_hash_map_t;
	HStringStream ss;
	int_pair_array_t exp( { { 1, 0 }, { 2, 1 }, { 3, 2 }, { 7, 3 }, { 19, 4 } } );
	int_ordered_hash_map_t data( exp.begin(), exp.end() );
	ss << "ala " << data << " kot";
	HString str;
	ss >> str;
	int_ordered_hash_map_t ohm;
	ss >> ohm;
	int_pair_array_t sorted( ohm.begin(), ohm.end() );
	sort( sorted.begin(), sorted.end() );
	ENSURE_EQUALS( "HOrderedHashMap text streams failed", sorted, exp );
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << data;
	ohm.clear();
	m >> ohm;
	sorted.assign( ohm.begin(), ohm.end() );
	sort( sorted.begin(), sorted.end() );
	ENSURE_EQUALS( "HOrderedHashMap binary streams failed", sorted, exp );
	ss.reset();
	ss << "ordered_hash_map(pair<13,7>))";
	ss >> ohm;
	ENSURE_EQUALS( "HOrderedHashMap text minimal streams failed", ohm, int_ordered_hash_map_t( { { 13, 7 } } ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "time::duruation_t write to stream in text mode" )
	time::duration_t d(
		time::duration( 7, time::UNIT::WEEK )
		+ time::duration( 2, time::UNIT::DAY )
		+ time::duration( 13, time::UNIT::HOUR )
		+ time::duration( 47, time::UNIT::MINUTE )
		+ time::duration( 51, time::UNIT::SECOND )
		+ time::duration( 389, time::UNIT::MILLISECOND )
		+ time::duration( 612, time::UNIT::MICROSECOND )
		+ time::duration( 707, time::UNIT::NANOSECOND )
	);
	HStringStream ss;
	ss << d;
	char const expected[] = "7 weeks 2 days";
	ENSURE_EQUALS( "duration text output conversion failed", ss.str(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "time::duruation_t write to stream in binary mode" )
	time::duration_t d(
		time::duration( 7, time::UNIT::WEEK )
		+ time::duration( 2, time::UNIT::DAY )
		+ time::duration( 13, time::UNIT::HOUR )
		+ time::duration( 47, time::UNIT::MINUTE )
		+ time::duration( 51, time::UNIT::SECOND )
		+ time::duration( 389, time::UNIT::MILLISECOND )
		+ time::duration( 612, time::UNIT::MICROSECOND )
		+ time::duration( 707, time::UNIT::NANOSECOND )
	);
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << d;
	time::duration_t::value_type expected(
		707
		+ 612 * 1000
		+ 389 * 1000000
		+ 51 * 1000000000LL
		+ 47 * 60 * 1000000000LL
		+ 13 * 60 * 60 * 1000000000LL
		+  2 * 24 * 60 * 60 * 1000000000LL
		+  7 * 7 * 24 * 60 * 60 * 1000000000LL
	);
	time::duration_t::value_type actual( 0 );
	m >> actual;
	ENSURE_EQUALS( "duration binary output conversion failed", actual, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "time::duruation_t read from stream in binary mode" )
	time::duration_t expected(
		time::duration( 7, time::UNIT::WEEK )
		+ time::duration( 2, time::UNIT::DAY )
		+ time::duration( 13, time::UNIT::HOUR )
		+ time::duration( 47, time::UNIT::MINUTE )
		+ time::duration( 51, time::UNIT::SECOND )
		+ time::duration( 389, time::UNIT::MILLISECOND )
		+ time::duration( 612, time::UNIT::MICROSECOND )
		+ time::duration( 707, time::UNIT::NANOSECOND )
	);
	time::duration_t::value_type data(
		707
		+ 612 * 1000
		+ 389 * 1000000
		+ 51 * 1000000000LL
		+ 47 * 60 * 1000000000LL
		+ 13 * 60 * 60 * 1000000000LL
		+  2 * 24 * 60 * 60 * 1000000000LL
		+  7 * 7 * 24 * 60 * 60 * 1000000000LL
	);
	HChunk buf;
	HMemory m( make_resource<HMemoryProvider>( buf, 100 ) );
	m << binary << data;
	time::duration_t actual( 0 );
	m >> actual;
	ENSURE_EQUALS( "duration binary input conversion failed", actual, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "time::duruation_t read from stream in text mode" )
	time::duration_t expected(
		time::duration( 7, time::UNIT::WEEK )
		+ time::duration( 2, time::UNIT::DAY )
		+ time::duration( 13, time::UNIT::HOUR )
		+ time::duration( 47, time::UNIT::MINUTE )
		+ time::duration( 51, time::UNIT::SECOND )
		+ time::duration( 389, time::UNIT::MILLISECOND )
		+ time::duration( 612, time::UNIT::MICROSECOND )
		+ time::duration( 707, time::UNIT::NANOSECOND )
	);
	char const data[] = "7 \t\t weeks \t \t 2 days 13 hours 47 \t \t\t \t minutes 51 seconds 389 milliseconds 612 microseconds 707 nanoseconds";
	char const tail[] = " \t 888 hoursq 333";
	HStringStream ss;
	ss << data << tail;
	time::duration_t d;
	ss >> d;
	HString s;
	getline( ss, s );
	ENSURE_EQUALS( "duration text input conversion failed", d, expected );
	ENSURE_EQUALS( "duration text input conversion consumed too much from stream", s, tail );
TUT_TEARDOWN()

TUT_UNIT_TEST( "use HDurationFormatter to write time::duruation_t to stream in text mode (auto scale)" )
	time::duration_t d(
		time::duration( 7, time::UNIT::WEEK )
		+ time::duration( 2, time::UNIT::DAY )
		+ time::duration( 13, time::UNIT::HOUR )
		+ time::duration( 47, time::UNIT::MINUTE )
		+ time::duration( 51, time::UNIT::SECOND )
		+ time::duration( 389, time::UNIT::MILLISECOND )
		+ time::duration( 612, time::UNIT::MICROSECOND )
		+ time::duration( 707, time::UNIT::NANOSECOND )
	);
	HStringStream ss;
	ss << d;
	char const expectedLong[] = "7 weeks 2 days";
	ENSURE_EQUALS( "duration text output conversion failed", ss.str(), expectedLong );
	ss.reset();
	ss << durationformat( time::UNIT_FORM::ABBREVIATED ) << d;
	char const expectedShort[] = "7w 2d";
	ENSURE_EQUALS( "duration text output conversion failed", ss.str(), expectedShort );
TUT_TEARDOWN()

TUT_UNIT_TEST( "use HDurationFormatter to write time::duruation_t to stream in text mode (forced scale)" )
	time::duration_t d(
		time::duration( 7, time::UNIT::WEEK )
		+ time::duration( 2, time::UNIT::DAY )
		+ time::duration( 13, time::UNIT::HOUR )
		+ time::duration( 47, time::UNIT::MINUTE )
		+ time::duration( 51, time::UNIT::SECOND )
		+ time::duration( 389, time::UNIT::MILLISECOND )
		+ time::duration( 612, time::UNIT::MICROSECOND )
		+ time::duration( 707, time::UNIT::NANOSECOND )
	);
	HStringStream ss;
	ss << durationformat( time::UNIT::NANOSECOND ) << d;
	char const expectedLong[] = "7 weeks 2 days 13 hours 47 minutes 51 seconds 389 milliseconds 612 microseconds 707 nanoseconds";
	ENSURE_EQUALS( "duration text output conversion failed", ss.str(), expectedLong );
	ss.reset();
	ss << durationformat( time::UNIT::NANOSECOND, time::UNIT_FORM::ABBREVIATED ) << d;
	char const expectedShort[] = "7w 2d 13h 47m 51s 389ms 612μs 707ns";
	ENSURE_EQUALS( "duration text output conversion failed", ss.str(), expectedShort );
TUT_TEARDOWN()

}


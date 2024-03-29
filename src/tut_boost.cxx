/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <math.h>

#include "config.hxx"

#ifdef HAVE_BOOST

#include <yaal/config.hxx>
#ifdef __HOST_OS_TYPE_SOLARIS__
#define BOOST_MATH_DISABLE_STD_FPCLASSIFY 1
#endif /* #ifdef __HOST_OS_TYPE_SOLARIS__ */
#define BOOST_ALL_DYN_LINK 1
#include <boost/config/user.hpp>
#include <boost/bind/bind.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lambda/lambda.hpp>

#include <TUT/tut.hpp>

#include <yaal/hcore/hcore.hxx>
#include <yaal/tools/hmonitor.hxx>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace boost;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::gregorian;
using namespace boost::placeholders;
using namespace tress::tut_helpers;

namespace tut {

struct tut_boost {
	typedef HInstanceTracker<tut_boost> item_t;
	virtual ~tut_boost( void ) {}
};

TUT_TEST_GROUP( tut_boost, "boost" );

typedef pair<int, int> pair_t;
typedef pair<string, string> person_t;

inline pair_t make_multi( void ) {
	static pair_t res[] = { make_pair( 1, 3 ), make_pair( 4, 1 ), make_pair( 2, 4 ), make_pair( 3, 2 ) };
	static int idx = 0;
	int i = idx;
	++ idx;
	idx %= static_cast<int>( ( sizeof ( res ) / sizeof ( pair_t ) ) );
	return ( res[ i ] );
}

TUT_UNIT_TEST( "binding" )
	clog << "sort by field using binding" << endl;
	clog << "{" << endl;
	typedef vector<pair_t> T;
	T v;
	generate_n( back_insert_iterator<T>( v ), 3, make_multi );
	copy( v.begin(), v.end(), ostream_iterator<pair_t>( clog ) );
	clog << endl;
	sort( v.begin(), v.end(), boost::bind( &pair_t::first, _1 ) < boost::bind( &pair_t::first, _2 ) );
	copy( v.begin(), v.end(), ostream_iterator<pair_t>( clog ) );
	clog << endl;
	clog << "}" << endl;
TUT_TEARDOWN()

namespace {

void dump_dir( path const& dir ) {
	clog << "dir: " << dir.string() << endl;
	directory_iterator end;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
	for ( directory_iterator it( dir ); it != end; ++ it ) {
		if ( is_directory( *it ) ) {
			dump_dir( *it );
		} else {
			clog << "file: " << (*it).path() << endl;
		}
	}
#pragma GCC diagnostic pop
	return;
}

}

#ifndef __HOST_OS_TYPE_SOLARIS__
TUT_UNIT_TEST( "filesystem" )
	yaal::hcore::HLock l( yaal::tools::HMonitor::get_instance().acquire( "locale" ) );
	setlocale( LC_ALL, "C" );
	try {
		dump_dir( path( "./build" ) );
	} catch ( ... ) {
		setlocale( LC_ALL, "" );
		throw;
	}
	setlocale( LC_ALL, "" );
TUT_TEARDOWN()
#endif /* #ifndef __HOST_OS_TYPE_SOLARIS__ */

TUT_UNIT_TEST( "date_time" )
	try {
		string birthday_s( "1978-05-24" );
		date birthday( from_simple_string( birthday_s ) );
		date now = day_clock::local_day();
		days alive = now - birthday;
		if ( alive == days( 1 ) ) {
			clog << "born yeasterday" << endl;
		} else if ( alive < days( 0 ) ) {
			clog << "not yet born" << endl;
		} else {
			clog << "you live " << alive.days() << " days" << endl;
		}
	} catch ( ... ) {
		cerr << "bad date" << endl;
	}
TUT_TEARDOWN()

struct test4helper {
	int _val;
	test4helper( int val ) : _val( val ) {}
	int get_val() const { return ( _val ); }
};

struct phony {
	template<typename tType>
	struct id {
		tType _val;
		id( tType val ) : _val( val ) {}
		tType operator()( void )
			{ return ( _val ); }
	};
};

template<typename tType,
	typename init0_t = phony, typename init1_t = phony,
	typename init2_t = phony, typename init3_t = phony,
	typename init4_t = phony, typename init5_t = phony>
struct generator {
	typedef phony* __;
	init0_t INIT0;
	init1_t INIT1;
	init2_t INIT2;
	init3_t INIT3;
	init4_t INIT4;
	init5_t INIT5;
	generator( init0_t init0 = init0_t(), init1_t init1 = init1_t(),
			init2_t init2 = init2_t(), init3_t init3 = init3_t(),
			init4_t init4 = init4_t(), init5_t init5 = init5_t() )
		: INIT0( init0 ), INIT1( init1 ), INIT2( init2 ), INIT3( init3 ),
		INIT4( init4 ), INIT5( init5 ) {}
	tType make( __, __, __, __, __, __ )
		{ return ( tType() ); }
	tType make( init0_t const*, __, __, __, __, __ )
		{ return ( tType( INIT0() ) ); }
	tType make( init0_t const*, init1_t const*, __, __, __, __ )
		{ return ( tType( INIT0(), INIT1() ) ); }
	tType make( init0_t const*, init1_t const*, init2_t const*, __, __, __ )
		{ return ( tType( INIT0(), INIT1(), INIT2() ) ); }
	tType make( init0_t const*, init1_t const*, init2_t const*,
			init3_t const*, __, __ )
		{ return ( tType( INIT0(), INIT1(), INIT2(), INIT3() ) ); }
	tType make( init0_t const*, init1_t const*, init2_t const*,
			init3_t const*, init4_t const*, __ )
		{ return ( tType( INIT0(), INIT1(), INIT2(), INIT3(), INIT4() ) ); }
	tType make( init0_t const*, init1_t const*, init2_t const*,
			init3_t const*, init4_t const*, init5_t const* )
		{ return ( tType( INIT0(), INIT1(), INIT2(), INIT3(), INIT4(),
					INIT5() ) ); }
	tType operator()() {
		return (
				make(
					static_cast<init0_t*>( nullptr ),
					static_cast<init1_t*>( nullptr ),
					static_cast<init2_t*>( nullptr ),
					static_cast<init3_t*>( nullptr ),
					static_cast<init4_t*>( nullptr ),
					static_cast<init5_t*>( nullptr ) ) );
	}
};

typedef pair<int const, test4helper> t4h_t;

inline ostream& operator << ( ostream& os, t4h_t const& p ) {
	os << "(" << p.first << "," << p.second.get_val() << ")";
	return os;
}

template<typename result_t, typename el1_t, typename el2_t>
result_t plus( el1_t const& el1, el2_t const& el2 )
	{ return ( el1 + el2 ); }

TUT_UNIT_TEST( "boost::bind, accumulate, plus" )
	clog << "accumulate all values returned by some\n"
		"method of class that represent values in map" << endl;
	clog << "{" << endl;
	typedef map<int,test4helper> T;
	T m;
	typedef generator<test4helper, inc> t4gh_t;
	generate_n( std::insert_iterator<T>( m, m.begin() ), 3,
			generator<t4h_t, inc, t4gh_t>( inc( 1 ), t4gh_t( inc( 7 ) ) ) );
	copy( m.begin(), m.end(), ostream_iterator<t4h_t>( clog ) );
	clog << endl;
	int sum = accumulate( m.begin(), m.end(), 0,
			boost::bind( std::plus<int>(), _1, boost::bind( &test4helper::get_val, boost::bind( &t4h_t::second, _2 ) ) ) );
	clog << sum << endl;
	clog << "}" << endl;
TUT_TEARDOWN()

inline pair_t foo( int first, int second ) {
	return ( make_pair( first, second ) );
}

TUT_UNIT_TEST( "boost::bind features" )
	ENSURE_EQUALS( "no args bind", boost::bind( &foo, _1, _2 )( 1, 2 ), make_pair( 1, 2 ) );
	ENSURE_EQUALS( "no args bind", boost::bind( &foo, _2, _1 )( 1, 2 ), make_pair( 2, 1 ) );
	ENSURE_EQUALS( "one arg bind _1, 4", boost::bind( &foo, _1, 4 )( 3 ), make_pair( 3, 4 ) );
	ENSURE_EQUALS( "one arg bind 4, _1", boost::bind( &foo, 4, _1 )( 3 ), make_pair( 4, 3 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "boost::bind filed assign" )
	person_t p( "Ala", "Nowak" );
	clog << p << endl;
	string const s( "Kowalska" );
	clog << ( boost::bind( &person_t::second, &p )() < s ) << endl;
	clog << ( boost::bind( &person_t::second, &p )() > s ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare with constant." )
	typedef list<item_t> list_t;
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), boost::bind( &item_t::id, _1 ) < 50 );
	copy( l.begin(), l.end(), ostream_iterator<item_t>( clog, " " ) );
	clog << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "lambda test." )
	using boost::lambda::_1;
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), _1 < 50 );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog, " " ) );
	clog << endl;
	l.clear();
	transform( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), _1 + 10 );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog, " " ) );
	clog << endl;
	l.clear();
	transform( a, a + yaal::size( a ), back_insert_iterator<list_t>( l ), _1 * 2 + 10 );
	copy( l.begin(), l.end(), ostream_iterator<int>( clog, " " ) );
	clog << endl;
	l.clear();
	for_each( a, a + yaal::size( a ), clog << ( _1 << 1 ) << " " );
	clog << endl;
TUT_TEARDOWN()

}

#endif /* #ifdef HAVE_BOOST */

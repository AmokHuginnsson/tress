/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_boost.cxx - this file is integral part of `tress' project.

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

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#define BOOST_ALL_DYN_LINK 1
#include <boost/config/user.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lambda/lambda.hpp>

#include <TUT/tut.hpp>

#include <yaal/hcore/hcore.hxx>
#include <yaal/tools/hmonitor.hxx>

M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace boost;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::gregorian;
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

TUT_UNIT_TEST( 1, "binding" )
	cout << "sort by field using binding" << endl;
	cout << "{" << endl;
	typedef vector<pair_t> T;
	T v;
	generate_n( back_insert_iterator<T>( v ), 3, make_multi );
	copy( v.begin(), v.end(), ostream_iterator<pair_t>( cout ) );
	cout << endl;
	sort( v.begin(), v.end(), boost::bind( &pair_t::first, _1 ) < boost::bind( &pair_t::first, _2 ) );
	copy( v.begin(), v.end(), ostream_iterator<pair_t>( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

namespace {

void dump_dir( path const& dir ) {
	cout << "dir: " << dir.string() << endl;
	directory_iterator end;
	for ( directory_iterator it( dir ); it != end; ++ it ) {
		if ( is_directory( *it ) )
			dump_dir( *it );
		else
			cout << "file: " << (*it).path() << endl;
	}
	return;
}

}

TUT_UNIT_TEST( 2, "filesystem" )
	yaal::tools::HMonitor& monitor( yaal::tools::HMonitor::get_instance() );
	yaal::hcore::HMutex& m( monitor.acquire( "locale" ) );
	yaal::hcore::HLock l( m );
	char const* locale( setlocale( LC_ALL, "C" ) );
	yaal::hcore::set_env( "LC_ALL", "C" );
	cout << ( locale ? locale : "(NULL)" ) << endl;
	dump_dir( path( "./build" ) );
	unsetenv( "LC_ALL" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "date_time" )
	try {
		string birthday_s( "1978-05-24" );
		date birthday( from_simple_string( birthday_s ) );
		date now = day_clock::local_day();
		days alive = now - birthday;
		if ( alive == days( 1 ) )
			cout << "born yeasterday" << endl;
		else if ( alive < days( 0 ) )
			cout << "not yet born" << endl;
		else
			cout << "you live " << alive.days() << " days" << endl;
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
					static_cast<init0_t*>( NULL ),
					static_cast<init1_t*>( NULL ),
					static_cast<init2_t*>( NULL ),
					static_cast<init3_t*>( NULL ),
					static_cast<init4_t*>( NULL ),
					static_cast<init5_t*>( NULL ) ) );
	}
};

typedef pair<int const, test4helper> t4h_t;

inline ostream& operator << ( ostream& os, t4h_t const& p ) {
	os << "(" << p.first << "," << p.second.get_val() << ")";
	return ( os );
}

template<typename result_t, typename el1_t, typename el2_t>
result_t plus( el1_t const& el1, el2_t const& el2 )
	{ return ( el1 + el2 ); }

TUT_UNIT_TEST( 4, "boost::bind, accumulate, plus" )
	cout << "accumulate all values returned by some\n"
		"method of class that represent values in map" << endl;
	cout << "{" << endl;
	typedef map<int,test4helper> T;
	T m;
	typedef generator<test4helper, inc> t4gh_t;
	generate_n( std::insert_iterator<T>( m, m.begin() ), 3,
			generator<t4h_t, inc, t4gh_t>( inc( 1 ), t4gh_t( inc( 7 ) ) ) );
	copy( m.begin(), m.end(), ostream_iterator<t4h_t>( cout ) );
	cout << endl;
	int sum = accumulate( m.begin(), m.end(), 0,
			boost::bind( std::plus<int>(), _1, boost::bind( &test4helper::get_val, boost::bind( &t4h_t::second, _2 ) ) ) );
	cout << sum << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

inline pair_t foo( int first, int second ) {
	return ( make_pair( first, second ) );
}

TUT_UNIT_TEST( 5, "boost::bind features" )
	ENSURE_EQUALS( "no args bind", boost::bind( &foo, _1, _2 )( 1, 2 ), make_pair( 1, 2 ) );
	ENSURE_EQUALS( "no args bind", boost::bind( &foo, _2, _1 )( 1, 2 ), make_pair( 2, 1 ) );
	ENSURE_EQUALS( "one arg bind _1, 4", boost::bind( &foo, _1, 4 )( 3 ), make_pair( 3, 4 ) );
	ENSURE_EQUALS( "one arg bind 4, _1", boost::bind( &foo, 4, _1 )( 3 ), make_pair( 4, 3 ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "boost::bind filed assign" )
	person_t p( "Ala", "Nowak" );
	cout << p << endl;
	string const s( "Kowalska" );
	cout << ( boost::bind( &person_t::second, &p )() < s ) << endl;
	cout << ( boost::bind( &person_t::second, &p )() > s ) << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "compare with constant." )
	typedef list<item_t> list_t;
	item_t a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ), boost::bind( &item_t::id, _1 ) < 50 );
	copy( l.begin(), l.end(), ostream_iterator<item_t>( cout, " " ) );
	cout << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "lambda test." )
	using boost::lambda::_1;
	typedef list<int> list_t;
	int a[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	list_t l;
	remove_copy_if( a, a + countof( a ), back_insert_iterator<list_t>( l ), _1 < 50 );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
	l.clear();
	transform( a, a + countof( a ), back_insert_iterator<list_t>( l ), _1 + 10 );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
	l.clear();
	transform( a, a + countof( a ), back_insert_iterator<list_t>( l ), _1 * 2 + 10 );
	copy( l.begin(), l.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;
	l.clear();
	for_each( a, a + countof( a ), cout << ( _1 << 1 ) << " " );
	cout << endl;
TUT_TEARDOWN()

}


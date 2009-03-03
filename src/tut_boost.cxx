/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_boost.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every yaal::copy
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

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::gregorian;
using namespace yaal;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

TUT_SIMPLE_MOCK( tut_boost );
TUT_TEST_GROUP_N( tut_boost, "boost" );

struct multi
	{
	int _first;
	int _second;
	};

multi make_multi( void )
	{
	static multi res[] = { { 1, 3 }, { 4, 1 }, { 2, 4 }, { 3, 2 } };
	static int idx = 0;
	int i = idx;
	++ idx;
	idx %= static_cast<int>( ( sizeof ( res ) / sizeof ( multi ) ) );
	return ( res[ i ] );
	}

ostream& operator << ( ostream& out, multi const& m )
	{
	out << "(" << m._first << "," << m._second << ")";
	return ( out );
	}

TUT_UNIT_TEST_N( 1, "/* binding */" )
	cout << "sort by field using binding" << endl;
	cout << "{" << endl;
	typedef vector<multi> T;
	T v;
	generate_n( std::back_insert_iterator<T>( v ), 3, make_multi );
	yaal::copy( v.begin(), v.end(), hcore::stream_iterator( cout ) );
	cout << endl;
	sort( v.begin(), v.end(), bind( &multi::_first, _1 ) < bind( &multi::_first, _2 ) );
	yaal::copy( v.begin(), v.end(), hcore::stream_iterator( cout ) );
	cout << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

void dump_dir( path const& dir )
	{
	cout << "dir: " << dir.string() << endl;
	directory_iterator end;
	for ( directory_iterator it( dir ); it != end; ++ it )
		{
		if ( is_directory( *it ) )
			dump_dir( *it );
		else
			cout << "file: " << (*it).path() << endl;
		}
	return;
	}

TUT_UNIT_TEST_N( 2, "/* filesystem */" )
	dump_dir( path( "." ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* date_time */" )
	try
		{
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
		}
	catch ( ... )
		{
		cerr << "bad date" << endl;
		}
TUT_TEARDOWN()

struct test4helper
	{
	int _val;
	test4helper( int val ) : _val( val ) {}
	int get_val() const { return ( _val ); }
	};

struct phony
	{
	template<typename tType>
	struct id
		{
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
struct generator
	{
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
	tType operator()()
		{
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

ostream& operator << ( ostream& os, t4h_t const& p )
	{
	os << "(" << p.first << "," << p.second.get_val() << ")";
	return ( os );
	}

template<typename result_t, typename el1_t, typename el2_t>
result_t plus( el1_t const& el1, el2_t const& el2 )
	{ return ( el1 + el2 ); }

TUT_UNIT_TEST_N( 4, "bind, accumulate, plus" )
	cout << "accumulate all values returned by some\n"
		"method of class that represent values in map" << endl;
	cout << "{" << endl;
	typedef map<int,test4helper> T;
	T m;
	typedef generator<test4helper, inc> t4gh_t;
	generate_n( std::insert_iterator<T>( m, m.begin() ), 3,
			generator<t4h_t, inc, t4gh_t>( inc( 1 ), t4gh_t( inc( 7 ) ) ) );
	yaal::copy( m.begin(), m.end(), hcore::stream_iterator( cout ) );
	cout << endl;
	int sum = accumulate( m.begin(), m.end(), 0,
			bind( std::plus<int>(), _1, bind( &test4helper::get_val, bind( &t4h_t::second, _2 ) ) ) );
	cout << sum << endl;
	cout << "}" << endl;
TUT_TEARDOWN()

}


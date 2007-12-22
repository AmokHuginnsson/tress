/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut.cxx - this file is integral part of `tress' project.

	i.  You may not make any changes in Copyright information.
	ii. You must attach Copyright information to any part of every copy
	    of this software.

Copyright:

 You are free to use this program as is, you can redistribute binary
 package freely but:
  1. You can not use any part of sources of this software.
  2. You can not redistribute any part of sources of this software.
  3. No reverse engineering is allowed.
  4. If you want redistribute binary package you can not demand any fees
     for this software.
     You can not even demand cost of the carrier (CD for example).
  5. You can not include it to any commercial enterprise (for example 
     as a free add-on to payed software or payed newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.h>

#include <yaal/yaal.h>
M_VCSID ( "$Id$" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_hcore_hlist
	{
	HString _cache;
	typedef HList<int> list_t;
	template<typename T>
	HString& to_string( T const& );
	void dump( list_t& );
	};

void tut_yaal_hcore_hlist::dump( list_t& l )
	{
	int s = l.size();
	cout << "l(" << s << "): [";
	for ( list_t::iterator it = l.begin(); it != l.end(); ++ it )
		cout << *it << ( s -- > 1 ? "," : "" );
	cout << "]" << endl;
	}

template<typename T>
HString& tut_yaal_hcore_hlist::to_string( T const& list )
	{
	_cache.clear();
	for ( typename T::iterator it = list.begin(); it != list.end(); ++ it )
		_cache += static_cast<char>( *it );
	return ( _cache );
	}

typedef test_group<tut_yaal_hcore_hlist>tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hlist_group ( "yaal::hcore::HList" );

/* Simple constructor. */
template<>
template<>
void module::test<1>( void )
	{
	list_t l_oList;
	ensure_equals ( "list not empty", l_oList.size(), 0 );
	}

/* Parametrized constructor. */
template<>
template<>
void module::test<2>( void )
	{
	list_t l_oList ( 3 );
	ensure_equals ( "list not empty", l_oList.size(), 3 );
	}

/* copy constructor */
template<>
template<>
void module::test<3>( void )
	{
	int l_iCtr = 0;
	list_t l_oList;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	list_t l_oAnother( l_oList );
	for ( list_t::iterator it = l_oAnother.begin();
			it != l_oAnother.end(); ++ it )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", *it, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* assignation operator (full to empty) */
template<>
template<>
void module::test<4>( void )
	{
	int l_iCtr = 0;
	list_t l_oList;
	list_t l_oAnother;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	l_oAnother = l_oList;
	for ( list_t::iterator it = l_oAnother.begin();
			it != l_oAnother.end(); ++ it )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", *it, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* assignation operator (empty to full) */
template<>
template<>
void module::test<5>( void )
	{
	list_t l_oList;
	list_t l_oAnother;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	l_oList = l_oAnother;
	ensure_equals ( "assign operation failed, wrong size", l_oList.size(), 0 );
	}

/* assignation operator (full to small) */
template<>
template<>
void module::test<6>( void )
	{
	int l_iCtr = 0;
	list_t l_oList;
	list_t l_oAnother;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	l_oAnother.add_tail() = 6;
	l_oAnother.add_tail() = 7;
	l_oAnother.add_tail() = 8;
	l_oAnother = l_oList;
	for ( list_t::iterator it = l_oAnother.begin();
			it != l_oAnother.end(); ++ it )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", *it, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* assignation operator (full to big) */
template<>
template<>
void module::test<7>( void )
	{
	int l_iCtr = 0;
	list_t l_oList;
	list_t l_oAnother;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	l_oAnother.add_tail() = 6;
	l_oAnother.add_tail() = 7;
	l_oAnother.add_tail() = 8;
	l_oAnother.add_tail() = 9;
	l_oAnother.add_tail() = 10;
	l_oAnother.add_tail() = 11;
	l_oAnother.add_tail() = 12;
	l_oAnother = l_oList;
	for ( list_t::iterator it = l_oAnother.begin();
			it != l_oAnother.end(); ++ it )
		{
		l_iCtr ++;
		ensure_equals ( "assign operation failed, wrong value", *it, l_iCtr );
		}
	ensure_equals ( "assign operation failed, wrong size", l_iCtr, 5 );
	}

/* .hook(), cyclic_iterator */
template<>
template<>
void module::test<8>( void )
	{
	list_t lst;
	lst.push_back( 'a' );
	lst.push_back( 'b' );
	lst.push_back( 'c' );
	ensure_equals( "push_back failed", to_string( lst ), "abc" );
	list_t::cyclic_iterator it = lst.hook();
	char const* const vec = "abcabc";
	for ( size_t i = 0; i < strlen( vec ); ++ i )
		{
		cout << i;
		ensure_equals( "cyclic_iterator failed", static_cast<char>( *it ), vec[ i ] );
		++ it;
		}
	char const* const vec2 = "acbacb";
	it = lst.hook();
	for ( size_t i = 0; i < strlen( vec ); ++ i )
		{
		cout << i;
		ensure_equals( "cyclic_iterator failed", static_cast<char>( *it ), vec2[ i ] );
		-- it;
		}
	cout << endl;
	it = lst.hook();
	ensure_equals( "hook is not head", *it, lst.head() );
	}

/* forward iterator */
template<>
template<>
void module::test<9>( void )
	{
	int l_iCtr = 0;
	list_t l_oList;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	list_t::iterator it;
	for ( it = l_oList.begin();
			it != l_oList.end(); ++ it )
		{
		l_iCtr ++;
		ensure( "iterator is invalid", it.is_valid() );
		ensure_equals( "for syntax: forward iterator made wrong move", ( *it ), l_iCtr );
		}
	ensure_equals( "for syntax: not the whole list was iterated", l_iCtr, 5 );
	ensure( "iterator is valid", ! it.is_valid() );
	ensure_equals( "begin is not head", *l_oList.begin(), l_oList.head() );
	}

/* backward iterator */
template<>
template<>
void module::test<10>( void )
	{
	int l_iCtr = 5;
	list_t l_oList;
	l_oList.add_tail() = 1;
	l_oList.add_tail() = 2;
	l_oList.add_tail() = 3;
	l_oList.add_tail() = 4;
	l_oList.add_tail() = 5;
	list_t::iterator it;
	for ( it = l_oList.rbegin();
			it != l_oList.rend(); -- it )
		{
		ensure_equals ( "for syntax: backward iterator made wrong move", ( *it ), l_iCtr );
		ensure( "iterator is invalid", it.is_valid() );
		l_iCtr --;
		}
	ensure_equals ( "for syntax: not the whole list was iterated", l_iCtr, 0 );
	ensure( "iterator is valid", ! it.is_valid() );
	ensure_equals( "begin is not head", *l_oList.rbegin(), l_oList.tail() );
	}

/* clear, size */
template<>
template<>
void module::test<11>( void )
	{
	list_t lst;
	lst.push_back( 'a' );
	lst.push_back( 'b' );
	lst.push_back( 'c' );
	ensure_equals( "size is wrong", lst.size(), 3 );
	lst.clear();
	ensure_equals( "clear failed or size is wrong", lst.size(), 0 );
	}

/* insert */
template<>
template<>
void module::test<12>( void )
	{
	}

/* add_tail, push_back */
template<>
template<>
void module::test<13>( void )
	{
	list_t lst;
	ensure_equals( "constructor malfunction", lst.size(), 0 );
	lst.push_back( 'a' );
	ensure_equals( "push_back failed", lst.size(), 1 );
	ensure_equals( "push_back failed", to_string( lst ), "a" );
	lst.add_tail() = 'b';
	ensure_equals( "add_tail failed", lst.size(), 2 );
	ensure_equals( "add_tail failed", to_string( lst ), "ab" );
	int c = 'c';
	lst.add_tail( &c );
	ensure_equals( "add_tail failed", lst.size(), 3 );
	ensure_equals( "add_tail failed", to_string( lst ), "abc" );
	lst.push_back( 'd' );
	ensure_equals( "push_back failed", lst.size(), 4 );
	ensure_equals( "push_back failed", to_string( lst ), "abcd" );
	}

/* pop_back, remove_tail */
template<>
template<>
void module::test<14>( void )
	{
	list_t lst;
	ensure_equals( "constructor malfunction", lst.size(), 0 );
	lst.push_back( 'a' );
	lst.add_tail() = 'b';
	int c = 'c';
	lst.add_tail( &c );
	ensure_equals( "add_tail failed", lst.size(), 3 );
	ensure_equals( "add_tail failed", to_string( lst ), "abc" );
	lst.pop_back();
	ensure_equals( "pop_back failed", lst.size(), 2 );
	ensure_equals( "pop_back failed", to_string( lst ), "ab" );
	lst.remove_tail();
	ensure_equals( "remove_tail failed", lst.size(), 1 );
	ensure_equals( "remove_tail failed", to_string( lst ), "a" );
	lst.pop_back();
	ensure_equals( "pop_back failed", lst.size(), 0 );
	ensure_equals( "pop_back failed", to_string( lst ), "" );
	try
		{
		lst.pop_back();
		fail( "poping back empty list did not fail" );
		}
	catch ( HException& )
		{
		// ok
		}
	}

/* add_head, push_front */
template<>
template<>
void module::test<15>( void )
	{
	list_t lst;
	ensure_equals( "constructor malfunction", lst.size(), 0 );
	lst.push_front( 'a' );
	ensure_equals( "push_back failed", lst.size(), 1 );
	ensure_equals( "push_back failed", to_string( lst ), "a" );
	lst.add_head() = 'b';
	ensure_equals( "add_tail failed", lst.size(), 2 );
	ensure_equals( "add_tail failed", to_string( lst ), "ba" );
	int c = 'c';
	lst.add_head( &c );
	ensure_equals( "add_tail failed", lst.size(), 3 );
	ensure_equals( "add_tail failed", to_string( lst ), "cba" );
	lst.push_front( 'd' );
	ensure_equals( "push_back failed", lst.size(), 4 );
	ensure_equals( "push_back failed", to_string( lst ), "dcba" );
	}

/* pop_front, remove_head */
template<>
template<>
void module::test<16>( void )
	{
	list_t lst;
	ensure_equals( "constructor malfunction", lst.size(), 0 );
	lst.push_back( 'a' );
	lst.add_tail() = 'b';
	int c = 'c';
	lst.add_tail( &c );
	ensure_equals( "add_tail failed", lst.size(), 3 );
	ensure_equals( "add_tail failed", to_string( lst ), "abc" );
	lst.pop_front();
	ensure_equals( "pop_front failed", lst.size(), 2 );
	ensure_equals( "pop_front failed", to_string( lst ), "bc" );
	lst.remove_head();
	ensure_equals( "remove_head failed", lst.size(), 1 );
	ensure_equals( "remove_head failed", to_string( lst ), "c" );
	lst.pop_front();
	ensure_equals( "pop_front failed", lst.size(), 0 );
	ensure_equals( "pop_front failed", to_string( lst ), "" );
	try
		{
		lst.pop_front();
		fail( "poping front empty list did not fail" );
		}
	catch ( HException& )
		{
		// ok
		}
	}

/* add_orderly */
template<>
template<>
void module::test<17>( void )
	{
	HList<char> lst;
	ensure_equals( "constructor malfunction", lst.size(), 0 );
	lst.add_orderly( 'd', &yaal::less<char> );
	ensure_equals( "add_orderly failed", lst.size(), 1 );
	ensure_equals( "add_orderly failed", to_string( lst ), "d" );
	lst.add_orderly( 'g', &yaal::less<char> );
	ensure_equals( "add_orderly failed", lst.size(), 2 );
	ensure_equals( "add_orderly failed", to_string( lst ), "dg" );
	lst.add_orderly( 'b', &yaal::less<char> );
	ensure_equals( "add_orderly failed", lst.size(), 3 );
	ensure_equals( "add_orderly failed", to_string( lst ), "bdg" );
	lst.add_orderly( 'e', &yaal::less<char> );
	ensure_equals( "add_orderly failed", lst.size(), 4 );
	ensure_equals( "add_orderly failed", to_string( lst ), "bdeg" );
	lst.add_orderly( 'c', &yaal::less<char> );
	lst.add_orderly( 'a', &yaal::less<char> );
	lst.add_orderly( 'h', &yaal::less<char> );
	lst.add_orderly( 'f', &yaal::less<char> );
	ensure_equals( "add_orderly failed", lst.size(), 8 );
	ensure_equals( "add_orderly failed", to_string( lst ), "abcdefgh" );
	}

/* erase */
template<>
template<>
void module::test<18>( void )
	{
	list_t l;
	l.push_back( 1 );
	l.push_back( 2 );
	cout << endl;
	for ( list_t::iterator it = l.begin(); it != l.end(); )
		{
		list_t::iterator e = it;
		++ it;
		l.erase( e );
		}
	}

/* n_th */
template<>
template<>
void module::test<19>( void )
	{
	list_t l;
	l.push_back( '1' );
	l.push_back( '2' );
	l.push_back( '3' );
	l.push_back( '4' );
	l.push_back( '5' );
	l.push_back( '6' );
	for ( int i = 0; i < 6; ++ i )
		ensure_equals( "n_th( n ) gives bogus result", *l.n_th( i ), i + '1' );
	for ( int i = -1; i > -7; -- i )
		ensure_equals( "n_th( -n ) gives bogus result", *l.n_th( i ), ( 6 + i ) + '1' );
	try
		{
		l.n_th( 6 );
		fail( "index too big and ok ??" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		l.n_th( -7 );
		fail( "index out of range and ok ??" );
		}
	catch ( HException& )
		{
		// ok
		}
	}

/* operator[] */
template<>
template<>
void module::test<20>( void )
	{
	list_t l;
	l.push_back( '1' );
	l.push_back( '2' );
	l.push_back( '3' );
	l.push_back( '4' );
	l.push_back( '5' );
	l.push_back( '6' );
	for ( int i = 0; i < 6; ++ i )
		ensure_equals( "operator[] malfunction", l[ i ], i + 1 + '0' );
	for ( int i = -1; i > -7; -- i )
		ensure_equals( "operator[ -n ] malfunction", l[ i ], i + 6 + '1' );
	try
		{
		l[ 6 ];
		fail( "index too big and ok ??" );
		}
	catch ( HException& )
		{
		// ok
		}
	try
		{
		l[ -7 ];
		fail( "index out of range and ok ??" );
		}
	catch ( HException& )
		{
		// ok
		}
	}

/* exchange */
template<>
template<>
void module::test<21>( void )
	{
	list_t l;
	l.push_back( '1' );
	l.push_back( '2' );
	l.push_back( '3' );
	l.push_back( '4' );
	l.push_back( '5' );
	l.push_back( '6' );
	ensure_equals( "construct error", to_string( l ), "123456" );
	l.exchange( l.begin(), l.rbegin() );
	ensure_equals( "ends exchange error", to_string( l ), "623451" );
	l.exchange( l.n_th( 1 ), l.n_th( 3 ) );
	ensure_equals( "midde items exchange error", to_string( l ), "643251" );
	l.sort_by_contents();
	ensure_equals( "sort error", to_string( l ), "123456" );
	}

/* Sorting. */
template<>
template<>
void module::test<22>( void )
	{
	list_t l_oList;
	l_oList.add_tail() = '3';
	l_oList.add_tail() = '1';
	l_oList.add_tail() = '2';
	ensure_equals ( "operator[] or add_tail failed", l_oList [ 0 ], '3' );
	ensure_equals ( "operator[] or add_tail failed", l_oList [ 1 ], '1' );
	ensure_equals ( "operator[] or add_tail failed", l_oList [ 2 ], '2' );
	l_oList.sort_by_contents();
	ensure_equals ( "sort failed", to_string( l_oList ), "123" );
	}

/* empty, is_empty */
template<>
template<>
void module::test<23>( void )
	{
	list_t l;
	ensure( "new list not empty", l.empty() );
	ensure( "new list not empty", l.is_empty() );
	l.push_back( '1' );
	l.push_back( '2' );
	ensure( "list with some stuff is empty", ! l.empty() );
	ensure( "list with some stuff is empty", ! l.is_empty() );
	}

}

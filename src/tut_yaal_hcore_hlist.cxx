/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hlist.cxx - this file is integral part of `tress' project.

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

#define private public
#define protected public

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_hcore_hlist
	{
	static HString _cache;
	typedef HList<int> list_t;
	template<typename T>
	static HString& to_string( T const& );
	void dump( list_t& );
	template<typename T>
	static void check_consistency( T const& );
	template<typename T>
	void to_list( char const* const, int, T& );
private:
	};

HString tut_yaal_hcore_hlist::_cache;

void tut_yaal_hcore_hlist::dump( list_t& l )
	{
	int long s = l.size();
	cout << "l(" << s << "): [";
	for ( list_t::iterator it = l.begin(); it != l.end(); ++ it )
		cout << *it << ( s -- > 1 ? "," : "" );
	cout << "]" << endl;
	}

template<typename T>
HString& tut_yaal_hcore_hlist::to_string( T const& list )
	{
	_cache.clear();
	for ( typename T::const_iterator it = list.begin(); it != list.end(); ++ it )
		_cache += static_cast<char>( *it );
	return ( _cache );
	}

template<typename T>
void tut_yaal_hcore_hlist::to_list( char const* const templ, int size, T& list )
	{
	list.clear();
	for ( int i = 0; i < size; ++ i )
		list.push_back( templ[ i ] );
	return;
	}

template<typename T>
void tut_yaal_hcore_hlist::check_consistency( T const& list )
	{
	int ctr = 0;
	bool hook_valid = false;
	bool index_valid = false;
	for ( typename T::const_iterator it = list.begin(); it != list.end(); ++ it, ++ ctr )
		{
		if ( it.f_poCurrent == list.f_poHook )
			hook_valid = true;
		if ( list.f_poIndex == it.f_poCurrent )
			{
			ensure_equals( "bad forward index", list.f_iIndex, ctr );
			index_valid = true;
			}
		ensure_equals( "links broken", it.f_poCurrent->f_poNext->f_poPrevious, it.f_poCurrent );
		ensure_equals( "links broken", it.f_poCurrent->f_poPrevious->f_poNext, it.f_poCurrent );
		}
	if ( ! list.f_poIndex )
		index_valid = true;
	if ( ! ctr && ( list.f_poHook == NULL ) )
		hook_valid = true;
	ensure_equals( "forward cycle", ctr, list.f_iSize );
	ensure( "no hook", hook_valid );
	ensure( "invalid index", index_valid );
	
	ctr = 0;
	hook_valid = false;
	index_valid = false;
	for ( typename T::const_iterator it = list.rbegin(); it != list.rend(); -- it, ++ ctr )
		{
		if ( it.f_poCurrent == list.f_poHook )
			hook_valid = true;
		if ( list.f_poIndex == it.f_poCurrent )
			{
			ensure_equals( "bad backward index", list.f_iIndex, ( list.f_iSize - ctr ) - 1 );
			index_valid = true;
			}
		ensure_equals( "links broken", it.f_poCurrent->f_poNext->f_poPrevious, it.f_poCurrent );
		ensure_equals( "links broken", it.f_poCurrent->f_poPrevious->f_poNext, it.f_poCurrent );
		}
	if ( ! list.f_poIndex )
		index_valid = true;
	if ( ! ctr && ( list.f_poHook == NULL ) )
		hook_valid = true;
	ensure_equals( "backward cycle", ctr, list.f_iSize );
	ensure( "no hook", hook_valid );
	ensure( "invalid index", index_valid );
	return;
	}

typedef test_group<tut_yaal_hcore_hlist>tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hlist_group ( "yaal::hcore::HList" );

/* Simple constructor. */
template<>
template<>
void module::test<1>( void )
	{
	list_t l;
	check_consistency( l );
	ensure_equals ( "list not empty", l.size(), 0 );
	check_consistency( l );
	}

/* Parametrized constructor. */
template<>
template<>
void module::test<2>( void )
	{
	list_t l ( 3 );
	check_consistency( l );
	ensure_equals ( "list not empty", l.size(), 3 );
	check_consistency( l );
	}

/* copy constructor */
template<>
template<>
void module::test<3>( void )
	{
	int l_iCtr = 0;
	list_t l;
	check_consistency( l );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	list_t o( l );
	check_consistency( o );
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it )
		{
		check_consistency( o );
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
	list_t l;
	check_consistency( l );
	list_t o;
	check_consistency( o );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	o = l;
	check_consistency( l );
	check_consistency( o );
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it )
		{
		check_consistency( o );
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
	list_t l;
	check_consistency( l );
	list_t o;
	check_consistency( o );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	l = o;
	check_consistency( l );
	check_consistency( o );
	ensure_equals ( "assign operation failed, wrong size", l.size(), 0 );
	}

/* assignation operator (full to small) */
template<>
template<>
void module::test<6>( void )
	{
	int l_iCtr = 0;
	list_t l;
	check_consistency( l );
	list_t o;
	check_consistency( o );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	o.add_tail() = 6;
	check_consistency( o );
	o.add_tail() = 7;
	check_consistency( o );
	o.add_tail() = 8;
	check_consistency( o );
	o = l;
	check_consistency( l );
	check_consistency( o );
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it )
		{
		check_consistency( o );
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
	list_t l;
	check_consistency( l );
	list_t o;
	check_consistency( o );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	o.add_tail() = 6;
	check_consistency( o );
	o.add_tail() = 7;
	check_consistency( o );
	o.add_tail() = 8;
	check_consistency( o );
	o.add_tail() = 9;
	check_consistency( o );
	o.add_tail() = 10;
	check_consistency( o );
	o.add_tail() = 11;
	check_consistency( o );
	o.add_tail() = 12;
	check_consistency( o );
	o = l;
	check_consistency( l );
	check_consistency( o );
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it )
		{
		check_consistency( o );
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
	list_t l;
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.push_back( 'b' );
	check_consistency( l );
	l.push_back( 'c' );
	check_consistency( l );
	ensure_equals( "push_back failed", to_string( l ), "abc" );
	list_t::cyclic_iterator it = l.hook();
	check_consistency( l );
	char const* const vec = "abcabc";
	for ( size_t i = 0; i < strlen( vec ); ++ i )
		{
		cout << i;
		ensure_equals( "cyclic_iterator failed", static_cast<char>( *it ), vec[ i ] );
		++ it;
		}
	char const* const vec2 = "acbacb";
	it = l.hook();
	check_consistency( l );
	for ( size_t i = 0; i < strlen( vec ); ++ i )
		{
		cout << i;
		ensure_equals( "cyclic_iterator failed", static_cast<char>( *it ), vec2[ i ] );
		-- it;
		}
	cout << endl;
	it = l.hook();
	check_consistency( l );
	ensure_equals( "hook is not head", *it, l.head() );
	check_consistency( l );
	}

/* forward iterator */
template<>
template<>
void module::test<9>( void )
	{
	int l_iCtr = 0;
	list_t l;
	check_consistency( l );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	list_t::iterator it;
	for ( it = l.begin();
			it != l.end(); ++ it )
		{
		check_consistency( l );
		l_iCtr ++;
		ensure( "iterator is invalid", it.is_valid() );
		ensure_equals( "for syntax: forward iterator made wrong move", ( *it ), l_iCtr );
		}
	ensure_equals( "for syntax: not the whole list was iterated", l_iCtr, 5 );
	ensure( "iterator is valid", ! it.is_valid() );
	check_consistency( l );
	ensure_equals( "begin is not head", *l.begin(), l.head() );
	check_consistency( l );
	}

/* backward iterator */
template<>
template<>
void module::test<10>( void )
	{
	int l_iCtr = 5;
	list_t l;
	check_consistency( l );
	l.add_tail() = 1;
	check_consistency( l );
	l.add_tail() = 2;
	check_consistency( l );
	l.add_tail() = 3;
	check_consistency( l );
	l.add_tail() = 4;
	check_consistency( l );
	l.add_tail() = 5;
	check_consistency( l );
	list_t::iterator it;
	for ( it = l.rbegin();
			it != l.rend(); -- it )
		{
		check_consistency( l );
		ensure_equals ( "for syntax: backward iterator made wrong move", ( *it ), l_iCtr );
		ensure( "iterator is invalid", it.is_valid() );
		l_iCtr --;
		}
	ensure_equals ( "for syntax: not the whole list was iterated", l_iCtr, 0 );
	ensure( "iterator is valid", ! it.is_valid() );
	check_consistency( l );
	ensure_equals( "begin is not head", *l.rbegin(), l.tail() );
	check_consistency( l );
	}

/* clear, size */
template<>
template<>
void module::test<11>( void )
	{
	list_t l;
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.push_back( 'b' );
	check_consistency( l );
	l.push_back( 'c' );
	check_consistency( l );
	ensure_equals( "size is wrong", l.size(), 3 );
	check_consistency( l );
	l.clear();
	check_consistency( l );
	ensure_equals( "clear failed or size is wrong", l.size(), 0 );
	check_consistency( l );
	}

/* insert */
template<>
template<>
void module::test<12>( void )
	{
	list_t l;
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	l.push_back( '3' );
	check_consistency( l );
	list_t::iterator it;
	ensure_equals( "push_back failed", to_string( l ), "123" );
	ensure_equals( "list malformed", l.size(), 3 );
	check_consistency( l );
	it = l.insert( l.begin(), 'a' );
	check_consistency( l );
	ensure_equals( "insert failed", to_string( l ), "a123" );
	ensure_equals( "list malformed", l.size(), 4 );
	check_consistency( l );
	ensure_equals( "bad iterator", *it, 'a' );
	it = l.insert( l.rbegin(), 'b' );
	check_consistency( l );
	ensure_equals( "insert failed", to_string( l ), "a12b3" );
	ensure_equals( "list malformed", l.size(), 5 );
	check_consistency( l );
	ensure_equals( "bad iterator", *it, 'b' );
	it = l.insert( l.hook(), 'x' );
	check_consistency( l );
	ensure_equals( "insert failed", to_string( l ), "a12b3x" );
	ensure_equals( "list malformed", l.size(), 6 );
	check_consistency( l );
	ensure_equals( "bad iterator", *it, 'x' );
	}

/* add_tail, push_back */
template<>
template<>
void module::test<13>( void )
	{
	list_t l;
	check_consistency( l );
	ensure_equals( "constructor malfunction", l.size(), 0 );
	l.push_back( 'a' );
	check_consistency( l );
	ensure_equals( "push_back failed", l.size(), 1 );
	check_consistency( l );
	ensure_equals( "push_back failed", to_string( l ), "a" );
	l.add_tail() = 'b';
	check_consistency( l );
	ensure_equals( "add_tail failed", l.size(), 2 );
	check_consistency( l );
	ensure_equals( "add_tail failed", to_string( l ), "ab" );
	int c = 'c';
	l.add_tail( &c );
	check_consistency( l );
	ensure_equals( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ensure_equals( "add_tail failed", to_string( l ), "abc" );
	l.push_back( 'd' );
	check_consistency( l );
	ensure_equals( "push_back failed", l.size(), 4 );
	check_consistency( l );
	ensure_equals( "push_back failed", to_string( l ), "abcd" );
	}

/* pop_back, remove_tail */
template<>
template<>
void module::test<14>( void )
	{
	list_t l;
	check_consistency( l );
	ensure_equals( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.add_tail() = 'b';
	check_consistency( l );
	int c = 'c';
	l.add_tail( &c );
	check_consistency( l );
	ensure_equals( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ensure_equals( "add_tail failed", to_string( l ), "abc" );
	l.pop_back();
	check_consistency( l );
	ensure_equals( "pop_back failed", l.size(), 2 );
	check_consistency( l );
	ensure_equals( "pop_back failed", to_string( l ), "ab" );
	l.remove_tail();
	check_consistency( l );
	ensure_equals( "remove_tail failed", l.size(), 1 );
	check_consistency( l );
	ensure_equals( "remove_tail failed", to_string( l ), "a" );
	l.pop_back();
	check_consistency( l );
	ensure_equals( "pop_back failed", l.size(), 0 );
	check_consistency( l );
	ensure_equals( "pop_back failed", to_string( l ), "" );
	try
		{
		l.pop_back();
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
	list_t l;
	check_consistency( l );
	ensure_equals( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.push_front( 'a' );
	check_consistency( l );
	ensure_equals( "push_back failed", l.size(), 1 );
	check_consistency( l );
	ensure_equals( "push_back failed", to_string( l ), "a" );
	l.add_head() = 'b';
	check_consistency( l );
	ensure_equals( "add_tail failed", l.size(), 2 );
	check_consistency( l );
	ensure_equals( "add_tail failed", to_string( l ), "ba" );
	int c = 'c';
	l.add_head( &c );
	check_consistency( l );
	ensure_equals( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ensure_equals( "add_tail failed", to_string( l ), "cba" );
	l.push_front( 'd' );
	check_consistency( l );
	ensure_equals( "push_back failed", l.size(), 4 );
	check_consistency( l );
	ensure_equals( "push_back failed", to_string( l ), "dcba" );
	}

/* pop_front, remove_head */
template<>
template<>
void module::test<16>( void )
	{
	list_t l;
	check_consistency( l );
	ensure_equals( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.add_tail() = 'b';
	check_consistency( l );
	int c = 'c';
	l.add_tail( &c );
	check_consistency( l );
	ensure_equals( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ensure_equals( "add_tail failed", to_string( l ), "abc" );
	l.pop_front();
	check_consistency( l );
	ensure_equals( "pop_front failed", l.size(), 2 );
	check_consistency( l );
	ensure_equals( "pop_front failed", to_string( l ), "bc" );
	l.remove_head();
	check_consistency( l );
	ensure_equals( "remove_head failed", l.size(), 1 );
	check_consistency( l );
	ensure_equals( "remove_head failed", to_string( l ), "c" );
	l.pop_front();
	check_consistency( l );
	ensure_equals( "pop_front failed", l.size(), 0 );
	check_consistency( l );
	ensure_equals( "pop_front failed", to_string( l ), "" );
	try
		{
		l.pop_front();
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
	HList<char> l;
	check_consistency( l );
	ensure_equals( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.add_orderly( 'd', &yaal::less<char> );
	check_consistency( l );
	ensure_equals( "add_orderly failed", l.size(), 1 );
	check_consistency( l );
	ensure_equals( "add_orderly failed", to_string( l ), "d" );
	l.add_orderly( 'g', &yaal::less<char> );
	check_consistency( l );
	ensure_equals( "add_orderly failed", l.size(), 2 );
	check_consistency( l );
	ensure_equals( "add_orderly failed", to_string( l ), "dg" );
	l.add_orderly( 'b', &yaal::less<char> );
	check_consistency( l );
	ensure_equals( "add_orderly failed", l.size(), 3 );
	check_consistency( l );
	ensure_equals( "add_orderly failed", to_string( l ), "bdg" );
	l.add_orderly( 'e', &yaal::less<char> );
	check_consistency( l );
	ensure_equals( "add_orderly failed", l.size(), 4 );
	check_consistency( l );
	ensure_equals( "add_orderly failed", to_string( l ), "bdeg" );
	l.add_orderly( 'c', &yaal::less<char> );
	check_consistency( l );
	l.add_orderly( 'a', &yaal::less<char> );
	check_consistency( l );
	l.add_orderly( 'h', &yaal::less<char> );
	check_consistency( l );
	l.add_orderly( 'f', &yaal::less<char> );
	check_consistency( l );
	ensure_equals( "add_orderly failed", l.size(), 8 );
	check_consistency( l );
	ensure_equals( "add_orderly failed", to_string( l ), "abcdefgh" );
	}

void erase_test_0( tut_yaal_hcore_hlist::list_t& l )
	{
	char const* const full = "123456";
	char const* ptr = full;
	for ( tut_yaal_hcore_hlist::list_t::iterator it = l.begin(); it != l.end(); )
		{
		it = l.erase( it );
		tut_yaal_hcore_hlist::check_consistency( l );
		ensure_equals( "erase failed", tut_yaal_hcore_hlist::to_string( l ), ++ ptr );
		ensure_equals( "erase failed", l.size(), 6 - ( ptr - full ) );
		}
	}

void erase_test_1( tut_yaal_hcore_hlist::list_t& l )
	{
	l.erase( l.begin() );
	tut_yaal_hcore_hlist::check_consistency( l );
	ensure_equals( "erase1 failed", tut_yaal_hcore_hlist::to_string( l ), "23456" );
	ensure_equals( "erase1 failed", l.size(), 5 );
	tut_yaal_hcore_hlist::check_consistency( l );
	}

void erase_test_2( tut_yaal_hcore_hlist::list_t& l )
	{
	tut_yaal_hcore_hlist::list_t::iterator it = l.erase( l.rbegin() );
	tut_yaal_hcore_hlist::check_consistency( l );
	ensure_equals( "erase2 failed", tut_yaal_hcore_hlist::to_string( l ), "12345" );
	ensure_equals( "erase2 failed", l.size(), 5 );
	tut_yaal_hcore_hlist::check_consistency( l );
	ensure( "open list erase for last element leaves bogus iterator", it == l.end() );
	tut_yaal_hcore_hlist::check_consistency( l );
	}

void erase_test_3( tut_yaal_hcore_hlist::list_t& l )
	{
	tut_yaal_hcore_hlist::list_t::cyclic_iterator it = l.erase( -- l.hook() );
	tut_yaal_hcore_hlist::check_consistency( l );
	ensure_equals( "erase2 failed", tut_yaal_hcore_hlist::to_string( l ), "12345" );
	ensure_equals( "erase2 failed", l.size(), 5 );
	tut_yaal_hcore_hlist::check_consistency( l );
	ensure( "open list erase for last element leaves bogus iterator", it == l.hook() );
	tut_yaal_hcore_hlist::check_consistency( l );
	}

/* erase */
template<>
template<>
void module::test<18>( void )
	{
	list_t l;
	typedef void (*erase_test_t)( list_t& );
	erase_test_t erase_tests[] = { erase_test_0, erase_test_1, erase_test_2, erase_test_3 };
	for ( size_t i = 0; i < sizeof ( erase_tests ) / sizeof ( erase_test_t ); ++ i )
		{
		l.clear();
		check_consistency( l );
		l.push_back( '1' ); l.push_back( '2' ); l.push_back( '3' ); l.push_back( '4' );
		check_consistency( l );
		l.push_back( '5' ); l.push_back( '6' );
		check_consistency( l );
		ensure_equals( "construction failed", l.size(), 6 );
		ensure_equals( "construction failed", to_string( l ), "123456" );
		erase_tests[ i ]( l );
		check_consistency( l );
		}
	}

/* n_th */
template<>
template<>
void module::test<19>( void )
	{
	list_t l;
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	l.push_back( '3' );
	check_consistency( l );
	l.push_back( '4' );
	check_consistency( l );
	l.push_back( '5' );
	check_consistency( l );
	l.push_back( '6' );
	check_consistency( l );
	for ( int i = 0; i < 6; ++ i )
		{
		ensure_equals( "n_th( n ) gives bogus result", *l.n_th( i ), i + '1' );
		check_consistency( l );
		}
	for ( int i = -1; i > -7; -- i )
		{
		ensure_equals( "n_th( -n ) gives bogus result", *l.n_th( i ), ( 6 + i ) + '1' );
		check_consistency( l );
		}
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
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	l.push_back( '3' );
	check_consistency( l );
	l.push_back( '4' );
	check_consistency( l );
	l.push_back( '5' );
	check_consistency( l );
	l.push_back( '6' );
	check_consistency( l );
	for ( int i = 0; i < 6; ++ i )
		{
		ensure_equals( "operator[] malfunction", l[ i ], i + 1 + '0' );
		check_consistency( l );
		}
	for ( int i = -1; i > -7; -- i )
		{
		ensure_equals( "operator[ -n ] malfunction", l[ i ], i + 6 + '1' );
		check_consistency( l );
		}
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
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	l.push_back( '3' );
	check_consistency( l );
	l.push_back( '4' );
	check_consistency( l );
	l.push_back( '5' );
	check_consistency( l );
	l.push_back( '6' );
	check_consistency( l );
	ensure_equals( "construct error", to_string( l ), "123456" );
	l.exchange( l.begin(), l.rbegin() );
	check_consistency( l );
	ensure_equals( "ends exchange error", to_string( l ), "623451" );
	l.exchange( l.n_th( 1 ), l.n_th( 3 ) );
	check_consistency( l );
	ensure_equals( "midde items exchange error", to_string( l ), "643251" );
	l.push_back( '0' );
	check_consistency( l );
	l.push_back( '8' );
	check_consistency( l );
	l.push_back( '7' );
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ensure_equals( "sort error", to_string( l ), "012345678" );
	l.clear();
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ensure_equals( "sort error", to_string( l ), "" );
	l.push_back( '1' );
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ensure_equals( "sort error", to_string( l ), "1" );
	char buf[] = "00000110";
	to_list( buf, 8, l );
	ensure_equals( "to_list failed", to_string( l ), buf );
	l.sort();
	ensure_equals( "sort failed", to_string( l ), "00000011" );
	}

/* Sorting. */
template<>
template<>
void module::test<22>( void )
	{
	list_t l;
	check_consistency( l );
	l.add_tail() = '3';
	check_consistency( l );
	l.add_tail() = '1';
	check_consistency( l );
	l.add_tail() = '2';
	check_consistency( l );
	ensure_equals ( "operator[] or add_tail failed", l [ 0 ], '3' );
	check_consistency( l );
	ensure_equals ( "operator[] or add_tail failed", l [ 1 ], '1' );
	check_consistency( l );
	ensure_equals ( "operator[] or add_tail failed", l [ 2 ], '2' );
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ensure_equals ( "sort failed", to_string( l ), "123" );
	l.clear();
	l.push_back( '3' );
	l.push_back( '2' );
	l.push_back( '1' );
	l.sort();
	check_consistency( l );
	ensure_equals ( "sort failed", to_string( l ), "123" );
	l.sort( OListBits::D_DESCENDING );
	check_consistency( l );
	ensure_equals ( "sort failed", to_string( l ), "321" );
	}

/* empty, is_empty */
template<>
template<>
void module::test<23>( void )
	{
	list_t l;
	check_consistency( l );
	ensure( "new list not empty", l.empty() );
	check_consistency( l );
	ensure( "new list not empty", l.is_empty() );
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	ensure( "list with some stuff is empty", ! l.empty() );
	check_consistency( l );
	ensure( "list with some stuff is empty", ! l.is_empty() );
	check_consistency( l );
	}

/* exchange */
template<>
template<>
void module::test<24>( void )
	{
	list_t l1;
	check_consistency( l1 );
	l1.push_back( '1' );
	check_consistency( l1 );
	l1.push_back( '2' );
	check_consistency( l1 );
	list_t l2;
	check_consistency( l2 );
	l2.push_back( 'a' );
	check_consistency( l2 );
	l2.push_back( 'b' );
	check_consistency( l2 );
	ensure_equals ( "build failed", to_string( l1 ), "12" );
	ensure_equals ( "build failed", to_string( l2 ), "ab" );
	swap( l1, l2 );
	check_consistency( l1 );
	check_consistency( l2 );
	ensure_equals ( "exchange failed", to_string( l2 ), "12" );
	ensure_equals ( "exchange failed", to_string( l1 ), "ab" );
	}

void check_sorted( tut_yaal_hcore_hlist::list_t const& l, OListBits::sort_order_t order )
	{
	if ( order == OListBits::D_ASCENDING )
		{
		int val = 0;
		for ( tut_yaal_hcore_hlist::list_t::const_iterator it = l.begin(); it != l.end(); ++ it )
			{
			ensure( "not sorted", val <= *it );
			val = *it;
			}
		}
	else
		{
		int val = 0;
		for ( tut_yaal_hcore_hlist::list_t::const_iterator it = l.rbegin(); it != l.rend(); -- it )
			{
			ensure( "not sorted (reversed)", val <= *it );
			val = *it;
			}
		}
	}

/* sort serious */
template<>
template<>
void module::test<25>( void )
	{
	//int long unsigned count = 0100000000;
	int long unsigned count = 01000000;
	char buf[10];
	list_t l;
	check_consistency( l );
	std::cout << std::setprecision( 2 ) << std::fixed;
	for ( int long unsigned i = 0; i < count; ++ i )
		{
		snprintf( buf, 9, "%08lo", i );
		for ( int k = 0; k < 8; ++ k )
			l.push_back( buf[ k ] );
		try
			{
			l.sort();
			check_consistency( l );
			check_sorted( l, OListBits::D_ASCENDING );
			l.sort( OListBits::D_DESCENDING );
			check_consistency( l );
			check_sorted( l, OListBits::D_DESCENDING );
			}
		catch ( ... )
			{
			std::cout << "(" << std::setw( 8 ) << std::setfill( '0' ) << std::oct << i << ")[" << to_string( l ) << "]" << std::endl;
			throw;
			}
		check_consistency( l );
		l.clear();
		check_consistency( l );
		if ( ! ( i % 8192 ) )
			std::cout << "\r               \r" << std::setw( 6 ) << 100. * ( static_cast<double>( i ) / static_cast<double>( count ) ) << '%' << std::flush;
		}
	}

}


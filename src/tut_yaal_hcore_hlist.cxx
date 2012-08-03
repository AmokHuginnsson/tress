/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hlist.cxx - this file is integral part of `tress' project.

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
#include <cstdio>

#include <yaal/hcore/hexception.hxx>

#define private public
#define protected public

#include <TUT/tut.hpp>

#include <yaal/hcore/hlist.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include <yaal/tools/collections.hxx>
#include <yaal/hconsole/hlistcontrol.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::collections;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hlist : public simple_mock<tut_yaal_hcore_hlist> {
	typedef simple_mock<tut_yaal_hcore_hlist> base_type;
	Stringifier _stringifier;
	typedef HList<int> list_t;
	void dump( list_t& );
	template<typename T>
	void check_consistency( T const& );
	template<typename T>
	void to_list( char const* const, int, T& );
	tut_yaal_hcore_hlist( void )
		: base_type(), _stringifier()
		{}
	virtual ~tut_yaal_hcore_hlist( void )
		{}
	void erase_test_0( list_t& l );
	void erase_test_1( list_t& l );
	void erase_test_2( list_t& l );
	void erase_test_3( list_t& l );
	list_t from_string( char const* );
private:
};

void tut_yaal_hcore_hlist::dump( list_t& l ) {
	int long s = l.size();
	cout << "l(" << s << "): [";
	for ( list_t::iterator it = l.begin(); it != l.end(); ++ it )
		cout << *it << ( s -- > 1 ? "," : "" );
	cout << "]" << endl;
}

template<typename T>
void tut_yaal_hcore_hlist::to_list( char const* const templ, int size, T& list ) {
	list.clear();
	for ( int i = 0; i < size; ++ i )
		list.push_back( templ[ i ] );
	return;
}

template<typename T>
void tut_yaal_hcore_hlist::check_consistency( T const& list ) {
	int ctr = 0;
	bool hook_valid = false;
	for ( typename T::const_iterator it = list.begin(); it != list.end(); ++ it, ++ ctr ) {
		if ( it._current == list._hook )
			hook_valid = true;
		ENSURE_EQUALS( "links broken", it._current->_next->_previous, it._current );
		ENSURE_EQUALS( "links broken", it._current->_previous->_next, it._current );
	}
	if ( ! ctr && ( list._hook == NULL ) )
		hook_valid = true;
	ENSURE_EQUALS( "forward cycle", ctr, list._size );
	ENSURE( "no hook", hook_valid );
	
	ctr = 0;
	hook_valid = false;
	for ( typename T::const_reverse_iterator it = list.rbegin(); it != list.rend(); ++ it, ++ ctr ) {
		if ( it.base()._current == list._hook )
			hook_valid = true;
		ENSURE_EQUALS( "links broken", it.base()._current->_next->_previous, it.base()._current );
		ENSURE_EQUALS( "links broken", it.base()._current->_previous->_next, it.base()._current );
	}
	if ( ! ctr && ( list._hook == NULL ) )
		hook_valid = true;
	ENSURE_EQUALS( "backward cycle", ctr, list._size );
	ENSURE( "no hook", hook_valid );
	return;
}

tut_yaal_hcore_hlist::list_t tut_yaal_hcore_hlist::from_string( char const* data_ ) {
	int const LEN( static_cast<int>( ::strlen( data_ ) ) );
	list_t l;
	for ( int i( 0 ); i < LEN; ++ i )
		l.push_back( data_[i] );
	return ( l );
}

TUT_TEST_GROUP( tut_yaal_hcore_hlist, "yaal::hcore::HList" );

TUT_UNIT_TEST( 1, "Simple constructor." )
	list_t l;
	check_consistency( l );
	ENSURE_EQUALS( "list not empty", l.size(), 0 );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "Parametrized constructor." )
	list_t l ( 3 );
	check_consistency( l );
	ENSURE_EQUALS( "list not empty", l.size(), 3 );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "copy constructor" )
	int ctr = 0;
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
			it != o.end(); ++ it ) {
		check_consistency( o );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "assignation operator (full to empty)" )
	int ctr = 0;
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
	list_t const& ro = o;
	for ( list_t::const_iterator it = ro.begin();
			it != ro.end(); ++ it ) {
		check_consistency( ro );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "assignation operator (empty to full)" )
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
	ENSURE_EQUALS( "assign operation failed, wrong size", l.size(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "assignation operator (full to small)" )
	int ctr = 0;
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
			it != o.end(); ++ it ) {
		check_consistency( o );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "assignation operator (full to big)" )
	int ctr = 0;
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
			it != o.end(); ++ it ) {
		check_consistency( o );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, ".hook(), cyclic_iterator" )
	list_t l;
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.push_back( 'b' );
	check_consistency( l );
	l.push_back( 'c' );
	check_consistency( l );
	ENSURE_EQUALS( "push_back failed", _stringifier.to_string<char>( l ), "abc" );
	list_t::cyclic_iterator it = l.hook();
	check_consistency( l );
	char const* const vec = "abcabc";
	for ( size_t i = 0; i < strlen( vec ); ++ i ) {
		cout << i;
		ENSURE_EQUALS( "cyclic_iterator failed", static_cast<char>( *it ), vec[ i ] );
		++ it;
	}
	char const* const vec2 = "acbacb";
	it = l.hook();
	check_consistency( l );
	for ( size_t i = 0; i < strlen( vec ); ++ i ) {
		cout << i;
		ENSURE_EQUALS( "cyclic_iterator failed", static_cast<char>( *it ), vec2[ i ] );
		-- it;
	}
	cout << endl;
	it = l.hook();
	check_consistency( l );
	ENSURE_EQUALS( "hook is not head", *it, l.head() );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "forward iterator" )
	int ctr = 0;
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
			it != l.end(); ++ it ) {
		check_consistency( l );
		ctr ++;
		ENSURE_EQUALS( "for syntax: forward iterator made wrong move", ( *it ), ctr );
	}
	ENSURE_EQUALS( "for syntax: not the whole list was iterated", ctr, 5 );
	check_consistency( l );
	ENSURE_EQUALS( "begin is not head", *l.begin(), l.head() );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "backward iterator" )
	int ctr = 5;
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
	for ( list_t::reverse_iterator it( l.rbegin() ); it != l.rend(); ++ it ) {
		check_consistency( l );
		ENSURE_EQUALS( "for syntax: backward iterator made wrong move", ( *it ), ctr );
		ctr --;
	}
	ENSURE_EQUALS( "for syntax: not the whole list was iterated", ctr, 0 );
	check_consistency( l );
	ENSURE_EQUALS( "begin is not head", *l.rbegin(), l.tail() );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "clear, size" )
	list_t l;
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.push_back( 'b' );
	check_consistency( l );
	l.push_back( 'c' );
	check_consistency( l );
	ENSURE_EQUALS( "size is wrong", l.size(), 3 );
	check_consistency( l );
	l.clear();
	check_consistency( l );
	ENSURE_EQUALS( "clear failed or size is wrong", l.size(), 0 );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "insert" )
	list_t l;
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	l.push_back( '3' );
	check_consistency( l );
	list_t::iterator it;
	ENSURE_EQUALS( "push_back failed", _stringifier.to_string<char>( l ), "123" );
	ENSURE_EQUALS( "list malformed", l.size(), 3 );
	check_consistency( l );
	it = l.insert( l.begin(), 'a' );
	check_consistency( l );
	ENSURE_EQUALS( "insert failed", _stringifier.to_string<char>( l ), "a123" );
	ENSURE_EQUALS( "list malformed", l.size(), 4 );
	check_consistency( l );
	ENSURE_EQUALS( "bad iterator", *it, 'a' );
	it = l.insert( l.rbegin().base(), 'b' );
	check_consistency( l );
	ENSURE_EQUALS( "insert failed", _stringifier.to_string<char>( l ), "a12b3" );
	ENSURE_EQUALS( "list malformed", l.size(), 5 );
	check_consistency( l );
	ENSURE_EQUALS( "bad iterator", *it, 'b' );
	it = l.insert( l.hook(), 'x' );
	check_consistency( l );
	ENSURE_EQUALS( "insert failed", _stringifier.to_string<char>( l ), "a12b3x" );
	ENSURE_EQUALS( "list malformed", l.size(), 6 );
	check_consistency( l );
	ENSURE_EQUALS( "bad iterator", *it, 'x' );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "add_tail, push_back" )
	list_t l;
	check_consistency( l );
	ENSURE_EQUALS( "constructor malfunction", l.size(), 0 );
	l.push_back( 'a' );
	check_consistency( l );
	ENSURE_EQUALS( "push_back failed", l.size(), 1 );
	check_consistency( l );
	ENSURE_EQUALS( "push_back failed", _stringifier.to_string<char>( l ), "a" );
	l.add_tail() = 'b';
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", l.size(), 2 );
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", _stringifier.to_string<char>( l ), "ab" );
	l.add_tail() = 'c';
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", _stringifier.to_string<char>( l ), "abc" );
	l.push_back( 'd' );
	check_consistency( l );
	ENSURE_EQUALS( "push_back failed", l.size(), 4 );
	check_consistency( l );
	ENSURE_EQUALS( "push_back failed", _stringifier.to_string<char>( l ), "abcd" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "pop_back, remove_tail" )
	list_t l;
	check_consistency( l );
	ENSURE_EQUALS( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.add_tail() = 'b';
	check_consistency( l );
	l.add_tail() = 'c';
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", _stringifier.to_string<char>( l ), "abc" );
	l.pop_back();
	check_consistency( l );
	ENSURE_EQUALS( "pop_back failed", l.size(), 2 );
	check_consistency( l );
	ENSURE_EQUALS( "pop_back failed", _stringifier.to_string<char>( l ), "ab" );
	l.pop_back();
	check_consistency( l );
	ENSURE_EQUALS( "pop_back failed", l.size(), 1 );
	check_consistency( l );
	ENSURE_EQUALS( "pop_back failed", _stringifier.to_string<char>( l ), "a" );
	l.pop_back();
	check_consistency( l );
	ENSURE_EQUALS( "pop_back failed", l.size(), 0 );
	check_consistency( l );
	ENSURE_EQUALS( "pop_back failed", _stringifier.to_string<char>( l ), "" );
	try {
		l.pop_back();
		FAIL( "poping back empty list did not FAIL" );
	} catch ( HException& ) {
		// ok
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 15, "add_head, push_front" )
	list_t l;
	check_consistency( l );
	ENSURE_EQUALS( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.push_front( 'a' );
	check_consistency( l );
	ENSURE_EQUALS( "push_front failed", l.size(), 1 );
	check_consistency( l );
	ENSURE_EQUALS( "push_front failed", _stringifier.to_string<char>( l ), "a" );
	l.add_head() = 'b';
	check_consistency( l );
	ENSURE_EQUALS( "add_head failed", l.size(), 2 );
	check_consistency( l );
	ENSURE_EQUALS( "add_head failed", _stringifier.to_string<char>( l ), "ba" );
	l.add_head() = 'c';
	check_consistency( l );
	ENSURE_EQUALS( "add_head failed", l.size(), 3 );
	check_consistency( l );
	ENSURE_EQUALS( "add_head failed", _stringifier.to_string<char>( l ), "cba" );
	l.push_front( 'd' );
	check_consistency( l );
	ENSURE_EQUALS( "push_front failed", l.size(), 4 );
	check_consistency( l );
	ENSURE_EQUALS( "push_front failed", _stringifier.to_string<char>( l ), "dcba" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "pop_front, remove_head" )
	list_t l;
	check_consistency( l );
	ENSURE_EQUALS( "constructor malfunction", l.size(), 0 );
	check_consistency( l );
	l.push_back( 'a' );
	check_consistency( l );
	l.add_tail() = 'b';
	check_consistency( l );
	l.add_tail() = 'c';
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", l.size(), 3 );
	check_consistency( l );
	ENSURE_EQUALS( "add_tail failed", _stringifier.to_string<char>( l ), "abc" );
	l.pop_front();
	check_consistency( l );
	ENSURE_EQUALS( "pop_front failed", l.size(), 2 );
	check_consistency( l );
	ENSURE_EQUALS( "pop_front failed", _stringifier.to_string<char>( l ), "bc" );
	l.pop_front();
	check_consistency( l );
	ENSURE_EQUALS( "pop_front failed", l.size(), 1 );
	check_consistency( l );
	ENSURE_EQUALS( "pop_front failed", _stringifier.to_string<char>( l ), "c" );
	l.pop_front();
	check_consistency( l );
	ENSURE_EQUALS( "pop_front failed", l.size(), 0 );
	check_consistency( l );
	ENSURE_EQUALS( "pop_front failed", _stringifier.to_string<char>( l ), "" );
	try {
		l.pop_front();
		FAIL( "poping front empty list did not FAIL" );
	} catch ( HException& ) {
		// ok
	}
TUT_TEARDOWN()

void tut_yaal_hcore_hlist::erase_test_0( tut_yaal_hcore_hlist::list_t& l ) {
	char const* const full = "123456";
	char const* ptr = full;
	for ( tut_yaal_hcore_hlist::list_t::iterator it = l.begin(); it != l.end(); ) {
		it = l.erase( it );
		tut_yaal_hcore_hlist::check_consistency( l );
		ENSURE_EQUALS( "erase failed", tut_yaal_hcore_hlist::_stringifier.to_string<char>( l ), ++ ptr );
		ENSURE_EQUALS( "erase failed", l.size(), 6 - ( ptr - full ) );
	}
}

void tut_yaal_hcore_hlist::erase_test_1( tut_yaal_hcore_hlist::list_t& l ) {
	l.erase( l.begin() );
	tut_yaal_hcore_hlist::check_consistency( l );
	ENSURE_EQUALS( "erase1 failed", tut_yaal_hcore_hlist::_stringifier.to_string<char>( l ), "23456" );
	ENSURE_EQUALS( "erase1 failed", l.size(), 5 );
	tut_yaal_hcore_hlist::check_consistency( l );
}

void tut_yaal_hcore_hlist::erase_test_2( tut_yaal_hcore_hlist::list_t& l ) {
	tut_yaal_hcore_hlist::list_t::iterator it = l.erase( l.rbegin().base() );
	tut_yaal_hcore_hlist::check_consistency( l );
	ENSURE_EQUALS( "erase2 failed", tut_yaal_hcore_hlist::_stringifier.to_string<char>( l ), "12345" );
	ENSURE_EQUALS( "erase2 failed", l.size(), 5 );
	tut_yaal_hcore_hlist::check_consistency( l );
	ENSURE( "open list erase for last element leaves bogus iterator", it == l.end() );
	tut_yaal_hcore_hlist::check_consistency( l );
}

void tut_yaal_hcore_hlist::erase_test_3( tut_yaal_hcore_hlist::list_t& l ) {
	tut_yaal_hcore_hlist::list_t::cyclic_iterator it = l.erase( -- l.hook() );
	tut_yaal_hcore_hlist::check_consistency( l );
	ENSURE_EQUALS( "erase2 failed", tut_yaal_hcore_hlist::_stringifier.to_string<char>( l ), "12345" );
	ENSURE_EQUALS( "erase2 failed", l.size(), 5 );
	tut_yaal_hcore_hlist::check_consistency( l );
	ENSURE( "open list erase for last element leaves bogus iterator", it == l.hook() );
	tut_yaal_hcore_hlist::check_consistency( l );
}

TUT_UNIT_TEST( 17, "resize" )
	list_t l;
	ENSURE_EQUALS( "constructor of empty failed", l.size(), 0 );
	l.resize( 5 );
	ENSURE_EQUALS( "resize up failed", l.size(), 5 );
	l.resize( 3 );
	ENSURE_EQUALS( "resize down failed", l.size(), 3 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "erase" )
	list_t l;
	typedef void (tut_yaal_hcore_hlist::*erase_test_t)( list_t& );
	erase_test_t erase_tests[] = {
		&tut_yaal_hcore_hlist::erase_test_0,
		&tut_yaal_hcore_hlist::erase_test_1,
		&tut_yaal_hcore_hlist::erase_test_2,
		&tut_yaal_hcore_hlist::erase_test_3
	};
	for ( size_t i = 0; i < sizeof ( erase_tests ) / sizeof ( erase_test_t ); ++ i ) {
		l.clear();
		check_consistency( l );
		l.push_back( '1' ); l.push_back( '2' ); l.push_back( '3' ); l.push_back( '4' );
		check_consistency( l );
		l.push_back( '5' ); l.push_back( '6' );
		check_consistency( l );
		ENSURE_EQUALS( "construction failed", l.size(), 6 );
		ENSURE_EQUALS( "construction failed", _stringifier.to_string<char>( l ), "123456" );
		(this->*erase_tests[ i ])( l );
		check_consistency( l );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 19, "assign( iter, iter )" )
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
	list_t o;
	o.assign( l.begin(), l.end() );
	check_consistency( o );
	int ctr = 0;
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it ) {
		check_consistency( o );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
	o.clear();
	o.push_back( -1 );
	o.push_back( -2 );
	o.assign( l.begin(), l.end() );
	check_consistency( o );
	ctr = 0;
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it ) {
		check_consistency( o );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
	o.clear();
	o.push_back( -1 );
	o.push_back( -2 );
	o.push_back( -3 );
	o.push_back( -4 );
	o.push_back( -5 );
	o.push_back( -6 );
	o.push_back( -7 );
	o.assign( l.begin(), l.end() );
	check_consistency( o );
	ctr = 0;
	for ( list_t::iterator it = o.begin();
			it != o.end(); ++ it ) {
		check_consistency( o );
		ctr ++;
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, ctr );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", ctr, 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "assign( count, val )" )
	list_t l;
	l.assign( 5, 7 );
	for ( list_t::iterator it( l.begin() ), end( l.end() ); it != end; ++ it ) {
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, 7 );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", l.size(), 5 );

	l.clear();
	l.push_back( -1 );
	l.push_back( -2 );
	l.assign( 5, 7 );
	for ( list_t::iterator it( l.begin() ), end( l.end() ); it != end; ++ it ) {
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, 7 );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", l.size(), 5 );

	l.clear();
	l.push_back( -1 );
	l.push_back( -2 );
	l.push_back( -3 );
	l.push_back( -4 );
	l.push_back( -5 );
	l.push_back( -6 );
	l.push_back( -7 );
	l.assign( 5, 7 );
	for ( list_t::iterator it( l.begin() ), end( l.end() ); it != end; ++ it ) {
		ENSURE_EQUALS( "assign operation failed, wrong value", *it, 7 );
	}
	ENSURE_EQUALS( "assign operation failed, wrong size", l.size(), 5 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 21, "exchange" )
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
	ENSURE_EQUALS( "construct error", _stringifier.to_string<char>( l ), "123456" );
	l.exchange( l.begin(), l.rbegin().base() );
	check_consistency( l );
	ENSURE_EQUALS( "ends exchange error", _stringifier.to_string<char>( l ), "623451" );
	l.exchange( n_th( l, 1 ), n_th( l, 3 ) );
	check_consistency( l );
	ENSURE_EQUALS( "midde items exchange error", _stringifier.to_string<char>( l ), "643251" );
	l.push_back( '0' );
	check_consistency( l );
	l.push_back( '8' );
	check_consistency( l );
	l.push_back( '7' );
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ENSURE_EQUALS( "sort error", _stringifier.to_string<char>( l ), "012345678" );
	l.exchange( n_th( l, 0 ), n_th( l, 1 ) );
	check_consistency( l );
	ENSURE_EQUALS( "0-1 exchange error", _stringifier.to_string<char>( l ), "102345678" );
	l.exchange( n_th( l, 1 ), n_th( l, 0 ) );
	check_consistency( l );
	ENSURE_EQUALS( "1-0 exchange error", _stringifier.to_string<char>( l ), "012345678" );
	l.exchange( n_th( l, 7 ), n_th( l, 8 ) );
	check_consistency( l );
	ENSURE_EQUALS( "7-8 exchange error", _stringifier.to_string<char>( l ), "012345687" );
	l.exchange( n_th( l, 8 ), n_th( l, 7 ) );
	check_consistency( l );
	ENSURE_EQUALS( "8-7 exchange error", _stringifier.to_string<char>( l ), "012345678" );
	l.clear();
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ENSURE_EQUALS( "sort error", _stringifier.to_string<char>( l ), "" );
	l.push_back( '0' );
	l.push_back( '1' );
	check_consistency( l );
	ENSURE_EQUALS( "push_back error", _stringifier.to_string<char>( l ), "01" );
	l.exchange( n_th( l, 0 ), n_th( l, 1 ) );
	check_consistency( l );
	ENSURE_EQUALS( "0-1 exchange error", _stringifier.to_string<char>( l ), "10" );
	l.exchange( n_th( l, 1 ), n_th( l, 0 ) );
	check_consistency( l );
	ENSURE_EQUALS( "1-0 exchange error", _stringifier.to_string<char>( l ), "01" );
	l.push_back( '2' );
	check_consistency( l );
	ENSURE_EQUALS( "push_back error", _stringifier.to_string<char>( l ), "012" );
	l.exchange( n_th( l, 0 ), n_th( l, 1 ) );
	check_consistency( l );
	ENSURE_EQUALS( "0-1 exchange error", _stringifier.to_string<char>( l ), "102" );
	l.exchange( n_th( l, 1 ), n_th( l, 0 ) );
	check_consistency( l );
	ENSURE_EQUALS( "1-0 exchange error", _stringifier.to_string<char>( l ), "012" );
	l.exchange( n_th( l, 1 ), n_th( l, 2 ) );
	check_consistency( l );
	ENSURE_EQUALS( "1-2 exchange error", _stringifier.to_string<char>( l ), "021" );
	l.exchange( n_th( l, 2 ), n_th( l, 1 ) );
	check_consistency( l );
	ENSURE_EQUALS( "2-1 exchange error", _stringifier.to_string<char>( l ), "012" );
	l.exchange( n_th( l, 0 ), n_th( l, 2 ) );
	check_consistency( l );
	ENSURE_EQUALS( "0-2 exchange error", _stringifier.to_string<char>( l ), "210" );
	l.exchange( n_th( l, 2 ), n_th( l, 0 ) );
	check_consistency( l );
	ENSURE_EQUALS( "2-2 exchange error", _stringifier.to_string<char>( l ), "012" );
	l.clear();
	l.push_back( '1' );
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ENSURE_EQUALS( "sort error", _stringifier.to_string<char>( l ), "1" );
	char buf[] = "00000110";
	to_list( buf, 8, l );
	ENSURE_EQUALS( "to_list failed", _stringifier.to_string<char>( l ), buf );
	l.sort();
	ENSURE_EQUALS( "sort failed", _stringifier.to_string<char>( l ), "00000011" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 22, "Sorting." )
	list_t l;
	check_consistency( l );
	l.add_tail() = '3';
	check_consistency( l );
	l.add_tail() = '1';
	check_consistency( l );
	l.add_tail() = '2';
	check_consistency( l );
	ENSURE_EQUALS( "operator[] or add_tail failed", *n_th( l, 0 ), '3' );
	check_consistency( l );
	ENSURE_EQUALS( "operator[] or add_tail failed", *n_th( l, 1 ), '1' );
	check_consistency( l );
	ENSURE_EQUALS( "operator[] or add_tail failed", *n_th( l, 2 ), '2' );
	check_consistency( l );
	l.sort();
	check_consistency( l );
	ENSURE_EQUALS( "sort failed", _stringifier.to_string<char>( l ), "123" );
	l.clear();
	l.push_back( '3' );
	l.push_back( '2' );
	l.push_back( '1' );
	l.sort();
	check_consistency( l );
	ENSURE_EQUALS( "sort failed", _stringifier.to_string<char>( l ), "123" );
	l.sort( greater<int>() );
	check_consistency( l );
	ENSURE_EQUALS( "sort failed", _stringifier.to_string<char>( l ), "321" );
TUT_TEARDOWN()

TUT_UNIT_TEST( 23, "empty, is_empty" )
	list_t l;
	check_consistency( l );
	ENSURE( "new list not empty", l.empty() );
	check_consistency( l );
	ENSURE( "new list not empty", l.is_empty() );
	check_consistency( l );
	l.push_back( '1' );
	check_consistency( l );
	l.push_back( '2' );
	check_consistency( l );
	ENSURE( "list with some stuff is empty", ! l.empty() );
	check_consistency( l );
	ENSURE( "list with some stuff is empty", ! l.is_empty() );
	check_consistency( l );
TUT_TEARDOWN()

TUT_UNIT_TEST( 24, "swap" )
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
	ENSURE_EQUALS( "build failed", _stringifier.to_string<char>( l1 ), "12" );
	ENSURE_EQUALS( "build failed", _stringifier.to_string<char>( l2 ), "ab" );
	swap( l1, l2 );
	check_consistency( l1 );
	check_consistency( l2 );
	ENSURE_EQUALS( "exchange failed", _stringifier.to_string<char>( l2 ), "12" );
	ENSURE_EQUALS( "exchange failed", _stringifier.to_string<char>( l1 ), "ab" );
TUT_TEARDOWN()

namespace {

void check_sorted( tut_yaal_hcore_hlist::list_t const& l, list_control_helper::OSortHelper::sort_order_t order ) {
	if ( order == list_control_helper::OSortHelper::ASCENDING ) {
		int val = 0;
		for ( tut_yaal_hcore_hlist::list_t::const_iterator it = l.begin(); it != l.end(); ++ it ) {
			ENSURE( "not sorted", val <= *it );
			val = *it;
		}
	} else {
		int val = 0;
		for ( tut_yaal_hcore_hlist::list_t::const_reverse_iterator it = l.rbegin(); it != l.rend(); ++ it ) {
			ENSURE( "not sorted (reversed)", val <= *it );
			val = *it;
		}
	}
}

}

TUT_UNIT_TEST( 25, "sort serious" )
	TIME_CONSTRAINT_EXEMPT();
	//int long unsigned count = 0100000000;
	int long unsigned count = 01000000;
	char buf[10];
	list_t l;
	check_consistency( l );
	std::cout << std::setprecision( 2 ) << std::fixed;
	for ( int long unsigned i = 0; i < count; ++ i ) {
		snprintf( buf, 9, "%08lo", i );
		for ( int k = 0; k < 8; ++ k )
			l.push_back( buf[ k ] );
		try {
			l.sort();
			check_consistency( l );
			check_sorted( l, list_control_helper::OSortHelper::ASCENDING );
			l.sort( greater<int>() );
			check_consistency( l );
			check_sorted( l, list_control_helper::OSortHelper::DESCENDING );
		} catch ( ... ) {
			std::cout << "(" << std::setw( 8 ) << std::setfill( '0' ) << std::oct << i << ")[" << _stringifier.to_string<char>( l ) << "]" << std::endl;
			throw;
		}
		check_consistency( l );
		l.clear();
		check_consistency( l );
		if ( ! ( i % 8192 ) )
			std::cout << "\r               \r" << std::setw( 6 ) << 100. * ( static_cast<double>( i ) / static_cast<double>( count ) ) << '%' << std::flush;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 26, "reverse iterator" )
	int a[] = { 2, 3, 5, 7 };
	int ra[] = { 7, 5, 3, 2 };
	list_t l( a, a + countof ( a ) );
	list_t r( l.rbegin(), l.rend() );
	list_t proto( ra, ra + countof ( ra ) );
	ENSURE_EQUALS( "reverse iterarion failed", r, proto );
TUT_TEARDOWN()

TUT_UNIT_TEST( 27, "splice( pos, list )" )
	/* from empty to empty */ {
		list_t l;
		list_t r;
		l.splice( l.begin(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE( "splice(pos, list) failed", l.is_empty() );
	}
	/* from empty */ {
		list_t l( from_string( "123" ) );
		list_t r;
		l.splice( l.begin(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) from empty failed", _stringifier.to_string<char>( l ), "123" );
	}
	/* to empty */ {
		list_t l;
		list_t r( from_string( "456" ) );
		l.splice( l.begin(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) to empty failed", _stringifier.to_string<char>( l ), "456" );
	}
	/* at the begining */ {
		list_t l( from_string( "123" ) );
		list_t r( from_string( "456" ) );
		l.splice( l.begin(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) at the begining failed", _stringifier.to_string<char>( l ), "456123" );
	}
	/* small dst begin */ {
		list_t l( from_string( "1" ) );
		list_t r( from_string( "456" ) );
		l.splice( l.begin(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) (small) at the begining failed", _stringifier.to_string<char>( l ), "4561" );
	}
	/* small dst end */ {
		list_t l( from_string( "1" ) );
		list_t r( from_string( "456" ) );
		l.splice( l.end(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) (small) at end failed", _stringifier.to_string<char>( l ), "1456" );
	}
	/* at end */ {
		list_t l( from_string( "123" ) );
		list_t r( from_string( "456" ) );
		l.splice( l.end(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) at end failed", _stringifier.to_string<char>( l ), "123456" );
	}
	/* small src begin */ {
		list_t l( from_string( "123" ) );
		list_t r( from_string( "4" ) );
		l.splice( l.begin(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) (small src) at the begining failed", _stringifier.to_string<char>( l ), "4123" );
	}
	/* small src end */ {
		list_t l( from_string( "123" ) );
		list_t r( from_string( "4" ) );
		l.splice( l.end(), r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) (small src) at end failed", _stringifier.to_string<char>( l ), "1234" );
	}
	/* in the middle */ {
		list_t l( from_string( "0123" ) );
		list_t r( from_string( "456" ) );
		list_t::iterator mid( l.begin() );
		++ mid;
		++ mid;
		l.splice( mid, r );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list) failed to clean", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list) in the middle failed", _stringifier.to_string<char>( l ), "0145623" );
	}
	/* bad iterator */ {
		list_t l;
		list_t r;
		try {
			l.splice( r.begin(), r );
			FAIL( "out of the blue iterator accepted" );
		} catch ( HFailedAssertion const& ) {
			/* ok */
		}
	}
	/* self splice */ {
		list_t l;
		try {
			l.splice( l.begin(), l );
			FAIL( "self splice accepted" );
		} catch ( HException const& ) {
			/* ok */
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 28, "splice( pos, list, elem )" )
	/* to empty */ {
		/* long middle */ {
			list_t l;
			list_t r( from_string( "123456789" ) );
			list_t::iterator it( r.begin() );
			advance( it, 2 );
			l.splice( l.begin(), r, it );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, elem) empty-dst-middle failed to remove elem", _stringifier.to_string<char>( r ), "12456789" );
			ENSURE_EQUALS( "splice(pos, list, elem) empty-dst-middle failed", _stringifier.to_string<char>( l ), "3" );
		}
		/* long beginning */ {
			list_t l;
			list_t r( from_string( "123456789" ) );
			l.splice( l.begin(), r, r.begin() );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, elem) empty-dst-beginning failed to remove elem", _stringifier.to_string<char>( r ), "23456789" );
			ENSURE_EQUALS( "splice(pos, list, elem) empty-dst-beginning failed", _stringifier.to_string<char>( l ), "1" );
		}
		/* long end */ {
			list_t l;
			list_t r( from_string( "123456789" ) );
			list_t::iterator it( r.begin() );
			advance( it, r.size() - 1 );
			l.splice( l.begin(), r, it );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, elem) empty-dst-end failed to remove elem", _stringifier.to_string<char>( r ), "12345678" );
			ENSURE_EQUALS( "splice(pos, list, elem) empty-dst-end failed", _stringifier.to_string<char>( l ), "9" );
		}
	}
	/* to small (size == 1) */ {
		/* long middle */ {
			/* to beg */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, 2 );
				l.splice( l.begin(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-middle failed to remove elem", _stringifier.to_string<char>( r ), "12456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-middle failed", _stringifier.to_string<char>( l ), "30" );
			}
			/* to end */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, 2 );
				l.splice( l.end(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-middle failed to remove elem", _stringifier.to_string<char>( r ), "12456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-middle failed", _stringifier.to_string<char>( l ), "03" );
			}
		}
		/* long beginning */ {
			/* to beg */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				l.splice( l.begin(), r, r.begin() );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-beginning failed to remove elem", _stringifier.to_string<char>( r ), "23456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-beginning failed", _stringifier.to_string<char>( l ), "10" );
			}
			/* to end */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				l.splice( l.begin(), r, r.end() );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-beginning failed to remove elem", _stringifier.to_string<char>( r ), "23456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-beginning failed", _stringifier.to_string<char>( l ), "01" );
			}
		}
		/* long end */ {
			/* to beg */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, r.size() - 1 );
				l.splice( l.begin(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed to remove elem", _stringifier.to_string<char>( r ), "12345678" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "90" );
			}
			/* to end */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, r.size() - 1 );
				l.splice( l.begin(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed to remove elem", _stringifier.to_string<char>( r ), "12345678" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "09" );
			}
		}
	}
	/* normal to normal */ {
		/* long middle */ {
			/* to beg */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, 2 );
				l.splice( l.begin(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-middle failed to remove elem", _stringifier.to_string<char>( r ), "12456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-middle failed", _stringifier.to_string<char>( l ), "3abcdefghi" );
			}
			/* to end */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, 2 );
				l.splice( l.end(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-middle failed to remove elem", _stringifier.to_string<char>( r ), "12456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-middle failed", _stringifier.to_string<char>( l ), "abcdefghi3" );
			}
			/* to middle */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, 2 );
				list_t::iterator to( l.begin() );
				advance( to, 4 );
				l.splice( to, r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-middle failed to remove elem", _stringifier.to_string<char>( r ), "12456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-middle failed", _stringifier.to_string<char>( l ), "abcd3efghi" );
			}
		}
		/* long beginning */ {
			/* to beg */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				l.splice( l.begin(), r, r.begin() );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-beginning failed to remove elem", _stringifier.to_string<char>( r ), "23456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-beginning failed", _stringifier.to_string<char>( l ), "1abcdefghi" );
			}
			/* to end */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				l.splice( l.begin(), r, r.end() );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-beginning failed to remove elem", _stringifier.to_string<char>( r ), "23456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-beginning failed", _stringifier.to_string<char>( l ), "abcdefghi1" );
			}
			/* to middle */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator to( l.begin() );
				advance( to, 4 );
				l.splice( to, r, r.begin() );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-beginning failed to remove elem", _stringifier.to_string<char>( r ), "23456789" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-end src-beginning failed", _stringifier.to_string<char>( l ), "abcd1efghi" );
			}
		}
		/* long end */ {
			/* to beg */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, r.size() - 1 );
				l.splice( l.begin(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed to remove elem", _stringifier.to_string<char>( r ), "12345678" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "9abcdefghi" );
			}
			/* to end */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, r.size() - 1 );
				l.splice( l.begin(), r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed to remove elem", _stringifier.to_string<char>( r ), "12345678" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "abcdefghi9" );
			}
			/* to middle */ {
				list_t l( from_string( "abcdefghi" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator it( r.begin() );
				advance( it, r.size() - 1 );
				list_t::iterator to( l.begin() );
				advance( to, 4 );
				l.splice( to, r, it );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed to remove elem", _stringifier.to_string<char>( r ), "12345678" );
				ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "abcd9efghi" );
			}
		}
	}
	/* from small (size == 1) to normal */ {
		list_t l( from_string( "abcdefghi" ) );
		list_t r( from_string( "1" ) );
		l.splice( l.begin(), r, r.begin() );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list, elem) small-dst-beg src-middle failed to remove elem", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list, elem) small-dst-beg src-middle failed", _stringifier.to_string<char>( l ), "1abcdefghi" );
	}
	/* self splice */ {
		/* to same point */ {
			list_t l( from_string( "123456789" ) );
			list_t::iterator from( l.begin() );
			list_t::iterator to( l.begin() );
			advance( from, 2 );
			advance( to, 2 );
			l.splice( to, l, from );
			check_consistency( l );
			ENSURE_EQUALS( "splice(pos, list, elem) self same point failed", _stringifier.to_string<char>( l ), "123456789" );
		}
		/* to next point */ {
			list_t l( from_string( "123456789" ) );
			list_t::iterator from( l.begin() );
			list_t::iterator to( l.begin() );
			advance( from, 2 );
			advance( to, 3 );
			l.splice( to, l, from );
			check_consistency( l );
			ENSURE_EQUALS( "splice(pos, list, elem) self next point failed", _stringifier.to_string<char>( l ), "123456789" );
		}
		/* to previous point */ {
			list_t l( from_string( "123456789" ) );
			list_t::iterator from( l.begin() );
			list_t::iterator to( l.begin() );
			advance( from, 3 );
			advance( to, 2 );
			l.splice( to, l, from );
			check_consistency( l );
			ENSURE_EQUALS( "splice(pos, list, elem) self previous point failed", _stringifier.to_string<char>( l ), "124356789" );
		}
		/* to head */ {
			list_t l( from_string( "123456789" ) );
			list_t::iterator from( l.begin() );
			list_t::iterator to( l.begin() );
			advance( from, 3 );
			l.splice( to, l, from );
			check_consistency( l );
			ENSURE_EQUALS( "splice(pos, list, elem) self to head failed", _stringifier.to_string<char>( l ), "412356789" );
		}
		/* from head */ {
			list_t l( from_string( "123456789" ) );
			list_t::iterator from( l.begin() );
			list_t::iterator to( l.begin() );
			advance( to, 3 );
			l.splice( to, l, from );
			check_consistency( l );
			ENSURE_EQUALS( "splice(pos, list, elem) self from head failed", _stringifier.to_string<char>( l ), "231456789" );
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 29, "splice( pos, list, fist, last )" )
	/* from empty to empty */ {
		list_t l;
		list_t r;
		l.splice( l.begin(), r, r.begin(), r.end() );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list, f, l) failed (src)", r.is_empty() );
		ENSURE( "splice(pos, list, f, l) failed (dst)", l.is_empty() );
	}
	/* from empty */ {
		list_t l( from_string( "123" ) );
		list_t r;
		l.splice( l.begin(), r, r.begin(), r.end() );
		check_consistency( l );
		check_consistency( r );
		ENSURE( "splice(pos, list, f, l) failed (src)", r.is_empty() );
		ENSURE_EQUALS( "splice(pos, list, f, l) from empty failed", _stringifier.to_string<char>( l ), "123" );
	}
	/* to empty */ {
		/* long middle */ {
			list_t l;
			list_t r( from_string( "123456789" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( f, 2 );
			advance( f, r.size() - 2 );
			l.splice( l.begin(), r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) empty-dst-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
			ENSURE_EQUALS( "splice(pos, list, f, l) empty-dst-middle failed", _stringifier.to_string<char>( l ), "34567" );
		}
		/* long beginning */ {
			list_t l;
			list_t r( from_string( "123456789" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( f, r.size() - 4 );
			l.splice( l.begin(), r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) empty-dst-beginning failed to remove chunk", _stringifier.to_string<char>( r ), "6789" );
			ENSURE_EQUALS( "splice(pos, list, f, l) empty-dst-beginning failed", _stringifier.to_string<char>( l ), "12345" );
		}
		/* long end */ {
			list_t l;
			list_t r( from_string( "123456789" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.end() );
			advance( f, 4 );
			l.splice( l.begin(), r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) empty-dst-end failed to remove chunk", _stringifier.to_string<char>( r ), "12345" );
			ENSURE_EQUALS( "splice(pos, list, f, l) empty-dst-end failed", _stringifier.to_string<char>( l ), "6789" );
		}
	}
	/* to small (size == 1) */ {
		/* to begin */ {
			/* long middle */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, 2 );
				advance( f, r.size() - 2 );
				l.splice( l.begin(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-middle to empty failed", _stringifier.to_string<char>( l ), "345670" );
			}
			/* long beginning */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, r.size() - 4 );
				l.splice( l.begin(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-beginning failed to remove chunk", _stringifier.to_string<char>( r ), "6789" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-beginning to empty failed", _stringifier.to_string<char>( l ), "123450" );
			}
			/* long end */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.end() );
				advance( f, 4 );
				l.splice( l.begin(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-end failed to remove chunk", _stringifier.to_string<char>( r ), "12345" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "67890" );
			}
		}
		/* to end */ {
			/* long middle */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, 2 );
				advance( f, r.size() - 2 );
				l.splice( l.end(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-middle to empty failed", _stringifier.to_string<char>( l ), "034567" );
			}
			/* long beginning */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, r.size() - 4 );
				l.splice( l.end(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-beginning failed to remove chunk", _stringifier.to_string<char>( r ), "6789" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-beginning to empty failed", _stringifier.to_string<char>( l ), "012345" );
			}
			/* long end */ {
				list_t l( from_string( "0" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.end() );
				advance( f, 4 );
				l.splice( l.end(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-end failed to remove chunk", _stringifier.to_string<char>( r ), "12345" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-end failed", _stringifier.to_string<char>( l ), "06789" );
			}
		}
	}
	/* to small (size == 2) */ {
		/* to begin */ {
			/* long middle */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, 2 );
				advance( f, r.size() - 2 );
				l.splice( l.begin(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-middle to empty failed", _stringifier.to_string<char>( l ), "345670a" );
			}
			/* long beginning */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, r.size() - 4 );
				l.splice( l.begin(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-beginning failed to remove chunk", _stringifier.to_string<char>( r ), "6789" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-beginning to empty failed", _stringifier.to_string<char>( l ), "123450a" );
			}
			/* long end */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.end() );
				advance( f, 4 );
				l.splice( l.begin(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-end failed to remove chunk", _stringifier.to_string<char>( r ), "12345" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-beg src-end failed", _stringifier.to_string<char>( l ), "67890a" );
			}
		}
		/* to end */ {
			/* long middle */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, 2 );
				advance( f, r.size() - 2 );
				l.splice( l.end(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-middle to empty failed", _stringifier.to_string<char>( l ), "0a34567" );
			}
			/* long beginning */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, r.size() - 4 );
				l.splice( l.end(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-beginning failed to remove chunk", _stringifier.to_string<char>( r ), "6789" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-beginning to empty failed", _stringifier.to_string<char>( l ), "0a12345" );
			}
			/* long end */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.end() );
				advance( f, 4 );
				l.splice( l.end(), r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-end failed to remove chunk", _stringifier.to_string<char>( r ), "12345" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-end src-end failed", _stringifier.to_string<char>( l ), "0a6789" );
			}
		}
		/* to middle */ {
			/* long middle */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, 2 );
				advance( f, r.size() - 2 );
				list_t::iterator it( l.begin() );
				++ it;
				l.splice( it, r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-mid src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-mid src-middle to empty failed", _stringifier.to_string<char>( l ), "034567a" );
			}
			/* long beginning */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.begin() );
				advance( f, r.size() - 4 );
				list_t::iterator it( l.begin() );
				++ it;
				l.splice( it, r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-mid src-beginning failed to remove chunk", _stringifier.to_string<char>( r ), "6789" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-mid src-beginning to empty failed", _stringifier.to_string<char>( l ), "012345a" );
			}
			/* long end */ {
				list_t l( from_string( "0a" ) );
				list_t r( from_string( "123456789" ) );
				list_t::iterator f( r.begin() );
				list_t::iterator e( r.end() );
				advance( f, 4 );
				list_t::iterator it( l.begin() );
				++ it;
				l.splice( it, r, f, e );
				check_consistency( l );
				check_consistency( r );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-mid src-end failed to remove chunk", _stringifier.to_string<char>( r ), "12345" );
				ENSURE_EQUALS( "splice(pos, list, f, l) small-dst-mid src-end failed", _stringifier.to_string<char>( l ), "06789a" );
			}
		}
	}
	/* to large */ {
		/* to begining */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "123456789" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( f, 2 );
			advance( f, r.size() - 2 );
			l.splice( l.begin(), r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg src-middle failed", _stringifier.to_string<char>( l ), "34567abcdefghi" );
		}
		/* to end */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "123456789" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( f, 2 );
			advance( f, r.size() - 2 );
			l.splice( l.end(), r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg src-middle failed", _stringifier.to_string<char>( l ), "abcdefghi34567" );
		}
		/* to middle */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "123456789" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( f, 2 );
			advance( f, r.size() - 2 );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg src-middle failed to remove chunk", _stringifier.to_string<char>( r ), "1289" );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg src-middle failed", _stringifier.to_string<char>( l ), "abcd34567efghi" );
		}
	}
	/* from small (size == 2) */ {
		/* from begining */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "12" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( e, 1 );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-src-beg failed to remove chunk", _stringifier.to_string<char>( r ), "2" );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-src-beg failed", _stringifier.to_string<char>( l ), "abcd1efghi" );
		}
		/* from end */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "12" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.end() );
			advance( f, 1 );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-src-beg failed to remove chunk", _stringifier.to_string<char>( r ), "1" );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-src-beg failed", _stringifier.to_string<char>( l ), "abcd2efghi" );
		}
		/* whole */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "12" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.end() );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE( "splice(pos, list, f, l) large-dst-beg small-whole failed to remove chunk", r.is_empty() );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-whole failed", _stringifier.to_string<char>( l ), "abcd12efghi" );
		}
	}
	/* from small (size == 1) */ {
		/* whole */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "1" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.end() );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE( "splice(pos, list, f, l) large-dst-beg small-whole failed to remove chunk", r.is_empty() );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-whole failed", _stringifier.to_string<char>( l ), "abcd1efghi" );
		}
	}
	/* from small (size == 3) */ {
		/* nothing */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "123" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.begin() );
			advance( f, 1 );
			advance( e, 1 );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-src-beg failed to remove chunk", _stringifier.to_string<char>( r ), "123" );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-whole failed", _stringifier.to_string<char>( l ), "abcdefghi" );
		}
		/* all */ {
			list_t l( from_string( "abcdefghi" ) );
			list_t r( from_string( "123" ) );
			list_t::iterator f( r.begin() );
			list_t::iterator e( r.end() );
			list_t::iterator it( l.begin() );
			advance( it, 4 );
			l.splice( it, r, f, e );
			check_consistency( l );
			check_consistency( r );
			ENSURE( "splice(pos, list, f, l) large-dst-beg small-whole failed to remove chunk", r.is_empty() );
			ENSURE_EQUALS( "splice(pos, list, f, l) large-dst-beg small-whole failed", _stringifier.to_string<char>( l ), "abcd123efghi" );
		}
	}
	/* bad iterator on destination */ {
		list_t l;
		list_t r;
		try {
			l.splice( r.begin(), r, r.begin(), r.end() );
			FAIL( "out of the blue destination iterator accepted" );
		} catch ( HFailedAssertion const& ) {
			/* ok */
		}
	}
	/* bad iterator on source (f) */ {
		list_t l;
		list_t r;
		try {
			l.splice( l.begin(), r, l.begin(), r.end() );
			FAIL( "out of the blue source (f) iterator accepted" );
		} catch ( HFailedAssertion const& ) {
			/* ok */
		}
	}
	/* bad iterator on source (l) */ {
		list_t l;
		list_t r;
		try {
			l.splice( l.begin(), r, r.begin(), l.end() );
			FAIL( "out of the blue source (l) iterator accepted" );
		} catch ( HFailedAssertion const& ) {
			/* ok */
		}
	}
	/* self splice */ {
		list_t l;
		list_t r;
		try {
			l.splice( l.begin(), l, r.begin(), r.end() );
			FAIL( "self splice accepted" );
		} catch ( HException const& ) {
			/* ok */
		}
#if 0
		/* when allowed */ {
			list_t l( from_string( "123456789" ) );
			list_t::iterator i1( l.begin() );
			list_t::iterator i2( l.begin() );
			list_t::iterator i3( l.begin() );
			advance( i1, 2 );
			advance( i2, 5 );
			advance( i3, r.size() - 2 );
			l.splice( i1, l, i2, i3 );
			check_consistency( l );
			ENSURE_EQUALS( "self splice(pos, list, f, l) failed", _stringifier.to_string<char>( l ), "126734589" );
		}
#endif
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 30, "remove( elem )" )
	/* random */ {
		list_t l( from_string( "5165377774891237589347583475891347591347907787123456789" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE_EQUALS( "random remove failed", _stringifier.to_string<char>( l ), "516534891235893458345891345913490812345689" );
	}
	/* from begining */ {
		list_t l( from_string( "7777489123" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE_EQUALS( "remove from begining failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* from begining (1) */ {
		list_t l( from_string( "7489123" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE_EQUALS( "remove from begining failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* from end */ {
		list_t l( from_string( "4891237777" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE_EQUALS( "remove from end failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* from end (1) */ {
		list_t l( from_string( "4891237" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE_EQUALS( "remove from end failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* all */ {
		list_t l( from_string( "777" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE( "remove from end failed", l.is_empty() );
	}
	/* none */ {
		list_t l( from_string( "489123" ) );
		l.remove( '7' );
		check_consistency( l );
		ENSURE_EQUALS( "remove from end failed", _stringifier.to_string<char>( l ), "489123" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 31, "remove_if( cond )" )
	/* random */ {
		list_t l( from_string( "5165377774891237589347583475891347591347907787123456789" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE_EQUALS( "random remove failed", _stringifier.to_string<char>( l ), "516534891235893458345891345913490812345689" );
	}
	/* from begining */ {
		list_t l( from_string( "7777489123" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE_EQUALS( "remove from begining failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* from begining (1) */ {
		list_t l( from_string( "7489123" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE_EQUALS( "remove from begining failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* from end */ {
		list_t l( from_string( "4891237777" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE_EQUALS( "remove from end failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* from end (1) */ {
		list_t l( from_string( "4891237" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE_EQUALS( "remove from end failed", _stringifier.to_string<char>( l ), "489123" );
	}
	/* all */ {
		list_t l( from_string( "777" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE( "remove from end failed", l.is_empty() );
	}
	/* none */ {
		list_t l( from_string( "489123" ) );
		l.remove_if( bind1st( equal_to<int>(), '7' ) );
		check_consistency( l );
		ENSURE_EQUALS( "remove from end failed", _stringifier.to_string<char>( l ), "489123" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 32, "unique()" )
	/* on sorted */ {
		char data[] = "5165377774891237589347583475891347591347907787123456789";
		list_t l( from_string( data ) );
		l.sort();
		check_consistency( l );
		l.unique();
		check_consistency( l );
		ENSURE_EQUALS( "sorted unique failed", _stringifier.to_string<char>( l ), "0123456789" );
	}
	/* on uniform */ {
		list_t l( from_string( "0000000000000000000" ) );
		l.unique();
		check_consistency( l );
		ENSURE_EQUALS( "uniform unique failed", _stringifier.to_string<char>( l ), "0" );
	}
	/* on random */ {
		list_t l( from_string( "00239908822309955000234772327798823337700222787755788234579772238877234099900222" ) );
		l.unique();
		check_consistency( l );
		ENSURE_EQUALS( "random unique failed", _stringifier.to_string<char>( l ), "023908230950234723279823702787578234579723872340902" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 33, "reverse()" )
	char data[] = "5165377774891237589347583475891347591347907787123456789";
	list_t l( from_string( data ) );
	list_t::iterator it( l.begin() );
	int const val( *it );
	l.reverse();
	check_consistency( l );
	reverse( data, data + ( countof ( data ) - 1 ) );
	ENSURE_EQUALS( "reverse failed", _stringifier.to_string<char>( l ), data );
	ENSURE_EQUALS( "reverse preserving iterators failed", *it, val );
TUT_TEARDOWN()

TUT_UNIT_TEST( 50, "speed test" )
	TIME_CONSTRAINT_EXEMPT();
	typedef std::list<int> proto_t;
	typedef HList<int> list_type;
	proto_t proto;
	list_type list;
	double long stPush( 0 );
	double long stPop( 0 );
	double long yt( 0 );
	int long LOOPS( 1000000 ); {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.push_back( static_cast<int>( i ) );
		clog << "*speed* std::list<>::push_back() = " << static_cast<int long>( stPush = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	} {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			list.push_back( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HList<>::push_back() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	}
	clog << "*speed* HList<>::push_back() result = " << ( ( stPush > yt ) ? green : red ) << ( yt / stPush ) << lightgray << endl; {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			proto.pop_back();
		clog << "*speed* std::list<>::pop_back() = " << static_cast<int long>( stPop = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	} {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			list.pop_back();
		clog << "*speed* yaal::hcore::HList<>::pop_back() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	}
	clog << "*speed* HList<>::pop_back() result = " << ( ( stPop > yt ) ? green : red ) << ( yt / stPop ) << lightgray << endl;
	typedef HList<int, allocator::pool<int> > list_on_pool_type;
	list_on_pool_type listOnPool; {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			listOnPool.push_back( static_cast<int>( i ) );
		clog << "*speed* yaal::hcore::HList<on_pool>::push_back() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	}
	clog << "*speed* HList<on_pool>::push_back() result = " << ( ( stPush > yt ) ? green : red ) << ( yt / stPush ) << lightgray << endl; {
		HClock c;
		for ( int long i( 0 ); i < LOOPS; ++ i )
			listOnPool.pop_back();
		clog << "*speed* yaal::hcore::HList<on_pool>::pop_back() = " << static_cast<int long>( yt = c.get_time_elapsed( HClock::UNIT::MILISECOND ) ) << endl;
	}
	clog << "*speed* HList<on_pool>::pop_back() result = " << ( ( stPop > yt ) ? green : red ) << ( yt / stPop ) << lightgray << endl;
TUT_TEARDOWN()

}


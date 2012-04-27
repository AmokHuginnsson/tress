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


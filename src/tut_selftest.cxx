/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_selftest.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"
#include "tut_selftest.hxx"

using namespace tut;
using namespace std;
using namespace tress::tut_helpers;

namespace tut {

struct SelfTestManager {
	typedef void (*callback_t)( int, char const* );
	struct test_info {
		callback_t _callback;
		int _no;
		char const* _title;
		test_info( callback_t callback_, int no_, char const* title_ )
			: _callback( callback_ ), _no( no_ ), _title( title_ ) {}
		test_info( test_info const& ti_ )
			: _callback( ti_._callback ), _no( ti_._no ), _title( ti_._title ) {}
		test_info& operator = ( test_info const& ti_ ) {
			if ( &ti_ != this ) {
				_callback = ti_._callback;
				_no = ti_._no;
				_title = ti_._title;
			}
			return ( *this );
		}
	};
	typedef std::vector<test_info> registrators_t;
	registrators_t _registrators;
	SelfTestManager( void )
		: _registrators() {}
	void register_all( void ) {
		for ( registrators_t::iterator it( _registrators.begin() ), end( _registrators.end() ); it != end; ++ it )
			it->_callback( it->_no, it->_title );
	}
	int register_test( callback_t callback_, int no_, char const* title_ ) {
		_registrators.push_back( test_info( callback_, no_, title_ ) );
		return ( SelfTestManager::DISABLE_OPT );
	}
	static int volatile DISABLE_OPT;
} selfTestManager;

}

namespace tress {

void register_selftest( void ) {
	selfTestManager.register_all();
}

}

namespace tut {

int volatile SelfTestManager::DISABLE_OPT = 0;

#undef TUT_SIMPLE_MOCK
#define TUT_SIMPLE_MOCK( name ) \
struct name : public simple_mock<name> { \
	virtual ~name( void ) \
		{} \
}

#undef TUT_TEST_GROUP
#define TUT_TEST_GROUP( mock, name ) \
typedef test_group<mock> mock##_group; \
typedef mock##_group::object mock##_module; \
namespace { \
mock##_group& mock##_instance( void ) { \
	static mock##_group group_instance( ( name ) ); \
	return ( group_instance ); \
} \
void register_test_##mock( int no, char const* title ) { \
	mock##_instance().register_test( no, title ); \
} \
} \
typedef void void_type

#undef TUT_UNIT_TEST
#define TUT_UNIT_TEST( suite, no, title ) \
namespace { static int const M_CONCAT( dropIt, __LINE__ ) __attribute__(( __used__ )) = selfTestManager.register_test( &register_test_##suite, no, title ); } \
template<> template<> void suite##_module::test<(no)>( void ) { do { set_test_meta( title, __FILE__, __LINE__ ); } while ( 0 );

TUT_SIMPLE_MOCK( tut_selftest_one );
TUT_TEST_GROUP( tut_selftest_one, "::selftest::one" );

TUT_UNIT_TEST( tut_selftest_one, 1, "first test" )
	ENSURE_EQUALS( "life, universe and everything else", 42, 42 );
TUT_TEARDOWN()

TUT_UNIT_TEST( tut_selftest_one, 2, "equality test" )
	ENSURE_EQUALS( "days in a week", 6, 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( tut_selftest_one, 3, "safe test" )
	throw std::runtime_error( "severe problem" );
TUT_TEARDOWN()

TUT_SIMPLE_MOCK( tut_selftest_two );
TUT_TEST_GROUP( tut_selftest_two, "::selftest::two" );

TUT_UNIT_TEST( tut_selftest_two, 1, "first test" )
TUT_TEARDOWN()

TUT_UNIT_TEST( tut_selftest_two, 2, "second test" )
TUT_TEARDOWN()

TUT_SIMPLE_MOCK( tut_selftest_three );
TUT_TEST_GROUP( tut_selftest_three, "::selftest::three" );

TUT_UNIT_TEST( tut_selftest_three, 1, "first test" )
TUT_TEARDOWN()

TUT_UNIT_TEST( tut_selftest_three, 2, "second test" )
TUT_TEARDOWN()

}


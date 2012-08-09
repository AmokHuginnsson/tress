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
		test_info& operator = ( test_info const& );
	};
	typedef std::vector<test_info> registrators_t;
	registrators_t _registrators;
	SelfTestManager( void )
		: _registrators() {}
	void register_selftest( void ) {
		for ( registrators_t::iterator it( _registrators.begin() ), end( _registrators.end() ); it != end; ++ it )
			it->_callback( it->_no, it->_title );
	}
	int register_test( callback_t callback_, int no_, char const* title_ ) {
		_registrators.push_back( test_info( callback_, no_, title_ ) );
		return ( SelfTestManager::DISABLE_OPT );
	}
	static int volatile DISABLE_OPT;
} selfTestManager;

int volatile SelfTestManager::DISABLE_OPT = 0;

#undef TUT_TEST_GROUP
#define TUT_TEST_GROUP( mock, name ) \
namespace mock##_namespace { \
namespace { \
typedef test_group<mock> group; \
typedef group::object module; \
group& instance( void ) { \
	static group group_instance( ( name ) ); \
	return ( group_instance ); \
} \
void register_test( int no, char const* title ) { \
	instance().register_test( no, title ); \
} \
typedef void void_type

#define TUT_TEST_GROUP_TEARDOWN() } }

#undef TUT_UNIT_TEST
#define TUT_UNIT_TEST( no, title ) \
namespace { static int const M_CONCAT( dropIt, __LINE__ ) __attribute__(( __used__ )) = selfTestManager.register_test( &register_test, no, title ); } \
template<> template<> void module::test<(no)>( void ) { do { set_test_meta( title, __FILE__, __LINE__ ); } while ( 0 );


TUT_SIMPLE_MOCK( tut_selftest );
TUT_TEST_GROUP( tut_selftest, "::selftest::one" );

TUT_UNIT_TEST( 1, "first test" )
TUT_TEARDOWN()

TUT_TEST_GROUP_TEARDOWN()

}


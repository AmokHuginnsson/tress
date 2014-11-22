/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hsbbstree.cxx - this file is integral part of `tress' project.

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

#include <yaal/hcore/hexception.hxx>

#define private public
#define protected public
#include <yaal/hcore/hset.hxx>
#undef protected
#undef private

#include <TUT/tut.hpp>

#include <yaal/hcore/hrandomizer.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hcore_hsbbstree.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hsbbstree : public tress::tut_helpers::simple_mock<tut_yaal_hcore_hsbbstree> {
	typedef tress::tut_helpers::simple_mock<tut_yaal_hcore_hsbbstree> base_type;
	static int const NUMBER_OF_TEST_NODES = 1000;
	static int const KEY_POOL_SIZE = 30000;
	tut_yaal_hcore_hsbbstree( void )
		: base_type(), _testedNodes( 0 ), _blackHeight( 0 ), _redNodeExists( false ), _blackNodeExists( false ), _root( NULL )
		{}
	virtual ~tut_yaal_hcore_hsbbstree( void )
		{}
	typedef yaal::hcore::HSet<int> set_t;
	typedef set_t::engine_t engine_t;
	void helper_stress_test_insert( set_t&, int );
	void helper_stress_test_erase( set_t&, int );
	void verify( set_t& );
	bool self_test( set_t& );
	bool integrity_test( set_t& );
	bool definition_test( set_t& );

	int long _testedNodes;
	int _blackHeight;
	bool _redNodeExists;
	bool _blackNodeExists;
	engine_t::HAbstractNode* _root;
	void init( set_t& );

	void helper_test_node_integrity( engine_t::HAbstractNode* );
	void helper_test_node_definition( engine_t::HAbstractNode* );
	int helper_count_exemplar_black_height( engine_t::HAbstractNode* );
	int helper_check_black_height( engine_t::HAbstractNode* );

	typedef set_t::insert_result (set_t::*set_insert_t)( int const& );
private:
	tut_yaal_hcore_hsbbstree( tut_yaal_hcore_hsbbstree const& );
	tut_yaal_hcore_hsbbstree& operator = ( tut_yaal_hcore_hsbbstree const& );
};

void tut_yaal_hcore_hsbbstree::init( set_t& ob ) {
	_testedNodes = 0;
	_blackHeight = 0;
	_redNodeExists = false;
	_blackNodeExists = false;
	_root = ob._engine._root;
}

void tut_yaal_hcore_hsbbstree::helper_test_node_integrity( engine_t::HAbstractNode* n ) {
	if ( ! n->_parent && ( n != _root ) )
		FAIL( "node with null parent is not root" );
	if ( n->_parent && ( n->_parent->_left != n ) && ( n->_parent->_right != n ) )
		FAIL( "parent node does not know about this node" );
	if ( n->_left ) {
		if ( n->_left->_parent != n )
			FAIL( "child node does not know about its parent (this node)" );
		helper_test_node_integrity( n->_left );
	}
	if ( n->_right ) {
		if ( n->_right->_parent != n )
			FAIL( "child node does not know about its parent (this node)" );
		helper_test_node_integrity( n->_right );
	}
	++ _testedNodes;
}

void tut_yaal_hcore_hsbbstree::helper_test_node_definition( engine_t::HAbstractNode* n ) {
	if ( n->_color == engine_t::HAbstractNode::RED ) {
		_redNodeExists = true;
		if ( ( n->_left && ( n->_left->_color == engine_t::HAbstractNode::RED ) )
				|| ( n->_right && ( n->_right->_color == engine_t::HAbstractNode::RED ) ) )
			FAIL( "subsequent red nodes" );
	} else
		_blackNodeExists = true;
	if ( n->_left )
		helper_test_node_definition( n->_left );
	if ( n->_right )
		helper_test_node_definition( n->_right );
	if ( ! ( n->_left || n->_right ) ) {
		if ( helper_check_black_height( n ) != _blackHeight )
			FAIL( "black height is not the same for all the nodes" );
	}
}

int tut_yaal_hcore_hsbbstree::helper_count_exemplar_black_height( engine_t::HAbstractNode* n ) {
	int bh = 0;
	while ( n ) {
		if ( n->_color == engine_t::HAbstractNode::BLACK )
			++ bh;
		n = n->_left;
	}
//	cout << bh << " ";
	return ( bh );
}

int tut_yaal_hcore_hsbbstree::helper_check_black_height( engine_t::HAbstractNode* n ) {
	int bh = 0;
	while ( n ) {
		if ( n->_color == engine_t::HAbstractNode::BLACK )
			++ bh;
		n = n->_parent;
	}
	return ( bh );
}

bool tut_yaal_hcore_hsbbstree::self_test( set_t& ob ) {
	init( ob );
	if ( _root == _root->_left )
		return ( true );
	if ( _root == _root->_right )
		return ( true );
	if ( _root == _root->_parent )
		return ( true );
	if ( _root->_left && ( _root->_left->_parent != _root ) )
		return ( true );
	if ( _root->_right && ( _root->_right->_parent != _root ) )
		return ( true );
	return ( false );
}

bool tut_yaal_hcore_hsbbstree::integrity_test( set_t& ob ) {
	init( ob );
	helper_test_node_integrity( _root );
	ENSURE_EQUALS( "quantity inconsistency", ob._engine._size, _testedNodes );
	return ( false );
}

bool tut_yaal_hcore_hsbbstree::definition_test( set_t& ob ) {
	init( ob );
	if ( _root->_color != engine_t::HAbstractNode::BLACK )
		FAIL ( "root is not black" );
	_blackHeight = helper_count_exemplar_black_height( _root );
	helper_test_node_definition( _root );
//	if ( _redNodeExists )
//		cout << "R";
	return ( false );
}

void tut_yaal_hcore_hsbbstree::helper_stress_test_insert( set_t& ob, int val ) {
	helper_stress_just_insert( ob, val );
	verify( ob );
}

void tut_yaal_hcore_hsbbstree::helper_stress_test_erase( set_t& ob, int val ) {
	helper_stress_just_erase( ob, val );
	verify( ob );
}

void tut_yaal_hcore_hsbbstree::verify( set_t& ob ) {
	ENSURE( "self test failed", ! self_test( ob ) );
	ENSURE( "integrity test failed", ! integrity_test( ob ) );
	ENSURE( "definition test failed", ! definition_test( ob ) );
	int biggest = - 1;
	for ( set_t::HIterator it = ob.begin(); it != ob.end(); ++ it ) {
		ENSURE( "elements not in order", *it > biggest );
		biggest = *it;
	}
	return;
}

TUT_TEST_GROUP( tut_yaal_hcore_hsbbstree, "yaal::hcore::HSBBSTree" );

TUT_UNIT_TEST( "Adding keys in ascending order." )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test_insert( s, i );
	ENSURE( "no red nodes were generated during the test", tut_yaal_hcore_hsbbstree::_redNodeExists );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Adding keys in descending order." )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		helper_stress_test_insert( s, i );
	ENSURE( "no red nodes were generated during the test", tut_yaal_hcore_hsbbstree::_redNodeExists );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Adding keys in random order." )
	HRandomizer r;
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test_insert( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
	ENSURE( "no red nodes were generated during the test", tut_yaal_hcore_hsbbstree::_redNodeExists );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in ascending order from lower half of the tree that was created by adding keys in ascending order." )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_just_insert( s, i );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in ascending order from upper half of the tree that was created by adding keys in ascending order." )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_just_insert( s, i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in descending order from lower half of the tree that was created by adding keys in ascending order." )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_just_insert( s, i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in descending order from upper half of the tree that was created by adding keys in ascending order." )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_just_insert( s, i );
	for ( int i = NUMBER_OF_TEST_NODES - 1; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in ascending order from lower half of the tree that was created by adding keys in descending order." )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		helper_stress_just_insert( s, i );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in ascending order from upper half of the tree that was created by adding keys in descending order." )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		helper_stress_just_insert( s, i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in descending order from lower half of the tree that was created by adding keys in descending order." )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		helper_stress_just_insert( s, i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in descending order from upper half of the tree that was created by adding keys in descending order." )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		helper_stress_just_insert( s, i );
	for ( int i = NUMBER_OF_TEST_NODES; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		helper_stress_test_erase( s, i );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in ascending order from lower half of the tree that was created by adding keys in random order." )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		helper_stress_just_insert( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i ) {
		try {
			helper_stress_test_erase( s, i );
		} catch ( HException const& e ) {
			if ( e.code() != static_cast<int>( engine_t::ERROR::NON_EXISTING_KEY ) )
				throw;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in ascending order from upper half of the tree that was created by adding keys in random order." )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		helper_stress_just_insert( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i ) {
		try {
			helper_stress_test_erase( s, i );
		} catch ( HException const& e ) {
			if ( e.code() != static_cast<int>( engine_t::ERROR::NON_EXISTING_KEY ) )
				throw;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in descending order from lower half of the tree that was created by adding keys in random order." )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		helper_stress_just_insert( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i ) {
		try {
			helper_stress_test_erase( s, i );
		} catch ( HException const& e ) {
			if ( e.code() != static_cast<int>( engine_t::ERROR::NON_EXISTING_KEY ) )
				throw;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in descending order from upper half of the tree that was created by adding keys in random order." )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		helper_stress_just_insert( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
	for ( int i = NUMBER_OF_TEST_NODES; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i ) {
		try {
			helper_stress_test_erase( s, i );
		} catch ( HException const& e ) {
			if ( e.code() != static_cast<int>( engine_t::ERROR::NON_EXISTING_KEY ) )
				throw;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "Removing keys in random order from upper half of the tree that was created by adding keys in random order." )
	TIME_CONSTRAINT_EXEMPT();
	HRandomizer r;
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_just_insert( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i ) {
		try {
			helper_stress_test_erase( s, static_cast<int>( r( KEY_POOL_SIZE ) ) );
		} catch ( HException const& e ) {
			if ( e.code() != static_cast<int>( engine_t::ERROR::NON_EXISTING_KEY ) )
				throw;
		}
	}
TUT_TEARDOWN()

#if 0
#endif

}


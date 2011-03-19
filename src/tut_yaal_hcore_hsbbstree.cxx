/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hsbbstree.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#include <yaal/yaal.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress::tut_helpers;

namespace tut
{

struct red_black_tree_stress_test
	{
	red_black_tree_stress_test( void )
		: root( NULL ), quantity( 0 ), tested_nodes( 0 ), black_height( 0 )
		{}
	virtual ~red_black_tree_stress_test( void ) {}
	struct node
		{
		typedef enum { red, black } color_t;
		void* nil;
		color_t color;
		node* parent;
		node* left;
		node* right;
		};
	node* root;
	int long quantity;
	template<typename T>
	bool self_test( HSet<T>& );
	template<typename T>
	bool integrity_test( HSet<T>& );
	template<typename T>
	bool definition_test( HSet<T>& );

	static bool red_node_exists;
	static bool black_node_exists;
private:
	int long tested_nodes;
	int black_height;
	template<typename T>
	void init( HSet<T>& );

	void helper_test_node_integrity( node* );
	void helper_test_node_definition( node* );
	int helper_count_exemplar_black_height( node* );
	int helper_check_black_height( node* );
private:
	red_black_tree_stress_test( red_black_tree_stress_test const& );
	red_black_tree_stress_test& operator = ( red_black_tree_stress_test const& );
	};

bool red_black_tree_stress_test::red_node_exists = false;
bool red_black_tree_stress_test::black_node_exists = false;

template<typename T>
void red_black_tree_stress_test::init( HSet<T>& ob )
	{
	red_black_tree_stress_test* hack = reinterpret_cast<red_black_tree_stress_test*> ( &ob );
	tested_nodes = 0;
	black_height = 0;
	red_node_exists = false;
	black_node_exists = false;
	root = hack->root;
	quantity = hack->quantity;
	}

void red_black_tree_stress_test::helper_test_node_integrity( node* n )
	{
	if ( ! n->parent && ( n != root ) )
		FAIL( "node with null parent is not root" );
	if ( n->parent && ( n->parent->left != n ) && ( n->parent->right != n ) )
		FAIL( "parent node does not know about this node" );
	if ( n->left )
		{
		if ( n->left->parent != n )
			FAIL( "child node does not know about its parent (this node)" );
		helper_test_node_integrity ( n->left );
		}
	if ( n->right )
		{
		if ( n->right->parent != n )
			FAIL( "child node does not know about its parent (this node)" );
		helper_test_node_integrity ( n->right );
		}
	++ tested_nodes;
	}

void red_black_tree_stress_test::helper_test_node_definition( node* n )
	{
	if ( n->color == node::red )
		{
		red_node_exists = true;
		if ( ( n->left && ( n->left->color == node::red ) )
				|| ( n->right && ( n->right->color == node::red ) ) )
			FAIL( "subsequent red nodes" );
		}
	else
		black_node_exists = true;
	if ( n->left )
		helper_test_node_definition( n->left );
	if ( n->right )
		helper_test_node_definition( n->right );
	if ( ! ( n->left || n->right ) )
		{
		if ( helper_check_black_height( n ) != black_height )
			FAIL( "black height is not the same for all the nodes" );
		}
	}

int red_black_tree_stress_test::helper_count_exemplar_black_height( node* n )
	{
	int bh = 0;
	while ( n )
		{
		if ( n->color == node::black )
			++ bh;
		n = n->left;
		}
//	cout << bh << " ";
	return ( bh );
	}

int red_black_tree_stress_test::helper_check_black_height( node* n )
	{
	int bh = 0;
	while ( n )
		{
		if ( n->color == node::black )
			++ bh;
		n = n->parent;
		}
	return ( bh );
	}

template<typename T>
bool red_black_tree_stress_test::self_test( HSet<T>& ob )
	{
	init( ob );
	if ( ob.size() != quantity )
		return ( true );
	if ( root == root->left )
		return ( true );
	if ( root == root->right )
		return ( true );
	if ( root == root->parent )
		return ( true );
	if ( root->left && ( root->left->parent != root ) )
		return ( true );
	if ( root->right && ( root->right->parent != root ) )
		return ( true );
	return ( false );
	}

template<typename T>
bool red_black_tree_stress_test::integrity_test( HSet<T>& ob )
	{
	init( ob );
	helper_test_node_integrity ( root );
	ENSURE_EQUALS( "quantity inconsistency", quantity, tested_nodes );
	return ( false );
	}

template<typename T>
bool red_black_tree_stress_test::definition_test( HSet<T>& ob )
	{
	init( ob );
	if ( root->color != node::black )
		FAIL ( "root is not black" );
	black_height = helper_count_exemplar_black_height( root );
	helper_test_node_definition( root );
//	if ( red_node_exists )
//		cout << "R";
	return ( false );
	}

struct tut_yaal_hcore_hsbbstree
	{
	static int const NUMBER_OF_TEST_NODES = 1000;
	static int const KEY_POOL_SIZE = 30000;
	red_black_tree_stress_test stress;
	tut_yaal_hcore_hsbbstree( void ) : stress()
		{}
	virtual ~tut_yaal_hcore_hsbbstree( void )
		{}
	template<typename object, typename subject, typename key>
	void helper_stress_test( object&, subject, key );
	typedef HSet<int> set_t;
	typedef set_t::insert_result (set_t::*set_insert_t)( int const& );
	};

template<typename object, typename subject, typename key>
void tut_yaal_hcore_hsbbstree::helper_stress_test( object& ob, subject member, key val )
	{
	( ob.*member )( val );
	ENSURE( "self test failed", ! stress.self_test<key>( ob ) );
	ENSURE( "integrity test failed", ! stress.integrity_test<key>( ob ) );
	ENSURE( "definition test failed", ! stress.definition_test<key>( ob ) );
	key biggest = - 1;
	for ( typename object::HIterator it = ob.begin(); it != ob.end(); ++ it )
		{
		ENSURE( "elements not in order", *it > biggest );
		biggest = *it;
		}
	return;
	}

TUT_TEST_GROUP_N( tut_yaal_hcore_hsbbstree, "yaal::hcore::HSBBSTree" );

TUT_UNIT_TEST_N( 1, "/* Adding keys in ascending order. */" )
	set_t s;
	set_insert_t insert = &set_t::insert;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test( s, insert, i );
	ENSURE ( "no red nodes were generated during the test", red_black_tree_stress_test::red_node_exists );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 2, "/* Adding keys in descending order. */" )
	set_t s;
	set_insert_t insert = &set_t::insert;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		helper_stress_test( s, insert, i );
	ENSURE ( "no red nodes were generated during the test", red_black_tree_stress_test::red_node_exists );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 3, "/* Adding keys in random order. */" )
	HRandomizer r;
	set_t s;
	set_insert_t insert = &set_t::insert;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test( s, insert, r( KEY_POOL_SIZE ) );
	ENSURE ( "no red nodes were generated during the test", red_black_tree_stress_test::red_node_exists );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 4, "/* Removing keys in ascending order from lower half of the tree that was created by adding keys in ascending order. */" )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* Removing keys in ascending order from upper half of the tree that was created by adding keys in ascending order. */" )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* Removing keys in descending order from lower half of the tree that was created by adding keys in ascending order. */" )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* Removing keys in descending order from upper half of the tree that was created by adding keys in ascending order. */" )
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = NUMBER_OF_TEST_NODES - 1; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( & set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* Removing keys in ascending order from lower half of the tree that was created by adding keys in descending order. */" )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		s.insert ( i );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* Removing keys in ascending order from upper half of the tree that was created by adding keys in descending order. */" )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 10, "/* Removing keys in descending order from lower half of the tree that was created by adding keys in descending order. */" )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 11, "/* Removing keys in descending order from upper half of the tree that was created by adding keys in descending order. */" )
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	for ( int i = NUMBER_OF_TEST_NODES; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 12, "/* Removing keys in ascending order from lower half of the tree that was created by adding keys in random order. */" )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		s.insert ( r( KEY_POOL_SIZE ) );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		{
		try
			{
			helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
			}
		catch ( HException & e )
			{
			if ( e.code() != static_cast<int>( HSBBSTree::ERROR::NON_EXISTING_KEY ) )
				throw e;
			}
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 13, "/* Removing keys in ascending order from upper half of the tree that was created by adding keys in random order. */" )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( r( KEY_POOL_SIZE ) );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		{
		try
			{
			helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
			}
		catch ( HException & e )
			{
			if ( e.code() != static_cast<int>( HSBBSTree::ERROR::NON_EXISTING_KEY ) )
				throw e;
			}
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 14, "/* Removing keys in descending order from lower half of the tree that was created by adding keys in random order. */" )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i >= 0; -- i )
		s.insert ( r( KEY_POOL_SIZE ) );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		{
		try
			{
			helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
			}
		catch ( HException & e )
			{
			if ( e.code() != static_cast<int>( HSBBSTree::ERROR::NON_EXISTING_KEY ) )
				throw e;
			}
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 15, "/* Removing keys in descending order from upper half of the tree that was created by adding keys in random order. */" )
	HRandomizer r;
	set_t s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( r( KEY_POOL_SIZE ) );
	for ( int i = NUMBER_OF_TEST_NODES; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		{
		try
			{
			helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), i );
			}
		catch ( HException& e )
			{
			if ( e.code() != static_cast<int>( HSBBSTree::ERROR::NON_EXISTING_KEY ) )
				throw e;
			}
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 16, "/* Removing keys in random order from upper half of the tree that was created by adding keys in random order. */" )
	TIME_CONSTRAINT_EXEMPT();
	HRandomizer r;
	set_t s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( r( KEY_POOL_SIZE ) );
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		{
		try
			{
			helper_stress_test( s, static_cast<int long ( set_t::* )( int const& )>( &set_t::erase ), r( KEY_POOL_SIZE ) );
			}
		catch ( HException& e )
			{
			if ( e.code() != static_cast<int>( HSBBSTree::ERROR::NON_EXISTING_KEY ) )
				throw e;
			}
		}
TUT_TEARDOWN()

#if 0
#endif

}


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

#include "header"
M_VCSID ( "$Id$" )

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace yaal
{

template < typename tType >
struct set
	{
	struct iterator
		{
		HBTree::HIterator f_oEngine;
		explicit iterator ( HBTree::HIterator const & it ) : f_oEngine ( it ){};
		iterator & operator ++ ( void )
			{
			++ f_oEngine;
			return ( * this );
			}
		tType & operator * ( void )
			{	return ( f_oEngine.get<tType> ( ) );	}
		tType * operator -> ( void )
			{ return ( & f_oEngine.get<tType> ( ) );	}
		bool operator == ( iterator const & it ) const
			{ return ( f_oEngine == it.f_oEngine ); }
		bool operator != ( iterator const & it ) const
			{ return ( f_oEngine != it.f_oEngine ); }
		};
	HBTree f_oEngine;
	set ( void ) : f_oEngine ( ) {};
	long int quantity ( void )
		{ return ( f_oEngine.quantity ( ) );	}
	void insert ( tType const & e )
		{	f_oEngine.insert ( e );	}
	void remove ( tType const & e )
		{	f_oEngine.remove ( e );	}
	iterator find ( tType const & e )
		{ return ( f_oEngine.find ( e ) ); }
	iterator begin ( void )
		{ return ( iterator ( f_oEngine.begin ( ) ) ); }
	iterator end ( void )
		{ return ( iterator ( f_oEngine.end ( ) ) ); }
	iterator rbegin ( void )
		{ return ( iterator ( f_oEngine.rbegin ( ) ) ); }
	iterator rend ( void )
		{ return ( iterator ( f_oEngine.rend ( ) ) ); }
	};

}

namespace tut
{

struct red_black_tree_stress_test
	{
	virtual ~red_black_tree_stress_test ( void ) {}
	struct node
		{
		typedef enum	{	red, black	} color_t;
		void * nil;
		color_t color;
		node * parent;
		node * left;
		node * right;
		};
	node * root;
	int long quantity;
	template < typename T >
	bool self_test ( set<T> & );
	template < typename T >
	bool integrity_test ( set<T> & );
	template < typename T >
	bool definition_test ( set<T> & );

	static bool red_node_exists;
private:
	int long tested_nodes;
	int black_height;
	template < typename T >
	void init ( set<T>& );

	void helper_test_node_integrity ( node * );
	void helper_test_node_definition ( node * );
	int helper_count_exemplar_black_height ( node * );
	int helper_check_black_height ( node * );
	};

bool red_black_tree_stress_test::red_node_exists = false;

template<typename T>
void red_black_tree_stress_test::init ( set<T>& ob )
	{
	red_black_tree_stress_test * hack = reinterpret_cast<red_black_tree_stress_test*> ( &ob );
	tested_nodes = 0;
	black_height = 0;
	red_node_exists = false;
	root = hack->root;
	quantity = hack->quantity;
	}

void red_black_tree_stress_test::helper_test_node_integrity ( node * n )
	{
	if ( ! n->parent && ( n != root ) )
		fail ( "node with null parent is not root" );
	if ( n->parent && ( n->parent->left != n ) && ( n->parent->right != n ) )
		fail ( "parent node does not know about this node" );
	if ( n->left )
		{
		if ( n->left->parent != n )
			fail ( "child node does not know about its parent (this node)" );
		helper_test_node_integrity ( n->left );
		}
	if ( n->right )
		{
		if ( n->right->parent != n )
			fail ( "child node does not know about its parent (this node)" );
		helper_test_node_integrity ( n->right );
		}
	++ tested_nodes;
	}

void red_black_tree_stress_test::helper_test_node_definition ( node * n )
	{
	if ( n->color == node::red )
		{
		red_node_exists = true;
		if ( ( n->left && ( n->left->color == node::red ) )
				|| ( n->right && ( n->right->color == node::red ) ) )
			fail ( "subsequent red nodes" );
		}
	if ( n->left )
		helper_test_node_definition ( n->left );
	if ( n->right )
		helper_test_node_definition ( n->right );
	if ( ! ( n->left || n->right ) )
		{
		if ( helper_check_black_height ( n ) != black_height )
			fail ( "black height is not the same for all the nodes" );
		}
	}

int red_black_tree_stress_test::helper_count_exemplar_black_height ( node * n )
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

int red_black_tree_stress_test::helper_check_black_height ( node * n )
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
bool red_black_tree_stress_test::self_test ( set<T> & ob )
	{
	init ( ob );
	if ( ob.quantity ( ) != quantity )
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
bool red_black_tree_stress_test::integrity_test ( set<T> & ob )
	{
	init ( ob );
	helper_test_node_integrity ( root );
	ensure_equals ( "quantity inconsistency", quantity,  tested_nodes );
	return ( false );
	}

template<typename T>
bool red_black_tree_stress_test::definition_test ( set<T> & ob )
	{
	init ( ob );
	if ( root->color != node::black )
		fail ( "root is not black" );
	black_height = helper_count_exemplar_black_height ( root );
	helper_test_node_definition ( root );
//	if ( red_node_exists )
//		cout << "R";
	return ( false );
	}

struct tut_yaal_hcore_hbtree
	{
	static int const NUMBER_OF_TEST_NODES = 2000;
	red_black_tree_stress_test stress;
	};

typedef test_group < tut_yaal_hcore_hbtree > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_hbtree_group ( "yaal::hcore::HBTree" );

/*
 * Adding keys in ascending order.
 */
template < >
template < >
void module::test<1> ( void )
	{
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		{
		s.insert ( i );
		ensure ( "self test failed", ! stress.self_test<int> ( s ) );
		ensure ( "integrity test failed", ! stress.integrity_test<int> ( s ) );
		ensure ( "definition test failed", ! stress.definition_test<int> ( s ) );
		}
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	ensure ( "no red nodes were generated during the test", red_black_tree_stress_test::red_node_exists );
	}

/*
 * Adding keys in descending order.
 */
template < >
template < >
void module::test<2> ( void )
	{
	set<int> s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		{
		s.insert ( i );
		ensure ( "self test failed", ! stress.self_test<int> ( s ) );
		ensure ( "integrity test failed", ! stress.integrity_test<int> ( s ) );
		ensure ( "definition test failed", ! stress.definition_test<int> ( s ) );
		}
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	ensure ( "no red nodes were generated during the test", red_black_tree_stress_test::red_node_exists );
	}

/*
 * Adding keys in random order.
 */
template < >
template < >
void module::test<3> ( void )
	{
	HRandomizer r;
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		{
		s.insert ( r.rnd ( 30000 ) );
		ensure ( "self test failed", ! stress.self_test<int> ( s ) );
		ensure ( "integrity test failed", ! stress.integrity_test<int> ( s ) );
		ensure ( "definition test failed", ! stress.definition_test<int> ( s ) );
		}
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	ensure ( "no red nodes were generated during the test", red_black_tree_stress_test::red_node_exists );
	}

/*
 * Removing keys in ascending order from lower half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<4> ( void )
	{
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		{
		s.remove ( i );
		ensure ( "self test failed", ! stress.self_test<int> ( s ) );
		ensure ( "integrity test failed", ! stress.integrity_test<int> ( s ) );
		ensure ( "definition test failed", ! stress.definition_test<int> ( s ) );
		}
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

#if 0
/*
 * Removing keys in ascending order from upper half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<5> ( void )
	{
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

/*
 * Removing keys in ascending order from lower half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<6> ( void )
	{
	set<int> s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	for ( int i = 0; i < ( NUMBER_OF_TEST_NODES / 2 ); ++ i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

/*
 * Removing keys in ascending order from upper half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<7> ( void )
	{
	set<int> s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i < NUMBER_OF_TEST_NODES; ++ i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

/*
 * Removing keys in descending order from lower half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<8> ( void )
	{
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

/*
 * Removing keys in descending order from upper half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<9> ( void )
	{
	set<int> s;
	for ( int i = 0; i < NUMBER_OF_TEST_NODES; ++ i )
		s.insert ( i );
	for ( int i = NUMBER_OF_TEST_NODES; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

/*
 * Removing keys in descending order from lower half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<10> ( void )
	{
	set<int> s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	for ( int i = ( NUMBER_OF_TEST_NODES / 2 ); i > 0; -- i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

/*
 * Removing keys in descending order from upper half of the tree that
 * was created by adding keys in ascending order.
 */
template < >
template < >
void module::test<11> ( void )
	{
	set<int> s;
	for ( int i = NUMBER_OF_TEST_NODES; i > 0; -- i )
		s.insert ( i );
	for ( int i = NUMBER_OF_TEST_NODES; i > ( NUMBER_OF_TEST_NODES / 2 ); -- i )
		s.remove ( i );
	int biggest = - 1;
	for ( set<int>::iterator it = s.begin ( ); it != s.end ( ); ++ it )
		{
		ensure ( "elements not in order", *it > biggest );
		biggest = *it;
		}
	}

#endif

}


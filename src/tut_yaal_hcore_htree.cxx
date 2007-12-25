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

struct tut_yaal_hcore_htree
	{
	static HString _cache;
	typedef HTree<char> tree_t;
	static HString& to_string( tree_t const& );
	static void to_string( tree_t::HNode const& );
	static void draw_tree( tree_t const& );
	static void draw_node( tree_t::HNode const& );
	};

HString tut_yaal_hcore_htree::_cache;

HString& tut_yaal_hcore_htree::to_string( tree_t const& t )
	{
	_cache.clear();
	to_string( *t.get_root() );
	return ( _cache );
	}

void tut_yaal_hcore_htree::to_string( tree_t::HNode const& n )
	{
	_cache += *n;
	for ( tree_t::iterator it = n.begin(); it != n.end(); ++ it )
		to_string( *it );
	}

void tut_yaal_hcore_htree::draw_tree( tree_t const& t )
	{
	_cache.clear();
	draw_node( *t.get_root() );
	return;
	}

void tut_yaal_hcore_htree::draw_node( tree_t::HNode const& n )
	{
	cout << _cache << *n << endl;
	for ( tree_t::iterator it = n.begin(); it != n.end(); ++ it )
		draw_node( *it );
	}

typedef test_group<tut_yaal_hcore_htree> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_hcore_htree_group( "yaal::hcore::HTree" );

/* trivial constructor */
template<>
template<>
void module::test<1>( void )
	{
	tree_t t;
	ensure_equals( "new tree not clear", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	}

/* creating root */
template<>
template<>
void module::test<2>( void )
	{
	tree_t t;
	ensure_equals( "new tree not clear", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	tree_t::node_t n = t.set_new_root();
	ensure( "root not created", n );
	ensure_equals( "new root is invalid", t.get_root(), n );
	}

/* setting getting values */
template<>
template<>
void module::test<3>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	(**n) = 'x';
	ensure_equals( "value set/get failed", **n, 'x' );
	}

/* get_parent */
template<>
template<>
void module::test<4>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	ensure_equals( "root node malformed", n->get_parent(), static_cast<tree_t::node_t>( NULL ) );
	}

/* add_node */
template<>
template<>
void module::test<5>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	(**n) = '0';
	tree_t::iterator it = n->add_node( 'x' );
	n->add_node( 'y' );
	it->add_node( 'A' );
	it->add_node( 'B' );
	it->insert_node( it->begin(), 'Q' );
	cout << endl << to_string( t ) << endl;
	draw_tree( t );
	}

}


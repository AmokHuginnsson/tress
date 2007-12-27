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
	if ( n.has_childs() )
		_cache += '{';
	for ( tree_t::iterator it = n.begin(); it != n.end(); ++ it )
		to_string( *it );
	if ( n.has_childs() )
		_cache += '}';
	}

void tut_yaal_hcore_htree::draw_tree( tree_t const& t )
	{
	_cache.clear();
	draw_node( *t.get_root() );
	return;
	}

void tut_yaal_hcore_htree::draw_node( tree_t::HNode const& n )
	{
	int len = _cache.get_length();
	if ( n.get_parent() )
		{
		cout << _cache << "\\_ ";
		if ( n.get_parent()->child_count() > 1 )
			_cache += "|  ";
		else
			_cache += "   ";
		}
	cout << *n << endl;
	for ( tree_t::iterator it = n.begin(); it != n.end(); ++ it )
		draw_node( *it );
	_cache.set_at( len, 0 );
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

/* set_new_root/get_root */
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
	ensure( "node addition / access failure", it == n->begin() );
	ensure_equals( "bad value for new node", **it, 'x' );
	}

/* has_childs */
template<>
template<>
void module::test<6>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	ensure( "new node has some spurious childs", ! n->has_childs() );
	n->add_node( 'y' );
	ensure( "childless node reported after node addition", n->has_childs() );
	n->add_node( 'x' );
	ensure( "childless node reported after node addition", n->has_childs() );
	}

/* child_count */
template<>
template<>
void module::test<7>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	ensure_equals( "new node has some spurious childs", n->child_count(), 0 );
	n->add_node( 'y' );
	ensure_equals( "childless node reported after node addition", n->child_count(), 1 );
	n->add_node( 'x' );
	ensure_equals( "bad child count reported", n->child_count(), 2 );
	}

/* clear */
template<>
template<>
void module::test<8>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	ensure( "new node has some spurious childs", ! n->has_childs() );
	ensure_equals( "new node has some spurious childs", n->child_count(), 0 );
	(**n) = '0';
	n->add_node( 'x' );
	ensure( "childless node reported after node addition", n->has_childs() );
	ensure_equals( "childless node reported after node addition", n->child_count(), 1 );
	t.clear();
	ensure_equals( "clear failed", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	}

/* basic shape tests */
template<>
template<>
void module::test<9>( void )
	{
	tree_t t;
	tree_t::node_t n = t.set_new_root();
	(**n) = '0';
	char const* const bad_shape = "bad shape";
	ensure_equals( bad_shape, to_string( t ), "0" );
	tree_t::iterator it = n->add_node( 'x' );
	ensure_equals( bad_shape, to_string( t ), "0{x}" );
	n->add_node( 'y' );
	ensure_equals( bad_shape, to_string( t ), "0{xy}" );
	it = it->add_node( '@' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@}y}" );
	tree_t::iterator a = it->add_node( 'A' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@{A}}y}" );
	it->add_node( 'B' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@{AB}}y}" );
	it->insert_node( it->begin(), 'Q' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@{QAB}}y}" );
	a->add_node( 'F' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@{QA{F}B}}y}" );
	a->add_node( 'G' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@{QA{FG}B}}y}" );
	a->add_node( 'H' );
	ensure_equals( bad_shape, to_string( t ), "0{x{@{QA{FGH}B}}y}" );
	}

}


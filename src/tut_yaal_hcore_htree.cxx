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
#include <tut_helpers.h>

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
	typedef counter<char> cc;
	typedef HTree<cc> tree_t;
	static HString& to_string( tree_t const& );
	static void to_string( tree_t::HNode const& );
	static void draw_tree( tree_t const& );
	static void draw_node( tree_t::HNode const& );
	};

HString tut_yaal_hcore_htree::_cache;

HString& tut_yaal_hcore_htree::to_string( tree_t const& t )
	{
	_cache.clear();
	if ( t.get_root() )
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
	if ( t.get_root() )
		draw_node( *t.get_root() );
	return;
	}

void tut_yaal_hcore_htree::draw_node( tree_t::HNode const& n )
	{
	int len = _cache.get_length();
	tree_t::const_node_t pn = NULL;
	if ( ( pn = n.get_parent() ) )
		{
		cout << _cache << "\\_ ";
		if ( ( pn->child_count() > 1 ) && ( &*( pn->rbegin() ) != &n ) )
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
		{
	tree_t t;
	ensure_equals( "new tree not clear", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* create_new_root/get_root */
template<>
template<>
void module::test<2>( void )
	{
		{
	tree_t t;
	ensure_equals( "new tree not clear", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	tree_t::node_t n = t.create_new_root();
	ensure( "root not created", n );
	ensure_equals( "new root is invalid", t.get_root(), n );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* setting getting values */
template<>
template<>
void module::test<3>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	(**n) = 'x';
	ensure_equals( "value set/get failed", **n, 'x' );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* get_parent */
template<>
template<>
void module::test<4>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	ensure_equals( "root node malformed", n->get_parent(), static_cast<tree_t::node_t>( NULL ) );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* add_node */
template<>
template<>
void module::test<5>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	(**n) = '0';
	tree_t::iterator it = n->add_node( 'x' );
	ensure( "node addition / access failure", it == n->begin() );
	ensure_equals( "bad value for new node", **it, 'x' );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* has_childs */
template<>
template<>
void module::test<6>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	ensure( "new node has some spurious childs", ! n->has_childs() );
	n->add_node( 'y' );
	ensure( "childless node reported after node addition", n->has_childs() );
	n->add_node( 'x' );
	ensure( "childless node reported after node addition", n->has_childs() );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* child_count */
template<>
template<>
void module::test<7>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	ensure_equals( "new node has some spurious childs", n->child_count(), 0 );
	n->add_node( 'y' );
	ensure_equals( "childless node reported after node addition", n->child_count(), 1 );
	n->add_node( 'x' );
	ensure_equals( "bad child count reported", n->child_count(), 2 );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* clear */
template<>
template<>
void module::test<8>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	ensure( "new node has some spurious childs", ! n->has_childs() );
	ensure_equals( "new node has some spurious childs", n->child_count(), 0 );
	(**n) = '0';
	n->add_node( 'x' );
	ensure( "childless node reported after node addition", n->has_childs() );
	ensure_equals( "childless node reported after node addition", n->child_count(), 1 );
	t.clear();
	ensure_equals( "clear failed", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* get_level() */
template<>
template<>
void module::test<9>( void )
	{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	ensure_equals( "incorrect level value", n->get_level(), 0 );
	tree_t::iterator it = n->add_node( '1' );
	ensure_equals( "incorrect level value", it->get_level(), 1 );
	it = it->add_node( '2' );
	ensure_equals( "incorrect level value", it->get_level(), 2 );
	ensure_equals( "incorrect level value", n->get_level(), 0 );
	}

/* swap() */
template<>
template<>
void module::test<10>( void )
	{
		{
		char const* const bad_shape = "bad shape";
		char const* const swap_failed = "swap failed";
		tree_t t1;
		tree_t::node_t n = t1.create_new_root();
		**n = '@';
		n->add_node( 'x' );
		n->add_node( 'y' );
		tree_t t2;
		n = t2.create_new_root();
		**n = '%';
		n->add_node( '1' );
		n->add_node( '2' );
		ensure_equals( bad_shape, to_string( t1 ), "@{xy}" );
		ensure_equals( bad_shape, to_string( t2 ), "%{12}" );
		t1.swap( t2 );
		ensure_equals( swap_failed, to_string( t2 ), "@{xy}" );
		ensure_equals( swap_failed, to_string( t1 ), "%{12}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* basic shape tests */
template<>
template<>
void module::test<11>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
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
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* graft */
template<>
template<>
void module::test<12>( void )
	{
		{
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	(**n) = '@';
	tree_t::iterator it = n->add_node( '0' );
	it = it->add_node( 'a' );
	tree_t::node_t b = &*it;
	it->add_node( 'A' );
	it->add_node( 'B' );
	it->add_node( 'C' );
	it = n->add_node( '1' );
	it->add_node( 'd' );
	it->add_node( 'e' );
	it->add_node( 'f' );
	it = n->add_node( '2' );
	it->add_node( 'g' );
	it->add_node( 'h' );
	it->add_node( 'i' );
	ensure_equals( "bad shape", to_string( t ), "@{0{a{ABC}}1{def}2{ghi}}" );
	n->replace_node( n->begin(), b );
	ensure( "bad parent", b->get_parent() == &*n ); 
	**b = '0';
	ensure_equals( "bad shape", to_string( t ), "@{0{ABC}1{def}2{ghi}}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* graft upwards */
template<>
template<>
void module::test<13>( void )
	{
		{
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::iterator it = n->add_node( '0' );
		tree_t::iterator q = it->add_node( 'q' );
		tree_t::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		it = it->add_node( 'a' );
		tree_t::node_t b = &*it;
		it->add_node( 'A' );
		tree_t::iterator B = it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ensure_equals( "incorrect level value", B->get_level(), 5 );
		ensure_equals( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		n->replace_node( n->begin(), b );
		ensure_equals( "incorrect level value", B->get_level(), 2 );
		ensure( "bad parent", b->get_parent() == &*n ); 
		ensure_equals( "bad shape", to_string( t ), "@{a{ABC}1{def}2{ghi}}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* graft downwards */
template<>
template<>
void module::test<14>( void )
	{
		{
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::iterator it0, it = it0 = n->add_node( '0' );
		tree_t::iterator q = it->add_node( 'q' );
		tree_t::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		tree_t::iterator B = it->add_node( 'B' );
		ensure_equals( "incorrect level value", B->get_level(), 5 );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ensure_equals( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		try
			{
			a->replace_node( B, &*it0 );
			fail( "graft downwards succeded, eek!" );
			}
		catch ( int& )
			{
			// ok
			}
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* graft sideways */
template<>
template<>
void module::test<15>( void )
	{
		{
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::iterator it = n->add_node( '0' );
		tree_t::iterator q = it->add_node( 'q' );
		tree_t::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ensure_equals( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		e->get_parent()->replace_node( e, &*a );
		ensure_equals( "bad shape", to_string( t ), "@{0{q{!#$}w{%^&}}1{da{ABC}f}2{ghi}}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* graft to root */
template<>
template<>
void module::test<16>( void )
	{
		{
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::iterator it = n->add_node( '0' );
		tree_t::iterator q = it->add_node( 'q' );
		tree_t::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ensure_equals( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		t.set_new_root( &*a );
		ensure_equals( "bad shape", to_string( t ), "a{ABC}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* across two trees */
template<>
template<>
void module::test<17>( void )
	{
		{
		tree_t::node_t n = NULL;
		tree_t::iterator it;
		tree_t t1;
		n = t1.create_new_root();
		**n = '@';
		tree_t::iterator a = it = n->add_node( '1' );
		it->add_node( '2' );
		it->add_node( '4' );
		it->add_node( '6' );
		it = n->add_node( '3' );
		it->add_node( '8' );
		it->add_node( '0' );
		n->add_node( '5' );

		tree_t t2;
		n = t2.create_new_root();
		**n = '%';
		it = n->add_node( 'a' );
		it->add_node( 'D' );
		it->add_node( 'E' );
		it->add_node( 'F' );
		it = n->add_node( 'b' );
		it->add_node( 'G' );
		it->add_node( 'H' );
		n->add_node( 'c' );
		ensure_equals( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ensure_equals( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		it->replace_node( it->rbegin(), &*a );
		ensure_equals( "bad shape", to_string( t1 ), "@{3{80}5}" );
		ensure_equals( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}}c}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* across two trees from root */
template<>
template<>
void module::test<18>( void )
	{
		{
		tree_t::node_t n = NULL;
		tree_t::iterator it;
		tree_t t1;
		n = t1.create_new_root();
		**n = '@';
		it = n->add_node( '1' );
		it->add_node( '2' );
		it->add_node( '4' );
		it->add_node( '6' );
		it = n->add_node( '3' );
		it->add_node( '8' );
		it->add_node( '0' );
		n->add_node( '5' );

		tree_t t2;
		n = t2.create_new_root();
		**n = '%';
		it = n->add_node( 'a' );
		it->add_node( 'D' );
		it->add_node( 'E' );
		it->add_node( 'F' );
		it = n->add_node( 'b' );
		it->add_node( 'G' );
		it->add_node( 'H' );
		n->add_node( 'c' );
		ensure_equals( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ensure_equals( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		it->replace_node( it->rbegin(), t1.get_root() );
		ensure_equals( "bad shape", to_string( t1 ), "" );
		ensure_equals( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}}c}" );
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

/* graft with bad iteroator */
template<>
template<>
void module::test<19>( void )
	{
		{
		tree_t::node_t n = NULL;
		tree_t::iterator it;
		tree_t t1;
		n = t1.create_new_root();
		**n = '@';
		it = n->add_node( '1' );
		it->add_node( '2' );
		it->add_node( '4' );
		it->add_node( '6' );
		it = n->add_node( '3' );
		it->add_node( '8' );
		it->add_node( '0' );
		n->add_node( '5' );

		tree_t t2;
		n = t2.create_new_root();
		**n = '%';
		it = n->add_node( 'a' );
		it->add_node( 'D' );
		it->add_node( 'E' );
		it->add_node( 'F' );
		it = n->add_node( 'b' );
		it->add_node( 'G' );
		it->add_node( 'H' );
		n->add_node( 'c' );
		ensure_equals( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ensure_equals( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		try
			{
			it->replace_node( it, t1.get_root() );
			fail( "grafintg with no coherency" );
			}
		catch ( int& )
			{
			// ok
			}
		}
	ensure_equals( "leak", cc::get_instances_count(), 0 );
	}

}


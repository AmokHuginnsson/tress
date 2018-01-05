/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_htree.cxx - this file is integral part of `tress' project.

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

#include <TUT/tut.hpp>

#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wkeyword-macro"
#define private public
#define protected public
#pragma GCC diagnostic error "-Wkeyword-macro"
#pragma GCC diagnostic error "-Wpragmas"
#include <yaal/hcore/htree.hxx>
#undef protected
#undef private

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "tut_yaal_allocator.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_htree : public simple_mock<tut_yaal_hcore_htree> {
	typedef simple_mock<tut_yaal_hcore_htree> base_type;
	typedef HTree<item_t> tree_t;
	HString _cache;
	tut_yaal_hcore_htree( void );
	virtual ~tut_yaal_hcore_htree( void )
		{}
	typedef HInstanceTracker<tut_yaal_hcore_htree> item_t;
	template<typename T>
	HString& to_string( T const& );
	template<typename T>
	void to_string_node( T const& );
	void draw_tree( tree_t const& );
	void draw_node( tree_t::HNode const& );
	template<typename T>
	void check_consistency( T const& );
	template<typename T>
	void check_node( T*, bool );
};


tut_yaal_hcore_htree::tut_yaal_hcore_htree( void )
	: base_type(), _cache() {
	item_t::set_start_id( -1 );
	item_t::allow_copying();
}

template<typename T>
HString& tut_yaal_hcore_htree::to_string( T const& t ) {
	_cache.clear();
	if ( t.get_root() )
		to_string_node( *t.get_root() );
	return ( _cache );
}

template<typename T>
void tut_yaal_hcore_htree::to_string_node( T const& n ) {
	_cache += static_cast<char>( n->id() );
	if ( n.has_children() )
		_cache += '{';
	for ( typename T::const_iterator it = n.begin(); it != n.end(); ++ it )
		to_string_node( *it );
	if ( n.has_children() )
		_cache += '}';
}

void tut_yaal_hcore_htree::draw_tree( tree_t const& t ) {
	_cache.clear();
	if ( t.get_root() ) {
		draw_node( *t.get_root() );
	}
	return;
}

void tut_yaal_hcore_htree::draw_node( tree_t::HNode const& n ) {
	int len = static_cast<int>( _cache.get_length() );
	tree_t::const_node_t pn = NULL;
	if ( ( pn = n.get_parent() ) ) {
		clog << _cache << "\\_ ";
		if ( ( pn->child_count() > 1 ) && ( &*( pn->rbegin() ) != &n ) ) {
			_cache += "|  ";
		} else {
			_cache += "   ";
		}
	}
	std::clog << *n << std::endl;
	for ( tree_t::HNode::const_iterator it = n.begin(); it != n.end(); ++ it ) {
		draw_node( *it );
	}
	_cache.set_at( len, 0_ycp );
}

template<typename T>
void tut_yaal_hcore_htree::check_node( T* node, bool root ) {
	if ( ! root )
		ENSURE_EQUALS( "bad root", node->_tree, static_cast<typename T::tree_t*>( NULL ) );
	for ( typename T::const_iterator it = node->begin(); it != node->end(); ++ it ) {
		ENSURE_EQUALS( "bad parent", it->_trunk, node );
		check_node( &*it, false );
	}
}

template<typename T>
void tut_yaal_hcore_htree::check_consistency( T const& tree ) {
	if ( tree.get_root() ) {
		ENSURE_EQUALS( "bad root", tree.get_root()->_tree, &tree );
		ENSURE_EQUALS( "bad parent for root", tree.get_root()->_trunk, static_cast<typename T::node_t>( NULL ) );
		check_node( tree.get_root(), true );
	}
}

TUT_TEST_GROUP( tut_yaal_hcore_htree, "yaal::hcore::HTree" );

TUT_UNIT_TEST( "trivial constructor" ) {
	tree_t t;
	ENSURE_EQUALS( "new tree not clear", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy constructor of empty trees (both are empty)" ) {
	tree_t t1;
	tree_t t2( t1 );
	ENSURE_EQUALS( "new tree not clear", t1.get_root(), static_cast<tree_t::node_t>( NULL ) );
	ENSURE_EQUALS( "copied tree not clear", t2.get_root(), static_cast<tree_t::node_t>( NULL ) );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap empty trees (both are empty)" ) {
	tree_t t1;
	tree_t t2;
	t1.swap( t2 );
	ENSURE_EQUALS( "new tree not clear", t1.get_root(), static_cast<tree_t::node_t>( NULL ) );
	ENSURE_EQUALS( "copied tree not clear", t2.get_root(), static_cast<tree_t::node_t>( NULL ) );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "create_new_root/get_root" ) {
	tree_t t;
	ENSURE_EQUALS( "new tree not clear", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE( "root not created", n ? true : false );
	ENSURE_EQUALS( "new root is invalid", t.get_root(), n );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "setting getting values" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	(**n) = 'x';
	check_consistency( t );
	ENSURE_EQUALS( "value set/get failed", **n, 'x' );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_parent" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE_EQUALS( "root node malformed", n->get_parent(), static_cast<tree_t::node_t>( NULL ) );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add_node" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	(**n) = '0';
	tree_t::HNode::iterator it = n->add_node( 'x' );
	check_consistency( t );
	ENSURE( "node addition / access failure", it == n->begin() );
	ENSURE_EQUALS( "bad value for new node", **it, 'x' );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "has_children" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE( "new node has some spurious childs", ! n->has_children() );
	n->add_node( 'y' );
	check_consistency( t );
	ENSURE( "childless node reported after node addition", n->has_children() );
	n->add_node( 'x' );
	check_consistency( t );
	ENSURE( "childless node reported after node addition", n->has_children() );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "child_count" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE_EQUALS( "new node has some spurious childs", n->child_count(), 0 );
	n->add_node( 'y' );
	check_consistency( t );
	ENSURE_EQUALS( "childless node reported after node addition", n->child_count(), 1 );
	n->add_node( 'x' );
	check_consistency( t );
	ENSURE_EQUALS( "bad child count reported", n->child_count(), 2 );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "clear" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE( "new node has some spurious childs", ! n->has_children() );
	ENSURE_EQUALS( "new node has some spurious childs", n->child_count(), 0 );
	(**n) = '0';
	n->add_node( 'x' );
	check_consistency( t );
	ENSURE( "childless node reported after node addition", n->has_children() );
	ENSURE_EQUALS( "childless node reported after node addition", n->child_count(), 1 );
	t.clear();
	check_consistency( t );
	ENSURE_EQUALS( "clear failed", t.get_root(), static_cast<tree_t::node_t>( NULL ) );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_level()" )
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE_EQUALS( "incorrect level value", n->get_level(), 0 );
	tree_t::HNode::iterator it = n->add_node( '1' );
	check_consistency( t );
	ENSURE_EQUALS( "incorrect level value", it->get_level(), 1 );
	it = it->add_node( '2' );
	check_consistency( t );
	ENSURE_EQUALS( "incorrect level value", it->get_level(), 2 );
	ENSURE_EQUALS( "incorrect level value", n->get_level(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "swap()" ) {
		char const* const bad_shape = "bad shape";
		char const* const swap_failed = "swap failed";
		tree_t t1;
		tree_t::node_t n = t1.create_new_root();
		check_consistency( t1 );
		**n = '@';
		n->add_node( 'x' );
		check_consistency( t1 );
		n->add_node( 'y' );
		check_consistency( t1 );
		tree_t t2;
		n = t2.create_new_root();
		check_consistency( t2 );
		**n = '%';
		n->add_node( '1' );
		check_consistency( t2 );
		n->add_node( '2' );
		check_consistency( t2 );
		ENSURE_EQUALS( bad_shape, to_string( t1 ), "@{xy}" );
		ENSURE_EQUALS( bad_shape, to_string( t2 ), "%{12}" );
		swap( t1, t2 );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( swap_failed, to_string( t2 ), "@{xy}" );
		ENSURE_EQUALS( swap_failed, to_string( t1 ), "%{12}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "basic shape tests" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	(**n) = '0';
	char const* const bad_shape = "bad shape";
	ENSURE_EQUALS( bad_shape, to_string( t ), "0" );
	tree_t::HNode::iterator it = n->add_node( 'x' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x}" );
	n->add_node( 'y' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{xy}" );
	it = it->add_node( '@' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@}y}" );
	tree_t::HNode::iterator a = it->add_node( 'A' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@{A}}y}" );
	it->add_node( 'B' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@{AB}}y}" );
	it->insert_node( it->begin(), 'Q' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@{QAB}}y}" );
	a->add_node( 'F' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@{QA{F}B}}y}" );
	a->add_node( 'G' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@{QA{FG}B}}y}" );
	a->add_node( 'H' );
	check_consistency( t );
	ENSURE_EQUALS( bad_shape, to_string( t ), "0{x{@{QA{FGH}B}}y}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "graft ( replace_node )" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	(**n) = '@';
	tree_t::HNode::iterator it = n->add_node( '0' );
	it = it->add_node( 'a' );
	check_consistency( t );
	tree_t::node_t b = &*it;
	it->add_node( 'A' );
	check_consistency( t );
	it->add_node( 'B' );
	check_consistency( t );
	it->add_node( 'C' );
	check_consistency( t );
	it = n->add_node( '1' );
	check_consistency( t );
	it->add_node( 'd' );
	check_consistency( t );
	it->add_node( 'e' );
	check_consistency( t );
	it->add_node( 'f' );
	check_consistency( t );
	it = n->add_node( '2' );
	check_consistency( t );
	it->add_node( 'g' );
	check_consistency( t );
	it->add_node( 'h' );
	check_consistency( t );
	it->add_node( 'i' );
	check_consistency( t );
	ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{a{ABC}}1{def}2{ghi}}" );
	item_t::stop_copying();
	n->replace_node( n->begin(), b );
	item_t::allow_copying();
	check_consistency( t );
	ENSURE( "bad parent", b->get_parent() == &*n );
	**b = '0';
	ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{ABC}1{def}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "graft upwards ( replace_node )" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		check_consistency( t );
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		check_consistency( t );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		check_consistency( t );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		check_consistency( t );
		q->add_node( '!' );
		check_consistency( t );
		it = q->add_node( '#' );
		check_consistency( t );
		q->add_node( '$' );
		check_consistency( t );
		w->add_node( '%' );
		check_consistency( t );
		w->add_node( '^' );
		check_consistency( t );
		w->add_node( '&' );
		check_consistency( t );
		it = it->add_node( 'a' );
		check_consistency( t );
		tree_t::node_t b = &*it;
		it->add_node( 'A' );
		check_consistency( t );
		tree_t::HNode::iterator B = it->add_node( 'B' );
		check_consistency( t );
		it->add_node( 'C' );
		check_consistency( t );
		it = n->add_node( '1' );
		check_consistency( t );
		it->add_node( 'd' );
		check_consistency( t );
		it->add_node( 'e' );
		check_consistency( t );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		check_consistency( t );
		it->add_node( 'h' );
		check_consistency( t );
		it->add_node( 'i' );
		check_consistency( t );
		ENSURE_EQUALS( "incorrect level value", B->get_level(), 5 );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		item_t::stop_copying();
		n->replace_node( n->begin(), b );
		item_t::allow_copying();
		check_consistency( t );
		ENSURE_EQUALS( "incorrect level value", B->get_level(), 2 );
		ENSURE( "bad parent", b->get_parent() == &*n );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{a{ABC}1{def}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "graft downwards (replace_node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it0, it = it0 = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		tree_t::HNode::iterator B = it->add_node( 'B' );
		ENSURE_EQUALS( "incorrect level value", B->get_level(), 5 );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		ENSURE_THROW( "graft downwards succeded, eek!", {
			check_consistency( t );
			item_t::allow_copying();
			a->replace_node( B, &*it0 );
			item_t::allow_copying();
		}, HFailedAssertion );
		item_t::allow_copying();
		check_consistency( t );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "graft sideways (replace_node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		check_consistency( t );
		item_t::stop_copying();
		e->get_parent()->replace_node( e, &*a );
		item_t::allow_copying();
		check_consistency( t );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#$}w{%^&}}1{da{ABC}f}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "graft to root (replace_node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		check_consistency( t );
		t.set_new_root( &*a );
		check_consistency( t );
		ENSURE_EQUALS( "bad shape", to_string( t ), "a{ABC}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees (replace_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
		tree_t t1;
		n = t1.create_new_root();
		**n = '@';
		tree_t::HNode::iterator a = it = n->add_node( '1' );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		item_t::stop_copying();
		it->replace_node( prev( it->end() ), &*a );
		item_t::allow_copying();
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees from root (replace_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		item_t::stop_copying();
		it->replace_node( prev( it->end() ), t1.get_root() );
		item_t::allow_copying();
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "graft with bad iteroator (replace_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		ENSURE_THROW( "grafintg with no coherency", {
			check_consistency( t1 );
			check_consistency( t2 );
			item_t::stop_copying();
			it->replace_node( it, t1.get_root() );
			item_t::allow_copying();
		}, tree_t::exception_type );
		item_t::allow_copying();
		check_consistency( t1 );
		check_consistency( t2 );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "move_node(it,node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		check_consistency( t );
		item_t::stop_copying();
		e->get_parent()->move_node( e, &*a );
		item_t::allow_copying();
		check_consistency( t );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#$}w{%^&}}1{da{ABC}ef}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "move_node(node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		check_consistency( t );
		item_t::stop_copying();
		e->get_parent()->move_node( &*a );
		item_t::allow_copying();
		check_consistency( t );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#$}w{%^&}}1{defa{ABC}}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees (move_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
		tree_t t1;
		n = t1.create_new_root();
		**n = '@';
		tree_t::HNode::iterator a = it = n->add_node( '1' );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		item_t::stop_copying();
		it->move_node( prev( it->end() ), &*a );
		item_t::allow_copying();
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees from root (move_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		item_t::stop_copying();
		it->move_node( prev( it->end() ), t1.get_root() );
		item_t::allow_copying();
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy_node(it,node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		check_consistency( t );
		e->get_parent()->copy_node( e, &*a );
		check_consistency( t );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{da{ABC}ef}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy_node(node)" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		check_consistency( t );
		e->get_parent()->copy_node( &*a );
		check_consistency( t );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{defa{ABC}}2{ghi}}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees (copy_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
		tree_t t1;
		n = t1.create_new_root();
		**n = '@';
		tree_t::HNode::iterator a = it = n->add_node( '1' );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->copy_node( prev( it->end() ), &*a );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees from root (copy_node)" ) {
		tree_t::node_t n = NULL;
		tree_t::HNode::iterator it;
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->copy_node( prev( it->end() ), t1.get_root() );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_parent" ) {
	tree_t t;
	tree_t::node_t n = t.create_new_root();
	check_consistency( t );
	ENSURE_EQUALS( "root node malformed", &n->get_tree(), &t );
	tree_t::HNode::iterator it( n->add_node( 'a' ) );
	ENSURE_EQUALS( "child node malformed, failed to get tree", &it->get_tree(), &t );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_parent" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		HString forward;
		for ( tree_t::const_iterator tit( t.begin() ), end( t.end() ); tit != end; ++ tit )
			forward += static_cast<char>( tit->id() );
		HString backward;
		for ( tree_t::const_reverse_iterator tit( t.rbegin() ), end( t.rend() ); tit != end; ++ tit )
			backward += static_cast<char>( tit->id() );
		clog << forward << endl;
		clog << backward << endl;
		reverse( backward.begin(), backward.end() );
		ENSURE_EQUALS( "forward/backward iteration failed", backward, forward );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "tree with explicit system allocator" ) {
		typedef HTree<item_t, allocator::system<item_t> > sys_tree_t;
		sys_tree_t t;
		sys_tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		sys_tree_t::HNode::iterator it = n->add_node( '0' );
		sys_tree_t::HNode::iterator q = it->add_node( 'q' );
		sys_tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		sys_tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		sys_tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		HString forward;
		for ( sys_tree_t::const_iterator tit( t.begin() ), end( t.end() ); tit != end; ++ tit )
			forward += static_cast<char>( tit->id() );
		HString backward;
		for ( sys_tree_t::const_reverse_iterator tit( t.rbegin() ), end( t.rend() ); tit != end; ++ tit )
			backward += static_cast<char>( tit->id() );
		clog << forward << endl;
		clog << backward << endl;
		reverse( backward.begin(), backward.end() );
		ENSURE_EQUALS( "forward/backward iteration failed", backward, forward );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "tree with explicit pool allocator" ) {
		typedef HTree<item_t, allocator::pool<item_t> > pool_tree_t;
		pool_tree_t t;
		pool_tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		pool_tree_t::HNode::iterator it = n->add_node( '0' );
		pool_tree_t::HNode::iterator q = it->add_node( 'q' );
		pool_tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		pool_tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		pool_tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		HString forward;
		for ( pool_tree_t::const_iterator tit( t.begin() ), end( t.end() ); tit != end; ++ tit )
			forward += static_cast<char>( tit->id() );
		HString backward;
		for ( pool_tree_t::const_reverse_iterator tit( t.rbegin() ), end( t.rend() ); tit != end; ++ tit )
			backward += static_cast<char>( tit->id() );
		clog << forward << endl;
		clog << backward << endl;
		reverse( backward.begin(), backward.end() );
		ENSURE_EQUALS( "forward/backward iteration failed", backward, forward );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees (replace_node) on booking allocator" )
	typedef booking_allocator<item_t> allocator_type;
	typedef HTree<item_t, allocator::ref<item_t, allocator_type> > booking_tree_t;
	typedef booking_tree_t::allocator_type ref_node_allocator_type;
	typedef ref_node_allocator_type::allocator_type true_node_allocator_type;
	typedef booking_tree_t::branch_allocator_type ref_branch_allocator_type;
	typedef ref_branch_allocator_type::allocator_type true_branch_allocator_type;

	clog << "sizeof ( item_t ) = " << sizeof ( item_t ) << endl;
	clog << "sizeof ( true_node_allocator_type::value_type ) = " << sizeof ( true_node_allocator_type::value_type ) << endl;
	clog << "sizeof ( ref_node_allocator_type::value_type ) = " << sizeof ( ref_node_allocator_type::value_type ) << endl;
	clog << "sizeof ( true_branch_allocator_type::value_type ) = " << sizeof ( true_branch_allocator_type::value_type ) << endl;
	clog << "sizeof ( ref_branch_allocator_type::value_type ) = " << sizeof ( ref_branch_allocator_type::value_type ) << endl;
	true_node_allocator_type na1( 1 );
	true_node_allocator_type na2( 2 );
	true_branch_allocator_type ba1( 1 );
	true_branch_allocator_type ba2( 2 );
	/* scope for tree destructors */ {
		booking_tree_t::node_t n = NULL;
		booking_tree_t::HNode::iterator it;
		ref_node_allocator_type rna1( &na1 );
		ref_branch_allocator_type rba1( &ba1 );
		booking_tree_t t1( rna1, rba1 );
		n = t1.create_new_root();
		**n = '@';
		booking_tree_t::HNode::iterator a = it = n->add_node( '1' );
		it->add_node( '2' );
		it->add_node( '4' );
		it->add_node( '6' );
		it = n->add_node( '3' );
		it->add_node( '8' );
		it->add_node( '0' );
		n->add_node( '5' );

		ref_node_allocator_type rna2( &na2 );
		ref_branch_allocator_type rba2( &ba2 );
		booking_tree_t t2( rna2, rba2 );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->replace_node( prev( it->end() ), &*a );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
	ENSURE( "deallocation failed on tree1 (nodes)", na1.is_valid() );
	ENSURE( "deallocation failed on tree2 (nodes)", na2.is_valid() );
	ENSURE( "deallocation failed on tree1 (branches)", ba1.is_valid() );
	ENSURE( "deallocation failed on tree2 (branches)", ba2.is_valid() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees from root (replace_node) on booking allocator" )
	typedef booking_allocator<item_t> allocator_type;
	typedef HTree<item_t, allocator::ref<item_t, allocator_type> > booking_tree_t;
	typedef booking_tree_t::allocator_type ref_node_allocator_type;
	typedef ref_node_allocator_type::allocator_type true_node_allocator_type;
	typedef booking_tree_t::branch_allocator_type ref_branch_allocator_type;
	typedef ref_branch_allocator_type::allocator_type true_branch_allocator_type;
	true_node_allocator_type na1( 1 );
	true_node_allocator_type na2( 2 );
	true_branch_allocator_type ba1( 1 );
	true_branch_allocator_type ba2( 2 );
	/* scope for tree destructors */ {
		booking_tree_t::node_t n = NULL;
		booking_tree_t::HNode::iterator it;
		ref_node_allocator_type rna1( &na1 );
		ref_branch_allocator_type rba1( &ba1 );
		booking_tree_t t1( rna1, rba1 );
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

		ref_node_allocator_type rna2( &na2 );
		ref_branch_allocator_type rba2( &ba2 );
		booking_tree_t t2( rna2, rba2 );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->replace_node( prev( it->end() ), t1.get_root() );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
	ENSURE( "deallocation failed on tree1 (nodes)", na1.is_valid() );
	ENSURE( "deallocation failed on tree2 (nodes)", na2.is_valid() );
	ENSURE( "deallocation failed on tree1 (branches)", ba1.is_valid() );
	ENSURE( "deallocation failed on tree2 (branches)", ba2.is_valid() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees (move_node) on booking allocator" )
	typedef booking_allocator<item_t> allocator_type;
	typedef HTree<item_t, allocator::ref<item_t, allocator_type> > booking_tree_t;
	typedef booking_tree_t::allocator_type ref_node_allocator_type;
	typedef ref_node_allocator_type::allocator_type true_node_allocator_type;
	typedef booking_tree_t::branch_allocator_type ref_branch_allocator_type;
	typedef ref_branch_allocator_type::allocator_type true_branch_allocator_type;
	true_node_allocator_type na1( 1 );
	true_node_allocator_type na2( 2 );
	true_branch_allocator_type ba1( 1 );
	true_branch_allocator_type ba2( 2 );
	/* scope for tree destructors */ {
		booking_tree_t::node_t n = NULL;
		booking_tree_t::HNode::iterator it;
		ref_node_allocator_type rna1( &na1 );
		ref_branch_allocator_type rba1( &ba1 );
		booking_tree_t t1( rna1, rba1 );
		n = t1.create_new_root();
		**n = '@';
		booking_tree_t::HNode::iterator a = it = n->add_node( '1' );
		it->add_node( '2' );
		it->add_node( '4' );
		it->add_node( '6' );
		it = n->add_node( '3' );
		it->add_node( '8' );
		it->add_node( '0' );
		n->add_node( '5' );

		ref_node_allocator_type rna2( &na2 );
		ref_branch_allocator_type rba2( &ba2 );
		booking_tree_t t2( rna2, rba2 );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->move_node( prev( it->end() ), &*a );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
	ENSURE( "deallocation failed on tree1 (nodes)", na1.is_valid() );
	ENSURE( "deallocation failed on tree2 (nodes)", na2.is_valid() );
	ENSURE( "deallocation failed on tree1 (branches)", ba1.is_valid() );
	ENSURE( "deallocation failed on tree2 (branches)", ba2.is_valid() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees from root (move_node) on booking allocator" )
	typedef booking_allocator<item_t> allocator_type;
	typedef HTree<item_t, allocator::ref<item_t, allocator_type> > booking_tree_t;
	typedef booking_tree_t::allocator_type ref_node_allocator_type;
	typedef ref_node_allocator_type::allocator_type true_node_allocator_type;
	typedef booking_tree_t::branch_allocator_type ref_branch_allocator_type;
	typedef ref_branch_allocator_type::allocator_type true_branch_allocator_type;
	true_node_allocator_type na1( 1 );
	true_node_allocator_type na2( 2 );
	true_branch_allocator_type ba1( 1 );
	true_branch_allocator_type ba2( 2 );
	/* scope for tree destructors */ {
		booking_tree_t::node_t n = NULL;
		booking_tree_t::HNode::iterator it;
		ref_node_allocator_type rna1( &na1 );
		ref_branch_allocator_type rba1( &ba1 );
		booking_tree_t t1( rna1, rba1 );
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

		ref_node_allocator_type rna2( &na2 );
		ref_branch_allocator_type rba2( &ba2 );
		booking_tree_t t2( rna2, rba2 );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->move_node( prev( it->end() ), t1.get_root() );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
	ENSURE( "deallocation failed on tree1 (nodes)", na1.is_valid() );
	ENSURE( "deallocation failed on tree2 (nodes)", na2.is_valid() );
	ENSURE( "deallocation failed on tree1 (branches)", ba1.is_valid() );
	ENSURE( "deallocation failed on tree2 (branches)", ba2.is_valid() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees (copy_node) on booking allocator" )
	typedef booking_allocator<item_t> allocator_type;
	typedef HTree<item_t, allocator::ref<item_t, allocator_type> > booking_tree_t;
	typedef booking_tree_t::allocator_type ref_node_allocator_type;
	typedef ref_node_allocator_type::allocator_type true_node_allocator_type;
	typedef booking_tree_t::branch_allocator_type ref_branch_allocator_type;
	typedef ref_branch_allocator_type::allocator_type true_branch_allocator_type;
	true_node_allocator_type na1( 1 );
	true_node_allocator_type na2( 2 );
	true_branch_allocator_type ba1( 1 );
	true_branch_allocator_type ba2( 2 );
	/* scope for tree destructors */ {
		booking_tree_t::node_t n = NULL;
		booking_tree_t::HNode::iterator it;
		ref_node_allocator_type rna1( &na1 );
		ref_branch_allocator_type rba1( &ba1 );
		booking_tree_t t1( rna1, rba1 );
		n = t1.create_new_root();
		**n = '@';
		booking_tree_t::HNode::iterator a = it = n->add_node( '1' );
		it->add_node( '2' );
		it->add_node( '4' );
		it->add_node( '6' );
		it = n->add_node( '3' );
		it->add_node( '8' );
		it->add_node( '0' );
		n->add_node( '5' );

		ref_node_allocator_type rna2( &na2 );
		ref_branch_allocator_type rba2( &ba2 );
		booking_tree_t t2( rna2, rba2 );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->copy_node( prev( it->end() ), &*a );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G1{246}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
	ENSURE( "deallocation failed on tree1 (nodes)", na1.is_valid() );
	ENSURE( "deallocation failed on tree2 (nodes)", na2.is_valid() );
	ENSURE( "deallocation failed on tree1 (branches)", ba1.is_valid() );
	ENSURE( "deallocation failed on tree2 (branches)", ba2.is_valid() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "across two trees from root (copy_node) on booking allocator" )
	typedef booking_allocator<item_t> allocator_type;
	typedef HTree<item_t, allocator::ref<item_t, allocator_type> > booking_tree_t;
	typedef booking_tree_t::allocator_type ref_node_allocator_type;
	typedef ref_node_allocator_type::allocator_type true_node_allocator_type;
	typedef booking_tree_t::branch_allocator_type ref_branch_allocator_type;
	typedef ref_branch_allocator_type::allocator_type true_branch_allocator_type;
	true_node_allocator_type na1( 1 );
	true_node_allocator_type na2( 2 );
	true_branch_allocator_type ba1( 1 );
	true_branch_allocator_type ba2( 2 );
	/* scope for tree destructors */ {
		booking_tree_t::node_t n = NULL;
		booking_tree_t::HNode::iterator it;
		ref_node_allocator_type rna1( &na1 );
		ref_branch_allocator_type rba1( &ba1 );
		booking_tree_t t1( rna1, rba1 );
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

		ref_node_allocator_type rna2( &na2 );
		ref_branch_allocator_type rba2( &ba2 );
		booking_tree_t t2( rna2, rba2 );
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
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{GH}c}" );
		check_consistency( t1 );
		check_consistency( t2 );
		it->copy_node( prev( it->end() ), t1.get_root() );
		check_consistency( t1 );
		check_consistency( t2 );
		ENSURE_EQUALS( "bad shape", to_string( t1 ), "@{1{246}3{80}5}" );
		ENSURE_EQUALS( "bad shape", to_string( t2 ), "%{a{DEF}b{G@{1{246}3{80}5}H}c}" );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
	ENSURE( "deallocation failed on tree1 (nodes)", na1.is_valid() );
	ENSURE( "deallocation failed on tree2 (nodes)", na2.is_valid() );
	ENSURE( "deallocation failed on tree1 (branches)", ba1.is_valid() );
	ENSURE( "deallocation failed on tree2 (branches)", ba2.is_valid() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_child_at()" ) {
		tree_t t;
		tree_t::node_t n = t.create_new_root();
		(**n) = '@';
		tree_t::HNode::iterator it = n->add_node( '0' );
		tree_t::HNode::iterator q = it->add_node( 'q' );
		tree_t::HNode::iterator w = it->add_node( 'w' );
		q->add_node( '!' );
		it = q->add_node( '#' );
		q->add_node( '$' );
		w->add_node( '%' );
		w->add_node( '^' );
		w->add_node( '&' );
		tree_t::HNode::iterator a = it = it->add_node( 'a' );
		it->add_node( 'A' );
		it->add_node( 'B' );
		it->add_node( 'C' );
		it = n->add_node( '1' );
		it->add_node( 'd' );
		tree_t::HNode::iterator e = it->add_node( 'e' );
		it->add_node( 'f' );
		it = n->add_node( '2' );
		it->add_node( 'g' );
		it->add_node( 'h' );
		it->add_node( 'i' );
		ENSURE_EQUALS( "bad shape", to_string( t ), "@{0{q{!#{a{ABC}}$}w{%^&}}1{def}2{ghi}}" );
		tree_t::node_t root( t.get_root() );
		ENSURE_THROW( "Obtained child with negative index.", root->get_child_at( -1 ), HException );
		for ( int i( 0 ); i < 3; ++ i )
			ENSURE_EQUALS( "get_child_at() from root failed", **root->get_child_at( i ), i + '0' );
		ENSURE_THROW( "Obtained child with out of range index.", root->get_child_at( 3 ), HException );
		tree_t::node_t child( root->get_child_at( 0 ) );
		ENSURE_EQUALS( "get_child_at() from child failed", **child->get_child_at( 0 ), 'q' );
		ENSURE_EQUALS( "get_child_at() from child failed", **child->get_child_at( 1 ), 'w' );
	}
	ENSURE_EQUALS( "leak", item_t::get_instance_count(), 0 );
TUT_TEARDOWN()

}


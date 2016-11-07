/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hxml.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hxml.hxx>
#include <yaal/tools/streamtools.hxx>
#include <yaal/hcore/bound.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hxml : public simple_mock<tut_yaal_tools_hxml> {
	typedef simple_mock<tut_yaal_tools_hxml> base_type;
	static HString _varTmpBuffer;
	HXml _xml;
	tut_yaal_tools_hxml( void )
		: base_type(), _xml()
		{}
	virtual ~tut_yaal_tools_hxml( void )
		{}
	static std::ostream& dump( std::ostream& out, HXml::HConstNodeProxy const& node_ ) {
		_varTmpBuffer.reserve( node_.get_level() * 2 + 2 );
		_varTmpBuffer.fillz( ' ', 0, node_.get_level() * 2 + 1 );
		if ( node_.get_type() == HXml::HNode::TYPE::NODE ) {
			if ( ! node_.get_name().is_empty() ) {
				out << _varTmpBuffer << "[" << node_.get_name() << "]<" << node_.get_level() << ">: - " << node_.get_line() << std::endl;
			}
			for ( HXml::HNode::properties_t::const_iterator it = node_.properties().begin(); it != node_.properties().end(); ++ it ) {
				out << _varTmpBuffer << "(" << it->first << ")->(";
				out << it->second << ") - " << node_.get_line() << std::endl;
			}
			if ( node_.has_childs() ) {
				_varTmpBuffer.fillz( ' ', 0, node_.get_level() * 2 + 2 );
				out << _varTmpBuffer << "{ - " << node_.get_line() << std::endl;
				for ( HXml::const_iterator it = node_.begin(); it != node_.end(); ++ it ) {
					HXml::HConstNodeProxy np;
					np = *it;
					dump( out, np );
					_varTmpBuffer.set_at( node_.get_level() * 2 + 2, 0 );
				}
				out << _varTmpBuffer << "}" << std::endl;
			}
		} else if ( node_.get_type() == HXml::HNode::TYPE::COMMENT )
			out << _varTmpBuffer << "" << node_.get_value() << "" << std::endl;
		else if ( node_.get_type() == HXml::HNode::TYPE::ENTITY )
			out << _varTmpBuffer << node_.get_value() << "(" << node_.get_name() << ")" << std::endl;
		else if ( ! node_.get_value().is_empty() )
			out << _varTmpBuffer << node_.get_value() << std::endl;
		return ( out );
	}
};

HString tut_yaal_tools_hxml::_varTmpBuffer;

TUT_TEST_GROUP( tut_yaal_tools_hxml, "yaal::tools::HXml" );

namespace {

bool deep_equals( HXml::HConstNodeProxy const& left, HXml::HConstNodeProxy const& right ) {
	HXml::HNode::TYPE type = left.get_type();
	bool equals = ( type == right.get_type() );

	if ( equals && ( type == HXml::HNode::TYPE::NODE ) )
		equals = ( left.get_name() == right.get_name() );
	if ( equals && ( type == HXml::HNode::TYPE::CONTENT ) )
		equals = ( left.get_value() == right.get_value() );
	if ( equals && ( type == HXml::HNode::TYPE::NODE ) )
		equals = ( left.has_childs() == right.has_childs() );
	if ( equals && ( type == HXml::HNode::TYPE::NODE ) )
		equals = ( left.child_count() == right.child_count() );
	if ( equals && ( type == HXml::HNode::TYPE::NODE ) )
		equals = ( left.get_level() == right.get_level() );
	if ( equals && ( type == HXml::HNode::TYPE::NODE ) ) {
		HXml::HNode::properties_t const& propLeft = left.properties();
		HXml::HNode::properties_t const& propRight = right.properties();
		HXml::HNode::properties_t::const_iterator itLeft = propLeft.begin();
		HXml::HNode::properties_t::const_iterator endLeft = propLeft.end();
		HXml::HNode::properties_t::const_iterator itRight = propRight.begin();
		HXml::HNode::properties_t::const_iterator endRight = propRight.end();
		for ( ;( itLeft != endLeft ) && equals; ++ itLeft, ++ itRight )
			equals = ( itRight != endRight ) && ( *itLeft == *itRight );
	}
	if ( equals && ( type == HXml::HNode::TYPE::NODE ) ) {
		HXml::const_iterator itLeft = left.begin();
		HXml::const_iterator endLeft = left.end();
		HXml::const_iterator itRight = right.begin();
		HXml::const_iterator endRight = right.end();
		for ( ;( itLeft != endLeft ) && equals; ++ itLeft, ++ itRight )
			equals = ( itRight != endRight ) && deep_equals( *itLeft, *itRight );
	}
	return ( equals );
}

void resort_entities( yaal::hcore::HString const& path_ ) {
	typedef yaal::hcore::HArray<yaal::hcore::HString> lines_t;
	lines_t lines;
	HFile in( path_, HFile::OPEN::READING );
	HString line;
	int entitiesStart( -1 );
	int entitiesEnd( -1 );
	while ( getline( in, line ).good() ) {
		if ( line.find( "<!ENTITY " ) == 0 ) {
			if ( entitiesStart == -1 ) {
				entitiesStart = static_cast<int>( lines.get_size() );
			}
		} else if ( ( entitiesStart != -1 ) && ( entitiesEnd == -1 ) ) {
			entitiesEnd = static_cast<int>( lines.get_size() );
		}
		lines.push_back( line );
	}
	in.close();
	if ( ( entitiesStart != -1 ) && ( entitiesEnd > entitiesStart ) ) {
		sort( lines.begin() + entitiesStart, lines.begin() + entitiesEnd );
	}
	HFile out( path_, HFile::OPEN::WRITING );
	for ( yaal::hcore::HString const& l : lines ) {
		out << l << endl;
	}
}

}

}

namespace yaal {
namespace tools {
inline bool operator == ( HXml const& left, HXml const& right ) {
	return ( deep_equals( left.get_root(), right.get_root() ) );
}

inline bool operator != ( HXml const& left, HXml const& right ) {
	return ( ! ( left == right ) );
}

inline std::ostream& operator << ( std::ostream& out, HXml const& xml ) {
	for ( HXml::entities_t::value_type const& ent : xml.entities() ) {
		out << "@: " << ent.first << "=>" << ent.second << std::endl;
	}
	HXml::HConstNodeProxy root( xml.get_root() );
	return ( !! root ? tut_yaal_tools_hxml::dump( out, root ) : out );
}
}
}

namespace tut {

TUT_UNIT_TEST( "Empty DOM." )
	HXml x;
	ENSURE( "fresh DOM not empty", ! x.get_root() );
	ENSURE_THROW( "accessing null node-proxy", x.get_root().get_type(), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Root node." )
	HXml x;
	static char const* const ROOT = "root";
	ENSURE_THROW( "invalid encoding accepted", x.create_root( ROOT, "invalid" ), HXmlException );
	x.create_root( ROOT );
	HXml::HNodeProxy n = x.get_root();
	ENSURE( "initialized DOM empty", !! n );
	ENSURE( "bad type of root element", n.get_type() == HXml::HNode::TYPE::NODE );
	ENSURE_EQUALS( "root value not stored", n.get_name(), ROOT );
	ENSURE_EQUALS( "bad level of root element", n.get_level(), 0 );
	ENSURE( "fresh node not empty", n.begin() == n.end() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "clear" )
	HXml x;
	static char const* const ROOT = "root";
	x.create_root( ROOT );
	HXml::HNodeProxy n = x.get_root();
	x.clear();
	ENSURE( "cleared DOM not empty", ! x.get_root() );
	ENSURE_THROW( "accessing null node-proxy", x.get_root().get_type(), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( "build, save, load" )
	HXml x;
	static char const* const ROOT = "root";
	static char const* const NODE = "node";
	static char const* const CHILD = "child";
	static char const* const PROP = "prop";
	static char const* const PROP_VALUE = "prop_value";
	static char const* const OUT_PATH = "out/y_test.xml";
	x.create_root( ROOT );
	HXml::HNodeProxy n = x.get_root();
	n.add_node( HXml::HNode::TYPE::NODE, NODE );
	HXml::HIterator it = n.add_node( HXml::HNode::TYPE::NODE, NODE );
	HXml::HIterator child = (*it).add_node( HXml::HNode::TYPE::NODE, CHILD );
	(*child).properties().insert( yaal::hcore::make_pair( PROP, PROP_VALUE ) );
	n.copy_node( *it );
	x.save( tools::ensure( HStreamInterface::ptr_t( new HFile( OUT_PATH, HFile::OPEN::WRITING ) ) ) );
	HXml y;
	y.load( HStreamInterface::ptr_t( new HFile( OUT_PATH, HFile::OPEN::READING ) ) );
	ENSURE_EQUALS( "DOMs differ", x, y );
	ENSURE_THROW( "copying from parent node", (*it).copy_node( n ), HXmlException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "node operations" )
	HXml xml;
	xml.create_root( "root" );
	HXml::HNodeProxy root( xml.get_root() );
	HXml::HIterator it( root.add_node( "child", "structured text" ) );
	it = root.insert_node( it, HXml::HNode::TYPE::CONTENT, "free form text" );
	root.insert_node( it, "quick", "data" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	resort_entities( "out/tut.xml" );
	ENSURE( "load xinclude failed", file_compare( "out/tut.xml", "data/xml-node-opers.xml" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "node operations (move,replace,copy,remove)" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml-node-opers.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	HXml::HNodeSet quick( xml.get_elements_by_path( "/root/quick" ) );
	HXml::HNodeSet child( xml.get_elements_by_name( "child" ) );
	HXml::HIterator copied;
	copied = child[0].copy_node( quick[0] );
	HXml::HConstNodeProxy cnp( *copied );
	ENSURE( "bad parent from copy_node", cnp.get_parent() == child[0] );
	ENSURE_NOT( "bad parent from copy_node", cnp.get_parent() == quick[0] );
	ENSURE( "bad parent from copy_node", cnp.get_parent() != quick[0] );
	ENSURE_NOT( "bad parent from copy_node", cnp.get_parent() != child[0] );
	ENSURE_THROW( "cycle created by copy", (*copied).copy_node( child[0] ), HXmlException );
	ENSURE_THROW( "cycle created by copy", (*copied).copy_node( (*copied).begin(), child[0] ), HXmlException );
	(*copied).set_name( "copied" );
	copied = child[0].copy_node( copied, quick[0] );
	(*copied).set_name( "copiedId" );
	(*(*copied).begin()).set_value( "modified value" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	ENSURE( "copy_node failed", file_compare( "out/tut.xml", "data/xml-copy.xml" ) );
	child[0].move_node( *child[0].begin() );
	++ copied;
	copied = child[0].move_node( child[0].begin(), *copied );
	ENSURE( "bad parent from move_node", (*copied).get_parent() == child[0] );
	HXml::HConstIterator cni( child[0].begin() );
	ENSURE( "bad iterator from move_node", cni == copied );
	HXml::HConstIterator last;
	last = child[0].rbegin().base();
	ENSURE_NOT( "bad iterator from move_node", cni == last );
	ENSURE_NOT( "bad iterator from move_node", cni != copied );
	ENSURE( "bad iterator from move_node", cni != last );
	ENSURE_THROW( "cycle created by move", (*copied).move_node( child[0] ), HXmlException );
	ENSURE_THROW( "cycle created by move", (*copied).move_node( (*copied).begin(), child[0] ), HXmlException );
	(*copied).set_name( "moved" );
	ENSURE( "bad xml from node", (*copied).xml() == &xml );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	ENSURE( "move_node failed", file_compare( "out/tut.xml", "data/xml-move.xml" ) );
	ENSURE_THROW( "cycle created by move", (*copied).replace_node( (*copied).begin(), child[0] ), HXmlException );
	child[0].replace_node( copied, *child[0].rbegin() );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	ENSURE( "replace_node failed", file_compare( "out/tut.xml", "data/xml-replace.xml" ) );
	child[0].remove_node( child[0].begin() );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	ENSURE( "replace_node failed", file_compare( "out/tut.xml", "data/xml-remove.xml" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "load, save" )
	HXml xml;
	HStringStream ss( "<xml></xml>" );
	ENSURE_THROW( "no encoding file loaded", xml.load( ss ), HXmlException );
	xml.init( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.parse( "/my_root/my_set/my_item" );
	xml.parse( "/my_root/my_set/my_item" ); /* mem-leak test */
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/set.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "load(file), save" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	resort_entities( "out/tut.xml" );
#ifndef __MSVCXX__
	char const expected[] = "data/xml-out.xml";
#else
	char const expected[] = "data/xml-out-278.xml";
#endif
	ENSURE( "load xinclude failed", file_compare( "out/tut.xml", expected ) );
	ENSURE_THROW( "empty document loaded", xml.load( HStreamInterface::ptr_t( new HFile( "data/xml-empty.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES | HXml::PARSER::AUTO_XINCLUDE ), HXmlException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "load(XINCLUDE) (resolve entities), save" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES | HXml::PARSER::AUTO_XINCLUDE );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut-xi.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	resort_entities( "out/tut-xi.xml" );
	ENSURE( "load xinclude failed", file_compare( "out/tut-xi.xml", "data/xml-xi-out.xml" ) );
	HXml fail;
	ENSURE_THROW( "bad xinclude loaded", fail.load( HStreamInterface::ptr_t( new HFile( "data/xml-fail-xi.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES | HXml::PARSER::AUTO_XINCLUDE ), HXmlException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "load(XINCLUDE) (no resolve entities), save" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::AUTO_XINCLUDE );
	HXml::HConstNodeSet ns( xml.get_elements_by_name( "my_sub" ) );
	HXml::HConstNodeProxy elem( ns[2].get_parent() );
	ENSURE_EQUALS( "try_node_val(it) get failed", xml::node_val( -- elem.end() ), "my precious data" );
	HXml::HConstNodeProxy special( elem.get_parent() );
	ENSURE_EQUALS( "try_attr_val(it) failed", xml::attr_val( special.begin(), "prop" ), "value" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut-xi.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	resort_entities( "out/tut-xi.xml" );
	ENSURE( "load xinclude failed", file_compare( "out/tut-xi.xml", "data/xml-xi-noent-out.xml" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "load, save, clear, handmade, save" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ) );
	xml.clear();
	xml.create_root( "xml" );
	HXml::HNodeProxy root = xml.get_root();
	root.add_node( HXml::HNode::TYPE::CONTENT, "Hello World!" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/hello.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "init, apply_style, parse, save, clear, handmade, save" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
	xml.clear();
	xml.create_root( "xml" );
	HXml::HNodeProxy root;
	root = xml.get_root();
	root.add_node( HXml::HNode::TYPE::CONTENT, "Hello World!" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/hello.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "apply stylesheet" )
	_xml.init( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	_xml.apply_style( "data/style.xml" );
	_xml.parse();
	std::cout << _xml;
TUT_TEARDOWN()

TUT_UNIT_TEST( "build, apply stylesheet" )
	HXml x;
	static char const* const ROOT = "root";
	static char const* const NODE = "node";
	static char const* const CHILD = "my_item";
	static char const* const PROP = "prop";
	static char const* const PROP_VALUE = "prop_value";
	static char const* const OUT_PRE_PATH = "out/pre_style.xml";
	static char const* const OUT_POST_PATH = "out/post_style.xml";
	x.create_root( ROOT );
	HXml::HNodeProxy n = x.get_root();
	n.add_node( HXml::HNode::TYPE::NODE, NODE );
	HXml::HIterator it = n.add_node( HXml::HNode::TYPE::NODE, NODE );
	HXml::HIterator child = (*it).add_node( HXml::HNode::TYPE::NODE, CHILD );
	(*child).properties().insert( yaal::hcore::make_pair( PROP, PROP_VALUE ) );
	n.copy_node( *it );
	x.save( tools::ensure( HStreamInterface::ptr_t( new HFile( OUT_PRE_PATH, HFile::OPEN::WRITING ) ) ) );
	x.apply_style( "data/style.xml" );
	x.parse();
	x.save( tools::ensure( HStreamInterface::ptr_t( new HFile( OUT_POST_PATH, HFile::OPEN::WRITING ) ) ) );
	HXml y;
	y.load( HStreamInterface::ptr_t( new HFile( OUT_POST_PATH, HFile::OPEN::READING ) ) );
	ENSURE_EQUALS( "DOMs differ", x, y );
TUT_TEARDOWN()

TUT_UNIT_TEST( "init, parse, apply, save" )
	HString string;
	HFile file;
	char const* doc = ( setup._argc > 1 ) ? setup._argv[ 1 ] : "./data/xml.xml";
	char const* style = ( setup._argc > 2 ) ? setup._argv[ 2 ] : "./data/style.xml";
	char const* out = ( setup._argc > 3 ) ? setup._argv[ 3 ] : "./out/tut.xml";
	char const* path = ( setup._argc > 4 ) ? setup._argv[ 4 ] : NULL;
	if ( setup._verbose ) {
		if ( file.open( doc, HFile::OPEN::READING ) )
			cout << file.get_error() << ": " << file.get_path() << endl;
		else {
			while ( file.read_line( string ) >= 0 )
				cout << string << endl;
			file.close();
		}
	}
	_xml.init( HStreamInterface::ptr_t( new HFile( doc, HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	_xml.apply_style( style );
	_xml.parse( path );
	_xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( out, HFile::OPEN::WRITING ) ) ) );
	return;
TUT_TEARDOWN()

TUT_UNIT_TEST( "load -> console dump" )
	char const* doc = ( setup._argc > 1 ) ? setup._argv[ 1 ] : "./data/xml.xml";
	_xml.load( HStreamInterface::ptr_t( new HFile( doc, HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	if ( cout.is_valid() )
		_xml.save( cout );
	std::clog << _xml;
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse bofere apply_style and after apply_style" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.parse();
	std::clog << xml;
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/raw.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	std::clog << xml;
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "conversion errors" );
	HStringStream src( "<?xml version=\"1.0\" encoding=\"ISO-8859-2\"?><pi>&#960;</pi>" );
	HXml xml;
	xml.load( src, HXml::PARSER::IGNORE_CONVERSION_ERRORS );
	HXml::HConstNodeProxy root( xml.get_root() );
	ENSURE_EQUALS( "ignoring conversion error failed", xml::node_val( root ), "π" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HXml copy." )
	HXml copy;
	/* scope for intermediate */ {
		HXml intermediate;
		/* scope for xml */ {
			HXml xml;
			xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
			xml.parse();
			intermediate = xml;
			std::clog << xml;
			xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/raw.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
		}
		intermediate.apply_style( "./data/style.xml" );
		intermediate.parse();
		copy = intermediate;
	}
	std::clog << copy;
	copy.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "HXml move." )
	HXml copy;
	/* scope for intermediate */ {
		HXml intermediate;
		/* scope for xml */ {
			HXml xml;
			xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
			xml.parse();
			HXml tmp( yaal::move( xml ) );
			std::clog << xml;
			intermediate = yaal::move( tmp );
			intermediate.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/raw.xml", HFile::OPEN::WRITING ) ) ), HXml::GENERATOR::INDENT );
		}
		intermediate.apply_style( "./data/style.xml" );
		intermediate.parse();
		copy = yaal::move( intermediate );
	}
	std::clog << copy;
	copy.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_element_by_path == 1" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_path( "/my_root/my_node/my_sub/" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 1 );
	ENSURE_NOT( "bad emptiness status", nodeSet.is_empty() );
	dump( std::clog, nodeSet[0] );
	ENSURE_EQUALS( "bad node name", nodeSet[0].get_name(), "my_sub" );
	ENSURE_EQUALS( "bad node value", (*nodeSet[0].begin()).get_value(), "node" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_element_by_path == 0" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_path( "/my_root/my_node/my_none/" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 0 );
	ENSURE( "bad emptiness status", nodeSet.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_element_by_path == many" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HNodeSet nodeSet( xml.get_elements_by_path( "/my_root/my_set/uber_item/line_no" ) );
	HXml::HConstNodeSet constNodeSet = const_cast<HXml const&>( xml ).get_elements_by_path( "/my_root/my_set/uber_item/line_no" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 3 );
	ENSURE_NOT( "bad emptiness status", nodeSet.is_empty() );
	char const values[][3] = { "17", "18", "20" };
	int i( 0 );
	for ( HXml::HConstNodeSet::HConstIterator it( constNodeSet.begin() ), end( constNodeSet.end() ); it != end; ++ it, ++ i ) {
		dump( std::clog, *it );
		ENSURE_EQUALS( "bad node name", (*it).get_name(), "line_no" );
		ENSURE( "bad node from const", (*it) == constNodeSet[i] );
		ENSURE_EQUALS( "bad node value", (*(*it).begin()).get_value(), values[i] );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_element_by_name == 0" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_name( "my_none" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 0 );
	ENSURE( "bad emptiness status", nodeSet.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( "get_element_by_name == many" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HNodeSet nodeSet( xml.get_elements_by_name( "my_sub" ) );
	HXml::HConstNodeSet constNodeSet( const_cast<HXml const&>( xml ).get_elements_by_name( "my_sub" ) );
	HXml::HConstNodeProxy root( xml.get_root() );
	HXml::HConstNodeSet constRootNodeSet( root.get_elements_by_name( "my_sub" ) );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 4 );
	ENSURE_EQUALS( "bad number of elements", constNodeSet.size(), 4 );
	ENSURE_NOT( "bad emptiness status", nodeSet.is_empty() );
	ENSURE_NOT( "bad emptiness status", nodeSet.empty() );
	int i( 0 );
	HXml::HNodeSet::HIterator end;
	end = nodeSet.end();
	for ( HXml::HNodeSet::HIterator it( nodeSet.begin() ); it != end; ++ it, ++ i ) {
		dump( std::clog, *it );
		ENSURE_EQUALS( "bad node name", (*it).get_name(), "my_sub" );
		ENSURE( "bad node from const", (*it) == constNodeSet[i] );
		ENSURE( "bad node from const", (*it) == constRootNodeSet[i] );
		HXml::HConstNodeSet::HConstIterator cit;
		cit = it;
		ENSURE( "bad copy iter", cit == it );
		ENSURE_NOT( "bad copy iter", cit != it );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "reverse iteration" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSetConst = xml.get_elements_by_path( "/my_root/my_set" );
	ENSURE_NOT( "bad emptiness status", nodeSetConst.is_empty() );
	int i( 0 );
	char const res[][8] = {
		"four",
		"three",
		"two",
		"one"
	};
	for ( HXml::HConstNodeProxy::const_reverse_iterator it( nodeSetConst[0].rbegin() ), end( nodeSetConst[0].rend() ); it != end; ++ it ) {
		if ( (*it).get_type() == HXml::HNode::TYPE::NODE ) {
			ENSURE_EQUALS(
				"bad rev it",
				(*find_if( (*it).begin(), (*it).end(), call( &HXml::HConstNodeProxy::get_type, _1 ) == HXml::HNode::TYPE::CONTENT )).get_value(),
				res[i++]
			);
		}
	}
	HXml::HNodeSet nodeSet = xml.get_elements_by_path( "/my_root/my_set" );
	i = 0;
	for ( HXml::HNodeProxy::reverse_iterator it( nodeSet[0].rbegin() ), end( nodeSet[0].rend() ); it != end; ++ it ) {
		if ( (*it).get_type() == HXml::HNode::TYPE::NODE ) {
			ENSURE_EQUALS(
				"bad rev it",
				(*find_if( (*it).begin(), (*it).end(), call( &HXml::HNodeProxy::get_type, _1 ) == HXml::HNode::TYPE::CONTENT )).get_value(),
				res[i++]
			);
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "try_node_val_by path" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	HXml::HConstNodeProxy root( xml.get_root() );
	ENSURE_EQUALS( "try_node_val_by failed", *xml::try_node_val_by_path( root.begin(), "/my_node/my_sub" ), "node" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "try_attr_val_by path" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	HXml::HNodeSet ns( xml.get_elements_by_name( "my_special" ) );
	HXml::HNodeSet::HIterator itX( ns.begin() );
	HXml::HNodeSet::HIterator it( itX );
	ENSURE_EQUALS( "try_attr_val_by failed", *xml::try_attr_val_by_path( (*it).begin(), "/my_sub/my_element/prop" ), "value" );
TUT_TEARDOWN()

}


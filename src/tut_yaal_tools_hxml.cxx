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
					dump( out, *it );
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
	HXml::HNode::TYPE::type_t type = left.get_type();
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
	for ( HXml::const_entity_iterator it( xml.entity_begin() ), end( xml.entity_end() ); it != end; ++ it )
		out << "@: " << it->first << "=>" << it->second << std::endl;
	return ( tut_yaal_tools_hxml::dump( out, xml.get_root() ) );
}
}
}

namespace tut {

TUT_UNIT_TEST( 1, "Empty DOM." )
	HXml x;
	ENSURE( "fresh DOM not empty", ! x.get_root() );
	ENSURE_THROW( "accessing null node-proxy", x.get_root().get_type(), HFailedAssertion );
TUT_TEARDOWN()


TUT_UNIT_TEST( 2, "Root node." )
	HXml x;
	static char const* const ROOT = "root";
	x.create_root( ROOT );
	HXml::HNodeProxy n = x.get_root();
	ENSURE( "initialized DOM empty", !! n );
	ENSURE( "bad type of root element", n.get_type() == HXml::HNode::TYPE::NODE );
	ENSURE_EQUALS( "root value not stored", n.get_name(), ROOT );
	ENSURE_EQUALS( "bad level of root element", n.get_level(), 0 );
	ENSURE( "fresh node not empty", n.begin() == n.end() );
TUT_TEARDOWN()


TUT_UNIT_TEST( 3, "clear" )
	HXml x;
	static char const* const ROOT = "root";
	x.create_root( ROOT );
	HXml::HNodeProxy n = x.get_root();
	x.clear();
	ENSURE( "cleared DOM not empty", ! x.get_root() );
	ENSURE_THROW( "accessing null node-proxy", x.get_root().get_type(), HFailedAssertion );
TUT_TEARDOWN()


TUT_UNIT_TEST( 4, "build, save, load" )
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
	ENSURE_THROW( "copying from parent node", (*it).copy_node( n ), HFailedAssertion );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "load, save" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.parse( "/my_root/my_set/my_item" );
	xml.parse( "/my_root/my_set/my_item" ); /* mem-leak test */
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/set.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "load, save" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "load, save, clear, handmade, save" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::WRITING ) ) ) );
	xml.clear();
	xml.create_root( "xml" );
	HXml::HNodeProxy root = xml.get_root();
	root.add_node( HXml::HNode::TYPE::CONTENT, "Hello World!" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/hello.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "init, apply_style, parse, save, clear, handmade, save" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
	xml.clear();
	xml.create_root( "xml" );
	HXml::HNodeProxy root = xml.get_root();
	root.add_node( HXml::HNode::TYPE::CONTENT, "Hello World!" );
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "out/hello.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "apply stylesheet" )
	_xml.init( HStreamInterface::ptr_t( new HFile( "data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	_xml.apply_style( "data/style.xml" );
	_xml.parse();
	std::cout << _xml;
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "init, parse, apply, save" )
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

TUT_UNIT_TEST( 11, "load -> console dump" )
	char const* doc = ( setup._argc > 1 ) ? setup._argv[ 1 ] : "./data/xml.xml";
	_xml.load( HStreamInterface::ptr_t( new HFile( doc, HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	if ( cout.is_valid() )
		_xml.save( cout );
	std::clog << _xml;
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "parse bofere apply_style and after apply_style" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.parse();
	std::clog << xml;
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/raw.xml", HFile::OPEN::WRITING ) ) ), true );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	std::clog << xml;
	xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "HXml copy." )
	HXml copy; {
		HXml intermediate; {
			HXml xml;
			xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
			xml.parse();
			intermediate = xml;
			std::clog << xml;
			xml.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/raw.xml", HFile::OPEN::WRITING ) ) ), true );
		}
		intermediate.apply_style( "./data/style.xml" );
		intermediate.parse();
		copy = intermediate;
	}
	std::clog << copy;
	copy.save( tools::ensure( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::WRITING ) ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( 14, "get_element_by_path == 1" )
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

TUT_UNIT_TEST( 15, "get_element_by_path == 0" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_path( "/my_root/my_node/my_none/" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 0 );
	ENSURE( "bad emptiness status", nodeSet.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 16, "get_element_by_path == many" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_path( "/my_root/my_set/uber_item/line_no" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 3 );
	ENSURE_NOT( "bad emptiness status", nodeSet.is_empty() );
	char const values[][3] = { "16", "17", "19" };
	int i( 0 );
	for ( HXml::HConstNodeSet::HConstIterator it( nodeSet.begin() ), end( nodeSet.end() ); it != end; ++ it, ++ i ) {
		dump( std::clog, *it );
		ENSURE_EQUALS( "bad node name", (*it).get_name(), "line_no" );
		ENSURE_EQUALS( "bad node value", (*(*it).begin()).get_value(), values[i] );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( 17, "get_element_by_name == 0" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_name( "my_none" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 0 );
	ENSURE( "bad emptiness status", nodeSet.is_empty() );
TUT_TEARDOWN()

TUT_UNIT_TEST( 18, "get_element_by_name == many" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml", HFile::OPEN::READING ) ), HXml::PARSER::RESOLVE_ENTITIES );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	HXml::HConstNodeSet nodeSet = xml.get_elements_by_name( "my_sub" );
	ENSURE_EQUALS( "bad number of elements", nodeSet.get_size(), 3 );
	ENSURE_NOT( "bad emptiness status", nodeSet.is_empty() );
	int i( 0 );
	for ( HXml::HConstNodeSet::HConstIterator it( nodeSet.begin() ), end( nodeSet.end() ); it != end; ++ it, ++ i ) {
		dump( std::clog, *it );
		ENSURE_EQUALS( "bad node name", (*it).get_name(), "my_sub" );
	}
TUT_TEARDOWN()

}


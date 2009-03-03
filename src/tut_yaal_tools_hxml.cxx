/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hxml.cxx - this file is integral part of `tress' project.

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

#include "setup.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut
{

struct tut_yaal_tools_hxml
	{
	static HString f_oVarTmpBuffer;
	HXml f_oXml;
	tut_yaal_tools_hxml( void ) : f_oXml()
		{}
	virtual ~tut_yaal_tools_hxml( void )
		{}
	static std::ostream& dump( std::ostream& out, HXml::HConstNodeProxy const& a_rsNode )
		{
		f_oVarTmpBuffer.hs_realloc( a_rsNode.get_level() * 2 + 3 );
		f_oVarTmpBuffer.fillz( ' ', a_rsNode.get_level() * 2 + 1 );
		if ( a_rsNode.get_type() == HXml::HNode::TYPE::D_NODE )
			{
			if ( ! a_rsNode.get_name().is_empty() )
				out << f_oVarTmpBuffer << "[" << a_rsNode.get_name() << "]<" << a_rsNode.get_level() << ">:" << std::endl;
			for ( HXml::HNode::properties_t::const_iterator it = a_rsNode.properties().begin(); it != a_rsNode.properties().end(); ++ it )
				{
				out << f_oVarTmpBuffer << "(" << it->first << ")->(";
				out << it->second << ")" << std::endl;
				}
			if ( a_rsNode.has_childs() )
				{
				f_oVarTmpBuffer.fillz( ' ', a_rsNode.get_level() * 2 + 2 );
				out << f_oVarTmpBuffer << "{" << std::endl;
				for ( HXml::const_iterator it = a_rsNode.begin(); it != a_rsNode.end(); ++ it )
					{
					dump( out, *it );
					f_oVarTmpBuffer.set_at( a_rsNode.get_level() * 2 + 2, 0 );
					}
				out << f_oVarTmpBuffer << "}" << std::endl;
				}
			}
		else if ( ! a_rsNode.get_value().is_empty() )
			out << f_oVarTmpBuffer << a_rsNode.get_value() << std::endl;
		return ( out );
		}
	};

HString tut_yaal_tools_hxml::f_oVarTmpBuffer;

typedef test_group<tut_yaal_tools_hxml> tut_group;
typedef tut_group::object module;
tut_group tut_yaal_tools_hxml_group( "yaal::tools::HXml" );

std::ostream& operator << ( std::ostream& out, HXml const& xml )
	{
	return ( tut_yaal_tools_hxml::dump( out, xml.get_root() ) );
	}

bool deep_equals( HXml::HConstNodeProxy const& left, HXml::HConstNodeProxy const& right )
	{
	HXml::HNode::TYPE::type_t type = left.get_type();
	bool equals = ( type == right.get_type() );

	if ( equals && ( type == HXml::HNode::TYPE::D_NODE ) )
		equals = ( left.get_name() == right.get_name() );
	if ( equals && ( type == HXml::HNode::TYPE::D_CONTENT ) )
		equals = ( left.get_value() == right.get_value() );
	if ( equals && ( type == HXml::HNode::TYPE::D_NODE ) )
		equals = ( left.has_childs() == right.has_childs() );
	if ( equals && ( type == HXml::HNode::TYPE::D_NODE ) )
		equals = ( left.child_count() == right.child_count() );
	if ( equals && ( type == HXml::HNode::TYPE::D_NODE ) )
		equals = ( left.get_level() == right.get_level() );
	if ( equals && ( type == HXml::HNode::TYPE::D_NODE ) )
		{
		HXml::HNode::properties_t const& propLeft = left.properties();
		HXml::HNode::properties_t const& propRight = right.properties();
		HXml::HNode::properties_t::const_iterator itLeft = propLeft.begin();
		HXml::HNode::properties_t::const_iterator endLeft = propLeft.end();
		HXml::HNode::properties_t::const_iterator itRight = propRight.begin();
		HXml::HNode::properties_t::const_iterator endRight = propRight.end();
		for ( ;( itLeft != endLeft ) && equals; ++ itLeft, ++ itRight )
			equals = ( itRight != endRight ) && ( *itLeft == *itRight );
		}
	if ( equals && ( type == HXml::HNode::TYPE::D_NODE ) )
		{
		HXml::const_iterator itLeft = left.begin();
		HXml::const_iterator endLeft = left.end();
		HXml::const_iterator itRight = right.begin();
		HXml::const_iterator endRight = right.end();
		for ( ;( itLeft != endLeft ) && equals; ++ itLeft, ++ itRight )
			equals = ( itRight != endRight ) && deep_equals( *itLeft, *itRight );
		}
	return ( equals );
	}

bool operator == ( HXml const& left, HXml const& right )
	{
	return ( deep_equals( left.get_root(), right.get_root() ) );
	}

bool operator != ( HXml const& left, HXml const& right )
	{
	return ( ! ( left == right ) );
	}


TUT_UNIT_TEST_N( 1, "/* Empty DOM. */" )
	HXml x;
	ensure( "fresh DOM not empty", ! x.get_root() );
	try
		{
		x.get_root().get_type();
		fail( "accessing null node-proxy" );
		}
	catch ( HFailedAssertion& )
		{
		// ok
		}
TUT_TEARDOWN()


TUT_UNIT_TEST_N( 2, "/* Root node. */" )
	HXml x;
	static char const* const D_ROOT = "root";
	x.create_root( D_ROOT );
	HXml::HNodeProxy n = x.get_root();
	ensure( "initialized DOM empty", !! n );
	ensure_equals( "root value not stored", n.get_name(), D_ROOT );
	ensure_equals( "bad level of root element", n.get_level(), 0 );
	ensure( "bad type of root element", n.get_type() == HXml::HNode::TYPE::D_NODE );
	ensure( "fresh node not empty", n.begin() == n.end() );
TUT_TEARDOWN()


TUT_UNIT_TEST_N( 3, "/* clear */" )
	HXml x;
	static char const* const D_ROOT = "root";
	x.create_root( D_ROOT );
	HXml::HNodeProxy n = x.get_root();
	x.clear();
	ensure( "cleared DOM not empty", ! x.get_root() );
	try
		{
		x.get_root().get_type();
		fail( "accessing null node-proxy" );
		}
	catch ( HFailedAssertion& )
		{
		// ok
		}
TUT_TEARDOWN()


TUT_UNIT_TEST_N( 4, "/* build, save, load */" )
	HXml x;
	static char const* const D_ROOT = "root";
	static char const* const D_NODE = "node";
	static char const* const D_CHILD = "child";
	static char const* const D_PROP = "prop";
	static char const* const D_PROP_VALUE = "prop_value";
	static char const* const D_OUT_PATH = "out/y_test.xml";
	x.create_root( D_ROOT );
	HXml::HNodeProxy n = x.get_root();
	n.add_node( HXml::HNode::TYPE::D_NODE, D_NODE );
	HXml::HIterator it = n.add_node( HXml::HNode::TYPE::D_NODE, D_NODE );
	HXml::HIterator child = (*it).add_node( HXml::HNode::TYPE::D_NODE, D_CHILD );
	(*child).properties().insert( yaal::hcore::make_pair( D_PROP, D_PROP_VALUE ) );
	n.copy_node( *it );
	x.save( HStreamInterface::ptr_t( new HFile( D_OUT_PATH, HFile::OPEN::D_WRITING ) ) );
	HXml y;
	y.load( HStreamInterface::ptr_t( new HFile( D_OUT_PATH ) ) );
	ensure_equals( "DOMs differ", x, y );
	try
		{
		(*it).copy_node( n );
		fail( "copying from parent node" );
		}
	catch ( HFailedAssertion& )
		{
		// ok
		}
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 5, "/* load, save */" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "data/xml.xml" ) ) );
	xml.parse( "/my_root/my_set/my_item" );
	xml.parse( "/my_root/my_set/my_item" ); /* mem-leak test */
	xml.save( HStreamInterface::ptr_t( new HFile( "out/set.xml", HFile::OPEN::D_WRITING ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 6, "/* load, save */" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml" ) ) );
	xml.save( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::D_WRITING ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 7, "/* load, save, clear, handmade, save */" )
	HXml xml;
	xml.load( HStreamInterface::ptr_t( new HFile( "data/xml.xml" ) ) );
	xml.save( HStreamInterface::ptr_t( new HFile( "out/tut.xml", HFile::OPEN::D_WRITING ) ) );
	xml.clear();
	xml.create_root( "xml" );
	HXml::HNodeProxy root = xml.get_root();
	root.add_node( HXml::HNode::TYPE::D_CONTENT, "Hello World!" );
	xml.save( HStreamInterface::ptr_t( new HFile( "out/hello.xml", HFile::OPEN::D_WRITING ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 8, "/* init, apply_style, parse, save, clear, handmade, save */" )
	HXml xml;
	xml.init( HStreamInterface::ptr_t( new HFile( "./data/xml.xml" ) ) );
	xml.apply_style( "./data/style.xml" );
	xml.parse();
	xml.save( HStreamInterface::ptr_t( new HFile( "./out/tut.xml", HFile::OPEN::D_WRITING ) ) );
	xml.clear();
	xml.create_root( "xml" );
	HXml::HNodeProxy root = xml.get_root();
	root.add_node( HXml::HNode::TYPE::D_CONTENT, "Hello World!" );
	xml.save( HStreamInterface::ptr_t( new HFile( "out/hello.xml", HFile::OPEN::D_WRITING ) ) );
TUT_TEARDOWN()

TUT_UNIT_TEST_N( 9, "/* apply stylesheet */" )
	f_oXml.init( HStreamInterface::ptr_t( new HFile( "data/xml.xml" ) ) );
	f_oXml.apply_style( "data/style.xml" );
	f_oXml.parse();
	dump( std::cout, f_oXml.get_root() );
TUT_TEARDOWN()

std::ostream& operator << ( std::ostream& out, yaal::hcore::HString const& s )
	{
	out << s.raw();
	return ( out );
	}

TUT_UNIT_TEST_N( 10, "/* init, parse, apply, save */" )
	HString string;
	HFile file;
	char const* doc = ( setup.f_iArgc > 1 ) ? setup.f_ppcArgv[ 1 ] : "./data/xml.xml";
	char const* style = ( setup.f_iArgc > 2 ) ? setup.f_ppcArgv[ 2 ] : "./data/style.xml";
	char const* out = ( setup.f_iArgc > 3 ) ? setup.f_ppcArgv[ 3 ] : "./out/tut.xml";
	char const* path = ( setup.f_iArgc > 4 ) ? setup.f_ppcArgv[ 4 ] : NULL;
	if ( setup.f_bVerbose )
		{
		if ( file.open( doc ) )
			cout << file.get_error() << ": " << file.get_path() << endl;
		else
			{
			while ( file.read_line( string, HFile::READ::D_STRIP_NEWLINES ) >= 0 )
				cout << string << endl;
			file.close();
			}
		}
	f_oXml.init( HStreamInterface::ptr_t( new HFile( doc ) ) );
	f_oXml.apply_style( style );
	f_oXml.parse( path );
	f_oXml.save( HStreamInterface::ptr_t( new HFile( out, HFile::OPEN::D_WRITING ) ) );
	return;
TUT_TEARDOWN()

}


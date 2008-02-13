/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hxml.cxx - this file is integral part of `tress' project.

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

#include "setup.h"

using namespace tut;
using namespace std;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hconsole;
using namespace yaal::tools;
using namespace yaal::tools::util;

namespace tut
{

struct tut_yaal_tools_hxml
	{
	HString f_oVarTmpBuffer;
	HXml f_oXml;
	void dump( HXml::HNodeProxy const& a_rsNode )
		{
		f_oVarTmpBuffer.hs_realloc ( a_rsNode.get_level() * 2 + 3 );
		f_oVarTmpBuffer.fill( ' ', a_rsNode.get_level() * 2 );
		f_oVarTmpBuffer.set_at( a_rsNode.get_level() * 2, 0 );
		if ( a_rsNode.get_type() == HXml::HNode::TYPE::D_NODE )
			{
			if ( ! a_rsNode.get_name().is_empty() )
				cout << f_oVarTmpBuffer << "[" << a_rsNode.get_name() << "]<" << a_rsNode.get_level() << ">:" << endl;
			for ( HXml::HNode::properties_t::HIterator it = a_rsNode.properties().begin(); it != a_rsNode.properties().end(); ++ it )
				{
				cout << f_oVarTmpBuffer << "(" << it->first << ")->(";
				cout << it->second << ")" << endl;
				}
			if ( a_rsNode.has_childs() )
				{
				f_oVarTmpBuffer.fill( ' ', a_rsNode.get_level() * 2 + 2 );
				f_oVarTmpBuffer.set_at( a_rsNode.get_level() * 2 + 2, 0 );
				cout << f_oVarTmpBuffer << "{" << endl;
				for ( HXml::iterator it = a_rsNode.begin(); it != a_rsNode.end(); ++ it )
					{
					dump ( *it );
					f_oVarTmpBuffer.set_at( a_rsNode.get_level() * 2 + 2, 0 );
					}
				cout << f_oVarTmpBuffer << "}" << endl;
				}
			}
		else if ( ! a_rsNode.get_value().is_empty() )
			cout << f_oVarTmpBuffer << a_rsNode.get_value() << endl;
		return;
		}
	};

typedef test_group < tut_yaal_tools_hxml > tut_group;
typedef tut_group::object module;
tut_group tut_yaal_tools_hxml_group ( "yaal::tools::HXml" );

/* init, parse */
template<>
template<>
void module::test<1>( void )
	{
	HString string;
	HFile file;
	if ( setup.f_iArgc < 2 )
		fail ( "You need to specify one argument for this test" );
	if ( setup.f_bVerbose )
		{
		if ( file.open( setup.f_ppcArgv[ 1 ] ) )
			cout << file.get_error() << ": " << file.get_path() << endl;
		else
			{
			while ( file.read_line( string, HFile::D_STRIP_NEWLINES ) >= 0 )
				cout << string << endl;
			file.close();
			}
		}
	f_oXml.init( setup.f_ppcArgv[ 1 ] );
	if ( setup.f_iArgc > 2 )
		f_oXml.parse( const_cast<char*>( setup.f_ppcArgv[ 2 ] ) );
	else
		f_oXml.parse();
	dump ( f_oXml.get_root ( ) );
	return;
	}

/* load, save */
template<>
template<>
void module::test<2>( void )
	{
	HXml xml;
	xml.load( "data/xml.xml" );
	xml.save( "out/tut.xml" );
	}

/* apply stylesheet */
template<>
template<>
void module::test<3>( void )
	{
	f_oXml.init( "data/xml.xml" );
	f_oXml.apply_style( "data/style.xml" );
	f_oXml.parse();
	dump( f_oXml.get_root() );
	}

}


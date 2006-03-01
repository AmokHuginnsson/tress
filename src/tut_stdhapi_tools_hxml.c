/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_stdhapi_tools_hxml.c - this file is integral part of `tress' project.

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

#include "TUT/tut.h"

#include <stdhapi.h>
M_CVSID ( "$CVSHeader$" )

#include "setup.h"

using namespace tut;
using namespace std;
using namespace stdhapi;
using namespace stdhapi::hcore;
using namespace stdhapi::hconsole;
using namespace stdhapi::tools;
using namespace stdhapi::tools::util;

namespace tut
{

struct tut_stdhapi_tools_hxml
	{
	HString f_oVarTmpBuffer;
	HXml f_oXml;
	void dump ( HXml::ONode & a_rsNode )
		{
		HString l_oPropertyName, l_oPropertyValue, * l_poContent = NULL;
		HXml::ONode * l_psNode = NULL;
		if ( a_rsNode.f_iLevel < 0 )
			return;
		f_oVarTmpBuffer.hs_realloc ( a_rsNode.f_iLevel * 2 + 3 );
		memset ( f_oVarTmpBuffer.raw ( ), ' ', a_rsNode.f_iLevel * 2 );
		f_oVarTmpBuffer [ a_rsNode.f_iLevel * 2 ] = 0;
		if ( ! a_rsNode.f_oName.is_empty ( ) )
			cout << f_oVarTmpBuffer << "[" << a_rsNode.f_oName << "]<" << a_rsNode.f_iLevel << ">:" << endl;
		while ( a_rsNode.f_oProperties.iterate ( l_oPropertyName,
					l_oPropertyValue ) )
			{
			cout << f_oVarTmpBuffer << "(" << l_oPropertyName << ")->(";
			cout << l_oPropertyValue << ")" << endl;
			}
		memset ( f_oVarTmpBuffer.raw ( ), ' ', a_rsNode.f_iLevel * 2 + 2 );
		f_oVarTmpBuffer [ a_rsNode.f_iLevel * 2 + 2 ] = 0;
		cout << f_oVarTmpBuffer << "{" << endl;
		if ( a_rsNode.f_oContents.quantity ( ) )
			l_poContent = & a_rsNode.f_oContents.go ( 0 );
		if ( a_rsNode.f_oChilds.quantity ( ) )
			l_psNode = & a_rsNode.f_oChilds.go ( 0 );
		if ( a_rsNode.f_oTypes.quantity ( ) )
			{
			for ( HXml::ONode::type_t * l_peType = & a_rsNode.f_oTypes.go ( 0 );
					l_peType; l_peType = a_rsNode.f_oTypes.to_tail ( 1, HList < int >::D_TREAT_AS_OPENED ) )
				{
				if ( ( * l_peType ) == HXml::ONode::D_NODE )
					{
					dump ( * l_psNode );
					l_psNode = a_rsNode.f_oChilds.to_tail ( );
					f_oVarTmpBuffer [ a_rsNode.f_iLevel * 2 + 2 ] = 0;
					}
				else
					{
					if ( l_poContent->get_length ( ) )
						cout << f_oVarTmpBuffer << ( * l_poContent ) << endl;
					l_poContent = a_rsNode.f_oContents.to_tail ( );
					}
				}
			}
		cout << f_oVarTmpBuffer << "}" << endl;
		return;
		}
	};

typedef test_group < tut_stdhapi_tools_hxml > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_tools_hxml_group ( "stdhapi::tools::HXml" );

template < >
template < >
void module::test<1> ( void )
	{
	HString string;
	HFile file;
	if ( setup.f_iArgc < 2 )
		fail ( "You need to specify one argument for this test" );
	if ( setup.f_bVerbose )
		{
		if ( file.open ( setup.f_ppcArgv [ 1 ] ) )
			cout << file.get_error ( ) << ": " << file.get_path ( ) << endl;
		else
			{
			while ( file.read_line ( string, HFile::D_STRIP_NEWLINES ) >= 0 )
				cout << string << endl;
			file.close ( );
			}
		}
	f_oXml.init ( setup.f_ppcArgv [ 1 ] );
	if ( setup.f_iArgc > 2 )
		f_oXml.parse ( const_cast < char * > ( setup.f_ppcArgv [ 2 ] ) );
	else
		f_oXml.parse ( );
	dump ( f_oXml.get_root ( ) );
	}

}


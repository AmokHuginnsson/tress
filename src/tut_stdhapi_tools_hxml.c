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
M_CVSID ( "$CVSHeader$" );

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

class HXmlDump : public HXml
	{
public:
	void * parse ( void * );
	};

void * HXmlDump::parse ( void * a_pvPath )
	{
	int l_iLevel = - 1;
	char const * l_pcPath = "/";
	HString l_oPropertyName, l_oPropertyValue;
	HXml::ONode l_sNode;
	if ( a_pvPath )
		l_pcPath = static_cast < char * > ( a_pvPath );
	while ( ( l_iLevel = iterate ( l_sNode, l_pcPath ) ) >= 0 )
		{
		cout << "[" << l_sNode.f_oName << "]<" << l_sNode.f_iLevel << ">:" << endl;
		while ( l_sNode.f_oProperties.iterate ( l_oPropertyName,
					l_oPropertyValue ) )
			{
			cout << "(" << l_oPropertyName << ")->(";
			cout << l_oPropertyValue << ")" << endl;
			}
		cout << "{" << l_sNode.f_oContents << "}" << endl;
		if ( l_iLevel != l_sNode.f_iLevel )
			{
			cout << "LEVEL: " << l_sNode.f_iLevel << ", RLEVEL: " << l_iLevel << endl;
			fail ( "bad returned level" );
			}
		}
	return ( NULL );
	}

struct tut_stdhapi_tools_hxml
	{
	};

typedef test_group < tut_stdhapi_tools_hxml > tut_group;
typedef tut_group::object module;
tut_group tut_stdhapi_tools_hxml_group ( "stdhapi::tools::HXml" );

template < >
template < >
void module::test<1> ( void )
	{
	HString string;
	HXmlDump xml;
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
	xml.init ( setup.f_ppcArgv [ 1 ] );
	if ( setup.f_iArgc > 2 )
		xml.parse ( const_cast < char * > ( setup.f_ppcArgv [ 2 ] ) );
	else
		xml.parse ( NULL );
	}

}


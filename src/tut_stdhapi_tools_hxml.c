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

#include "variables.h"

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

void * HXmlDump::parse ( void * )
	{
	char const * name, * prop;
	HString str, val;
	while ( ( name = iterate ( str, "/" ) ) )
		{
		cout << "[" << name << "]:" << endl;
		while ( ( prop = next_property ( val ) ) )
			cout << "(" << prop << ")->(" << static_cast < char * > ( val ) << ")" << endl;
		cout << "{" << static_cast < char * > ( str ) << "}" << endl;
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
	if ( g_iArgc != 2 )
		fail ( "You need to specify one argument for this test" );
	if ( file.open ( g_ppcArgv [ 1 ] ) )
		cout << file.get_error ( ) << ": " << file.get_path ( ) << endl;
	else
		{
		while ( file.read_line ( string, HFile::D_STRIP_NEWLINES ) >= 0 )
			cout << string << endl;
		file.close ( );
		}
	xml.init ( g_ppcArgv [ 1 ] );
	xml.parse ( 0 );
	}

}


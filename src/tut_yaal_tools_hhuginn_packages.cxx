/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_packages.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/hhuginn.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hstringstream.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_packages : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_packages, "yaal::tools::HHuginn,packages" );

TUT_UNIT_TEST( "Algorithms.range" )
	ENSURE_EQUALS(
		"Algorithms.range failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s=\"\";\n"
			"for(x : algo.range(3, 17, 4)) {\n"
			"s=s+\":\"+string(x);"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\":3:7:11:15\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Algorithms.sorted" )
	ENSURE_EQUALS(
		"Algorithms.sorted (list) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l=[2,7,3,9,0,-5];\n"
			"return(algo.sorted(l));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (deque) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s=\"\";\n"
			"d=deque(2,7,3,9,0,-5);\n"
			"for(x : algo.sorted(d)) {\n"
			"s=s+\":\"+string(x);"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\":-5:0:2:3:7:9\""
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (set) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"r=\"\";\n"
			"s=set(2,7,3,9,0,-5);\n"
			"for(x : algo.sorted(s)) {\n"
			"r=r+\":\"+string(x);"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\":-5:0:2:3:7:9\""
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (order) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"r=\"\";\n"
			"o=order(2,7,3,9,0,-5);\n"
			"for(x : algo.sorted(o)) {\n"
			"r=r+\":\"+string(x);"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\":-5:0:2:3:7:9\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Cryptography" )
	ENSURE_EQUALS(
		"Cryptography.md5 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.md5(\"\"));\n"
			"}"
		),
		"\"d41d8cd98f00b204e9800998ecf8427e\""
	);
	ENSURE_EQUALS(
		"Cryptography.sha1 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.sha1(\"\"));\n"
			"}"
		),
		"\"da39a3ee5e6b4b0d3255bfef95601890afd80709\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "RegularExpressions" )
	ENSURE_EQUALS(
		"RegularExpressions.match failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"[0-9]-[0-9]\" );\n"
			"r = \"\";\n"
			"m = rec.match(\"[123+123+3123]\");\n"
			"if (m.matched()) {\n"
			"r = r + \"fail match\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"m = rec.match(\"[123-456-789]\");"
			"if (m.matched()) {\n"
			"for ( w : m ) {\n"
			"r = r + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no match\";\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok3-46-7\""
	);
	ENSURE_EQUALS(
		"RegularExpressions.groups failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"^([a-z]*)@([a-z.]*)$\" );\n"
			"r = \"\";\n"
			"g = rec.groups(\"user@example2.com\");\n"
			"if ( g != none ) {\n"
			"r = r + \"fail groups\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"g = rec.groups(\"user@example.com\");\n"
			"if ( g != none ) {\n"
			"for ( w : g ) {\n"
			"r = r + \"|\" + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no groups\";\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok|user@example.com|user|example.com\""
	);
TUT_TEARDOWN()

}


/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_regularexpressions : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_regularexpressions( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_regularexpressions, "yaal::tools::HHuginn.RegularExpressions" );

TUT_UNIT_TEST( "match" )
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
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy" )
	ENSURE_EQUALS(
		"RegularExpressions copy failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"[0-9]-[0-9]\" );\n"
			"r = \"\";\n"
			"for( rg : [rec,copy(rec)] ) {\n"
			"m = rg.match(\"[123+123+3123]\");\n"
			"if (m.matched()) {\n"
			"r = r + \"fail match\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"m = rg.match(\"[123-456-789]\");"
			"if (m.matched()) {\n"
			"for ( w : m ) {\n"
			"r = r + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no match\";\n"
			"}\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok3-46-7ok3-46-7\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "groups" )
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

TUT_UNIT_TEST( "replace" )
	ENSURE_EQUALS(
		"RegularExpressions.replace failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"cre=re.compile(\"([0-9]+)\");\n"
			"return(cre.replace(\"abc012def789ghj\",\"$$$1}\"));\n"
			"}"
		),
		"\"abc$012}def$789}ghj\""
	);
	ENSURE_EQUALS(
		"RegularExpressions.replace failed",
		execute_except(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"cre=re.compile(\"([0-9]+)\");\n"
			"cre.replace(\"abc012def789ghj\",\"{$2}\");\n"
			"}"
		),
		"*anonymous stream*:4:12: Uncaught RegularExpressionsException: Invalid back-reference number in replacement string: 2."
	);
TUT_TEARDOWN()

}


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

struct tut_yaal_tools_hhuginn_base64 : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_base64( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_base64, "yaal::tools::HHuginn.Base64" );

#if SIZEOF_DOUBLE_LONG > SIZEOF_DOUBLE
#	ifdef __aarch64__
char const base64data[] = "\"5wMAAAAAAADlPVd4jRvSe9FCRLUfkgBASHVnaW5uLWJhc2U2NAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==\"";
#	else /* #	ifdef __aarch64__ */
char const base64data[] = "\"5wMAAAAAAAAAAAAAAADSe9FCRLUfkgBASHVnaW5uLWJhc2U2NAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==\"";
#	endif /* #	else #	ifdef __aarch64__ */
#else
char const base64data[] = "\"5wMAAAAAAAAYLURU-yEJQEh1Z2lubi1iYXNlNjQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==\"";
#endif

TUT_UNIT_TEST( "encode" )
	ENSURE_EQUALS(
		"Base64.encode failed",
		execute(
			"import Base64 as base64;\n"
			"main(){\n"
			"b = blob(64);\n"
			"bi = b.io();\n"
			"bi.write_integer(999,8);\n"
			"bi.write_real(3.141592653589793, "_ys.append( SIZEOF_DOUBLE_LONG ).append(
				");\n"
				"bi.write_line(\"Huginn-base64\");\n"
				"return(base64.encode(b));\n"
				"}"
			)
		),
		base64data
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "decode" )
	ENSURE_EQUALS(
		"Base64.decode failed",
		execute(
			"import Base64 as base64;\n"
			"main(){\n"
			"b = base64.decode("_ys.append( base64data ).append(
				");\n"
				"bi = b.io();\n"
				"l = [];\n"
				"l.push(bi.read_integer(8));\n"
				"l.push(bi.read_real("
			).append( SIZEOF_DOUBLE_LONG ).append(
				"));\n"
				"l.push(bi.read_line());\n"
				"return(l);\n"
				"}"
			)
		),
		"[999, 3.14159265359, \"Huginn-base64\"]"
	);
	ENSURE_EQUALS(
		"Base64.decode failed",
		execute(
			"import Base64 as base64;\n"
			"main(){\n"
			"b = base64.decode(\"\");\n"
			"return(size(b));\n"
			"}"
		),
		"0"
	);
TUT_TEARDOWN()

}


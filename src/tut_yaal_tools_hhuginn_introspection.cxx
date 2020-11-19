/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hcore.hxx>
#include <yaal/tools/stringalgo.hxx>
#include <yaal/hcore/hformat.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_introspection : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_introspection( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_introspection, "yaal::tools::HHuginn.Introspection" );

TUT_UNIT_TEST( "version" )
	typedef yaal::hcore::HArray<yaal::hcore::HString> tokens_t;
	tokens_t yaalVersion( string::split<tokens_t>( yaal_version( true ), character_class<CHARACTER_CLASS::WHITESPACE>().data(), HTokenizer::DELIMITED_BY_ANY_OF ) );
	ENSURE_EQUALS(
		"Introspection.version failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"return ( intro.version() );"
			"}\n"
		),
		format( "(\"%s\", \"%s\")", yaalVersion[0], yaalVersion[1] )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "symbol" )
	ENSURE_EQUALS(
		"Introspection.symbol (built-in function) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"s = intro.symbol(\"size\");\n"
			"return ( s(\"Huginn\") );"
			"}\n"
		),
		"6"
	);
	ENSURE_EQUALS(
		"Introspection.symbol (user function) failed",
		execute(
			"import Introspection as intro;\n"
			"triple(x){x*3;}\n"
			"main() {\n"
			"triple;\n"
			"t = intro.symbol(\"triple\");\n"
			"return ( t(7) );"
			"}\n"
		),
		"21"
	);
	ENSURE_EQUALS(
		"Introspection.symbol (package) failed",
		execute(
			"import Algorithms as algo;"
			"import Introspection as intro;\n"
			"main() {\n"
			"algo;\n"
			"a = intro.symbol(\"algo\");\n"
			"return ( a.max([1,3]) );"
			"}\n"
		),
		"3"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "attribute" )
	ENSURE_EQUALS(
		"Introspection.attribute (built-in, unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"tu = intro.attribute(string, \"to_upper\");\n"
			"return ( tu( \"Huginn\" ) );"
			"}\n"
		),
		"\"HUGINN\""
	);
	ENSURE_EQUALS(
		"Introspection.attribute (built-in, bound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"h = \"Huginn\";\n"
			"H = intro.attribute(h, \"to_upper\");\n"
			"return ( H() );"
			"}\n"
		),
		"\"HUGINN\""
	);
	ENSURE_EQUALS(
		"Introspection.attribute (user, unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; }"
			"main() {\n"
			"A().x;\n"
			"f = intro.attribute(A, \"x\");\n"
			"return ( f );"
			"}\n"
		),
		"17"
	);
	ENSURE_EQUALS(
		"Introspection.attribute (user, bound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; }"
			"main() {\n"
			"A().x;\n"
			"a = A();\n"
			"f = intro.attribute(a, \"x\");\n"
			"return ( f );"
			"}\n"
		),
		"17"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "list_attributes" )
	ENSURE_EQUALS(
		"Introspection.list_attributes (built-in unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"return ( intro.list_attributes(number) );"
			"}\n"
		),
		"(\"is_exact\", \"is_integral\", \"get_precision\", \"set_precision\")"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (built-in bound) failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"return ( intro.list_attributes($0) );"
			"}\n"
		),
		"(\"is_exact\", \"is_integral\", \"get_precision\", \"set_precision\")"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (user unbound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; y = none; }\n"
			"main() {\n"
			"a=A();a.x;a.y;\n"
			"return ( intro.list_attributes(A) );"
			"}\n"
		),
		"(\"x\", \"y\")"
	);
	ENSURE_EQUALS(
		"Introspection.list_attributes (user bound) failed",
		execute(
			"import Introspection as intro;\n"
			"class A { x = 17; y = none; }\n"
			"main() {\n"
			"a=A();a.x;a.y;\n"
			"return ( intro.list_attributes(a) );"
			"}\n"
		),
		"(\"x\", \"y\")"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "import" )
	ENSURE_EQUALS(
		"Introspection.import failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"t = intro.import(\"Tress\");\n"
			"return ( t.diagonal(3., 4.) );"
			"}\n",
			{ "./data/" }
		),
		"5.0"
	);
	ENSURE_EQUALS(
		"Introspection.import restricted succeeded",
		execute_except(
			"import Introspection as intro;\n"
			"main() {\n"
			"intro.import(\"return\");\n"
			"}\n"
		),
		"*anonymous stream*:3:13: `return` is restricted keyword."
	);
	ENSURE_EQUALS(
		"Introspection.import previously imported packgage failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"i = intro.import(\"Introspection\");\n"
			"return ( [type(i) == type(intro),i.KIND.ENUM == intro.KIND.ENUM] );"
			"}\n"
		),
		"[true, true]"
	);
	ENSURE_EQUALS(
		"Introspection.import existing package failed",
		execute_except(
			"import Introspection as intro;\n"
			"main() {\n"
			"intro.import(\"intro\");\n"
			"}\n"
		),
		"*anonymous stream*:3:13: Package alias of the same name already exists."
	);
	ENSURE_EQUALS(
		"Introspection.import existing enum succeeded",
		execute_except(
			"import Introspection as intro;\n"
			"enum E {\n"
			"E\n"
			"}\n"
			"main() {\n"
			"intro.import(\"E\");\n"
			"}\n"
		),
		"*anonymous stream*:6:13: Enumeration of the same name already exists."
	);
	ENSURE_EQUALS(
		"Introspection.import existing class succeeded",
		execute_except(
			"import Introspection as intro;\n"
			"class C {\n"
			"f=0;\n"
			"}\n"
			"main() {\n"
			"intro.import(\"C\");\n"
			"C().f;\n"
			"}\n"
		),
		"*anonymous stream*:6:13: Class of the same name already exists."
	);
	ENSURE_EQUALS(
		"Introspection.import existing function succeeded",
		execute_except(
			"import Introspection as intro;\n"
			"main() {\n"
			"intro.import(\"main\");\n"
			"}\n"
		),
		"*anonymous stream*:3:13: Function of the same name already exists."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "call_stack" )
	ENSURE_EQUALS(
		"Introspection.call_stack failed",
		execute(
			"import Introspection as intro;\n"
			"foo( n ) {\n"
			"r = none;\n"
			"if ( n > 0 ) {\n"
			"r = foo( n - 1 );\n"
			"} else {\n"
			"r = intro.call_stack();\n"
			"}\n"
			"return ( r );\n"
			"}\n"
			"main() {\n"
			"return ( foo( 3 ) );"
			"}\n"
		),
		"[*anonymous stream*:7:21:foo, *anonymous stream*:5:8:foo, *anonymous stream*:5:8:foo, *anonymous stream*:5:8:foo, *anonymous stream*:12:13:main]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "kind" )
	ENSURE_EQUALS(
		"Introspection.kind failed",
		execute(
			"import Introspection as intro;\n"
			"import Mathematics as math;\n"
			"import FileSystem as fs;\n"
			"import Tress as tress;\n"
			"class A {\n"
			"x = 0;\n"
			"}\n"
			"enum E {\n"
			"E\n"
			"}\n"
			"main() {\n"
			"x = 7;x;\n"
			"return ( (\n"
			"intro.kind( x ),\n"
			"intro.kind( main ), \n"
			"intro.kind( A ), \n"
			"intro.kind( E ), \n"
			"intro.kind( math.pi ), \n"
			"intro.kind( math.Matrix ), \n"
			"intro.kind( fs.OPEN_MODE ), \n"
			"intro.kind( tress ), \n"
			"intro.kind( tress.bug ), \n"
			"intro.kind( tress.Object ), \n"
			"intro.kind( tress.ENUM ), \n"
			"intro.kind( tress.algo ), \n"
			") );"
			"}\n",
			{ "./data/" }
		),
		"(intro.KIND.LOCAL, intro.KIND.FUNCTION, intro.KIND.CLASS, intro.KIND.ENUM, intro.KIND.FUNCTION, intro.KIND.CLASS, intro.KIND.ENUM, intro.KIND.PACKAGE, intro.KIND.FUNCTION, intro.KIND.CLASS, intro.KIND.ENUM, intro.KIND.PACKAGE)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "subject" )
	ENSURE_EQUALS(
		"Introspection.subject failed",
		execute(
			"import Introspection as intro;\n"
			"main() {\n"
			"s = \"Huginn\";\n"
			"bc = s.to_upper;\n"
			"return ( intro.subject( bc ) );"
			"}\n"
		),
		"\"Huginn\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "list_imports" )
	ENSURE_EQUALS(
		"Introspection.list_imports failed",
		execute(
			"import Introspection as intro;\n"
			"import Algorithms as algo;\n"
			"enum COLOR { RED, GREEN, BLUE }\n"
			"foo() { return ( ( foo, COLOR.RED ) ); }\n"
			"main() {\n"
			"return ( algo.sorted( intro.list_imports() ) );"
			"}\n"
		),
		"[(\"algo\", \"Algorithms\"), (\"intro\", \"Introspection\")]"
	);
TUT_TEARDOWN()

}


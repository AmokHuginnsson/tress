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

struct tut_yaal_tools_hhuginn_yaml : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_yaml( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_yaml, "yaal::tools::HHuginn.YAML" );

TUT_UNIT_TEST( "save" )
	char const expected[] =
		"["
		"\"int: 7\\n\", "
		"\"real: 3.1415\\n\", "
		"\"number: 2.71828182845904523536028747\\n\", "
		"\"string: Huginn-YAML\\n\", "
		"\"bday: 1978-05-24\\n\", "
		"\"true: true\\n\", "
		"\"false: false\\n\", "
		"\"null: null\\n\", "
		"\"character: h\\n\", "
		"\"array:\\n\", "
		"\"- 1\\n\", "
		"\"- 2\\n\", "
		"\"- 3\\n\", "
		"\"- 4\\n\", "
		"\"lookup:\\n\", "
		"\"  one: 1\\n\", "
		"\"  two: 2\\n\", "
		"\"  three: 3\\n\", "
		"\"  four: 4\\n\", "
		"\"tuple:\\n\", "
		"\"- 1\\n\", "
		"\"- 2\\n\", "
		"\"- 3\\n\", "
		"\"- 4\\n\", "
		"\"deque:\\n\", "
		"\"- 1\\n\", "
		"\"- 2\\n\", "
		"\"- 3\\n\", "
		"\"- 4\\n\", "
		"\"order:\\n\", "
		"\"- 1\\n\", "
		"\"- 2\\n\", "
		"\"- 3\\n\", "
		"\"- 4\\n\", "
		"\"set:\\n\", "
		"\"- 1\\n\", "
		"\"- 2\\n\", "
		"\"- 3\\n\", "
		"\"- 4\\n\", "
		"\"dict:\\n\", "
		"\"  four: 4\\n\", "
		"\"  one: 1\\n\", "
		"\"  three: 3\\n\", "
		"\"  two: 2\\n\""
		"]"
	;
	ENSURE_EQUALS(
		"YAML.save failed",
		execute(
			"import YAML as yaml;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"\"int\": 7,\n"
			"\"real\": 3.1415,\n"
			"\"number\": $2.71828182845904523536028747,\n"
			"\"string\": \"Huginn-YAML\",\n"
			"\"bday\": Time( 1978, 5, 24, 0, 0, 0 ),\n"
			"\"true\": true,\n"
			"\"false\": false,\n"
			"\"null\": none,\n"
			"\"character\": 'h',\n"
			"\"array\": [1,2,3,4],\n"
			"\"lookup\": {\"one\":1,\"two\":2,\"three\":3,\"four\":4},\n"
			"\"tuple\": (1,2,3,4),\n"
			"\"deque\": deque(1,2,3,4),\n"
			"\"order\": order(1,2,3,4),\n"
			"\"set\": set(1,2,3,4),\n"
			"\"dict\": [\"one\":1,\"two\":2,\"three\":3,\"four\":4]\n"
			"};\n"
			"s = text.stream();\n"
			"yaml.save(d,s);"
			"return(s.read_lines());\n"
			"}"
		),
		expected
	);
	ENSURE_EQUALS(
		"YAML.save of non-YAML-serializable succeeded",
		execute_except(
			"import YAML as yaml;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"\"data\": type\n"
			"};\n"
			"s = text.stream();\n"
			"yaml.save(d,s);"
			"return(s.read_line());\n"
			"}"
		),
		"*anonymous stream*:8:10: Value of type a `*function_reference*` is not YAML serializable."
	);
	ENSURE_EQUALS(
		"YAML.save non-string key in object succeeded",
		execute_except(
			"import YAML as yaml;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"0: 0\n"
			"};\n"
			"s = text.stream();\n"
			"yaml.save(d,s);"
			"return(s.read_line());\n"
			"}"
		),
		"*anonymous stream*:8:10: Keys in YAML objects must be `string`s, not an `integer`."
	);
	ENSURE_EQUALS(
		"YAML.save non-string key in object succeeded",
		execute_except(
			"import YAML as yaml;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"\"data\": [0.0:0]\n"
			"};\n"
			"s = text.stream();\n"
			"yaml.save(d,s);"
			"return(s.read_line());\n"
			"}"
		),
		"*anonymous stream*:8:10: Keys in YAML objects must be `string`s, not a `real`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "load" )
	ENSURE_EQUALS(
		"YAML.load failed",
		execute(
			"import YAML as yaml;\n"
			"import Text as text;\n"
			"main(){\n"
			"e = {\n"
			"\"int\": 7,\n"
			"\"real\": 3.1415,\n"
			"\"number\": $2.71828182845904523536028747,\n"
			"\"string\": \"Huginn-YAML\",\n"
			"\"bday\": Time( 1978, 5, 24, 0, 0, 0 ),\n"
			"\"true\": true,\n"
			"\"false\": false,\n"
			"\"null\": none,\n"
			"\"array\": [1,2,3,4],\n"
			"\"object\": {\"one\":1,\"two\":2,\"three\":3,\"four\":4}\n"
			"};\n"
			"s = \"string: \\\"Huginn-YAML\\\"\\n"
			"bday: 1978-05-24\\n"
			"false: false\\n"
			"array:\\n"
			"- 1\\n"
			"- 2\\n"
			"- 3\\n"
			"- 4\\n"
			"null: null\\n"
			"true: true\\n"
			"object:\\n"
			"  three: 3\\n"
			"  one: 1\\n"
			"  two: 2\\n"
			"  four: 4\\n"
			"real: 3.1415\\n"
			"int: 7\\n"
			"number: 2.71828182845904523536028747\\n"
			"\";"
			"d = yaml.load(text.stream(s));\n"
			"return(d==e);\n"
			"}"
		),
		"true"
	);
	ENSURE_EQUALS(
		"YAML.load of invalid YAML succeeded",
		execute_except(
			"import YAML as yaml;\n"
			"import Text as text;\n"
			"main(){\n"
			"s = \"what:\\nthat\\n\";\n"
			"d = yaml.load(text.stream(s));\n"
			"return(d);\n"
			"}"
		),
		"*anonymous stream*:5:14: Uncaught YAMLException: Malformed YAML document read from stream."
	);
TUT_TEARDOWN()

}


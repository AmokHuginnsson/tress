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

struct tut_yaal_tools_hhuginn_json : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_json( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_json, "yaal::tools::HHuginn.JSON" );

TUT_UNIT_TEST( "save" )
#if TARGET_CPU_BITS == 32
	char const expected[] =
		"\"{\\\"order\\\": [1, 2, 3, 4], \\\"set\\\": [1, 2, 3, 4], "
		"\\\"lookup\\\": {\\\"one\\\": 1, \\\"two\\\": 2, \\\"three\\\": 3, \\\"four\\\": 4}, \\\"string\\\": \\\"Huginn-JSON\\\", "
		"\\\"array\\\": [1, 2, 3, 4], \\\"tuple\\\": [1, 2, 3, 4], \\\"deque\\\": [1, 2, 3, 4], \\\"null\\\": null, \\\"true\\\": true, "
		"\\\"dict\\\": {\\\"one\\\": 1, \\\"two\\\": 2, \\\"three\\\": 3, \\\"four\\\": 4}, \\\"false\\\": false, "
		"\\\"number\\\": 2.71828182845904523536028747, \\\"real\\\": 3.1415, \\\"int\\\": 7, \\\"character\\\": \\\"h\\\"}\""
	;
#elif defined ( __HOST_OS_TYPE_FREEBSD__ )
	char const expected[] =
		"\"{\\\"string\\\": \\\"Huginn-JSON\\\", \\\"false\\\": false, \\\"set\\\": [1, 2, 3, 4], "
		"\\\"order\\\": [1, 2, 3, 4], \\\"character\\\": \\\"h\\\", \\\"array\\\": [1, 2, 3, 4], "
		"\\\"dict\\\": {\\\"three\\\": 3, \\\"one\\\": 1, \\\"two\\\": 2, \\\"four\\\": 4}, \\\"true\\\": true, \\\"null\\\": null, "
		"\\\"tuple\\\": [1, 2, 3, 4], \\\"deque\\\": [1, 2, 3, 4], "
		"\\\"lookup\\\": {\\\"three\\\": 3, \\\"one\\\": 1, \\\"two\\\": 2, \\\"four\\\": 4}, "
		"\\\"real\\\": 3.1415, \\\"int\\\": 7, \\\"number\\\": 2.71828182845904523536028747}\""
	;
#else
	char const expected[] =
		"\"{\\\"string\\\": \\\"Huginn-JSON\\\", \\\"false\\\": false, \\\"set\\\": [1, 2, 3, 4], \\\"character\\\": \\\"h\\\", "
		"\\\"order\\\": [1, 2, 3, 4], \\\"array\\\": [1, 2, 3, 4], \\\"null\\\": null, \\\"true\\\": true, "
		"\\\"dict\\\": {\\\"three\\\": 3, \\\"one\\\": 1, \\\"two\\\": 2, \\\"four\\\": 4}, \\\"tuple\\\": [1, 2, 3, 4], "
		"\\\"deque\\\": [1, 2, 3, 4], \\\"lookup\\\": {\\\"three\\\": 3, \\\"one\\\": 1, \\\"two\\\": 2, \\\"four\\\": 4}, "
		"\\\"real\\\": 3.1415, \\\"int\\\": 7, \\\"number\\\": 2.71828182845904523536028747}\""
	;
#endif
	ENSURE_EQUALS(
		"JSON.save failed",
		execute(
			"import JSON as json;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"\"int\": 7,\n"
			"\"real\": 3.1415,\n"
			"\"number\": $2.71828182845904523536028747,\n"
			"\"string\": \"Huginn-JSON\",\n"
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
			"json.save(d,s,false);"
			"return(s.read_line());\n"
			"}"
		),
		expected
	);
	ENSURE_EQUALS(
		"JSON.save of non-JSON-serializable succeeded",
		execute_except(
			"import JSON as json;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"\"data\": type\n"
			"};\n"
			"s = text.stream();\n"
			"json.save(d,s,false);"
			"return(s.read_line());\n"
			"}"
		),
		"*anonymous stream*:8:10: Value of type a `*function_reference*` is not JSON serializable."
	);
	ENSURE_EQUALS(
		"JSON.save non-string key in object succeeded",
		execute_except(
			"import JSON as json;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"0: 0\n"
			"};\n"
			"s = text.stream();\n"
			"json.save(d,s,false);"
			"return(s.read_line());\n"
			"}"
		),
		"*anonymous stream*:8:10: Keys in JSON objects must be `string`s, not an `integer`."
	);
	ENSURE_EQUALS(
		"JSON.save non-string key in object succeeded",
		execute_except(
			"import JSON as json;\n"
			"import Text as text;\n"
			"main(){\n"
			"d = {\n"
			"\"data\": [0.0:0]\n"
			"};\n"
			"s = text.stream();\n"
			"json.save(d,s,false);"
			"return(s.read_line());\n"
			"}"
		),
		"*anonymous stream*:8:10: Keys in JSON objects must be `string`s, not a `real`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "load" )
	ENSURE_EQUALS(
		"JSON.load failed",
		execute(
			"import JSON as json;\n"
			"import Text as text;\n"
			"main(){\n"
			"e = {\n"
			"\"int\": 7,\n"
			"\"real\": 3.1415,\n"
			"\"number\": $2.71828182845904523536028747,\n"
			"\"string\": \"Huginn-JSON\",\n"
			"\"true\": true,\n"
			"\"false\": false,\n"
			"\"null\": none,\n"
			"\"array\": [1,2,3,4],\n"
			"\"object\": {\"one\":1,\"two\":2,\"three\":3,\"four\":4}\n"
			"};\n"
			"s = \"{\\\"string\\\": \\\"Huginn-JSON\\\", \\\"false\\\": false, "
			"\\\"array\\\": [1, 2, 3, 4], \\\"null\\\": null, \\\"true\\\": true, "
			"\\\"object\\\": {\\\"three\\\": 3, \\\"one\\\": 1, \\\"two\\\": 2, \\\"four\\\": 4}, "
			"\\\"real\\\": 3.1415, \\\"int\\\": 7, \\\"number\\\": 2.71828182845904523536028747}\";"
			"d = json.load(text.stream(s));\n"
			"return(d==e);\n"
			"}"
		),
		"true"
	);
	ENSURE_EQUALS(
		"JSON.load of invalid JSON succeeded",
		execute_except(
			"import JSON as json;\n"
			"import Text as text;\n"
			"main(){\n"
			"s = \"what?\";\n"
			"d = json.load(text.stream(s));\n"
			"return(d);\n"
			"}"
		),
		"*anonymous stream*:5:14: Uncaught JSONException: Invalid JSON data at position 0 in input stream, expected one of characters: {"
	);
TUT_TEARDOWN()

}


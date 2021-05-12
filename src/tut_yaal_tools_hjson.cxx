/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hjson.hxx>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace yaal {
namespace tools {
inline std::ostream& operator << ( std::ostream& out, HJSON const& json_ ) {
	HStringStream ss;
	json_.save( ss );
	HUTF8String utf8( ss.string() );
	out.write( utf8.c_str(), utf8.byte_count() );
	return out;
}
}
}

namespace tut {

struct tut_yaal_tools_hjson : public simple_mock<tut_yaal_tools_hjson> {
	virtual ~tut_yaal_tools_hjson( void ) {}
};

namespace {

HJSON make_json( void ) {
	HJSON json;
	HJSON::HValue& r( json.element() );
	r["name"] = "nameValue";
	r["date"] = "1978-05-24";
	HJSON::HValue::array_t& records( r["records"].get_elements() );
	records.push_back(
		HJSON::HValue::members_t({
			{ "id", "int" },
			{ "data", 9 }
		})
	);
	records.push_back(
		HJSON::HValue::members_t({
			{ "id", "float" },
			{ "data", 12.345L }
		})
	);
	records.push_back(
		HJSON::HValue::members_t({
			{ "id", "str" },
			{ "data", "yaal-JSON" }
		})
	);
	r["number_like"] = HJSON::HValue::members_t({
		{ "int", 13 },
		{ "real", 3.14159265359L },
		{ "number", "2.718281828459045235360287471"_yn }
	});
	HJSON::HValue::members_t& empty( r["empty"].get_members() );
	empty.insert( make_pair( "arr", HJSON::HValue::array_t() ) );
	empty.insert( make_pair( "obj", HJSON::HValue::members_t() ) );
	r["banner"] = "yaal's JSON generator";
	r["literals"] = HJSON::HValue::array_t({ HJSON::HValue::LITERAL::TRUE, HJSON::HValue::LITERAL::FALSE,	HJSON::HValue::LITERAL::NULL });
	return json;
}

#if TARGET_CPU_BITS == 64
char const complexJSONnl[] =
	"{\n"
	"\t\"empty\": {\n"
	"\t\t\"arr\": [],\n"
	"\t\t\"obj\": {\n"
	"\t\t}\n"
	"\t},\n"
	"\t\"number_like\": {\n"
	"\t\t\"number\": 2.718281828459045235360287471,\n"
	"\t\t\"int\": 13,\n"
	"\t\t\"real\": 3.14159265359\n"
	"\t},\n"
	"\t\"name\": \"nameValue\",\n"
	"\t\"literals\": [true, false, null],\n"
	"\t\"date\": \"1978-05-24\",\n"
	"\t\"banner\": \"yaal's JSON generator\",\n"
	"\t\"records\": [{\n"
	"\t\t\"id\": \"int\",\n"
	"\t\t\"data\": 9\n"
	"\t}, {\n"
	"\t\t\"id\": \"float\",\n"
	"\t\t\"data\": 12.345\n"
	"\t}, {\n"
	"\t\t\"id\": \"str\",\n"
	"\t\t\"data\": \"yaal-JSON\"\n"
	"\t}]\n"
	"}\n"
;

char const complexJSON[] =
	"{"
	"\"empty\": {"
	"\"arr\": [], "
	"\"obj\": {}"
	"}, "
	"\"number_like\": {"
	"\"number\": 2.718281828459045235360287471, "
	"\"int\": 13, "
	"\"real\": 3.14159265359"
	"}, "
	"\"name\": \"nameValue\", "
	"\"literals\": [true, false, null], "
	"\"date\": \"1978-05-24\", "
	"\"banner\": \"yaal's JSON generator\", "
	"\"records\": [{"
	"\"id\": \"int\", "
	"\"data\": 9"
	"}, {"
	"\"id\": \"float\", "
	"\"data\": 12.345"
	"}, {"
	"\"id\": \"str\", "
	"\"data\": \"yaal-JSON\""
	"}]"
	"}"
;

char const relaxedJSON[] =
	"{"
	"\"records\": [{"
	"\"id\": 'int', "
	"\"data\": 9"
	"}, {"
	"\"id\": \"float\", "
	"data: 12.345"
	"}, {"
	"\"id\": \"str\", "
	"\"data\": \"yaal-JSON\","
	"}], "
	"banner: \"yaal's JSON generator\", "
	"\"number_like\": {"
	"\"int\": 13, "
	"'number': 2.718281828459045235360287471, "
	"\"real\": 3.14159265359"
	"}, "
	"'name': \"nameValue\", "
	"\"date\": \"1978-05-24\", "
	"\"literals\": [true, false, null,], "
	"\"empty\": {"
	"\"arr\": [], "
	"\"obj\": {}"
	"}"
	"}"
;
#elif defined( __HOST_OS_TYPE_RASPBIAN__ )
char const complexJSONnl[] =
	"{\n"
	"\t\"records\": [{\n"
	"\t\t\"id\": \"int\",\n"
	"\t\t\"data\": 9\n"
	"\t}, {\n"
	"\t\t\"id\": \"float\",\n"
	"\t\t\"data\": 12.345\n"
	"\t}, {\n"
	"\t\t\"id\": \"str\",\n"
	"\t\t\"data\": \"yaal-JSON\"\n"
	"\t}],\n"
	"\t\"banner\": \"yaal's JSON generator\",\n"
	"\t\"number_like\": {\n"
	"\t\t\"int\": 13,\n"
	"\t\t\"number\": 2.718281828459045235360287471,\n"
	"\t\t\"real\": 3.14159265359\n"
	"\t},\n"
	"\t\"name\": \"nameValue\",\n"
	"\t\"date\": \"1978-05-24\",\n"
	"\t\"literals\": [true, false, null],\n"
	"\t\"empty\": {\n"
	"\t\t\"arr\": [],\n"
	"\t\t\"obj\": {\n"
	"\t\t}\n"
	"\t}\n"
	"}\n"
;

char const complexJSON[] =
	"{"
	"\"records\": [{"
	"\"id\": \"int\", "
	"\"data\": 9"
	"}, {"
	"\"id\": \"float\", "
	"\"data\": 12.345"
	"}, {"
	"\"id\": \"str\", "
	"\"data\": \"yaal-JSON\""
	"}], "
	"\"banner\": \"yaal's JSON generator\", "
	"\"number_like\": {"
	"\"int\": 13, "
	"\"number\": 2.718281828459045235360287471, "
	"\"real\": 3.14159265359"
	"}, "
	"\"name\": \"nameValue\", "
	"\"date\": \"1978-05-24\", "
	"\"literals\": [true, false, null], "
	"\"empty\": {"
	"\"arr\": [], "
	"\"obj\": {}"
	"}"
	"}"
;

char const relaxedJSON[] =
	"{"
	"\"records\": [{"
	"\"id\": 'int', "
	"\"data\": 9"
	"}, {"
	"\"id\": \"float\", "
	"data: 12.345"
	"}, {"
	"\"id\": \"str\", "
	"\"data\": \"yaal-JSON\","
	"}], "
	"banner: \"yaal's JSON generator\", "
	"\"number_like\": {"
	"\"int\": 13, "
	"'number': 2.718281828459045235360287471, "
	"\"real\": 3.14159265359"
	"}, "
	"'name': \"nameValue\", "
	"\"date\": \"1978-05-24\", "
	"\"literals\": [true, false, null,], "
	"\"empty\": {"
	"\"arr\": [], "
	"\"obj\": {}"
	"}"
	"}"
;
#else
char const complexJSONnl[] =
	"{\n"
	"\t\"records\": [{\n"
	"\t\t\"id\": \"int\",\n"
	"\t\t\"data\": 9\n"
	"\t}, {\n"
	"\t\t\"id\": \"float\",\n"
	"\t\t\"data\": 12.345\n"
	"\t}, {\n"
	"\t\t\"id\": \"str\",\n"
	"\t\t\"data\": \"yaal-JSON\"\n"
	"\t}],\n"
	"\t\"number_like\": {\n"
	"\t\t\"int\": 13,\n"
	"\t\t\"real\": 3.14159265359,\n"
	"\t\t\"number\": 2.718281828459045235360287471\n"
	"\t},\n"
	"\t\"banner\": \"yaal's JSON generator\",\n"
	"\t\"name\": \"nameValue\",\n"
	"\t\"date\": \"1978-05-24\",\n"
	"\t\"literals\": [true, false, null],\n"
	"\t\"empty\": {\n"
	"\t\t\"arr\": [],\n"
	"\t\t\"obj\": {\n"
	"\t\t}\n"
	"\t}\n"
	"}\n"
;

char const complexJSON[] =
	"{"
	"\"records\": [{"
	"\"id\": \"int\", "
	"\"data\": 9"
	"}, {"
	"\"id\": \"float\", "
	"\"data\": 12.345"
	"}, {"
	"\"id\": \"str\", "
	"\"data\": \"yaal-JSON\""
	"}], "
	"\"number_like\": {"
	"\"int\": 13, "
	"\"real\": 3.14159265359, "
	"\"number\": 2.718281828459045235360287471"
	"}, "
	"\"banner\": \"yaal's JSON generator\", "
	"\"name\": \"nameValue\", "
	"\"date\": \"1978-05-24\", "
	"\"literals\": [true, false, null], "
	"\"empty\": {"
	"\"arr\": [], "
	"\"obj\": {}"
	"}"
	"}"
;

char const relaxedJSON[] =
	"{"
	"\"empty\": {"
	"\"arr\": [], "
	"\"obj\": {}"
	"}, "
	"\"records\": [{"
	"\"id\": 'int', "
	"\"data\": 9"
	"}, {"
	"\"id\": \"float\", "
	"data: 12.345"
	"}, {"
	"\"id\": \"str\", "
	"\"data\": \"yaal-JSON\","
	"}], "
	"banner: \"yaal's JSON generator\", "
	"\"number_like\": {"
	"\"int\": 13, "
	"'number': 2.718281828459045235360287471, "
	"\"real\": 3.14159265359"
	"}, "
	"'name': \"nameValue\", "
	"\"date\": \"1978-05-24\", "
	"\"literals\": [true, false, null,]"
	"}"
;
#endif

}

TUT_TEST_GROUP( tut_yaal_tools_hjson, "yaal::tools::HJSON" );

TUT_UNIT_TEST( "generate int" )
	HJSON json;
	json.element() = 13;
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just an int generation failed", ss.string(), "13\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just an int generation failed", ss.string(), "13" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate real" )
	HJSON json;
	json.element() = 3.141592653589793L;
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just a real generation failed", ss.string(), "3.14159265359\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just a real generation failed", ss.string(), "3.14159265359" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate number" )
	HJSON json;
	json.element() = "2.718281828459045"_yn;
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just a number generation failed", ss.string(), "2.718281828459045\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just a number generation failed", ss.string(), "2.718281828459045" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate string" )
	HJSON json;
	json.element() = "yaal's JSON generator";
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just a string generation failed", ss.string(), "\"yaal's JSON generator\"\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just a string generation failed", ss.string(), "\"yaal's JSON generator\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate literal" )
	HJSON json;
	json.element() = HJSON::HValue::LITERAL::TRUE;
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just a literal generation failed", ss.string(), "true\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just a literal generation failed", ss.string(), "true" );
	json.element() = HJSON::HValue::LITERAL::FALSE;
	ss.reset();
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just a literal generation failed", ss.string(), "false\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just a literal generation failed", ss.string(), "false" );
	json.element() = HJSON::HValue::LITERAL::NULL;
	ss.reset();
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just a literal generation failed", ss.string(), "null\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just a literal generation failed", ss.string(), "null" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate array" )
	HJSON json;
	json.element().push_back( 13 );
	json.element().push_back( 3.141592653589793L );
	json.element().push_back( "2.718281828459045"_yn );
	json.element().push_back( "yaal's JSON generator" );
	json.element().push_back( HJSON::HValue::LITERAL::TRUE );
	json.element().push_back( HJSON::HValue::LITERAL::FALSE );
	json.element().push_back( HJSON::HValue::LITERAL::NULL );
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "[JSON] just an array generation failed", ss.string(), "[13, 3.14159265359, 2.718281828459045, \"yaal's JSON generator\", true, false, null]\n" );
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS( "[JSON] just an array generation failed", ss.string(), "[13, 3.14159265359, 2.718281828459045, \"yaal's JSON generator\", true, false, null]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate object" )
	HJSON json;
	HJSON::HValue::members_t& m( json.element().get_members() );
	m["bad_luck"] = 13;
	m["pi"] = 3.141592653589793L;
	m["e"] = "2.718281828459045"_yn;
	m["banner"] = "yaal's JSON generator";
	m["true"] = HJSON::HValue::LITERAL::TRUE;
	m["false"] = HJSON::HValue::LITERAL::FALSE;
	m["null"] = HJSON::HValue::LITERAL::NULL;
	HStringStream ss;
	json.save( ss );
#if TARGET_CPU_BITS == 64
	char const expectedNL[] =
		"{\n"
		"\t\"false\": false,\n"
		"\t\"pi\": 3.14159265359,\n"
		"\t\"bad_luck\": 13,\n"
		"\t\"banner\": \"yaal's JSON generator\",\n"
		"\t\"true\": true,\n"
		"\t\"e\": 2.718281828459045,\n"
		"\t\"null\": null\n"
		"}\n"
	;
#else
	char const expectedNL[] =
		"{\n"
		"\t\"banner\": \"yaal's JSON generator\",\n"
		"\t\"pi\": 3.14159265359,\n"
		"\t\"bad_luck\": 13,\n"
		"\t\"false\": false,\n"
		"\t\"true\": true,\n"
		"\t\"e\": 2.718281828459045,\n"
		"\t\"null\": null\n"
		"}\n"
	;
#endif
	ENSURE_EQUALS( "[JSON] just an object generation failed", ss.string(), expectedNL );
	ss.reset();
	json.save( ss, false );
#if TARGET_CPU_BITS == 64
	char const expected[] =
		"{"
		"\"false\": false, "
		"\"pi\": 3.14159265359, "
		"\"bad_luck\": 13, "
		"\"banner\": \"yaal's JSON generator\", "
		"\"true\": true, "
		"\"e\": 2.718281828459045, "
		"\"null\": null}"
	;
#else
	char const expected[] =
		"{"
		"\"banner\": \"yaal's JSON generator\", "
		"\"pi\": 3.14159265359, "
		"\"bad_luck\": 13, "
		"\"false\": false, "
		"\"true\": true, "
		"\"e\": 2.718281828459045, "
		"\"null\": null}"
	;
#endif
	ENSURE_EQUALS( "[JSON] just an object generation failed", ss.string(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate complex JSON" )
	HJSON json( make_json() );
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS(
		"[JSON] just an object generation failed",
		ss.string(),
		complexJSONnl
	);
	ss.reset();
	json.save( ss, false );
	ENSURE_EQUALS(
		"[JSON] just an object generation failed",
		ss.string(),
		complexJSON
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse int" )
	HJSON expected;
	expected.element() = 13;
	HJSON json;
	HStringStream ss( "13" );
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone int failed", json, expected );
	json.clear();
	ss << "13" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone int failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse real" )
	HJSON expected;
	expected.element() = 3.14159265359L;
	HJSON json;
	HStringStream ss( "3.14159265359" );
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone real failed", json, expected );
	json.clear();
	ss << "3.14159265359" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone real failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse number" )
	HJSON expected;
	expected.element() = "2.718281828459045235360287471"_yn;
	HJSON json;
	HStringStream ss( "2.718281828459045235360287471" );
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone number failed", json, expected );
	json.clear();
	ss << "2.718281828459045235360287471" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone number failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse string" )
	HJSON expected;
	expected.element() = "yaal's JSON generator";
	HJSON json;
	HStringStream ss( "\"yaal's JSON generator\"" );
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone string failed", json, expected );
	json.clear();
	ss << "\"yaal's JSON generator\"" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone string failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse literal" )
	HJSON expected;
	expected.element() = HJSON::HValue::LITERAL::TRUE;
	HStringStream ss( "true" );
	HJSON json;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone literal(true) failed", json, expected );
	json.clear();
	ss << "true" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone literal(true) failed", json, expected );

	expected.element() = HJSON::HValue::LITERAL::FALSE;
	json.clear();
	ss << "false";
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone literal(false) failed", json, expected );
	json.clear();
	ss << "false" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone literal(false) failed", json, expected );

	expected.element() = HJSON::HValue::LITERAL::NULL;
	json.clear();
	ss << "null";
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone literal(null) failed", json, expected );
	json.clear();
	ss << "null" << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone literal(null) failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse array" )
	HJSON expected;
	expected.element().push_back( 13 );
	expected.element().push_back( 3.14159265359L );
	expected.element().push_back( "2.718281828459045235360287471"_yn );
	expected.element().push_back( "yaal's JSON generator" );
	expected.element().push_back( HJSON::HValue::LITERAL::TRUE );
	expected.element().push_back( HJSON::HValue::LITERAL::FALSE );
	expected.element().push_back( HJSON::HValue::LITERAL::NULL );
	char const data[] = "[13, 3.14159265359, 2.718281828459045235360287471, \"yaal's JSON generator\", true, false, null]\n";
	HStringStream ss( data );
	HJSON json;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone array failed", json, expected );
	ss << data << endl;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone array failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse object" )
	HJSON expected;
	expected.element()["bad_luck"] = 13;
	expected.element()["pi"] = 3.14159265359L;
	expected.element()["e"] = "2.718281828459045235360287471"_yn;
	expected.element()["banner"] = "yaal's JSON generator";
	expected.element()["true"] = HJSON::HValue::LITERAL::TRUE;
	expected.element()["false"] = HJSON::HValue::LITERAL::FALSE;
	expected.element()["null"] = HJSON::HValue::LITERAL::NULL;
	HStringStream ss( "{\"false\": false, \"pi\": 3.14159265359, \"bad_luck\": 13, \"banner\": \"yaal's JSON generator\", \"true\": true, \"e\": 2.718281828459045235360287471, \"null\": null}" );
	HJSON json;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone object failed", json, expected );
	ss.str(
		"{\n"
		"\t\"false\": false,\n"
		"\t\"pi\": 3.14159265359,\n"
		"\t\"bad_luck\": 13,\n"
		"\t\"banner\": \"yaal's JSON generator\",\n"
		"\t\"true\": true,\n"
		"\t\"e\": 2.718281828459045235360287471,\n"
		"\t\"null\": null\n"
		"}\n"
	);
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing alone object failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse complex JSON" )
	HJSON expected( make_json() );
	HStringStream ss( complexJSON );
	HJSON json;
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing complex JSON failed", json, expected );
	ss.str( complexJSONnl );
	json.load( ss );
	ENSURE_EQUALS( "[JSON] parsing complex JSON nl failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse relaxed JSON" )
	HJSON expected( make_json() );
	HStringStream ss( relaxedJSON );
	HJSON json;
	ENSURE_THROW( "paring relaxed JSON with strict parser succeeded", json.load( ss ), HJSONException );
	ss.str( relaxedJSON );
	clog << "JSON: `" << ss.string() << "`" << endl;
	json.load( ss, HJSON::PARSER::RELAXED );
	ENSURE_EQUALS( "[JSON] parsing relaxed JSON failed", json, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare JSON (==)" )
	HJSON a( make_json() );
	HJSON b( make_json() );
	ENSURE_EQUALS( "[JSON] equality operator failed", a, b );
	a.element()["records"][1]["data"] = 12.3456L;
	ENSURE_NOT( "[JSON] equality operator failed", a == b );
	b.element()["records"][1]["data"] = 12.3456L;
	ENSURE_EQUALS( "[JSON] equality operator failed", a, b );
	a.element()["records"][1]["data"] = "12.3456";
	ENSURE_NOT( "[JSON] equality operator failed", a == b );
	b.element()["records"][1]["data"] = "12.3456";
	ENSURE_EQUALS( "[JSON] equality operator failed", a, b );
	a.element()["records"][1]["data"] = "12.3457";
	ENSURE_NOT( "[JSON] equality operator failed", a == b );
	a.element()["records"][1]["data"] = HJSON::HValue::LITERAL::TRUE;
	b.element()["records"][1]["data"] = HJSON::HValue::LITERAL::TRUE;
	ENSURE_EQUALS( "[JSON] equality operator failed", a, b );
	a.element()["records"][1]["data"] = HJSON::HValue::LITERAL::FALSE;
	ENSURE_NOT( "[JSON] equality operator failed", a == b );
	a.element()["records"][1]["data"] = 7;
	b.element()["records"][1]["data"] = 7;
	ENSURE_EQUALS( "[JSON] equality operator failed", a, b );
	a.element()["records"][1]["data"] = -7;
	ENSURE_NOT( "[JSON] equality operator failed", a == b );
	HJSON c;
	HJSON d;
	ENSURE_EQUALS( "[JSON] equality operator failed", c, d );
TUT_TEARDOWN()

TUT_UNIT_TEST( "node type guards" )
	HJSON json;
	HJSON::HValue& r( json.element() );
	r = 7;
	HJSON::HValue const& cr( r );
	ENSURE_EQUALS( "integer getter failed", r.get_integer(), 7 );
	ENSURE_THROW( "array access type guard failed", r.push_back( 0 ), HJSONException );
	ENSURE_THROW( "array access type guard failed", r[0], HJSONException );
	ENSURE_THROW( "member access type guard failed", r["json"], HJSONException );
	ENSURE_THROW( "array access type guard failed", cr[0], HJSONException );
	ENSURE_THROW( "member access type guard failed", cr["json"], HJSONException );
	ENSURE_THROW( "array access type guard failed", r.get_elements(), HJSONException );
	ENSURE_THROW( "member access type guard failed", r.get_members(), HJSONException );
	ENSURE_THROW( "array access type guard failed", cr.get_elements(), HJSONException );
	ENSURE_THROW( "member access type guard failed", cr.get_members(), HJSONException );
	ENSURE_THROW( "real getter type guard failed", r.get_real(), HJSONException );
	ENSURE_THROW( "number getter type guard failed", r.get_number(), HJSONException );
	ENSURE_THROW( "string getter type guard failed", r.get_string(), HJSONException );
	ENSURE_THROW( "literal getter type guard failed", r.get_literal(), HJSONException );
	r = 0.0;
	ENSURE_THROW( "integer getter type guard failed", r.get_integer(), HJSONException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generator errors" )
	HJSON json;
	HStringStream ss;
	json.save( ss );
	ENSURE_EQUALS( "serialization of empty JSON failed", ss.string(), "" );
	HJSON::HValue& r( json.element() );
	r["elem"];
	ENSURE_THROW( "serialization of uninitialized node succeeded", json.save( ss ), HJSONException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parser errors" )
	HJSON json;
	HStringStream ss( "{\"almost\": \"a\" }" );
	json.load( ss );
	json.clear();
	ss.str( "{\"almost\": \"a\", 7 }" );
	ENSURE_THROW( "serialization of uninitialized node succeeded", json.load( ss ), HJSONException );
TUT_TEARDOWN()

}


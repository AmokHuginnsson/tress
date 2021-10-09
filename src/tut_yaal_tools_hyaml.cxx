/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hyaml.hxx>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::model;
using namespace tress::tut_helpers;

namespace yaal {
namespace tools {
inline std::ostream& operator << ( std::ostream& out, HYAML const& json_ ) {
	HStringStream ss;
	json_.save( ss );
	HUTF8String utf8( ss.string() );
	out.write( utf8.c_str(), utf8.byte_count() );
	return out;
}
}
}

namespace tut {

struct tut_yaal_tools_hyaml : public simple_mock<tut_yaal_tools_hyaml> {
	virtual ~tut_yaal_tools_hyaml( void ) {}
};

namespace {

HYAML make_yaml( void ) {
	HYAML yaml;
	HValue& r( yaml.add_document() );
	r["name"] = "nameValue";
	r["date"] = HTime( 1978, 5, 24 );
	HValue::array_t& records( r["records"].get_elements() );
	records.push_back(
		HValue::members_t({
			{ "id", "int" },
			{ "data", 9 }
		})
	);
	records.push_back(
		HValue::members_t({
			{ "id", "float" },
			{ "data", 12.345L }
		})
	);
	records.push_back(
		HValue::members_t({
			{ "id", "str" },
			{ "data", "yaal-YAML" }
		})
	);
	r["number_like"] = HValue::members_t({
		{ "int", 13 },
		{ "real", 3.14159265359L },
		{ "number", "2.718281828459045235360287471"_yn }
	});
	HValue::members_t& empty( r["empty"].get_members() );
	empty.insert( make_pair( "arr", HValue::array_t() ) );
	empty.insert( make_pair( "obj", HValue::members_t() ) );
	r["banner"] = "yaal's YAML generator";
	r["quoted"] = "yaal's {YAML} generator";
	r["literals"] = HValue::array_t({ HValue::LITERAL::TRUE, HValue::LITERAL::FALSE,	HValue::LITERAL::NULL });
	return yaml;
}

char const complexYAML[] =
	"name: nameValue\n"
	"date: 1978-05-24\n"
	"records:\n"
	"- id: int\n"
	"  data: 9\n"
	"- id: float\n"
	"  data: 12.345\n"
	"- id: str\n"
	"  data: yaal-YAML\n"
	"number_like:\n"
	"  int: 13\n"
	"  real: 3.14159265359\n"
	"  number: 2.718281828459045235360287471\n"
	"empty:\n"
	"  arr: []\n"
	"  obj: {}\n"
	"banner: yaal's YAML generator\n"
	"quoted: \"yaal's {YAML} generator\"\n"
	"literals:\n"
	"- true\n"
	"- false\n"
	"- null\n"
;

}

#ifdef __HOST_OS_TYPE_CENTOS__
#define end_implicit_workaround "...\n"
#else
#define end_implicit_workaround
#endif

TUT_TEST_GROUP( tut_yaal_tools_hyaml, "yaal::tools::HYAML" );

TUT_UNIT_TEST( "generate int" )
	HYAML yaml;
	yaml.add_document() = 13;
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just an int generation failed", ss.string(), "13\n" end_implicit_workaround );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate real" )
	HYAML yaml;
	yaml.add_document() = 3.141592653589793L;
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a real generation failed", ss.string(), "3.14159265359\n" end_implicit_workaround );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate number" )
	HYAML yaml;
	yaml.add_document() = "2.718281828459045"_yn;
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a number generation failed", ss.string(), "2.718281828459045\n" end_implicit_workaround );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate string" )
	HYAML yaml;
	model::HValue& doc( yaml.add_document() );
	doc = "yaal's YAML generator";
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a string generation failed", ss.string(), "yaal's YAML generator\n" end_implicit_workaround );
	ss.reset();
	doc = "yaal's {YAML} generator";
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a string generation failed", ss.string(), "\"yaal's {YAML} generator\"\n" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate timestamp" )
	HYAML yaml;
	model::HValue& doc( yaml.add_document() );
	doc = HTime( 1978, 5, 24, 23, 30, 17 );
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a timestamp generation failed", ss.string(), "1978-05-24 23:30:17\n" end_implicit_workaround );
	ss.reset();
	doc = HTime( 1989, 8, 24 );
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a timestamp generation failed", ss.string(), "1989-08-24\n" end_implicit_workaround );
	ss.reset();
	doc = HTime( 0, 1, 1, 13, 49, 27 );
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a timestamp generation failed", ss.string(), "13:49:27\n" end_implicit_workaround );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate literal" )
	HYAML yaml;
	model::HValue& doc( yaml.add_document() );
	doc = HValue::LITERAL::TRUE;
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a literal generation failed", ss.string(), "true\n" end_implicit_workaround );
	doc = HValue::LITERAL::FALSE;
	ss.reset();
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a literal generation failed", ss.string(), "false\n" end_implicit_workaround );
	doc = HValue::LITERAL::NULL;
	ss.reset();
	yaml.save( ss );
	ENSURE_EQUALS( "[YAML] just a literal generation failed", ss.string(), "null\n" end_implicit_workaround );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate array" )
	HYAML yaml;
	model::HValue& doc( yaml.add_document() );
	doc.push_back( 13 );
	doc.push_back( 3.141592653589793L );
	doc.push_back( "2.718281828459045"_yn );
	doc.push_back( HTime( 1978, 5, 24, 23, 30, 17 ) );
	doc.push_back( "yaal's YAML generator" );
	doc.push_back( "yaal's {YAML} generator" );
	doc.push_back( HValue::LITERAL::TRUE );
	doc.push_back( HValue::LITERAL::FALSE );
	doc.push_back( HValue::LITERAL::NULL );
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS(
		"[YAML] just an array generation failed",
		ss.string(),
		"- 13\n"
		"- 3.14159265359\n"
		"- 2.718281828459045\n"
		"- 1978-05-24 23:30:17\n"
		"- yaal's YAML generator\n"
		"- \"yaal's {YAML} generator\"\n"
		"- true\n"
		"- false\n"
		"- null\n"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate object" )
	HYAML yaml;
	HValue::members_t& m( yaml.add_document().get_members() );
	m["bad_luck"] = 13;
	m["pi"] = 3.141592653589793L;
	m["e"] = "2.718281828459045"_yn;
	m["bday"] = HTime( 1978, 5, 24 );
	m["banner"] = "yaal's YAML generator";
	m["quoted"] = "yaal's {YAML} generator";
	m["true"] = HValue::LITERAL::TRUE;
	m["false"] = HValue::LITERAL::FALSE;
	m["null"] = HValue::LITERAL::NULL;
	HStringStream ss;
	yaml.save( ss );
	char const expectedNL[] =
		"bad_luck: 13\n"
		"pi: 3.14159265359\n"
		"e: 2.718281828459045\n"
		"bday: 1978-05-24\n"
		"banner: yaal's YAML generator\n"
		"quoted: \"yaal's {YAML} generator\"\n"
		"true: true\n"
		"false: false\n"
		"null: null\n"
	;
	ENSURE_EQUALS( "[YAML] just an object generation failed", ss.string(), expectedNL );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generate complex YAML" )
	HYAML yaml( make_yaml() );
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS(
		"[YAML] just an object generation failed",
		ss.string(),
		complexYAML
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse int" )
	HYAML expected;
	expected.add_document() = 13;
	HYAML yaml;
	HStringStream ss( "13" );
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone int failed", yaml, expected );
	yaml.clear();
	ss << "13" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone int failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse real" )
	HYAML expected;
	expected.add_document() = 3.14159265359L;
	HYAML yaml;
	HStringStream ss( "3.14159265359" );
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone real failed", yaml, expected );
	yaml.clear();
	ss << "3.14159265359" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone real failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse number" )
	HYAML expected;
	expected.add_document() = "2.718281828459045235360287471"_yn;
	HYAML yaml;
	HStringStream ss( "2.718281828459045235360287471" );
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone number failed", yaml, expected );
	yaml.clear();
	ss << "2.718281828459045235360287471" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone number failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse string" )
	HYAML expected;
	expected.add_document() = "yaal's YAML generator";
	HYAML yaml;
	HStringStream ss( "\"yaal's YAML generator\"" );
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone string failed", yaml, expected );
	yaml.clear();
	ss << "\"yaal's YAML generator\"" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone string failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse literal" )
	HYAML expected;
	model::HValue& doc( expected.add_document() );
	doc = HValue::LITERAL::TRUE;
	HStringStream ss( "true" );
	HYAML yaml;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone literal(true) failed", yaml, expected );
	yaml.clear();
	ss << "true" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone literal(true) failed", yaml, expected );

	doc = HValue::LITERAL::FALSE;
	yaml.clear();
	ss << "false";
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone literal(false) failed", yaml, expected );
	yaml.clear();
	ss << "false" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone literal(false) failed", yaml, expected );

	doc = HValue::LITERAL::NULL;
	yaml.clear();
	ss << "null";
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone literal(null) failed", yaml, expected );
	yaml.clear();
	ss << "null" << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone literal(null) failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse array" )
	HYAML expected;
	model::HValue& doc( expected.add_document() );
	doc.push_back( 13 );
	doc.push_back( 3.14159265359L );
	doc.push_back( "2.718281828459045235360287471"_yn );
	doc.push_back( "yaal's YAML generator" );
	doc.push_back( HValue::LITERAL::TRUE );
	doc.push_back( HValue::LITERAL::FALSE );
	doc.push_back( HValue::LITERAL::NULL );
	char const data[] = "[13, 3.14159265359, 2.718281828459045235360287471, \"yaal's YAML generator\", true, false, null]\n";
	HStringStream ss( data );
	HYAML yaml;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone array failed", yaml, expected );
	ss << data << endl;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone array failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse object" )
	HYAML expected;
	model::HValue& doc( expected.add_document() );
	doc["bad_luck"] = 13;
	doc["pi"] = 3.14159265359L;
	doc["e"] = "2.718281828459045235360287471"_yn;
	doc["banner"] = "yaal's YAML generator";
	doc["quoted"] = "yaal's {YAML} generator";
	doc["true"] = HValue::LITERAL::TRUE;
	doc["false"] = HValue::LITERAL::FALSE;
	doc["null"] = HValue::LITERAL::NULL;
	HStringStream ss(
		"bad_luck: 13\n"
		"pi: 3.14159265359\n"
		"e: 2.718281828459045235360287471\n"
		"banner: yaal's YAML generator\n"
		"quoted: \"yaal's {YAML} generator\"\n"
		"true: true\n"
		"false: false\n"
		"null: null\n"
	);
	HYAML yaml;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone object failed", yaml, expected );
	ss.str(
		"bad_luck: 13\n"
		"pi: 3.14159265359\n"
		"e: 2.718281828459045235360287471\n"
		"banner: yaal's YAML generator\n"
		"quoted: \"yaal's {YAML} generator\"\n"
		"true: true\n"
		"false: false\n"
		"null: null\n"
	);
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing alone object failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parse complex YAML" )
	HYAML expected( make_yaml() );
	HStringStream ss( complexYAML );
	HYAML yaml;
	yaml.load( ss );
	ENSURE_EQUALS( "[YAML] parsing complex YAML failed", yaml, expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( "compare YAML (==)" )
	HYAML ya( make_yaml() );
	model::HValue& a( ya.documents().front() );
	HYAML yb( make_yaml() );
	model::HValue& b( yb.documents().front() );
	ENSURE_EQUALS( "[YAML] equality operator failed", ya, yb );
	a["records"][1]["data"] = 12.3456L;
	ENSURE_NOT( "[YAML] equality operator failed", ya == yb );
	b["records"][1]["data"] = 12.3456L;
	ENSURE_EQUALS( "[YAML] equality operator failed", ya, yb );
	a["records"][1]["data"] = "12.3456";
	ENSURE_NOT( "[YAML] equality operator failed", ya == yb );
	b["records"][1]["data"] = "12.3456";
	ENSURE_EQUALS( "[YAML] equality operator failed", ya, yb );
	a["records"][1]["data"] = "12.3457";
	ENSURE_NOT( "[YAML] equality operator failed", ya == yb );
	a["records"][1]["data"] = HValue::LITERAL::TRUE;
	b["records"][1]["data"] = HValue::LITERAL::TRUE;
	ENSURE_EQUALS( "[YAML] equality operator failed", ya, yb );
	a["records"][1]["data"] = HValue::LITERAL::FALSE;
	ENSURE_NOT( "[YAML] equality operator failed", ya == yb );
	a["records"][1]["data"] = 7;
	b["records"][1]["data"] = 7;
	ENSURE_EQUALS( "[YAML] equality operator failed", ya, yb );
	a["records"][1]["data"] = -7;
	ENSURE_NOT( "[YAML] equality operator failed", ya == yb );
	HYAML c;
	HYAML d;
	ENSURE_EQUALS( "[YAML] equality operator failed", c, d );
TUT_TEARDOWN()

TUT_UNIT_TEST( "node type guards" )
	HYAML yaml;
	HValue& r( yaml.add_document() );
	r = 7;
	HValue const& cr( r );
	ENSURE_EQUALS( "integer getter failed", r.get_integer(), 7 );
	ENSURE_THROW( "array access type guard failed", r.push_back( 0 ), HModelException );
	ENSURE_THROW( "array access type guard failed", r[0], HModelException );
	ENSURE_THROW( "member access type guard failed", r["yaml"], HModelException );
	ENSURE_THROW( "array access type guard failed", cr[0], HModelException );
	ENSURE_THROW( "member access type guard failed", cr["yaml"], HModelException );
	ENSURE_THROW( "array access type guard failed", r.get_elements(), HModelException );
	ENSURE_THROW( "member access type guard failed", r.get_members(), HModelException );
	ENSURE_THROW( "array access type guard failed", cr.get_elements(), HModelException );
	ENSURE_THROW( "member access type guard failed", cr.get_members(), HModelException );
	ENSURE_THROW( "real getter type guard failed", r.get_real(), HModelException );
	ENSURE_THROW( "number getter type guard failed", r.get_number(), HModelException );
	ENSURE_THROW( "string getter type guard failed", r.get_string(), HModelException );
	ENSURE_THROW( "literal getter type guard failed", r.get_literal(), HModelException );
	ENSURE_THROW( "timestamp getter type guard failed", r.get_time(), HModelException );
	r = 0.0;
	ENSURE_THROW( "integer getter type guard failed", r.get_integer(), HModelException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "generator errors" )
	HYAML yaml;
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS( "serialization of empty YAML failed", ss.string(), "" );
	HValue& r( yaml.add_document() );
	r["elem"];
	ENSURE_THROW( "serialization of uninitialized node succeeded", yaml.save( ss ), HYAMLException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parser errors" )
	HYAML yaml;
	HStringStream ss( "almost: a\n" );
	yaml.load( ss );
	yaml.clear();
	ss.str( "almost: a\nb\n  c\n" );
	ENSURE_THROW( "paring of malformed node succeeded", yaml.load( ss ), HYAMLException );
TUT_TEARDOWN()

char const specialYAML[] =
	"quote: text \"citation\" epilog\n"
	"newline: |-\n"
	"  text\n"
	"  next line\n"
	"mixed: |-\n"
	"  text \"Q\"\n"
	"  \"Q\"\n"
	"path: c:\\windows\\system\\etc\\\"hosts\"\n"
;

TUT_UNIT_TEST( "embedded quotes on parsing" )
	HYAML yaml;
	model::HValue& doc( yaml.add_document() );
	HStringStream ss( specialYAML );
	yaml.load( ss );
	ENSURE_EQUALS( "embedded quotes failed during parsing", doc["quote"].get_string(), "text \"citation\" epilog" );
	ENSURE_EQUALS( "embedded newline failed during parsing", doc["newline"].get_string(), "text\nnext line" );
	ENSURE_EQUALS( "embedded quotes and newline failed during parsing", doc["mixed"].get_string(), "text \"Q\"\n\"Q\"" );
	ENSURE_EQUALS( "embedded with quotes & paths failed during parsing", doc["path"].get_string(), "c:\\windows\\system\\etc\\\"hosts\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "embedded quotes during emiting" )
	HYAML yaml;
	model::HValue& doc( yaml.add_document() );
	doc["quote"] = "text \"citation\" epilog";
	doc["newline"] = "text\nnext line";
	doc["mixed"] = "text \"Q\"\n\"Q\"";
	doc["path"] = "c:\\windows\\system\\etc\\\"hosts\"";
	HStringStream ss;
	yaml.save( ss );
	ENSURE_EQUALS(
		"embedded quotes failed during embedded",
		ss.str(),
		specialYAML
	);
TUT_TEARDOWN()

}


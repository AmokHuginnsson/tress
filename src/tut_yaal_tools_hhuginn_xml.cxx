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

struct tut_yaal_tools_hhuginn_xml : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_xml( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_xml, "yaal::tools::HHuginn.XML" );

TUT_UNIT_TEST( "load" )
	ENSURE_EQUALS(
		"XML.load failed",
		execute(
			"import XML as xml;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"file = fs.open(\"data/xml.xml\", fs.OPEN_MODE.READ);\n"
			"doc = xml.load(file);\n"
			"return ( doc.root().name() );\n"
			"}\n"
		),
		"\"my_root\""
	);
	ENSURE_EQUALS(
		"XML.load failed",
		execute_except(
			"import XML as xml;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"file = fs.open(\"data/nl.txt\", fs.OPEN_MODE.READ);\n"
			"xml.load(file);\n"
			"}\n"
		),
		"*anonymous stream*:5:9: Uncaught XMLException: cannot parse `data/nl.txt'"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "create" )
	ENSURE_EQUALS(
		"XML.create failed",
		execute(
			"import XML as xml;\n"
			"main() {\n"
			"doc = xml.create(\"DOM\");\n"
			"return ( doc.root().name() );\n"
			"}\n"
		),
		"\"DOM\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "tree walk" )
	ENSURE_EQUALS(
		"tree walk failed",
		execute(
			"import XML as xml;\n"
			"import FileSystem as fs;\n"
			"dump_node( log, n ) {\n"
			"	log.push( ( type( n ), n.name() ) );\n"
			"	for ( e : n ) {\n"
			"		if ( type( e ) == xml.Element ) {\n"
			"			dump_node( log, e );\n"
			"		} else {\n"
			"			log.push( ( type( e ), string( e ).strip() ) );\n"
			"		}\n"
			"	}\n"
			"}\n"
			"main() {\n"
			"file = fs.open(\"data/xml.xml\", fs.OPEN_MODE.READ);\n"
			"doc = xml.load(file);\n"
			"log = [];\n"
			"dump_node( log, doc.root() );\n"
			"return ( log );\n"
			"}\n"
		),
		"[(xml.Element, \"my_root\"),"
		" (xml.Element, \"my_node\"),"
		" (xml.Element, \"my_sub\"),"
		" (xml.Text, \"node\"),"
		" (xml.Text, \"Zażółcić gęsią jaźń.\"),"
		" (xml.Entity, \"my precious data\"),"
		" (xml.Text, \"Filmuj rzeź żądań, pość, gnęb chłystków!\nMężny bądź, chroń pułk twój i sześć flag.\"),"
		" (xml.Element, \"my_empty\"),"
		" (xml.Element, \"xi:include\"),"
		" (xml.Element, \"my_set\"),"
		" (xml.Element, \"my_item\"),"
		" (xml.Text, \"one\"),"
		" (xml.Entity, \"<xml:entity_reference>&amp;trade;</xml:entity_reference>\"),"
		" (xml.Element, \"my_item\"),"
		" (xml.Text, \"two\"),"
		" (xml.Element, \"my_fake\"),"
		" (xml.Text, \"three\"),"
		" (xml.Element, \"my_item\"),"
		" (xml.Text, \"four\"),"
		" (xml.Comment, \"my_item>hidden</my_item\"),"
		" (xml.Element, \"my_special\"),"
		" (xml.Element, \"my_sub\"),"
		" (xml.Element, \"my_element\"),"
		" (xml.Element, \"my_sub\"),"
		" (xml.Text, \"data\"),"
		" (xml.Element, \"my_sub\"),"
		" (xml.Entity, \"my precious data\")]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Element.append" )
	ENSURE_EQUALS(
		"XML.Element.append or XML.Document.save failed",
		execute(
			"import XML as xml;\n"
			"import Text as text;\n"
			"main() {\n"
			"doc = xml.create(\"DOM\");\n"
			"doc.root().append( xml.Text, \"Huginn\" );\n"
			"s = text.stream();\n"
			"doc.save( s );\n"
			"return ( s.read_string( 1000 ) );\n"
			"}\n"
		),
		"\"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<DOM>Huginn</DOM>\n\""
	);
	ENSURE_EQUALS(
		"XML.Element.append of integer succeeded",
		execute_except(
			"import XML as xml;\n"
			"main() {\n"
			"doc = xml.create(\"DOM\");\n"
			"doc.root().append(integer,\"\");\n"
			"}\n"
		),
		"*anonymous stream*:4:18: Node type must be one of: `XML.Element`, `XML.Text`, `XML.Comment` or `XML.Entity`, not `integer`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy(Doc), copy(Element)" )
	ENSURE_EQUALS(
		"copy on XML.Element succeeded",
		execute_except(
			"import XML as xml;\n"
			"main() {\n"
			"doc = xml.create(\"DOM\");\n"
			"copy( doc.root() );\n"
			"}\n"
		),
		"*anonymous stream*:4:5: Copy semantics is not supported on `XML.Element`s."
	);
	ENSURE_EQUALS(
		"copy on XML.Document failed",
		execute(
			"import XML as xml;\n"
			"import Text as text;\n"
			"main() {\n"
			"doc = xml.create(\"DOM\");\n"
			"doc.root().append( xml.Text, \"Huginn\" );\n"
			"doc2 = copy( doc );\n"
			"doc.root().append( xml.Element, \"child\" );\n"
			"s = text.stream();\n"
			"doc.save( s );\n"
			"res = [];\n"
			"res.push(s.read_string( 1000 ));\n"
			"doc2.save( s );\n"
			"res.push(s.read_string( 1000 ));\n"
			"return ( res );\n"
			"}\n"
		),
		"[\"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<DOM>Huginn\t<child/>\n</DOM>\n\", \"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<DOM>Huginn</DOM>\n\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "parent, subscript, Element.document" )
	ENSURE_EQUALS(
		"XML.Element.parent or XML.Element.subscript or XML.Element.document failed",
		execute(
			"import XML as xml;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"file = fs.open(\"data/xml.xml\", fs.OPEN_MODE.READ);\n"
			"doc = xml.load(file);\n"
			"r = doc.root();\n"
			"docRef = r.document();\n"
			"root = docRef.root();\n"
			"child = root[0];\n"
			"return ( [child.name(), child.parent().name()] );\n"
			"}\n"
		),
		"[\"my_node\", \"my_root\"]"
	);
	ENSURE_EQUALS(
		"invalid XML.Element.subscript index succeeded",
		execute_except(
			"import XML as xml;\n"
			"import FileSystem as fs;\n"
			"main() {\n"
			"file = fs.open(\"data/xml.xml\", fs.OPEN_MODE.READ);\n"
			"root = xml.load(file).root();\n"
			"root[5];\n"
			"}\n"
		),
		"*anonymous stream*:6:5: Invalid `XML.Element` child index: 5"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "remove, remove_nth" )
	ENSURE_EQUALS(
		"XML.Element.remove or XML.Element.remove_nth failed",
		execute(
			"import XML as xml;\n"
			"import Text as text;\n"
			"main() {\n"
			"xmlStr = text.stream( \"<?xml version=\\\"1.0\\\" encoding=\\\"utf-8\\\"?><r><n1><c1></c1><c2></c2></n1><n2><c1></c1><c2><l>text</l></c2></n2><n3><c1></c1><c2></c2></n3></r>\" );\n"
			"doc = xml.load(xmlStr);\n"
			"s = text.stream();\n"
			"res = [];"
			"doc.save( s );\n"
			"res.push( s.read_string( 1000 ).replace( \"\\t\", \"\" ).replace( \"\\n\", \"\" ) );\n"
			"r = doc.root();\n"
			"r.remove( r[2] );\n"
			"doc.save( s );\n"
			"res.push( s.read_string( 1000 ).replace( \"\\t\", \"\" ).replace( \"\\n\", \"\" ) );\n"
			"r.remove_nth( 0 );\n"
			"doc.save( s );\n"
			"res.push( s.read_string( 1000 ).replace( \"\\t\", \"\" ).replace( \"\\n\", \"\" ) );\n"
			"return ( res );\n"
			"}\n"
		),
		"[\"<?xml version=\"1.0\" encoding=\"UTF-8\"?><r><n1><c1/><c2/></n1><n2><c1/><c2><l>text</l></c2></n2><n3><c1/><c2/></n3></r>\","
		" \"<?xml version=\"1.0\" encoding=\"UTF-8\"?><r><n1><c1/><c2/></n1><n2><c1/><c2><l>text</l></c2></n2></r>\","
		" \"<?xml version=\"1.0\" encoding=\"UTF-8\"?><r><n2><c1/><c2><l>text</l></c2></n2></r>\"]"
	);
	ENSURE_EQUALS(
		"remove during for loop failed",
		execute(
			"import XML as xml;\n"
			"import Text as text;\n"
			"main() {\n"
			"xmlStr = text.stream( \"<?xml version=\\\"1.0\\\" encoding=\\\"utf-8\\\"?><r><n1><c1></c1><c2></c2></n1><n2><c1></c1><c2><l>text</l></c2></n2><n3><c1></c1><c2></c2></n3></r>\" );\n"
			"doc = xml.load(xmlStr);\n"
			"res = [];"
			"for ( e : doc.root() ) {\n"
			"res.push( e.name() );\n"
			"e.parent().remove( e );\n"
			"}\n"
			"s = text.stream();\n"
			"doc.save( s );\n"
			"res.push( s.read_string( 1000 ).replace( \"\\t\", \"\" ).replace( \"\\n\", \"\" ) );\n"
			"return ( res );\n"
			"}\n"
		),
		"[\"n1\", \"n2\", \"n3\", \"<?xml version=\"1.0\" encoding=\"UTF-8\"?><r/>\"]"
	);
TUT_TEARDOWN()

}


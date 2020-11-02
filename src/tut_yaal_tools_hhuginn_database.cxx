/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hmonitor.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_database : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_database( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_database, "yaal::tools::HHuginn.Database" );

TUT_UNIT_TEST( "table_names" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	ENSURE_EQUALS(
		"DatabaseConnection.table_names",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"return(dbc.table_names());"
			"}"
		),
		"[\"config\", \"crud\", \"test\", \"test_dict\", \"test_item\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "column_names" )
	ENSURE_EQUALS(
		"DatabaseConnection.column_names",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"return(dbc.column_names(\"config\"));"
			"}"
		),
		"[\"id\", \"name\", \"data\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "query" )
	ENSURE_EQUALS(
		"DatabaseConnection.query, Query, QueryResult",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"q=dbc.query(\"SELECT name FROM config WHERE id != ?;\");"
			"q.bind(1, \"2\");"
			"qr=q.execute();"
			"res=\"\";"
			"i=0;"
			"fc=qr.field_count();"
			"while(i<fc){"
			"res+=qr.column_name(i);"
			"res+=\",\";"
			"i+=1;"
			"}"
			"if(qr.has_next()){"
			"for(r:qr){"
			"for(v:r){"
			"res+=v;"
			"res+=\",\";"
			"}"
			"}"
			"}"
			"q=dbc.query(\"SELECT name, data FROM config WHERE id = ?;\");"
			"q.bind(1, \"2\");"
			"qr=q.execute();"
			"while(qr.has_next()){"
			"for(v:qr.fetch_row()){"
			"res+=(v!=none ? v : \"none\");"
			"res+=\",\";"
			"}"
			"}"
			"q=dbc.query(\"INSERT INTO config ( name, data ) VALUES ( ?, ? );\");"
			"q.bind(1, \"special\");"
			"q.bind(2, \"special_value\");"
			"qr=q.execute();"
			"res += string(qr.insert_id());"
			"q=dbc.query(\"DELETE FROM config WHERE name = ?;\");"
			"q.bind(1, \"special\");"
			"qr = q.execute();"
			"res += \",\";"
			"res += string(size(qr));"
			"return(res);"
			"}"
		),
		"\"name,one,three,two,none,4,1\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect invalid" )
	ENSURE_EQUALS(
		"DatabaseConnection.connect exception",
		execute(
			"import Database as db;"
			"main(){"
			"try{"
			"db.connect(\"sqlite3:///out/tress-non-existing\");"
			"}catch(DatabaseException  e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:44: Database file `out/tress-non-existing.sqlite' is not accessible.\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "query invalid" )
	ENSURE_EQUALS(
		"DatabaseConnection.query exception",
		execute(
			"import Database as db;"
			"main(){"
			"try{"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"dbc.query(\"invalid;\");"
			"}catch(DatabaseException  e){"
			"return ( e.message() );"
			"}"
			"}"
		),
		"\"*anonymous stream*:1:82: SQL prepare error: 'invalid;': near \\\"invalid\\\": syntax error\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy connection exception" )
	ENSURE_EQUALS(
		"DatabaseConnection.copy exception",
		execute_except(
			"import Database as db;\n"
			"main(){\n"
			"dbc=db.connect(\"sqlite3:///out/tress\");\n"
			"copy(dbc);\n"
			"}\n"
		),
		"*anonymous stream*:4:5: Copy semantics is not supported on DatabaseConnection."
	);
TUT_TEARDOWN()

}


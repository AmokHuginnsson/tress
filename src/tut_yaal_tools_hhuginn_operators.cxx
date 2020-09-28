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

struct tut_yaal_tools_hhuginn_operators : public tress::tut_yaal_tools_hhuginn_base {
	virtual ~tut_yaal_tools_hhuginn_operators( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_operators, "yaal::tools::HHuginn.Operators" );

TUT_UNIT_TEST( "add" )
	ENSURE_EQUALS(
		"Operators.add failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.add(1,2));\n"
			"}"
		),
		"3"
	);
	ENSURE_EQUALS(
		"Operators.add failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.add(1,2.));\n"
			"}"
		),
		"*anonymous stream*:3:16: Operand types for `+` do not match: an `integer` vs a `real`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "less" )
	ENSURE_EQUALS(
		"Operators.less failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return((oper.less(1,2), oper.less(1,1)));\n"
			"}"
		),
		"(true, false)"
	);
	ENSURE_EQUALS(
		"Operators.less failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.less(1,2.));\n"
			"}"
		),
		"*anonymous stream*:3:17: Operand types for `<` do not match: an `integer` vs a `real`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "equals" )
	ENSURE_EQUALS(
		"Operators.equals failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return((oper.equals(1,2), oper.equals(1,1), oper.equals(1,none), oper.equals(none, 1)));\n"
			"}"
		),
		"(false, true, false, false)"
	);
	ENSURE_EQUALS(
		"Operators.equals failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.equals(1,2.));\n"
			"}"
		),
		"*anonymous stream*:3:19: Operand types for `==` do not match: an `integer` vs a `real`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "and" )
	ENSURE_EQUALS(
		"Operators.and failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return((oper.and(true,true),oper.and(true,false)));\n"
			"}"
		),
		"(true, false)"
	);
	ENSURE_EQUALS(
		"Operators.and failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.and(true,1));\n"
			"}"
		),
		"*anonymous stream*:3:16: Operators.and() second argument must be a `boolean`, not an `integer`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "is_element_of" )
	ENSURE_EQUALS(
		"Operators.is_element_of failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return((oper.is_element_of(1,[0,1,2]), oper.is_element_of(1,[0,2])));\n"
			"}"
		),
		"(true, false)"
	);
	ENSURE_EQUALS(
		"Operators.is_element_of failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.is_element_of(1,2));\n"
			"}"
		),
		"*anonymous stream*:3:26: Operand is not a collection type: an `integer`"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "negate" )
	ENSURE_EQUALS(
		"Operators.negate failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.negate(1));\n"
			"}"
		),
		"-1"
	);
	ENSURE_EQUALS(
		"Operators.negate failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.negate('a'));\n"
			"}"
		),
		"*anonymous stream*:3:19: There is no `-x` operator for a `character`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "not" )
	ENSURE_EQUALS(
		"Operators.not failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.not(true));\n"
			"}"
		),
		"false"
	);
	ENSURE_EQUALS(
		"Operators.not failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.not('a'));\n"
			"}"
		),
		"*anonymous stream*:3:16: Operators.not() argument must be a `boolean`, not a `character`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "subscript" )
	ENSURE_EQUALS(
		"Operators.subscript failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.subscript(\"Huginn\",3));\n"
			"}"
		),
		"'i'"
	);
	ENSURE_EQUALS(
		"Operators.subscript failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.subscript(1,2));\n"
			"}"
		),
		"*anonymous stream*:3:22: Subscript is not supported on an `integer`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "range" )
	ENSURE_EQUALS(
		"Operators.range failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.range(\"Huginn\",2));\n"
			"}"
		),
		"\"ginn\""
	);
	ENSURE_EQUALS(
		"Operators.range failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.range(\"abcdefghijk\",2,5));\n"
			"}"
		),
		"\"cde\""
	);
	ENSURE_EQUALS(
		"Operators.range failed",
		execute(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.range(\"abcdefghijk\",2,12,2));\n"
			"}"
		),
		"\"cegik\""
	);
	ENSURE_EQUALS(
		"Operators.range failed",
		execute_except(
			"import Operators as oper;\n"
			"main(){\n"
			"return(oper.range(1,2));\n"
			"}"
		),
		"*anonymous stream*:3:18: Range operator is not supported on an `integer`."
	);
TUT_TEARDOWN()

}


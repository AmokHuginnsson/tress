/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hterminal.hxx>
#include <yaal/tools/ansi.hxx>
#include <yaal/tools/hmonitor.hxx>
#include <yaal/hcore/hcore.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"
#include "fake_console_subsystem.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_terminal : public tress::tut_yaal_tools_hhuginn_base {
#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
	tress::fake_console_subsystem::HFakeConsoleGuard _fakeConoleGuard;
	tut_yaal_tools_hhuginn_terminal( void )
		: _fakeConoleGuard() {
	}
#endif /* #if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */
	virtual ~tut_yaal_tools_hhuginn_terminal( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_terminal, "yaal::tools::HHuginn.Terminal" );

TUT_UNIT_TEST( "is_valid" )
	ENSURE_EQUALS(
		"Terminal.is_valid failed",
		execute(
			"import Terminal as term;\n"
			"main(){\n"
			"return(term.is_valid());\n"
			"}"
		),
		HTerminal::get_instance().exists() ? "true" : "false"
	);
TUT_TEARDOWN()

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
TUT_UNIT_TEST( "lines columns" )
	ENSURE_EQUALS(
		"Terminal.lines and Terminal.columns failed",
		execute_except(
			"import Terminal as term;\n"
			"main(){\n"
			"return((term.lines(),term.columns()));\n"
			"}"
		),
		"*anonymous stream*:3:19: Inappropriate ioctl for device"
	);
	set_env( "LINES", "25" );
	set_env( "COLUMNS", "80" );
	ENSURE_EQUALS(
		"Terminal.lines and Terminal.columns failed",
		execute(
			"import Terminal as term;\n"
			"main(){\n"
			"return((term.lines(),term.columns()));\n"
			"}"
		),
		"(25, 80)"
	);
TUT_TEARDOWN()
#endif /* #if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */

TUT_UNIT_TEST( "attribute" )
	ENSURE_EQUALS(
		"Terminal.attribute failed",
		execute(
			"import Terminal as term;\n"
			"main(){\n"
			"return(term.attribute(term.ATTRIBUTE.BOLD,\"bold\"));\n"
			"}"
		),
		"\""_ys.append( *ansi::bold ).append( "bold" ).append( *ansi::reset ).append( '"' )
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "color" )
	ENSURE_EQUALS(
		"Terminal.color failed",
		execute(
			"import Terminal as term;\n"
			"main(){\n"
			"return(term.color(term.COLOR.BRIGHTBLUE,\"brightblue\"));\n"
			"}"
		),
		"\""_ys.append( *ansi::brightblue ).append( "brightblue" ).append( *ansi::reset ).append( '"' )
	);
TUT_TEARDOWN()

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
TUT_UNIT_TEST( "move" )
	ENSURE_EQUALS(
		"Terminal.move failed",
		execute(
			"import Terminal as term;\n"
			"main(){\n"
			"return(term.move(7,13));\n"
			"}"
		),
		"\"\033[8;14H\""
	);
TUT_TEARDOWN()
#endif /* #if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */

TUT_UNIT_TEST( "save, clear, restore, reset" )
	ENSURE_EQUALS(
		"Terminal.(save, clear, restore, reset) failed",
		execute(
			"import Terminal as term;\n"
			"main(){\n"
			"return((term.save(),term.clear(),term.restore(),term.reset()));\n"
			"}"
		),
		"(\"\033[s\", \"\033[2J\", \"\033[u\", \"\033[0m\")"
	);
TUT_TEARDOWN()

}


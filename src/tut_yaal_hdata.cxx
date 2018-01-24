/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <yaal/config.hxx>
#include "config.hxx"

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
#ifndef __HOST_OS_TYPE_DARWIN__
#if TARGET_CPU_BITS == 64

#include <TUT/tut.hpp>

#include <yaal/hdata/hdataprocess.hxx>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hconsole_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;
using namespace yaal::hdata;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hdata : public tut_yaal_hconsole_base {
	tui_t do_make_tui( void ) override {
		tui_t tui( new HDataProcess() );
		return ( tui );
	}
};

TUT_TEST_GROUP( tut_yaal_hdata, "yaal::hdata" );

TUT_UNIT_TEST( "load data" )
	play( "load data", { '\r', KEY<'q'>::command, KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "cancel add record" )
	play( "load data", { '\r', KEY<'n'>::command, 'a', KEY<'q'>::command, KEY_CODE::LEFT, '\r', KEY<'x'>::command } );
	play( "load data", { '\r', KEY<'n'>::command, 'a', KEY<'q'>::command, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, '\r', KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add record (no children)" )
	play(
		"add record", {
			'\r',
			KEY<'n'>::command,
			't', 'e', 'x', 't', 'u', 'a', 'l', ' ', 'd', 'a', 't', 'a', '\t',
			'7', '\t',
			'3', '.', '1', '4', '\t',
			KEY_CODE::DOWN, KEY_CODE::LEFT, '\r', '\t',
			'1', '4', ':', '2', '3', ':', '5', '7', '\t',
			'1', '9', '7', '8', '-', '0', '5', '-', '2', '4', ' ', '2', '3', ':', '3', '0', ':', '0', '0', '\t',
			KEY_CODE::DOWN, KEY_CODE::DOWN, '\r', KEY<'w'>::command,
			KEY_CODE::END, KEY<'d'>::command,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "add record (with children)" )
	play(
		"add record and children", {
			'\r',
			KEY<'n'>::command,
			't', 'e', 'x', 't', 'u', 'a', 'l', ' ', 'd', 'a', 't', 'a', '\t',
			'7', '\t',
			'3', '.', '1', '4', '\t',
			KEY_CODE::DOWN, KEY_CODE::LEFT, '\r', '\t',
			'1', '4', ':', '2', '3', ':', '5', '7', '\t',
			'1', '9', '7', '8', '-', '0', '5', '-', '2', '4', ' ', '2', '3', ':', '3', '0', ':', '0', '0', '\t',
			KEY_CODE::DOWN, KEY_CODE::DOWN, '\r', '\t',
			KEY_CODE::INSERT, KEY_CODE::F2, 'v', 'a', 'l', 'u', 'e', '1', '\t', 'd', 'a', 't', 'a', '1', '\t', '3', '7', '\r',
			KEY_CODE::INSERT, KEY_CODE::F2, 'v', 'a', 'l', 'u', 'e', '2', '\t', 'd', 'a', 't', 'a', '2', '\t', '6', '1', '\r',
			KEY<'w'>::command,
			KEY_CODE::END, KEY<'d'>::command,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "edit record" )
	play(
		"edit record", {
			'\r',
			KEY<'n'>::command,
			't', 'e', 'x', 't', 'u', 'a', 'l', ' ', 'd', 'a', 't', 'a', '\t',
			'7', '\t',
			'3', '.', '1', '4', '\t',
			KEY_CODE::DOWN, KEY_CODE::LEFT, '\r', '\t',
			'1', '4', ':', '2', '3', ':', '5', '7', '\t',
			'1', '9', '7', '8', '-', '0', '5', '-', '2', '4', ' ', '2', '3', ':', '3', '0', ':', '0', '0', '\t',
			KEY_CODE::DOWN, KEY_CODE::DOWN, '\r', '\t',
			KEY_CODE::INSERT, KEY_CODE::F2, 'v', 'a', 'l', 'u', 'e', '1', '\t', 'd', 'a', 't', 'a', '1', '\t', '3', '7', '\r',
			KEY_CODE::INSERT, KEY_CODE::F2, 'v', 'a', 'l', 'u', 'e', '2', '\t', 'd', 'a', 't', 'a', '2', '\t', '6', '1', '\r',
			KEY<'w'>::command, KEY_CODE::END,
			KEY<'e'>::command,
			KEY_CODE::ESCAPE, 'I',
			KEY_CODE::ESCAPE, 'I',
			KEY_CODE::DOWN, KEY_CODE::DOWN,
			KEY_CODE::INSERT, KEY_CODE::F2, KEY_CODE::DELETE, 'v', 'a', 'l', 'u', 'e', '3', '\t', 'd', 'a', 't', 'a', '3', '\t', '2', '.', '7', '\r',
			KEY<'w'>::command, KEY_CODE::END,
			KEY<'e'>::command,
			KEY_CODE::ESCAPE, 'I',
			KEY_CODE::ESCAPE, 'I',
			KEY_CODE::F2, '\t', KEY_CODE::END, KEY_CODE::BACKSPACE, 'X', KEY_CODE::HOME, KEY_CODE::BACKSPACE, '\r', KEY_CODE::DOWN, KEY_CODE::DELETE,
			KEY<'w'>::command, KEY_CODE::END,
			KEY<'d'>::command,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "requery (edit)" )
	play(
		"requery (edit)", {
			'\r',
			KEY<'e'>::command,
			KEY<'r'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "requery (view)" )
	play(
		"requery (view)", {
			'\r',
			KEY<'r'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "save (view)" )
	play(
		"save (view)", {
			'\r',
			KEY<'w'>::command,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "edit (edit)" )
	play(
		"edit (edit)", {
			'\r',
			KEY<'e'>::command,
			KEY<'e'>::command,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "delete (edit)" )
	play(
		"delete (edit)", {
			'\r',
			KEY<'e'>::command,
			KEY<'d'>::command,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "cancel" )
	play(
		"cancel view record", {
			'\r',
			KEY_CODE::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"cancel add record", {
			'\r',
			KEY<'n'>::command,
			KEY_CODE::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"cancel edit record", {
			'\r',
			KEY<'e'>::command,
			KEY_CODE::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "confim box" )
	play(
		"confirm box", {
			'\r',
			KEY<'e'>::command, KEY_CODE::DELETE,
			KEY<'x'>::command, 0, KEY_CODE::LEFT, '\r'
		}
	);
TUT_TEARDOWN()

}

#endif /* #ifdef TARGET_CPU_BITS == 64 */
#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hdata.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

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
	play( "load data", { '\r', KEY<'n'>::command, 'a', KEY<'q'>::command, KEY_CODES::LEFT, '\r', KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add record (no children)" )
	play(
		"add record", {
			'\r',
			KEY<'n'>::command,
			't', 'e', 'x', 't', 'u', 'a', 'l', ' ', 'd', 'a', 't', 'a', '\t',
			'7', '\t',
			'3', '.', '1', '4', '\t',
			KEY_CODES::DOWN, KEY_CODES::LEFT, '\r', '\t',
			'1', '4', ':', '2', '3', ':', '5', '7', '\t',
			'1', '9', '7', '8', '-', '0', '5', '-', '2', '4', ' ', '2', '3', ':', '3', '0', ':', '0', '0', '\t',
			KEY_CODES::DOWN, KEY_CODES::DOWN, '\r', KEY<'w'>::command,
			KEY_CODES::END, KEY<'d'>::command,
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
			KEY_CODES::DOWN, KEY_CODES::LEFT, '\r', '\t',
			'1', '4', ':', '2', '3', ':', '5', '7', '\t',
			'1', '9', '7', '8', '-', '0', '5', '-', '2', '4', ' ', '2', '3', ':', '3', '0', ':', '0', '0', '\t',
			KEY_CODES::DOWN, KEY_CODES::DOWN, '\r', '\t',
			KEY_CODES::INSERT, KEY_CODES::F2, 'v', 'a', 'l', 'u', 'e', '1', '\t', 'd', 'a', 't', 'a', '1', '\t', '3', '7', '\r',
			KEY_CODES::INSERT, KEY_CODES::F2, 'v', 'a', 'l', 'u', 'e', '2', '\t', 'd', 'a', 't', 'a', '2', '\t', '6', '1', '\r',
			KEY<'w'>::command,
			KEY_CODES::END, KEY<'d'>::command,
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
			KEY_CODES::DOWN, KEY_CODES::LEFT, '\r', '\t',
			'1', '4', ':', '2', '3', ':', '5', '7', '\t',
			'1', '9', '7', '8', '-', '0', '5', '-', '2', '4', ' ', '2', '3', ':', '3', '0', ':', '0', '0', '\t',
			KEY_CODES::DOWN, KEY_CODES::DOWN, '\r', '\t',
			KEY_CODES::INSERT, KEY_CODES::F2, 'v', 'a', 'l', 'u', 'e', '1', '\t', 'd', 'a', 't', 'a', '1', '\t', '3', '7', '\r',
			KEY_CODES::INSERT, KEY_CODES::F2, 'v', 'a', 'l', 'u', 'e', '2', '\t', 'd', 'a', 't', 'a', '2', '\t', '6', '1', '\r',
			KEY<'w'>::command, KEY_CODES::END,
			KEY<'e'>::command,
			KEY_CODES::ESCAPE, 'I',
			KEY_CODES::ESCAPE, 'I',
			KEY_CODES::DOWN, KEY_CODES::DOWN,
			KEY_CODES::INSERT, KEY_CODES::F2, KEY_CODES::DELETE, 'v', 'a', 'l', 'u', 'e', '3', '\t', 'd', 'a', 't', 'a', '3', '\t', '2', '.', '7', '\r',
			KEY<'w'>::command, KEY_CODES::END,
			KEY<'e'>::command,
			KEY_CODES::ESCAPE, 'I',
			KEY_CODES::ESCAPE, 'I',
			KEY_CODES::F2, '\t', KEY_CODES::END, KEY_CODES::BACKSPACE, 'X', KEY_CODES::HOME, KEY_CODES::BACKSPACE, '\r', KEY_CODES::DOWN, KEY_CODES::DELETE,
			KEY<'w'>::command, KEY_CODES::END,
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
			KEY_CODES::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"cancel add record", {
			'\r',
			KEY<'n'>::command,
			KEY_CODES::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"cancel edit record", {
			'\r',
			KEY<'e'>::command,
			KEY_CODES::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "confim box" )
	play(
		"confirm box", {
			'\r',
			KEY<'e'>::command, KEY_CODES::DELETE,
			KEY<'x'>::command, 0, KEY_CODES::LEFT, '\r'
		}
	);
TUT_TEARDOWN()

}

#endif /* #ifdef TARGET_CPU_BITS == 64 */
#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


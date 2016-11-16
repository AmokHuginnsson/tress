/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hconsole.cxx - this file is integral part of `tress' project.

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

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "tut_yaal_hconsole_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;
using namespace tress;
using namespace tress::tut_helpers;
using namespace tress::fake_console_subsystem;

namespace tut {

struct tut_yaal_hconsole : public tut_yaal_hconsole_base {
	tui_t do_make_tui( void ) override {
		return ( make_resource<HTUIProcess>() );
	}
};

TUT_TEST_GROUP( tut_yaal_hconsole, "yaal::hconsole" );

TUT_UNIT_TEST( "Enter and leave" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	ENSURE_EQUALS( "bad width", cons.get_width(), CONSOLE_WIDTH );
	ENSURE_EQUALS( "bad height", cons.get_height(), CONSOLE_HEIGHT );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "cursor position" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	int row( -1 );
	int col( -1 );
	cons.getyx( row, col );
	ENSURE_EQUALS( "bad pos row", row, 0 );
	ENSURE_EQUALS( "bad pos col", col, 0 );
	static int const newRow( 10 );
	static int const newCol( 15 );
	cons.move( newRow, newCol );
	cons.getyx( row, col );
	ENSURE_EQUALS( "bad pos row", row, newRow );
	ENSURE_EQUALS( "bad pos col", col, newCol );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "set/get_attr" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	int attr( COLORS::ATTR_NORMAL );
	cons.set_attr( attr );
	ENSURE_EQUALS( "ATTR_NORMAL failed", cons.get_attr(), attr );
	attr = COLORS::BG_BLUE | COLORS::FG_CYAN;
	cons.set_attr( attr );
	ENSURE_EQUALS( "ATTR_NORMAL failed", cons.get_attr(), attr );
	attr = COLORS::BG_BLUE | COLORS::FG_YELLOW;
	cons.set_attr( attr );
	ENSURE_EQUALS( "ATTR_NORMAL failed", cons.get_attr(), attr );
	attr = COLORS::BG_BRIGHTGREEN | COLORS::FG_RED;
	cons.set_attr( attr );
	ENSURE_EQUALS( "ATTR_NORMAL failed", cons.get_attr(), attr );
	attr = COLORS::BG_BRIGHTGREEN | COLORS::FG_BRIGHTCYAN;
	cons.set_attr( attr );
	ENSURE_EQUALS( "ATTR_NORMAL failed", cons.get_attr(), attr );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "addch" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.set_attr( COLORS::FG_GREEN );
	cons.move( 10, 15 );
	cons.addch( 'a' );
	ENSURE_EQUALS( "addch failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{gk}a{kk}[ ,1184]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "printf" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.set_attr( COLORS::FG_BLUE );
	cons.move( 10, 15 );
	cons.printf( "Ala ma kota %d", 13 );
	ENSURE_EQUALS( "printf failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{bk}Ala ma kota 13{kk}[ ,1171]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "mvprintf" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.set_attr( COLORS::FG_RED );
	cons.mvprintf( 10, 15, "Ala ma kota %d", 13 );
	ENSURE_EQUALS( "mvprintf failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{rk}Ala ma kota 13{kk}[ ,1171]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "cmvprintf" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.cmvprintf( 10, 15, COLORS::FG_MAGENTA, "Ala ma kota %d", 13 );
	ENSURE_EQUALS( "cmvprintf failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{mk}Ala ma kota 13{kk}[ ,1171]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "addstr" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.clear_terminal();
	cons.set_attr( COLORS::FG_CYAN );
	cons.move( 10, 15 );
	cons.addstr( "Ala ma kota" );
	ENSURE_EQUALS( "addstr failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{ck}Ala ma kota{kk}[ ,1174]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "ungetch/getch" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	int keys[] = {
		KEY_CODES::ESCAPE, KEY_CODES::PAGE_UP, KEY_CODES::PAGE_DOWN, KEY_CODES::DOWN, KEY_CODES::UP,
		KEY_CODES::LEFT, KEY_CODES::RIGHT, KEY_CODES::HOME, KEY_CODES::END, KEY_CODES::DELETE, KEY_CODES::INSERT, KEY_CODES::BACKSPACE,
		KEY_CODES::F1, KEY_CODES::F2, KEY_CODES::F3, KEY_CODES::F4, KEY_CODES::F5, KEY_CODES::F6,
		KEY_CODES::F7, KEY_CODES::F8, KEY_CODES::F9, KEY_CODES::F10, KEY_CODES::F11, KEY_CODES::F12,
		KEY_CODES::F13, KEY_CODES::F14, KEY_CODES::F15, KEY_CODES::F16, KEY_CODES::F17, KEY_CODES::F18,
		KEY_CODES::F19, KEY_CODES::F20, KEY_CODES::F21, KEY_CODES::F22, KEY_CODES::F23, KEY_CODES::F24,
		KEY<'c'>::ctrl, KEY<'x'>::command
	};
	for ( int key : keys ) {
		cons.ungetch( key );
		ENSURE_EQUALS( "ungetch/getch failed", cons.get_key(), key );
	}
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "fg_to_bg" )
	ENSURE_EQUALS( "red", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_RED ) ), static_cast<int>( COLORS::BG_RED ) );
	ENSURE_EQUALS( "green", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_GREEN ) ), static_cast<int>( COLORS::BG_GREEN ) );
	ENSURE_EQUALS( "blue", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BLUE ) ), static_cast<int>( COLORS::BG_BLUE ) );
	ENSURE_EQUALS( "brown", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BROWN ) ), static_cast<int>( COLORS::BG_BROWN ) );
	ENSURE_EQUALS( "black", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BLACK ) ), static_cast<int>( COLORS::BG_BLACK ) );
	ENSURE_EQUALS( "cyan", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_CYAN ) ), static_cast<int>( COLORS::BG_CYAN ) );
	ENSURE_EQUALS( "magenta", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_MAGENTA ) ), static_cast<int>( COLORS::BG_MAGENTA ) );
	ENSURE_EQUALS( "gray", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_GRAY ) ), static_cast<int>( COLORS::BG_GRAY ) );
	ENSURE_EQUALS( "brightred", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BRIGHTRED ) ), static_cast<int>( COLORS::BG_BRIGHTRED ) );
	ENSURE_EQUALS( "brightgreen", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BRIGHTGREEN ) ), static_cast<int>( COLORS::BG_BRIGHTGREEN ) );
	ENSURE_EQUALS( "brightblue", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BRIGHTBLUE ) ), static_cast<int>( COLORS::BG_BRIGHTBLUE ) );
	ENSURE_EQUALS( "brightcyan", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BRIGHTCYAN ) ), static_cast<int>( COLORS::BG_BRIGHTCYAN ) );
	ENSURE_EQUALS( "brightmagenta", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_BRIGHTMAGENTA ) ), static_cast<int>( COLORS::BG_BRIGHTMAGENTA ) );
	ENSURE_EQUALS( "yellow", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_YELLOW ) ), static_cast<int>( COLORS::BG_YELLOW ) );
	ENSURE_EQUALS( "white", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_WHITE ) ), static_cast<int>( COLORS::BG_WHITE ) );
	ENSURE_EQUALS( "lightgray", static_cast<int>( COLORS::fg_to_bg( COLORS::FG_LIGHTGRAY ) ), static_cast<int>( COLORS::BG_LIGHTGRAY ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "notify_keyboard" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.ungetch( KEY<'x'>::command );
	cons.notify_keyboard();
	HTUIProcess tp;
	tp.init_xrc( "tress", "data/tress.xrc" );
	tp.run();
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "tui quit" )
	play( "quit by menu", { KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, '\r' } );
	play( "quit by command line", { ':', 'q', 'u', 'i', 't', '\r' } );
	play( "quit by keyboard shortcut", { KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "tui window" )
	play( "all widgets (no database)", { KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', KEY<'q'>::command, KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget search" )
	play(
		"search forward", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', '/', '\r', '?', '\\', '\r', '/', 'x', '/', 'x', '\r', '/', '\\', 'u', '\r',
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search backward (all flags + programmable)", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', '/', 'u', '/', 'f', 'c', 'C', 'i', '\r',
			KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl,
			KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search forward", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', '/', '[', 'v', 'h', ']', '/', 'e', '\r',
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget sort" )
	play( "listwidget sort", { KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', 'n', 't', 'i', 'r', 'd', 'N', 'T', 'I', 'R', 'D', KEY<'q'>::command, KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget movement" )
	play(
		"listwidget movement", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r',
			KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, ' ', KEY_CODES::DOWN,
			KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN,
			KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN,
			KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP,
			KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP,
			KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP,
			KEY_CODES::PAGE_DOWN, KEY_CODES::PAGE_DOWN, KEY_CODES::PAGE_DOWN, KEY_CODES::PAGE_DOWN,
			KEY_CODES::PAGE_UP, KEY_CODES::PAGE_UP, KEY_CODES::PAGE_UP, KEY_CODES::PAGE_UP,
			KEY_CODES::DOWN, KEY_CODES::PAGE_DOWN, KEY_CODES::UP, KEY_CODES::PAGE_DOWN,
			KEY_CODES::UP, KEY_CODES::PAGE_UP, KEY_CODES::END, KEY_CODES::HOME,
			KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN,
			KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP,
			KEY_CODES::PAGE_UP,
			KEY_CODES::END,
			KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP,
			KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN, KEY_CODES::DOWN,
			KEY_CODES::PAGE_DOWN,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "edit widget edit and motion" )
	play(
		"edit widget motion", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', KEY_CODES::ESCAPE, 'x',
			KEY_CODES::HOME, KEY_CODES::ESCAPE, 'f', KEY_CODES::ESCAPE, 'f', KEY_CODES::ESCAPE, 'f', KEY_CODES::RIGHT, KEY_CODES::ESCAPE, 'd',
			'c', 'r', 'e', 'a', 't', 'o', 'r',
			KEY_CODES::END, KEY_CODES::ESCAPE, 'b', KEY_CODES::ESCAPE, 'b', KEY_CODES::ESCAPE, 'b', KEY_CODES::ESCAPE, 'b', KEY_CODES::ESCAPE, 'b', KEY_CODES::ESCAPE, 'b', KEY_CODES::ESCAPE, 'b', KEY_CODES::LEFT,
			KEY<'w'>::ctrl, KEY_CODES::BACKSPACE, 's', 'e', 'l', 'f', ',', '\t',
			KEY_CODES::ESCAPE, 'T', KEY_CODES::DOWN, KEY_CODES::ESCAPE, 'x',
			KEY_CODES::UP,
			KEY_CODES::END, KEY_CODES::LEFT, KEY_CODES::LEFT, KEY_CODES::DELETE, KEY_CODES::DELETE, KEY_CODES::HOME, KEY_CODES::DELETE, KEY_CODES::DELETE, KEY<'u'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "logpad motion" )
	play(
		"logpad motion", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', KEY_CODES::ESCAPE, 'L',
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::RIGHT, KEY_CODES::UP, KEY_CODES::LEFT, KEY_CODES::LEFT,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "tree motion" )
	play(
		"tree motion", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::END, KEY_CODES::UP, KEY_CODES::UP, KEY_CODES::UP,
			KEY_CODES::END, KEY_CODES::UP, KEY_CODES::LEFT, KEY_CODES::LEFT, KEY_CODES::HOME,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "date motion" )
	play(
		"date motion", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r', KEY_CODES::ESCAPE, 'D',
			'\r', KEY_CODES::PAGE_UP, KEY_CODES::UP, KEY_CODES::LEFT, KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::PAGE_DOWN, '\r',
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "mouse" )
	play(
		"mouse", {
			KEY<'l'>::ctrl,
			KEY_CODES::MOUSE, 2, 4,
			KEY_CODES::MOUSE, 6, 5,
			KEY_CODES::MOUSE, 6, 5,
			KEY_CODES::MOUSE, 2, 5,
			KEY_CODES::MOUSE, 15, 2,
			KEY_CODES::MOUSE, 15, 2,
			KEY_CODES::MOUSE, 30, 10,
			KEY_CODES::MOUSE, 30, 10,
			KEY_CODES::MOUSE, 70, 13,
			KEY_CODES::MOUSE, 70, 13,
			KEY_CODES::MOUSE, 62, 18,
			KEY_CODES::MOUSE, 62, 18,
			KEY_CODES::MOUSE, 24, 10,
			KEY_CODES::MOUSE, 24, 10,
			KEY_CODES::MOUSE, 2, 11,
			KEY_CODES::MOUSE, 2, 11,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "window list" )
	play(
		"window list", {
			KEY_CODES::DOWN, KEY_CODES::RIGHT, KEY_CODES::DOWN, '\r',
			KEY_CODES::ESCAPE, '\t', '\t', KEY_CODES::DOWN, '\r',
			KEY_CODES::ESCAPE, '0',
			KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

}

#endif /* #ifdef TARGET_CPU_BITS == 64 */
#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <yaal/config.hxx>
#include "config.hxx"

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
#ifndef __HOST_OS_TYPE_DARWIN__
#if TARGET_CPU_BITS == 64

#include <TUT/tut.hpp>
#include <yaal/hconsole/hwindow.hxx>
#include <yaal/tools/keycode.hxx>

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
	ENSURE_THROW( "leave_curses on non initialized succeeded", cons.leave_curses(), HConsoleException );
	ENSURE_THROW( "set_attr on non initialized succeeded", cons.set_attr( COLOR::ATTR_DEFAULT ), HConsoleException );
	ENSURE_THROW( "set_background on non initialized succeeded", cons.set_background( COLOR::BG_BLACK ), HConsoleException );
	ENSURE_THROW( "addch on non initialized succeeded", cons.addch( 0 ), HConsoleException );
	ENSURE_THROW( "addstr on non initialized succeeded", cons.addstr( "" ), HConsoleException );
	ENSURE_THROW( "get_key on non initialized succeeded", cons.get_key(), HConsoleException );
	ENSURE_THROW( "kbhit on non initialized succeeded", cons.kbhit(), HConsoleException );
	ENSURE_THROW( "get_attr on non initialized succeeded", cons.get_attr(), HConsoleException );
	ENSURE_THROW( "clear on non initialized succeeded", cons.clear(), HConsoleException );
	ENSURE_THROW( "clear_terminal on non initialized succeeded", cons.clear_terminal(), HConsoleException );
	ENSURE_THROW( "printf on non initialized succeeded", cons.printf( "" ), HConsoleException );
	ENSURE_THROW( "mvprintf on non initialized succeeded", cons.mvprintf( 0, 0, "" ), HConsoleException );
	ENSURE_THROW( "cmvprintf on non initialized succeeded", cons.cmvprintf( 0, 0, COLOR::ATTR_DEFAULT, "" ), HConsoleException );
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
	COLOR::color_t attr( COLOR::ATTR_DEFAULT );
	cons.set_attr( attr );
	ENSURE_EQUALS( "ATTR_DEFAULT failed", static_cast<int>( cons.get_attr() ), static_cast<int>( attr ) );
	attr = COLOR::combine( COLOR::BG_BLUE, COLOR::FG_CYAN );
	cons.set_attr( attr );
	ENSURE_EQUALS( "BG_BLUE | FG_CYAN failed", static_cast<int>( cons.get_attr() ), static_cast<int>( attr ) );
	attr = COLOR::combine( COLOR::BG_BLUE, COLOR::FG_YELLOW );
	cons.set_attr( attr );
	ENSURE_EQUALS( "BG_BLUE | FG_YELLOW failed", static_cast<int>( cons.get_attr() ), static_cast<int>( attr ) );
	attr = COLOR::combine( COLOR::BG_BRIGHTGREEN, COLOR::FG_RED );
	cons.set_attr( attr );
	ENSURE_EQUALS( "BG_BRIGHTGREEN | FG_RED failed", static_cast<int>( cons.get_attr() ), static_cast<int>( attr ) );
	attr = COLOR::combine( COLOR::BG_BRIGHTGREEN, COLOR::FG_BRIGHTCYAN );
	cons.set_attr( attr );
	ENSURE_EQUALS( "BG_BRIGHTGREEN | FG_BRIGHTCYAN failed", static_cast<int>( cons.get_attr() ), static_cast<int>( attr ) );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "addch" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.set_attr( COLOR::FG_GREEN );
	cons.move( 10, 15 );
	cons.addch( 'a' );
	ENSURE_EQUALS( "addch failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{gk}a{kk}[ ,1184]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "printf" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.set_attr( COLOR::FG_BLUE );
	cons.move( 10, 15 );
	cons.printf( "Ala ma kota %d", 13 );
	ENSURE_EQUALS( "printf failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{bk}Ala ma kota 13{kk}[ ,1171]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "mvprintf" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.set_attr( COLOR::FG_RED );
	cons.mvprintf( 10, 15, "Ala ma kota %d", 13 );
	ENSURE_EQUALS( "mvprintf failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{rk}Ala ma kota 13{kk}[ ,1171]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "cmvprintf" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.cmvprintf( 10, 15, COLOR::FG_MAGENTA, "Ala ma kota %d", 13 );
	ENSURE_EQUALS( "cmvprintf failed", tress::fake_console_subsystem::packed_dump(), "{kk}[ ,815]{mk}Ala ma kota 13{kk}[ ,1171]" );
	cons.leave_curses();
TUT_TEARDOWN()

TUT_UNIT_TEST( "addstr" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	cons.clear_terminal();
	cons.set_attr( COLOR::FG_CYAN );
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
		KEY_CODE::ESCAPE, KEY_CODE::PAGE_UP, KEY_CODE::PAGE_DOWN, KEY_CODE::DOWN, KEY_CODE::UP,
		KEY_CODE::LEFT, KEY_CODE::RIGHT, KEY_CODE::HOME, KEY_CODE::END, KEY_CODE::DELETE, KEY_CODE::INSERT, KEY_CODE::BACKSPACE,
		KEY_CODE::F1, KEY_CODE::F2, KEY_CODE::F3, KEY_CODE::F4, KEY_CODE::F5, KEY_CODE::F6,
		KEY_CODE::F7, KEY_CODE::F8, KEY_CODE::F9, KEY_CODE::F10, KEY_CODE::F11, KEY_CODE::F12,
		KEY_CODE::F13, KEY_CODE::F14, KEY_CODE::F15, KEY_CODE::F16, KEY_CODE::F17, KEY_CODE::F18,
		KEY_CODE::F19, KEY_CODE::F20, KEY_CODE::F21, KEY_CODE::F22, KEY_CODE::F23, KEY_CODE::F24,
		KEY<'c'>::ctrl, KEY<'x'>::command
	};
	for ( int key : keys ) {
		cons.ungetch( key );
		ENSURE_EQUALS( "ungetch/getch failed", cons.get_key(), key );
	}
	cons.leave_curses();
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
	play( "quit by menu", { KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, '\r' } );
	play( "quit by command line", { ':', 'q', 'u', 'i', 't', '\r' } );
	play( "quit by keyboard shortcut", { KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "tui window" )
	play( "all widgets (no database)", { KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', KEY<'q'>::command, KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget search" )
	play(
		"search forward", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '/', '\r', '?', '\\', '\r', '/', 'x', '/', 'x', '\r', '/', '\\', 'u', '\r',
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search backward (all flags + programmable)", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '/', 'u', '/', 'f', 'c', 'C', 'i', '\r',
			KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl,
			KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl, KEY<'p'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search forward", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '/', '[', 'v', 'h', ']', '/', 'e', '\r',
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl, KEY<'n'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search cancel", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '/', KEY_CODE::BACKSPACE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search bad forw", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '/', 'x', 'x', 'x', '\r',  KEY<'n'>::ctrl, KEY<'p'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"search bad back", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '?', 'x', 'x', 'x', '\r',  KEY<'n'>::ctrl, KEY<'p'>::ctrl,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget sort" )
	play( "listwidget sort", { KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', 'n', 't', 'i', 'r', 'd', 'N', 'T', 'I', 'R', 'D', KEY<'q'>::command, KEY<'x'>::command } );
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget movement" )
	play(
		"listwidget movement", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r',
			KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, ' ', KEY_CODE::DOWN,
			KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN,
			KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN,
			KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP,
			KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP,
			KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP,
			KEY_CODE::PAGE_DOWN, KEY_CODE::PAGE_DOWN, KEY_CODE::PAGE_DOWN, KEY_CODE::PAGE_DOWN,
			KEY_CODE::PAGE_UP, KEY_CODE::PAGE_UP, KEY_CODE::PAGE_UP, KEY_CODE::PAGE_UP,
			KEY_CODE::DOWN, KEY_CODE::PAGE_DOWN, KEY_CODE::UP, KEY_CODE::PAGE_DOWN,
			KEY_CODE::UP, KEY_CODE::PAGE_UP, KEY_CODE::END, KEY_CODE::HOME,
			KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN,
			KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP,
			KEY_CODE::PAGE_UP,
			KEY_CODE::END,
			KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP,
			KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN, KEY_CODE::DOWN,
			KEY_CODE::PAGE_DOWN,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "edit widget edit and motion" )
	play(
		"edit widget motion", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', KEY_CODE::ESCAPE, 'x',
			KEY_CODE::HOME, KEY_CODE::ESCAPE, 'f', KEY_CODE::ESCAPE, 'f', KEY_CODE::ESCAPE, 'f', KEY_CODE::RIGHT,
			KEY_CODE::INSERT, KEY_CODE::INSERT,
			KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT,
			KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT,
			KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT,
			KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT,
			KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT,
			KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::RIGHT,
			KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::HOME, KEY_CODE::ESCAPE, 'f', KEY_CODE::ESCAPE, 'f', KEY_CODE::ESCAPE, 'f', KEY_CODE::RIGHT, KEY_CODE::ESCAPE, 'd',
			'c', 'r', 'e', 'a', 't', 'o', 'r',
			KEY_CODE::END, KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'b', KEY_CODE::LEFT,
			KEY<'w'>::ctrl, KEY_CODE::BACKSPACE, 's', 'e', 'l', 'f', ',', '\t',
			KEY_CODE::ESCAPE, 'T', KEY_CODE::DOWN, KEY_CODE::ESCAPE, 'x',
			KEY_CODE::UP,
			KEY_CODE::END, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::DELETE, KEY_CODE::DELETE, KEY_CODE::HOME, KEY_CODE::DELETE, KEY_CODE::DELETE, KEY<'u'>::ctrl, KEY<'u'>::ctrl,
			KEY_CODE::PAGE_UP, KEY_CODE::PAGE_DOWN, KEY_CODE::UP, KEY_CODE::DOWN,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"find_eow", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', '\t',
			KEY_CODE::END, KEY_CODE::ESCAPE, 'b', KEY_CODE::ESCAPE, 'f',
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "logpad motion" )
	play(
		"logpad motion", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', KEY_CODE::ESCAPE, 'L',
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::RIGHT, KEY_CODE::UP, KEY_CODE::LEFT, KEY_CODE::LEFT,
			KEY_CODE::END, KEY_CODE::HOME,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "tree motion" )
	play(
		"tree motion", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::END, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP,
			KEY_CODE::END, KEY_CODE::UP, KEY_CODE::LEFT, KEY_CODE::LEFT, KEY_CODE::HOME,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "date motion" )
	play(
		"date motion", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', KEY_CODE::ESCAPE, 'D',
			'\r', KEY_CODE::PAGE_UP, KEY_CODE::UP, KEY_CODE::LEFT, KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::PAGE_DOWN, '\r',
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "time motion" )
	play(
		"time motion", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', KEY_CODE::ESCAPE, 'i',
			KEY_CODE::UP, KEY_CODE::RIGHT, KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::UP, KEY_CODE::RIGHT, KEY_CODE::LEFT,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "combobox motion" )
	play(
		"combobox motion", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r', KEY_CODE::ESCAPE, 'N',
			KEY_CODE::UP, KEY_CODE::ESCAPE, fake_console_subsystem::COMMIT_ESCAPE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "listwidget edit" )
	play(
		"listwidget edit numerical cells", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r',
			KEY_CODE::ESCAPE, 'E',
			KEY_CODE::INSERT, KEY_CODE::F2, '\t', 'x', '\t', KEY_CODE::BACKSPACE, '0', '\t', 'x', '\t', KEY_CODE::BACKSPACE, '0', '\r',
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
	play(
		"listwidget edit remove row", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r',
			KEY_CODE::ESCAPE, 'E',
			KEY_CODE::INSERT, '0', '\r', KEY_CODE::INSERT, '1', '\r', KEY_CODE::INSERT, '2', '\r',
			KEY_CODE::UP,
			KEY_CODE::PAGE_DOWN,
			KEY_CODE::PAGE_DOWN,
			KEY_CODE::INSERT, '3', '\r', KEY_CODE::INSERT, '4', '\r', KEY_CODE::INSERT, '5', '\r',
			KEY_CODE::INSERT, '6', '\r', KEY_CODE::INSERT, '7', '\r',
			KEY_CODE::F2, KEY_CODE::ESCAPE, COMMIT_ESCAPE,
			KEY_CODE::DELETE, KEY_CODE::UP, KEY_CODE::DELETE, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::UP, KEY_CODE::DELETE, KEY_CODE::HOME, KEY_CODE::DELETE,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "mouse" )
	play(
		"mouse", {
			KEY<'l'>::ctrl,
			KEY_CODE::MOUSE, 2, 4, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 6, 5, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 6, 5, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 2, 5, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 15, 2, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 15, 2, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 30, 10, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 30, 10, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 70, 13, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 70, 13, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 62, 18, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 62, 18, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 24, 10, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 24, 10, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 2, 11, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 2, 11, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 50, 13, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 50, 13, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 48, 17, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 48, 17, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 5, 5, MOUSE_BUTTON1,
			KEY_CODE::MOUSE, 5, 5, MOUSE_WHEEL_DOWN,
			KEY_CODE::MOUSE, 5, 5, MOUSE_WHEEL_UP,
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "window list" )
	play(
		"window list", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, '\r',
			KEY_CODE::ESCAPE, '\t', '\t', KEY_CODE::DOWN, '\r',
			KEY_CODE::ESCAPE, '0',
			KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "XML Window" )
	play(
		"XML Window", {
			KEY_CODE::DOWN, KEY_CODE::RIGHT, KEY_CODE::DOWN, KEY_CODE::DOWN, '\r',
			KEY<'q'>::command, KEY<'x'>::command
		}
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Bad HEditWidget" )
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	HWindow w( "Bad HEditWidget" );
	ENSURE_THROW(
		"edit-widget right aligned and multiline at the same time",
		create_widget<HEditWidget>(
			&w, -13, 1, 1, 18, "&Int",
			HEditWidgetAttributes().rightaligned( true ).multiline( true )
		),
		HEditWidgetException
	);
	ENSURE_THROW(
		"edit-widget buffer size is ridiculously low",
		create_widget<HEditWidget>(
			&w, -13, 1, 1, 18, "&Int",
			HEditWidgetAttributes().max_string_size( 0 )
		),
		HEditWidgetException
	);
	ENSURE_THROW(
		"edit-widget initial value too big",
		create_widget<HEditWidget>(
			&w, -13, 1, 1, 18, "&Int",
			HEditWidgetAttributes().max_string_size( 16 ).text( "a string way too long" )
		),
		HEditWidgetException
	);
	ENSURE_THROW(
		"edit-widget invalid mask",
		create_widget<HEditWidget>(
			&w, -13, 1, 1, 18, "&Int",
			HEditWidgetAttributes().mask( "[a-z" )
		),
		HEditWidgetException
	);
	ENSURE_THROW(
		"edit-widget value does not match mask",
		create_widget<HEditWidget>(
			&w, -13, 1, 1, 18, "&Int",
			HEditWidgetAttributes().mask( "^[a-z]*$" ).text( "abc4" )
		),
		HEditWidgetException
	);
	HEditWidget* e(
		create_widget<HEditWidget>(
			&w, -13, 1, 1, 18, "&Int",
			HEditWidgetAttributes().text( "abc4" )
		)
	);
	ENSURE_EQUALS( "set/get text failed", e->get_text(), "abc4" );
	cons.leave_curses();
TUT_TEARDOWN()

}

#endif /* #ifdef TARGET_CPU_BITS == 64 */
#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


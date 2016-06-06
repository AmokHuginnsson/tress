/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hconsole_hconsole.cxx - this file is integral part of `tress' project.

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

#include "config.hxx"

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
#ifndef __HOST_OS_TYPE_DARWIN__

#include <TUT/tut.hpp>

#include <yaal/hconsole/hconsole.hxx>
#include <yaal/hconsole/htuiprocess.hxx>
#include <yaal/tools/util.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "fake_console_subsystem.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace yaal::hconsole;
using namespace tress::tut_helpers;

namespace tut {


struct tut_yaal_hconsole_hconsole : public simple_mock<tut_yaal_hconsole_hconsole> {
	static int const CONSOLE_WIDTH;
	static int const CONSOLE_HEIGHT;
	tut_yaal_hconsole_hconsole( void )
		: _fakeConoleGuard() {
	}
	virtual ~tut_yaal_hconsole_hconsole( void ) {
		if ( HConsole::get_instance().is_enabled() ) {
			HConsole::get_instance().leave_curses();
		}
	}
	void play( int_array_t );
	void push_keys( int );
	bool quit( HTUIProcess*, hconsole::HEvent const& );
	tress::fake_console_subsystem::HFakeConsoleGuard _fakeConoleGuard;
};
int const tut_yaal_hconsole_hconsole::CONSOLE_WIDTH = 80;
int const tut_yaal_hconsole_hconsole::CONSOLE_HEIGHT = 25;

void tut_yaal_hconsole_hconsole::play( int_array_t input_ ) {
	HThread t;
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	reverse( input_.begin(), input_.end() );
	for ( int key : input_ ) {
		cons.ungetch( key );
	}
	HTUIProcess tp;
	tp.init_xrc( "tress", "data/tress.xrc" );
	tp.register_command_handler( "run_quit", call( &tut_yaal_hconsole_hconsole::quit, this, &tp, _1 ) );
	tress::fake_console_subsystem::_fakeConsole_.init_input();
	HScopeExitCall sec( call( &tress::fake_console_subsystem::HFakeConsole::destroy_input, &tress::fake_console_subsystem::_fakeConsole_ ) );
	t.spawn( call( &tut_yaal_hconsole_hconsole::push_keys, this, static_cast<int>( input_.get_size() ) ) );
	tp.run();
	cons.leave_curses();
}

void tut_yaal_hconsole_hconsole::push_keys( int keyCount_ ) {
	HConsole& cons( HConsole::get_instance() );
	tress::fake_console_subsystem::_fakeConsole_.init_dump();
	HScopeExitCall sec( call( &tress::fake_console_subsystem::HFakeConsole::destroy_dump, &tress::fake_console_subsystem::_fakeConsole_ ) );
	for ( int i( 0 ); i < keyCount_; ++ i ) {
		cons.notify_keyboard();
		tress::fake_console_subsystem::_fakeConsole_.wait_io();
//		clog << tress::fake_console_subsystem::term_dump() << endl;
		clog << tress::fake_console_subsystem::packed_dump() << endl;
		tress::fake_console_subsystem::_fakeConsole_.wake_io();
	}
}

bool tut_yaal_hconsole_hconsole::quit( yaal::hconsole::HTUIProcess* tp, yaal::hconsole::HEvent const& ) {
	tp->quit();
	return ( true );
}

TUT_TEST_GROUP( tut_yaal_hconsole_hconsole, "yaal::hconsole::HConsole" );

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
	cons.clrscr();
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
	int key = KEY<'x'>::command;
	cons.ungetch( key );
	ENSURE_EQUALS( "ungetch/getch failed", cons.get_key(), key );
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
	play( { KEY_CODES::RIGHT, KEY_CODES::DOWN, KEY_CODES::DOWN, '\r' } );
	play( { ':', 'q', 'u', 'i', 't', '\r' } );
TUT_TEARDOWN()

}

#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


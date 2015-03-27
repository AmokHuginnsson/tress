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

#include <TUT/tut.hpp>

#include <yaal/hconsole/hconsole.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include "fake_console_subsystem.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
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
	HFakeConsoleGuard _fakeConoleGuard;
};
int const tut_yaal_hconsole_hconsole::CONSOLE_WIDTH = 80;
int const tut_yaal_hconsole_hconsole::CONSOLE_HEIGHT = 25;

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

}

#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


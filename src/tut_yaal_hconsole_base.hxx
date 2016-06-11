/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hconsole_base.hxx - this file is integral part of `tress' project.

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

#ifndef TUT_YAAL_HCONSOLE_BASE_HXX_INCLUDED
#define TUT_YAAL_HCONSOLE_BASE_HXX_INCLUDED 1

#include <yaal/hconsole/hconsole.hxx>
#include <yaal/hconsole/htuiprocess.hxx>

#include "config.hxx"
#include "tut_helpers.hxx"
#include "fake_console_subsystem.hxx"

namespace tress {

struct tut_yaal_hconsole_base : public tut_helpers::simple_mock<tut_yaal_hconsole_base> {
	typedef yaal::hcore::HResource<yaal::hconsole::HTUIProcess> tui_t;
	static int const CONSOLE_WIDTH;
	static int const CONSOLE_HEIGHT;
	tut_yaal_hconsole_base( void )
		: _fakeConoleGuard() {
	}
	virtual ~tut_yaal_hconsole_base( void );
	tui_t make_tui( void );
	void play( char const*, int_array_t );
	void push_keys( int );
	bool quit( yaal::hconsole::HTUIProcess*, yaal::hconsole::HEvent const& );
	bool test( yaal::hconsole::HTUIProcess*, yaal::hconsole::HEvent const& );
	tress::fake_console_subsystem::HFakeConsoleGuard _fakeConoleGuard;
	virtual tui_t do_make_tui( void ) = 0;
};

}

#endif /* not TUT_YAAL_HCONSOLE_BASE_HXX_INCLUDED */


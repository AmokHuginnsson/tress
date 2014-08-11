/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  fake_console_subsystem.cxx - this file is integral part of `tress' project.

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

#ifdef HAVE_DECL_RTLD_NEXT

#include <cstdlib>
#include <dlfcn.h>

#include <yaal/hcore/base.hxx>

#include "fake_console_subsystem.hxx"

class HFakeConsole {
private:
	bool _active;
public:
	HFakeConsole( void )
		: _active( false ) {
	}
	void activate( void ) {
		_active = true;
	}
	void deactivate( void ) {
		_active = false;
	}
	bool is_active() const {
		return ( _active );
	}
} _fakeConsole_;

HFakeConsoleGuard::HFakeConsoleGuard( void ) {
	_fakeConsole_.activate();
}

HFakeConsoleGuard::~HFakeConsoleGuard( void ) {
	_fakeConsole_.deactivate();
}

namespace fake_console_subsystem {

struct WINDOW {
	int short _y;
	int short _x;
	int short _my;
	int short _mx;
	char _buf[2048];
	WINDOW( void )
		: _y( 0 ), _x( 0 ),
		_my( 24 ), _mx( 79 ),
		_buf() {
	}
} stdscr;

}

extern "C" {

int tcgetattr( int, struct termios* );
int tcgetattr( int a0, struct termios* a1 ) {
	typedef int (*tcgetattr_t)( int, struct termios* );
	static tcgetattr_t orig_tcgetattr = yaal::bit_cast<tcgetattr_t>( dlsym( RTLD_NEXT, "tcgetattr" ) );
	int ret( orig_tcgetattr( a0, a1 ) );
	return ( ! _fakeConsole_.is_active() ? ret : 0 );
}

int tcsetattr( int, int, const struct termios* );
int tcsetattr( int a0, int a1, const struct termios* a2 ) {
	typedef int (*tcsetattr_t)( int, int, const struct termios* );
	static tcsetattr_t orig_tcsetattr = yaal::bit_cast<tcsetattr_t>( dlsym( RTLD_NEXT, "tcsetattr" ) );
	int ret( orig_tcsetattr( a0, a1, a2 ) );
	return ( ! _fakeConsole_.is_active() ? ret : 0 );
}

#ifndef __HOST_OS_TYPE_SOLARIS__
int isatty( int );
#endif /* #ifndef __HOST_OS_TYPE_SOLARIS__ */
int isatty( int fd_ ) {
	typedef int (*isatty_t)( int );
	static isatty_t orig_isatty = yaal::bit_cast<isatty_t>( dlsym( RTLD_NEXT, "isatty" ) );
	int ret( orig_isatty( fd_ ) );
	return ( ! _fakeConsole_.is_active() ? ret : 1 );
}

using namespace fake_console_subsystem;

WINDOW* initscr( void );
WINDOW* initscr( void ) {
	return ( &stdscr );
}

int cbreak( void );
int cbreak( void ) {
	return ( 0 );
}

int start_color( void );
int start_color( void ) {
	return ( 0 );
}

int nonl( void );
int nonl( void ) {
	return ( 0 );
}

int nl( void );
int nl( void ) {
	return ( 0 );
}

int keypad( WINDOW*, bool );
int keypad( WINDOW*, bool ) {
	return ( 0 );
}

int intrflush( WINDOW*, bool );
int intrflush( WINDOW*, bool ) {
	return ( 0 );
}

int scrollok( WINDOW*, bool );
int scrollok( WINDOW*, bool ) {
	return ( 0 );
}

int leaveok( WINDOW*, bool );
int leaveok( WINDOW*, bool ) {
	return ( 0 );
}

int use_default_colors( void );
int use_default_colors( void ) {
	return ( 0 );
}

int assume_default_colors( int, int );
int assume_default_colors( int, int ) {
	return ( 0 );
}

int long unsigned mousemask( int long unsigned, int long unsigned* );
int long unsigned mousemask( int long unsigned newmask, int long unsigned* ) {
	return ( newmask );
}

bool has_mouse( void );
bool has_mouse( void ) {
	return ( true );
}

int wrefresh( WINDOW* );
int wrefresh( WINDOW* ) {
	return ( 0 );
}

int wprintw( WINDOW*, char const*, ... );
int wprintw( WINDOW*, char const*, ... ) {
	return ( 0 );
}

int nocbreak( void );
int nocbreak( void ) {
	return ( 0 );
}

int endwin( void );
int endwin( void ) {
	return ( 0 );
}

int wbkgd( WINDOW*, int long unsigned );
int wbkgd( WINDOW*, int long unsigned ) {
	return ( 0 );
}

}

#endif /* #ifdef HAVE_DECL_RTLD_NEXT */


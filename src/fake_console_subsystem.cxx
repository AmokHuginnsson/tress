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

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )

#include <cstring>
#include <cstdlib>
#include <dlfcn.h>

#include <yaal/hcore/base.hxx>
#include <yaal/tools/hmonitor.hxx>
#include <yaal/tools/ansi.hxx>
#include <yaal/tools/hstringstream.hxx>

#include "fake_console_subsystem.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;

namespace tress {

namespace fake_console_subsystem {

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

HFakeConsoleGuard::HFakeConsoleGuard( void )
	: _exclusiveAccess( yaal::tools::HMonitor::get_instance().acquire( "terminal" ) ) {
	_fakeConsole_.activate();
}

HFakeConsoleGuard::~HFakeConsoleGuard( void ) {
	_fakeConsole_.deactivate();
}

struct WINDOW {
	static int const ROWS = 25;
	static int const COLS = 80;
	int short _y;
	int short _x;
	int short _my;
	int short _mx;
	int short _by;
	int short _bx;
	int short _flags;
	int long unsigned _attr;
	int long unsigned _background;
	char dummy[16];
	char _buf[2 * ROWS * COLS];
	WINDOW( void )
		: _y( 0 )
		, _x( 0 )
		, _my( ROWS - 1 )
		, _mx( COLS - 1 )
		, _by( 0 )
		, _bx( 0 )
		, _flags( 0 )
		, _attr( 0 )
		, _background( 0 )
		, dummy()
		, _buf() {
	}
	void init( void ) {
		_x = 0;
		_y = 0;
		_mx = COLS - 1;
		_my = ROWS - 1;
		memset( dummy, 0, sizeof ( dummy ) );
		memset( _buf, 0, 2 * COLS * ROWS );
	}
	void wbkgd( int long unsigned bkgd_ ) {
		_background = bkgd_;
	}
	char* at( int row_, int col_ ) {
		return ( _buf + row_ * ( _mx + 1 ) + col_ );
	}
	char* cur( void ) {
		return ( _buf + _y * ( _mx + 1 ) + _x );
	}
	void addch( int ch_ ) {
		char* p( cur() );
		*p = static_cast<char>( ch_ );
		++p;
		*p = static_cast<char>( _attr );
		++ _x;
		if ( _x > _mx ) {
			_x = 0;
			++ _y;
		}
		if ( _y > _my ) {
			_y = _my;
			_x = _mx;
		}
	}
} stdscr;

namespace {
char const* col( int attr_ ) {
	char const* c( "" );
	switch ( attr_ & 0xf ) {
		case ( 0 ):  break;
		case ( 1 ):  c = *ansi::red;           break;
		case ( 2 ):  c = *ansi::green;         break;
		case ( 3 ):  c = *ansi::brown;         break;
		case ( 4 ):  c = *ansi::blue;          break;
		case ( 5 ):  c = *ansi::magenta;       break;
		case ( 6 ):  c = *ansi::cyan;          break;
		case ( 7 ):  c = *ansi::lightgray;     break;
		case ( 8 ):  c = *ansi::gray;          break;
		case ( 9 ):  c = *ansi::brightred;     break;
		case ( 10 ): c = *ansi::brightgreen;   break;
		case ( 11 ): c = *ansi::yellow;        break;
		case ( 12 ): c = *ansi::brightblue;    break;
		case ( 13 ): c = *ansi::brightmagenta; break;
		case ( 14 ): c = *ansi::brightcyan;    break;
		case ( 15 ): c = *ansi::white;         break;
	}
	return ( c );
}
}

yaal::hcore::HString dump( bool toTerm_ ) {
	HStringStream ss;
	HString line;
	if ( toTerm_ ) {
		line.append( "+" );
		for ( int c( 0 ); c <= stdscr._mx; ++ c ) {
			line.append( "-" );
		}
		line.append( "+\n" );
	}
	ss << line;
	if ( toTerm_ ) {
		ss << "rows = " << ( stdscr._my + 1 )
			<< ", cols = " << ( stdscr._mx + 1 )
			<< ", row = " << stdscr._y
			<< ", col = " << stdscr._x
			<< ", attr = " << stdscr._attr
			<< ", bkgd = " << stdscr._background
			<< ", raw = ";
		ss << hex;
		for ( int i( 0 ); i <= static_cast<int>( sizeof ( stdscr.dummy ) ); ++ i ) {
			if ( i ) {
				ss << ' ';
			}
			ss << static_cast<int>( stdscr.dummy[i] );
		}
		ss << dec << "\n";
	}
	ss << line;
	for ( int r( 0 ); r <= stdscr._my; ++ r ) {
		if ( toTerm_ ) {
			ss << '|';
		}
		for ( int c( 0 ); c <= stdscr._mx; ++ c ) {
			char* p( stdscr.at( r, c ) );
			int ch( *p );
			++ p;
			int attr( *p );
			if ( toTerm_ ) {
				ss << col( attr );
			} else {
				ss << "0123456789ABCDEF"[attr & 0xf];
			}
			if ( ch ) {
				ss << static_cast<char>( ch );
			} else {
				ss << ' ';
			}
		}
		if ( toTerm_ ) {
			ss << *ansi::reset << '|';
		}
		ss << '\n';
	}
	ss << line;
	return ( ss.str() );
}

}

}

extern "C" {

int tcgetattr( int, struct termios* );
int tcgetattr( int a0, struct termios* a1 ) {
	typedef int (*tcgetattr_t)( int, struct termios* );
	static tcgetattr_t orig_tcgetattr = yaal::bit_cast<tcgetattr_t>( dlsym( RTLD_NEXT, "tcgetattr" ) );
	int ret( orig_tcgetattr( a0, a1 ) );
	return ( ! tress::fake_console_subsystem::_fakeConsole_.is_active() ? ret : 0 );
}

int tcsetattr( int, int, const struct termios* );
int tcsetattr( int a0, int a1, const struct termios* a2 ) {
	typedef int (*tcsetattr_t)( int, int, const struct termios* );
	static tcsetattr_t orig_tcsetattr = yaal::bit_cast<tcsetattr_t>( dlsym( RTLD_NEXT, "tcsetattr" ) );
	int ret( orig_tcsetattr( a0, a1, a2 ) );
	return ( ! tress::fake_console_subsystem::_fakeConsole_.is_active() ? ret : 0 );
}

#ifndef __HOST_OS_TYPE_SOLARIS__
int isatty( int );
#endif /* #ifndef __HOST_OS_TYPE_SOLARIS__ */
int isatty( int fd_ ) {
	typedef int (*isatty_t)( int );
	static isatty_t orig_isatty = yaal::bit_cast<isatty_t>( dlsym( RTLD_NEXT, "isatty" ) );
	int ret( orig_isatty( fd_ ) );
	return ( ! tress::fake_console_subsystem::_fakeConsole_.is_active() ? ret : 1 );
}

using namespace tress::fake_console_subsystem;

WINDOW* initscr( void );
WINDOW* initscr( void ) {
	stdscr.init();
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

int waddch( WINDOW*, int );
int waddch( WINDOW* win_, int ch_ ) {
	win_->addch( ch_ );
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
int wbkgd( WINDOW* win_, int long unsigned bkgd_ ) {
	win_->wbkgd( bkgd_ );
	return ( 0 );
}

}

#endif /* #if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


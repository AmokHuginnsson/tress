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

#include <cstdarg>

#include "config.hxx"

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )

#include <cstring>
#include <cstdlib>
#include <dlfcn.h>

#include <yaal/hcore/base.hxx>
#include <yaal/hcore/hfile.hxx>
#include <yaal/tools/hmonitor.hxx>
#include <yaal/tools/ansi.hxx>
#include <yaal/tools/hstringstream.hxx>
#include <yaal/hconsole/console.hxx>
#include <yaal/hconsole/hconsole.hxx>
#include <yaal/hconsole/hwindowfactory.hxx>
#include <yaal/hconsole/hwidgetfactory.hxx>

#include <yaal/hcore/hlog.hxx>

#include "fake_console_subsystem.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;

namespace tress {

namespace fake_console_subsystem {

struct MEVENT {
	int short _id;
	int _x;
	int _y;
	int _z;
	mmask_t _state;
};

HFakeConsole::HFakeConsole( void )
	: _active( false )
	, _background()
	, _attributes()
	, _inputQueue()
	, _mutex()
	, _dump()
	, _input() {
}

void HFakeConsole::activate( void ) {
	_active = true;
	_background.clear();
	_attributes.clear();
	_inputQueue.clear();
	return;
}

int HFakeConsole::attr( chtype_t attr_ ) const {
	HLock l( _mutex );
	int a( COLORS::ATTR_DEFAULT );
	attribute_map_t::const_iterator it( _attributes.find( attr_ ) );
	if ( it != _attributes.end() ) {
		a = it->second;
	}
	return ( a );
}

int HFakeConsole::bg( chtype_t bg_ ) const {
	HLock l( _mutex );
	int b( COLORS::BG_BLACK );
	attribute_map_t::const_iterator it( _background.find( bg_ ) );
	if ( it != _background.end() ) {
		b = it->second;
	}
	return ( b );
}

void HFakeConsole::ungetch( int key_ ) {
	HLock l( _mutex );
	_inputQueue.push( key_ );
}

int HFakeConsole::getch( void ) {
	HLock l( _mutex );
	int key( -1 );
	if ( ! _inputQueue.is_empty() ) {
		key = _inputQueue.top();
		_inputQueue.pop();
	}
	if ( !! _dump && ( key != -1 ) && ( key != KEY<>::ctrl_r( _commandComposeCharacter_ ) ) ) {
		_dump->signal();
		l.unlock();
		/* dump happens here */
		_input->wait();
		l.lock();
	}
	if ( key == COMMIT_ESCAPE ) {
		key = -1;
	}

	return ( key );
}

void HFakeConsole::getmouse( MEVENT* ev_ ) {
	HLock l( _mutex );
	M_ASSERT( ! _inputQueue.is_empty() );
	::memset( ev_, 0, sizeof ( MEVENT ) );
	ev_->_x = _inputQueue.top();
	_inputQueue.pop();
	M_ASSERT( ! _inputQueue.is_empty() );
	ev_->_y = _inputQueue.top();
	_inputQueue.pop();
	ev_->_state = 4;
	return;
}

void HFakeConsole::wait_io( void ) {
	_dump->wait();
}

void HFakeConsole::wake_io( void ) {
	_input->signal();
}

void HFakeConsole::wait_dump( void ) {
	_input->wait();
}

void HFakeConsole::init_dump( void ) {
	HLock l( _mutex );
	_dump = make_resource<hcore::HEvent>();
	_input->signal();
}

void HFakeConsole::destroy_dump( void ) {
	HLock l( _mutex );
	_inputQueue.clear();
	_dump.reset();
}

void HFakeConsole::init_input( void ) {
	HLock l( _mutex );
	_input = make_resource<hcore::HEvent>();
}

void HFakeConsole::destroy_input( void ) {
	HLock l( _mutex );
	if ( !! _dump ) {
		while ( ! _inputQueue.is_empty() ) {
			if ( _inputQueue.top() != KEY<>::ctrl_r( _commandComposeCharacter_ ) ) {
				_dump->signal();
				l.unlock();
				_input->wait();
				l.lock();
			}
			if ( _inputQueue.is_empty() ) {
				break;
			}
			_inputQueue.pop();
		}
	}
	_input.reset();
}

HFakeConsole _fakeConsole_;

HFakeConsoleGuard::HFakeConsoleGuard( void )
	: _exclusiveAccess( yaal::tools::HMonitor::get_instance().acquire( "terminal" ) ) {
	M_PROLOG
	unsetenv( "YAAL_HAS_BROKEN_BRIGHT_BACKGROUND" );
	unsetenv( "MRXVT_TABTITLE" );
	unsetenv( "TERMINATOR_UUID" );
	setenv( "DISPLAY", ":0.0", 1 );
	_useMouse_ = USE_MOUSE::YES;
	_fakeConsole_.activate();
	HWindowFactory::get_instance().initialize_globals();
	HWidgetFactory::get_instance().initialize_globals();
	return;
	M_EPILOG
}

HFakeConsoleGuard::~HFakeConsoleGuard( void ) {
	M_PROLOG
	HWidgetFactory::get_instance().cleanup_globals();
	HWindowFactory::get_instance().cleanup_globals();
	_fakeConsole_.deactivate();
	return;
	M_DESTRUCTOR_EPILOG
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
	chtype_t _attr;
	chtype_t _background;
	char dummy[16];
	static int const BUF_SIZE = 2 * ROWS * COLS;
	char _buf[BUF_SIZE];
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
		_by = 0;
		_bx = 0;
		_flags = 0;
		_attr = 0;
		_background = 0;
		memset( dummy, 0, sizeof ( dummy ) );
		memset( _buf, 0, BUF_SIZE );
	}
	void wbkgd( chtype_t bkgd_ ) {
		_background = bkgd_;
	}
	char* at( int row_, int col_ ) {
		return ( _buf + 2 * ( row_ * ( _mx + 1 ) + col_ ) );
	}
	char* cur( void ) {
		return ( _buf + 2 * ( _y * ( _mx + 1 ) + _x ) );
	}
	void addch( int ch_ ) {
		char* p( cur() );
		*p = static_cast<char>( ch_ );
		++p;
		*p = static_cast<char>( _fakeConsole_.attr( _attr ) );
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
	void print( char const* format_, void* ap_ ) __attribute__(( format(printf, 2, 0) )) {
		HString s;
		s.vformat( format_, ap_ );
		for ( char c : s ) {
			addch( c );
		}
	}
	void addnstr( char const* str_, int len_ ) {
		if ( len_ < 0 ) {
			len_ = static_cast<int>( strlen( str_ ) );
		}
		for ( int i( 0 ); i < len_; ++ i ) {
			addch( str_[i] );
		}
	}
	void clrtoeol( void ) {
		for ( int i( _x ); i <= _mx; ++ i ) {
			char* p = at( _y, i );
			*p = static_cast<char>( '\0' );
			++p;
			*p = static_cast<char>( _fakeConsole_.bg( _background ) );
		}
	}
	void clear() {
		for ( int i( 0 ); i < BUF_SIZE; i += 2 ) {
			_buf[i] = 0;
			_buf[i + 1] = static_cast<char>( _fakeConsole_.bg( _background ) );
		}
	}
} stdscr;

void HFakeConsole::build_attribute_maps( WINDOW* win_ ) {
	HLock l( _mutex );
	HConsole& cons( HConsole::get_instance() );
	HScopedValueReplacement<chtype_t> b( win_->_background, 0 );
	HScopedValueReplacement<chtype_t> a( win_->_attr, 0 );
	_inputQueue.clear();
	_background.clear();
	for ( int col( COLORS::BG_BLACK ); col <= COLORS::BG_WHITE; col += 16 ) {
		cons.set_background( col );
		_background[win_->_background] = col;
	}
	_attributes.clear();
	for ( int col( 0 ); col < 256; ++ col ) {
		cons.set_attr( col );
		_attributes[win_->_attr] = col;
	}
}

namespace {

HString col( int attr_ ) {
	HString c;
	switch ( attr_ & 0xf ) {
		case ( 0 ):  c.append( *ansi::black );         break;
		case ( 1 ):  c.append( *ansi::red );           break;
		case ( 2 ):  c.append( *ansi::green );         break;
		case ( 3 ):  c.append( *ansi::brown );         break;
		case ( 4 ):  c.append( *ansi::blue );          break;
		case ( 5 ):  c.append( *ansi::magenta );       break;
		case ( 6 ):  c.append( *ansi::cyan );          break;
		case ( 7 ):  c.append( *ansi::lightgray );     break;
		case ( 8 ):  c.append( *ansi::gray );          break;
		case ( 9 ):  c.append( *ansi::brightred );     break;
		case ( 10 ): c.append( *ansi::brightgreen );   break;
		case ( 11 ): c.append( *ansi::yellow );        break;
		case ( 12 ): c.append( *ansi::brightblue );    break;
		case ( 13 ): c.append( *ansi::brightmagenta ); break;
		case ( 14 ): c.append( *ansi::brightcyan );    break;
		case ( 15 ): c.append( *ansi::white );         break;
	}
	switch ( ( attr_ >> 4 ) & 0xf ) {
		case ( 0 ):  c.append( *ansi::bgblack );         break;
		case ( 1 ):  c.append( *ansi::bgred );           break;
		case ( 2 ):  c.append( *ansi::bggreen );         break;
		case ( 3 ):  c.append( *ansi::bgbrown );         break;
		case ( 4 ):  c.append( *ansi::bgblue );          break;
		case ( 5 ):  c.append( *ansi::bgmagenta );       break;
		case ( 6 ):  c.append( *ansi::bgcyan );          break;
		case ( 7 ):  c.append( *ansi::bglightgray );     break;
		case ( 8 ):  c.append( *ansi::bggray );          break;
		case ( 9 ):  c.append( *ansi::bgbrightred );     break;
		case ( 10 ): c.append( *ansi::bgbrightgreen );   break;
		case ( 11 ): c.append( *ansi::bgyellow );        break;
		case ( 12 ): c.append( *ansi::bgbrightblue );    break;
		case ( 13 ): c.append( *ansi::bgbrightmagenta ); break;
		case ( 14 ): c.append( *ansi::bgbrightcyan );    break;
		case ( 15 ): c.append( *ansi::bgwhite );         break;
	}
	return ( c );
}

HString attr_name( int attr_ ) {
	HString an;
	int nibble( attr_ & 0xf );
	for ( int i( 0 ); i < 2; ++ i ) {
		if ( i > 0 ) {
			an.append( ":" );
			nibble = ( attr_ >> 4 ) & 0xf;
		}
		switch ( nibble ) {
			case ( 0 ):  an.append( "black" );         break;
			case ( 1 ):  an.append( "red" );           break;
			case ( 2 ):  an.append( "green" );         break;
			case ( 3 ):  an.append( "brown" );         break;
			case ( 4 ):  an.append( "blue" );          break;
			case ( 5 ):  an.append( "magenta" );       break;
			case ( 6 ):  an.append( "cyan" );          break;
			case ( 7 ):  an.append( "lightgray" );     break;
			case ( 8 ):  an.append( "gray" );          break;
			case ( 9 ):  an.append( "brightred" );     break;
			case ( 10 ): an.append( "brightgreen" );   break;
			case ( 11 ): an.append( "yellow" );        break;
			case ( 12 ): an.append( "brightblue" );    break;
			case ( 13 ): an.append( "brightmagenta" ); break;
			case ( 14 ): an.append( "brightcyan" );    break;
			case ( 15 ): an.append( "white" );         break;
		}
	}
	return ( an );
}

HString attr_name_short( int attr_ ) {
	char colorSymbols[] = "krgnbmclKRGyBMCw";
	HString ans( '{' );
	ans.append( colorSymbols[attr_ & 0xf] );
	ans.append( colorSymbols[( attr_ >> 4 ) & 0xf] );
	ans.append( '}' );
	return ( ans );
}

}

void build_attribute_maps( void ) {
	_fakeConsole_.build_attribute_maps( &stdscr );
}

yaal::hcore::HString term_dump( void ) {
	HStringStream ss;
	HString line;
	line.append( "+" );
	for ( int c( 0 ); c <= stdscr._mx; ++ c ) {
		line.append( "-" );
	}
	line.append( "+\n" );
	ss << line;
	ss << "rows = " << ( stdscr._my + 1 )
		<< ", cols = " << ( stdscr._mx + 1 )
		<< ", row = " << stdscr._y
		<< ", col = " << stdscr._x
		<< ", attr = " << attr_name( _fakeConsole_.attr( stdscr._attr ) )
		<< ", bkgd = " << attr_name( _fakeConsole_.bg( stdscr._background ) )
		<< ", raw = " << stdscr._by << ' ' << stdscr._bx << ' ';
	ss << hex;
	for ( int i( 0 ); i <= static_cast<int>( sizeof ( stdscr.dummy ) ); ++ i ) {
		if ( i ) {
			ss << ' ';
		}
		ss << static_cast<int>( stdscr.dummy[i] );
	}
	ss << dec << "\n";
	ss << line;
	int lastAttr( -1 );
	for ( int r( 0 ); r <= stdscr._my; ++ r ) {
		ss << '|';
		for ( int c( 0 ); c <= stdscr._mx; ++ c ) {
			char* p( stdscr.at( r, c ) );
			int ch( *p );
			++ p;
			int attr( *p );
			if ( attr != lastAttr ) {
				ss << col( attr );
				lastAttr = attr;
			}
			if ( ch ) {
				ss << static_cast<char>( ch );
			} else {
				ss << ' ';
			}
		}
		lastAttr = -1;
		ss << *ansi::reset << '|';
		ss << '\n';
	}
	ss << line;
	return ( ss.str() );
}

yaal::hcore::HString packed_dump( void ) {
	int attr( -1 );
	HStringStream ss;
	char const* p( stdscr.at( 0, 0 ) );
	char lastChar( static_cast<char>( 255 ) );
	int repeat( 0 );
	HString s;
	auto f = [&repeat, &lastChar, &ss, &s]() {
		if ( repeat > 0 ) {
			if ( repeat < 6 ) {
				s.assign( repeat, lastChar );
			} else {
				s.assign( '[' ).append( lastChar ).append( ',' ).append( repeat ).append( ']' );
			}
			ss << s;
			repeat = 0;
		}
	};
	for ( int i( 0 ); i < ( WINDOW::ROWS * WINDOW::COLS ); ++ i ) {
		char ch( *p ? *p : ' ' );
		++ p;
		int a( *p );
		++ p;
		if ( a != attr ) {
			attr = a;
			f();
			ss << attr_name_short( attr );
		}
		if ( ch != lastChar ) {
			f();
			lastChar = ch;
		}
		++ repeat;
	}
	f();
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
	stdscr.init();
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

int noecho( void );
int noecho( void ) {
	return ( 0 );
}

int echo( void );
int echo( void ) {
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

int ungetch( int );
int ungetch( int key_ ) {
	_fakeConsole_.ungetch( key_ );
	return ( 0 );
}

int wgetch( WINDOW* );
int wgetch( WINDOW* ) {
	return ( _fakeConsole_.getch() );
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

int getmouse( MEVENT* );
int getmouse( MEVENT* ev_ ) {
	_fakeConsole_.getmouse( ev_ );
	return ( 0 );
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

int wprintw( WINDOW*, char const*, ... ) __attribute__(( format(printf, 2, 3) ));
int wprintw( WINDOW* win_, char const* format_, ... ) {
	::std::va_list ap;
	va_start( ap, format_ );
	try {
		win_->print( format_, &ap );
	} catch ( ... ) {
		va_end( ap );
		throw;
	}
	va_end( ap );
	return ( 0 );
}

int vwprintw( WINDOW*, char const*, void* ) __attribute__(( format(printf, 2, 0) ));
int vwprintw( WINDOW* win_, char const* format_, void* ap_ ) {
	win_->print( format_, ap_ );
	return ( 0 );
}

int waddnstr( WINDOW*, char const*, int );
int waddnstr( WINDOW* win_, char const* str_, int n_ ) {
	win_->addnstr( str_, n_ );
	return ( 0 );
}

int wclrtoeol( WINDOW* );
int wclrtoeol( WINDOW* win_ ) {
	win_->clrtoeol();
	return ( 0 );
}

int wclear( WINDOW* );
int wclear( WINDOW* win_ ) {
	win_->clear();
	return ( 0 );
}

int werase( WINDOW* );
int werase( WINDOW* win_ ) {
	win_->clear();
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

int wbkgd( WINDOW*, chtype_t );
int wbkgd( WINDOW* win_, chtype_t bkgd_ ) {
	win_->wbkgd( bkgd_ );
	return ( 0 );
}

}

#endif /* #if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


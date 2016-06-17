/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  fake_console_subsystem.hxx - this file is integral part of `tress' project.

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

#ifndef HAVE_TRESS_FAKE_CONSOLE_SUBSYSTEM_HXX_INCLUDED
#define HAVE_TRESS_FAKE_CONSOLE_SUBSYSTEM_HXX_INCLUDED 1

#include <yaal/hcore/hthread.hxx>
#include <yaal/hcore/hstack.hxx>
#include <yaal/hcore/hhashmap.hxx>

namespace tress {

namespace fake_console_subsystem {

class HFakeConsoleGuard {
	yaal::hcore::HLock _exclusiveAccess;
public:
	HFakeConsoleGuard( void );
	virtual ~HFakeConsoleGuard( void );
};

#if SIZEOF_CHTYPE == 8
typedef yaal::u64_t chtype_t;
#else
typedef yaal::u32_t chtype_t;
#endif

struct WINDOW;
struct MEVENT;

class HFakeConsole {
private:
	typedef yaal::hcore::HStack<int> input_queue_t;
	typedef yaal::hcore::HHashMap<chtype_t, int> attribute_map_t;
	typedef yaal::hcore::HResource<yaal::hcore::HEvent> event_t;
	bool _active;
	attribute_map_t _background;
	attribute_map_t _attributes;
	input_queue_t _inputQueue;
	mutable yaal::hcore::HMutex _mutex;
	mutable event_t _dump;
	mutable event_t _input;
public:
	HFakeConsole( void );
	void activate( void );
	void deactivate( void ) {
		_active = false;
	}
	bool is_active() const {
		return ( _active );
	}
	void build_attribute_maps( WINDOW* );
	int attr( chtype_t attr_ ) const;
	int bg( chtype_t bg_ ) const;
	void ungetch( int key_ );
	int getch( void );
	void getmouse( MEVENT* );
	void wait_io( void );
	void wait_dump( void );
	void wake_io( void );
	void init_input( void );
	void destroy_input( void );
	void init_dump( void );
	void destroy_dump( void );
};

extern HFakeConsole _fakeConsole_;

void build_attribute_maps( void );
yaal::hcore::HString term_dump( void );
yaal::hcore::HString packed_dump( void );

}

}

#endif /* #ifndef HAVE_TRESS_FAKE_CONSOLE_SUBSYSTEM_HXX_INCLUDED */


/* Read tress/LICENSE.md file for copyright and licensing information. */

#ifndef HAVE_TRESS_FAKE_CONSOLE_SUBSYSTEM_HXX_INCLUDED
#define HAVE_TRESS_FAKE_CONSOLE_SUBSYSTEM_HXX_INCLUDED 1

#include <yaal/hcore/hthread.hxx>
#include <yaal/hcore/hstack.hxx>
#include <yaal/hcore/hhashmap.hxx>

#include "config.hxx"

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

#if SIZEOF_MMASK_T == 8
typedef yaal::u64_t mmask_t;
#else
typedef yaal::u32_t mmask_t;
#endif

struct WINDOW;
struct MEVENT;

static int const COMMIT_ESCAPE = -2;
static int const MOUSE_BUTTON1 = 4;
static int const MOUSE_WHEEL_UP = 524288;
static int const MOUSE_WHEEL_DOWN = 8388608;

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


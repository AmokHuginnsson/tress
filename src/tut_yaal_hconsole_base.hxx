/* Read tress/LICENSE.md file for copyright and licensing information. */

#ifndef TUT_YAAL_HCONSOLE_BASE_HXX_INCLUDED
#define TUT_YAAL_HCONSOLE_BASE_HXX_INCLUDED 1

#include <yaal/hconsole/hconsole.hxx>
#include <yaal/hconsole/htuiprocess.hxx>

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


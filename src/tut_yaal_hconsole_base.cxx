/* Read tress/LICENSE.md file for copyright and licensing information. */

#include "config.hxx"

#if defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 )
#ifndef __HOST_OS_TYPE_DARWIN__

#include <yaal/hcore/hlog.hxx>
#include <yaal/tools/util.hxx>
#include <yaal/tools/hmonitor.hxx>
#include <yaal/tools/streamtools.hxx>
#include <yaal/tools/keycode.hxx>
#include <yaal/dbwrapper/dbwrapper.hxx>

M_VCSID( "$Id: " __ID__ " $" )

#include "tut_yaal_hconsole_base.hxx"
#include "tut_yaal_hconsole_testwindow.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::util;
using namespace yaal::hconsole;
using namespace tress::fake_console_subsystem;

namespace tress {

int const tut_yaal_hconsole_base::CONSOLE_WIDTH = 80;
int const tut_yaal_hconsole_base::CONSOLE_HEIGHT = 25;

tut_yaal_hconsole_base::~tut_yaal_hconsole_base( void ) {
	if ( HConsole::get_instance().is_enabled() ) {
		HConsole::get_instance().leave_curses();
	}
}

tut_yaal_hconsole_base::tui_t tut_yaal_hconsole_base::make_tui( void ) {
	return ( do_make_tui() );
}

void tut_yaal_hconsole_base::play( char const* name_, int_array_t input_ ) {
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	clog << "### Starting scenario: " << name_ << endl;
	HThread t;
	HConsole& cons( HConsole::get_instance() );
	cons.enter_curses();
	tress::fake_console_subsystem::build_attribute_maps();
	reverse( input_.begin(), input_.end() );
	int skip( 0 );
	for ( int key : input_ ) {
		if ( key == KEY_CODE::MOUSE ) {
			skip += 3;
		} else if ( key == KEY<'l'>::ctrl ) {
			cons.ungetch( -1 );
		}
		if ( ( key == MOUSE_WHEEL_DOWN ) || ( key == MOUSE_WHEEL_UP ) ) {
			tress::fake_console_subsystem::_fakeConsole_.ungetch( key );
		} else {
			cons.ungetch( key );
		}
	}
	tui_t tp( make_tui() );
	tp->init_xrc( "tress", "data/tress.xrc" );
	tp->register_command_handler( "run_quit", call( &tut_yaal_hconsole_base::quit, this, tp.raw(), _1 ) );
	tp->register_command_handler( "run_test", call( &tut_yaal_hconsole_base::test, this, tp.raw(), _1 ) );
	tress::fake_console_subsystem::_fakeConsole_.init_input();
	try {
		HScopeExitCall sec( call( &tress::fake_console_subsystem::HFakeConsole::destroy_input, &tress::fake_console_subsystem::_fakeConsole_ ) );
		t.spawn( call( &tut_yaal_hconsole_base::push_keys, this, static_cast<int>( input_.get_size() ) - skip ) );
		tress::fake_console_subsystem::_fakeConsole_.wait_dump();
		tp->run();
	} catch ( HException const& e ) {
		HTee( cerr, hcore::log ) << "Unexpected exception: " << e.what() << endl;
	}
	t.finish();
	cons.leave_curses();
}

void tut_yaal_hconsole_base::push_keys( int keyCount_ ) {
	HConsole& cons( HConsole::get_instance() );
	tress::fake_console_subsystem::_fakeConsole_.init_dump();
	HScopeExitCall sec( call( &tress::fake_console_subsystem::HFakeConsole::destroy_dump, &tress::fake_console_subsystem::_fakeConsole_ ) );
	for ( int i( 0 ); i < keyCount_; ++ i ) {
		cons.notify_keyboard();
		tress::fake_console_subsystem::_fakeConsole_.wait_io();
		clog << tress::fake_console_subsystem::term_dump() << endl;
//		clog << tress::fake_console_subsystem::packed_dump() << endl;
		tress::fake_console_subsystem::_fakeConsole_.wake_io();
	}
}

bool tut_yaal_hconsole_base::quit( yaal::hconsole::HTUIProcess* tp, yaal::hconsole::HEvent const& ) {
	tp->quit();
	return ( true );
}

bool tut_yaal_hconsole_base::test( yaal::hconsole::HTUIProcess* tp, yaal::hconsole::HEvent const& ) {
	tp->add_window( make_pointer<tress::HTestWindow>( "Test", dbwrapper::util::connect( "sqlite3:///out/tress.sqlite" ) ) );
	return ( true );
}

}

#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
#endif /* defined( HAVE_DECL_RTLD_NEXT ) && ( HAVE_DECL_RTLD_NEXT == 1 ) */


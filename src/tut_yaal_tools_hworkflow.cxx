/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_hworkflow.cxx - this file is integral part of `tress' project.

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

#include <functional>

#include <TUT/tut.hpp>

#include <yaal/tools/hworkflow.hxx>
#include <yaal/tools/sleep.hxx>
#include <yaal/hcore/hlog.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"
#include <yaal/hcore/hhashmap.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_hworkflow );
TUT_TEST_GROUP( tut_yaal_tools_hworkflow, "yaal::tools::HWorkFlow" );

namespace {

class Task {
public:
	struct Fiber {
		bool _loop;
		bool _emptyRun;
		bool _fail;
		Fiber()
			: _loop( true )
			, _emptyRun( false )
			, _fail( false ) {
		}
	};
	typedef HHashMap<HThread::id_t, Fiber> fibers_t;
	typedef HArray<bool> slots_t;
private:
	mutable HMutex _mutex;
	int _workUnits;
	int _sleep;
	fibers_t _fibers;
	slots_t _slots;
public:
	typedef HInstanceTracker<Task> counter_t;
	Task( int sleep_ = 0, int slots_ = 0 )
		: _mutex( HMutex::TYPE::RECURSIVE )
		, _workUnits( 0 )
		, _sleep( sleep_ )
		, _fibers()
		, _slots( slots_ ) {
	}
	void foo( int id, char symbol, int waitTime ) {
		cout << "foo" << id << flush;
		register_runner();
		HClock c;
		for ( int i = 0; i < ( _sleep / waitTime ); ++ i ) {
			tools::sleep::milisecond( waitTime );
			cout << symbol << flush;
		}
		cout << "[" << id << "]" << endl;
	}
	void bar( counter_t c ) {
		do_work();
		cout << c.to_string() << endl;
	}
	void do_work( void ) {
		/* lock scope */ {
			HLock l( _mutex );
			++ _workUnits;
		}
		tools::sleep::milisecond( _sleep );
	}
	void do_slot_work( int idx_ ) {
		HLock l( _mutex );
		M_ASSERT( idx_ < _slots.get_size() );
		_slots[idx_] = true;
		tools::sleep::milisecond( _sleep );
	}
	int get_slot_fill( void ) const {
		return ( static_cast<int>( count( _slots.begin(), _slots.end(), true ) ) );
	}
	Fiber* register_runner() {
		HLock l( _mutex );
		return ( &( _fibers.insert( make_pair( HThread::get_current_thread_id(), Fiber() ) ).first->second ) );
	}
	int get_runner_count( void ) const {
		HLock l( _mutex );
		return ( static_cast<int>( _fibers.get_size() ) );
	}
	int get_performed_work_units( void ) const {
		HLock l( _mutex );
		return ( _workUnits );
	}
	void async_stop( Fiber** f_ ) {
		HLock l( _mutex );
		if ( *f_ ) {
			(*f_)->_loop = false;
		}
	}
	void worker( Fiber** fiber_, int target_ ) {
		*fiber_ = register_runner();
		/* empty run check */ {
			HLock l( _mutex );
			if ( (*fiber_)->_emptyRun ) {
				(*fiber_)->_fail = true;
				return;
			}
			if ( ! (*fiber_)->_loop ) {
				(*fiber_)->_emptyRun = true;
			}
		}
		while ( true ) {
			/* Get loop */ {
				HLock l( _mutex );
				if ( _workUnits >= target_ ) {
					break;
				}
				if ( ! (*fiber_)->_loop ) {
					break;
				}
			}
			do_work();
		}
	}
	bool want_restart( Fiber** fiber_, int target_ ) const {
		HLock l( _mutex );
		return ( !(*fiber_)->_fail && ( _workUnits < target_ ) );
	}
	void clear_fibers( void ) {
		_fibers.clear();
	}
};

}

TUT_UNIT_TEST( "Pushing tasks (functional test)." )
	TIME_CONSTRAINT_EXEMPT();
	/* Order of Task and HWorkFlow matters. */
	static int const SLEEP( 640 );
	Task t( SLEEP );
	char const mark[] = "!@#$%^&*+?";
	static int const WORKER_COUNT( static_cast<int>( sizeof ( mark ) ) - 1 );
	HWorkFlow w( WORKER_COUNT );
	int slp( 40 );
	int id( 0 );
	for ( char m : mark ) {
		w.push_task( call( &Task::foo, &t, id, m, slp ) );
		++ id;
		slp += 40;
	}
	tools::sleep::milisecond( SLEEP );
	ENSURE( "work not parallelized properly", t.get_runner_count() > 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Cleanup of finished tasks." ) {
	/* Order of Task and HWorkFlow matters. */
	Task t;
	HWorkFlow w( 3 );
	w.push_task( call( &Task::bar, &t, Task::counter_t() ) );
	if ( tools::sleep::milisecond( 400 ) ) {
		log_trace << "sleep interrupted!" << endl;
	}
	tools::sleep::milisecond( 100 );
	ENSURE_EQUALS( "work was not performed", t.get_performed_work_units(), 1 );
	ENSURE_EQUALS( "HWorkFlow did not cleaned its task list.", Task::counter_t::get_instance_count(), 0 );
}
TUT_TEARDOWN()

TUT_UNIT_TEST( "interrupt and explicit continue" )
	static int const SLEEP( 30 );
	Task t( SLEEP );
	static int const WORKER_COUNT( 16 );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	static int const TARGET( 150 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.push_task( call( &Task::worker, &t, &f, TARGET ), call( &Task::async_stop, &t, &f ), call( &Task::want_restart, &t, &f, TARGET ) );
		}
		tools::sleep::milisecond( ( TARGET / WORKER_COUNT ) * SLEEP / 2 );
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		int wu( t.get_performed_work_units() );
		ENSURE( "work not parallelized", t.get_runner_count() > 1 );
		ENSURE( "work was not performed", wu > 0 );
		ENSURE( "work was not interrupted", wu < TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		w.start();
	}
	ENSURE( "work was not performed", t.get_performed_work_units() >= TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "interrupt and implicit continue" )
	static int const SLEEP( 30 );
	Task t( SLEEP );
	static int const WORKER_COUNT( 16 );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	static int const TARGET( 150 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.push_task( call( &Task::worker, &t, &f, TARGET ), call( &Task::async_stop, &t, &f ), call( &Task::want_restart, &t, &f, TARGET ) );
		}
		tools::sleep::milisecond( ( TARGET / WORKER_COUNT ) * SLEEP / 2 );
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		int wu( t.get_performed_work_units() );
		ENSURE( "work not parallelized", t.get_runner_count() > 1 );
		ENSURE( "work was not performed", wu > 0 );
		ENSURE( "work was not interrupted", wu < TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
	}
	ENSURE( "work was not performed", t.get_performed_work_units() >= TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "abort" )
	static int const SLEEP( 30 );
	Task t( SLEEP );
	static int const WORKER_COUNT( 16 );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	static int const TARGET( 150 );
	int workUnitsInFirstShot( 0 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.push_task( call( &Task::worker, &t, &f, TARGET ), call( &Task::async_stop, &t, &f ), call( &Task::want_restart, &t, &f, TARGET ) );
		}
		tools::sleep::milisecond( ( TARGET / WORKER_COUNT ) * SLEEP / 2 );
		/* ABORT will crash if incorrectly implemented. */
		w.windup( HWorkFlow::WINDUP_MODE::ABORT );
		workUnitsInFirstShot = t.get_performed_work_units();
		ENSURE( "work not parallelized", t.get_runner_count() > 1 );
		ENSURE( "work was not performed", workUnitsInFirstShot > 0 );
		ENSURE( "work was not interrupted", workUnitsInFirstShot < TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
	}
	ENSURE_EQUALS( "additional work after abort performed", t.get_performed_work_units(), workUnitsInFirstShot );
TUT_TEARDOWN()

TUT_UNIT_TEST( "schedule_windup" )
	static int const SLEEP( 30 );
	Task t( SLEEP );
	static int const WORKER_COUNT( 16 );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	static int const TARGET( 150 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.push_task( call( &Task::worker, &t, &f, TARGET ), call( &Task::async_stop, &t, &f ), call( &Task::want_restart, &t, &f, TARGET ) );
		}
		tools::sleep::milisecond( ( TARGET / WORKER_COUNT ) * SLEEP / 2 );
		w.schedule_windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		while ( ! w.can_join() ) {
			tools::sleep::milisecond( 1 );
		}
		HClock c;
		w.join();
		ENSURE( "join blocked", c.get_time_elapsed( HClock::UNIT::MILISECOND ) < 20 );
		int wu( t.get_performed_work_units() );
		ENSURE( "work not parallelized", t.get_runner_count() > 1 );
		ENSURE( "work was not performed", wu > 0 );
		ENSURE( "work was not interrupted", wu < TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		w.start();
	}
	ENSURE( "work was not performed", t.get_performed_work_units() >= TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add task during interrupt (implicit restart)" )
	static int const SLEEP( 30 );
	static int const WORKER_COUNT( 16 );
	static int const TARGET( 150 );
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	int done( 0 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.push_task( call( &Task::worker, &t, &f, TARGET ), call( &Task::async_stop, &t, &f ), call( &Task::want_restart, &t, &f, TARGET ) );
		}
		tools::sleep::milisecond( ( TARGET / WORKER_COUNT ) * SLEEP / 2 );
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		int wu( t.get_performed_work_units() );
		ENSURE( "work not parallelized", t.get_runner_count() > 1 );
		ENSURE( "work was not performed", wu > 0 );
		ENSURE( "work was not interrupted", wu < TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		w.push_task( call( &std::function<void()>::operator(), make_pointer<std::function<void()>>( [&done](){ done = 1; } ) ) );
	}
	ENSURE( "work was not performed", t.get_performed_work_units() >= TARGET );
	ENSURE_EQUALS( "additional task not executed", done, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "many tasks" )
	static int const SLEEP( 4 );
	static int const SLOTS( 320 );
	Task t( SLEEP, SLOTS );
	static int const WORKER_COUNT( 16 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( int i( 0 ); i < SLOTS; ++ i ) {
			w.push_task( call( &Task::do_slot_work, &t, i ) );
		}
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
	}
	ENSURE_EQUALS( "work not done", t.get_slot_fill(), SLOTS );
TUT_TEARDOWN()

TUT_UNIT_TEST( "suspend" )
	static int const SLEEP( 4 );
	static int const SLOTS( 320 );
	Task t( SLEEP, SLOTS );
	static int const WORKER_COUNT( 16 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		int halve( SLOTS / 2 );
		for ( int i( 0 ); i < halve; ++ i ) {
			w.push_task( call( &Task::do_slot_work, &t, i ) );
		}
		w.windup( HWorkFlow::WINDUP_MODE::SUSPEND );
		ENSURE_EQUALS( "work not done", t.get_slot_fill(), halve );
		for ( int i( halve ); i < SLOTS; ++ i ) {
			w.push_task( call( &Task::do_slot_work, &t, i ) );
		}
	}
	ENSURE_EQUALS( "work not done", t.get_slot_fill(), SLOTS );
TUT_TEARDOWN()

}


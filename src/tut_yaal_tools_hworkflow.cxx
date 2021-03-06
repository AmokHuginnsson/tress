/* Read tress/LICENSE.md file for copyright and licensing information. */

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
		typedef yaal::hcore::HPointer<HEventDetector> detector_t;
		detector_t _waiter;
		Fiber()
			: _loop( true )
			, _emptyRun( false )
			, _fail( false )
			, _waiter( new HEventDetector ) {
		}
	};
	typedef HHashMap<HThread::id_t, Fiber> fibers_t;
	typedef HArray<bool> slots_t;
private:
	mutable HMutex _mutex;
	HEventDetector _eventDetector;
	int _workUnits;
	int _sleep;
	int _stopRequests;
	fibers_t _fibers;
	slots_t _slots;
public:
	typedef HInstanceTracker<Task> counter_t;
	Task( int sleep_ = 0, int slots_ = 0 )
		: _mutex( HMutex::TYPE::RECURSIVE )
		, _eventDetector()
		, _workUnits( 0 )
		, _sleep( sleep_ )
		, _stopRequests( 0 )
		, _fibers()
		, _slots( slots_ ) {
	}
	void foo( int id, char symbol, int waitTime ) {
		clog << "foo" << id << flush;
		register_runner();
		HClock c;
		for ( int i = 0; i < ( _sleep / waitTime ); ++ i ) {
			sleep_for( duration( waitTime, time::UNIT::MILLISECOND ) );
			clog << symbol << flush;
		}
		clog << "[" << id << "]" << endl;
	}
	void bar( counter_t c ) {
		do_work();
		clog << c.to_string() << endl;
	}
	void do_work( void ) {
		/* scope */ {
			HLock l( _mutex );
			++ _workUnits;
		}
		Fiber* f( register_runner() );
		if ( f->_waiter->wait( duration( _sleep, time::UNIT::MILLISECOND ) ) ) {
			f->_waiter->reset();
		}
	}
	void do_slot_work( int idx_ ) {
		Fiber* f( nullptr );
		/* scope */ {
			HLock l( _mutex );
			M_ASSERT( idx_ < _slots.get_size() );
			_slots[idx_] = true;
			f = register_runner();
		}
		if ( f->_waiter->wait( duration( _sleep, time::UNIT::MILLISECOND ) ) ) {
			f->_waiter->reset();
		}
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
		++ _stopRequests;
		if ( *f_ ) {
			(*f_)->_loop = false;
			(*f_)->_waiter->signal();
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
				if ( _stopRequests > 0 ) {
					-- _stopRequests;
					break;
				}
				if ( _workUnits >= target_ ) {
					break;
				}
				if ( ! (*fiber_)->_loop ) {
					break;
				}
				if ( ( _workUnits > 1 ) && ( get_runner_count() > 1 ) ) {
					_eventDetector.signal();
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
		HLock l( _mutex );
		_fibers.clear();
	}
	void reset_workunits( int wu_ ) {
		HLock l( _mutex );
		_workUnits = wu_;
	}
	bool wait_for_event( time::duration_t duration_ ) {
		return ( _eventDetector.wait( duration_ ) );
	}
};

static int const SLEEP( 16 );
static int const WORKER_COUNT( 4 );
static int const TARGET( 80 );

}

TUT_UNIT_TEST( "Pushing tasks (functional test)." )
	TIME_CONSTRAINT_EXEMPT();
	/* Order of Task and HWorkFlow matters. */
	static int const SLEEP( 160 );
	Task t( SLEEP );
	char const mark[] = "!@#$%^&*+?";
	static int const WORKER_COUNT( static_cast<int>( sizeof ( mark ) ) - 1 );
	HWorkFlow w( WORKER_COUNT );
	int slp( SLEEP / WORKER_COUNT );
	int id( 0 );
	int tries( 0 );
	static int const MAX_RETRIES( 16 );
	do {
		for ( char m : mark ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &Task::foo, &t, id, m, slp ) );
			++ id;
			slp += ( SLEEP / WORKER_COUNT );
		}
		sleep_for( duration( SLEEP, time::UNIT::MILLISECOND ) );
		++ tries;
	} while ( ( t.get_runner_count() < 2 ) && ( tries < MAX_RETRIES ) );
	if ( tries > 1 ) {
		cerr << "test " << get_test_name() << " retried " << tries << " times" << endl;
	}
	ENSURE_GREATER( "work not parallelized properly", t.get_runner_count(), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Cleanup of finished tasks." ) {
	TIME_CONSTRAINT_EXEMPT();
	/* Order of Task and HWorkFlow matters. */
	Task t;
	HWorkFlow w( 3 );
	w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &Task::bar, &t, Task::counter_t() ) );
	if ( ! sleep_for( duration( 400, time::UNIT::MILLISECOND ) ) ) {
		log_trace << "sleep interrupted!" << endl;
	}
	sleep_for( duration( 100, time::UNIT::MILLISECOND ) );
	ENSURE_EQUALS( "work was not performed", t.get_performed_work_units(), 1 );
	ENSURE_EQUALS( "HWorkFlow did not cleaned its task list.", Task::counter_t::get_instance_count(), 0 );
}
TUT_TEARDOWN()

TUT_UNIT_TEST( "interrupt and explicit continue" )
	TIME_CONSTRAINT_EXEMPT();
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &f, TARGET ),
				call( &Task::async_stop, &t, &f ),
				call( &Task::want_restart, &t, &f, TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		int wu( t.get_performed_work_units() );
		ENSURE_GREATER( "work not parallelized", t.get_runner_count(), 1 );
		ENSURE_GREATER( "work was not performed", wu, 0 );
		ENSURE_LESS( "work was not interrupted", wu, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		w.start();
	}
	ENSURE_GREATER_OR_EQUAL( "work was not performed", t.get_performed_work_units(), TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "interrupt and implicit continue" )
	TIME_CONSTRAINT_EXEMPT();
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &f, TARGET ),
				call( &Task::async_stop, &t, &f ),
				call( &Task::want_restart, &t, &f, TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		int wu( t.get_performed_work_units() );
		ENSURE_GREATER( "work not parallelized", t.get_runner_count(), 1 );
		ENSURE_GREATER( "work was not performed", wu, 0 );
		ENSURE_LESS( "work was not interrupted", wu, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
	}
	ENSURE_GREATER_OR_EQUAL( "work was not performed", t.get_performed_work_units(), TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "abort" )
	TIME_CONSTRAINT_EXEMPT();
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	int workUnitsInFirstShot( 0 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &f, TARGET ),
				call( &Task::async_stop, &t, &f ),
				call( &Task::want_restart, &t, &f, TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		/* ABORT will crash if incorrectly implemented. */
		w.windup( HWorkFlow::WINDUP_MODE::ABORT );
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		workUnitsInFirstShot = t.get_performed_work_units();
		ENSURE_GREATER( "work not parallelized", t.get_runner_count(), 1 );
		ENSURE_GREATER( "work was not performed", workUnitsInFirstShot, 0 );
		ENSURE_LESS( "work was not interrupted", workUnitsInFirstShot, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
	}
	ENSURE_EQUALS( "additional work after abort performed", t.get_performed_work_units(), workUnitsInFirstShot );
TUT_TEARDOWN()

TUT_UNIT_TEST( "schedule_windup" )
	TIME_CONSTRAINT_EXEMPT();
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &f, TARGET ),
				call( &Task::async_stop, &t, &f ),
				call( &Task::want_restart, &t, &f, TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		/*
		 * .schedule_windup() should alway be immediate (never waits),
		 * no matter waht WINDUP_MODE was used.
		 */
		w.schedule_windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		clog << "schedule_windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		/*
		 * .can_join() loop can hang depending on WINDUP_MODE.
		 */
		while ( ! w.can_join() ) {
			/* busy wait */
		}
		clog << "can_join: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		/*
		 * If .schedule_windup() fails to work properly then .can_join() loop takes at least 320 ms.
		 */
#ifdef __MSVCXX__
#	ifdef CONTINUOUS_INTEGRATION_APPVEYOR
		int expectJoin( 640 );
#	else
		int expectJoin( 160 );
#	endif
#elif defined( __HOST_OS_TYPE_FREEBSD__ )
		int expectJoin( 80 );
#else
		int expectJoin( 40 );
#endif
		int elapsed( static_cast<int>( c.get_time_elapsed( time::UNIT::MILLISECOND ) ) );
		if ( elapsed >= expectJoin ) {
			w.join();
		}
		ENSURE_LESS( ".can_join() loop blocked", elapsed, expectJoin );
		c.reset();
		/*
		 * .join() after .can_join() loop should never hang.
		 */
		w.join();
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		ENSURE_LESS( "join blocked", c.get_time_elapsed( time::UNIT::MILLISECOND ), expectJoin );
		int wu( t.get_performed_work_units() );
		ENSURE_GREATER( "work not parallelized", t.get_runner_count(), 1 );
		ENSURE_GREATER( "work was not performed", wu, 0 );
		ENSURE_LESS( "work was not interrupted", wu, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		w.start();
	}
	ENSURE_GREATER_OR_EQUAL( "work was not performed", t.get_performed_work_units(), TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "add task during interrupt (implicit restart)" )
	TIME_CONSTRAINT_EXEMPT();
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	int done( 0 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( Task::Fiber*& f : fibers ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &f, TARGET ),
				call( &Task::async_stop, &t, &f ),
				call( &Task::want_restart, &t, &f, TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		int wu( t.get_performed_work_units() );
		ENSURE_GREATER( "work not parallelized", t.get_runner_count(), 1 );
		ENSURE_GREATER( "work was not performed", wu, 0 );
		ENSURE_LESS( "work was not interrupted", wu, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &std::function<void()>::operator(), make_pointer<std::function<void()>>( [&done](){ done = 1; } ) ) );
	}
	ENSURE_GREATER_OR_EQUAL( "work was not performed", t.get_performed_work_units(), TARGET );
	ENSURE_EQUALS( "additional task not executed", done, 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "task in worker after interrupt, implicit restart" )
	TIME_CONSTRAINT_EXEMPT();
	Task t( SLEEP );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( int i( 0 ); i < ( WORKER_COUNT / 2 ); ++ i ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &fibers[i], TARGET ),
				call( &Task::async_stop, &t, &fibers[i] ),
				call( &Task::want_restart, &t, &fibers[i], TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		int wu( t.get_performed_work_units() );
		int runnerCount( t.get_runner_count() );
		clog << "runnerCount = " << runnerCount << endl;
		ENSURE_GREATER( "work not parallelized", runnerCount, 1 );
		ENSURE_GREATER( "work was not performed", wu, 0 );
		ENSURE_LESS( "work was not interrupted", wu, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
	}
	clog << "runnerCount = " << t.get_runner_count() << endl;
	ENSURE_GREATER_OR_EQUAL( "work was not performed", t.get_performed_work_units(), TARGET );
TUT_TEARDOWN()

TUT_UNIT_TEST( "spawn more task directly during resume" )
	TIME_CONSTRAINT_EXEMPT();
	static int const TARGET( 80 );
	static int const SLOTS( 20 );
	Task t( SLEEP, SLOTS );
	Task::Fiber* fibers[WORKER_COUNT] = {};
	int runnerCount( 0 );
	int workUnits( 0 );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( int i( 0 ); i < ( WORKER_COUNT / 2 ); ++ i ) {
			w.schedule_task(
				HWorkFlow::SCHEDULE_POLICY::LAZY,
				call( &Task::worker, &t, &fibers[i], TARGET ),
				call( &Task::async_stop, &t, &fibers[i] ),
				call( &Task::want_restart, &t, &fibers[i], TARGET )
			);
		}
		HClock c;
		t.wait_for_event( duration( ( TARGET / WORKER_COUNT ) * SLEEP, time::UNIT::MILLISECOND ) );
		clog << "waited: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		c.reset();
		w.windup( HWorkFlow::WINDUP_MODE::SUSPEND );
		clog << "windup: " << c.get_time_elapsed( time::UNIT::MILLISECOND ) << endl;
		runnerCount = t.get_runner_count();
		clog << "runnerCount = " << runnerCount << endl;
		ENSURE_GREATER( "work not parallelized", runnerCount, 1 );
		workUnits = t.get_performed_work_units();
		ENSURE_GREATER_OR_EQUAL( "work was not performed", workUnits, TARGET );
		for ( Task::Fiber const* f : fibers ) {
			ENSURE_NOT( "muliple empty runs", ( f ? f->_fail : false ) );
		}
		t.clear_fibers();
		fill( begin( fibers ), end( fibers ), nullptr );
		for ( int i( 0 ); i < SLOTS; ++ i ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &Task::do_slot_work, &t, i ) );
		}
	}
	clog << "runnerCount = " << t.get_runner_count() << endl;
	ENSURE_EQUALS( "work not done", t.get_slot_fill(), SLOTS );
	ENSURE_GREATER( "extra runners not spawned", t.get_runner_count(), runnerCount );
	ENSURE_EQUALS( "additional work units performed", t.get_performed_work_units(), workUnits );
TUT_TEARDOWN()

TUT_UNIT_TEST( "many tasks" )
	TIME_CONSTRAINT_EXEMPT();
	static int const SLEEP( 4 );
	static int const SLOTS( WORKER_COUNT * 10 );
	Task t( SLEEP, SLOTS );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		for ( int i( 0 ); i < SLOTS; ++ i ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &Task::do_slot_work, &t, i ) );
		}
		w.windup( HWorkFlow::WINDUP_MODE::INTERRUPT );
	}
	ENSURE_EQUALS( "work not done", t.get_slot_fill(), SLOTS );
TUT_TEARDOWN()

TUT_UNIT_TEST( "suspend" )
	TIME_CONSTRAINT_EXEMPT();
	static int const SLEEP( 4 );
	static int const SLOTS( WORKER_COUNT * 10 );
	Task t( SLEEP, SLOTS );
	/* HWorkFlow scope */ {
		HWorkFlow w( WORKER_COUNT );
		int halve( SLOTS / 2 );
		for ( int i( 0 ); i < halve; ++ i ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &Task::do_slot_work, &t, i ) );
		}
		w.windup( HWorkFlow::WINDUP_MODE::SUSPEND );
		ENSURE_EQUALS( "work not done", t.get_slot_fill(), halve );
		for ( int i( halve ); i < SLOTS; ++ i ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &Task::do_slot_work, &t, i ) );
		}
	}
	ENSURE_EQUALS( "work not done", t.get_slot_fill(), SLOTS );
TUT_TEARDOWN()

TUT_UNIT_TEST( "start_task (expanting slots)" )
	TIME_CONSTRAINT_EXEMPT();
	static int const SLOTS( 16 );
#ifdef __MSVCXX__
	static int const SLEEP( 2560 );
#else
	static int const SLEEP( 640 );
#endif
	Task t( SLEEP, SLOTS );
	/* HWorkFlow scope */ {
		HWorkFlow w( 1 );
		for ( int i( 0 ); i < SLOTS; ++ i ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::EAGER, call( &Task::do_slot_work, &t, i ) );
		}
	}
	ENSURE_EQUALS( "workflow size not expanded", t.get_runner_count(), SLOTS );
TUT_TEARDOWN()

TUT_UNIT_TEST( "start_task (reusing slots)" )
	TIME_CONSTRAINT_EXEMPT();
	static int const SLOTS( 16 );
	static int const SLEEP_IN_TASK( 1 );
#ifdef __MSVCXX__
	static int const SLEEP_BETWEEN_TASKS( 640 );
#else
	static int const SLEEP_BETWEEN_TASKS( 64 );
#endif
	Task t( SLEEP_IN_TASK, SLOTS );
	/* HWorkFlow scope */ {
		HWorkFlow w( 1 );
		for ( int i( 0 ); i < SLOTS; ++ i ) {
			w.schedule_task( HWorkFlow::SCHEDULE_POLICY::EAGER, call( &Task::do_slot_work, &t, i ) );
			sleep_for( duration( SLEEP_BETWEEN_TASKS, time::UNIT::MILLISECOND ) );
		}
	}
	ENSURE_EQUALS( "workflow size was expanded", t.get_runner_count(), 1 );
TUT_TEARDOWN()

namespace {
void dummy() {}
}

TUT_UNIT_TEST( "schedule after close" )
	HWorkFlow w;
	w.windup( HWorkFlow::WINDUP_MODE::CLOSE );
	ENSURE_THROW( "schedule after close acceptrd", w.schedule_task( HWorkFlow::SCHEDULE_POLICY::LAZY, call( &dummy ) ), HWorkFlowException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parallel start" )
	HWorkFlow w;
	ENSURE_THROW( "parallel start accepted", w.start(), HWorkFlowException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "parallel stop" )
	HWorkFlow w;
	w.schedule_windup( HWorkFlow::WINDUP_MODE::SUSPEND );
	ENSURE_THROW( "parallel stop accepted", w.windup( HWorkFlow::WINDUP_MODE::CLOSE ), HWorkFlowException );
	w.join();
TUT_TEARDOWN()

TUT_UNIT_TEST( "start while suspended" )
	HWorkFlow w;
	w.windup( HWorkFlow::WINDUP_MODE::SUSPEND );
	ENSURE_THROW( "tast started while suspended", w.schedule_task( HWorkFlow::SCHEDULE_POLICY::EAGER, call( &dummy ) ), HWorkFlowException );
TUT_TEARDOWN()

}


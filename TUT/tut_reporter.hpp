#ifndef TUT_REPORTER
#define TUT_REPORTER

#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "tut.hpp"
#include "tut_terminal.hpp"
#include <yaal/hcore/hthread.hxx>
#include <yaal/tools/xmath.hxx>

#ifdef __MSVCXX__
#include <windows.h>
#include <yaal/cleanup.hxx>
#endif /* __MSVCXX__ */

/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */
namespace {

static int const _maxWidth_(
	yaal::tools::HTerminal::get_instance().exists()
		? yaal::tools::xmath::clip( 80, yaal::tools::HTerminal::get_instance().size().columns(), 128 )
		: 0x10000
);

std::ostream& operator << ( std::ostream& os_, const tut::test_result& tr ) {
	char const* tags[][2] = {
			{ ".", "OK" },
			{ ",", "OK'" },
			{ "=F", " assertion failed" },
			{ "=S", " test skipped" },
			{ "=C", " unexpected excepion from mock constructor" },
			{ "=X", " unexpected excepion" },
			{ "=W", " warning" },
			{ "=T", " execution terminated" },
			{ "=P", " rethrown exception" },
			{ "=I", " setup error" }
	};
	int tag( tress::setup._verbose ? 1 : 0 );
	if ( tress::setup._verbose || ( ( tr._result != tut::test_result::ok ) && ( tr._result != tut::test_result::setup ) ) ) {
		os_ << "[" << std::flush;
	}
	if ( tr._result == tut::test_result::skipped ) {
		os_ << yaal::ansi::yellow << std::flush;
	} else if ( tr._result != tut::test_result::ok ) {
		os_ << yaal::ansi::red << std::flush;
	} else if ( tress::setup._verbose ) {
		os_ << yaal::ansi::green << std::flush;
	}
	switch ( tr._result ) {
		case tut::test_result::ok:
			os_ << ( errno == 0 ? tags[0][tag] : tags[1][tag] ) << std::flush;
		break;
		case tut::test_result::fail:
			os_ << tr._testNo << tags[2][tag] << std::flush;
		break;
		case tut::test_result::skipped:
			os_ << tr._testNo << tags[3][tag] << std::flush;
		break;
		case tut::test_result::ex_ctor:
			os_ << tr._testNo << tags[4][tag] << std::flush;
		break;
		case tut::test_result::ex:
			os_ << tr._testNo << tags[5][tag] << std::flush;
		break;
		case tut::test_result::warn:
			os_ << tr._testNo << tags[6][tag] << std::flush;
		break;
		case tut::test_result::term:
			os_ << tr._testNo << tags[7][tag] << std::flush;
		break;
		case tut::test_result::rethrown:
			os_ << tr._testNo << tags[8][tag] << std::flush;
		break;
		case tut::test_result::setup:
			os_ << "no such group: `" << tr._message << "'" << std::flush;
		break;
		case tut::test_result::setup_test_number:
			os_ << tr._testNo << tags[9][tag] << std::flush;
		break;
	}
	if ( tress::setup._verbose )
		os_ << " in " << tr._time << " ms";
	if ( tress::setup._verbose || ( tr._result != tut::test_result::ok ) ) {
		os_ << yaal::ansi::reset << std::flush;
	}
	if ( tress::setup._verbose || ( ( tr._result != tut::test_result::ok ) && ( tr._result != tut::test_result::setup ) ) ) {
		os_ << "]" << std::flush;
	}
	if ( tress::setup._verbose )
		os_ << std::endl;
	return os_;
}

}         // end of namespace

namespace tut {

std::string console_error_line( tut::test_result const& );
std::string console_error_line( tut::test_result const& tr_ ) {
	std::stringstream ss;
	if ( tr_._result == test_result::fail )
		ss << "     failed assertion in \"" << tr_._file << ":" << tr_._line << " ";
	else if ( tr_._result == test_result::ex ) {
		if ( tr_._line >= 0 )
			ss << "     unexpected exception in \"" << tr_._file << ":" << tr_._line << " ";
	} else if ( tr_._result == test_result::term )
		ss << "     segmentation fault in \"" << tr_._file << ":" << tr_._line << " ";
	else
		ss << "     message: \"";
	ss << tr_._message << "\"" << std::endl;
	return ( ss.str() );
}

std::string vim_error_line( tut::test_result const& );
std::string vim_error_line( tut::test_result const& tr_ ) {
	std::stringstream ss;
	if ( tr_._result == test_result::fail )
		ss << tr_._file << ":" << tr_._line << ": failed assertion \"";
	else if ( tr_._result == test_result::ex ) {
		if ( tr_._line >= 0 )
			ss << tr_._file << ":" << tr_._line << ": unexpected exception \"";
	} else if ( tr_._result == test_result::term )
		ss << tr_._file << ":" << tr_._line << ": segmentation fault in \"";
	else
		ss << "message: \"";
	ss << tr_._message << "\"" << std::endl;
	return ( ss.str() );
}

std::string visual_studio_error_line( tut::test_result const& );
std::string visual_studio_error_line( tut::test_result const& tr_ ) {
	std::stringstream ss;
	if ( tr_._result == test_result::fail )
		ss << tr_._file << "(" << tr_._line << ") : failed assertion \"";
	else if ( tr_._result == test_result::ex ) {
		if ( tr_._line >= 0 )
			ss << tr_._file << "(" << tr_._line << ") : unexpected exception \"";
	} else if ( tr_._result == test_result::term )
		ss << tr_._file << "(" << tr_._line << ") : segmentation fault in \"";
	else
		ss << "message: \"";
	ss << tr_._message << "\"" << std::endl;
#ifdef __MSVCXX__
	::OutputDebugString( ss.str().c_str() );
#endif /* __MSVCXX__ */
	return ( ss.str() );
}

/**
 * Default TUT callback handler.
 */
template<typename stream_t = std::ostream>
class reporter : public tut::callback {
	typedef stream_t stream_type;
	typedef std::string ( *error_line_t )( tut::test_result const& );
	typedef error_line_t error_line_type;

	std::string _currentGroup;
	typedef std::list<tut::test_result> not_passed_list_t;
	not_passed_list_t _notPassed;
	std::ostream& _os;
	yaal::hcore::HMutex _mutex;
	stream_type& _ls;
	error_line_type _errorLine;
	std::stringstream _groupTestLog;
	static int const MAX_SEPARATOR_LEN = 79;

public:

	int _okCount;
	int _exceptionsCount;
	int _failuresCount;
	int _skippedCount;
	int _terminationsCount;
	int _warningsCount;
	int _setupCount;
	int _totalTestCount;
	int _currentGroupTestCount;

	reporter()
		: _currentGroup()
		, _notPassed()
		, _os( std::cout )
		, _mutex()
		, _ls( std::cerr )
		, _errorLine( &console_error_line )
		, _groupTestLog()
		, _okCount( 0 )
		, _exceptionsCount( 0 )
		, _failuresCount( 0 )
		, _skippedCount( 0 )
		, _terminationsCount( 0 )
		, _warningsCount( 0 )
		, _setupCount( 0 )
		, _totalTestCount( 0 )
		, _currentGroupTestCount( 0 ) {
		clear();
	}

	reporter( std::ostream& out )
		: _currentGroup()
		, _notPassed()
		, _os( out )
		, _mutex()
		, _ls( &out == &std::cout ? std::cerr : std::cout )
		, _errorLine( &console_error_line )
		, _groupTestLog()
		, _okCount( 0 )
		, _exceptionsCount( 0 )
		, _failuresCount( 0 )
		, _skippedCount( 0 )
		, _terminationsCount( 0 )
		, _warningsCount( 0 )
		, _setupCount( 0 )
		, _totalTestCount( 0 )
		, _currentGroupTestCount( 0 ) {
	}

	reporter( std::ostream& out, stream_type& logger )
		: _currentGroup()
		, _notPassed()
		, _os( out )
		, _mutex()
		, _ls( logger )
		, _errorLine( &console_error_line )
		, _groupTestLog()
		, _okCount( 0 )
		, _exceptionsCount( 0 )
		, _failuresCount( 0 )
		, _skippedCount( 0 )
		, _terminationsCount( 0 )
		, _warningsCount( 0 )
		, _setupCount( 0 )
		, _totalTestCount( 0 )
		, _currentGroupTestCount( 0 ) {
	}

	virtual void run_started( int groupCount_, int testCount_ ) {
		clear();
		_totalTestCount = testCount_;
		_os << "tests plan: groups: " << groupCount_ << ", total: " << _totalTestCount << "\n" << std::endl;
	}

	void set_error_line( error_line_type errorLine_ ) {
		_errorLine = errorLine_;
	}

	virtual void group_started( std::string const& name, int ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: group: [" << name << "]" << std::endl;
		if ( tress::setup._verbose ) {
			int const textLen( static_cast<int>( name.length() + ( sizeof ( "[ " " ]" ) - 1 ) ) );
			int sepLen( ( MAX_SEPARATOR_LEN - textLen ) / 2 );
			if ( sepLen <= 0 ) {
				sepLen = 1;
			}
			int const sepLenExtra( MAX_SEPARATOR_LEN > ( sepLen * 2 + textLen ) ? MAX_SEPARATOR_LEN - ( sepLen * 2 + textLen ) : 0 );
			std::string sep( static_cast<size_t>( sepLen ), '=' );
			_os << yaal::ansi::yellow << sep << "[ "
				<< yaal::ansi::brightcyan << name
				<< yaal::ansi::yellow << " ]" << sep
				<< ( sepLenExtra > 0 ? "=" : "" )
				<< yaal::ansi::reset
				<< std::endl;
		}
	}

	virtual void group_completed( group_base const* group_ ) {
		if ( tress::setup._verbose ) {
			std::stringstream ss;
			group_base::run_stat_t stats( group_->get_stat() );
			ss << stats.first << '/' << stats.second << " in " << group_->get_time_elapsed() << " ms";
			std::string status( ss.str() );
			static std::string const sepIntro( 8, '=' );
			int const sepLen( MAX_SEPARATOR_LEN - ( static_cast<int>( status.length() ) + 10 ) );
			std::string const sep( static_cast<size_t>( sepLen > 0 ? sepLen : 1 ), '=' );
			_os << yaal::ansi::yellow << sepIntro << '[';
			if ( stats.first == stats.second ) {
				_os << ( group_->skipped() ? yaal::ansi::yellow : yaal::ansi::green );
			} else {
				_os << yaal::ansi::red;
			}
			_os << status << yaal::ansi::yellow << ']' << sep << yaal::ansi::reset << std::endl;
		}
	}

	virtual void test_started( std::string const& groupName_, int n, std::string const& title_ ) {
		yaal::hcore::HLock l( _mutex );
		using std::operator <<;
		_ls << "TUT: module::test<" << n << "> " << title_ << std::endl;
		if ( tress::setup._verbose ) {
			int const noLen( n > 99 ? 3 : ( n > 9 ? 2 : 1 ) );
			int const textLen( static_cast<int>( groupName_.length() + title_.length() + ( sizeof ( " TUT: " "::<" "> " " " ) - 1 ) ) + noLen );
			int sepLen( ( MAX_SEPARATOR_LEN - textLen ) / 2 );
			if ( sepLen <= 0 ) {
				sepLen = 1;
			}
			int const sepLenExtra( MAX_SEPARATOR_LEN > ( sepLen * 2 + textLen ) ? MAX_SEPARATOR_LEN - ( sepLen * 2 + textLen ) : 0 );
			std::string sep( static_cast<size_t>( sepLen ), '-' );
			_os << yaal::ansi::brightcyan << sep
				<< yaal::ansi::reset
				<< " TUT: " << groupName_ << "::<" << n << "> " << title_ << " "
				<< yaal::ansi::brightcyan
				<< sep << ( sepLenExtra > 0 ? "-" : "" )
				<< yaal::ansi::reset
				<< std::endl;
		}
	}

	virtual void test_completed( const tut::test_result& tr ) {
		yaal::hcore::HLock l( _mutex );

		std::string const& name( tr._group ? tr._group->get_name() : tr._message );

		if ( ! tress::setup._verbose && ( name != _currentGroup ) ) {
			if ( ! _currentGroup.empty() )
				_os << "\n";
			if ( ( _errorLine == console_error_line ) && tress::setup._fancy )
				_os << "\r" << std::string( static_cast<size_t>( _maxWidth_ - 1 ), ' ' ) << "\r" << name << std::flush;
			else
				_os << name << ": " << std::flush;
			_currentGroup = name;
			_currentGroupTestCount = 0;
			_groupTestLog.str( std::string() );
		}

		if ( tr._result == tut::test_result::ok )
			_okCount ++;
		else if ( tr._result == tut::test_result::ex )
			_exceptionsCount ++;
		else if ( tr._result == tut::test_result::ex_ctor )
			_exceptionsCount ++;
		else if ( tr._result == tut::test_result::fail )
			_failuresCount ++;
		else if ( tr._result == tut::test_result::skipped )
			_skippedCount ++;
		else if ( tr._result == tut::test_result::rethrown )
			_failuresCount ++;
		else if ( tr._result == tut::test_result::warn )
			_warningsCount ++;
		else if ( tr._result == tut::test_result::setup )
			_setupCount ++;
		else
			_terminationsCount ++;

		if ( tress::setup._fancy ) {
			_groupTestLog << tr << std::flush;
			int progressMax( _maxWidth_ - 12 );
			int total( _terminationsCount + _exceptionsCount + _failuresCount + _skippedCount + _warningsCount + _setupCount + _okCount );
			int progressCur( ( progressMax * total ) / _totalTestCount );
			if ( total )
				_os << "\n";
			_os << "tress: " << std::string( static_cast<size_t>( progressCur ), '=' )
				<< std::string( static_cast<size_t>( progressMax - progressCur ), ' ' )
				<< " " << ( ( 100 * total ) / _totalTestCount ) << "%"
				<< *yaal::ansi::up_bol << _currentGroup << ": " << _groupTestLog.str() << std::flush;
		} else {
			_os << tr << std::flush;
		}

		if ( tr._result == tut::test_result::ok ) {
			++ _currentGroupTestCount;
		} else {
			_currentGroupTestCount += ( tr._testNo < 10 ? 5 : ( tr._testNo < 100 ? 6 : 7 ) );
		}

		if ( tr._result != tut::test_result::ok ) {
			_notPassed.push_back( tr );
		}
		group_base::run_stat_t status( tr._group ? tr._group->get_stat() : group_base::run_stat_t( 0, 0 ) );
		if ( ! tr._group || ( ( status.second + tr._group->skipped() ) < tr._group->get_real_test_count() ) ) {
			return;
		}
		std::stringstream ss;
		ss << '(' << tr._group->get_time_elapsed() << ')';
		std::string timeElapsed( ss.str() );
		if ( ! tress::setup._fancy ) {
			_os << " " << timeElapsed;
			return;
		}
		int spaceCount( _maxWidth_ - ( 9 + static_cast<int>( name.length() ) + _currentGroupTestCount + static_cast<int>( timeElapsed.length() ) ) );
		if ( spaceCount > 0 ) {
			std::string space( static_cast<size_t>( spaceCount ), ' ' );
			_os << space;
		}
		_os << timeElapsed;
		if ( status.first == status.second ) {
			_os << " [" << ( tr._group->skipped() ? yaal::ansi::yellow : yaal::ansi::green ) << "Pass" << yaal::ansi::reset << "]" << std::flush;
		} else {
			_os << " [" << yaal::ansi::red << "Fail" << yaal::ansi::reset << "]" << std::flush;
		}
	}

	virtual void run_completed() {
		if ( ! tress::setup._verbose )
			_os << std::endl;

		if ( _notPassed.size() > 0 ) {
			not_passed_list_t::const_iterator i = _notPassed.begin();
			while ( i != _notPassed.end() ) {
				tut::test_result tr = *i;
				++ i;
				if ( tr._result == test_result::setup ) {
					continue;
				}
				if ( ( tr._result == test_result::skipped ) && ! tress::setup._verbose ) {
					continue;
				}

				_os << std::endl;

				_os << "---> " << "group: " << ( tr._group ? tr._group->get_name() : "" )
					<< ", test: test<" << tr._testNo << ">"
					<< ( ! tr._name.empty() ? ( std::string( " : " ) + tr._name ) : std::string() )
					<< std::endl;

#if defined ( TUT_USE_POSIX )
				if ( tr.pid != getpid() ) {
					_os << "     child pid: " << tr.pid << std::endl;
				}
#endif
				_os << "     problem: " << std::flush;
				switch ( tr._result ) {
					case test_result::rethrown:
						_os << "assertion failed in child" << std::endl;
					break;
					case test_result::fail :
						_os << "assertion failed" << std::endl;
					break;
					case test_result::ex:
					case test_result::ex_ctor: {
						_os << "unexpected exception" << std::endl;
						if ( ! tr._exceptionTypeId.empty() ) {
							_os << "     exception typeid: " << tr._exceptionTypeId << std::endl;
						}
						if ( tr._line > 0 ) {
							_os << "     last good location: " << tr._file << ":" << tr._line << std::endl;
						}
					}
					break;
					case test_result::term:
						_os << "would be terminated" << std::endl;
						tr._message = "segmentation fault";
					break;
					case test_result::warn:
						_os << "test passed, but cleanup code (destructor) raised"
						" an exception" << std::endl;
					break;
					default:
					break;
				}

				if ( ! tr._message.empty() )
					_os << _errorLine( tr );
			}
		}

		_os << std::endl;

		_os << "tests summary:" << std::flush;
		int total( _terminationsCount + _exceptionsCount + _failuresCount + _warningsCount + _setupCount + _okCount );
		_os << " run:" << total << "/" << _totalTestCount << " (" << ( ( total * 100. ) / _totalTestCount ) << "%)" << std::flush;
		if ( _terminationsCount > 0 ) {
			_os << ", terminations:" << _terminationsCount << " (" << ( ( 100. * _terminationsCount ) / _totalTestCount ) <<  "%)" << std::flush;
		}

		if ( _exceptionsCount > 0 ) {
			_os << ", exceptions:" << _exceptionsCount << " (" << ( ( 100. * _exceptionsCount ) / _totalTestCount ) <<  "%)" << std::flush;
		}

		if ( _failuresCount > 0 ) {
			_os << ", failures:" << _failuresCount << " (" << ( ( 100. * _failuresCount ) / _totalTestCount ) <<  "%)" << std::flush;
		}

		if ( _skippedCount > 0 ) {
			_os << ", skipped:" << _skippedCount << " (" << ( ( 100. * _skippedCount ) / _totalTestCount ) <<  "%)" << std::flush;
		}

		if ( _warningsCount > 0 ) {
			_os << ", warnings:" << _warningsCount << " (" << ( ( 100. * _warningsCount ) / _totalTestCount ) <<  "%)" << std::flush;
		}

		if ( _setupCount > 0 ) {
			_os << ", setups:" << _setupCount << " (" << ( ( 100. * _setupCount ) / _totalTestCount ) <<  "%)" << std::flush;
		}

		_os << ", ok:" << _okCount << " (" << ( ( 100. * _okCount ) / _totalTestCount ) <<  "%)" << std::flush;
		_os << std::endl;
	}

	virtual bool all_ok() const {
		return ( _notPassed.empty() ) ;
	}

	virtual int fail_count( void ) const {
		return ( _exceptionsCount + _failuresCount + _terminationsCount + _warningsCount + _setupCount );
	}

private:

	void clear() {
		_okCount = 0;
		_exceptionsCount = 0;
		_failuresCount = 0;
		_skippedCount = 0;
		_terminationsCount = 0;
		_warningsCount = 0;
		_setupCount = 0;
		_currentGroup.clear();
		_notPassed.clear();
	}
};

}

#endif


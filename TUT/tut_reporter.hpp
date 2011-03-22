#ifndef TUT_REPORTER
#define TUT_REPORTER

#include <cstdlib>
#include <iostream>

#include "tut.hpp"
#include <yaal/hcore/hthread.hxx>

/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */
namespace
{

std::ostream& operator <<( std::ostream& _os, const tut::test_result& tr )
	{
	switch ( tr._result )
		{
		case tut::test_result::ok:
			_os << ( errno == 0 ? '.' : ',' ) << std::flush;
		break;
		case tut::test_result::fail:
			_os << '[' << tr._testNo << "=F]" << std::flush;
		break;
		case tut::test_result::ex_ctor:
			_os << '[' << tr._testNo << "=C]" << std::flush;
		break;
		case tut::test_result::ex:
			_os << '[' << tr._testNo << "=X]" << std::flush;
		break;
		case tut::test_result::warn:
			_os << '[' << tr._testNo << "=W]" << std::flush;
		break;
		case tut::test_result::term:
			_os << '[' << tr._testNo << "=T]" << std::flush;
		break;
		case tut::test_result::rethrown:
			_os << '[' << tr._testNo << "=P]" << std::flush;
		break;
		case tut::test_result::setup:
			_os << "no such group" << std::flush;
		break;
		}

	return ( _os );
	}
}         // end of namespace

namespace tut
{

std::string console_error_line( tut::test_result const& tr_ )
	{
	std::stringstream ss;
	if ( tr_._result == test_result::fail )
		ss << "     failed assertion in \"" << tr_._file << ":" << tr_._line << " ";
	else if ( tr_._result == test_result::ex )
		{
		if ( tr_._line >= 0 )
			ss << "     unexpected exception in \"" << tr_._file << ":" << tr_._line << " ";
		}
	else if ( tr_._result == test_result::term )
		ss << "     segmentation fault in \"" << tr_._file << ":" << tr_._line << " ";
	else
		ss << "     message: \"";
	ss << tr_._message << "\"" << std::endl;
	return ( ss.str() );
	}

std::string vim_error_line( tut::test_result const& tr_ )
	{
	std::stringstream ss;
	if ( tr_._result == test_result::fail )
		ss << tr_._file << ":" << tr_._line << ": failed assertion \"";
	else if ( tr_._result == test_result::ex )
		{
		if ( tr_._line >= 0 )
			ss << tr_._file << ":" << tr_._line << ": unexpected exception \"";
		}
	else if ( tr_._result == test_result::term )
		ss << tr_._file << ":" << tr_._line << ": segmentation fault in \"";
	else
		ss << "message: \"";
	ss << tr_._message << "\"" << std::endl;
	return ( ss.str() );
	}

std::string visual_studio_error_line( tut::test_result const& tr_ )
	{
	std::stringstream ss;
	if ( tr_._result == test_result::fail )
		ss << tr_._file << "(" << tr_._line << ") : failed assertion \"";
	else if ( tr_._result == test_result::ex )
		{
		if ( tr_._line >= 0 )
			ss << tr_._file << "(" << tr_._line << ") : unexpected exception \"";
		}
	else if ( tr_._result == test_result::term )
		ss << tr_._file << "(" << tr_._line << ") : segmentation fault in \"";
	else
		ss << "message: \"";
	ss << tr_._message << "\"" << std::endl;
	return ( ss.str() );
	}

/**
 * Default TUT callback handler.
 */
template<typename stream_t = std::ostream>
class reporter : public tut::callback
	{
	typedef std::string ( *error_line_t )( tut::test_result const& );
	typedef stream_t stream_type;
	typedef error_line_t error_line_type;
	std::string _currentGroup;
	typedef std::list<tut::test_result> not_passed_list_t;
	not_passed_list_t _notPassed;
	std::ostream& _os;
	yaal::hcore::HMutex _mutex;
	stream_type& _ls;
	error_line_type _errorLine;

	public:

	int _okCount;
	int _exceptionsCount;
	int _failuresCount;
	int _terminationsCount;
	int _warningsCount;
	int _setupCount;

	reporter()
		: _currentGroup(), _notPassed(), _os( std::cout ), _mutex(), _ls( std::cerr ),
		_errorLine( &console_error_line ),
		_okCount( 0 ), _exceptionsCount( 0 ), _failuresCount( 0 ),
		_terminationsCount( 0 ), _warningsCount( 0 ), _setupCount( 0 )
		{
		clear();
		}

	reporter( std::ostream& out )
		: _currentGroup(), _notPassed(), _os( out ), _mutex(),
		_ls( &out == &std::cout ? std::cerr : std::cout ),
		_errorLine( &console_error_line ),
		_okCount( 0 ), _exceptionsCount( 0 ), _failuresCount( 0 ),
		_terminationsCount( 0 ), _warningsCount( 0 ), _setupCount( 0 )
		{
		}

	reporter( std::ostream& out, stream_type& logger )
		: _currentGroup(), _notPassed(), _os( out ), _mutex(), _ls( logger ),
		_errorLine( &console_error_line ),
		_okCount( 0 ), _exceptionsCount( 0 ), _failuresCount( 0 ),
		_terminationsCount( 0 ), _warningsCount( 0 ), _setupCount( 0 )
		{
		}

	void run_started()
		{
		clear();
		}
	void set_error_line( error_line_type errorLine_ )
		{
		_errorLine = errorLine_;
		}

	void group_started( std::string const&name )
		{
		yaal::hcore::HLock l( _mutex );

		_ls << "TUT: group: [" << name << "]" << std::endl;
		}

	void test_started( const int&n )
		{
		yaal::hcore::HLock l( _mutex );

		_ls << "TUT: module::test<" << n << ">" << std::endl;
		}

	void test_completed( const tut::test_result& tr )
		{
		yaal::hcore::HLock l( _mutex );

		if ( tr._group != _currentGroup )
			{
			_os << std::endl << tr._group << ": " << std::flush;
			_currentGroup = tr._group;
			}

		_os << tr << std::flush;
		if ( tr._result == tut::test_result::ok )
			_okCount ++;

		else if ( tr._result == tut::test_result::ex )
			_exceptionsCount ++;
		else if ( tr._result == tut::test_result::ex_ctor )
			_exceptionsCount ++;
		else if ( tr._result == tut::test_result::fail )
			_failuresCount ++;
		else if ( tr._result == tut::test_result::rethrown )
			_failuresCount ++;
		else if ( tr._result == tut::test_result::warn )
			_warningsCount ++;
		else if ( tr._result == tut::test_result::setup )
			_setupCount ++;
		else
			_terminationsCount ++;

		if ( tr._result != tut::test_result::ok )
			_notPassed.push_back( tr );
		}

	void run_completed()
		{
		_os << std::endl;

		if ( _notPassed.size() > 0 )
			{
			not_passed_list_t::const_iterator i = _notPassed.begin();
			while ( i != _notPassed.end() )
				{
				tut::test_result tr = *i;
				++ i;
				if ( tr._result == test_result::setup )
					continue;

				_os << std::endl;

				_os << "---> " << "group: " << tr._group
					<< ", test: test<" << tr._testNo << ">"
					<< ( !tr._name.empty() ? ( std::string( " : " ) + tr._name ) : std::string() )
					<< std::endl;

#if defined ( TUT_USE_POSIX )
				if ( tr.pid != getpid() )
					{
					_os << "     child pid: " << tr.pid << std::endl;
					}

#endif
				_os << "     problem: " << std::flush;
				switch ( tr._result )
					{
					case test_result::rethrown:
						_os << "assertion failed in child" << std::endl;
					break;
					case test_result::fail :
						_os << "assertion failed" << std::endl;
					break;
					case test_result::ex:
					case test_result::ex_ctor:
						{
						_os << "unexpected exception" << std::endl;
						if ( tr._exceptionTypeId != "" )
							{
							std::string symbol( yaal::hcore::demangle( tr._exceptionTypeId.c_str() ).raw() );
							_os << "     exception typeid: " << ( symbol.empty() ? std::string( "(nil)" ) : symbol ) << std::endl;
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
		if ( _terminationsCount > 0 )
			{
			_os << " terminations:" << _terminationsCount << std::flush;
			}

		if ( _exceptionsCount > 0 )
			{
			_os << " exceptions:" << _exceptionsCount << std::flush;
			}

		if ( _failuresCount > 0 )
			{
			_os << " failures:" << _failuresCount << std::flush;
			}

		if ( _warningsCount > 0 )
			{
			_os << " warnings:" << _warningsCount << std::flush;
			}

		if ( _setupCount > 0 )
			{
			_os << " setups:" << _setupCount << std::flush;
			}

		_os << " ok:" << _okCount << std::flush;
		_os << std::endl;
		}

	bool all_ok() const
		{
		return ( _notPassed.empty() ) ;
		}

	private:

	void clear()
		{
		_okCount = 0;
		_exceptionsCount = 0;
		_failuresCount = 0;
		_terminationsCount = 0;
		_warningsCount = 0;
		_setupCount = 0;
		_currentGroup.clear();
		_notPassed.clear();
		}
	};
}

#endif

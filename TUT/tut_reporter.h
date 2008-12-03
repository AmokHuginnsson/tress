#ifndef TUT_REPORTER
#define TUT_REPORTER

#include <cxxabi.h>
#include "tut.h"
#include <yaal/hcore/hthread.hxx>

/**
 * Template Unit Tests Framework for C++.
 * http://tut.dozen.ru
 *
 * @author Vladimir Dyuzhev, Vladimir.Dyuzhev@gmail.com
 */
namespace
{

std::ostream& operator <<( std::ostream& os, const tut::test_result& tr )
	{
	switch ( tr.result )
		{
		case tut::test_result::ok:
			os << ( errno == 0 ? '.' : ',' ) << std::flush;
		break;
		case tut::test_result::fail:
			os << '[' << tr._testNo << "=F]" << std::flush;
		break;
		case tut::test_result::ex_ctor:
			os << '[' << tr._testNo << "=C]" << std::flush;
		break;
		case tut::test_result::ex:
			os << '[' << tr._testNo << "=X]" << std::flush;
		break;
		case tut::test_result::warn:
			os << '[' << tr._testNo << "=W]" << std::flush;
		break;
		case tut::test_result::term:
			os << '[' << tr._testNo << "=T]" << std::flush;
		break;
		case tut::test_result::setup:
			os << "no such group" << std::flush;
		}

	return ( os );
	}
}         // end of namespace

namespace tut
{
/**
 * Default TUT callback handler.
 */
template<typename tType = std::ostream>
class reporter : public tut::
	callback
	{
	std::string current_group;
	typedef std::list<tut::test_result> not_passed_list;
	not_passed_list not_passed;
	std::ostream& os;
	yaal::hcore::HMutex f_oMutex;
	tType& ls;

	public:

	int ok_count;
	int exceptions_count;
	int failures_count;
	int terminations_count;
	int warnings_count;
	int setup_count;

	reporter() : os( std::cout ), ls( std::cerr )
		{
		init();
		}

	reporter( std::ostream& out ) : os( out ),
		ls( &out == &std::cout ? std::cerr : std::cout )
		{
		init();
		}

	reporter( std::ostream& out, tType& logger ) : os( out ), ls( logger )
		{
		init();
		}

	void run_started()
		{
		init();
		}

	void group_started( std::string const&name )
		{
		yaal::hcore::HLock l( f_oMutex );

		ls << "TUT: group: [" << name << "]" << std::endl;
		}

	void test_started( const int&n )
		{
		yaal::hcore::HLock l( f_oMutex );

		ls << "TUT: module::test<" << n << ">" << std::endl;
		}

	void test_completed( const tut::test_result& tr )
		{
		yaal::hcore::HLock l( f_oMutex );

		if ( tr.group != current_group )
			{
			os << std::endl << tr.group << ": " << std::flush;
			current_group = tr.group;
			}

		os << tr << std::flush;
		if ( tr.result == tut::test_result::ok )
			ok_count ++;

		else if ( tr.result == tut::test_result::ex )
			exceptions_count ++;
		else if ( tr.result == tut::test_result::ex_ctor )
			exceptions_count ++;
		else if ( tr.result == tut::test_result::fail )
			failures_count ++;
		else if ( tr.result == tut::test_result::warn )
			warnings_count ++;
		else if ( tr.result == tut::test_result::setup )
			setup_count ++;
		else
			terminations_count ++;

		if ( tr.result != tut::test_result::ok )
			not_passed.push_back( tr );
		}

	void run_completed()
		{
		os << std::endl;

		if ( not_passed.size() > 0 )
			{
			not_passed_list::const_iterator i = not_passed.begin();
			while ( i != not_passed.end() )
				{
				tut::test_result tr = *i;
				++ i;
				if ( tr.result == test_result::setup )
					continue;

				os << std::endl;

				os << "---> " << "group: " << tr.group
					<< ", test: test<" << tr._testNo << ">"
					<< ( !tr._name.empty() ? ( std::string( " : " ) + tr._name ) : std::string() )
					<< std::endl;

				os << "     problem: " << std::flush;
				switch ( tr.result )
					{
					case test_result::fail :
						os << "assertion failed" << std::endl;
					break;
					case test_result::ex:
					case test_result::ex_ctor:
						{
						os << "unexpected exception" << std::endl;
						if ( tr._exceptionTypeId != "" )
							{
							int status = 0;
							os << "     exception typeid: " << abi::__cxa_demangle( tr._exceptionTypeId.c_str(), 0, 0, &status ) << std::endl;
							}
						}
					break;
					case test_result::term:
						os << "would be terminated" << std::endl;
						tr._message = "segmentation fault";
					break;
					case test_result::warn:
						os << "test passed, but cleanup code (destructor) raised"
						" an exception" << std::endl;
					break;
					default:
					break;
					}

				if ( ! tr._message.empty() )
					{
					if ( tr.result == test_result::fail )
						os << "     failed assertion in \"" << tr._file << ":" << tr._line << " ";
					else if ( tr.result == test_result::ex )
						{
						if ( tr._line >= 0 )
							os << "     unexpected exception in \"" << tr._file << ":" << tr._line << " ";
						}
					else if ( tr.result == test_result::term )
						os << "     segmentation fault in \"" << tr._file << ":" << tr._line << " ";
					else
						os << "     message: \"";
					os << tr._message << "\"" << std::endl;
					}
				}
			}

		os << std::endl;

		os << "tests summary:" << std::flush;
		if ( terminations_count > 0 )
			{
			os << " terminations:" << terminations_count << std::flush;
			}

		if ( exceptions_count > 0 )
			{
			os << " exceptions:" << exceptions_count << std::flush;
			}

		if ( failures_count > 0 )
			{
			os << " failures:" << failures_count << std::flush;
			}

		if ( warnings_count > 0 )
			{
			os << " warnings:" << warnings_count << std::flush;
			}

		if ( setup_count > 0 )
			{
			os << " setups:" << setup_count << std::flush;
			}

		os << " ok:" << ok_count << std::flush;
		os << std::endl;
		}

	bool all_ok() const
		{
		return ( not_passed.empty() ) ;
		}

	private:

	void init()
		{
		ok_count = 0;
		exceptions_count = 0;
		failures_count = 0;
		terminations_count = 0;
		warnings_count = 0;
		setup_count = 0;
		not_passed.clear();
		}
	};
}

#endif

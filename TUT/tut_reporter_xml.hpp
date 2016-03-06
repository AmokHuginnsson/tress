#ifndef TUT_REPORTER_XML
#define TUT_REPORTER_XML

#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "tut.hpp"
#include "tut_reporter_cppunit.hpp"

namespace tut {
/**
 * \brief JUnit XML TUT reporter
 * @author Lukasz Maszczynski, NSN
 * @date 11/07/2008
 */
class reporter_xml : public tut::callback {
	typedef std::vector<tut::test_result> TestResults;
	typedef std::map<std::string, TestResults> TestGroups;

	TestGroups _allTests;   /// holds all test results
	const std::string _filename;   /// filename base
	typedef std::unique_ptr<std::ostream> stream_t;
	stream_t _stream;

	/**
	 * \brief Builds "testcase" XML entity with given parameters
	 * Builds \<testcase\> entity according to given parameters. \<testcase\>-s are part of \<testsuite\>.
	 * @param tr test result to be used as source data
	 * @param failure_type type of failure to be reported ("Assertion" or "Error", empty if test passed)
	 * @param failure_msg failure message to be reported (empty, if test passed)
	 * @return string with \<testcase\> entity
	 */
	std::string xml_build_testcase( const tut::test_result& tr, const std::string& failure_type,
		const std::string& failure_msg, int pid = 0 ) {
		using std::endl;
		using std::string;

		std::ostringstream out;

		if ( tr._result == test_result::ok ) {
			out << "\t\t<testcase classname=\"" << reporter_cppunit::encode( tr._group->get_name() ) << "\" name=\"" << reporter_cppunit::encode( tr._name ) << "\" status=\"run\" time=\"" << tr._time << "\" />";
		} else {
			string err_msg = reporter_cppunit::encode( failure_msg + tr._message );

			string tag;       // determines tag name: "failure" or "error"
			if ( ( tr._result == test_result::fail) || ( tr._result == test_result::warn)
			     || ( tr._result == test_result::ex) || ( tr._result == test_result::ex_ctor) || ( tr._result == test_result::rethrown) ) {
				tag = "failure";
			} else {
				tag = "error";
			}

			out << "\t\t<testcase classname=\"" << ( tr._group ? reporter_cppunit::encode( tr._group->get_name() ) : "no such group" ) << "\" name=\"" << reporter_cppunit::encode( tr._name ) << "\" time=\"" << tr._time <<  "\">" << endl;
			out << "\t\t\t<" << tag << " message=\"" << err_msg << "\"" << " type=\"" << failure_type << "\"";
#if defined(TUT_USE_POSIX)
			if ( pid != getpid() ) {
				out << " child=\"" << pid << "\"";
			}
#else
			(void)pid;
#endif
			out << ">\n\t\t\t\t<![CDATA[" << tr._file << ":" << tr._line << "\n" << err_msg << "]]>\n\t\t\t</" << tag << ">" << endl;
			out << "\t\t</testcase>";
		}

		return ( out.str() ) ;
	}

	/**
	 * \brief Builds "testsuite" XML entity
	 * Builds \<testsuite\> XML entity according to given parameters.
	 * @param errors number of errors to be reported
	 * @param failures number of failures to be reported
	 * @param total total number of tests to be reported
	 * @param name test suite name
	 * @param testcases reporter_cppunit::encoded XML string containing testcases
	 * @return string with \<testsuite\> entity
	 */
	std::string xml_build_testsuite( int errors, int failures, int total,
		const std::string& name, const std::string& testcases ) {
		std::ostringstream out;

		out << "\t<testsuite name=\"" << reporter_cppunit::encode( name ) << "\" tests=\"" << total << "\" failures=\"" << failures << "\" disabled=\"0\" errors=\"" << errors << "\" time=\"0\">" << std::endl;
		out << testcases;
		out << "\t</testsuite>";

		return ( out.str() ) ;
	}

public:
	int _okCount;             /// number of passed tests
	int _exceptionsCount;     /// number of tests that threw exceptions
	int _failuresCount;       /// number of tests that failed
	int _skippedCount;        /// number of tests that were skipped
	int _terminationsCount;   /// number of tests that would terminate
	int _warningsCount;       /// number of tests where destructors threw an exception

	/**
	 * \brief Default constructor
	 * @param filename base filename
	 */
	reporter_xml( const std::string& filename )
		: _allTests()
		, _filename( filename )
		, _stream( new std::ofstream( _filename.c_str() ) )
		, _okCount( 0 )
		, _exceptionsCount( 0 )
		, _failuresCount( 0 )
		, _skippedCount( 0 )
		, _terminationsCount( 0 )
		, _warningsCount( 0 ) {
		if ( !_stream->good() ) {
			throw tut_error( "Cannot open output file `" + _filename + "`" );
		}
	}

	reporter_xml( std::ostream& stream )
		: _allTests()
		, _filename()
		, _stream( &stream )
		, _okCount( 0 )
		, _exceptionsCount( 0 )
		, _failuresCount( 0 )
		, _skippedCount( 0 )
		, _terminationsCount( 0 )
		, _warningsCount( 0 ) {
	}

	~reporter_xml() {
		if ( _filename.empty() ) {
			_stream.release();
		}
	}

	/**
	 * \brief Callback function
	 * This function is called before the first test is executed. It initializes counters.
	 */
	virtual void run_started( int, int ) {
		_okCount = 0;
		_exceptionsCount = 0;
		_failuresCount = 0;
		_skippedCount = 0;
		_terminationsCount = 0;
		_warningsCount = 0;
		_allTests.clear();
	}

	virtual void group_started( const std::string& /*name */, int /* total test count for group */ ) {
	}
	virtual void group_completed( group_base const* ) {
	}
	virtual void test_started( std::string const&, int /*n */, std::string const& ) {
	}
	virtual int fail_count( void ) const {
		return ( _exceptionsCount + _failuresCount + _terminationsCount + _warningsCount );
	}

	/**
	 * \brief Callback function
	 * This function is called when test completes. Counters are updated here, and test results stored.
	 */
	virtual void test_completed( const tut::test_result& tr ) {
		// update global statistics
		switch ( tr._result ) {
			case test_result::ok:
				_okCount ++;
				break;
			case test_result::fail:
			case test_result::rethrown:
				_failuresCount ++;
				break;
			case test_result::skipped:
				_skippedCount ++;
				break;
			case test_result::ex:
			case test_result::ex_ctor:
				_exceptionsCount ++;
				break;
			case test_result::warn:
				_warningsCount ++;
				break;
			case test_result::term:
				_terminationsCount ++;
				break;
			case test_result::setup:
			case test_result::setup_test_number:
				break;
		}   // switch

		// add test result to results table
		_allTests[ tr._group ? tr._group->get_name() : "no such group" ].push_back( tr );
	}

	/**
	 * \brief Callback function
	 * This function is called when all tests are completed. It generates XML output
	 * to file(s). File name base can be set with constructor.
	 */
	virtual void run_completed() {
		/* *********************** header ***************************** */
		*_stream << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>" << std::endl;

		// iterate over all test groups
		int passed = 0;               // passed in single group
		int exceptions = 0;           // exceptions in single group
		int failures = 0;             // failures in single group
		int skipped = 0;              // skipped tests
		int terminations = 0;         // terminations in single group
		int warnings = 0;             // warnings in single group
		int errors = 0;               // errors in single group
		for ( TestGroups::const_iterator tgi = _allTests.begin(); tgi != _allTests.end(); ++ tgi ) {
			const TestResults&results = tgi->second;
			for ( TestResults::const_iterator tri = results.begin(); tri != results.end(); ++ tri ) {
				std::string failure_type;            // string describing the failure type
				std::string failure_msg;             // a string with failure message

				switch ( tri->_result ) {
					case test_result::ok:
						passed ++;
						break;
					case test_result::fail:
						failures ++;
						break;
					case test_result::skipped:
						skipped ++;
						break;
					case test_result::ex:
						exceptions ++;
						break;
					case test_result::warn:
						warnings ++;
						break;
					case test_result::term:
						terminations ++;
						break;
					case test_result::ex_ctor:
						exceptions ++;
						break;
					case test_result::rethrown:
						failures ++;
						break;
					default:
						errors ++;
						break;
				}       // switch
			}
		}
		int total( passed + failures + skipped + exceptions + warnings + terminations + errors );
		int totalFail( failures + exceptions + warnings );
		int totalError( errors + terminations );

		*_stream << "<testsuites tests=\"" << total << "\" failures=\"" << totalFail << "\" disabled=\"0\" errors=\"" << totalError << "\" time=\"0\" name=\"AllTests\">" << std::endl;
		for ( TestGroups::const_iterator tgi = _allTests.begin(); tgi != _allTests.end(); ++ tgi ) {
			/* per-group statistics */
			passed = 0;               // passed in single group
			exceptions = 0;           // exceptions in single group
			failures = 0;             // failures in single group
			skipped = 0;              // skipped in single group
			terminations = 0;         // terminations in single group
			warnings = 0;             // warnings in single group
			errors = 0;               // errors in single group

			// output is written to string stream buffer, because JUnit format <testsuite> tag
			// contains statistics, which aren't known yet
			std::ostringstream out;

			// iterate over all test cases in the current test group
			const TestResults&results = tgi->second;
			for ( TestResults::const_iterator tri = results.begin(); tri != results.end(); ++ tri ) {
				std::string failure_type;            // string describing the failure type
				std::string failure_msg;             // a string with failure message

				switch ( tri->_result ) {
					case test_result::ok:
						passed ++;
						break;
					case test_result::fail:
						failure_type = "Assertion";
						failure_msg  = "";
						failures ++;
						break;
					case test_result::skipped:
						failure_type = "Skipped";
						failure_msg  = "";
						skipped ++;
						break;
					case test_result::ex:
						failure_type = "Assertion";
						failure_msg  = "Thrown exception: " + tri->_exceptionTypeId + '\n';
						exceptions ++;
						break;
					case test_result::warn:
						failure_type = "Assertion";
						failure_msg  = "Destructor failed.\n";
						warnings ++;
						break;
					case test_result::term:
						failure_type = "Error";
						failure_msg  = "Test application terminated abnormally.\n";
						terminations ++;
						break;
					case test_result::ex_ctor:
						failure_type = "Assertion";
						failure_msg  = "Constructor has thrown an exception: " + tri->_exceptionTypeId + ".\n";
						exceptions ++;
						break;
					case test_result::rethrown:
						failure_type = "Assertion";
						failure_msg  = "Child failed.\n";
						failures ++;
						break;
					case test_result::setup:
						failure_type = "Error";
						failure_msg  = "Invalid runtime configuration.\n";
						errors ++;
						break;
					default:
						failure_type = "Error";
						failure_msg  = "Unknown test status, this should have never happened. "
						               "You may just have found a bug in TUT, please report it immediately.\n";
						errors ++;
						break;
				}       // switch

#if defined(TUT_USE_POSIX)
				out << xml_build_testcase( *tri, failure_type, failure_msg, tri->pid ) << std::endl;
#else
				out << xml_build_testcase( *tri, failure_type, failure_msg ) << std::endl;
#endif
			}     // iterate over all test cases

			// calculate per-group statistics
			int stat_errors = terminations + errors;
			int stat_failures = failures + warnings + exceptions;
			int stat_all = stat_errors + stat_failures + passed + skipped;

			*_stream << xml_build_testsuite( stat_errors, stat_failures, stat_all, (*tgi).first /* name */, out.str() /* testcases */ ) << std::endl;
		}   // iterate over all test groups

		*_stream << "</testsuites>" << std::endl;
	}

	/**
	 * \brief Returns true, if all tests passed
	 */
	virtual bool all_ok() const {
		return ( (_terminationsCount + _failuresCount + _skippedCount + _warningsCount + _exceptionsCount) == 0);
	}
};

}

#endif


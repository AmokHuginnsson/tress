#ifndef TUT_REPORTER_CPPUNIT
#define TUT_REPORTER_CPPUNIT

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <memory>

#include "tut.hpp"

namespace tut {
/**
 * CppUnit TUT reporter
 */
class reporter_cppunit : public tut::callback {
	std::vector<tut::test_result> _failedTests;
	std::vector<tut::test_result> _passedTests;
	const std::string _filename;
	std::unique_ptr<std::ostream> _stream;

	reporter_cppunit( const reporter_cppunit& );
	reporter_cppunit&operator = ( const reporter_cppunit& );

public:
	explicit reporter_cppunit( const std::string&filename = "testResult.xml" )
		: _failedTests()
		, _passedTests()
		, _filename( filename )
		, _stream( new std::ofstream( _filename.c_str() ) ) {
		if ( !_stream->good() ) {
			throw tut_error( "Cannot open output file `" + _filename + "`" );
		}
	}

	explicit reporter_cppunit( std::ostream&stream )
		: _failedTests()
		, _passedTests()
		, _filename()
		, _stream( &stream ) {
	}

	~reporter_cppunit() {
		if ( _filename.empty() ) {
			_stream.release();
		}
	}

	void run_started( int, int ) {
		_failedTests.clear();
		_passedTests.clear();
	}

	void test_completed( const tut::test_result& tr ) {
		if ( tr._result == test_result::ok ) {
			_passedTests.push_back( tr );
		} else {
			_failedTests.push_back( tr );
		}
	}

	virtual void group_started( const std::string& /*name */, int /* total test count for group */ ) {
	}
	virtual void group_completed( group_base const* ) {
	}
	virtual void test_started( std::string const&, int /*n */, std::string const& ) {
	}
	virtual int fail_count( void ) const {
		return ( static_cast<int>( _failedTests.size() ) );
	}

	void run_completed() {
		int errors = 0;
		int failures = 0;
		std::string failure_type;
		std::string failure_msg;

		*_stream << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\" ?>" << std::endl
		         << "<TestRun>" << std::endl;

		if ( _failedTests.size() > 0 ) {
			*_stream << "  <FailedTests>" << std::endl;

			for ( unsigned int i = 0; i < _failedTests.size(); i ++ ) {
				switch ( _failedTests[ i ]._result ) {
					case test_result::fail:
						failure_type = "Assertion";
						failure_msg  = "";
						failures ++;
						break;
					case test_result::ex:
						failure_type = "Assertion";
						failure_msg  = "Thrown exception: " + _failedTests[ i ]._exceptionTypeId + '\n';
						failures ++;
						break;
					case test_result::warn:
						failure_type = "Assertion";
						failure_msg  = "Destructor failed\n";
						failures ++;
						break;
					case test_result::term:
						failure_type = "Error";
						failure_msg  = "Test application terminated abnormally\n";
						errors ++;
						break;
					case test_result::ex_ctor:
						failure_type = "Error";
						failure_msg  = "Constructor has thrown an exception: " + _failedTests[ i ]._exceptionTypeId + '\n';
						errors ++;
						break;
					case test_result::rethrown:
						failure_type = "Assertion";
						failure_msg  = "Child failed\n";
						failures ++;
						break;
					default:           // ok, skipped, dummy
						failure_type = "Error";
						failure_msg  = "Unknown test status, this should have never happened. "
						               "You may just have found a bug in TUT, please report it immediately.\n";
						errors ++;
						break;
				}

				test_result& tr( _failedTests[ i ] );
				*_stream << "    <FailedTest id=\"" << tr._testNo << "\">" << std::endl
				         << "      <Name>" << ( tr._group ? encode( tr._group->get_name() ) : "no such group" ) + "::" + encode( tr._name ) << "</Name>" << std::endl
				         << "      <FailureType>" << failure_type << "</FailureType>" << std::endl
				         << "      <Location>" << std::endl
				         << "        <File>" << tr._file << "</File>" << std::endl
				         << "        <Line>" << tr._line << "</Line>" << std::endl
				         << "      </Location>" << std::endl
				         << "      <Message>" << encode( failure_msg + tr._message ) << "</Message>" << std::endl
				         << "    </FailedTest>" << std::endl;
			}

			*_stream << "  </FailedTests>" << std::endl;
		}

		/* *********************** passed tests ***************************** */
		if ( _passedTests.size() > 0 ) {
			*_stream << "  <SuccessfulTests>" << std::endl;

			for ( unsigned int i = 0; i < _passedTests.size(); i ++ ) {
				test_result& tr( _passedTests[ i ] );
				*_stream << "    <Test id=\"" << tr._testNo << "\">" << std::endl
				         << "      <Name>" << encode( tr._group->get_name() ) + "::" + encode( tr._name ) << "</Name>" << std::endl
				         << "    </Test>" << std::endl;
			}

			*_stream << "  </SuccessfulTests>" << std::endl;
		}

		/* *********************** statistics ***************************** */
		*_stream << "  <Statistics>" << std::endl
		         << "    <Tests>" << (_failedTests.size() + _passedTests.size() ) << "</Tests>" << std::endl
		         << "    <FailuresTotal>" << _failedTests.size() << "</FailuresTotal>" << std::endl
		         << "    <Errors>" << errors << "</Errors>" << std::endl
		         << "    <Failures>" << failures << "</Failures>" << std::endl
		         << "  </Statistics>" << std::endl;

		/* *********************** footer ***************************** */
		*_stream << "</TestRun>" << std::endl;
	}

	virtual bool all_ok() const {
		return ( _failedTests.empty() ) ;
	}

	/**
	 * \brief Encodes text to XML
	 * XML-reserved characters (e.g. "<") are encoded according to specification
	 * @param text text to be encoded
	 * @return encoded string
	 */
	static std::string encode( const std::string& text ) {
		std::string out;

		for ( unsigned int i = 0; i < text.length(); ++ i ) {
			char c = text[ i ];
			switch ( c ) {
				case '<':
					out += "&lt;";
					break;
				case '>':
					out += "&gt;";
					break;
				case '&':
					out += "&amp;";
					break;
				case '\'':
					out += "&apos;";
					break;
				case '"':
					out += "&quot;";
					break;
				default:
					out += c;
			}
		}

		return ( out) ;
	}
};

}

#endif


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
	std::vector<tut::test_result> failed_tests_;
	std::vector<tut::test_result> passed_tests_;
	const std::string filename_;
	std::auto_ptr<std::ostream> stream_;

	reporter_cppunit( const reporter_cppunit& );
	reporter_cppunit&operator = ( const reporter_cppunit& );

public:
	explicit reporter_cppunit( const std::string&filename = "testResult.xml" )
		: failed_tests_(),
		passed_tests_(),
		filename_( filename ),
		stream_( new std::ofstream( filename_.c_str() ) ) {
		if ( !stream_->good() ) {
			throw tut_error( "Cannot open output file `" + filename_ + "`" );
		}
	}

	explicit reporter_cppunit( std::ostream&stream )
		: failed_tests_(),
		passed_tests_(),
		filename_(),
		stream_( &stream )
		  {}

	~reporter_cppunit() {
		if ( filename_.empty() ) {
			stream_.release();
		}
	}

	void run_started( int, int ) {
		failed_tests_.clear();
		passed_tests_.clear();
	}

	void test_completed( const tut::test_result& tr ) {
		if ( tr._result == test_result::ok ) {
			passed_tests_.push_back( tr );
		} else {
			failed_tests_.push_back( tr );
		}
	}

	virtual void group_started( const std::string& /*name */, int /* total test count for group */ ) {
	}
	virtual void group_completed( group_base const* ) {
	}
	virtual void test_started( char const*, int /*n */, char const*, bool ) {
	}
	virtual int fail_count( void ) const {
		return ( static_cast<int>( failed_tests_.size() ) );
	}

	void run_completed() {
		int errors = 0;
		int failures = 0;
		std::string failure_type;
		std::string failure_msg;

		*stream_ << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\" ?>" << std::endl
		         << "<TestRun>" << std::endl;

		if ( failed_tests_.size() > 0 ) {
			*stream_ << "  <FailedTests>" << std::endl;

			for ( unsigned int i = 0; i < failed_tests_.size(); i ++ ) {
				switch ( failed_tests_[ i ]._result ) {
					case test_result::fail:
						failure_type = "Assertion";
						failure_msg  = "";
						failures ++;
						break;
					case test_result::ex:
						failure_type = "Assertion";
						failure_msg  = "Thrown exception: " + failed_tests_[ i ]._exceptionTypeId + '\n';
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
						failure_msg  = "Constructor has thrown an exception: " + failed_tests_[ i ]._exceptionTypeId + '\n';
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

				test_result& tr( failed_tests_[ i ] );
				*stream_ << "    <FailedTest id=\"" << tr._testNo << "\">" << std::endl
				         << "      <Name>" << ( tr._group ? encode( tr._group->get_name() ) : "no such group" ) + "::" + encode( tr._name ) << "</Name>" << std::endl
				         << "      <FailureType>" << failure_type << "</FailureType>" << std::endl
				         << "      <Location>" << std::endl
				         << "        <File>" << tr._file << "</File>" << std::endl
				         << "        <Line>" << tr._line << "</Line>" << std::endl
				         << "      </Location>" << std::endl
				         << "      <Message>" << encode( failure_msg + tr._message ) << "</Message>" << std::endl
				         << "    </FailedTest>" << std::endl;
			}

			*stream_ << "  </FailedTests>" << std::endl;
		}

		/* *********************** passed tests ***************************** */
		if ( passed_tests_.size() > 0 ) {
			*stream_ << "  <SuccessfulTests>" << std::endl;

			for ( unsigned int i = 0; i < passed_tests_.size(); i ++ ) {
				test_result& tr( passed_tests_[ i ] );
				*stream_ << "    <Test id=\"" << tr._testNo << "\">" << std::endl
				         << "      <Name>" << encode( tr._group->get_name() ) + "::" + encode( tr._name ) << "</Name>" << std::endl
				         << "    </Test>" << std::endl;
			}

			*stream_ << "  </SuccessfulTests>" << std::endl;
		}

		/* *********************** statistics ***************************** */
		*stream_ << "  <Statistics>" << std::endl
		         << "    <Tests>" << (failed_tests_.size() + passed_tests_.size() ) << "</Tests>" << std::endl
		         << "    <FailuresTotal>" << failed_tests_.size() << "</FailuresTotal>" << std::endl
		         << "    <Errors>" << errors << "</Errors>" << std::endl
		         << "    <Failures>" << failures << "</Failures>" << std::endl
		         << "  </Statistics>" << std::endl;

		/* *********************** footer ***************************** */
		*stream_ << "</TestRun>" << std::endl;
	}

	virtual bool all_ok() const {
		return ( failed_tests_.empty() ) ;
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


#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#ifdef __MSVCXX__
#include <windows.h>
inline struct tm *localtime_r( const time_t *timep, struct tm *result ) {
	localtime_s( result, timep );
	return ( result );
}
#endif

using namespace std;

namespace {

string now( void ) {
	char buf[256];
	time_t t( time( NULL ) );
	tm b;
	localtime_r( &t, &b );
	::strftime( buf, sizeof ( buf ) - 1, "%a, %d %b %Y %H:%M:%S %z", &b );
	return ( buf );
}

}

int main( int argc_, char** argv_ ) {
#ifdef __MSVCXX__
	/* DebugBreak(); */
#endif
	int ret( 0 );
	try {
		string const path( "./out/hpipedchild.log" );
		ofstream log( path.c_str() );
		if ( ! log ) {
			throw runtime_error( "Cannot open file: " + path );
		}

		log << now() << ": child start ..." << endl;
		string line;

		int i( 0 );
		int limit( 1 );
		if ( argc_ > 1 ) {
			limit = stoi( argv_[1] );
		}
		while ( getline( cin, line ).good() ) {
			log << now() << ": read input: " << line << endl;
			string output;
			if ( line == "out" ) {
				cout << ( output = "hello-OUT" ) << endl;
			} else if ( line == "err" ) {
				cerr << ( output = "hello-ERR" ) << endl;
			} else {
				cout << ( output = "error" ) << endl;
				cerr << output << endl;
			}
			log << now() << ": written output [" << output << "]" << endl;
			++ i;
			if ( i >= limit ) {
				break;
			}
		}
		log << now() << ": exiting" << endl;
	} catch ( exception const& e ) {
		cerr << "Exception caught: " << e.what() << endl;
		ret = 1;
	}
	return ( ret );
}


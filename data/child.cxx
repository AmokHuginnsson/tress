#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#ifdef __MSVCXX__
#include <windows.h>
#endif

using namespace std;

string now( void )
	{
	char buf[256];
	time_t t( time( NULL ) );
	tm* b( localtime( &t ) );
	::strftime( buf, sizeof ( buf ) - 1, "%a, %d %b %Y %H:%M:%S %z", b );
	return ( buf );
	}

int main( int, char** )
	{
#ifdef __MSVCXX__
	// DebugBreak();
#endif
	ofstream log( ".\\out\\hpipedchild.log" );
	log << now() << ": child start ..." << endl;
	string line;
	cin >> line;
	log << now() << ": read input: " << line << endl;
	if ( line == "out" )
		cout << "hello-OUT" << endl;
	else if ( line == "err" )
		cerr << "hello-ERR" << endl;
	else
		{
		cout << "error" <<endl;
		cerr << "error" <<endl;
		}
	log << now() << ": written output ..." << endl;
	log << now() << ": exiting" << endl;
	return ( 0 );
	}
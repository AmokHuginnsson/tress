#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main( int, char** ) {
	cout << "Content-Type: text/plain; charset=UTF-8\r\n\r\n" << flush;
	cout << "CWD: " << get_current_dir_name() << endl;
	char const codePath[] = "../cgi.cxx";
	cout << "code-path: " << codePath << endl;
	cout << "\n";
	ifstream codeStream( codePath );
	string line;
	while ( getline( codeStream, line ).good() ) {
		cout << line << endl;
	}
	/* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. *//* This is an abnormally long line which total length shall exceed 4096 bytes. */
	return ( 0 );
}


extern "C" {

int tcgetattr( int, struct termios* );
int tcgetattr( int, struct termios* ) {
	return ( 0 );
}

int tcsetattr( int, int, const struct termios* );
int tcsetattr( int, int, const struct termios* ) {
	return ( 0 );
}

}


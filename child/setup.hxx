/* Read tress/LICENSE.md file for copyright and licensing information. */

#ifndef CHILD_SETUP_HXX_INCLUDED
#define CHILD_SETUP_HXX_INCLUDED

#include <yaal/hcore/hstring.hxx>

#include "config.hxx"

namespace child {

struct OSetup {
	bool _quiet;			/* --quiet, --silent */
	bool _verbose;		/* --verbose */
	char* _programName;
	yaal::hcore::HString _logPath;
	int _exitStatus;
	yaal::hcore::HString _terminate;
	yaal::hcore::HString _script;
	/* self-sufficient */
	OSetup( void )
		: _quiet( false ), _verbose( false ),
		_programName( NULL ), _logPath(), _exitStatus( 0 ),
		_terminate(), _script() {}
	void test_setup( void );
private:
	OSetup( OSetup const& );
	OSetup& operator = ( OSetup const& );
};

extern OSetup setup;

}

#endif /* CHILD_SETUP_HXX_INCLUDED */


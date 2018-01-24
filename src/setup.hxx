/* Read tress/LICENSE.md file for copyright and licensing information. */

#ifndef TRESS_SETUP_HXX_INCLUDED
#define TRESS_SETUP_HXX_INCLUDED

#include <yaal/hcore/hstring.hxx>
#include <yaal/hcore/duration.hxx>
#include <yaal/hcore/hdeque.hxx>

#include "config.hxx"

namespace tress {

struct OSetup {
	OSetup( void );
	typedef yaal::hcore::HDeque<yaal::hcore::HString> group_names_t;
	typedef yaal::hcore::HDeque<yaal::hcore::HString> set_definitions_t;
	bool _quiet;			/* --quiet, --silent */
	bool _verbose;		/* --verbose */
	bool _debug;      /* --debug */
	bool _listGroups;
	bool _restartable;
	bool _exit;
	bool _fancy;
	bool _color;
	bool _forceRunAll;
	bool _selftest;
	int _testNumber;
	int _jobs;
	yaal::hcore::time::duration_t _timeConstraint;
	int _argc;
	char const* const* _argv;
	char* _programName;
	yaal::hcore::HString _logPath;
	group_names_t _testGroups;
	set_definitions_t _testSets;
	yaal::hcore::HString _testGroupPattern;
	yaal::hcore::HString _testGroupListFilePath;
	yaal::hcore::HString _reporter;
	yaal::hcore::HString _errorLine;
	int _clockQualityMultiplier;
	static int const DEFAULT_JOB_COUNT = 1;
	static int long const DEFAULT_TIME_CONSTRAINT = 0;
	static int const DEFAULT_CLOCK_QUALITY_MULTIPLIER = 1;
	void test_setup( void );
private:
	OSetup( OSetup const& );
	OSetup& operator = ( OSetup const& );
};

extern OSetup setup;

}

#endif /* TRESS_SETUP_HXX_INCLUDED */

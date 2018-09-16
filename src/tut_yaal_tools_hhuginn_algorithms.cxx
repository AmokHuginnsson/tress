/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_algorithms : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_algorithms, "yaal::tools::HHuginn.Algorithms" );

TUT_UNIT_TEST( "slice" )
	ENSURE_EQUALS(
		"Algorithms.slice failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"return(("
			"	algo.materialize(algo.slice(l,2,7,2), list),"
			"	algo.materialize(algo.slice(l,2,6,2), list),"
			"	algo.materialize(algo.slice(l,2,5), list),"
			"	algo.materialize(algo.slice(l,2), list),"
			"	algo.materialize(algo.slice(l,2,2), list),"
			"	algo.materialize(algo.slice(l,2,2,0), list),"
			"	algo.materialize(algo.slice([],100), list)"
			"));"
			"}"
		),
		"([5, 11, 17], [5, 11], [5, 7, 11], [2, 3], [], [], [])"
	);
	ENSURE_EQUALS(
		"Algorithms.slice on invalid (FROM > TO) succeeded",
		execute_except(
			"import Algorithms as algo;"
			"main(){algo.slice([],1,0);}"
		),
		"*anonymous stream*:1:44: Invalid slice."
	);
	ENSURE_EQUALS(
		"Algorithms.slice on invalid (FROM < 0) succeeded",
		execute_except(
			"import Algorithms as algo;"
			"main(){algo.slice([],-1,0);}"
		),
		"*anonymous stream*:1:44: Invalid slice."
	);
	ENSURE_EQUALS(
		"Algorithms.slice on invalid (STEP < 0) succeeded",
		execute_except(
			"import Algorithms as algo;"
			"main(){algo.slice([],0,-1);}"
		),
		"*anonymous stream*:1:44: Invalid slice."
	);
	ENSURE_EQUALS(
		"Algorithms.slice on invalid (STEP == 0 && STOP > FROM) succeeded",
		execute_except(
			"import Algorithms as algo;"
			"main(){algo.slice([],0,1,0);}"
		),
		"*anonymous stream*:1:44: Invalid slice."
	);
TUT_TEARDOWN()

}


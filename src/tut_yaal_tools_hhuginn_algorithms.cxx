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

TUT_UNIT_TEST( "iterator" )
	ENSURE_EQUALS(
		"Algorithms.iterator failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"i = algo.iterator(l);"
			"return(algo.materialize(algo.zip(i,i), list));"
			"}"
		),
		"[(2, 3), (5, 7), (11, 13), (17, 19)]"
	);
	ENSURE_EQUALS(
		"Algorithms.iterator failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"i = algo.iterator(l);"
			"res = [];"
			"while(i.is_valid()) {"
			"res.push(i.value());"
			"i.next();"
			"}"
			"return(res);"
			"}"
		),
		"[2, 3, 5, 7, 11, 13, 17, 19]"
	);
	ENSURE_EQUALS(
		"Algorithms.iterator failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l=[2,3,5];\n"
			"i = algo.iterator(l);\n"
			"ci = copy( i );\n"
			"l.push(7);\n"
			"res = [];"
			"res.push( size( i ) );\n"
			"res.push( algo.materialize( i, list ) );\n"
			"res.push( algo.materialize( ci, list ) );\n"
			"return(res);"
			"}"
		),
		"[4, [2, 3, 5, 7], [2, 3, 5]]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "zip" )
	ENSURE_EQUALS(
		"Algorithms.zip failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l1=[2,3,5,7,11,13,17,19];"
			"l2=[2,4,8,16,32,64,128,256];"
			"z=algo.zip(l1,l2);"
			"r = [];"
			"for(x : copy(z)) {"
			"r.push(x);"
			"}"
			"return((r,size(z)));"
			"}"
		),
		"([(2, 2), (3, 4), (5, 8), (7, 16), (11, 32), (13, 64), (17, 128), (19, 256)], 8)"
	);
	ENSURE_EQUALS(
		"Algorithms.zip failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"i=algo.iterator(algo.zip(l));"
			"r = [];"
			"r.push(i.value());"
			"i.is_valid();"
			"r.push(i.value());"
			"return(r);"
			"}"
		),
		"[(2,), (2,)]"
	);
	ENSURE_EQUALS(
		"Algorithms.zip failed",
		execute_except(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5];"
			"i=algo.iterator(l);"
			"i=algo.iterator(algo.zip(i,i));"
			"r = [];"
			"r.push(i.value());"
			"i.next();"
			"r.push(i.value());"
			"return(r);"
			"}"
		),
		"*anonymous stream*:1:142: Getting value from an invalid iterator."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "enumerate" )
	ENSURE_EQUALS(
		"Algorithms.enumerate failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[2,3,5,7,11,13,17,19];"
			"e=algo.enumerate(l,100);"
			"r = [];"
			"for(x : copy(e)) {"
			"r.push(x);"
			"}"
			"return((r,size(e)));"
			"}"
		),
		"([(100, 2), (101, 3), (102, 5), (103, 7), (104, 11), (105, 13), (106, 17), (107, 19)], 8)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "map" )
	ENSURE_EQUALS(
		"Algorithms.map (fun) failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[];"
			"m=algo.map([3, 17, 4],@(x){x*x;});"
			"for(x : copy(m)) {"
			"l.push(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[9, 289, 16], 3]"
	);
	ENSURE_EQUALS(
		"Algorithms.map (method) failed",
		execute(
			"import Algorithms as algo;"
			"class M {\n"
			"do(x){\n"
			"return(x*x);\n"
			"}\n"
			"}\n"
			"main(){"
			"l=[];"
			"m=algo.map([3, 17, 4],M().do);"
			"for(x : copy(m)) {"
			"l.push(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[9, 289, 16], 3]"
	);
	ENSURE_EQUALS(
		"Algorithms.map (ubound method) failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[\"ala\",\"ma\",\"kota\"];"
			"m=algo.map(l,string.to_upper);"
			"l=[];\n"
			"for(x : copy(m)) {"
			"l.push(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[\"ALA\", \"MA\", \"KOTA\"], 3]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "range" )
	ENSURE_EQUALS(
		"Algorithms.range failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"s=\"\";"
			"r = algo.range(3, 17, 4);"
			"for(x : copy(r)) {"
			"s=s+\":\"+string(x);"
			"}"
			"return([s,size(r)]);"
			"}"
		),
		"[\":3:7:11:15\", 4]"
	);
	ENSURE_EQUALS(
		"Algorithms.range invalid succeeded",
		execute_except(
			"import Algorithms as algo;"
			"main(){"
			"algo.range(1,2,-1);"
			"}"
		),
		"*anonymous stream*:1:44: Invalid range."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "materialize" )
	ENSURE_EQUALS(
		"Algorithms.materialize (to tuple) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),tuple));\n"
			"}"
		),
		"(3, 7, 11, 15)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to list) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),list));\n"
			"}"
		),
		"[3, 7, 11, 15]"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to deque) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),deque));\n"
			"}"
		),
		"deque(3, 7, 11, 15)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to order) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),order));\n"
			"}"
		),
		"order(3, 7, 11, 15)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of non uniform keys (to order) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([0,1.],order);\n"
			"}"
		),
		"*anonymous stream*:3:17: Invalid key type: a `real`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize to order did not set key type",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"o = algo.materialize([0],order);\n"
			"o.insert(1.);\n"
			"}"
		),
		"*anonymous stream*:4:9: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to heap) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),heap));\n"
			"}"
		),
		"heap(15, 11, 7, 3)"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of non uniform keys (to heap) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([0,1.],heap);\n"
			"}"
		),
		"*anonymous stream*:3:17: Invalid key type: a `real`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize to heap did not set key type",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"h = algo.materialize([0],heap);\n"
			"h.push(1.);\n"
			"}"
		),
		"*anonymous stream*:4:7: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to set) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),set));\n"
			"}"
		),
		"{15, 3, 7, 11}"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to dict) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize([(0,1),(2,3),(4,5)],dict));\n"
			"}"
		),
		"[0: 1, 2: 3, 4: 5]"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of non tuple (to dict) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([0],dict);\n"
			"}"
		),
		"*anonymous stream*:3:17: Each value materialized into a `dict` must be a `tuple` not an `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of wrong tuple size (to dict) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([(0,0,0)],dict);\n"
			"}"
		),
		"*anonymous stream*:3:17: Each `tuple` materialized into a `dict` must be a key-value pair, i.e. contain exactly two elements."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of non uniform keys (to dict) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([(0,0),(1.,0)],dict);\n"
			"}"
		),
		"*anonymous stream*:3:17: Invalid key type: a `real`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize to dict did not set key type",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d = algo.materialize([(0,0)],dict);\n"
			"d[1.];\n"
			"}"
		),
		"*anonymous stream*:4:2: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to lookup) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize([(0,1),(2,3),(4,5)],lookup));\n"
			"}"
		),
		"{0: 1, 4: 5, 2: 3}"
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of non tuple (to lookup) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([0],lookup);\n"
			"}"
		),
		"*anonymous stream*:3:17: Each value materialized into a `lookup` must be a `tuple` not an `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize of wrong tuple size (to lookup) succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([(0,0,0)],lookup);\n"
			"}"
		),
		"*anonymous stream*:3:17: Each `tuple` materialized into a `lookup` must be a key-value pair, i.e. contain exactly two elements."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize on invalid succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.materialize([],integer);\n"
			"}"
		),
		"*anonymous stream*:3:17: Invalid materialized type: `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to string) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.reversed(\"Huginn\"),string));\n"
			"}"
		),
		"\"nniguH\""
	);
	ENSURE_EQUALS(
		"Algorithms.materialize (to string) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(['a','b','c',0],string));\n"
			"}"
		),
		"*anonymous stream*:3:24: A non-`character` type value materialized into a `string`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "reduce" )
	ENSURE_EQUALS(
		"Algorithms.reduce (function) failed",
		execute(
			"import Algorithms as algo;\n"
			"s(x,y){\n"
			"return(x+y);\n"
			"}\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),s));\n"
			"}"
		),
		"36"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (bound method) failed",
		execute(
			"import Algorithms as algo;\n"
			"class R {\n"
			"do(x,y){\n"
			"return(x+y);\n"
			"}\n"
			"}\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),R().do));\n"
			"}"
		),
		"36"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (unbound method) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),list.push,[]));\n"
			"}"
		),
		"[3, 7, 11, 15]"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (lambda method) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.reduce(algo.range(3, 17, 4),@(x,y){x+y;}));\n"
			"}"
		),
		"36"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce (functor) failed",
		execute(
			"import Algorithms as algo;\n"
			"class S{call(x,y){x+y;}}\n"
			"main(){\n"
			"s = S();\n"
			"return(algo.reduce(algo.range(3, 17, 4),s));\n"
			"}"
		),
		"36"
	);
	ENSURE_EQUALS(
		"Algorithms.reduce on empty succeeded",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"algo.reduce([],@(x,y){x+y;});\n"
			"}"
		),
		"*anonymous stream*:3:12: reduce() on empty."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "filter" )
	ENSURE_EQUALS(
		"Algorithms.filter (function) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"f=algo.filter(algo.range(3, 44, 4),@(x){x%3==0;});\n"
			"return(size(f));\n"
			"}"
		),
		"*anonymous stream*:4:12: Getting size of `Filter` is an invalid operation."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (invalid function) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),@(x){x;}),list));\n"
			"}"
		),
		"*anonymous stream*:3:24: Filter function returned wrong type, expected `boolean` got: `integer`."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (function) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),@(x){x%3==0;}),list));\n"
			"}"
		),
		"[3, 15, 27, 39]"
	);
	ENSURE_EQUALS(
		"Algorithms.filter (method) failed",
		execute(
			"import Algorithms as algo;\n"
			"class F {\n"
			"do(x){\n"
			"return(x%3==0);\n"
			"}\n"
			"}\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),F().do),list));\n"
			"}"
		),
		"[3, 15, 27, 39]"
	);
	ENSURE_EQUALS(
		"Algorithms.filter (invalid bound method) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(algo.range(3, 44, 4),[].push),list));\n"
			"}"
		),
		"*anonymous stream*:3:24: Filter functor returned wrong type, expected `boolean` got: `list`."
	);
	ENSURE_EQUALS(
		"Algorithms.filter (unbound method) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"q = \"a1b2c3d4efgh78iop9zzz\";\n"
			"f = algo.filter(q,character.is_digit);\n"
			"F = copy(f);\n"
			"q += \"0\";\n"
			"return(algo.reduce(algo.materialize(f,list)+algo.materialize(F,list), @(x,y){x+string(y);},\"\"));\n"
			"}"
		),
		"\"123478901234789\""
	);
	ENSURE_EQUALS(
		"Algorithms.filter (invalid unbound method) failed",
		execute_except(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.filter(['a','b','c'],character.to_upper),list));\n"
			"}"
		),
		"*anonymous stream*:3:24: Filter functor returned wrong type, expected `boolean` got: `character`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "sorted" )
	ENSURE_EQUALS(
		"Algorithms.sorted (tuple) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"t=(2,7,3,9,0,-5);\n"
			"return(algo.sorted(t));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (list) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l=[2,7,3,9,0,-5];\n"
			"return(algo.sorted(l));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (deque) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d=deque(2,7,3,9,0,-5);\n"
			"return(algo.sorted(d));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (set) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s=set(2,7,3,9,0,-5);\n"
			"return(algo.sorted(s));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (order) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"o=order(2,7,3,9,0,-5);\n"
			"return(algo.sorted(o));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (dict) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d=[2:0,7:0,3:0,9:0,0:0,-5:0];\n"
			"return(algo.sorted(d));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (lookup) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l={2:0,7:0,3:0,9:0,0:0,-5:0};\n"
			"return(algo.sorted(l));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (heap) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"h=heap(2,5,1,8,3);\n"
			"return(algo.sorted(h));\n"
			"}"
		),
		"[1, 2, 3, 5, 8]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (key retr func) failed",
		execute(
			"import Algorithms as algo;\n"
			"class Pair {\n"
			"_first = none;\n"
			"_second = none;\n"
			"constructor( first_, second_ ) {\n"
			"_first = first_;\n"
			"_second = second_;\n"
			"}\n"
			"to_string() {\n"
			"return(\"{{{},{}}}\".format(_first,_second));\n"
			"}\n"
			"}\n"
			"main(){\n"
			"l=[Pair(2,9),Pair(7,3),Pair(3,-1),Pair(9,4),Pair(0,2),Pair(-5,7)];\n"
			"sf = algo.materialize(algo.map(algo.sorted(l, @(x){x._first;}),string),list);\n"
			"ss = algo.materialize(algo.map(algo.sorted(l, @(x){x._second;}),string),list);\n"
			"return([sf,ss]);\n"
			"}"
		),
		"[[\"{-5,7}\", \"{0,2}\", \"{2,9}\", \"{3,-1}\", \"{7,3}\", \"{9,4}\"], [\"{3,-1}\", \"{0,2}\", \"{7,3}\", \"{9,4}\", \"{-5,7}\", \"{2,9}\"]]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (iterable) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"i=algo.map([2,7,3,9,0,-5],@(x){x;});\n"
			"return(algo.sorted(i));\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (string) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s=\"502397\";"
			"return(algo.sorted(s));\n"
			"}"
		),
		"['0', '2', '3', '5', '7', '9']"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "max" )
	ENSURE_EQUALS(
		"Algorithms.max failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.max(77, 7, 39, 57, 80, 16, 72, 70, 87, 33));\n"
			"}"
		),
		"87"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "min" )
	ENSURE_EQUALS(
		"Algorithms.min failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.min(77, 7, 39, 57, 80, 16, 72, 70, 87, 33));\n"
			"}"
		),
		"7"
	);
TUT_TEARDOWN()

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

TUT_UNIT_TEST( "chain" )
	ENSURE_EQUALS(
		"Algorithms.chain failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.sorted(algo.materialize(algo.chain([1,2,3],(4,5,6),{7,8,9}),list)));\n"
			"}"
		),
		"[1, 2, 3, 4, 5, 6, 7, 8, 9]"
	);
	ENSURE_EQUALS(
		"size(Chain) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(size(algo.chain([1,2,3],(4,5,6),{7,8,9})));\n"
			"}"
		),
		"9"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "product" )
	ENSURE_EQUALS(
		"Algorithms.product failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.product([1,2,3],(4,5,6)),list));\n"
			"}"
		),
		"[(1, 4), (1, 5), (1, 6), (2, 4), (2, 5), (2, 6), (3, 4), (3, 5), (3, 6)]"
	);
	ENSURE_EQUALS(
		"size(Product) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(size(algo.product([1,2,3],(4,5,6))));\n"
			"}"
		),
		"9"
	);
TUT_TEARDOWN()

}


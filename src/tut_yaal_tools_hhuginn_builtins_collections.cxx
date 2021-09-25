/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::huginn;
using namespace yaal::tools::executing_parser;
using namespace tress;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_builtins_collections : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_builtins_collections, "yaal::tools::HHuginn,builtins.collections" );

TUT_UNIT_TEST( "tuple()" )
	ENSURE_EQUALS(
		"tuple failed (explicit)",
		execute( "main(){x=tuple(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS(
		"tuple failed (literal)",
		execute( "main(){x=(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS( "tuple failed (crazy)", execute( "f(a){return(\"X\"+a+\"X\");}main(){return((f,)[0](\"hi\"));}" ), "\"XhiX\"" );
	ENSURE_EQUALS(
		"list find failed",
		execute(
			"main(){"
			"x=(2,3,2,5,3,2,7);"
			"return((x.find(2),x.find(3),x.find(5),x.find(7),x.find(0),x.find(2,2), x.find(2,3), x.find(2,2,2)));"
			"}"
		),
		"(0, 1, 3, 6, -1, 2, 5, -1)"
	);
	ENSURE_EQUALS(
		"tuple to_string failed",
		execute( "main(){x=tuple(2,3,5,7);return(x);}" ),
		"(2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"tuple append failed",
		execute( "main(){x=(2,3,5,7);x += (4,8,16);return(x);}" ),
		"(2, 3, 5, 7, 4, 8, 16)"
	);
	ENSURE_EQUALS( "tuple reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed((2,3,5,7)),tuple);}" ), "(7, 5, 3, 2)" );
	ENSURE_EQUALS( "tuple size/copy reversed() failed", execute( "import Algorithms as algo;main(){x=algo.reversed((2,3,5,7));(algo.materialize(copy(x),tuple),size(x));}" ), "((7, 5, 3, 2), 4)" );
	ENSURE_EQUALS(
		"tuple equals failed",
		execute(
			"main(){"
			"t1=(1,2,3);"
			"t2=(1,2,3);"
			"t3=(1,2,4);"
			"return((t1==t2,t1==t3));}"
		),
		"(true, false)"
	);
	ENSURE_EQUALS(
		"tuple equals failed",
		execute(
			"main(){"
			"t1=(1,2,3);"
			"t2=(1,2,3);"
			"t3=(1,2,4);"
			"return((t1<t2,t1<t3));}"
		),
		"(false, true)"
	);
	ENSURE_EQUALS(
		"tuple() iterator failed",
		execute( "main(){x=(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"tuple copy failed",
		execute( "main(){s=\"orig\";x=tuple(2,3,s);y=copy(x);s+=\"new\";return((x,y));}" ),
		"((2, 3, \"orignew\"), (2, 3, \"orig\"))"
	);
	ENSURE_EQUALS(
		"tuple hash failed",
		execute( "import Introspection as intro;main(){(intro.hash(()),intro.hash((1,)));}" ),
		"(7, 22)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "list()" )
	ENSURE_EQUALS(
		"list failed (explicit)",
		execute( "main(){x=list(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS(
		"list failed (literal)",
		execute( "main(){x=[\"a\",\"b\",\"c\"];v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS( "list failed (crazy)", execute( "f(a){return(\"X\"+a+\"X\");}main(){return([f][0](\"hi\"));}" ), "\"XhiX\"" );
	ENSURE_EQUALS(
		"list to_string failed",
		execute( "main(){x=list(2,3,5,7);return(x);}" ),
		"[2, 3, 5, 7]"
	);
	ENSURE_EQUALS(
		"list push failed",
		execute( "main(){x=list(2,3,5,7);x.push(0);return(x);}" ),
		"[2, 3, 5, 7, 0]"
	);
	ENSURE_EQUALS(
		"list append failed",
		execute( "main(){x=[2,3,5,7];x.append([4,8,16]).append(deque(20)).append(order(30)).append({40}).append((11,22,33));return(x);}" ),
		"[2, 3, 5, 7, 4, 8, 16, 20, 30, 40, 11, 22, 33]"
	);
	ENSURE_EQUALS(
		"list insert failed",
		execute( "main(){x=[2,3,5,7];x.insert(2, 0).insert(5, -1);return(x);}" ),
		"[2, 3, 0, 5, 7, -1]"
	);
	ENSURE_EQUALS(
		"list insert on invalid position succeeded",
		execute_except( "main(){x=[2,3,5,7];x.insert(5,-1);}" ),
		"*anonymous stream*:1:28: invalid insertion position: 5"
	);
	ENSURE_EQUALS(
		"list erase failed",
		execute( "main(){x=[2,3,2,3,5,2,3,7,2,3];x.erase(3);return(x);}" ),
		"[2, 2, 5, 2, 7, 2]"
	);
	ENSURE_EQUALS(
		"list erase limited by count failed",
		execute( "main(){x=[2,3,2,3,5,2,3,7,2,3];x.erase(3,2);return(x);}" ),
		"[2, 2, 5, 2, 3, 7, 2, 3]"
	);
	ENSURE_EQUALS(
		"list erase with bad count succeeded",
		execute_except( "main(){x=[2,3,2,3,5,2,3,7,2,3];x.erase(3,0);return(x);}" ),
		"*anonymous stream*:1:39: invalid erase count: 0"
	);
	ENSURE_EQUALS(
		"list erase in for",
		execute(
			"main(){\n"
			"l=[2,3,2,3,5,2,3,7,2,3];\n"
			"r = [];"
			"for(e:l){\n"
			"if(e==5){\n"
			"l.erase(3);\n"
			"}\n"
			"r.push(e);\n"
			"}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 3, 2, 3, 5, 2, 7, 2, [2, 2, 5, 2, 7, 2]]"
	);
	ENSURE_EQUALS(
		"list erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l=[2,3,2,3,5,2,3,7,2,3];\n"
			"r = [];"
			"for(e:algo.reversed(l)){\n"
			"if(e==5){\n"
			"l.erase(3);\n"
			"}\n"
			"r.push(e);\n"
			"}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, 2, 7, 3, 2, 5, 2, 2, [2, 2, 5, 2, 7, 2]]"
	);
	ENSURE_EQUALS(
		"list clear in for",
		execute(
			"main(){\n"
			"l=[2,3,2,3,5,2,3,7,2,3];\n"
			"r = [];"
			"for(e:l){\n"
			"if(e==5){\n"
			"l.clear();\n"
			"}\n"
			"r.push(e);\n"
			"}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 3, 2, 3, 5, []]"
	);
	ENSURE_EQUALS(
		"list resize failed",
		execute( "main(){x=[].resize(5,0);x[0]+=1;y=copy(x).resize(3,none);return((x,y));}" ),
		"([1, 0, 0, 0, 0], [1, 0, 0])"
	);
	ENSURE_EQUALS(
		"list resize with invalid size succeeded",
		execute_except( "main(){[].resize(-1,none);}" ),
		"*anonymous stream*:1:17: invalid new size: -1"
	);
	ENSURE_EQUALS(
		"list pop failed",
		execute( "main(){x=list(2,3,5,7);x.pop();return(x);}" ),
		"[2, 3, 5]"
	);
	ENSURE_EQUALS(
		"list sort failed",
		execute(
			"main(){\n"
			"l=[2,7,3,9,0,-5];\n"
			"return(l.sort());\n"
			"}"
		),
		"[-5, 0, 2, 3, 7, 9]"
	);
	ENSURE_EQUALS(
		"list sort (key retr func) failed",
		execute(
			"class Pair {\n"
			"_first = none;\n"
			"_second = none;\n"
			"constructor( first_, second_ ) {\n"
			"_first = first_;\n"
			"_second = second_;\n"
			"}\n"
			"to_string() {\n"
			"return(\"{{{}, {}}}\".format(_first,_second));\n"
			"}\n"
			"}\n"
			"main(){\n"
			"l=[Pair(2,9),Pair(7,3),Pair(3,-1),Pair(9,4),Pair(0,2),Pair(-5,7)];\n"
			"return((copy(l).sort(@(x){x._first;}),l.sort(@(x){x._second;})));\n"
			"}"
		),
		"([{-5, 7}, {0, 2}, {2, 9}, {3, -1}, {7, 3}, {9, 4}], [{3, -1}, {0, 2}, {7, 3}, {9, 4}, {-5, 7}, {2, 9}])"
	);
	ENSURE_EQUALS(
		"list clear failed",
		execute( "main(){x=list(2,3,5,7);x.clear();return(x);}" ),
		"[]"
	);
	ENSURE_EQUALS(
		"list find failed",
		execute(
			"main(){"
			"x=[2,3,2,5,3,2,7];"
			"return([x.find(2),x.find(3),x.find(5),x.find(7),x.find(0),x.find(2,2), x.find(2,3), x.find(2,2,2)]);"
			"}"
		),
		"[0, 1, 3, 6, -1, 2, 5, -1]"
	);
	ENSURE_EQUALS( "list reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed([2,3,5,7]),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "list size/copy reversed() failed", execute( "import Algorithms as algo;main(){x=algo.reversed([2,3,5,7]);algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"list equals failed",
		execute(
			"main(){"
			"l1=[1,2,3];"
			"l2=[1,2,3];"
			"l3=[1,2,4];"
			"return([l1==l2,l1==l3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"list equals failed",
		execute(
			"main(){"
			"l1=[1,2,3];"
			"l2=[1,2,3];"
			"l3=[1,2,4];"
			"return([l1<l2,l1<l3]);}"
		),
		"[false, true]"
	);
	ENSURE_EQUALS(
		"list() iterator failed",
		execute( "main(){x=[2,3,5,7];v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"list copy failed",
		execute( "main(){x=list(2,3,5);y=copy(x);x.push(7);return([x,y]);}" ),
		"[[2, 3, 5, 7], [2, 3, 5]]"
	);
	ENSURE_EQUALS(
		"list hash failed",
		execute( "import Introspection as intro;main(){[intro.hash([]),intro.hash([1])];}" ),
		"[8, 25]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "deque()" )
	ENSURE_EQUALS(
		"deque failed (explicit)",
		execute( "main(){x=deque(\"a\",\"b\",\"c\");v=\"\";v=v+string(size(x));v=v+x[0];v=v+x[1];v=v+x[2];return(v);}" ),
		"\"3abc\""
	);
	ENSURE_EQUALS(
		"deque to_string failed",
		execute( "main(){x=deque(2,3,5,7);return(x);}" ),
		"deque(2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque push failed",
		execute( "main(){x=deque(2,3,5,7);x.push(0);return(x);}" ),
		"deque(2, 3, 5, 7, 0)"
	);
	ENSURE_EQUALS(
		"deque push_front failed",
		execute( "main(){x=deque(2,3,5,7);x.push_front(0);return(x);}" ),
		"deque(0, 2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque pop failed",
		execute( "main(){x=deque(2,3,5,7);x.pop();return(x);}" ),
		"deque(2, 3, 5)"
	);
	ENSURE_EQUALS(
		"deque append failed",
		execute( "main(){x=deque(2,3,5,7);x.append([4,8,16]).append(deque(20)).append(order(30)).append({40}).append((11,22,33));return(x);}" ),
		"deque(2, 3, 5, 7, 4, 8, 16, 20, 30, 40, 11, 22, 33)"
	);
	ENSURE_EQUALS(
		"deque prepend failed",
		execute( "main(){x=deque(2,3,5,7);x.prepend([4,8,16]).prepend(deque(20)).prepend(order(30)).prepend({40}).prepend((11,22,33));return(x);}" ),
		"deque(11, 22, 33, 40, 30, 20, 4, 8, 16, 2, 3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque insert failed",
		execute( "main(){x=deque(2,3,5,7);x.insert(2, 0).insert(5,-1);return(x);}" ),
		"deque(2, 3, 0, 5, 7, -1)"
	);
	ENSURE_EQUALS(
		"deque insert on invalid position succeeded",
		execute_except( "main(){x=deque(2,3,5,7);x.insert(5,-1);}" ),
		"*anonymous stream*:1:33: invalid insertion position: 5"
	);
	ENSURE_EQUALS(
		"deque erase failed",
		execute( "main(){x=deque(2,3,2,3,5,2,3,7,2,3);x.erase(3);return(x);}" ),
		"deque(2, 2, 5, 2, 7, 2)"
	);
	ENSURE_EQUALS(
		"deque erase limited by count failed",
		execute( "main(){x=deque(2,3,2,3,5,2,3,7,2,3);x.erase(3,2);return(x);}" ),
		"deque(2, 2, 5, 2, 3, 7, 2, 3)"
	);
	ENSURE_EQUALS(
		"deque erase with bad count succeeded",
		execute_except( "main(){x=deque(2,3,2,3,5,2,3,7,2,3);x.erase(3,0);return(x);}" ),
		"*anonymous stream*:1:44: invalid erase count: 0"
	);
	ENSURE_EQUALS(
		"deque pop_front failed",
		execute( "main(){x=deque(2,3,5,7);x.pop_front();return(x);}" ),
		"deque(3, 5, 7)"
	);
	ENSURE_EQUALS(
		"deque clear failed",
		execute( "main(){x=deque(2,3,5,7);x.clear();return(x);}" ),
		"deque()"
	);
	ENSURE_EQUALS(
		"deque find failed",
		execute(
			"main(){"
			"x=deque(2,3,2,5,3,2,7);"
			"return(deque(x.find(2),x.find(3),x.find(5),x.find(7),x.find(0),x.find(2,2), x.find(2,3), x.find(2,2,2)));"
			"}"
		),
		"deque(0, 1, 3, 6, -1, 2, 5, -1)"
	);
	ENSURE_EQUALS( "deque reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed(deque(2,3,5,7)),deque);}" ), "deque(7, 5, 3, 2)" );
	ENSURE_EQUALS( "deque reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed(deque(2,3,5,7));algo.materialize(copy(x),deque).push(size(x));}" ), "deque(7, 5, 3, 2, 4)" );
	ENSURE_EQUALS(
		"deque equals failed",
		execute(
			"main(){"
			"d1=deque(1,2,3);"
			"d2=deque(1,2,3);"
			"d3=deque(1,2,4);"
			"return([d1==d2,d1==d3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"deque equals failed",
		execute(
			"main(){"
			"d1=deque(1,2,3);"
			"d2=deque(1,2,3);"
			"d3=deque(1,2,4);"
			"return([d1<d2,d1<d3]);}"
		),
		"[false, true]"
	);
	ENSURE_EQUALS(
		"deque() iterator failed",
		execute( "main(){x=deque(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"deque copy failed",
		execute( "main(){x=deque(2,3,5);y=copy(x);x.push_front(7);return([x,y]);}" ),
		"[deque(7, 2, 3, 5), deque(2, 3, 5)]"
	);
	ENSURE_EQUALS(
		"deque hash failed",
		execute( "import Introspection as intro;main(){[intro.hash(deque()),intro.hash(deque(1))];}" ),
		"[9, 28]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "dict()" )
	ENSURE_EQUALS(
		"dict() iterator failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];v=\"\";for(e:x){v=v+e;v=v+string(x[e]);}return(v);}" ),
		"\"Ala0kota.2ma1\""
	);
	ENSURE_EQUALS(
		"dict() failed (explicit)",
		execute( "main(){x=dict();x[\"Ala\"]=0;x[\"ma\"]=1;x[\"kota.\"]=2;return(x);}" ),
		"[\"Ala\": 0, \"kota.\": 2, \"ma\": 1]"
	);
	ENSURE_EQUALS(
		"dict() failed (literal)",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(x);}" ),
		"[\"Ala\": 0, \"kota.\": 2, \"ma\": 1]"
	);
	ENSURE_EQUALS(
		"dict() size() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(size(x));}" ),
		"3"
	);
	ENSURE_EQUALS(
		"dict.kas_key() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return([x.has_key(\"kota.\"),x.has_key(\"psa.\")]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"dict.get()/dict.try_get() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return([x.get(\"ma\"),x.get(\"psa.\",3)]);}" ),
		"[1, 3]"
	);
	ENSURE_EQUALS(
		"dict.ensure() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return((x.ensure(\"data\", 7),x.ensure( \"ma\", 99 ),x));}" ),
		"(7, 1, [\"Ala\": 0, \"data\": 7, \"kota.\": 2, \"ma\": 1])"
	);
	ENSURE_EQUALS(
		"dict.get() on non existing succeeded",
		execute_except( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];return(x.get(\"psa\"));}" ),
		"*anonymous stream*:1:49: Key does not exist in `dict`."
	);
	ENSURE_EQUALS(
		"dict.erase() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];x.erase(\"kota.\");return(x);}" ),
		"[\"Ala\": 0, \"ma\": 1]"
	);
	ENSURE_EQUALS(
		"dict.clear()/dict.clone() failed",
		execute( "main(){x=[\"Ala\":0,\"ma\":1,\"kota.\":2];y=copy(x);x.clear();return([x,y]);}" ),
		"[dict(), [\"Ala\": 0, \"kota.\": 2, \"ma\": 1]]"
	);
	ENSURE_EQUALS( "dict reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed([2:0,3:1,5:-1,7:-2]),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "dict reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed([2:0,3:1,5:-1,7:-2]);algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"dict equals failed",
		execute(
			"main(){"
			"d1=[1:1,2:2,3:3];"
			"d2=[1:1,2:2,3:3];"
			"d3f=[1:1,2:2,4:3];"
			"d3s=[1:1,2:2,3:4];"
			"return([d1==d2,d1==d3f,d1==d3s]);}"
		),
		"[true, false, false]"
	);
	ENSURE_EQUALS(
		"dict values() failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"d = [0:1,1:2,2:4,3:8];"
			"algo.materialize(d.values(),list);"
			"}"
		),
		"[(0, 1), (1, 2), (2, 4), (3, 8)]"
	);
	ENSURE_EQUALS(
		"dict values() size/copy failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"d = [0:1,1:2,2:4,3:8];"
			"v = copy(d.values());"
			"algo.materialize(v,list).push(size(v));"
			"}"
		),
		"[(0, 1), (1, 2), (2, 4), (3, 8), 4]"
	);
	ENSURE_EQUALS(
		"dict on non-uniform succeeded",
		execute_except( "main(){[1:2,2.:3.];}" ),
		"*anonymous stream*:1:13: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"dict on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){x=[A():0, A():1];return(x);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:35: Class `A` does not have `less` method."
	);
	ENSURE_EQUALS(
		"dict update failed",
		execute(
			"main(){\n"
			"d1=[2:2,3:3,5:5];\n"
			"d2=[2:2,4:4,8:8];\n"
			"d1.update(d2);\n"
			"return(d1);\n"
			"}\n"
		),
		"[2: 2, 3: 3, 4: 4, 5: 5, 8: 8]"
	);
	ENSURE_EQUALS(
		"dict update from empty failed",
		execute(
			"main(){\n"
			"d1=dict();\n"
			"d2=dict();\n"
			"d1.update(d2);\n"
			"return(d1);\n"
			"}\n"
		),
		"dict()"
	);
	ENSURE_EQUALS(
		"dict.update on non-uniform succeeded",
		execute_except( "main(){[1:2].update([2.:3.]);}" ),
		"*anonymous stream*:1:20: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"dict hash failed",
		execute(
			"import Introspection as intro;"
			"main(){[intro.hash(dict()),intro.hash([1:2])];}"
		),
		"[10, 95]"
	);
	ENSURE_EQUALS(
		"dict clear in for",
		execute(
			"main(){\n"
			"d=[2:2,3:3,5:5];\n"
			"r = [];"
			"for(e:d){d.clear();r.push(e);}\n"
			"r.push(d);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, dict()]"
	);
	ENSURE_EQUALS(
		"dict erase in for",
		execute(
			"main(){\n"
			"d=[2:2,3:3,5:5];\n"
			"r = [];"
			"for(e:d){d.erase(e);r.push(e);}\n"
			"r.push(d);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 3, 5, dict()]"
	);
	ENSURE_EQUALS(
		"dict erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"d=[2:2,3:3,5:5];\n"
			"r = [];"
			"for(e:algo.reversed(d)){d.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[5, 3, 2]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "lookup()" )
#if ( TARGET_CPU_BITS == 64 )
	char const expected1[] = "{none: 7, true: false, 1: \"ma\", \"Ala\": 0, \"kota.\": 2}";
#else
	char const expected1[] = "{none: 7, true: false, 1: \"ma\", \"kota.\": 2, \"Ala\": 0}";
#endif
	ENSURE_EQUALS(
		"lookup() iterator failed",
		execute( "main(){x={\"Ala\":0,1:\"ma\",\"kota.\":2,none:7,true:false};return(x);}" ),
		expected1
	);
	ENSURE_EQUALS(
		"hash on user succeeded",
		execute_except( "class A{_x=none;}main(){l=lookup();return(l[A()]=0);}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:44: Class `A` does not have `hash` method."
	);
	ENSURE_EQUALS(
		"lookup() iterator failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return([x.has_key(1),x.has_key(2)]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"lookup() size failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return(size(x));}" ),
		"5"
	);
	ENSURE_EQUALS(
		"lookup() clear failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;s=size(x);x.clear();return([s,size(x)]);}" ),
		"[5, 0]"
	);
	ENSURE_EQUALS(
		"lookup reversed() failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"algo.materialize(algo.reversed(x),list);"
			"}"
		),
		"[7, 5, 3, 2]"
	);
	ENSURE_EQUALS(
		"lookup reversed() size/copy failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"y=algo.reversed(x);"
			"algo.materialize(copy(y),list).push(size(y));"
			"}"
		),
		"[7, 5, 3, 2, 4]"
	);
	ENSURE_EQUALS(
		"lookup values() failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"algo.materialize(x.values(),list);"
			"}"
		),
		"[(2, 0), (3, 1), (5, -1), (7, -2)]"
	);
	ENSURE_EQUALS(
		"lookup values() size/copy failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"x={2: 0, 3: 1, 5: -1, 7: -2};"
			"y=x.values();"
			"algo.materialize(copy(y),list).push(size(y));"
			"}"
		),
		"[(2, 0), (3, 1), (5, -1), (7, -2), 4]"
	);
#if ( TARGET_CPU_BITS == 64 )
	char const expected2[] = "\"none7truefalse1maAla0kota.2|1maAla0kota.2\"";
#else
	char const expected2[] = "\"none7truefalse1makota.2Ala0|1makota.2Ala0\"";
#endif
	ENSURE_EQUALS(
		"lookup() erase failed",
		execute( "d(x){v=\"\";for(e:x){v+=string(e);v+=string(x[e]);}return(v);}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;v=d(x);v+=\"|\";x.erase(none);x.erase(true);v+=d(x);return(v);}" ),
		expected2
	);
	ENSURE_EQUALS(
		"lookup() get failed",
		execute( "main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;return([x.get(1),x.get(2,7)]);}" ),
		"[\"ma\", 7]"
	);
#if ( TARGET_CPU_BITS == 64 )
	char const expected4[] = "(\"data\", \"ma\", {1: \"ma\", 7: \"data\", \"Ala\": 0, \"kota.\": 2})";
#else
	char const expected4[] = "(\"data\", \"ma\", {1: \"ma\", \"kota.\": 2, 7: \"data\", \"Ala\": 0})";
#endif
	ENSURE_EQUALS(
		"lookup.ensure() failed",
		execute( "main(){x={\"Ala\":0,1:\"ma\",\"kota.\":2};return((x.ensure(7,\"data\"),x.ensure( 1, \"je\" ),x));}" ),
		expected4
	);
	ENSURE_EQUALS(
		"lookup equals failed",
		execute(
			"main(){"
			"l1=lookup();l1[1]=1;l1[2]=2;l1[3]=3;"
			"l2=lookup();l2[1]=1;l2[2]=2;l2[3]=3;"
			"l3f=lookup();l3f[1]=1;l3f[2]=2;l3f[4]=3;"
			"l3s=lookup();l3s[1]=1;l3s[2]=2;l3s[3]=4;"
			"return([l1==l2,l1==l3f,l1==l3s]);}"
		),
		"[true, false, false]"
	);
#if ( TARGET_CPU_BITS == 64 )
	char const expected3[] = "[\"1maAla0kota.2\", \"none7truefalse1maAla0kota.2\"]";
#else
	char const expected3[] = "[\"1makota.2Ala0\", \"none7truefalse1makota.2Ala0\"]";
#endif
	ENSURE_EQUALS(
		"lookup() copy() failed",
		execute( "d(x){v=\"\";for(e:x){v+=string(e);v+=string(x[e]);}return(v);}main(){x=lookup();x[\"Ala\"]=0;x[1]=\"ma\";x[\"kota.\"]=2;x[none]=7;x[true]=false;y=copy(x);x.erase(none);x.erase(true);return([d(x),d(y)]);}" ),
		expected3
	);
	ENSURE_EQUALS(
		"lookup update failed",
		execute(
			"main(){\n"
			"l1=lookup();l1[2]=2;l1[3]=3;l1[5]=5;"
			"l2=lookup();l2[2]=2;l2[4]=4;l2[8]=8;"
			"l1.update(l2);\n"
			"r=\"\";\n"
			"for(k:l1) {\n"
			"r+=\"{} -> {}, \".format(k, l1[k]);\n"
			"}\n"
			"return(r);\n"
			"}\n"
		),
		"\"2 -> 2, 3 -> 3, 4 -> 4, 5 -> 5, 8 -> 8, \""
	);
	ENSURE_EQUALS(
		"lookup hash failed",
		execute(
			"import Introspection as intro;"
			"main(){[intro.hash({}),intro.hash({1:2})];}"
		),
		"[12, 113]"
	);
	ENSURE_EQUALS(
		"lookup clear in for",
		execute(
			"main(){\n"
			"l={2:2,3:3,5:5};\n"
			"r = [];"
			"for(e:l){l.clear();r.push(e);}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, {}]"
	);
	ENSURE_EQUALS(
		"lookup erase in for",
		execute(
			"main(){\n"
			"l={2:2,3:3,5:5};\n"
			"r = [];"
			"for(e:l){l.erase(e);r.push(e);}\n"
			"r.push(l);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, 5, 2, {}]"
	);
	ENSURE_EQUALS(
		"lookup erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"l={2:2,3:3,5:5};\n"
			"r = [];"
			"for(e:algo.reversed(l)){l.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 5, 3]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "order()" )
	ENSURE_EQUALS(
		"order() failed",
		execute( "main(){x=order(2,3,1,4,7,5);x.insert(10).insert(0);return(x);}" ),
		"order(0, 1, 2, 3, 4, 5, 7, 10)"
	);
	ENSURE_EQUALS(
		"order iterator failed",
		execute( "main(){x=order(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"order has_key failed",
		execute( "main(){x=order(2,3,1,4,7,5);return([x.has_key(3),x.has_key(0)]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"order erase failed",
		execute( "main(){x=order(2,3,1,4,7,5);x.erase(3).erase(4);return(x);}" ),
		"order(1, 2, 5, 7)"
	);
	ENSURE_EQUALS(
		"order equals failed",
		execute(
			"main(){"
			"o1=order(1,2,3);"
			"o2=order(1,2,3);"
			"o3=order(1,2,4);"
			"return([o1==o2,o1==o3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"order clear/copy failed",
		execute( "main(){x=order(2,3,1,4,7,5);y=copy(x);x.clear();return([x,y,size(y)]);}" ),
		"[order(), order(1, 2, 3, 4, 5, 7), 6]"
	);
	ENSURE_EQUALS( "order reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed(order(2,3,5,7)),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "order reversed() copy/size failed", execute( "import Algorithms as algo;main(){x=algo.reversed(order(2,3,5,7));algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"order on non-uniform succeeded",
		execute_except( "main(){order(1,2.);}" ),
		"*anonymous stream*:1:13: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"order on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){order(A(),A());}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:30: Class `A` does not have `less` method."
	);
	ENSURE_EQUALS(
		"order update failed",
		execute(
			"main(){\n"
			"o1=order(2,3,5);\n"
			"o2=order(2,4,8);\n"
			"o1.update(o2);\n"
			"return(o1);\n"
			"}\n"
		),
		"order(2, 3, 4, 5, 8)"
	);
	ENSURE_EQUALS(
		"order update from empty failed",
		execute(
			"main(){\n"
			"o1=order();\n"
			"o2=order();\n"
			"o1.update(o2);\n"
			"return(o1);\n"
			"}\n"
		),
		"order()"
	);
	ENSURE_EQUALS(
		"order.update on non-uniform succeeded",
		execute_except( "main(){order(1).update(order(2.));}" ),
		"*anonymous stream*:1:23: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"order hash failed",
		execute(
			"import Introspection as intro;"
			"main(){[intro.hash(order()),intro.hash(order(1))];}"
		),
		"[11, 34]"
	);
	ENSURE_EQUALS(
		"order clear in for",
		execute(
			"main(){\n"
			"o=order(2,3,5);\n"
			"r = [];"
			"for(e:o){o.clear();r.push(e);}\n"
			"r.push(o);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, order()]"
	);
	ENSURE_EQUALS(
		"order erase in for",
		execute(
			"main(){\n"
			"o=order(2,3,5);\n"
			"r = [];"
			"for(e:o){o.erase(e);r.push(e);}\n"
			"r.push(o);\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 3, 5, order()]"
	);
	ENSURE_EQUALS(
		"order erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"o=order(2,3,5);\n"
			"r = [];"
			"for(e:algo.reversed(o)){o.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[5, 3, 2]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "set()" )
	ENSURE_IN(
		"set() failed",
		execute( "main(){x=set(2,\"ala\",3.14);x.insert($7.34).insert('Q');return(x);}" ),
		std::vector<hcore::HString>({
			"{2, 'Q', 3.14, $7.34, \"ala\"}",
			"{2, 'Q', $7.34, \"ala\", 3.14}",
			"{2, 'Q', 3.14, \"ala\", $7.34}"
		})
	);
	ENSURE_EQUALS(
		"set() iterator failed",
		execute( "main(){x=set(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"2:3:5:7:\""
	);
	ENSURE_EQUALS(
		"set has_key failed",
		execute( "main(){x=set(2,\"ala\",3.14);return([x.has_key(\"ala\"),x.has_key(3.145)]);}" ),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"set erase failed",
		execute( "main(){x=set(2,\"ala\",3.14,$7.34,'Q');x.erase($7.34).erase(\"ala\");return(x);}" ),
		"{2, 'Q', 3.14}"
	);
	ENSURE_EQUALS(
		"set equals failed",
		execute(
			"main(){"
			"s1=set(1,2,3);"
			"s2=set(1,2,3);"
			"s3=set(1,2,4);"
			"return([s1==s2,s1==s3]);}"
		),
		"[true, false]"
	);
	ENSURE_IN(
		"set copy/clear failed",
		execute( "main(){x=set(2,\"ala\",3.14,$7.34,'Q');y=copy(x);x.clear();return([x,y,size(y)]);}" ),
		std::vector<hcore::HString>({
			"[set(), {2, 3.14, 'Q', $7.34, \"ala\"}, 5]",
			"[set(), {2, 'Q', $7.34, \"ala\", 3.14}, 5]",
			"[set(), {2, 3.14, 'Q', \"ala\", $7.34}, 5]"
		})
	);
	ENSURE_EQUALS( "set reversed() failed", execute( "import Algorithms as algo;main(){algo.materialize(algo.reversed({2,3,5,7}),list);}" ), "[7, 5, 3, 2]" );
	ENSURE_EQUALS( "set reversed() size/copy failed", execute( "import Algorithms as algo;main(){x=algo.reversed({2,3,5,7});algo.materialize(copy(x),list).push(size(x));}" ), "[7, 5, 3, 2, 4]" );
	ENSURE_EQUALS(
		"set update failed",
		execute(
			"main(){\n"
			"s1={2,3,5};\n"
			"s2={2,4,8};\n"
			"s1.update(s2);\n"
			"return(s1);\n"
			"}\n"
		),
		"{2, 3, 4, 5, 8}"
	);
	ENSURE_EQUALS(
		"set hash failed",
		execute(
			"import Introspection as intro;"
			"main(){[intro.hash(set()),intro.hash({1})];}"
		),
		"[13, 40]"
	);
	ENSURE_EQUALS(
		"set clear in for",
		execute(
			"main(){\n"
			"s={2,3,5};\n"
			"r = [];"
			"for(e:s){s.clear();r.push(e);}\n"
			"r.push(s);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, set()]"
	);
	ENSURE_EQUALS(
		"set erase in for",
		execute(
			"main(){\n"
			"s={2,3,5};\n"
			"r = [];"
			"for(e:s){s.erase(e);r.push(e);}\n"
			"r.push(s);\n"
			"return(r);\n"
			"}\n"
		),
		"[3, 5, 2, set()]"
	);
	ENSURE_EQUALS(
		"set erase in reversed for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s={2,3,5};\n"
			"r = [];"
			"for(e:algo.reversed(s)){s.erase(e);r.push(e);}\n"
			"return(r);\n"
			"}\n"
		),
		"[2, 5, 3]"
	);
	ENSURE_EQUALS(
		"set operator `+` failed",
		execute(
			"main(){\n"
			"s1={2,3,5};\n"
			"s2={2,4,8};\n"
			"return(s1 + s2);\n"
			"}\n"
		),
		"{2, 3, 4, 5, 8}"
	);
	ENSURE_EQUALS(
		"set operator `-` failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s1={2,3,5};\n"
			"s2={2,4,8};\n"
			"s3={2,4,8};\n"
			"s4={1,7,11};\n"
			"return(algo.materialize(algo.map([s1 - s2, s2 - s3, s1 - s4], algo.sorted), list));\n"
			"}\n"
		),
		"[[3, 5], [], [2, 3, 5]]"
	);
	ENSURE_EQUALS(
		"set operator `-` (subject set is bigger) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s1={2,3,5,4,7};\n"
			"s2={2,4,8};\n"
			"return(algo.sorted(s1 - s2));\n"
			"}\n"
		),
		"[3, 5, 7]"
	);
	ENSURE_EQUALS(
		"set operator `-` (object set is bigger) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s1={2,3,5};\n"
			"s2={2,4,8,16,32};\n"
			"return(algo.sorted(s1 - s2));\n"
			"}\n"
		),
		"[3, 5]"
	);
	ENSURE_EQUALS(
		"set operator `*` failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"s1={2,3,5};\n"
			"s2={2,4,8};\n"
			"s3={2,4,8};\n"
			"s4={1,7,11};\n"
			"return(algo.materialize(algo.map([s1 * s2, s2 * s3, s1 * s4], algo.sorted), list));\n"
			"}\n"
		),
		"[[2], [2, 4, 8], []]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "heap()" )
	ENSURE_EQUALS(
		"heap() failed",
		execute( "main(){x=heap(7, 19, 4);x.push(0).push(11);return(x);}" ),
		"heap(19, 11, 7, 4, 0)"
	);
	ENSURE_EQUALS(
		"heap() iterator failed",
		execute( "main(){x=heap(2,3,5,7);v=\"\";for(e:x){v+=string(e);v+=\":\";}return(v);}" ),
		"\"7:5:3:2:\""
	);
	ENSURE_EQUALS(
		"heap top failed",
		execute( "main(){x=heap(1,2,3,4);return(x.top());}" ),
		"4"
	);
	ENSURE_EQUALS(
		"heap pop failed",
		execute( "main(){x=heap(1, 4, 2, 3);return([x.pop(),x]);}" ),
		"[4, heap(3, 2, 1)]"
	);
	ENSURE_EQUALS(
		"heap equals failed",
		execute(
			"main(){"
			"h1=heap(1,2,3);"
			"h2=heap(1,2,3);"
			"h3=heap(1,2,4);"
			"return([h1==h2,h1==h3]);}"
		),
		"[true, false]"
	);
	ENSURE_EQUALS(
		"heap copy/clear failed",
		execute( "main(){x=heap(1,2,3,5);y=copy(x);x.clear();return([x,y,size(y)]);}" ),
		"[heap(), heap(5, 3, 2, 1), 4]"
	);
	ENSURE_EQUALS(
		"heap hash failed",
		execute(
			"import Introspection as intro;"
			"main(){[intro.hash(heap()),intro.hash(heap(1))];}"
		),
		"[14, 43]"
	);
	ENSURE_EQUALS(
		"heap clear in for",
		execute(
			"main(){\n"
			"h=heap(2,3,5);\n"
			"r = [];"
			"for(e:h){h.clear();r.push(e);}\n"
			"r.push(h);\n"
			"return(r);\n"
			"}\n"
		),
		"[5, heap()]"
	);
	ENSURE_EQUALS(
		"heap pop in for",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"h=heap(1,2,3,4,5,6,7,8,9);\n"
			"i = 0;\n"
			"r = [];\n"
			"for(e:h){\n"
			"if(i > 1){\n"
			"for (_:algo.range(6)) {\n"
			"h.pop();\n"
			"}\n"
			"i=-100;\n"
			"}\n"
			"r.push(e);\n"
			"i += 1;\n"
			"}\n"
			"r.push(h);\n"
			"return(r);\n"
			"}\n"
		),
		"[9, 8, 7, 2, 1, heap(3, 2, 1)]"
	);
	ENSURE_EQUALS(
		"heap on non-uniform succeeded",
		execute_except( "main(){heap(1,2.);}" ),
		"*anonymous stream*:1:12: Non-uniform key types, got a `real` instead of an `integer`."
	);
	ENSURE_EQUALS(
		"heap on non-comparable succeeded",
		execute_except( "class A{_x=none;}main(){heap(A(),A());}", HHuginn::COMPILER::BE_SLOPPY ),
		"*anonymous stream*:1:29: Class `A` does not have `less` method."
	);
TUT_TEARDOWN()

}


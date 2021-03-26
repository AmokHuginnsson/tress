/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hhuginn.hxx>
#include <yaal/hcore/hcore.hxx>
#include <yaal/hcore/system.hxx>
#include <yaal/tools/huginn/runtime.hxx>
#include <yaal/tools/huginn/thread.hxx>
#include <yaal/tools/huginn/objectfactory.hxx>
#include <yaal/tools/huginn/helper.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hstringstream.hxx>

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

struct tut_yaal_tools_hhuginn_statements : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_statements, "yaal::tools::HHuginn,statements" );

TUT_UNIT_TEST( "if" )
	ENSURE_EQUALS( "if (true) failed", execute( "main(){x=2;if(x>0){x=x*x;}return(x);}" ), "4" );
	ENSURE_EQUALS( "if (false) failed", execute( "main(){x=2;if(x>2){x=x*x;}return(x);}" ), "2" );
	ENSURE_EQUALS(
		"if else if else chain failed",
		execute(
			"foo(b,v) {\n"
			"if(b) {\n"
			"v+=\"foo\";\n"
			"} else {\n"
			"throw Exception(\"ex\");\n"
			"}\n"
			"}\n"
			"main(){\n"
			"r=\"\";\n"
			"try{\n"
			"v=0;\n"
			"if(v>0){\n"
			"r+=\"bad\";\n"
			"} else if(foo(false, v) > 0){\n"
			"r+=\"bad2\";\n"
			"} else if(foo(true, v) > 0){\n"
			"r+=\"bad3\";\n"
			"} else {\n"
			"r+=\"bad4\";\n"
			"}\n"
			"}catch(Exception e){\n"
			"r+=e.what();"
			"}\n"
			"return(r);\n"
			"}\n"
		),
		"\"ex\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "while" )
	ENSURE_EQUALS( "while failed", execute( "main(){x=2;while(x<100){x=x*x;}return(x);}" ), "256" );
TUT_TEARDOWN()

char const ITERABLE_DEF[] =
	"class ListNode {\n"
	"	_data = none;\n"
	"	_next = none;\n"
	"	constructor( data_, next_ ) {\n"
	"		_data = data_;\n"
	"		_next = next_;\n"
	"	}\n"
	"}\n"
	"\n"
	"class ListIterator {\n"
	"	_cur = none;\n"
	"	constructor( cur_ ) {\n"
	"		_cur = cur_;\n"
	"	}\n"
	"	is_valid() {\n"
	"		return ( _cur != none );\n"
	"	}\n"
	"	value() {\n"
	"		return ( _cur._data );\n"
	"	}\n"
	"	next() {\n"
	"		_cur = _cur._next;\n"
	"	}\n"
	"}\n"
	"\n"
	"class List {\n"
	"	_head = none;\n"
	"	add( data_ ) {\n"
	"		_head = ListNode( data_, _head );\n"
	"		return(this);\n"
	"	}\n"
	"	iterator() {\n"
	"		return ( ListIterator( _head ) );\n"
	"	}\n"
	"}\n"
	"\n";

TUT_UNIT_TEST( "for" )
	ENSURE_EQUALS( "for failed", execute( "main(){x=list(1,2,3);s=0;for(e:x){s=s+e;}return(s);}" ), "6" );
	ENSURE_EQUALS( "for(expr:) failed", execute( "main(){x=list(1,2,3);s=0;l=[0];for(l[0]:x){s=s+l[0];}return(string(s)+string(l[0]));}" ), "\"63\"" );
	ENSURE_EQUALS(
		"for(user-def) failed",
		execute(
			to_string( ITERABLE_DEF ).append(
				"main() {"
				"s=\"\";"
				"l=List();"
				"l.add(\"one\").add(\"two\").add(\"three\");"
				"for ( e : l ) {"
				"s+=e;"
				"s+=\"+\";"
				"}"
				"return(s);"
				"}"
			)
		),
		"\"three+two+one+\""
	);
	ENSURE_EQUALS(
		"tuple unpacking failed",
		execute(
			"main(){\n"
			"\td = [(0,1),(2,3),(4,5),(6,7)];\n"
			"\tr = [];\n"
			"\tfor( x, y : d ) {\n"
			"\tr.push([x,y]);\n"
			"\t}\n"
			"\treturn ( r );\n"
			"}\n"
		),
		"[[0, 1], [2, 3], [4, 5], [6, 7]]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "user defined iterator-adaptor" )
	ENSURE_EQUALS(
		"iterator-adaptor in algorithms failed",
		execute(
			"import Algorithms as algo;\n"_ys.append(
				ITERABLE_DEF
			).append(
				"main() {"
				"l=List();"
				"l.add(0).add(1).add(2);"
				"return(algo.materialize(l, list));"
				"}"
			)
		),
		"[2, 1, 0]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "switch" )
	ENSURE_EQUALS( "switch (no match, no default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}}return(x);}" ), "\"x\"" );
	ENSURE_EQUALS( "switch (no match, with default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}default:{x=\"y\";}}return(x);}" ), "\"y\"" );
	ENSURE_EQUALS( "switch (match, fallthrough, no default) failed", execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}case(1):{x=x+\"y\";}case(2):{x=x+\"z\";}}return(x);}" ), "\"xyz\"" );
	ENSURE_EQUALS(
		"switch (match, fallthrough, default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}case(1):{x=x+\"y\";}case(2):{x=x+\"z\";}default:{x=x+\"!\";}}return(x);}" ),
		"\"xyz!\""
	);
	ENSURE_EQUALS(
		"switch (match, no fallthrough, no default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}break;case(1):{x=x+\"y\";}break;case(2):{x=x+\"z\";}break;}return(x);}" ),
		"\"xy\""
	);
	ENSURE_EQUALS(
		"switch (match, no fallthrough, default) failed",
		execute( "main(){x=\"x\";n=1;switch(n){case(0):{x=\"0\";}break;case(1):{x=x+\"y\";}break;case(2):{x=x+\"z\";}break;default:{x=x+\"!\";}}return(x);}" ),
		"\"xy\""
	);
	ENSURE_EQUALS(
		"switch, case expression failed",
		execute(
			"foo(b,v) {\n"
			"if(b) {\n"
			"v+=\"foo\";\n"
			"} else {\n"
			"throw Exception(\"ex\");\n"
			"}\n"
			"}\n"
			"main(){\n"
			"r=\"\";\n"
			"try{\n"
			"v=0;\n"
			"switch(v){\n"
			"case(7):{\n"
			"r+=\"bad\";\n"
			"}break;\n"
			"case(foo(false, v)):{\n"
			"r+=\"bad2\";\n"
			"}break;\n"
			"case(foo(true, v)):{\n"
			"r+=\"bad3\";\n"
			"} break;\n"
			"default: {\n"
			"r+=\"bad4\";\n"
			"}\n"
			"}\n"
			"}catch(Exception e){\n"
			"r+=e.what();"
			"}\n"
			"return(r);\n"
			"}\n"
		),
		"\"ex\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "break;" )
	ENSURE_EQUALS( "break; failed (while)", execute( "main(){x=0;y=0;while(y<100){y=y+1;if(x>100){break;}x=x+y*y;}return(x);}" ), "140" );
	ENSURE_EQUALS( "break; failed (for)", execute( "main(){x=[\"A\",\"a\",\"B\",\"b\",\"C\",\"c\"];v=\"\";for(e:x){if(size(v)>2){break;}v=v+e;}return(v);}" ), "\"AaB\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "continue;" )
	ENSURE_EQUALS(
		"continue; failed (while)",
		execute(
			"main(){\n"
			"x=\"ALAMAKOTA\";\n"
			"y=\"alamakota\";\n"
			"i=0;\n"
			"c=size(x);\n"
			"z=\"\";\n"
			"while(i<c){\n"
			"idx=i;\n"
			"i=i+1;\n"
			"z=z+string(x[idx]);\n"
			"if(i>(c/2)){continue;}\n"
			"z=z+string(y[idx]);\n"
			"}\n"
			"return(z);}"
		),
		"\"AaLlAaMmAKOTA\""
	);
	ENSURE_EQUALS(
		"continue; failed (for)",
		execute(
			"main(){\n"
			"i=0;\n"
			"x=\"Ala ma kota.\";\n"
			"z=\"\";\n"
			"for(e:x){\n"
			"z=z+string(e);\n"
			"if(i>4){continue;}\n"
			"z=z+\"+\";\n"
			"i=i+1;\n"
			"}\n"
			"return(z);}"
		),
		"\"A+l+a+ +m+a kota.\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "class" )
	ENSURE_EQUALS(
		"class failed",
		execute(
			"class A{_d=none;}"
			"main(){"
			"o=A();"
			"o._d=\"ok\";"
			"return(o._d);"
			"}"
		),
		"\"ok\""
	);
	ENSURE_EQUALS(
		"default constructor failed",
		execute(
			"class A{"
			"_d=none;"
			"}"
			"main(){"
			"o=A(\"ok\");"
			"return(o._d);"
			"}"
		),
		"\"ok\""
	);
	ENSURE_EQUALS(
		"default constructor failed",
		execute(
			"class A{"
			"_a=none;"
			"_b=none;"
			"}"
			"main(){"
			"o=A(\"ok\");"
			"return(\"{}{}\".format(o._a, o._b));"
			"}"
		),
		"\"oknone\""
	);
	ENSURE_EQUALS(
		"default constructor failed",
		execute(
			"class A{"
			"foo(){_a;}"
			"_a=none;"
			"_b=none;"
			"}"
			"main(){"
			"o=A(\"ok\");"
			"return(\"{}{}\".format(o.foo(), o._b));"
			"}"
		),
		"\"oknone\""
	);
	ENSURE_EQUALS(
		"constructor failed",
		execute(
			"class A{"
			"_d=none;"
			"constructor(d_){"
			"_d=d_ + d_;"
			"}"
			"}"
			"main(){"
			"o=A(\"ok\");"
			"return(o._d);"
			"}"
		),
		"\"okok\""
	);
	ENSURE_EQUALS(
		"destructor failed",
		execute(
			"class A{"
			"_d=none;"
			"constructor(d_){_d=d_;}"
			"destructor(){_d.push(\"ok\");}"
			"}"
			"main(){"
			"l=list();"
			"{o=A(l);type(o);}"
			"return(l[0]);"
			"}"
		),
		"\"ok\""
	);
	ENSURE_EQUALS(
		"super failed",
		execute(
			"class B{_d=none;constructor(d_){_d=d_;}destructor(){_d.push(\"ok\");}}\n"
			"class D:B{_n=none;constructor(l_,n_){super.constructor(l_);_n=n_;}}\n"
			"main(){\n"
			"s=none;\n"
			"l=list();\n"
			"{\n"
			"o=D(l,\"arg\");\n"
			"s=o._n;\n"
			"}\n"
			"return(l[0]+s);\n"
			"}"
		),
		"\"okarg\""
	);
	ENSURE_EQUALS(
		"destructor chain failed",
		execute(
			"class B{_d=none;constructor(d_){_d=d_;}destructor(){_d.push(\"base\");}}"
			"class D:B{constructor(l_){super.constructor(l_);}destructor(){_d.push(\"derived\");}}"
			"main(){l=list();{o=D(l);type(o);}return(l[0]+l[1]);}"
		),
		"\"derivedbase\""
	);
	ENSURE_EQUALS(
		"class this failed",
		execute(
			"class A{_d=\"\";f(s_){_d=_d+s_;return(this);}}"
			"main(){a=A();a.f(\"this\").f(\"ok\");return(a._d);}"
		),
		"\"thisok\""
	);
	ENSURE_EQUALS(
		"class to_string failed",
		execute(
			"class A{_d=none;_x=none;constructor(d_,x_){_d=d_;_x=x_;}to_string(){return(string(_d)+\":\"+string(_x));}}"
			"main(){a=A(7,'Q');return(string(a));}"
		),
		"\"7:Q\""
	);
	ENSURE_EQUALS(
		"class copy failed",
		execute(
			"class A{"
			"_x=none;"
			"constructor(x_){_x=x_;}"
			"to_string(){return(string(_x));}"
			"fv0(x_){_x=x_;}"
			"}"
			"main(){"
			"a=A(7);b=a;c=copy(a);a.fv0(3);"
			"return([string(a),string(b),string(c)]);"
			"}"
		),
		"[\"3\", \"3\", \"7\"]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "enum" )
	ENSURE_EQUALS(
		"user enum failed",
		execute(
			"enum COLOR {\n"
			"RED,\n"
			"GREEN,\n"
			"BLUE\n"
			"}\n"
			"main(){\n"
			"return((COLOR.RED,COLOR.GREEN,COLOR.BLUE));\n"
			"}"
		),
		"(COLOR.RED, COLOR.GREEN, COLOR.BLUE)"
	);
	ENSURE_EQUALS(
		"user enum failed",
		execute(
			"enum COLOR {\n"
			"RED,\n"
			"GREEN,\n"
			"BLUE\n"
			"}\n"
			"main(){\n"
			"r = COLOR.RED;"
			"return((r == COLOR.RED, r == COLOR.BLUE));\n"
			"}"
		),
		"(true, false)"
	);
	ENSURE_EQUALS(
		"built-in enum failed",
		execute(
			"import FileSystem as fs;"
			"main(){\n"
			"fs;\n"
			"return((Stream.SEEK.BEGIN, Stream.SEEK.CURRENT, Stream.SEEK.END));\n"
			"}"
		),
		"(Stream.SEEK.BEGIN, Stream.SEEK.CURRENT, Stream.SEEK.END)"
	);
	ENSURE_EQUALS(
		"built-in enum failed",
		execute(
			"import FileSystem as fs;"
			"main(){\n"
			"return((fs.OPEN_MODE.READ, fs.OPEN_MODE.WRITE));\n"
			"}"
		),
		"(fs.OPEN_MODE.READ, fs.OPEN_MODE.WRITE)"
	);
TUT_TEARDOWN()

namespace {
void notify_vec( int val_, tut_yaal_tools_hhuginn_statements::int_array_t& dest_ ) {
	dest_.push_back( val_ );
}
}

TUT_UNIT_TEST( "scopes - order of destruction" )
#define N "class A{_log = none;_id=0;destructor(){_log.push(_id);notify(_id);}}main(){log=[];"
	/* simple scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (simple scope)",
			execute( h, N "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;" "log;" "}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (simple scope)", val, int_array_t{ 3, 2, 1 } );
	}
	/* for scope (one iter) */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (for scope 1 iter)",
			execute( h, N "for(x:[0]) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (for scope 1 iter)", val, int_array_t{ 3, 2, 1 } );
	}
	/* for scope (two iter) */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (for scope 2 iters)",
			execute( h, N "for(x:[0,0]) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;" "}log;}" ),
			"[3, 2, 1, 3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (for scope 2 iters)", val, int_array_t{ 3, 2, 1, 3, 2, 1 } );
	}
	/* while scope (one iter) */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (while scope 1 iter)",
			execute( h, N "x=0;while(x<1) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x+=1;" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (while scope 1 iter)", val, int_array_t{ 3, 2, 1 } );
	}
	/* while scope (two iter) */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (while scope 2 iters)",
			execute( h, N "x=0;while(x<2) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x+=1;" "}log;}" ),
			"[3, 2, 1, 3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (while scope 2 iters)", val, int_array_t{ 3, 2, 1, 3, 2, 1 } );
	}
	/* if scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (if scope)",
			execute( h, N "x=0;if(x<1) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x+=1;" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (if scope)", val, int_array_t{ 3, 2, 1 } );
	}
	/* if with control var and two vars in the scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (if scope)",
			execute( h, N "z = A(log,-1);if((x = A(log, 0))._id<1) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x;" "}z;log;}" ),
			"[3, 2, 1, 0, -1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (if scope)", val, int_array_t{ 3, 2, 1, 0, -1 } );
	}
	/* sequential ifs with control var and two vars in the scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (if scope)",
			execute(
				h,
				N "z1 = A(log,-1);if((x = A(log, 0))._id<1) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x;" "}"
				"z2 = A(log,-2);if((x = A(log, 4))._id<10) {" "a = A(log, 5);" "b = A(log, 6);" "c = A(log, 7);" "a;b;c;x;" "}z2;z1;log;}"
			),
			"[3, 2, 1, 0, 7, 6, 5, 4, -2, -1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (if scope)", val, int_array_t{ 3, 2, 1, 0, 7, 6, 5, 4, -2, -1 } );
	}
	/* if with control var and one extra var after if scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (if scope)",
			execute(
				h,
				"class A{_log = none;_id=0;constructor(log_, id_){_log = log_; _id = id_;_log.push(-_id);notify(-_id);}destructor(){_log.push(_id);notify(_id);}}"
				"main(){log=[];if((x = A(log, 10))._id<11) {" "x;" "} z = A(log, 77);z;log;}"
			),
			"[-10, 10, -77, 77]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (if scope)", val, int_array_t{ -10, 10, -77, 77 } );
	}
	/* sequential ifs with control var and two vars in the scope and one extra var after if scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (if scope)",
			execute(
				h,
				"class A{_log = none;_id=0;constructor(log_, id_){_log = log_; _id = id_;_log.push(-_id);notify(-_id);}destructor(){_log.push(_id);notify(_id);}}"
				"main(){log=[];z1 = A(log,7);if((x = A(log, 10))._id<11) {" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x;" "} z2 = A(log, 77);z2;z1;log;}"
			),
			"[-7, -10, -1, -2, -3, 3, 2, 1, 10, -77, 77, 7]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (if scope)", val, int_array_t{ -7, -10, -1, -2, -3, 3, 2, 1, 10, -77, 77, 7 } );
	}
	/* else scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (else scope)",
			execute( h, N "x=1;if(x<0){}else{" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x+=1;" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (else scope)", val, int_array_t{ 3, 2, 1 } );
	}
	/* switch scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (switch scope)",
			execute( h, N "switch(0) { case ( 0 ): {" "a = A(log, 1);a;} case ( 1 ): {" "b = A(log, 2);" "c = A(log, 3);b;c;}" "}log;}" ),
			"[1, 3, 2]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (switch scope)", val, int_array_t{ 1, 3, 2 } );
	}
	/* try scope no except */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (try scope no except)",
			execute( h, N "try{" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;" "}catch(Exception e){" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (try scope no expect)", val, int_array_t{ 3, 2, 1 } );
	}
	/* catch scope */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (catch scope)",
			execute( h, N "try{x=0;1/x;}catch(Exception e){" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (catch scope)", val, int_array_t{ 3, 2, 1 } );
	}
	/* try scope catchable except */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (try scope catchable except)",
			execute( h, N "try{" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;x=0;1/x;" "}catch(Exception e){" "}log;}" ),
			"[3, 2, 1]"
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (try scope catchable expect)", val, int_array_t{ 3, 2, 1 } );
	}
	/* try scope non-catchable except */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int_array_t val;
		register_function( *h, "notify", call( notify_vec, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"exec failed (try scope non-catchable except)",
			execute_except( h, N "try{" "a = A(log, 1);" "b = A(log, 2);" "c = A(log, 3);" "a;b;c;a._id+1.0;" "}catch(Exception e){" "}log;}" ),
			"*anonymous stream*:1:140: Operand types for `+` do not match: an `integer` vs a `real`."
		);
		h.reset();
		ENSURE_EQUALS( "wrong oreder of destruction (try scope non-catchable expect)", val, int_array_t{ 3, 2, 1 } );
	}
#undef N
TUT_TEARDOWN()

TUT_UNIT_TEST( "throw,try,catch" )
	ENSURE_EQUALS(
		"throw,try,catch failed",
		execute(
			"f( x ) {\n"
			"\tif ( x < 0 ) {\n"
			"\t\tthrow Exception( \"neg arg\" );\n"
			"\t}\n"
			"\treturn( x * x );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tv = \"\";\n"
			"\ttry {\n"
			"\t\tv = string( f( 2 ) );\n"
			"\t\tv = v + string( f( -2 ) );\n"
			"\t\tv = v + \"end\";\n"
			"\t} catch( Exception e ) {\n"
			"\t\tv = v + e.what();\n"
			"\t}\n"
			"\treturn ( v );\n"
			"}\n"
		),
		"\"4neg arg\""
	);
	ENSURE_EQUALS(
		"throw,try,catch(Type expr) failed",
		execute(
			"f( x ) {\n"
			"\tif ( x < 0 ) {\n"
			"\t\tthrow Exception( \"neg arg\" );\n"
			"\t}\n"
			"\treturn( x * x );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tv = \"\";\n"
			"\t\tl = [0];"
			"\ttry {\n"
			"\t\tv = string( f( 2 ) );\n"
			"\t\tv = v + string( f( -2 ) );\n"
			"\t\tv = v + \"end\";\n"
			"\t} catch( Exception2 e ) {\n"
			"\t\tl = e;\n"
			"\t} catch( Exception l[0] ) {\n"
			"\t\tv = v + l[0].what();\n"
			"\t}\n"
			"\treturn ( v );\n"
			"}\n"
		),
		"\"4neg arg\""
	);
	ENSURE_EQUALS(
		"throw,try,catch(Type expr) failed",
		execute(
			"f( x ) {\n"
			"\tif ( x < 0 ) {\n"
			"\t\tthrow Exception( \"neg arg\" );\n"
			"\t}\n"
			"\treturn( x * x );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tv = \"\";\n"
			"\tl = [\"x\"];"
			"\ttry {\n"
			"\t\tv = string( f( 2 ) );\n"
			"\t\tv = v + string( f( -2 ) );\n"
			"\t\tv = v + \"end\";\n"
			"\t} catch( Exception2 e ) {\n"
			"\t\tl = e;\n"
			"\t} catch( Exception l[0] ) {\n"
			"\t\tv = v + l[0].what();\n"
			"\t}\n"
			"\tv = v + l[0].what();\n"
			"\treturn ( v );\n"
			"}\n"
		),
		"\"4neg argneg arg\""
	);
	ENSURE_EQUALS(
		"catch by base failed",
		execute(
			"main() {"
			"v=\"\";"
			"try {"
			"z=0;"
			"1/z;"
			"} catch( Exception e ) {"
			"v = e.what();"
			"}"
			"return ( v );"
			"}"
		),
		"\"Division by zero.\""
	);
	ENSURE_EQUALS(
		"throw from return did return",
		execute(
			"atom( token ) {"
			"a = token;"
			"try {"
			"return ( integer( token ) );"
			"} catch ( Exception e ) {"
			"}"
			"return ( a );"
			"}"
			"main() {"
			"return(atom(\"ala\"));"
			"}"
		),
		"\"ala\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "assert" )
	/* no message */ {
		HHuginn h;
		HStringStream src(
			"main( argv_ ) {\n"
			"\tassert( type( argv_ ) == list );\n"
			"\tassert( size( argv_ ) > 1 );\n"
			"\treturn( 0 );\n"
			"}"
		);
		h.add_argument( "assert" );
		h.load( src );
		h.preprocess();
		ENSURE( "parse failed", h.parse() );
		ENSURE( "compile", h.compile() );
		ENSURE_NOT( "execute", h.execute() );
		ENSURE_EQUALS( "reporting failed assertion failed", h.error_message(), "*anonymous stream*:3:8: size( argv_ ) > 1" );
		ENSURE_EQUALS( "reporting error position for failed assert failed", h.error_position(), 57 );
		ENSURE_EQUALS( "reporting error line for failed assert failed", h.error_coordinate().line(), 3 );
		ENSURE_EQUALS( "reporting error column for failed assert failed", h.error_coordinate().column(), 8 );
	}
	/* with message */ {
		HHuginn h;
		HStringStream src(
			"main( argv_ ) {\n"
			"\tassert( size( argv_ ) > 1, \"bad number of arguments\" );\n"
			"\treturn( 0 );\n"
			"}"
		);
		h.add_argument( "assert" );
		h.load( src );
		h.preprocess();
		ENSURE( "parse failed", h.parse() );
		ENSURE( "compile", h.compile() );
		ENSURE_NOT( "execute", h.execute() );
		ENSURE_EQUALS( "reporting failed assertion failed", h.error_message(), "*anonymous stream*:2:8: size( argv_ ) > 1, bad number of arguments" );
		ENSURE_EQUALS( "reporting error position for failed assert failed", h.error_position(), 23 );
		ENSURE_EQUALS( "reporting error line for failed assert failed", h.error_coordinate().line(), 2 );
		ENSURE_EQUALS( "reporting error column for failed assert failed", h.error_coordinate().column(), 8 );
	}
TUT_TEARDOWN()

}


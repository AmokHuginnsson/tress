/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/hhuginn.hxx>
#include <yaal/hcore/hcore.hxx>
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

struct tut_yaal_tools_hhuginn : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn, "yaal::tools::HHuginn", 80 );

TUT_UNIT_TEST( "grammar test" )
	HHuginn h;
	HRule hg( h.make_engine() );
	HGrammarDescription gd( hg );

	char const expected[][500] = {
		"huginnGrammar = +( classDefinition | functionDefinition | enumDefinition | importStatement | fromStatement )",
		"classDefinition = ( \"class\" >> classIdentifier >> -( ':' >> baseIdentifier ) >> '{' >> +( field | functionDefinition ) >> '}' )",
		"functionDefinition = ( functionDefinitionIdentifier >> callable )",
		"enumDefinition = ( \"enum\" >> enumIdentifier >> '{' >> enumeral >> *( ',' >> enumeral ) >> '}' )",
		"importStatement = ( \"import\" >> packageName >> \"as\" >> importName >> ';' )",
		"fromStatement = ( \"from\" >> packageName >> \"import\" >> ( ( importedSymbol >> *( ',' >> importedSymbol ) ) | \"*\" ) >> ';' )",
		"field = ( fieldIdentifier >> '=' >> expression >> ';' )",
		"callable = ( '(' >> -( ( nameList >> -( ',' >> variadicParameter ) >> -( ',' >> namedParameterCapture ) ) | ( variadicParameter >> -( ',' >> namedParameterCapture ) ) | namedParameterCapture ) >> ')' >> '{' >> *statement >> '}' )",
		"enumeral = fieldIdentifier",
		"packageName = ( moduleName >> *( '.' >> moduleName ) )",
		"expression = ( *( ( assignablePack >> ( \"=\" | \"+=\" | \"-=\" | \"*=\" | \"/=\" | \"%=\" | \"^=\" ) ) ^ '=' ) >> value )",
		"nameList = ( parameter >> *( ',' >> parameter ) )",
		"variadicParameter = ( parameterIdentifier >> \"...\" )",
		"namedParameterCapture = ( parameterIdentifier >> \":::\" )",
		"statement = ( ifStatement | whileStatement | forStatement | switchStatement | tryCatchStatement | throwStatement | breakStatement | continueStatement | returnStatement | expressionStatement | scope )",
		"assignablePack = ( () >> assignable >> *( ',' >> assignable ) >> () )",
		"value = ternary",
		"parameter = ( ( parameterIdentifier ^ ( \"...\" | \":::\" ) ) >> -( '=' >> value ) )",
		"ifStatement = ( ifClause >> *( \"else\" >> ifClause ) >> -( \"else\" >> scope ) )",
		"whileStatement = ( \"while\" >> '(' >> expression >> ')' >> scope )",
		"forStatement = ( \"for\" >> '(' >> forCtrlVar >> *( ',' >> forCtrlVar ) >> ':' >> expression >> ')' >> scope )",
		"switchStatement = ( \"switch\" >> '(' >> expression >> ')' >> '{' >> +caseStatement >> -defaultStatement >> '}' )",
		"tryCatchStatement = ( \"try\" >> scope >> +catchStatement )",
		"throwStatement = ( \"throw\" >> expression >> ';' )",
		"breakStatement = ( \"break\" >> ';' )",
		"continueStatement = ( \"continue\" >> ';' )",
		"returnStatement = ( \"return\" >> -( '(' >> expression >> ')' ) >> ';' )",
		"expressionStatement = ( expression >> ';' )",
		"scope = ( '{' >> *statement >> '}' )",
		"assignable = ( subscript | variableSetter )",
		"ternary = ( booleanXor >> -( '?' >> expression >> ':' >> expression ) )",
		"ifClause = ( \"if\" >> '(' >> expression >> ')' >> scope )",
		"forCtrlVar = assignable",
		"caseStatement = ( \"case\" >> '(' >> expression >> ')' >> ':' >> scope >> -breakStatement )",
		"defaultStatement = ( \"default\" >> ':' >> scope )",
		"catchStatement = ( \"catch\" >> '(' >> exceptionType >> assignable >> ')' >> scope )",
		"subscript = ( reference >> +( subscriptOperator | functionCallOperator | memberAccess ) )",
		"booleanXor = ( booleanOr >> -( ( \"^^\" | \"⊕\" ) >> booleanOr ) )",
		"subscriptOperator = ( '[' >> ( ( ( rangeOper >> -argument ) | ( argument >> -( rangeOper >> -argument ) ) ) >> -( rangeOper >> -argument ) ) >> ']' )",
		"functionCallOperator = ( '(' >> -( ( argList >> -( ',' >> repackedNamedParameters ) ) | repackedNamedParameters ) >> ')' )",
		"memberAccess = ( '.' >> member )",
		"booleanOr = ( booleanAnd >> *( ( \"||\" | \"⋁\" ) >> booleanAnd ) )",
		"rangeOper = ':'",
		"argument = expression",
		"argList = ( functionArgument >> *( ',' >> functionArgument ) )",
		"repackedNamedParameters = ( repackedNamedParameter >> *( ',' >> repackedNamedParameter ) )",
		"booleanAnd = ( booleanNot >> *( ( \"&&\" | \"⋀\" ) >> booleanNot ) )",
		"functionArgument = ( ( argument ^ ':' ) >> -\"...\" )",
		"repackedNamedParameter = ( namedParameters | unpackedNamedParameters )",
		"booleanNot = ( ( '!¬' >> equality ) | equality )",
		"namedParameters = ( () >> namedParameter >> *( ',' >> namedParameter ) >> () >> () )",
		"unpackedNamedParameters = ( argument >> \":::\" )",
		"equality = ( compare >> -( ( \"==\" | \"!=\" | \"≠\" ) >> compare ) )",
		"namedParameter = ( parameterName >> ':' >> functionArgument )",
		"compare = ( sum >> -( ( \"<=\" | \">=\" | \"<\" | \">\" | \"≤\" | \"≥\" | \"∈\" | \"∉\" ) >> sum ) )",
		"sum = ( multiplication >> *( '+-' >> multiplication ) )",
		"multiplication = ( negation >> *( '*/%' >> negation ) )",
		"negation = ( ( '-' >> negation ) | power )",
		"power = ( factorial >> *( '^' >> negation ) )",
		"factorial = ( atom >> -( ( '!' & \"==\" ) | ( '!' ^ '=' ) ) )",
		"atom = ( modulus | ( parenthesis >> -( memberAccess >> dereference ) ) | real | integer"
			" | ( ( numberLiteral | character_literal ) >> -( memberAccess >> functionCallOperator ) )"
			" | ( ( tupleLiteral | listLiteral | dictLiteral | lookupLiteral | stringLiteral ) >> -( ( subscriptOperator | memberAccess ) >> dereference ) )"
			" | ( setLiteral >> -( memberAccess >> dereference ) ) | none | true | false"
			" | ( reference >> dereference ) | ( lambda >> -( functionCallOperator >> dereference ) ) )",
		"modulus = ( '|' >> expression >> '|' )",
		"parenthesis = ( '(' >> expression >> ')' )",
		"dereference = *( subscriptOperator | functionCallOperator | memberAccess )",
		"numberLiteral = ( '$' >> real )",
		"tupleLiteral = ( '(' >> -argList >> -',' >> ')' )",
		"listLiteral = ( '[' >> -argList >> ']' )",
		"dictLiteral = ( '[' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> ']' )",
		"lookupLiteral = ( '{' >> -( dictLiteralElement >> *( ',' >> dictLiteralElement ) ) >> '}' )",
		"stringLiteral = string_literal",
		"setLiteral = ( '{' >> argument >> *( ',' >> argument ) >> '}' )",
		"none = \"none\"",
		"true = \"true\"",
		"false = \"false\"",
		"lambda = ( ( '@' >> -( '[' >> captureList >> ']' ) ) >> callable )",
		"dictLiteralElement = ( argument >> ':' >> argument )",
		"captureList = ( capture >> *( ',' >> capture ) )",
		"capture = ( captureIdentifier >> -( ':' >> expression ) )"
	};

	int i( 0 );
	for ( HGrammarDescription::const_iterator it( gd.begin() ), end( gd.end() ); it != end; ++ it, ++ i ) {
		clog << *it << endl;
		ENSURE( "too many rules in Huginn grammar", i < yaal::size( expected ) );
		ENSURE_EQUALS( "bad rule in Huginn grammar", *it, expected[i] );
	}
	ENSURE_EQUALS( "not all rules found for Huginn grammar", i, yaal::size( expected ) );
TUT_TEARDOWN()

char const simpleProg[] =
	"/*\n"
	" * Sample code in huginn.\n"
	" */\n"
	"\n"
	"sum( a, b ) {\n"
	"\treturn ( a + b );\n"
	"}\n"
	"\n"
	"main( args ) {\n"
	"\ta = integer( args[0] );\n"
	"\tb = integer( args[1] );\n"
	"\treturn ( sum( 3 + a, sum( 4, ( b + 1 ) * 2 ) ) );\n"
	"}\n"
	"\n"
;

TUT_UNIT_TEST( "program return types and values" )
	/* none */ {
		OHuginnResult hr( execute_result( "main(){return(none);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::NONE );
	}
	/* integer */ {
		OHuginnResult hr( execute_result( "main(){return(0);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::INTEGER );
		ENSURE_EQUALS( "bad value returned", static_cast<huginn::HInteger*>( hr._result.raw() )->value(), 0 );
	}
	/* real */ {
		OHuginnResult hr( execute_result( "main(){return(3.14);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::REAL );
		ENSURE_DISTANCE( "bad value returned", static_cast<huginn::HReal*>( hr._result.raw() )->value(), 3.14L, epsilon );
	}
	/* string */ {
		OHuginnResult hr( execute_result( "main(){return(\"hello world\");}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::STRING );
		ENSURE_EQUALS( "bad value returned", static_cast<huginn::HString*>( hr._result.raw() )->value(), "hello world" );
	}
	/* character */ {
		OHuginnResult hr( execute_result( "main(){return('X');}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::CHARACTER );
		ENSURE_EQUALS( "bad value returned", static_cast<huginn::HCharacter*>( hr._result.raw() )->value(), code_point_t( 'X' ) );
	}
	/* number */ {
		OHuginnResult hr( execute_result( "main(){return($7);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::NUMBER );
		ENSURE_EQUALS( "bad value returned", static_cast<huginn::HNumber*>( hr._result.raw() )->value(), 7_yn );
	}
	/* boolean */ {
		OHuginnResult hr( execute_result( "main(){return(true);}" ) );
		ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::BOOLEAN );
		ENSURE_EQUALS( "bad value returned", static_cast<huginn::HBoolean*>( hr._result.raw() )->value(), true );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "set variable" )
	OHuginnResult hr( execute_result( "main(){a=7;return(a);}" ) );
	ENSURE_EQUALS( "bad result type", hr._result->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<huginn::HInteger*>( hr._result.raw() )->value(), 7 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "run non-main function" )
	HHuginn h;
	HStringStream ss;
	ss <<
		"add(a,b){\n"
		"return ( a + b );\n"
		"}\n"
		"main() {\n"
		"return ( -1 );\n"
		"}\n";
	h.load( ss );
	h.preprocess();
	if ( ! h.parse() ) {
		ENSURE_EQUALS( "parsing failed", h.error_message(), "" );
	}
	if ( ! h.compile() ) {
		ENSURE_EQUALS( "compilation failed", h.error_message(), "" );
	}
	HHuginn::values_t args;
	args.push_back( h.value( 3 ) );
	args.push_back( h.value( 13 ) );
	HHuginn::value_t res( h.call( "add", args ) );
	ENSURE( "call failed", !! res );
	ENSURE_EQUALS( "call returned wrong type", res->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "call returned wrong value", huginn::get_integer( res ), 16 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "function definitions/calls/default arguments/variadic paramaters/named parameters" )
	ENSURE_EQUALS(
		"function result failed",
		execute( "f(){return(7);}main(){return(f());}" ),
		7
	);
	ENSURE_EQUALS(
		"dafult arguments failed",
		execute(
			"f(a1=-1,a2=-2,a3=-3,a4=-4){\n"
			"return([a1,a2,a3,a4]);\n"
			"}\n"
			"main(){\n"
			"return(f(1,2));\n"
			"}\n"
		),
		"[1, 2, -3, -4]"
	);
	ENSURE_EQUALS(
		"lambda as default argument failed",
		execute(
			"f(x,l=@(y){y;}){l(x);}\n"
			"main(){\n"
			"return([f(1),f(3),f(1,@(x){x*7;}),f(3,@(x){x*13;})]);"
			"}\n"
		),
		"[1, 3, 7, 39]"
	);
	ENSURE_EQUALS(
		"variadic failed",
		execute(
			"f( x, y = 7, args... ){\n"
			"\treturn([x, y, args]);\n"
			"}\n"
			"main(){\n"
			"\treturn((f(1), f(1,2), f(1,2,3,4)));\n"
			"}\n"
		),
		"([1, 7, ()], [1, 2, ()], [1, 2, (3, 4)])"
	);
	ENSURE_EQUALS(
		"variadic unpacking failed",
		execute(
			"f( a, b, c ){\n"
			"\treturn([a, b, c]);\n"
			"}\n"
			"main(){\n"
			"x = ( 1, 2, 3 );\n"
			"\treturn(f(x...));\n"
			"}\n"
		),
		"[1, 2, 3]"
	);
	ENSURE_EQUALS(
		"keyword arguments failed",
		execute(
			"f( x, y = 7, kwArgs::: ){\n"
			"\treturn([x, y, kwArgs]);\n"
			"}\n"
			"main(){\n"
			"\treturn((f(1), f(1,2), f(1,2,a:3,b:4)));\n"
			"}\n"
		),
		"([1, 7, {}], [1, 2, {}], [1, 2, {\"a\": 3, \"b\": 4}])"
	);
	ENSURE_EQUALS(
		"keyword arguments unpacking failed",
		execute(
			"f( a, b, c ){\n"
			"\treturn([a, b, c]);\n"
			"}\n"
			"main(){\n"
			"x = { \"a\": 1, \"b\": 2, \"c\": 3 };\n"
			"\treturn(f(x:::));\n"
			"}\n"
		),
		"[1, 2, 3]"
	);
	ENSURE_EQUALS(
		"variadic and keyword arguments failed",
		execute(
			"f( x, y = 7, args..., kwArgs::: ){\n"
			"\treturn([x, y, args, kwArgs]);\n"
			"}\n"
			"main(){\n"
			"\treturn((f(1), f(1,2), f(1,2,3,4), f(1,a:3), f(1,2,3,4,a:5,b:6)));\n"
			"}\n"
		),
		"([1, 7, (), {}], [1, 2, (), {}], [1, 2, (3, 4), {}], [1, 7, (), {\"a\": 3}], [1, 2, (3, 4), {\"a\": 5, \"b\": 6}])"
	);
	ENSURE_EQUALS(
		"none as default argument failed",
		execute(
			"f( x,y = none, z = none ) {(x, y, z);}\n"
			"main(){\n"
			"return([f(1)+f(2,3)+f(4,5,6)]);"
			"}\n"
		),
		"[(1, none, none, 2, 3, none, 4, 5, 6)]"
	);
	ENSURE_EQUALS(
		"user defined functor",
		execute(
			"class Functor {\n"
			"call(x) {\n"
			"return ( x * x );\n"
			"}\n"
			"}\n"
			"main(){\n"
			"f = Functor();\n"
			"return(f(2));"
			"}\n"
		),
		"4"
	);
	ENSURE_EQUALS(
		"forwarding failed",
		execute(
			"bar( a, b, args..., kwArgs::: ) {\n"
			"return ((a, b, args, kwArgs));\n"
			"}\n"
			"foo( a, b, args..., kwArgs::: ) {\n"
			"return (bar(a, b, args..., kwArgs:::));\n"
			"}\n"
			"main(){\n"
			"return(foo(1, 2, 3, 4, x:5, y: 6));"
			"}\n"
		),
		"(1, 2, (3, 4), {\"x\": 5, \"y\": 6})"
	);
	ENSURE_EQUALS(
		"forward and expand failed",
		execute(
			"bar( a, b, args..., kwArgs::: ) {\n"
			"return ((a, b, args, kwArgs));\n"
			"}\n"
			"foo( a, b, c, d, e, f, args..., kwArgs::: ) {\n"
			"return (bar(a, b, c, d, args..., kwArgs:::, e: e, f: f));\n"
			"}\n"
			"main(){\n"
			"return(foo(1, 2, 3, 4, 5, 6, 7, 8, x:9, y: 0));"
			"}\n"
		),
		"(1, 2, (3, 4, 7, 8), {\"x\": 9, \"y\": 0, \"e\": 5, \"f\": 6})"
	);
TUT_TEARDOWN()

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

TUT_UNIT_TEST( "exceptions" )
	ENSURE_EQUALS(
		"exception failed",
		execute(
			"main(){\n"
			"r=none;\n"
			"try{\n"
			"1/0;\n"
			"}catch(ArithmeticException e) {\n"
			"ce = copy(e);\n"
			"f=ce.trace()[0];"
			"r=[ce.message(),ce.where(),ce.what(),f.file(),f.line(),f.column(),f.context(),string(f)];\n"
			"}\n"
			"return(r);\n"
			"}\n" ),
		"[\"*anonymous stream*:4:2: Division by zero.\", \"*anonymous stream*:4:2\", \"Division by zero.\", \"*anonymous stream*\", 4, 2, \"main\", \"*anonymous stream*:4:2:main\"]"
	);
	ENSURE_EQUALS(
		"StackFrameInfo copy succeeded",
		execute_except(
			"main() {\n"
			"\tcopy(Exception(\"\").trace()[0]);\n"
			"}\n"
		),
		"*anonymous stream*:2:6: Copy semantics is not supported on StackFrameInfo."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "function ref" )
	ENSURE_EQUALS( "function ref failed", execute( "f(){return(\"x\");}g(){return(f);}main(){return(g()());}" ), "\"x\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "lambda, closure" )
	ENSURE_EQUALS( "lambda failed", execute( "main(){s=[\"fail\"];l=@(x){x[0]=\"ok\";};l(s);return(s[0]);}" ), "\"ok\"" );
	ENSURE_EQUALS(
		"closure failed",
		execute(
			"main(){\n"
			"a=2;\n"
			"b=7;\n"
			"x=@[a,b](c){(a-b)*c;};\n"
			"return(x(4));\n"
			"}\n"
		),
		"-20"
	);
	ENSURE_EQUALS(
		"inline closure failed",
		execute(
			"main(){\n"
			"x=@[a:2,b:7](c){(a-b)*c;};\n"
			"return(x(4));\n"
			"}\n"
		),
		"-20"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "ternary" )
	ENSURE_EQUALS( "ternary failed", execute( "main(){a=\"A\";b=\"B\";q=7;x=q>5?(a=\"1\"):(b=\"2\");return(a+b+x);}" ), "\"1B1\"" );
	ENSURE_EQUALS( "ternary failed", execute( "main(){a=\"A\";b=\"B\";q=7;x=q<5?(a=\"1\"):(b=\"2\");return(a+b+x);}" ), "\"A22\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "tuple unpacking" )
	ENSURE_EQUALS(
		execute(
			"main(){\n"
			"x, y = ( 0, 1 );\n"
			"return([x, y]);\n"
			"}\n"
		),
		"[0, 1]"
	);
	ENSURE_EQUALS(
		execute(
			"main(){\n"
			"x = 0;\n"
			"y = 1;\n"
			"x, y = ( y, x );\n"
			"return([x, y]);\n"
			"}\n"
		),
		"[1, 0]"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "short circuit in boolean `and`" )
	char const p0[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) && ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T && T)", execute( p0 ), "\"12T\"" );
	char const p1[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) && ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T && F)", execute( p1 ), "\"12F\"" );
	char const p2[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) && ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F && T)", execute( p2 ), "\"10F\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "short circuit in boolean `or`" )
	char const p0[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) || ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F || T)", execute( p0 ), "\"12T\"" );
	char const p1[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) || ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T || F)", execute( p1 ), "\"10T\"" );
	char const p2[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 0 ) || ( ( b = 2 ) > 0 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (T || T)", execute( p2 ), "\"10T\"" );
	char const p3[] =
		"main() {"
		" a = 0;"
		" b = 0;"
		" x = ( ( a = 1 ) > 2 ) || ( ( b = 2 ) > 3 );"
		" return ( string( a ) + string( b ) + ( x ? \"T\" : \"F\" ) );"
		"}"
	;
	ENSURE_EQUALS( "ternary failed (F || F)", execute( p3 ), "\"12F\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean xor" )
	char const p[] =
		"main() {"
		" a = 1;"
		" b = 2;"
		" w = ( a == 1 ) ^^ ( b == 2 );"
		" x = ( a == 1 ) ^^ ( b == 0 );"
		" y = ( a == 0 ) ^^ ( b == 2 );"
		" z = ( a == 0 ) ^^ ( b == 0 );"
		" s = \"\";"
		" s = s + ( w ? \"T\" : \"F\" );"
		" s = s + ( x ? \"T\" : \"F\" );"
		" s = s + ( y ? \"T\" : \"F\" );"
		" s = s + ( z ? \"T\" : \"F\" );"
		" return ( s );"
		"}"
	;
	ENSURE_EQUALS( "boolean xor fqailed", execute( p ), "\"FTTF\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "print" )
	HHuginn h;
	HStringStream src( "main(){print(\"Hello World!\\n\");print(13);print(3.14);print($2.71);print('X');print(true);return(7);}" );
	HStringStream out;
	h.set_output_stream( out );
	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile() );
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<huginn::HInteger*>( r.raw() )->value(), 7 );
	ENSURE_EQUALS( "print failed", out.string(), "Hello World!\n133.142.71X1" );
	ENSURE_EQUALS(
		"print of bad type succeded",
		execute_except(
			"main(){print(size);}"
		),
		"*anonymous stream*:1:13: Printing `*function_reference*`s is not supported."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "input" )
	HHuginn h;
	HStringStream src( "main(){s=input();print(\"[\"+s+\"]\");return(13);}" );
	HStringStream in( "Amok" );
	HStringStream out;
	h.set_input_stream( in );
	h.set_output_stream( out );
	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile() );
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<huginn::HInteger*>( r.raw() )->value(), 13 );
	ENSURE_EQUALS( "print failed", out.string(), "[Amok]" );
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

namespace {
void notify( int val_, int& dest_ ) {
	dest_ = val_;
}
}

TUT_UNIT_TEST( "reference cycle garbage collection" )
	/* `list` */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int val( 0 );
		register_function( *h, "notify", call( notify, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"garbage collection of `list` failed",
			execute(
				h,
				"class A{destructor(){notify(1);}}"
				"main(){"
				"l=[A()];"
				"l.push(l);"
				"none;"
				"}"
			),
			"none"
		);
		h.reset();
		ENSURE_EQUALS( "destuctor from `list` was not invoked", val, 1 );
	}
	/* `deque` */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int val( 0 );
		register_function( *h, "notify", call( notify, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"garbage collection of `deque` failed",
			execute(
				h,
				"class A{destructor(){notify(2);}}"
				"main(){"
				"d=deque(A());"
				"d.push(d);"
				"none;"
				"}"
			),
			"none"
		);
		h.reset();
		ENSURE_EQUALS( "destuctor from `deque` was not invoked", val, 2 );
	}
	/* `dict` */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int val( 0 );
		register_function( *h, "notify", call( notify, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"garbage collection of `dict` (by value) failed",
			execute(
				h,
				"class A{destructor(){notify(3);}}"
				"main(){"
				"d=[0:A()];"
				"d[1] = d;"
				"none;"
				"}"
			),
			"none"
		);
		h.reset();
		ENSURE_EQUALS( "destuctor from `dict` was not invoked", val, 3 );
	}
	/* `lookup` */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int val( 0 );
		register_function( *h, "notify", call( notify, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"garbage collection of `lookup` (by value) failed",
			execute(
				h,
				"class A{destructor(){notify(4);}}"
				"main(){"
				"l={0:A()};"
				"l[none] = l;"
				"none;"
				"}"
			),
			"none"
		);
		h.reset();
		ENSURE_EQUALS( "destuctor from `lookup` was not invoked", val, 4 );
	}
	/* `set` */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int val( 0 );
		register_function( *h, "notify", call( notify, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"garbage collection of `set` failed",
			execute(
				h,
				"class A{destructor(){notify(5);}hash(){77777;}}"
				"main(){"
				"s=set(A());"
				"s.insert(s);"
				"none;"
				"}"
			),
			"none"
		);
		h.reset();
		ENSURE_EQUALS( "destuctor from `set` was not invoked", val, 5 );
	}
	/* `set` */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int val( 0 );
		register_function( *h, "notify", call( notify, _1, ref( val ) ), "notify" );
		ENSURE_EQUALS(
			"garbage collection of `Objects` failed",
			execute(
				h,
				"class Node {"
				"_other = none;"
				"destructor(){notify(6);}"
				"}"
				"main(){"
				"n=Node();"
				"n._other = n;"
				"none;"
				"}"
			),
			"none"
		);
		h.reset();
		ENSURE_EQUALS( "destuctor from `Objects` was not invoked", val, 6 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "inheritance from built-in" )
	ENSURE_EQUALS(
		"inheritance from built-in failed",
		execute(
			"class TressException : Exception {"
			"constructor(){"
			"super.constructor( \"TressException\" );"
			"}"
			"}"
			"main(){"
			"res = none;"
			"try{"
			"throw TressException();"
			"} catch ( Exception e ) {"
			"res = e;"
			"}"
			"return([res.message(),res.trace()]);"
			"}"
		),
		"[\"*anonymous stream*:1:66: TressException\", [*anonymous stream*:1:66:constructor, *anonymous stream*:1:131:main]]"
	);
	ENSURE_EQUALS(
		"method on uninitialized base succeded",
		execute_except(
			"class TressException : Exception {"
			"create(){"
			"super.constructor( \"TressException\" );"
			"create;"
			"}"
			"}"
			"main(){"
			"res = none;"
			"try{"
			"throw TressException();"
			"} catch ( Exception e ) {"
			"res = e;"
			"}"
			"return([res.message(),res.trace()]);"
			"}"
		),
		"*anonymous stream*:1:189: Base class `Exception` is not initialized."
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
			"\ttry {\n"
			"\t\tl = [0];"
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
			"1/0;"
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

TUT_UNIT_TEST( "OPTIMIZE flag" )
	ENSURE_EQUALS(
		"assert did not execute",
		execute(
			"main() {\n"
			"\tx = 13;\n"
			"\tassert( ( x = 7 ) > 0, \"oops\" );\n"
			"\treturn( x );\n"
			"}"
		),
		"7"
	);
	HHuginn::ptr_t h( make_pointer<HHuginn>( HHuginn::COMPILER::OPTIMIZE ) );
	ENSURE_EQUALS(
		"OPTIMIZE flag failed",
		execute(
			h,
			"main() {\n"
			"\tx = 13;\n"
			"\tassert( ( x = 7 ) > 0, \"oops\" );\n"
			"\treturn( x );\n"
			"}"
		),
		"13"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "empty return" )
	ENSURE_EQUALS(
		"empty return failed",
		execute(
			"f(l_) {\n"
			"l_.push(1);\n"
			"return;\n"
			"l_.push(2);\n"
			"return(3);\n"
			"}\n"
			"main(){\n"
			"l = list();\n"
			"s = string(type(f(l)));\n"
			"s = s + string(size(l));\n"
			"s = s + string(l[0]);\n"
			"return(s);\n"
			"}",
			HHuginn::COMPILER::BE_SLOPPY
		),
		"\"*none*11\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "boolean not" )
	ENSURE_EQUALS(
		"boolean not failed (lval)",
		execute(
			"main(){s=\"\";a=0==1;\n"
			"if(!a) {\n"
			"s=\"ok\";"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\"ok\""
	);
	ENSURE_EQUALS(
		"boolean not failed (rval)",
		execute(
			"main(){s=\"\";a=0;\n"
			"if(!(a==1)) {\n"
			"s=\"ok\";"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\"ok\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "operator precedence" )
	ENSURE_EQUALS(
		"boolean not failed",
		execute(
			"main(){"
			"s=\"\";"
			"s+=string(2-3+5);s+=\":\";"
			"s+=string(2+3*5);s+=\":\";"
			"s+=string($2+$3^$5);s+=\":\";"
			"s+=string($2*$3^$5);s+=\":\";"
			"s+=string($5^$3^$2);s+=\":\";"
			"s+=string(7/2*5);s+=\":\";"
			"s+=string(3%2*5);s+=\":\";"
			"x=$3;"
			"s+=string(-x!);s+=\":\";"
			"s+=string(|-2|-|-3|);s+=\":\";"
			"s+=string($2+$3!);s+=\":\";"
			"return(s);"
			"}"
		),
		"\"4:17:245:486:1953125:15:5:-6:-1:8:\""
	);
	ENSURE_EQUALS(
		"boolean not failed",
		execute(
			"main(){"
			"s=\"\";"
			"s+=string(2-(3+5));s+=\":\";"
			"s+=string((2+3)*5);s+=\":\";"
			"s+=string(($2+$3)^$5);s+=\":\";"
			"s+=string(($2*$3)^$5);s+=\":\";"
			"s+=string(($2^$3)^$5);s+=\":\";"
			"s+=string(7/(2*3));s+=\":\";"
			"s+=string(3%(2*5));s+=\":\";"
			"x=$-3;"
			"s+=string((-x)!);s+=\":\";"
			"s+=string(($2+$3)!);s+=\":\";"
			"return(s);"
			"}"
		),
		"\"-6:25:3125:7776:32768:1:3:6:120:\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "are constants constant? (immutable)" )
	ENSURE_EQUALS(
		"constant in assignment was modified",
		execute(
			"main(){"
			"s=\"\";"
			"for(e:[1,1]) {"
			"x=0;"
			"x+=e;"
			"s+=string(x);"
			"}"
			"return(s);"
			"}"
		),
		"\"11\""
	);
	ENSURE_EQUALS(
		"constant in function call was modified",
		execute(
			"inc(x){"
			"x+=1;"
			"return(x);"
			"}"
			"main(){"
			"s=\"\";"
			"for(e:[0,0]) {"
			"x=inc(0);"
			"x+=e;"
			"s+=string(x);"
			"}"
			"return(s);"
			"}"
		),
		"\"11\""
	);
	ENSURE_EQUALS(
		"constant in function call (second arg) was modified",
		execute(
			"inc(x, y){"
			"y+=x;"
			"return(y);"
			"}"
			"main(){"
			"s=\"\";"
			"for(e:[1,1]) {"
			"x=inc(e, 0);"
			"s+=string(x);"
			"}"
			"return(s);"
			"}"
		),
		"\"11\""
	);
	ENSURE_EQUALS(
		"constant as map's key was modified",
		execute(
			"f(m){"
			"m[0]=0;"
			"}"
			"main(){"
			"m=lookup();"
			"f(m);"
			"for(k:m){"
			"k+=1;"
			"}"
			"m2=dict();"
			"f(m2);"
			"s=\"\";"
			"for(k:m2){"
			"s=string(k);"
			"}"
			"return(s);"
			"}"
		),
		"\"0\""
	);
	ENSURE_EQUALS(
		"constant from ternary true path was modified",
		execute(
			"f() {\n"
			"  x = true ? 0 : 7;\n"
			"  x += 1;\n"
			"  x;\n"
			"}\n"
			"\n"
			"main() {\n"
			"  f();\n"
			"  f();\n"
			"  return (f());\n"
			"}\n"
		),
		"1"
	);
	ENSURE_EQUALS(
		"constant from ternary false path was modified",
		execute(
			"f() {\n"
			"  x = false ? 7 : 0;\n"
			"  x += 1;\n"
			"  x;\n"
			"}\n"
			"\n"
			"main() {\n"
			"  f();\n"
			"  f();\n"
			"  return (f());\n"
			"}\n"
		),
		"1"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "assignment/subscript regressions check" )
	ENSURE_EQUALS(
		"assignment subscript mix failed",
		execute(
			"main() {"
			"  H = {none:0};"
			"  h0 = {};"
			"  h1 = {};"
			"  h2 = {};"
			"  h3 = {};"
			"  h4 = {};"
			"  h5 = {};"
			"  h6 = {};"
			"  h7 = {};"
			"  h8 = {};"
			"  h9 = {};"
			"  zero = 0;"
			""
			"  a = h0[1] = b = h1[h2[zero + 2] = H[none]] = c = h3[d = h4[3 + zero] = h5[h6[4] = e = H[zero + 5] = h7[6] = H[none]] = h8[H[none]] = 7 + zero] = f = g = h9[8] = h = 9;"
			""
			"  r = ( H, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, a, b, c, d, e, f, g, h );"
			"  return ( r );"
			"}"
		),
		"({none: 0, 5: 0}, {1: 9}, {0: 9}, {2: 0}, {7: 9}, {3: 7}, {0: 7}, {4: 0}, {6: 0}, {0: 7}, {8: 9}, 9, 9, 9, 7, 0, 9, 9, 9)"
	);
	ENSURE_EQUALS(
		"assignment subscript mix on user defined failed",
		execute(
			"class Sub {_d = {};constructor(d={}){_d=d;}subscript(k){_d[k];}set_subscript(k,v){_d[k]=v;} to_string(){string(_d);}}"
			"main() {"
			"  H = Sub({none:0});"
			"  h0 = Sub();"
			"  h1 = Sub();"
			"  h2 = Sub();"
			"  h3 = Sub();"
			"  h4 = Sub();"
			"  h5 = Sub();"
			"  h6 = Sub();"
			"  h7 = Sub();"
			"  h8 = Sub();"
			"  h9 = Sub();"
			"  zero = 0;"
			""
			"  a = h0[1] = b = h1[h2[zero + 2] = H[none]] = c = h3[d = h4[3 + zero] = h5[h6[4] = e = H[zero + 5] = h7[6] = H[none]] = h8[H[none]] = 7 + zero] = f = g = h9[8] = h = 9;"
			""
			"  r = ( H, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, a, b, c, d, e, f, g, h );"
			"  return ( r );"
			"}"
		),
		"({none: 0, 5: 0}, {1: 9}, {0: 9}, {2: 0}, {7: 9}, {3: 7}, {0: 7}, {4: 0}, {6: 0}, {0: 7}, {8: 9}, 9, 9, 9, 7, 0, 9, 9, 9)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "optimized out scopes regressions checks" )
	ENSURE_EQUALS(
		"`break` from `while` with optimized-out scope",
		execute(
			"main() {"
			"	while ( true ) {"
			"		if ( true ) {"
			"			break;"
			"		}"
			"	}"
			"}"
		),
		"none"
	);
	ENSURE_EQUALS(
		"`throw` from `while` with optimized-out scope",
		execute_except(
			"foo() {"
			"	while ( true ) {"
			"		if ( true ) {"
			"			throw Exception(\"EX\");"
			"		}"
			"	}"
			"}"
			"main(){foo();}"
		),
		"*anonymous stream*:1:43: Uncaught Exception: EX"
	);
	ENSURE_EQUALS(
		"`return` from `while` with optimized-out scope",
		execute(
			"foo() {"
			"	while ( true ) {"
			"		if ( true ) {"
			"			return ( 7 );"
			"		}"
			"	}"
			"}"
			"main(){foo();}"
		),
		"7"
	);
	ENSURE_EQUALS(
		"`break` from `for` with optimized-out scope",
		execute(
			"main() {"
			"	for ( a : [0] ) {"
			"		if ( true ) {"
			"			break;"
			"		}"
			"	}"
			"}"
		),
		"none"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "bugs regressions checks" )
	ENSURE_EQUALS(
		"access to variable defined in unused (due to short-circuiting) path of expression",
		execute(
			"main() {\n"
			"x = 0;\n"
			"y = 0;\n"
			"true ? 0 : x = 1;\n"
			"false ? 0 : y = 1;\n"
			"(x,y);\n"
			"}\n"
		),
		"(0, 1)"
	);
	ENSURE_EQUALS(
		"error position from nested algorithms",
		execute_except(
			"import Algorithms as algo;\n"
			"import FileSystem as fs;\n"
			"\n"
			"process( stream_ ) {\n"
			"	processor = algo.filter(\n"
			"		algo.map(\n"
			"			stream_,\n"
			"			string.strip\n"
			"		),\n"
			"		@( item ){ size( item ) > 0; }\n"
			"	);\n"
			"	return ( processor );\n"
			"}\n"
			"\n"
			"main() {\n"
			"	f = fs.open( \"./data/lines-latin2.txt\", fs.OPEN_MODE.READ );\n"
			"	l = algo.materialize(\n"
			"		process( f ),\n"
			"		list\n"
			"	);\n"
			"	return ( l );\n"
			"}\n\n"
		),
		"*anonymous stream*:17:22: Uncaught ConversionException: Invalid UTF-8 tail sequence at: 6"
	);
	ENSURE_EQUALS(
		"exception while new key-value pair is created via multiple assignment",
		execute(
			"main(){"
			"a = {};"
			"try {"
			"a[0] = a[1/0] = 0;"
			"} catch ( Exception e ) {"
			"}"
			"b = dict();"
			"try {"
			"b[0] = b[1/0] = 0;"
			"} catch ( Exception e ) {"
			"}"
			"return ( (a,b) );"
			"}"
		),
		"({}, dict())"
	);
	ENSURE_EQUALS(
		"session id assignment for inlined scopes (scheme)",
		execute(
			"main() {"
			"	if ( false ) {"
			"		@(){};"
			"	} else {"
			"		x = 7;"
			"		return ( x );"
			"	}"
			"	return ( 0 );"
			"}"
		),
		"7"
	);
	ENSURE_EQUALS(
		"function arguments caching mechanism",
		execute(
			"main(){"
			"{[0],string};"
			"}"
		),
		"{[0], string}"
	);
	ENSURE_EQUALS(
		"recursive user destructor",
		execute(
			"class Crash {\n"
			"	_next = none;\n"
			"	_prev = none;\n"
			"}\n"
			"\n"
			"main() {\n"
			"	handle = none;\n"
			"	/* scope */ {\n"
			"		n1 = Crash();\n"
			"		n2 = Crash();\n"
			"		n1._next = n2;\n"
			"		n2._prev = n1;\n"
			"		handle = observe( n1 );\n"
			"	}\n"
			"	use( handle )._next = none;\n"
			"	return ( 0 );\n"
			"}\n"
		),
		"0"
	);
	ENSURE_EQUALS(
		"invalid destructor signature",
		execute_except(
			"class Crash {\n"
			"	_name = none;\n"
			"	_next = none;\n"
			"	_prev = none;\n"
			"	constructor( name_ ) {\n"
			"		_name = name_;\n"
			"		_name.clear();\n"
			"	}\n"
			"	destructor( name_ ) {\n"
			"	}\n"
			"}\n"
			"\n"
			"main() {\n"
			"	handle = none;\n"
			"	/* scope */ {\n"
			"		n1 = Crash( \"one\" );\n"
			"		n2 = Crash( \"two\" );\n"
			"		n1._next = n2;\n"
			"		n2._prev = n1;\n"
			"		handle = observe( n1 );\n"
			"	}\n"
			"	use( handle )._next = none;\n"
			"	return ( 0 );\n"
			"}\n"
		),
		"*anonymous stream*:1:1: In call to `destructor()`, missing required positional argument: `name_`."
	);
	ENSURE_EQUALS(
		"throw from destructor",
		execute_except(
			"class Crash {\n"
			"	_name = none;\n"
			"	constructor( name_ ) {\n"
			"		_name = name_;\n"
			"	}\n"
			"	destructor() {\n"
			"		throw Exception( \"Boom!: \" + _name );\n"
			"	}\n"
			"}\n"
			"\n"
			"main() {\n"
			"	res = none;\n"
			"	try {\n"
			"		Crash( \"one\" );\n"
			"	} catch ( Exception e ) {\n"
			"		res = e.message();\n"
			"	}\n"
			"	return ( res );\n"
			"}\n"
		),
		"*anonymous stream*:7:3: Uncaught Exception from destructor: Boom!: one"
	);
	ENSURE_EQUALS(
		"definition of many variables in one expression failed",
		execute(
			"main(){"
			"a=b=c=d=e=f=g=h=i=j=k=l=m=n=o=p=q=r=s=t=u=v=w=x=y=z=1;"
			"return(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z);"
			"}"
		),
		"26"
	);
	ENSURE_EQUALS(
		"definition of many variables in one expression after dynamic import of simplistic code failed",
		execute(
			"import Introspection as intro;"
			"foo(){"
			"a=b=c=d=e=f=g=h=i=j=k=l=m=n=o=p=q=r=s=t=u=v=w=x=y=z=1;"
			"return(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z);"
			"}"
			"main() {"
			"intro.import(\"Short\").foo(0,0);"
			"foo();"
			"}",
			{ "data" }
		),
		"26"
	);
	ENSURE_EQUALS(
		"order of operations failed",
		execute(
			"main(){"
			"return($-284650292555885^$3+$66229832190556^$3+$283450105697727^$3);"
			"}"
		),
		"$74"
	);
	ENSURE_EQUALS(
		"invalid construction from type(expr)(...) succeeded",
		execute_except(
			"import OperatingSystem as os;\n"
			"main(){\n"
			"s=os.stdout();\n"
			"type(s)();\n"
			"}\n"
		),
		"*anonymous stream*:4:8: Explicit construction of class `Stream` objects (instances) is forbidden."
	);
	ENSURE_EQUALS(
		"out of order named parameter hash",
		execute(
			"f(a,b,μ,σ){"
			"[a,b,μ,σ];"
			"}"
			"main(){"
			"return(f(1,2,μ:3,σ:4));"
			"}"
		),
		"[1, 2, 3, 4]"
	);
	ENSURE_EQUALS(
		"skipped positional argument with named parameters",
		execute(
			"long(x,y,p=0,q=1,r=2,s=3,t=4,args...,kwArgs:::) {"
			"[x,y,p,q,r,s,t,args,kwArgs];"
			"}"
			"main(){"
			"return(long(11,22,q:7,s:9));"
			"}"
		),
		"[11, 22, 0, 7, 2, 9, 4, (), {}]"
	);
	ENSURE_EQUALS(
		"package defined enumeration hidden by enum in global namespace",
		execute(
			"import Terminal as term;"
			"enum COLOR { RED, GREEN, BLUE }"
			"main(){"
			"return( ( term.COLOR.BRIGHTBLUE, COLOR.BLUE ) );"
			"}"
		),
		"(term.COLOR.BRIGHTBLUE, COLOR.BLUE)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "bound call as field value" )
	ENSURE_EQUALS(
		"bound call as field value failed",
		execute(
			"class A{_val=none;constructor(val_){_val=val_;}do(val_){return(_val*val_);}}"
			"class B{_call=none;constructor(call_){_call=call_;}do(val_){return(_call(val_));}}"
			"main(){"
			"a=A(7);"
			"return (B(a.do).do(13));"
			"}"
		),
		"91"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Stream" )
	ENSURE_EQUALS(
		"Stream.iterator failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"res=[];"
			"for ( l : fs.open(\"./data/nl.txt\",fs.OPEN_MODE.READ)) {\n"
			"res.push(l.strip());"
			"}\n"
			"return(res);\n"
			"}\n"
		),
		"[\"Ala\", \"ma\", \"kota.\", \"\"]"
	);
	ENSURE_EQUALS(
		"Stream.read failed",
		execute(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(fs.open(\"./data/nl.txt\",fs.OPEN_MODE.READ).read_string(100));\n"
			"}\n"
		),
		"\"Ala\nma\nkota.\n\n\""
	);
	ENSURE_EQUALS(
		"Stream copy succeeded",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(copy(fs.open(\"./data/nl.txt\",fs.OPEN_MODE.READ)));\n"
			"}\n"
		),
		"*anonymous stream*:3:12: Copy semantics is not supported on Stream."
	);
	ENSURE_EQUALS(
		"Stream size succeeded",
		execute_except(
			"import FileSystem as fs;\n"
			"main() {\n"
			"return(size(fs.open(\"./data/nl.txt\",fs.OPEN_MODE.READ)));\n"
			"}\n"
		),
		"*anonymous stream*:3:12: Getting size of `Stream` is an invalid operation."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "standard streams" )
	HHuginn h;
	HStringStream src(
		"import OperatingSystem as os;"
		"main() {"
		"os.stdout().write_line(\"stdout\");"
		"os.stderr().write_line(\"stderr\");"
		"os.stdlog().write_line(\"stdlog\");"
		"return (integer(os.stdin().read_line()));"
		"}"
	);
	HStreamInterface::ptr_t inS( make_pointer<HStringStream>() );
	HStreamInterface::ptr_t outS( make_pointer<HStringStream>() );
	HStreamInterface::ptr_t errS( make_pointer<HStringStream>() );
	HStreamInterface::ptr_t logS( make_pointer<HStringStream>() );
	h.set_input_stream( inS );
	h.set_output_stream( outS );
	h.set_error_stream( errS );
	h.set_log_stream( logS );
	ENSURE_EQUALS( "bad smart input", &h.input_stream(), inS.raw() );
	ENSURE_EQUALS( "bad smart output", &h.output_stream(), outS.raw() );
	ENSURE_EQUALS( "bad smart error", &h.error_stream(), errS.raw() );
	ENSURE_EQUALS( "bad smart log", &h.log_stream(), logS.raw() );
	HStringStream in;
	HStringStream out;
	HStringStream err;
	HStringStream log;
	h.set_input_stream( in );
	h.set_output_stream( out );
	h.set_error_stream( err );
	h.set_log_stream( log );
	ENSURE_EQUALS( "bad raw input", &h.input_stream(), &in );
	ENSURE_EQUALS( "bad raw output", &h.output_stream(), &out );
	ENSURE_EQUALS( "bad raw error", &h.error_stream(), &err );
	ENSURE_EQUALS( "bad raw log", &h.log_stream(), &log );

	h.load( src );
	h.preprocess();
	ENSURE( "parse failed", h.parse() );
	ENSURE( "compile", h.compile() );
	in << "123";
	ENSURE( "execute", h.execute() );
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "stdin", static_cast<huginn::HInteger*>( r.raw() )->value(), 123 );
	ENSURE_EQUALS( "stdout failed", out.string(), "stdout" );
	ENSURE_EQUALS( "stderr failed", err.string(), "stderr" );
	ENSURE_EQUALS( "stdlog failed", log.string(), "stdlog" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "modules" )
	ENSURE_EQUALS(
		"using module failed",
		execute(
			"import Mathematics as M;\n"
			"import Tress as tress;\n"
			"main() {\n"
			"return ([\n"
			"tress.rectangle(2,3),\n"
			"tress.diagonal(3,4),\n"
			"tress.wrap(\"yaal\"),\n"
			"tress.ENUM.TWO,\n"
			"tress.Object($7),\n"
			"type(M),\n"
			"tress.algo().max([ 1, 2, 3 ])\n"
			"]);"
			"}",
			{ "./data/" }
		),
		"[6, 5.0, \"#yaal#\", tress.ENUM.TWO, 7, Mathematics, 3]"
	);
	ENSURE_EQUALS(
		"invalid field access failure",
		execute_except(
			"import Tress as tress;\n"
			"main() {\n"
			"tress.bug(0);\n"
			"}\n",
			{ "./data/" }
		),
		"./data//Tress.hgn:60:15: `Mathematics` does not have `square_foot` member (did you mean `square_root`?)."
	);
	ENSURE_EQUALS(
		"using subtree module failed",
		execute(
			"import sub.Sub as ss;"
			"main() {"
			"return ( \"{}: {}\".format( type( ss ), ss.main() ) );"
			"}",
			{ "./data/" }
		),
		"\"sub.Sub: 7\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "from ... import ..." )
	ENSURE_EQUALS(
		"from ... import sym, sym  failed",
		execute(
			"from Algorithms import materialize, range;"
			"main() {"
			"return ( materialize( range( 5 ), list ) );"
			"}"
		),
		"[0, 1, 2, 3, 4]"
	);
	ENSURE_EQUALS(
		"from ... import *  failed",
		execute(
			"from Algorithms import *;"
			"main() {"
			"return ( materialize( range( 5 ), list ) );"
			"}"
		),
		"[0, 1, 2, 3, 4]"
	);
	ENSURE_EQUALS(
		"from ... import * (enum)",
		execute(
			"from Mathematics import *;"
			"from Text import *;"
			"main() {"
			"return ( ( Randomizer.DISTRIBUTION.NORMAL, CHARACTER_CLASS.GREEK ) );"
			"}"
		),
		"(Randomizer.DISTRIBUTION.NORMAL, CHARACTER_CLASS.GREEK)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "binary packages" )
	ENSURE_EQUALS(
		"binary package failed",
		execute(
			"import Greeter as g;\n"
			"main() {\n"
			"return( g.greet(\"Huginn\") );\n"
			"}\n",
			{ "./data" }
		),
		"\"Hello, Huginn\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "create Huginn value from C++" )
	/* main types */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		h->add_argument( h->value( 7LL ) );
		h->add_argument( h->value( 3.14159L ) );
		h->add_argument( h->value( "2.718281828459045"_yn ) );
		h->add_argument( h->value( "Huginn"_ys ) );
		h->add_argument( h->value( 10003_ycp ) );
		h->add_argument( h->value( true ) );
		h->add_argument( h->value( false ) );
		h->add_argument( h->value( static_cast<void const*>( nullptr ) ) );
		h->add_argument( h->value( int_array_t{ 1, 2, 3, 4 } ) );
		h->add_argument( h->value( int_deque_t{ 5, 6, 7, 8 } ) );
		ENSURE_EQUALS(
			"binary package failed",
			execute(
				h,
				"main( argv_ ) {\n"
				"return( argv_ );\n"
				"}\n"
			),
			"[7, 3.14159, $2.718281828459045, \"Huginn\", '✓', true, false, none, [1, 2, 3, 4], deque(5, 6, 7, 8)]"
		);
	}
	/* forwarded types */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		h->add_argument( "wrong" );
		h->clear_arguments();
		h->add_argument( h->value( static_cast<int short>( 1 ) ) );
		h->add_argument( h->value( static_cast<int short unsigned>( 2 ) ) );
		h->add_argument( h->value( static_cast<int>( 3 ) ) );
		h->add_argument( h->value( static_cast<int unsigned>( 4 ) ) );
		h->add_argument( h->value( static_cast<int long>( 5 ) ) );
		h->add_argument( h->value( static_cast<int long unsigned>( 6 ) ) );
		h->add_argument( h->value( static_cast<int long long>( 7 ) ) );
		h->add_argument( h->value( static_cast<int long long unsigned>( 8 ) ) );
		h->add_argument( h->value( static_cast<float>( 3.14 ) ) );
		h->add_argument( h->value( static_cast<double>( 3.1415 ) ) );
		h->add_argument( h->value( static_cast<double long>( 3.14159265 ) ) );
		h->add_argument( h->value( "yaal" ) );
		h->add_argument( h->value( nullptr ) );
		ENSURE_EQUALS(
			"binary package failed",
			execute(
				h,
				"main( argv_ ) {\n"
				"argv_[8] = real(string(argv_[8])[:4]);\n"
				"return( argv_ );\n"
				"}\n"
			),
			"[1, 2, 3, 4, 5, 6, 7, 8, 3.14, 3.1415, 3.14159265, \"yaal\", none]"
		);
	}
TUT_TEARDOWN()

namespace {
HHuginn::value_t native_add( huginn::HThread* thread_, HHuginn::value_t*, HHuginn::values_t& values_, int position_ ) {
	verify_signature( "native_add", values_, { HHuginn::TYPE::INTEGER, HHuginn::TYPE::INTEGER }, thread_, position_ );
	return ( thread_->runtime().object_factory()->create_integer( get_integer( values_[0] ) + get_integer( values_[1] ) ) );
}
}

TUT_UNIT_TEST( "native functions" )
	HHuginn::ptr_t h( make_pointer<HHuginn>() );
	char const doc[] = "( *x*, *y* ) - return sum of *x* and *y*";
	ENSURE_THROW(
		"registering function with restricted name succeeded",
		h->register_function( "print", call( &native_add, _1, _2, _3, _4 ), doc ),
		HHuginn::HHuginnRuntimeException
	);

	h->register_function( "native_add", call( &native_add, _1, _2, _3, _4 ), doc );
	ENSURE_EQUALS(
		"native function failed",
		execute(
			h,
			"main() {\n"
			"return( native_add( 3, 19 ) );\n"
			"}\n"
		),
		"22"
	);
	h->reset();
	ENSURE_EQUALS(
		"native function failed",
		execute_except(
			h,
			"main() {\n"
			"return( native_add( 3, 19. ) );\n"
			"}\n"
		),
		"*anonymous stream*:2:19: native_add() second argument must be an `integer`, not a `real`."
	);
TUT_TEARDOWN()

namespace {
int short add( int short unsigned a, int unsigned b ) {
	return ( static_cast<int short>( a + b ) );
}
double quadratic_equation( double long a, double b, float c ) {
	double d( static_cast<double>( b * b - 4 * a * c ) );
	return ( ( -b - math::square_root( d ) ) / 2. );
}
double long area( int long long x0, int long long unsigned y0, int long x1, int long unsigned y1 ) {
	int w( max( static_cast<int>( x0 ), static_cast<int>( x1 ) ) - min( static_cast<int>( x0 ), static_cast<int>( x1 ) ) );
	int h( max( static_cast<int>( y0 ), static_cast<int>( y1 ) ) - min( static_cast<int>( y0 ), static_cast<int>( y1 ) ) );
	return ( w * h );
}
hcore::HString title( hcore::HString text_ ) {
	if ( ! text_.is_empty() ) {
		text_.lower();
		text_.set_at( 0, code_point_t( static_cast<code_point_t::value_type>( toupper( static_cast<int>( text_.front().get() ) ) ) ) );
	}
	return ( text_ );
}
char const* mid( char const* text_, int short idx_ ) {
	return ( text_ + idx_ );
}
yaal::hcore::HNumber square( yaal::hcore::HNumber const& n_ ) {
	return ( n_ ^ 2 );
}
code_point_t next_cp( code_point_t cp_ ) {
	return ( code_point_t( cp_.get() + 1 ) );
}
char next_ch( char ch_ ) {
	return ( static_cast<char>( ch_ + 1 ) );
}
int short foo5( int short a, int b, int c, int d, int e ) {
	return ( static_cast<int short>( a * b * c * d * e ) );
}
float foo6( int a, int b, int c, int d, int e, int f ) {
	return ( static_cast<float>( a * b * c * d * e * f ) );
}
int unsigned foo7( int a, int b, int c, int d, int e, int f, int g ) {
	return ( static_cast<int unsigned>( a * b * c * d * e * f * g ) );
}
int long unsigned foo8( int long a, int long b, int long c, int long d, int long e, int long f, int long g, int long h ) {
	return ( static_cast<int long unsigned>( a * b * c * d * e * f * g * h ) );
}
int long long unsigned foo9(
	int long long a, int long long b, int long long c, int long long d, int long long e,
	int long long f, int long long g, int long long h, int long long i
) {
	return ( static_cast<int long long unsigned>( a * b * c * d * e * f * g * h * i ) );
}
int long long unsigned foo10(
	int long long a, int long long b, int long long c, int long long d, int long long e,
	int long long f, int long long g, int long long h, int long long i, int long long j
) {
	return ( static_cast<int long long unsigned>( a * b * c * d * e * f * g * h * i * j ) );
}
void fv0( int* r ) {
	*r = 1;
}
void fv1( int* r, int a ) {
	*r = a;
}
void fv2( int* r, int a, int b ) {
	*r = a * b;
}
void fv3( int* r, int a, int b, int c ) {
	*r = a * b * c;
}
void fv4( int* r, int a, int b, int c, int d ) {
	*r = a * b * c * d;
}
void fv5( int* r, int a, int b, int c, int d, int e ) {
	*r = a * b * c * d * e;
}
void fv6( int* r, int a, int b, int c, int d, int e, int f ) {
	*r = a * b * c * d * e * f;
}
void fv7( int* r, int a, int b, int c, int d, int e, int f, int g ) {
	*r = a * b * c * d * e * f * g;
}
void fv8( int* r, int a, int b, int c, int d, int e, int f, int g, int h ) {
	*r = a * b * c * d * e * f * g * h;
}
void fv9(
	int long long* r,
	int long long a, int long long b, int long long c, int long long d, int long long e,
	int long long f, int long long g, int long long h, int long long i
) {
	*r = a * b * c * d * e * f * g * h * i;
}
struct S {
	static int long long r;
	static void fv10(
		int long long a, int long long b, int long long c, int long long d, int long long e,
		int long long f, int long long g, int long long h, int long long i, int long long j
	) {
		r = a * b * c * d * e * f * g * h * i * j;
	}
};
int long long S::r = 0;
}

TUT_UNIT_TEST( "easy function registration" )
	/* getpid */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "getpid", system::getpid, "getpid" );
		ENSURE_EQUALS( "getpid failed", execute( h, "main() { return ( getpid() ); }" ), to_string( system::getpid() ) );
	}
	/* min */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "mid", mid, "get right part of the string" );
		ENSURE_EQUALS( "mid failed", execute( h, "main() { return ( mid( \"acdefghijk\", 6 ) ); }" ), "\"hijk\"" );
	}
	/* square */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "square", square, "calculate square of a number" );
		ENSURE_EQUALS( "square failed", execute( h, "main() { return ( square( $7 ) ); }" ), "$49" );
	}
	/* title */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "title", title, "make string title case" );
		ENSURE_EQUALS( "title failed", execute( h, "main() { return ( title( \"hUgInN\" ) ); }" ), "\"Huginn\"" );
	}
	/* add */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "add", add, "add two objects" );
		ENSURE_EQUALS( "add failed", execute( h, "main() { return ( add( 1, 2 ) ); }" ), "3" );
	}
	/* quadratic_equation */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "quadratic_equation", quadratic_equation, "calculate solution to quadratic equation" );
		ENSURE_EQUALS( "quadratic_equation failed", execute( h, "main() { return ( quadratic_equation( 1., 2., -8. ) ); }" ), "-4.0" );
	}
	/* area */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "area", area, "calculate rectangle area" );
		ENSURE_EQUALS( "area failed", execute( h, "main() { return ( area( 1, 2, 3, 4 ) ); }" ), "4.0" );
	}
	/* next_(cp|ch) */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "next_cp", next_cp, "next code point" );
		register_function( *h, "next_ch", next_ch, "next character" );
		ENSURE_EQUALS( "next_(cp|ch) failed", execute( h, "main() { return ( ( next_cp( 'a' ), next_ch( 'b' ) ) ); }" ), "('b', 'c')" );
	}
	/* foo5 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "foo5", foo5, "foo 5 numbers" );
		ENSURE_EQUALS( "foo5 failed", execute( h, "main() { return ( foo5( 2, 3, 5, 7, 11 ) ); }" ), "2310" );
	}
	/* foo6 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "foo6", foo6, "foo 6 numbers" );
		ENSURE_EQUALS( "foo6 failed", execute( h, "main() { return ( foo6( 2, 3, 5, 7, 11, 13 ) ); }" ), "30030.0" );
	}
	/* foo7 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "foo7", foo7, "foo 7 numbers" );
		ENSURE_EQUALS( "foo7 failed", execute( h, "main() { return ( foo7( 2, 3, 5, 7, 11, 13, 17 ) ); }" ), "510510" );
	}
	/* foo8 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "foo8", foo8, "foo 8 numbers" );
		ENSURE_EQUALS( "foo8 failed", execute( h, "main() { return ( foo8( 2, 3, 5, 7, 11, 13, 17, 19 ) ); }" ), "9699690" );
	}
	/* foo9 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "foo9", foo9, "foo 9 numbers" );
		ENSURE_EQUALS( "foo9 failed", execute( h, "main() { return ( foo9( 2, 3, 5, 7, 11, 13, 17, 19, 23 ) ); }" ), "223092870" );
	}
	/* foo10 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "foo10", foo10, "foo 10 numbers" );
		ENSURE_EQUALS( "foo10 failed", execute( h, "main() { return ( foo10( 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 ) ); }" ), "6469693230" );
	}
	/* fv0 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv0", call( &fv0, &i ), "no return value" );
		ENSURE_EQUALS( "fv0 failed", execute( h, "main() { return ( fv0() ); }" ), "none" );
		ENSURE_EQUALS( "fv0 call failed", i, 1 );
	}
	/* fv1 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv1", call( &fv1, &i, _1 ), "no return value" );
		ENSURE_EQUALS( "fv1 failed", execute( h, "main() { return ( fv1( 2 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv1 call failed", i, 2 );
	}
	/* fv2 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv2", call( &fv2, &i, _1, _2 ), "no return value" );
		ENSURE_EQUALS( "fv2 failed", execute( h, "main() { return ( fv2( 2, 3 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv2 call failed", i, 6 );
	}
	/* fv3 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv3", call( &fv3, &i, _1, _2, _3 ), "no return value" );
		ENSURE_EQUALS( "fv3 failed", execute( h, "main() { return ( fv3( 2, 3, 5 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv3 call failed", i, 30 );
	}
	/* fv4 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv4", call( &fv4, &i, _1, _2, _3, _4 ), "no return value" );
		ENSURE_EQUALS( "fv4 failed", execute( h, "main() { return ( fv4( 2, 3, 5, 7 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv4 call failed", i, 210 );
	}
	/* fv5 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv5", call( &fv5, &i, _1, _2, _3, _4, _5 ), "no return value" );
		ENSURE_EQUALS( "fv5 failed", execute( h, "main() { return ( fv5( 2, 3, 5, 7, 11 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv5 call failed", i, 2310 );
	}
	/* fv6 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv6", call( &fv6, &i, _1, _2, _3, _4, _5, _6 ), "no return value" );
		ENSURE_EQUALS( "fv6 failed", execute( h, "main() { return ( fv6( 2, 3, 5, 7, 11, 13 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv6 call failed", i, 30030 );
	}
	/* fv7 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv7", call( &fv7, &i, _1, _2, _3, _4, _5, _6, _7 ), "no return value" );
		ENSURE_EQUALS( "fv7 failed", execute( h, "main() { return ( fv7( 2, 3, 5, 7, 11, 13, 17 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv7 call failed", i, 510510 );
	}
	/* fv8 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int i( 0 );
		register_function( *h, "fv8", call( &fv8, &i, _1, _2, _3, _4, _5, _6, _7, _8 ), "no return value" );
		ENSURE_EQUALS( "fv8 failed", execute( h, "main() { return ( fv8( 2, 3, 5, 7, 11, 13, 17, 19 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv8 call failed", i, 9699690 );
	}
	/* fv9 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		int long long i( 0 );
		register_function( *h, "fv9", call( &fv9, &i, _1, _2, _3, _4, _5, _6, _7, _8, _9 ), "no return value" );
		ENSURE_EQUALS( "fv9 failed", execute( h, "main() { return ( fv9( 2, 3, 5, 7, 11, 13, 17, 19, 23 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv9 call failed", i, 223092870LL );
	}
	/* fv10 */ {
		HHuginn::ptr_t h( make_pointer<HHuginn>() );
		register_function( *h, "fv10", &S::fv10, "no return value" );
		ENSURE_EQUALS( "fv10 failed", execute( h, "main() { return ( fv10( 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 ) ); }" ), "none" );
		ENSURE_EQUALS( "fv10 call failed", S::r, 6469693230LL );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "easy function call" )
	/* no args */ {
		HHuginn::ptr_t h( compile_function( "foo() { return ( 17 ); } main(){ foo; }" ) );
		ENSURE_EQUALS( "getpid failed", to_string( call_function( *h, "foo" ), h.raw() ), "17" );
	}
	/* one arg */ {
		HHuginn::ptr_t h( compile_function( "foo(a) { return ( a * a ); } main(){ foo; }" ) );
		ENSURE_EQUALS( "getpid failed", to_string( call_function( *h, "foo", 19 ), h.raw() ), "361" );
	}
	/* two args */ {
		HHuginn::ptr_t h( compile_function( "from Text import split;main(){split;}" ) );
		ENSURE_EQUALS( "getpid failed", code( call_function( *h, "split", "a,b,c", "," ), h.raw() ), "[\"a\", \"b\", \"c\"]" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "incremental mode" )
	lines_t l0{
		{ "x=0;" },
		{ "print(\"x\");" },
		{ "x+=1;" },
		{ "x;" }
	};
	ENSURE_EQUALS( "incremental mode failed", execute_incremental( l0 ), "0xnone11" );
	lines_t l1{
		{ "class X{x=0;}", OLine::TYPE::DEFINITION },
		{ "X(){}", OLine::TYPE::DEFINITION }
	};
	ENSURE_EQUALS(
		"creation of function of name that is used by class succeeded",
		execute_incremental( l1 ),
		"none*anonymous stream*:2:1: Class of the same name `X` is already defined."
	);
	lines_t l2{
		{ "x=0;x+=1;" }
	};
	ENSURE_EQUALS( "multiple statements in single input in incremental mode failed", execute_incremental( l2 ), "1" );
	lines_t l3{
		{ "@(x){x;};" },
		{ "@(x){x;};" }
	};
	ENSURE_EQUALS( "bug in incremental mode management of statement counter resurfaced", execute_incremental( l3 ), "@2:1@3:1" );
	lines_t l4{
		{ "main();" }
	};
	ENSURE_EQUALS(
		"bug in incremental mode management recursive main resurfaced",
		execute_incremental( l4 ),
		"*anonymous stream*:2:1: Referencing main() function in incremental mode is forbidden."
	);
	lines_t l5{
		{ "2+2;" },
		{ "import CannotParse as cp;", OLine::TYPE::IMPORT },
		{ "3*4;" }
	};
	ENSURE_EQUALS(
		"Parser errors in incemental mode while importing user defined submodule",
		execute_incremental( l5, { "./data" } ),
		"4*anonymous stream*:1:8: ./data/CannotParse.hgn:3:1: expected one of characters: -12"
	);
	lines_t l6{
		{ "2+2;" },
		{ "import CannotCompile as cp;", OLine::TYPE::IMPORT },
		{ "3*4;" }
	};
	ENSURE_EQUALS(
		"Compiler errors in incemental mode while importing user defined submodule",
		execute_incremental( l6, { "./data" } ),
		"4*anonymous stream*:1:8: ./data/CannotCompile.hgn:2:4: Operand types for `+` do not match: an `integer` vs a `real`.12"
	);
	lines_t l7{
		{ "solve(){a;}", OLine::TYPE::DEFINITION },
		{ "solve();" }
	};
	ENSURE_EQUALS(
		"Crash trigger",
		execute_incremental( l7 ),
		"*anonymous stream*:1:9: Symbol `a` is not defined in this context (did you mean `√`?).*anonymous stream*:2:1: Symbol `solve` is not defined in this context (did you mean `set`?)."
	);
	lines_t l8{
		{ "class A { constructor(){a;} }", OLine::TYPE::DEFINITION },
		{ "A();" }
	};
	ENSURE_EQUALS(
		"Crash trigger",
		execute_incremental( l8 ),
		"*anonymous stream*:1:25: Symbol `a` is not defined in this context (did you mean `√`?)."
		"*anonymous stream*:2:1: Symbol `A` is not defined in this context (did you mean `√`?)."
	);
	lines_t l9{
		{ "x = 1 / 0;" },
		{ "x;" }
	};
	ENSURE_EQUALS(
		"Crash trigger",
		execute_incremental( l9 ),
		"*anonymous stream*:2:7: Uncaught ArithmeticException: Division by zero."
		"*anonymous stream*:2:1: Symbol `x` is not defined in this context (did you mean `√`?)."
	);
	lines_t l10{
		{ "inc(x){x+1;}", OLine::TYPE::DEFINITION },
		{ "class CC { u(x){inc(x);}}", OLine::TYPE::DEFINITION },
		{ "(c = CC()) != none;" },
		{ "c.u(0);" }
	};
	ENSURE_EQUALS(
		"Crash trigger, reference to old function (inc) lost",
		execute_incremental( l10 ),
		"nonenonetrue1"
	);
	lines_t l11{
		{ "import Introspection as intro;", OLine::TYPE::IMPORT },
		{ "class A{x = 0;}", OLine::TYPE::DEFINITION },
		{ "cp = intro.import(\"CannotParse\");" },
		{ "0;" },
	};
	ENSURE_EQUALS(
		"unparsable runtime import",
		execute_incremental( l11, { "./data" } ),
		"nonenone*anonymous stream*:4:18: Uncaught IntrospectionException: ./data/CannotParse.hgn:3:1: expected one of characters: -0"
	);
	lines_t l12{
		{ "import Introspection as intro;", OLine::TYPE::IMPORT },
		{ "class A{x = 0;}", OLine::TYPE::DEFINITION },
		{ "cc = intro.import(\"CannotCompile\");" },
		{ "0;" },
	};
	ENSURE_EQUALS(
		"uncompilable runtime import",
		execute_incremental( l12, { "./data" } ),
		"nonenone*anonymous stream*:4:18: Uncaught IntrospectionException: ./data/CannotCompile.hgn:2:4: Operand types for `+` do not match: an `integer` vs a `real`.0"
	);
	lines_t l13{
		{ "import Tress as tress;", OLine::TYPE::IMPORT },
		{ "tress.runtime_error();" }
	};
	ENSURE_EQUALS(
		"runtime error from submodule",
		execute_incremental( l13, { "./data" } ),
		"none./data/Tress.hgn:64:2: Uncaught Exception: Ouch!"
	);
	lines_t l14{
		{ "import Short as short;", OLine::TYPE::IMPORT },
		{ "bar() { \"foo(x,y){x+y;}\"; }", OLine::TYPE::DEFINITION },
		{ "2+2;" }
	};
	ENSURE_EQUALS(
		"multiple imports and docs",
		execute_incremental( l14, { "./data" } ),
		"nonenone4"
	);
	lines_t l15{
		{ "from Algorithms import materialize, zip;", OLine::TYPE::IMPORT },
		{ "keys = [1, 2, 3];" },
		{ "values = ['a', 'b', 'c'];" },
		{ "materialize( zip( keys, values ), dict );" }
	};
	ENSURE_EQUALS(
		"from Pkg import sym failed",
		execute_incremental( l15 ),
		"none[1, 2, 3]['a', 'b', 'c'][1: 'a', 2: 'b', 3: 'c']"
	);
	lines_t l16{
		{ "f(){@(x){z;};}", OLine::TYPE::DEFINITION },
		{ "f()(0);" }
	};
	ENSURE_EQUALS(
		"function definition with invalid lambda not cleared",
		execute_incremental( l16 ),
		"*anonymous stream*:1:10: Symbol `z` is not defined in this context (did you mean `√`?).*anonymous stream*:2:1: Symbol `f` is not defined in this context (did you mean `√`?)."
	);
	lines_t l17{
		{ "f(){@(x){x + 7;};}", OLine::TYPE::DEFINITION },
		{ "f(){@(x){z;};}", OLine::TYPE::DEFINITION },
		{ "f()(0);" }
	};
	ENSURE_EQUALS(
		"function definition with invalid lambda not cleared",
		execute_incremental( l17 ),
		"none*anonymous stream*:2:10: Symbol `z` is not defined in this context (did you mean `√`?).7"
	);
	lines_t l18{
		{ "f(){@(){@(x){z;};};}", OLine::TYPE::DEFINITION },
		{ "f()(0);" }
	};
	ENSURE_EQUALS(
		"function definition with invalid lambda not cleared",
		execute_incremental( l18 ),
		"*anonymous stream*:1:14: Symbol `z` is not defined in this context (did you mean `√`?).*anonymous stream*:2:4: Function `@1:5()` accepts exactly 0 positional arguments, but 1 were given."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "introspection" )
	HIntrospector introspector;
	ENSURE_EQUALS(
		"Stream.read failed",
		execute(
			"foo( x ) {\n"
			"\ty = x + 1;\n"
			"\ty += 2;\n"
			"\treturn ( y );\n"
			"}\n"
			"\n"
			"bar( p ) {\n"
			"\tq = foo( p ) * 2;\n"
			"\treturn ( q );\n"
			"}\n"
			"\n"
			"main() {\n"
			"\tz = bar( 0 );\n"
			"\tz = z + bar( 1 );\n"
			"\treturn ( z );\n"
			"}\n",
			HHuginn::COMPILER::DEFAULT,
			&introspector
		),
		"14"
	);
	HHuginn::call_stack_t const* callStack( introspector.get_stack( "*anonymous stream*", 2 ) );
	char const expected[][64] = {
		"*anonymous stream*:2:2:foo",
		"*anonymous stream*:8:9:bar",
		"*anonymous stream*:13:9:main"
	};
	HStringStream ss;
	int row( 0 );
	for ( HHuginn::HCallSite const& cs : *callStack ) {
		ss << cs.file() << ":" << cs.line() << ":" << cs.column() << ":" << cs.context();
		ENSURE_EQUALS( "getting call stack failed", ss.str(), expected[row] );
		ss.reset();
		++ row;
	}
	/* top frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals( "*anonymous stream*", 2 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "x 0 y 1" );
	}
	/* top frame, next line */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals( "*anonymous stream*", 3 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "x 0 y 3" );
	}
	/* second frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals_up( "*anonymous stream*", 2 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "p 0 q <undefined>" );
	}
	/* bottom frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals( "*anonymous stream*", 13 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "z 6" );
	}
	/* bottom frame, next line */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals( "*anonymous stream*", 14 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "z 14" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "incremental introspection" )
	HIntrospector introspector;
	lines_t lines{
		{ "foo( x ) { y = x + 1; y += 2; return ( y ); }", OLine::TYPE::DEFINITION },
		{ "bar( p ) { q = foo( p ) * 2; return ( q ); }", OLine::TYPE::DEFINITION },
		{ "bar( 0 );" }
	};
	ENSURE_EQUALS(
		"Stream.read failed",
		execute_incremental(
			lines,
			HHuginn::COMPILER::BE_SLOPPY,
			&introspector
		),
		"nonenone6"
	);
	HHuginn::call_stack_t const* callStack( introspector.get_stack( "*anonymous stream*", 1 ) );
	char const expected[][64] = {
		"*anonymous stream*:1:12:foo",
		"*anonymous stream*:2:19:bar",
		"*anonymous stream*:4:4:main"
	};
	HStringStream ss;
	int row( 0 );
	for ( HHuginn::HCallSite const& cs : *callStack ) {
		ss << cs.file() << ":" << cs.line() << ":" << cs.column() << ":" << cs.context();
		ENSURE_EQUALS( "getting call stack failed", ss.str(), expected[row] );
		ss.reset();
		++ row;
	}
	/* top frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals( "*anonymous stream*", 1 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "x 0 y 1" );
	}
	/* second frame */ {
		HIntrospector::identifier_names_t const* identifierNames( introspector.get_locals_up( "*anonymous stream*", 1 ) );
		hcore::HString names;
		for ( HIntrospector::OVar const& v : *identifierNames ) {
			if ( ! names.is_empty() ) {
				names.append( " " );
			}
			names.append( v.name ).append( " " ).append( v.value );
		}
		ENSURE_EQUALS( "get_locals failed", names, "p 0 q <undefined>" );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "max call stack size" )
	HHuginn h;
	ENSURE_THROW( "invalid max call stack size accepted", h.set_max_call_stack_size( 100 ), HHuginnException );
	ENSURE_EQUALS(
		"max call stack size check failed",
		execute_except( "main(){\nmain();\n}\n" ),
		"*anonymous stream*:2:5: Call stack size limit exceeded: 129"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "observe/use" )
	ENSURE_EQUALS(
		"obseve/use basic failed",
		execute(
			"main(){"
			"r=[];"
			"x=none;"
			"y=7;"
			"x=observe(y);"
			"r.push(type(x));"
			"z=use(x);"
			"r.push(type(z));"
			"r.push(copy(z));"
			"z=none;"
			"y=none;"
			"z=use(x);"
			"r.push(type(z));"
			"return(r);"
			"}"
		),
		"[*observer*, integer, 7, *none*]"
	);
	ENSURE_EQUALS(
		"obseve/use complex failed",
		execute(
			"class Node {"
			"	_data = none;"
			"	_ref = none;"
			"	_next = none;"
			"	_prev = none;"
			"	constructor( data_, ref_ ) {"
			"		_data = data_;"
			"		_ref = ref_;"
			"		_ref += 1;"
			"	}"
			"	prev_data() {"
			"		x = use( _prev );"
			"		return ( x._data );"
			"	}"
			"	destructor() {"
			"		_ref -= 1;"
			"	}"
			"}"
			""
			"main() {"
			"	ref = 0;"
			"	res = \"\";"
			"	/* scope */ {"
			"		n1 = Node( \"a\", ref );"
			"		n2 = Node( \"b\", ref );"
			"		n1._next = n2;"
			"		n2._prev = observe( n1 );"
			"		res += string( ref );"
			"		res += n2.prev_data();"
			"	}"
			"	res += string( ref );"
			"	return ( res );"
			"}"
		),
		"\"2a0\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "helpers" )
	ENSURE_EQUALS(
		"verify_arg_collection_value_type order invalid succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.statistics(order('a','b','c'));"
			"}"
		),
		"*anonymous stream*:1:50: NumberSetStatistics.constructor() a collection contains value of an unexpected type: a `character`."
	);
	ENSURE_EQUALS(
		"did not detect a cycle",
		execute_except(
			"class D{_x=none;constructor(x){_x=x;}destructor(){_x.clear();}}"
			"import FileSystem as fs;"
			"main(){"
			"x=[];"
			"d=D(x);"
			"x.push(x);"
			"f = fs.open(\"out/cycle.hds\", fs.OPEN_MODE.WRITE);"
			"f.serialize(x);"
			"d;"
			"}"
		),
		"*anonymous stream*:1:177: Cycle detected on type: list"
	);
	ENSURE_EQUALS(
		"did not detect a cycle",
		execute_except(
			"import FileSystem as fs;"
			"main(){"
			"fs.open(\"out/cycle.hds\", 0);"
			"}"
		),
		"*anonymous stream*:1:39: FileSystem.open() second argument must be an `OPEN_MODE_ENUMERAL`, not an `integer`."
	);
	HHuginn::ptr_t h( make_pointer<HHuginn>() );
	execute( h, "main(){7;}" );
	ENSURE_EQUALS( "get_integer(HValue const*) failed", get_integer( h->result().raw() ), 7LL );
	h = make_pointer<HHuginn>();
	execute( h, "main(){7.;}" );
	ENSURE_EQUALS( "get_real(HValue const*) failed", get_real( h->result().raw() ), 7.L );
	h = make_pointer<HHuginn>();
	execute( h, "main(){$7;}" );
	ENSURE_EQUALS( "get_number(HValue const*) failed", get_number( h->result().raw() ), "7"_yn );
	h = make_pointer<HHuginn>();
	execute( h, "main(){true;}" );
	ENSURE_EQUALS( "get_boolean(HValue const*) failed", get_boolean( h->result().raw() ), true );
	h = make_pointer<HHuginn>();
	execute( h, "main(){'a';}" );
	ENSURE_EQUALS( "get_character(HValue const*) failed", get_character( h->result().raw() ), 'a'_ycp );
	h = make_pointer<HHuginn>();
	execute( h, "import FileSystem as fs;main(){fs.OPEN_MODE.READ;}" );
	ENSURE_EQUALS( "get_enumeral(HValue const*) failed", get_enumeral( h->result().raw() ), static_cast<int>( HFile::OPEN::READING.value() ) );
	h = make_pointer<HHuginn>();
	execute( h, "main(){7.;}" );
	HHuginn::value_t v( h->result() );
	ENSURE_EQUALS( "get_by_type<double long>(...) failed", get_by_type<huginn::HReal::value_type>( v ), 7.L );
	v.reset();
	h = make_pointer<HHuginn>();
	execute( h, "main(){$7;}" );
	v = h->result();
	ENSURE_EQUALS( "get_by_type<HNumber>(...) failed", get_by_type<huginn::HNumber::value_type&>( v ), "7"_yn );
	v.reset();
TUT_TEARDOWN()

TUT_UNIT_TEST( "simple program" )
	clog << simpleProg << endl;
	HHuginn h;
	HStringStream src( simpleProg );
	h.load( src );
	h.preprocess();
	if ( ! h.parse() ) {
		clog << h.error_message() << endl;
	}
	h.compile();
	h.add_argument( "7" );
	h.add_argument( "13" );
	h.execute();
	HHuginn::value_t r( h.result() );
	ENSURE( "nothing returned", !! r );
	ENSURE_EQUALS( "bad result type", r->type_id(), HHuginn::TYPE::INTEGER );
	ENSURE_EQUALS( "bad value returned", static_cast<huginn::HInteger*>( r.raw() )->value(), 42 );
TUT_TEARDOWN()

}


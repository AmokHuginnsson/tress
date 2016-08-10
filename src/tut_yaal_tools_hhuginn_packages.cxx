/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

  tut_yaal_tools_hhuginn_packages.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

#include <TUT/tut.hpp>

#include <yaal/tools/hhuginn.hxx>
#include <yaal/tools/hmonitor.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/tools/hstringstream.hxx>

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::executing_parser;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_packages : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_packages, "yaal::tools::HHuginn,packages" );

TUT_UNIT_TEST( "Algorithms" )
	ENSURE_EQUALS(
		"Algorithms.map failed",
		execute(
			"import Algorithms as algo;"
			"main(){"
			"l=[];"
			"m=algo.map([3, 17, 4],@(x){x*x;});"
			"for(x : copy(m)) {"
			"l.add(x);"
			"}"
			"return([l,size(m)]);"
			"}"
		),
		"[[9, 289, 16], 3]"
	);
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
		"Algorithms.materialize failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"return(algo.materialize(algo.range(3, 17, 4),list));\n"
			"}"
		),
		"[3, 7, 11, 15]"
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
			"s=\"\";\n"
			"d=deque(2,7,3,9,0,-5);\n"
			"for(x : algo.sorted(d)) {\n"
			"s=s+\":\"+string(x);"
			"}\n"
			"return(s);\n"
			"}"
		),
		"\":-5:0:2:3:7:9\""
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (set) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"r=\"\";\n"
			"s=set(2,7,3,9,0,-5);\n"
			"for(x : algo.sorted(s)) {\n"
			"r=r+\":\"+string(x);"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\":-5:0:2:3:7:9\""
	);
	ENSURE_EQUALS(
		"Algorithms.sorted (order) failed",
		execute(
			"import Algorithms as algo;\n"
			"main(){\n"
			"r=\"\";\n"
			"o=order(2,7,3,9,0,-5);\n"
			"for(x : algo.sorted(o)) {\n"
			"r=r+\":\"+string(x);"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\":-5:0:2:3:7:9\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Cryptography" )
	ENSURE_EQUALS(
		"Cryptography.md5 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.md5(\"\"));\n"
			"}"
		),
		"\"d41d8cd98f00b204e9800998ecf8427e\""
	);
	ENSURE_EQUALS(
		"Cryptography.sha1 failed",
		execute(
			"import Cryptography as crypto;\n"
			"main(){\n"
			"return(crypto.sha1(\"\"));\n"
			"}"
		),
		"\"da39a3ee5e6b4b0d3255bfef95601890afd80709\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "RegularExpressions" )
	ENSURE_EQUALS(
		"RegularExpressions.match failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"[0-9]-[0-9]\" );\n"
			"r = \"\";\n"
			"m = rec.match(\"[123+123+3123]\");\n"
			"if (m.matched()) {\n"
			"r = r + \"fail match\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"m = rec.match(\"[123-456-789]\");"
			"if (m.matched()) {\n"
			"for ( w : m ) {\n"
			"r = r + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no match\";\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok3-46-7\""
	);
	ENSURE_EQUALS(
		"RegularExpressions.groups failed",
		execute(
			"import RegularExpressions as re;\n"
			"main(){\n"
			"rec = re.compile( \"^([a-z]*)@([a-z.]*)$\" );\n"
			"r = \"\";\n"
			"g = rec.groups(\"user@example2.com\");\n"
			"if ( g != none ) {\n"
			"r = r + \"fail groups\";\n"
			"} else {\n"
			"r = r + \"ok\";\n"
			"}\n"
			"g = rec.groups(\"user@example.com\");\n"
			"if ( g != none ) {\n"
			"for ( w : g ) {\n"
			"r = r + \"|\" + w;\n"
			"}\n"
			"} else {\n"
			"r = r + \"fail no groups\";\n"
			"}\n"
			"return(r);\n"
			"}"
		),
		"\"ok|user@example.com|user|example.com\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Mathematics" )
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){return(math.square_root(7.));}" ), "2.645751311065" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){return(math.square_root($7));}" ), "$2.6457513110645905905016157536392604257102591830824501803683344592010688232302836277603928864745436106" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){try{math.square_root(-1.);}catch(MathematicsException e){return(e.what());}}" ), "\"bad domain\"" );
	ENSURE_EQUALS( "Mathematics.natural_expotential failed", execute( "import Mathematics as math;main(){return(math.natural_expotential(7.));}" ), "1096.633158428459" );
	ENSURE_EQUALS( "Mathematics.natural_expotential failed", execute( "import Mathematics as math;main(){return(math.natural_expotential($7));}" ), "$1096.6331584284585992637202382881214324422191348336131437827392407761217693312331290224785687872498437141" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){return(math.natural_logarithm(7.));}" ), "1.945910149055" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){return(math.natural_logarithm($7));}" ), "$1.945910149055313305105352743443179729637084729581861188459390149937579862752069267787658498587871527" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){try{math.natural_logarithm(0.);}catch(MathematicsException e){return(e.what());}}" ), "\"bad domain\"" );
	ENSURE_EQUALS( "Mathematics.sinus failed", execute( "import Mathematics as math;main(){return(math.sinus(7.));}" ), "0.656986598719" );
	ENSURE_EQUALS( "Mathematics.sinus failed", execute( "import Mathematics as math;main(){return(math.sinus($7));}" ), "$0.6569865987187890903969990915936351779368700104974900746578543341892928371312270315099351216010552127" );
	ENSURE_EQUALS( "Mathematics.cosinus failed", execute( "import Mathematics as math;main(){return(math.cosinus(7.));}" ), "0.753902254343" );
	ENSURE_EQUALS( "Mathematics.cosinus failed", execute( "import Mathematics as math;main(){return(math.cosinus($7));}" ), "$0.7539022543433046381411975217191820122183133914601268395436138808138760267207174056254283910893024825" );
	ENSURE_EQUALS( "Mathematics.tangens failed", execute( "import Mathematics as math;main(){return(math.tangens(7.));}" ), "0.871447982724" );
	ENSURE_EQUALS( "Mathematics.tangens failed", execute( "import Mathematics as math;main(){return(math.tangens($7));}" ), "$0.8714479827243187364564508896003135663222034245984200644480154523301674476556679351044748556811165168" );
	ENSURE_EQUALS( "Mathematics.cotangens failed", execute( "import Mathematics as math;main(){return(math.cotangens(7.));}" ), "1.147515422405" );
	ENSURE_EQUALS( "Mathematics.cotangens failed", execute( "import Mathematics as math;main(){return(math.cotangens($7));}" ), "$1.1475154224051356850571278335968690125843802678361633445170108981521966892555002012462107148960973854" );
	ENSURE_EQUALS( "Mathematics.arcus_sinus failed", execute( "import Mathematics as math;main(){return(math.arcus_sinus(.7));}" ), "0.775397496611" );
	ENSURE_EQUALS( "Mathematics.arcus_sinus failed", execute( "import Mathematics as math;main(){return(math.arcus_sinus($0.7));}" ), "$0.7753974966107530637403533527149871135557887386411619935977199637327202118807111988654109034943728765" );
	ENSURE_EQUALS( "Mathematics.arcus_cosinus failed", execute( "import Mathematics as math;main(){return(math.arcus_cosinus(.7));}" ), "0.795398830184" );
	ENSURE_EQUALS( "Mathematics.arcus_cosinus failed", execute( "import Mathematics as math;main(){return(math.arcus_cosinus($0.7));}" ), "$0.7953988301841435554909683389247643285427959610463909168897523324211879912623933004486065091766856575" );
	ENSURE_EQUALS( "Mathematics.arcus_tangens failed", execute( "import Mathematics as math;main(){return(math.arcus_tangens(7.));}" ), "1.428899272191" );
	ENSURE_EQUALS( "Mathematics.arcus_tangens failed", execute( "import Mathematics as math;main(){return(math.arcus_tangens($7));}" ), "$1.4288992721907326964184700745371983590908029409590888381093422667904665763831733383698255510368120159" );
	ENSURE_EQUALS( "Mathematics.arcus_cotangens failed", execute( "import Mathematics as math;main(){return(math.arcus_cotangens(7.));}" ), "0.141897054604" );
	ENSURE_EQUALS( "Mathematics.arcus_cotangens failed", execute( "import Mathematics as math;main(){return(math.arcus_cotangens($7));}" ), "$0.1418970546041639228128516171025530830077817587284640723781300293634416267599311609441918616342465181" );
	hcore::HString hyperbolicSinusRes( execute( "import Mathematics as math;main(){return(math.hyperbolic_sinus(7.0));}" ) );
	hyperbolicSinusRes.pop_back();
	ENSURE_EQUALS( "Mathematics.hyperbolic_sinus failed", hyperbolicSinusRes, "548.31612327324" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_sinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_sinus($7));}" ), "$548.3161232732465223737561175760185115797963305545428538644492123213499399256719093579746212541216894908" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cosinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cosinus(7.0));}" ), "548.317035155212" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cosinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cosinus($7));}" ), "$548.3170351552120768899641207121029208624228042790702899182900284547718294055612196645039475331281543912" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_tangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_tangens(7.));}" ), "0.999998336944" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_tangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_tangens($7));}" ), "$0.9999983369439446717357164159506671128820569920922747109692404742809110481696115057511479211747076493" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cotangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cotangens(7.));}" ), "1.000001663059" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cotangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cotangens($7));}" ), "$1.0000016630588210883070615776102514764913523331922228239871821889401302787085050299163985440938683564" );
	ENSURE_EQUALS( "Mathematics.sigmoid failed", execute( "import Mathematics as math;main(){return(math.sigmoid(7.0));}" ), "0.999088948806" );
	ENSURE_EQUALS( "Mathematics.sigmoid failed", execute( "import Mathematics as math;main(){return(math.sigmoid($7));}" ), "$0.9990889488055993546421366762253058586758519397386814335751812177406547366392254595319805404147834436" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round(7.1234));}" ), "7.000000000000" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round($7.123456,3));}" ), "$7.123" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){try{math.round(7.1234, 3);}catch(MathematicsException e){return(e.what());}}" ), "\"rounding to nth place on real is not supported\"" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor(7.1234));}" ), "7.000000000000" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor($7.123456));}" ), "$7" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor(-7.1234));}" ), "-8.000000000000" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor($-7.123456));}" ), "$-8" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil(7.1234));}" ), "8.000000000000" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil($7.123456));}" ), "$8" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil(-7.1234));}" ), "-7.000000000000" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil($-7.123456));}" ), "$-7" );
	ENSURE_EQUALS( "Mathematics.differs_at failed", execute( "import Mathematics as math;main(){return(math.differs_at($7.1234567, $7.1235567));}" ), "3" );
	ENSURE_EQUALS( "Mathematics.differs_at failed", execute( "import Mathematics as math;main(){return(math.differs_at($2234.1234567, $1234.1234567));}" ), "-4" );
	ENSURE_EQUALS(
		"Mathematics.matrix (add) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"m2=math.matrix([9.,8.],[7.,6.]);"
			"m1+=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([10.000000000000, 10.000000000000], [10.000000000000, 10.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (add) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.matrix([$7.,$6.],[$9.,$8.]);"
			"m1+=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$8, $8], [$12, $12])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (sub) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"m2=math.matrix([9.,8.],[7.,6.]);"
			"m1-=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([-8.000000000000, -6.000000000000], [-4.000000000000, -2.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (sub) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.matrix([$9.,$8.],[$7.,$6.]);"
			"m1-=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$-8, $-6], [$-4, $-2])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (mul) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"m2=math.matrix([9.,8.],[7.,6.]);"
			"m1*=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([23.000000000000, 20.000000000000], [55.000000000000, 48.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (mul) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.matrix([$9.,$8.],[$7.,$6.]);"
			"m1*=m2;"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$23, $20], [$55, $48])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (scale) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"m1.scale(2.);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([2.000000000000, 4.000000000000], [6.000000000000, 8.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (scale) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1.,$2.],[$3.,$4.]);"
			"m1.scale($2);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$2, $4], [$6, $8])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (scale_to) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"m1.scale_to(12.);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([3.000000000000, 6.000000000000], [9.000000000000, 12.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (scale_to) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1.,$2.],[$3.,$4.]);"
			"m1.scale_to($12);"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$3, $6], [$9, $12])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (det) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"return(m1.det());"
			"}"
		),
		"-2.000000000000"
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (det) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1,$2],[$3,$4]);"
			"return(m1.det());"
			"}"
		),
		"$-2"
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (invert) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([1.,2.],[3.,4.]);"
			"return(string(m1*copy(m1).invert()));"
			"}"
		),
		"\"Matrix([1.000000000000, 0.000000000000], [0.000000000000, 1.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (invert) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix([$1.,$2.],[$3.,$4.]);"
			"return(string(m1*copy(m1).invert()));"
			"}"
		),
		"\"Matrix([$1, $0], [$0, $1])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (set/get) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix(real,2,2);"
			"m1.set(0,0,1.);"
			"m1.set(0,1,2.);"
			"m1.set(1,0,3.);"
			"m1.set(1,1,4.);"
			"m1.scale(m1.get(0,1));"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([2.000000000000, 4.000000000000], [6.000000000000, 8.000000000000])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix (set/get) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.matrix(number,2,2);"
			"m1.set(0,0,$1.);"
			"m1.set(0,1,$2.);"
			"m1.set(1,0,$3.);"
			"m1.set(1,1,$4.);"
			"m1.scale(m1.get(0,1));"
			"return(string(m1));"
			"}"
		),
		"\"Matrix([$2, $4], [$6, $8])\""
	);
	ENSURE_EQUALS(
		"Mathematics.matrix rows failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.matrix(real,3,2);"
			"return(m.rows());"
			"}"
		),
		"3"
	);
	ENSURE_EQUALS(
		"Mathematics.matrix rows failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.matrix(number,3,2);"
			"return(m.rows());"
			"}"
		),
		"3"
	);
	ENSURE_EQUALS(
		"Mathematics.matrix columns failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.matrix(real,3,2);"
			"return(m.columns());"
			"}"
		),
		"2"
	);
	ENSURE_EQUALS(
		"Mathematics.matrix columns failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.matrix(number,3,2);"
			"return(m.columns());"
			"}"
		),
		"2"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Database" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	ENSURE_EQUALS(
		"DatabaseConnection.table_names",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"return(dbc.table_names());"
			"}"
		),
		"[\"config\", \"crud\", \"test\", \"test_dict\", \"test_item\"]"
	);
	ENSURE_EQUALS(
		"DatabaseConnection.column_names",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"return(dbc.column_names(\"config\"));"
			"}"
		),
		"[\"id\", \"name\", \"data\"]"
	);
	ENSURE_EQUALS(
		"DatabaseConnection.query, Query, QueryResult",
		execute(
			"import Database as db;"
			"main(){"
			"dbc=db.connect(\"sqlite3:///out/tress\");"
			"q=dbc.query(\"SELECT name FROM config WHERE id != ?;\");"
			"q.bind(1, \"2\");"
			"qr=q.execute();"
			"res=\"\";"
			"i=0;"
			"fc=qr.field_count();"
			"while(i<fc){"
			"res+=qr.column_name(i);"
			"res+=\",\";"
			"i+=1;"
			"}"
			"if(qr.has_next()){"
			"for(r:qr){"
			"for(v:r){"
			"res+=v;"
			"res+=\",\";"
			"}"
			"}"
			"}"
			"q=dbc.query(\"SELECT name, data FROM config WHERE id = ?;\");"
			"q.bind(1, \"2\");"
			"qr=q.execute();"
			"while(qr.has_next()){"
			"for(v:qr.fetch_row()){"
			"res+=(v!=none ? v : \"none\");"
			"res+=\",\";"
			"}"
			"}"
			"return(res);"
			"}"
		),
		"\"name,one,three,two,none,\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "OperatingSystem" )
	ENSURE_EQUALS(
		"OperatingSystem.env",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"return(os.env(\"DEFAULT_TARGET\"));"
			"}"
		),
		"\"debug\""
	);
	ENSURE_EQUALS(
		"OperatingSystem.exec",
		execute_except(
			"import OperatingSystem as os;"
			"main(){"
			"os.exec(\"/non/existing\",\"arg1\");"
			"return(0);"
			"}"
		),
		"*anonymous stream*:1:44: Uncaught exception: No such file or directory"
	);
	/* It is impossible to test exit(). */
	hcore::HString CHILD( "./data/child" EXE_SUFFIX );
	ENSURE_EQUALS(
		"OperatingSystem.spawn",
		execute(
			"import OperatingSystem as os;"
			"main(){"
			"c=os.spawn(\"" + CHILD + "\");"
			"c.in().write(\"out\\n\");"
			"return(c.out().read_line().strip());"
			"}"
		),
		"\"hello-OUT\""
	);
TUT_TEARDOWN()

}


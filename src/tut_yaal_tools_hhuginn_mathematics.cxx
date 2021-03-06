/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <csignal>
#include <TUT/tut.hpp>

#include <yaal/tools/hhuginn.hxx>
#include <yaal/tools/stringalgo.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_mathematics : public tress::tut_yaal_tools_hhuginn_base {
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_mathematics, "yaal::tools::HHuginn.Mathematics" );

TUT_UNIT_TEST( "constants pi and e" )
	ENSURE_EQUALS( "Mathematics.{pi, e} failed", execute( "import Mathematics as math;main(){return([math.pi(real),math.e(number,200)]);}" ), "[3.14159265359, $2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901]" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "square_root" )
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){return(math.square_root(7.));}" ), "2.645751311065" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){return(math.square_root($7));}" ), "$2.6457513110645905905016157536392604257102591830824501803683344592010688232302836277603928864745436106" );
	ENSURE_EQUALS( "Mathematics.square_root failed", execute( "import Mathematics as math;main(){try{math.square_root(-1.);}catch(ArithmeticException e){return(e.what());}}" ), "\"bad domain\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "natural_exponential" )
	ENSURE_EQUALS( "Mathematics.natural_exponential failed", execute( "import Mathematics as math;main(){return(math.natural_exponential(7.));}" ), "1096.633158428459" );
	ENSURE_EQUALS( "Mathematics.natural_exponential failed", execute( "import Mathematics as math;main(){return(math.natural_exponential($7));}" ), "$1096.6331584284585992637202382881214324422191348336131437827392407761217693312331290224785687872498438842" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "natural_logarithm" )
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){return(math.natural_logarithm(7.));}" ), "1.945910149055" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){return(math.natural_logarithm($7));}" ), "$1.945910149055313305105352743443179729637084729581861188459390149937579862752069267787658498587871527" );
	ENSURE_EQUALS( "Mathematics.natural_logarithm failed", execute( "import Mathematics as math;main(){try{math.natural_logarithm(0.);}catch(MathematicsException e){return(e.what());}}" ), "\"bad domain\"" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "trigonometric" )
	ENSURE_EQUALS( "Mathematics.sinus failed", execute( "import Mathematics as math;main(){return(math.sinus(7.));}" ), "0.656986598719" );
	ENSURE_EQUALS( "Mathematics.sinus failed", execute( "import Mathematics as math;main(){return(math.sinus($7));}" ), "$0.6569865987187890903969990915936351779368700104974900746578543341892928371312270315099351216010552127" );
	ENSURE_EQUALS( "Mathematics.cosinus failed", execute( "import Mathematics as math;main(){return(math.cosinus(7.));}" ), "0.753902254343" );
	ENSURE_EQUALS( "Mathematics.cosinus failed", execute( "import Mathematics as math;main(){return(math.cosinus($7));}" ), "$0.7539022543433046381411975217191820122183133914601268395436138808138760267207174056254283910893024825" );
	ENSURE_EQUALS( "Mathematics.tangens failed", execute( "import Mathematics as math;main(){return(math.tangens(7.));}" ), "0.871447982724" );
	ENSURE_EQUALS( "Mathematics.tangens failed", execute( "import Mathematics as math;main(){return(math.tangens($7));}" ), "$0.8714479827243187364564508896003135663222034245984200644480154523301674476556679351044748556811165168" );
	ENSURE_EQUALS( "Mathematics.cotangens failed", execute( "import Mathematics as math;main(){return(math.cotangens(7.));}" ), "1.147515422405" );
	ENSURE_EQUALS( "Mathematics.cotangens failed", execute( "import Mathematics as math;main(){return(math.cotangens($7));}" ), "$1.1475154224051356850571278335968690125843802678361633445170108981521966892555002012462107148960973854" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "arcus (inverse trigonometric)" )
	ENSURE_EQUALS( "Mathematics.arcus_sinus failed", execute( "import Mathematics as math;main(){return(math.arcus_sinus(.7));}" ), "0.775397496611" );
	ENSURE_EQUALS( "Mathematics.arcus_sinus failed", execute( "import Mathematics as math;main(){return(math.arcus_sinus($0.7));}" ), "$0.7753974966107530637403533527149871135557887386411619935977199637327202118807111988654109034943728765" );
	ENSURE_EQUALS( "Mathematics.arcus_cosinus failed", execute( "import Mathematics as math;main(){return(math.arcus_cosinus(.7));}" ), "0.795398830184" );
	ENSURE_EQUALS( "Mathematics.arcus_cosinus failed", execute( "import Mathematics as math;main(){return(math.arcus_cosinus($0.7));}" ), "$0.7953988301841435554909683389247643285427959610463909168897523324211879912623933004486065091766856575" );
	ENSURE_EQUALS( "Mathematics.arcus_tangens failed", execute( "import Mathematics as math;main(){return(math.arcus_tangens(7.));}" ), "1.428899272191" );
	ENSURE_EQUALS( "Mathematics.arcus_tangens failed", execute( "import Mathematics as math;main(){return(math.arcus_tangens($7));}" ), "$1.4288992721907326964184700745371983590908029409590888381093422667904665763831733383698255510368120159" );
	ENSURE_EQUALS( "Mathematics.arcus_cotangens failed", execute( "import Mathematics as math;main(){return(math.arcus_cotangens(7.));}" ), "0.141897054604" );
	ENSURE_EQUALS( "Mathematics.arcus_cotangens failed", execute( "import Mathematics as math;main(){return(math.arcus_cotangens($7));}" ), "$0.1418970546041639228128516171025530830077817587284640723781300293634416267599311609441918616342465181" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "hyperbolic trigonometric" )
	hcore::HString hyperbolicSinusRes( execute( "import Mathematics as math;main(){return(math.hyperbolic_sinus(7.0));}" ) );
	hyperbolicSinusRes.pop_back();
	ENSURE_EQUALS( "Mathematics.hyperbolic_sinus failed", hyperbolicSinusRes, "548.31612327324" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_sinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_sinus($7));}" ), "$548.3161232732465223737561175760185115797963305545428538644492123213499399256719093579746212541216894919" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cosinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cosinus(7.0));}" ), "548.317035155212" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cosinus failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cosinus($7));}" ), "$548.3170351552120768899641207121029208624228042790702899182900284547718294055612196645039475331281543923" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_tangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_tangens(7.));}" ), "0.999998336944" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_tangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_tangens($7));}" ), "$0.9999983369439446717357164159506671128820569920922747109692404742809110481696115057511479211747076493" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cotangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cotangens(7.));}" ), "1.000001663059" );
	ENSURE_EQUALS( "Mathematics.hyperbolic_cotangens failed", execute( "import Mathematics as math;main(){return(math.hyperbolic_cotangens($7));}" ), "$1.0000016630588210883070615776102514764913523331922228239871821889401302787085050299163985440938683564" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "sigmoid" )
	ENSURE_EQUALS( "Mathematics.sigmoid failed", execute( "import Mathematics as math;main(){return(math.sigmoid(7.0));}" ), "0.999088948806" );
	ENSURE_EQUALS( "Mathematics.sigmoid failed", execute( "import Mathematics as math;main(){return(math.sigmoid($7));}" ), "$0.9990889488055993546421366762253058586758519397386814335751812177406547366392254595319805404147834436" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "error_function" )
	ENSURE_EQUALS( "Mathematics.error_function failed", execute( "import Mathematics as math;main(){return(math.error_function(0.7));}" ), "0.677801193837" );
	ENSURE_EQUALS( "Mathematics.error_function failed", execute( "import Mathematics as math;main(){return(math.error_function($0.7));}" ), "$0.677801193837" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "cumulative_distribution_function" )
	ENSURE_EQUALS( "Mathematics.cumulative_distribution_function failed", execute( "import Mathematics as math;main(){return(math.cumulative_distribution_function(1.,-1.,2.));}" ), "0.841344746069" );
	ENSURE_EQUALS( "Mathematics.cumulative_distribution_function failed", execute( "import Mathematics as math;main(){return(math.cumulative_distribution_function($1,$-1,$2));}" ), "$0.8413447460685" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "rounding" )
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round(7.1234));}" ), "7.0" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round($7.12354321,3));}" ), "$7.124" );
	ENSURE_EQUALS( "Mathematics.round failed", execute( "import Mathematics as math;main(){return(math.round(7.1235, 3));}" ), "7.124" );
	ENSURE_EQUALS( "Mathematics.round failed", execute_except( "import Mathematics as math;main(){return(math.round(7.1235, -1));}" ), "*anonymous stream*:1:52: Invalid requested round value: -1" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor(7.1234));}" ), "7.0" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor($7.123456));}" ), "$7" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor(-7.1234));}" ), "-8.0" );
	ENSURE_EQUALS( "Mathematics.floor failed", execute( "import Mathematics as math;main(){return(math.floor($-7.123456));}" ), "$-8" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil(7.1234));}" ), "8.0" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil($7.123456));}" ), "$8" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil(-7.1234));}" ), "-7.0" );
	ENSURE_EQUALS( "Mathematics.ceil failed", execute( "import Mathematics as math;main(){return(math.ceil($-7.123456));}" ), "$-7" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "greatest_common_divisor" )
	ENSURE_EQUALS(
		"Mathematics.greatest_common_divisor (integer) failed",
		execute( "import Mathematics as math;main(){return(math.greatest_common_divisor(814001929, 6324168833));}" ),
		"62615533"
	);
	ENSURE_EQUALS(
		"Mathematics.greatest_common_divisor (number) failed",
		execute(
			"import Mathematics as math;"
			"main(){return(math.greatest_common_divisor($923090048436318902677028845148129025191, $921677335697990140168149321344815984979));}"
		),
		"$117726061527396875739960316942753351"
	);
	ENSURE_EQUALS(
		"Mathematics.greatest_common_divisor number on non-integral succeeded",
		execute_except( "import Mathematics as math;main(){return(math.greatest_common_divisor($1.5, $1));}" ),
		"*anonymous stream*:1:70: Invalid argument."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "binomial_coefficient" )
	ENSURE_EQUALS(
		"Mathematics.binomial_coefficient failed",
		execute( "import Mathematics as math;main(){return(math.binomial_coefficient($10, $3));}" ),
		"$120"
	);
	ENSURE_EQUALS(
		"Mathematics.binomial_coefficient number on non-integral succeeded",
		execute_except( "import Mathematics as math;main(){return(math.binomial_coefficient($1.5, $1));}" ),
		"*anonymous stream*:1:67: Invalid argument."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "modular_multiplicative_inverse" )
	ENSURE_EQUALS(
		"modular_multiplicative_inverse failed",
		execute( "import Mathematics as math;main(){return(math.modular_multiplicative_inverse(integer( $2 ^ $55 - $55 ), 101));}" ),
		"12841947452303969"
	);
	ENSURE_EQUALS(
		"modular_multiplicative_inverse failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"return((math.modular_multiplicative_inverse(17, 13),math.modular_multiplicative_inverse(17, 4)));"
			"}"
		),
		"(4, 13)"
	);
	ENSURE_EQUALS(
		"modular_multiplicative_inverse with invalid mod succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplicative_inverse(0, 101));}" ),
		"*anonymous stream*:1:77: Invalid argument."
	);
	ENSURE_EQUALS(
		"modular_multiplicative_inverse with invalid val succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplicative_inverse(17, 0));}" ),
		"*anonymous stream*:1:77: Invalid argument."
	);
	ENSURE_EQUALS(
		"modular_multiplicative_inverse with invalid mod - value relation succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplicative_inverse(17, 101));}" ),
		"*anonymous stream*:1:77: Invalid argument."
	);
	ENSURE_EQUALS(
		"modular_multiplicative_inverse with no inverse succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplicative_inverse(54, 24));}" ),
		"*anonymous stream*:1:77: Uncaught MathematicsException: Multiplicative inverse does not exist."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "modular_multiplication" )
	ENSURE_EQUALS(
		"modular_multiplication failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"base = 101;"
			"mod = integer( $2 ^ $55 - $55 );"
			"inv = math.modular_multiplicative_inverse(mod, base);"
			"v = 3175387;"
			"x = math.modular_multiplication( v, base, mod);"
			"r = math.modular_multiplication( x, inv, mod);"
			"return((x, r));"
			"}"
		),
		"(320714087, 3175387)"
	);
	ENSURE_EQUALS(
		"modular_multiplication failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m = integer( $2 ^ $61 - $1 );"
			"x = integer( $2 ^ $55 - $55 );"
			"return(math.modular_multiplication(x,x,m));"
			"}"
		),
		"649081296294775759"
	);
	ENSURE_EQUALS(
		"modular_multiplication with bad fact1 succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplication(-1, 12, 123));}" ),
		"*anonymous stream*:1:69: Invalid argument."
	);
	ENSURE_EQUALS(
		"modular_multiplication with bad fact2 succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplication(12, -1, 123));}" ),
		"*anonymous stream*:1:69: Invalid argument."
	);
	ENSURE_EQUALS(
		"modular_multiplication with bad mod succeeded",
		execute_except( "import Mathematics as math;main(){return(math.modular_multiplication(12, 12, 0));}" ),
		"*anonymous stream*:1:69: Invalid argument."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "differs_at" )
	ENSURE_EQUALS( "Mathematics.differs_at failed", execute( "import Mathematics as math;main(){return(math.differs_at($7.1234567, $7.1235567));}" ), "3" );
	ENSURE_EQUALS( "Mathematics.differs_at failed", execute( "import Mathematics as math;main(){return(math.differs_at($2234.1234567, $1234.1234567));}" ), "-4" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "Matrix" )
	ENSURE_EQUALS(
		"Mathematics.Matrix (add) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m2=math.Matrix([9.,8.],[7.,6.]);"
			"m1+=m2;"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([10.0, 10.0], [10.0, 10.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (add) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.Matrix([$7.,$6.],[$9.,$8.]);"
			"m1+=m2;"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([$8, $8], [$12, $12])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (sub) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m2=math.Matrix([9.,8.],[7.,6.]);"
			"m1-=m2;"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([-8.0, -6.0], [-4.0, -2.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (sub) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.Matrix([$9.,$8.],[$7.,$6.]);"
			"m1-=m2;"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([$-8, $-6], [$-4, $-2])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (mul) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m2=math.Matrix([9.,8.],[7.,6.]);"
			"m1*=m2;"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([23.0, 20.0], [55.0, 48.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (mul) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m2=math.Matrix([$9.,$8.],[$7.,$6.]);"
			"m1*=m2;"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([$23, $20], [$55, $48])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m1.scale(2.);"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([2.0, 4.0], [6.0, 8.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m1.scale($2);"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([$2, $4], [$6, $8])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale_to) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"m1.scale_to(12.);"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([3.0, 6.0], [9.0, 12.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (scale_to) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"m1.scale_to($12);"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([$3, $6], [$9, $12])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (det) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([1.,2.],[3.,4.]);"
			"return(|m1|);"
			"}"
		),
		"-2.0"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (det) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix([$1,$2],[$3,$4]);"
			"return(math.round(|m1|,50));"
			"}"
		),
		"$-2"
	);
	ENSURE_IN(
		"Mathematics.Matrix (inverse) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([1.,2.],[3.,4.]);"
			"return(string((m*m.inverse()).apply(@(x,y,v){x;y;math.round(v,9);})));"
			"}"
		),
		std::vector<char const*>( { "\"math.Matrix([1.0, 0.0], [-0.0, 1.0])\"", "\"math.Matrix([1.0, 0.0], [0.0, 1.0])\"" } )
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (inverse) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([$1.,$2.],[$3.,$4.]);"
			"return(string((m*m.inverse()).apply(@(x,y,v){x;y;math.round(v,7);})));"
			"}"
		),
		"\"math.Matrix([$1, $0], [$0, $1])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (transpose) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([1.,2.],[3.,4.],[5.,6.]);"
			"return(string(m.transpose()));"
			"}"
		),
		"\"math.Matrix([1.0, 3.0, 5.0], [2.0, 4.0, 6.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (transpose) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix([$1.,$2.],[$3.,$4.],[$5,$6]);"
			"return(string(m.transpose()));"
			"}"
		),
		"\"math.Matrix([$1, $3, $5], [$2, $4, $6])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (set/get) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix(real,2,2);"
			"m1.set(0,0,1.);"
			"m1.set(0,1,2.);"
			"m1.set(1,0,3.);"
			"m1.set(1,1,4.);"
			"m1.scale(m1.get(0,1));"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([2.0, 4.0], [6.0, 8.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix (set/get) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m1=math.Matrix(number,2,2);"
			"m1.set(0,0,$1.);"
			"m1.set(0,1,$2.);"
			"m1.set(1,0,$3.);"
			"m1.set(1,1,$4.);"
			"m1.scale(m1.get(0,1));"
			"return(string(m1));"
			"}"
		),
		"\"math.Matrix([$2, $4], [$6, $8])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix rows/columns (real) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix(real,3,2);"
			"return([m.rows(),m.columns()]);"
			"}"
		),
		"[3, 2]"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix rows/columns (number) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"m=math.Matrix(number,3,2);"
			"return([m.rows(),m.columns()]);"
			"}"
		),
		"[3, 2]"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (real) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"return(string(math.Matrix(real,2,2).apply(@(r,c,z){real(c+1+r*2)+z;})));"
			"}"
		),
		"\"math.Matrix([1.0, 2.0], [3.0, 4.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (real) (meth) failed",
		execute(
			"import Mathematics as math;"
			"class Apply {"
			"do(r,c,z) {"
			"real(c+1+r*2)+z;"
			"}"
			"}"
			"main(){"
			"return(string(math.Matrix(real,2,2).apply(Apply().do)));"
			"}"
		),
		"\"math.Matrix([1.0, 2.0], [3.0, 4.0])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (number) failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"return(string(math.Matrix(number,2,2).apply(@(r,c,z){number(c+1+r*2)+z;})));"
			"}"
		),
		"\"math.Matrix([$1, $2], [$3, $4])\""
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix apply (number) (meth) failed",
		execute(
			"import Mathematics as math;"
			"class Apply {"
			"do(r,c,z) {"
			"number(c+1+r*2)+z;"
			"}"
			"}"
			"main(){"
			"return(string(math.Matrix(number,2,2).apply(Apply().do)));"
			"}"
		),
		"\"math.Matrix([$1, $2], [$3, $4])\""
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Matrix err" )
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid rows succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix(real,0,1);"
			"}"
		),
		"*anonymous stream*:1:46: Invalid number of rows in matrix specification: 0."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid cols succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix(real,1,0);"
			"}"
		),
		"*anonymous stream*:1:46: Invalid number of columns in matrix specification: 0."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix(integer,1,1);"
			"}"
		),
		"*anonymous stream*:1:46: Bad matrix type: `integer`."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid cols from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([]);"
			"}"
		),
		"*anonymous stream*:1:46: Invalid number of columns in matrix specification: 0."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix invalid type from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0]);"
			"}"
		),
		"*anonymous stream*:1:46: Matrix must have numeric data, either `number` or `real`."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix col count mismatch from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.],[0.,0.]);"
			"}"
		),
		"*anonymous stream*:1:46: Inconsistent number of columns across rows: 2 vs 1."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix non-uniform type from list succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.,$0]);"
			"}"
		),
		"*anonymous stream*:1:46: Non uniformly typed data in matrix definition, in row: 0, column: 1."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).get(-1,0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).get(-1,0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).get(0,-1);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in get succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).get(0,-1);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).set(-1,0,0.);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad row in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).set(-1,0,$0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad row: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).set(0,-1,0.);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad column in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).set(0,-1,$0);"
			"}"
		),
		"*anonymous stream*:1:56: Bad column: -1"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).set(0,0,$0);"
			"}"
		),
		"*anonymous stream*:1:56: Matrix.set() third argument must be a `real`, not a `number`."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in set succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).set(0,0,0.);"
			"}"
		),
		"*anonymous stream*:1:56: Matrix.set() third argument must be a `number`, not a `real`."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in add succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0])+math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:52: Non matching data types."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix dim mismatch in add succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.])+math.Matrix([0.,0.]);"
			"}"
		),
		"*anonymous stream*:1:52: columns dimensions do not match"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in sub succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0])-math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:52: Non matching data types."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix dim mismatch in sub succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.])-math.Matrix([0.,0.]);"
			"}"
		),
		"*anonymous stream*:1:52: columns dimensions do not match"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad type in mul succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0])*math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:52: Non matching data types."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix dim mismatch in mul succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.,0.])*math.Matrix([0.]);"
			"}"
		),
		"*anonymous stream*:1:55: columns does not match rows"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix det on non-square succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"|math.Matrix([0.,0.])|;"
			"}"
		),
		"*anonymous stream*:1:56: matrix is not square"
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix scale on zero Matrix succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([0.]).scale_to(1.);"
			"}"
		),
		"*anonymous stream*:1:61: Zeroed matrix cannot be scaled."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix scale on zero Matrix succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([$0]).scale_to($1);"
			"}"
		),
		"*anonymous stream*:1:61: Zeroed matrix cannot be scaled."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix type mismatch on scale succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.Matrix([1.]).scale_to($1);"
			"}"
		),
		"*anonymous stream*:1:61: Matrix.scale_to() argument must be a `real`, not a `number`."
	);
	ENSURE_EQUALS(
		"Mathematics.Matrix bad apply return type succeeded",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"return(string(math.Matrix(real,2,2).apply(@(r,c,z){number(c+1+r*2)+number(z);})));"
			"}"
		),
		"*anonymous stream*:1:76: Applied transformation function shall return `real`, but result was a `number` instead."
	);
#ifndef __HOST_OS_TYPE_DARWIN__
#ifndef __HOST_OS_TYPE_CYGWIN__
#ifndef CONTINUOUS_INTEGRATION_TRAVIS
#if SIZEOF_INT_LONG == 8
	char const err[] = "*anonymous stream*:3:12: yaal::memory::new: new returned NULL";
#else
	char const err[] = "*anonymous stream*:3:12: Signed integer multiplication overflow.";
#endif
	ENSURE_EQUALS(
		"Allocation Matrix of absurd size succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Matrix(real,0x40000000,1);\n"
			"}\n"
		),
		err
	);
#endif /* #ifndef CONTINUOUS_INTEGRATION_TRAVIS */
#endif /* #ifndef __HOST_OS_TYPE_CYGWIN__ */
#endif /* #ifndef __HOST_OS_TYPE_DARWIN__ */
TUT_TEARDOWN()

TUT_UNIT_TEST( "Mathematics Complex" )
	ENSURE_EQUALS(
		"Mathematics.Complex add",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a + b);\n"
			"}\n"
		),
		"math.Complex(4.0, 6.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex sub",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a - b);\n"
			"}\n"
		),
		"math.Complex(-2.0, -2.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex mul",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a * b);\n"
			"}\n"
		),
		"math.Complex(-5.0, 10.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex div",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(3.,4.);\n"
			"return(a / b);\n"
			"}\n"
		),
		"math.Complex(0.44, 0.08)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex div (0+0i)",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"a = math.Complex(1.,2.);\n"
			"b = math.Complex(0.,0.);\n"
			"return(a / b);\n"
			"}\n"
		),
		"*anonymous stream*:5:10: Uncaught ArithmeticException: denominator equals 0"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex mod",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return(|b|);\n"
			"}\n"
		),
		"5.0"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex neg",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( - b );\n"
			"}\n"
		),
		"math.Complex(-3.0, -4.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex argument",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( b.argument() );\n"
			"}\n"
		),
		"0.927295218002"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex argument (0+0i)",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(0.,0.);\n"
			"return( b.argument() );\n"
			"}\n"
		),
		"*anonymous stream*:4:19: Uncaught ArithmeticException: Argument for 0 + 0i is undefined."
	);
	ENSURE_EQUALS(
		"Mathematics.Complex real/imaginary",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( ( b.real(), b.imaginary() ) );\n"
			"}\n"
		),
		"(3.0, 4.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex get",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(3.,4.);\n"
			"return( b.get() );\n"
			"}\n"
		),
		"(3.0, 4.0)"
	);
	ENSURE_EQUALS(
		"Mathematics.Complex set",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"b = math.Complex(0.,0.);\n"
			"b.set(3.,4.);\n"
			"return( b.get() );\n"
			"}\n"
		),
		"(3.0, 4.0)"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Randomizer" )
	ENSURE_EQUALS(
		"Mathematics.Randomizer( DISCRETE ) failed",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(math.Randomizer.DISTRIBUTION.DISCRETE, 1, 10);\n"
			"d=r.next();\n"
			"return([r,d>=1,d<=10]);\n"
			"}\n"
		),
		"[math.Randomizer(math.Randomizer.DISTRIBUTION.DISCRETE, 1, 10), true, true]"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( UNIFORM ) failed",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(math.Randomizer.DISTRIBUTION.UNIFORM, -1., 1.);\n"
			"u=r.next();\n"
			"return([r,u>=-1.,u<=1.]);\n"
			"}\n"
		),
		"[math.Randomizer(math.Randomizer.DISTRIBUTION.UNIFORM, -1.0, 1.0), true, true]"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( TRIANGLE ) failed",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(math.Randomizer.DISTRIBUTION.TRIANGLE, 1., 4., 3.);\n"
			"t=r.next();\n"
			"return([r,t>=1.,t<=4.]);\n"
			"}\n"
		),
		"[math.Randomizer(math.Randomizer.DISTRIBUTION.TRIANGLE, 1.0, 4.0, 3.0), true, true]"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( NORMAL ) failed",
		execute(
			"import Algorithms as algo;\n"
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(math.Randomizer.DISTRIBUTION.NORMAL, 0., 1.);\n"
			"l=[];\n"
			"for(i : algo.range(100000)){\n"
			"x=r.next();\n"
			"if((x>-3.)&&(x<3.)) {\n"
			"l.push(x);\n"
			"}\n"
			"}\n"
			"bucketCount = 31;\n"
			"midBucketIdx = bucketCount / 2;\n"
			"halfMidBucketIdx = midBucketIdx / 2;\n"
			"s=math.statistics(l,bucketCount);\n"
			"h=algo.materialize(algo.map(s.histogram(),real), list);\n"
			"leftTail = h[1] - h[0];\n"
			"leftSlope = h[halfMidBucketIdx] - h[halfMidBucketIdx - 1];\n"
			"leftPeak = h[midBucketIdx] - h[midBucketIdx - 1];\n"
			"rightTail = h[-1-1] - h[-0-1];\n"
			"rightSlope = h[-halfMidBucketIdx-1] - h[-(halfMidBucketIdx - 1)-1];\n"
			"rightPeak = h[-midBucketIdx-1] - h[-(midBucketIdx - 1)-1];\n"
			"s = [leftTail < leftSlope, leftSlope > leftPeak, rightPeak < rightSlope, rightSlope > rightTail];\n"
			"return([r,s]);\n"
			"}\n"
		),
		"[math.Randomizer(math.Randomizer.DISTRIBUTION.NORMAL, 0.0, 1.0), [true, true, true, true]]"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer copy failed",
		execute(
			"import Mathematics as math;\n"
			"import Algorithms as algo;\n"
			"class RndGen {_rnd=none;constructor(rnd_){_rnd=rnd_;}do(x){x;_rnd.next();}}"
			"main(){\n"
			"range1=algo.range(100);\n"
			"range2=copy(range1);\n"
			"rnd1=math.Randomizer(math.Randomizer.DISTRIBUTION.DISCRETE, -1000000,1000000);\n"
			"rnd2=copy(rnd1);\n"
			"res1=algo.materialize(algo.map(range1,RndGen(rnd1).do),list);\n"
			"res2=algo.materialize(algo.map(range2,RndGen(rnd2).do),list);\n"
			"return(res1==res2);\n"
			"}\n"
		),
		"true"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer.seed failed",
		execute(
			"import Algorithms as algo;\n"
			"import Mathematics as math;\n"
			"main(){\n"
			"r=math.Randomizer(math.Randomizer.DISTRIBUTION.DISCRETE, 0,100);\n"
			"r.seed(0);\n"
			"l1 = algo.materialize(algo.map(algo.range(16),@[r](_){_;r.next();}),list);\n"
			"r.seed(0);\n"
			"l2 = algo.materialize(algo.map(algo.range(16),@[r](_){_;r.next();}),list);\n"
			"return((l1,l2, l1 == l2));\n"
			"}\n"
		),
		"([50, 34, 77, 98, 11, 13, 12, 64, 50, 25, 44, 81, 92, 91, 47, 96], [50, 34, 77, 98, 11, 13, 12, 64, 50, 25, 44, 81, 92, 91, 47, 96], true)"
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( DISCRETE ) invalid definition succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Randomizer(math.Randomizer.DISTRIBUTION.DISCRETE, 1, 0);\n"
			"}\n"
		),
		"*anonymous stream*:3:16: Invalid DISCRETE parametrization."
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( UNIFORM ) invalid definition succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Randomizer(math.Randomizer.DISTRIBUTION.UNIFORM, 0., 1);\n"
			"}\n"
		),
		"*anonymous stream*:3:16: Randomizer.constructor() third argument must be a `real`, not an `integer`."
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( TRIANGLE ) invalid definition succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Randomizer(math.Randomizer.DISTRIBUTION.TRIANGLE, -1., 1., 2.);\n"
			"}\n"
		),
		"*anonymous stream*:3:16: Invalid TRIANGLE parametrization."
	);
	ENSURE_EQUALS(
		"Mathematics.Randomizer( NORMAL ) invalid definition succeeded",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"math.Randomizer(math.Randomizer.DISTRIBUTION.NORMAL, 0., 0.);\n"
			"}\n"
		),
		"*anonymous stream*:3:16: Invalid NORMAL parametrization."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "max" )
	ENSURE_EQUALS(
		"Mathematics.max failed",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"return(math.max(77, 7, 39, 57, 80, 16, 72, 70, 87, 33));\n"
			"}"
		),
		"87"
	);
	ENSURE_EQUALS(
		"Mathematics.max failed",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"return(math.max(1,2.));\n"
			"}"
		),
		"*anonymous stream*:3:16: Operand types for `<` do not match: an `integer` vs a `real`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "min" )
	ENSURE_EQUALS(
		"Mathematics.min failed",
		execute(
			"import Mathematics as math;\n"
			"main(){\n"
			"return(math.min(77, 7, 39, 57, 80, 16, 72, 70, 87, 33));\n"
			"}"
		),
		"7"
	);
	ENSURE_EQUALS(
		"Mathematics.min failed",
		execute_except(
			"import Mathematics as math;\n"
			"main(){\n"
			"return(math.min(1,2.));\n"
			"}"
		),
		"*anonymous stream*:3:16: Operand types for `<` do not match: a `real` vs an `integer`."
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "Mathematics.NumberSetStatistics" )
	ENSURE_IN(
		"tuple real failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), real),tuple));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation(), nss.sample_skewness(), nss.sample_skewness(),"
							"nss.sample_kurtosis(), nss.sample_kurtosis()]);"
			"}"
		),
	  std::vector<hcore::HString>({
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666667, 76.026311234993, 73.448394581956, 63.466666666667, 0.0, 0.0, -1.2, -1.2]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5779.999999999998, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667, 0.0, 0.0, -1.2, -1.2]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667, 0.0, 0.0, -1.2, -1.2]"
		})
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics tuple (number) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), number),tuple));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation(), nss.sample_skewness(), nss.sample_skewness(),"
							"nss.sample_kurtosis(), nss.sample_kurtosis()]);"
			"}"
		),
		"[15, $1, $239, $238, $120, $1800, $120, $120, $136, $5780, $5394.6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $76.026311234992849677911904736863392004981024226791874625210506343957711471685366580090089884878597349, $73.448394581955749284280964275663962120658982146661260896728683175175663615565836209204090274863582671, $63.4666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $0, $0, $-1.1999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995, $-1.1999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995]"
	);
	ENSURE_IN(
		"Mathematics.NumberSetStatistics list (real) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), real),list));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
	  std::vector<hcore::HString>({
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666667, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5779.999999999998, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]"
		})
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics list (number) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), number),list));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
		"[15, $1, $239, $238, $120, $1800, $120, $120, $136, $5780, $5394.6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $76.026311234992849677911904736863392004981024226791874625210506343957711471685366580090089884878597349, $73.448394581955749284280964275663962120658982146661260896728683175175663615565836209204090274863582671, $63.4666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666]"
	);
	ENSURE_IN(
		"verify_arg_collection_value_type deque failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), real),deque));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
	  std::vector<hcore::HString>({
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666667, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5779.999999999998, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]"
		})
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics deque (number) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), number),deque));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
		"[15, $1, $239, $238, $120, $1800, $120, $120, $136, $5780, $5394.6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $76.026311234992849677911904736863392004981024226791874625210506343957711471685366580090089884878597349, $73.448394581955749284280964275663962120658982146661260896728683175175663615565836209204090274863582671, $63.4666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666]"
	);
	ENSURE_IN(
		"verify_arg_collection_value_type set failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), real),set));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
	  std::vector<hcore::HString>({
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666667, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5779.999999999998, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]"
		})
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics set (number) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), number),set));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
		"[15, $1, $239, $238, $120, $1800, $120, $120, $136, $5780, $5394.6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $76.026311234992849677911904736863392004981024226791874625210506343957711471685366580090089884878597349, $73.448394581955749284280964275663962120658982146661260896728683175175663615565836209204090274863582671, $63.4666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666]"
	);
	ENSURE_IN(
		"verify_arg_collection_value_type order failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), real),order));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
	  std::vector<hcore::HString>({
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666667, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5779.999999999998, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]",
			"[15, 1.0, 239.0, 238.0, 120.0, 1800.0, 120.0, 120.0, 136.0, 5780.0, 5394.666666666668, 76.026311234993, 73.448394581956, 63.466666666667]"
		})
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics order (number) failed",
		execute(
			"import Algorithms as algo;"
			"import Mathematics as math;"
			"main(){"
			"nss=math.statistics(algo.materialize(algo.map(algo.range(1,256,17), number),order));"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
		"[15, $1, $239, $238, $120, $1800, $120, $120, $136, $5780, $5394.6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666, $76.026311234992849677911904736863392004981024226791874625210506343957711471685366580090089884878597349, $73.448394581955749284280964275663962120658982146661260896728683175175663615565836209204090274863582671, $63.4666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666]"
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics on one element failed",
		execute(
			"import Mathematics as math;"
			"main(){"
			"nss = math.statistics([1.]);"
			"return([nss.count(),nss.minimum(),nss.maximum(),"
							"nss.range(),nss.mid_range(),nss.sum(),nss.arithmetic_mean(),nss.median(),"
							"nss.interquartile_range(),nss.sample_variance(),nss.population_variance(),"
							"nss.sample_standard_deviation(),nss.population_standard_deviation(),"
							"nss.mean_absolute_deviation()]);"
			"}"
		),
		"[1, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, none, 0.0, none, 0.0, 0.0]"
	);
	ENSURE_EQUALS(
		"Mathematics.NumberSetStatistics on empty failed",
		execute_except(
			"import Mathematics as math;"
			"main(){"
			"math.statistics([]);"
			"}"
		),
		"*anonymous stream*:1:50: Cannot aggregate statistics over empty set."
	);
	typedef yaal::hcore::HArray<HString> string_array_t;
	string_array_t sa;
	transform( begin( _testData_[0] ), end( _testData_[0] ), back_insert_iterator( sa ), static_cast<HString (*)( double )>( &to_string ) );
	HString data( string::join( sa, "," ) );
	ENSURE_EQUALS(
		"histogram failed",
		execute(
			"import Mathematics as math;"
			"main() {"
			"data = ["
			""_ys.append( data ).append(
				"];"
				"stats = math.statistics( data, 10 );"
				"return ( stats.histogram() );"
				"}"
			)
		),
		"[16, 13, 9, 9, 11, 8, 9, 9, 9, 7]"
	);
	ENSURE_EQUALS(
		"histogram failed",
		execute_except(
			"import Mathematics as math;"
			"main() {"
			"data = ["
			""_ys.append( data ).append(
				"];"
				"stats = math.statistics( data );"
				"return ( stats.histogram() );"
				"}"
			)
		),
		"*anonymous stream*:1:672: No histogram information was requested nor generated."
	);
TUT_TEARDOWN()

}


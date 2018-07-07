/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/money.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::money;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_money_in_words );
TUT_TEST_GROUP( tut_yaal_tools_money_in_words, "yaal::tools::money::in_words" );

TUT_UNIT_TEST( "en < 20" )
	char const expected[][64] = {
		"zero dollars and zero cents",
		"one dollar and zero cents",
		"two dollars and zero cents",
		"three dollars and zero cents",
		"four dollars and zero cents",
		"five dollars and zero cents",
		"six dollars and zero cents",
		"seven dollars and zero cents",
		"eight dollars and zero cents",
		"nine dollars and zero cents",
		"ten dollars and zero cents",
		"eleven dollars and zero cents",
		"twelve dollars and zero cents",
		"thirteen dollars and zero cents",
		"fourteen dollars and zero cents",
		"fifteen dollars and zero cents",
		"sixteen dollars and zero cents",
		"seventeen dollars and zero cents",
		"eighteen dollars and zero cents",
		"nineteen dollars and zero cents"
	};
	HString s;
	for ( int i( 0 ); i < 20; ++ i ) {
		ENSURE_EQUALS( "en "_ys.append( i ).append( " failed" ), s = in_words_en( i, CURRENCY::DOLLAR ), expected[i] );
		clog << i << " = [" << s << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "tenths en" )
	char const expected[][64] = {
		"ten dollars and zero cents",
		"twenty dollars and zero cents",
		"thirty dollars and zero cents",
		"forty dollars and zero cents",
		"fifty dollars and zero cents",
		"sixty dollars and zero cents",
		"seventy dollars and zero cents",
		"eighty dollars and zero cents",
		"ninety dollars and zero cents"
	};
	HString s;
	for ( int i( 0 ), v( 10 ); v < 100; v += 10, ++ i ) {
		ENSURE_EQUALS( "en "_ys.append( v ).append( " failed" ), s = in_words_en( v, CURRENCY::DOLLAR ), expected[i] );
		clog << v << " = [" << s << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "en 18 < x < 32" )
	char const expected[][64] = {
		"nineteen dollars and zero cents",
		"twenty dollars and zero cents",
		"twenty-one dollars and zero cents",
		"twenty-two dollars and zero cents",
		"twenty-three dollars and zero cents",
		"twenty-four dollars and zero cents",
		"twenty-five dollars and zero cents",
		"twenty-six dollars and zero cents",
		"twenty-seven dollars and zero cents",
		"twenty-eight dollars and zero cents",
		"twenty-nine dollars and zero cents",
		"thirty dollars and zero cents",
		"thirty-one dollars and zero cents"
	};
	HString s;
	for ( int i( 0 ), v( 19 ); v < 32; ++ v, ++ i ) {
		ENSURE_EQUALS( "en "_ys.append( v ).append( " failed" ), s = in_words_en( v, CURRENCY::DOLLAR ), expected[i] );
		clog << v << " = [" << s << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "en 85 < x < 257" )
	char const expected[][64] = {
		"eighty-four dollars and zero cents",
		"ninety-seven dollars and zero cents",
		"one hundred ten dollars and zero cents",
		"one hundred twenty-three dollars and zero cents",
		"one hundred thirty-six dollars and zero cents",
		"one hundred forty-nine dollars and zero cents",
		"one hundred sixty-two dollars and zero cents",
		"one hundred seventy-five dollars and zero cents",
		"one hundred eighty-eight dollars and zero cents",
		"two hundred one dollars and zero cents",
		"two hundred fourteen dollars and zero cents",
		"two hundred twenty-seven dollars and zero cents",
		"two hundred forty dollars and zero cents",
		"two hundred fifty-three dollars and zero cents"
	};
	HString s;
	for ( int i( 0 ), v( 84 ); v < 257; v += 13, ++ i ) {
		ENSURE_EQUALS( "en "_ys.append( v ).append( " failed" ), s = in_words_en( v, CURRENCY::DOLLAR ), expected[i] );
		clog << v << " = [" << s << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "big en" )
	char const expected[][200] = {
		"zero dollars and zero cents",
		"one dollar and zero cents",
		"two dollars and zero cents",
		"three dollars and zero cents",
		"four dollars and zero cents",
		"five dollars and zero cents",
		"six dollars and zero cents",
		"seven dollars and zero cents",
		"eight dollars and zero cents",
		"nine dollars and zero cents",
		"ten dollars and zero cents",
		"eleven dollars and zero cents",
		"twelve dollars and zero cents",
		"twenty-three dollars and zero cents",
		"thirty-four dollars and zero cents",
		"forty-five dollars and zero cents",
		"fifty-six dollars and zero cents",
		"sixty-seven dollars and zero cents",
		"seventy-eight dollars and zero cents",
		"eighty-nine dollars and zero cents",
		"one hundred dollars and zero cents",
		"one hundred eleven dollars and zero cents",
		"one hundred twenty-two dollars and zero cents",
		"two hundred thirty-three dollars and zero cents",
		"three hundred forty-four dollars and zero cents",
		"four hundred fifty-five dollars and zero cents",
		"five hundred sixty-six dollars and zero cents",
		"six hundred seventy-seven dollars and zero cents",
		"seven hundred eighty-eight dollars and zero cents",
		"eight hundred ninety-nine dollars and zero cents",
		"one thousand ten dollars and zero cents",
		"one thousand one hundred twenty-one dollars and zero cents",
		"two thousand two hundred thirty-two dollars and zero cents",
		"three thousand three hundred forty-three dollars and zero cents",
		"four thousand four hundred fifty-four dollars and zero cents",
		"five thousand five hundred sixty-five dollars and zero cents",
		"six thousand six hundred seventy-six dollars and zero cents",
		"seven thousand seven hundred eighty-seven dollars and zero cents",
		"eight thousand eight hundred ninety-eight dollars and zero cents",
		"ten thousand nine dollars and zero cents",
		"eleven thousand one hundred twenty dollars and zero cents",
		"twenty-two thousand two hundred thirty-one dollars and zero cents",
		"thirty-three thousand three hundred forty-two dollars and zero cents",
		"forty-four thousand four hundred fifty-three dollars and zero cents",
		"fifty-five thousand five hundred sixty-four dollars and zero cents",
		"sixty-six thousand six hundred seventy-five dollars and zero cents",
		"seventy-seven thousand seven hundred eighty-six dollars and zero cents",
		"eighty-eight thousand eight hundred ninety-seven dollars and zero cents",
		"one hundred thousand eight dollars and zero cents",
		"one hundred eleven thousand one hundred nineteen dollars and zero cents",
		"two hundred twenty-two thousand two hundred thirty dollars and zero cents",
		"three hundred thirty-three thousand three hundred forty-one dollars and zero cents",
		"four hundred forty-four thousand four hundred fifty-two dollars and zero cents",
		"five hundred fifty-five thousand five hundred sixty-three dollars and zero cents",
		"six hundred sixty-six thousand six hundred seventy-four dollars and zero cents",
		"seven hundred seventy-seven thousand seven hundred eighty-five dollars and zero cents",
		"eight hundred eighty-eight thousand eight hundred ninety-six dollars and zero cents",
		"one million seven dollars and zero cents",
		"one million one hundred eleven thousand one hundred eighteen dollars and zero cents",
		"two million two hundred twenty-two thousand two hundred twenty-nine dollars and zero cents",
		"three million three hundred thirty-three thousand three hundred forty dollars and zero cents",
		"four million four hundred forty-four thousand four hundred fifty-one dollars and zero cents",
		"five million five hundred fifty-five thousand five hundred sixty-two dollars and zero cents",
		"six million six hundred sixty-six thousand six hundred seventy-three dollars and zero cents",
		"seven million seven hundred seventy-seven thousand seven hundred eighty-four dollars and zero cents",
		"eight million eight hundred eighty-eight thousand eight hundred ninety-five dollars and zero cents",
		"ten million six dollars and zero cents",
		"eleven million one hundred eleven thousand one hundred seventeen dollars and zero cents",
		"twenty-two million two hundred twenty-two thousand two hundred twenty-eight dollars and zero cents",
		"thirty-three million three hundred thirty-three thousand three hundred thirty-nine dollars and zero cents",
		"forty-four million four hundred forty-four thousand four hundred fifty dollars and zero cents",
		"fifty-five million five hundred fifty-five thousand five hundred sixty-one dollars and zero cents",
		"sixty-six million six hundred sixty-six thousand six hundred seventy-two dollars and zero cents",
		"seventy-seven million seven hundred seventy-seven thousand seven hundred eighty-three dollars and zero cents",
		"eighty-eight million eight hundred eighty-eight thousand eight hundred ninety-four dollars and zero cents",
		"one hundred million five dollars and zero cents",
		"one hundred eleven million one hundred eleven thousand one hundred sixteen dollars and zero cents",
		"two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-seven dollars and zero cents",
		"three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-eight dollars and zero cents",
		"four hundred forty-four million four hundred forty-four thousand four hundred forty-nine dollars and zero cents",
		"five hundred fifty-five million five hundred fifty-five thousand five hundred sixty dollars and zero cents",
		"six hundred sixty-six million six hundred sixty-six thousand six hundred seventy-one dollars and zero cents",
		"seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred eighty-two dollars and zero cents",
		"eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred ninety-three dollars and zero cents",
		"one billion four dollars and zero cents",
		"one billion one hundred eleven million one hundred eleven thousand one hundred fifteen dollars and zero cents",
		"two billion two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-six dollars and zero cents",
		"three billion three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-seven dollars and zero cents",
		"four billion four hundred forty-four million four hundred forty-four thousand four hundred forty-eight dollars and zero cents",
		"five billion five hundred fifty-five million five hundred fifty-five thousand five hundred fifty-nine dollars and zero cents",
		"six billion six hundred sixty-six million six hundred sixty-six thousand six hundred seventy dollars and zero cents",
		"seven billion seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred eighty-one dollars and zero cents",
		"eight billion eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred ninety-two dollars and zero cents",
		"ten billion three dollars and zero cents",
		"eleven billion one hundred eleven million one hundred eleven thousand one hundred fourteen dollars and zero cents",
		"twenty-two billion two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-five dollars and zero cents",
		"thirty-three billion three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-six dollars and zero cents",
		"forty-four billion four hundred forty-four million four hundred forty-four thousand four hundred forty-seven dollars and zero cents",
		"fifty-five billion five hundred fifty-five million five hundred fifty-five thousand five hundred fifty-eight dollars and zero cents",
		"sixty-six billion six hundred sixty-six million six hundred sixty-six thousand six hundred sixty-nine dollars and zero cents",
		"seventy-seven billion seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred eighty dollars and zero cents",
		"eighty-eight billion eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred ninety-one dollars and zero cents",
		"one hundred billion two dollars and zero cents",
		"one hundred eleven billion one hundred eleven million one hundred eleven thousand one hundred thirteen dollars and zero cents",
		"two hundred twenty-two billion two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-four dollars and zero cents",
		"three hundred thirty-three billion three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-five dollars and zero cents",
		"four hundred forty-four billion four hundred forty-four million four hundred forty-four thousand four hundred forty-six dollars and zero cents",
		"five hundred fifty-five billion five hundred fifty-five million five hundred fifty-five thousand five hundred fifty-seven dollars and zero cents",
		"six hundred sixty-six billion six hundred sixty-six million six hundred sixty-six thousand six hundred sixty-eight dollars and zero cents",
		"seven hundred seventy-seven billion seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred seventy-nine dollars and zero cents",
		"eight hundred eighty-eight billion eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred ninety dollars and zero cents",
		"one trillion one dollars and zero cents",
		"one trillion one hundred eleven billion one hundred eleven million one hundred eleven thousand one hundred twelve dollars and zero cents",
		"two trillion two hundred twenty-two billion two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-three dollars and zero cents",
		"three trillion three hundred thirty-three billion three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-four dollars and zero cents",
		"four trillion four hundred forty-four billion four hundred forty-four million four hundred forty-four thousand four hundred forty-five dollars and zero cents",
		"five trillion five hundred fifty-five billion five hundred fifty-five million five hundred fifty-five thousand five hundred fifty-six dollars and zero cents",
		"six trillion six hundred sixty-six billion six hundred sixty-six million six hundred sixty-six thousand six hundred sixty-seven dollars and zero cents",
		"seven trillion seven hundred seventy-seven billion seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred seventy-eight dollars and zero cents",
		"eight trillion eight hundred eighty-eight billion eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred eighty-nine dollars and zero cents",
		"ten trillion dollars and zero cents",
		"eleven trillion one hundred eleven billion one hundred eleven million one hundred eleven thousand one hundred eleven dollars and zero cents",
		"twelve trillion two hundred twenty-two billion two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-two dollars and zero cents",
		"twenty-three trillion three hundred thirty-three billion three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-three dollars and zero cents",
		"thirty-four trillion four hundred forty-four billion four hundred forty-four million four hundred forty-four thousand four hundred forty-four dollars and zero cents",
		"forty-five trillion five hundred fifty-five billion five hundred fifty-five million five hundred fifty-five thousand five hundred fifty-five dollars and zero cents",
		"fifty-six trillion six hundred sixty-six billion six hundred sixty-six million six hundred sixty-six thousand six hundred sixty-six dollars and zero cents",
		"sixty-seven trillion seven hundred seventy-seven billion seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred seventy-seven dollars and zero cents",
		"seventy-eight trillion eight hundred eighty-eight billion eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred eighty-eight dollars and zero cents",
		"eighty-nine trillion nine hundred ninety-nine billion nine hundred ninety-nine million nine hundred ninety-nine thousand nine hundred ninety-nine dollars and zero cents"
	};
	HString s;
	int long long step( 1 );
	for ( int long long i( 0 ), v( 0 ); v < 100000000000000LL; v += step, ++ i ) {
		ENSURE_EQUALS( "en "_ys.append( v ).append( " failed" ), s = in_words_en( v, CURRENCY::DOLLAR ), expected[i] );
		clog << v << " = [" << s << "]" << endl;
		if ( v > 11111111111111LL ) {
			step = 11111111111111LL;
		} else if ( v > 1111111111111LL ) {
			step = 1111111111111LL;
		} else if ( v > 111111111111LL ) {
			step = 111111111111LL;
		} else if ( v > 11111111111LL ) {
			step = 11111111111LL;
		} else if ( v > 1111111111LL ) {
			step = 1111111111LL;
		} else if ( v > 111111111LL ) {
			step = 111111111LL;
		} else if ( v > 11111111LL ) {
			step = 11111111LL;
		} else if ( v > 1111111LL ) {
			step = 1111111LL;
		} else if ( v > 111111LL ) {
			step = 111111LL;
		} else if ( v > 11111LL ) {
			step = 11111LL;
		} else if ( v > 1111LL ) {
			step = 1111LL;
		} else if ( v > 111LL ) {
			step = 111LL;
		} else if ( v > 11LL ) {
			step = 11LL;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "mostly zeros en" )
	char const expected[][64] = {
		"zero dollars and zero cents",
		"one dollar and zero cents",
		"ten dollars and zero cents",
		"eleven dollars and zero cents",
		"one hundred dollars and zero cents",
		"one hundred one dollars and zero cents",
		"one thousand dollars and zero cents",
		"one thousand one dollars and zero cents",
		"one thousand one hundred dollars and zero cents",
		"ten thousand dollars and zero cents",
		"ten thousand one dollars and zero cents",
		"ten thousand one hundred dollars and zero cents",
		"eleven thousand dollars and zero cents",
		"one hundred thousand dollars and zero cents",
		"one hundred thousand one dollars and zero cents",
		"one hundred thousand one hundred dollars and zero cents",
		"one hundred one thousand dollars and zero cents",
		"one million dollars and zero cents",
		"one million one dollars and zero cents",
		"one million one hundred dollars and zero cents",
		"one million one thousand dollars and zero cents",
		"one million one hundred thousand dollars and zero cents",
		"ten million dollars and zero cents",
		"ten million one dollars and zero cents",
		"ten million one hundred dollars and zero cents",
		"ten million one thousand dollars and zero cents",
		"ten million one hundred thousand dollars and zero cents",
		"one hundred million dollars and zero cents",
		"one billion dollars and zero cents",
		"ten billion dollars and zero cents",
		"ten million one hundred dollars and one cent"
	};
	int long long v[] = {
		       0LL,        1LL,        10LL,         11LL,         100LL,
		     101LL,     1000LL,      1001LL,       1100LL,       10000LL,
		   10001LL,    10100LL,     11000LL,     100000LL,      100001LL,
		  100100LL,   101000LL,   1000000LL,    1000001LL,     1000100LL,
		 1001000LL,  1100000LL,  10000000LL,   10000001LL,    10000100LL,
		10001000LL, 10100000LL, 100000000LL, 1000000000LL, 10000000000LL
	};
	HString s;
	for ( int i( 0 ); i < yaal::size( v ); ++ i ) {
		ENSURE_EQUALS( "en "_ys.append( v[i] ).append( " failed" ), s = in_words_en( v[i], CURRENCY::DOLLAR ), expected[i] );
		clog << v[i] << " = [" << s << "]" << endl;
	}
	HNumber n( "10000100.01" );
	ENSURE_EQUALS( "en "_ys.append( n.to_string() ).append( " failed" ), s = in_words_en( n, CURRENCY::DOLLAR ), "ten million one hundred dollars and one cent" );
	clog << n.to_string() << " = [" << s << "]" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "pl < 20" )
	char const expected[][64] = {
		"zero złotych zero groszy",
		"jeden złoty zero groszy",
		"dwa złote zero groszy",
		"trzy złote zero groszy",
		"cztery złote zero groszy",
		"pięć złotych zero groszy",
		"sześć złotych zero groszy",
		"siedem złotych zero groszy",
		"osiem złotych zero groszy",
		"dziewięć złotych zero groszy",
		"dziesięć złotych zero groszy",
		"jedenaście złotych zero groszy",
		"dwanaście złotych zero groszy",
		"trzynaście złotych zero groszy",
		"czternaście złotych zero groszy",
		"piętnaście złotych zero groszy",
		"szesnaście złotych zero groszy",
		"siedemnaście złotych zero groszy",
		"osiemnaście złotych zero groszy",
		"dziewiętnaście złotych zero groszy"
	};
	HString s;
	for ( int i( 0 ); i < 20; ++ i ) {
		ENSURE_EQUALS( "pl "_ys.append( i ).append( " failed" ), s = in_words_pl( i, CURRENCY::PLN ), expected[i] );
		clog << i << " = [" << s << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "Iwona" )
	char const trials[][2][160] = {
		{ "854925.10", "osiemset pięćdziesiąt cztery tysiące dziewięćset dwadzieścia pięć dollarów dziesięć centów" },
		{ "3423854923.02", "trzy miliardy czterysta dwadzieścia trzy miliony osiemset pięćdziesiąt cztery tysiące dziewięćset dwadzieścia trzy dollary dwa centy" }
	};
	HString s;
	for ( int i( 0 ); i < yaal::size( trials ); ++ i ) {
		ENSURE_EQUALS( "pl "_ys.append( trials[i][0] ).append( " failed" ), s = in_words_pl( trials[i][0], CURRENCY::DOLLAR ), trials[i][1] );
		clog << trials[i][0] << " = [" << s << "]" << endl;
	}
TUT_TEARDOWN()

}


/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_money_in_words.cxx - this file is integral part of `tress' project.

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
	for ( int i( 0 ); i < 20; ++ i ) {
		cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "tenths en" )
	for ( int i( 10 ); i < 100; i += 10 ) {
		cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "en 18 < x < 32" )
	for ( int i( 19 ); i < 32; ++ i ) {
		cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "en 85 < x < 257" )
	for ( int i( 84 ); i < 257; i += 13 ) {
		cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "big en" )
	int long long step( 1 );
	for ( int long long i( 0 ); i < 100000000000000LL; i += step ) {
		cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
		if ( i > 11111111111111LL ) {
			step = 11111111111111LL;
		} else if ( i > 1111111111111LL ) {
			step = 1111111111111LL;
		} else if ( i > 111111111111LL ) {
			step = 111111111111LL;
		} else if ( i > 11111111111LL ) {
			step = 11111111111LL;
		} else if ( i > 1111111111LL ) {
			step = 1111111111LL;
		} else if ( i > 111111111LL ) {
			step = 111111111LL;
		} else if ( i > 11111111LL ) {
			step = 11111111LL;
		} else if ( i > 1111111LL ) {
			step = 1111111LL;
		} else if ( i > 111111LL ) {
			step = 111111LL;
		} else if ( i > 11111LL ) {
			step = 11111LL;
		} else if ( i > 1111LL ) {
			step = 1111LL;
		} else if ( i > 111LL ) {
			step = 111LL;
		} else if ( i > 11LL ) {
			step = 11LL;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "mostly zeros en" )
	int long long i( 0 );
	i = 0LL;           cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1LL;           cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10LL;          cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 11LL;          cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 100LL;         cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 101LL;         cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1000LL;        cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1001LL;        cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1100LL;        cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10000LL;       cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10001LL;       cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10100LL;       cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 11000LL;       cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 100000LL;      cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 100001LL;      cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 100100LL;      cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 101000LL;      cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1000000LL;     cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1000001LL;     cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1000100LL;     cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1001000LL;     cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1100000LL;     cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10000000LL;    cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10000001LL;    cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10000100LL;    cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10001000LL;    cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10100000LL;    cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 100000000LL;   cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 1000000000LL;  cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	i = 10000000000LL; cout << i << " = [" << in_words_en( i, CURRENCY::DOLLAR ) << "]" << endl;
	HNumber n;
	n = "10000100.01"; cout << n.to_string() << " = [" << in_words_en( n, CURRENCY::DOLLAR ) << "]" << endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "pl < 20" )
	for ( int i( 0 ); i < 20; ++ i ) {
		cout << i << " = [" << in_words_pl( i, CURRENCY::PLN ) << "]" << endl;
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "Iwona" )
	HNumber n;
	n = "854925.10"; cout << n.to_string() << " = [" << in_words_pl( n, CURRENCY::DOLLAR ) << "]" << endl;
	n = "3423854923.02"; cout << n.to_string() << " = [" << in_words_pl( n, CURRENCY::DOLLAR ) << "]" << endl;
TUT_TEARDOWN()

}


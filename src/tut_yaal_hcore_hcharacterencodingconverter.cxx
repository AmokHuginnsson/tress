/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_hcore_hcharacterencodingconverter.cxx - this file is integral part of `tress' project.

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

#include <cstring>
#include <TUT/tut.hpp>

#include <yaal/hcore/hcharacterencodingconverter.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

namespace {
	char const UTF8[] = "utf-8";
}

TUT_SIMPLE_MOCK( tut_yaal_hcore_hcharacterencodingconverter );
TUT_TEST_GROUP( tut_yaal_hcore_hcharacterencodingconverter, "yaal::hcore::HCharacterEncodingConverter" );

TUT_UNIT_TEST( "invalid encoding" )
	ENSURE_THROW( "invalid from accepted", HCharacterEncodingConverter( "invalid", "ascii" ), HCharacterEncodingConverterException );
	ENSURE_THROW( "invalid to accepted", HCharacterEncodingConverter( "ascii", "invalid" ), HCharacterEncodingConverterException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "no op" )
	HCharacterEncodingConverter ascii( "ascii", "ascii" );
	char const en[] = "The quick brown fox jumps over the lazy dog!";
	HCharacterEncodingConversionResult out;
	ascii.convert( en, sizeof ( en ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( en ) ) - 1 );
	ENSURE_EQUALS( "no op failed", memcmp( out.c_str(), en, static_cast<size_t>( out.size() ) + 1 ), 0 );
	HCharacterEncodingConverter latin2( "latin2", "ISO-8859-2" );
	char const pl[] = "Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!";
	latin2.convert( pl, sizeof ( pl ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( pl ) ) - 1 );
	ENSURE_EQUALS( "no op failed", memcmp( out.c_str(), pl, static_cast<size_t>( out.size() ) + 1 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "real conversion" )
	HCharacterEncodingConverter latin2ToUTF8( "latin2", "Utf-8" );
	char const pl[] = "Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!";
	char const plUTF8[] = "MÄ™Å¼ny bÄ…dÅº, chroÅ„ puÅ‚k twÃ³j i szeÅ›Ä‡ flag!";
	HCharacterEncodingConversionResult out;
	latin2ToUTF8.convert( pl, sizeof ( pl ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( plUTF8 ) ) - 1 );
	ENSURE_EQUALS( "latin2 -> utf8 failed", memcmp( out.c_str(), plUTF8, static_cast<size_t>( out.size() ) + 1 ), 0 );
	HCharacterEncodingConverter utf8ToLatin2( UTF8, "iso8859-2" );
	utf8ToLatin2.convert( plUTF8, sizeof ( plUTF8 ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( pl ) ) - 1 );
	ENSURE_EQUALS( "utf8 -> latin2 failed", memcmp( out.c_str(), pl, static_cast<size_t>( out.size() ) + 1 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "copy" )
	HCharacterEncodingConverter init( "latin2", "Utf-8" );
	HCharacterEncodingConverter latin2ToUTF8( init );
	char const pl[] = "Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!";
	char const plUTF8[] = "MÄ™Å¼ny bÄ…dÅº, chroÅ„ puÅ‚k twÃ³j i szeÅ›Ä‡ flag!";
	HCharacterEncodingConversionResult out;
	latin2ToUTF8.convert( pl, sizeof ( pl ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( plUTF8 ) ) - 1 );
	ENSURE_EQUALS( "latin2 -> utf8 failed", memcmp( out.c_str(), plUTF8, static_cast<size_t>( out.size() ) + 1 ), 0 );
	HCharacterEncodingConverter init2( UTF8, "iso8859-2" );
	HCharacterEncodingConverter utf8ToLatin2( "ascii", "ascii" );
	utf8ToLatin2 = init2;
	utf8ToLatin2.convert( plUTF8, sizeof ( plUTF8 ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( pl ) ) - 1 );
	ENSURE_EQUALS( "utf8 -> latin2 failed", memcmp( out.c_str(), pl, static_cast<size_t>( out.size() ) + 1 ), 0 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "move" )
	HCharacterEncodingConverter init( "latin2", "Utf-8" );
	HCharacterEncodingConverter latin2ToUTF8( yaal::move( init ) );
	char const pl[] = "Mê¿ny b±d¼, chroñ pu³k twój i sze¶æ flag!";
	char const plUTF8[] = "MÄ™Å¼ny bÄ…dÅº, chroÅ„ puÅ‚k twÃ³j i szeÅ›Ä‡ flag!";
	HCharacterEncodingConversionResult out;
	latin2ToUTF8.convert( pl, sizeof ( pl ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( plUTF8 ) ) - 1 );
	ENSURE_EQUALS( "latin2 -> utf8 failed", memcmp( out.c_str(), plUTF8, static_cast<size_t>( out.size() ) + 1 ), 0 );
	HCharacterEncodingConverter init2( UTF8, "iso8859-2" );
	HCharacterEncodingConverter utf8ToLatin2( "ascii", "ascii" );
	utf8ToLatin2 = yaal::move( init2 );
	utf8ToLatin2.convert( plUTF8, sizeof ( plUTF8 ) - 1, out );
	ENSURE_EQUALS( "bad out len", out.size(), static_cast<int>( sizeof ( pl ) ) - 1 );
	ENSURE_EQUALS( "utf8 -> latin2 failed", memcmp( out.c_str(), pl, static_cast<size_t>( out.size() ) + 1 ), 0 );
TUT_TEARDOWN()

}



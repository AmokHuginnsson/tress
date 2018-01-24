/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hvector.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_hcore_hvector : public simple_mock<tut_yaal_hcore_hvector> {
	virtual ~tut_yaal_hcore_hvector( void ) {}
	typedef HVector<double long> vector_t;
	void eq( char const* oper_, vector_t const& v1_, vector_t const& v2_ ) {
		ENSURE_EQUALS( "bad row", v1_.dim(), v2_.dim() );
		for ( int c( 0 ); c < v1_.dim(); ++ c ) {
			ENSURE_DISTANCE( to_string( oper_ ).append( " failed" ), v1_[c], v2_[c], epsilon );
		}
	}
};
TUT_TEST_GROUP( tut_yaal_hcore_hvector, "yaal::hcore::HVector" );

TUT_UNIT_TEST( "basic vector operations" )
	std::clog << "<<< vector >>>" << std::endl;
	vector_t v( { 1.2, 2.4, 3.5 } );
	std::clog << "    v = " << v << std::endl;
	vector_t w( 3 );
	w[ 0 ] = 4.7;	w[ 1 ] = 5.1; w[ 2 ] = 6.6;
	eq( "set", w, vector_t( { 4.7, 5.1, 6.6 } ) );
	std::clog << "    w = " << w << std::endl;
	eq( "sum", v + w, vector_t( { 5.9, 7.5, 10.1 } ) );
	std::clog << "v + w = " << v + w << std::endl;
	eq( "scale", v * 2.L, vector_t( { 2.4, 4.8, 7. } ) );
	std::clog << "v * 2 = " << v * 2.L << std::endl;
	eq( "scale", 3.L * w, vector_t( { 14.1, 15.3, 19.8 } ) );
	std::clog << "3 * w = " << 3.L * w << std::endl;
	eq( "diff", w - v, vector_t( { 3.5000, 2.7, 3.1 } ) );
	std::clog << "w - v = " << w - v << std::endl;
	eq( "div scale", w / 2.L, vector_t( { 2.35, 2.55, 3.3 } ) );
	std::clog << "w / 2 = " << w / 2.L << std::endl;
	ENSURE_DISTANCE( "scalar mul", v | w, 40.98L, epsilon );
	std::clog << "v | w = " << ( v | w ) << std::endl;
	eq( "neq", -v, vector_t( { -1.2, -2.4, -3.5 } ) );
	std::clog << "  - v = " << - v << std::endl;
TUT_TEARDOWN()

TUT_UNIT_TEST( "norm()" )
	vector_t v( { 1.2, 2.4, 3.5 } );
	ENSURE_DISTANCE( "bad norm calculated", ! v, 4.41022L, epsilon * 100.L );
	std::clog << "  ! v = " << ! v << std::endl;
	HVector<double> v2( 2 );
	v2[0] = 3.;
	v2[1] = 4.;
	ENSURE_DISTANCE( "bad norm calculated", v2.norm(), 5., static_cast<double>( epsilon ) );
TUT_TEARDOWN()


}


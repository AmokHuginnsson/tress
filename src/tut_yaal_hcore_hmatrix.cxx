/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hmatrix.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {


struct tut_yaal_hcore_hmatrix : public simple_mock<tut_yaal_hcore_hmatrix> {
	virtual ~tut_yaal_hcore_hmatrix( void ) {}
	typedef HMatrix<double long> matrix_t;
	void eq( char const* oper_, matrix_t const& m1_, matrix_t const& m2_ ) {
		ENSURE_EQUALS( "bad row", m1_.rows(), m2_.rows() );
		ENSURE_EQUALS( "bad col", m1_.columns(), m2_.columns() );
		for ( int r( 0 ); r < m1_.rows(); ++ r ) {
			for ( int c( 0 ); c < m1_.columns(); ++ c ) {
				ENSURE_DISTANCE( to_string( oper_ ).append( " failed" ), m1_[r][c], m2_[r][c], epsilon );
			}
		}
	}
};
TUT_TEST_GROUP( tut_yaal_hcore_hmatrix, "yaal::hcore::HMatrix" );

TUT_UNIT_TEST( "ctor" )
	ENSURE_THROW( "initializer list failed to detect malformed source", matrix_t( { {1, 2}, {3} } ), HExceptionT<matrix_t> );
TUT_TEARDOWN()

TUT_UNIT_TEST( "matrix determinant, non-triwial row swap" )
	matrix_t m( 3, 3 );
	m[0][2] = m[1][0] = m[1][1] = m[2][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 1", m.det(), -1.L, epsilon );
	m[0][2] = m[1][0] = m[1][1] = m[2][0] = 0.;
	m[0][2] = m[2][0] = m[2][1] = m[1][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 2", m.det(), 1.L, epsilon );
	m[0][2] = m[2][0] = m[2][1] = m[1][0] = 0.;
	m[1][2] = m[0][0] = m[0][1] = m[2][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 3", m.det(), 1.L, epsilon );
	m[1][2] = m[0][0] = m[0][1] = m[2][0] = 0.;
	m[1][2] = m[2][0] = m[2][1] = m[0][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 4", m.det(), -1.L, epsilon );
	m[1][2] = m[2][0] = m[2][1] = m[0][0] = 0.;
	m[2][2] = m[0][0] = m[0][1] = m[1][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 5", m.det(), -1.L, epsilon );
	m[2][2] = m[0][0] = m[0][1] = m[1][0] = 0.;
	m[2][2] = m[1][0] = m[1][1] = m[0][0] = 1.;
	ENSURE_DISTANCE( "failed to find determinant 6", m.det(), 1.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "det 0" )
	matrix_t m( {
		{  32, -30, -29,  29,  28, -26, -25,  25 },
		{ -23,  23,  22, -20, -19,  19,  18, -16 },
		{ -15,  15,  14, -12, -11,  11,  10,  -8 },
		{   8,  -6,  -5,   5,   4,  -2,  -1,   1 },
		{   0,   2,   3,  -3,  -4,   6,   7,  -7 },
		{   9,  -9, -10,  12,  13, -13, -14,  16 },
		{  17, -17, -18,  20,  21, -21, -22,  24 },
		{ -24,  26,  27, -27, -28,  30,  31, -31 }
	} );
	ENSURE_DISTANCE( "det failed", m.det(), 0.L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "inverse" )
	matrix_t m( {
		{  6, 13, -10, -3,  4 },
		{ 12, -6,  -4,  3,  5 },
		{ -7, -5,   2,  9, 11 },
		{ -1,  1,   8, 10, -8 },
		{  0,  7,  14, -9, -2 }
	} );
	ENSURE_DISTANCE( "det failed", m.det(), 780000.L, epsilon );
	matrix_t res( {
		{  0.011987,  0.068077, -0.018462,  0.018077,  0.020321 },
		{  0.060064, -0.020385,  0.012308,  0.029615,  0.018397 },
		{ -0.013333,  0.020000,  0.020000,  0.020000,  0.053333 },
		{  0.021603,  0.010385,  0.027692,  0.060385, -0.020064 },
		{  0.019679,  0.021923,  0.058462, -0.028077,  0.028013 }
	} );
	matrix_t im( m.inverse() );
	eq( "inverse", im, res );
TUT_TEARDOWN()

TUT_UNIT_TEST( "basic matrix operations" )
	matrix_t V( 3, 3 );
	matrix_t W( 3, 3 );
	matrix_t X( 2, 2 );
	std::clog << "<<< matrix >>>" << std::endl;
	V [ 0 ] [ 0 ] = 1.2, V [ 0 ] [ 1 ] = 2.3, V [ 0 ] [ 2 ] = 3.4;
	V [ 1 ] [ 0 ] = 4.3, V [ 1 ] [ 1 ] = 3.2, V [ 1 ] [ 2 ] = 2.1;
	V [ 2 ] [ 0 ] = 2.4, V [ 2 ] [ 1 ] = 5.6, V [ 2 ] [ 2 ] = 7.7;
	X [ 0 ] [ 0 ] = 1.2, X [ 0 ] [ 1 ] = 2.3;
	X [ 1 ] [ 0 ] = 4.3, X [ 1 ] [ 1 ] = 3.2;
	W = V;
	W *= 2;
	std::clog << "V = ..." << std::endl << V << std::endl;
	std::clog << "W = ..." << std::endl << W << std::endl;
	matrix_t sum( V + W );
	std::clog << "V + W = ..." << std::endl << sum << std::endl;
	matrix_t sumRes( {
		{  3.6000,  6.9000, 10.2000 },
		{ 12.9000,  9.6000,  6.3000 },
		{  7.2000, 16.8000, 23.1000 }
	} );
	eq( "sum", sum, sumRes );
	std::clog << "X = ..." << std::endl << X << std::endl;
	matrix_t inv( X.inverse() );
	std::clog << "X ^ - 1 = ..." << std::endl << inv << std::endl;
	matrix_t invRes( {
		{ -0.528926,  0.380165 },
		{  0.710744, -0.198347 }
	} );
	eq( "inv sum", inv, invRes );
	matrix_t id( X * inv );
	std::clog << "X * X ^ - 1 = ..." << std::endl << id << std::endl;
	matrix_t idRes( {
		{ 1, 0 },
		{ 0, 1 }
	} );
	eq( "inv( sum ) mul", id, idRes );
	matrix_t invV( V.inverse() );
	std::clog << "V ^ - 1 = ..." << std::endl << invV << std::endl;
	matrix_t invVRes( {
		{  1.93538693,  0.199849737, -0.909090909 },
		{ -4.21788129,  0.162283997,  1.818181818 },
		{  2.46431255, -0.180315552, -0.909090909 }
	} );
	eq( "inverse 3", invV, invVRes );
	matrix_t idV( V * invV );
	std::clog << "V * V ^ - 1 = ..." << std::endl << idV << std::endl;
	matrix_t idVRes( {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	} );
	eq( "inverse 3 mul", idV, idVRes );
TUT_TEARDOWN()

}


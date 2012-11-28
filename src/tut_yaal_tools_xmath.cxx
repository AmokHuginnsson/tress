/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_tools_xmath.cxx - this file is integral part of `tress' project.

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

#include <yaal/tools/xmath.hxx>
M_VCSID( "$Id: "__ID__" $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::xmath;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_xmath );
TUT_TEST_GROUP( tut_yaal_tools_xmath, "yaal::tools::xmath" );

TUT_UNIT_TEST( 1, "clip" )
	ENSURE_EQUALS( "in range clip failed", clip( 1, 2, 3 ), 2 );
	ENSURE_EQUALS( "below range clip failed", clip( 2, 1, 3 ), 2 );
	ENSURE_EQUALS( "above range clip failed", clip( 1, 3, 2 ), 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 2, "factorial" )
	ENSURE_EQUALS( "factorial(1) failed", factorial( 1 ), 1 );
	ENSURE_EQUALS( "factorial(2) failed", factorial( 2 ), 2 );
	ENSURE_EQUALS( "factorial(3) failed", factorial( 3 ), 6 );
	ENSURE_EQUALS( "factorial(4) failed", factorial( 4 ), 24 );
	ENSURE_EQUALS( "factorial(5) failed", factorial( 5 ), 120 );
	ENSURE_EQUALS( "factorial(6) failed", factorial( 6 ), 720 );
	ENSURE_EQUALS( "factorial(7) failed", factorial( 7 ), 5040 );
	ENSURE_EQUALS( "factorial(8) failed", factorial( 8 ), 40320 );
	ENSURE_EQUALS( "factorial(9) failed", factorial( 9 ), 362880 );
	ENSURE_EQUALS( "factorial(10) failed", factorial( 10 ), 3628800 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 3, "binomial_coefficient" )
	ENSURE_EQUALS( "binomial_coefficient( 7, 2 )", binomial_coefficient( 7, 2 ), 21 );
	ENSURE_EQUALS( "binomial_coefficient( 1, 0 )", binomial_coefficient( 1, 0 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 1, 1 )", binomial_coefficient( 1, 1 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 2, 0 )", binomial_coefficient( 2, 0 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 2, 1 )", binomial_coefficient( 2, 1 ), 2 );
	ENSURE_EQUALS( "binomial_coefficient( 2, 2 )", binomial_coefficient( 2, 2 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 3, 0 )", binomial_coefficient( 3, 0 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 3, 1 )", binomial_coefficient( 3, 1 ), 3 );
	ENSURE_EQUALS( "binomial_coefficient( 3, 2 )", binomial_coefficient( 3, 2 ), 3 );
	ENSURE_EQUALS( "binomial_coefficient( 3, 3 )", binomial_coefficient( 3, 3 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 4, 0 )", binomial_coefficient( 4, 0 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 4, 1 )", binomial_coefficient( 4, 1 ), 4 );
	ENSURE_EQUALS( "binomial_coefficient( 4, 2 )", binomial_coefficient( 4, 2 ), 6 );
	ENSURE_EQUALS( "binomial_coefficient( 4, 3 )", binomial_coefficient( 4, 3 ), 4 );
	ENSURE_EQUALS( "binomial_coefficient( 4, 4 )", binomial_coefficient( 4, 4 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 5, 0 )", binomial_coefficient( 5, 0 ), 1 );
	ENSURE_EQUALS( "binomial_coefficient( 5, 1 )", binomial_coefficient( 5, 1 ), 5 );
	ENSURE_EQUALS( "binomial_coefficient( 5, 2 )", binomial_coefficient( 5, 2 ), 10 );
	ENSURE_EQUALS( "binomial_coefficient( 5, 3 )", binomial_coefficient( 5, 3 ), 10 );
	ENSURE_EQUALS( "binomial_coefficient( 5, 4 )", binomial_coefficient( 5, 4 ), 5 );
	ENSURE_EQUALS( "binomial_coefficient( 5, 5 )", binomial_coefficient( 5, 5 ), 1 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 4, "number set stats: minimum" )
	ENSURE_EQUALS( "number_set_stats().minimum() failed", number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).minimum(), _testData_[0][0] );
TUT_TEARDOWN()

TUT_UNIT_TEST( 5, "number set stats: maximum" )
	ENSURE_EQUALS( "number_set_stats().maximum() failed", number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).maximum(), _testData_[0][countof ( _testData_[0] ) - 1] );
TUT_TEARDOWN()

TUT_UNIT_TEST( 6, "number set stats: count" )
	ENSURE_EQUALS( "number_set_stats().count() failed", number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).count(), 100 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 7, "number set stats: sum" )
	ENSURE_EQUALS( "number_set_stats().sum() failed", number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).sum(), 24133 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 8, "number set stats: average" )
#ifdef __HOST_OS_TYPE_CYGWIN__
	double expected( 24133 / 100. );
#else /* #ifdef __HOST_OS_TYPE_CYGWIN__ */
	double long expected( 24133 / 100.l );
#endif /* #else #ifdef __HOST_OS_TYPE_CYGWIN__ */
	ENSURE_EQUALS( "number_set_stats().average() failed", number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).average(), expected );
TUT_TEARDOWN()

TUT_UNIT_TEST( 9, "number set stats: variance" )
	ENSURE_DISTANCE( "number_set_stats().variance() failed",
			number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).variance(), 25865.7586868687L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 10, "number set stats: standard_deviation" )
	ENSURE_DISTANCE( "number_set_stats().standard_deviation() failed",
			number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).standard_deviation(), 160.828351626412L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 11, "number set stats: population_variance" )
	ENSURE_DISTANCE( "number_set_stats().population_variance() failed",
			number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).population_variance(), 25607.1011L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 12, "number set stats: population_standard_deviation" )
	ENSURE_DISTANCE( "number_set_stats().population_standard_deviation() failed",
			number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) ).population_standard_deviation(), 160.022189398846L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( 13, "number set stats: median" )
	ENSURE_EQUALS( "number_set_stats().median() failed",
			number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ), static_cast<AGGREGATE_TYPE::type_t>( AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEDIAN ) ).median(), 229 );
	ENSURE_EQUALS( "number_set_stats().median() failed",
			number_set_stats( _testData_[0], _testData_[0] + countof ( _testData_[0] ) - 1, static_cast<AGGREGATE_TYPE::type_t>( AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEDIAN ) ).median(), 229 );
TUT_TEARDOWN()

TUT_UNIT_TEST( 20, "stats on dice" )
	double long dice[] = { 1, 2, 3, 4, 5, 6 };
	HNumberSetStats<double long> diceStats( dice, dice + countof ( dice ), static_cast<AGGREGATE_TYPE::type_t>( AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEDIAN ) );
	clog << "dice stats: " << endl
		<< "minimum                       = " << diceStats.minimum() << endl
		<< "maximum                       = " << diceStats.maximum() << endl
		<< "sum                           = " << diceStats.sum() << endl
		<< "count                         = " << diceStats.count() << endl
		<< "average                       = " << diceStats.average() << endl
		<< "variance                      = " << diceStats.variance() << endl
		<< "standard deviation            = " << diceStats.standard_deviation() << endl
		<< "population variance           = " << diceStats.population_variance() << endl
		<< "population standard deviation = " << diceStats.population_standard_deviation() << endl
		<< "median                        = " << diceStats.median() << endl;
TUT_TEARDOWN()

template<typename T>
T average_on_range( HArray<T> const& src_, int long pos_, int long range_ ) {
	T val = T();
	int long preRange( ( range_ - 1 ) / 2 );
	int long size( src_.get_size() );
	int long valuesInRange( 0 );
	for ( int long i( 0 ); i < range_; ++ i ) {
		int long idx( pos_ + i - preRange );
		if ( ( idx >= 0 ) && ( idx < size ) ) {
			val += src_[idx];
			++ valuesInRange;
		}
	}
	return ( val / static_cast<T>( valuesInRange ) );
}

TUT_UNIT_TEST( 21, "central_moving_average" )
	/* first lest prepare periodic triangle signal series */
	int const dataCount( 1024 );
	typedef HArray<double> data_t;
	data_t data( dataCount );
	int const triangleCount( 8 );
	int long testRanges[] = { 33, 65, 97 };
	int idx( 0 );
	for ( int i( 0 ); i < triangleCount; ++ i ) {
		int const triangleWidth( dataCount / triangleCount );
		for ( int j( 0 ); j < ( triangleWidth / 2 ); ++ j )
			data[idx ++] = j;
		for ( int j( 0 ); j < ( triangleWidth / 2 ); ++ j )
			data[idx ++] = ( triangleWidth  / 2 ) - j;
	}
	data_t cma( dataCount );
	data_t expect( dataCount );
	for ( int t( 0 ); t < countof ( testRanges ); ++ t ) {
		central_moving_average( data.begin(), data.end(), cma.begin(), testRanges[t] );
		for ( int i( 0 ); i < dataCount; ++ i )
			expect[i] = average_on_range( data, i, testRanges[t] );
		for ( int i( 0 ); i < dataCount; ++ i )
			ENSURE_DISTANCE( "calculating central moving average failed", cma[i], expect[i], static_cast<double>( epsilon * dataCount ) );
	}
	try {
		central_moving_average( data.begin(), data.end(), cma.begin(), -1 );
		FAIL( "calculating CMA with negative range succeeded" );
	} catch ( HException const& ) {
		/* ok */
	}
	try {
		central_moving_average( data.begin(), data.end(), cma.begin(), 0 );
		FAIL( "calculating CMA with empty range succeeded" );
	} catch ( HException const& ) {
		/* ok */
	}
	try {
		central_moving_average( data.begin(), data.end(), cma.begin(), 8 );
		FAIL( "calculating CMA with even range succeeded" );
	} catch ( HException const& ) {
		/* ok */
	}
TUT_TEARDOWN()

}


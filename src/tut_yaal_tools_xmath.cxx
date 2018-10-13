/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/tools/xmath.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include <yaal/hcore/hnumber.hxx>

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::tools::xmath;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_tools_xmath );
TUT_TEST_GROUP( tut_yaal_tools_xmath, "yaal::tools::xmath" );

TUT_UNIT_TEST( "clip" )
	ENSURE_EQUALS( "in range clip failed", clip( 1, 2, 3 ), 2 );
	ENSURE_EQUALS( "below range clip failed", clip( 2, 1, 3 ), 2 );
	ENSURE_EQUALS( "above range clip failed", clip( 1, 3, 2 ), 2 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "factorial" )
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

TUT_UNIT_TEST( "binomial_coefficient" )
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

TUT_UNIT_TEST( "number set stats: minimum" )
	ENSURE_EQUALS( "number_set_stats().minimum() failed", number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).minimum(), _testData_[0][0] );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: maximum" )
	ENSURE_EQUALS( "number_set_stats().maximum() failed", number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).maximum(), _testData_[0][yaal::size( _testData_[0] ) - 1] );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: count" )
	ENSURE_EQUALS( "number_set_stats().count() failed", number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).count(), 100 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: sum" )
	ENSURE_EQUALS( "number_set_stats().sum() failed", number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).sum(), 24133 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: arithmetic_mean" )
#ifdef __HOST_OS_TYPE_CYGWIN__
	double long e( epsilon * 100 );
#else /* #ifdef __HOST_OS_TYPE_CYGWIN__ */
	double long e( epsilon );
#endif /* #else #ifdef __HOST_OS_TYPE_CYGWIN__ */
	double long expected( 24133 / 100.l );
	ENSURE_DISTANCE( "number_set_stats().arithmetic_mean() failed",
			number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).arithmetic_mean(),
			expected,
			e );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: sample_variance" )
	ENSURE_DISTANCE( "number_set_stats().sample_variance() failed",
			number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).sample_variance(), 25865.7586868687L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: sample_standard_deviation" )
	ENSURE_DISTANCE( "number_set_stats().sample_standard_deviation() failed",
			number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).sample_standard_deviation(), 160.828351626412L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: population_variance" )
	ENSURE_DISTANCE( "number_set_stats().population_variance() failed",
			number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).population_variance(), 25607.1011L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: population_standard_deviation" )
	ENSURE_DISTANCE( "number_set_stats().population_standard_deviation() failed",
			number_set_stats( begin( _testData_[0] ), end( _testData_[0] ) ).population_standard_deviation(), 160.022189398846L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "number set stats: median" )
	int_array_t even( begin( _testData_[0] ), end( _testData_[0] ) );
	int_array_t odd( begin( _testData_[0] ), end( _testData_[0] ) - 1 );
	for ( int i( 0 ); i < 100; ++ i ) {
		yaal::random_shuffle( even.begin(), even.end() );
		yaal::random_shuffle( odd.begin(), odd.end() );
		ENSURE_EQUALS( "number_set_stats().median() failed",
				number_set_stats( even.begin(), even.end(), AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEDIAN ).median(), 231 );
		ENSURE_EQUALS( "number_set_stats().median() failed",
				number_set_stats( odd.begin(), odd.end(), AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEDIAN ).median(), 229 );
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "mean_absolute_deviation" )
	ENSURE_DISTANCE( "number_set_stats().mean_absolute_deviation() failed",
			number_set_stats( begin( _testData_[0] ), end( _testData_[0] ), AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEAN_ABSOLUTE_DEVIATION ).mean_absolute_deviation(), 139.2098L, epsilon );
TUT_TEARDOWN()

TUT_UNIT_TEST( "stats on dice" )
	double long dice[] = { 1, 2, 3, 4, 5, 6 };
	HNumberSetStats<double long> diceStats( dice, dice + yaal::size( dice ), AGGREGATE_TYPE::BASIC | AGGREGATE_TYPE::MEDIAN );
	clog << "dice stats: " << endl
		<< "minimum                       = " << diceStats.minimum() << endl
		<< "maximum                       = " << diceStats.maximum() << endl
		<< "sum                           = " << diceStats.sum() << endl
		<< "count                         = " << diceStats.count() << endl
		<< "arithmetic_mean               = " << diceStats.arithmetic_mean() << endl
		<< "sample_variance               = " << diceStats.sample_variance() << endl
		<< "standard deviation            = " << diceStats.sample_standard_deviation() << endl
		<< "population sample_variance    = " << diceStats.population_variance() << endl
		<< "population standard deviation = " << diceStats.population_standard_deviation() << endl
		<< "median                        = " << diceStats.median() << endl;
TUT_TEARDOWN()

template<typename T>
T central_average_on_range( HArray<T> const& src_, int long pos_, int long range_ ) {
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

TUT_UNIT_TEST( "central_moving_average" )
	/* first lest prepare periodic triangle signal series */
	int const dataCount( 1024 );
	typedef HArray<double> data_t;
	data_t data( dataCount );
	int const triangleCount( 8 );
	int long testRanges[] = { 33, 65, 97, 163 };
	int idx( 0 );
	for ( int i( 0 ); i < triangleCount; ++ i ) {
		int const triangleWidth( dataCount / triangleCount );
		for ( int j( 0 ); j < ( triangleWidth / 2 ); ++ j )
			data[idx ++] = j;
		for ( int j( 0 ); j < ( triangleWidth / 2 ); ++ j )
			data[idx ++] = ( triangleWidth  / 2 ) - j;
	}
	data_t expect( dataCount );
	data_t cma[yaal::size( testRanges )];
	HFile o;
	if ( tress::setup._debug )
		o.open( "./out/data.txt", HFile::OPEN::WRITING );
	for ( int t( 0 ); t < yaal::size( testRanges ); ++ t ) {
		cma[t].resize( dataCount );
		central_moving_average( data.begin(), data.end(), cma[t].begin(), testRanges[t] );
		for ( int i( 0 ); i < dataCount; ++ i )
			expect[i] = central_average_on_range( data, i, testRanges[t] );
		for ( int i( 0 ); i < dataCount; ++ i )
			ENSURE_DISTANCE( "calculating central moving average failed", cma[t][i], expect[i], static_cast<double>( epsilon * dataCount ) );
	}
	if ( tress::setup._debug ) {
		for ( int i( 0 ); i < dataCount; ++ i ) {
			o << data[i];
			for ( int t( 0 ); t < yaal::size( testRanges ); ++ t )
				o << " " << cma[t][i];
			o << endl;
		}
	}
	ENSURE_THROW( "calculating CMA with negative range succeeded", central_moving_average( data.begin(), data.end(), cma[0].begin(), -1 ), HException );
	ENSURE_THROW( "calculating CMA with empty range succeeded", central_moving_average( data.begin(), data.end(), cma[0].begin(), 0 ), HException );
	ENSURE_THROW( "calculating CMA with even range succeeded", central_moving_average( data.begin(), data.end(), cma[0].begin(), 8 ), HException );
TUT_TEARDOWN()

template<typename T>
T average_on_range( HArray<T> const& src_, int long pos_, int long range_ ) {
	T val = T();
	int long valuesInRange( 0 );
	for ( int long i( 0 ); i < range_; ++ i ) {
		int long idx( pos_ - i );
		if ( idx >= 0 ) {
			val += src_[idx];
			++ valuesInRange;
		}
	}
	return ( val / static_cast<T>( valuesInRange ) );
}

TUT_UNIT_TEST( "moving_average" )
	/* first lest prepare periodic triangle signal series */
	int const dataCount( 1024 );
	typedef HArray<double> data_t;
	data_t data( dataCount );
	int const triangleCount( 8 );
	int long testRanges[] = { 16, 33, 65, 97, 160 };
	int idx( 0 );
	for ( int i( 0 ); i < triangleCount; ++ i ) {
		int const triangleWidth( dataCount / triangleCount );
		for ( int j( 0 ); j < ( triangleWidth / 2 ); ++ j )
			data[idx ++] = j;
		for ( int j( 0 ); j < ( triangleWidth / 2 ); ++ j )
			data[idx ++] = ( triangleWidth  / 2 ) - j;
	}
	data_t expect( dataCount );
	data_t ma[yaal::size( testRanges )];
	HFile o;
	if ( tress::setup._debug )
		o.open( "./out/data.txt", HFile::OPEN::WRITING );
	for ( int t( 0 ); t < yaal::size( testRanges ); ++ t ) {
		ma[t].resize( dataCount );
		moving_average( data.begin(), data.end(), ma[t].begin(), testRanges[t] );
		for ( int i( 0 ); i < dataCount; ++ i )
			expect[i] = average_on_range( data, i, testRanges[t] );
		for ( int i( 0 ); i < dataCount; ++ i )
			ENSURE_DISTANCE( "calculating moving average failed", ma[t][i], expect[i], static_cast<double>( epsilon * dataCount ) );
	}
	if ( tress::setup._debug ) {
		for ( int i( 0 ); i < dataCount; ++ i ) {
			o << data[i];
			for ( int t( 0 ); t < yaal::size( testRanges ); ++ t )
				o << " " << ma[t][i];
			o << endl;
		}
	}
TUT_TEARDOWN()

TUT_UNIT_TEST( "historgram" )
	int_array_t data( begin( _testData_[0] ), end( _testData_[0] ) );
	HNumberSetStats<double long> ns10( number_set_stats( data.begin(), data.end(), AGGREGATE_TYPE::HISTOGRAM, 10 ) );
	int_array_t exp10( { 16, 13, 9, 9, 11, 8, 9, 9, 9, 7 } );
	ENSURE_EQUALS( "historgram (10 buckets) failed", ns10.histogram(), exp10 );
	ENSURE_EQUALS( "histogram(10) sum is invalid", yaal::accumulate( ns10.histogram().begin(), ns10.histogram().end(), 0 ), 100 );

	HNumberSetStats<double long> ns7( number_set_stats( data.begin(), data.end(), AGGREGATE_TYPE::HISTOGRAM, 7 ) );
	int_array_t exp7( { 21, 15, 14, 13, 13, 14, 10 } );
	ENSURE_EQUALS( "historgram (7 buckets) failed", ns7.histogram(), exp7 );
	ENSURE_EQUALS( "histogram(7) sum is invalid", yaal::accumulate( ns7.histogram().begin(), ns7.histogram().end(), 0 ), 100 );

	HNumberSetStats<double long> ns13( number_set_stats( data.begin(), data.end(), AGGREGATE_TYPE::HISTOGRAM, 13 ) );
	int_array_t exp13( { 14, 9, 7, 9, 7, 7, 8, 6, 7, 6, 8, 7, 5 } );
	ENSURE_EQUALS( "historgram (13 buckets) failed", ns13.histogram(), exp13 );
	ENSURE_EQUALS( "histogram(13) sum is invalid", yaal::accumulate( ns13.histogram().begin(), ns13.histogram().end(), 0 ), 100 );
TUT_TEARDOWN()

TUT_UNIT_TEST( "big factorial" )
	ENSURE_EQUALS( "factorial(10) failed", factorial( HNumber( 100 ) ), "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000" );
TUT_TEARDOWN()

}


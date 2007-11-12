#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>
#include <ctime>
#include <tseries.hpp>

using namespace boost::unit_test_framework;

// seed random number generator
// srand((unsigned)time(0));

void null_constructor_test() {
  TSeries<double,double> x;

  // so we have the same type
  TSDIM zero = 0;
  BOOST_CHECK_EQUAL( x.nrow(), zero );
  BOOST_CHECK_EQUAL( x.ncol(), zero );
  BOOST_CHECK_EQUAL( x.getData(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getDates(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getColnames().size(), zero );
}

void std_constructor_test() {
  TSDIM nr = 1000;
  TSDIM nc = 10;
  TSDIM zero = 0;

  TSeries<double,double> x(nr,nc);

  BOOST_CHECK_EQUAL( x.nrow(), nr );
  BOOST_CHECK_EQUAL( x.ncol(), nc );
  BOOST_CHECK( x.getData() != static_cast<double*>(NULL) );
  BOOST_CHECK( x.getDates() != static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getColnames().size(), zero );
}

void set_colnames_test() {
  TSeries<double,double> x;

  vector<string> newColnames;

  newColnames.push_back("hat");
  newColnames.push_back("cat");

  // not allowed to set colnames not equal to number of cols
  BOOST_CHECK_EQUAL(x.setColnames(newColnames) , 1 );

  TSeries<double,double> y(100,2);

  // test set colnames success
  BOOST_CHECK_EQUAL(y.setColnames(newColnames) , 0 );

  // test that getColnames returns the correct value
  BOOST_CHECK_EQUAL(y.getColnames()==newColnames, 1);
}

void operators_test() {
  TSDIM nr = 100;
  TSDIM nc = 10;

  TSeries<double,double> x(nr,nc);
  TSeries<double,double> y(nr,nc);

  TSeries<double,double> z = x + y;

  BOOST_CHECK_EQUAL( z.nrow(), 0 );
  BOOST_CHECK_EQUAL( z.ncol(), 0 );
}


test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
  test_suite* test= BOOST_TEST_SUITE("tslib test");

  test->add( BOOST_TEST_CASE( &null_constructor_test ) );
  test->add( BOOST_TEST_CASE( &std_constructor_test ) );
  test->add( BOOST_TEST_CASE( &set_colnames_test ) );
  
  test->add( BOOST_TEST_CASE( &operators_test ) );
  return test;
}

  

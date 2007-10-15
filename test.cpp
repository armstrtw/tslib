#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>
#include <ctime>
#include "tseries.hpp"

using namespace boost::unit_test_framework;

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

test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
  test_suite* test= BOOST_TEST_SUITE("tslib test");

  test->add( BOOST_TEST_CASE( &null_constructor_test ) );
  test->add( BOOST_TEST_CASE( &set_colnames_test ) );
  return test;
}

  

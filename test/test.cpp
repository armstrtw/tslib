#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>
#include <ctime>
#include <tseries.hpp>
#include <vector/window.apply.hpp>
#include <vector/mean.hpp>

using namespace boost::unit_test_framework;
using std::cout;
using std::endl;

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

void range_specifier_test() {

  vector<int> x;
  vector<int> y;

  x.push_back(1);
  x.push_back(2);
  x.push_back(3);
  x.push_back(4);
  x.push_back(5);

  y.push_back(1);
  y.push_back(3);
  y.push_back(5);

  RangeSpecifier<int,size_t> r(&x[0],&y[0],x.size(),y.size());

  BOOST_CHECK(r.getSize() == 3);
  BOOST_CHECK(r.getArg1()[0] == 0);
  BOOST_CHECK(r.getArg1()[1] == 2);
  BOOST_CHECK(r.getArg1()[2] == 4);
  
  BOOST_CHECK(r.getArg2()[0] == 0);
  BOOST_CHECK(r.getArg2()[1] == 1);
  BOOST_CHECK(r.getArg2()[2] == 2);
  
  r.print();
}

void operators_test() {
  TSDIM xnr = 100;
  TSDIM ynr = 10;
  TSDIM nc = 10;

  TSeries<double,double> x(xnr,nc);
  TSeries<double,double> y(ynr,nc);

  // gernate data
  fill_n(x.getData(),x.nrow()*x.ncol(),100.0);
  fill_n(y.getData(),y.nrow()*y.ncol(),5.0);

  // generate dates
  for(TSDIM xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi;

  // generate dates
  for(TSDIM yi = 0; yi < y.nrow(); yi++)
    y.getDates()[yi] = yi;
    
  TSeries<double,double> Zplus = x + y;
  TSeries<double,double> Zminus = x - y;
  TSeries<double,double> Zmultiplies = x * y;
  TSeries<double,double> Zdivides = x / y;

  BOOST_CHECK_EQUAL( Zplus.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zplus.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zminus.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zminus.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zmultiplies.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zmultiplies.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zdivides.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zdivides.ncol(), 10 );

  cout << Zmultiplies << endl;

  // add test for all== later
  TSeries<double,double> XplusS = x + 100.0;
  TSeries<double,double> SplusX = 100.0 + x;

  TSeries<double,double> XminusS = x - 100.0;
  TSeries<double,double> SminusX = 100.0 - x;

  TSeries<double,double> XmultS = x * 100.0;
  TSeries<double,double> SmultX = 100.0 * x;

  TSeries<double,double> XdivS = x / 100.0;
  TSeries<double,double> SdivX = 100.0 * x;
}

void assignment_test() {
  TSDIM xnr = 10;
  TSDIM xnc = 2;

  TSDIM ynr = 100;
  TSDIM ync = 50;

  TSeries<double,double> x(xnr,xnc);
  TSeries<double,double> y(ynr,ync);

  fill_n(x.getData(),x.nrow()*x.ncol(),1.0);
  fill_n(y.getData(),y.nrow()*y.ncol(),2.0);

  // test self assignment
  x = x;

  BOOST_CHECK_EQUAL(x.nrow(),xnr);
  BOOST_CHECK_EQUAL(x.ncol(),xnc);
  BOOST_CHECK_EQUAL(x.getData()[0],1.0);


  // TS TS assignment
  BOOST_CHECK_EQUAL(y.getData()[0],2.0);
  y = x;
  
  BOOST_CHECK_EQUAL(y.nrow(),xnr);
  BOOST_CHECK_EQUAL(y.ncol(),xnc);
  BOOST_CHECK_EQUAL(y.getData()[0],1.0);

  x = 100.0;

  // check that dims are same as before
  BOOST_CHECK_EQUAL(x.nrow(),xnr);
  BOOST_CHECK_EQUAL(x.ncol(),xnc);

  // now all values of x shoud be == 100.0
  for(TSDIM i = 0; i < x.nrow()*x.ncol(); i++) {
    BOOST_CHECK_EQUAL(x.getData()[i],100);
  }
}


void vector_window_apply_test() {
  
  // define our answer type
  typedef meanTraits<double>::ReturnType ansType;

  // gernate data
  int N = 100;
  double* x = new double[N];
  ansType* ans = new ansType[N];
  // gernate data
  for(TSDIM vi = 0; vi < N; vi++)
    x[vi] = vi+1;

  windowApply<ansType,Mean>::apply(ans,x,x+N,20);

  BOOST_CHECK_EQUAL(ans[19],10.5);
}

void window_apply_test() {
  // define our answer type
  typedef meanTraits<double>::ReturnType ansType;

  TSDIM xnr = 50;
  TSDIM xnc = 5;

  TSeries<double,double> x(xnr,xnc);


  // gernate data
  for(TSDIM vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;
  
  // generate dates
  for(TSDIM xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  TSeries<double,ansType> ans = x.window<Mean>(5);
  BOOST_CHECK_EQUAL(ans.getData()[4],3);
}


test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
  
  test_suite* test= BOOST_TEST_SUITE("tslib test");
  test->add( BOOST_TEST_CASE( &null_constructor_test ) );
  test->add( BOOST_TEST_CASE( &std_constructor_test ) );
  test->add( BOOST_TEST_CASE( &set_colnames_test ) );  
  test->add( BOOST_TEST_CASE( &range_specifier_test ) );
  test->add( BOOST_TEST_CASE( &operators_test ) );
  test->add( BOOST_TEST_CASE( &assignment_test ) );
  test->add( BOOST_TEST_CASE( &vector_window_apply_test ) );
  test->add( BOOST_TEST_CASE( &window_apply_test ) );
  return test;
}

  

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>
#include <ctime>

#include <tseries.hpp>
#include <vector.summary.hpp>

using namespace tslib;
using namespace boost::unit_test_framework;
using std::cout;
using std::endl;
using std::fill_n;

// seed random number generator
// srand((unsigned)time(0));

void null_constructor_test() {
  TSeries<double,double> x;

  // so we have the same type
  long zero = 0;
  BOOST_CHECK_EQUAL( x.nrow(), zero );
  BOOST_CHECK_EQUAL( x.ncol(), zero );
  BOOST_CHECK_EQUAL( x.getData(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getDates(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getColnames().size(), zero );
}

void std_constructor_test() {
  long nr = 1000;
  long nc = 10;
  long zero = 0;

  TSeries<double,double> x(nr,nc);

  BOOST_CHECK_EQUAL( x.nrow(), nr );
  BOOST_CHECK_EQUAL( x.ncol(), nc );
  BOOST_CHECK( x.getData() != static_cast<double*>(NULL) );
  BOOST_CHECK( x.getDates() != static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getColnames().size(), zero );
}

void tsdata_constructor_test() {
  long nr = 1000;
  long nc = 10;
  long zero = 0;

  TSdataSingleThreaded<double,double>* ts_data = TSdataSingleThreaded<double,double>::init(nr,nc);
  TSeries<double,double> x(ts_data);

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
  long xnr = 100;
  long ynr = 10;
  long nc = 10;

  TSeries<double,double> x(xnr,nc);
  TSeries<double,double> y(ynr,nc);

  // gernate data
  fill_n(x.getData(),x.nrow()*x.ncol(),100.0);
  fill_n(y.getData(),y.nrow()*y.ncol(),5.0);

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi;

  // generate dates
  for(long yi = 0; yi < y.nrow(); yi++)
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
  long xnr = 10;
  long xnc = 2;

  long ynr = 100;
  long ync = 50;

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
  for(long i = 0; i < x.nrow()*x.ncol(); i++) {
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
  for(long vi = 0; vi < N; vi++)
    x[vi] = vi+1;

  windowApply<ansType,Mean>::apply(ans,x,x+N,20);

  BOOST_CHECK_EQUAL(ans[19],10.5);
}

void window_apply_test() {
  // define our answer type
  typedef meanTraits<double>::ReturnType mean_ansType;
  typedef sumTraits<double>::ReturnType sum_ansType;
  typedef rankTraits<double>::ReturnType rank_ansType;

  long xnr = 50;
  long xnc = 5;

  TSeries<double,double> x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  TSeries<double,mean_ansType> mean_ans = x.window<mean_ansType,Mean>(5);
  BOOST_CHECK_EQUAL(mean_ans.getData()[4],3);

  TSeries<double,sum_ansType> sum_ans = x.window<sum_ansType,Sum>(5);
  BOOST_CHECK_EQUAL(sum_ans.getData()[4],(5.0*6.0)/2.0);

  TSeries<double,rank_ansType> rank_ans = x.window<rank_ansType,Rank>(5);
  BOOST_CHECK_EQUAL(rank_ans.getData()[4],5);

  cout << rank_ans << endl;
}


void lag_lead_test() {

  long xnr = 50;
  long xnc = 5;

  TSeries<double,double> x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  //TSeries<double,double> ans = x(1);
  //TSeries<double,double> ans = x(-1);
  cout << x(-2) << endl;
}


void posix_date_test() {
  const char* jan_01_2007 = "01/01/2007";
  const char* fmt_america = "%m/%d/%Y";

  long dt = PosixDate<long>::toDate(jan_01_2007,fmt_america);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(dt,fmt_america).c_str(),"01/01/2007"),0);

  // shifting
  long d1_shft_1d = PosixDate<long>::AddDays(dt,1);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(d1_shft_1d,fmt_america).c_str(),"01/02/2007"),0);

  long d1_shft_1m = PosixDate<long>::AddMonths(dt,1);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(d1_shft_1m,fmt_america).c_str(),"02/01/2007"),0);

  long d1_shft_1yr = PosixDate<long>::AddYears(dt,1);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(d1_shft_1yr,fmt_america).c_str(),"01/01/2008"),0);

  long d1_shft_24m = PosixDate<long>::AddMonths(dt,24);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(d1_shft_24m,fmt_america).c_str(),"01/01/2009"),0);

  long d1_shft_neg24m = PosixDate<long>::AddMonths(dt,-24);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(d1_shft_neg24m,fmt_america).c_str(),"01/01/2005"),0);

  long d1_shft_neg18m = PosixDate<long>::AddMonths(dt,-18);
  BOOST_CHECK_EQUAL(strcmp(PosixDate<long>::toString(d1_shft_neg18m,fmt_america).c_str(),"07/01/2005"),0);

}

test_suite*
init_unit_test_suite( int argc, char* argv[] ) {

  test_suite* test= BOOST_TEST_SUITE("tslib test");

  test->add( BOOST_TEST_CASE( &null_constructor_test ) );
  test->add( BOOST_TEST_CASE( &std_constructor_test ) );
  test->add( BOOST_TEST_CASE( &tsdata_constructor_test) );
  test->add( BOOST_TEST_CASE( &set_colnames_test ) );
  test->add( BOOST_TEST_CASE( &range_specifier_test ) );
  test->add( BOOST_TEST_CASE( &operators_test ) );
  test->add( BOOST_TEST_CASE( &assignment_test ) );
  test->add( BOOST_TEST_CASE( &vector_window_apply_test ) );
  test->add( BOOST_TEST_CASE( &window_apply_test ) );
  test->add( BOOST_TEST_CASE( &lag_lead_test ) );
  test->add( BOOST_TEST_CASE( &posix_date_test ) );
  return test;
}

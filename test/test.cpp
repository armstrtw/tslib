///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008  Whit Armstrong                                    //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, either version 3 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details.                          //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>
#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>

#include <tslib/tseries.hpp>
#include <tslib/ts.opps/ts.opps.hpp>
#include <tslib/utils/window.function.hpp>
#include <tslib/utils/cbind.hpp>
#include <tslib/vector.summary.hpp>
#include <tslib/vector.transform.hpp>

using namespace tslib;
using namespace boost::unit_test_framework;
using std::cout;
using std::endl;
using std::fill_n;
using std::ostream_iterator;
using std::vector;

//LDL = long, double, long
//DDL = double, double, long
typedef TSeries<long,double,long,TSdataSingleThreaded,PosixDate> LDL_ts;
typedef TSeries<long,int,long,TSdataSingleThreaded,PosixDate> LIL_ts;
typedef TSeries<double,double,long,TSdataSingleThreaded,PosixDate> DDL_ts;

// seed random number generator
//srand (time(NULL));



void null_constructor_test() {
  LDL_ts x;

  // so we have the same type
  long zero = 0;
  BOOST_CHECK_EQUAL( x.nrow(), zero );
  BOOST_CHECK_EQUAL( x.ncol(), zero );
  BOOST_CHECK_EQUAL( x.getData(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getDates(), static_cast<long*>(NULL) );
  BOOST_CHECK_EQUAL( static_cast<long>(x.getColnames().size()), zero );
}

void std_constructor_test() {
  long nr = 1000;
  long nc = 10;
  long zero = 0;

  LDL_ts x(nr,nc);

  BOOST_CHECK_EQUAL( x.nrow(), nr );
  BOOST_CHECK_EQUAL( x.ncol(), nc );
  BOOST_CHECK( x.getDates() != static_cast<long*>(NULL) );
  BOOST_CHECK( x.getData() != static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( static_cast<long>(x.getColnames().size()), zero );
}

void tsdata_constructor_test() {
  long nr = 1000;
  long nc = 10;
  long zero = 0;

  TSdataSingleThreaded<double,double>* ts_data = TSdataSingleThreaded<double,double>::init(nr,nc);
  DDL_ts x(ts_data);

  BOOST_CHECK_EQUAL( x.nrow(), nr );
  BOOST_CHECK_EQUAL( x.ncol(), nc );
  BOOST_CHECK( x.getData() != static_cast<double*>(NULL) );
  BOOST_CHECK( x.getDates() != static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( static_cast<long>(x.getColnames().size()), zero );
}

void set_colnames_test() {
  LDL_ts x;

  std::vector<std::string> newColnames;

  newColnames.push_back("hat");
  newColnames.push_back("cat");

  // not allowed to set colnames not equal to number of cols
  BOOST_CHECK_EQUAL(x.setColnames(newColnames) , 1 );

  LDL_ts y(100,2);

  // test set colnames success
  BOOST_CHECK_EQUAL(y.setColnames(newColnames) , 0 );

  // test that getColnames returns the correct value
  BOOST_CHECK_EQUAL(y.getColnames()==newColnames, 1);
}

void range_specifier_test() {

  std::vector<int> x;
  std::vector<int> y;

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

  //r.print();
}

void operators_test() {
  long xnr = 100;
  long ynr = 10;
  long nc = 10;

  LDL_ts x(xnr,nc);
  LDL_ts y(ynr,nc);

  // gernate data
  fill_n(x.getData(),x.nrow()*x.ncol(),100.0);
  fill_n(y.getData(),y.nrow()*y.ncol(),5.0);

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi;

  // generate dates
  for(long yi = 0; yi < y.nrow(); yi++)
    y.getDates()[yi] = yi;

  LDL_ts Zplus = x + y;
  LDL_ts Zminus = x - y;
  LDL_ts Zmultiplies = x * y;
  LDL_ts Zdivides = x / y;

  BOOST_CHECK_EQUAL( Zplus.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zplus.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zminus.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zminus.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zmultiplies.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zmultiplies.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zdivides.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zdivides.ncol(), 10 );

  // add test for all== later
  LDL_ts XplusS = x + 100.0;
  LDL_ts SplusX = 100.0 + x;

  LDL_ts XminusS = x - 100.0;
  LDL_ts SminusX = 100.0 - x;

  LDL_ts XmultS = x * 100.0;
  LDL_ts SmultX = 100.0 * x;

  LDL_ts XdivS = x / 100.0;
  LDL_ts SdivX = 100.0 * x;

  vector<bool> xb_eq_scalar = x == 10;
  vector<bool> xb_neq_ts = x != y;
  vector<bool> xb_gt_ts = x > y;
  vector<bool> xb_gte_ts = x >= y;
  vector<bool> xb_lt_ts = x < y;
  vector<bool> xb_lte_ts = x <= y;
}

void mixed_operators_test() {
  long xnr = 100;
  long ynr = 10;
  long nc = 10;

  LDL_ts x(xnr,nc);
  LIL_ts y(ynr,nc);

  // gernate data
  fill_n(x.getData(),x.nrow()*x.ncol(),100.0);
  fill_n(y.getData(),y.nrow()*y.ncol(),5);

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi;

  // generate dates
  for(long yi = 0; yi < y.nrow(); yi++)
    y.getDates()[yi] = yi;

  LDL_ts Zplus = x + y;
  LDL_ts Zminus = x - y;
  LDL_ts Zmultiplies = x * y;
  LDL_ts Zdivides = x / y;

  BOOST_CHECK_EQUAL( Zplus.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zplus.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zminus.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zminus.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zmultiplies.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zmultiplies.ncol(), 10 );

  BOOST_CHECK_EQUAL( Zdivides.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( Zdivides.ncol(), 10 );

  vector<bool> xb_eq_scalar = x == static_cast<int>(10);
  vector<bool> xb_neq_ts = x != y;
  vector<bool> xb_gt_ts = x > y;
  vector<bool> xb_gte_ts = x >= y;
  vector<bool> xb_lt_ts = x < y;
  vector<bool> xb_lte_ts = x <= y;
}

void assignment_test() {
  long xnr = 10;
  long xnc = 2;

  long ynr = 100;
  long ync = 50;

  LDL_ts x(xnr,xnc);
  LDL_ts y(ynr,ync);

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
  const int N = 100;
  const int window = 20;
  double* x = new double[N];
  ansType* ans = new ansType[N - (window - 1)];

  // gernate data
  for(long vi = 0; vi < N; vi++)
    x[vi] = vi+1;

  windowApply<ansType,Mean>::apply(ans,x,x+N,window);

  BOOST_CHECK_EQUAL(ans[0],10.5);
  delete []x;
  delete []ans;
}

void rsi_test() {

  // define our answer type
  typedef rsiTraits<double>::ReturnType ansType;

  // gernate data
  const int N = 100;
  const int window = 20;
  double* x = new double[N];
  ansType* ans = new ansType[N - (window - 1)];

  // gernate data
  for(long vi = 0; vi < N; vi++)
    x[vi] = vi+1;

  windowApply<ansType,RSI>::apply(ans,x,x+N,window);

  delete []x;
  delete []ans;
}


void window_apply_test() {
  // define our answer type
  typedef meanTraits<double>::ReturnType mean_ansType;
  typedef sumTraits<double>::ReturnType sum_ansType;
  typedef rankTraits<double>::ReturnType rank_ansType;

  long xnr = 50;
  long xnc = 5;

  LDL_ts x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  TSeries<long,mean_ansType,long,TSdataSingleThreaded,PosixDate> mean_ans = x.window<mean_ansType,Mean>(5);
  BOOST_CHECK_EQUAL(mean_ans.getData()[0],3);

  TSeries<long,sum_ansType,long,TSdataSingleThreaded,PosixDate> sum_ans = x.window<sum_ansType,Sum>(5);
  BOOST_CHECK_EQUAL(sum_ans.getData()[0],(5.0*6.0)/2.0);

  TSeries<long,rank_ansType,long,TSdataSingleThreaded,PosixDate> rank_ans = x.window<rank_ansType,Rank>(5);
  BOOST_CHECK_EQUAL(rank_ans.getData()[0],5);
}

void vector_transform_test() {

  // define our answer type
  typedef fillTraits<double>::ReturnType ansType;

  // gernate data
  int N = 10;
  double* x = new double[N];
  ansType* ans = new ansType[N];

  // gernate data
  for(long vi = 0; vi < N; vi++)
    x[vi] = vi+1;

  x[4] = NAN;

  FillBwd<ansType>::apply(ans,x,x+N);

  // 6 because 5 is NA and 6 is next ele
  BOOST_CHECK_EQUAL(ans[4],6);

  /*
  cout << "data" << endl;
  copy(x, x+N,
       ostream_iterator<double>(cout, " "));
  cout << endl;
  cout << "ans" << endl;
  copy(ans, ans+N,
       ostream_iterator<double>(cout, " "));
  cout << endl;
  */
  delete []x;
  delete []ans;
}

void vector_ema_test() {

  // define our answer type
  typedef meanTraits<double>::ReturnType ansType;

  // gernate data
  int N = 28;
  double* x = new double[N];
  ansType* ans = new ansType[N];

  // gernate data
  for(long vi = 0; vi < N; vi++)
    x[vi] = vi+1;

  int periods = 14;
  EMA<ansType>::apply(ans,x,x+N, periods);

  cout << "data" << endl;
  copy(x, x+N,
       ostream_iterator<double>(cout, " "));
  cout << endl;
  cout << "ans" << endl;
  copy(ans, ans+N,
       ostream_iterator<double>(cout, " "));
  cout << endl;

  delete []x;
  delete []ans;
}

void transform_test() {
  // define our answer type
  typedef fillTraits<double>::ReturnType fill_ansType;

  long xnr = 50;
  long xnc = 5;

  LDL_ts x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  x.getData()[21] = NAN;

  TSeries<long,fill_ansType,long,TSdataSingleThreaded,PosixDate> fillbwd_ans = x.transform<fill_ansType,FillBwd>();
  BOOST_CHECK_EQUAL(fillbwd_ans.getData()[21], static_cast<double>(23));
}

void pad_test() {
  long xnr = 10;
  long xnc = 5;

  LDL_ts x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  vector<long> pad_dates;
  pad_dates.push_back(x.nrow() + 10);
  pad_dates.push_back(x.nrow() + 20);
  LDL_ts ans = x.pad(pad_dates.begin(),pad_dates.end());
  cout << "pad test:" << endl;
  cout << x << endl;
  cout << ans << endl;
}


void lag_lead_test() {

  long xnr = 10;
  long xnc = 5;

  LDL_ts x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;
  /*
  cout << "original" << endl;
  cout << x << endl;
  LDL_ts ans_lag = x(1);
  cout << "lag:" << endl;
  cout << ans_lag << endl;
  LDL_ts ans_lead = x(-1);
  cout << "lead:" << endl;
  cout << ans_lead << endl;
  */
}

void diff_test() {

  long xnr = 10;
  long xnc = 5;

  LDL_ts x(xnr,xnc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  LDL_ts y(x.diff(1));
  cout << y << endl;
}

void expanding_max_test() {

  std::vector<double> x;
  std::vector<double> ans;

  x.push_back(numeric_traits<double>::NA());
  x.push_back(1.0);
  x.push_back(2.0);
  x.push_back(3.0);
  x.push_back(1.0);
  x.push_back(1.0);
  x.push_back(1.0);

  //ans.reserve(x.size());
  //ExpandingMaximum<double>::apply(back_insert_iterator<std::vector<double> >(ans),x.begin(),x.end());;
  ExpandingMaximum<double>::apply(back_inserter(ans),x.begin(),x.end());
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

void window_function_test() {
const char* jan_01_2007 = "01/01/2007";
  const char* fmt_america = "%m/%d/%Y";
  std::vector<long> dts;

  long xnr = 365;
  long xnc = 1;

  long ynr = 100;
  long ync = 1;

  LDL_ts x(xnr,xnc);
  LDL_ts y(ynr,ync);

  // gernate data for x
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = rand();

  long dt = PosixDate<long>::toDate(jan_01_2007,fmt_america);

  for(int i = 0; i < xnr; i++)
    x.getDates()[i] = PosixDate<long>::AddDays(dt,i);

  // gernate data for y
  for(long vi = 0; vi < y.nrow()*y.ncol(); vi++)
    y.getData()[vi] = rand();

  for(int i = 0; i < ynr; i++)
    y.getDates()[i] = PosixDate<long>::AddDays(dt,i);

  TSeries<long,corTraits<double>::ReturnType,long,TSdataSingleThreaded,PosixDate> ans =  window_function<corTraits<double>::ReturnType,Cor>(x,x,20);
  TSeries<long,corTraits<double>::ReturnType,long,TSdataSingleThreaded,PosixDate> ans2 =  window_function<corTraits<double>::ReturnType,Cor>(x,y,5);
}

void cbind_test() {
  long xnr = 5;
  long xnc = 1;

  long ynr = 10;
  long ync = 3;

  LDL_ts x(xnr,xnc);
  LDL_ts y(ynr,ync);

  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i; }
  for(int i = 0; i < x.nrow()*x.ncol(); i++) { x.getData()[i] = 1; }
  for(int i = 0; i < y.nrow(); i++) { y.getDates()[i] = i; }
  for(int i = 0; i < y.nrow()*y.ncol(); i++) { y.getData()[i] = i; }
  vector< LDL_ts > seq;
  seq.push_back(x);
  seq.push_back(y);

  /*
  cout << "cbind:" << endl;
  cout << "x" << x << endl;
  cout << "y" << y << endl;

  LDL_ts z_union = cbind(seq,false);
  cout << z_union.nrow() << endl;
  cout << z_union.ncol() << endl;
  cout << "z_union" << endl << z_union << endl;

  LDL_ts z_intersect = cbind(seq,true);
  cout << z_intersect.nrow() << endl;
  cout << z_intersect.ncol() << endl;
  cout << "z_intersect:" << endl << z_intersect << endl;
  */
}

void freq_conv_test_year() {
  long xnr = 365 * 5;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60*24; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyy>(1);
  cout << "freq year:" << endl;
  cout << ans << endl;
}

void freq_conv_test_quarter() {
  long xnr = 365 * 5;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60*24; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyyqq>();
  cout << "freq quarter:" << endl;
  cout << ans << endl;
}

void freq_conv_test_month() {
  long xnr = 365;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60*24; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyymm>();
  cout << "freq months:" << endl;
  cout << ans << endl;
}

void freq_conv_test_week() {
  long xnr = 240;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data -- 1 day increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60*24; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyyww>();
  cout << "freq week:" << endl;
  cout << ans << endl;
}

void freq_conv_test_day() {
  long xnr = 240;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data -- 1 hour increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyymmdd>();
  cout << "freq day:" << endl;
  cout << ans << endl;
}

void freq_conv_test_hour() {
  long xnr = 240;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data -- 1 min increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyymmddHH>();
  cout << "freq hour:" << endl;
  cout << ans << endl;
}

void freq_conv_test_minute() {
  long xnr = 240;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data -- 1 sec increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyymmddHHMM>();
  cout << "freq minute:" << endl;
  cout << ans << endl;
}

void freq_conv_test_second() {
  long xnr = 100;
  long xnc = 5;
  DDL_ts x(xnr,xnc);
  // generate dates/data -- 1/10 sec increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = static_cast<double>(i)/10; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);
  DDL_ts ans = x.freq<yyyymmddHHMMSS>();
  cout << "freq second:" << endl;
  cout << ans << endl;

  DDL_ts ans2 = x.freq<yyyymmddHHMMSS>(2);
  cout << "freq 2 seconds:" << endl;
  cout << ans2 << endl;

  DDL_ts ans3 = x.freq<yyyymmddHHMMSS>(3);
  cout << "freq 3 seconds:" << endl;
  cout << ans3 << endl;
}

void time_window_test_month() {
  // define our answer type
  typedef sumTraits<double>::ReturnType sum_ansType;

  long xnr = 500;
  long xnc = 5;

  DDL_ts x(xnr,xnc);

  // generate dates/data
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60*24; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);

  DDL_ts sum_ans = x.time_window<sum_ansType,Sum,yyyymm>();

  cout << "months:" << endl;
  cout << sum_ans << endl;
}

void time_window_test_day() {
  // define our answer type
  typedef sumTraits<double>::ReturnType sum_ansType;

  long xnr = 240;
  long xnc = 5;

  DDL_ts x(xnr,xnc);

  // generate dates/data -- 1 hour increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60*60; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);

  DDL_ts sum_ans = x.time_window<sum_ansType,Sum,yyyymmdd>();

  cout << "days:" << endl;
  cout << sum_ans << endl;
}

void time_window_test_hour() {
  // define our answer type
  typedef sumTraits<double>::ReturnType sum_ansType;

  long xnr = 240;
  long xnc = 5;

  DDL_ts x(xnr,xnc);

  // generate dates/data -- 1 min increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i * 60; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);

  DDL_ts sum_ans = x.time_window<sum_ansType,Sum,yyyymmddHH>();

  cout << "hours:" << endl;
  cout << sum_ans << endl;
}

void time_window_test_minute() {
  // define our answer type
  typedef sumTraits<double>::ReturnType sum_ansType;

  long xnr = 240;
  long xnc = 5;

  DDL_ts x(xnr,xnc);

  // generate dates/data -- 1 sec increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = i; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);

  DDL_ts sum_ans = x.time_window<sum_ansType,Sum,yyyymmddHHMM>();

  cout << "minutes:" << endl;
  cout << sum_ans << endl;
}

void time_window_test_second() {
  // define our answer type
  typedef sumTraits<double>::ReturnType sum_ansType;

  long xnr = 240;
  long xnc = 5;

  DDL_ts x(xnr,xnc);

  // generate dates/data -- 1/10 sec increments
  for(int i = 0; i < x.nrow(); i++) { x.getDates()[i] = static_cast<double>(i)/10; }
  std::fill(x.getData(), x.getData() + x.nrow() * x.ncol(), 1.0);

  DDL_ts sum_ans = x.time_window<sum_ansType,Sum,yyyymmddHHMMSS>();
  cout << "seconds:" << endl;
  cout << sum_ans << endl;

  DDL_ts sum_ans2 = x.time_window<sum_ansType,Sum,yyyymmddHHMMSS>(2);
  cout << "2 seconds:" << endl;
  cout << sum_ans2 << endl;

  DDL_ts sum_ans3 = x.time_window<sum_ansType,Sum,yyyymmddHHMMSS>(3);
  cout << "3 seconds:" << endl;
  cout << sum_ans3 << endl;
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
  test->add( BOOST_TEST_CASE( &mixed_operators_test ) );
  test->add( BOOST_TEST_CASE( &assignment_test ) );
  test->add( BOOST_TEST_CASE( &vector_window_apply_test ) );
  test->add( BOOST_TEST_CASE( &window_apply_test ) );
  test->add( BOOST_TEST_CASE( &lag_lead_test ) );
  test->add( BOOST_TEST_CASE( &diff_test ) );
  test->add( BOOST_TEST_CASE( &posix_date_test ) );
  test->add( BOOST_TEST_CASE( &vector_transform_test ) );
  test->add( BOOST_TEST_CASE( &vector_ema_test ) );
  test->add( BOOST_TEST_CASE( &transform_test ) );
  test->add( BOOST_TEST_CASE( &window_function_test ) );
  test->add( BOOST_TEST_CASE( &expanding_max_test ) );
  test->add( BOOST_TEST_CASE( &pad_test ) );

  test->add( BOOST_TEST_CASE( &time_window_test_month ) );
  test->add( BOOST_TEST_CASE( &time_window_test_day ) );
  test->add( BOOST_TEST_CASE( &time_window_test_hour ) );
  test->add( BOOST_TEST_CASE( &time_window_test_minute ) );
  test->add( BOOST_TEST_CASE( &time_window_test_second ) );

  test->add( BOOST_TEST_CASE( &cbind_test ) );

  test->add( BOOST_TEST_CASE( &freq_conv_test_year ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_quarter ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_month ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_week ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_day ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_hour ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_minute ) );
  test->add( BOOST_TEST_CASE( &freq_conv_test_second ) );

  return test;
}

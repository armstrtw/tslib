///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016  Whit Armstrong                                    //
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

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ctime>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>


#include <tslib/tseries.hpp>
#include <tslib/tseries.io.hpp>
#include <tslib/ts.opps/ts.opps.hpp>
#include <tslib/utils/window.function.hpp>
#include <tslib/utils/cbind.hpp>
#include <tslib/vector.summary.hpp>
#include <tslib/vector.transform.hpp>

using namespace tslib;
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

LDL_ts make_ascending_ts(long nr, long nc) {
  LDL_ts x(nr,nc);

  // gernate data
  for(long vi = 0; vi < x.nrow()*x.ncol(); vi++)
    x.getData()[vi] = vi+1;

  // generate dates
  for(long xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi+1;

  return x;
}

TEST_CASE("Constructors.") {
  
  SECTION("null_constructor_test") {
    LDL_ts x;

    // so we have the same type
    long zero = 0;
    REQUIRE( x.nrow()==zero );
    REQUIRE( x.ncol()==zero );
    REQUIRE( x.getData()==static_cast<double*>(NULL) );
    REQUIRE( x.getDates()== static_cast<long*>(NULL) );
    REQUIRE( static_cast<long>(x.getColnames().size())==zero );
  }

  SECTION("std_constructor_test") {
    long nr = 1000;
    long nc = 10;
    long zero = 0;

    LDL_ts x(nr,nc);

    REQUIRE( x.nrow()==nr );
    REQUIRE( x.ncol()==nc );
    REQUIRE( x.getDates() != static_cast<long*>(NULL) );
    REQUIRE( x.getData() != static_cast<double*>(NULL) );
    REQUIRE( static_cast<long>(x.getColnames().size())==zero );
  }

  SECTION("tsdata_constructor_test") {
    long nr = 1000;
    long nc = 10;
    long zero = 0;

    TSdataSingleThreaded<double,double> ts_data = TSdataSingleThreaded<double,double>(nr,nc);
    DDL_ts x(ts_data);

    REQUIRE( x.nrow()==nr );
    REQUIRE( x.ncol()==nc );
    REQUIRE( x.getData() != static_cast<double*>(NULL) );
    REQUIRE( x.getDates() != static_cast<double*>(NULL) );
    REQUIRE( static_cast<long>(x.getColnames().size())==zero );
  }

  SECTION("external_data_constructor_test") {
    long nr = 1000;
    long nc = 10;
    long zero = 0;

    double* dates_p = new double[nr];
    double* data_p = new double[nr*nc];

    DDL_ts x(data_p,dates_p,nr,nc,false);

    REQUIRE( x.nrow()==nr );
    REQUIRE( x.ncol()==nc );
    REQUIRE( x.getData()==data_p );
    REQUIRE( x.getDates()==dates_p );
    REQUIRE( static_cast<long>(x.getColnames().size())==zero );

    // release these b/c we asked for release=false in the ctor
    delete[] dates_p;
    delete[] data_p;
  }
}

TEST_CASE("Mutators.") {
  SECTION("Set colnames") {

    std::vector<std::string> newColnames;
    newColnames.push_back("hat");
    newColnames.push_back("cat");

    // not allowed to set colnames not equal to number of cols
    LDL_ts x(100,1);
    REQUIRE( x.setColnames(newColnames)==false );

    LDL_ts y(100,2);

    // test set colnames success
    REQUIRE(y.setColnames(newColnames)==true );

    // test that getColnames returns the correct value
    REQUIRE(y.getColnames()==newColnames);
  }
}

TEST_CASE("Range specifier") {

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

  REQUIRE(r.getSize() == 3);
  REQUIRE(r.getArg1()[0] == 0);
  REQUIRE(r.getArg1()[1] == 2);
  REQUIRE(r.getArg1()[2] == 4);

  REQUIRE(r.getArg2()[0] == 0);
  REQUIRE(r.getArg2()[1] == 1);
  REQUIRE(r.getArg2()[2] == 2);

  //r.print();
}

TEST_CASE("Operators") {
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

  REQUIRE( Zplus.nrow()==y.nrow() );
  REQUIRE( Zplus.ncol()==10 );

  REQUIRE( Zminus.nrow()==y.nrow() );
  REQUIRE( Zminus.ncol()==10 );

  REQUIRE( Zmultiplies.nrow()==y.nrow() );
  REQUIRE( Zmultiplies.ncol()==10 );

  REQUIRE( Zdivides.nrow()==y.nrow() );
  REQUIRE( Zdivides.ncol()==10 );

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

TEST_CASE("mixed_operators_test") {
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

  REQUIRE( Zplus.nrow()==y.nrow() );
  REQUIRE( Zplus.ncol()==10 );

  REQUIRE( Zminus.nrow()==y.nrow() );
  REQUIRE( Zminus.ncol()==10 );

  REQUIRE( Zmultiplies.nrow()==y.nrow() );
  REQUIRE( Zmultiplies.ncol()==10 );

  REQUIRE( Zdivides.nrow()==y.nrow() );
  REQUIRE( Zdivides.ncol()==10 );

  vector<bool> xb_eq_scalar = x == static_cast<int>(10);
  vector<bool> xb_neq_ts = x != y;
  vector<bool> xb_gt_ts = x > y;
  vector<bool> xb_gte_ts = x >= y;
  vector<bool> xb_lt_ts = x < y;
  vector<bool> xb_lte_ts = x <= y;
}

TEST_CASE("assignment_test") {
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

  REQUIRE(x.nrow()==xnr);
  REQUIRE(x.ncol()==xnc);
  REQUIRE(x.getData()[0] == 1.0);


  // TS TS assignment
  REQUIRE(y.getData()[0]==2.0);
  y = x;

  REQUIRE(y.nrow()==xnr);
  REQUIRE(y.ncol()==xnc);
  REQUIRE(y.getData()[0]==1.0);

  x = 100.0;

  // check that dims are same as before
  REQUIRE(x.nrow()==xnr);
  REQUIRE(x.ncol()==xnc);

  // now all values of x shoud be == 100.0
  for(long i = 0; i < x.nrow()*x.ncol(); i++) {
    REQUIRE(x.getData()[i]==100);
  }
}


TEST_CASE("vector_window_apply_test") {

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

  REQUIRE(ans[0]==10.5);
  delete []x;
  delete []ans;
}

TEST_CASE("rsi_test") {

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


TEST_CASE("window_apply_test") {
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
  REQUIRE(mean_ans.getData()[0]==3);

  TSeries<long,sum_ansType,long,TSdataSingleThreaded,PosixDate> sum_ans = x.window<sum_ansType,Sum>(5);
  REQUIRE(sum_ans.getData()[0]==(5.0*6.0)/2.0);

  TSeries<long,rank_ansType,long,TSdataSingleThreaded,PosixDate> rank_ans = x.window<rank_ansType,Rank>(5);
  REQUIRE(rank_ans.getData()[0]==5);
}

TEST_CASE("vector_transform_test") {

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
  REQUIRE(ans[4]==6);

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

TEST_CASE("vector_ema_test") {

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

TEST_CASE("transform_test") {
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
  REQUIRE(fillbwd_ans.getData()[21]==static_cast<double>(23));
}

TEST_CASE("pad_test") {
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


TEST_CASE("lag_lead_test") {

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

TEST_CASE("diff_test") {

  LDL_ts x = make_ascending_ts(10,5);

  LDL_ts y(x.diff(1));
  cout << y << endl;
}

TEST_CASE("expanding_max_test") {

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


TEST_CASE("posix_date_test") {
  const char* jan_01_2007 = "01/01/2007";
  const char* fmt_america = "%m/%d/%Y";

  long dt = PosixDate<long>::toDate(jan_01_2007,fmt_america);
  REQUIRE(strcmp(PosixDate<long>::toString(dt,fmt_america).c_str(),"01/01/2007")==0);

  // shifting
  long d1_shft_1d = PosixDate<long>::AddDays(dt,1);
  REQUIRE(strcmp(PosixDate<long>::toString(d1_shft_1d,fmt_america).c_str(),"01/02/2007")==0);

  long d1_shft_1m = PosixDate<long>::AddMonths(dt,1);
  REQUIRE(strcmp(PosixDate<long>::toString(d1_shft_1m,fmt_america).c_str(),"02/01/2007")==0);

  long d1_shft_1yr = PosixDate<long>::AddYears(dt,1);
  REQUIRE(strcmp(PosixDate<long>::toString(d1_shft_1yr,fmt_america).c_str(),"01/01/2008")==0);

  long d1_shft_24m = PosixDate<long>::AddMonths(dt,24);
  REQUIRE(strcmp(PosixDate<long>::toString(d1_shft_24m,fmt_america).c_str(),"01/01/2009")==0);

  long d1_shft_neg24m = PosixDate<long>::AddMonths(dt,-24);
  REQUIRE(strcmp(PosixDate<long>::toString(d1_shft_neg24m,fmt_america).c_str(),"01/01/2005")==0);

  long d1_shft_neg18m = PosixDate<long>::AddMonths(dt,-18);
  REQUIRE(strcmp(PosixDate<long>::toString(d1_shft_neg18m,fmt_america).c_str(),"07/01/2005")==0);

}

TEST_CASE("window_function_test") {
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

TEST_CASE("cbind_test") {
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

TEST_CASE("freq_conv_test_year") {
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

TEST_CASE("freq_conv_test_quarter") {
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

TEST_CASE("freq_conv_test_month") {
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

TEST_CASE("freq_conv_test_week") {
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

TEST_CASE("freq_conv_test_day") {
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

TEST_CASE("freq_conv_test_hour") {
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

TEST_CASE("freq_conv_test_minute") {
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

TEST_CASE("freq_conv_test_second") {
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

TEST_CASE("time_window_test_month") {
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

TEST_CASE("time_window_test_day") {
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

TEST_CASE("time_window_test_hour") {
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

TEST_CASE("time_window_test_minute") {
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

TEST_CASE("time_window_test_second") {
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

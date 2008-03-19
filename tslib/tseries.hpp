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

#ifndef TSERIES_HPP
#define TSERIES_HPP

#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <functional>

#include <tslib/tseries.data.hpp>
#include <tslib/range.specifier/rangeSpecifier.hpp>
#include <tslib/ts.opps/ts.opps.predeclare.hpp>
#include <tslib/ts.opps/ts.ts.opp.hpp>
#include <tslib/ts.opps/ts.scalar.opp.hpp>
#include <tslib/utils/window.apply.hpp>
#include <tslib/utils/window.function.hpp>
#include <tslib/vector.transform.hpp>
#include <tslib/date.policies/posix.date.policy.hpp>
#include <tslib/date.policies/date.breaks.hpp>

using std::plus;
using std::minus;
using std::multiplies;
using std::divides;
using std::greater;
using std::less;
using std::greater_equal;
using std::less_equal;
using std::equal_to;
using std::not_equal_to;

namespace tslib {

  template <typename TDATE, typename TDATA,
            typename TSDIM = long,
            template<typename,typename,typename> class TSDATABACKEND = TSdataSingleThreaded,
            template<typename> class DatePolicy = PosixDate>
  class TSeries {
  private:
    TSDATABACKEND<TDATE,TDATA,TSDIM>* tsdata_;
    const TSDIM offset(const TSDIM row, const TSDIM col) const;
  public:
    // ctors dtors
    ~TSeries();
    TSeries();
    TSeries(TSDATABACKEND<TDATE,TDATA,TSDIM>* tsdata);
    TSeries(const TSDIM rows, const TSDIM cols);
    TSeries(const TSeries& T);

    // copy an object
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> copy() const;

    // accessors
    TSDATABACKEND<TDATE,TDATA,TSDIM>* getIMPL() const;
    vector<string> getColnames() const;
    const TSDIM nrow() const;
    const TSDIM ncol() const;
    TDATA* getData() const;
    TDATE* getDates() const;

    // mutators
    int setColnames(const vector<string>& cnames);

    // transforms
    template<typename ReturnType, template<class> class F>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> window(const int window);

    template<typename ReturnType, template<class> class F>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> transform();

    template<typename ReturnType, template<class> class F, typename T>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> transform_1arg(T arg1);

    // frequency conversion (only highfreq to lowfreq conversion)
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> toQuarterly() const;
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> toMonthly() const;
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> toWeekly() const;

    // subsets
    template<typename T>
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> row_subset(T beg, T end) const;

    //operators
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& operator=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& x);
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& operator=(const TDATA x);

    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator() (const int n);

    // binary TS TS opps
    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+ <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator- <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator* <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/ <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);
    // binary TDATA TS opps
    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+ <> (const TDATA lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator- <> (const TDATA lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator* <> (const TDATA lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/ <> (const TDATA lhs,
                                                                             const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    // binary TS TDATA opps
    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+ <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TDATA rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator- <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TDATA rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator* <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TDATA rhs);

    friend TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/ <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                             const TDATA rhs);

    friend vector<bool> operator> <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                      const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);
    friend vector<bool> operator< <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                      const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);
    friend vector<bool> operator>= <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                       const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);
    friend vector<bool> operator<= <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                       const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);
    friend vector<bool> operator== <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                       const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);
    friend vector<bool> operator!= <> (const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                       const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

    friend std::ostream& operator<< <> (std::ostream& os,
                                        const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts);
  };

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  const TSDIM TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::offset(const TSDIM row, const TSDIM col) const {
    return row + col*nrow();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::operator=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {

    // self assignment
    if(tsdata_ == rhs.tsdata_) {
      return *this;
    }

    // release old data
    tsdata_->detach();

    // attach to new data
    tsdata_ = rhs.tsdata_;
    tsdata_->attach();

    return *this;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::operator=(const TDATA rhs) {
    TDATA* data = getData();
    for(TSDIM i = 0; i < nrow()*ncol(); i++) {
      data[i] = rhs;
    }
    return *this;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::operator() (const int n) {
    if(n == 0) {
      return *this;
    }

    // positive value is lag
    // negative value is lead
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(nrow(), ncol());

    // copy over dates
    std::copy(getDates(),getDates()+nrow(),ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    TDATA* ans_data = ans.getData();
    TDATA* data = getData();

    if(n > 0) {
      for(TSDIM c = 0; c < ncol(); c++) {
        Lag<TDATA>::apply(ans_data,data,data+nrow(),std::abs(n));
        ans_data+=ans.nrow();
        data+=nrow();
      }
    } else {
      for(TSDIM c = 0; c < ncol(); c++) {
        Lead<TDATA>::apply(ans_data,data,data+nrow(),std::abs(n));
        ans_data+=ans.nrow();
        data+=nrow();
      }
    }
    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,plus<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,minus<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,multiplies<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,divides<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,plus<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,minus<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,multiplies<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,divides<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA rhs) {
    return apply_opp(lhs,rhs,plus<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA rhs) {
    return apply_opp(lhs,rhs,minus<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA rhs) {
    return apply_opp(lhs,rhs,multiplies<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA rhs) {
    return apply_opp(lhs,rhs,divides<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator>(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_boolean_opp(lhs,rhs,greater<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator<(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_boolean_opp(lhs,rhs,less<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator>=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_boolean_opp(lhs,rhs,greater_equal<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator<=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_boolean_opp(lhs,rhs,less_equal<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator==(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_boolean_opp(lhs,rhs,equal_to<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator!=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_boolean_opp(lhs,rhs,not_equal_to<TDATA>());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  std::ostream& operator<< (std::ostream& os, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts) {
    vector<string> cnames(ts.getColnames());

    if(cnames.size()) {
      // shift out to be in line w/ first column of values (space is for dates column)
      os << "\t";
      for(vector<string>::const_iterator iter = cnames.begin(); iter != cnames.end(); iter++) {
        os << *iter++ << " ";
      }
    }

    TDATE* dates = ts.getDates();
    TDATA* data = ts.getData();
    TSDIM nr  = ts.nrow();
    TSDIM nc  = ts.ncol();

    for(TSDIM row = 0; row < nr; row++) {
      os << DatePolicy<TDATE>::toString(dates[row],"%Y-%m-%d %T") << "\t";
      for(TSDIM col = 0; col < nc; col++) {
        if(numeric_traits<TDATA>::ISNA(data[ts.offset(row,col)])) {
          os << "NA" << " ";
        } else {
          os << data[ts.offset(row,col)] << " ";
        }
      }
      os << std::endl;
    }
    return os;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::~TSeries() {
    tsdata_->detach();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::TSeries() {
    tsdata_ = TSDATABACKEND<TDATE,TDATA,TSDIM>::init();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::TSeries(TSDATABACKEND<TDATE,TDATA,TSDIM>* tsdata) {
    tsdata_ = tsdata;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::TSeries(const TSDIM rows, const TSDIM cols) {
    tsdata_ = TSDATABACKEND<TDATE,TDATA,TSDIM>::init(rows,cols);
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::TSeries(const TSeries& T) {
    tsdata_ = T.tsdata_;
    tsdata_->attach();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::copy() const {
    TSeries ans(nrow(),ncol());
    ans.setColnames(getColnames());

    std::copy(getDates(),getDates()+nrow(),ans.getDates());
    std::copy(getData(),getData()+nrow()*ncol(),ans.getData());

    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  TSDATABACKEND<TDATE,TDATA,TSDIM>* TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::getIMPL() const {
    return tsdata_;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  TDATE* TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::getDates() const {
    return tsdata_->getDates();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  TDATA* TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::getData() const {
    return tsdata_->getData();
  }


  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  const TSDIM TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::nrow() const {
    return tsdata_->nrow();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  const TSDIM TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::ncol() const {
    return tsdata_->ncol();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  inline
  vector<string> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::getColnames() const {
    return tsdata_->getColnames();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  int TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::setColnames(const vector<string>& cnames) {
    if(static_cast<TSDIM>(cnames.size()) == ncol()) {
      tsdata_->setColnames(cnames);
      return 0; // SUCCESS
    } else {
      return 1; // FAILURE
    }
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename ReturnType, template<class> class F>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::window(const int window) {

    // allocate new answer
    TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> ans(nrow(), ncol());

    // copy over dates
    std::copy(getDates(),getDates()+nrow(),ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    ReturnType* ans_data = ans.getData();
    TDATA* data = getData();

    for(TSDIM col = 0; col < ncol(); col++) {
      windowApply<ReturnType,F>::apply(ans_data, data, data + nrow(), window);
      ans_data += ans.nrow();
      data += nrow();
    }
    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename ReturnType, template<class> class F>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::transform() {

    // allocate new answer
    TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> ans(nrow(), ncol());

    // copy over dates
    std::copy(getDates(),getDates()+nrow(),ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    ReturnType* ans_data = ans.getData();
    TDATA* data = getData();

    for(TSDIM col = 0; col < ncol(); col++) {
      F<ReturnType>::apply(ans_data, data, data + nrow());
      ans_data += ans.nrow();
      data += nrow();
    }
    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename ReturnType, template<class> class F, typename T>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::transform_1arg(T arg1) {

    // allocate new answer
    TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> ans(nrow(), ncol());

    // copy over dates
    std::copy(getDates(),getDates()+nrow(),ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    ReturnType* ans_data = ans.getData();
    TDATA* data = getData();

    for(TSDIM col = 0; col < ncol(); col++) {
      F<ReturnType>::apply(ans_data, data, data + nrow(), arg1);
      ans_data += ans.nrow();
      data += nrow();
    }
    return ans;
  }


  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::toQuarterly() const {
    vector<TSDIM> breaks;
    QuarterlyBreaks<DatePolicy>(getDates(), getDates()+nrow(), breaks);
    return row_subset(breaks.begin(), breaks.end());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::toMonthly() const {
    vector<TSDIM> breaks;
    MonthlyBreaks<DatePolicy>(getDates(), getDates()+nrow(), breaks);
    return row_subset(breaks.begin(), breaks.end());
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::toWeekly() const {
    vector<TSDIM> breaks;
    WeeklyBreaks<DatePolicy>(getDates(), getDates()+nrow(), breaks);
    return row_subset(breaks.begin(), breaks.end());
  }

  // this is for a positive row subset (positive and negative rowsets cannot mix)
  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename T>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::row_subset(T beg, T end) const {
    TSDIM new_nrow = static_cast<TSDIM>( std::distance(beg,end) );
    TSDIM new_ncol = ncol();

    // allocate new answer
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(new_nrow, new_ncol);

    // copy over colnames
    ans.setColnames(getColnames());

    TDATE* dates = getDates();
    TDATA* data = getData();
    TDATE* ans_dates = ans.getDates();
    TDATA* ans_data = ans.getData();

    TSDIM ans_index = 0;

    while(beg!=end) {
      ans_dates[ans_index] = dates[*beg];
      for(TSDIM c = 0; c < ncol(); c++) {
        ans_data[ans.offset(ans_index,c)] = data[offset(*beg,c)];
      }
      ++beg;
      ++ans_index;
    }
    return ans;
  }

}  // namespace tslib

#endif // TSERIES_HPP

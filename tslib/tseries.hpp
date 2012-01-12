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

#include <set>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <stdexcept>

#include <tslib/tseries.data.hpp>
#include <tslib/range.specifier/rangeSpecifier.hpp>
#include <tslib/ts.opps/ts.opps.hpp>
#include <tslib/utils/window.apply.hpp>
#include <tslib/utils/window.function.hpp>
#include <tslib/utils/breaks.hpp>
#include <tslib/vector.transform.hpp>
#include <tslib/date.policies/posix.date.policy.hpp>
#include <tslib/date.policies/date.partition.hpp>

namespace tslib {

  class TSeriesError : public std::runtime_error {
  public:
    TSeriesError(const std::string& msg = "") : std::runtime_error(msg) {}
  };

  template <typename TDATE, typename TDATA,
            typename TSDIM,
            template<typename,typename,typename> class TSDATABACKEND,
            template<typename> class DatePolicy>
  class TSeries {
  private:
    TSDATABACKEND<TDATE,TDATA,TSDIM>* tsdata_;
    const TSDIM offset(const TSDIM row, const TSDIM col) const {
      return row + col*nrow();
    }
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
    std::vector<std::string> getColnames() const;
    const TSDIM nrow() const;
    const TSDIM ncol() const;
    TDATA* getData() const;
    TDATE* getDates() const;

    // mutators
    int setColnames(const std::vector<std::string>& cnames);

    // transforms
    template<typename ReturnType, template<class> class F>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> window(const size_t window) const;

    template<typename ReturnType, template<class> class F, template<class, template<typename> class> class PFUNC>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> time_window(const int n = 1) const;

    template<typename ReturnType, template<class> class F>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> transform() const;

    template<typename ReturnType, template<class> class F, typename T>
    const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> transform_1arg(T arg1) const;

    // frequency conversion (only highfreq to lowfreq conversion)
    template<template<class, template<typename> class> class PFUNC>
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> freq(const int n = 1) const;

    // subsets
    template<typename T>
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> row_subset(T beg, T end) const;

    // pad
    template<typename T>
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> pad(T beg, T end) const;

    //operators
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& operator=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& x);
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& operator=(const TDATA x);

    // lag lead
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator() (const int n) const;
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> lag(const unsigned int n) const;
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> lead(const unsigned int n) const;
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> diff(const unsigned int n) const;

    // matix index
    TDATA operator() (const TSDIM row, const TSDIM col) const;
    TDATA& operator() (const TSDIM row, const TSDIM col);

    friend std::ostream& operator<< <> (std::ostream& os, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts);
  };

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
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::operator() (const int n) const {
    if( n > 0 ) {
      return lag(n);
    } else if( n < 0) {
      return lead(abs(n));
    }
    return *this;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::lag(const unsigned int n) const {
    if(n >= nrow()) {
      TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> bad_ans(0,ncol());
      bad_ans.setColnames(getColnames());
      return bad_ans;
    }
    const TSDIM new_size = nrow() - n;
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(new_size, ncol());
    TDATA* ans_data = ans.getData();
    const TDATA* data = getData();

    // copy over dates
    std::copy(getDates() + n, getDates() + n + new_size, ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    for(TSDIM c = 0; c < ncol(); c++) {
      std::copy(data, data + new_size, ans_data);
      ans_data += ans.nrow();
      data += nrow();
    }
    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::lead(const unsigned int n) const {
    if(n >= nrow()) {
      TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> bad_ans(0,ncol());
      bad_ans.setColnames(getColnames());
      return bad_ans;
    }
    const TSDIM new_size = nrow() - n;
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(new_size, ncol());
    TDATA* ans_data = ans.getData();
    const TDATA* data = getData();

    // copy over dates
    std::copy(getDates(), getDates() + new_size, ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    for(TSDIM c = 0; c < ncol(); c++) {
      std::copy(data + n, data + n + new_size, ans_data);
      ans_data += ans.nrow();
      data += nrow();
    }
    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::diff(const unsigned int n) const {
    if(n >= nrow()) {
      TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> bad_ans(0,ncol());
      bad_ans.setColnames(getColnames());
      return bad_ans;
    }
    const TSDIM new_size = nrow() - n;
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(new_size, ncol());
    TDATA* ans_data = ans.getData();
    const TDATA* data = getData();

    // copy over dates
    std::copy(getDates() + n, getDates() + n + new_size, ans.getDates());

    // set new colnames
    ans.setColnames(getColnames());

    for(TSDIM c = 0; c < ncol(); c++) {
      for(TSDIM r = n; r < nrow(); r++) {
        if(numeric_traits<TDATA>::ISNA(data[r]) || numeric_traits<TDATA>::ISNA(data[r-n])) {
          ans_data[r-n] = numeric_traits<TDATA>::NA();
        } else {
          ans_data[r-n] = data[r] - data[r-n];
        }
      }
      ans_data += ans.nrow();
      data += nrow();
    }
    return ans;
  }


  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TDATA TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::operator() (const TSDIM row, const TSDIM col) const {
    TDATA* data = getData();
    return data[offset(row, col)];
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TDATA& TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::operator() (const TSDIM row, const TSDIM col) {
    TDATA* data = getData();
    return data[offset(row, col)];
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  std::ostream& operator<< (std::ostream& os, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts) {
    std::vector<std::string> cnames(ts.getColnames());

    if(cnames.size()) {
      // shift out to be in line w/ first column of values (space is for dates column)
      os << "\t";
      for(std::vector<std::string>::const_iterator iter = cnames.begin(); iter != cnames.end(); iter++) {
        os << *iter++ << " ";
      }
    }

    TDATE* dates = ts.getDates();
    TSDIM nr  = ts.nrow();
    TSDIM nc  = ts.ncol();

    for(TSDIM row = 0; row < nr; row++) {
      os << DatePolicy<TDATE>::toString(dates[row],"%Y-%m-%d %T") << "\t";
      for(TSDIM col = 0; col < nc; col++) {
        if(numeric_traits<TDATA>::ISNA(ts(row,col))) {
          os << "NA" << " ";
        } else {
          os << ts(row,col) << " ";
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
  std::vector<std::string> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::getColnames() const {
    return tsdata_->getColnames();
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  int TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::setColnames(const std::vector<std::string>& cnames) {
    if(static_cast<TSDIM>(cnames.size()) == ncol()) {
      tsdata_->setColnames(cnames);
      return 0; // SUCCESS
    } else {
      return 1; // FAILURE
    }
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename ReturnType, template<class> class F>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::window(const size_t window) const {

    // allocate new answer
    TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> ans(nrow() - (window - 1), ncol());

    // copy over dates
    std::copy(getDates() + (window - 1), getDates()+nrow(), ans.getDates());

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
  template<typename ReturnType, template<class> class F, template<class, template<typename> class> class PFUNC>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::time_window(const int n) const {
    // pre-allocate vector for transformed dates
    typename std::vector<TDATE> partitions;
    partitions.resize(nrow());
    TDATE* dts = getDates();
    // transform dates
    for(TSDIM row = 0; row < nrow(); row++) {
      partitions[row] = PFUNC<TDATE, DatePolicy>()(dts[row],n);
    }
    //std::transform(getDates(), getDates() + nrow(), partitions.begin(), std::bind2nd(PFUNC<TDATE, DatePolicy>(), n));
    // vector for selected rows
    std::vector<TSDIM> ans_rows;
    breaks(partitions.begin(),partitions.end(),std::back_inserter(ans_rows));

    TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> ans(ans_rows.size(), ncol());
    ans.setColnames(getColnames());
    TDATE* dates = getDates();
    TDATE* ans_dates = ans.getDates();
    for(size_t i = 0; i < ans_rows.size(); i++) {
      ans_dates[i] = dates[ans_rows[i]];
    }

    ReturnType* ans_data = ans.getData();
    TDATA* data = getData();
    for(TSDIM ans_col = 0; ans_col < ans.ncol(); ans_col++, data+=nrow()) {
      size_t range_start = 0;
      for(size_t i = 0; i < ans_rows.size(); i++) {
        ans_data[ans.offset(i, ans_col)] = F<ReturnType>::apply(data + range_start, data + ans_rows[i] + 1);
        range_start = ans_rows[i] + 1;
      }
    }
    return ans;
  }

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename ReturnType, template<class> class F>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::transform() const {

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
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::transform_1arg(T arg1) const {

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

  // this is for a positive row subset (positive and negative rowsets cannot mix)
  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<typename T>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::pad(T beg, T end) const {
    std::set<TDATE> new_dts;
    // add existing dates
    for(TDATE* d = getDates(); d < getDates() + nrow(); d++) { new_dts.insert(*d); }

    // add new dates
    while(beg!=end) { new_dts.insert(static_cast<TDATE>(*beg++)); }

    // allocate new answer
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(new_dts.size(), ncol());

    // copy colnames
    ans.setColnames(getColnames());

    // init dates
    TDATE* dts = ans.getDates();
    for(typename std::set<TDATE>::iterator iter = new_dts.begin(); iter != new_dts.end(); iter++) {
      *dts++ = *iter;
    }

    // init to NA
    for(TSDIM i = 0; i < ans.nrow() * ans.ncol(); i++) {
      ans.getData()[i] = numeric_traits<TDATA>::NA();
    }

    RangeSpecifier<TDATE,TSDIM> range(getDates(),ans.getDates(),nrow(),ans.nrow());
    const TSDIM* r1 = range.getArg1();
    const TSDIM* r2 = range.getArg2();
    TDATA* ans_data = ans.getData();
    TDATA* this_data = getData();
    for(TSDIM col = 0; col < ans.ncol(); col++) {
      for(TSDIM i = 0; i < range.getSize(); i++) {
        ans_data[ans.offset(r2[i],col)] = this_data[offset(r1[i],col)];
      }
    }
    return ans;
  }


  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  template<template<class, template<typename> class> class PFUNC>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>::freq(const int n) const {

    // pre-allocate vector for transformed dates
    typename std::vector<TDATE> partitions;
    partitions.resize(nrow());
    // transform dates
    TDATE* dts = getDates();
    for(TSDIM row = 0; row < nrow(); row++) {
      partitions[row] = PFUNC<TDATE, DatePolicy>()(dts[row],n);
    }
    //std::transform(getDates(), getDates() + nrow(), partitions.begin(), std::bind2nd(PFUNC<TDATE, DatePolicy>, n));
    // vector for selected rows
    std::vector<TSDIM> ans_rows;
    breaks(partitions.begin(),partitions.end(),std::back_inserter(ans_rows));
    return row_subset(ans_rows.begin(), ans_rows.end());
  }
}  // namespace tslib

#endif // TSERIES_HPP

#ifndef TSERIES_HPP
#define TSERIES_HPP

#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <functional>

#include <tslib/tseries.data.hpp>
#include <tslib/range.specifier/rangeSpecifier.hpp>
#include <tslib/utils/copyVector.hpp>
#include <tslib/ts.opps/ts.ts.opp.hpp>
#include <tslib/ts.opps/ts.scalar.opp.hpp>
#include <tslib/utils/window.apply.hpp>
#include <tslib/vector.transform/lag.hpp>
#include <tslib/vector.transform/lead.hpp>
#include <tslib/date.policies/posix.date.policy.hpp>

using std::plus;
using std::minus;
using std::multiplies;
using std::divides;


namespace tslib {

// pre-declare template friends
template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> class TSeries;

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> correlation(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                                                const TSDIM periods);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> covariance(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                                                const TSDIM periods);

  /*
    template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy, typename F >
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> applyWindowIntersection(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
    const U periods);
  */

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TDATA lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TDATA lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TDATA lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);


template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
std::ostream& operator<<(std::ostream& os,
                         const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts);

template <typename TDATE, typename TDATA,
          typename TSDIM = long,
          template<typename,typename,typename> class TSDATABACKEND = TSdataSingleThreaded,
          template<typename> class DatePolicy = PosixDate>
class TSeries {
private:
  TSDATABACKEND<TDATE,TDATA,TSDIM>* tsdata_;

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
  template<typename ReturnType, template <class> class F>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> window(const int window);

  template<typename ReturnType, template <class> class F>
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> transform();

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

  friend std::ostream& operator<< <> (std::ostream& os,
                                      const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts);
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
  copyVector(ans.getDates(),getDates(),nrow());

  // set new colnames
  ans.setColnames(getColnames());

  TDATA* ans_data = ans.getData();
  TDATA* data = getData();

  if(n > 0) {
    for(TSDIM c = 0; c < ncol(); c++) {
      lag(ans_data,data,data+nrow(),std::abs(n));
      ans_data+=ans.nrow();
      data+=nrow();
    }
  } else {
    for(TSDIM c = 0; c < ncol(); c++) {
      lead(ans_data,data,data+nrow(),std::abs(n));
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
    os << dates[row] << "\t";
    for(TSDIM col = 0; col < nc; col++) {
      if(numeric_traits<TDATA>::ISNA(data[row + col*nr])) {
          os << "NA" << " ";
      } else {
        os << data[row + col*nr] << " ";
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

  copyVector(ans.getDates(), getDates(),nrow());
  copyVector(ans.getData(), getData(), nrow() * ncol() );

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
  if(cnames.size() == ncol()) {
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
  copyVector(ans.getDates(),getDates(),nrow());

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
  copyVector(ans.getDates(),getDates(),nrow());

  // set new colnames
  ans.setColnames(getColnames());

  TDATA* ans_data = ans.getData();
  TDATA* data = getData();

  for(TSDIM col = 0; col < ncol(); col++) {
    F<TDATA>::apply(ans_data, data, data + nrow());
    ans_data += ans.nrow();
    data += nrow();
  }
  return ans;
}

}  // namespace tslib

#endif // TSERIES_HPP

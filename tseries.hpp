#ifndef TSERIES_HPP
#define TSERIES_HPP

#include <cstdlib>
#include <iostream>
#include "tseries.data.hpp"
#include "utils/copyVector.hpp"

template <typename TDATE,typename TDATA>
class TSeries {
private:
  TSdata<TDATE,TDATA>* tsdata_;

public:
  ~TSeries();
  TSeries();
  TSeries(const TSDIM rows, const TSDIM cols);
  TSeries(const TSeries& T);

  TSeries<TDATE,TDATA> copy() const;

  // accessors
  vector<string> getColnames() const;
  TSDIM nrow() const;
  TSDIM ncol() const;
  TDATA* getData() const;
  TDATE* getDates() const;

  // mutators
  int setColnames(const vector<string>& cnames);
};

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::~TSeries() {
  tsdata_->detach();
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries() {
  tsdata_ = TSdata<TDATE,TDATA>::init();
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries(const TSDIM rows, const TSDIM cols) {
  tsdata_ = TSdata<TDATA,TDATA>::init(rows,cols);
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries(const TSeries& T) {
  tsdata_ = T.tsdata_;
  tsdata_->attach();
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA> TSeries<TDATE,TDATA>::copy() const {
  TSeries ans(nrow(),ncol());
  ans.setColnames(getColnames());

  copyVector(ans.getDates(), getDates(),nrow());
  copyVector(ans.getData(), getData(), nrow() * ncol() );

  return ans;
}

template <typename TDATE,typename TDATA>
inline
TDATE* TSeries<TDATE,TDATA>::getDates() const {
  return tsdata_->getDates();
}

template <typename TDATE,typename TDATA>
inline
TDATA* TSeries<TDATE,TDATA>::getData() const {
  return tsdata_->getData();
}


template <typename TDATE,typename TDATA>
inline
TSDIM TSeries<TDATE,TDATA>::nrow() const {
  return tsdata_->nrow();
}

template <typename TDATE,typename TDATA>
inline
TSDIM TSeries<TDATE,TDATA>::ncol() const {
  return tsdata_->ncol();
}

template <typename TDATE,typename TDATA>
inline
vector<string> TSeries<TDATE,TDATA>::getColnames() const {
  return tsdata_->getColnames();
}

template <typename TDATE,typename TDATA>
int TSeries<TDATE,TDATA>::setColnames(const vector<string>& cnames) {
  if(cnames.size() == ncol()) {
    tsdata_->setColnames(cnames);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}


#endif // TSERIES_HPP

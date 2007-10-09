#ifndef TSERIES_HPP
#define TSERIES_HPP

#include <iostream>

typedef long TSDIM;

template <typename TDATE,typename TDATA>
class TSeries {
private:
  TSDIM rows_;
  TSDIM cols_;
  TDATE* dates_;
  TDATA* data_;
public:
  TSeries();
  TSeries(const TSDIM rows, const TSDIM cols);
  ~TSeries();

};

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries() : rows_(0), cols_(0), dates_(NULL), data_(NULL) {
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::TSeries(const TSDIM rows, const TSDIM cols) : rows_(rows), cols_(cols), dates_(NULL), data_(NULL) {
  data_ = new TDATA[rows*cols];
  dates_ = new TDATE[rows];
  
  if(data_ == NULL || dates_ == NULL) {
    delete[] data_;
    delete[] dates_;
    rows = 0;
    cols = 0;
  }
}

template <typename TDATE,typename TDATA>
TSeries<TDATE,TDATA>::~TSeries() {
  delete[] data_;
  delete[] dates_;
}


#endif // TSERIES_HPP

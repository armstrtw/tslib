#ifndef TSERIES_HPP
#define TSERIES_HPP

#include <iostream>

typedef long TSDIM;

template <typename TDATE,typename TDATA>
class tseries {
private:
  TSDIM rows_;
  TSDIM cols_;
  TDATE* dates_;
  TDATA* data_;
public:
  tseries();
  tseries(const TSDIM rows, const TSDIM cols);
  ~tseries();

};

template <typename TDATE,typename TDATA>
tseries<TDATE,TDATA>::tseries() : rows_(0), cols_(0), dates_(NULL), data_(NULL) {
}

template <typename TDATE,typename TDATA>
tseries<TDATE,TDATA>::tseries(const TSDIM rows, const TSDIM cols) : rows_(rows), cols_(cols), dates_(NULL), data_(NULL) {
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
tseries<TDATE,TDATA>::~tseries() {
  delete[] data_;
  delete[] dates_;
}


#endif // TSERIES_HPP

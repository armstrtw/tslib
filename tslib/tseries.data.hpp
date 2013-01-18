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

#ifndef TSERIES_DATA_HPP
#define TSERIES_DATA_HPP

#include <vector>
#include <string>

namespace tslib {

  template <typename TDATE,typename TDATA, typename TSDIM = long>
  class TSdataSingleThreaded {
  private:
    bool release_data_;
    std::vector<std::string> colnames_;
    TSDIM rows_;
    TSDIM cols_;
    TDATE* dates_;
    TDATA* data_;
  public:
    ~TSdataSingleThreaded();
    TSdataSingleThreaded();
    TSdataSingleThreaded(const TSdataSingleThreaded& t);

    TSdataSingleThreaded(const TSDIM rows, const TSDIM cols);

    TSdataSingleThreaded(TDATA* external_data,
                         TDATE* external_dates,
                         const TSDIM rows,
                         const TSDIM cols,
                         const bool release = false);

    TSdataSingleThreaded& operator=(const TSdataSingleThreaded& rhs);

    TSDIM nrow() const;
    TSDIM ncol() const;
    TDATA* getData() const;
    TDATE* getDates() const;
    void setColnames(const std::vector<std::string>& cnames);
    std::vector<std::string> getColnames() const;
    const size_t getColnamesSize() const;
  };

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::~TSdataSingleThreaded() {
    if(release_data_) {
      delete []dates_;
      delete []data_;
    }
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded():
    release_data_(true), rows_(0), cols_(0), dates_(NULL), data_(NULL) {}

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded(const TSdataSingleThreaded& t):
  release_data_(true), colnames_(t.colnames_), rows_(t.rows_), cols_(t.cols_), dates_(new TDATE[t.rows_]), data_(new TDATA[t.rows_*t.cols_]) {
    std::copy(t.dates_, t.dates_ + rows_, dates_);
    std::copy(t.data_, t.data_ + t.rows_*t.cols_, data_);
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded(const TSDIM rows, const TSDIM cols):
    release_data_(true), rows_(rows), cols_(cols), dates_(new TDATE[rows]), data_(new TDATA[rows*cols]) {}

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded(TDATA* external_data, TDATE* external_dates, const TSDIM nrows, const TSDIM ncols, const bool release):
    release_data_(release), rows_(nrows), cols_(ncols), dates_(external_dates), data_(external_data) {}

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>& TSdataSingleThreaded<TDATE,TDATA,TSDIM>::operator=(const TSdataSingleThreaded& rhs) {
    // release old data
    if(release_data_) {
      delete []dates_;
      delete []data_;
    }
    release_data_ = true;
    colnames_ = rhs.colnames_;
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    dates_ = new TDATE[rhs.rows_];
    data_ = new TDATA[rhs.rows_*rhs.cols_];
    std::copy(rhs.dates_, rhs.dates_ + rhs.rows_, dates_);
    std::copy(rhs.data_, rhs.data_ + rhs.rows_*rhs.cols_, data_);
    return *this;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  void TSdataSingleThreaded<TDATE,TDATA,TSDIM>::setColnames(const std::vector<std::string>& cnames) {
    colnames_ = cnames;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  std::vector<std::string> TSdataSingleThreaded<TDATE,TDATA,TSDIM>::getColnames() const {
    return colnames_;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  const size_t TSdataSingleThreaded<TDATE,TDATA,TSDIM>::getColnamesSize() const {
    return colnames_.size();
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  TDATA* TSdataSingleThreaded<TDATE,TDATA,TSDIM>::getData() const {
    return data_;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  TDATE* TSdataSingleThreaded<TDATE,TDATA,TSDIM>::getDates() const {
    return dates_;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  TSDIM TSdataSingleThreaded<TDATE,TDATA,TSDIM>::nrow() const {
    return rows_;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  TSDIM TSdataSingleThreaded<TDATE,TDATA,TSDIM>::ncol() const {
    return cols_;
  }

} // namespace tslib

#endif // TSERIES_DATA_HPP

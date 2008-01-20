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

using std::vector;
using std::string;

namespace tslib {

  template <typename TDATE,typename TDATA, typename TSDIM = long>
  class TSdataSingleThreaded {
  private:
    int refcount_;
    bool release_data_;
    vector<string> colnames_;
    TSDIM rows_;
    TSDIM cols_;
    TDATE* dates_;
    TDATA* data_;

    TSdataSingleThreaded();
    TSdataSingleThreaded(const TSdataSingleThreaded& t); // not allowed

    TSdataSingleThreaded(const TSDIM rows, const TSDIM cols);

    TSdataSingleThreaded(TDATA* external_data,
                         TDATE* external_dates,
                         const TSDIM rows,
                         const TSDIM cols,
                         const bool release = false);

    TSdataSingleThreaded& operator=(const TSdataSingleThreaded& right);  // not allowed

  public:
    ~TSdataSingleThreaded();

    static TSdataSingleThreaded* init();

    static TSdataSingleThreaded* init(const TSDIM rows, const TSDIM cols);

    static TSdataSingleThreaded* init(TDATA* external_data,
                                      TDATE* external_dates,
                                      const TSDIM rows,
                                      const TSDIM cols,
                                      const bool release = false);

    void attach();
    void detach();

    TSDIM nrow() const;
    TSDIM ncol() const;
    TDATA* getData() const;
    TDATE* getDates() const;
    void setColnames(const vector<string>& cnames);
    vector<string> getColnames() const;
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
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded() {
    refcount_ = 1;
    release_data_ = true;
    rows_ = 0;
    cols_ = 0;
    dates_ = NULL;
    data_ = NULL;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded(const TSDIM rows, const TSDIM cols) {
    refcount_ = 1;
    release_data_ = true;
    rows_ = rows;
    cols_ = cols;

    dates_ = new TDATE[rows];
    data_ = new TDATA[rows*cols];

    if(data_==NULL || dates_==NULL) {
      //cerr << "memory allocation error." << endl;
      delete []data_;
      delete []dates_;
      data_ = NULL;
      dates_ = NULL;
      rows_ = 0;
      cols_ = 0;
    }
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>::TSdataSingleThreaded(TDATA* external_data,
                                                                TDATE* external_dates,
                                                                const TSDIM nrows,
                                                                const TSDIM ncols,
                                                                const bool release) {

    // make null series if some data is null
    if(external_data==NULL || external_dates==NULL) {
      refcount_ = 1;
      release_data_ = release;
      data_ = NULL;
      dates_ = NULL;
      rows_ = 0;
      cols_ = 0;
    } else {
      refcount_ = 1;
      release_data_ = release;
      data_ = external_data;
      dates_ = external_dates;
      rows_ = nrows;
      cols_ = ncols;
    }
  }


  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>* TSdataSingleThreaded<TDATE,TDATA,TSDIM>::init() {
    return new TSdataSingleThreaded();
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>* TSdataSingleThreaded<TDATE,TDATA,TSDIM>::init(const TSDIM rows, const TSDIM cols) {
    return new TSdataSingleThreaded(rows, cols);
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  TSdataSingleThreaded<TDATE,TDATA,TSDIM>* TSdataSingleThreaded<TDATE,TDATA,TSDIM>::init(TDATA* external_data,
                                                                                         TDATE* external_dates,
                                                                                         const TSDIM nrows,
                                                                                         const TSDIM ncols,
                                                                                         const bool release) {

    return new TSdataSingleThreaded(external_data,
                                    external_dates,
                                    nrows,
                                    ncols,
                                    release);
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  void TSdataSingleThreaded<TDATE,TDATA,TSDIM>::attach() {
    ++refcount_;
    //cout << "attach, new refcount_: " << refcount_ << endl;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  void TSdataSingleThreaded<TDATE,TDATA,TSDIM>::detach() {
    refcount_--;
    //cout << "detach, refcount_: " << refcount_ << endl;
    if(refcount_ == 0) {
      delete this;
    }
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  void TSdataSingleThreaded<TDATE,TDATA,TSDIM>::setColnames(const vector<string>& cnames) {
    colnames_ = cnames;
  }

  template <typename TDATE,typename TDATA, typename TSDIM>
  inline
  vector<string> TSdataSingleThreaded<TDATE,TDATA,TSDIM>::getColnames() const {
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

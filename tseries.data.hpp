#ifndef TSERIES_DATA_HPP
#define TSERIES_DATA_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;

typedef long TSDIM;

template <typename TDATE,typename TDATA>
class TSdata {
private:
  int refcount_;
  bool release_data_;
  vector<string> colnames_;
  TSDIM rows_;
  TSDIM cols_;
  TDATE* dates_;
  TDATA* data_;

  TSdata();
  TSdata(const TSdata& t); // not allowed

  TSdata(const TSDIM rows, const TSDIM cols);

  TSdata(TDATA* external_data,
         TDATE* external_dates,
         const TSDIM rows,
         const TSDIM cols,
         const bool release = false);

  TSdata& operator=(const TSdata& right);  // not allowed

public:
  ~TSdata();

  static TSdata* init();

  static TSdata* init(const TSDIM rows, const TSDIM cols);

  static TSdata* init(TDATA* external_data,
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


template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>::~TSdata() {
  if(release_data_) {
    delete []dates_;
    delete []data_;
  }
}

template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>::TSdata() {
  refcount_ = 1;
  release_data_ = true;
  rows_ = 0;
  cols_ = 0;
  dates_ = NULL;
  data_ = NULL;
}

template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>::TSdata(const TSDIM rows, const TSDIM cols) {
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

template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>::TSdata(TDATA* external_data,
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


template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>* TSdata<TDATE,TDATA>::init() {
  return new TSdata();
}

template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>* TSdata<TDATE,TDATA>::init(const TSDIM rows, const TSDIM cols) {
  return new TSdata(rows, cols);
}

template <typename TDATE,typename TDATA>
TSdata<TDATE,TDATA>* TSdata<TDATE,TDATA>::init(TDATA* external_data,
                                               TDATE* external_dates,
                                               const TSDIM nrows,
                                               const TSDIM ncols,
                                               const bool release) {

  return new TSdata(external_data,
                    external_dates,
                    nrows,
                    ncols,
                    release);
}

template <typename TDATE,typename TDATA>
void TSdata<TDATE,TDATA>::attach() {
  ++refcount_;
  //cout << "attach, new refcount_: " << refcount_ << endl;
}

template <typename TDATE,typename TDATA>
void TSdata<TDATE,TDATA>::detach() {
  refcount_--;
  //cout << "detach, refcount_: " << refcount_ << endl;
  if(refcount_ == 0) {
    delete this;
  }
}

template <typename TDATE,typename TDATA>
void TSdata<TDATE,TDATA>::setColnames(const vector<string>& cnames) {
  colnames_ = cnames;
}

template <typename TDATE,typename TDATA>
inline
vector<string> TSdata<TDATE,TDATA>::getColnames() const {
  return colnames_;
}

template <typename TDATE,typename TDATA>
inline
const size_t TSdata<TDATE,TDATA>::getColnamesSize() const {
  return colnames_.size();
}

template <typename TDATE,typename TDATA>
inline
TDATA* TSdata<TDATE,TDATA>::getData() const {
  return data_;
}

template <typename TDATE,typename TDATA>
inline
TDATE* TSdata<TDATE,TDATA>::getDates() const {
  return dates_;
}

template <typename TDATE,typename TDATA>
inline
TSDIM TSdata<TDATE,TDATA>::nrow() const {
  return rows_;
}

template <typename TDATE,typename TDATA>
inline
TSDIM TSdata<TDATE,TDATA>::ncol() const {
  return cols_;
}


#endif // TSERIES_DATA_HPP

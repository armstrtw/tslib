#ifndef RANGESPECIFIER_HPP
#define RANGESPECIFIER_HPP

using std::cout;
using std::cerr;
using std::endl;
using std::distance;
using std::set_intersection;

template<typename T, typename U>
class RangeSpecifier {
private:
  T* dates_;  // intersection dates_
  U* index1_;   // index of intersections of index1_
  U* index2_;   // index of intersections of index2_
  U size;    // also the length of all the internal vectors: dates_, index1_, index2_

public:
  ~RangeSpecifier();
  RangeSpecifier(const RangeSpecifier &r); // not allowed!!
  RangeSpecifier(T *dates_1,
		 T *dates_2,
		 const U length_index1_,
		 const U length_index2_);

  const T* getDates() const;
  const U* getArg1() const;
  const U* getArg2() const;
  const U getSize() const;
  void print() const;
  
  template<typename D, typename BinaryOpp>
  void applyOpp(D* ans, D* index1_Data, D* index2_Data, BinaryOpp opp) const;
};

template<typename T, typename U>
RangeSpecifier<T,U>::~RangeSpecifier() {
  delete [] dates_;
  delete [] index1_;
  delete [] index2_;
}

template<typename T, typename U>
RangeSpecifier<T,U>::RangeSpecifier(T *dates_1,
                                    T *dates_2,
                                    const U length_index1_,
                                    const U length_index2_) {

  // find size of smaller of the two arguments
  const U bufferSize = length_index1_ < length_index2_ ? length_index1_ : length_index2_;

  // alloc new buffer for dates_, size is smallest of the two arguments
  dates_ = new T[bufferSize];

  // if we can't get memory then print error and return NULL range specifier
  if(dates_==NULL) {
    cerr << "ERROR: RangeSpecifier" << endl;
    cerr << "out of memory" << endl;
    size = 0;
    index1_ = NULL;
    index2_ = NULL;
    dates_ = NULL;
    return;
  }

  // find size of date intersection
  T* dates_end =  set_intersection(dates_1, dates_1+length_index1_, dates_2, dates_2+length_index2_, dates_);

  size = distance(dates_,dates_end);

  // if there is no intersection then specifier has no size, and elements should be set to null
  // must delete buffer of dates_ that we allocated
  if(size==0) {
    delete []dates_;
    index1_ = NULL;
    index2_ = NULL;
    dates_ = NULL;
  }

  // since we have some dates_ in the intersection
  // we can alloc space for the intersection points
  index1_ = new U[size];
  index2_ = new U[size];
	
  // if we cannot get memory, then print error, release any memory that was allocated and return
  if(index1_==NULL || index2_==NULL) {
    cerr << "ERROR: RangeSpecifier::RangeSpecifier" << endl;
    cerr << "out of memory" << endl;
    delete []index1_;
    delete []index2_;
    delete []dates_;
    index1_ = NULL;
    index2_ = NULL;
    dates_ = NULL;
    size = 0;
    return;
  }

  // placeholders to find intersecting dates_
  U date1_index = 0;
  U date2_index = 0;
  U dates_index = 0;

  // go through all the dates_ in the intersection
  while(dates_index < size) {

    // catch up arg 1 to dates_ intersection
    while(dates_[dates_index] != dates_1[date1_index]) {
      date1_index++;
    }

    // catch up arg 2 to dates_ intersection
    while(dates_[dates_index] != dates_2[date2_index]) {
      date2_index++;
    }

    // when equal, record position of matching elements
    if(dates_[dates_index] == dates_1[date1_index] && dates_[dates_index] == dates_2[date2_index]) {
      index1_[dates_index] = date1_index;
      index2_[dates_index] = date2_index;
      dates_index++;
      date1_index++;
      date2_index++;
    }
  }
}

template<typename T, typename U>
const U RangeSpecifier<T,U>::getSize() const {
  return size;
}

template<typename T, typename U>
const T* RangeSpecifier<T,U>::getDates() const {
  return dates_;
}

template<typename T, typename U>
const U* RangeSpecifier<T,U>::getArg1() const {
  return index1_;
}

template<typename T, typename U>
const U* RangeSpecifier<T,U>::getArg2() const {
  return index2_;
}

template<typename T, typename U>
template<typename D, typename BinaryOpp>
void RangeSpecifier<T,U>::applyOpp(D* ans, D* index1_Data, D* index2_Data, BinaryOpp opp) const {
  for(U i = 0; i < size; i++)
    ans[i] = opp( index1_Data[ index1_[i] ] , index2_Data[ index2_[i] ] );
}

template<typename T, typename U>
void RangeSpecifier<T,U>::print() const {
  for(U i = 0; i < size; i++) {
    cout << dates_[i] << ":" << index1_[i] << ":" << index2_[i] << endl;
  }
}

#endif

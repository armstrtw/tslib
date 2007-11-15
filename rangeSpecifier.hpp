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
  T* dates;  // intersection dates
  U* arg1;   // index of intersections of arg1
  U* arg2;   // index of intersections of arg2
  U size;    // also the length of all the internal vectors: dates, arg1, arg2

public:
  ~RangeSpecifier();
  RangeSpecifier(const RangeSpecifier &r); // not allowed!!
  RangeSpecifier();
  RangeSpecifier(T *dates1,
		 T *dates2,
		 const U length_arg1,
		 const U length_arg2);

  const T* getDates();
  const U* getArg1();
  const U* getArg2();
  const U getSize();
  void print();
  
  template<typename D, typename BinaryOpp>
  void applyOpp(D* ans, D* arg1Data, D* arg2Data, BinaryOpp opp);
};

template<typename T, typename U>
RangeSpecifier<T,U>::~RangeSpecifier() {
  delete []dates;
  delete []arg1;
  delete []arg2;
}

template<typename T, typename U>
RangeSpecifier<T,U>::RangeSpecifier() {
  dates = NULL;
  arg1 = NULL;
  arg2 = NULL;
  size = 0;
}

template<typename T, typename U>
RangeSpecifier<T,U>::RangeSpecifier(T *dates1,
                                    T *dates2,
                                    const U length_arg1,
                                    const U length_arg2) {

  // find size of smaller of the two arguments
  const U bufferSize = length_arg1 < length_arg2 ? length_arg1 : length_arg2;

  // alloc new buffer for dates, size is smallest of the two arguments
  dates = new T[bufferSize];

  // if we can't get memory then print error and return NULL range specifier
  if(dates==NULL) {
    cerr << "ERROR: RangeSpecifier" << endl;
    cerr << "out of memory" << endl;
    size = 0;
    arg1 = NULL;
    arg2 = NULL;
    dates = NULL;
    return;
  }

  // find size of date intersection
  T* dates_end =  set_intersection(dates1, dates1+length_arg1, dates2, dates2+length_arg2, dates);

  size = distance(dates,dates_end);

  // if there is no intersection then specifier has no size, and elements should be set to null
  // must delete buffer of dates that we allocated
  if(size==0) {
    delete []dates;
    arg1 = NULL;
    arg2 = NULL;
    dates = NULL;
  }

  // since we have some dates in the intersection
  // we can alloc space for the intersection points
  arg1 = new U[size];
  arg2 = new U[size];
	
  // if we cannot get memory, then print error, release any memory that was allocated and return
  if(arg1==NULL || arg2==NULL) {
    cerr << "ERROR: RangeSpecifier::RangeSpecifier" << endl;
    cerr << "out of memory" << endl;
    delete []arg1;
    delete []arg2;
    delete []dates;
    arg1 = NULL;
    arg2 = NULL;
    dates = NULL;
    size = 0;
    return;
  }

  // placeholders to find intersecting dates
  U date1_index = 0;
  U date2_index = 0;
  U dates_index = 0;

  // go through all the dates in the intersection
  while(dates_index < size) {

    // catch up arg 1 to dates intersection
    while(dates[dates_index] != dates1[date1_index]) {
      date1_index++;
    }

    // catch up arg 2 to dates intersection
    while(dates[dates_index] != dates2[date2_index]) {
      date2_index++;
    }

    // when equal, record position of matching elements
    if(dates[dates_index] == dates1[date1_index] && dates[dates_index] == dates2[date2_index]) {
      arg1[dates_index] = date1_index;
      arg2[dates_index] = date2_index;
      dates_index++;
      date1_index++;
      date2_index++;
    }
  }
}

template<typename T, typename U>
const U RangeSpecifier<T,U>::getSize() {
  return size;
}

template<typename T, typename U>
const T* RangeSpecifier<T,U>::getDates() {
  return dates;
}

template<typename T, typename U>
const U* RangeSpecifier<T,U>::getArg1() {
  return arg1;
}

template<typename T, typename U>
const U* RangeSpecifier<T,U>::getArg2() {
  return arg2;
}

template<typename T, typename U>
template<typename D, typename BinaryOpp>
void RangeSpecifier<T,U>::applyOpp(D* ans, D* arg1Data, D* arg2Data, BinaryOpp opp) {
  for(U i = 0; i < size; i++)
    ans[i] = opp( arg1Data[ arg1[i] ] , arg2Data[ arg2[i] ] );
}

template<typename T, typename U>
void RangeSpecifier<T,U>::print() {
  for(U i = 0; i < size; i++) {
    cout << dates[i] << ":" << arg1[i] << ":" << arg2[i] << endl;
  }
}

#endif

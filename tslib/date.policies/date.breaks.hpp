#ifndef PERIOD_BREAKS
#define PERIOD_BREAKS

#include <algorithm>
#include <iterator>

namespace tslib {

template<template<typename> class DatePolicy,
         typename TSDIM,
         typename T,
         template<typename U, typename = std::allocator<U> > class COLL>
void QuarterlyBreaks(T beg, T end, COLL<TSDIM>& coll) {
  typedef typename std::iterator_traits<T>::value_type value_type;

  T next = beg + 1;
  TSDIM i = 0;

  while(beg != (end - 1) ) {
    //cout << DatePolicy<value_type>::month(*beg) << endl;
    // end of quarter
    if(DatePolicy<value_type>::month(*beg) % 3 == 0
       &&
       // diffferent month or different year is next
       (DatePolicy<value_type>::month(*beg) != DatePolicy<value_type>::month(*next) ||
        DatePolicy<value_type>::year(*beg) != DatePolicy<value_type>::year(*next) )
       )
      {
        back_inserter(coll) = i;
      }
    ++i;
    ++beg;
    ++next;
  }
  // last element is always in
  back_inserter(coll) = i;
}

}  // namespace tslib

#endif // PERIOD_BREAKS

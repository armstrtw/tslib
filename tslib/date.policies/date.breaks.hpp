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
    // end of quarter
    if(DatePolicy<value_type>::month(*beg) % 3 == 0
       && // and diffferent month or different year is next
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

template<template<typename> class DatePolicy,
         typename TSDIM,
         typename T,
         template<typename U, typename = std::allocator<U> > class COLL>
void MonthlyBreaks(T beg, T end, COLL<TSDIM>& coll) {
  typedef typename std::iterator_traits<T>::value_type value_type;

  T next = beg + 1;
  TSDIM i = 0;

  while(beg != (end - 1) ) {

    if(// diffferent month or different year is next
       DatePolicy<value_type>::month(*beg) != DatePolicy<value_type>::month(*next) ||
       DatePolicy<value_type>::year(*beg) != DatePolicy<value_type>::year(*next) )
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

template<template<typename> class DatePolicy,
         typename TSDIM,
         typename T,
         template<typename U, typename = std::allocator<U> > class COLL>
void WeeklyBreaks(T beg, T end, COLL<TSDIM>& coll) {
  typedef typename std::iterator_traits<T>::value_type value_type;

  T next = beg + 1;
  TSDIM i = 0;

  while(beg != (end - 1) ) {

    if(
       // day of week > next day of week
       DatePolicy<value_type>::dayofweek(*beg) > DatePolicy<value_type>::dayofweek(*next) ||
       // because dates can be sparse, if we travel more than 7 days, then it's a new week
       DatePolicy<value_type>::daily_distance(*beg, *next) >= 7
       ) {
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

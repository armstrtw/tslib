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

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

#ifndef DATE_PARTITION
#define DATE_PARTITION

#include <algorithm>
#include <iterator>

namespace tslib {

  template<template<typename> class DatePolicy, template<class, template<typename> class> class PFUNC, typename T, typename U>
  void calcPartitionRanges(T beg, T end, U oiter) {
    typedef typename std::iterator_traits<T>::difference_type DT;
    typedef typename std::iterator_traits<T>::value_type VT;

    typename std::vector<VT> partitions;
    typename std::vector<VT> unique_partitions;
    //typedef std::vector<VT>::iterator partition_iter;

    partitions.resize(std::distance(beg, end));
    std::transform(beg, end, partitions.begin(), PFUNC<VT, DatePolicy>());
    std::unique_copy(partitions.begin(), partitions.end(), std::inserter(unique_partitions,unique_partitions.begin()));
    typename std::vector<VT>::iterator pbeg = partitions.begin();
    typename std::vector<VT>::iterator siter = pbeg;
    typename std::vector<VT>::iterator eiter;

    for(typename std::vector<VT>::iterator p = unique_partitions.begin(); p != unique_partitions.end() - 1; p++) {
      eiter = std::find(siter, partitions.end(), *(p+1));
      *oiter++ = std::pair<DT, DT>(std::distance(pbeg,siter), std::distance(pbeg,eiter));
      siter = eiter;
    }
    // last row
    *oiter = std::pair<DT, DT>(std::distance(pbeg,siter),std::distance(pbeg,partitions.end()));
  }

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymm {
  public:
    yyyymm() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmdd {
  public:
    yyyymmdd() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHH {
  public:
    yyyymmddHH() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHHMM {
  public:
    yyyymmddHHMM() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date), DatePolicy<T>::minute(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHHMMSS {
  public:
    yyyymmddHHMMSS() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date), DatePolicy<T>::minute(date), DatePolicy<T>::second(date));
    }
  };

}  // namespace tslib

#endif // DATE_PARTITION

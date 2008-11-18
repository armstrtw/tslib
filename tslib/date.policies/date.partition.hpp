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

  template<typename PTYPE, template<typename> class DatePolicy, template<class, template<typename> class, class> class PFUNC, typename T, typename U>
  void calcPartitionRanges(T beg, T end, U oiter) {
    typedef typename std::vector<PTYPE>::iterator partition_iter;
    typedef typename std::iterator_traits<partition_iter>::difference_type DT;
    typedef typename std::iterator_traits<T>::value_type VT;

    typename std::vector<PTYPE> partitions;
    typename std::vector<PTYPE> unique_partitions;

    partitions.resize(std::distance(beg, end));
    std::transform(beg, end, partitions.begin(), PFUNC<VT, DatePolicy, PTYPE>());
    std::unique_copy(partitions.begin(), partitions.end(), std::inserter(unique_partitions,unique_partitions.begin()));
    partition_iter pbeg = partitions.begin();
    partition_iter siter = pbeg;
    partition_iter eiter;

    for(partition_iter p = unique_partitions.begin(); p != unique_partitions.end() - 1; p++) {
      eiter = std::find(siter, partitions.end(), *(p+1));
      *oiter++ = std::pair<DT, DT>(std::distance(pbeg,siter), std::distance(pbeg,eiter));
      siter = eiter;
    }
    // last row
    *oiter = std::pair<DT, DT>(std::distance(pbeg,siter),std::distance(pbeg,partitions.end()));
  }

  template<typename T,
           template<typename> class DatePolicy,
           typename ReturnType>
  class yyyymm {
  public:
    yyyymm() {}
    ReturnType operator()(const T date) {
      return DatePolicy<T>::year(date) * 100  + DatePolicy<T>::month(date);
    }
  };
}  // namespace tslib

#endif // DATE_PARTITION

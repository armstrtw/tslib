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

#ifndef EMA_HPP
#define EMA_HPP

#include <iterator>
#include <tslib/vector.summary/mean.hpp>

namespace tslib {


  template<typename ReturnType>
  class EMA {
  public:
    template<typename T, typename U, typename V>
    static inline void apply(T dest, U beg, U end, V periods) {
      const double p = static_cast<double>(periods);
      ReturnType initial_value = Mean<ReturnType>::apply(beg,beg+periods);

      // fill with NA until we have initial window
      int initial_count = 0;
      while(initial_count < (periods - 1)  && beg != end) {
        *dest++ = numeric_traits<ReturnType>::NA();
        ++beg;
        ++initial_count;
      }
      *dest++ = initial_value;
      ++beg;

      while(beg != end) {
	if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
	  *dest = numeric_traits<typename std::iterator_traits<T>::value_type>::NA();
	} else {
	  *dest = (*(dest-1) * (p - 1.0) + *beg)/p;
	}
	++beg;
	++dest;
      }
    }
  };

} // namespace tslib

#endif // EMA_HPP

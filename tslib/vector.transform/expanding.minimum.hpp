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

#ifndef EXPANDING_MINIMUM_HPP
#define EXPANDING_MINIMUM_HPP

#include <iterator>

namespace tslib {

  template<typename ReturnType>
  class ExpandingMinimum {
  public:
    template<typename T, typename U>
    static inline void apply(T dest, U beg, U end) {

      // fill with NA until we have values
      while(numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*beg) && beg != end) {
        *dest++ = numeric_traits<ReturnType>::NA();
        ++beg;
      }
      
      // init first value
      ReturnType running_max = *beg++;
      *dest++ = running_max;

      while(beg != end) {
        running_max = std::min(*beg,running_max);
        *dest = running_max;

	++beg;
	++dest;
      }
    }
  };

} // namespace tslib

#endif // EXPANDING_MINIMUM_HPP

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

#ifndef SINCE_NA_HPP
#define SINCE_NA_HPP

#include <iterator>

namespace tslib {

  template<typename ReturnType>
  class SinceNA {
  public:
    template<typename T, typename U>
    static inline void apply(T dest, U beg, U end) {

      typedef typename std::iterator_traits<T>::value_type dest_type;

      dest_type count(0);

      // while no NA is found at all in the tseries then -1
      while(beg != end && !numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*beg) ) {
        *dest = static_cast<dest_type>(-1);
        ++beg;
        ++dest;
      }

      // if we get here, then an NA has been found
      while(beg != end) {
        if(numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*beg)) {
          *dest = static_cast<dest_type>(0);
          count = 0;
        } else {
          *dest = count;
        }
        ++count;
        ++beg;
        ++dest;
      }
    }
  };
} // namespace tslib

#endif // SINCE_NA_HPP

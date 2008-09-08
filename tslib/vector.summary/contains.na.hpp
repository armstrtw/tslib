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

#ifndef CONTAINS_NA_HPP
#define CONTAINS_NA_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename T>
  static inline bool containsNA(T beg, T end) {
    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return true;
      }
      ++beg;
    }
    return false;
  };
} // namespace tslib

#endif // CONTAINS_NA_HPP

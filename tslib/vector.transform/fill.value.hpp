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

#ifndef FILL_VALUE_HPP
#define FILL_VALUE_HPP

#include <iterator>

namespace tslib {

  template<typename ReturnType>
  class FillValue {
  public:
    template<typename T, typename U, typename V>
    static inline void apply(T dest, U beg, U end, V value) {

      while(beg != end) {
	if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
	  *dest = static_cast< typename std::iterator_traits<T>::value_type >(value);
	} else {
	  *dest = *beg;
	}
	++beg;
	++dest;
      }
    }
  };

} // namespace tslib

#endif // FILL_VALUE_HPP

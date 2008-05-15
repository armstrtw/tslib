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

#ifndef FILL_FWD_HPP
#define FILL_FWD_HPP

#include <iterator>

namespace tslib {

  template<typename ReturnType>
  class FillFwd {
  public:
    template<typename T, typename U>
    static inline void apply(T dest, U beg, U end) {

      // nothing we can do about elelment [0]
      *dest++ = *beg++;

      while(beg != end) {
	if(numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*beg)) {
	  *dest = *(dest - 1);
	} else {
	  *dest = *beg;
	}
	++beg;
	++dest;
      }
    }
  };

} // namespace tslib

#endif // FILL_FWD_HPP

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

#ifndef FILL_BWD_HPP
#define FILL_BWD_HPP

#include <iterator>

namespace tslib {

  template<typename ReturnType>
  class FillBwd {
  public:
    template<typename T, typename U>
    static inline void apply(T dest, U beg, U end) {

      // have to find offset to start from back
      typename std::iterator_traits<U>::difference_type len =  distance(beg,end);

      // push beg off end of array since we are comming towards it
      --beg;

      // shift dest to element N-1
      dest += (len - 1);

      // end is beyond array right now
      --end;
      //cout << *end << endl;

      // set last element to value of end
      *dest-- = *end--;


      while(end != beg) {
	if(numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*end)) {
	  *dest = *(dest + 1);
	} else {
	  *dest = *end;
	}
	--dest;
	--end;
      }
    }
  };

} // namespace tslib

#endif // FILL_BWD_HPP

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

#ifndef LEAD_HPP
#define LEAD_HPP

#include <algorithm>

namespace tslib {

  template<typename ReturnType>
  class Lead {
  public:
    template<typename T, typename U, typename V>
    static inline void apply(T dest, U beg, U end, V periods) {

      beg+=periods;

      if(beg < end)
	std::copy(beg, end, dest);

      // advance dest to beginning of NA's
      dest += std::distance(beg,end);

      // set tail values to NA
      for(V i = 0; i < periods; i++, dest++)
	*dest = numeric_traits<ReturnType>::NA();
    }
  };

} // namespace tslib

#endif // LEAD_HPP

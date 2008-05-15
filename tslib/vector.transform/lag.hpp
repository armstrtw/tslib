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

#ifndef LAG_HPP
#define LAG_HPP

#include <algorithm>

namespace tslib {

  template<typename ReturnType>
  class Lag {
  public:
    template<typename T, typename U, typename V>
    static inline void apply(T dest, U beg, U end, V periods) {

      // set head to NA
      for(V i = 0; i < periods; i++, dest++, end--)
	*dest = numeric_traits<ReturnType>::NA();

      if( end > beg )
	std::copy(beg, end, dest);
    }
  };

} // namespace tslib

#endif // LAG_HPP

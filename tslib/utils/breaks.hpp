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

#ifndef BREAKS_HPP
#define BREAKS_HPP

namespace tslib {

  template<typename T, typename U>
  void breaks(T beg, T end, U ans) {
    T original_beg = beg;
    // FIXME: check beg==end
    // advance one position
    while(beg != (end - 1)) {
      if(*beg != *(beg+1)) {
        ans = std::distance(original_beg, beg);
      }
      ++beg;
    }
    ans = std::distance(original_beg, end) - 1;
  }
}

#endif // BREAKS_HPP

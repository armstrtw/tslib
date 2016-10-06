///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016  Whit Armstrong                                    //
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
#pragma once
#include <vector>
#include <utility>
#include <algorithm>

namespace tslib {

template <typename T>
std::pair<std::vector<size_t>, std::vector<size_t>> intersection_map(T xbeg, T xend, T ybeg, T yend) {
  typename std::iterator_traits<T>::difference_type max_size{
      std::min(std::distance(xbeg, xend), std::distance(ybeg, yend))};
  std::vector<size_t> xmap, ymap;
  xmap.reserve(max_size);
  ymap.reserve(max_size);
  size_t xpos{0}, ypos{0};

  while (xbeg != xend && ybeg != yend) {
    if (*xbeg < *ybeg) {
      ++xbeg;
      ++xpos;
    } else if (*ybeg < *xbeg) {
      ++ybeg;
      ++ypos;
    } else {
      xmap.push_back(xpos);
      ymap.push_back(ypos);
      ++xbeg;
      ++xpos;
      ++ybeg;
      ++ypos;
    }
  }
  return make_pair(xmap, ymap);
}

} // namespace tslib

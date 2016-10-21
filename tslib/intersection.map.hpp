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
#include <algorithm>
#include <utility>
#include <vector>

namespace tslib {

template <typename T> std::vector<std::pair<size_t, size_t>> intersection_map(T xbeg, T xend, T ybeg, T yend) {
  // max size of intersection is the smaller of the two series
  typename std::iterator_traits<T>::difference_type max_size{
      std::min(std::distance(xbeg, xend), std::distance(ybeg, yend))};
  std::vector<std::pair<size_t, size_t>> res;
  res.reserve(max_size);
  T xp{xbeg}, yp{ybeg};

  while (xp != xend && yp != yend) {
    if (*xp < *yp) {
      ++xp;
    } else if (*yp < *xp) {
      ++yp;
    } else {
      res.push_back(std::make_pair(std::distance(xbeg, xp), std::distance(ybeg, yp)));
      ++xp;
      ++yp;
    }
  }
  return res;
}

} // namespace tslib

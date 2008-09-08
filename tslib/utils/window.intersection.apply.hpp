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

#ifndef WINDOW_INTERSECTION_APPLY_HPP
#define WINDOW_INTERSECTION_APPLY_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename ReturnType,
	   template<class> class F>
  class windowIntersectionApply {
  public:
    template<typename T, class DataIter, typename TSDIM>
    static inline void apply(T ans, DataIter x_iter, DataIter y_iter, TSDIM size, const size_t window) {

      std::advance(x_iter, window - 1);
      std::advance(y_iter, window - 1);

      for(TSDIM i = (window-1); i < size; i++) {
	*ans = F<ReturnType>::apply(x_iter-(window-1),x_iter+1,y_iter-(window-1),y_iter+1);
	++x_iter;
	++y_iter;
	++ans;
      }
    }
  };
} // namespace tslib

#endif // WINDOW_INTERSECTION_APPLY_HPP

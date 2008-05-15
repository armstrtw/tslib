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

#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename ReturnType,
	   template<class> class F>
  class windowIntersectionApply {
  public:
    template<typename T, class DataIter, typename TSDIM>
    static inline void apply(T ans, DataIter x_iter, DataIter y_iter, TSDIM size, const int window) {

      // if window is bigger than len, return all NA
      if(size < static_cast<TSDIM>(window)) {
	for(TSDIM i = 0; i < size; i++) {
	  *ans = numeric_traits<ReturnType>::NA();
	  ++ans;
	}
	return;
      }

      // set 1st (N-1) to NA
      for(int i = 1; i < window; i++, x_iter++, y_iter++, ans++) {
	*ans = numeric_traits<ReturnType>::NA();
      }

      // apply fun to rest
      // FIXME: check this range to make sure it's right
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

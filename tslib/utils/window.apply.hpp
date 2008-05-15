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

#ifndef WINDOW_APPLY_HPP
#define WINDOW_APPLY_HPP

#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename ReturnType,
	   template<class> class F>
  class windowApply {
  public:
    template<typename T, typename U>
    static inline void apply(T ans, U beg, U end, const int window) {

      // if window is bigger than len, return all NA
      if(static_cast<int>(distance(beg,end)) < window) {
	while(beg != end) {
	  *ans = numeric_traits<ReturnType>::NA();
	  ++ans;
	  ++beg;
	}
	return;
      }

      // set 1st (N-1) to NA
      for(int i = 1; i < window; i++, beg++, ans++) {
	*ans = numeric_traits<ReturnType>::NA();
      }

      // apply fun to rest
      while(beg != end) {
	*ans = F<ReturnType>::apply(beg-(window-1),beg+1);
	++beg;
	++ans;
      }
    }
  };

} // namespace tslib

#endif // WINDOW_APPLY_HPP

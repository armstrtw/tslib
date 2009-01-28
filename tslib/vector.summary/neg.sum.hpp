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

#ifndef NEG_SUM_HPP
#define NEG_SUM_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename T>
  class negSumTraits;

  template<>
  class negSumTraits<double> {
  public:
    typedef double ReturnType;
  };

  template<>
  class negSumTraits<int> {
  public:
    typedef int ReturnType;
  };


  template<typename ReturnType>
  class NegSum {
  public:
    template<typename T>
    static inline ReturnType apply(T beg, T end) {
      ReturnType ans = 0;

      while(beg != end) {
	if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
	  return numeric_traits<ReturnType>::NA();
	}
	ans += *beg < 0 ? std::abs(*beg) : 0;
	++beg;
      }
      return ans;
    }
  };

} // namespace tslib

#endif // NEG_SUM_HPP

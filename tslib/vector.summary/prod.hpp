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

#ifndef PROD_HPP
#define PROD_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename T>
  class prodTraits;

  template<>
  class prodTraits<double> {
  public:
    typedef double ReturnType;
  };

  template<>
  class prodTraits<int> {
  public:
    typedef int ReturnType;
  };


  template<typename ReturnType>
  class Prod {
  public:
    template<typename T>
    static inline ReturnType apply(T beg, T end) {
      ReturnType ans = static_cast<ReturnType>( 1 );

      while(beg != end) {
	if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
	  return numeric_traits<ReturnType>::NA();
	}
	ans *= *beg;
	++beg;
      }
      return ans;
    }
  };

} // namespace tslib

#endif // PROD_HPP

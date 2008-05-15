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

#ifndef COR_HPP
#define COR_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>
#include <tslib/vector.summary/stdev.hpp>

namespace tslib {

  template<typename T>
  class corTraits;

  template<>
  class corTraits<double> {
  public:
    typedef double ReturnType;
  };

  template<>
  class corTraits<int> {
  public:
    typedef double ReturnType;
  };


  template<typename ReturnType>
  class Cor {
  public:
    template<typename T>
    static inline ReturnType apply(T x_beg, T x_end, T y_beg, T y_end) {

      ReturnType xy_cov = Cov<ReturnType>::apply(x_beg, x_end, y_beg, y_end);

      if(numeric_traits<ReturnType>::ISNA(xy_cov)) {
	return numeric_traits<ReturnType>::NA();
      }

      ReturnType x_sd = Stdev<ReturnType>::apply(x_beg, x_end);
      ReturnType y_sd = Stdev<ReturnType>::apply(y_beg, y_end);

      return xy_cov / ( x_sd * y_sd );
    }
  };

} // namespace tslib

#endif // COR_HPP

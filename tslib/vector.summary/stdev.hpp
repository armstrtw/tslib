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

#ifndef STDEV_HPP
#define STDEV_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename T>
  class stdevTraits;

  template<>
  class stdevTraits<double> {
  public:
    typedef double ReturnType;
  };

  template<>
  class stdevTraits<int> {
  public:
    typedef double ReturnType;
  };


  template<typename ReturnType>
  class Stdev {
  public:
    template<typename T>
    static inline ReturnType apply(T beg, T end) {
      ReturnType ans = 0;
      ReturnType len =  static_cast<ReturnType>(std::distance(beg,end));

      // can't take stdev of only 1 element
      if(len <= 1) {
	return numeric_traits<ReturnType>::NA();
      }

      ReturnType vec_mean = Mean<ReturnType>::apply(beg,end);

      // check NA of mean
      if(numeric_traits<ReturnType>::ISNA(vec_mean)) {
	return numeric_traits<ReturnType>::NA();
      }

      while(beg != end) {
	ans += std::pow(*beg - vec_mean, 2);
	++beg;
      }
      return std::pow( ans/(len - 1), 0.5);
    }
  };

} // namespace tslib

#endif // STDEV_HPP

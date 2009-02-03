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

#ifndef RSI_HPP
#define RSI_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename T>
  class rsiTraits;

  template<>
  class rsiTraits<double> {
  public:
    typedef double ReturnType;
  };

  template<>
  class rsiTraits<int> {
  public:
    typedef double ReturnType;
  };

  template<typename ReturnType>
  class RSI {
  public:
    template<typename T>
    static inline ReturnType apply(T beg, T end) {
      ReturnType pos_count = 0;
      ReturnType neg_count = 0;
      ReturnType pos_sum = 0;
      ReturnType neg_sum = 0;
      double avg_gain = 0;
      double avg_loss = 0;

      if(numeric_traits<ReturnType>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }
      if(*beg > 0) {
        ++pos_count;
        pos_sum += *beg;
      }
      if(*beg < 0) {
        ++neg_count;
        neg_sum += std::abs(*beg);
      }
      if(pos_count) {
        avg_gain = pos_sum/pos_count;
      }
      if(neg_count) {
        avg_loss = neg_sum/neg_count;
      }
      return 100.0 - 100.0 / (1.0 + avg_gain/avg_loss);
    }
  };


} // namespace tslib

#endif // RSI_HPP

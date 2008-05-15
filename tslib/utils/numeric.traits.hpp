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

#ifndef NUMERIC_TRAITS_HPP
#define NUMERIC_TRAITS_HPP

#include <limits>
#include <cmath>

namespace tslib {

  // to be conformant to R's NA value
  typedef union {
    double value;
    unsigned int word[2];
  } ieee_type;


  template<typename T>
  class numeric_traits;

  template<>
  class numeric_traits<double> {
  private:
    static double calculate_NA() {
      volatile ieee_type ans_ieee;

      // do this b/c don't have a good way to determine
      // endianness at compile time
      double ans = std::numeric_limits<double>::quiet_NaN();

      ans_ieee.value = ans;

      if( ans_ieee.word[0] == 0 ) {
        ans_ieee.word[0] = 1954;
      } else {
        ans_ieee.word[1] = 1954;
      }

      return ans_ieee.value;
    }

  public:
    static const bool has_NA = true;

    static inline double NA() {
      static double na_value = calculate_NA();
      return na_value;
    }

    static inline bool ISNA(double x) {
      return std::isnan(x);
    }
  };

  template<>
  class numeric_traits<int> {
  public:
    static const bool has_NA = true;

    static inline int NA() {
      return std::numeric_limits<int>::min();
    }

    static inline bool ISNA(int x) {
      return x == std::numeric_limits<int>::min() ? true : false;
    }
  };

}  // namespace tslib

#endif //NUMERIC_TRAITS_HPP

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
#include <limits>
#include <cmath>

template <typename T> class RNT;

template <> class RNT<double> {
private:
  // to be conformant to R's NA value
  static double calculate_NA() {
    union {
      double value;
      unsigned int word[2];
    };
    // do this b/c don't have a good way to determine
    // endianness at compile time
    value = std::numeric_limits<double>::quiet_NaN();

    if (word[0] == 0) {
      word[0] = 1954;
    } else {
      word[1] = 1954;
    }

    return value;
  }

public:
  static const bool has_NA = true;

  static inline double NA() {
    static double na_value = calculate_NA();
    return na_value;
  }

  static inline bool ISNA(double x) { return std::isnan(x); }
};

template <> class RNT<int> {
public:
  static const bool has_NA = true;

  static inline int NA() { return std::numeric_limits<int>::min(); }

  static inline bool ISNA(int x) { return x == std::numeric_limits<int>::min() ? true : false; }
};

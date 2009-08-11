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

#ifndef DATE_PARTITION
#define DATE_PARTITION

#include <algorithm>
#include <iterator>

namespace tslib {

  template<typename T,
           template<typename> class DatePolicy>
  class yyyy {
  public:
    yyyy() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), 1, 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyyqq {
  public:
    yyyyqq() {}
    T operator()(const T date) {
      int adj_month = (static_cast<int>((DatePolicy<T>::month(date) - 1)/3) + 1) * 3 - 2;
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), adj_month, 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymm {
  public:
    yyyymm() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmdd {
  public:
    yyyymmdd() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHH {
  public:
    yyyymmddHH() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHHMM {
  public:
    yyyymmddHHMM() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date), DatePolicy<T>::minute(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHHMMSS {
  public:
    yyyymmddHHMMSS() {}
    T operator()(const T date) {
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date), DatePolicy<T>::minute(date), DatePolicy<T>::second(date));
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyyww {
  public:
    yyyyww() {}
    T operator()(const T date) {
      int adj = 6 - DatePolicy<T>::dayofweek(date);
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date) + adj);
    }
  };

}  // namespace tslib

#endif // DATE_PARTITION

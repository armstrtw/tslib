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
    T operator()(const T date, const int n) {
      int year = DatePolicy<T>::year(date);
      return DatePolicy<T>::toDate(year - year % n, 1, 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyyqq {
  public:
    yyyyqq() {}
    T operator()(const T date, const int n) {
      int adj_month = (static_cast<int>((DatePolicy<T>::month(date) - 1)/3) + 1) * 3 - 2;
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), adj_month - adj_month % n, 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymm {
  public:
    yyyymm() {}
    T operator()(const T date, const int n) {
      int month = DatePolicy<T>::month(date);
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), month - month % n, 1);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmdd {
  public:
    yyyymmdd() {}
    T operator()(const T date, const int n) {
      int day = DatePolicy<T>::dayofmonth(date);
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), day - day % n);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHH {
  public:
    yyyymmddHH() {}
    T operator()(const T date, const int n) {
      int hour = DatePolicy<T>::hour(date);
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), hour - hour % n);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHHMM {
  public:
    yyyymmddHHMM() {}
    T operator()(const T date, const int n) {
      int minute = DatePolicy<T>::minute(date);
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date), minute - minute % n);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyymmddHHMMSS {
  public:
    yyyymmddHHMMSS() {}
    T operator()(const T date, const int n) {
      int second = DatePolicy<T>::second(date);
      return DatePolicy<T>::toDate(DatePolicy<T>::year(date), DatePolicy<T>::month(date), DatePolicy<T>::dayofmonth(date), DatePolicy<T>::hour(date), DatePolicy<T>::minute(date), second - second % n);
    }
  };

  template<typename T,
           template<typename> class DatePolicy>
  class yyyyww {
  public:
    yyyyww() {}
    T operator()(const T date, const int n) {
      return DatePolicy<T>::AddDays(date,6 - DatePolicy<T>::dayofweek(date));
    }
  };

}  // namespace tslib

#endif // DATE_PARTITION

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

#ifndef JULIAN_DATE_POLICY_HPP
#define JULIAN_DATE_POLICY_HPP

namespace tslib {

  template<typename T>
  class JulianDate {
  public:
    static const T toDate(const char* date, const char* format);
    static const T toDate(const int year, const int month, const int day, const int hour, const int minute, const int second);
    static const std::string toString(const T x, const char* format);
    static const int dayofweek(const T x);
    static const int dayofmonth(const T x);
    static const int month(const T x);
    static const int year(const T x);
    static const int last_day_of_month(const T x);
    static const T AddYears(const T x, const int n);
    static const T AddMonths(const T x, const int n);
    static const T AddDays(const T x, const int n);
  };

} // namespace tslib

#endif // JULIAN_DATE_POLICY_HPP

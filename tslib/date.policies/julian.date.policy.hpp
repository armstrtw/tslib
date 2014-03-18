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
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace tslib {

  template<typename T>
  class JulianDate {
  private:
    //static const boost::gregorian::date fromRDate(const T x) { return boost::gregorian::date(1970,1,1) + boost::gregorian::date_duration(x); }
    static const boost::gregorian::date fromRDate(const T x) { return boost::gregorian::date(1970,1,1) + boost::gregorian::days(x); }
    static const T toRDate(const boost::gregorian::date x) { return static_cast<int>(boost::gregorian::date_period(boost::gregorian::date(1970,1,1),x).length().days()); }
  public:
    //static const T toDate(const char* date, const char* format);
    static const T toDate(const int year, const int month, const int day, const int hour = 0, const int minute = 0, const int second = 0, const int millisecond = 0) { return toRDate(boost::gregorian::date(year, month, day)); }
    static const std::string toString(const T x, const char* format);
    static const int second(const T x) { return 0; }
    static const int minute(const T x) { return 0; }
    static const int hour(const T x) { return 0; }
    static const int dayofweek(const T x) { return static_cast<int>(fromRDate(x).day_of_week()); }
    static const int dayofmonth(const T x) { return static_cast<int>(fromRDate(x).day()); }
    static const int month(const T x)  { return static_cast<int>(fromRDate(x).month()); }
    static const int year(const T x)   { return static_cast<int>(fromRDate(x).year()); }
    static const int last_day_of_month(const T x) { return toRDate(fromRDate(x).end_of_month()); }
    static const T AddYears(const T x, const int n) { return toRDate(fromRDate(x) + boost::gregorian::years(n)); }
    static const T AddMonths(const T x, const int n) { return toRDate(fromRDate(x) + boost::gregorian::months(n)); }
    static const T AddDays(const T x, const int n) { return toRDate(fromRDate(x) + boost::gregorian::days(n)); }
    static const double daily_distance(const T x, const T y) { return x - y; }
  };

} // namespace tslib



#endif // JULIAN_DATE_POLICY_HPP

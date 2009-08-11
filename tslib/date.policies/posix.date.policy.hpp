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

#ifndef POSIX_DATE_POLICY_HPP
#define POSIX_DATE_POLICY_HPP

#include <string.h>
#include <ctime>

namespace tslib {


  template<typename T>
  class PosixDate {
  private:
    static void to_time_tm(struct tm& posix_time_tm, const T x);
    static void check_day_of_month(struct tm& posix_time_tm); // needs to check for leapyears too
    static const int dst_shift_check(const T ans,const T x); // returns seconds from original hour and minute that has occurred
    static const bool is_leap_year(const int year);
  public:
    static const T toDate(const char* date, const char* format);
    static const T toDate(const int year, const int month, const int day, const int hour = 0, const int minute = 0, const int second = 0, const int millisecond = 0);
    static const std::string toString(const T x, const char* format);
    static const int second(const T x);
    static const int minute(const T x);
    static const int hour(const T x);
    static const int dayofweek(const T x);
    static const int dayofmonth(const T x);
    static const int month(const T x);
    static const int year(const T x);
    static const int last_day_of_month(const T x);
    static const T AddYears(const T x, const int n);
    static const T AddMonths(const T x, const int n);
    static const T AddDays(const T x, const int n);
    static const double daily_distance(const T x, const T y);
  };

  template<typename T>
  void PosixDate<T>::to_time_tm(struct tm& posix_time_tm, const T x) {
    const time_t posix_time_t = static_cast<time_t>(x);
#ifdef WIN32
    memcpy(static_cast<void*>(&posix_time_tm),localtime(&posix_time_t), sizeof(struct tm));
#else
    localtime_r(&posix_time_t,&posix_time_tm);
#endif
  }

  // does not check for negative months, only running off the back of a month
  template<typename T>
  void PosixDate<T>::check_day_of_month(struct tm& posix_time_tm) {

    if(posix_time_tm.tm_mday < 28) {
      return;
    }

    // tm_mon is 0 to 11
    switch(posix_time_tm.tm_mon + 1) {

      // case for Apr, June, Sep, Nov (30 day months)
    case 4:
    case 6:
    case 9:
    case 11:
      posix_time_tm.tm_mday =  (posix_time_tm.tm_mday > 30) ? 30 : posix_time_tm.tm_mday;
      break;

      /* Do we need these cases?  there is no way of creating a day of month 32 from the
	 methods that would call this check, so don't do it.

	 // case for Jan, March, May, July, Aug, Oct, Dec
	 case 1:
	 case 3:
	 case 5:
	 case 7:
	 case 8:
	 case 10:
	 case 12:
	 posix_time_tm.tm_mday =  (posix_time_tm.tm_mday > 31) ? 31 : posix_time_tm.tm_mday;
	 break;
      */
      // special case for feb
    case 2:
      if(is_leap_year(posix_time_tm.tm_year + 1900)) {
	posix_time_tm.tm_mday =  (posix_time_tm.tm_mday > 29) ? 29 : posix_time_tm.tm_mday;
      } else {
	posix_time_tm.tm_mday =  (posix_time_tm.tm_mday > 28) ? 28 : posix_time_tm.tm_mday;
      }
      break;
    }
  }

  template<typename T>
  const int PosixDate<T>::dst_shift_check(const T shifted, const T original) {
    struct tm original_time_tm, shifted_time_tm;

    to_time_tm(original_time_tm, original);
    to_time_tm(shifted_time_tm, shifted);

    // hour = 60s/min * 60min = 3600 seconds
    int ans = (original_time_tm.tm_hour - shifted_time_tm.tm_hour) * 3600;

    // some zones have half hour shifts
    ans += (original_time_tm.tm_min - shifted_time_tm.tm_min) * 60;

    return ans;
  }

  // takes a year in the form YYYY
  // so you must add 1900 to tm_year before calling this func
  template<typename T>
  const bool PosixDate<T>::is_leap_year(const int year) {
    int mod_4 = year % 4;
    int mod_100 = year % 100;
    int mod_400 = year % 400;

    // mod_400 or mod_4 but not mod_100
    return (mod_400 == 0 || (mod_4 && !(mod_100) ) ) ? 1 : 0;
  }

#ifndef WIN32
  /* strptime not available on windows */
  template<typename T>
  const T PosixDate<T>::toDate(const char* date, const char* format) {
    struct tm posix_time_tm;
    memset(&posix_time_tm, '\0', sizeof(struct tm));
    strptime(date,format,&posix_time_tm);
    posix_time_tm.tm_isdst = -1;
    return static_cast<T>(mktime(&posix_time_tm));
  }
#endif

  template<typename T>
  const T PosixDate<T>::toDate(const int year, const int month, const int day, const int hour, const int minute, const int second, const int millisecond) {

    struct tm localtime_tm;

    // init struct
    memset(&localtime_tm, '\0', sizeof(struct tm));

    // for years, 1970 is 70
    localtime_tm.tm_year = year - 1900;

    // months are 0 to 11
    localtime_tm.tm_mon = month - 1;

    // day of month is 1 to 31
    localtime_tm.tm_mday = day;

    localtime_tm.tm_hour = hour;
    localtime_tm.tm_min = minute;
    localtime_tm.tm_sec = second;

    // have to do this so mktime will fix the dst field
    // do not remove this (it works)
    localtime_tm.tm_isdst = -1;

    // convert to POSIXct
    return static_cast<T>(mktime(&localtime_tm)) + static_cast<T>(millisecond/1000.0);
  }

  template<typename T>
  const std::string PosixDate<T>::toString(const T x, const char* format) {
    struct tm posix_time_tm;
    const int BUFFSIZE = 32;
    char ans_char[BUFFSIZE];
    to_time_tm(posix_time_tm, x);
    strftime(ans_char,BUFFSIZE,format,&posix_time_tm);
    return std::string(ans_char);
  }

  template<typename T>
  const int PosixDate<T>::second(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_sec;
  }

  template<typename T>
  const int PosixDate<T>::minute(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_min;
  }

  template<typename T>
  const int PosixDate<T>::hour(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_hour;
  }

  template<typename T>
  const int PosixDate<T>::dayofweek(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_wday;  // days since sunday 0 to 6
  }

  template<typename T>
  const int PosixDate<T>::dayofmonth(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_mday;  // no adjustment, it's already 1 to 31
  }

  template<typename T>
  const int PosixDate<T>::month(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_mon + 1;  // posix is 0 to 11, we want 1 to 12
  }

  template<typename T>
  const int PosixDate<T>::year(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);
    return posix_time_tm.tm_year + 1900;  // we want actual year instead of years since 1900
  }

  template<typename T>
  const int PosixDate<T>::last_day_of_month(const T x) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);

    switch(posix_time_tm.tm_mon + 1) {

      // case for Apr, June, Sep, Nov (30 day months)
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
      break;

      // case for Jan, March, May, July, Aug, Oct, Dec
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      return 31;
      break;

      // special case for feb
    case 2:
      if(is_leap_year(posix_time_tm.tm_year + 1900)) {
	return 29;
      } else {
	return 28;
      }
      break;
    }
  }

  template<typename T>
  const T PosixDate<T>::AddYears(const T x, const int n) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);

    // adjust years
    posix_time_tm.tm_year+=n;

    // make sure we drop out Feb 29 if we go from leapyear to non-leapyear
    check_day_of_month(posix_time_tm);

    // convert to POSIXct
    return static_cast<T>(mktime(&posix_time_tm));
  }

  template<typename T>
  const T PosixDate<T>::AddMonths(const T x, const int n) {
    struct tm posix_time_tm;
    to_time_tm(posix_time_tm, x);

    int yrs_to_add = n / 12;

    // adjust years
    posix_time_tm.tm_year += yrs_to_add;

    // adjust months to add
    //n = ( std::abs(n) % 12 ) * std::sign(n);
    // adjust months
    posix_time_tm.tm_mon += (n % 12);

    // check day of month
    check_day_of_month(posix_time_tm);

    // because we can cross a DST boundry
    posix_time_tm.tm_isdst = -1;

    // convert to POSIXct
    return static_cast<T>(mktime(&posix_time_tm));
  }

  template<typename T>
  const T PosixDate<T>::AddDays(const T x, const int n) {
    // one day is 60*60*24 seconds = 86400
    const int seconds_in_day = 86400;

    T ans = x + (seconds_in_day * n);

    // do DST shift check
    int shift_error = dst_shift_check(ans,x);

    return ans + shift_error;
  }

  template<typename T>
  const double PosixDate<T>::daily_distance(const T x, const T y) {

    const long seconds_in_day = 60*60*24;

    return (x - y)/seconds_in_day;
  }

} // namespace tslib

#endif // POSIX_DATE_POLICY_HPP

#ifndef POSIX_DATE_POLICY_HPP
#define POSIX_DATE_POLICY_HPP

#include <ctime>

template<typename T>
class PosixDate {
private:
  static void to_time_tm(struct tm* posix_time_tm, const T x);
public:
  static const T toDate(const char* date, const char* format1);
  static const T toDate(const int year, const int month, const int day, const int hour, const int minute, const int second);
  static const std::string toString(const T x, const char* format1);
  static const int dayofweek(const T x);
  static const int dayofmonth(const T x);
  static const int month(const T x);
  static const int year(const T x);
};

template<typename T>
void to_time_tm(struct tm* posix_time_tm, const T x) {
  const time_t posix_time_t = static_cast<time_t>(x);  
#ifdef WIN32
  memcpy(posix_time_tm,localtime(&posix_time_t), sizeof(struct tm));
#else
  localtime_r(&posix_time_t,posix_time_tm);
#endif
}

template<typename T>
const T PosixDate<T>::toDate(const char* date, const char* format) {
  struct tm posix_time_tm;
  memset(&posix_time_tm, '\0', sizeof(struct tm));
  strptime(date,format,&posix_time_tm);
  posix_time_tm.tm_isdst = -1;
  return static_cast<T>(mktime(&posix_time_tm));
}

template<typename T>
const T PosixDate<T>::toDate(const int year, const int month, const int day, const int hour, const int minute, const int second) {

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
  return static_cast<T>(mktime(&localtime_tm));
}

template<typename T>
const std::string PosixDate<T>::toString(const T x, const char* format) {
  struct tm posix_time_tm;
  const int BUFFSIZE = 32;
  char ans_char[BUFFSIZE];
  to_time_tm(&posix_time_tm, x);  
  strftime(ans_char,BUFFSIZE,format,&posix_time_tm);
  return std::string(ans_char);
}

template<typename T>
const int PosixDate<T>::dayofweek(const T x) {
  struct tm posix_time_tm;
  to_time_tm(&posix_time_tm, x);
  return posix_time_tm.tm_wday;  // days since sunday 0 to 6
}

template<typename T>
const int PosixDate<T>::dayofmonth(const T x) {
  struct tm posix_time_tm;
  to_time_tm(&posix_time_tm, x);
  return posix_time_tm.tm_mday;  // no adjustment, it's already 1 to 31
}

template<typename T>
const int PosixDate<T>::month(const T x) {
  struct tm posix_time_tm;
  to_time_tm(&posix_time_tm, x);
  return posix_time_tm.tm_mon + 1;  // posix is 0 to 11, we want 1 to 12
}

template<typename T>
const int PosixDate<T>::year(const T x) {
  struct tm posix_time_tm;
  to_time_tm(&posix_time_tm, x);
  return posix_time_tm.tm_year + 1900;  // we want actual year instead of years since 1900
}

#endif // POSIX_DATE_POLICY_HPP

#ifndef JULIAN_DATE_POLICY_HPP
#define JULIAN_DATE_POLICY_HPP

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

#endif // JULIAN_DATE_POLICY_HPP

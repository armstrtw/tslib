#ifndef NUMERIC_TRAITS_HPP
#define NUMERIC_TRAITS_HPP

#include <limits>
#include <cmath>

template<typename T>
class numeric_traits;

template<>
class numeric_traits<double> {
public:
  static const bool has_NA = true;

  static double NA() {
    return std::numeric_limits<double>::quiet_NaN();
  }
};

template<>
class numeric_traits<int> {
public:
  static const bool has_NA = true;
  
  static int NA() {
    return std::numeric_limits<int>::min();
  }
};

#endif //NUMERIC_TRAITS_HPP

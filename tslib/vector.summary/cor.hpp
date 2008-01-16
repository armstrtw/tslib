#ifndef COR_HPP
#define COR_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

template<typename T>
class corTraits;

template<>
class corTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class corTraits<int> {
public:
  typedef double ReturnType;
};


template<typename ReturnType>
class Cor {
public:
  template<typename T>
  static ReturnType apply(T x_beg, T x_end, T y_beg, T y_end) {

    ReturnType xy_cov = Cov<ReturnType>::apply(x_beg, x_end, y_beg, y_end);

    if(numeric_traits<ReturnType>::ISNA(xy_cov)) {
      return numeric_traits<ReturnType>::NA();
    }

    ReturnType x_sd = Stdev<ReturnType>::apply(x_beg, x_end);
    ReturnType y_sd = Stdev<ReturnType>::apply(y_beg, y_end);

    return xy_cov / ( x_sd * y_sd );
  }
};

} // namespace tslib

#endif // COR_HPP

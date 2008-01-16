#ifndef COV_HPP
#define COV_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

template<typename T>
class covTraits;

template<>
class covTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class covTraits<int> {
public:
  typedef double ReturnType;
};


template<typename ReturnType>
class Cov {
public:
  template<typename T>
  static ReturnType apply(T x_beg, T x_end, T y_beg, T y_end) {
    typedef typename std::iterator_traits<T>::difference_type DT;
    typedef typename std::iterator_traits<T>::value_type VT;

    DT x_len =  std::distance(x_beg,x_end);
    DT y_len =  std::distance(y_beg,y_end);

    if(x_len != y_len) {
      return numeric_traits<ReturnType>::NA();
    }

    ReturnType x_mean = Mean<ReturnType>::apply(x_beg,x_end);
    ReturnType y_mean = Mean<ReturnType>::apply(y_beg,y_end);

    // if we know that x_mean or y_mean is already NA, then just return NA
    if(numeric_traits<ReturnType>::ISNA(x_mean) || numeric_traits<ReturnType>::ISNA(y_mean)) {
      return numeric_traits<ReturnType>::NA();
    }

    ReturnType ans = 0;

    while(x_beg != x_end) {
      ans += (*x_beg - x_mean)*(*y_beg - y_mean);
      ++x_beg;
      ++y_beg;
    }
    return ans/(x_len - 1);
  }
};

} // namespace tslib

#endif // COV_HPP

#ifndef SUM_HPP
#define SUM_HPP

#include <iterator>
#include "../utils/numeric.traits.hpp"

namespace tslib {

template<typename T>
class sumTraits;

template<>
class sumTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class sumTraits<int> {
public:
  typedef int ReturnType;
};


template<typename ReturnType>
class Sum{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = 0;

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }
      ans += *beg;
      ++beg;
    }
    return ans;
  }
};

} // namespace tslib

#endif // SUM_HPP

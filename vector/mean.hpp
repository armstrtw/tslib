#ifndef MEAN_HPP
#define MEAN_HPP

#include <iterator>
#include "utils/numeric.traits.hpp"

namespace tslib {

template<typename T>
class meanTraits;

template<>
class meanTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class meanTraits<int> {
public:
  typedef double ReturnType;
};


template<typename ReturnType>
class Mean{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = 0;
    ReturnType len =  static_cast<ReturnType>(distance(beg,end));

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }
      ans += *beg;
      ++beg;
    }
    return ans/len;
  }
};

} // namespace tslib

#endif // MEAN_HPP

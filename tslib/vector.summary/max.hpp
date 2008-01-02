#ifndef MAX_HPP
#define MAX_HPP

#include <iterator>
#include "../utils/numeric.traits.hpp"

namespace tslib {

template<typename T>
class maxTraits {
public:
  typedef T ReturnType;
};

template<typename ReturnType>
class Max{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = *beg++;

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }
      ans = *beg > ans ? *beg : ans;
      ++beg;
    }
    return ans;
  }
};

} // namespace tslib

#endif // MAX_HPP

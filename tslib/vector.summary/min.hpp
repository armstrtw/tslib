#ifndef MIN_HPP
#define MIN_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

template<typename T>
class minTraits {
public:
  typedef T ReturnType;
};

template<typename ReturnType>
class Min{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = *beg++;

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }
      ans = *beg < ans ? *beg : ans;
      ++beg;
    }
    return ans;
  }
};

} // namespace tslib

#endif // MIN_HPP

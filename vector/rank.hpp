#ifndef RANK_HPP
#define RANK_HPP

#include <iterator>
#include "utils/numeric.traits.hpp"

namespace tslib {

template<typename T>
class rankTraits {
public:
  typedef int ReturnType;
};

template<typename ReturnType>
class Rank{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = 0;

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }

      // if end > data[index] then increment it's rank
      ans += (*end > *beg ? 1 : 0);
      ++beg;
    }
    return ans;
  }
};

} // namespace tslib

#endif // RANK_HPP

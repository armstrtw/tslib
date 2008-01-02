#ifndef RANK_HPP
#define RANK_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

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
    ReturnType ans = 1;
    typename std::iterator_traits<T>::value_type rank_value = *(end - 1);
    while(beg != (end - 1)) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        return numeric_traits<ReturnType>::NA();
      }

      // if end > data[index] then increment it's rank
      ans += (rank_value > *beg ? 1 : 0);
      ++beg;
    }
    return ans;
  }
};

} // namespace tslib

#endif // RANK_HPP

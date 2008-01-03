#ifndef STDEV_HPP
#define STDEV_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

template<typename T>
class stdevTraits;

template<>
class stdevTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class stdevTraits<int> {
public:
  typedef double ReturnType;
};


template<typename ReturnType>
class Stdev{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = 0;
    ReturnType len =  static_cast<ReturnType>(distance(beg,end));

    // can't take stdev of only 1 element
    if(len <= 1) {
      return numeric_traits<ReturnType>::NA();
    }

    ReturnType vec_mean = Mean<ReturnType>::apply(beg,end);

    // check NA of mean
    if(numeric_traits<ReturnType>::ISNA(vec_mean)) {
      return numeric_traits<ReturnType>::NA();
    }

    while(beg != end) {
      ans += std::pow(*beg - vec_mean, 2);
      ++beg;
    }
    return std::pow( ans/(len - 1), 0.5);
  }
};

} // namespace tslib

#endif // STDEV_HPP

#ifndef SUM_HPP
#define SUM_HPP

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
      ans += *beg;
      ++beg;
    }
    return ans;
  }
};

} // namespace tslib

#endif // SUM_HPP

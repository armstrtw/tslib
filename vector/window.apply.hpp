#ifndef WINDOW_APPLY_HPP
#define WINDOW_APPLY_HPP

#include "../utils/numeric.traits.hpp"

namespace tslib {

template<typename ReturnType,
         template<class> class F>
class windowApply {
public:
  template<typename T, typename U>
  static void apply(T ans, U beg, U end, const int window) {

    // if window is bigger than len, return all NA
    if(static_cast<int>(distance(beg,end)) < window) {
      while(beg != end) {
        *ans = numeric_traits<ReturnType>::NA();
        ++ans;
        ++beg;
      }
      return;
    }

    // set 1st (N-1) to NA
    for(int i = 1; i < window; i++, beg++, ans++) {
      *ans = numeric_traits<ReturnType>::NA();
    }

    // apply fun to rest
    while(beg != end) {
      *ans = F<ReturnType>::apply(beg-(window-1),beg+1);
      ++beg;
      ++ans;
    }
  }
};

} // namespace tslib

#endif // WINDOW_APPLY_HPP

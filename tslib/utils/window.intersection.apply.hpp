#ifndef WINDOW_APPLY_HPP
#define WINDOW_APPLY_HPP

#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

template<typename ReturnType,
         template<class> class F>
class windowIntersectionApply {
public:
  template<typename T, template<class,class> DataIter, typename TSDIM>
  static void apply(T ans, DataIter x_iter, DataIter y_iter, TSDIM size, const int window) {

    // if window is bigger than len, return all NA
    if(size < static_cast<TSDIM>(window)) {
      for(TSDIM i = 0; i < size; i++) {
        *ans = numeric_traits<ReturnType>::NA();
        ++ans;
      }
      return;
    }

    // set 1st (N-1) to NA
    for(int i = 1; i < window; i++, x_iter++, y_iter++, ans++) {
      *ans = numeric_traits<ReturnType>::NA();
    }

    // apply fun to rest
    while(beg != end) {
      *ans = F<ReturnType>::apply(x_iter-(window-1),x_iter+1,y_iter-(window-1),y_iter+1);
      ++x_iter;
      ++y_iter;
      ++ans;
    }
  }
};

} // namespace tslib

#endif // WINDOW_APPLY_HPP

#ifndef WINDOW_APPLY_HPP
#define WINDOW_APPLY_HPP

#include "numeric.traits.hpp"
using namespace std;


// assumes ans is same len as end - beg
//template <template<class> class F>
template <class T, template<class> class F>
void windowApply(T* ans, T* beg, T* end, const int window) {
  
  //typename T* marker = beg;
  T* marker = beg;

  typedef typename sumTraits<T>::ReturnType ReturnType;

  // if window is bigger than len, return all NA
  if(static_cast<int>(distance(beg,end)) < window) {
      while(beg != end) {
        *ans = numeric_traits<ReturnType>::NA();
        ++beg;
        ++ans;
      }
      return;
  }

  // set 1st (N-1) to NA
  for(int i = 0; i < (window-1); i++, beg++, ans++)
    *ans = numeric_traits<ReturnType>::NA();

  // apply fun to rest
  while(beg != end) {
    *ans = F<T>()(marker,beg);
    ++beg;
    ++marker;
    ++ans;
  }
}

#endif // WINDOW_APPLY_HPP

#ifndef FILL_BWD_HPP
#define FILL_BWD_HPP

#include <iterator>

namespace tslib {

template <typename T>
void fill_bwd(T dest, const T beg, const T end) {

  // have to find offset to start from back
  typename std::iterator_traits<T>::distance_type len =  distance(beg,end);

  // shift dest to element N-1
  dest += (len - 1);

  // nothing we can do about last element
  --end;
  *dest-- = *end--;

  while(beg != end) {
    if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*end)) {
      *dest = *(dest + 1);
      --dest;
      --end;
    }
  }
}

} // namespace tslib

#endif // FILL_BWD_HPP

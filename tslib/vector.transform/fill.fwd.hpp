#ifndef FILL_FWD_HPP
#define FILL_FWD_HPP

#include <iterator>

namespace tslib {

template <typename T>
void fill_fwd(T dest, const T beg, const T end) {

  // nothing we can do about elelment [0]
  *dest++ = *beg++;

  while(beg != end) {
    if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
      *dest = *(beg - 1);
      beg++;
      dest++;
    }
  }
}

} // namespace tslib

#endif // FILL_FWD_HPP

#ifndef DIFF_HPP
#define DIFF_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

template <typename T>
void diff(T dest, const T beg, const T end) {

  // set dest[0] to NA
  *dest++ = numeric_traits< typename std::iterator_traits<T>::value_type >::NA();
  ++beg;

  while(beg != end) {
    *dest = *beg - *(beg-1);
    beg++;
    dest++;
  }
}

} // namespace tslib

#endif // DIFF_HPP

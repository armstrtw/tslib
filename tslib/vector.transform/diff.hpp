#ifndef DIFF_HPP
#define DIFF_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {
template<typename ReturnType>
class Diff {
public:
  template<typename T, typename U>
  static void apply(T dest, U beg, U end) {

    // set dest[0] to NA
    *dest++ = numeric_traits< typename std::iterator_traits<T>::value_type >::NA();
    ++beg;

    while(beg != end) {
      *dest = *beg - *(beg-1);
      beg++;
      dest++;
    }
  }
};

} // namespace tslib

#endif // DIFF_HPP

#ifndef FILL_FWD_HPP
#define FILL_FWD_HPP

#include <iterator>

namespace tslib {

template<typename ReturnType>
class FillFwd {
public:
  template<typename T, typename U>
  static void apply(T dest, U beg, U end) {

    // nothing we can do about elelment [0]
    *dest++ = *beg++;

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*beg)) {
        *dest = *(dest - 1);
      } else {
        *dest = *beg;
      }
      ++beg;
      ++dest;
    }
  }
};

} // namespace tslib

#endif // FILL_FWD_HPP

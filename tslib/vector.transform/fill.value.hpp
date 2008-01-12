#ifndef FILL_VALUE_HPP
#define FILL_VALUE_HPP

#include <iterator>

namespace tslib {

template<typename ReturnType>
class FillValue {
public:
  template<typename T, typename U, typename V>
  static void apply(T dest, U beg, U end, V value) {

    while(beg != end) {
      if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
        *dest = static_cast< typename std::iterator_traits<T>::value_type >(value);
      } else {
        *dest = *beg;
      }
      ++beg;
      ++dest;
    }
  }
};

} // namespace tslib

#endif // FILL_VALUE_HPP

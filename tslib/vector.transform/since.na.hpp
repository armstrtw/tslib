#ifndef SINCE_NA_HPP
#define SINCE_NA_HPP

#include <iterator>

namespace tslib {

template <typename T, typename U>
void since_na(T dest, U beg, U end) {

  /*
  typedef std::iterator_traits<T>::value_type dest_type;

  dest_type count;

  // while no NA is found at all in the tseries then -1
  while(beg != end && !numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg) ) {
    *dest = static_cast<dest_type>(-1);
    ++beg;
    ++dest;
  }

  // if we get here, then an NA has been found
  while(beg != end) {
    if(numeric_traits<typename std::iterator_traits<T>::value_type>::ISNA(*beg)) {
      *dest = static_cast<dest_type>(0);
      count = 0;
    } else {
      *dest = count;
      count++;
    }
    ++beg;
    ++dest;
  }
  */
}

} // namespace tslib

#endif // SINCE_NA_HPP

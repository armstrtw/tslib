#ifndef LEAD_HPP
#define LEAD_HPP

#include <algorithm>

namespace tslib {

template<typename ReturnType>
class Lead {
public:
  template<typename T, typename U, typename V>
  static void apply(T dest, U beg, U end, V periods) {

    beg+=periods;

    if(beg < end)
      std::copy(beg, end, dest);

    // advance dest to beginning of NA's
    dest += std::distance(beg,end);

    // set tail values to NA
    for(V i = 0; i < periods; i++, dest++)
      *dest = numeric_traits<ReturnType>::NA();
  }
};

} // namespace tslib

#endif // LEAD_HPP

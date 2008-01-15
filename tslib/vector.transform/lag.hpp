#ifndef LAG_HPP
#define LAG_HPP

#include <algorithm>

namespace tslib {

template<typename ReturnType>
class Lag {
public:
  template<typename T, typename U, typename V>
  static void apply(T dest, U beg, U end, V periods) {

    // set head to NA
    for(V i = 0; i < periods; i++, dest++, end--)
      *dest = numeric_traits<ReturnType>::NA();

    if( end > beg )
      std::copy(beg, end, dest);
  }
};

} // namespace tslib

#endif // LAG_HPP

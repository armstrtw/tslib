#ifndef LAG_HPP
#define LAG_HPP

#include <tslib/utils/copyVector.hpp>

namespace tslib {

template <typename T, typename U>
void lag(T* dest, const T* source_beg, const T* source_end, const U periods) {

  // set head to NA
  for(U i = 0; i < periods; i++, dest++, --source_end)
    *dest = numeric_traits<T>::NA();

  if( source_end > source_beg )
    copyVector(dest, source_beg, std::distance(source_beg,source_end) );
}

} // namespace tslib

#endif // LAG_HPP

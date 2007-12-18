#ifndef LEAD_HPP
#define LEAD_HPP

#include "../utils/copyVector.hpp"

namespace tslib {

template <typename T, typename U>
void lead(T* dest, const T* source_beg, const T* source_end, const U periods) {

  source_beg+=periods;

  if(source_beg < source_end)
    copyVector(dest, source_beg, std::distance(source_beg,source_end) );

  // advance dest to beginning of NA's
  dest += std::distance(source_beg,source_end);

  // set tail values to NA
  for(U i = 0; i < periods; i++,dest++)
    *dest = numeric_traits<T>::NA();
}

} // namespace tslib

#endif // LEAD_HPP

#ifndef LAG_HPP
#define LAG_HPP

#include "../utils/copyVector.hpp"

template <typename T, typename U>
void lag(T* dest, const T* source_beg, const T* source_end, const U periods) {

  // set head to NA
  for(U i = 0; i < periods; i++, dest++, --source_end)
    *dest = numeric_traits<T>::NA();

  if( source_end > source_beg )
    copyVector(dest, source_beg, std::distance(source_beg,source_end) );  
}

#endif // LAG_HPP

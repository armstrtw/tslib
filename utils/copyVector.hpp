#ifndef COPY_VECTOR_HPP
#define COPY_VECTOR_HPP

template <typename T, typename U>
inline
void copyVector(T* dest, const T* source, const U len) {
  for(U i = 0; i < len; i++) {
    dest[i] = source[i];
  }
}

// specialized for builtins
template <typename U>
inline
void copyVector(double* dest, const double* source, const U len) {
  memcpy(dest, source, len * sizeof(double) );
}

template <typename U>
inline
void copyVector(int* dest, const int* source, const U len) {
  memcpy(dest, source, len * sizeof(int) );
}


#endif // COPY_VECTOR_HPP

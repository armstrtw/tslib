#ifndef COPY_VECTOR_HPP
#define COPY_VECTOR_HPP



template <typename T, typename U>
void copyVector(T* dest, T* source, U len) {
  for(U i = 0; i < len; i++) {
    dest[i] = source[i];
  }
}



// specialized for builtins
template <typename U>
inline
void copyVector(double* dest, double* source, U len) {
  memcpy(dest, source, len * sizeof(double) );
}


template <typename U>
inline
void copyVector(int* dest, int* source, U len) {
  memcpy(dest, source, len * sizeof(int) );
}


#endif // COPY_VECTOR_HPP

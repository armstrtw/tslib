#ifndef FILL_TRAITS_HPP
#define FILL_TRAITS_HPP

template<typename T>
class fillTraits;

template<>
class fillTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class fillTraits<int> {
public:
  typedef int ReturnType;
};


#endif // FILL_TRAITS_HPP

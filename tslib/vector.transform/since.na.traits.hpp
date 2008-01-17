#ifndef SINCE_NA_TRAITS_HPP
#define SINCE_NA_TRAITS_HPP

template<typename T>
class SinceNATraits;

template<>
class SinceNATraits<double> {
public:
  typedef int ReturnType;
};

template<>
class SinceNATraits<int> {
public:
  typedef int ReturnType;
};


#endif // SINCE_NA_TRAITS_HPP

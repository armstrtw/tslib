#ifndef FILL_TRAITS_HPP
#define FILL_TRAITS_HPP

template<typename T>
class fillTraits;

template<>
class fillTraits<double> {
public:
  typedef double ReturnType;
  typedef double ArgType; // for fillValue
};

template<>
class fillTraits<int> {
public:
  typedef int ReturnType;
  typedef int ArgType; // for fillValue
};


#endif // FILL_TRAITS_HPP

#ifndef LAG_LEAD_TRAITS_HPP
#define LAG_LEAD_TRAITS_HPP

template<typename T>
class lagleadTraits;

template<>
class lagleadTraits<double> {
public:
  typedef double ReturnType;
  typedef int ArgType;  // for periods
};

template<>
class lagleadTraits<int> {
public:
  typedef int ReturnType;
  typedef int ArgType; // for periods
};


#endif // LAG_LEAD_TRAITS_HPP

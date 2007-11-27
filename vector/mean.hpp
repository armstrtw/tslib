#ifndef MEAN_HPP
#define MEAN_HPP


template<typename T>
class meanTraits;

template<>
class meanTraits<double> {
public:
  typedef double ReturnType;
};

template<>
class meanTraits<int> {
public:
  typedef double ReturnType;
};


template<typename ReturnType>
class Mean{
public:
  template<typename T>
  static ReturnType apply(T beg, T end) {
    ReturnType ans = 0;
    ReturnType len =  static_cast<ReturnType>(distance(beg,end));

    while(beg != end) {
      ans += *beg;
      ++beg;
    }
    return ans/len;
  }
};

#endif // MEAN_HPP

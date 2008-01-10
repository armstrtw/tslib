#ifndef FILL_BWD_HPP
#define FILL_BWD_HPP

#include <iterator>

namespace tslib {

template<typename ReturnType>
class FillBwd {
public:
  template<typename T, typename U>
  static void apply(T dest, U beg, U end) {

    // have to find offset to start from back
    typename std::iterator_traits<U>::difference_type len =  distance(beg,end);

    // push beg off end of array since we are comming towards it
    --beg;

    // shift dest to element N-1
    dest += (len - 1);

    // end is beyond array right now
    --end;
    //cout << *end << endl;

    // set last element to value of end
    *dest-- = *end--;


    while(end != beg) {
      if(numeric_traits<typename std::iterator_traits<U>::value_type>::ISNA(*end)) {
        *dest = *(dest + 1);
      } else {
        *dest = *end;
      }
      --dest;
      --end;
    }
  }
};

} // namespace tslib

#endif // FILL_BWD_HPP

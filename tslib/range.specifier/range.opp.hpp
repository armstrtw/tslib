#ifndef RANGE_OPP_HPP
#define RANGE_OPP_HPP

#include <tslib/range.specifier/range.iterator.hpp>

template<typename T, typename U, typename RangeIterator, typename BinaryOpp>
void applyRangeOpp(T ans_iter, RangeIterator iter1, RangeIterator iter2, const U size, BinaryOpp opp) {
  for(U i = 0; i < size; i++) {
    *ans_iter = opp( *iter1 , *iter2 );
    ++ans_iter;
    ++iter1;
    ++iter2;
  }
}

#endif // RANGE_OPP_HPP

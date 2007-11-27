#ifndef TS_WINDOW_APPLY_HPP
#define TS_WINDOW_APPLY_HPP

#include "copyVector.hpp"

template<class TDATE, class TDATA, template<class U, class V> class TSeries, class <template> T windowOpp>
const TSeries<TDATE, typename windowOpp<TDATA>::ReturnType> windowApply(const TSeries<TDATE,TDATA>& x, const int window) {
  
  // allocate new answer
  TSeries<typename windowOpp<TDATA>::ReturnType,TDATA> ans(x.nrow(), x.ncol());

  // copy over dates
  copyVector(ans.getDates(),x.getDates(),x.nrow());

  // set new colnames
  ans.setColnames(x.getColnames());

  TDATA* ans_data = ans.getData();
  TDATA* x_data = x.getData();

  for(TSDIM col = 0; col < lhs.ncol(); col++) {
    windowApply<TDATA,windowOpp>(ans_data, x_data, x_data+x.nrow(), window);

    // increment column
    ans_data+= ans.nrow();
    lhs_data+= lhs.nrow();
    rhs_data+= rhs.nrow();
  }
  return ans;
}

#endif // TS_WINDOW_APPLY_HPP

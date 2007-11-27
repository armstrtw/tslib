#ifndef TS_SCALAR_OPP_HPP
#define TS_SCALAR_OPP_HPP

#include "../tseries.data.hpp"
#include "../utils/copyVector.hpp"

template<class TDATE, class TDATA, template<class U, class V> class TSeries, class opptype>
const TSeries<TDATE,TDATA> apply_opp(const TDATA lhs_scalar, 
                                     const TSeries<TDATE,TDATA>& rhs_TSeries, 
                                     opptype opp) {

  // allocate new answer
  TSeries<TDATE,TDATA> ans(rhs_TSeries.nrow(),rhs_TSeries.ncol());

  // copy over dates
  copyVector(ans.getDates(),rhs_TSeries.getDates(),rhs_TSeries.nrow());
  TDATA* ans_data = ans.getData();
  TDATA* rhs_TSeries_data = rhs_TSeries.getData();

  for(TSDIM i = 0; i < rhs_TSeries.nrow()*rhs_TSeries.ncol(); i++)
    ans_data[i] = opp(lhs_scalar,rhs_TSeries_data[i]);

  return ans;
}


template<class TDATE, class TDATA, template<class U, class V> class TSeries, class opptype>
const TSeries<TDATE,TDATA> apply_opp(const TSeries<TDATE,TDATA>& lhs_TSeries,
                                     const TDATA rhs_scalar,
                                     opptype opp) {

  // allocate new answer
  TSeries<TDATE,TDATA> ans(lhs_TSeries.nrow(),lhs_TSeries.ncol());

  // copy over dates
  copyVector(ans.getDates(),lhs_TSeries.getDates(),lhs_TSeries.nrow());
  TDATA* ans_data = ans.getData();
  TDATA* lhs_TSeries_data = lhs_TSeries.getData();

  for(TSDIM i = 0; i < lhs_TSeries.nrow()*lhs_TSeries.ncol(); i++)
    ans_data[i] = opp(lhs_TSeries_data[i],rhs_scalar);

  return ans;
}

#endif // TS_SCALAR_OPP_HPP

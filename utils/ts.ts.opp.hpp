#ifndef TS_TS_OPP_HPP
#define TS_TS_OPP_HPP

#include "../tseries.data.hpp"
#include "rangeSpecifier.hpp"
#include "copyVector.hpp"

//template<template<TDATE,TDATA> class TSeries>
//template<typename TDATE, typename TDATA, template<TDATE,TDATA> class TSeries>
//template<template<class TDATE, class TDATA> class TSeries>
//template<typename opptype>

template<class TDATE, class TDATA, template<class U, class V> class TSeries, class opptype>
const TSeries<TDATE,TDATA> apply_opp(const TSeries<TDATE,TDATA>& lhs, 
                                     const TSeries<TDATE,TDATA>& rhs, 
                                     opptype opp) {

  if(lhs.ncol() != rhs.ncol())
    return TSeries<TDATE,TDATA>();
  
  // find date intersection
  RangeSpecifier<TDATE,TSDIM> range(lhs.getDates(), rhs.getDates(), lhs.nrow(), rhs.nrow() );

  if(!range.getSize())
    return TSeries<TDATE,TDATA>();

  // allocate new answer
  TSeries<TDATE,TDATA> ans(range.getSize(),lhs.ncol());

  // copy over dates
  copyVector(ans.getDates(),range.getDates(),range.getSize());
  TDATA* ans_data = ans.getData();
  TDATA* lhs_data = lhs.getData();
  TDATA* rhs_data = rhs.getData();

  for(TSDIM col = 0; col < lhs.ncol(); col++) {
    range.applyOpp(ans_data, lhs_data, rhs_data, opp);

    // increment column
    ans_data+= ans.nrow();
    lhs_data+= lhs.nrow();
    rhs_data+= rhs.nrow();
  }

  return ans;
}

#endif // TS_TS_OPP_HPP

#ifndef TS_TS_OPP_HPP
#define TS_TS_OPP_HPP

#include "../tseries.data.hpp"
#include "../utils/rangeSpecifier.hpp"
#include "../utils/copyVector.hpp"

//template<template<TDATE,TDATA> class TSeries>
//template<typename TDATE, typename TDATA, template<TDATE,TDATA> class TSeries>
//template<template<class TDATE, class TDATA> class TSeries>
//template<typename opptype>

template<class TDATE, class TDATA, class TSDIM, template<class U, class V, class W> class TSeries, class opptype>
const TSeries<TDATE,TDATA,TSDIM> apply_opp(const TSeries<TDATE,TDATA,TSDIM>& lhs, 
                                     const TSeries<TDATE,TDATA,TSDIM>& rhs, 
                                     opptype opp) {

  if(lhs.ncol() != rhs.ncol())
    return TSeries<TDATE,TDATA,TSDIM>();
  
  // find date intersection
  RangeSpecifier<TDATE,TSDIM> range(lhs.getDates(), rhs.getDates(), lhs.nrow(), rhs.nrow() );

  if(!range.getSize())
    return TSeries<TDATE,TDATA,TSDIM>();

  // allocate new answer
  TSeries<TDATE,TDATA,TSDIM> ans(range.getSize(),lhs.ncol());

  // copy over dates
  copyVector(ans.getDates(),range.getDates(),range.getSize());

  // set new colnames
  vector<string> lhs_cnames = lhs.getColnames();
  vector<string> rhs_cnames = rhs.getColnames();
  vector<string> ans_cnames;

  if(lhs_cnames==rhs_cnames) {
    ans_cnames = lhs_cnames;
  } else {
    // loop through and combine colnames from lhs and rhs
    if(lhs_cnames.size() && rhs_cnames.size()) {
      for(size_t i = 0; i < lhs_cnames.size(); i++) {
        ans_cnames.push_back( lhs_cnames[i] + rhs_cnames[i] );
      }
    } else {
      ans_cnames = lhs_cnames.size() ? lhs_cnames : rhs_cnames;
    }
  }

  ans.setColnames(ans_cnames);

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

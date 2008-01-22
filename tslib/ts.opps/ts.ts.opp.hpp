///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008  Whit Armstrong                                    //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, either version 3 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details.                          //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#ifndef TS_TS_OPP_HPP
#define TS_TS_OPP_HPP

#include <algorithm>

#include <tslib/tseries.data.hpp>
#include <tslib/range.specifier/rangeSpecifier.hpp>
#include <tslib/range.specifier/range.opp.hpp>

namespace tslib {


  template<class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
           class opptype>

  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> apply_opp(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                      const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                                                      opptype opp) {

    if(lhs.ncol() != rhs.ncol())
      return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();

    // find date intersection
    RangeSpecifier<TDATE,TSDIM> range(lhs.getDates(), rhs.getDates(), lhs.nrow(), rhs.nrow() );

    if(!range.getSize())
      return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();

    // allocate new answer
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(range.getSize(),lhs.ncol());

    // copy over dates
    std::copy(range.getDates(),range.getDates()+range.getSize(),ans.getDates());

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

      RangeIterator<const TDATA*, const TSDIM*> lhs_iter(lhs_data, range.getArg1());
      RangeIterator<const TDATA*, const TSDIM*> rhs_iter(rhs_data, range.getArg2());

      applyRangeOpp(ans_data, lhs_iter, rhs_iter, range.getSize(), opp);

      // increment column
      ans_data+= ans.nrow();
      lhs_data+= lhs.nrow();
      rhs_data+= rhs.nrow();
    }

    return ans;
  }


  template<class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
           class opptype>

  const vector<bool> apply_boolean_opp(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                       const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                       opptype opp) {

    vector<bool> ans;

    if(lhs.ncol() != rhs.ncol())
      return ans;

    // find date intersection
    RangeSpecifier<TDATE,TSDIM> range(lhs.getDates(), rhs.getDates(), lhs.nrow(), rhs.nrow() );

    if(!range.getSize())
      return ans;

    // allocate new answer
    ans.reserve(range.getSize()*lhs.ncol);

    vector<bool>::iterator ans_data = ans.begin();
    TDATA* lhs_data = lhs.getData();
    TDATA* rhs_data = rhs.getData();

    for(TSDIM col = 0; col < lhs.ncol(); col++) {

      RangeIterator<const TDATA*, const TSDIM*> lhs_iter(lhs_data, range.getArg1());
      RangeIterator<const TDATA*, const TSDIM*> rhs_iter(rhs_data, range.getArg2());

      applyRangeOpp(ans_data, lhs_iter, rhs_iter, range.getSize(), opp);

      // increment column
      ans_data += range.getSize();
      lhs_data += lhs.nrow();
      rhs_data += rhs.nrow();
    }

    return ans;
  }

} // namespace tslib

#endif // TS_TS_OPP_HPP

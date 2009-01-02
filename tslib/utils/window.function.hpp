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

#ifndef WINDOW_FUNCTION_HPP
#define WINDOW_FUNCTION_HPP

#include <algorithm>

#include <tslib/tseries.data.hpp>
#include <tslib/range.specifier/rangeSpecifier.hpp>
#include <tslib/utils/window.intersection.apply.hpp>
#include <tslib/range.specifier/range.iterator.hpp>

namespace tslib {

  template<typename ReturnType,
           template<class> class F,
           class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries>
  inline
  const TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> window_function(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                                 const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                                                                 const size_t window) {
    TSDIM lhs_ncol = lhs.ncol();
    TSDIM rhs_ncol = rhs.ncol();

    if(lhs_ncol != rhs_ncol && lhs_ncol != 1 && rhs_ncol != 1)
      return TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy>();

    // find date intersection
    RangeSpecifier<TDATE,TSDIM> range(lhs.getDates(), rhs.getDates(), lhs.nrow(), rhs.nrow() );

    if(!range.getSize())
      return TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy>();

    TSDIM ans_ncol = (lhs_ncol > rhs_ncol) ? lhs_ncol : rhs_ncol;

    // allocate new answer
    TSDIM ans_nrow = range.getSize() - (window - 1);
    if(ans_nrow <= 0)
      return TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy>();

    TSeries<TDATE,ReturnType,TSDIM,TSDATABACKEND,DatePolicy> ans(ans_nrow, ans_ncol);

    // copy over dates
    std::copy(range.getDates() + (window - 1), range.getDates()+range.getSize(), ans.getDates());

    // set new colnames
    std::vector<std::string> lhs_cnames = lhs.getColnames();
    std::vector<std::string> rhs_cnames = rhs.getColnames();
    std::vector<std::string> ans_cnames;


    // FIXME: this will take some work to get correct
    if(lhs_cnames==rhs_cnames) {
      ans_cnames = lhs_cnames;
    } else {
      ans_cnames = lhs_cnames.size() ? lhs_cnames : rhs_cnames;
    }

    ans.setColnames(ans_cnames);

    ReturnType* ans_data = ans.getData();
    TDATA* lhs_data = lhs.getData();
    TDATA* rhs_data = rhs.getData();

    for(TSDIM col = 0; col < lhs.ncol(); col++) {

      RangeIterator<const TDATA*, const TSDIM*> lhs_iter(lhs_data, range.getArg1());
      RangeIterator<const TDATA*, const TSDIM*> rhs_iter(rhs_data, range.getArg2());

      windowIntersectionApply<ReturnType,F>::apply(ans_data, lhs_iter, rhs_iter, range.getSize(), window);

      // increment column
      ans_data+= ans.nrow();
      lhs_data+= lhs.nrow();
      rhs_data+= rhs.nrow();
    }
    return ans;
  }

} // namespace tslib

#endif // WINDOW_FUNCTION_HPP

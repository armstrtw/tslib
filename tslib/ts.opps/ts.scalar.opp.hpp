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

#ifndef TS_SCALAR_OPP_HPP
#define TS_SCALAR_OPP_HPP

#include <algorithm>

#include <tslib/tseries.data.hpp>

namespace tslib {

  template<class TDATE,
           class TDATA1,
           class TDATA2,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
           class opptype>

  const TSeries<TDATE, typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> apply_opp(const TDATA1 lhs_scalar,
													    const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs_TSeries,
													    opptype opp) {

    typedef typename Promotion<TDATA1,TDATA2>::ResultT ResultT;

    // allocate new answer
    TSeries<TDATE,ResultT,TSDIM,TSDATABACKEND,DatePolicy> ans(rhs_TSeries.nrow(),rhs_TSeries.ncol());

    // copy over dates
    std::copy(rhs_TSeries.getDates(),rhs_TSeries.getDates()+rhs_TSeries.nrow(),ans.getDates());
    ResultT* ans_data = ans.getData();
    TDATA2* rhs_TSeries_data = rhs_TSeries.getData();

    for(TSDIM i = 0; i < rhs_TSeries.nrow()*rhs_TSeries.ncol(); i++)
      ans_data[i] = opp(static_cast<ResultT>(lhs_scalar),static_cast<ResultT>(rhs_TSeries_data[i]));

    return ans;
  }


  template<class TDATE,
	   class TDATA1,
	   class TDATA2,
	   class TSDIM,
	   template<typename,typename,typename> class TSDATABACKEND,
	   template<typename> class DatePolicy,
	   template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
	   class opptype>


  const TSeries<TDATE, typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> apply_opp(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs_TSeries,
													    const TDATA2 rhs_scalar,
													    opptype opp) {

    typedef typename Promotion<TDATA1,TDATA2>::ResultT ResultT;

    // allocate new answer
    TSeries<TDATE,ResultT,TSDIM,TSDATABACKEND,DatePolicy> ans(lhs_TSeries.nrow(),lhs_TSeries.ncol());

    // copy over dates
    std::copy(lhs_TSeries.getDates(),lhs_TSeries.getDates()+lhs_TSeries.nrow(),ans.getDates());
    ResultT* ans_data = ans.getData();
    TDATA1* lhs_TSeries_data = lhs_TSeries.getData();

    for(TSDIM i = 0; i < lhs_TSeries.nrow()*lhs_TSeries.ncol(); i++)
      ans_data[i] = opp(static_cast<ResultT>(lhs_TSeries_data[i]),static_cast<ResultT>(rhs_scalar));

    return ans;
  }


  template<class TDATE,
           class TDATA1,
           class TDATA2,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
           class opptype>

  const std::vector<bool> apply_boolean_opp(const TDATA1 lhs_scalar,
					    const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
					    opptype opp) {

    typedef typename Promotion<TDATA1,TDATA2>::ResultT ResultT;
    std::vector<bool> ans;

    // allocate new answer
    ans.reserve(rhs.nrow()*rhs.ncol());

    std::vector<bool>::iterator ans_data = ans.begin();
    TDATA2* rhs_data = rhs.getData();

    for(TSDIM i = 0; i < rhs.nrow() * rhs.ncol(); i++)
      ans_data[i] = opp(static_cast<ResultT>(lhs_scalar),static_cast<ResultT>(rhs_data[i]));

    return ans;
  }

  template<class TDATE,
           class TDATA1,
           class TDATA2,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
           class opptype>

  const std::vector<bool> apply_boolean_opp(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
					    const TDATA2 rhs_scalar,					    
					    opptype opp) {

    typedef typename Promotion<TDATA1,TDATA2>::ResultT ResultT;
    std::vector<bool> ans;

    // allocate new answer
    ans.reserve(lhs.nrow()*lhs.ncol());

    std::vector<bool>::iterator ans_data = ans.begin();
    TDATA1* lhs_data = lhs.getData();

    for(TSDIM i = 0; i < lhs.nrow() * lhs.ncol(); i++)
      ans_data[i] = opp(static_cast<ResultT>(lhs_data[i]),static_cast<ResultT>(rhs_scalar));

    return ans;
  }

} // namespace tslib

#endif // TS_SCALAR_OPP_HPP

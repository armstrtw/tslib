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

#ifndef TS_OPPS_HPP
#define TS_OPPS_HPP

#include <tslib/ts.opps/ts.promotion.hpp>
#include <tslib/ts.opps/ts.ts.opp.hpp>
#include <tslib/ts.opps/ts.scalar.opp.hpp>

namespace tslib {
  using std::plus;
  using std::minus;
  using std::multiplies;
  using std::divides;
  using std::greater;
  using std::less;
  using std::greater_equal;
  using std::less_equal;
  using std::equal_to;
  using std::not_equal_to;

  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,plus<typename Promotion<TDATA1,TDATA2>::ResultT>());
  }
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,minus<typename Promotion<TDATA1,TDATA2>::ResultT>());
  }
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,multiplies<typename Promotion<TDATA1,TDATA2>::ResultT>());
  }
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,divides<typename Promotion<TDATA1,TDATA2>::ResultT>());
  }

  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TDATA1 lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) {
    return apply_opp(lhs,rhs,plus<typename Promotion<TDATA1,TDATA2>::ResultT>());
  }

  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA2 rhs) {
    return apply_opp(lhs,rhs,plus<typename Promotion<TDATA1,TDATA2>::ResultT>());
  }

} // namespace tslib
#endif // TS_OPPS_HPP

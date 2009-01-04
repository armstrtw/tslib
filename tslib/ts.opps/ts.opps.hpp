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

#define DEFINE_TS_TS_OPP(function_name,opp) \
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> \
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> function_name(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) { \
    return apply_opp(lhs,rhs,opp<typename Promotion<TDATA1,TDATA2>::ResultT>()); \
  }
#define DEFINE_TS_SCALAR_OPP(function_name,opp) \
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> \
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> function_name(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA2 rhs) { \
    return apply_opp(lhs,rhs,opp<typename Promotion<TDATA1,TDATA2>::ResultT>()); \
  }
#define DEFINE_SCALAR_TS_OPP(function_name,opp)	\
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> \
  TSeries<TDATE,typename Promotion<TDATA1,TDATA2>::ResultT,TSDIM,TSDATABACKEND,DatePolicy> function_name(const TDATA1 lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) { \
    return apply_opp(lhs,rhs,opp<typename Promotion<TDATA1,TDATA2>::ResultT>()); \
  }
#define DEFINE_TS_TS_BOOL_OPP(function_name,opp)			\
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> \
  std::vector<bool> function_name(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) { \
    return apply_boolean_opp(lhs,rhs,opp<typename Promotion<TDATA1,TDATA2>::ResultT>()); \
  }
#define DEFINE_SCALAR_TS_BOOL_OPP(function_name,opp) \
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> \
  std::vector<bool> function_name(const TDATA1 lhs, const TSeries<TDATE,TDATA2,TSDIM,TSDATABACKEND,DatePolicy>& rhs) { \
    return apply_boolean_opp(lhs,rhs,opp<typename Promotion<TDATA1,TDATA2>::ResultT>()); \
  }
#define DEFINE_TS_SCALAR_BOOL_OPP(function_name,opp) \
  template<typename TDATE, typename TDATA1, typename TDATA2, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> \
  std::vector<bool> function_name(const TSeries<TDATE,TDATA1,TSDIM,TSDATABACKEND,DatePolicy>& lhs, const TDATA2 rhs) { \
    return apply_boolean_opp(lhs,rhs,opp<typename Promotion<TDATA1,TDATA2>::ResultT>()); \
  }


namespace tslib {

  // pre-declare template friends
  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> class TSeries;

  // predeclaration for friend template
  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  std::ostream& operator<<(std::ostream& os,
			   const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts);

  DEFINE_TS_TS_OPP(operator+,std::plus)
  DEFINE_TS_SCALAR_OPP(operator+,std::plus)
  DEFINE_SCALAR_TS_OPP(operator+,std::plus)

  DEFINE_TS_TS_OPP(operator-,std::minus)
  DEFINE_TS_SCALAR_OPP(operator-,std::minus)
  DEFINE_SCALAR_TS_OPP(operator-,std::minus)

  DEFINE_TS_TS_OPP(operator*,std::multiplies)
  DEFINE_TS_SCALAR_OPP(operator*,std::multiplies)
  DEFINE_SCALAR_TS_OPP(operator*,std::multiplies)

  DEFINE_TS_TS_OPP(operator/,std::divides)
  DEFINE_TS_SCALAR_OPP(operator/,std::divides)
  DEFINE_SCALAR_TS_OPP(operator/,std::divides)

  DEFINE_TS_TS_BOOL_OPP(operator==,std::equal_to)
  DEFINE_SCALAR_TS_BOOL_OPP(operator==,std::equal_to)
  DEFINE_TS_SCALAR_BOOL_OPP(operator==,std::equal_to)

  DEFINE_TS_TS_BOOL_OPP(operator!=,std::not_equal_to)
  DEFINE_SCALAR_TS_BOOL_OPP(operator!=,std::not_equal_to)
  DEFINE_TS_SCALAR_BOOL_OPP(operator!=,std::not_equal_to)

  DEFINE_TS_TS_BOOL_OPP(operator>,std::greater)
  DEFINE_SCALAR_TS_BOOL_OPP(operator>,std::greater)
  DEFINE_TS_SCALAR_BOOL_OPP(operator>,std::greater)

  DEFINE_TS_TS_BOOL_OPP(operator>=,std::greater_equal)
  DEFINE_SCALAR_TS_BOOL_OPP(operator>=,std::greater_equal)
  DEFINE_TS_SCALAR_BOOL_OPP(operator>=,std::greater_equal)

  DEFINE_TS_TS_BOOL_OPP(operator<,std::less)
  DEFINE_SCALAR_TS_BOOL_OPP(operator<,std::less)
  DEFINE_TS_SCALAR_BOOL_OPP(operator<,std::less)

  DEFINE_TS_TS_BOOL_OPP(operator<=,std::less_equal)
  DEFINE_SCALAR_TS_BOOL_OPP(operator<=,std::less_equal)
  DEFINE_TS_SCALAR_BOOL_OPP(operator<=,std::less_equal)

} // namespace tslib
#endif // TS_OPPS_HPP

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

namespace tslib {

  // pre-declare template friends
  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> class TSeries;

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TDATA lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TDATA lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TDATA lhs,
								const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TDATA rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TDATA rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TDATA rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
								const TDATA rhs);


  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator>(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                         const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator<(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                         const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator>=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                          const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator<=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                          const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator==(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                          const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  vector<bool> operator!=(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                          const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);


  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  std::ostream& operator<<(std::ostream& os,
                           const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts);

} // namespace tslib

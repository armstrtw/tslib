///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2014  Whit Armstrong                                    //
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

#ifndef TSERIES_IO_HPP
#define TSERIES_IO_HPP

#include <iostream>

namespace tslib {

  template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
  std::ostream& operator<< (std::ostream& os, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts) {
    std::vector<std::string> cnames(ts.getColnames());

    if(cnames.size()) {
      // shift out to be in line w/ first column of values (space is for dates column)
      os << "\t";
      for(std::vector<std::string>::const_iterator iter = cnames.begin(); iter != cnames.end(); iter++) {
        os << *iter++ << " ";
      }
    }

    TDATE* dates = ts.getDates();
    TSDIM nr  = ts.nrow();
    TSDIM nc  = ts.ncol();

    for(TSDIM row = 0; row < nr; row++) {
      os << DatePolicy<TDATE>::toString(dates[row],"%Y-%m-%d %T") << "\t";
      for(TSDIM col = 0; col < nc; col++) {
        if(numeric_traits<TDATA>::ISNA(ts(row,col))) {
          os << "NA" << " ";
        } else {
          os << ts(row,col) << " ";
        }
      }
      os << std::endl;
    }
    return os;
  }
}  // namespace tslib

#endif // TSERIES_IO_HPP

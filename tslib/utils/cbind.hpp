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

#ifndef CBIND_HPP
#define CBIND_HPP

namespace tslib {

  template<class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W, template<typename,typename,typename> class DATABACKEND, template<typename> class DP> class TSeries,
           template<class X, class=allocator<X> > Seq>

  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> cbind(Seq<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> > s) {
    int i = 0;
    Seq<TSeries>::iterator it;
    //Seq<TSeries>::iterator it;
    //while(Seq<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::iterator  it = s.begin() != s.end()) {
    /*
    while(Seq<TSeries>::iterator it = s.begin() != s.end()) {
      i += it->ncol();
    }
    std::cout << i << std::endl;
    */
    return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
  }

}
#endif // CBIND_HPP

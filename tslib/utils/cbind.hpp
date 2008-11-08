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

#include <vector>
#include <set>
#include <algorithm>

namespace tslib {

  template<class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           template<class U, class V, class W,
		    template<typename,typename,typename> class DATABACKEND,
		    template<typename> class DP> class TSeries,
	   template<typename ELEM, typename = std::allocator<ELEM> > class CONT>

  TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>
  cbind(CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
	const bool intersection)
  {
    size_t sz = cont.size();
    if(sz == 0) {
      return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
    }
    if(sz == 1) {
      return *cont.begin();
    }

    return *cont.begin();
  }

  template<class TDATE,
	   class TDATA,
	   class TSDIM,
	   template<typename,typename,typename> class TSDATABACKEND,
	   template<typename> class DatePolicy,
	   template<class U, class V, class W,
		    template<typename,typename,typename> class DATABACKEND,
		    template<typename> class DP> class TSeries,
	   template<typename ELEM, typename = std::allocator<ELEM> > class CONT,
	   class I>
  void
  date_intersection(CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
		    I& output_dates)
  {

    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::iterator it = cont.begin();
    std::vector<TDATE> inBuff;
    std::vector<TDATE> outBuff;

    std::copy(it->getDates(),it->getDates() + it->nrow(),
	      std::inserter(inBuff,inBuff.begin()));
    while(it != cont.end()) {
      set_intersection(inBuff.begin(),inBuff.end(),
		       it->getDates(),it->getDates() + it->nrow(),
		       insert_iterator(outBuff));
      // swap buffs
      inBuff.erase();
      std::copy(outBuff.begin(),outBuff.end(),
		std::inserter(inBuff,inBuff.begin()));
      outBuff.erase();
      ++it;
    }
    std::copy(outBuff.begin(),outBuff.end(),output_dates);
  }

  template<class TDATE,
	   class TDATA,
	   class TSDIM,
	   template<typename,typename,typename> class TSDATABACKEND,
	   template<typename> class DatePolicy,
	   template<class U, class V, class W,
		    template<typename,typename,typename> class DATABACKEND,
		    template<typename> class DP> class TSeries,
	   template<typename ELEM, typename = std::allocator<ELEM> > class CONT,
	   class I>
  void
  date_union(CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
	     I& output_dates)
  {
    std::set<TDATE> ans;
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::iterator it = cont.begin();

    // walk through all tseries adding all dates
    // let std::set drop dups for us
    while(it != cont.end()) {
      TSDIM nrow = it->nrow();
      TDATE* dts = it->getDates();
      for(TSDIM i = 0; i < it->nrow(); i++) {
	ans.insert(dts[i]);
      }
    }
    std::copy(ans.begin(), ans.end(), output_dates);
  }

  template<class TDATE,
	   class TDATA,
	   class TSDIM,
	   template<typename,typename,typename> class TSDATABACKEND,
	   template<typename> class DatePolicy,
	   template<class U, class V, class W,
		    template<typename,typename,typename> class DATABACKEND,
		    template<typename> class DP> class TSeries,
	   template<typename ELEM, typename = std::allocator<ELEM> > class CONT>
  TSDIM
  cbind_total_cols(CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont)
  {
    TSDIM ans = 0;
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::iterator it;
    for(it = cont.begin(); it != cont.end(); it++) {
      ans += it->ncol();
    }
    return ans;
  }

  template<class TDATE,
	   class TDATA,
	   class TSDIM,
	   template<typename,typename,typename> class TSDATABACKEND,
	   template<typename> class DatePolicy,
	   template<class U, class V, class W,
		    template<typename,typename,typename> class DATABACKEND,
		    template<typename> class DP> class TSeries,
	   template<typename ELEM, typename = std::allocator<ELEM> > class CONT>
  TSDIM
  cbind_max_nrow(CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont)
  {
    std::vector<TSDIM> nrows;
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::iterator it;
    for(it = cont.begin(); it != cont.end(); it++) {
      nrows.push_back(it->nrow());
    }
    return *max_element(nrows.begin(), nrows.end());
  }

} // namespace tslib

#endif // CBIND_HPP

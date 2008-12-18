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
  cbind(const CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
	const bool intersection)
  {
    size_t sz = cont.size();
    if(sz == 0) {
      return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
    }
    if(sz == 1) {
      return *cont.begin();
    }

    std::vector<TDATE> ans_dates;
    if(intersection) {
      date_intersection(cont,std::inserter(ans_dates,ans_dates.begin()));
    } else {
      date_union(cont,std::inserter(ans_dates,ans_dates.begin()));
    }

    if(ans_dates.size() == 0) {
      return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
    }

    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(ans_dates.size(),cbind_total_cols(cont));
    std::copy(ans_dates.begin(), ans_dates.end(), ans.getDates());
    // FIXME: set colnames

    // if union, then we must initialize the values of ans to NA
    if(!intersection) {
      for(TSDIM i = 0; i < ans.nrow() * ans.ncol(); i++) {
	ans.getData()[i] = numeric_traits<TDATA>::NA();
      }
    }

    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::const_iterator it = cont.begin();

    // walk along iterator and map values into ans
    TSDIM offset = 0;
    while(it != cont.end()) {
      cbind_map_values(ans, *it, offset);
      offset += it->ncol();
      ++it;
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
	   template<typename ELEM, typename = std::allocator<ELEM> > class CONT,
	   typename II>

  void
  date_intersection(const CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
		    II output_dates)
  {
    std::vector<TDATE> inBuff;
    std::vector<TDATE> outBuff;

    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::const_iterator it = cont.begin();

    // pre-load dates for first series
    std::copy(it->getDates(),it->getDates() + it->nrow(),
	      std::inserter(inBuff,inBuff.begin()));

    for(it = cont.begin() + 1; it != cont.end(); it++) {
      outBuff.clear();
      set_intersection(inBuff.begin(),inBuff.end(),
		       it->getDates(),it->getDates() + it->nrow(),
		       std::inserter(outBuff,outBuff.begin()));
      // swap buffs
      inBuff.clear();
      std::copy(outBuff.begin(),outBuff.end(),
		std::inserter(inBuff,inBuff.begin()));
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
	   typename II>
  void
  date_union(const CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
	     II output_dates)
  {
    std::set<TDATE> ans;
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::const_iterator it;

    // walk through all tseries adding all dates
    // let std::set drop dups for us
    for(it = cont.begin(); it != cont.end(); it++) {
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
  cbind_total_cols(const CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont)
  {
    TSDIM ans = 0;
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::const_iterator it;
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
  cbind_max_nrow(const CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont)
  {
    std::vector<TSDIM> nrows;
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::const_iterator it;
    for(it = cont.begin(); it != cont.end(); it++) {
      nrows.push_back(it->nrow());
    }
    return *max_element(nrows.begin(), nrows.end());
  }

  template<class TDATE,
	   class TDATA,
	   class TSDIM,
	   template<typename,typename,typename> class TSDATABACKEND,
	   template<typename> class DatePolicy,
	   template<class U, class V, class W,
		    template<typename,typename,typename> class DATABACKEND,
		    template<typename> class DP> class TSeries>
  void
  cbind_map_values(TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ans,
		   const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& ts_values,
		   const TSDIM offset)
  {
    RangeSpecifier<TDATE,TSDIM> range(ans.getDates(),
				      ts_values.getDates(),
				      ans.nrow(),
				      ts_values.nrow());

    TDATA* ans_data = ans.getData();

    //advance ans_data by offset
    ans_data += ans.nrow() * offset;

    for(TSDIM col = 0; col < ts_values.ncol(); col++) {
      RangeIterator<const TDATA*, const TSDIM*> ts_data_iter(ts_values.getData()+ ts_values.nrow()*col,
							     range.getArg2());
      std::copy(ts_data_iter,ts_data_iter + range.getSize(),ans_data);
      ans_data += ans.nrow();
    }
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
	   typename II>
  void cbind_create_colnames(const CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >& cont,
			     II new_colnames)
  {
    typename CONT<TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> >::const_iterator it;
    for(it = cont.begin(); it != cont.end(); it++) {
      std::vector<std::string> this_cnames;
      // if series has non-empty colnames, pad them into new_colnames
      // otherwise pad empty strings

      //FIXME: add a test for all series having empty colnames, then ans should not have blnk strings set as colnames
      if(this_cnames.size()) {
	for(std::vector<std::string>::const_iterator cn_it = this_cnames.begin();it != this_cnames.end(); cn_it++) {
	  *new_colnames++ = *cn_it;
	}
      } else {
	for(int i = 0; i < it->ncol(); i++) {
	  *new_colnames++ = std::string("");
	}
      }
    }

  }

} // namespace tslib

#endif // CBIND_HPP

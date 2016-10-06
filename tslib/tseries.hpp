///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016  Whit Armstrong                                    //
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
#pragma once
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <iostream>
#include <tslib/intersection.map.hpp>

namespace tslib {

template <typename IDX, typename V, typename DIM, template <typename, typename, typename> class BACKEND,
          template <typename> class DatePolicy, template <typename> class NumericTraits>
class TSeries {
private:
  BACKEND<IDX, V, DIM> tsdata_;

public:
  typedef typename BACKEND<IDX, V, DIM>::const_index_iterator const_index_iterator;
  typedef typename BACKEND<IDX, V, DIM>::index_iterator index_iterator;
  typedef typename BACKEND<IDX, V, DIM>::const_data_iterator const_data_iterator;
  typedef typename BACKEND<IDX, V, DIM>::data_iterator data_iterator;
  typedef typename std::vector<const_data_iterator> const_row_iterator;
  typedef typename std::vector<data_iterator> row_iterator;

  // ctors
  TSeries(const TSeries &T) : tsdata_(T.tsdata_) {}
  TSeries(BACKEND<IDX, V, DIM> &tsdata) : tsdata_{tsdata} {}
  TSeries(DIM nrow, DIM ncol) : tsdata_{nrow, ncol} {}

  // accessors
  const BACKEND<IDX, V, DIM> &getBackend() const { return tsdata_; }
  const std::vector<std::string> getColnames() const { return tsdata_.getColnames(); }
  const bool setColnames(const std::vector<std::string> &names) { return tsdata_.setColnames(names); }

  const DIM nrow() const { return tsdata_.nrow(); }
  const DIM ncol() const { return tsdata_.ncol(); }

  const_index_iterator index_begin() const { return tsdata_.index_begin(); }
  index_iterator index_begin() { return tsdata_.index_begin(); }
  const_index_iterator index_end() const { return tsdata_.index_end(); }
  index_iterator index_end() { return tsdata_.index_end(); }

  const_data_iterator col_begin(DIM i) const { return tsdata_.col_begin(i); }
  data_iterator col_begin(DIM i) { return tsdata_.col_begin(i); }

  const_data_iterator col_end(DIM i) const { return tsdata_.col_end(i); }
  data_iterator col_end(DIM i) { return tsdata_.col_end(i); }

  const_row_iterator getRow(DIM n) const {
    const_row_iterator ans(ncol());
    for (DIM i = 0; i < ncol(); ++i) {
      const_data_iterator this_col = col_begin(i);
      std::advance(this_col, n);
      ans[i] = this_col;
    }
    return ans;
  }

  TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits> lag(DIM n) const {
    if (n >= nrow()) { throw std::logic_error("lag: n > nrow of time series."); }
    TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits> ans(nrow() - n, ncol());

    // copy over dates
    const_index_iterator beg{index_begin()};
    std::advance(beg, n);
    std::copy(beg, index_end(), ans.index_begin());

    // copy colnames
    ans.setColnames(getColnames());

    for (DIM i = 0; i < ncol(); ++i) {
      const_data_iterator src_beg{col_begin(i)};
      const_data_iterator src_end{col_end(i)};
      data_iterator dst_beg{ans.col_begin(i)};
      std::advance(src_end, -n);
      std::copy(src_beg, src_end, dst_beg);
    }
    return ans;
  }
};

template <typename IDX, typename V, typename DIM, template <typename, typename, typename> class BACKEND,
          template <typename> class DatePolicy, template <typename> class NumericTraits>
std::ostream &operator<<(std::ostream &os, const TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits> &ts) {
  std::vector<std::string> cnames(ts.getColnames());

  if (cnames.size()) {
    // shift out to be in line w/ first column of values (space is for dates column)
    os << "\t";
    for (auto name : cnames) { os << name << " "; }
  }

  typename TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits>::const_index_iterator idx{ts.index_begin()};
  typename TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits>::const_index_iterator idx_end{ts.index_end()};
  typename TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits>::const_row_iterator row_iter(ts.getRow(0));

  for (; idx != idx_end; ++idx) {
    os << DatePolicy<IDX>::toString(*idx, "%Y-%m-%d %T") << "\t";
    for (auto &value : row_iter) {
      if (NumericTraits<V>::ISNA(*value)) {
        os << "NA";
      } else {
        os << *value << " ";
      }
      os << " ";
      ++value; // next row
    }
    os << "\n"; // no flush
  }
  return os;
}

} // namespace tslib

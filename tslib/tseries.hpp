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
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <tslib/functors.hpp>
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
  TSeries(TSeries &&) = default;

  // accessors
  const BACKEND<IDX, V, DIM> &getBackend() const { return tsdata_; }

  const std::vector<std::string> getColnames() const { return tsdata_.getColnames(); }
  const DIM getColnamesSize() const { return tsdata_.getColnamesSize(); }
  const bool hasColnames() const { return getColnamesSize() > 0 ? true : false; }
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

  /* compound ops only for scalar ops, self-assignment doesn't make sense when nrow is changing */
  template <typename S>
  TSeries<IDX, typename std::common_type<V, S>::type, DIM, BACKEND, DatePolicy, NumericTraits> &operator+=(S rhs) {
    for (DIM i = 0; i < ncol(); ++i) {
      for (auto iter = col_begin(i); iter != col_end(i); ++iter) {
        if (!NumericTraits<V>::ISNA(*iter)) { *iter += rhs; }
      }
    }
    return *this;
  }

  template <typename S>
  TSeries<IDX, typename std::common_type<V, S>::type, DIM, BACKEND, DatePolicy, NumericTraits> &operator-=(S rhs) {
    for (DIM i = 0; i < ncol(); ++i) {
      for (auto iter = col_begin(i); iter != col_end(i); ++iter) {
        if (!NumericTraits<V>::ISNA(*iter)) { *iter -= rhs; }
      }
    }
    return *this;
  }

  template <typename S>
  TSeries<IDX, typename std::common_type<V, S>::type, DIM, BACKEND, DatePolicy, NumericTraits> &operator*=(S rhs) {
    for (DIM i = 0; i < ncol(); ++i) {
      for (auto iter = col_begin(i); iter != col_end(i); ++iter) {
        if (!NumericTraits<V>::ISNA(*iter)) { *iter *= rhs; }
      }
    }
    return *this;
  }

  template <typename S>
  TSeries<IDX, typename std::common_type<V, S>::type, DIM, BACKEND, DatePolicy, NumericTraits> &operator/=(S rhs) {
    for (DIM i = 0; i < ncol(); ++i) {
      for (auto iter = col_begin(i); iter != col_end(i); ++iter) {
        if (!NumericTraits<V>::ISNA(*iter)) { *iter /= rhs; }
      }
    }
    return *this;
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

template <template <typename, typename> class Pred, typename IDX, typename U, typename V, typename DIM,
          template <typename, typename, typename> class BACKEND, template <typename> class DatePolicy,
          template <typename> class NumericTraits>
auto binary_opp(const TSeries<IDX, U, DIM, BACKEND, DatePolicy, NumericTraits> &lhs,
                const TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits> &rhs) {

  typedef typename std::common_type<U, V>::type RV;
  Pred<U, V> pred;

  if (lhs.ncol() != rhs.ncol() && lhs.ncol() != 1 && rhs.ncol() != 1) {
    throw std::logic_error("Number of colums must match. or one time series must be a single column.");
  }

  auto rowmap{intersection_map(lhs.index_begin(), lhs.index_end(), rhs.index_begin(), rhs.index_end())};
  std::cout << rowmap.first.size() << std::endl;
  for (std::size_t i = 0; i < rowmap.first.size(); ++i) {
    std::cout << rowmap.first[i] << ":" << rowmap.second[i] << std::endl;
  }
  TSeries<IDX, typename std::common_type<U, V>::type, DIM, BACKEND, DatePolicy, NumericTraits> res(
      rowmap.first.size(), std::max(lhs.ncol(), rhs.ncol()));

  // set colnames from larger of two args but prefer lhs
  if (lhs.getColnamesSize() >= rhs.getColnamesSize()) {
    res.setColnames(lhs.getColnames());
  } else if (rhs.hasColnames()) {
    res.setColnames(rhs.getColnames());
  }

  // set index from lhs
  auto idx{res.index_begin()};
  const auto lhs_idx{lhs.index_begin()};
  // for (auto i : rowmap.first) { *idx = lhs_idx[rowmap.first[i]]; }
  for (auto i : rowmap.first) { *idx = lhs_idx[i]; }
  for (DIM nc = 0; nc < res.ncol(); ++nc) {
    const auto lhs_col{lhs.col_begin(nc)}, rhs_col{rhs.col_begin(nc)};
    auto res_col{res.col_begin(nc)};
    for (DIM nr = 0; nr < res.nrow(); ++nr) {
      U lhs_val{lhs_col[rowmap.first[nr]]};
      V rhs_val{rhs_col[rowmap.second[nr]]};
      res_col[nr] = NumericTraits<V>::ISNA(lhs_val) || NumericTraits<U>::ISNA(rhs_val) ? NumericTraits<RV>::NA()
                                                                                       : pred(lhs_val, rhs_val);
    }
  }
  return res;
}

template <typename IDX, typename V, typename U, typename DIM, template <typename, typename, typename> class BACKEND,
          template <typename> class DatePolicy, template <typename> class NumericTraits>
TSeries<IDX, typename std::common_type<V, U>::type, DIM, BACKEND, DatePolicy, NumericTraits>
operator+(const TSeries<IDX, V, DIM, BACKEND, DatePolicy, NumericTraits> &lhs,
          const TSeries<IDX, U, DIM, BACKEND, DatePolicy, NumericTraits> &rhs) {
  return binary_opp<PlusFunctor>(lhs, rhs);
}

} // namespace tslib

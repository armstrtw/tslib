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
#pragma once

#include <vector>
#include <string>
#include <iterator>

namespace tslib {

template <typename IDX, typename T, typename DIM> class VectorBackend {
private:
  DIM ncol_;
  std::vector<IDX> index_;
  std::vector<T> data_;
  std::vector<std::string> colnames_;
  // col major offset
  size_t column_offset(DIM i) const { return static_cast<size_t>(i) * index_.size(); }

public:
  typedef typename std::vector<IDX>::iterator index_iterator;
  typedef typename std::vector<IDX>::const_iterator const_index_iterator;

  typedef typename std::vector<T>::const_iterator const_data_iterator;
  typedef typename std::vector<T>::iterator data_iterator;

  VectorBackend() = delete;
  VectorBackend(const VectorBackend &t) : ncol_{t.ncol_}, index_{t.index_}, data_{t.data_}, colnames_{t.colnames_} {}
  VectorBackend(DIM nrow, DIM ncol) : ncol_{ncol}, index_(nrow), data_(nrow * ncol), colnames_{} {}
  VectorBackend &operator=(const VectorBackend &rhs) = delete;

  DIM nrow() const { return static_cast<DIM>(index_.size()); }
  DIM ncol() const { return ncol_; }

  const_index_iterator index_begin() const { return index_.begin(); }
  index_iterator index_begin() { return index_.begin(); }
  const_index_iterator index_end() const { return index_.end(); }
  index_iterator index_end() { return index_.end(); }

  const_data_iterator col_begin(DIM i) const { return data_.begin() + column_offset(i); } // head of column
  data_iterator col_begin(DIM i) { return data_.begin() + column_offset(i); }
  const_data_iterator col_end(DIM i) const { return data_.begin() + column_offset(i + 1L); } // head of next column
  data_iterator col_end(DIM i) { return data_.begin() + column_offset(i + 1L); }

  const bool setColnames(const std::vector<std::string> &names) {
    if (static_cast<DIM>(names.size()) == ncol_) {
      colnames_ = names;
      return true;
    }
    return false;
  }

  const std::vector<std::string> getColnames() const { return colnames_; }
  const bool hasColnames() const { return colnames_.size() > 0 ? true : false; }
};

} // namespace tslib

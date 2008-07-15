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

#ifndef RANGE_ITERATOR_HPP
#define RANGE_ITERATOR_HPP
#include <iterator>

namespace tslib {

  using std::iterator_traits;

  template<typename DATAPOINTER, typename INDEXPOINTER>
  class RangeIterator {
  private:
    const DATAPOINTER data_pointer_;
    INDEXPOINTER index_pointer_;
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename std::iterator_traits<DATAPOINTER>::value_type value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    RangeIterator(const DATAPOINTER data_pointer, const INDEXPOINTER index_pointer);
    RangeIterator(const RangeIterator& r);

    RangeIterator<DATAPOINTER,INDEXPOINTER>& operator++();
    RangeIterator<DATAPOINTER,INDEXPOINTER> operator++(const int i);
    RangeIterator<DATAPOINTER,INDEXPOINTER>& operator--();
    RangeIterator<DATAPOINTER,INDEXPOINTER> operator--(const int i);

    RangeIterator<DATAPOINTER,INDEXPOINTER>& operator+=(const int i);
    RangeIterator<DATAPOINTER,INDEXPOINTER>& operator-=(const int i);

    RangeIterator<DATAPOINTER,INDEXPOINTER> operator+(const int i) const;
    RangeIterator<DATAPOINTER,INDEXPOINTER> operator-(const int i) const;

    typename std::iterator_traits<DATAPOINTER>::value_type operator*();

    friend bool operator==(RangeIterator& lhs, RangeIterator& rhs) {
      return (lhs.data_pointer_ == rhs.data_pointer_) && (lhs.index_pointer_ == rhs.index_pointer_);
    }

    friend bool operator!=(RangeIterator& lhs, RangeIterator& rhs) {
      return (lhs.data_pointer_ != rhs.data_pointer_) || (lhs.index_pointer_ != rhs.index_pointer_);
    }

    friend difference_type operator-(RangeIterator& lhs, RangeIterator& rhs) {
      return (lhs.index_pointer_ - rhs.index_pointer_);
    }
  };

  template<typename DATAPOINTER, typename INDEXPOINTER>
  RangeIterator<DATAPOINTER,INDEXPOINTER>::RangeIterator(const DATAPOINTER data_pointer, const INDEXPOINTER index_pointer) :
    data_pointer_(data_pointer),
    index_pointer_(index_pointer) {
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER>::RangeIterator(const RangeIterator& r) :
    data_pointer_(r.data_pointer_),
    index_pointer_(r.index_pointer_) {
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER>& RangeIterator<DATAPOINTER,INDEXPOINTER>::operator++() {
    ++index_pointer_;
    return *this;
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER> RangeIterator<DATAPOINTER,INDEXPOINTER>::operator++(const int i) {
    RangeIterator<DATAPOINTER,INDEXPOINTER> tmp(*this);
    ++*this;
    return tmp;
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER>& RangeIterator<DATAPOINTER,INDEXPOINTER>::operator--() {
    --index_pointer_;
    return *this;
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER> RangeIterator<DATAPOINTER,INDEXPOINTER>::operator--(const int i) {
    RangeIterator<DATAPOINTER,INDEXPOINTER> tmp(*this);
    --*this;
    return tmp;
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER>& RangeIterator<DATAPOINTER,INDEXPOINTER>::operator+=(const int i) {
    index_pointer_ += i;
    return *this;
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER>& RangeIterator<DATAPOINTER,INDEXPOINTER>::operator-=(const int i) {
    index_pointer_ -= i;
    return *this;
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER> RangeIterator<DATAPOINTER,INDEXPOINTER>::operator+(const int i) const {
    return RangeIterator(data_pointer_, index_pointer_ + i);
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  RangeIterator<DATAPOINTER,INDEXPOINTER> RangeIterator<DATAPOINTER,INDEXPOINTER>::operator-(const int i) const {
    return RangeIterator(data_pointer_, index_pointer_ - i);
  }

  template<typename DATAPOINTER, typename INDEXPOINTER>
  inline
  typename std::iterator_traits<DATAPOINTER>::value_type RangeIterator<DATAPOINTER,INDEXPOINTER>::operator*() {
    return data_pointer_[ *index_pointer_ ];
  }

} // namespace tslib

#endif // RANGE_ITERATOR_HPP

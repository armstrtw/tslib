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

#ifndef RANGESPECIFIER_HPP
#define RANGESPECIFIER_HPP

#include <iostream>

namespace tslib {

  template<typename T, typename U>
  class RangeSpecifier {
  private:
    T* dates_;  // intersection dates_
    U* index1_;   // index of intersections of index1_
    U* index2_;   // index of intersections of index2_
    U size_;    // also the length of all the internal vectors: dates_, index1_, index2_

  public:
    ~RangeSpecifier();
    RangeSpecifier(const RangeSpecifier &r); // not allowed!!
    RangeSpecifier(T *dates_1,
		   T *dates_2,
		   const U length_index1_,
		   const U length_index2_);

    const T* getDates() const;
    const U* getArg1() const;
    const U* getArg2() const;
    const U getSize() const;
    void print() const;
  };

  template<typename T, typename U>
  RangeSpecifier<T,U>::~RangeSpecifier() {
    delete [] dates_;
    delete [] index1_;
    delete [] index2_;
  }

  template<typename T, typename U>
  RangeSpecifier<T,U>::RangeSpecifier(T *dates_1,
				      T *dates_2,
				      const U length_index1_,
				      const U length_index2_) {

    // find size of smaller of the two arguments
    const U bufferSize = length_index1_ < length_index2_ ? length_index1_ : length_index2_;

    // alloc new buffer for dates_, size_ is smallest of the two arguments
    dates_ = new T[bufferSize];

    // if we can't get memory then print error and return NULL range specifier
    if(dates_==NULL) {
      std::cerr << "ERROR: RangeSpecifier" << std::endl;
      std::cerr << "out of memory" << std::endl;
      size_ = 0;
      index1_ = NULL;
      index2_ = NULL;
      dates_ = NULL;
      return;
    }

    // find size of date intersection
    T* dates_end =  std::set_intersection(dates_1, dates_1+length_index1_, dates_2, dates_2+length_index2_, dates_);

    size_ = std::distance(dates_,dates_end);

    // if there is no intersection then specifier has no size, and elements should be set to null
    // must delete buffer of dates_ that we allocated
    if(size_==0) {
      delete []dates_;
      index1_ = NULL;
      index2_ = NULL;
      dates_ = NULL;
    }

    // since we have some dates_ in the intersection
    // we can alloc space for the intersection points
    index1_ = new U[size_];
    index2_ = new U[size_];

    // if we cannot get memory, then print error, release any memory that was allocated and return
    if(index1_==NULL || index2_==NULL) {
      std::cerr << "ERROR: RangeSpecifier::RangeSpecifier" << std::endl;
      std::cerr << "out of memory" << std::endl;
      delete []index1_;
      delete []index2_;
      delete []dates_;
      index1_ = NULL;
      index2_ = NULL;
      dates_ = NULL;
      size_ = 0;
      return;
    }

    // placeholders to find intersecting dates_
    U date1_index = 0;
    U date2_index = 0;
    U dates_index = 0;

    // go through all the dates_ in the intersection
    while(dates_index < size_) {

      // catch up arg 1 to dates_ intersection
      while(dates_[dates_index] != dates_1[date1_index]) {
	date1_index++;
      }

      // catch up arg 2 to dates_ intersection
      while(dates_[dates_index] != dates_2[date2_index]) {
	date2_index++;
      }

      // when equal, record position of matching elements
      if(dates_[dates_index] == dates_1[date1_index] && dates_[dates_index] == dates_2[date2_index]) {
	index1_[dates_index] = date1_index;
	index2_[dates_index] = date2_index;
	dates_index++;
	date1_index++;
	date2_index++;
      }
    }
  }

  template<typename T, typename U>
  const U RangeSpecifier<T,U>::getSize() const {
    return size_;
  }

  template<typename T, typename U>
  const T* RangeSpecifier<T,U>::getDates() const {
    return dates_;
  }

  template<typename T, typename U>
  const U* RangeSpecifier<T,U>::getArg1() const {
    return index1_;
  }

  template<typename T, typename U>
  const U* RangeSpecifier<T,U>::getArg2() const {
    return index2_;
  }

  template<typename T, typename U>
  void RangeSpecifier<T,U>::print() const {
    for(U i = 0; i < size_; i++) {
      std::cout << dates_[i] << ":" << index1_[i] << ":" << index2_[i] << std::endl;
    }
  }

} // namespace tslib

#endif

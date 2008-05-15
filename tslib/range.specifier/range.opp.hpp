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

#ifndef RANGE_OPP_HPP
#define RANGE_OPP_HPP

#include <tslib/range.specifier/range.iterator.hpp>

template<typename T, typename U, typename RangeIterator, typename BinaryOpp>
inline
void applyRangeOpp(T ans_iter, RangeIterator iter1, RangeIterator iter2, const U size, BinaryOpp opp) {
  for(U i = 0; i < size; i++) {
    *ans_iter = opp( *iter1 , *iter2 );
    ++ans_iter;
    ++iter1;
    ++iter2;
  }
}

#endif // RANGE_OPP_HPP

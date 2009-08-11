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

#ifndef OPEN_HPP
#define OPEN_HPP

#include <iterator>
#include <tslib/utils/numeric.traits.hpp>

namespace tslib {

  template<typename T>
  class openTraits {
  public:
    typedef T ReturnType;
  };

  template<typename ReturnType>
  class Open {
  public:
    template<typename T>
    static inline ReturnType apply(T beg, T end) {
      return *beg;
    }
  };

} // namespace tslib

#endif // OPEN_HPP

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

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <iostream>
#include <tslib/tseries.hpp>
#include <vector.backend.hpp>
#include <gregorian.date.policy.hpp>
#include <numeric.traits.hpp>

using namespace tslib;

// LDL = long, double, long
// DDL = double, double, long
typedef TSeries<long, double, long, VectorBackend, GregorianDate, RNT> LDL_ts;

TEST_CASE("Constructors.") {

  SECTION("null_constructor_test") {
    LDL_ts x(10, 2);
    std::iota(x.index_begin(), x.index_end(), 0);
    std::iota(x.col_begin(0), x.col_end(0), 1);
    std::iota(x.col_begin(1), x.col_end(1), 11);
    std::cout << x << std::endl;
    LDL_ts y(x.lag(1));
    std::cout << y << std::endl;
  }
}

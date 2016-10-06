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
    int NR{10}, NC{2};
    LDL_ts x(NR, NC);
    REQUIRE(x.nrow() == NR);
    REQUIRE(x.ncol() == NC);
    std::iota(x.index_begin(), x.index_end(), 0);
    std::iota(x.col_begin(0), x.col_end(0), 1);
    std::iota(x.col_begin(1), x.col_end(1), 11);
    LDL_ts y(x.lag(1));
    REQUIRE(y.nrow() == NR - 1);
    REQUIRE(y.ncol() == NC);
  }

  SECTION("date intersection") {
    size_t LEN{10};
    std::vector<int> u(LEN);
    std::vector<int> v(LEN);
    int m = {0};
    std::generate(u.begin(), u.end(), [&m] { return m++; });
    int n = {0};
    std::generate(v.begin(), v.end(), [&n] { return n += 2; });

    std::pair<std::vector<size_t>, std::vector<size_t>> xymap{intersection_map(u.begin(), u.end(), v.begin(), v.end())};
    REQUIRE(xymap.first.size() == xymap.second.size());

    // extract values at intersection points from u and v
    std::vector<int> uvals, vvals;
    std::transform(xymap.first.begin(), xymap.first.end(), std::back_inserter(uvals), [&u](size_t i) { return u[i]; });
    std::transform(xymap.second.begin(), xymap.second.end(), std::back_inserter(vvals), [&v](size_t i) { return v[i]; });
    REQUIRE(std::equal(uvals.begin(), uvals.begin(), vvals.begin()));
  }
}

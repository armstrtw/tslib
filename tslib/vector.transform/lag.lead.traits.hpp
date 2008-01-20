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

#ifndef LAG_LEAD_TRAITS_HPP
#define LAG_LEAD_TRAITS_HPP

template<typename T>
class lagleadTraits;

template<>
class lagleadTraits<double> {
public:
  typedef double ReturnType;
  typedef int ArgType;  // for periods
};

template<>
class lagleadTraits<int> {
public:
  typedef int ReturnType;
  typedef int ArgType; // for periods
};


#endif // LAG_LEAD_TRAITS_HPP

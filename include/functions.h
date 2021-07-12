/* 
Copyright (C) 2021 Adele Zaini, Elisa Legnani

This file is part of PhotorealisticRendering.

PhotorealisticRendering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PhotorealisticRendering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _functions_h_
#define _functions_h_

#include <cmath>
#include <string>

using namespace std;

inline bool are_close(float x, float y, float epsilon = 1e-4) {
  return fabs(x - y) < epsilon;
}

inline string float_to_string(float number){
  string float_num = to_string(number);
  string first_num = float_num.substr(0, float_num.find("."));
  string second_num = float_num.substr(float_num.find("."));
  string final_num = second_num.substr(0,second_num.find("0"));
  return first_num+final_num;
}

#endif

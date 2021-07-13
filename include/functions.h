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
#include <stdio.h>
#include <time.h>

using namespace std;

/**
 Check if two floating-point paraments (if deviation < 1e-4).
 Needed to avoid floating-point approximation limits.
 */
inline bool are_close(float x, float y, float epsilon = 1e-4) {
  return fabs(x - y) < epsilon;
}

/**
 * Convert a float into a string, avoiding displaying several zeroes after last significant decimal
 */

inline string float_to_string(float number){
  string float_num = to_string(number);
  string first_num = float_num.substr(0, float_num.find("."));
  string second_num = float_num.substr(float_num.find("."));
  string final_num = second_num.substr(0,second_num.find("0"));
  return first_num+final_num;
}

/**
 * Return a string of current date_time (format YYYY-MM-DD.HH:mm:ss)
 */

inline string current_date_time() {
    time_t now = time(0);
    struct tm  tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);

    return buf;
}

inline string get_format(string filename){
  size_t find = filename.find_last_of(".");
  return filename.substr(find);
}

inline string get_path(string filename_with_path){
  size_t find = filename_with_path.find_last_of("/");
  return filename_with_path.substr(0,find+1);
}

#endif

/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the “Software”), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of
the Software. THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include "scene.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("Input file", "[inputstream]") {

    stringstream sstr;
    sstr << "abc   \nd\nef";
    InputStream stream(sstr);

    REQUIRE(stream.location.line_num == 1);
    REQUIRE(stream.location.col_num == 1);

    REQUIRE(stream.read_character() == 'a');
    REQUIRE(stream.location.line_num == 1);
    REQUIRE(stream.location.col_num == 2);

    stream.unread_character('A');
    REQUIRE(stream.location.line_num == 1);
    REQUIRE(stream.location.col_num == 1);

    REQUIRE(stream.read_character() == 'A');
    REQUIRE(stream.location.line_num == 1);
    REQUIRE(stream.location.col_num == 2);

    REQUIRE(stream.read_character() == 'b');
    REQUIRE(stream.location.line_num == 1);
    REQUIRE(stream.location.col_num == 3);

    REQUIRE(stream.read_character() == 'c');
    REQUIRE(stream.location.line_num == 1);
    REQUIRE(stream.location.col_num == 4);

    stream.skip_whitespaces();

    REQUIRE(stream.read_character() == 'd');
    REQUIRE(stream.location.line_num == 2);
    REQUIRE(stream.location.col_num == 2);

    REQUIRE(stream.read_character() == '\n');
    REQUIRE(stream.location.line_num == 3);
    REQUIRE(stream.location.col_num == 1);

    REQUIRE(stream.read_character() == 'e');
    REQUIRE(stream.location.line_num == 3);
    REQUIRE(stream.location.col_num == 2);

    REQUIRE(stream.read_character() == 'f');
    REQUIRE(stream.location.line_num == 3);
    REQUIRE(stream.location.col_num == 3);

    REQUIRE(stream.read_character() == '\0');
}
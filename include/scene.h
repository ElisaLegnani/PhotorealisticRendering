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

#ifndef _scene_h_
#define _scene_h_

enum class TokenType {
  LITERAL_NUMBER,
  LITERAL_STRING,
  SYMBOL,
  KEYWORD,
};

union TokenValue {
  float number;
  string string;

  TokenValue() : number{0.0} {}
  ~TokenValue() {}
}:

struct Token {
  TokenType type;
  TokenValue value;

  Token() : type(TokenType::LITERAL_NUMBER) {}

  void assign_number(float val) {
      type = TokenType::LITERAL_NUMBER;
      value.number = val;
  }

  void assign_string(const string & s) {
      type = TokenType::LITERAL_STRING;
      value.string = s;
  }
};

#endif
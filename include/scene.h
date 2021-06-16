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

#include <iostream>

using namespace std;

/*#define WHITESPACE = {" ", "\t", "\n", "\r"}
#define SYMBOLS = {"(",")","<",">","[","]","*"}*/

#ifndef _scene_h_
#define _scene_h_

struct SourceLocation {
  string file_name{""};
  int line_num{};
  int col_num{};
};

enum class Keyword{
  MATERIAL, PLANE, SPHERE, DIFFUSE, SPECULAR, UNIFORM, CHECKERED, IMAGE, IDENTITY, TRANSLATION, ROTATION_X, ROTATION_Y, ROTATION_Z, SCALING, CAMERA, ORTHOGONAL, PERSPECTIVE, FLOAT,
};

enum class TokenType {
  LITERAL_NUMBER, LITERAL_STRING, SYMBOL, KEYWORD, IDENTIFIER, STOPTOKEN,
};


union TokenValue {
  float number;
  string str;
  char symbol;
  Keyword key;

  TokenValue() : number{0.0} {}
  ~TokenValue() {}
};

struct Token {
  SourceLocation location;
  TokenType type;
  TokenValue value;

  Token(SourceLocation loc = SourceLocation()) : location{loc} {}

  void assign_number(float val) {
      type = TokenType::LITERAL_NUMBER;
      value.number = val;
  }

  void assign_string(const string & s) {
      type = TokenType::LITERAL_STRING;
      value.str = s;
  }
  
  void assign_symbol(char sym) {
      type = TokenType::SYMBOL;
      value.symbol = sym;
  }
  
  void assign_keyword(Keyword keyword) {
      type = TokenType::KEYWORD;
      value.key = keyword;
  }
  
  void assign_identifier(const string & s) {
      type = TokenType::IDENTIFIER;
      value.str = s;
  }
  
  void assign_stoptoken() {
      type = TokenType::STOPTOKEN;
  }
  
};

struct ParserError{
  SourceLocation location;
  string message;
};

struct InputStream{
  
  istream &stream_in;
  SourceLocation location;
  int tabulations;
  char saved_char;
  SourceLocation saved_location;
  Token saved_token;
  
  InputStream(istream &stream, int tab = 8) : stream_in{stream}, tabulations{tab} {}
   
  void update_location(char character){
    if(character == '\0') return;
    else if (character == '\n'){
      location.line_num += 1;
      location.col_num += 1;
    }else if(character =='\t'){
      location.col_num += tabulations;
    }else{
      location.col_num += 1;
    }
  }
  
  char read_character(){
    
    char ch;
    if(saved_char != '\0'){
      ch = saved_char;
      saved_char = '\0';
    }else{
      stream_in >> ch;
    }
    saved_location = location;
    update_location(ch);
    
    return ch;
  }
  
  void unread_character(char ch){
    if(saved_char == '\0') return;
    saved_char = ch;
    location = saved_location;
  }
  
  void skip_whitespaces(){
    char ch = read_character();
    while(ch == ' ' or ch == '\t' or ch == '\n' or ch == '\r'){
      ch = read_character();
      if(ch == '\0') return;
    }
    unread_character(ch);
  }
  
};

#endif

/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED “AS
IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "imagetracer.h"
#include "render.h"
#include <iostream>
#include <unordered_map>

using namespace std;

#define WHITESPACES string { " #\t\n\r" }
#define SYMBOLS string { "()<>[]*," }

#ifndef _scene_h_
#define _scene_h_

struct SourceLocation {
  string file_name{""};
  int line_num{};
  int col_num{};
};

enum class Keyword {
  NEW,
  MATERIAL,
  PLANE,
  SPHERE,
  DIFFUSE,
  SPECULAR,
  UNIFORM,
  CHECKERED,
  IMAGE,
  IDENTITY,
  TRANSLATION,
  ROTATION_X,
  ROTATION_Y,
  ROTATION_Z,
  SCALING,
  CAMERA,
  ORTHOGONAL,
  PERSPECTIVE,
  FLOAT,
};

enum class TokenType {
  LITERAL_NUMBER,
  LITERAL_STRING,
  SYMBOL,
  KEYWORD,
  IDENTIFIER,
  STOPTOKEN,
};

union TokenValue {
  float number;
  string str;
  char symbol;
  Keyword keyword;

  TokenValue() : number{0.0} {}
  TokenValue(const TokenValue &token) : str{token.str} {}
  ~TokenValue() {}
};

struct Token {
  SourceLocation location;
  TokenType type;
  TokenValue value;

  Token(SourceLocation loc = SourceLocation()) : location{loc} {}

  Token(const Token &);

  Token operator=(const Token &);

  void assign_number(float);

  void assign_string(string);

  void assign_symbol(char);

  void assign_keyword(Keyword);

  void assign_identifier(string);

  void assign_stoptoken();
};

struct GrammarError : public runtime_error {
  SourceLocation location;
  GrammarError(const string &message, SourceLocation loc): 
      location{loc}, runtime_error{message} {}
};

struct Scene {
  unordered_map<string, Material> materials;
  World world;
  shared_ptr<Camera> camera;
  unordered_map<string, float> float_variables;
  vector<string> overridden_variables;
};

struct InputStream {

  istream &stream_in;
  SourceLocation location;
  int tabulations;
  char saved_char = '\0';
  SourceLocation saved_location;
  Token saved_token;

  InputStream(istream &stream, string file_name = "", int tab = 8)
      : stream_in{stream}, location{file_name, 1, 1}, tabulations{tab} {}

  void update_location(char);

  char read_character();

  void unread_character(char);

  void skip_whitespaces_and_comments();

  Token parse_string_token();

  Token parse_float_token(char);

  Token parse_keyword_or_identifier_token(char);

  Token read_token();

  void unread_token(Token);

  void expect_symbol(char);

  Keyword expect_keyword(vector<Keyword>);

  float expect_number(Scene);

  string expect_string();

  string expect_identifier();

  Vec parse_vector(Scene);

  Color parse_color(Scene);

  shared_ptr<Pigment> parse_pigment(Scene);

  shared_ptr<BRDF> parse_brdf(Scene);

  tuple<string, Material> parse_material(Scene);

  Transformation parse_transformation(Scene);

  Sphere parse_sphere(Scene);

  Plane parse_plane(Scene);

  shared_ptr<Camera> parse_camera(Scene);

  Scene parse_scene (unordered_map<string, float>);
  
};

#endif

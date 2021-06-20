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

#include "render.h"
#include "imagetracer.h"
#include <iostream>
#include <unordered_map>

using namespace std;

#define WHITESPACES string{" \t\n\r"}
#define SYMBOLS string{"()<>[]*"}

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

unordered_map<string, Keyword> KEYWORDS = {
  {"new", Keyword::NEW},
  {"material", Keyword::MATERIAL},
  {"plane", Keyword::PLANE},
  {"sphere", Keyword::SPHERE},
  {"diffuse", Keyword::DIFFUSE},
  {"specular", Keyword::SPECULAR},
  {"uniform", Keyword::UNIFORM},
  {"checkered", Keyword::CHECKERED},
  {"image", Keyword::IMAGE},
  {"identity", Keyword::IDENTITY},
  {"translation", Keyword::TRANSLATION},
  {"rotation_x", Keyword::ROTATION_X},
  {"rotation_y", Keyword::ROTATION_Y},
  {"rotation_z", Keyword::ROTATION_Z},
  {"scaling", Keyword::SCALING},
  {"camera", Keyword::CAMERA},
  {"orthogonal", Keyword::ORTHOGONAL},
  {"perspective", Keyword::PERSPECTIVE},
  {"float", Keyword::FLOAT},
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
  TokenValue(const TokenValue &token): str{token.str} {}
  ~TokenValue() {}
};

struct Token {
  SourceLocation location;
  TokenType type;
  TokenValue value;

  Token(SourceLocation loc = SourceLocation()) : location{loc} {}
  Token(const Token &token): location{token.location}, type{token.type} {} // implementare tokenvalue
  Token operator = (const Token &token) {} // implementare

  void assign_number(float val) {
    type = TokenType::LITERAL_NUMBER;
    value.number = val;
  }

  void assign_string(const string &s) {
    type = TokenType::LITERAL_STRING;
    value.str = s;
  }

  void assign_symbol(char sym) {
    type = TokenType::SYMBOL;
    value.symbol = sym;
  }

  void assign_keyword(Keyword keyword) {
    type = TokenType::KEYWORD;
    value.keyword = keyword;
  }

  void assign_identifier(const string &s) {
    type = TokenType::IDENTIFIER;
    value.str = s;
  }

  void assign_stoptoken() { type = TokenType::STOPTOKEN; }
};

struct GrammarError : public runtime_error {
  SourceLocation location;
  explicit GrammarError(const string &message, SourceLocation loc) noexcept
      : location{loc}, runtime_error(message) {}
};

struct Scene {
  unordered_map<string, Material> materials;
  World world;
  shared_ptr<Camera> camera;
  unordered_map<string, float> float_variables;
  // overridden_variables: Set[str] = field(default_factory=set) --> implementare
};

struct InputStream {

  istream &stream_in;
  SourceLocation location;
  int tabulations;
  char saved_char;
  SourceLocation saved_location;
  Token saved_token;

  InputStream(istream &stream, string file_name = "", int tab = 8)
      : stream_in{stream}, location{file_name, 1, 1}, tabulations{tab} {}

  void update_location(char ch) {
    if (ch == '\0')
      return;
    else if (ch == '\n') {
      location.line_num += 1;
      location.col_num = 1;
    } else if (ch == '\t') {
      location.col_num += tabulations;
    } else {
      location.col_num += 1;
    }
  }

  char read_character() {

    char ch;
    if (saved_char != '\0') {
      ch = saved_char;
      saved_char = '\0';
    } else {
      stream_in.get(ch);
    }
    saved_location = location;
    update_location(ch);

    return ch;
  }

  void unread_character(char ch) {
    stream_in.putback(ch);
    location = saved_location;
  }

  void skip_whitespaces() {
    char ch = read_character();
    while (WHITESPACES.find(ch) != string::npos) { // string::npos if no matches found
      ch = read_character();
      if (ch == '\0')
        return;
    }
    unread_character(ch);
  }

  Token parse_string_token() {
    string str{};
    while (true) {
      char ch = read_character();
      if (ch=='"')
        break;
      if (ch=='\0')
        throw GrammarError("unterminated string", location);
      str += ch;
    }
    Token token(location);
    token.assign_string(str);
    return token;
  }

  Token parse_float_token(char first_ch) {
    string str{first_ch};
    float value;
    while (true) {
      char ch = read_character();
      if (!isdigit(ch) || ch != '.' || ch != 'e' || ch != 'E') {
        unread_character(ch);
        break;
      }
      str += ch;
    }
    try {
      value = stof(str);
    } catch (invalid_argument) {
      throw GrammarError(str + " is an invalid floating-point number", location);
    }
    Token token(location);
    token.assign_number(value);
    return token;
  }

  Token parse_keyword_or_identifier_token(char first_ch) {
    string str{first_ch};
    while (true) {
      char ch = read_character();
      if (!isalnum(ch) || ch != '_') {
        unread_character(ch);
        break;
      }
      str += ch;
    }
    Token token(location);
    /*try { // If it is a keyword, it must be listed in the KEYWORDS dictionary --> implementare
      token.assign_keyword(str);
    } catch (invalid_argument) { // If it is not a keyword, it must be an identifier
      token.assign_identifier(str);
    }*/
    return token;
  }

  Token read_token() {

    if(saved_token.location.line_num != 0 || saved_token.location.col_num != 0) { 
      Token result = saved_token;
      //saved_token = Token(); --> implementare
      return result;
    }

    skip_whitespaces();
    char ch = read_character();

    if (ch == '\0') { // No more characters in the file
      Token token(location);
      token.assign_stoptoken();
      return token;
    } else if (ch == '#') { // Start of a comment: keep reading until the end of the line
      while (ch != '\r' || ch != '\n' || ch != '\0')
        ch = read_character();
      skip_whitespaces();
    } else {
      unread_character(ch);
    }
    // At this point we must check what kind of token begins with the "ch" character
    // First, we save the position in the stream
    SourceLocation token_location = location;
    Token token(location);
    // Now we read again ch (which was put back using self.unread_char)
    ch = read_character();
    if (SYMBOLS.find(ch) != string::npos) { // One-character symbol
      token.assign_symbol(ch); 
      return token;
    } else if (ch == '"') // A literal string 
      return parse_string_token();
    else if (isdigit(ch) || ch == '+' || ch == '-' || ch == '.') // A floating-point number
      return parse_float_token(ch);
    else if (isalpha(ch) || ch == '_') // Alphabetic character, thus it must either a keyword or a identifier
      return parse_keyword_or_identifier_token(ch);
    else // We got some weird character, like '@` or `&`
      throw GrammarError(ch + " is an invalid character", location);
  }

  /*void unread_token(Token token) { --> implementare = Token
    if(saved_token.location.line_num != 0 || saved_token.location.col_num != 0)
      saved_token = token;
  }*/

  void expect_symbol(char sym) {
    Token token = read_token();
    if(token.type != TokenType::SYMBOL || token.value.symbol != sym)
      throw GrammarError("got " + string{token.value.symbol} + " instead of " + sym, token.location);
  }

  Keyword expect_keyword(vector<Keyword> keywords) {
    Token token = read_token();
    if(token.type != TokenType::KEYWORD)
      throw GrammarError("expected a keyword instead of " /*+ string{token.value.keyword}*/, token.location);
    if(find(keywords.begin(), keywords.end(), token.value.keyword) == keywords.end())
      throw GrammarError("expected one of the keywords instead of " /*+ string{token.value.keyword}*/, token.location);
    return token.value.keyword;
  }


  float expect_number(Scene scene) {
    Token token = read_token();
    if(token.type == TokenType::LITERAL_NUMBER)
      return token.value.number;
    else if(token.type == TokenType::IDENTIFIER) {
      string variable_name = token.value.str;
      if(scene.float_variables.find(token.value.str) == scene.float_variables.end())
        throw GrammarError("unknown variable " + token.value.str, token.location);
      return scene.float_variables[variable_name];
    } else
      throw GrammarError("got " + token.value.str + " instead of a number", token.location);
  }

  string expect_string() {
    Token token = read_token();
    if(token.type != TokenType::LITERAL_STRING)
      throw GrammarError("got " + token.value.str + " instead of a string", token.location);
    return token.value.str;
  }

  string expect_identifier() {
    Token token = read_token();
    if(token.type != TokenType::IDENTIFIER)
      throw GrammarError("got " + token.value.str + " instead of an identifier", token.location);
    return token.value.str;
  }

  Vec parse_vector(Scene scene) {
    expect_symbol('[');
    float x = expect_number(scene);
    expect_symbol(',');
    float y = expect_number(scene);
    expect_symbol(',');
    float z = expect_number(scene);
    expect_symbol(']');

    return Vec(x, y, z);
  }

  Color parse_color(Scene scene) {
    expect_symbol('<');
    float red = expect_number(scene);
    expect_symbol(',');
    float green = expect_number(scene);
    expect_symbol(',');
    float blue = expect_number(scene);
    expect_symbol('>');

    return Color(red, green, blue);
  }

  shared_ptr<Pigment> parse_pigment(Scene scene) {
    shared_ptr<Pigment> result;

    Keyword keyword = expect_keyword(vector{Keyword::UNIFORM, Keyword::CHECKERED, Keyword::IMAGE});
    expect_symbol('(');

    if (keyword == Keyword::UNIFORM) {
      Color color = parse_color(scene);
      result = make_shared<UniformPigment>(color);
    } else if (keyword == Keyword::CHECKERED) {
      Color color1 = parse_color(scene);
      expect_symbol(',');
      Color color2 = parse_color(scene);
      expect_symbol(',');
      int num_of_steps = int(expect_number(scene));
      result = make_shared<CheckeredPigment>(color1, color2, num_of_steps);
    } else if (keyword == Keyword::IMAGE) {
      string file_name = expect_string();
      HdrImage image(file_name);
      result = make_shared<ImagePigment>(image);
    }

    expect_symbol(')');
    return result;
  }

  shared_ptr<BRDF> parse_brdf(Scene scene) {
    Keyword keyword = expect_keyword(vector{Keyword::DIFFUSE, Keyword::SPECULAR});
    expect_symbol('(');
    shared_ptr<Pigment> pigment = parse_pigment(scene);
    expect_symbol(')');

    if (keyword == Keyword::DIFFUSE)
      return make_shared<DiffuseBRDF>(pigment);
    else if (keyword == Keyword::SPECULAR)
      return make_shared<SpecularBRDF>(pigment);
  }

  tuple<string, Material> parse_material(Scene scene) {
    string name = expect_identifier();

    expect_symbol('(');
    shared_ptr<BRDF> brdf = parse_brdf(scene);
    expect_symbol(',');
    shared_ptr<Pigment> emitted_radiance = parse_pigment(scene);
    expect_symbol(')');

    return tuple<string, Material>{name, Material(brdf, emitted_radiance)};
  }

  Transformation parse_transformation(Scene scene) {
    Transformation result = Transformation();

    while (true) {
      Keyword keyword = expect_keyword(vector{Keyword::IDENTITY, Keyword::TRANSLATION,
        Keyword::ROTATION_X, Keyword::ROTATION_Y, Keyword::ROTATION_Z,
        Keyword::SCALING});

      if (keyword == Keyword::TRANSLATION){
        expect_symbol('(');
        result = result * translation(parse_vector(scene));
        expect_symbol(')');
      } else if (keyword == Keyword::ROTATION_X){
        expect_symbol('(');
        result = result * rotation_x(expect_number(scene));
        expect_symbol(')');
      } else if (keyword == Keyword::ROTATION_Y){
        expect_symbol('(');
        result = result * rotation_y(expect_number(scene));
        expect_symbol(')');
      } else if (keyword == Keyword::ROTATION_Z){
        expect_symbol('(');
        result = result * rotation_z(expect_number(scene));
        expect_symbol(')');
      } else if (keyword == Keyword::SCALING){
        expect_symbol('(');
        result = result * scaling(parse_vector(scene));
        expect_symbol(')');
      }

      // We must peek the next token to check if there is another transformation that is being
      // chained or if the sequence ends; thus, this is a LL(1) parser
      Token next_token = read_token();
      if(next_token.type != TokenType::SYMBOL || next_token.value.symbol != '*'){
        //unread_token(next_token); --> implementare!
        break;
      }
    }
    return result;  
  }

  Sphere parse_sphere(Scene scene) {
    expect_symbol('(');

    string material_name = expect_identifier();
    /*if (material_name not in scene.materials.keys() { --> implementare
      // We raise the exception here because input_file is pointing to the end of the wrong identifier
      throw GrammarError("unknown material " + material_name, location);
    }*/

    expect_symbol(',');
    Transformation transformation = parse_transformation(scene);
    expect_symbol(')');

    return Sphere(transformation, scene.materials[material_name]);
  }

  Plane parse_plane(Scene scene) {
    expect_symbol('(');

    string material_name = expect_identifier();
   /* if (material_name not in scene.materials.keys() { --> implementare
      // We raise the exception here because input_file is pointing to the end of the wrong identifier
      throw GrammarError("unknown material " + material_name, location);
    }*/

    expect_symbol(',');
    Transformation transformation = parse_transformation(scene);
    expect_symbol(')');

    return Plane(transformation, scene.materials[material_name]);
  }

  shared_ptr<Camera> parse_camera(Scene scene) {
    shared_ptr<Camera> result;
    expect_symbol('(');
    Keyword keyword = expect_keyword(vector{Keyword::PERSPECTIVE, Keyword::ORTHOGONAL});
    expect_symbol(',');
    Transformation transformation = parse_transformation(scene);
    expect_symbol(',');
    float aspect_ratio = expect_number(scene);
    expect_symbol(',');
    float distance = expect_number(scene);
    expect_symbol(')');

    if (keyword == Keyword::PERSPECTIVE)
      result = make_shared<PerspectiveCamera>(distance, aspect_ratio, transformation);
    else if (keyword == Keyword::ORTHOGONAL)
      result = make_shared<OrthogonalCamera>(aspect_ratio, transformation);

    return result;
  }
};

#endif


// parse scene !
// poi ricontrollare tutto e risolvere errori!
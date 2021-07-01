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

#include "scene.h"

using namespace std;

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

Token ::Token(const Token &token) : location{token.location}, type{token.type} {
  if (token.type == TokenType::LITERAL_NUMBER)
    value.number = token.value.number;
  else if (token.type == TokenType::LITERAL_STRING ||
           token.type == TokenType::IDENTIFIER)
    new ((void *)&value.str) string{token.value.str};
  else if (token.type == TokenType::SYMBOL)
    value.symbol = token.value.symbol;
  else if (token.type == TokenType::KEYWORD)
    value.keyword = token.value.keyword;
}

Token Token ::operator=(const Token &token) {
  location = token.location;
  type = token.type;
  if (token.type == TokenType::LITERAL_NUMBER)
    value.number = token.value.number;
  else if (token.type == TokenType::LITERAL_STRING ||
           token.type == TokenType::IDENTIFIER)
    new ((void *)&value.str) string{token.value.str};
  else if (token.type == TokenType::SYMBOL)
    value.symbol = token.value.symbol;
  else if (token.type == TokenType::KEYWORD)
    value.keyword = token.value.keyword;
  return *this;
}

void Token::assign_number(float val) {
  type = TokenType::LITERAL_NUMBER;
  value.number = val;
}

void Token::assign_string(string s) {
  type = TokenType::LITERAL_STRING;
  new ((void *)&value.str) string{s};
}

void Token::assign_symbol(char sym) {
  type = TokenType::SYMBOL;
  value.symbol = sym;
}

void Token::assign_keyword(Keyword keyword) {
  type = TokenType::KEYWORD;
  value.keyword = keyword;
}

void Token::assign_identifier(string s) {
  type = TokenType::IDENTIFIER;
  new ((void *)&value.str) string{s};
}

void Token::assign_stoptoken() { type = TokenType::STOPTOKEN; }

void InputStream::update_location(char ch) {
  if (ch == '\0') {
  } // Nothing
  else if (ch == '\n') {
    location.line_num += 1;
    location.col_num = 1;
  } else if (ch == '\t') {
    location.col_num += tabulations;
  } else {
    location.col_num += 1;
  }
}

char InputStream::read_character() {
  char ch;
  if (saved_char != '\0') {
    ch = saved_char;
    saved_char = '\0';
  } else {
    stream_in.get(ch);
    if (stream_in.eof()) {
      ch = '\0';
    }
  }
  saved_location = location;
  update_location(ch);
  return ch;
}

void InputStream::unread_character(char ch) {
  stream_in.putback(ch);
  location = saved_location;
}

void InputStream::skip_whitespaces_and_comments() {
  char ch = read_character();
  while (WHITESPACES.find(ch) !=
         string::npos) { // string::npos if no matches found
    if (ch == '#') {
      // Start of a comment: keep reading until the end of the line
      while (ch != '\r' && ch != '\n' && ch != '\0')
        ch = read_character();
    }
    ch = read_character();
    if (ch == '\0')
      return;
  }
  unread_character(ch);
}

Token InputStream::parse_string_token() {
  string str{};
  while (true) {
    char ch = read_character();
    if (ch == '"')
      break;
    if (ch == '\0')
      throw GrammarError("unterminated string", location);
    str.push_back(ch);
  }
  Token token(location);
  token.assign_string(str);
  return token;
}

Token InputStream::parse_float_token(char first_ch) {
  string str{first_ch};
  float value;
  while (true) {
    char ch = read_character();
    if (!isdigit(ch) && ch != '.' && ch != 'e' && ch != 'E') {
      unread_character(ch);
      break;
    }
    str.push_back(ch);
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

Token InputStream::parse_keyword_or_identifier_token(char first_ch) {
  string str{first_ch};
  while (true) {
    char ch = read_character();
    if (!isalnum(ch) && ch != '_') {
      unread_character(ch);
      break;
    }    
    str.push_back(ch);
  }
  Token token(location);
  try { // If it is a keyword, it must be listed in the KEYWORDS dictionary
    token.assign_keyword(KEYWORDS.at(str));
  } catch (out_of_range) { // If it is not a keyword, it must be an identifier
    token.assign_identifier(str);
  }
  return token;
}

Token InputStream::read_token() {

  if (saved_token.location.line_num != 0 || saved_token.location.col_num != 0) {
    Token result = saved_token;
    saved_token = Token();
    return result;
  }

  skip_whitespaces_and_comments();
  char ch = read_character();

  if (ch == '\0') { // No more characters in the file
    Token token(location);
    token.assign_stoptoken();
    return token;
  }

  // At this point we must check what kind of token begins with the "ch"
  // character First, we save the position in the stream
  SourceLocation token_location = location;
  Token token(location);

  if (SYMBOLS.find(ch) != string::npos) { // One-character symbol
    token.assign_symbol(ch);
    return token;
  } else if (ch == '"') { // A literal string
    return parse_string_token();
  } else if (isdigit(ch) || ch == '+' || ch == '-' ||
             ch == '.') { // A floating-point number
    return parse_float_token(ch);
  } else if (isalpha(ch) || ch == '_') { // Alphabetic character, thus it must
                                         // either a keyword or a identifier
    return parse_keyword_or_identifier_token(ch);
  } else { // We got some weird character, like '@` or `&`
    throw GrammarError("got an invalid character", location);
  }
}

void InputStream::unread_token(Token token) {
  if (saved_token.location.line_num == 0 && saved_token.location.col_num == 0)
    saved_token = token;
}

void InputStream::expect_symbol(char sym) {
  Token token = read_token();
  if (token.type != TokenType::SYMBOL || token.value.symbol != sym)
    throw GrammarError("got " + string{token.value.symbol} + " instead of " +
                           sym,
                       token.location);
}

Keyword InputStream::expect_keyword(vector<Keyword> keywords) {
  Token token = read_token();
  if (token.type != TokenType::KEYWORD)
    throw GrammarError("expected a keyword", token.location);
  if (find(keywords.begin(), keywords.end(), token.value.keyword) ==
      keywords.end())
    throw GrammarError("expected one of the keywords", token.location);
  return token.value.keyword;
}

float InputStream::expect_number(Scene scene) {
  Token token = read_token();
  if (token.type == TokenType::LITERAL_NUMBER)
    return token.value.number;
  else if (token.type == TokenType::IDENTIFIER) {
    string variable_name = token.value.str;
    if (scene.float_variables.find(token.value.str) ==
        scene.float_variables.end())
      throw GrammarError("unknown variable " + token.value.str, token.location);
    return scene.float_variables[variable_name];
  } else
    throw GrammarError("got " + token.value.str + " instead of a number",
                       token.location);
}

string InputStream::expect_string() {
  Token token = read_token();
  if (token.type != TokenType::LITERAL_STRING)
    throw GrammarError("got " + token.value.str + " instead of a string",
                       token.location);
  return token.value.str;
}

string InputStream::expect_identifier() {
  Token token = read_token();
  if (token.type != TokenType::IDENTIFIER)
    throw GrammarError("got " + token.value.str + " instead of an identifier",
                       token.location);
  return token.value.str;
}

Vec InputStream::parse_vector(Scene scene) {
  expect_symbol('[');
  float x = expect_number(scene);
  expect_symbol(',');
  float y = expect_number(scene);
  expect_symbol(',');
  float z = expect_number(scene);
  expect_symbol(']');

  return Vec(x, y, z);
}

Color InputStream::parse_color(Scene scene) {
  expect_symbol('<');
  float red = expect_number(scene);
  expect_symbol(',');
  float green = expect_number(scene);
  expect_symbol(',');
  float blue = expect_number(scene);
  expect_symbol('>');

  return Color(red, green, blue);
}

shared_ptr<Pigment> InputStream::parse_pigment(Scene scene) {
  shared_ptr<Pigment> result;

  Keyword keyword = expect_keyword(
      vector{Keyword::UNIFORM, Keyword::CHECKERED, Keyword::IMAGE});
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

shared_ptr<BRDF> InputStream::parse_brdf(Scene scene) {
  Keyword keyword = expect_keyword(vector{Keyword::DIFFUSE, Keyword::SPECULAR});
  expect_symbol('(');
  shared_ptr<Pigment> pigment = parse_pigment(scene);
  expect_symbol(')');

  if (keyword == Keyword::DIFFUSE)
    return make_shared<DiffuseBRDF>(pigment);
  else // if (keyword == Keyword::SPECULAR)
    return make_shared<SpecularBRDF>(pigment);
}

tuple<string, Material> InputStream::parse_material(Scene scene) {
  string name = expect_identifier();

  expect_symbol('(');
  shared_ptr<BRDF> brdf = parse_brdf(scene);
  expect_symbol(',');
  shared_ptr<Pigment> emitted_radiance = parse_pigment(scene);
  expect_symbol(')');

  return tuple<string, Material>{name, Material(brdf, emitted_radiance)};
}

Transformation InputStream::parse_transformation(Scene scene) {
  Transformation result = Transformation();

  while (true) {
    Keyword keyword = expect_keyword(
        vector{Keyword::IDENTITY, Keyword::TRANSLATION, Keyword::ROTATION_X,
               Keyword::ROTATION_Y, Keyword::ROTATION_Z, Keyword::SCALING});

    if (keyword == Keyword::TRANSLATION) {
      expect_symbol('(');
      result = result * translation(parse_vector(scene));
      expect_symbol(')');
    } else if (keyword == Keyword::ROTATION_X) {
      expect_symbol('(');
      result = result * rotation_x(expect_number(scene));
      expect_symbol(')');
    } else if (keyword == Keyword::ROTATION_Y) {
      expect_symbol('(');
      result = result * rotation_y(expect_number(scene));
      expect_symbol(')');
    } else if (keyword == Keyword::ROTATION_Z) {
      expect_symbol('(');
      result = result * rotation_z(expect_number(scene));
      expect_symbol(')');
    } else if (keyword == Keyword::SCALING) {
      expect_symbol('(');
      result = result * scaling(parse_vector(scene));
      expect_symbol(')');
    }

    // We must peek the next token to check if there is another transformation
    // that is being chained or if the sequence ends; thus, this is a LL(1) parser
    Token next_token = read_token();
    if (next_token.type == TokenType::SYMBOL &&
        next_token.value.symbol != '*') {
      unread_token(next_token);
      break;
    }
  }
  return result;
}

Sphere InputStream::parse_sphere(Scene scene) {
  expect_symbol('(');

  string material_name = expect_identifier();
  if (scene.materials.find(material_name) == scene.materials.end()) {
    // We raise the exception here because input_file is pointing to the end
    // of the wrong identifier
    throw GrammarError("unknown material " + material_name, location);
  }

  expect_symbol(',');
  Transformation transformation = parse_transformation(scene);
  expect_symbol(')');

  return Sphere(transformation, scene.materials[material_name]);
}

Plane InputStream::parse_plane(Scene scene) {
  expect_symbol('(');

  string material_name = expect_identifier();
  if (scene.materials.find(material_name) == scene.materials.end()) {
    // We raise the exception here because input_file is pointing to the end
    // of the wrong identifier
    throw GrammarError("unknown material " + material_name, location);
  }

  expect_symbol(',');
  Transformation transformation = parse_transformation(scene);
  expect_symbol(')');

  return Plane(transformation, scene.materials[material_name]);
}

shared_ptr<Camera> InputStream::parse_camera(Scene scene) { 
  shared_ptr<Camera> result;
  expect_symbol('(');
  Keyword keyword =
      expect_keyword(vector{Keyword::PERSPECTIVE, Keyword::ORTHOGONAL});
  expect_symbol(',');
  Transformation transformation = parse_transformation(scene);
  expect_symbol(',');
  float aspect_ratio = expect_number(scene);
  float distance;
  if (keyword == Keyword::PERSPECTIVE){
    expect_symbol(',');
    distance = expect_number(scene);
  }
  expect_symbol(')');

  if (keyword == Keyword::PERSPECTIVE)
    result =
        make_shared<PerspectiveCamera>(distance, aspect_ratio, transformation);
  else if (keyword == Keyword::ORTHOGONAL)
    result = make_shared<OrthogonalCamera>(aspect_ratio, transformation);

  return result;
}

Scene InputStream::parse_scene(unordered_map<string, float> variables) {
  Scene scene;
  scene.float_variables = variables;
  for(auto var : variables)
    scene.overridden_variables.push_back(var.first);

  while (true) {
    Token what = read_token();

    if (what.type == TokenType::STOPTOKEN)
      break;

    if (what.type != TokenType::KEYWORD)
      throw GrammarError("expected a keyword", location);

    if (what.value.keyword == Keyword::FLOAT) {
      string variable_name = expect_identifier();

      // Save this for the error message
      SourceLocation variable_loc = location;

      expect_symbol('(');
      float variable_value = expect_number(scene);
      expect_symbol(')');

      if (scene.float_variables.find(variable_name) !=
              scene.float_variables.end() &&
          find(scene.overridden_variables.begin(),
               scene.overridden_variables.end(),
               variable_name) == scene.overridden_variables.end())
        throw GrammarError("variable " + variable_name + " cannot be redefined",
                           variable_loc);

      if (find(scene.overridden_variables.begin(),
               scene.overridden_variables.end(),
               variable_name) == scene.overridden_variables.end())
        // Only define the variable if it was not defined by the user *outside*
        // the scene file (e.g., from the command line)
        scene.float_variables[variable_name] = variable_value;

    } else if (what.value.keyword == Keyword::SPHERE) {
      scene.world.add_shape(make_shared<Sphere>(parse_sphere(scene)));

    } else if (what.value.keyword == Keyword::PLANE) {
      scene.world.add_shape(make_shared<Plane>(parse_plane(scene)));

    } else if (what.value.keyword == Keyword::CAMERA) {
      if (scene.camera)
        throw GrammarError("You cannot define more than one camera", location);
      scene.camera = parse_camera(scene);

    } else if (what.value.keyword == Keyword::MATERIAL) {
      tuple<string, Material> material = parse_material(scene);
      scene.materials[get<string>(material)] = get<Material>(material);
    }
  }
  return scene;
}

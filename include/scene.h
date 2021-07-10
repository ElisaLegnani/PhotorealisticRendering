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

#include "imagetracer.h"
#include "render.h"
#include <iostream>
#include <unordered_map>

using namespace std;

#define WHITESPACES string { " #\t\n\r" }
#define SYMBOLS string { "()<>[]{}*," }

#ifndef _scene_h_
#define _scene_h_

/**
 *Position in the source file (to be updated step by step while lexer works)
 *
 *@param
 *@param
 *@param
 */
struct SourceLocation {
  string file_name{""};
  int line_num{};
  int col_num{};
};

/**
 *List of all possible keywords recognized by the lexer
 */
enum class Keyword {
  NEW,
  MATERIAL,
  PLANE,
  SPHERE,
  BOX,
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

//––––––––––––– Tagged union Token –––––––––––––
/**
 *List of all possible token types recognized by the lexer (TAG)
 */
enum class TokenType {
  LITERAL_NUMBER,
  LITERAL_STRING,
  SYMBOL,
  KEYWORD,
  IDENTIFIER,
  STOPTOKEN,
};

/**
 *Token with variables, default constructor and destructor (UNION)
 */
union TokenValue {
  float number;
  string str;
  char symbol;
  Keyword keyword;

  TokenValue() : number{0.0} {}
  TokenValue(const TokenValue &token) : str{token.str} {}
  ~TokenValue() {}
};

/**
 *Token struct with methods to assign TokenType and TokenValue (STRUCT)
 */
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


/**
 * The scene with all the elements passed by the input file
 */
struct Scene {
  unordered_map<string, Material> materials;
  World world;
  shared_ptr<Camera> camera;
  unordered_map<string, float> float_variables;
  vector<string> overridden_variables;
};


//––––––––––––– Lexer & Parser –––––––––––––

/**
 *Raise an exception when lexer or parser finds a grammar error
 *
 *@param message error message
 */
struct GrammarError : public runtime_error {
  
  GrammarError(const string &message, SourceLocation loc): runtime_error{message + " -> position (" + to_string(int(loc.line_num)) + "," + to_string(int(loc.col_num)) + ")"} {}
};

/**
 * Struct gathering all the LEXER and PARSER functionalities.
 * It works on an input stream and it analyses it checking for lexical or sintattic error.
 */
struct InputStream {

  istream &stream_in;
  SourceLocation location;
  int tabulations;
  char saved_char = '\0';
  SourceLocation saved_location;
  Token saved_token;

  InputStream(istream &stream, string file_name = "", int tab = 8)
      : stream_in{stream}, location{file_name, 1, 1}, tabulations{tab} {}

    //––––––––––––– Single characters –––––––––––––
  /**
   * Update the location in the file stream
   *
   * @param ch character of the (previous) location to update
   */
  void update_location(char);

  /**
   * Read a character from the stream and update location
   */
  char read_character();

  /**
   * Go back to the previous character.
   * Useful when the look ahead functionality is needed
   */
  void unread_character(char);

  /**
   * Pass over whitespaces and comments until an "effective" character is found
   */
  void skip_whitespaces_and_comments();

  
  //––––––––––––– Tokens –––––––––––––
  
  /**
   * Read a string from the stream and create a StringToken,
   * print an error message if the string does not have an end.
   */
  Token parse_string_token();

  /**
   * Read a floating point number and create a NumberToken,
   * print an error message if it is an unvalid floating point number.
   */
  Token parse_float_token(char);

  /**
   * Read a sequence of characters, verify if it's a keywork, otherwise it's an identifier.
   * and create a KeywordToken or an IdentifierToken.
   */
  Token parse_keyword_or_identifier_token(char);

  /**
   *Interprent the sequence of characters from the stream and create a Token,
   *except if meeting an invalid character (ex: & or @)
   */
  Token read_token();
  
  /**
   * Go back to the previous token.
   * Useful when the look ahead functionality is needed (ex: transformations)
   */
  void unread_token(Token);

  //––––––––––––– Structs/classes –––––––––––––
  
  /**
   * Check if the present token from the stream matches with the given symbol
   */
  void expect_symbol(char);

  /**
   * Check if the present token in the stream matches with the given keyword
   *
   * @param keyword given one
   * @return keyword from stream (ridden token)
   */
  Keyword expect_keyword(vector<Keyword>);

  /**
   * Check if the present token in the stream matches with a number or a variable in the given scene
   *
   * @param scene from which extract variable to check
   * @return number or scene variable from stream (ridden token)
   */
  float expect_number(Scene);

  /**
   * Check if the present token in the stream matches with the given string
   *
   * @return string from stream (ridden token)
   */
  string expect_string();
  
  /**
   * Check if the present token in the stream matches with the given identifier
   *
   * @return identifier from stream (ridden token)
   */
    string expect_identifier();

  /**
   * Create a Vec if a sequence of characters follows the order [number,number,number]
   *
   * @return Vec(x,y,z)
   */
  Vec parse_vector(Scene);

  /**
   * Create a Color if a sequence of characters follows the order <number,number,number>
   *
   * @return Color(red,green,blue)
   */
  Color parse_color(Scene);

  /**
   * Create a Point if a sequence of characters follows the order {number,number,number}
   *
   * @return Point(x,y,z)
   */
  Point parse_point(Scene);

  /**
   * Create a Pigment if a KewwordToken is UNIFORM/CHECKERED/IMAGE folowed by relative arguments
   *
   * @return UniformPigment(color) or CheckeredPigment(color1, color2, num_of_steps) or ImagePigment(image)
   */
  shared_ptr<Pigment> parse_pigment(Scene);

  /**
   * Create a BRDF if a KewwordToken is DIFFUSE/SPECULAR followed by the pigment argument
   *
   * @return DiffuseBRDF(pigment) or SpecularBRDF(pigment)
   */
  shared_ptr<BRDF> parse_brdf(Scene);

  /**
   * Create a Material if a sequence of characters follows the order identifier(brdf,pigment)
   *
   * @return Material(brdf, emitted_radiance)
   */
  tuple<string, Material> parse_material(Scene);

  /**
   * Create a Transformation if a Keyword is IDENTITY/TRANSLATION/ROTATION_X/ROTATION_Y/ROTATION_Z/SCALING followed by a Vec/number.
   * It can recognize a composition of transformations.
   *
   */
  Transformation parse_transformation(Scene);

  /**
   * Create a Sphere if a sequence of characters follows the order identifier(material, transformation)
   *
   * @return Sphere(transformation, scene.materials[material_name])
   */
  Sphere parse_sphere(Scene);

  /**
   * Create a Plane if a sequence of characters follows the order identifier(material, transformation)
   *
   * @return Plane(transformation, scene.materials[material_name])
   */
  Plane parse_plane(Scene);

  /**
   * Create a Box if a sequence of characters follows the order identifier(material, point, point, transformation)
   *
   * @return Box(point, point, transformation, scene.materials[material_name])
   */
  Box parse_box(Scene);

  /**
   * Create a Camera if a KewwordToken is PERSPECTIVE/ORTHOGONAL folowed by relative arguments
   *
   * @return PerspectiveCamera(distance, aspect_ratio,transformation) or OrthogonalCamera(aspect_ratio, transformation)
   */
  shared_ptr<Camera> parse_camera(Scene);

  /**
   * Read from the input stream and create the scene
   *
   * @return Scene
   */
  Scene parse_scene (unordered_map<string, float>);
  
};

#endif

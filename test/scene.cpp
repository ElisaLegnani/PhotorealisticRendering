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

    stream.skip_whitespaces_and_comments();

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


TEST_CASE("Lexer", "[token]") {

    stringstream sstr;
    sstr << "# This is a comment"
        "\n# This is another comment"
        "\nnew material sky_material("
        "\n    diffuse(image(\"my_file.pfm\")),"
        "\n    <5.0, 500.0, 300.0>"
        "\n) # Comment at the end of the line\n";
    InputStream stream(sstr);

    Token token = stream.read_token();
    REQUIRE(token.type == TokenType::KEYWORD);
    REQUIRE(token.value.keyword == Keyword::NEW);

    token = stream.read_token();
    REQUIRE(token.type == TokenType::KEYWORD);
    REQUIRE(token.value.keyword == Keyword::MATERIAL);

    token = stream.read_token();
    REQUIRE(token.type == TokenType::IDENTIFIER);
    REQUIRE(token.value.str == "sky_material");

    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == '(');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::KEYWORD);
    REQUIRE(token.value.keyword == Keyword::DIFFUSE);

    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == '(');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::KEYWORD);
    REQUIRE(token.value.keyword == Keyword::IMAGE);

    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == '(');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::LITERAL_STRING);
    REQUIRE(token.value.str == "my_file.pfm");

    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == ')');
  
    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == ')');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == ',');
    
    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == '<');
    
    token = stream.read_token();
    REQUIRE(token.type == TokenType::LITERAL_NUMBER);
    REQUIRE(are_close(token.value.number, 5.0));
    
    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == ',');
    
    token = stream.read_token();
    REQUIRE(token.type == TokenType::LITERAL_NUMBER);
    REQUIRE(are_close(token.value.number, 500.0));
    
    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == ',');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::LITERAL_NUMBER);
    REQUIRE(are_close(token.value.number, 300.0));
    
    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == '>');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::SYMBOL);
    REQUIRE(token.value.symbol == ')');

    token = stream.read_token();
    REQUIRE(token.type == TokenType::STOPTOKEN);
    
}

TEST_CASE("Parser", "[scene]") {

    stringstream sstr;
    sstr << "float clock(150)"
        "\n"
        "\nmaterial sky_material("
        "\n    diffuse(uniform(<0, 0, 0>)),"
        "\n    uniform(<0.7, 0.5, 1>)"
        "\n)"
        "\n"
        "\n# Here is a comment"
        "\n"
        "\nmaterial ground_material("
        "\n    diffuse(checkered(<0.3, 0.5, 0.1>,"
        "\n                      <0.1, 0.2, 0.5>, 4)),"
        "\n    uniform(<0, 0, 0>)"
        "\n)"
        "\n"
        "\nmaterial sphere_material("
        "\n    specular(uniform(<0.5, 0.5, 0.5>)),"
        "\n    uniform(<0, 0, 0>)"
        "\n)"
        "\n"
        "\nplane (sky_material, translation([0, 0, 100]) * rotation_y(clock))"
        "\nplane (ground_material, identity)"
        "\n"
        "\nsphere(sphere_material, translation([0, 0, 1]))"
        "\n"
        "\ncamera(perspective, rotation_z(30) * translation([-4, 0, 1]), 1.0, 2.0)"
        "\n";

    InputStream stream(sstr);
    unordered_map<string, float> variables;

    Scene scene = stream.parse_scene(variables);

    // Check that the float variables are ok

    REQUIRE(scene.float_variables.size() == 1);
    REQUIRE(scene.float_variables.find("clock")!=scene.float_variables.end());
    REQUIRE(scene.float_variables["clock"] == 150.0);

    // Check that the materials are ok

    REQUIRE(scene.materials.size() == 3);
    REQUIRE(scene.materials.find("sphere_material")!=scene.materials.end());
    REQUIRE(scene.materials.find("sky_material")!=scene.materials.end());
    REQUIRE(scene.materials.find("ground_material")!=scene.materials.end());

    Material sphere_material = scene.materials["sphere_material"];
    Material sky_material = scene.materials["sky_material"];
    Material ground_material = scene.materials["ground_material"];

    //REQUIRE(sky_material.brdf==DiffuseBRDF); -----------------------> how do I test these?
    //REQUIRE(sky_material.brdf->pigment==UniformPigment);
    //REQUIRE(sky_material.brdf->pigment->color.is_close(Color(0, 0, 0)));

    //REQUIRE(ground_material.brdf==DiffuseBRDF);
    //REQUIRE(ground_material.brdf->pigment==CheckeredPigment);
    //REQUIRE(ground_material.brdf->pigment->color1.is_close(Color(0.3, 0.5, 0.1)));
    //REQUIRE(ground_material.brdf->pigment->color1.is_close(Color(0.1, 0.2, 0.5)));
    //REQUIRE(ground_material.brdf->pigment->color1.num_of_steps == 4);

    //REQUIRE(sphere_material.brdf==SpecularBRDF);
    //REQUIRE(sphere_material.brdf->pigment==UniformPigment);
    //REQUIRE(sphere_material.brdf->pigment->color.is_close(Color(0.5, 0.5, 0.5)));

    //REQUIRE(sky_material.emitted_radiance == UniformPigment);
    //REQUIRE(sky_material.emitted_radiance.color.is_close(Color(0.7, 0.5, 1.0)));
    //REQUIRE(ground_material.emitted_radiance == UniformPigment);
    //REQUIRE(ground_material.emitted_radiance.color.is_close(Color(0, 0, 0)));
    //REQUIRE(sphere_material.emitted_radiance == UniformPigment);
    //REQUIRE(sphere_material.emitted_radiance.color.is_close(Color(0, 0, 0)));

    // Check that the shapes are ok

    REQUIRE(scene.world.shapes.size() == 3);
    //REQUIRE(scene.world.shapes[0] == Plane);
    REQUIRE(scene.world.shapes[0]->transformation.is_close(translation(Vec(0, 0, 100)) * rotation_y(150.0)));
    //REQUIRE(scene.world.shapes[1] == Plane);
    REQUIRE(scene.world.shapes[1]->transformation.is_close(Transformation()));
    //REQUIRE(scene.world.shapes[2] == Sphere);
    REQUIRE(scene.world.shapes[2]->transformation.is_close(translation(Vec(0, 0, 1))));

    // Check that the camera is ok

    //REQUIRE(scene.camera == PerspectiveCamera);
    REQUIRE(scene.camera->transformation.is_close(rotation_z(30) * translation(Vec(-4, 0, 1))));
    REQUIRE(are_close(scene.camera->aspect_ratio, 1.0));
    //REQUIRE(are_close(scene.camera->screen_distance, 2.0));
}

TEST_CASE("Parser - undefined material", "[scene]") {

    // Check that unknown materials raises a GrammarError

    stringstream sstr;
    sstr << "plane(this_material_does_not_exist, identity)";

    InputStream stream(sstr);
    unordered_map<string, float> variables;

    try {
        Scene scene = stream.parse_scene(variables);
        INFO("The code did not throw an exception");
        REQUIRE(false);
    } catch (GrammarError &e) {
        REQUIRE(true);
    }
}

TEST_CASE("Parser - double camera", "[scene]") {

    // Check that defining two cameras in the same file raises a GrammarError

    stringstream sstr;
    sstr << "camera(perspective, rotation_z(30) * translation([-4, 0, 1]), 1.0, 1.0)"
        "\ncamera(orthogonal, identity, 1.0, 1.0)";

    InputStream stream(sstr);
    unordered_map<string, float> variables;

    try {
        Scene scene = stream.parse_scene(variables);
        INFO("The code did not throw an exception");
        REQUIRE(false);
    } catch (GrammarError &e) {
        REQUIRE(true);
    }
}


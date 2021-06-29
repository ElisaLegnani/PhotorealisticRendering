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

#include "args.hxx"
#include "scene.h"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

void convert_hdr2ldr(string, string, float, float);
void image_render(string, string, int, int, uint64_t, uint64_t, int, int, string, vector<string>);
unordered_map<string, float> build_variable_dictionary(vector<string>);

int main(int argc, char **argv) {

  args::ArgumentParser parser(
      "This is a program for creating photorealistic images.");
  args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
  args::Group commands(parser, "commands");
  args::Command hdr2ldr(commands, "hdr2ldr", "Convert hdr image to ldr");
  args::Command render(commands, "render", "Create a demo image");

  args::Group hdr2ldr_arguments(parser, "hdr2ldr arguments",
                                args::Group::Validators::DontCare,
                                args::Options::Global);
  args::ValueFlag<string> pfm_file(hdr2ldr_arguments, "",
                                       "Input PFM filename", {"pfm", "pfm_file"});
  args::ValueFlag<string> out_file(hdr2ldr_arguments, "",
                                       "Output PNG/JPG filename", {"out", "out_file"});
  args::ValueFlag<float> a(hdr2ldr_arguments, "",
                           "Luminosity normalization factor, 0<a<1", {'a'});
  args::ValueFlag<float> gamma(hdr2ldr_arguments, "",
                               "Monitor calibration factor gamma", {'g', "gamma"});

  args::Group render_arguments(parser, "render arguments",
                               args::Group::Validators::DontCare,
                               args::Options::Global);
  args::ValueFlag<int> width(render_arguments, "",
                             "Width of the rendered image", {'w', "width"});
  args::ValueFlag<int> height(render_arguments, "",
                              "Height of the rendered image", {'h', "heght"});
  args::ValueFlag<string> algorithm(render_arguments, "",
                                    "Renderer algorithm: \n onoff/flat/pathtracer",
                                    {'r', 'a', "renderer", "algorithm"});
  args::ValueFlag<string> scene_file(render_arguments, "",
                                    "Input scene file", {"scene", "scene_file"});
  args::ValueFlag<string> output_file(render_arguments, "",
                                      "Output filename: PFM/PNG/JPG", {"output", "output_file"});
  args::ValueFlag<int> n_rays(render_arguments, "",
                             "Number of rays", {'n', "n_rays", "rays"});
  args::ValueFlag<int> max_depth(render_arguments, "",
                             "Maximum depth", {'d', "max_depth", "depth"});
  args::ValueFlag<uint64_t> state(render_arguments, "",
                             "Initial seed for the PCG random number generator", {'s', "state"});
  args::ValueFlag<uint64_t> seq(render_arguments, "",
                             "Identifier of the sequence produced by the PCG random number generator", {'i', "seq", "seq_id"});
  args::ValueFlagList<string> declare_variables(render_arguments, "",
                             "Declare float variables: \n --declare_var name:variable", {'v', "declare_var"});
  args::CompletionFlag completion(parser, {"complete"});

  try {
    parser.ParseCLI(argc, argv);
  
  } catch (const args::Completion &e) {
    std::cout << e.what();
    return 0;
  
  } catch (const args::Help &) {
    std::cout << parser;
    return 0;
  
  } catch (const args::ParseError &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }

  if (hdr2ldr) {
    convert_hdr2ldr(args::get(pfm_file), args::get(out_file), args::get(a), args::get(gamma));
  }

  else if (render) {

    vector<string> variables_list;
    if (declare_variables) {
      for (const auto &var: args::get(declare_variables))
        variables_list.push_back(var);
    }

    image_render(args::get(scene_file), args::get(algorithm), args::get(n_rays),
                 args::get(max_depth), args::get(state), args::get(seq),
                 args::get(width), args::get(height), args::get(output_file), variables_list);
  }

  return 0;
}


//–––––––––––––––––– HDR2LDR ––––––––––––––––––––––––

void convert_hdr2ldr(string pfm_file, string output_file, float a, float gamma) {

  HdrImage img(pfm_file);

  img.normalize_image(a);
  img.clamp_image();

  img.write_ldr_image(output_file, gamma);
  cout << "LDR image written to " << output_file << endl;
}


//–––––––––––––––––– RENDER ––––––––––––––––––––––––

unordered_map<string, float> build_variable_dictionary(vector<string> variables_list){

  unordered_map<string, float> variables;
  
  size_t pos_start = 0, pos_end;
  for (const auto var: variables_list) {

    size_t find = var.find("=");
    float value = stof(var.substr(find + 1));
    string name = var.substr(0, find);
    
    variables[name] = value;
  }

  return variables;
}

void image_render(string scene_file, string algorithm, int n_rays, int max_depth, uint64_t state, uint64_t seq,
                  int width, int height, string output_file, vector<string> variables_list) {

  unordered_map<string, float> variables = build_variable_dictionary(variables_list);

  HdrImage image(width, height);

  ifstream in;
  in.open(scene_file);
  Scene scene;

  try {
    InputStream scene_stream(in);
    scene = scene_stream.parse_scene(variables);

  } catch (GrammarError &e) {
    cout << e.what() << endl;
    return;
  }

  // Run the ray-tracer
  ImageTracer tracer(image, scene.camera);

  PCG pcg(state, seq);
  int rr_lim = 3;

  shared_ptr<Renderer> renderer;
  if (algorithm == "onoff") {
    renderer = make_shared<OnOffRenderer>(scene.world);
  } else if (algorithm == "flat") {
    renderer = make_shared<FlatRenderer>(scene.world);
  } else if (algorithm == "pathtracer") {
    renderer = make_shared<PathTracer>(scene.world, BLACK, pcg, n_rays,
                                       max_depth, rr_lim);
  }

  tracer.fire_all_rays(
      [&](Ray ray) -> Color { return (*renderer)(ray); }); //***

  // Understand format output file (PFM/PNG/JPG)
  string file_str = string(output_file);
  size_t find = file_str.find_last_of(".");
  string format = file_str.substr(find);

  // Output the image to the disk file in PNG format
  if (format == ".pfm") {

    ofstream stream(output_file);
    tracer.image.save_pfm(stream, Endianness::little_endian);
    cout << "PFM demo image: " << output_file << endl;
  } else if (format == ".png" || format == ".jpg") {

    tracer.image.normalize_image(1.);
    tracer.image.clamp_image();

    tracer.image.write_ldr_image(output_file, 1.0);
    cout << "LDR demo image: " << output_file << endl;
  }
}

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


/**
 * COMMAND 1:  GENERATE AN IMAGE USING A RAYTRACING ALGORITHM
 *
 * @param scene_file TXT input file name with indications of the scene one wants to create
 * @param algorithm raytracing algorithm to choose among onoff, flat, pathtracer to render the image
 * @param n_rays number of ray to generate (high number -> better image quality, less efficiency)
 * @param max_depth number of ray reflections on objects (high number -> better image quality, less efficiency)
 * @param init_state initial seed for the PCG random number generator
 * @param init_seq identifier of the sequence produced by the PCG random number generator
 * @param width Output image width
 * @param height Output image height
 * @param output_file PFM/PNG/JPEG output file name with the path where to place it
 * @param variables_list floating point variables list to set parameters directly from the command line (ex: angle where to see the scene)
 *
 */
void image_render(string, string, int, int, uint64_t, uint64_t, int, int, int, string, vector<string>);

/**
 * Function needed to convert the variable_list passed from the command line into the a dictionary variable
 */
unordered_map<string, float> build_variable_dictionary(vector<string>);


/**
 * COMMAND 2:  CONVERSION HDR2LDR
 *
 * @param pfm_file PFM input file name with the path where to find it
 * @param out_file PNG/JPEG output file name with the path where to place it
 * @param a luminosity normalization factor
 * @param gamma monitor calibration factor
 */
void convert_hdr2ldr(string, string, float, float);




//––––––––––––––––––––– MAIN –––––––––––––––––––––––––––––––––––––––––––––
int main(int argc, char **argv) {

  args::ArgumentParser parser(
      "This is a program for creating photorealistic images.");
  args::HelpFlag help(parser, "help", "Display help menu", {'h', "help"});
  args::Group commands(parser, "commands");
  args::Command render(commands, "render", "Create a photorealistic image");
  args::Command hdr2ldr(commands, "hdr2ldr", "Convert hdr image to ldr");

  //args::HelpFlag helpr(render, "help", "Display help menu", {'h', "help"});
  args::Group render_arguments(render, "render arguments",
                               args::Group::Validators::DontCare,
                               args::Options::Global);
  
  args::ValueFlag<int> width(render_arguments, "",
                             "Width of the rendered image \n (default 640)", {'w', "width"});
  args::ValueFlag<int> height(render_arguments, "",
                              "Height of the rendered image \n (default 480)", {'h', "heght"});
  args::ValueFlag<string> algorithm(render_arguments, "",
                                    "Renderer algorithm: \n onoff/flat/pathtracer/pointlight \n (default pathtracer)",
                                    {'r', 'a', "renderer", "algorithm"});
  args::ValueFlag<string> scene_file(render_arguments, "",
                                    "Input scene file", {"scene", "scene_file"});
  args::ValueFlag<string> output_file(render_arguments, "",
                                      "Output filename: PFM/PNG/JPG \n (default DIY_image.png)", {"output", "output_file"});
  args::ValueFlag<int> n_rays(render_arguments, "",
                             "Number of rays (default 10)", {'n', "n_rays", "rays"});
  args::ValueFlag<int> max_depth(render_arguments, "",
                             "Maximum depth (default 2)", {'d', "max_depth", "depth"});
  args::ValueFlag<int> samples_per_pixel(render_arguments, "",
                             "Number of samples per pixel \n for antialiasing, must be a perfect \n square (default 0)", {"samples", "samples_per_pixel"});
  args::ValueFlag<uint64_t> state(render_arguments, "",
                             "Initial seed for the PCG random number \n generator (default 42)", {'s', "state"});
  args::ValueFlag<uint64_t> seq(render_arguments, "",
                             "Identifier of the sequence produced by \n the PCG random number generator \n (default 54)", 
                             {'i', "seq", "seq_id"});
  args::ValueFlagList<string> declare_variables(render_arguments, "",
                             "Declare float variables: \n --declare_var name=value \n Example: --declare_var ang=10",
                             {'v', "declare_var"});
  
  //args::HelpFlag helph(hdr2ldr, "help", "Display help menu", {'h', "help"});
  
  args::Group hdr2ldr_arguments(hdr2ldr, "hdr2ldr arguments",
                                args::Group::Validators::DontCare,
                                args::Options::Global);
  
  args::ValueFlag<string> pfm_file(hdr2ldr_arguments, "",
                                       "Input PFM filename", {"pfm", "pfm_file"});
  args::ValueFlag<string> out_file(hdr2ldr_arguments, "",
                                       "Output PNG/JPG filename \n (default ldrimage_a_gamma.png)", {"out", "out_file"});
  args::ValueFlag<float> a(hdr2ldr_arguments, "",
                           "Luminosity normalization factor \n 0<a<1 (default 0.3)", {'a'});
  args::ValueFlag<float> gamma(hdr2ldr_arguments, "",
                               "Monitor calibration factor gamma \n (default 1)", {'g', "gamma"});
  
  args::CompletionFlag completion(parser, {"complete"});
  
  

  try {
    parser.ParseCLI(argc, argv);
  
  } catch (const args::Completion &e) {
    cout << e.what();
    return 0;
  
  } catch (const args::Help &) {
    cout << parser;
    return 0;

  } catch (const args::Error &e) {
  cout << e.what();
  cout << parser;
  return 0;
  }

  if (render) {

    vector<string> variables_list;
    if (declare_variables) {
      for (const auto &var: args::get(declare_variables))
        variables_list.push_back(var);
    }
    
    
    string _algorithm = "pathtracer", _output_file = "DIY_image.png";
    int _n_rays = 10, _max_depth = 2, _state = 42, _seq = 54, _samples_per_pixel=0, _width = 640, _height = 480;
    
    if (!scene_file){
      cerr << "Error: missing Input scene file." <<endl;
      cerr << parser;
      return 0;
    }
    if (algorithm) _algorithm = args::get(algorithm);
    if (n_rays) _n_rays = args::get(n_rays);
    if (max_depth) _max_depth = args::get(max_depth);
    if (state) _state = args::get(state);
    if (seq) _seq = args::get(seq);
    if (samples_per_pixel) _samples_per_pixel =  args::get(samples_per_pixel);
    if (width) _width = args::get(width);
    if (height) _height = args::get(height);
    if (output_file) _output_file = args::get(output_file);

    image_render(args::get(scene_file), _algorithm, _n_rays, _max_depth, _state, _seq,
                 _samples_per_pixel, _width, _height, _output_file, variables_list);
  }
    
  else if (hdr2ldr) {

    float _a = 0.3, _gamma = 1.;
    
    if (!pfm_file){
      cout << "Error: missing Input PFM filename." <<endl;
      cout << parser;
      return 0;
    }
    if (a) _a = args::get(a);
    if (gamma) _gamma = args::get(gamma);
    string _out_file = string{"ldrimage_"+to_string(_a)+"_"+to_string(_gamma)+".png"};
    if (out_file) _out_file = args::get(out_file);

    convert_hdr2ldr(args::get(pfm_file), _out_file, _a, _gamma);
  }

  return 0;
}
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––


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
                  int samples_per_pixel, int width, int height, string output_file, vector<string> variables_list) {

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

  PCG pcg(state, seq);
  int rr_lim = 3;
  int samples_per_side = int(sqrt(samples_per_pixel));
  if (pow(samples_per_side,2) != samples_per_pixel){
    cout << "Error: the number of samples per pixel must be a perfect square" << endl;
    return;
  }

   // Run the ray-tracer
  ImageTracer tracer(image, scene.camera, samples_per_side, pcg);

  shared_ptr<Renderer> renderer;
  if (algorithm == "onoff") {
    renderer = make_shared<OnOffRenderer>(scene.world);
  } else if (algorithm == "flat") {
    renderer = make_shared<FlatRenderer>(scene.world);
  } else if (algorithm == "pathtracer") {
    renderer = make_shared<PathTracer>(scene.world, BLACK, pcg, n_rays, max_depth, rr_lim);
  } else if (algorithm == "pointlight") {
    renderer = make_shared<PointLightTracer>(scene.world, BLACK);
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

//–––––––––––––––––– HDR2LDR ––––––––––––––––––––––––

void convert_hdr2ldr(string pfm_file, string output_file, float a, float gamma) {

  HdrImage img(pfm_file);

  img.normalize_image(a);
  img.clamp_image();

  img.write_ldr_image(output_file, gamma);
  cout << "LDR image written to " << output_file << endl;
}

//––––––––––––––––––––––––––––––––––––––––––– *** ––––––––––––––––––––––––––––––––––––––––––––––––––

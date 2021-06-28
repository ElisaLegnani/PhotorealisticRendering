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
#include <iostream>
#include <string.h>
#include <fstream>
#include "args.hxx"

using namespace std;

void render(string, string, int, int, int, int, string);
//unordered_map<string, float> build_variable_dictionary();

int main(int argc, char *argv[]) {

  if (argv[1] == NULL) {
    cout << "Insert command: hdr2ldr or render" << endl;
    return 0;
  }

  //–––––––––––––––––– HDR2LDR ––––––––––––––––––––––––
  
  if (strcmp(argv[1], "hdr2ldr") == 0) {

    string pfm_filename;
    string out_filename;
    float a, gamma;

    if (argv[2] == NULL) {
      cout << "Insert input PFM filename: ";
      cin >> pfm_filename;
      cout << "Insert luminosity normalization factor a (0<a<1, 0.3 by default): ";
      cin >> a;
      cout << "Insert monitor calibration factor gamma (1.0 by default): ";
      cin >> gamma;
      cout << "You may change a and gamma according to the image visualization preferences."<<endl;
      cout << "Insert output PNG/JPG filename: ";
      cin >> out_filename;
    } else {
      pfm_filename = argv[2];
      a = atof(argv[3]);
      gamma = atof(argv[4]);
      out_filename = argv[5];
    }

    HdrImage img(pfm_filename);

    img.normalize_image(a);
    img.clamp_image();

    img.write_ldr_image(out_filename, gamma);
    cout << "LDR image written to " << out_filename << endl;

  }
  
 //–––––––––––––––––– RENDER ––––––––––––––––––––––––
  
  else if (strcmp(argv[1], "render") == 0) {

    int width, height;
    //float angle_deg;
    string algorithm;
    string scene_file, output_file;
    int n_rays = 0, max_depth = 0;

    if (argv[2] == NULL) {
      cout << "Insert input scene_file: ";
      cin >> scene_file;
      /*cout << "Insert angle of view (deg): ";
      cin >> angle_deg;*/
      cout << "Insert renderer algorithm (onoff/flat/pathtracer): ";
      cin >> algorithm;
      if (algorithm == "pathtracer"){
        cout << "Insert number of rays: ";
        cin >> n_rays;
        cout << "Insert max depth: ";
        cin >> max_depth;
      }
      cout << "Insert rendered image width: ";
      cin >> width;
      cout << "Insert rendered image height: ";
      cin >> height;
      cout << "Insert output filename (PFM/PNG/JPG): ";
      cin >> output_file;
    }
    else {
//      angle_deg = atof(argv[4]);
      scene_file = argv[2];
      algorithm = argv[3];
      width = atoi(argv[4]);
      height = atoi(argv[5]);
      output_file = argv[6];
      if (algorithm == "pathtracer"){
        n_rays = atoi(argv[7]);
        max_depth = atoi(argv[8]);
      }
    }

    render(scene_file, algorithm, n_rays, max_depth, width, height, output_file);
  }

  return 0;
}

/*unordered_map<string, float> build_variable_dictionary(){
  
  unordered_map<string, float> variables;
  
}*/

//–––––––––––––––––– RENDER FUNCTION ––––––––––––––––––––––––

void render(string scene_file, string algorithm, int n_rays, int max_depth, int width, int height, string output_file) { // float angle_deg

  unordered_map<string, float> variables;//=build_variable_dictionary();
  
  HdrImage image(width, height);
  
  ifstream in;
  in.open(scene_file);
  Scene scene;
  
  try{
    InputStream scene_stream(in);
    scene = scene_stream.parse_scene(variables);
    
  } catch(GrammarError &e){
    cout << e.what()<<endl;
    return;
  }
  

  // Run the ray-tracer
  ImageTracer tracer(image, scene.camera);

  PCG pcg;
  int rr_lim = 3;

  shared_ptr<Renderer> renderer;
  if (algorithm == "onoff") {
    renderer = make_shared<OnOffRenderer>(scene.world);
  } else if (algorithm == "flat") {
    renderer = make_shared<FlatRenderer>(scene.world);
  } else if (algorithm == "pathtracer") {
    renderer = make_shared<PathTracer>(scene.world, BLACK, pcg, n_rays, max_depth, rr_lim);
  }

  tracer.fire_all_rays([&](Ray ray) -> Color { return (*renderer)(ray); }); //***

  //  Understand format output file (PFM/PNG/JPG)
  string filename_str = string(output_file);
  size_t find = filename_str.find_last_of(".");
  string format = filename_str.substr(find);

  // Output the image to the disk file in PNG format
  if(format==".pfm"){
    
    ofstream stream(output_file);
    tracer.image.save_pfm(stream, Endianness::little_endian);
    cout << "PFM demo image: " << output_file << endl;
  } else if (format == ".png" || format == ".jpg"){
    
    tracer.image.normalize_image(1.);
    tracer.image.clamp_image();

    tracer.image.write_ldr_image(output_file, 1.0);
    cout << "LDR demo image: " << output_file << endl;
  }
  
}

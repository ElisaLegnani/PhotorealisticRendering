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

#include "imagetracer.h"
#include "world.h"
#include "render.h"
#include <iostream>
#include <string.h>

using namespace std;

void demo(int, int, float, string, string, string, int, int);

int main(int argc, char *argv[]) {

  if (argv[1] == NULL) {
    cout << "Insert command: hdr2ldr or demo" << endl;
    return 0;
  }

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

  else if (strcmp(argv[1], "demo") == 0) {

    string cameratype;
    int width, height;
    float angle_deg;
    string algorithm;
    string filename;
    int n_rays = 0, max_depth = 0;

    if (argv[2] == NULL) {
      cout << "Insert camera type (orthogonal/perspective): ";
      cin >> cameratype;
      cout << "Insert demo image width: ";
      cin >> width;
      cout << "Insert demo image height: ";
      cin >> height;
      cout << "Insert angle of view (deg): ";
      cin >> angle_deg;
      cout << "Insert renderer algorithm (onoff/flat/pathtracer): ";
      cin >> algorithm;
      if (algorithm == "pathtracer"){
        cout << "Insert number of rays: ";
        cin >> n_rays;
        cout << "Insert max depth: ";
        cin >> max_depth;
      }
      cout << "Insert output filename (PFM/PNG/JPG): ";
      cin >> filename;
    }
    else {
      cameratype = argv[2];
      width = atoi(argv[3]);
      height = atoi(argv[4]);
      angle_deg = atof(argv[5]);
      algorithm = argv[6];
      filename = argv[7];
      if (algorithm == "pathtracer"){
        n_rays = atoi(argv[8]);
        max_depth = atoi(argv[9]);
      }
    }

    demo(width, height, angle_deg, cameratype, algorithm, filename, n_rays, max_depth);
  }

  return 0;
}

void demo(int width, int height, float angle_deg, string cameratype,
          string algorithm, string output, int n_rays, int max_depth) {

  HdrImage image(width, height);

  // Create a world and populate it with a few shapes
  World world;

  Color sphere_color1(0.0, 0.0, 100.0);
  Color sphere_color2(0.0, 100.0, 0.0);
  Color sphere_color3(0.0, 100.0, 100.0);
  Color sphere_color4(100.0, 100.0, 0.0);

  Material material1(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(sphere_color1)));
  Material material2(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(sphere_color2)));
  Material material3(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(sphere_color3)));
  Material material4(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(sphere_color4)));
  Material material5(make_shared<DiffuseBRDF>(make_shared<CheckeredPigment>(sphere_color3, sphere_color4)));
  Material material6(make_shared<DiffuseBRDF>(make_shared<CheckeredPigment>(sphere_color1, sphere_color2)));
  Material material;
  
  for (int x{}; x < 2; ++x) {
    for (int y{}; y < 2; ++y) {
      for (int z{}; z < 2; ++z) {

        if (x==y && x==z) material = material1;
        else if(x==y && x!=z) material = material2;
        else if(x!=y && x==z) material = material3;
        else material = material4;

        world.add(
            make_shared<Sphere>(translation(Vec(x - 0.5, y - 0.5, z - 0.5)) *
                                scaling(Vec(0.1, 0.1, 0.1)), material));
      }
    }
  }

  // Place two other balls in the bottom/left part of the cube, so that we can
  // check if there are issues with the orientation of the image
  world.add(make_shared<Sphere>(translation(Vec(0.0, 0.0, -0.5)) *
                                scaling(Vec(0.1, 0.1, 0.1)),material5));
  world.add(make_shared<Sphere>(translation(Vec(0.0, 0.5, 0.0)) *
                                scaling(Vec(0.1, 0.1, 0.1)), material6));
  
//  –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
  World world2;

  Material sky_material(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(BLACK)), make_shared<UniformPigment>(Color(0.6, 0.8, 1.0)));
  Material ground_material(make_shared<DiffuseBRDF>(make_shared<CheckeredPigment>(Color(0.3, 0.5, 0.1), Color(0.1, 0.2, 0.5))));
  Material sphere_material(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(Color(0.8, 0.2, 0.5))));
  Material mirror_material(make_shared<SpecularBRDF>(make_shared<UniformPigment>(Color(0.5, 0.3, 0.3))));

  HdrImage img_pigment("../examples/hdr2ldr/sky.pfm");
  img_pigment.normalize_image(0.3);
  img_pigment.clamp_image();
  Material image_material(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(BLACK)), make_shared<ImagePigment>(img_pigment));
  
  world2.add(make_shared<Sphere>(scaling(Vec(200., 200., 200.))* translation(Vec(0., 0.,0.8))*rotation_z(150), image_material));
  world2.add(make_shared<Plane>(translation(Vec(0., 0., 0.)), ground_material));
  world2.add(make_shared<Sphere>(translation(Vec(0., 0., 0.8))*scaling(Vec(0.8,0.8,0.8)), sphere_material));
  world2.add(make_shared<Sphere>(translation(Vec(1, -2, 0.6))*scaling(Vec(0.6,0.6,0.6)), sky_material));
  world2.add(make_shared<Sphere>(translation(Vec(1., 2.5, 0.)), mirror_material));
             
  // Initialize a camera
  Transformation camera_tr;
  if (algorithm == "onoff" || algorithm == "flat") {
    camera_tr = rotation_z(angle_deg) * translation(Vec(-1.0, 0.0, 0.0));
  } else if (algorithm == "pathtracer") {
    camera_tr = rotation_z(angle_deg) * translation(Vec(-1.0, 0.0, 1.0));
  }

  shared_ptr<Camera> camera;
  if (cameratype == "orthogonal") {
    camera = make_shared<OrthogonalCamera>(width / height, camera_tr);
  } else if (cameratype == "perspective") {
    camera = make_shared<PerspectiveCamera>(1.0, width / height, camera_tr);
  }

  // Run the ray-tracer
  ImageTracer tracer(image, camera);

  PCG pcg;
  int rr_lim = 3;

  shared_ptr<Renderer> renderer;
  if (algorithm == "onoff") {
    renderer = make_shared<OnOffRenderer>(world);
  } else if (algorithm == "flat") {
    renderer = make_shared<FlatRenderer>(world);
  } else if (algorithm == "pathtracer") {
    renderer = make_shared<PathTracer>(world2, BLACK, pcg, n_rays, max_depth, rr_lim);
  }

  tracer.fire_all_rays([&](Ray ray) -> Color { return (*renderer)(ray); }); //***

  //  Understand format output file (PFM/PNG/JPG)
  string filename_str = string(output);
  size_t find = filename_str.find_last_of(".");
  string format = filename_str.substr(find);

  // Output the image to the disk file in PNG format
  if(format==".pfm"){
    
    ofstream stream(output);
    tracer.image.save_pfm(stream, Endianness::little_endian);
    cout << "PFM demo image: " << output << endl;
  } else if (format == ".png" || format == ".jpg"){
    
    tracer.image.normalize_image(1.);
    tracer.image.clamp_image();

    tracer.image.write_ldr_image(output, 1.0);
    cout << "LDR demo image: " << output << endl;
  }
  
}

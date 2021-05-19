#include "imagetracer.h"
#include "world.h"
#include <iostream>
#include <string.h>

using namespace std;

void demo(int, int, float, string, string, string);

int main(int argc, char *argv[]) {

  if(strcmp(argv[1],"pfm2image")==0) {

  string pfm_filename;
  string out_filename;
  float a, gamma;

  if (argv[2] == NULL) {
    cout << "Insert input PFM filename: ";
    cin >> pfm_filename;
    cout << "Insert a: ";
    cin >> a;
    cout << "Insert gamma: ";
    cin >> gamma;
    cout << "Insert output PNG/JPG filename: ";
    cin >> out_filename;
  } else {
    pfm_filename = argv[1];
    a = atof(argv[2]);
    gamma = atof(argv[3]);
    out_filename = argv[4];
  }

  HdrImage img(pfm_filename);

  img.normalize_image(a);
  img.clamp_image();

  img.write_ldr_image(out_filename, gamma);

  }

  else if(strcmp(argv[1],"demo")==0) {
    demo(500, 500, 0.0, "orthogonal", "prova.pfm", "prova.png");
  }

  else { 
    cout << "Insert command: pfm2image or demo" << endl;
  }

  return 0;
}



void demo(int width, int height, float angle_deg, string cameratype, string pfm_output, string png_output){

  HdrImage image(width, height);

  // Create a world and populate it with a few shapes
  World world;

  for(int x{}; x<2; ++x) {
    for(int y{}; y<2; ++y) {
      for(int z{}; z<2; ++z) {
        world.add(make_shared<Sphere>(translation(Vec(x-0.5, y-0.5, z-0.5)) * scaling(Vec(0.1, 0.1, 0.1))));
      }
    }
  }

  // Place two other balls in the bottom/left part of the cube, so that we can check if there are issues with the orientation of the image
  world.add(make_shared<Sphere>(translation(Vec(0.0, 0.0, -0.5)) * scaling(Vec(0.05, 0.05, 0.05))));
  world.add(make_shared<Sphere>(translation(Vec(0.0, 0.5, 0.0)) * scaling(Vec(0.05, 0.05, 0.05))));

  // Initialize a camera
  Transformation camera_tr = rotation_z(angle_deg) * translation(Vec(-1.0, 0.0, 0.0));
  /*if(cameratype == "orthogonal") {
    OrthogonalCamera camera(width / height, camera_tr);
  } else if(cameratype == "perspective") {
    PerspectiveCamera camera(1.0, width / height, camera_tr);
  }*/
  
  OrthogonalCamera camera(width / height, camera_tr);

  // Run the ray-tracer
  ImageTracer tracer(image, camera);
  tracer.fire_all_rays([&] (Ray ray) -> Color {
    if(world.ray_intersection(ray).init){
      return Color(1.0, 1.0, 1.0); //white
    } else {
      return Color(0.0, 0.0, 0.0); //black
    }
  });

  // Save the HDR image
  ofstream stream(pfm_output);
  tracer.image.save_pfm(stream, Endianness::little_endian);
  cout << "HDR demo image written to {pfm_output}" << endl;

  // Apply tone-mapping to the image
  tracer.image.normalize_image(1.0);
  tracer.image.clamp_image();

  tracer.image.write_ldr_image(png_output, 1.0);
  cout << "PNG demo image written to {png_output}" << endl;
}


#include "imagetracer.h"
#include "world.h"
#include <iostream>
#include <string.h>

using namespace std;

void demo(int, int, float, string, string);

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

    string filename;
    string cameratype;
    int width, height;
    float angle_deg;

    if (argv[2] == NULL) {
      cout << "Insert camera type (orthogonal/perspective): ";
      cin >> cameratype;
      cout << "Insert demo image width: ";
      cin >> width;
      cout << "Insert demo image height: ";
      cin >> height;
      cout << "Insert angle of view (deg): ";
      cin >> angle_deg;
      cout << "Insert output filename (PFM/PNG/JPG): ";
      cin >> filename;
    }
    else {
      cameratype = argv[2];
      width = atoi(argv[3]);
      height = atoi(argv[4]);
      angle_deg = atof(argv[5]);
      filename = argv[6];
    }

    demo(width, height, angle_deg, cameratype, filename);
  }

  return 0;
}

void demo(int width, int height, float angle_deg, string cameratype,
          string output) {

  HdrImage image(width, height);

  // Create a world and populate it with a few shapes
  World world;

  for (int x{}; x < 2; ++x) {
    for (int y{}; y < 2; ++y) {
      for (int z{}; z < 2; ++z) {
        world.add(
            make_shared<Sphere>(translation(Vec(x - 0.5, y - 0.5, z - 0.5)) *
                                scaling(Vec(0.1, 0.1, 0.1))));
      }
    }
  }

  // Place two other balls in the bottom/left part of the cube, so that we can
  // check if there are issues with the orientation of the image
  world.add(make_shared<Sphere>(translation(Vec(0.0, 0.0, -0.5)) *
                                scaling(Vec(0.1, 0.1, 0.1))));
  world.add(make_shared<Sphere>(translation(Vec(0.0, 0.5, 0.0)) *
                                scaling(Vec(0.1, 0.1, 0.1))));

  // Initialize a camera
  Transformation camera_tr =
      rotation_z(angle_deg) * translation(Vec(-1.0, 0.0, 0.0));
  shared_ptr<Camera> camera;

  if (cameratype == "orthogonal") {
    camera = make_shared<OrthogonalCamera>(width / height, camera_tr);
  } else if (cameratype == "perspective") {
    camera = make_shared<PerspectiveCamera>(1.0, width / height, camera_tr);
  }

  // Run the ray-tracer
  ImageTracer tracer(image, camera);
  tracer.fire_all_rays([&](Ray ray) -> Color {
    if (world.ray_intersection(ray).init) {
      return WHITE;
    } else {
      return BLACK;
    }
  });

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
    
    tracer.image.normalize_image(0.3);
    tracer.image.clamp_image();

    tracer.image.write_ldr_image(output, 1.0);
    cout << "LDR demo image: " << output << endl;
  }
  
  /*// Save the HDR image
  ofstream stream(pfm_output);
  tracer.image.save_pfm(stream, Endianness::little_endian);
  cout << "PFM demo image: " << pfm_output << endl;

  // Apply tone-mapping to the image
  tracer.image.normalize_image(0.3);
  tracer.image.clamp_image();

  tracer.image.write_ldr_image(png_output, 1.0);
  cout << "PNG demo image: " << png_output << endl;*/
}

# Photorealistic Rendering
A simple raytracer for generating photorealistic images written in C++. 
It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor Maurizio Tomasi (University of Milan, AY2020-2021).

*Note: it is a WIP project*


## Installation

### Dependencies

A C++ compiler is needed (C++14 or higher).

You also need to install the following dependencies:
- [Cmake](https://cmake.org/) (version 3.12 or higher);
- [GD library](https://libgd.github.io/) (version 2.3.0 or higher).

### Install from git repository

Clone this repository with the commands: 
```sh
$ git clone https://github.com/ElisaLegnani/PhotorealisticRendering.git
$ cd PhotorealisticRendering
```

Compile:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Executables files can be found in the `build` directory.

For testing, run in the `build` directory:

```sh
$ ctest
```

## Usage

<details><summary><b>Convert HDR image to LDR</b></summary>

  In the  `build` directory: 
  
  ```sh
  $ ./raytracer pfm2ldr
  ```

  The HDR image format supported is PFM, while LDR ones are PNG and JPG.

  Some parameters need to be set according to the preferences in the output image visualisation:
  - <img src="https://render.githubusercontent.com/render/math?math=a"> – *luminosity normalization factor*: changes image luminosity (default value: 0.3);
  - <img src="https://render.githubusercontent.com/render/math?math=\gamma"> – *monitor calibration factor*: depends on the user's monitor (default value: 1.0);

  You can set these properties directy by command line or being followed step by step:

  Command line:

  ```sh
  $ ./raytracer pfm2ldr input_file.pfm 0.3 1.0 output_file.jpg
  ```

  Step by step:

  ```sh
  $ ./raytracer pfm2ldr
  Insert input PFM filename: input_file.pfm
  Insert luminosity normalization factor a (0<a<1, 0.3 by default): 0.3
  Insert monitor calibration factor gamma (1.0 by default): 1.0
  You may rerun the program and change a and gamma according to the image visualization preferences.
  Insert output PNG/JPG filename: output_file.png
  ```
  
  ### Example:
  
  In the `examples/pfm2ldr` directory, there is a PFM input file called `memorial.pfm`.
  You can play with the code and parameters simply running (in the `build` directory):
  
  ```sh
  $ ./raytracer pfm2ldr ../examples/pfm2ldr/memorial.pfm 0.3 1.0 ../examples/pfm2ldr/memorial_0.3_1.0.png
  ```
  
  <p align="center">
  <img src="./img/example1.png" width="1000">
</p>
</details>


<details><summary><b>Create demo image</b></summary>

In the  `build` directory: 
  
```sh
$ ./raytracer demo
```

It is also provided a demo image, composed by ten white spheres on a black screen.

You can choose the camera type (orthogonal/perspective), the image width and height, the angle of view (deg), the output HDR filename (PFM) and LDR filename (PNG), again directly or step by step.

```sh
$ ./raytracer demo perspective 640 480 0 output_file.pfm output_file.png
```
  
</details>
  

## License

The code is released under a MIT license. See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

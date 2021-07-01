# Photorealistic Rendering
A simple raytracer for generating photorealistic images written in C++. 
It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor Maurizio Tomasi (University of Milan, AY2020-2021).

*Note: it is a WIP project*

## Table of Contents

- [Explanation](#explanation)
- [Installation](#installation)
  - [Dependencies](#dependencies)
  - [Install from git repository](#install-from-git-repository)
- [Usage](#usage)
  - [Create your own photorealistic image](#own-image)
  - [Convert HDR image to LDR](#convert)
- [Expectations](#expectations)
- [Contributing](#contributing)
- [License](#license)

## Explanation

More infos coming soon! Stay tuned!

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
The testing interface is built using [Catch2](https://github.com/catchorg/Catch2).

## Usage

You can run the program through the script `raytracer`. The code implements two features, that you can call with commands:
- creates a photorealistic image: `render`;
- converts HDR image to LDR: `hdr2ldr`.

To get commmand-line help, run in the  `build` directory: 
  
```sh
$ ./raytracer --help

```
For further details, see below.


### CREATE YOUR OWN PHOTOREALISTIC IMAGE
  
  In order to create your photorealistic images, you need to give instructions to the code on the scene you want to render. You can write them in a TXT file and run in the  `build` directory: 
  
  ```sh
  $ ./raytracer render --scene <scene_file.txt>
  ```
  
  More information on how to write this kind of file will be available soon! 
  
  
  In the `examples/render` directory, it is provided `demo.txt` file, where instructions are given to create a demo image for the program to start playing with the code!
  
  You can also set the following parameters:
  - image width (default value: `640`);
  - image height (default value: `480`);
  - renderer algorithm: `onoff`/`flat`/`pathtracer`/`pointlight` (default: `pathtracer`);
  - output filename: PFM/PNG/JPG file (default: `DIY_image.png`);
  - number of rays (default value: `10`);
  - maximum depth (default value: `2`);
  - initial seed for the random number generator (default value: `42`);
  - identifier of the sequence produced by the random number generator (default value: `54`);
  - number of samples per pixel for antialiasing (default value: `0`)
  - additional float parameters, e.g angle of view, camera distance ...
  
  **Warning on pointlight tracer**: the pointlight tracer is not able to render reflective surfaces.
  
  **Note**: the rendering process takes a long time to produce an image.
  
  #### Example:
  
  You may easily try the code running in the `examples/render` directory:
  
  ```sh
  $ ./generate-image.sh ANGLE
  ```
  
  which automatically runs the following code:
  
  ```sh
  $ ../../build/./raytracer render --scene demo_img.txt --declare_var ang=ANGLE --output img/imageANGLE.png
  ```
  
  You just need to set the `ANGLE` (deg) from which you look at the scene.
  
  <p align="center">
    <img width="500" src=https://user-images.githubusercontent.com/62106779/123851051-0ec3f600-d91b-11eb-9b2d-b5944efe7df6.png>
  </p>
  
  #### Animation:
  
  In the `examples/render` directory, you may generate an animation of the demo scene, rotating 360° around the objects.
  
  In order to run the code, you need to:
  - install `ffmpeg` : `sudo apt install ffmpeg` (or `brew install ffmpeg` if you use Homebrew);
  - install `GNU Parallel` : `sudo apt install parallel` (or `brew install parallel`);
  - find out the number of cores of your machine: `nproc --all`for Linux or `sysctl -n hw.ncpu` for MacOS, to pass as `NUM_OF_CORES` in the command line;
  
  This is needed to run in parallel the code and speed up the execution, otherwise it would take a very long time.
  
  ```sh
  $ ./generate-animation.sh NUM_OF_CORES
  ```
 
### CONVERT HDR IMAGE INTO LDR

  In the  `build` directory run: 
  
  ```sh
  $ ./raytracer hdr2ldr --pfm <input_file.pfm>
  ```

  The HDR image format supported is PFM, while LDR ones are PNG and JPG.

  You can also set some parameters according to your preferences in the output image visualisation:
  - <img src="https://render.githubusercontent.com/render/math?math=a"> – *luminosity normalization factor*: changes image luminosity, 0<*a*<1 (default value: `0.3`);
  - <img src="https://render.githubusercontent.com/render/math?math=\gamma"> – *monitor calibration factor*: depends on the user's monitor (default value: `1.0`);
  - *output filename*: PNG/JPG file (default: `ldrimage_a_gamma.png`).

  You can set these properties directly in the command line:

  ```sh
  $ ./raytracer hdr2ldr --pfm <input_file.pfm> -a 0.3 -g 1.0 --out <output_file.jpg>
  ```

  #### Example:
  
  In the `examples/hdr2ldr` directory, there is a PFM input file called `memorial.pfm`.
  You can play with the code and parameters simply running (in the `build` directory):
  
  ```sh
  $ ./raytracer hdr2ldr --pfm ../examples/hdr2ldr/memorial.pfm -a 0.3 -g 1.0 --out ../examples/hdr2ldr/memorial_0.3_1.0.png
  ```

  <p align="center">
       <img width="800" src=https://user-images.githubusercontent.com/59051647/123945827-d665fb80-d99e-11eb-9bb2-f5957ce53e94.png>
  </p>


The command line interface is built using the argument parsing library [Taywee/args](https://github.com/Taywee/args).
  
## Expectations

More infos coming soon! Stay tuned!

## Contributing

Please use the [issue tracker](https://github.com/ElisaLegnani/PhotorealisticRendering/issues) to report any bugs or file feature requests.

## License

The code is released under a MIT license. See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

# Photorealistic Rendering

![release](https://img.shields.io/github/v/release/ElisaLegnani/PhotorealisticRendering)
![OS](https://img.shields.io/badge/OS-Linux%20%7C%20MacOS-yellow)
![license](https://img.shields.io/github/license/ElisaLegnani/PhotorealisticRendering)
![build](https://img.shields.io/github/workflow/status/ElisaLegnani/PhotorealisticRendering/CMake)
![Top Language](https://img.shields.io/github/languages/top/ElisaLegnani/PhotorealisticRendering)


πͺ A simple raytracing library for generating photorealistic images written in C++.

It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor [Maurizio Tomasi](https://github.com/ziotom78) (University of Milan, AY2020-2021).

π©π»βπ» The main contributors to this repository are [Elisa Legnani](https://github.com/ElisaLegnani) and [Adele Zaini](https://github.com/adelezaini).

## Brief description

The main functionality of the library is rendering photorealistic images from user instructions on an external input text file. The code features four different backwards raytracing algorithms (onoff, flat, pathtracer, pointlight tracer) and βat the momentβ the scene elements are basic geometric shapes (spheres, planes, boxes). Setting material properties of the objects determines the interaction with light rays, while the observer point of view is represented by a camera with two different projections available (orthogonal and perspective).
This library has another useful functionality that is converting HDR images to LDR ones. The format supported are respectively PFM and PNG/JPG.

π *"Reality leaves a lot to the imagination." β J. Lennon*. Here is the mean, now it's your turn... unleash all your imagination!

#### Website 
π
A webpage [Photorealistic rendering](https://elisalegnani.github.io/PhotorealisticRendering) has been created in order to give more detailed explanations.


## Installation

### Dependencies

A C++ compiler is needed (C++14 or higher).

You also need to install the following dependencies:
- [Cmake](https://cmake.org/) (version 3.12 or higher);
- [GD library](https://libgd.github.io/) (version 2.3.0 or higher).

If you want to parallelize the execution or run animations, the required dependencies are:
- [GNU Parallel](https://www.gnu.org/software/parallel/)
- [FFmpeg](https://www.ffmpeg.org/) (version 4.4 or higher)

> *Note*: they are not needed for running the raytracing code.

### Download latest release
You can download the latest stable release [here](https://github.com/ElisaLegnani/PhotorealisticRendering/releases/tag/v1.1.0) (version 1.1.0) and then unpack it running in the command line (Linux):

```sh
tar -xvf PhotorealisticRendering-1.0.0.tar
```
The command is ```tar xopf``` for MacOS.

### Install from git repository

You can also clone this repository through the command: 

```sh
git clone https://github.com/ElisaLegnani/PhotorealisticRendering.git
```

### Compile

In order to build and compile the code, run the following commands:

```sh
cd PhotorealisticRendering
mkdir build
cd build
cmake ..
make
```

Executables files can be found in the `build` directory.

### Testing

Tests are being implemented in the `test` directory. 

In order to test the code, run in the `build` directory:

```sh
ctest
```
The testing interface is built using [Catch2](https://github.com/catchorg/Catch2).

## Usage

You can run the program through the script `raytracer`, located in the `build` directory. 

The code implements two features, that you can call with commands:
- π `render`: creates a photorealistic image;
- π `hdr2ldr`: converts HDR image to LDR.

The basic usage is the following:

```sh
./raytracer [COMMAND] [INPUT_FILENAME] {OPTIONS}

```
The `[INPUT_FILENAME]` is required. There are some examples in the `examples` directory if you want to give it a try or play with the code.

To have more information about available `{OPTIONS}`, a commmand-line help shows more details about program features and parameters:

```sh
./raytracer --help

```

The command line interface is built using the argument parsing library [Taywee/args](https://github.com/Taywee/args).

π For further details, examples and full documentation of the code, see the page [Photorealistic rendering](https://elisalegnani.github.io/PhotorealisticRendering).
  
## Potentialities and examples

π€Ήπ»ββοΈ There is a nice [overview of the library potentialities](https://elisalegnani.github.io/PhotorealisticRendering/explore) with lots of examples, hoping this can tickle your creativity! 

Here is just a spoiler of what awaits you!

<p align="center">
       <img width="450" src=https://user-images.githubusercontent.com/59051647/126571722-28e2cfe1-0b22-4961-bc0a-b1d05eb507ec.png>
       <img src="https://user-images.githubusercontent.com/59051647/126542691-8f384c07-c567-4276-8116-9e497611da4f.gif" width="450" /> 
</p>

## Documentation

π The complete documentation of the library is available [here](https://elisalegnani.github.io/PhotorealisticRendering/html/index.html). It was generated with [Doxygen](http://www.doxygen.nl). This is the first versione of the documentation, any suggestions are very appreciated!


## Contributing

π§ Please open [pull requests](https://github.com/ElisaLegnani/PhotorealisticRendering/pulls) or use the [issue tracker](https://github.com/ElisaLegnani/PhotorealisticRendering/issues) to suggest any code implementations or report bugs. Any contributions are welcome! 

## License

π The code is released under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html). See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

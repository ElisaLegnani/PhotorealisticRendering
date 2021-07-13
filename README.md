# Photorealistic Rendering

![release](https://img.shields.io/github/v/release/ElisaLegnani/PhotorealisticRendering)
![OS](https://img.shields.io/badge/OS-Linux%20%7C%20MacOS-yellow)
![license](https://img.shields.io/github/license/ElisaLegnani/PhotorealisticRendering)
![build](https://img.shields.io/github/workflow/status/ElisaLegnani/PhotorealisticRendering/CMake)
![Top Language](https://img.shields.io/github/languages/top/ElisaLegnani/PhotorealisticRendering)


A simple raytracer for generating photorealistic images written in C++.
[brief description]

It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor [Maurizio Tomasi](https://github.com/ziotom78) (University of Milan, AY2020-2021).

The main contributors to this repository are [Elisa Legnani](https://github.com/ElisaLegnani) and [Adele Zaini](https://github.com/adelezaini).

#### Website 
A webpage [Photorealistic rendering](https://elisalegnani.github.io/PhotorealisticRendering) has been created in order to give more detailed explanations.

## Installation

### Dependencies

A C++ compiler is needed (C++14 or higher).

You also need to install the following dependencies:
- [Cmake](https://cmake.org/) (version 3.12 or higher);
- [GD library](https://libgd.github.io/) (version 2.3.0 or higher).

If you want to run animations, the required dependencies are:
- [FFmpeg](https://www.ffmpeg.org/) (version 4.4 or higher)
- [GNU Parallel](https://www.gnu.org/software/parallel/)

*Note*: they are not needed for running the raytracing code.

### Download latest release
You can download the latest stable release [here](https://github.com/ElisaLegnani/PhotorealisticRendering/releases/tag/v1.0.0) (version 1.0.0) and then unpack it running in the command line (Linux):

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

You can run the program through the script `raytracer`. The code implements two features, that you can call with commands:
- creates a photorealistic image: `render`;
- converts HDR image to LDR: `hdr2ldr`.

To get commmand-line help, run in the  `build` directory: 
  
```sh
./raytracer --help

```

The command line interface is built using the argument parsing library [Taywee/args](https://github.com/Taywee/args).

For further details, examples and full documentation of the code, see the page [Photorealistic rendering](https://elisalegnani.github.io/PhotorealisticRendering).
  
## Expectations

More infos coming soon! Stay tuned!

## Contributing

Any contributions are welcome! Please use the [issue tracker](https://github.com/ElisaLegnani/PhotorealisticRendering/issues) to report any bugs or file feature requests.

## License

The code is released under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html). See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

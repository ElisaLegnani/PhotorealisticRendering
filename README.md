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

### Convert HDR image to LDR

```sh
$ ./raytracer pfm2ldr
```

### Create demo image

```sh
$ ./raytracer demo
```

More infos coming soon!

{::comment}
it is required to provide infos as... ecc..
{:/comment}

## Play with it!
It is provided a directory called `examples`, where you may play with the code and learn it better.

{::comment}
contenuto di cartella e istruzioni (con tendina che si apre)
{:/comment}

## License

The code is released under a MIT license. See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

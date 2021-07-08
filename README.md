# Photorealistic Rendering

[brief description]

It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor [Maurizio Tomasi](https://github.com/ziotom78) (University of Milan, AY2020-2021).

The main contributors to this repository are [Elisa Legnani](https://github.com/ElisaLegnani) and [Adele Zaini](https://github.com/adelezaini).

For a more detailed description see the page [Photorealistic rendering](https://elisalegnani.github.io/PhotorealisticRendering).

## Installation

You can find [here](https://github.com/ElisaLegnani/PhotorealisticRendering/releases/tag/v0.3.0) the latest stable release of the code (version 0.3.0).

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

The command line interface is built using the argument parsing library [Taywee/args](https://github.com/Taywee/args).

For further details, examples and full documentation of the code, see the page [Photorealistic rendering](https://elisalegnani.github.io/PhotorealisticRendering).
  
## Expectations

More infos coming soon! Stay tuned!

## Contributing

Any contributions are welcome! Please use the [issue tracker](https://github.com/ElisaLegnani/PhotorealisticRendering/issues) to report any bugs or file feature requests.

## License

The code is released under a MIT license. See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

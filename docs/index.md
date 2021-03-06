It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor [Maurizio Tomasi](https://github.com/ziotom78) (University of Milan, AY2020-2021).

π©π»βπ» The main contributors to this repository are [Elisa Legnani](https://github.com/ElisaLegnani) and [Adele Zaini](https://github.com/adelezaini).

# Table of Contents

- [Brief description](#brief-description)
- [Installation](#installation)
- [Usage](#usage)
  - [Create your own photorealistic image](#create-your-own-photorealistic-image)
  - [Convert HDR image into LDR](#convert-hdr-image-into-ldr)
- [Documentation](#documentation)
- [Potentialities and examples](#potentialities-and-examples)
- [Contributing](#contributing)
- [License](#license)


## Brief description

The main functionality of the library is rendering photorealistic images from user instructions on an external input text file. The code features four different backwards raytracing algorithms (onoff, flat, pathtracer, pointlight tracer) and βat the momentβ the scene elements are basic geometric shapes (spheres, planes, boxes). Setting material properties of the objects determines the interaction with light rays, while the observer point of view is represented by a camera with two different projections available (orthogonal and perspective).
This library has another useful functionality that is converting HDR images to LDR ones. The format supported are respectively PFM and PNG/JPG.

Here you can find a detailed explanation of the program usage for better understanding how to generate photorealistic images and to convert images together with the parameters you can set.

π *"Reality leaves a lot to the imagination." β J. Lennon*. Here is the mean, now it's your turn... unleash all your imagination!

# Installation

π Information on how to install and compile the code are on our [GitHub repository](https://github.com/ElisaLegnani/PhotorealisticRendering).

# Usage

You can run the program through the script `raytracer`, located in the `build` directory. 

The code implements two features, that you can call with commands:
- π `render`: creates a photorealistic image;
- π `hdr2ldr`: converts HDR image to LDR.

The basic usage is the following:

```sh
./raytracer [COMMAND] [INPUT_FILENAME] {OPTIONS}

```
The `[INPUT_FILENAME]` represents the input filename with the path where to find it, it is a required argument to pass. There are some examples in the `examples` directory if you want to give it a try or play with the code!

To have more information about available `{OPTIONS}`, a commmand-line help shows more details about program features and parameters:
  
```sh
./raytracer --help
```

The command line interface is built using the argument parsing library [Taywee/args](https://github.com/Taywee/args).

For further details, see below.


## Create your own photorealistic image
  
  In order to create your photorealistic images, you need to give instructions to the code on the scene you want to render. You can write them in a TXT file and run in the  `build` directory: 
  
  ```sh
  ./raytracer render [SCENE_FILENAME] {OPTIONS}
  ```
 
### Scene file
  
  First argument to pass is:
  
  - `[SCENE_FILENAME]`: input scene filename with path to the directory (REQUIRED);
  
  At the moment *(any contribution is welcome!!)*, the implemented elements you can add at the scene are:
  - π? Spheres
  - π§ Planes
  - π¦ Boxes
  - βοΈ PointLight source

whose you can set material and geometric properties. 

π You can find detailed instructions on how to write the scene file at the page [Scene description](https://elisalegnani.github.io/PhotorealisticRendering/scene).

  In the [`examples/render`](https://github.com/ElisaLegnani/PhotorealisticRendering/tree/master/examples/render) directory, some scene file examples are provided to start playing with the code. Expecially, look at `demo.txt` to explore all the potentialities of the code! Our suggestion is to try passing the same scene file with different rendering algorithms while changing the parameters setting, this will surely tickle your creativity! β¨
  
### Parameters
  
  Some parameters are available for users to set properties of the rendered image. You can set them directly in the command line, as explained in `{OPTIONS}` of the help interface (running `./raytracer render`). 
  
  - `-w|--width`: width of the rendered image (default value: `640`);
  - `-h|--height`: height of the rendered image  (default value: `480`);
  - `-r|--renderer|--algorithm`: renderer algorithm: `onoff`/`flat`/`pathtracer`/ π‘ `pointlight` (default: `pathtracer`);
  - `--output|--output_file`: PFM/PNG/JPG file with path to the directory (default: `image_date_time.png` in the directory where the scene file is located);
  - `-n|--rays|--n_rays`: number of rays (default value: `10`);
  - `-d|--depth|--max_depth`: maximum depth (default value: `2`);
  - `--sample|--samples_per_pixel`: number of extracted samples per pixel for antialiasing (default value: `0`, no antialiasing);
  - `-s|--state`: initial seed for the PCG random number generator (default value: `42`);
  - `-i|--seq_id|--seq`: identifier of the sequence produced by the PCG random number generator (default value: `54`);
  - `--a_r`: luminosity normalization factor (default value: `1.0`);
  - `--g_r|--gamma_r`: monitor calibration factor (default value: `1.0`);
  - `-v|--declare_var [...]`: additional float parameters associated to variable identifiers in the scene file, e.g angle of view, camera distance ... (ex: `--declare_var ang=10`).
  
π For further explanation on the fuctionality of each parameter, see the [full documentation](https://elisalegnani.github.io/PhotorealisticRendering/html/index.html).
  
  Here is an example of usage:

  ```sh
  ./raytracer render ../examples/render/demo.txt -w 640 -h 480 -r pathtracer --output ../my_first_image.png -v angle=30
  ```
  
  > **π‘ Warning on pointlight tracer**: the pointlight tracer is not able to render reflective surfaces.
  
  > **β³ Note**: the more parameters values increase, the more the rendering process takes a long time to produce an image.
  
  
### Generate image
  
  You may easily try the code running in the `examples/render` directory:
  
  ```sh
  ./generate-image.sh ANGLE <a-factor>
  ```
  
  which automatically runs the following code:
  
  ```sh
  ../../build/./raytracer render image.txt --declare_var ang=ANGLE --output img/imageANGLE.png --a_r a-factor
  ```
  
  You just need to set the `ANGLE` (deg) from which you look at the scene and optionally also the luminosity `<a-factor>` (default `1`).
  
 <p align="center">
 <img src="https://user-images.githubusercontent.com/59051647/126571722-28e2cfe1-0b22-4961-bc0a-b1d05eb507ec.png" width="700" >
 </p>
  
  The scene description is in `image.txt` file (*support file*).
  
  > *Note:* if you change `image.txt` content, remember to:
  > 
  > 1) adapt the files path properly, you are now in `examples/render` directory;
  > 2) keep `rotation_z(ang)` in the `camera` transformation.
    
  
### Generate animation
  
  In the `examples/render` directory, you may generate an animation of a simple scene described in `image.txt`, rotating 360Β° around the objects.
  
  In order to run the code, you need to:
  - install [ffmpeg](http://ffmpeg.org/) : `sudo apt install ffmpeg` (or `brew install ffmpeg` if you use Homebrew);
  - install [GNU Parallel](https://www.gnu.org/software/parallel/) : `sudo apt install parallel` (or `brew install parallel`);
  - find out the number of cores of your machine: `nproc --all`for Linux or `sysctl -n hw.ncpu` for MacOS, to pass as `NUM_OF_CORES` in the command line;
  
  This is needed to run in parallel the code and speed up the execution, otherwise it would take a very long time.
  
  ```sh
  ./generate-animation.sh NUM_OF_CORES <a-factor> <output_filename>
  ```
  
  You can also set the luminosity `<a-factor>` (default `1`) and the `<output_filename>` (default `video.mp4`).

Here is a suggestive animation of the solar system:

<p align="center">
<img src="https://user-images.githubusercontent.com/59051647/126542691-8f384c07-c567-4276-8116-9e497611da4f.gif" width="500" /> 
</p>

  > β³ Pay attention when passing a scene description that takes long to render: even if we are using a parallel execution there are lots of images to render and can take a while.

### Parallelize image execution

In the `examples/render` directory, another script called `./parallelize-image.sh` has the functionality to parallelize the program execution when rendering the instructions in `image.txt`. The purpose is to speed up the execution particullarly when running the *pathtracer* algorithm. Here is the usage:

```sh
./parallelize-image.sh NUM_OF_CORES <angle> <width> <height> <output_filename> <a-factor> <samples> <n_rays> <depth>
  ```
You just need to set the `NUM_OF_CORES`, while the other parameters are optional. 

> Default values: `angle` 0 `width` 640 `height` 480 `output_filename` image.png ` a-factor` 1 `samples` 0 `n_rays` 10 `depth` 2

## Convert HDR image into LDR

  In the  `build` directory run: 
  
  ```sh
  ./raytracer hdr2ldr [HDR_IMAGE] {OPTIONS}
  ```

  The HDR image format supported is PFM, while LDR ones are PNG and JPG.

  You can also set some parameters according to your preferences in the output image visualisation. You can set them directly in the command line, as explained in `{OPTIONS}` of the help interface (running `./raytracer hdr2ldr`). 
  
  - `[HDR_IMAGE]`: input PFM image with path to the directory (REQUIRED);
  - `--out|--out_file`: PNG/JPG file with path to the directory (default: `input-filename_a_gamma.png` in the directory where the HDR image is located);
  - `-a`: luminosity normalization factor (default value: `0.3`);
  - `-g|--gamma`: monitor calibration factor (default value: `1.0`).


  ```sh
  ./raytracer hdr2ldr [HDR_IMAGE] -a 0.3 -g 1.0 --out <output_file.jpg>
  ```
  
  π For further explanation on the specific meaning of the two parameters, see the [full documentation](https://elisalegnani.github.io/PhotorealisticRendering/html/index.html).

### Example
  
  In the `examples/hdr2ldr` directory, there is a PFM input file called `memorial.pfm`.
  You can play with the code and parameters simply running (in the `build` directory):
  
  ```sh
  ./raytracer hdr2ldr ../examples/hdr2ldr/memorial.pfm -a 0.3 -g 1.0 
  ```

  ![PFM](https://user-images.githubusercontent.com/59051647/123945827-d665fb80-d99e-11eb-9bb2-f5957ce53e94.png)

# Documentation

π The complete documentation of the library is available [here](https://elisalegnani.github.io/PhotorealisticRendering/html/index.html). It was generated with [Doxygen](http://www.doxygen.nl). This is the first version of the documentation, any suggestions are very appreciated!

# Potentialities and examples

π€Ήπ»ββοΈ There is a nice [overview of the library potentialities](https://elisalegnani.github.io/PhotorealisticRendering/explore) with lots of examples, hoping this can tickle your creativity! 

# Contributing

π§ Please open [pull requests](https://github.com/ElisaLegnani/PhotorealisticRendering/pulls) or use the [issue tracker](https://github.com/ElisaLegnani/PhotorealisticRendering/issues) to suggest any code implementations or report bugs. Any contributions are welcome! 

# License

π The code is released under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html). See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

[brief description]

It is developed for the course [*Numerical techniques for photorealistic image generation*](https://www.unimi.it/en/education/degree-programme-courses/2021/numerical-tecniques-photorealistic-image-generation) held by professor [Maurizio Tomasi](https://github.com/ziotom78) (University of Milan, AY2020-2021).

The main contributors to this repository are [Elisa Legnani](https://github.com/ElisaLegnani) and [Adele Zaini](https://github.com/adelezaini).

Here you can find a detailed explanation of the program usage for better understanding how to generate photorealistic images and to convert images from HDR to LDR format, and the parameters you can set. Have fun!

# Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Create your own photorealistic image](#create-your-own-photorealistic-image)
  - [Convert HDR image into LDR](#convert-hdr-image-into-ldr)
- [Documentation](#documentation)
- [Expectations and examples](#expectations-and-examples)
- [Contributing](#contributing)
- [License](#license)

# Installation

Information on how to install and compile the code are on our [GitHub repository](https://github.com/ElisaLegnani/PhotorealisticRendering).

# Usage

You can run the program through the script `raytracer`, located in the `build` directory. 

The code implements two features, that you can call with commands:
- `render`: creates a photorealistic image;
- `hdr2ldr`: converts HDR image to LDR.

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
  
  You can find information on how to write the `[SCENE_FILENAME]` at the page [Scene description](https://elisalegnani.github.io/PhotorealisticRendering/scene).
  In the `examples/render` directory, it is provided `demo.txt` file, where instructions are given to create a demo image for the program to start playing with the code!
  
  Some parameters are available for users to set properties of the rendered image. You can set them directly in the command line, as explained in `{OPTIONS}` of the help interface (running `./raytracer render`). 
  
  - `[SCENE_FILENAME]`: input scene filename (REQUIRED);
  - `-w|--width`: width of the rendered image (default value: `640`);
  - `-h|--height`: height of the rendered image  (default value: `480`);
  - `-r|--renderer|--algorithm`: renderer algorithm: `onoff`/`flat`/`pathtracer`/ 💡 `pointlight` (default: `pathtracer`);
  - `--output|--output_file`: PFM/PNG/JPG file with path to the directory (default: `image_date_time.png` in the directory where the scene file is located);
  - `-n|--rays|--n_rays`: number of rays (default value: `10`);
  - `-d|--depth|--max_depth`: maximum depth (default value: `2`);
  - `--sample|--samples_per_pixel`: number of extracted samples per pixel for antialiasing (default value: `0`, no antialiasing);
  - `-s|--state`: initial seed for the PCG random number generator (default value: `42`);
  - `-i|--seq_id|--seq`: identifier of the sequence produced by the PCG random number generator (default value: `54`);
  - `--a_r`: luminosity normalization factor (0<a<1, default value: `1.0`);
  - `--g_r|--gamma_r`: monitor calibration factor (default value: `1.0`);
  - `-v|--declare_var [...]`: additional float parameters associated to variable identifiers in the scene file, e.g angle of view, camera distance ... (ex: `--declare_var ang=10`).
  
For further explanation on the fuctionality of each parameter, see the documentation[link].
  
  Here is an example of usage:

  ```sh
  ./raytracer render ../examples/render/demo.txt -w 640 -h 480 -r pathtracer --output ../my_first_image.png -v angle=30
  ```
  
  **💡 Warning on pointlight tracer**: the pointlight tracer is not able to render reflective surfaces.
  
  **⏳ Note**: the more parameters values increase, the more the rendering process takes a long time to produce an image.
  
### Demo image
  
  You may easily try the code running in the `examples/render` directory:
  
  ```sh
  ./generate-image.sh ANGLE
  ```
  
  which automatically runs the following code:
  
  ```sh
  ../../build/./raytracer render demo_img.txt --declare_var ang=ANGLE --output img/imageANGLE.png
  ```
  
  You just need to set the `ANGLE` (deg) from which you look at the scene.
  
  ![render](https://user-images.githubusercontent.com/62106779/123851051-0ec3f600-d91b-11eb-9b2d-b5944efe7df6.png)

  If you want to use this script to generate a different image, just change the scene description of the `demo_img.txt` file.
    
  
### Demo animation
  
  In the `examples/render` directory, you may generate an animation of the demo scene, rotating 360° around the objects.
  
  In order to run the code, you need to:
  - install [ffmpeg](http://ffmpeg.org/) : `sudo apt install ffmpeg` (or `brew install ffmpeg` if you use Homebrew);
  - install [GNU Parallel](https://www.gnu.org/software/parallel/) : `sudo apt install parallel` (or `brew install parallel`);
  - find out the number of cores of your machine: `nproc --all`for Linux or `sysctl -n hw.ncpu` for MacOS, to pass as `NUM_OF_CORES` in the command line;
  
  This is needed to run in parallel the code and speed up the execution, otherwise it would take a very long time.
  
  ```sh
  ./generate-animation.sh NUM_OF_CORES
  ```
 
## Convert HDR image into LDR

  In the  `build` directory run: 
  
  ```sh
  ./raytracer hdr2ldr [HDR_IMAGE] {OPTIONS}
  ```

  The HDR image format supported is PFM, while LDR ones are PNG and JPG.

  You can also set some parameters according to your preferences in the output image visualisation. You can set them directly in the command line, as explained in `{OPTIONS}` of the help interface (running `./raytracer hdr2ldr`). 
  
  - `[HDR_IMAGE]`: input PFM image (REQUIRED);
  - `--out|--out_file`: PNG/JPG file with path to the directory (default: `input-filename_a_gamma.png` in the directory where the HDR image is located);
  - `-a`: luminosity normalization factor (0<a<1, default value: `0.3`);
  - `-g|--gamma`: monitor calibration factor (default value: `1.0`).


  ```sh
  ./raytracer hdr2ldr [HDR_IMAGE] -a 0.3 -g 1.0 --out <output_file.jpg>
  ```
  
  For further explanation on the specific meaning of the two parameters, see the documentation[link].

### Example
  
  In the `examples/hdr2ldr` directory, there is a PFM input file called `memorial.pfm`.
  You can play with the code and parameters simply running (in the `build` directory):
  
  ```sh
  ./raytracer hdr2ldr ../examples/hdr2ldr/memorial.pfm -a 0.3 -g 1.0 
  ```

  ![PFM](https://user-images.githubusercontent.com/59051647/123945827-d665fb80-d99e-11eb-9bb2-f5957ce53e94.png)

# Documentation

A link to the complete documentation of the code will be available soon!

# Expectations and examples

More infos coming soon! Stay tuned!

# Contributing

Any contributions are welcome! Please use the [issue tracker](https://github.com/ElisaLegnani/PhotorealisticRendering/issues) to report any bugs, enhancements or file feature requests.

# License

The code is released under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html). See the file [LICENSE.md](https://github.com/ElisaLegnani/PhotorealisticRendering/blob/master/LICENSE.md).

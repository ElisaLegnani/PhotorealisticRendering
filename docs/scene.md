# How to create a scene description

This is a guide to write a .TXT file with the instructions of the scene you want to render. 

In the [`examples/render`](https://github.com/ElisaLegnani/PhotorealisticRendering/tree/master/examples/render) directory, there are some examples to look for inspirations. [Here](https://elisalegnani.github.io/PhotorealisticRendering/html/explore.md) you can have a look to the corrispective results.

🔗 If you desire further information on the meaning of the scene elements and their parameters, look at full descriptions in the [complete documentation](https://elisalegnani.github.io/PhotorealisticRendering/html/index.html).

<img align="right" src="https://user-images.githubusercontent.com/59051647/126191811-f2d0a468-7624-43a2-9da4-fd51d96f4444.png" width="250"/>



### Basic variable definition

Some basic elements are identified as follows:

- point (x, y, z): `{float, float, float}`
- vector (x, y, z): `[float, float, float]`
- color (R, G, B): `<float, float, float>`

> *Note*: The reference system is the one depicted in the side image.

🔗 *Practical advise*: you can find [here](https://ziotom78.github.io/raytracing_course/tomasi-ray-tracing-02a-colors.html#/colori-rgb) a quick way to determine the RGB combination for the desired color (credits to professor [Maurizio Tomasi](https://github.com/ziotom78) (University of Milan)).


## How to create a scene


### Define the parameters of the observer

Via `camera(type, transformation, aspect_ratio, distance)`, where:
- `type`: `orthogonal`/`perspective`
- `transformation`: any transformation you want to apply to the observer's position:
	- none: `identity`
	- `translation(vector)`
	- `scaling(vector)`
	- `rotation_x(angle)`, `rotation_y(angle)`, `rotation_z(angle)`, with angle in degrees

		*Note*: transformations can be conbined together with `*`
- `aspect_ratio` of the screen 
- `distance` of the observer from the scene (needed just if the camera is `perspective`)


### Add some elements to the scene

- Plane: `plane(material_name, transformation)`

- Sphere: `sphere(material_name, transformation)`

- Box: `box(material_name, point1, point2, transformation)`, where `point1` and `point2` are two opposites vertices (front-bottom-left, back-top-right).

- PointLight: `light(point, color, float)`, where `float` is the linear radius ![formula](https://render.githubusercontent.com/render/math?math=lr) used to compute the soild angle subtended by the light at distance ![formula](https://render.githubusercontent.com/render/math?math=d): ![formula](https://render.githubusercontent.com/render/math?math=\Omega=(lr/d)^2)

> *Note*: the PointLight is an element rendered just by the `pointlight` tracer, other renderers will ignore it.


### Define their materials

Before adding elements define their materials:

`material material_name(BRDF(pigment), pigment)`, where:
- `BRDF`: `diffuse`/`specular`
- `pigment`: `uniform(color)`/`checkered(color1, color2, n_steps)`/`image("image_path")`,
	where `n_steps` is an integer number regulating the pattern alternation between the two colors.

> *Note*: the image for the image pigment must be in PFM format



### Define arbitrary parameters

You can also declare parameters `variable_value` to use them in the file itself:

- `variable_name(variable_value)` (e.g. `angle(10)`).

### Declare floating point parameters from the command line

You may wish to change some floating point parameters directly from the command line. This is possible! 

You just need to:
1. include an identifier variable where it was supposed a floating point number:

`camera(perspective, rotation_z(ang) * translation([-1, 0, 1]), 1.333, 1.)`;

2. use the right flag in the command line (as exaplained in details [here](https://elisalegnani.github.io/PhotorealisticRendering)): 

`./raytracer render <scene_file> --declare_var ang=10`.

**🤹🏻‍♀️ Now there nothing else to say than.. have fun!**







	


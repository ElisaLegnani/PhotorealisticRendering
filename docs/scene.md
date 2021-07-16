# How to create a scene description

Give instructions to the code on the scene you want to render in a .TXT file. To have a better meaning of the objects and their parameters, look at their full descriptions in the documentation[link] .

In the [`examples/render` directory](https://github.com/ElisaLegnani/PhotorealisticRendering/tree/master/examples/render), there are some examples to look for inspirations. 

*Note*: define variables as follows:

- point: `{float, float, float}`
- vector: `[float, float, float]`
- color (rgb): `<float, float, float>`


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


### Add some geometric elements to the scene

- Plane: `plane(material_name, transformation)`

- Sphere: `sphere(material_name, transformation)`

- Box: `box(material_name, point1, point2, transformation)`, where `point1` and `point2` are two opposites vertices (front-bottom-left, back-top-right).




### Define their materials

`material material_name(BRDF(pigment), pigment)`, where:
- `BRDF`: `diffuse`/`specular`
- `pigment`: `uniform(color)`/`checkered(color1, color2)`/`image("image_path")`

	*Note*: the image for the image pigment must be in PFM format



### Define arbitrary parameters

You can also set some floating-point parameters to use them in the file. 

They have to be declared as follows: `variable_name(variable_value)` (e.g. `angle(10)`).





	


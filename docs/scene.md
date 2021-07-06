# How to create a scene description

Give instructions to the code on the scene you want to render in a .TXT file.

*Note*: define variables as follows:
point: `{float, float, float}`
vector: `[float, float, float]`
color(rgb): `<float, float, float>`


## How to create a scene


### Define the parameters of the observer

Via `Camera(type, transformation, aspect_ratio, distance)`, where:
- `type`: `orthogonal/perspective`
- `transformation`: any transformation you want to apply to the observer's position:
	- none: `identity`
	- `translation(vector)`
	- `scaling(vector)`
	- `rotation_x(angle)`, `rotation_y(angle)`, `rotation_z(angle)`, with angle in degrees
- `aspect_ratio` of the screen 
- `distance` of the observer from the scene


### Add some geometric elements to the scene

#### `Plane`

#### `Sphere`

#### `Box`


### Define their materials

`material material_name()`


### Define arbitrary parameters

You can also set some parameters to use them in the file. They must be declared as follows:
`variable_name(variable_value)`
e.g. `angle(10)`





	


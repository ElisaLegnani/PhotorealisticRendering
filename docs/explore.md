# Explore library potentialities

Here is a presentation of the program usage showing some examples to explore the potentialities of this raytracing library.

The scene files used to render these images are in the [`examples/render`](https://github.com/ElisaLegnani/PhotorealisticRendering/tree/master/examples/render) directory, so you can try yourself!

> *Note*: all the following images are rendered with antialiasing to sample each pixel properly (9 samples per pixel).

## Demo image

> Scene filename: `demo.txt`

Here are gathered all the main functionalities of the library, in particular regarding **path tracer**. Note how it can render light interaction so naturally with total reflective, diffusive and emitting surfaces on the different shapes (spheres, boxes and planes).

<p align="center">
       <img width="700" src=https://user-images.githubusercontent.com/59051647/126571722-28e2cfe1-0b22-4961-bc0a-b1d05eb507ec.png>
  </p>
  
Here is a comparison with the other two tracers (flat and pointlight tracer) to better appreciate the advantages of using the pathtracer:

<p align="center">
       <img width="300" src=https://user-images.githubusercontent.com/59051647/126571125-4ab12267-9e95-4d17-b2ee-85340a969097.png>
       <img width="300" src=https://user-images.githubusercontent.com/59051647/126571444-389e17d6-3c6b-4b62-9397-e282843b4dcb.png>
       <img width="300" src=https://user-images.githubusercontent.com/59051647/126570183-d4ac3e89-4158-41e7-a75a-bd2246c958b5.png>
  </p>


The last image is an edited version for the pointlight renderer because of its inability to represent reflective surfaces.

> Scene filename: `demo_pointlight.txt`

This image is so representative of the pontentials of the code... now let's start exploring a bit more! 🤹🏻‍♀️

## Sunset

> Scene filename: `sunset.txt`

Here you can see how a **pointlight tracer** is able to wonderfully render a situation where the light source is very intense and point-like (or far away, as the sun approaching the horizon...). Look how it can render the romantic long shadows of sunsets!

  <p align="center">
       <img width="600" src=https://user-images.githubusercontent.com/59051647/126517271-032815f0-6f9c-4470-869a-6a9f5b4b3a6b.png>
  </p>

  
You can appreciate this tracer looking at the same scene rendered with pathtracer and the flat render:

<p align="center">
  <img src="https://user-images.githubusercontent.com/59051647/126517847-ff9d1a21-bef5-49e0-a7d7-ac60bb9aac40.png" width="400" />
  <img src="https://user-images.githubusercontent.com/59051647/126517959-44c6dc55-91d5-4fe4-90c8-c040d588ad03.png" width="400" /> 
</p>



## Chess player

> Scene filename: `chess.txt`

This image simulates a chess game situation. It was an excuse to overuse the checkered pattern (not use in the demo image) and to make the **antialiasing** property evident (9 samples per pixel were here extracted on the right image). The pointlight renderer is perfect to simulate the intense atmosphere of this game, as well as to better show the antialiasing.

<p align="center">
  <img src="https://user-images.githubusercontent.com/59051647/126518747-db4771bf-9ebb-4a30-b160-cce379b9cc99.png" width="450" />
  <img src="https://user-images.githubusercontent.com/59051647/126518689-ed5d9648-946c-4d82-a5b7-ac02e56d9fa8.png" width="450" /> 
</p>

Look at this animation to better appreciate the differences!

<p align="center">
<img src="https://user-images.githubusercontent.com/59051647/126524419-2f030c29-15e4-4d3b-a76c-b62300ed0de2.gif" width="700" />
</p>

> Advise: tone down the image setting the luminosity factor `--a_r 0.6` in the command line if you want to reproduce this image yourself.

## Fireflies

> Scene filename: `fireflies.txt`

The **onoff renderer** is usually used for debugging purposes when starting writing done the code, but you know what? I'm seeing fireflies dancing in a dark night!

<p align="center">
  <img src="https://user-images.githubusercontent.com/59051647/126528098-21cce91a-57f4-49f3-9ab1-c2880919913e.png" width="450" />
  <img src="https://user-images.githubusercontent.com/59051647/126528177-97d570dc-aff1-4864-be48-e49be60885ce.gif" width="450" /> 
</p>

## Solar system

> Scene filename: `solar_system.txt`

Someone may think that the **flat renderer** is a second-class renderer, but it can be used for simple images with dark background and has the great advantage of being extremely quick... Look how it renders the solar system!

<p align="center">
<img src="https://user-images.githubusercontent.com/59051647/126561115-6b933ad1-8c21-4617-9b4c-97bdb33c4818.png" width="600" /> 
</p>

Being extremely quick it takes little time to generate this wonderful animation!

<p align="center">
<img src="https://user-images.githubusercontent.com/59051647/126542691-8f384c07-c567-4276-8116-9e497611da4f.gif" width="500" /> 
</p>

> Advise: tone down the image setting the luminosity factor `--a_r 0.2` in the command line if you want to reproduce this image yourself.


Here an example rendered with the poinlight tracer:

<p align="center">
<img src="https://user-images.githubusercontent.com/59051647/126561337-d63b8346-5fe4-49f5-8262-5e966163947a.png" width="500" /> 
</p>

## Cornell box

> Scene filename: `cornell_box.txt`

The one and only cornell box! It is used in photorealistic rendering to test the accuracy of the code.
[to be continued...]

Voilà! Here is just an invitation to contribute ❣️


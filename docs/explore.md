# Explore library potentialities

Here is a presentation of the program usage showing some examples to explore the potentialities of this raytracing library.

The scene files used to render these images are in the [`examples/render`](https://github.com/ElisaLegnani/PhotorealisticRendering/tree/master/examples/render) directory, so you can try yourself!

> *Note*: all the following images are rendered with the antialiasing option to sample each pixel properly (9 samples per pixel).

## Demo image

Here are gathered all the main functionalities of the code: you can see how the three tracers (flat, path tracer, pointlight tracer) render geometric objects with different optical properties.


Little edited version for the pointlight renderer because of its inability to represent reflective surfaces.

Okay, now it's time to play! 🤹🏻‍♀️

## Sunset

Here you can see how a pointlight tracer is able to wonderfully render a situation where the light source is very intense and point-like (or far away, as the sun approaching the horizon...). Look how it can render the romantic long shadows of sunsets!

</details>
  <p align="center">
       <img width="600" src=https://user-images.githubusercontent.com/59051647/126517271-032815f0-6f9c-4470-869a-6a9f5b4b3a6b.png>
  </p>

  
Look how much it looses when render with pathtracer and the flat render:

<p align="center">
  <img src="https://user-images.githubusercontent.com/59051647/126517847-ff9d1a21-bef5-49e0-a7d7-ac60bb9aac40.png" width="400" />
  <img src="https://user-images.githubusercontent.com/59051647/126517959-44c6dc55-91d5-4fe4-90c8-c040d588ad03.png" width="400" /> 
</p>



## Chess player

This image simulates a chess game situation. It was an excuse to overuse the checkered pattern (not use in the demo image) and to make the antialiasing property evident (9 samples per pixel were here extracted).

<p align="center">
  <img src="https://user-images.githubusercontent.com/59051647/126518747-db4771bf-9ebb-4a30-b160-cce379b9cc99.png" width="450" />
  <img src="https://user-images.githubusercontent.com/59051647/126518689-ed5d9648-946c-4d82-a5b7-ac02e56d9fa8.png" width="450" /> 
</p>

## Cornell box

The one and only cornell box! It is used in photorealistic rendering to test the accuracy of the code.
[to be continued...]

## Solar system

Someone may think that the flat renderer is a second-class renderer, but it can be used for simple images with dark background and has the great advantage of being extremely quick. Look how it renders the solar system!

## Fireflies

The onoff renderer is usually used for debugging purposes when starting writing done the code, but you know what? I'm seeing fireflies dancing in a dark night!

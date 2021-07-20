# Explore library potentialities

Here is a presentation of the program usage showing some examples to explore the potentialities of this raytracing library.

The scene files used to render these images are in the [`examples/render`](https://github.com/ElisaLegnani/PhotorealisticRendering/tree/master/examples/render) directory, so you can try yourself!

## Demo image

Here are gathered all the main functionalities of the code: you can see how the three tracers (flat, path tracer, pointlight tracer) render geometric objects with different optical properties.


Little edited version for the pointlight renderer because of its inability to represent reflective surfaces.

Okay, now it's time to play! 🤹🏻‍♀️

## Sunset

Here you can see how a pointlight tracer is able to wonderfully render a situation where the light source is very intense and point-like (or far away, as the sun approaching the horizon...). Look how it can render the romantic long shadows of sunsets!


## Chess player

This image simulates a chess game situation. It was an excuse to overuse the checkered pattern (not use in the demo image) and to make the antialiasing property evident, implemented to sample each pixel properly (9 samples per pixel were here extracted).


## Cornell box

The one and only cornell box! It is used in photorealistic rendering to test the accuracy of the code.
[to be continued...]

## Solar system

Someone may think that the flat renderer is a second-class renderer, but it can be used for simple images with dark background and has the great advantage of being extremely quick. Look how it renders the solar system!

## Fireflies

The onoff renderer is usually used for debugging purposes when starting writing done the code, but you know what? I'm seeing fireflies dancing in a dark night!

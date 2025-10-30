# Mandelbrot set demo
This demo lets you explore the Mandelbrot set fractal.
It demonstrates the use of compute shaders and buffer objects in Nymphaea.

<img src="https://github.com/FiveN1/nymphaea/blob/main/demos/Mandelbrot_set_demo/res/img/screenshots.png" alt="Mandelbrot set demo image" width="512"/>

## Controls
use `WSAD` for movement and `QE` for zoom.

## About
Computes the Mandelbrot set fractal on the GPU, using a compute shader.
The fractal is rendered to a texture, that is displayed on a 2D quad that fills the whole screen (viewport).
With the use of SSBOs, data is passed from the CPU to the compute shader (data like camera position, color scheme ... and more)

## How to run?
Run `build.bat` and type `compile` or `c` to compile the program and run it.
> [!NOTE]
> This builds the project using VisualStudio 2022!

> [!TIP]
> Use any of the premake commands *(if you type `help` you will get a list of them)* to generate the project files for any editor/compiler you like!
> Then you can build the project from the generated project files.

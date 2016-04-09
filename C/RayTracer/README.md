# Ray Tracer

A ray tracer programmed in C to render 3D image a scene.  The program utilizes the X11 Window system. Parameters for the window size, number of objects, and levels of recursion are defined at the top of raytracer.c file. 

![Ray Tracer](https://raw.githubusercontent.com/ericbachmeier5/School/master/C/RayTracer/raytracer.png)

## To Install:

In terminal, clone the repository as follows in your working directory by typing:

```
$ git clone git@github.com:ericbachmeier5/RayTracer.git
```

Install X11 Window system if you don't already have it.


- [Download X11 here](https://dl.bintray.com/xquartz/legacy-downloads/SL/XQuartz-2.7.8.dmg)

Install the GNU compiler to create the executable needed. In terminal, type the following:

```
$ xcode-select --install
```


## To Run:

```
$ cc -std=c99 -o raytracer raytracer.c -I/opt/X11/include -L/opt/X11/lib -lX11 -lm
$ ./raytracer
```

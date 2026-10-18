# HW3D

A program that creates random 3D triangles, finds which ones intersect, and shows them in a 3D window. Intersecting triangles are drawn in red.

## How it works

1. You enter the number of triangles `n`.
2. The program creates `n` random triangles.
3. A spatial grid finds pairs of triangles that may intersect.
4. The Möller algorithm checks only these pairs.
5. The scene is drawn with OpenGL.

## Requirements

- CMake 3.16 or newer
- C++ compiler
- OpenGL
- GLFW
- GLM

## Build

```
mkdir build
cd build
cmake ..
make
cd ..
```

## Run

Run the program from the project folder (it needs the `shaders` folder):

```
./build/HW3D
```

Then type the number of triangles and press Enter.

## Controls

- Hold the mouse button and move the mouse: look around
- `W` / `S`: move forward / back
- `A` / `D`: move left / right

## Speed

| Triangles | Loading time |
|-----------|--------------|
| 10^6      | about 7 seconds |
| 10^7      | about 40 seconds |

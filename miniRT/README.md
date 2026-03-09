*This project has been created as part of the 42 curriculum by mrys, mberczyn.*

# miniRT

## Description
miniRT is a small ray tracer written in C. The program reads a scene description file (`.rt`), renders the scene using ray tracing, and displays the resulting image in a window using MiniLibX.

The goal of the project is to implement the core components of a minimal rendering pipeline:
- camera model (field of view, view direction)
- ray generation per pixel
- ray–object intersections (sphere, plane, cylinder)
- lighting (ambient + diffuse) and hard shadows

## Features
Mandatory features implemented:
- Objects: sphere, plane, cylinder
- Camera: position, orientation vector, horizontal FOV
- Lighting: ambient + diffuse (Lambert) with hard shadows (shadow rays)
- Transforms: translation and rotation for supported primitives (per subject constraints)
- Display: rendering shown in an MLX window; clean exit via ESC and window close

## Input Format and Constraints (`.rt`)
Scene files describe elements using identifiers such as 
    `A` -> ambient lighting
    `C` -> camera,
    `L` -> lights,
    `sp` -> sphere,
    `pl` -> plane,
    `cy` ->cylinder.

### Common constraints
- **RGB colors** are integers in **[0, 255]** and written as `R,G,B` (e.g., `255,120,0`).
- **Ratios** (ambient intensity, light brightness) are in **[0.0, 1.0]**.
- **Orientation vectors** (camera direction, plane normal, cylinder axis) must be **normalized** (unit length).
- **FOV** is in degrees and must be in **[0, 180]** (horizontal FOV for the camera).

### Element summary (format of .rt file)
- `A <ratio> <R,G,B>`
- `C <x,y,z> <nx,ny,nz> <fov>`
- `L <x,y,z> <ratio> <R,G,B>` (light color may be unused in mandatory part)
- `sp <x,y,z> <diameter> <R,G,B>`
- `pl <x,y,z> <nx,ny,nz> <R,G,B>`
- `cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>`

## Instructions

### Build
```bash
make
# BZFlag Model Writer

BZFlag currently does not use an external model to load the tank geometry/materials. Everything is just hard-coded OpenGL calls. This code implements some of the OpenGL C API to allow converting those OpenGL calls to a Wavefront OBJ file.

## License and Copyright

This uses some types and constants from the Mesa gl.h file under the MIT license.

This uses some code and textures from BZFlag, copyright Tim Riker. It is dual-licensed LGPL 2.1 and Apache 2.0, and I am choose to use it under the LGPL 2.1.

The original code here is licensed under the LGPL 2.1 as well.

See the full text of the LGPL 2.1 in LICENSE.md. The MIT license for gl.h is in the header of glite.h.

## Compiling

Note that this uses GLM, so install that first and make sure that cmake can find it.

```
mkdir build
cd build
cmake ..
make
```

## Usage

From the top level source directory, run: ```./build/bzflag-model-writer```

The models and materials will be written to the current working directory. Note that the model uses Z up. If importing, in Wings3D check "Swap Y and Z Axes" and in Blender set Up to Z Up.

## Files/information from BZFlag
Several files are from src/geometry/ and src/geometry/models/tank/

Color information is from src/common/Team.cxx
